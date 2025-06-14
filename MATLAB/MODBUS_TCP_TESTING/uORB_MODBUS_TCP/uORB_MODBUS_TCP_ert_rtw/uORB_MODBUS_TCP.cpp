//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: uORB_MODBUS_TCP.cpp
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
#include "uORB_MODBUS_TCP.h"
#include "rtwtypes.h"

// Block signals (default storage)
B_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_B;

// Block states (default storage)
DW_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_DW;

// Real-time model
RT_MODEL_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_M_{ };

RT_MODEL_uORB_MODBUS_TCP_T *const uORB_MODBUS_TCP_M{ &uORB_MODBUS_TCP_M_ };

static void rate_monotonic_scheduler(void);

//
// Set which subrates need to run this base step (base rate always runs).
// This function must be called prior to calling the model step function
// in order to remember which rates need to run this base step.  The
// buffering of events allows for overlapping preemption.
//
void uORB_MODBUS_TCP_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  // Task runs when its counter is zero, computed via rtmStepTask macro
  eventFlags[1] = ((boolean_T)rtmStepTask(uORB_MODBUS_TCP_M, 1));
}

//
//         This function updates active task flag for each subrate
//         and rate transition flags for tasks that exchange data.
//         The function assumes rate-monotonic multitasking scheduler.
//         The function must be called at model base rate so that
//         the generated code self-manages all its subrates and rate
//         transition flags.
//
static void rate_monotonic_scheduler(void)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (uORB_MODBUS_TCP_M->Timing.TaskCounters.TID[1])++;
  if ((uORB_MODBUS_TCP_M->Timing.TaskCounters.TID[1]) > 19) {// Sample time: [5.0s, 0.0s] 
    uORB_MODBUS_TCP_M->Timing.TaskCounters.TID[1] = 0;
  }
}

