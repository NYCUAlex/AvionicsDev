#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "MassSpringDamperModel_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#else
#include "builtin_typeid_types.h"
#include "MassSpringDamperModel.h"
#include "MassSpringDamperModel_capi.h"
#include "MassSpringDamperModel_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"MassSpringDamperModel/Damping" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0
} , { 1 , 0 , TARGET_STRING ( "MassSpringDamperModel/Mass" ) , TARGET_STRING
( "acc" ) , 0 , 0 , 0 , 0 , 0 } , { 2 , 0 , TARGET_STRING (
"MassSpringDamperModel/Stiffness" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 3 , 0 , TARGET_STRING ( "MassSpringDamperModel/Sum1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 4 , 0 , TARGET_STRING (
"MassSpringDamperModel/Integrator, Second-Order" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 5 , 0 , TARGET_STRING (
"MassSpringDamperModel/Integrator, Second-Order" ) , TARGET_STRING ( "" ) , 1
, 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 6 ,
TARGET_STRING ( "MassSpringDamperModel/Integrator, Second-Order" ) ,
TARGET_STRING ( "ICDXDT" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0
, 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 7 , 0 , TARGET_STRING (
"MassSpringDamperModel/Force" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 }
, { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_Signals rtRootOutputs [ ] = { { 8 , 0 , TARGET_STRING (
"MassSpringDamperModel/Position" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0
} , { 9 , 0 , TARGET_STRING ( "MassSpringDamperModel/Velocity" ) ,
TARGET_STRING ( "" ) , 2 , 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL ) ,
0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters
rtModelParameters [ ] = { { 10 , TARGET_STRING ( "b" ) , 0 , 0 , 0 } , { 11 ,
TARGET_STRING ( "k" ) , 0 , 0 , 0 } , { 12 , TARGET_STRING ( "m" ) , 0 , 0 ,
0 } , { 13 , TARGET_STRING ( "x0" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 ,
0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . eij5wjulfu , & rtB . ppb0pnoz4c ,
& rtB . gidkns4ehh , & rtB . m2m4ulflmp , & rtB . odw0n0q2pz , & rtB .
kz2whdmvme , & rtP . IntegratorSecondOrder_ICDXDT , & rtU . iiex1hf42w , &
rtY . dwjuvpkpys , & rtY . pfdpqpobqg , & rtP . b , & rtP . k , & rtP . m , &
rtP . x0 , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } }
;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] = {
1 , 1 } ; static const real_T rtcapiStoredFloats [ ] = { 0.0 } ; static const
rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , (
int8_T ) 0 , ( uint8_T ) 0 } } ; static rtwCAPI_ModelMappingStaticInfo
mmiStatic = { { rtBlockSignals , 6 , rtRootInputs , 1 , rtRootOutputs , 2 } ,
{ rtBlockParameters , 1 , rtModelParameters , 4 } , { ( NULL ) , 0 } , {
rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap
, rtDimensionArray } , "float" , { 3255789942U , 3568203557U , 2272714081U ,
1676864927U } , ( NULL ) , 0 , ( boolean_T ) 0 , rt_LoggedStateIdxList } ;
const rtwCAPI_ModelMappingStaticInfo * MassSpringDamperModel_GetCAPIStaticMap
( void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void MassSpringDamperModel_InitializeDataMapInfo ( void ) {
rtwCAPI_SetVersion ( ( * rt_dataMapInfoPtr ) . mmi , 1 ) ;
rtwCAPI_SetStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ;
rtwCAPI_SetLoggingStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetDataAddressMap ( ( * rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ;
rtwCAPI_SetVarDimsAddressMap ( ( * rt_dataMapInfoPtr ) . mmi ,
rtVarDimsAddrMap ) ; rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr )
. mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi
, ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi ,
0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void MassSpringDamperModel_host_InitializeDataMapInfo (
MassSpringDamperModel_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap ->
mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
