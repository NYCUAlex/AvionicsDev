#ifndef RTW_HEADER_MassSpringDamperModel_h_
#define RTW_HEADER_MassSpringDamperModel_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap_simtarget.h"
#ifndef MassSpringDamperModel_COMMON_INCLUDES_
#define MassSpringDamperModel_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "MassSpringDamperModel_types.h"
#include "multiword_types.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME MassSpringDamperModel
#define NSAMPLE_TIMES (2) 
#define NINPUTS (1)       
#define NOUTPUTS (2)     
#define NBLOCKIO (6) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (2)   
#elif NCSTATES != 2
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T odw0n0q2pz ; real_T kz2whdmvme ; real_T eij5wjulfu ;
real_T gidkns4ehh ; real_T m2m4ulflmp ; real_T ppb0pnoz4c ; } B ; typedef
struct { int_T dwq0q4j4af ; boolean_T mhkiwlpa2k ; } DW ; typedef struct {
real_T dtspun1pil [ 2 ] ; } X ; typedef struct { real_T dtspun1pil [ 2 ] ; }
XDot ; typedef struct { boolean_T dtspun1pil [ 2 ] ; } XDis ; typedef struct
{ real_T dtspun1pil [ 2 ] ; } CStateAbsTol ; typedef struct { real_T
dtspun1pil [ 2 ] ; } CXPtMin ; typedef struct { real_T dtspun1pil [ 2 ] ; }
CXPtMax ; typedef struct { real_T iiex1hf42w ; } ExtU ; typedef struct {
real_T dwjuvpkpys ; real_T pfdpqpobqg ; } ExtY ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T b ; real_T
k ; real_T m ; real_T x0 ; real_T IntegratorSecondOrder_ICDXDT ; } ; extern
const char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ;
extern DW rtDW ; extern ExtU rtU ; extern ExtY rtY ; extern P rtP ; extern
mxArray * mr_MassSpringDamperModel_GetDWork ( ) ; extern void
mr_MassSpringDamperModel_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_MassSpringDamperModel_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * MassSpringDamperModel_GetCAPIStaticMap (
void ) ; extern SimStruct * const rtS ; extern const int_T gblNumToFiles ;
extern const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ;
extern rtInportTUtable * gblInportTUtables ; extern const char *
gblInportFileName ; extern const int_T gblNumRootInportBlks ; extern const
int_T gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ;
extern const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [
] ; extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif
