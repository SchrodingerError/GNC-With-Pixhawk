#include "modbus_tcp_client.h"
#include <sys/select.h>  // For select() timeout

ModbusTCPClient::ModbusTCPClient(const char* ip, int port)
    : serverIP(ip), serverPort(port), socketFD(-1), transactionID(1) {}

ModbusTCPClient::~ModbusTCPClient() {
    disconnectServer();
}

bool ModbusTCPClient::connectServer() {
    // Step 1: If socket is already open, verify it's still connected
    if (socketFD != -1) {
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 100ms timeout for connection check

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(socketFD, &read_fds);

        int result = select(socketFD + 1, &read_fds, NULL, NULL, &timeout);
        
        if (result == 0) {
            // No error in select, socket is still connected
            printf("MODBUS_TCP_CLIENT: Already connected to MODBUS server\n");
            return true;
        } else {
            // Connection is broken, close and reset
            printf("MODBUS_TCP_CLIENT: Warning: Connection lost, reconnecting...\n");
            disconnectServer();
        }
    }

    // Step 2: Create a new socket
    for (int attempts = 0; attempts < 5; attempts++) {  // Retry up to 5 times
        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0) {
            printf("MODBUS_TCP_CLIENT: Error: Could not create socket\n");
            return false;
        }

        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

        // Step 3: Attempt to connect
        printf("MODBUS_TCP_CLIENT: Attempting to connect to MODBUS server (Try %d)...\n", attempts + 1);
        if (connect(socketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0) {
            printf("MODBUS_TCP_CLIENT: Connected to MODBUS server at %s:%d\n", serverIP, serverPort);
            return true;
        }

        printf("MODBUS_TCP_CLIENT: Connection failed, retrying...\n");
        disconnectServer();  // Close socket before retrying
        usleep(100000);  // Wait 100ms before retrying
    }
}

void ModbusTCPClient::disconnectServer() {
    if (socketFD != -1) {
        close(socketFD);
        socketFD = -1;
        printf("MODBUS_TCP_CLIENT: Disconnected from MODBUS server\n");
    }
}

void ModbusTCPClient::setTimeout(int milliseconds) {
    timeoutMilliseconds = milliseconds;
    printf("MODBUS_TCP_CLIENT: Timeout set to %d ms\n", timeoutMilliseconds);
}

bool ModbusTCPClient::isConnected() const {
    return socketFD != -1;
}

bool ModbusTCPClient::reconnectServer() {
    printf("MODBUS_TCP_CLIENT: Attempting manual reconnection...\n");
    disconnectServer();
    return connectServer();
}

bool ModbusTCPClient::sendRequest(uint8_t* request, int requestSize) {
    // Ensure we're connected before sending
    if (socketFD == -1) {
        printf("MODBUS_TCP_CLIENT: Connection lost. Attempting to reconnect...\n");
        if (!connectServer()) {
            printf("MODBUS_TCP_CLIENT: Reconnection failed. Cannot send request.\n");
            return false;
        }
    }

    int bytesSent = write(socketFD, request, requestSize);
    if (bytesSent <= 0) {  // Detect broken connection during write
        printf("MODBUS_TCP_CLIENT: Write failed, connection lost. Disconnecting...\n");
        disconnectServer();
        return false;
    }

    return bytesSent == requestSize;
    return bytesSent == requestSize;
}

