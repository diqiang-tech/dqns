#include "udm_led.h"

TS_UDM_DEVICE gg_udm_led;
static T_UDM_LED_IOCTL udm_led_ioctl_data;

static void UdmledInit(void){
    gg_udm_led.e_device_id = E_UDM_DEVICE_LED;
    gg_udm_led.e_already_open = E_FALSE;
    gg_udm_led.p_ioctl_data = &udm_led_ioctl_data;
    gg_udm_led.p_fn_init = UdmledInit;
    gg_udm_led.p_fn_open = UdmledOpen;
    gg_udm_led.p_fn_close = UdmledClose;
    gg_udm_led.p_fn_read = UdmledRead;
    gg_udm_led.p_fn_write = UdmledWrite;
    gg_udm_led.p_fn_ioctl = UdmledIOCtl;
}

static TE_UDM_RET_CODE UdmledOpen(T_UDM_OPEN_MODE open_mode){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmledClose(void){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmledRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmledWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmledIOCtl(void * p_data){
    return E_UDM_OK;
}

