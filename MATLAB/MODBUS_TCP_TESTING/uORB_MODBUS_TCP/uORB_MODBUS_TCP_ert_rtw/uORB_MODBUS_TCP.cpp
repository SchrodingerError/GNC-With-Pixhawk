//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: uORB_MODBUS_TCP.cpp
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
#include "uORB_MODBUS_TCP.h"

// Block signals (default storage)
B_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_B;

// Real-time model
RT_MODEL_uORB_MODBUS_TCP_T uORB_MODBUS_TCP_M_{ };

RT_MODEL_uORB_MODBUS_TCP_T *const uORB_MODBUS_TCP_M{ &uORB_MODBUS_TCP_M_ };

// Model step function
void uORB_MODBUS_TCP_step(void)
{
  // CFunction: '<Root>/C Function3'
  {
    static ModbusTCPClient modbus("192.168.0.249", 5020, 10, 10, 10, 10);
    if (!modbus.isConnected()) {
      modbus.setTimeout(1000);
      if (!modbus.connectServer()) {
        printf("Failed to connect to MODBUS server!\n");
        return;
      }
    }

    const int num_reads = 1000;
    uint16_t last_value = 0;
    uint16_t holdingRegisters[10] = { 0 };

    float sum_differences = 0.0;

    // Initial read to populate last_value
    modbus.readMultipleHoldingRegisters(0, 10, holdingRegisters);
    last_value = holdingRegisters[0];

    // Loop 1000 times
    for (int i = 0; i < num_reads; ++i) {
      modbus.readMultipleHoldingRegisters(0, 10, holdingRegisters);
      uint16_t current_value = holdingRegisters[0];

      // Handle 16-bit rollover
      uint16_t diff = (current_value >= last_value)
        ? (current_value - last_value)
        : (current_value + (65536 - last_value));
      sum_differences += (float)diff;
      last_value = current_value;
    }

    // Average the differences
    float avg_diff = sum_differences / num_reads;
    printf("Average time difference between reads (ms): %.2f\n", avg_diff);
  }
}

// Model initialize function
void uORB_MODBUS_TCP_initialize(void)
{
  // (no initialization code required)
}

// Model terminate function
void uORB_MODBUS_TCP_terminate(void)
{
  // (no terminate code required)
}

//
// File trailer for generated code.
//
// [EOF]
//
