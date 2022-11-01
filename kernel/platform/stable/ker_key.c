#include <string.h>
#include "ker_key.h"
#include "ker_msg.h"
#include "ker_timer.h"
#include "ker_fsm.h"


static TU_KER_KEY_BITS g_drv_key_bits;
static TU_KER_KEY_BITS g_ker_key_bits;

extern TS_KER_KEY* gg_key_list[];

extern TFP_KEY_HANDLE gg_key_press_handlers[E_KER_KEY_COUNT];
extern TFP_KEY_HANDLE gg_key_long_press1_handlers[E_KER_KEY_COUNT];
extern TFP_KEY_HANDLE gg_key_long_press2_handlers[E_KER_KEY_COUNT];
extern TFP_KEY_HANDLE gg_key_long_press3_handlers[E_KER_KEY_COUNT];
extern TFP_KEY_HANDLE gg_key_release_handlers[E_KER_KEY_COUNT];
extern TFP_KEY_HANDLE gg_key_stuck_handlers[E_KER_KEY_COUNT];
extern TFP_KEY_HANDLE gg_key_combine_handlers[];

extern TFP_KEY_HANDLE * gg_key_msg_type_handlers[E_KEY_MSG_TYPE_COUNT];
extern const TS_KER_COMBINE_KEY_BITS gg_combine_key_bits[];


/* internal functions */
static void KerKeyScan(void);
static TE_KER_COMBINE_KEYS KerKeyCombineKey(TS_KER_KEY* p_key,T_KER_KEY_BITS ker_key_bits);
static void KerKeyScanActual(TE_KER_KEYS actual_key);
static void KerKeyDeinit(TS_KER_KEY * ps_key);
static void KerKeySendKeyMsg(TE_KER_KEYS e_key,TE_KER_KEY_MSG_TYPE key_msg_type);
static TE_BOOL KerKeyPressHandle(void* param);
static TE_BOOL KerKeyLongPress1Handle(void* param);
static TE_BOOL KerKeyLongPress2Handle(void* param);
static TE_BOOL KerKeyLongPress3Handle(void* param);
static TE_BOOL KerKeyReleaseHandle(void* param);
static TE_BOOL KerKeyStuckHandle(void* param);
static TE_BOOL KerKeyCombineHandle(void* param);
static void KerKeyScanTimerHandle(TE_KER_TIMER_ID e_timer_id);

void KerKeyInit(void)
{
    g_drv_key_bits.key_bits = 0;
    g_ker_key_bits.key_bits = 0;

    KerKeyCleanAllHandle();

    KerMsgBind(E_KER_MSG_KEY_PRESS,KerKeyPressHandle);
    KerMsgBind(E_KER_MSG_KEY_LONG_PRESS_1,KerKeyLongPress1Handle);
    KerMsgBind(E_KER_MSG_KEY_LONG_PRESS_2,KerKeyLongPress2Handle);
    KerMsgBind(E_KER_MSG_KEY_LONG_PRESS_3,KerKeyLongPress3Handle);
    KerMsgBind(E_KER_MSG_KEY_RELEASE,KerKeyReleaseHandle);
    KerMsgBind(E_KER_MSG_KEY_STUCK,KerKeyStuckHandle);
    KerMsgBind(E_KER_MSG_KEY_COMBINE,KerKeyCombineHandle);

    KerKeyUserInit();

    /* bind key scan timer handle */
    KerTimerBind(E_KER_TIMER_KEY_SCAN,KerKeyScanTimerHandle);

    KerKeyScanStart();
}


void KerKeyScanStart(void)
{
    KerTimerSetPeriod(E_KER_TIMER_KEY_SCAN,KEY_SCAN_MS);
}

void KerKeyScanStop(void)
{
    KerTimerDisable(E_KER_TIMER_KEY_SCAN);
}

void KerKeyBind(TE_KER_KEYS e_key,TE_KER_KEY_MSG_TYPE e_key_msg_type,TFP_KEY_HANDLE key_handle_func)
{
    M_Assert(e_key < E_KER_KEY_COUNT);
    M_Assert(e_key_msg_type < E_KEY_MSG_TYPE_COUNT);
    M_Assert(key_handle_func);

    gg_key_msg_type_handlers[e_key_msg_type][e_key] = key_handle_func;
}

