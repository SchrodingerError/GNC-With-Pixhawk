//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: uORB_MODBUS_TCP.h
//
// Code generated for Simulink model 'uORB_MODBUS_TCP'.
//
// Model version                  : 1.16
// Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
// C/C++ source code generated on : Sat Mar 22 17:15:30 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef uORB_MODBUS_TCP_h_
#define uORB_MODBUS_TCP_h_
#include "rtwtypes.h"
#include "uORB_MODBUS_TCP_types.h"
#include "modbus_tcp_client.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
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
#include "modbus_tcp_client.h"

// Block signals (default storage)
struct B_uORB_MODBUS_TCP_T {
  real32_T CFunction3;                 // '<Root>/C Function3'
};

// Real-time Model Data Structure
struct tag_RTM_uORB_MODBUS_TCP_T {
  const char_T * volatile errorStatus;
};

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_B;

#ifdef __cplusplus

}

#endif

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void uORB_MODBUS_TCP_initialize(void);
  extern void uORB_MODBUS_TCP_step(void);
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


//-
//  Requirements for '<Root>': uORB_MODBUS_TCP


#endif                                 // uORB_MODBUS_TCP_h_

//
// File trailer for generated code.
//
// [EOF]
//
