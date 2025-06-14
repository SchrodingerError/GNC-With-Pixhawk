#include "customcode_NrUqZ7JIZtB1SCgcPvEdbB.h"
#ifdef __cplusplus
extern "C" {
#endif


/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
DLL_EXPORT_CC extern void get_NMBS_BROADCAST_ADDRESS_addr_NrUqZ7JIZtB1SCgcPvEdbB(const uint8_T **varAddr);
DLL_EXPORT_CC extern const char_T *get_dll_checksum_NrUqZ7JIZtB1SCgcPvEdbB();
DLL_EXPORT_CC extern void nmbs_set_read_timeout_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, int32_T timeout_ms);
DLL_EXPORT_CC extern void nmbs_set_byte_timeout_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, int32_T timeout_ms);
DLL_EXPORT_CC extern void nmbs_platform_conf_create_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_platform_conf *platform_conf);
DLL_EXPORT_CC extern void nmbs_set_platform_arg_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, void *arg);
DLL_EXPORT_CC extern void nmbs_callbacks_create_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_callbacks *callbacks);
DLL_EXPORT_CC extern nmbs_error nmbs_server_create_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint8_T address_rtu, const nmbs_platform_conf *platform_conf, const nmbs_callbacks *callbacks);
DLL_EXPORT_CC extern nmbs_error nmbs_server_poll_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs);
DLL_EXPORT_CC extern void nmbs_set_callbacks_arg_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, void *arg);
DLL_EXPORT_CC extern nmbs_error nmbs_client_create_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, const nmbs_platform_conf *platform_conf);
DLL_EXPORT_CC extern void nmbs_set_destination_rtu_address_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint8_T address);
DLL_EXPORT_CC extern nmbs_error nmbs_read_coils_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, uint16_T quantity, uint8_T coils_out[250]);
DLL_EXPORT_CC extern nmbs_error nmbs_read_discrete_inputs_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, uint16_T quantity, uint8_T inputs_out[250]);
DLL_EXPORT_CC extern nmbs_error nmbs_read_holding_registers_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, uint16_T quantity, uint16_T *registers_out);
DLL_EXPORT_CC extern nmbs_error nmbs_read_input_registers_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, uint16_T quantity, uint16_T *registers_out);
DLL_EXPORT_CC extern nmbs_error nmbs_write_single_coil_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, boolean_T value);
DLL_EXPORT_CC extern nmbs_error nmbs_write_single_register_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, uint16_T value);
DLL_EXPORT_CC extern nmbs_error nmbs_write_multiple_coils_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, uint16_T quantity, const uint8_T coils[250]);
DLL_EXPORT_CC extern nmbs_error nmbs_write_multiple_registers_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T address, uint16_T quantity, const uint16_T *registers);
DLL_EXPORT_CC extern nmbs_error nmbs_read_file_record_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T file_number, uint16_T record_number, uint16_T *registers, uint16_T count);
DLL_EXPORT_CC extern nmbs_error nmbs_write_file_record_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T file_number, uint16_T record_number, const uint16_T *registers, uint16_T count);
DLL_EXPORT_CC extern nmbs_error nmbs_read_write_registers_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint16_T read_address, uint16_T read_quantity, uint16_T *registers_out, uint16_T write_address, uint16_T write_quantity, const uint16_T *registers);
DLL_EXPORT_CC extern nmbs_error nmbs_read_device_identification_basic_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, char_T *vendor_name, char_T *product_code, char_T *major_minor_revision, uint8_T buffers_length);
DLL_EXPORT_CC extern nmbs_error nmbs_read_device_identification_regular_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, char_T *vendor_url, char_T *product_name, char_T *model_name, char_T *user_application_name, uint8_T buffers_length);
DLL_EXPORT_CC extern nmbs_error nmbs_read_device_identification_extended_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint8_T object_id_start, uint8_T *ids, char_T **buffers, uint8_T ids_length, uint8_T buffer_length, uint8_T *objects_count_out);
DLL_EXPORT_CC extern nmbs_error nmbs_read_device_identification_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint8_T object_id, char_T *buffer, uint8_T buffer_length);
DLL_EXPORT_CC extern nmbs_error nmbs_send_raw_pdu_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint8_T fc, const uint8_T *data, uint16_T data_len);
DLL_EXPORT_CC extern nmbs_error nmbs_receive_raw_pdu_response_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_t *nmbs, uint8_T *data_out, uint8_T data_out_len);
DLL_EXPORT_CC extern uint16_T nmbs_crc_calc_NrUqZ7JIZtB1SCgcPvEdbB(const uint8_T *data, uint32_T length, void *arg);
DLL_EXPORT_CC extern const char_T *nmbs_strerror_NrUqZ7JIZtB1SCgcPvEdbB(nmbs_error error);

/* Function Definitions */
DLL_EXPORT_CC const uint8_T *get_checksum_source_info(int32_T *size);
#ifdef __cplusplus
}
#endif

