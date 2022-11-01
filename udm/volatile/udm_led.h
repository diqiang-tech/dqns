#ifndef UDM_LED_H
#define UDM_LED_H

#ifdef __cplusplus
extern "C"{
#endif

#include "udm_types.h"
#include "udm_device_tbl.h"

typedef T_U32 T_UDM_LED_IOCTL;

static void UdmledInit(void);
static TE_UDM_RET_CODE UdmledOpen(T_UDM_OPEN_MODE open_mode);
static TE_UDM_RET_CODE UdmledClose(void);
static TE_UDM_RET_CODE UdmledRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmledWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmledIOCtl(void * p_data);

#ifdef __cplusplus
}
#endif

#endif
