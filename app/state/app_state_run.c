#include "app_state_run.h"

extern TS_KER_STATE gg_app_state_run;

static void AppStateRunEnter(void* param);
static void AppStateRunLeave(void);

/*<dqns_gen_timer_handle_declare_begin>*/
static void AppStateRunReturnTimerHandle(TE_KER_TIMER_ID e_timer_id);
/*<dqns_gen_timer_handle_declare_end>*/

/*<dqns_gen_key_press_handle_declare_begin>*/
static TE_BOOL AppStateRunKeyRunStopPressHandle(void);
static TE_BOOL AppStateRunKeyLevelPressHandle(void);
static TE_BOOL AppStateRunKeySmartPressHandle(void);
static TE_BOOL AppStateRunKeyEqPressHandle(void);
/*<dqns_gen_key_press_handle_declare_end>*/

/*<dqns_gen_key_lp1_handle_declare_begin>*/
/*<dqns_gen_key_lp1_handle_declare_end>*/

/*<dqns_gen_key_lp2_handle_declare_begin>*/
/*<dqns_gen_key_lp2_handle_declare_end>*/

/*<dqns_gen_key_lp3_handle_declare_begin>*/
/*<dqns_gen_key_lp3_handle_declare_end>*/

/*<dqns_gen_key_release_handle_declare_begin>*/
static TE_BOOL AppStateRunKeyEqReleaseHandle(void);
/*<dqns_gen_key_release_handle_declare_end>*/

/*<dqns_gen_key_combine_handle_declare_begin>*/
/*<dqns_gen_key_combine_handle_declare_end>*/

/*<dqns_gen_user_msg_handle_declare_begin>*/
static TE_BOOL AppStateRunAbnormalMsgHandle(void* param);
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateRunInit(void){
    KerFSMStateBind(E_KER_STATE_ID_RUN,AppStateRunEnter,AppStateRunLeave);
}

static void AppStateRunEnter(void* param){
    (void)param;

    /*<dqns_gen_timer_handle_tbl_begin>*/
    KerTimerBind(E_KER_TIMER_RETURN,AppStateRunReturnTimerHandle);
    /*<dqns_gen_timer_handle_tbl_end>*/

    /*<dqns_gen_key_press_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_PRESS,AppStateRunKeyRunStopPressHandle);
    KerKeyBind(E_KER_KEY_LEVEL,E_KEY_MSG_TYPE_PRESS,AppStateRunKeyLevelPressHandle);
    KerKeyBind(E_KER_KEY_SMART,E_KEY_MSG_TYPE_PRESS,AppStateRunKeySmartPressHandle);
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_PRESS,AppStateRunKeyEqPressHandle);
    /*<dqns_gen_key_press_handle_tbl_end>*/

    /*<dqns_gen_key_lp1_handle_tbl_begin>*/
    /*<dqns_gen_key_lp1_handle_tbl_end>*/

    /*<dqns_gen_key_lp2_handle_tbl_begin>*/
    /*<dqns_gen_key_lp2_handle_tbl_end>*/

    /*<dqns_gen_key_lp3_handle_tbl_begin>*/
    /*<dqns_gen_key_lp3_handle_tbl_end>*/

    /*<dqns_gen_key_release_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_RELEASE,AppStateRunKeyEqReleaseHandle);
    /*<dqns_gen_key_release_handle_tbl_end>*/

    /*<dqns_gen_key_combine_handle_tbl_begin>*/
    /*<dqns_gen_key_combine_handle_tbl_end>*/

    /*<dqns_gen_user_msg_handle_tbl_begin>*/
    KerMsgBind(E_KER_MSG_ABNORMAL,AppStateRunAbnormalMsgHandle);
    /*<dqns_gen_user_msg_handle_tbl_end>*/

    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
    KerPumpRun();
}
static void AppStateRunLeave(void){

}

/*<dqns_gen_timer_handle_definition_begin>*/
static void AppStateRunReturnTimerHandle(TE_KER_TIMER_ID e_timer_id){
    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
}
/*<dqns_gen_timer_handle_definition_end>*/


/*<dqns_gen_key_press_handle_definition_begin>*/
static TE_BOOL AppStateRunKeyRunStopPressHandle(void){
    KerPumpStop();
    KerFSMGo(E_KER_STATE_ID_IDLE,0);
    return E_TRUE;
}
static TE_BOOL AppStateRunKeyLevelPressHandle(void){
    if (E_KER_DIG_SHOW_LEVEL == KerDigShowType()){
        KerPumpSwitchLevel();
    }
    KerDigShow(E_KER_DIG_SHOW_LEVEL);
    KerTimerSetOnce(E_KER_TIMER_RETURN, KER_DIG_RETURN_ONCE_MS);
    return E_TRUE;
}
static TE_BOOL AppStateRunKeySmartPressHandle(void){
    KerPumpSwitchMode();
    return E_TRUE;
}
static TE_BOOL AppStateRunKeyEqPressHandle(void){
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
static TE_BOOL AppStateRunKeyEqReleaseHandle(void){
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
static TE_BOOL AppStateRunAbnormalMsgHandle(void* param){
    KerFSMGo(E_KER_STATE_ID_ABNORMAL,param);
    return E_TRUE;
}
/*<dqns_gen_user_msg_handle_definition_end>*/


