#include "ker_fsm_user.h"



/*<dqns_gen_state_definition_begin>*/
TS_KER_STATE gg_app_state_demo;
TS_KER_STATE gg_app_state_x;
TS_KER_STATE gg_app_state_idle;
TS_KER_STATE gg_app_state_run;
TS_KER_STATE gg_app_state_abnormal;
TS_KER_STATE gg_app_state_debug;
/*<dqns_gen_state_definition_end>*/



TS_KER_STATE* gg_all_state_table[] = {
    0,    
    /*<dqns_gen_state_tbl_begin>*/
    &gg_app_state_demo,
    &gg_app_state_x,
    &gg_app_state_idle,
    &gg_app_state_run,
    &gg_app_state_abnormal,
    &gg_app_state_debug,
    /*<dqns_gen_state_tbl_end>*/
};


