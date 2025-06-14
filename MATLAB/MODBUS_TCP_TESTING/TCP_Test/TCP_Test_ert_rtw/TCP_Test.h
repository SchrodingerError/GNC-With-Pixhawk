//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TCP_Test.h
//
// Code generated for Simulink model 'TCP_Test'.
//
// Model version                  : 1.24
// Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
// C/C++ source code generated on : Wed Mar  5 18:29:04 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objective: Debugging
// Validation result: Not run
//
#ifndef TCP_Test_h_
#define TCP_Test_h_
#include <drivers/drv_hrt.h>
#include "rtwtypes.h"
#include "TCP_Test_types.h"
#include <unistd.h>                    // For usleep()

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
#include "tcp_send.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Block signals (default storage)
struct B_TCP_Test_T {
  uint64_T PX4Timestamp;               // '<Root>/PX4 Timestamp'
};

// Block states (default storage) for system '<Root>'
struct DW_TCP_Test_T {
  px4_internal_block_getPX4Abso_T obj; // '<Root>/PX4 Timestamp'
  boolean_T objisempty;                // '<Root>/PX4 Timestamp'
};

// Real-time Model Data Structure
struct tag_RTM_TCP_Test_T {
  const char_T * volatile errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    struct {
      uint16_T TID[4];
    } TaskCounters;
  } Timing;
};

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_TCP_Test_T TCP_Test_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_TCP_Test_T TCP_Test_DW;

// External function called from main
#ifdef __cplusplus

extern "C"
{

#endif

  extern void TCP_Test_SetEventsForThisBaseStep(boolean_T *eventFlags);

#ifdef __cplusplus

}

#endif

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void TCP_Test_initialize(void);
  extern void TCP_Test_step0(void);
  extern void TCP_Test_step1(void);
  extern void TCP_Test_step2(void);
  extern void TCP_Test_step3(void);
  extern void TCP_Test_step(int_T tid);
  extern void TCP_Test_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_TCP_Test_T *const TCP_Test_M;

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
//  '<Root>' : 'TCP_Test'


//-
//  Requirements for '<Root>': TCP_Test


#endif                                 // TCP_Test_h_

//
// File trailer for generated code.
//
// [EOF]
//
