//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: uORB_MODBUS_TCP.h
//
// Code generated for Simulink model 'uORB_MODBUS_TCP'.
//
// Model version                  : 1.22
// Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
// C/C++ source code generated on : Sat Apr 12 20:53:52 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef uORB_MODBUS_TCP_h_
#define uORB_MODBUS_TCP_h_
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "MW_uORB_Read.h"
#include "MW_uORB_Write.h"
#include "uORB_MODBUS_TCP_types.h"
#include <uORB/topics/plc_holding_registers_read.h>
#include <uORB/topics/plc_input_registers.h>
#include <uORB/topics/plc_coils_read.h>
#include <uORB/topics/plc_discrete_inputs.h>
#include "modbus_tcp_client.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

// user code (top of header file)
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Block signals (default storage)
struct B_uORB_MODBUS_TCP_T {
  px4_Bus_plc_holding_registers_read BusAssignment;// '<Root>/Bus Assignment'
  px4_Bus_plc_holding_registers_read SourceBlock_o2_l;// '<S5>/SourceBlock'
  px4_Bus_plc_holding_registers_read In1_e;// '<S13>/In1'
  px4_Bus_plc_holding_registers_read r;
  px4_Bus_plc_input_registers BusAssignment2;// '<Root>/Bus Assignment2'
  px4_Bus_plc_input_registers SourceBlock_o2;// '<S7>/SourceBlock'
  px4_Bus_plc_input_registers In1;     // '<S15>/In1'
  px4_Bus_plc_input_registers r1;
  px4_Bus_plc_coils_read BusAssignment1;// '<Root>/Bus Assignment1'
  px4_Bus_plc_coils_read SourceBlock_o2_d;// '<S6>/SourceBlock'
  px4_Bus_plc_coils_read In1_m;        // '<S14>/In1'
  uint16_T PLCMODBUSTCPReadAll_o2[128];// '<Root>/PLC MODBUS TCP ReadAll'
  uint16_T PLCMODBUSTCPReadAll_o4[128];// '<Root>/PLC MODBUS TCP ReadAll'
  px4_Bus_plc_coils_read r2;
  px4_Bus_plc_discrete_inputs BusAssignment3;// '<Root>/Bus Assignment3'
  px4_Bus_plc_discrete_inputs SourceBlock_o2_j;// '<S8>/SourceBlock'
  px4_Bus_plc_discrete_inputs In1_b;   // '<S16>/In1'
  px4_Bus_plc_discrete_inputs r3;
  boolean_T PLCMODBUSTCPReadAll_o1[128];// '<Root>/PLC MODBUS TCP ReadAll'
  boolean_T PLCMODBUSTCPReadAll_o3[128];// '<Root>/PLC MODBUS TCP ReadAll'
  boolean_T SourceBlock_o1;            // '<S8>/SourceBlock'
  boolean_T SourceBlock_o1_g;          // '<S7>/SourceBlock'
  boolean_T SourceBlock_o1_l;          // '<S6>/SourceBlock'
  boolean_T SourceBlock_o1_c;          // '<S5>/SourceBlock'
};

// Block states (default storage) for system '<Root>'
struct DW_uORB_MODBUS_TCP_T {
  px4_internal_block_Subscriber_T obj; // '<S8>/SourceBlock'
  px4_internal_block_Subscriber_T obj_e;// '<S7>/SourceBlock'
  px4_internal_block_Subscriber_T obj_j;// '<S6>/SourceBlock'
  px4_internal_block_Subscriber_T obj_d;// '<S5>/SourceBlock'
  px4_internal_block_Publisher__T obj_f;// '<S12>/SinkBlock'
  px4_internal_block_Publisher__T obj_a;// '<S11>/SinkBlock'
  px4_internal_block_Publisher__T obj_g;// '<S10>/SinkBlock'
  px4_internal_block_Publisher__T obj_m;// '<S9>/SinkBlock'
  boolean_T objisempty;                // '<S12>/SinkBlock'
  boolean_T objisempty_n;              // '<S11>/SinkBlock'
  boolean_T objisempty_i;              // '<S10>/SinkBlock'
  boolean_T objisempty_nn;             // '<S9>/SinkBlock'
  boolean_T objisempty_e;              // '<S8>/SourceBlock'
  boolean_T objisempty_b;              // '<S7>/SourceBlock'
  boolean_T objisempty_bt;             // '<S6>/SourceBlock'
  boolean_T objisempty_a;              // '<S5>/SourceBlock'
};

