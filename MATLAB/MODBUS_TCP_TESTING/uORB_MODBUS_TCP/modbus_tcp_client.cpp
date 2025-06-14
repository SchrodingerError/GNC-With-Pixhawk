#include "modbus_tcp_client.h"
#include <sys/select.h>

// --- Helper: Compute maximum read response size based on configured counts.
int ModbusTCPClient::computeMaxReadResponseSize() const {
    // For registers: 9 + (count * 2)
    int rIR = 9 + (numInputRegisters * 2);
    int rHR = 9 + (numHoldingRegisters * 2);
    // For coils/discrete: 9 + ceil(count/8)
    int rCoils = 9 + ((numCoils + 7) / 8);
    int rDI = 9 + ((numDiscreteInputs + 7) / 8);
    int maxVal = rIR;
    if (rHR > maxVal) maxVal = rHR;
    if (rCoils > maxVal) maxVal = rCoils;
    if (rDI > maxVal) maxVal = rDI;
    return maxVal;
}

// --- Helper: Compute maximum write request size based on configured counts.
int ModbusTCPClient::computeMaxWriteRequestSize() const {
    // For write multiple holding registers: 13 + (numHoldingRegisters * 2)
    int wHR = 13 + (numHoldingRegisters * 2);
    // For write multiple coils: 13 + ceil(numCoils/8)
    int wCoils = 13 + ((numCoils + 7) / 8);
    return (wHR > wCoils) ? wHR : wCoils;
}

// --- Constructors ---
ModbusTCPClient::ModbusTCPClient(const char* ip, int port, int numCoils, int numDI, int numIR, int numHR,
    int startCoils, int startDI, int startIR, int startHR)
    : serverIP(ip), serverPort(port), socketFD(-1), transactionID(1),
      numCoils(numCoils), numDiscreteInputs(numDI), numInputRegisters(numIR), numHoldingRegisters(numHR),
      startCoils(startCoils), startDiscreteInputs(startDI), startInputRegisters(startIR), startHoldingRegisters(startHR) {

    // Allocate internal storage for automatic readAll()/writeAll() mode.
    coilsRead = new bool[numCoils]();
    coilsWrite = new bool[numCoils]();
    discreteInputs = new bool[numDI]();
    inputRegisters = new uint16_t[numIR]();
    holdingRegistersRead = new uint16_t[numHR]();
    holdingRegistersWrite = new uint16_t[numHR]();

    // Allocate shared communication buffers.
    commRequestBufferSize = computeMaxWriteRequestSize();  // Worst-case request size.
    commResponseBufferSize = computeMaxReadResponseSize();  // Worst-case response size.
    commRequestBuffer = new uint8_t[commRequestBufferSize];
    commResponseBuffer = new uint8_t[commResponseBufferSize];

    // Initialize the socket mutex.
    pthread_mutex_init(&socketMutex, NULL);
}

ModbusTCPClient::ModbusTCPClient(const char* ip, int port)
    : serverIP(ip), serverPort(port), socketFD(-1), transactionID(1) {
    // This constructor is for manual MODBUS function calls; readAll/writeAll will not be available.
    coilsRead = nullptr;
    coilsWrite = nullptr;
    discreteInputs = nullptr;
    inputRegisters = nullptr;
    holdingRegistersRead = nullptr;
    holdingRegistersWrite = nullptr;

    // Allocate default communication buffers for simple operations.
    commRequestBufferSize = 12;
    commResponseBufferSize = 9 + (256 * 2); // Default for 256 registers worst-case.
    commRequestBuffer = new uint8_t[commRequestBufferSize];
    commResponseBuffer = new uint8_t[commResponseBufferSize];

    // Initialize the socket mutex.
    pthread_mutex_init(&socketMutex, NULL);
}

ModbusTCPClient::~ModbusTCPClient() {
    delete[] coilsRead;
    delete[] coilsWrite;
    delete[] discreteInputs;
    delete[] inputRegisters;
    delete[] holdingRegistersRead;
    delete[] holdingRegistersWrite;

    delete[] commRequestBuffer;
    delete[] commResponseBuffer;

    // Destroy the pthread mutex.
    pthread_mutex_destroy(&socketMutex);
}

