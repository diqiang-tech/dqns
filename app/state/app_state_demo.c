#include "../../kernel/platform/stable/ker_fsm.h"
#include "app_state_demo.h"

extern TS_KER_STATE gg_app_state_demo;

static void AppStateDemoEnter(void* param);
static void AppStateDemoLeave(void);

/*<dqns_gen_timer_handle_declare_begin>*/
static void AppStateDemoWorkingLedTimerHandle(TE_KER_TIMER_ID e_timer_id);
/*<dqns_gen_timer_handle_declare_end>*/

/*<dqns_gen_key_press_handle_declare_begin>*/
static TE_BOOL AppStateDemoKeyRunStopPressHandle(void);
/*<dqns_gen_key_press_handle_declare_end>*/

/*<dqns_gen_key_lp1_handle_declare_begin>*/
/*<dqns_gen_key_lp1_handle_declare_end>*/

/*<dqns_gen_key_lp2_handle_declare_begin>*/
static TE_BOOL AppStateDemoKeyRunStopLp2Handle(void);
/*<dqns_gen_key_lp2_handle_declare_end>*/

/*<dqns_gen_key_lp3_handle_declare_begin>*/
static TE_BOOL AppStateDemoKeyRunStopLp3Handle(void);
/*<dqns_gen_key_lp3_handle_declare_end>*/

/*<dqns_gen_key_release_handle_declare_begin>*/
static TE_BOOL AppStateDemoKeyRunStopReleaseHandle(void);
/*<dqns_gen_key_release_handle_declare_end>*/

/*<dqns_gen_key_combine_handle_declare_begin>*/
/*<dqns_gen_key_combine_handle_declare_end>*/

/*<dqns_gen_user_msg_handle_declare_begin>*/
static TE_BOOL AppStateDemoUserTestMsgHandle(void* param);
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateDemoInit(void){
    KerFSMStateBind(E_KER_STATE_ID_DEMO,AppStateDemoEnter,AppStateDemoLeave);
}

static void AppStateDemoEnter(void* param){
    (void)param;

    /*<dqns_gen_timer_handle_tbl_begin>*/
    KerTimerBind(E_KER_TIMER_WORKING_LED,AppStateDemoWorkingLedTimerHandle);
    /*<dqns_gen_timer_handle_tbl_end>*/

    /*<dqns_gen_key_press_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_PRESS,AppStateDemoKeyRunStopPressHandle);
    /*<dqns_gen_key_press_handle_tbl_end>*/

    /*<dqns_gen_key_lp1_handle_tbl_begin>*/
    /*<dqns_gen_key_lp1_handle_tbl_end>*/

    /*<dqns_gen_key_lp2_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_LONG_PRESS_2,AppStateDemoKeyRunStopLp2Handle);
    /*<dqns_gen_key_lp2_handle_tbl_end>*/

    /*<dqns_gen_key_lp3_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_LONG_PRESS_3,AppStateDemoKeyRunStopLp3Handle);
    /*<dqns_gen_key_lp3_handle_tbl_end>*/

    /*<dqns_gen_key_release_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_RELEASE,AppStateDemoKeyRunStopReleaseHandle);
    /*<dqns_gen_key_release_handle_tbl_end>*/

    /*<dqns_gen_key_combine_handle_tbl_begin>*/
    /*<dqns_gen_key_combine_handle_tbl_end>*/

    /*<dqns_gen_user_msg_handle_tbl_begin>*/
    KerMsgBind(E_KER_MSG_USER_TEST,AppStateDemoUserTestMsgHandle);
    /*<dqns_gen_user_msg_handle_tbl_end>*/

}
static void AppStateDemoLeave(void){

}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_timer_handle_definition_begin>*/
static void AppStateDemoWorkingLedTimerHandle(TE_KER_TIMER_ID e_timer_id){

}
/*<dqns_gen_timer_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_press_handle_definition_begin>*/
static TE_BOOL AppStateDemoKeyRunStopPressHandle(void){
    return E_FALSE;
}
/*<dqns_gen_key_press_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_lp1_handle_definition_begin>*/
/*<dqns_gen_key_lp1_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_lp2_handle_definition_begin>*/
static TE_BOOL AppStateDemoKeyRunStopLp2Handle(void){
    return E_FALSE;
}
/*<dqns_gen_key_lp2_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_lp3_handle_definition_begin>*/
static TE_BOOL AppStateDemoKeyRunStopLp3Handle(void){
    return E_FALSE;
}
/*<dqns_gen_key_lp3_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_release_handle_definition_begin>*/
static TE_BOOL AppStateDemoKeyRunStopReleaseHandle(void){
    return E_FALSE;
}
/*<dqns_gen_key_release_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_combine_handle_definition_begin>*/
/*<dqns_gen_key_combine_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_user_msg_handle_definition_begin>*/
static TE_BOOL AppStateDemoUserTestMsgHandle(void* param){
    return E_FALSE;
}
/*<dqns_gen_user_msg_handle_definition_end>*/

