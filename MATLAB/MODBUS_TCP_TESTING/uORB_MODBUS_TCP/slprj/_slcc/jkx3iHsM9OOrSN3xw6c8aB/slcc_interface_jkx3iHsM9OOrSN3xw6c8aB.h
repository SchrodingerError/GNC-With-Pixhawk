#include "customcode_jkx3iHsM9OOrSN3xw6c8aB.h"
#ifdef __cplusplus
extern "C" {
#endif


/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
DLL_EXPORT_CC extern const char_T *get_dll_checksum_jkx3iHsM9OOrSN3xw6c8aB();
DLL_EXPORT_CC extern void *create_ModbusTCPClient_DTOtnS5jzeCt7wI4BrWszE_jkx3iHsM9OOrSN3xw6c8aB(const char_T *ip, int32_T port, int32_T numCoils, int32_T numDI, int32_T numIR, int32_T numHR, int32_T startCoils, int32_T startDI, int32_T startIR, int32_T startHR);
DLL_EXPORT_CC extern void *create_ModbusTCPClient_m6DHLsRJatb7jFhPa9sibF_jkx3iHsM9OOrSN3xw6c8aB(const char_T *ip, int32_T port);
DLL_EXPORT_CC extern void delete_ModbusTCPClient_IUI8Q2S0ulkAvLxLsx7k7_jkx3iHsM9OOrSN3xw6c8aB(void *classObj);
DLL_EXPORT_CC extern void ModbusTCPClient_setStartAddresses_WBPKyX5chtvoJpkQQz9yaE_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T startCoils, int32_T startDI, int32_T startIR, int32_T startHR);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_connectServer_QWoAn8DsWluHwos1RJjgIB_jkx3iHsM9OOrSN3xw6c8aB(void *classObj);
DLL_EXPORT_CC extern void ModbusTCPClient_disconnectServer_8RQB4Kyl2X5kNVGUlAlOgF_jkx3iHsM9OOrSN3xw6c8aB(void *classObj);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_isConnected_6gPjpu9NwavTxFjRzBfnHH_jkx3iHsM9OOrSN3xw6c8aB(void *classObj);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_reconnectServer_tmHQpYOBqsG4QOWlcN1JCG_jkx3iHsM9OOrSN3xw6c8aB(void *classObj);
DLL_EXPORT_CC extern void ModbusTCPClient_setTimeout_pKk7C4CiK7cGunjmXsoo9G_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T milliseconds);
DLL_EXPORT_CC extern void ModbusTCPClient_setCoil_uKV63H2F6Bk5GhMpqdzPnH_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, boolean_T value);
DLL_EXPORT_CC extern void ModbusTCPClient_setHoldingRegister_4XFxsavHXRTDHK2Ce0yJN_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, uint16_T value);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_getCoil_koLGZb1i8WN62u3e1PZwYH_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_getDesiredCoil_4MZCcH6ezDGZg0uObXZUCC_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_getDiscreteInput_ae9HPljrPWD4BuZzmFBLEH_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address);
DLL_EXPORT_CC extern uint16_T ModbusTCPClient_getHoldingRegister_mYLPn0wppPgH4bOhTiVvvF_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address);
DLL_EXPORT_CC extern uint16_T ModbusTCPClient_getDesiredHoldingRegister_15FbNf22xvcBTZOmdfDtkC_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address);
DLL_EXPORT_CC extern uint16_T ModbusTCPClient_getInputRegister_ULtxwrYKJbrRxoQjkBCEs_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_getMultipleHoldingRegisters_dolsLHExIVVRdXIf6qYZmF_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T startAddress, int32_T count, uint16_T *destination);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readAll_0LzP2HH0Zq4XkTmFCbG4o_jkx3iHsM9OOrSN3xw6c8aB(void *classObj);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_writeAll_zaImFzR1o00mWpc4RczmN_jkx3iHsM9OOrSN3xw6c8aB(void *classObj);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readCoil_zMFMzEaWMy4AM0fCGw6vkB_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, boolean_T *coilState);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readMultipleCoils_FsHZsYjrSrPY8P2Ay58lEB_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, int32_T count, boolean_T *coilStates);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readDiscreteInput_hw3i2qSdn19YvGoOIzPSQF_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, boolean_T *discreteInput);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readMultipleDiscreteInputs_ejm6F8zFfmummwJiWr5WWE_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, int32_T count, boolean_T *discreteInputs);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readHoldingRegister_6gyuCNdZQDr6LxODE49ARC_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, uint16_T *holdingRegister);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readMultipleHoldingRegisters_Nsd2PmYkYCsTdyTlOKb0KB_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, int32_T count, uint16_T *holdingRegisters);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readInputRegister_LiIzv9TV0ONDt8VfLmy35G_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, uint16_T *inputRegister);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_readMultipleInputRegisters_two67DgbwFGoO6KyFi3I5B_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, int32_T count, uint16_T *inputRegisters);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_writeCoil_QoP3Zii3RZpABaPcesHRiB_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, boolean_T value);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_writeMultipleCoils_p5zcgcGPFH7wlbBhce5JYG_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, int32_T count, const boolean_T *values);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_writeHoldingRegister_mGVMywqtoVY5ZLnrtEy19G_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, uint16_T value);
DLL_EXPORT_CC extern ModbusError ModbusTCPClient_writeMultipleHoldingRegisters_ga2jca071NX41GYGjHLKzB_jkx3iHsM9OOrSN3xw6c8aB(void *classObj, int32_T address, int32_T count, const uint16_T *values);

/* Function Definitions */
DLL_EXPORT_CC const uint8_T *get_checksum_source_info(int32_T *size);
#ifdef __cplusplus
}
#endif

