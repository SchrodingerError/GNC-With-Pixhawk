//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include "TCP_Test.h"
#include "TCP_Test_private.h"
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
px4_sem_t subrateTaskSem[3];
int taskId[3];
pthread_t schedulerThread;
pthread_t baseRateThread;
void *threadJoinStatus;
int terminatingmodel = 0;
pthread_t subRateThread[3];
int subratePriority[3];
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

    TCP_Test_step(subRateId);

    // Get model outputs here
  }

  pthread_exit((void *)0);
  return NULL;
}

void *baseRateTask(void *arg)
{
  int_T i;
  runModel = (rtmGetErrorStatus(TCP_Test_M) == (nullptr));
  while (runModel) {
    px4_sem_wait(&baserateTaskSem);

#ifdef MW_RTOS_DEBUG

    printf("*base rate task semaphore received\n");
    fflush(stdout);

#endif

    for (i = 1
         ; i <= 3; i++) {
      if (rtmStepTask(TCP_Test_M, i)
          ) {
        px4_sem_post(&subrateTaskSem[ i - 1
                     ]);
      }
    }

    TCP_Test_step(0);

    // Get model outputs here
    stopRequested = !((rtmGetErrorStatus(TCP_Test_M) == (nullptr)));
  }

  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(TCP_Test_M, "stopping the model");
  runModel = 0;
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    int i;

    // Signal all periodic tasks to complete
    for (i=0; i<3; i++) {
      CHECK_STATUS(px4_sem_post(&subrateTaskSem[i]), 0, "px4_sem_post");
      CHECK_STATUS(px4_sem_destroy(&subrateTaskSem[i]), 0, "px4_sem_destroy");
    }

    // Wait for all periodic tasks to complete
    for (i=0; i<3; i++) {
      CHECK_STATUS(pthread_join(subRateThread[i], &threadJoinStatus), 0,
                   "pthread_join");
    }

    runModel = 0;
  }

  MW_PX4_Terminate();

  // Terminate model
  TCP_Test_terminate();
  px4_sem_post(&stopSem);
  return NULL;
}

int px4_simulink_app_task_main (int argc, char *argv[])
{
  subratePriority[0] = 249;
  subratePriority[1] = 248;
  subratePriority[2] = 247;
  px4_simulink_app_control_MAVLink();
  rtmSetErrorStatus(TCP_Test_M, 0);

  // Initialize model
  TCP_Test_initialize();

  // Call RTOS Initialization function
  nuttxRTOSInit(0.099999999999999992, 3);

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