// Model step function for TID0
void uORB_MODBUS_TCP_step0(void)       // Sample time: [0.25s, 0.0s]
{
  int32_T i;

  {                                    // Sample time: [0.25s, 0.0s]
    rate_monotonic_scheduler();
  }

  // CFunction: '<Root>/PLC MODBUS TCP ReadAll'
  {
    // Rename variables following the new convention.
    const int num_DI_to_read = 10;
    const int num_IR_to_read = 10;
    const int num_CO_to_read = 10;
    const int num_HR_to_read = 10;
    const int expected_uorb_DI = 128;
    const int expected_uorb_IR = 128;
    const int expected_uorb_CO = 128;
    const int expected_uorb_HR = 128;

    // Create the Modbus client with renamed parameters.
    static ModbusTCPClient modbus("192.168.0.190",
      5020,
      num_CO_to_read,
      num_DI_to_read,
      num_IR_to_read,
      num_HR_to_read);

    // Prepare buffers for holding values before assigning them to the output arrays.
    bool DI_array_buffer[num_DI_to_read] = { 0 };

    uint16_t IR_array_buffer[num_IR_to_read] = { 0 };

    bool CO_array_buffer[num_CO_to_read] = { 0 };

    uint16_t HR_array_buffer[num_HR_to_read] = { 0 };

    // Connect to the Modbus server if not already connected.
    if (!modbus.isConnected()) {
      modbus.setTimeout(3000);         // Set timeout in milliseconds
      if (!modbus.connectServer()) {
        printf("Failed to connect to MODBUS server in!\n");
      }
    }

    if (modbus.readAll() != ModbusError::NONE) {
      printf("Error calling modbus.readAll()\n");
    }

    // --- Holding Registers (HR) ---
    // Read a subset of HR registers into our buffer.
    ModbusError HR_error = modbus.getMultipleHoldingRegisters(0, num_HR_to_read,
      HR_array_buffer);
    if (HR_error != ModbusError::NONE) {
      printf("Failed to read HR registers: error code %d\n", static_cast<int>
             (HR_error));
    }

    // Assign HR buffer values to the output array.
    for (int i = 0; i < expected_uorb_HR; i++) {
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o4[i] = (i < num_HR_to_read) ?
        HR_array_buffer[i] : 0;
    }

    // --- Input Registers (IR) ---
    // Read a subset of IR registers into our buffer.
    ModbusError IR_error = modbus.getMultipleInputRegisters(0, num_IR_to_read,
      IR_array_buffer);
    if (IR_error != ModbusError::NONE) {
      printf("Failed to read IR registers: error code %d\n", static_cast<int>
             (IR_error));
    }

    // Assign IR buffer values to the output array.
    for (int i = 0; i < expected_uorb_IR; i++) {
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o2[i] = (i < num_IR_to_read) ?
        IR_array_buffer[i] : 0;
    }

    // --- Discrete Inputs (DI) ---
    // Read a subset of DI registers into our buffer.
    ModbusError DI_error = modbus.getMultipleDiscreteInputs(0, num_DI_to_read,
      DI_array_buffer);
    if (DI_error != ModbusError::NONE) {
      printf("Failed to read DI registers: error code %d\n", static_cast<int>
             (DI_error));
    }

    // Assign DI buffer values to the output array.
    for (int i = 0; i < expected_uorb_DI; i++) {
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o1[i] = (i < num_DI_to_read) ?
        DI_array_buffer[i] : 0;
    }

    // --- Coils (CO) ---
    // Read a subset of CO registers (coils) into our buffer.
    ModbusError CO_error = modbus.getMultipleCoils(0, num_CO_to_read,
      CO_array_buffer);
    if (CO_error != ModbusError::NONE) {
      printf("Failed to read CO registers: error code %d\n", static_cast<int>
             (CO_error));
    }

    // Assign CO buffer values to the output array.
    for (int i = 0; i < expected_uorb_CO; i++) {
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o3[i] = (i < num_CO_to_read) ?
        CO_array_buffer[i] : 0;
    }
  }

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Constant: '<S1>/Constant'

  uORB_MODBUS_TCP_B.BusAssignment = uORB_MODBUS_TCP_P.Constant_Value;

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   CFunction: '<Root>/PLC MODBUS TCP ReadAll'

  for (i = 0; i < 128; i++) {
    uORB_MODBUS_TCP_B.BusAssignment.register_array_read[i] =
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o4[i];
  }

  // MATLABSystem: '<S9>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  uORB_write_step(uORB_MODBUS_TCP_DW.obj_m.orbMetadataObj,
                  &uORB_MODBUS_TCP_DW.obj_m.orbAdvertiseObj,
                  &uORB_MODBUS_TCP_B.BusAssignment);

  // BusAssignment: '<Root>/Bus Assignment1' incorporates:
  //   Constant: '<S2>/Constant'

  uORB_MODBUS_TCP_B.BusAssignment1 = uORB_MODBUS_TCP_P.Constant_Value_m;

  // BusAssignment: '<Root>/Bus Assignment1' incorporates:
  //   CFunction: '<Root>/PLC MODBUS TCP ReadAll'

  for (i = 0; i < 128; i++) {
    uORB_MODBUS_TCP_B.BusAssignment1.coil_array_read[i] =
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o3[i];
  }

  // MATLABSystem: '<S10>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment1'

  uORB_write_step(uORB_MODBUS_TCP_DW.obj_g.orbMetadataObj,
                  &uORB_MODBUS_TCP_DW.obj_g.orbAdvertiseObj,
                  &uORB_MODBUS_TCP_B.BusAssignment1);

  // BusAssignment: '<Root>/Bus Assignment2' incorporates:
  //   Constant: '<S3>/Constant'

  uORB_MODBUS_TCP_B.BusAssignment2 = uORB_MODBUS_TCP_P.Constant_Value_f;

  // BusAssignment: '<Root>/Bus Assignment2' incorporates:
  //   CFunction: '<Root>/PLC MODBUS TCP ReadAll'

  for (i = 0; i < 128; i++) {
    uORB_MODBUS_TCP_B.BusAssignment2.register_array[i] =
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o2[i];
  }

  // MATLABSystem: '<S11>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment2'

  uORB_write_step(uORB_MODBUS_TCP_DW.obj_a.orbMetadataObj,
                  &uORB_MODBUS_TCP_DW.obj_a.orbAdvertiseObj,
                  &uORB_MODBUS_TCP_B.BusAssignment2);

  // BusAssignment: '<Root>/Bus Assignment3' incorporates:
  //   Constant: '<S4>/Constant'

  uORB_MODBUS_TCP_B.BusAssignment3 = uORB_MODBUS_TCP_P.Constant_Value_d;

  // BusAssignment: '<Root>/Bus Assignment3' incorporates:
  //   CFunction: '<Root>/PLC MODBUS TCP ReadAll'

  for (i = 0; i < 128; i++) {
    uORB_MODBUS_TCP_B.BusAssignment3.input_array[i] =
      uORB_MODBUS_TCP_B.PLCMODBUSTCPReadAll_o1[i];
  }

  // MATLABSystem: '<S12>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment3'

  uORB_write_step(uORB_MODBUS_TCP_DW.obj_f.orbMetadataObj,
                  &uORB_MODBUS_TCP_DW.obj_f.orbAdvertiseObj,
                  &uORB_MODBUS_TCP_B.BusAssignment3);
}