void ModbusTCPClient::setStartAddresses(int startCoils, int startDI, int startIR, int startHR) {
    this->startCoils = startCoils;
    this->startDiscreteInputs = startDI;
    this->startInputRegisters = startIR;
    this->startHoldingRegisters = startHR;
}

// --- Connection Functions ---
bool ModbusTCPClient::connectServer() {
    pthread_mutex_lock(&socketMutex);
    if (socketFD != -1) {
        pthread_mutex_unlock(&socketMutex);
        return true;
    }
    for (int attempts = 0; attempts < 5; attempts++) {
        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0) {
            printf("MODBUS_TCP_CLIENT: Could not create socket\n");
            pthread_mutex_unlock(&socketMutex);
            return false;
        }
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);
        printf("MODBUS_TCP_CLIENT: Attempting to connect (Try %d)...\n", attempts + 1);
        if (connect(socketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0) {
            printf("MODBUS_TCP_CLIENT: Connected to %s:%d\n", serverIP, serverPort);
            pthread_mutex_unlock(&socketMutex);
            return true;
        }
        printf("MODBUS_TCP_CLIENT: Connection failed, retrying...\n");
        pthread_mutex_unlock(&socketMutex);
        disconnectServer();
        usleep(100000);
    }
    pthread_mutex_unlock(&socketMutex);
    return false;
}

void ModbusTCPClient::disconnectServer() {
    pthread_mutex_lock(&socketMutex);
    if (socketFD != -1) {
        close(socketFD);
        socketFD = -1;
        printf("MODBUS_TCP_CLIENT: Disconnected from server\n");
    }
    pthread_mutex_unlock(&socketMutex);
}

bool ModbusTCPClient::isConnected() const {
    return socketFD != -1;
}

bool ModbusTCPClient::reconnectServer() {
    disconnectServer();
    return connectServer();
}

void ModbusTCPClient::setTimeout(int milliseconds) {
    timeoutMilliseconds = milliseconds;
    printf("MODBUS_TCP_CLIENT: Timeout set to %d ms\n", timeoutMilliseconds);
}

bool ModbusTCPClient::sendRequest(uint8_t* request, int requestSize) {
    if (socketFD == -1) {
        printf("MODBUS_TCP_CLIENT: Not connected. Cannot send request.\n");
        return false;
    }
    int bytesSent = write(socketFD, request, requestSize);
    if (bytesSent <= 0) {
        printf("MODBUS_TCP_CLIENT: Write failed, disconnecting...\n");
        disconnectServer();
        return false;
    }
    return bytesSent == requestSize;
}

bool ModbusTCPClient::receiveResponse(uint8_t* response, int expectedSize) {
    int totalBytesReceived = 0;
    while (totalBytesReceived < expectedSize) {
        struct timeval timeout;
        timeout.tv_sec = timeoutMilliseconds / 1000;
        timeout.tv_usec = (timeoutMilliseconds % 1000) * 1000;
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(socketFD, &read_fds);
        int ready = select(socketFD + 1, &read_fds, NULL, NULL, &timeout);
        if (ready == 0) {
            printf("MODBUS_TCP_CLIENT: Timeout waiting for response. Disconnecting...\n");
            disconnectServer();
            return false;
        } else if (ready < 0) {
            printf("MODBUS_TCP_CLIENT: Select failed. Disconnecting...\n");
            disconnectServer();
            return false;
        }
        int bytesReceived = read(socketFD, response + totalBytesReceived, expectedSize - totalBytesReceived);
        if (bytesReceived <= 0) {
            printf("MODBUS_TCP_CLIENT: Connection lost while reading. Disconnecting...\n");
            disconnectServer();
            return false;
        }
        totalBytesReceived += bytesReceived;
    }
    return true;
}

