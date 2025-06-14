//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TCP_Test_types.h
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
#ifndef TCP_Test_types_h_
#define TCP_Test_types_h_
#include "rtwtypes.h"
#ifndef struct_e_px4_internal_block_SampleTi_T
#define struct_e_px4_internal_block_SampleTi_T

struct e_px4_internal_block_SampleTi_T
{
  int32_T __dummy;
};

#endif                                // struct_e_px4_internal_block_SampleTi_T

#ifndef struct_px4_internal_block_getPX4Abso_T
#define struct_px4_internal_block_getPX4Abso_T

struct px4_internal_block_getPX4Abso_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_px4_internal_block_SampleTi_T SampleTimeHandler;
};

#endif                                // struct_px4_internal_block_getPX4Abso_T

// Forward declaration for rtModel
typedef struct tag_RTM_TCP_Test_T RT_MODEL_TCP_Test_T;

#endif                                 // TCP_Test_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
