#ifndef UDM_PUMP_H
#define UDM_PUMP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "udm_types.h"
#include "udm_device_tbl.h"

typedef T_U32 T_UDM_PUMP_IOCTL;

static void UdmPumpInit(void);
static TE_UDM_RET_CODE UdmPumpOpen(T_UDM_OPEN_MODE open_mode);
static TE_UDM_RET_CODE UdmPumpClose(void);
static TE_UDM_RET_CODE UdmPumpRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmPumpWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmPumpIOCtl(void * p_data);

#ifdef __cplusplus
}
#endif

#endif
