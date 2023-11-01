#include "rt_logging_mmi.h"
#include "MassSpringDamperModel_capi.h"
#include <math.h>
#include "MassSpringDamperModel.h"
#include "MassSpringDamperModel_private.h"
#include "MassSpringDamperModel_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 1 , & stopRequested ) ; }
rtExtModeShutdown ( 1 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 2 ; const char_T
* gbl_raccel_Version = "9.6 (R2021b) 14-May-2021" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 1 ; const int_T
gblNumModelInputs = 1 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ 0 } ; const int_T gblInportDims [ ] = { 1 , 1 } ; const int_T
gblInportComplex [ ] = { 0 } ; const int_T gblInportInterpoFlag [ ] = { 1 } ;
const int_T gblInportContinuous [ ] = { 1 } ; int_T enableFcnCallFlag [ ] = {
1 , 1 } ; const char * raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S ,
const char * inportFileName , int * matFileFormat ) { return
rt_RAccelReadInportsMatFile ( S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
B rtB ; X rtX ; DW rtDW ; ExtU rtU ; ExtY rtY ; static SimStruct model_S ;
SimStruct * const rtS = & model_S ; void MdlInitialize ( void ) { boolean_T
tmp ; rtX . dtspun1pil [ 1 ] = rtP . IntegratorSecondOrder_ICDXDT ; rtDW .
dwq0q4j4af = 0 ; rtDW . mhkiwlpa2k = true ; if ( ssIsFirstInitCond ( rtS ) )
{ tmp = slIsRapidAcceleratorSimulating ( ) ; if ( tmp ) { tmp =
ssGetGlobalInitialStatesAvailable ( rtS ) ; rtDW . mhkiwlpa2k = ! tmp ; }
else { rtDW . mhkiwlpa2k = true ; } } } void MdlStart ( void ) { { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) {
rtwISigstreamManagerSetDestinationBase ( pISigstreamManager , 0 , & rtU .
iiex1hf42w ) ; } } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { if (
gblInportFileName != ( NULL ) ) { bool externalInputIsInDatasetFormat = false
; void * pISigstreamManager = rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( slIsRapidAcceleratorSimulating ( ) &&
externalInputIsInDatasetFormat ) { const int maxErrorBufferSize = 16384 ;
char errMsg [ 16384 ] ; bool bSetErrorStatus = false ; if ( 1 ) { { real_T
time = ssGetTaskTime ( rtS , 0 ) ; if ( !
rtwISigstreamManagerIsPeriodicFcnCall ( pISigstreamManager , 0 ) ) { int_T
sampleHit = 0U ; bSetErrorStatus = rtwISigstreamManagerInjectDataMultiRate (
pISigstreamManager , 0 , time , 1 , "<Root>/Force" , "[]" , & sampleHit ,
errMsg , maxErrorBufferSize ) ; } } } if ( bSetErrorStatus ) {
ssSetErrorStatus ( rtS , errMsg ) ; return ; } } else { int_T currTimeIdx ;
int_T i ; if ( gblInportTUtables [ 0 ] . nTimePoints > 0 ) { if ( 1 ) { {
real_T time = ssGetTaskTime ( rtS , 0 ) ; int k = 1 ; if ( gblInportTUtables
[ 0 ] . nTimePoints == 1 ) { k = 0 ; } currTimeIdx = rt_getTimeIdx (
gblInportTUtables [ 0 ] . time , time , gblInportTUtables [ 0 ] . nTimePoints
, * ( gblInportTUtables [ 0 ] . currTimeIdx ) , 1 , 0 ) ; ( *
gblInportTUtables [ 0 ] . currTimeIdx ) = currTimeIdx ; for ( i = 0 ; i < 1 ;
i ++ ) { real_T * realPtr1 = ( real_T * ) gblInportTUtables [ 0 ] . ur + i *
gblInportTUtables [ 0 ] . nTimePoints + currTimeIdx ; real_T * realPtr2 =
realPtr1 + 1 * k ; ( void ) rt_Interpolate_Datatype ( realPtr1 , realPtr2 , &
rtU . iiex1hf42w , time , gblInportTUtables [ 0 ] . time [ currTimeIdx ] ,
gblInportTUtables [ 0 ] . time [ currTimeIdx + k ] , gblInportTUtables [ 0 ]
. uDataType ) ; } } } } } } if ( rtDW . mhkiwlpa2k ) { rtX . dtspun1pil [ 0 ]
= rtP . x0 ; } rtB . odw0n0q2pz = rtX . dtspun1pil [ 0 ] ; rtB . kz2whdmvme =
rtX . dtspun1pil [ 1 ] ; rtY . dwjuvpkpys = rtB . odw0n0q2pz ; rtY .
pfdpqpobqg = rtB . kz2whdmvme ; rtB . eij5wjulfu = rtP . b * rtB . kz2whdmvme
; rtB . gidkns4ehh = rtP . k * rtB . odw0n0q2pz ; rtB . m2m4ulflmp = ( rtU .
iiex1hf42w - rtB . gidkns4ehh ) - rtB . eij5wjulfu ; rtB . ppb0pnoz4c = 1.0 /
rtP . m * rtB . m2m4ulflmp ; UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID1
( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid ) {
rtDW . mhkiwlpa2k = false ; UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID1 (
int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) {
XDot * _rtXdot ; _rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; if ( rtDW .
dwq0q4j4af == 0 ) { _rtXdot -> dtspun1pil [ 0 ] = rtX . dtspun1pil [ 1 ] ;
_rtXdot -> dtspun1pil [ 1 ] = rtB . ppb0pnoz4c ; } } void MdlProjection (
void ) { } void MdlTerminate ( void ) { } static void
mr_MassSpringDamperModel_cacheDataAsMxArray ( mxArray * destArray , mwIndex i
, int j , const void * srcData , size_t numBytes ) ; static void
mr_MassSpringDamperModel_cacheDataAsMxArray ( mxArray * destArray , mwIndex i
, int j , const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_MassSpringDamperModel_restoreDataFromMxArray ( void *
destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ;
static void mr_MassSpringDamperModel_restoreDataFromMxArray ( void * destData
, const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy (
( uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_MassSpringDamperModel_cacheBitFieldToMxArray ( mxArray * destArray ,
mwIndex i , int j , uint_T bitVal ) ; static void
mr_MassSpringDamperModel_cacheBitFieldToMxArray ( mxArray * destArray ,
mwIndex i , int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j
, mxCreateDoubleScalar ( ( double ) bitVal ) ) ; } static uint_T
mr_MassSpringDamperModel_extractBitFieldFromMxArray ( const mxArray *
srcArray , mwIndex i , int j , uint_T numBits ) ; static uint_T
mr_MassSpringDamperModel_extractBitFieldFromMxArray ( const mxArray *
srcArray , mwIndex i , int j , uint_T numBits ) { const uint_T varVal = (
uint_T ) mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return
varVal & ( ( 1u << numBits ) - 1u ) ; } static void
mr_MassSpringDamperModel_cacheDataToMxArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes )
; static void mr_MassSpringDamperModel_cacheDataToMxArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_MassSpringDamperModel_restoreDataFromMxArrayWithOffset ( void *
destData , const mxArray * srcArray , mwIndex i , int j , mwIndex offset ,
size_t numBytes ) ; static void
mr_MassSpringDamperModel_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData (
mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData ,
( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static
void mr_MassSpringDamperModel_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static
void mr_MassSpringDamperModel_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( double ) fieldVal ) ) ; } static uint_T
mr_MassSpringDamperModel_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ;
static uint_T mr_MassSpringDamperModel_extractBitFieldFromCellArrayWithOffset
( const mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T
numBits ) { const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_MassSpringDamperModel_GetDWork ( ) {
static const char * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "NULL_PrevZCX"
, } ; mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_MassSpringDamperModel_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * )
& ( rtB ) , sizeof ( rtB ) ) ; { static const char * rtdwDataFieldNames [ 2 ]
= { "rtDW.dwq0q4j4af" , "rtDW.mhkiwlpa2k" , } ; mxArray * rtdwData =
mxCreateStructMatrix ( 1 , 1 , 2 , rtdwDataFieldNames ) ;
mr_MassSpringDamperModel_cacheDataAsMxArray ( rtdwData , 0 , 0 , ( const void
* ) & ( rtDW . dwq0q4j4af ) , sizeof ( rtDW . dwq0q4j4af ) ) ;
mr_MassSpringDamperModel_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void
* ) & ( rtDW . mhkiwlpa2k ) , sizeof ( rtDW . mhkiwlpa2k ) ) ;
mxSetFieldByNumber ( ssDW , 0 , 1 , rtdwData ) ; } return ssDW ; } void
mr_MassSpringDamperModel_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW ;
mr_MassSpringDamperModel_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW
, 0 , 0 , sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber
( ssDW , 0 , 1 ) ; mr_MassSpringDamperModel_restoreDataFromMxArray ( ( void *
) & ( rtDW . dwq0q4j4af ) , rtdwData , 0 , 0 , sizeof ( rtDW . dwq0q4j4af ) )
; mr_MassSpringDamperModel_restoreDataFromMxArray ( ( void * ) & ( rtDW .
mhkiwlpa2k ) , rtdwData , 0 , 1 , sizeof ( rtDW . mhkiwlpa2k ) ) ; } }
mxArray * mr_MassSpringDamperModel_GetSimStateDisallowedBlocks ( ) { return (
NULL ) ; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 2 )
; ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 2 ) ; ssSetNumU
( rtS , 1 ) ; ssSetDirectFeedThrough ( rtS , 1 ) ; ssSetNumSampleTimes ( rtS
, 1 ) ; ssSetNumBlocks ( rtS , 8 ) ; ssSetNumBlockIO ( rtS , 6 ) ;
ssSetNumBlockParams ( rtS , 5 ) ; } void MdlInitializeSampleTimes ( void ) {
ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 3255789942U ) ;
ssSetChecksumVal ( rtS , 1 , 3568203557U ) ; ssSetChecksumVal ( rtS , 2 ,
2272714081U ) ; ssSetChecksumVal ( rtS , 3 , 1676864927U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; ( void ) memset ( ( char * ) rtS , 0 ,
sizeof ( SimStruct ) ) ; ( void ) memset ( ( char * ) & mdlInfo , 0 , sizeof
( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr ( rtS , & mdlInfo ) ;
ssSetExecutionInfo ( rtS , executionInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; { rtB . odw0n0q2pz = 0.0 ; rtB . kz2whdmvme = 0.0 ;
rtB . eij5wjulfu = 0.0 ; rtB . gidkns4ehh = 0.0 ; rtB . m2m4ulflmp = 0.0 ;
rtB . ppb0pnoz4c = 0.0 ; } } { ssSetU ( rtS , ( ( void * ) & rtU ) ) ; rtU .
iiex1hf42w = 0.0 ; } { ssSetY ( rtS , & rtY ) ; rtY . dwjuvpkpys = 0.0 ; rtY
. pfdpqpobqg = 0.0 ; ssSetWorkSizeInBytes ( rtS , sizeof ( rtY ) , "YOut" ) ;
} { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ; ( void )
memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = ( void * ) &
rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork , 0 , sizeof
( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T *
) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo
) ; dtInfo . numDataTypes = 20 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [
0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . BTransTable
= & rtBTransTable ; dtInfo . PTransTable = & rtPTransTable ; dtInfo .
dataTypeInfoTable = rtDataTypeInfoTable ; }
MassSpringDamperModel_InitializeDataMapInfo ( ) ;
ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ;
ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"MassSpringDamperModel" ) ; ssSetPath ( rtS , "MassSpringDamperModel" ) ;
ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 20.0 ) ; { static RTWLogInfo
rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = ( NULL ) ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 1 , 1 , } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , } ; static int_T
rt_LoggedStateDimensions [ ] = { 1 , 1 , } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , } ; static int_T
rt_LoggedStateComplexSignals [ ] = { 0 , 0 , } ; static
RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) ,
( NULL ) , } ; static const char_T * rt_LoggedStateLabels [ ] = { "CSTATE" ,
"CSTATE" , } ; static const char_T * rt_LoggedStateBlockNames [ ] = {
"MassSpringDamperModel/Integrator,\nSecond-Order" ,
"MassSpringDamperModel/Integrator,\nSecond-Order" , } ; static const char_T *
rt_LoggedStateNames [ ] = { "pos" , "vel" , } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , } ; static RTWLogDataTypeConvert
rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } ,
} ; static int_T rt_LoggedStateIdxList [ ] = { 0 , } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 2 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 2 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . dtspun1pil [ 0 ] ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . dtspun1pil [ 1 ] ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "t" ) ; rtliSetLogX ( ssGetRTWLogInfo
( rtS ) , "tmp_raccel_xout" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"xFinal" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 2 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; { static void * rt_LoggedOutputSignalPtrs [ ] = { & rtY .
dwjuvpkpys , & rtY . pfdpqpobqg } ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( ( LogSignalPtrsType ) rt_LoggedOutputSignalPtrs ) ) ; } { static
int_T rt_LoggedOutputWidths [ ] = { 1 , 1 } ; static int_T
rt_LoggedOutputNumDimensions [ ] = { 1 , 1 } ; static int_T
rt_LoggedOutputDimensions [ ] = { 1 , 1 } ; static boolean_T
rt_LoggedOutputIsVarDims [ ] = { 0 , 0 } ; static void *
rt_LoggedCurrentSignalDimensions [ ] = { ( NULL ) , ( NULL ) } ; static int_T
rt_LoggedCurrentSignalDimensionsSize [ ] = { 4 , 4 } ; static BuiltInDTypeId
rt_LoggedOutputDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE } ; static int_T
rt_LoggedOutputComplexSignals [ ] = { 0 , 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingPreprocessingFcnPtrs [ ] = { ( NULL ) , ( NULL ) } ; static const
char_T * rt_LoggedOutputLabels_0 [ ] = { "" } ; static const char_T *
rt_LoggedOutputBlockNames_0 [ ] = { "MassSpringDamperModel/Position" } ;
static const char_T * rt_LoggedOutputLabels_1 [ ] = { "" } ; static const
char_T * rt_LoggedOutputBlockNames_1 [ ] = { "MassSpringDamperModel/Velocity"
} ; static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static RTWLogSignalInfo
rt_LoggedOutputSignalInfo [ ] = { { 1 , rt_LoggedOutputWidths ,
rt_LoggedOutputNumDimensions , rt_LoggedOutputDimensions ,
rt_LoggedOutputIsVarDims , rt_LoggedCurrentSignalDimensions ,
rt_LoggedCurrentSignalDimensionsSize , rt_LoggedOutputDataTypeIds ,
rt_LoggedOutputComplexSignals , ( NULL ) , rt_LoggingPreprocessingFcnPtrs , {
rt_LoggedOutputLabels_0 } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedOutputBlockNames_0 } , { ( NULL ) } , ( NULL ) ,
rt_RTWLogDataTypeConvert , ( NULL ) } , { 1 , rt_LoggedOutputWidths + 1 ,
rt_LoggedOutputNumDimensions + 1 , rt_LoggedOutputDimensions + 1 ,
rt_LoggedOutputIsVarDims + 1 , rt_LoggedCurrentSignalDimensions + 1 ,
rt_LoggedCurrentSignalDimensionsSize + 1 , rt_LoggedOutputDataTypeIds + 1 ,
rt_LoggedOutputComplexSignals + 1 , ( NULL ) , rt_LoggingPreprocessingFcnPtrs
+ 1 , { rt_LoggedOutputLabels_1 } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedOutputBlockNames_1 } , { ( NULL ) } , ( NULL ) ,
rt_RTWLogDataTypeConvert + 1 , ( NULL ) } } ; rtliSetLogYSignalInfo (
ssGetRTWLogInfo ( rtS ) , rt_LoggedOutputSignalInfo ) ;
rt_LoggedCurrentSignalDimensions [ 0 ] = & rt_LoggedOutputWidths [ 0 ] ;
rt_LoggedCurrentSignalDimensions [ 1 ] = & rt_LoggedOutputWidths [ 1 ] ; }
rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "tmp_raccel_yout1,tmp_raccel_yout2" )
; } { static struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , &
statesInfo2 ) ; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 2 ] ;
static real_T absTol [ 2 ] = { 1.0E-6 , 1.0E-6 } ; static uint8_T
absTolControl [ 2 ] = { 2U , 2U } ; static real_T
contStateJacPerturbBoundMinVec [ 2 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 2 ] ; { int i ; for ( i = 0 ; i < 2 ; ++ i )
{ contStateJacPerturbBoundMinVec [ i ] = 0 ; contStateJacPerturbBoundMaxVec [
i ] = rtGetInf ( ) ; } } ssSetSolverRelTol ( rtS , 0.001 ) ; ssSetStepSize (
rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , -
1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ; ssSetMaxStepSize ( rtS , 0.4 )
; ssSetSolverMaxOrder ( rtS , - 1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ;
ssSetOutputTimes ( rtS , ( NULL ) ) ; ssSetNumOutputTimes ( rtS , 0 ) ;
ssSetOutputTimesOnly ( rtS , 0 ) ; ssSetOutputTimesIndex ( rtS , 0 ) ;
ssSetZCCacheNeedsReset ( rtS , 0 ) ; ssSetDerivCacheNeedsReset ( rtS , 0 ) ;
ssSetNumNonContDerivSigInfos ( rtS , 0 ) ; ssSetNonContDerivSigInfos ( rtS ,
( NULL ) ) ; ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS ,
"VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS , 1 ) ;
ssSetSolverConsistencyChecking ( rtS , 0 ) ; ssSetSolverAdaptiveZcDetection (
rtS , 0 ) ; ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector (
rtS , absTol ) ; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 3255789942U ) ; ssSetChecksumVal ( rtS , 1 ,
3568203557U ) ; ssSetChecksumVal ( rtS , 2 , 2272714081U ) ; ssSetChecksumVal
( rtS , 3 , 1676864927U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 1 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; }
slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_MassSpringDamperModel_GetSimStateDisallowedBlocks ) ;
slsaGetWorkFcnForSimTargetOP ( rtS , mr_MassSpringDamperModel_GetDWork ) ;
slsaSetWorkFcnForSimTargetOP ( rtS , mr_MassSpringDamperModel_SetDWork ) ;
rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if ( ssGetErrorStatus ( rtS ) )
{ return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 1 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID1 ( tid ) ; }
