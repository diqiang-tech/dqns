#include "app_state_run_normal.h"

extern TS_KER_STATE gg_app_state_run_normal;

static void AppStateRunNormalEnter(void* param);
static void AppStateRunNormalLeave(void);

/*<dqns_gen_timer_handle_declare_begin>*/
static void AppStateRunNormalReturnTimerHandle(TE_KER_TIMER_ID e_timer_id);
/*<dqns_gen_timer_handle_declare_end>*/

/*<dqns_gen_key_press_handle_declare_begin>*/
static TE_BOOL AppStateRunNormalKeyRunStopPressHandle(void);
static TE_BOOL AppStateRunNormalKeyLevelPressHandle(void);
static TE_BOOL AppStateRunNormalKeySmartPressHandle(void);
static TE_BOOL AppStateRunNormalKeyEqPressHandle(void);
/*<dqns_gen_key_press_handle_declare_end>*/

/*<dqns_gen_key_lp1_handle_declare_begin>*/
/*<dqns_gen_key_lp1_handle_declare_end>*/

/*<dqns_gen_key_lp2_handle_declare_begin>*/
/*<dqns_gen_key_lp2_handle_declare_end>*/

/*<dqns_gen_key_lp3_handle_declare_begin>*/
/*<dqns_gen_key_lp3_handle_declare_end>*/

/*<dqns_gen_key_release_handle_declare_begin>*/
static TE_BOOL AppStateRunNormalKeyEqReleaseHandle(void);
/*<dqns_gen_key_release_handle_declare_end>*/

/*<dqns_gen_key_combine_handle_declare_begin>*/
/*<dqns_gen_key_combine_handle_declare_end>*/

/*<dqns_gen_user_msg_handle_declare_begin>*/
static TE_BOOL AppStateRunNormalAbnormalMsgHandle(void* param);
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateRunNormalInit(void){
    KerFSMStateBind(E_KER_STATE_ID_RUN_NORMAL,AppStateRunNormalEnter,AppStateRunNormalLeave);
}

static void AppStateRunNormalEnter(void* param){
    (void)param;

    /*<dqns_gen_timer_handle_tbl_begin>*/
    KerTimerBind(E_KER_TIMER_RETURN,AppStateRunNormalReturnTimerHandle);
    /*<dqns_gen_timer_handle_tbl_end>*/

    /*<dqns_gen_key_press_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_PRESS,AppStateRunNormalKeyRunStopPressHandle);
    KerKeyBind(E_KER_KEY_LEVEL,E_KEY_MSG_TYPE_PRESS,AppStateRunNormalKeyLevelPressHandle);
    KerKeyBind(E_KER_KEY_SMART,E_KEY_MSG_TYPE_PRESS,AppStateRunNormalKeySmartPressHandle);
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_PRESS,AppStateRunNormalKeyEqPressHandle);
    /*<dqns_gen_key_press_handle_tbl_end>*/

    /*<dqns_gen_key_lp1_handle_tbl_begin>*/
    /*<dqns_gen_key_lp1_handle_tbl_end>*/

    /*<dqns_gen_key_lp2_handle_tbl_begin>*/
    /*<dqns_gen_key_lp2_handle_tbl_end>*/

    /*<dqns_gen_key_lp3_handle_tbl_begin>*/
    /*<dqns_gen_key_lp3_handle_tbl_end>*/

    /*<dqns_gen_key_release_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_EQ,E_KEY_MSG_TYPE_RELEASE,AppStateRunNormalKeyEqReleaseHandle);
    /*<dqns_gen_key_release_handle_tbl_end>*/

    /*<dqns_gen_key_combine_handle_tbl_begin>*/
    /*<dqns_gen_key_combine_handle_tbl_end>*/

    /*<dqns_gen_user_msg_handle_tbl_begin>*/
    KerMsgBind(E_KER_MSG_ABNORMAL,AppStateRunNormalAbnormalMsgHandle);
    /*<dqns_gen_user_msg_handle_tbl_end>*/

    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
    KerPumpRun();
}
static void AppStateRunNormalLeave(void){

}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_timer_handle_definition_begin>*/
static void AppStateRunNormalReturnTimerHandle(TE_KER_TIMER_ID e_timer_id){

}
/*<dqns_gen_timer_handle_definition_end>*/
static void AppStateRunNormalReturnTimerHandle(TE_KER_TIMER_ID e_timer_id){
    KerDigShow(E_KER_DIG_SHOW_PRESSURE);
}


/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_press_handle_definition_begin>*/
static TE_BOOL AppStateRunNormalKeyRunStopPressHandle(void){
    return E_FALSE;
}
static TE_BOOL AppStateRunNormalKeyLevelPressHandle(void){
    return E_FALSE;
}
static TE_BOOL AppStateRunNormalKeySmartPressHandle(void){
    return E_FALSE;
}
static TE_BOOL AppStateRunNormalKeyEqPressHandle(void){
    return E_FALSE;
}
/*<dqns_gen_key_press_handle_definition_end>*/
static TE_BOOL AppStateRunNormalKeyRunStopPressHandle(void){
    KerPumpStop();
    KerFSMGo(E_KER_STATE_ID_IDLE,0);
    return E_TRUE;
}
static TE_BOOL AppStateRunNormalKeyLevelPressHandle(void){
    if (E_KER_DIG_SHOW_LEVEL == KerDigShowType()){
        KerPumpSwitchLevel();
    }
    KerDigShow(E_KER_DIG_SHOW_LEVEL);
    KerTimerSetOnce(E_KER_TIMER_RETURN, KER_DIG_RETURN_ONCE_MS);
    return E_TRUE;
}
static TE_BOOL AppStateRunNormalKeySmartPressHandle(void){
    KerPumpSwitchMode();
    KerFSMGo(E_KER_STATE_ID_RUN_SMART,0);
    return E_TRUE;
}
static TE_BOOL AppStateRunNormalKeyEqPressHandle(void){
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
static TE_BOOL AppStateRunNormalKeyEqReleaseHandle(void){
    return E_FALSE;
}
/*<dqns_gen_key_release_handle_definition_end>*/
static TE_BOOL AppStateRunNormalKeyEqReleaseHandle(void){
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
static TE_BOOL AppStateRunNormalAbnormalMsgHandle(void* param){
    return E_FALSE;
}
/*<dqns_gen_user_msg_handle_definition_end>*/
static TE_BOOL AppStateRunNormalAbnormalMsgHandle(void* param){
    KerFSMGo(E_KER_STATE_ID_ABNORMAL,param);
    return E_TRUE;
}

