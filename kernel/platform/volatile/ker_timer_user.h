#ifndef KER_TIMER_USER_H
#define KER_TIMER_USER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "../../../common/common.h"

#define KER_TIMER_MANAGE_PERIOD_MS 5

typedef enum{
    E_KER_TIMER_TYPE_ONCE,
    E_KER_TIMER_TYPE_PERIOD,
    E_KER_TIMER_TYPE_NA
}TE_KER_TIMER_TYPE;


typedef enum{
    /* ------ these timer id used by dqns self, ------begin*/  
    E_KER_TIMER_KEY_SCAN,/* key scan timer id */    
    E_KER_TIMER_PIN_SCAN,/* io pin scan timer id */
    E_KER_TIMER_PORT_SCAN,/* io port scan timer id */
    E_KER_TIMER_ADC_SCAN,    /* adc scan timer id */
    E_KER_TIMER_RX_PC_TIMEOUT,/* timeout timer of receive char  */   
    E_KER_TIMER_WAIT_PC_ACK_TIMEOUT,/* wait ack timeout timer */
    /* ------ these timer id used by dqns self, ------end*/  
   
    /*<dqns_gen_user_timer_id_begin>*/
    E_KER_TIMER_RETURN,    //dig display return to pressure from level
    E_KER_TIMER_RUN_STOP,    //用于智能模式下的走走停停
    E_KER_TIMER_DIG_FRESH,    //数码管刷新timer
    E_KER_TIMER_WORKING_LED,    //timer for led flash in working state
    /*<dqns_gen_user_timer_id_end>*/
  
   
    E_KER_TIMER_COUNT
}TE_KER_TIMER_ID;


typedef void(* TFP_KER_TIMER_CALLBACK)(TE_KER_TIMER_ID e_timer_id);


typedef struct{
    TE_KER_TIMER_ID e_timer_id;
    TE_KER_TIMER_TYPE e_timer_type;
    T_U32 period;
    T_U32 count;
    TFP_KER_TIMER_CALLBACK timer_callback_func;
    TE_BOOL enable;    
}TS_KER_TIMER;

TS_KER_TIMER * KerTimerUserGetTimerList(void);

#ifdef __cplusplus
}
#endif

#endif

