
#include "../../../driver/drv_debug.h"
#include "../../../driver/drv_lock.h"
#include "../stable/ker_pin.h"


#include "ker_pin_user.h"


static TS_KER_PIN g_pin_debug;
static TS_KER_PIN g_pin_lock;

TS_KER_PIN* gg_pin_tbl[]={    
    &g_pin_debug,
    &g_pin_lock,
};

TFP_U8_VOID gg_pin_read_func_tbl[]={
    DrvDebugStatus,
    DrvLockStatus,
};

T_U8 gg_pin_filter_count_tbl[]={
    PIN_DebugStatus_FILTER_COUNT,
    PIN_LockStatus_FILTER_COUNT,
};

void KerPinUserInit(void){
    T_U8 pin_status;

    //initialize debug status pin
    pin_status = DrvDebugStatus();
    M_KerPinInit((&g_pin_debug),0,0,PIN_DebugStatus_FILTER_COUNT,pin_status,pin_status);

    //initialize lock status pin
    pin_status = DrvLockStatus();
    M_KerPinInit((&g_pin_lock),0,0,PIN_LockStatus_FILTER_COUNT,pin_status,pin_status);

   
}
