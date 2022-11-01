#include "../../kernel/platform/stable/ker_fsm.h"
#include "app_state_x.h"

extern TS_KER_STATE gg_app_state_x;

static void AppStateXEnter(void* param);
static void AppStateXLeave(void);

/*<dqns_gen_timer_handle_declare_begin>*/
/*<dqns_gen_timer_handle_declare_end>*/

/*<dqns_gen_key_press_handle_declare_begin>*/
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
static TE_BOOL AppStateXPostMsgHandle(void* param);
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateXInit(void){
    KerFSMStateBind(E_KER_STATE_ID_X,AppStateXEnter,AppStateXLeave);
}

static void AppStateXEnter(void* param){
    (void)param;

    /*<dqns_gen_timer_handle_tbl_begin>*/
    /*<dqns_gen_timer_handle_tbl_end>*/

    /*<dqns_gen_key_press_handle_tbl_begin>*/
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
    KerMsgBind(E_KER_MSG_POST,AppStateXPostMsgHandle);
    /*<dqns_gen_user_msg_handle_tbl_end>*/

    KerDigShow(E_KER_DIG_SHOW_POST);

}
static void AppStateXLeave(void){

}

/*<dqns_gen_timer_handle_definition_begin>*/
/*<dqns_gen_timer_handle_definition_end>*/

/*<dqns_gen_key_press_handle_definition_begin>*/
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
static TE_BOOL AppStateXPostMsgHandle(void* param){
    if (0 == param){
        KerFSMGo(E_KER_STATE_ID_IDLE, 0);
    }
    else{
        KerFSMGo(E_KER_STATE_ID_ABNORMAL,param);
    }
    return E_TRUE;
}
/*<dqns_gen_user_msg_handle_definition_end>*/


