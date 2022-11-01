#ifndef UDM_API_H
#define UDM_API_H

#ifdef __cplusplus
extern "C"{
#endif


#include "../../common/common.h"
#include "../../common/c_defs.h"
#include "../volatile/udm_types.h"
#include "../volatile/udm_device_tbl.h"

void UdmInit(TE_UDM_DEVICE_ID e_device_id);
TE_UDM_RET_CODE UdmOpen(TE_UDM_DEVICE_ID e_device_id,T_UDM_OPEN_MODE open_mode);
TE_UDM_RET_CODE UdmClose(TE_UDM_DEVICE_ID e_device_id);
TE_UDM_RET_CODE UdmRead(TE_UDM_DEVICE_ID e_device_id,T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
TE_UDM_RET_CODE UdmWrite(TE_UDM_DEVICE_ID e_device_id,T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
TE_UDM_RET_CODE UdmIOCtl(TE_UDM_DEVICE_ID e_device_id,void * p_data);


#ifdef __cplusplus
}
#endif

#endif