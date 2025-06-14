//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TCP_Test.cpp
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
#include "TCP_Test.h"
#include "rtwtypes.h"

// Block signals (default storage)
B_TCP_Test_T TCP_Test_B;

// Block states (default storage)
DW_TCP_Test_T TCP_Test_DW;

// Real-time model
RT_MODEL_TCP_Test_T TCP_Test_M_{ };

RT_MODEL_TCP_Test_T *const TCP_Test_M{ &TCP_Test_M_ };

static void rate_monotonic_scheduler(void);

//
// Set which subrates need to run this base step (base rate always runs).
// This function must be called prior to calling the model step function
// in order to remember which rates need to run this base step.  The
// buffering of events allows for overlapping preemption.
//
void TCP_Test_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  // Task runs when its counter is zero, computed via rtmStepTask macro
  eventFlags[1] = ((boolean_T)rtmStepTask(TCP_Test_M, 1));
  eventFlags[2] = ((boolean_T)rtmStepTask(TCP_Test_M, 2));
  eventFlags[3] = ((boolean_T)rtmStepTask(TCP_Test_M, 3));
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

  (TCP_Test_M->Timing.TaskCounters.TID[1])++;
  if ((TCP_Test_M->Timing.TaskCounters.TID[1]) > 6) {// Sample time: [0.7s, 0.0s] 
    TCP_Test_M->Timing.TaskCounters.TID[1] = 0;
  }

  (TCP_Test_M->Timing.TaskCounters.TID[2])++;
  if ((TCP_Test_M->Timing.TaskCounters.TID[2]) > 9) {// Sample time: [1.0s, 0.0s] 
    TCP_Test_M->Timing.TaskCounters.TID[2] = 0;
  }

  (TCP_Test_M->Timing.TaskCounters.TID[3])++;
  if ((TCP_Test_M->Timing.TaskCounters.TID[3]) > 299) {// Sample time: [30.0s, 0.0s] 
    TCP_Test_M->Timing.TaskCounters.TID[3] = 0;
  }
}

// Model step function for TID0
void TCP_Test_step0(void)         // Sample time: [0.099999999999999992s, 0.0s]
{
  {                               // Sample time: [0.099999999999999992s, 0.0s]
    rate_monotonic_scheduler();
  }
}

// Model step function for TID1
void TCP_Test_step1(void)              // Sample time: [0.7s, 0.0s]
{
  // CFunction: '<Root>/C Function'
  {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "192.168.0.210", &server_addr.sin_addr) <= 0) {
      close(sock);
    }

    int result = connect(sock, (struct sockaddr*)&server_addr, sizeof
                         (server_addr));
    if (result < 0) {
      close(sock);
    }

    char message[] = "Hello from PX4 very fast!";
    send(sock, message, strlen(message), 0);
    close(sock);
  }
}

// Model step function for TID2
void TCP_Test_step2(void)              // Sample time: [1.0s, 0.0s]
{
  uint64_T tmp;

  // MATLABSystem: '<Root>/PX4 Timestamp'
  tmp = hrt_absolute_time();

  // MATLABSystem: '<Root>/PX4 Timestamp'
  TCP_Test_B.PX4Timestamp = tmp;

  // CFunction: '<Root>/C Function1' incorporates:
  //   MATLABSystem: '<Root>/PX4 Timestamp'

  {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
      return;                          // Failed to create socket
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.129");

    // Convert uint64 to a char array (string)
    char message[32];
    snprintf(message, sizeof(message), "%llu", (unsigned long long)
             TCP_Test_B.PX4Timestamp); // Convert to string

    // Send the formatted string over UDP
    sendto(sock, message, strlen(message), 0, (struct sockaddr*)&server_addr,
           sizeof(server_addr));
    close(sock);
  }
}

// Model step function for TID3
void TCP_Test_step3(void)              // Sample time: [30.0s, 0.0s]
{
  // CFunction: '<Root>/C Function2'
  {
    // uint64_T initial_time;
    // uint64_T current_time;

    // initial_time = hrt_absolute_time();
    // current_time = hrt_absolute_time();

    // while (current_time - 10000000 < initial_time) {
    //
    // }
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "192.168.0.129", &server_addr.sin_addr) <= 0) {
      close(sock);
    }

    int result = connect(sock, (struct sockaddr*)&server_addr, sizeof
                         (server_addr));
    if (result < 0) {
      close(sock);
    }

    char message[] = "Sleeping for 10s";
    send(sock, message, strlen(message), 0);

    //usleep(10 * 1000000);
    uint64_t start_time = hrt_absolute_time();// Get current time in microseconds
    while (hrt_absolute_time() - start_time < 10 * 1000000) {
      // Do nothing, just waste CPU cycles
    }

    char message2[] = "Awakened after 10s";
    send(sock, message2, strlen(message2), 0);
    close(sock);
  }
}

// Use this function only if you need to maintain compatibility with an existing static main program.
void TCP_Test_step(int_T tid)
{
  switch (tid) {
   case 0 :
    TCP_Test_step0();
    break;

   case 1 :
    TCP_Test_step1();
    break;

   case 2 :
    TCP_Test_step2();
    break;

   case 3 :
    TCP_Test_step3();
    break;

   default :
    // do nothing
    break;
  }
}

// Model initialize function
void TCP_Test_initialize(void)
{
  // Start for MATLABSystem: '<Root>/PX4 Timestamp'
  TCP_Test_DW.obj.matlabCodegenIsDeleted = false;
  TCP_Test_DW.objisempty = true;
  TCP_Test_DW.obj.isInitialized = 1;
  TCP_Test_DW.obj.isSetupComplete = true;
}

// Model terminate function
void TCP_Test_terminate(void)
{
  // Terminate for MATLABSystem: '<Root>/PX4 Timestamp'
  if (!TCP_Test_DW.obj.matlabCodegenIsDeleted) {
    TCP_Test_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/PX4 Timestamp'
}

//
// File trailer for generated code.
//
// [EOF]
//
