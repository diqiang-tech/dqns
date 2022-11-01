#include "udm_pump.h"

TS_UDM_DEVICE gg_udm_pump;
static T_UDM_PUMP_IOCTL udm_pump_ioctl_data;

static void UdmPumpInit(void){
    gg_udm_pump.e_device_id = E_UDM_DEVICE_PUMP;
    gg_udm_pump.e_already_open = E_FALSE;
    gg_udm_pump.p_ioctl_data = &udm_pump_ioctl_data;
    gg_udm_pump.p_fn_init = UdmPumpInit;
    gg_udm_pump.p_fn_open = UdmPumpOpen;
    gg_udm_pump.p_fn_close = UdmPumpClose;
    gg_udm_pump.p_fn_read = UdmPumpRead;
    gg_udm_pump.p_fn_write = UdmPumpWrite;
    gg_udm_pump.p_fn_ioctl = UdmPumpIOCtl;
}

static TE_UDM_RET_CODE UdmPumpOpen(T_UDM_OPEN_MODE open_mode){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmPumpClose(void){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmPumpRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmPumpWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmPumpIOCtl(void * p_data){
    return E_UDM_OK;
}

