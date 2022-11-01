#include "../stable/ker_comm.h"
#include "ker_comm_user.h"

/*<dqns_gen_comm_obj_begin>*/
extern TS_KER_COMM_INFO gg_comm_pc;
/*<dqns_gen_comm_obj_end>*/


const TS_KER_COMM_INFO* cgg_comm_info[E_KER_COMM_ID_COUNT] = {
    /*<dqns_gen_comm_obj_tbl_begin>*/
    &gg_comm_pc,
    /*<dqns_gen_comm_obj_tbl_end>*/
};

void KerCommUserInit(void)
{
    /*<dqns_gen_comm_user_init_begin>*/
    KerCommPcInit();
    /*<dqns_gen_comm_user_init_end>*/
}

