#ifndef UDM_KEY_H
#define UDM_KEY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "udm_types.h"
#include "udm_device_tbl.h"


/* key bit value */      
/*<dqns_gen_udm_key_bits_begin>*/
#define UDM_KEY_BITx_RUN_STOP	1
#define UDM_KEY_BITx_LEVEL	2
#define UDM_KEY_BITx_SMART	4
#define UDM_KEY_BITx_EQ	8
/*<dqns_gen_udm_key_bits_end>*/

typedef T_U32 T_UDM_KEY_IOCTL;

static void UdmKeyInit(void);
static TE_UDM_RET_CODE UdmKeyOpen(T_UDM_OPEN_MODE open_mode);
static TE_UDM_RET_CODE UdmKeyClose(void);
static TE_UDM_RET_CODE UdmKeyRead(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmKeyWrite(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
static TE_UDM_RET_CODE UdmKeyIOCtl(void * p_data);


#ifdef __cplusplus
}
#endif

#endif