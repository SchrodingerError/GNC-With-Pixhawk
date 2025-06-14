#include "customcode_WOZg8SrZCI3YH7YaIklGiE.h"
#ifdef __cplusplus
extern "C" {
#endif


/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
DLL_EXPORT_CC extern const char_T *get_dll_checksum_WOZg8SrZCI3YH7YaIklGiE();
DLL_EXPORT_CC extern void *create_ModbusTCPClient_m6DHLsRJatb7jFhPa9sibF_WOZg8SrZCI3YH7YaIklGiE(const char_T *ip, int32_T port);
DLL_EXPORT_CC extern void delete_ModbusTCPClient_IUI8Q2S0ulkAvLxLsx7k7_WOZg8SrZCI3YH7YaIklGiE(void *classObj);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_connectServer_QWoAn8DsWluHwos1RJjgIB_WOZg8SrZCI3YH7YaIklGiE(void *classObj);
DLL_EXPORT_CC extern void ModbusTCPClient_disconnectServer_8RQB4Kyl2X5kNVGUlAlOgF_WOZg8SrZCI3YH7YaIklGiE(void *classObj);
DLL_EXPORT_CC extern boolean_T ModbusTCPClient_readCoil_I0fzDOaax3ByUlCPekapKG_WOZg8SrZCI3YH7YaIklGiE(void *classObj, int32_T address);
DLL_EXPORT_CC extern void ModbusTCPClient_writeCoil_QoP3Zii3RZpABaPcesHRiB_WOZg8SrZCI3YH7YaIklGiE(void *classObj, int32_T address, boolean_T value);
DLL_EXPORT_CC extern uint16_T ModbusTCPClient_readHoldingRegister_g900vXiXPbOtZqtApt9hNC_WOZg8SrZCI3YH7YaIklGiE(void *classObj, int32_T address);
DLL_EXPORT_CC extern void ModbusTCPClient_writeHoldingRegister_mGVMywqtoVY5ZLnrtEy19G_WOZg8SrZCI3YH7YaIklGiE(void *classObj, int32_T address, uint16_T value);
DLL_EXPORT_CC extern void ModbusTCPClient_readAll_0LzP2HH0Zq4XkTmFCbG4o_WOZg8SrZCI3YH7YaIklGiE(void *classObj);
DLL_EXPORT_CC extern boolean_T (*get_coils_ModbusTCPClient_IUI8Q2S0ulkAvLxLsx7k7_WOZg8SrZCI3YH7YaIklGiE(void *classObj))[16];
DLL_EXPORT_CC extern boolean_T (*get_discreteInputs_ModbusTCPClient_IUI8Q2S0ulkAvLxLsx7k7_WOZg8SrZCI3YH7YaIklGiE(void *classObj))[16];
DLL_EXPORT_CC extern uint16_T (*get_inputRegisters_ModbusTCPClient_IUI8Q2S0ulkAvLxLsx7k7_WOZg8SrZCI3YH7YaIklGiE(void *classObj))[16];
DLL_EXPORT_CC extern uint16_T (*get_holdingRegisters_ModbusTCPClient_IUI8Q2S0ulkAvLxLsx7k7_WOZg8SrZCI3YH7YaIklGiE(void *classObj))[16];

/* Function Definitions */
DLL_EXPORT_CC const uint8_T *get_checksum_source_info(int32_T *size);
#ifdef __cplusplus
}
#endif