void KerKeyCombineBind(TE_KER_COMBINE_KEYS e_combine_key,TFP_KEY_HANDLE key_handle_func)
{
    M_Assert(e_combine_key < E_KER_KEY_COMBINE_COUNT);
    M_Assert(key_handle_func);

    gg_key_combine_handlers[e_combine_key] = key_handle_func;
}

void KerKeyCleanAllHandle(void){
    memset(gg_key_press_handlers,NULL,sizeof(TFP_VOID_VOID)*E_KER_KEY_COUNT);
    memset(gg_key_long_press1_handlers,NULL,sizeof(TFP_VOID_VOID)*E_KER_KEY_COUNT);
    memset(gg_key_long_press2_handlers,NULL,sizeof(TFP_VOID_VOID)*E_KER_KEY_COUNT);
    memset(gg_key_long_press3_handlers,NULL,sizeof(TFP_VOID_VOID)*E_KER_KEY_COUNT);
    memset(gg_key_release_handlers,NULL,sizeof(TFP_VOID_VOID)*E_KER_KEY_COUNT);
    memset(gg_key_stuck_handlers,NULL,sizeof(TFP_VOID_VOID)*E_KER_KEY_COUNT);
    memset(gg_key_combine_handlers,NULL,sizeof(TFP_VOID_VOID)*E_KER_KEY_COMBINE_COUNT);
}

static void KerKeyScan(void){
    //TE_KER_KEYS e_key;
    T_U8 e_key;
    /* key bits information from driver. */
    g_drv_key_bits.key_bits = KerKeyUserBits();
    
    /* scan keys */ 
    for(e_key = (TE_KER_KEYS)0;e_key<E_KER_KEY_COUNT;e_key++){
        KerKeyScanActual((TE_KER_KEYS)e_key);       
    }
    
}

static TE_KER_COMBINE_KEYS KerKeyCombineKey(TS_KER_KEY* p_key,T_KER_KEY_BITS ker_key_bits){
    int i;

    M_Assert(p_key);

    for(i=0;i<E_KER_KEY_COMBINE_COUNT;i++){
        if (gg_combine_key_bits[i].combine_key_bits == ker_key_bits &&
            (p_key->key_combine_bits & ker_key_bits)){
            return (TE_KER_COMBINE_KEYS)i;
        }
    }

    return E_KER_KEY_COMBINE_COUNT;
}

