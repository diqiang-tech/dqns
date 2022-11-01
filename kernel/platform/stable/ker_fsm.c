#include "ker_fsm.h"
      
extern TS_KER_STATE* gg_all_state_table[];
static TE_KER_STATE_ID g_cur_state_id;


/* initialization  */
void KerFSMInit(void)
{      
    g_cur_state_id = E_KER_STATE_ID_NONE;
}


/* get current state id */
TE_KER_STATE_ID KerFSMCurStateID(void)
{
    return g_cur_state_id;
}


/* set current state id */
void KerFSMSetCurStateID(TE_KER_STATE_ID e_cur_state_id)
{
    g_cur_state_id = e_cur_state_id;
}

/* get current state object */
TS_KER_STATE* KerFSMCurStateObj(void)
{
    TE_KER_STATE_ID e_cur_state_id;

    e_cur_state_id = KerFSMCurStateID();
    
    return gg_all_state_table[e_cur_state_id];
}


/* get state object according to the state id */
TS_KER_STATE* KerFSMStateObj(TE_KER_STATE_ID e_state_id)
{
    M_Assert(e_state_id < E_KER_STATE_ID_COUNT);

    return gg_all_state_table[e_state_id];
}


/* switch current state to corresponding e_state_id point to */
void KerFSMGo(TE_KER_STATE_ID e_state_id,void* param)
{
    TS_KER_STATE* p_cur_state = NULL;
    TS_KER_STATE* p_goal_state = NULL;

    p_cur_state = KerFSMCurStateObj();
    p_goal_state = KerFSMStateObj(e_state_id);

    M_Assert(p_cur_state);
    M_Assert(p_goal_state);

    /* if goal state is equal current state, do nothing ,*/
    if (KerFSMCurStateID() == e_state_id){
        return;
    }


    /* if current state is NONE ,means first call KerFSMGo,can't call Leave() */
    if (KerFSMCurStateID() != E_KER_STATE_ID_NONE){
        if (p_cur_state->Leave){
            p_cur_state->Leave();
        }
    }        

    /* set current state id */
    KerFSMSetCurStateID(e_state_id); 

    M_Assert(p_goal_state->Enter);
    if (p_goal_state->Enter){
        p_goal_state->Enter(param);
    }
   
}


void KerFSMStateBind(TE_KER_STATE_ID e_state_id,TFP_VOID_VOID_STAR enter_func,TFP_VOID_VOID leave_func)
{
    M_Assert(e_state_id < E_KER_STATE_ID_COUNT);
    
    TS_KER_STATE* p_state = gg_all_state_table[e_state_id];

    M_Assert(p_state);

    p_state->e_state_id = e_state_id;
    p_state->Enter = enter_func;
    p_state->Leave = leave_func;
}