// Model step function for TID1
void uORB_MODBUS_TCP_step1(void)       // Sample time: [5.0s, 0.0s]
{
  boolean_T b_varargout_1;

  // MATLABSystem: '<S8>/SourceBlock'
  b_varargout_1 = uORB_read_step(uORB_MODBUS_TCP_DW.obj.orbMetadataObj,
    &uORB_MODBUS_TCP_DW.obj.eventStructObj, &uORB_MODBUS_TCP_B.r3, false, 1.0);

  // MATLABSystem: '<S8>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o1 = b_varargout_1;

  // MATLABSystem: '<S8>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o2_j = uORB_MODBUS_TCP_B.r3;

  // Outputs for Enabled SubSystem: '<S8>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S16>/Enable'

  if (uORB_MODBUS_TCP_B.SourceBlock_o1) {
    // SignalConversion generated from: '<S16>/In1' incorporates:
    //   MATLABSystem: '<S8>/SourceBlock'

    uORB_MODBUS_TCP_B.In1_b = uORB_MODBUS_TCP_B.SourceBlock_o2_j;
  }

  // End of Outputs for SubSystem: '<S8>/Enabled Subsystem'

  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = uORB_read_step(uORB_MODBUS_TCP_DW.obj_e.orbMetadataObj,
    &uORB_MODBUS_TCP_DW.obj_e.eventStructObj, &uORB_MODBUS_TCP_B.r1, false, 1.0);

  // MATLABSystem: '<S7>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o1_g = b_varargout_1;

  // MATLABSystem: '<S7>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o2 = uORB_MODBUS_TCP_B.r1;

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S15>/Enable'

  if (uORB_MODBUS_TCP_B.SourceBlock_o1_g) {
    // SignalConversion generated from: '<S15>/In1' incorporates:
    //   MATLABSystem: '<S7>/SourceBlock'

    uORB_MODBUS_TCP_B.In1 = uORB_MODBUS_TCP_B.SourceBlock_o2;
  }

  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'

  // MATLABSystem: '<S6>/SourceBlock'
  b_varargout_1 = uORB_read_step(uORB_MODBUS_TCP_DW.obj_j.orbMetadataObj,
    &uORB_MODBUS_TCP_DW.obj_j.eventStructObj, &uORB_MODBUS_TCP_B.r2, false, 1.0);

  // MATLABSystem: '<S6>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o1_l = b_varargout_1;

  // MATLABSystem: '<S6>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o2_d = uORB_MODBUS_TCP_B.r2;

  // Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S14>/Enable'

  if (uORB_MODBUS_TCP_B.SourceBlock_o1_l) {
    // SignalConversion generated from: '<S14>/In1' incorporates:
    //   MATLABSystem: '<S6>/SourceBlock'

    uORB_MODBUS_TCP_B.In1_m = uORB_MODBUS_TCP_B.SourceBlock_o2_d;
  }

  // End of Outputs for SubSystem: '<S6>/Enabled Subsystem'

  // MATLABSystem: '<S5>/SourceBlock'
  b_varargout_1 = uORB_read_step(uORB_MODBUS_TCP_DW.obj_d.orbMetadataObj,
    &uORB_MODBUS_TCP_DW.obj_d.eventStructObj, &uORB_MODBUS_TCP_B.r, false, 1.0);

  // MATLABSystem: '<S5>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o1_c = b_varargout_1;

  // MATLABSystem: '<S5>/SourceBlock'
  uORB_MODBUS_TCP_B.SourceBlock_o2_l = uORB_MODBUS_TCP_B.r;

  // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S13>/Enable'

  if (uORB_MODBUS_TCP_B.SourceBlock_o1_c) {
    // SignalConversion generated from: '<S13>/In1' incorporates:
    //   MATLABSystem: '<S5>/SourceBlock'

    uORB_MODBUS_TCP_B.In1_e = uORB_MODBUS_TCP_B.SourceBlock_o2_l;
  }

  // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'

  // CFunction: '<Root>/Print All PLC Values'
  printf("\n");

  // Print table header
  printf("%-5s %-5s %-5s %-5s %-5s\n", "Idx", "CO", "DI", "IR", "HR");

  // Print the first 10 rows
  for (int i = 0; i < 10; i++) {
    // Print index, then CO, DI as 1 (true) or 0 (false), then IR and HR values.
    printf("%-5d %-5d %-5d %-5u %-5u\n",
           i,
           uORB_MODBUS_TCP_B.In1_m.coil_array_read[i] ? 1 : 0,
           uORB_MODBUS_TCP_B.In1_b.input_array[i] ? 1 : 0,
           uORB_MODBUS_TCP_B.In1.register_array[i],
           uORB_MODBUS_TCP_B.In1_e.register_array_read[i]);
  }
}

