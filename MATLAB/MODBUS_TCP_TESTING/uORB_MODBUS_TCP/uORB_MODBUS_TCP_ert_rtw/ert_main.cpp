//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include "uORB_MODBUS_TCP.h"
#include "uORB_MODBUS_TCP_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "MW_PX4_TaskControl.h"
#include "nuttxinitialize.h"
#define UNUSED(x)                      x = x
#define NAMELEN                        16

// Function prototype declaration
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
px4_sem_t stopSem;
px4_sem_t baserateTaskSem;
px4_sem_t subrateTaskSem[1];
int taskId[1];
pthread_t schedulerThread;
pthread_t baseRateThread;
void *threadJoinStatus;
int terminatingmodel = 0;
pthread_t subRateThread[1];
int subratePriority[1];
void *subrateTask(void *arg)
{
  int tid = *((int *) arg);
  int subRateId;
  subRateId = tid + 1;
  while (runModel) {
    px4_sem_wait(&subrateTaskSem[tid]);
    if (terminatingmodel)
      break;

#ifdef MW_RTOS_DEBUG

    printf(" -subrate task %d semaphore received\n", subRateId);

#endif

    uORB_MODBUS_TCP_step(subRateId);

    // Get model outputs here
  }

  pthread_exit((void *)0);
  return NULL;
}

void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(uORB_MODBUS_TCP_M) == (nullptr));
  while (runModel) {
    px4_sem_wait(&baserateTaskSem);

#ifdef MW_RTOS_DEBUG

    printf("*base rate task semaphore received\n");
    fflush(stdout);

#endif

    if (rtmStepTask(uORB_MODBUS_TCP_M, 1)
        ) {
      px4_sem_post(&subrateTaskSem[0]);
    }

    uORB_MODBUS_TCP_step(0);

    // Get model outputs here
    stopRequested = !((rtmGetErrorStatus(uORB_MODBUS_TCP_M) == (nullptr)));
  }

  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(uORB_MODBUS_TCP_M, "stopping the model");
  runModel = 0;
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    int i;

    // Signal all periodic tasks to complete
    for (i=0; i<1; i++) {
      CHECK_STATUS(px4_sem_post(&subrateTaskSem[i]), 0, "px4_sem_post");
      CHECK_STATUS(px4_sem_destroy(&subrateTaskSem[i]), 0, "px4_sem_destroy");
    }

    // Wait for all periodic tasks to complete
    for (i=0; i<1; i++) {
      CHECK_STATUS(pthread_join(subRateThread[i], &threadJoinStatus), 0,
                   "pthread_join");
    }

    runModel = 0;
  }

  MW_PX4_Terminate();

  // Terminate model
  uORB_MODBUS_TCP_terminate();
  px4_sem_post(&stopSem);
  return NULL;
}

int px4_simulink_app_task_main (int argc, char *argv[])
{
  subratePriority[0] = 249;
  px4_simulink_app_control_MAVLink();
  rtmSetErrorStatus(uORB_MODBUS_TCP_M, 0);

  // Initialize model
  uORB_MODBUS_TCP_initialize();

  // Call RTOS Initialization function
  nuttxRTOSInit(0.25, 1);

  // Wait for stop semaphore
  px4_sem_wait(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(px4_sem_destroy(&timerTaskSem[i]), 0, "px4_sem_destroy");
    }
  }

#endif

  return 0;
}

//
// File trailer for generated code.
//
// [EOF]
//
