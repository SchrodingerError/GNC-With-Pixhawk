#ifndef MODBUS_TCP_CLIENT_H
#define MODBUS_TCP_CLIENT_H

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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

enum class ModbusError {
    NONE = 0,                  // No error
    TIMEOUT,                   // No response from server
    INVALID_RESPONSE,          // Response does not match request
    CONNECTION_LOST,           // Connection issue
    EXCEPTION_RESPONSE,        // MODBUS Exception response (error code)
    INVALID_REQUEST,           // User tries doing something they shouldn't
};


class ModbusTCPClient {
public:
    ModbusTCPClient(const char* ip, int port); // Extra constructor that does CANNOT use readAll() or writeAll()
    ModbusTCPClient(const char* ip, int port, int numCoils, int numDI, int numIR, int numHR,
        int startCoils = 0, int startDI = 0, int startIR = 0, int startHR = 0);

    ~ModbusTCPClient();

    // Set the start address of each type. Either use this after creating the object or put them in the constructor
    void setStartAddresses(int startCoils, int startDI, int startIR, int startHR);

    bool connectServer();
    void disconnectServer();
    bool isConnected() const;
    
    // Manually disconnectServer and return reconnectServer()
    bool reconnectServer();

    // Set the timeout for receiving responses
    void setTimeout(int milliseconds);

    // Setters (preferred to be used when calling writeAll())
    void setCoil(int address, bool value);
    void setHoldingRegister(int address, uint16_t value);

    // Getters (preferred to be used when calling readAll())
    bool getCoil(int address) const;
    bool getDesiredCoil(int address) const;  // Retrieves the "to be written" value
    bool getDiscreteInput(int address) const;
    uint16_t getHoldingRegister(int address) const;
    uint16_t getDesiredHoldingRegister(int address) const;  // Retrieves the "to be written" value
    uint16_t getInputRegister(int address) const;

    ModbusError readAll(); // Reads every coil, DI, IR, and HR
    ModbusError writeAll(); // Writes every coil and HR
    
    // Manual MODBUS TCP actions (not preferred to be called by user)
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
    int timeoutMilliseconds = 2000; // Default 2 second timeout on receiving responses

    // Storing MODBUS register information
    int numCoils, numDiscreteInputs, numInputRegisters, numHoldingRegisters;
    int startCoils, startDiscreteInputs, startInputRegisters, startHoldingRegisters; // The start address of each type of register
        
    bool* coilsRead;       // Stores the actual state of coils on the MODBUS server
    bool* coilsWrite;      // Stores the desired state of coils to be written
    bool* discreteInputs;  // Only read from the MODBUS server (no writes)
        
    uint16_t* inputRegisters;        // Only read from the MODBUS server
    uint16_t* holdingRegistersRead;  // Stores actual values from the MODBUS server
    uint16_t* holdingRegistersWrite; // Stores desired values to write

    bool sendRequest(uint8_t* request, int requestSize);
    bool receiveResponse(uint8_t* response, int expectedSize);

    void buildReadRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t startAddr, uint16_t quantity);
    void buildWriteSingleRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t address, uint16_t value);
    void buildWriteMultipleRequest(uint8_t* buffer, ModbusFunction functionCode, uint16_t address, uint16_t count, const void* values, uint8_t byteCount);
};

#endif // MODBUS_TCP_CLIENT_H