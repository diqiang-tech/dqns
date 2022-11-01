#include "../../kernel/platform/stable/ker_fsm.h"
#include "app_state_abnormal.h"

extern TS_KER_STATE gg_app_state_abnormal;

static void AppStateAbnormalEnter(void* param);
static void AppStateAbnormalLeave(void);

/*<dqns_gen_timer_handle_declare_begin>*/
/*<dqns_gen_timer_handle_declare_end>*/

/*<dqns_gen_key_press_handle_declare_begin>*/
static TE_BOOL AppStateAbnormalKeyRunStopPressHandle(void);
/*<dqns_gen_key_press_handle_declare_end>*/

/*<dqns_gen_key_lp1_handle_declare_begin>*/
/*<dqns_gen_key_lp1_handle_declare_end>*/

/*<dqns_gen_key_lp2_handle_declare_begin>*/
/*<dqns_gen_key_lp2_handle_declare_end>*/

/*<dqns_gen_key_lp3_handle_declare_begin>*/
/*<dqns_gen_key_lp3_handle_declare_end>*/

/*<dqns_gen_key_release_handle_declare_begin>*/
/*<dqns_gen_key_release_handle_declare_end>*/

/*<dqns_gen_key_combine_handle_declare_begin>*/
/*<dqns_gen_key_combine_handle_declare_end>*/

/*<dqns_gen_user_msg_handle_declare_begin>*/
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateAbnormalInit(void){
    KerFSMStateBind(E_KER_STATE_ID_ABNORMAL,AppStateAbnormalEnter,AppStateAbnormalLeave);
}

static void AppStateAbnormalEnter(void* param){
    (void)param;

    /*<dqns_gen_timer_handle_tbl_begin>*/
    /*<dqns_gen_timer_handle_tbl_end>*/

    /*<dqns_gen_key_press_handle_tbl_begin>*/
    KerKeyBind(E_KER_KEY_RUN_STOP,E_KEY_MSG_TYPE_PRESS,AppStateAbnormalKeyRunStopPressHandle);
    /*<dqns_gen_key_press_handle_tbl_end>*/

    /*<dqns_gen_key_lp1_handle_tbl_begin>*/
    /*<dqns_gen_key_lp1_handle_tbl_end>*/

    /*<dqns_gen_key_lp2_handle_tbl_begin>*/
    /*<dqns_gen_key_lp2_handle_tbl_end>*/

    /*<dqns_gen_key_lp3_handle_tbl_begin>*/
    /*<dqns_gen_key_lp3_handle_tbl_end>*/

    /*<dqns_gen_key_release_handle_tbl_begin>*/
    /*<dqns_gen_key_release_handle_tbl_end>*/

    /*<dqns_gen_key_combine_handle_tbl_begin>*/
    /*<dqns_gen_key_combine_handle_tbl_end>*/

    /*<dqns_gen_user_msg_handle_tbl_begin>*/
    /*<dqns_gen_user_msg_handle_tbl_end>*/

    KerDigShow(E_KER_DIG_SHOW_ERROR);
    KerTimerDisable(E_KER_TIMER_DIG_FRESH);

}
static void AppStateAbnormalLeave(void){

}

/*<dqns_gen_timer_handle_definition_begin>*/
/*<dqns_gen_timer_handle_definition_end>*/

/*<dqns_gen_key_press_handle_definition_begin>*/
static TE_BOOL AppStateAbnormalKeyRunStopPressHandle(void){
    KerFSMGo(E_KER_STATE_ID_IDLE, 0);
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
/*<dqns_gen_key_release_handle_definition_end>*/

/*<dqns_gen_key_combine_handle_definition_begin>*/
/*<dqns_gen_key_combine_handle_definition_end>*/

/*<dqns_gen_user_msg_handle_definition_begin>*/
/*<dqns_gen_user_msg_handle_definition_end>*/

