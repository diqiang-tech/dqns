#include "app_state.h"


void AppStateInit(void)
{    
    AppStateXInit();
    AppStateIdleInit();
    AppStateDebugInit();
    AppStateAbnormalInit();
    AppStateRunInit();   
    
}