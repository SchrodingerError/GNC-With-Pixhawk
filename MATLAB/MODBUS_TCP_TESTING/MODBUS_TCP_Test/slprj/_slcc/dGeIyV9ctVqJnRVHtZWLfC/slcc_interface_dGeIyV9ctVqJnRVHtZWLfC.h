#include "customcode_dGeIyV9ctVqJnRVHtZWLfC.h"
#ifdef __cplusplus
extern "C" {
#endif


/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
DLL_EXPORT_CC extern void get_libmodbus_version_micro_addr_dGeIyV9ctVqJnRVHtZWLfC(const uint32_T **varAddr);
DLL_EXPORT_CC extern void get_libmodbus_version_major_addr_dGeIyV9ctVqJnRVHtZWLfC(const uint32_T **varAddr);
DLL_EXPORT_CC extern void get_libmodbus_version_minor_addr_dGeIyV9ctVqJnRVHtZWLfC(const uint32_T **varAddr);
DLL_EXPORT_CC extern const char_T *get_dll_checksum_dGeIyV9ctVqJnRVHtZWLfC();
DLL_EXPORT_CC extern int32_T modbus_set_slave_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T slave);
DLL_EXPORT_CC extern int32_T modbus_get_slave_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern int32_T modbus_set_error_recovery_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, modbus_error_recovery_mode error_recovery);
DLL_EXPORT_CC extern int32_T modbus_set_socket_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T s);
DLL_EXPORT_CC extern int32_T modbus_get_socket_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern int32_T modbus_get_response_timeout_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T *to_sec, uint32_T *to_usec);
DLL_EXPORT_CC extern int32_T modbus_set_response_timeout_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T to_sec, uint32_T to_usec);
DLL_EXPORT_CC extern int32_T modbus_get_byte_timeout_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T *to_sec, uint32_T *to_usec);
DLL_EXPORT_CC extern int32_T modbus_set_byte_timeout_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T to_sec, uint32_T to_usec);
DLL_EXPORT_CC extern int32_T modbus_get_indication_timeout_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T *to_sec, uint32_T *to_usec);
DLL_EXPORT_CC extern int32_T modbus_set_indication_timeout_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T to_sec, uint32_T to_usec);
DLL_EXPORT_CC extern int32_T modbus_get_header_length_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern int32_T modbus_connect_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern void modbus_close_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern void modbus_free_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern int32_T modbus_flush_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern int32_T modbus_set_debug_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T flag);
DLL_EXPORT_CC extern const char_T *modbus_strerror_dGeIyV9ctVqJnRVHtZWLfC(int32_T errnum);
DLL_EXPORT_CC extern int32_T modbus_read_bits_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T addr, int32_T nb, uint8_T *dest);
DLL_EXPORT_CC extern int32_T modbus_read_input_bits_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T addr, int32_T nb, uint8_T *dest);
DLL_EXPORT_CC extern int32_T modbus_read_registers_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T addr, int32_T nb, uint16_T *dest);
DLL_EXPORT_CC extern int32_T modbus_read_input_registers_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T addr, int32_T nb, uint16_T *dest);
DLL_EXPORT_CC extern int32_T modbus_write_bit_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T coil_addr, int32_T status);
DLL_EXPORT_CC extern int32_T modbus_write_register_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T reg_addr, const uint16_T value);
DLL_EXPORT_CC extern int32_T modbus_write_bits_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T addr, int32_T nb, const uint8_T *data);
DLL_EXPORT_CC extern int32_T modbus_write_registers_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T addr, int32_T nb, const uint16_T *data);
DLL_EXPORT_CC extern int32_T modbus_mask_write_register_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T addr, uint16_T and_mask, uint16_T or_mask);
DLL_EXPORT_CC extern int32_T modbus_write_and_read_registers_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T write_addr, int32_T write_nb, const uint16_T *src, int32_T read_addr, int32_T read_nb, uint16_T *dest);
DLL_EXPORT_CC extern int32_T modbus_report_slave_id_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T max_dest, uint8_T *dest);
DLL_EXPORT_CC extern modbus_mapping_t *modbus_mapping_new_start_address_dGeIyV9ctVqJnRVHtZWLfC(uint32_T start_bits, uint32_T nb_bits, uint32_T start_input_bits, uint32_T nb_input_bits, uint32_T start_registers, uint32_T nb_registers, uint32_T start_input_registers, uint32_T nb_input_registers);
DLL_EXPORT_CC extern modbus_mapping_t *modbus_mapping_new_dGeIyV9ctVqJnRVHtZWLfC(int32_T nb_bits, int32_T nb_input_bits, int32_T nb_registers, int32_T nb_input_registers);
DLL_EXPORT_CC extern void modbus_mapping_free_dGeIyV9ctVqJnRVHtZWLfC(modbus_mapping_t *mb_mapping);
DLL_EXPORT_CC extern int32_T modbus_send_raw_request_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, const uint8_T *raw_req, int32_T raw_req_length);
DLL_EXPORT_CC extern int32_T modbus_send_raw_request_tid_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, const uint8_T *raw_req, int32_T raw_req_length, int32_T tid);
DLL_EXPORT_CC extern int32_T modbus_receive_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint8_T *req);
DLL_EXPORT_CC extern int32_T modbus_receive_confirmation_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint8_T *rsp);
DLL_EXPORT_CC extern int32_T modbus_reply_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, const uint8_T *req, int32_T req_length, modbus_mapping_t *mb_mapping);
DLL_EXPORT_CC extern int32_T modbus_reply_exception_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, const uint8_T *req, uint32_T exception_code);
DLL_EXPORT_CC extern int32_T modbus_enable_quirks_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T quirks_mask);
DLL_EXPORT_CC extern int32_T modbus_disable_quirks_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, uint32_T quirks_mask);
DLL_EXPORT_CC extern void modbus_set_bits_from_byte_dGeIyV9ctVqJnRVHtZWLfC(uint8_T *dest, int32_T idx, const uint8_T value);
DLL_EXPORT_CC extern void modbus_set_bits_from_bytes_dGeIyV9ctVqJnRVHtZWLfC(uint8_T *dest, int32_T idx, uint32_T nb_bits, const uint8_T *tab_byte);
DLL_EXPORT_CC extern uint8_T modbus_get_byte_from_bits_dGeIyV9ctVqJnRVHtZWLfC(const uint8_T *src, int32_T idx, uint32_T nb_bits);
DLL_EXPORT_CC extern real32_T modbus_get_float_dGeIyV9ctVqJnRVHtZWLfC(const uint16_T *src);
DLL_EXPORT_CC extern real32_T modbus_get_float_abcd_dGeIyV9ctVqJnRVHtZWLfC(const uint16_T *src);
DLL_EXPORT_CC extern real32_T modbus_get_float_dcba_dGeIyV9ctVqJnRVHtZWLfC(const uint16_T *src);
DLL_EXPORT_CC extern real32_T modbus_get_float_badc_dGeIyV9ctVqJnRVHtZWLfC(const uint16_T *src);
DLL_EXPORT_CC extern real32_T modbus_get_float_cdab_dGeIyV9ctVqJnRVHtZWLfC(const uint16_T *src);
DLL_EXPORT_CC extern void modbus_set_float_dGeIyV9ctVqJnRVHtZWLfC(real32_T f, uint16_T *dest);
DLL_EXPORT_CC extern void modbus_set_float_abcd_dGeIyV9ctVqJnRVHtZWLfC(real32_T f, uint16_T *dest);
DLL_EXPORT_CC extern void modbus_set_float_dcba_dGeIyV9ctVqJnRVHtZWLfC(real32_T f, uint16_T *dest);
DLL_EXPORT_CC extern void modbus_set_float_badc_dGeIyV9ctVqJnRVHtZWLfC(real32_T f, uint16_T *dest);
DLL_EXPORT_CC extern void modbus_set_float_cdab_dGeIyV9ctVqJnRVHtZWLfC(real32_T f, uint16_T *dest);
DLL_EXPORT_CC extern modbus_t *modbus_new_rtu_dGeIyV9ctVqJnRVHtZWLfC(const char_T *device, int32_T baud, char_T parity, int32_T data_bit, int32_T stop_bit);
DLL_EXPORT_CC extern int32_T modbus_rtu_set_serial_mode_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T mode);
DLL_EXPORT_CC extern int32_T modbus_rtu_get_serial_mode_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern int32_T modbus_rtu_set_rts_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T mode);
DLL_EXPORT_CC extern int32_T modbus_rtu_get_rts_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern int32_T modbus_rtu_set_custom_rts_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, void (*set_rts)(modbus_t *, int32_T));
DLL_EXPORT_CC extern int32_T modbus_rtu_set_rts_delay_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T us);
DLL_EXPORT_CC extern int32_T modbus_rtu_get_rts_delay_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx);
DLL_EXPORT_CC extern modbus_t *modbus_new_tcp_dGeIyV9ctVqJnRVHtZWLfC(const char_T *ip_address, int32_T port);
DLL_EXPORT_CC extern int32_T modbus_tcp_listen_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T nb_connection);
DLL_EXPORT_CC extern int32_T modbus_tcp_accept_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T *s);
DLL_EXPORT_CC extern modbus_t *modbus_new_tcp_pi_dGeIyV9ctVqJnRVHtZWLfC(const char_T *node, const char_T *service);
DLL_EXPORT_CC extern int32_T modbus_tcp_pi_listen_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T nb_connection);
DLL_EXPORT_CC extern int32_T modbus_tcp_pi_accept_dGeIyV9ctVqJnRVHtZWLfC(modbus_t *ctx, int32_T *s);

/* Function Definitions */
DLL_EXPORT_CC const uint8_T *get_checksum_source_info(int32_T *size);
#ifdef __cplusplus
}
#endif

