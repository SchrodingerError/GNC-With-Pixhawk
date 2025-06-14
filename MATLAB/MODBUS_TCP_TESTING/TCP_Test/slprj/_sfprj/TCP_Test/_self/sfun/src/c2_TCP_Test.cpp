/* Include files */

#include "TCP_Test_sfun.h"
#include "c2_TCP_Test.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
const int32_T CALL_EVENT{ -1 };

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance);
static void initialize_params_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance);
static void mdl_start_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance);
static void mdl_terminate_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance);
static void mdl_setup_runtime_resources_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *
  chartInstance);
static void mdl_cleanup_runtime_resources_c2_TCP_Test
  (SFc2_TCP_TestInstanceStruct *chartInstance);
static void enable_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance);
static void disable_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance);
static void sf_gateway_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance);
static void ext_mode_exec_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance);
static void c2_update_jit_animation_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance);
static void c2_do_animation_call_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance);
static void set_sim_state_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance,
  const mxArray *c2_st);
static const mxArray *c2_chart_data_browse_helper(SFc2_TCP_TestInstanceStruct
  *chartInstance);
static void init_dsm_address_info(SFc2_TCP_TestInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_TCP_TestInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
  chartInstance->c2_doneDoubleBufferReInit = false;
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void initialize_params_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance)
{
}

static void mdl_start_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void mdl_terminate_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance)
{
}

static void mdl_setup_runtime_resources_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *
  chartInstance)
{
  static const uint32_T c2_decisionTxtEndIdx{ 0U };

  static const uint32_T c2_decisionTxtStartIdx{ 0U };

  setDataBrowseFcn(chartInstance->S, (void *)&c2_chart_data_browse_helper);
  chartInstance->c2_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c2_RuntimeVar,
    &chartInstance->c2_IsDebuggerActive,
    &chartInstance->c2_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c2_mlFcnLineNumber, &chartInstance->c2_IsHeatMapPresent, 0);
  sfSetAnimationVectors(chartInstance->S, &chartInstance->c2_JITStateAnimation[0],
                        &chartInstance->c2_JITTransitionAnimation[0]);
  covrtCreateStateflowInstanceData(chartInstance->c2_covrtInstance, 1U, 0U, 1U,
    0U);
  covrtChartInitFcn(chartInstance->c2_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c2_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c2_decisionTxtStartIdx, &c2_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c2_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c2_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 4U, 0U, 0U, "c2_TCP_Test",
                     0, -1, 118);
}

static void mdl_cleanup_runtime_resources_c2_TCP_Test
  (SFc2_TCP_TestInstanceStruct *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c2_RuntimeVar);
  covrtDeleteStateflowInstanceData(chartInstance->c2_covrtInstance);
}

static void enable_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void sf_gateway_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_JITTransitionAnimation[0] = 0U;
  chartInstance->c2_sfEvent = CALL_EVENT;
  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 4U, 0, 0);
  tcp_send();
}

static void ext_mode_exec_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance)
{
}

static void c2_update_jit_animation_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance)
{
}

