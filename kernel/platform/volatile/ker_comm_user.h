#ifndef KER_COMM_USER_H
#define KER_COMM_USER_H

#ifdef __cplusplus
extern "C"{
#endif


#include "../../../common/common.h"
/*<dqns_gen_include_comm_head_begin>*/
#include "ker_comm_pc.h"
/*<dqns_gen_include_comm_head_end>*/




/* communication channel */
typedef enum{
    /*<dqns_gen_comm_id_begin>*/
    E_KER_COMM_ID_PC,
    /*<dqns_gen_comm_id_end>*/
    E_KER_COMM_ID_COUNT
}TE_KER_COMM_CHANNEL;


typedef enum{
    E_COMM_RET_OK,
    E_COMM_RET_UNKNOW_CMD,
    E_COMM_RET_INVALID_CRC,
    E_COMM_RET_INVALID_PKT,
    E_COMM_RET_SYS_BUSY,
    E_COMM_RET_COUNT
}TE_COMM_RET_CODE;


void KerCommUserInit(void);


#ifdef __cplusplus
}
#endif


#endif

