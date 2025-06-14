//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: uORB_MODBUS_TCP_types.h
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
#ifndef uORB_MODBUS_TCP_types_h_
#define uORB_MODBUS_TCP_types_h_
#include "rtwtypes.h"
#include <uORB/topics/plc_holding_registers_read.h>
#include <uORB/topics/plc_coils_read.h>
#include <uORB/topics/plc_input_registers.h>
#include <uORB/topics/plc_discrete_inputs.h>
#ifndef struct_e_px4_internal_block_SampleTi_T
#define struct_e_px4_internal_block_SampleTi_T

struct e_px4_internal_block_SampleTi_T
{
  int32_T __dummy;
};

#endif                                // struct_e_px4_internal_block_SampleTi_T

#ifndef struct_px4_internal_block_Subscriber_T
#define struct_px4_internal_block_Subscriber_T

struct px4_internal_block_Subscriber_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_px4_internal_block_SampleTi_T SampleTimeHandler;
  pollfd_t eventStructObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // struct_px4_internal_block_Subscriber_T

#ifndef struct_px4_internal_block_Publisher__T
#define struct_px4_internal_block_Publisher__T

struct px4_internal_block_Publisher__T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  orb_advert_t orbAdvertiseObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // struct_px4_internal_block_Publisher__T

// Parameters (default storage)
typedef struct P_uORB_MODBUS_TCP_T_ P_uORB_MODBUS_TCP_T;

// Forward declaration for rtModel
typedef struct tag_RTM_uORB_MODBUS_TCP_T RT_MODEL_uORB_MODBUS_TCP_T;

#endif                                 // uORB_MODBUS_TCP_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