bool ModbusTCPClient::receiveResponse(uint8_t* response, int expectedSize) {
    int totalBytesReceived = 0;

    while (totalBytesReceived < expectedSize) {
        struct timeval timeout;
        timeout.tv_sec = timeoutMilliseconds / 1000;          // Convert ms to seconds
        timeout.tv_usec = (timeoutMilliseconds % 1000) * 1000; // Convert remaining ms to µs

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(socketFD, &read_fds);

        // Use select() to wait for data before reading
        int ready = select(socketFD + 1, &read_fds, NULL, NULL, &timeout);
        if (ready == 0) {  // Timeout case
            printf("MODBUS_TCP_CLIENT: Error: Timeout waiting for MODBUS response. Disconnecting...\n");
            disconnectServer();  // Close socket and reset socketFD
            return false;
        } else if (ready < 0) {  // Select failed
            printf("MODBUS_TCP_CLIENT: Error: Select failed. Disconnecting...\n");
            disconnectServer();  // Close socket and reset socketFD
            return false;
        }

        // Read available data
        int bytesReceived = read(socketFD, response + totalBytesReceived, expectedSize - totalBytesReceived);
        if (bytesReceived <= 0) {  // Connection lost or no data received
            printf("MODBUS_TCP_CLIENT: Error: Connection lost. Disconnecting...\n");
            disconnectServer();  // Close socket and reset socketFD
            return false;
        }

        totalBytesReceived += bytesReceived;
    }

    return true;
}

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
    // Quantity (How many coils to read)
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

ModbusError ModbusTCPClient::readCoil(int address, bool &coilState) {
    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_COIL, address, 1);

    sendRequest(request, 12);

    uint8_t response[10]; // Expecting 10 bytes
    if (!receiveResponse(response, 10)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure function code matches the request (allowing for server behavior)
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_COIL)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_COIL), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Extract coil state (only first bit is used)
    coilState = (response[9] & 0x01) != 0;  // Adjusted index based on 10-byte response
    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readMultipleCoils(int address, int count, bool coilStates[]) {
    if (count < 1 || count > 2000) {
        printf("MODBUS_TCP_CLIENT: Error: Invalid coil count (1-2000 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }

    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_COIL, address, count);

    sendRequest(request, 12);

    // Expected response size: Fixed header (9) + variable byte count
    int byteCount = (count + 7) / 8; // 1 byte per 8 coils
    int expectedSize = 9 + byteCount;

    uint8_t response[256]; // Ensure buffer is large enough
    if (!receiveResponse(response, expectedSize)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure the function code matches
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_COIL)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_COIL), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Read coil values
    for (int i = 0; i < count; i++) {
        int byteIndex = 9 + (i / 8);  // Data starts at index 9
        int bitIndex = i % 8;
        coilStates[i] = (response[byteIndex] >> bitIndex) & 0x01;
    }

    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readDiscreteInput(int address, bool &discreteInput) {
    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_DISCRETE_INPUT, address, 1);

    sendRequest(request, 12);

    uint8_t response[10]; // Expected response size
    if (!receiveResponse(response, 10)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure function code matches the request
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_DISCRETE_INPUT)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_DISCRETE_INPUT), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Extract single discrete input state
    discreteInput = (response[9] & 0x01) != 0;
    return ModbusError::NONE;  // Success
}

ModbusError ModbusTCPClient::readMultipleDiscreteInputs(int address, int count, bool discreteInputs[]) {
    if (count < 1 || count > 2000) {
        printf("MODBUS_TCP_CLIENT: Error: Invalid discrete input count (1-2000 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }

    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_DISCRETE_INPUT, address, count);

    sendRequest(request, 12);

    // Expected response size: Fixed header (9) + variable byte count
    int byteCount = (count + 7) / 8; // 1 byte per 8 inputs
    int expectedSize = 9 + byteCount;

    uint8_t response[256]; // Ensure buffer is large enough
    if (!receiveResponse(response, expectedSize)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure the function code matches
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_DISCRETE_INPUT)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_DISCRETE_INPUT), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Read discrete input values
    for (int i = 0; i < count; i++) {
        int byteIndex = 9 + (i / 8);  // Data starts at index 9
        int bitIndex = i % 8;
        discreteInputs[i] = (response[byteIndex] >> bitIndex) & 0x01;
    }

    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readHoldingRegister(int address, uint16_t &holdingRegister) {
    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_HOLDING_REGISTER, address, 1);

    sendRequest(request, 12);

    uint8_t response[11]; // Expected response size for reading 1 register
    if (!receiveResponse(response, 11)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure function code matches the request
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_HOLDING_REGISTER)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_HOLDING_REGISTER), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Extract holding register value (Big-endian format)
    holdingRegister = (response[9] << 8) | response[10];
    return ModbusError::NONE;  // Success
}

