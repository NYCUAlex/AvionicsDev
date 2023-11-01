#include "MassSpringDamperModel_capi_host.h"
static MassSpringDamperModel_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        MassSpringDamperModel_host_InitializeDataMapInfo(&(root), "MassSpringDamperModel");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction() {return(getRootMappingInfo());}
