#ifndef KER_MSG_H
#define KER_MSG_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../../common/common.h"
#include "../volatile/ker_msg_user.h"


void KerMsgInit(void);
void KerMsgPump(void);
void KerMsgSend(TE_KER_MSG_ID msg_id, void* param);
void KerMsgBind(TE_KER_MSG_ID e_msg_id,TFP_MSG_FUNC p_msg_func);
void KerMsgClearAllHandles(void);
TE_BOOL KerMsgIsQueueEmpty(void);


#ifdef __cplusplus
}
#endif

#endif

