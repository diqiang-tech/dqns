
#include "drv_ear.h"
#include "drv_pca.h"
#include "drv_cam.h"

#include "ker_io.h"
#include "ker_msg.h"


#include "ker_io_user.h"


static TS_KER_IO_PIN g_io_pin_left_ear;
static TS_KER_IO_PIN g_io_pin_right_ear;
static TS_KER_IO_PIN g_io_pin_pca;

static TS_KER_IO_PORT g_io_port_cam;

TS_KER_IO_PIN* gg_io_pin_tbl[]={    
    &g_io_pin_left_ear,
    &g_io_pin_right_ear,
    &g_io_pin_pca
};

TFP_U8_VOID gg_io_pin_read_func_tbl[]={      
    DrvEarLeft,
    DrvEarRight,
    DrvPcaConnectStatus
};

T_U8 gg_io_pin_filter_count_tbl[]={    
    IO_PIN_LeftEarStatus_FILTER_COUNT,     
    IO_PIN_RightEarStatus_FILTER_COUNT,  
    IO_PIN_PcaConnectStatus_FILTER_COUNT   
};

TS_KER_IO_PORT* gg_io_port_tbl[]={
    &g_io_port_cam
};

TFP_U8_VOID gg_io_port_read_func_tbl[]={
    DrvCamPort
};

T_U8 gg_io_port_filter_count_tbl[]={
    IO_PORT_CAM_FILTER_COUNT
};


void KerIOUserInit(void){
    T_U8 pin_status;
    T_U8 port_value;

    //initialize left ear status pin
    pin_status = DrvEarLeft();
    M_KerIOPinInit((&g_io_pin_left_ear),0,0,IO_PIN_LeftEarStatus_FILTER_COUNT,pin_status,pin_status);    

    //initialize right ear status pin
    pin_status = DrvEarRight();
    M_KerIOPinInit((&g_io_pin_right_ear),0,0,IO_PIN_RightEarStatus_FILTER_COUNT,pin_status,pin_status); 

    //initialize pca conn status pin
    pin_status = DrvPcaConnectStatus();
    M_KerIOPinInit((&g_io_pin_pca),0,0,IO_PIN_PcaConnectStatus_FILTER_COUNT,pin_status,pin_status); 

    //initialize cam port
    DrvCamPwrCtl(E_ON);
    UtilityDelayMs(5);
    port_value = DrvCamPort();

    DrvCamPwrCtl(E_OFF);
    M_KerIOPortInit((&g_io_port_cam),0,0,IO_PORT_CAM_FILTER_COUNT,port_value,port_value); 
    
}
