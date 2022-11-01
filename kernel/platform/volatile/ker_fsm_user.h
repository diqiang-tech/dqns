#ifndef KER_FSM_USER_H
#define KER_FSM_USER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "../../../common/common_types.h"

typedef enum{
    E_KER_STATE_ID_NONE,    
    /*<dqns_gen_state_id_begin>*/
    E_KER_STATE_ID_DEMO,
    E_KER_STATE_ID_X,
    E_KER_STATE_ID_IDLE,
    E_KER_STATE_ID_RUN,
    E_KER_STATE_ID_ABNORMAL,
    E_KER_STATE_ID_DEBUG,
    /*<dqns_gen_state_id_end>*/
    
    E_KER_STATE_ID_COUNT
}TE_KER_STATE_ID;


typedef struct{
    TE_KER_STATE_ID         e_state_id; /* state id */       
    TFP_VOID_VOID_STAR      Enter;
    TFP_VOID_VOID           Leave;    
}TS_KER_STATE;





#ifdef __cplusplus
}
#endif


#endif
