#include "ker_key_user.h"
#include "../stable/ker_key.h"
#include "../../../udm/stable/udm_api.h"
#include "../../../udm/volatile/udm_key.h"

/*<dqns_gen_key_obj_begin>*/
TS_KER_KEY gg_key_run_stop;    //启停按键
TS_KER_KEY gg_key_level;    //档位按键
TS_KER_KEY gg_key_smart;    //智能按键
TS_KER_KEY gg_key_eq;    //electronic quality电量按键
/*<dqns_gen_key_obj_end>*/


TS_KER_KEY* gg_key_list[] = {
    /*<dqns_gen_key_obj_tbl_begin>*/
    &gg_key_run_stop,    //启停按键
    &gg_key_level,    //档位按键
    &gg_key_smart,    //智能按键
    &gg_key_eq,    //electronic quality电量按键
    /*<dqns_gen_key_obj_tbl_end>*/
};



TS_KER_COMBINE_KEY_BITS gg_combine_key_bits[E_KER_KEY_COMBINE_COUNT] = {
    /*<dqns_gen_combine_key_bits_map_begin>*/
    {E_KER_KEY_COMBINE_DUMMY,UDM_KEY_BITx_LEVEL+UDM_KEY_BITx_SMART},
    /*<dqns_gen_combine_key_bits_map_end>*/
};

TFP_KEY_HANDLE gg_key_press_handlers[E_KER_KEY_COUNT];
TFP_KEY_HANDLE gg_key_long_press1_handlers[E_KER_KEY_COUNT];
TFP_KEY_HANDLE gg_key_long_press2_handlers[E_KER_KEY_COUNT];
TFP_KEY_HANDLE gg_key_long_press3_handlers[E_KER_KEY_COUNT];
TFP_KEY_HANDLE gg_key_release_handlers[E_KER_KEY_COUNT];
TFP_KEY_HANDLE gg_key_stuck_handlers[E_KER_KEY_COUNT];
TFP_KEY_HANDLE gg_key_combine_handlers[E_KER_KEY_COMBINE_COUNT];

TFP_KEY_HANDLE * gg_key_msg_type_handlers[E_KEY_MSG_TYPE_COUNT]={
    gg_key_press_handlers,
    gg_key_long_press1_handlers,
    gg_key_long_press2_handlers,
    gg_key_long_press3_handlers,
    gg_key_release_handlers,
    gg_key_stuck_handlers
};

void KerKeyUserInit(void){
    /*<dqns_gen_key_initialization_begin>*/
    /* run_stop key initialization */ 
    gg_key_run_stop.press_counter = 0;
    gg_key_run_stop.release_counter = 0;
    gg_key_run_stop.filter_counts = KER_FILTER_COUNT_MAX;
    gg_key_run_stop.key_bit = UDM_KEY_BITx_RUN_STOP;
    gg_key_run_stop.key_combine_bits = UDM_KEY_BITx_RUN_STOP;
    gg_key_run_stop.key_flag.key_flags = 0;
    gg_key_run_stop.key_flag.key_flags_struct.need_care_long_press1_flag = 0;
    gg_key_run_stop.key_flag.key_flags_struct.need_care_long_press2_flag = 0;
    gg_key_run_stop.key_flag.key_flags_struct.need_care_long_press3_flag = 0;
    gg_key_run_stop.key_flag.key_flags_struct.need_care_stuck_flag = 0;

    /* level key initialization */ 
    gg_key_level.press_counter = 0;
    gg_key_level.release_counter = 0;
    gg_key_level.filter_counts = KER_FILTER_COUNT_MAX;
    gg_key_level.key_bit = UDM_KEY_BITx_LEVEL;
    gg_key_level.key_combine_bits = UDM_KEY_BITx_LEVEL;
    gg_key_level.key_flag.key_flags = 0;
    gg_key_level.key_flag.key_flags_struct.need_care_long_press1_flag = 0;
    gg_key_level.key_flag.key_flags_struct.need_care_long_press2_flag = 0;
    gg_key_level.key_flag.key_flags_struct.need_care_long_press3_flag = 0;
    gg_key_level.key_flag.key_flags_struct.need_care_stuck_flag = 0;

    /* smart key initialization */ 
    gg_key_smart.press_counter = 0;
    gg_key_smart.release_counter = 0;
    gg_key_smart.filter_counts = KER_FILTER_COUNT_MAX;
    gg_key_smart.key_bit = UDM_KEY_BITx_SMART;
    gg_key_smart.key_combine_bits = UDM_KEY_BITx_SMART;
    gg_key_smart.key_flag.key_flags = 0;
    gg_key_smart.key_flag.key_flags_struct.need_care_long_press1_flag = 0;
    gg_key_smart.key_flag.key_flags_struct.need_care_long_press2_flag = 0;
    gg_key_smart.key_flag.key_flags_struct.need_care_long_press3_flag = 0;
    gg_key_smart.key_flag.key_flags_struct.need_care_stuck_flag = 0;

    /* eq key initialization */ 
    gg_key_eq.press_counter = 0;
    gg_key_eq.release_counter = 0;
    gg_key_eq.filter_counts = KER_FILTER_COUNT_MAX;
    gg_key_eq.key_bit = UDM_KEY_BITx_EQ;
    gg_key_eq.key_combine_bits = UDM_KEY_BITx_EQ;
    gg_key_eq.key_flag.key_flags = 0;
    gg_key_eq.key_flag.key_flags_struct.need_care_long_press1_flag = 0;
    gg_key_eq.key_flag.key_flags_struct.need_care_long_press2_flag = 0;
    gg_key_eq.key_flag.key_flags_struct.need_care_long_press3_flag = 0;
    gg_key_eq.key_flag.key_flags_struct.need_care_stuck_flag = 0;

    /*<dqns_gen_key_initialization_end>*/

    UdmOpen(E_UDM_DEVICE_KEY,UDM_OPEN_MODE_R);    

}

T_KER_KEY_BITS KerKeyUserBits(void){
    return (T_KER_KEY_BITS)(0);
}

