#ifndef __c2_TCP_Test_h__
#define __c2_TCP_Test_h__

/* Forward Declarations */
struct SFc2_TCP_TestInstanceStruct;

/* Type Definitions */
#ifndef c2_typedef_c2_TCP_TestStackData
#define c2_typedef_c2_TCP_TestStackData

struct c2_TCP_TestStackData
{
};

#endif                                 /* c2_typedef_c2_TCP_TestStackData */

#ifndef struct_SFc2_TCP_TestInstanceStruct
#define struct_SFc2_TCP_TestInstanceStruct

struct SFc2_TCP_TestInstanceStruct
{
  SimStruct *S;
  ChartInfoStruct chartInfo;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  void *c2_RuntimeVar;
  int32_T c2_IsDebuggerActive;
  int32_T c2_IsSequenceViewerPresent;
  int32_T c2_SequenceViewerOptimization;
  int32_T c2_IsHeatMapPresent;
  uint8_T c2_JITStateAnimation[1];
  uint8_T c2_JITTransitionAnimation[1];
  uint32_T c2_mlFcnLineNumber;
  CovrtStateflowInstance *c2_covrtInstance;
  void *c2_fEmlrtCtx;
};

#endif                                 /* struct_SFc2_TCP_TestInstanceStruct */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_TCP_Test_get_eml_resolved_functions_info();

/* Function Definitions */
extern void sf_c2_TCP_Test_get_check_sum(mxArray *plhs[]);
extern void c2_TCP_Test_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
