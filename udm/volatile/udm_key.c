#include "udm_key.h"

TS_UDM_DEVICE gg_udm_key  ;
static T_UDM_KEY_IOCTL udm_key_ioctl_data;

static void UdmKeyInit(void){
    gg_udm_key.e_device_id = E_UDM_DEVICE_KEY;
    gg_udm_key.e_already_open = E_FALSE;
    gg_udm_key.p_ioctl_data = &udm_key_ioctl_data;
    gg_udm_key.p_fn_init = UdmKeyInit;
    gg_udm_key.p_fn_open = UdmKeyOpen;
    gg_udm_key.p_fn_close = UdmKeyClose;
    gg_udm_key.p_fn_read = UdmKeyRead;
    gg_udm_key.p_fn_write = UdmKeyWrite;
    gg_udm_key.p_fn_ioctl = UdmKeyIOCtl;
}

static TE_UDM_RET_CODE UdmKeyOpen(T_UDM_OPEN_MODE open_mode){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmKeyClose(void){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmKeyRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmKeyWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    return E_UDM_OK;
}

static TE_UDM_RET_CODE UdmKeyIOCtl(void * p_data){
    return E_UDM_OK;
}



