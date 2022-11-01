
#include "init.h"



static void DriverInit(void);
static void KernelInit(void);
static void UiInit(void);
static void AppInit(void);


void Init(void){
    
    DriverInit();
    UdmInit(E_UDM_DEVICE_KEY);
    UdmInit(E_UDM_DEVICE_LED);
    UdmInit(E_UDM_DEVICE_DIG);
    UdmInit(E_UDM_DEVICE_PUMP);
    KernelInit();
    UiInit();
    AppInit();

    KerFSMGo(E_KER_STATE_ID_X,0);
    KerFctRun();
    
}


static void DriverInit(void){     
    
}

static void KernelInit(void){
    /* ------------- platform ------------- */
    KerTimerInit();
    KerMsgInit();
    KerKeyInit();
    KerFSMInit();
    KerPinInit();
    KerCommInit();

    /* ------------- product ------------- */
    KerDigInit();
    KerFctInit();
    KerPumpInit();
    
    
}

static void UiInit(void){
   
}

static void AppInit(void){
    AppStateInit();
}