// Parameters (default storage)
struct P_uORB_MODBUS_TCP_T_ {
  px4_Bus_plc_holding_registers_read Out1_Y0;// Computed Parameter: Out1_Y0
                                                //  Referenced by: '<S13>/Out1'

  px4_Bus_plc_holding_registers_read Constant_Value;// Computed Parameter: Constant_Value
                                                       //  Referenced by: '<S1>/Constant'

  px4_Bus_plc_holding_registers_read Constant_Value_o;// Computed Parameter: Constant_Value_o
                                                         //  Referenced by: '<S5>/Constant'

  px4_Bus_plc_input_registers Out1_Y0_h;// Computed Parameter: Out1_Y0_h
                                           //  Referenced by: '<S15>/Out1'

  px4_Bus_plc_input_registers Constant_Value_f;// Computed Parameter: Constant_Value_f
                                                  //  Referenced by: '<S3>/Constant'

  px4_Bus_plc_input_registers Constant_Value_om;// Computed Parameter: Constant_Value_om
                                                   //  Referenced by: '<S7>/Constant'

  px4_Bus_plc_coils_read Out1_Y0_g;    // Computed Parameter: Out1_Y0_g
                                          //  Referenced by: '<S14>/Out1'

  px4_Bus_plc_coils_read Constant_Value_m;// Computed Parameter: Constant_Value_m
                                             //  Referenced by: '<S2>/Constant'

  px4_Bus_plc_coils_read Constant_Value_k;// Computed Parameter: Constant_Value_k
                                             //  Referenced by: '<S6>/Constant'

  px4_Bus_plc_discrete_inputs Out1_Y0_l;// Computed Parameter: Out1_Y0_l
                                           //  Referenced by: '<S16>/Out1'

  px4_Bus_plc_discrete_inputs Constant_Value_d;// Computed Parameter: Constant_Value_d
                                                  //  Referenced by: '<S4>/Constant'

  px4_Bus_plc_discrete_inputs Constant_Value_mf;// Computed Parameter: Constant_Value_mf
                                                   //  Referenced by: '<S8>/Constant'

};

// Real-time Model Data Structure
struct tag_RTM_uORB_MODBUS_TCP_T {
  const char_T * volatile errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_DW;

// External function called from main
#ifdef __cplusplus

extern "C"
{

#endif

  extern void uORB_MODBUS_TCP_SetEventsForThisBaseStep(boolean_T *eventFlags);

#ifdef __cplusplus

}

#endif

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void uORB_MODBUS_TCP_initialize(void);
  extern void uORB_MODBUS_TCP_step0(void);
  extern void uORB_MODBUS_TCP_step1(void);
  extern void uORB_MODBUS_TCP_step(int_T tid);
  extern void uORB_MODBUS_TCP_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_uORB_MODBUS_TCP_T *const uORB_MODBUS_TCP_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'uORB_MODBUS_TCP'
//  '<S1>'   : 'uORB_MODBUS_TCP/PX4 uORB Message'
//  '<S2>'   : 'uORB_MODBUS_TCP/PX4 uORB Message1'
//  '<S3>'   : 'uORB_MODBUS_TCP/PX4 uORB Message2'
//  '<S4>'   : 'uORB_MODBUS_TCP/PX4 uORB Message3'
//  '<S5>'   : 'uORB_MODBUS_TCP/PX4 uORB Read'
//  '<S6>'   : 'uORB_MODBUS_TCP/PX4 uORB Read1'
//  '<S7>'   : 'uORB_MODBUS_TCP/PX4 uORB Read2'
//  '<S8>'   : 'uORB_MODBUS_TCP/PX4 uORB Read3'
//  '<S9>'   : 'uORB_MODBUS_TCP/PX4 uORB Write1'
//  '<S10>'  : 'uORB_MODBUS_TCP/PX4 uORB Write2'
//  '<S11>'  : 'uORB_MODBUS_TCP/PX4 uORB Write3'
//  '<S12>'  : 'uORB_MODBUS_TCP/PX4 uORB Write4'
//  '<S13>'  : 'uORB_MODBUS_TCP/PX4 uORB Read/Enabled Subsystem'
//  '<S14>'  : 'uORB_MODBUS_TCP/PX4 uORB Read1/Enabled Subsystem'
//  '<S15>'  : 'uORB_MODBUS_TCP/PX4 uORB Read2/Enabled Subsystem'
//  '<S16>'  : 'uORB_MODBUS_TCP/PX4 uORB Read3/Enabled Subsystem'


//-
//  Requirements for '<Root>': uORB_MODBUS_TCP


#endif                                 // uORB_MODBUS_TCP_h_

//
// File trailer for generated code.
//
// [EOF]
//
