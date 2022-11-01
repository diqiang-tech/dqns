#ifndef KER_FSM_H
#define KER_FSM_H

#ifdef __cplusplus
extern "C"{
#endif 

#include "../../../common/common.h"
#include "../volatile/ker_fsm_user.h"

/* init  */
void KerFSMInit(void);

/* get  */
TE_KER_STATE_ID KerFSMCurStateID(void);/* get current state id */
TS_KER_STATE* KerFSMCurStateObj(void);/* get current state object */
TS_KER_STATE* KerFSMStateObj(TE_KER_STATE_ID e_state_id);/* get state object according to the state id */

/* set */
void KerFSMSetCurStateID(TE_KER_STATE_ID e_cur_state_id);/* set current state id */


/* enter and leave entrance bind */
void KerFSMStateBind(TE_KER_STATE_ID e_state_id,TFP_VOID_VOID_STAR enter_func,TFP_VOID_VOID leave_func);


/* state jump */
#ifdef __cplusplus
void KerFSMGo(TE_KER_STATE_ID e_state_id,void* param = 0);
#else
void KerFSMGo(TE_KER_STATE_ID e_state_id,void* param);
#endif



#ifdef __cplusplus
}
#endif 

#endif