static void c2_do_animation_call_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_TCP_Test(SFc2_TCP_TestInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st{ nullptr };

  const mxArray *c2_y{ nullptr };

  c2_st = nullptr;
  c2_y = nullptr;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_TCP_Test(SFc2_TCP_TestInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

const mxArray *sf_c2_TCP_Test_get_eml_resolved_functions_info()
{
  const mxArray *c2_nameCaptureInfo{ nullptr };

  c2_nameCaptureInfo = nullptr;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", nullptr, 0,
    0U, 1, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_chart_data_browse_helper(SFc2_TCP_TestInstanceStruct
  *chartInstance)
{
  return nullptr;
}

static void init_dsm_address_info(SFc2_TCP_TestInstanceStruct *chartInstance)
{
}

static void init_simulink_io_address(SFc2_TCP_TestInstanceStruct *chartInstance)
{
  chartInstance->c2_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c2_TCP_Test_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2135056398U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3794922571U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1847542433U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2957949060U);
}

mxArray *sf_c2_TCP_Test_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_TCP_Test_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("tcp_send");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_TCP_Test_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_TCP_Test(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiCOAGI2IOYAYiYGCGCF8hmhfEa4OAtcXAGISyoLUkHixUXJnilAOi8xF8xPLK3"
    "wzEvLZwAA+RkJgQ=="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_TCP_Test_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "sMgtle7e3ISrISZc2xq2FZF";
}

static void sf_opaque_initialize_c2_TCP_Test(void *chartInstanceVar)
{
  initialize_params_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*) chartInstanceVar);
  initialize_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_TCP_Test(void *chartInstanceVar)
{
  enable_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_TCP_Test(void *chartInstanceVar)
{
  disable_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_TCP_Test(void *chartInstanceVar)
{
  sf_gateway_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_TCP_Test(SimStruct* S)
{
  return get_sim_state_c2_TCP_Test((SFc2_TCP_TestInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_TCP_Test(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c2_TCP_Test(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_TCP_TestInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_TCP_Test_optimization_info();
    }

    mdl_cleanup_runtime_resources_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*)
      chartInstanceVar);
    ((SFc2_TCP_TestInstanceStruct*) chartInstanceVar)->
      ~SFc2_TCP_TestInstanceStruct();
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c2_TCP_Test(void *chartInstanceVar)
{
  mdl_start_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*) chartInstanceVar);
  if (chartInstanceVar) {
    sf_reset_warnings_ChartRunTimeInfo(((SFc2_TCP_TestInstanceStruct*)
      chartInstanceVar)->S);
  }
}

static void sf_opaque_mdl_terminate_c2_TCP_Test(void *chartInstanceVar)
{
  mdl_terminate_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_TCP_Test(SimStruct *S)
{
  mdlProcessParamsCommon(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_TCP_Test((SFc2_TCP_TestInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c2_TCP_Test_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [19] = {
    "eNrlWMtu20YUHRlOkCZpkG7aLII2y2wCBPaiWRRFHUpMCFi1ENJpYaAIRuQVOfBwSM9DlrII+hH",
    "9qn5B1t32A9pl7lCULMiqzKEKOGkJ0PSQPHPunLkvinSCPsHjHp6/fknITbzewnOHzI4b9bizdM",
    "7u75Lv6vHgNiFxRqUOxKgg7kdcJJCCCM1oxCaOWGHyAZU0Vy14Bc3hFaiCG80K4WY8EyOQIGKco",
    "CykduJVLDeciVPfiNgyq58yFmdhVhiePMcJaXIk+PSfeEujB8jYZRJi7QMkOpOFSTOf03SzClKf",
    "exnEp8rkzlop0KEp7VJV33DNSg69CcSBUJqiCuqK9YaaavD0xNlDmArn6CIvOaOiudYZVSGU6B0",
    "ajssE/x4Zjeo15EW+IRNUF5JR3su5Zz28IXbA0c4+ujV31lnnugtDk6ZMpFZdaXIQuH70kwZajb",
    "xiDJKmcCQcY9CurjepNnjhl81jMLBu2SoGTT7bFdUKW/H2xqiQasnrx8KjnCs3bFSUhzAGXvF3q",
    "aYtsDN+B7BSLImK11TaKHCMJCPYmYEa6xUiYc13eLyCqhLuj5g8G8BZbl0KEpR5Yfpioqt80ihd",
    "5B6GUffwsCHfZWwgNMgRjaFx7pOUKUCDK79y5E2YokNu0aiSrlbZeAYQraFEjYzonhfyFDV2TbI",
    "XWtlIcENDkkIXNFQJo4fe/Zpy09DmXGGGs+5xrDBjufEi1sZPK3BM4wwSW08Yhz4oO4FqnJ+xjh",
    "zgasdMT7ugYsnKppFkFCRYSKxK0bSEY3EqinPhyyIP645gg18BYNagUmBZeI5lSU59NL6Z1RLOI",
    "utZbdqznGpOh9Y3XoDAymLXaishjTGqegJbNzRoG2zI3mJpF4opje3UtFfFQFL1ow86bv3oF/V4",
    "fxFLgYok7hTFMiywUzoYVs0eRCyH6kZIsaeYDevD8j4lF7yf7Wzm3cH/Oi1xZEvcD0u43TX63Fn",
    "C3a/H8d6byBu8iUDptfx3G+jcBEcu4S70nV8fL+E7a3jJ0nWbfVnW6fMVnt0V3M1aq8e/3Pnt6/",
    "P3L179dfDHn7+/y7bhv+Xox/fq8cN5X7aoXONLyd2++/IKP/hqxQ/sWPVTzeFb2A9CGYQn8d7kb",
    "M8/8av5fiab7SUr9s7vP8JTY2Kr8qSMg6T+xrJjama9/6cQX9cVz9dp578V9/9nnGs++9Tff7oh",
    "75CV9+9/xOtYvbatax/but4Tt7rzTT3+fvGt6WWMJ2u63foxNqSjdU//I/79t6N+8zrbs/rVP5a",
    "d7B8IyqfY3s4+H+rbA2l/p1k8kkDV+m+I66hD8+uzK/qKGyvxbcfHkf/k2Rb17ANhxvTT",
    ""
  };

  static char newstr [1345] = "";
  newstr[0] = '\0';
  for (i = 0; i < 19; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c2_TCP_Test(SimStruct *S)
{
  const char* newstr = sf_c2_TCP_Test_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(2483772712U));
  ssSetChecksum1(S,(1205368606U));
  ssSetChecksum2(S,(3795973970U));
  ssSetChecksum3(S,(1753139947U));
}

static void mdlRTW_c2_TCP_Test(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c2_TCP_Test(SimStruct *S)
{
  SFc2_TCP_TestInstanceStruct *chartInstance;
  chartInstance = (SFc2_TCP_TestInstanceStruct *)utMalloc(sizeof
    (SFc2_TCP_TestInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_TCP_TestInstanceStruct));
  chartInstance = new (chartInstance) SFc2_TCP_TestInstanceStruct;
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_TCP_Test;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_TCP_Test;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c2_TCP_Test;
  chartInstance->chartInfo.mdlTerminate = sf_opaque_mdl_terminate_c2_TCP_Test;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c2_TCP_Test;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_TCP_Test;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_TCP_Test;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_TCP_Test;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_TCP_Test;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_TCP_Test;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_TCP_Test;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_TCP_Test;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c2_TCP_Test(chartInstance);
}

void c2_TCP_Test_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c2_TCP_Test(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_TCP_Test(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_TCP_Test(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_TCP_Test_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
