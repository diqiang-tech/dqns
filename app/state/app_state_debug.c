#include "../../kernel/platform/stable/ker_fsm.h"
#include "app_state_debug.h"

extern TS_KER_STATE gg_app_state_debug;

static void AppStateDebugEnter(void* param);
static void AppStateDebugLeave(void);

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
/*<dqns_gen_user_msg_handle_declare_end>*/

void AppStateDebugInit(void){
    KerFSMStateBind(E_KER_STATE_ID_DEBUG,AppStateDebugEnter,AppStateDebugLeave);
}

static void AppStateDebugEnter(void* param){
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
    /*<dqns_gen_user_msg_handle_tbl_end>*/

}
static void AppStateDebugLeave(void){

}

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_timer_handle_definition_begin>*/
/*<dqns_gen_timer_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_press_handle_definition_begin>*/
/*<dqns_gen_key_press_handle_definition_end>*/

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
/*<dqns_gen_key_release_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_key_combine_handle_definition_begin>*/
/*<dqns_gen_key_combine_handle_definition_end>*/

/*这里是脚本生成的框架，请剪切出去实现，防止被脚本冲掉*/
/*<dqns_gen_user_msg_handle_definition_begin>*/
/*<dqns_gen_user_msg_handle_definition_end>*/

