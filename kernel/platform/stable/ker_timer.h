#ifndef KER_TIMER_H
#define KER_TIMER_H

#ifdef __cplusplus
extern "C"{
#endif

//#include "common.h"
#include "../volatile/ker_timer_user.h"


void KerTimerInit(void);
void KerTimerBind(TE_KER_TIMER_ID e_timer_id,TFP_KER_TIMER_CALLBACK fp_timer_callback);
void KerTimerSetOnce(TE_KER_TIMER_ID e_timer_id,T_U32 ms);
void KerTimerSetPeriod(TE_KER_TIMER_ID e_timer_id,T_U32 ms);
void KerTimerExec(TE_KER_TIMER_ID e_timer_id);
void KerTimerEnable(TE_KER_TIMER_ID e_timer_id);
void KerTimerDisable(TE_KER_TIMER_ID e_timer_id);
void KerTimerManage(void);
T_U32 KerTimerRemainMS(TE_KER_TIMER_ID e_timer_id);

#ifdef __cplusplus
}
#endif

#endif

