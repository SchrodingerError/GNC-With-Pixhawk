//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: MODBUS_TCP_Test.h
//
// Code generated for Simulink model 'MODBUS_TCP_Test'.
//
// Model version                  : 1.4
// Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
// C/C++ source code generated on : Fri Mar  7 20:25:14 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef MODBUS_TCP_Test_h_
#define MODBUS_TCP_Test_h_
#include "rtwtypes.h"
#include "MODBUS_TCP_Test_types.h"
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

// Real-time Model Data Structure
struct tag_RTM_MODBUS_TCP_Test_T {
  const char_T * volatile errorStatus;
};

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void MODBUS_TCP_Test_initialize(void);
  extern void MODBUS_TCP_Test_step(void);
  extern void MODBUS_TCP_Test_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_MODBUS_TCP_Test_T *const MODBUS_TCP_Test_M;

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
//  '<Root>' : 'MODBUS_TCP_Test'


//-
//  Requirements for '<Root>': MODBUS_TCP_Test


#endif                                 // MODBUS_TCP_Test_h_

//
// File trailer for generated code.
//
// [EOF]
//
