#include "app_state_idle.h"

extern TS_KER_STATE gg_app_state_idle;

static void AppStateIdleEnter(void* param);
static void AppStateIdleLeave(void);

/*<dqns_gen_timer_handle_declare_begin>*/
static void AppStateIdleReturnTimerHandle(TE_KER_TIMER_ID e_timer_id);
/*<dqns_gen_timer_handle_declare_end>*/

/*<dqns_gen_key_press_handle_declare_begin>*/
static TE_BOOL AppStateIdleKeyRunStopPressHandle(void);
static TE_BOOL AppStateIdleKeyLevelPressHandle(void);
static TE_BOOL AppStateIdleKeySmartPressHandle(void);
static TE_BOOL AppStateIdleKeyEqPressHandle(void);
/*<dqns_gen_key_press_handle_declare_end>*/

/*<dqns_gen_key_lp1_handle_declare_begin>*/
/*<dqns_gen_key_lp1_handle_declare_end>*/

/*<dqns_gen_key_lp2_handle_declare_begin>*/
/*<dqns_gen_key_lp2_handle_declare_end>*/

/*<dqns_gen_key_lp3_handle_declare_begin>*/
/*<dqns_gen_key_lp3_handle_declare_end>*/

/*<dqns_gen_key_release_handle_declare_begin>*/
static TE_BOOL AppStateIdleKeyEqReleaseHandle(void);
/*<dqns_gen_key_release_handle_declare_end>*/

/*<dqns_gen_key_combine_handle_declare_begin>*/
/*<dqns_gen_key_combine_handle_declare_end>*/

/*<dqns_gen_user_msg_handle_declare_begin>*/
static TE_BOOL AppStateIdleAbnormalMsgHandle(void* param);
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateIdleInit(void){
    KerFSMStateBind(E_KER_STATE_ID_IDLE,AppStateIdleEnter,AppStateIdleLeave);
}

static void AppStateIdleEnter(void* param){
    (void)param;

    /*<dqns_gen_timer_handle_tbl_begin>*/
    KerTimerBind(E_KER_TIMER_RETURN,AppStateIdleReturnTimerHandle);
    /*<dqns_gen_timer_handle_tbl_end>*/

    /*<dqns_gen_key_press_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_PRESS,AppStateIdleKeyRunStopPressHandle);
    KerKeyBind(E_KER_KEY_LEVEL,E_KEY_MSG_TYPE_PRESS,AppStateIdleKeyLevelPressHandle);
    KerKeyBind(E_KER_KEY_SMART,E_KEY_MSG_TYPE_PRESS,AppStateIdleKeySmartPressHandle);
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_PRESS,AppStateIdleKeyEqPressHandle);
    /*<dqns_gen_key_press_handle_tbl_end>*/

    /*<dqns_gen_key_lp1_handle_tbl_begin>*/
    /*<dqns_gen_key_lp1_handle_tbl_end>*/

    /*<dqns_gen_key_lp2_handle_tbl_begin>*/
    /*<dqns_gen_key_lp2_handle_tbl_end>*/

    /*<dqns_gen_key_lp3_handle_tbl_begin>*/
    /*<dqns_gen_key_lp3_handle_tbl_end>*/

    /*<dqns_gen_key_release_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_RELEASE,AppStateIdleKeyEqReleaseHandle);
    /*<dqns_gen_key_release_handle_tbl_end>*/

    /*<dqns_gen_key_combine_handle_tbl_begin>*/
    /*<dqns_gen_key_combine_handle_tbl_end>*/

    /*<dqns_gen_user_msg_handle_tbl_begin>*/
    KerMsgBind(E_KER_MSG_ABNORMAL,AppStateIdleAbnormalMsgHandle);
    /*<dqns_gen_user_msg_handle_tbl_end>*/
    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
    KerTimerSetPeriod(E_KER_TIMER_DIG_FRESH,KER_DIG_FRESH_PERIOD_MS);

}
static void AppStateIdleLeave(void){

}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_timer_handle_definition_begin>*/
static void AppStateIdleReturnTimerHandle(TE_KER_TIMER_ID e_timer_id){
    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
}
/*<dqns_gen_timer_handle_definition_end>*/


/*<dqns_gen_key_press_handle_definition_begin>*/
static TE_BOOL AppStateIdleKeyRunStopPressHandle(void){
    //lock pin is not locked,
    if (0 == KerPinStatus(E_KER_PIN_LockStatus)){
        //run into run mode
        KerFSMGo(E_KER_STATE_ID_RUN, 0);        
    }    
    return E_TRUE;
}
static TE_BOOL AppStateIdleKeyLevelPressHandle(void){
    if (E_KER_DIG_SHOW_LEVEL == KerDigShowType()){
        KerPumpSwitchLevel();
    }
    KerDigShow(E_KER_DIG_SHOW_LEVEL);
    KerTimerSetOnce(E_KER_TIMER_RETURN, KER_DIG_RETURN_ONCE_MS);
    return E_TRUE;
}
static TE_BOOL AppStateIdleKeySmartPressHandle(void){
    KerPumpSwitchMode();
    return E_TRUE;
}
static TE_BOOL AppStateIdleKeyEqPressHandle(void){
    KerDigShow(E_KER_DIG_SHOW_EQ);
    KerTimerDisable(E_KER_TIMER_RETURN);
    return E_TRUE;
}
/*<dqns_gen_key_press_handle_definition_end>*/


/*<dqns_gen_key_lp1_handle_definition_begin>*/
/*<dqns_gen_key_lp1_handle_definition_end>*/

/*<dqns_gen_key_lp2_handle_definition_begin>*/
/*<dqns_gen_key_lp2_handle_definition_end>*/

/*<dqns_gen_key_lp3_handle_definition_begin>*/
/*<dqns_gen_key_lp3_handle_definition_end>*/

/*<dqns_gen_key_release_handle_definition_begin>*/
static TE_BOOL AppStateIdleKeyEqReleaseHandle(void){
    KerDigShowPre();
    if (E_KER_DIG_SHOW_LEVEL == KerDigShowType()){
        KerTimerSetOnce(E_KER_TIMER_RETURN,KER_DIG_RETURN_ONCE_MS);
    }
    return E_TRUE;
}

/*<dqns_gen_key_release_handle_definition_end>*/



/*<dqns_gen_key_combine_handle_definition_begin>*/
/*<dqns_gen_key_combine_handle_definition_end>*/

/*<dqns_gen_user_msg_handle_definition_begin>*/
static TE_BOOL AppStateIdleAbnormalMsgHandle(void* param){
    KerFSMGo(E_KER_STATE_ID_ABNORMAL,param);
    return E_TRUE;
}
/*<dqns_gen_user_msg_handle_definition_end>*/