// --- Message Building Functions ---
void ModbusTCPClient::buildReadRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t startAddr, uint16_t quantity) {
    transactionID++;

    // Transaction ID
    buffer[0] = transactionID >> 8;
    buffer[1] = transactionID & 0xFF;
    // Protocol ID, always 00 00
    buffer[2] = 0x00;
    buffer[3] = 0x00;
    // Length (remaining bytes after Unit ID)
    buffer[4] = 0x00;
    buffer[5] = 0x06;
    // Unit ID (Slave Address)
    buffer[6] = 0x01;
    // Function code
    buffer[7] = static_cast<uint8_t>(functionCode);
    // Start Address
    buffer[8] = startAddr >> 8;
    buffer[9] = startAddr & 0xFF;
    // Quantity (How many coils/registers to read)
    buffer[10] = quantity >> 8;
    buffer[11] = quantity & 0xFF;
}

void ModbusTCPClient::buildWriteSingleRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t address, uint16_t value) {
    transactionID++;
    buffer[0] = transactionID >> 8;
    buffer[1] = transactionID & 0xFF;
    buffer[2] = 0x00;
    buffer[3] = 0x00;
    buffer[4] = 0x00;
    buffer[5] = 0x06;
    buffer[6] = 0x01;
    buffer[7] = static_cast<uint8_t>(functionCode);
    buffer[8] = address >> 8;
    buffer[9] = address & 0xFF;
    buffer[10] = value >> 8;
    buffer[11] = value & 0xFF;
}

void ModbusTCPClient::buildWriteMultipleRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t address, uint16_t count, const void* values, uint8_t byteCount) {
    transactionID++;

    // MODBUS TCP Header
    buffer[0] = transactionID >> 8;
    buffer[1] = transactionID & 0xFF;
    buffer[2] = 0x00;  // Protocol ID (always 0x0000)
    buffer[3] = 0x00;
    buffer[4] = 0x00;  // Length (remaining bytes after Unit ID)
    buffer[5] = 7 + byteCount;
    buffer[6] = 0x01;  // Unit ID
    buffer[7] = static_cast<uint8_t>(functionCode);  // Function Code (0x0F for coils, 0x10 for registers)
    buffer[8] = address >> 8;  // Start address high byte
    buffer[9] = address & 0xFF;  // Start address low byte
    buffer[10] = count >> 8;  // Quantity high byte
    buffer[11] = count & 0xFF;  // Quantity low byte
    buffer[12] = byteCount;  // Byte count

    // Copy data payload manually (instead of memcpy)
    const uint8_t* data = (const uint8_t*)values;
    for (uint8_t i = 0; i < byteCount; i++) {
        buffer[13 + i] = data[i];
    }
}

// --- High-Level Read/Write Functions ---

