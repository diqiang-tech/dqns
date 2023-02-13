#include "udm_api.h"


void UdmInit(void){
    UdmDeviceInit();
}


TE_UDM_RET_CODE UdmOpen(TE_UDM_DEVICE_ID e_device_id,T_UDM_OPEN_MODE open_mode){
    TE_UDM_RET_CODE e_ret_code = E_UDM_OK;
    TS_UDM_DEVICE * p_device = 0;
    p_device = UdmDeviceObj(e_device_id);
    M_Assert(p_device);
    e_ret_code = p_device->p_fn_open(open_mode);
    return e_ret_code;
}
TE_UDM_RET_CODE UdmClose(TE_UDM_DEVICE_ID e_device_id){
    TE_UDM_RET_CODE e_ret_code = E_UDM_OK;
    TS_UDM_DEVICE * p_device = 0;
    p_device = UdmDeviceObj(e_device_id);
    M_Assert(p_device);
    e_ret_code = p_device->p_fn_close();
    return e_ret_code;
}

TE_UDM_RET_CODE UdmRead(TE_UDM_DEVICE_ID e_device_id,T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    TE_UDM_RET_CODE e_ret_code = E_UDM_OK;
    TS_UDM_DEVICE * p_device = 0;
    p_device = UdmDeviceObj(e_device_id);
    M_Assert(e_device_id < E_UDM_DEVICE_CNT);
    M_Assert(p_device);
    e_ret_code = p_device->p_fn_read(start_addr,len,p_data);
    return e_ret_code;
}
TE_UDM_RET_CODE UdmWrite(TE_UDM_DEVICE_ID e_device_id,T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data){
    TE_UDM_RET_CODE e_ret_code = E_UDM_OK;
    TS_UDM_DEVICE * p_device = 0;
    p_device = UdmDeviceObj(e_device_id);
    M_Assert(e_device_id < E_UDM_DEVICE_CNT);
    M_Assert(p_device);
    e_ret_code = p_device->p_fn_write(start_addr,len,p_data);
    return e_ret_code;
}
TE_UDM_RET_CODE UdmIOCtl(TE_UDM_DEVICE_ID e_device_id,void * p_data){
    TE_UDM_RET_CODE e_ret_code = E_UDM_OK;
    TS_UDM_DEVICE * p_device = 0;
    p_device = UdmDeviceObj(e_device_id);
    M_Assert(e_device_id < E_UDM_DEVICE_CNT);
    M_Assert(p_device);
    e_ret_code = p_device->p_fn_ioctl(p_data);
    return e_ret_code;
}

