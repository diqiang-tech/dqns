#ifndef UDM_DIG_H
#define UDM_DIG_H

#ifdef __cplusplus
extern "C"{
#endif

#include "udm_types.h"
#include "udm_device_tbl.h"

typedef T_U32 T_UDM_DIG_IOCTL;

static void UdmDigInit(void);
static TE_UDM_RET_CODE UdmDigOpen(T_UDM_OPEN_MODE open_mode);
static TE_UDM_RET_CODE UdmDigClose(void);
static TE_UDM_RET_CODE UdmDigRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmDigWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmDigIOCtl(void * p_data);

#ifdef __cplusplus
}
#endif

#endif
