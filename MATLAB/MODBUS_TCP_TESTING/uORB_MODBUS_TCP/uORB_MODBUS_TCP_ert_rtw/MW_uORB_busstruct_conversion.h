#ifndef _MW_UORB_BUSSTRUCT_CONVERSION_H_
#define _MW_UORB_BUSSTRUCT_CONVERSION_H_

#include <uORB/topics/plc_coils_read.h>
#include <uORB/topics/plc_discrete_inputs.h>
#include <uORB/topics/plc_holding_registers_read.h>
#include <uORB/topics/plc_input_registers.h>

typedef struct plc_coils_read_s  px4_Bus_plc_coils_read ;
typedef struct plc_discrete_inputs_s  px4_Bus_plc_discrete_inputs ;
typedef struct plc_holding_registers_read_s  px4_Bus_plc_holding_registers_read ;
typedef struct plc_input_registers_s  px4_Bus_plc_input_registers ;

#endif