// Use this function only if you need to maintain compatibility with an existing static main program.
void uORB_MODBUS_TCP_step(int_T tid)
{
  switch (tid) {
   case 0 :
    uORB_MODBUS_TCP_step0();
    break;

   case 1 :
    uORB_MODBUS_TCP_step1();
    break;

   default :
    // do nothing
    break;
  }
}

// Model initialize function
void uORB_MODBUS_TCP_initialize(void)
{
  // SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem'
  // SystemInitialize for SignalConversion generated from: '<S13>/In1' incorporates:
  //   Outport: '<S13>/Out1'

  uORB_MODBUS_TCP_B.In1_e = uORB_MODBUS_TCP_P.Out1_Y0;

  // End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem'

  // SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem'
  // SystemInitialize for SignalConversion generated from: '<S14>/In1' incorporates:
  //   Outport: '<S14>/Out1'

  uORB_MODBUS_TCP_B.In1_m = uORB_MODBUS_TCP_P.Out1_Y0_g;

  // End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem'

  // SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem'
  // SystemInitialize for SignalConversion generated from: '<S15>/In1' incorporates:
  //   Outport: '<S15>/Out1'

  uORB_MODBUS_TCP_B.In1 = uORB_MODBUS_TCP_P.Out1_Y0_h;

  // End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem'

  // SystemInitialize for Enabled SubSystem: '<S8>/Enabled Subsystem'
  // SystemInitialize for SignalConversion generated from: '<S16>/In1' incorporates:
  //   Outport: '<S16>/Out1'

  uORB_MODBUS_TCP_B.In1_b = uORB_MODBUS_TCP_P.Out1_Y0_l;

  // End of SystemInitialize for SubSystem: '<S8>/Enabled Subsystem'

  // Start for MATLABSystem: '<S9>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  uORB_MODBUS_TCP_DW.obj_m.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty_nn = true;
  uORB_MODBUS_TCP_DW.obj_m.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj_m.orbMetadataObj = ORB_ID(plc_holding_registers_read);
  uORB_write_initialize(uORB_MODBUS_TCP_DW.obj_m.orbMetadataObj,
                        &uORB_MODBUS_TCP_DW.obj_m.orbAdvertiseObj,
                        &uORB_MODBUS_TCP_B.BusAssignment, 1);
  uORB_MODBUS_TCP_DW.obj_m.isSetupComplete = true;

  // Start for MATLABSystem: '<S10>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment1'

  uORB_MODBUS_TCP_DW.obj_g.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty_i = true;
  uORB_MODBUS_TCP_DW.obj_g.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj_g.orbMetadataObj = ORB_ID(plc_coils_read);
  uORB_write_initialize(uORB_MODBUS_TCP_DW.obj_g.orbMetadataObj,
                        &uORB_MODBUS_TCP_DW.obj_g.orbAdvertiseObj,
                        &uORB_MODBUS_TCP_B.BusAssignment1, 1);
  uORB_MODBUS_TCP_DW.obj_g.isSetupComplete = true;

  // Start for MATLABSystem: '<S11>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment2'

  uORB_MODBUS_TCP_DW.obj_a.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty_n = true;
  uORB_MODBUS_TCP_DW.obj_a.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj_a.orbMetadataObj = ORB_ID(plc_input_registers);
  uORB_write_initialize(uORB_MODBUS_TCP_DW.obj_a.orbMetadataObj,
                        &uORB_MODBUS_TCP_DW.obj_a.orbAdvertiseObj,
                        &uORB_MODBUS_TCP_B.BusAssignment2, 1);
  uORB_MODBUS_TCP_DW.obj_a.isSetupComplete = true;

  // Start for MATLABSystem: '<S12>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment3'

  uORB_MODBUS_TCP_DW.obj_f.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty = true;
  uORB_MODBUS_TCP_DW.obj_f.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj_f.orbMetadataObj = ORB_ID(plc_discrete_inputs);
  uORB_write_initialize(uORB_MODBUS_TCP_DW.obj_f.orbMetadataObj,
                        &uORB_MODBUS_TCP_DW.obj_f.orbAdvertiseObj,
                        &uORB_MODBUS_TCP_B.BusAssignment3, 1);
  uORB_MODBUS_TCP_DW.obj_f.isSetupComplete = true;

  // Start for MATLABSystem: '<S8>/SourceBlock'
  uORB_MODBUS_TCP_DW.obj.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty_e = true;
  uORB_MODBUS_TCP_DW.obj.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj.orbMetadataObj = ORB_ID(plc_discrete_inputs);
  uORB_read_initialize(uORB_MODBUS_TCP_DW.obj.orbMetadataObj,
                       &uORB_MODBUS_TCP_DW.obj.eventStructObj);
  uORB_MODBUS_TCP_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S7>/SourceBlock'
  uORB_MODBUS_TCP_DW.obj_e.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty_b = true;
  uORB_MODBUS_TCP_DW.obj_e.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj_e.orbMetadataObj = ORB_ID(plc_input_registers);
  uORB_read_initialize(uORB_MODBUS_TCP_DW.obj_e.orbMetadataObj,
                       &uORB_MODBUS_TCP_DW.obj_e.eventStructObj);
  uORB_MODBUS_TCP_DW.obj_e.isSetupComplete = true;

  // Start for MATLABSystem: '<S6>/SourceBlock'
  uORB_MODBUS_TCP_DW.obj_j.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty_bt = true;
  uORB_MODBUS_TCP_DW.obj_j.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj_j.orbMetadataObj = ORB_ID(plc_coils_read);
  uORB_read_initialize(uORB_MODBUS_TCP_DW.obj_j.orbMetadataObj,
                       &uORB_MODBUS_TCP_DW.obj_j.eventStructObj);
  uORB_MODBUS_TCP_DW.obj_j.isSetupComplete = true;

  // Start for MATLABSystem: '<S5>/SourceBlock'
  uORB_MODBUS_TCP_DW.obj_d.matlabCodegenIsDeleted = false;
  uORB_MODBUS_TCP_DW.objisempty_a = true;
  uORB_MODBUS_TCP_DW.obj_d.isInitialized = 1;
  uORB_MODBUS_TCP_DW.obj_d.orbMetadataObj = ORB_ID(plc_holding_registers_read);
  uORB_read_initialize(uORB_MODBUS_TCP_DW.obj_d.orbMetadataObj,
                       &uORB_MODBUS_TCP_DW.obj_d.eventStructObj);
  uORB_MODBUS_TCP_DW.obj_d.isSetupComplete = true;
}