static void KerKeyScanActual(TE_KER_KEYS actual_key){
    T_KER_KEY_BITS key_drv_bit = 0;
    T_KER_KEY_BITS key_ker_bit = 0;
    T_KER_KEY_BITS key_bit = 0;
    T_KER_KEY_BITS combine_key_bits = 0;
    TS_KER_KEY* p_key = 0;    

    M_Assert(actual_key < E_KER_KEY_COUNT);

    p_key = gg_key_list[actual_key];

    M_Assert(p_key);

    key_drv_bit = g_drv_key_bits.key_bits & (p_key->key_bit);
    key_ker_bit = g_ker_key_bits.key_bits & (p_key->key_bit);
    key_bit = p_key->key_bit;
    combine_key_bits = p_key->key_combine_bits;
    
    /* key  port bit */
    if (key_drv_bit){
        p_key->release_counter = 0;

        p_key->press_counter ++;

        /* Now the key status is released. */
        if (0 == key_ker_bit){            

            /* step over the jitter filter */
            //if (p_key->press_counter >= KEY_PRESS_COUNT_MAX){
            if (p_key->press_counter >= p_key->filter_counts){
                
                /* We need to clear release_counter , from disturbance.*/
                p_key->release_counter = 0;

                /* Now, key  is in pressed status. */    
                g_ker_key_bits.key_bits |= key_bit; 

                /* Before ,there are no other keys are pressed,except combine keys. */                
                if (0 == (g_ker_key_bits.key_bits & (~combine_key_bits))){                    
                    /* send key  press message */
                    KerKeySendKeyMsg(actual_key,E_KEY_MSG_TYPE_PRESS);
                    p_key->key_flag.key_flags_struct.already_send_press_msg_flag = 1;
                }                               
                
            }
                
        }        
        /* Now , the key status is pressed. */
        else if (key_ker_bit){        

            /* We need to clear release_counter , from disturbance.*/
            p_key->release_counter = 0;

            /* Don't reach stuck counts. */
            if (p_key->press_counter < KEY_STUCK_COUNT_MAX){                

                if (p_key->key_flag.key_flags_struct.need_care_long_press1_flag &&
                    p_key->press_counter >= KEY_LONG_PRESS1_COUNT_MAX &&
                    p_key->press_counter <  KEY_LONG_PRESS2_COUNT_MAX){

                    /* There are no other keys are pressed, except combine keys */                   
                    if (0 == (g_ker_key_bits.key_bits & (~(combine_key_bits?combine_key_bits:key_bit))) &&
                        (g_ker_key_bits.key_bits & key_bit)){
                        if (0 == p_key->key_flag.key_flags_struct.already_send_long_press1_flag){
                            /* send key  long press1 message */                            
                            KerKeySendKeyMsg(actual_key,E_KEY_MSG_TYPE_LONG_PRESS_1);
                            p_key->key_flag.key_flags_struct.already_send_long_press1_flag = 1;                           
                        }
                    }                    
                }
                else if (p_key->key_flag.key_flags_struct.need_care_long_press2_flag &&
                         p_key->press_counter >=  KEY_LONG_PRESS2_COUNT_MAX &&
                         p_key->press_counter <   KEY_LONG_PRESS3_COUNT_MAX){

                    /* There are no other keys are pressed, except combine keys */                   
                    if (0 == (g_ker_key_bits.key_bits & (~(combine_key_bits?combine_key_bits:key_bit))) &&
                        (g_ker_key_bits.key_bits & key_bit)){
                        if (0 == p_key->key_flag.key_flags_struct.already_send_long_press2_flag){
                            /* send key long press2 message */
                            KerKeySendKeyMsg(actual_key,E_KEY_MSG_TYPE_LONG_PRESS_2);
                            p_key->key_flag.key_flags_struct.already_send_long_press2_flag = 1;                            
                        }
                    }
                }
                else if (p_key->key_flag.key_flags_struct.need_care_long_press3_flag &&
                         p_key->press_counter >=  KEY_LONG_PRESS3_COUNT_MAX &&
                         p_key->press_counter < KEY_STUCK_COUNT_MAX){

                    /* There are no other keys are pressed, except combine keys */                    
                    if (0 == (g_ker_key_bits.key_bits & (~(combine_key_bits?combine_key_bits:key_bit))) &&
                        (g_ker_key_bits.key_bits & key_bit)){
                        if (0 == p_key->key_flag.key_flags_struct.already_send_long_press3_flag){
                            /* send key long press3 event */
                            KerKeySendKeyMsg(actual_key,E_KEY_MSG_TYPE_LONG_PRESS_3);
                            p_key->key_flag.key_flags_struct.already_send_long_press3_flag = 1;                            
                        }
                    }
                }                
            }
            /* key stuck */
            else if (p_key->key_flag.key_flags_struct.need_care_stuck_flag){

                if (0 == p_key->key_flag.key_flags_struct.already_send_key_stuck_flag){
                    /* send key stuck message */
                    KerKeySendKeyMsg(actual_key,E_KEY_MSG_TYPE_STUCK);
                    p_key->key_flag.key_flags_struct.already_send_key_stuck_flag = 1;                    
                }                
            }            
        }
    }

    else if (0 == key_drv_bit){
        p_key->press_counter = 0;
        if (key_ker_bit){
            p_key->release_counter ++;

            //if (p_key->release_counter >= KEY_RELEASE_COUNT_MAX){
            if (p_key->release_counter >= p_key->filter_counts){
                /* send key release event */
                KerKeySendKeyMsg(actual_key,E_KEY_MSG_TYPE_RELEASE);                
                g_ker_key_bits.key_bits &= (T_KER_KEY_BITS)(~key_bit);
                
                KerKeyDeinit(p_key);                  
            }            
        }
    }
}

static void KerKeyDeinit(TS_KER_KEY * ps_key)
{   
    M_Assert(ps_key);
    
    ps_key->press_counter = 0;
    ps_key->release_counter = 0;        
    ps_key->key_flag.key_flags_struct.already_send_press_msg_flag = 0;
    ps_key->key_flag.key_flags_struct.already_send_long_press1_flag = 0;
    ps_key->key_flag.key_flags_struct.already_send_long_press2_flag = 0;
    ps_key->key_flag.key_flags_struct.already_send_long_press3_flag = 0;
    ps_key->key_flag.key_flags_struct.already_send_key_stuck_flag = 0;
}

