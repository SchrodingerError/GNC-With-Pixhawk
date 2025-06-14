#ifndef MODBUS_TCP_CLIENT_H
#define MODBUS_TCP_CLIENT_H

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>  // Use mutexes

// Enum class for MODBUS function codes
enum class ModbusFunction : uint8_t {
    READ_COIL = 0x01,
    READ_DISCRETE_INPUT = 0x02,
    READ_HOLDING_REGISTER = 0x03,
    READ_INPUT_REGISTER = 0x04,
    WRITE_SINGLE_COIL = 0x05,
    WRITE_SINGLE_HOLDING_REGISTER = 0x06,
    WRITE_MULTIPLE_COILS = 0x0F,
    WRITE_MULTIPLE_HOLDING_REGISTERS = 0x10
};

// Enum class for error codes
enum class ModbusError {
    NONE = 0,
    TIMEOUT,
    INVALID_RESPONSE,
    CONNECTION_LOST,
    EXCEPTION_RESPONSE,
    INVALID_REQUEST
};

class ModbusTCPClient {
public:
    // Constructor that allocates dynamic buffers based on provided counts and start addresses.
    ModbusTCPClient(const char* ip, int port, int numCoils, int numDI, int numIR, int numHR,
                    int startCoils = 0, int startDI = 0, int startIR = 0, int startHR = 0);
    // Simpler constructor for manual MODBUS function calls (without readAll/writeAll)
    ModbusTCPClient(const char* ip, int port);
    ~ModbusTCPClient();

    // Set start addresses for each type.
    void setStartAddresses(int startCoils, int startDI, int startIR, int startHR);

    // Connection functions
    bool connectServer();
    void disconnectServer();
    bool isConnected() const;
    bool reconnectServer();

    // Set the timeout (in milliseconds) for receiving responses.
    void setTimeout(int milliseconds);

    // Getters and setters for data values (if using the automatic mode).
    void setCoil(int address, bool value);
    void setHoldingRegister(int address, uint16_t value);
    bool getCoil(int address) const;
    bool getDesiredCoil(int address) const;
    bool getDiscreteInput(int address) const;
    uint16_t getHoldingRegister(int address) const;
    uint16_t getDesiredHoldingRegister(int address) const;
    uint16_t getInputRegister(int address) const;

    // High-level functions: readAll and writeAll update the internal buffers.
    ModbusError readAll();
    ModbusError writeAll();

    // Low-level MODBUS functions (manual calls)
    ModbusError readCoil(int address, bool &coilState);
    ModbusError readMultipleCoils(int address, int count, bool coilStates[]);
    ModbusError readDiscreteInput(int address, bool &discreteInput);
    ModbusError readMultipleDiscreteInputs(int address, int count, bool discreteInputs[]);
    ModbusError readHoldingRegister(int address, uint16_t &holdingRegister);
    ModbusError readMultipleHoldingRegisters(int address, int count, uint16_t holdingRegisters[]);
    ModbusError readInputRegister(int address, uint16_t &inputRegister);
    ModbusError readMultipleInputRegisters(int address, int count, uint16_t inputRegisters[]);

    ModbusError writeCoil(int address, bool value);
    ModbusError writeMultipleCoils(int address, int count, const bool values[]);
    ModbusError writeHoldingRegister(int address, uint16_t value);
    ModbusError writeMultipleHoldingRegisters(int address, int count, const uint16_t values[]);

private:
    // TCP settings
    const char* serverIP;
    int serverPort;
    int socketFD;
    uint16_t transactionID;
    int timeoutMilliseconds = 2000; // Default 2-second timeout

    // Start addresses for each data type
    int startCoils, startDiscreteInputs, startInputRegisters, startHoldingRegisters;
    // Number of items for each type
    int numCoils, numDiscreteInputs, numInputRegisters, numHoldingRegisters;

    // Internal storage for automatic readAll()/writeAll() mode
    bool* coilsRead;       // Actual state from PLC
    bool* coilsWrite;      // Desired state to write
    bool* discreteInputs;  // Only read
    uint16_t* inputRegisters;        // Only read
    uint16_t* holdingRegistersRead;  // Actual values from PLC
    uint16_t* holdingRegistersWrite; // Desired values to write

    // --- Communication buffers (shared for both reading and writing)
    uint8_t* commRequestBuffer;  // Preallocated request buffer
    uint8_t* commResponseBuffer; // Preallocated response buffer
    int commRequestBufferSize;   // Maximum request size needed
    int commResponseBufferSize;  // Maximum response size needed

    // Global mutex to protect the TCP socket and communication buffers.
    pthread_mutex_t socketMutex;

    // Low-level communication functions using the shared buffers.
    bool sendRequest(uint8_t* request, int requestSize);
    bool receiveResponse(uint8_t* response, int expectedSize);

    // Message building functions – they write into a provided buffer.
    void buildReadRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t startAddr, uint16_t quantity);
    void buildWriteSingleRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t address, uint16_t value);
    void buildWriteMultipleRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t address, uint16_t count, const void* values, uint8_t byteCount);

    // Helper functions to compute maximum buffer sizes.
    int computeMaxReadResponseSize() const;
    int computeMaxWriteRequestSize() const;
};

#endif // MODBUS_TCP_CLIENT_H
