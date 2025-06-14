//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: MODBUS_TCP_Test.cpp
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
#include "MODBUS_TCP_Test.h"

// Real-time model
RT_MODEL_MODBUS_TCP_Test_T MODBUS_TCP_Test_M_{ };

RT_MODEL_MODBUS_TCP_Test_T *const MODBUS_TCP_Test_M{ &MODBUS_TCP_Test_M_ };

// Model step function
void MODBUS_TCP_Test_step(void)
{
  // CFunction: '<Root>/C Function3'
  {
    static ModbusTCPClient modbus("192.168.0.129", 5020, 10, 10, 10, 10);
    if (!modbus.isConnected()) {       // Only connect if not already connected
      modbus.setTimeout(1000);
      if (!modbus.connectServer()) {
        printf("Failed to connect to MODBUS server!\n");
        return 1;
      }
    }

    // Read fresh MODBUS values
    modbus.readAll();
    uint16_t new_value = modbus.getHoldingRegister(0);
    printf("After readAll: Holding Register: %u\n", new_value);
  }
}

// Model initialize function
void MODBUS_TCP_Test_initialize(void)
{
  // (no initialization code required)
}

// Model terminate function
void MODBUS_TCP_Test_terminate(void)
{
  // (no terminate code required)
}

//
// File trailer for generated code.
//
// [EOF]
//