ModbusError ModbusTCPClient::readMultipleHoldingRegisters(int address, int count, uint16_t holdingRegisters[]) {
    if (count < 1 || count > 125) { // MODBUS limits reading up to 125 registers per request
        printf("MODBUS_TCP_CLIENT: Error: Invalid holding register count (1-125 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }

    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_HOLDING_REGISTER, address, count);

    sendRequest(request, 12);

    // Expected response size: 9-byte header + 2 * count registers
    int expectedSize = 9 + (count * 2);
    uint8_t response[256]; // Ensure buffer is large enough

    if (!receiveResponse(response, expectedSize)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure function code matches the request
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_HOLDING_REGISTER)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_HOLDING_REGISTER), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Extract register values (each register is 2 bytes, big-endian)
    for (int i = 0; i < count; i++) {
        holdingRegisters[i] = (response[9 + (i * 2)] << 8) | response[10 + (i * 2)];
    }

    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::readInputRegister(int address, uint16_t &inputRegister) {
    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_INPUT_REGISTER, address, 1);

    sendRequest(request, 12);

    uint8_t response[11]; // Expected response size for reading 1 register
    if (!receiveResponse(response, 11)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure function code matches the request
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_INPUT_REGISTER)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_INPUT_REGISTER), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Extract input register value (Big-endian format)
    inputRegister = (response[9] << 8) | response[10];
    return ModbusError::NONE;  // Success
}

