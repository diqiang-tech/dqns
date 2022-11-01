#include "udm_dig.h"

TS_UDM_DEVICE gg_udm_dig;
static T_UDM_DIG_IOCTL udm_dig_ioctl_data;

static void UdmDigInit(void){
    gg_udm_dig.e_device_id = E_UDM_DEVICE_DIG;
    gg_udm_dig.e_already_open = E_FALSE;
    gg_udm_dig.p_ioctl_data = &udm_dig_ioctl_data;
    gg_udm_dig.p_fn_init = UdmDigInit;
    gg_udm_dig.p_fn_open = UdmDigOpen;
    gg_udm_dig.p_fn_close = UdmDigClose;
    gg_udm_dig.p_fn_read = UdmDigRead;
    gg_udm_dig.p_fn_write = UdmDigWrite;
    gg_udm_dig.p_fn_ioctl = UdmDigIOCtl;
}

static TE_UDM_RET_CODE UdmDigOpen(T_UDM_OPEN_MODE open_mode){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmDigClose(void){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmDigRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmDigWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmDigIOCtl(void * p_data){
    return E_UDM_OK;
}

