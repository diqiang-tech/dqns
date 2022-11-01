#include "app_state_run_smart.h"

extern TS_KER_STATE gg_app_state_run_smart;

static void AppStateRunSmartEnter(void* param);
static void AppStateRunSmartLeave(void);

/*<dqns_gen_timer_handle_declare_begin>*/
static void AppStateRunSmartReturnTimerHandle(TE_KER_TIMER_ID e_timer_id);
/*<dqns_gen_timer_handle_declare_end>*/

/*<dqns_gen_key_press_handle_declare_begin>*/
static TE_BOOL AppStateRunSmartKeyRunStopPressHandle(void);
static TE_BOOL AppStateRunSmartKeyLevelPressHandle(void);
static TE_BOOL AppStateRunSmartKeySmartPressHandle(void);
static TE_BOOL AppStateRunSmartKeyEqPressHandle(void);
/*<dqns_gen_key_press_handle_declare_end>*/

/*<dqns_gen_key_lp1_handle_declare_begin>*/
/*<dqns_gen_key_lp1_handle_declare_end>*/

/*<dqns_gen_key_lp2_handle_declare_begin>*/
/*<dqns_gen_key_lp2_handle_declare_end>*/

/*<dqns_gen_key_lp3_handle_declare_begin>*/
/*<dqns_gen_key_lp3_handle_declare_end>*/

/*<dqns_gen_key_release_handle_declare_begin>*/
static TE_BOOL AppStateRunSmartKeyEqReleaseHandle(void);
/*<dqns_gen_key_release_handle_declare_end>*/

/*<dqns_gen_key_combine_handle_declare_begin>*/
/*<dqns_gen_key_combine_handle_declare_end>*/

/*<dqns_gen_user_msg_handle_declare_begin>*/
static TE_BOOL AppStateRunSmartAbnormalMsgHandle(void* param);
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateRunSmartInit(void){
    KerFSMStateBind(E_KER_STATE_ID_RUN_SMART,AppStateRunSmartEnter,AppStateRunSmartLeave);
}

static void AppStateRunSmartEnter(void* param){
    (void)param;

    /*<dqns_gen_timer_handle_tbl_begin>*/
    KerTimerBind(E_KER_TIMER_RETURN,AppStateRunSmartReturnTimerHandle);
    /*<dqns_gen_timer_handle_tbl_end>*/

    /*<dqns_gen_key_press_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_PRESS,AppStateRunSmartKeyRunStopPressHandle);
    KerKeyBind(E_KER_KEY_LEVEL,E_KEY_MSG_TYPE_PRESS,AppStateRunSmartKeyLevelPressHandle);
    KerKeyBind(E_KER_KEY_SMART,E_KEY_MSG_TYPE_PRESS,AppStateRunSmartKeySmartPressHandle);
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_PRESS,AppStateRunSmartKeyEqPressHandle);
    /*<dqns_gen_key_press_handle_tbl_end>*/

    /*<dqns_gen_key_lp1_handle_tbl_begin>*/
    /*<dqns_gen_key_lp1_handle_tbl_end>*/

    /*<dqns_gen_key_lp2_handle_tbl_begin>*/
    /*<dqns_gen_key_lp2_handle_tbl_end>*/

    /*<dqns_gen_key_lp3_handle_tbl_begin>*/
    /*<dqns_gen_key_lp3_handle_tbl_end>*/

    /*<dqns_gen_key_release_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_RELEASE,AppStateRunSmartKeyEqReleaseHandle);
    /*<dqns_gen_key_release_handle_tbl_end>*/

    /*<dqns_gen_key_combine_handle_tbl_begin>*/
    /*<dqns_gen_key_combine_handle_tbl_end>*/

    /*<dqns_gen_user_msg_handle_tbl_begin>*/
    KerMsgBind(E_KER_MSG_ABNORMAL,AppStateRunSmartAbnormalMsgHandle);
    /*<dqns_gen_user_msg_handle_tbl_end>*/

    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
    KerPumpRun();

}
static void AppStateRunSmartLeave(void){

}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_timer_handle_definition_begin>*/
static void AppStateRunSmartReturnTimerHandle(TE_KER_TIMER_ID e_timer_id){

}
/*<dqns_gen_timer_handle_definition_end>*/
static void AppStateRunSmartReturnTimerHandle(TE_KER_TIMER_ID e_timer_id){
    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_press_handle_definition_begin>*/
static TE_BOOL AppStateRunSmartKeyRunStopPressHandle(void){
    return E_FALSE;
}
static TE_BOOL AppStateRunSmartKeyLevelPressHandle(void){
    return E_FALSE;
}
static TE_BOOL AppStateRunSmartKeySmartPressHandle(void){
    return E_FALSE;
}
static TE_BOOL AppStateRunSmartKeyEqPressHandle(void){
    return E_FALSE;
}
/*<dqns_gen_key_press_handle_definition_end>*/
static TE_BOOL AppStateRunSmartKeyRunStopPressHandle(void){
    KerPumpStop();
    KerFSMGo(E_KER_STATE_ID_IDLE,0);
    return E_TRUE;
}
static TE_BOOL AppStateRunSmartKeyLevelPressHandle(void){
    if (E_KER_DIG_SHOW_LEVEL == KerDigShowType()){
        KerPumpSwitchLevel();
    }
    KerDigShow(E_KER_DIG_SHOW_LEVEL);
    KerTimerSetOnce(E_KER_TIMER_RETURN, KER_DIG_RETURN_ONCE_MS);
    return E_TRUE;
}
static TE_BOOL AppStateRunSmartKeySmartPressHandle(void){
    KerPumpSwitchMode();
    KerFSMGo(E_KER_STATE_ID_RUN_NORMAL,0);
    return E_TRUE;
}
static TE_BOOL AppStateRunSmartKeyEqPressHandle(void){
    KerDigShow(E_KER_DIG_SHOW_EQ);
    KerTimerDisable(E_KER_TIMER_RETURN);
    return E_TRUE;
}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_lp1_handle_definition_begin>*/
/*<dqns_gen_key_lp1_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_lp2_handle_definition_begin>*/
/*<dqns_gen_key_lp2_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_lp3_handle_definition_begin>*/
/*<dqns_gen_key_lp3_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_release_handle_definition_begin>*/
static TE_BOOL AppStateRunSmartKeyEqReleaseHandle(void){
    return E_FALSE;
}
/*<dqns_gen_key_release_handle_definition_end>*/
static TE_BOOL AppStateRunSmartKeyEqReleaseHandle(void){
    KerDigShowPre();
    if (E_KER_DIG_SHOW_LEVEL == KerDigShowType()){
        KerTimerSetOnce(E_KER_TIMER_RETURN,KER_DIG_RETURN_ONCE_MS);
    }
    return E_TRUE;
}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_combine_handle_definition_begin>*/
/*<dqns_gen_key_combine_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_user_msg_handle_definition_begin>*/
static TE_BOOL AppStateRunSmartAbnormalMsgHandle(void* param){
    return E_FALSE;
}
/*<dqns_gen_user_msg_handle_definition_end>*/
static TE_BOOL AppStateRunSmartAbnormalMsgHandle(void* param){
    KerFSMGo(E_KER_STATE_ID_ABNORMAL,param);
    return E_TRUE;
}

