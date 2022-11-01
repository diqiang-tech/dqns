#ifndef KER_MSG_USER_H
#define KER_MSG_USER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "../../../service/ring_queue.h"

/*<dqns_gen_ring_queue_size_begin>*/
#define KER_MSG_RING_QUEUE_SIZE 3
/*<dqns_gen_ring_queue_size_end>*/



/* Include all messages of the system.  */
typedef enum{        
    /* ------------- key message ------------- */
    E_KER_MSG_KEY_PRESS = 0,           
    E_KER_MSG_KEY_LONG_PRESS_1 = 1,
    E_KER_MSG_KEY_LONG_PRESS_2 = 2,
    E_KER_MSG_KEY_LONG_PRESS_3 = 3,   
    E_KER_MSG_KEY_RELEASE = 4,
    E_KER_MSG_KEY_STUCK = 5,
    E_KER_MSG_KEY_COMBINE = 6,

    /* ------------- io pin status/io port value shange message ------------- */
    /* IO Pin Status Change */
    E_KER_MSG_PIN_STATUS_CHANGE = 7,    
    /* IO Port Value Change */
    E_KER_MSG_IO_PORT_VALUE_CHANGE = 8,

    
    /* ------------- need care adc values -------------*/
    E_KER_MSG_NEED_CARE_ADC = 9,
    E_KER_MSG_UpdateData = 10,

    /* ------------- user message ------------- begin*/    
    /*<dqns_gen_user_msg_id_begin>*/    
    E_KER_MSG_POST,    //post msg
    E_KER_MSG_ABNORMAL,    //alarm msg
    /*<dqns_gen_user_msg_id_end>*/  
    /* ------------- user message ------------- end*/    

    /* NULL msg as default msg */
    E_KER_MSG_NULL,

    E_KER_MSG_COUNT
}TE_KER_MSG_ID;

/* Message struct type. */
typedef struct{
    TE_KER_MSG_ID msg_id;
    void* param;
}TS_KER_MSG;


/* Message handler function type. */
typedef TE_BOOL(*TFP_MSG_FUNC)(void* param);


/* message pump struct type. */
typedef struct{
    TS_RING_QUEUE * p_msg_ring_queue;
    TFP_MSG_FUNC * pp_msg_func;
    T_U8 msg_count;
}TS_MSG_PUMP;


void KerMsgUserInit(void);
TS_MSG_PUMP * KerMsgUserMsgPumpObj(void);



#ifdef __cplusplus
}
#endif


#endif
