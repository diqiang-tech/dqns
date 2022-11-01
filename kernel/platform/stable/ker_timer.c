#include "ker_timer.h"

static TS_KER_TIMER* g_ker_timer_list = 0;

/***********************************************
* Description:
*    Timer module initialization.
*
* Prototype:    KerTimerInit
*
* Argument:void
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerInit(void){
    //TE_KER_TIMER_ID e_timer_id;
    T_U8 e_timer_id;

    g_ker_timer_list = KerTimerUserGetTimerList();

    for (e_timer_id = (TE_KER_TIMER_ID)0;e_timer_id < E_KER_TIMER_COUNT;e_timer_id++){
        g_ker_timer_list[e_timer_id].enable = E_FALSE;
        g_ker_timer_list[e_timer_id].timer_callback_func = 0;
    }      
    
}

/***********************************************
* Description:
*    Bind timer callback function.
*
* Prototype:    KerTimerBind
*
* Argument:
*    e_timer_id:timer id
*    fp_timer_callback:timer callback function
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerBind(TE_KER_TIMER_ID e_timer_id,TFP_KER_TIMER_CALLBACK fp_timer_callback){
    M_Assert(fp_timer_callback);

    g_ker_timer_list[e_timer_id].e_timer_id = e_timer_id;
    g_ker_timer_list[e_timer_id].e_timer_type = E_KER_TIMER_TYPE_NA;
    g_ker_timer_list[e_timer_id].period = 0;
    g_ker_timer_list[e_timer_id].count = 0;
    g_ker_timer_list[e_timer_id].timer_callback_func = fp_timer_callback;
    g_ker_timer_list[e_timer_id].enable = E_FALSE;
}


/***********************************************
* Description:
*    Let the timer to run once.
*
* Prototype:    KerTimerSetOnce
*
* Argument:
*    e_timer_id:timer id
*    ms:after N ms will call timer callback function
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerSetOnce(TE_KER_TIMER_ID e_timer_id,T_U32 ms){
    g_ker_timer_list[e_timer_id].e_timer_id = e_timer_id;
    g_ker_timer_list[e_timer_id].e_timer_type = E_KER_TIMER_TYPE_ONCE;
    g_ker_timer_list[e_timer_id].period = 0;
    g_ker_timer_list[e_timer_id].count = ms/KER_TIMER_MANAGE_PERIOD_MS;
    g_ker_timer_list[e_timer_id].enable = E_TRUE;    
}


/***********************************************
* Description:
*    Let the timer to run periodically.
*
* Prototype:    KerTimerSetPeriod
*
* Argument:
*    e_timer_id:timer id
*    ms:after N ms will call timer callback function
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerSetPeriod(TE_KER_TIMER_ID e_timer_id,T_U32 ms){
    g_ker_timer_list[e_timer_id].e_timer_id = e_timer_id;
    g_ker_timer_list[e_timer_id].e_timer_type = E_KER_TIMER_TYPE_PERIOD;
    g_ker_timer_list[e_timer_id].period = ms/KER_TIMER_MANAGE_PERIOD_MS;
    g_ker_timer_list[e_timer_id].count = ms/KER_TIMER_MANAGE_PERIOD_MS;
    g_ker_timer_list[e_timer_id].enable = E_TRUE;    
}


/***********************************************
* Description:
*    Execute timer callback function.
*
* Prototype:    KerTimerExec
*
* Argument:
*    e_timer_id:timer id
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerExec(TE_KER_TIMER_ID e_timer_id){
    M_Assert(e_timer_id == g_ker_timer_list[e_timer_id].e_timer_id);
    M_Assert(g_ker_timer_list[e_timer_id].timer_callback_func);

    g_ker_timer_list[e_timer_id].timer_callback_func(e_timer_id);
}


/***********************************************
* Description:
*    Enable a timer.
*
* Prototype:    KerTimerEnable
*
* Argument:
*    e_timer_id:timer id
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerEnable(TE_KER_TIMER_ID e_timer_id){  
    g_ker_timer_list[e_timer_id].enable = E_TRUE;
    
}

/***********************************************
* Description:
*    Disable a timer.
*
* Prototype:    KerTimerDisable
*
* Argument:
*    e_timer_id:timer id
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerDisable(TE_KER_TIMER_ID e_timer_id){
    g_ker_timer_list[e_timer_id].enable = E_FALSE;

}

/***********************************************
* Description:
*    Timer management machine.
*
* Prototype:    KerTimerManage
*
* Argument:void
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerTimerManage(void){
    //TE_KER_TIMER_ID e_timer_id;
    T_U8 e_timer_id;
    
   
    for (e_timer_id = (TE_KER_TIMER_ID)0;e_timer_id < E_KER_TIMER_COUNT;e_timer_id++){
        if (e_timer_id == g_ker_timer_list[e_timer_id].e_timer_id &&
            E_TRUE == g_ker_timer_list[e_timer_id].enable){
            
            if (g_ker_timer_list[e_timer_id].count){
                g_ker_timer_list[e_timer_id].count--;

                if (0 == g_ker_timer_list[e_timer_id].count){
                    if (E_KER_TIMER_TYPE_ONCE == g_ker_timer_list[e_timer_id].e_timer_type){
                        g_ker_timer_list[e_timer_id].enable = E_FALSE;
                        M_Assert(g_timer_list[e_timer_id].timer_callback_func);
                        g_ker_timer_list[e_timer_id].timer_callback_func((TE_KER_TIMER_ID)e_timer_id);
                    }
                    else if (E_KER_TIMER_TYPE_PERIOD == g_ker_timer_list[e_timer_id].e_timer_type){
                        g_ker_timer_list[e_timer_id].count = g_ker_timer_list[e_timer_id].period;
                        M_Assert(g_ker_timer_list[e_timer_id].timer_callback_func);
                        g_ker_timer_list[e_timer_id].timer_callback_func((TE_KER_TIMER_ID)e_timer_id);
                    }
                }
            }                
        }
    }
}

T_U32 KerTimerRemainMS(TE_KER_TIMER_ID e_timer_id){
    return (g_ker_timer_list[e_timer_id].count * KER_TIMER_MANAGE_PERIOD_MS);
}