// Model terminate function
void uORB_MODBUS_TCP_terminate(void)
{
  // Terminate for MATLABSystem: '<S9>/SinkBlock'
  if (!uORB_MODBUS_TCP_DW.obj_m.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj_m.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj_m.isSetupComplete) {
      uORB_write_terminate(&uORB_MODBUS_TCP_DW.obj_m.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S9>/SinkBlock'

  // Terminate for MATLABSystem: '<S10>/SinkBlock'
  if (!uORB_MODBUS_TCP_DW.obj_g.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj_g.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj_g.isSetupComplete) {
      uORB_write_terminate(&uORB_MODBUS_TCP_DW.obj_g.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S10>/SinkBlock'

  // Terminate for MATLABSystem: '<S11>/SinkBlock'
  if (!uORB_MODBUS_TCP_DW.obj_a.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj_a.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj_a.isSetupComplete) {
      uORB_write_terminate(&uORB_MODBUS_TCP_DW.obj_a.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S11>/SinkBlock'

  // Terminate for MATLABSystem: '<S12>/SinkBlock'
  if (!uORB_MODBUS_TCP_DW.obj_f.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj_f.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj_f.isSetupComplete) {
      uORB_write_terminate(&uORB_MODBUS_TCP_DW.obj_f.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S12>/SinkBlock'

  // Terminate for MATLABSystem: '<S8>/SourceBlock'
  if (!uORB_MODBUS_TCP_DW.obj.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj.isSetupComplete) {
      uORB_read_terminate(&uORB_MODBUS_TCP_DW.obj.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S8>/SourceBlock'

  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!uORB_MODBUS_TCP_DW.obj_e.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj_e.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj_e.isSetupComplete) {
      uORB_read_terminate(&uORB_MODBUS_TCP_DW.obj_e.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'

  // Terminate for MATLABSystem: '<S6>/SourceBlock'
  if (!uORB_MODBUS_TCP_DW.obj_j.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj_j.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj_j.isSetupComplete) {
      uORB_read_terminate(&uORB_MODBUS_TCP_DW.obj_j.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S6>/SourceBlock'

  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!uORB_MODBUS_TCP_DW.obj_d.matlabCodegenIsDeleted) {
    uORB_MODBUS_TCP_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((uORB_MODBUS_TCP_DW.obj_d.isInitialized == 1) &&
        uORB_MODBUS_TCP_DW.obj_d.isSetupComplete) {
      uORB_read_terminate(&uORB_MODBUS_TCP_DW.obj_d.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
}

//
// File trailer for generated code.
//
// [EOF]
//