ModbusError ModbusTCPClient::readMultipleInputRegisters(int address, int count, uint16_t inputRegisters[]) {
    if (count < 1 || count > 125) { // MODBUS limits reading up to 125 registers per request
        printf("MODBUS_TCP_CLIENT: Error: Invalid input register count (1-125 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }

    uint8_t request[12];
    buildReadRequest(request, ModbusFunction::READ_INPUT_REGISTER, address, count);

    sendRequest(request, 12);

    // Expected response size: 9-byte header + 2 * count registers
    int expectedSize = 9 + (count * 2);
    uint8_t response[256]; // Ensure buffer is large enough

    if (!receiveResponse(response, expectedSize)) {
        return ModbusError::TIMEOUT;
    }

    // Handle MODBUS exception responses (0x80 + function code)
    if (response[7] & 0x80) {
        printf("MODBUS_TCP_CLIENT: Error: MODBUS Exception Code %02X\n", response[8]);
        return ModbusError::EXCEPTION_RESPONSE;
    }

    // Ensure function code matches the request
    if (response[7] != static_cast<uint8_t>(ModbusFunction::READ_INPUT_REGISTER)) {
        printf("MODBUS_TCP_CLIENT: Warning: Unexpected function code (Expected: %02X, Got: %02X)\n",
               static_cast<uint8_t>(ModbusFunction::READ_INPUT_REGISTER), response[7]);
        return ModbusError::INVALID_RESPONSE;
    }

    // Extract register values (each register is 2 bytes, big-endian)
    for (int i = 0; i < count; i++) {
        inputRegisters[i] = (response[9 + (i * 2)] << 8) | response[10 + (i * 2)];
    }

    return ModbusError::NONE;
}

ModbusError ModbusTCPClient::writeCoil(int address, bool value) {
    uint8_t request[12];
    buildWriteSingleRequest(request, ModbusFunction::WRITE_SINGLE_COIL, address, value ? 0xFF00 : 0x0000);
    sendRequest(request, 12);

    // Receive response
    uint8_t response[12];
    if (!receiveResponse(response, 12)) {
        return ModbusError::TIMEOUT;  // No response received
    }

    // Check if response matches request (MODBUS TCP should echo back the same request)
    for (int i = 0; i < 12; i++) {
        if (request[i] != response[i]) {
            printf("MODBUS_TCP_CLIENT: Error: Response does not match request!\n");
            return ModbusError::INVALID_RESPONSE;
        }
    }

    return ModbusError::NONE;  // Success
}

ModbusError ModbusTCPClient::writeMultipleCoils(int address, int count, const bool values[]) {
    if (count < 1 || count > 1968) {  // MODBUS limit: max 1968 coils per request
        printf("MODBUS_TCP_CLIENT: Error: Invalid coil count (1-1968 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }

    int byteCount = (count + 7) / 8;  // Each byte holds 8 coils
    uint8_t coilData[byteCount];

    // Initialize to 0 (since we may not use all bits)
    for (int i = 0; i < byteCount; i++) {
        coilData[i] = 0;
    }

    // Pack coil data into bytes
    for (int i = 0; i < count; i++) {
        if (values[i]) {
            coilData[i / 8] |= (1 << (i % 8));
        }
    }

    uint8_t request[13 + byteCount];
    buildWriteMultipleRequest(request, ModbusFunction::WRITE_MULTIPLE_COILS, address, count, coilData, byteCount);

    sendRequest(request, 13 + byteCount);

    // The expected response is always **12 bytes**
    uint8_t response[12];
    if (!receiveResponse(response, 12)) {
        return ModbusError::TIMEOUT;
    }

    // Ensure the response matches the **first 10 bytes**, except for byte 5 (message length byte)
    for (int i = 0; i < 10; i++) {
        if (i == 5) continue;  // Skip byte 5 (message length field)

        if (request[i] != response[i]) {
            printf("MODBUS_TCP_CLIENT: Error: Response does not match request!\n");
            return ModbusError::INVALID_RESPONSE;
        }
    }

    return ModbusError::NONE;  // Success
}

ModbusError ModbusTCPClient::writeHoldingRegister(int address, uint16_t value) {
    uint8_t request[12];
    buildWriteSingleRequest(request, ModbusFunction::WRITE_SINGLE_HOLDING_REGISTER, address, value);

    sendRequest(request, 12);

    // Expected response size = 12 bytes (full echo of the request)
    uint8_t response[12];
    if (!receiveResponse(response, 12)) {
        return ModbusError::TIMEOUT;
    }

    // Ensure response matches request exactly (full 12 bytes)
    for (int i = 0; i < 12; i++) {
        if (request[i] != response[i]) {
            printf("MODBUS_TCP_CLIENT: Error: Response does not match request!\n");
            return ModbusError::INVALID_RESPONSE;
        }
    }

    return ModbusError::NONE;  // Success
}

ModbusError ModbusTCPClient::writeMultipleHoldingRegisters(int address, int count, const uint16_t values[]) {
    if (count < 1 || count > 123) {  // MODBUS limit: max 123 registers per request
        printf("MODBUS_TCP_CLIENT: Error: Invalid register count (1-123 allowed)\n");
        return ModbusError::INVALID_RESPONSE;
    }

    int byteCount = count * 2;  // Each register is 2 bytes
    uint8_t registerData[byteCount];

    // Convert register values to byte array (big-endian format)
    for (int i = 0; i < count; i++) {
        registerData[i * 2] = values[i] >> 8;      // High byte
        registerData[i * 2 + 1] = values[i] & 0xFF; // Low byte
    }

    uint8_t request[13 + byteCount];
    buildWriteMultipleRequest(request, ModbusFunction::WRITE_MULTIPLE_HOLDING_REGISTERS, address, count, registerData, byteCount);

    sendRequest(request, 13 + byteCount);

    // Expected response size = 12 bytes (first 10 bytes + 2 bytes for number of registers written)
    uint8_t response[12];
    if (!receiveResponse(response, 12)) {
        return ModbusError::TIMEOUT;
    }

    // Ensure response matches request (except for byte 5)
    for (int i = 0; i < 10; i++) {
        if (i == 5) continue;  // Skip byte 5 (message length field)

        if (request[i] != response[i]) {
            printf("MODBUS_TCP_CLIENT: Error: Response does not match request!\n");
            return ModbusError::INVALID_RESPONSE;
        }
    }

    return ModbusError::NONE;  // Success
}