#include "ker_pump.h"
#include "../../udm/stable/udm_api.h"

static TE_KER_PUMP_LEVEL g_cur_pump_level;
static TE_KER_PUMP_MODE g_cur_pump_mode;
static TE_BOOL g_is_pump_run;

void KerPumpInit(void){
    g_cur_pump_level = E_KER_PUMP_LEVEL_3;
    g_cur_pump_mode = E_KER_PUMP_MODE_NORMAL;
    g_is_pump_run = E_FALSE;
    UdmInit(E_UDM_DEVICE_PUMP);
}

void KerPumpRun(void){
    UdmWrite(E_UDM_DEVICE_PUMP, 0, 0, (void *)(E_TRUE));
    g_is_pump_run = E_TRUE;
}

void KerPumpStop(void){
    UdmWrite(E_UDM_DEVICE_PUMP, 0, 0, (void *)(E_FALSE));
    g_is_pump_run = E_FALSE;
    
}

TE_BOOL KerPumpIsRun(void){
    return g_is_pump_run;
}

void KerPumpSetLevel(TE_KER_PUMP_LEVEL e_pump_level){
    M_Assert(e_pump_level < E_KER_PUMP_LEVEL_COUNT);
    g_cur_pump_level = e_pump_level;
    if (E_KER_PUMP_LEVEL_1 == g_cur_pump_level){
        g_cur_pump_level = E_KER_PUMP_LEVEL_2;
    }
    else if (E_KER_PUMP_LEVEL_2 == g_cur_pump_level){
        g_cur_pump_level = E_KER_PUMP_LEVEL_3;
    }
    else if (E_KER_PUMP_LEVEL_3 == g_cur_pump_level){
        g_cur_pump_level = E_KER_PUMP_LEVEL_1;
    }
}
void KerPumpSwitchLevel(void){
    
}
TE_KER_PUMP_LEVEL KerPumpLevel(void){
    return g_cur_pump_level;
}
void KerPumpSetMode(TE_KER_PUMP_MODE e_pump_mode){
    M_Assert(e_pump_mode < E_KER_PUMP_MODE_COUNT);
    g_cur_pump_mode = e_pump_mode;
}
void KerPumpSwitchMode(void){
    g_cur_pump_mode = (g_cur_pump_mode == E_KER_PUMP_MODE_NORMAL)?E_KER_PUMP_MODE_SMART:E_KER_PUMP_MODE_NORMAL;
}
TE_KER_PUMP_MODE KerPumpMode(void){
    return g_cur_pump_mode;
}