static void KerKeySendKeyMsg(TE_KER_KEYS e_key,TE_KER_KEY_MSG_TYPE key_msg_type)
{

    TS_KER_KEY* p_key = 0;
    TE_KER_COMBINE_KEYS combine_key = E_KER_KEY_COMBINE_COUNT;    

    M_Assert(e_key < E_KER_KEY_COUNT);
    M_Assert(key_msg_type < E_KEY_MSG_TYPE_COUNT);

    p_key = gg_key_list[e_key];

    if (key_msg_type == E_KEY_MSG_TYPE_PRESS){        
        
        combine_key = KerKeyCombineKey(p_key,g_ker_key_bits.key_bits);
        if (combine_key != E_KER_KEY_COMBINE_COUNT){
            KerMsgSend(E_KER_MSG_KEY_COMBINE,(void*)combine_key);
        }
        else{
            KerMsgSend(E_KER_MSG_KEY_PRESS,(void*)e_key);
        }
    }
    else{
        KerMsgSend((TE_KER_MSG_ID)key_msg_type,(void*)e_key);
    }    
  
}

static TE_BOOL KerKeyPressHandle(void* param){
    TE_KER_KEYS e_key = (TE_KER_KEYS)((T_U32)param);

    M_Assert(e_key < E_KER_KEY_COUNT);

    if(gg_key_press_handlers[e_key]){
        return (gg_key_press_handlers[e_key]());
    }

    /* the screen get the msg firstly */
    /* if return true,means will not call control's msg callback function  */
    return E_TRUE;   
}
static TE_BOOL KerKeyLongPress1Handle(void* param){
    TE_KER_KEYS e_key = (TE_KER_KEYS)((T_U32)param);

    M_Assert(e_key < E_KER_KEY_COUNT);

    if(gg_key_long_press1_handlers[e_key]){
        return (gg_key_long_press1_handlers[e_key]());
    }

    /* the screen get the msg firstly */
    /* if return true,means will not call control's msg callback function  */
    return E_TRUE;  
}
static TE_BOOL KerKeyLongPress2Handle(void* param){
    TE_KER_KEYS e_key = (TE_KER_KEYS)((T_U32)param);

    M_Assert(e_key < E_KER_KEY_COUNT);

    if(gg_key_long_press2_handlers[e_key]){
        return (gg_key_long_press2_handlers[e_key]());
    }

    /* the screen get the msg firstly */
    /* if return true,means will not call control's msg callback function  */
    return E_TRUE;  
}
static TE_BOOL KerKeyLongPress3Handle(void* param){
    TE_KER_KEYS e_key = (TE_KER_KEYS)((T_U32)param);

    M_Assert(e_key < E_KER_KEY_COUNT);

    if(gg_key_long_press3_handlers[e_key]){
        return (gg_key_long_press3_handlers[e_key]());
    }

    /* the screen get the msg firstly */
    /* if return true,means will not call control's msg callback function  */
    return E_TRUE;  
}
static TE_BOOL KerKeyReleaseHandle(void* param){
    TE_KER_KEYS e_key = (TE_KER_KEYS)((T_U32)param);

    M_Assert(e_key < E_KER_KEY_COUNT);

    if(gg_key_release_handlers[e_key]){
        return (gg_key_release_handlers[e_key]());
    }

    /* the screen get the msg firstly */
    /* if return true,means will not call control's msg callback function  */
    return E_TRUE;  
}
static TE_BOOL KerKeyStuckHandle(void* param){
    TE_KER_KEYS e_key = (TE_KER_KEYS)((T_U32)param);

    M_Assert(e_key < E_KER_KEY_COUNT);

    if(gg_key_stuck_handlers[e_key]){
        return (gg_key_stuck_handlers[e_key]());
    }

    /* the screen get the msg firstly */
    /* if return true,means will not call control's msg callback function  */
    return E_TRUE;  
}
static TE_BOOL KerKeyCombineHandle(void* param){
    TE_KER_KEYS e_key = (TE_KER_KEYS)((T_U32)param);

    M_Assert(e_key < E_KER_KEY_COUNT);

    if(gg_key_combine_handlers[e_key]){
        return (gg_key_combine_handlers[e_key]());
    }

    /* the screen get the msg firstly */
    /* if return true,means will not call control's msg callback function  */
    return E_TRUE;  
}

static void KerKeyScanTimerHandle(TE_KER_TIMER_ID e_timer_id){
    KerKeyScan();
}