ModbusError ModbusTCPClient::readCoil(int address, bool &coilState) {
    pthread_mutex_lock(&socketMutex);
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_COIL, address, 1);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);    
        return ModbusError::TIMEOUT;
    }
    // Expect 10 bytes: header (9 bytes) + 1 byte data
    int expectedSize = 9 + 1;
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
        
    // Handle MODBUS exception responses (0x80 + function code)
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    // Ensure the function code in the response matches the request.
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_COIL)) {
        pthread_mutex_unlock(&socketMutex);    
        return ModbusError::INVALID_RESPONSE;
    }
    // Set the internal coil state from the response    
    coilState = (commResponseBuffer[9] & 0x01) != 0;
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readMultipleCoils(int address, int count, bool coilStates[]) {
    if (count < 1 || count > 2000) { // MODBUS limits: 1-2000 coils per request
        printf("MODBUS_TCP_CLIENT: Invalid coil count (1-2000 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }
    pthread_mutex_lock(&socketMutex);
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_COIL, address, count);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Expected response size: fixed header (9 bytes) + variable byte count.
    int byteCount = (count + 7) / 8; // 1 byte per 8 coils
    int expectedSize = 9 + byteCount;
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Handle MODBUS exception responses (0x80 + function code)
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: MODBUS Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    // Ensure the function code in the response matches the request.
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_COIL)) {
        pthread_mutex_unlock(&socketMutex);    
        return ModbusError::INVALID_RESPONSE;
    }
    // Extract coil values: data starts at index 9.
    for (int i = 0; i < count; i++) {
        int byteIndex = 9 + (i / 8);
        int bitIndex = i % 8;
        coilStates[i] = (commResponseBuffer[byteIndex] >> bitIndex) & 0x01;
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readDiscreteInput(int address, bool &discreteInput) {
    pthread_mutex_lock(&socketMutex);
    // Build a request for one discrete input (quantity = 1)
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_DISCRETE_INPUT, address, 1);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Expect 10 bytes: header (9 bytes) + 1 byte data
    int expectedSize = 9 + 1;
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Check for MODBUS exception response
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    // Validate function code
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_DISCRETE_INPUT)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::INVALID_RESPONSE;
    }
    // Extract the discrete input state (first bit of the data byte at index 9)
    discreteInput = (commResponseBuffer[9] & 0x01) != 0;
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readMultipleDiscreteInputs(int address, int count, bool discreteInputsArray[]) {
    if (count < 1 || count > 2000) { // MODBUS limits: 1-2000 discrete inputs per request
        printf("MODBUS_TCP_CLIENT: Invalid discrete input count (1- allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }
    pthread_mutex_lock(&socketMutex);
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_DISCRETE_INPUT, address, count);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Expected response: 9-byte header + ceil(count/8) bytes of data
    int byteCount = (count + 7) / 8;
    int expectedSize = 9 + byteCount;
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_DISCRETE_INPUT)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::INVALID_RESPONSE;
    }
    // Extract each discrete input bit from the data starting at index 9
    for (int i = 0; i < count; i++) {
        int byteIndex = 9 + (i / 8);
        int bitIndex = i % 8;
        discreteInputsArray[i] = (commResponseBuffer[byteIndex] >> bitIndex) & 0x01;
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readHoldingRegister(int address, uint16_t &holdingRegister) {
    pthread_mutex_lock(&socketMutex);
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_HOLDING_REGISTER, address, 1);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // For one register, expect 9-byte header + 2 bytes data = 11 bytes total
    int expectedSize = 9 + 2;
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_HOLDING_REGISTER)) {
        pthread_mutex_unlock(&socketMutex);    
        return ModbusError::INVALID_RESPONSE;
    }
    // Extract the register value (big-endian: data at indices 9 and 10)
    holdingRegister = (commResponseBuffer[9] << 8) | commResponseBuffer[10];
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readMultipleHoldingRegisters(int address, int count, uint16_t holdingRegistersArray[]) {
    if (count < 1 || count > 125) { // MODBUS limits: 1-125 registers per request
        printf("MODBUS_TCP_CLIENT: Invalid holding register count (1-125 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }
    pthread_mutex_lock(&socketMutex);
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_HOLDING_REGISTER, address, count);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // For multiple registers: expected size = 9 + (count * 2)
    int expectedSize = 9 + (count * 2);
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_HOLDING_REGISTER)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::INVALID_RESPONSE;
    }
    // Extract each register value (each register is 2 bytes, big-endian)
    for (int i = 0; i < count; i++) {
        holdingRegistersArray[i] = (commResponseBuffer[9 + (i * 2)] << 8) | commResponseBuffer[10 + (i * 2)];
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readInputRegister(int address, uint16_t &inputRegister) {
    pthread_mutex_lock(&socketMutex);
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_INPUT_REGISTER, address, 1);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // For one input register: expected size = 9 + 2 = 11 bytes
    int expectedSize = 9 + 2;
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_INPUT_REGISTER)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::INVALID_RESPONSE;
    }
    inputRegister = (commResponseBuffer[9] << 8) | commResponseBuffer[10];
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readMultipleInputRegisters(int address, int count, uint16_t inputRegistersArray[]) {
    if (count < 1 || count > 125) { // MODBUS limits: 1-125 registers per request
        printf("MODBUS_TCP_CLIENT: Invalid input register count (1-125 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }
    pthread_mutex_lock(&socketMutex);
    buildReadRequest(commRequestBuffer, ModbusFunction::READ_INPUT_REGISTER, address, count);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // For multiple registers: expected size = 9 + (count * 2)
    int expectedSize = 9 + (count * 2);
    if (!receiveResponse(commResponseBuffer, expectedSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    if (commResponseBuffer[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Exception Code %02X\n", commResponseBuffer[8]);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::EXCEPTION_RESPONSE;
    }
    if (commResponseBuffer[7] != static_cast<uint8_t>(ModbusFunction::READ_INPUT_REGISTER)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::INVALID_RESPONSE;
    }
    // Extract each register value (each register is 2 bytes, big-endian)
    for (int i = 0; i < count; i++) {
        inputRegistersArray[i] = (commResponseBuffer[9 + (i * 2)] << 8) | commResponseBuffer[10 + (i * 2)];
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::writeCoil(int address, bool value) {
    pthread_mutex_lock(&socketMutex);
    buildWriteSingleRequest(commRequestBuffer, ModbusFunction::WRITE_SINGLE_COIL, address, value ? 0xFF00 : 0x0000);
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    if (!receiveResponse(commResponseBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    for (int i = 0; i < 12; i++) {
        if (commRequestBuffer[i] != commResponseBuffer[i]) {
            printf("MODBUS_TCP_CLIENT: Response does not match request!\n");
            pthread_mutex_unlock(&socketMutex);
            return ModbusError::INVALID_RESPONSE;
        }
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::writeMultipleCoils(int address, int count, const bool values[]) {
    pthread_mutex_lock(&socketMutex);

    if (count < 1 || count > numCoils) {
        printf("MODBUS_TCP_CLIENT: Invalid coil count (1-%d allowed)\n", numCoils);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::INVALID_RESPONSE;
    }

    // Each coil is a bit; compute number of bytes required.
    int byteCount = (count + 7) / 8;
    uint8_t coilData[byteCount];
    // Initialize coilData to 0.
    for (int i = 0; i < byteCount; i++) {
        coilData[i] = 0;
    }
    // Pack each boolean value into the appropriate bit.
    for (int i = 0; i < count; i++) {
        if (values[i]) {
            coilData[i / 8] |= (1 << (i % 8));
        }
    }
    // Build the write multiple coils request.
    // Request size is 13 + byteCount.
    int requestSize = 13 + byteCount;
    buildWriteMultipleRequest(commRequestBuffer, ModbusFunction::WRITE_MULTIPLE_COILS, address, count, coilData, byteCount);
    // Send the request.
    if (!sendRequest(commRequestBuffer, requestSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }

    // The expected response size for a write multiple coils request is always 12 bytes.
    int expectedResponseSize = 12;
    if (!receiveResponse(commResponseBuffer, expectedResponseSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }

    // Validate that the response echoes the request correctly.
    // According to MODBUS TCP, the response echoes the first 10 bytes (except byte 5, which is the length field).
    for (int i = 0; i < 10; i++) {
        if (i == 5) continue;  // Skip the length field.
        if (commRequestBuffer[i] != commResponseBuffer[i]) {
            printf("MODBUS_TCP_CLIENT: Response does not match request at byte %d!\n", i);
            pthread_mutex_unlock(&socketMutex);
            return ModbusError::INVALID_RESPONSE;
        }
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::writeHoldingRegister(int address, uint16_t value) {
    pthread_mutex_lock(&socketMutex);
    // Build the write single holding register request.
    buildWriteSingleRequest(commRequestBuffer, ModbusFunction::WRITE_SINGLE_HOLDING_REGISTER, address, value);
    // Send the 12-byte request.
    if (!sendRequest(commRequestBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Expect a full 12-byte echo response.
    if (!receiveResponse(commResponseBuffer, 12)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Validate that the entire 12-byte response matches the request.
    for (int i = 0; i < 12; i++) {
        if (commRequestBuffer[i] != commResponseBuffer[i]) {
            printf("MODBUS_TCP_CLIENT: Response does not match request at byte %d!\n", i);
            pthread_mutex_unlock(&socketMutex);
            return ModbusError::INVALID_RESPONSE;
        }
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::writeMultipleHoldingRegisters(int address, int count, const uint16_t values[]) {
    pthread_mutex_lock(&socketMutex);
    if (count < 1 || count > numHoldingRegisters) {
        printf("MODBUS_TCP_CLIENT: Invalid register count (1-%d allowed)\n", numHoldingRegisters);
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::INVALID_RESPONSE;
    }
    // Each register is 2 bytes.
    int byteCount = count * 2;
    uint8_t registerData[byteCount];
    // Convert each register value into big-endian format.
    for (int i = 0; i < count; i++) {
        registerData[i * 2] = values[i] >> 8;         // High byte
        registerData[i * 2 + 1] = values[i] & 0xFF;     // Low byte
    }
    // Build the write multiple holding registers request.
    // Request size is 13 + byteCount.
    int requestSize = 13 + byteCount;
    buildWriteMultipleRequest(commRequestBuffer, ModbusFunction::WRITE_MULTIPLE_HOLDING_REGISTERS, address, count, registerData, byteCount);
    // Send the request.
    if (!sendRequest(commRequestBuffer, requestSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // The expected response size for a write multiple holding registers request is 12 bytes.
    int expectedResponseSize = 12;
    if (!receiveResponse(commResponseBuffer, expectedResponseSize)) {
        pthread_mutex_unlock(&socketMutex);
        return ModbusError::TIMEOUT;
    }
    // Validate the response: Compare the first 10 bytes, skipping byte 5 (length field).
    for (int i = 0; i < 10; i++) {
        if (i == 5) continue;  // Skip the length field.
        if (commRequestBuffer[i] != commResponseBuffer[i]) {
            printf("MODBUS_TCP_CLIENT: Response does not match request at byte %d!\n", i);
            pthread_mutex_unlock(&socketMutex);
            return ModbusError::INVALID_RESPONSE;
        }
    }
    pthread_mutex_unlock(&socketMutex);
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readAll() {
    // For brevity, call low-level functions that update internal storage.
    ModbusError error = ModbusError::NONE;
    if (coilsRead) {
        error = readMultipleCoils(startCoils, numCoils, coilsRead);
        if (error != ModbusError::NONE) return error;
    }
    if (discreteInputs) {
        error = readMultipleDiscreteInputs(startDiscreteInputs, numDiscreteInputs, discreteInputs);
        if (error != ModbusError::NONE) return error;
    }
    if (inputRegisters) {
        error = readMultipleInputRegisters(startInputRegisters, numInputRegisters, inputRegisters);
        if (error != ModbusError::NONE) return error;
    }
    if (holdingRegistersRead) {
        error = readMultipleHoldingRegisters(startHoldingRegisters, numHoldingRegisters, holdingRegistersRead);
    }
    return error;
}

ModbusError ModbusTCPClient::writeAll() {
    ModbusError error = ModbusError::NONE;
    if (coilsWrite) {
        error = writeMultipleCoils(startCoils, numCoils, coilsWrite);
        if (error != ModbusError::NONE) return error;
    }
    if (holdingRegistersWrite) {
        error = writeMultipleHoldingRegisters(startHoldingRegisters, numHoldingRegisters, holdingRegistersWrite);
    }
    return error;
}

// Setters for writing values (preferred to be used)
void ModbusTCPClient::setCoil(int address, bool value) {
    if (address >= 0 && address < numCoils) {
        coilsWrite[address] = value;
    }
}

void ModbusTCPClient::setHoldingRegister(int address, uint16_t value) {
    if (address >= 0 && address < numHoldingRegisters) {
        holdingRegistersWrite[address] = value;
    }
}

// Getters (preferred to be used as long as readAll is being called)
bool ModbusTCPClient::getCoil(int address) const {
    return (address >= 0 && address < numCoils) ? coilsRead[address] : false;
}

bool ModbusTCPClient::getDesiredCoil(int address) const {
    return (address >= 0 && address < numCoils) ? coilsWrite[address] : false;
}

bool ModbusTCPClient::getDiscreteInput(int address) const {
    return (address >= 0 && address < numDiscreteInputs) ? discreteInputs[address] : false;
}

uint16_t ModbusTCPClient::getHoldingRegister(int address) const {
    return (address >= 0 && address < numHoldingRegisters) ? holdingRegistersRead[address] : 0;
}

uint16_t ModbusTCPClient::getDesiredHoldingRegister(int address) const {
    return (address >= 0 && address < numHoldingRegisters) ? holdingRegistersWrite[address] : 0;
}

uint16_t ModbusTCPClient::getInputRegister(int address) const {
    return (address >= 0 && address < numInputRegisters) ? inputRegisters[address] : 0;
}