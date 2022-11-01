
#include "ker_pin.h"
#include "ker_msg.h"
#include "ker_timer.h"

#if 1
extern TS_KER_PIN* gg_pin_tbl[];
extern TFP_U8_VOID gg_pin_read_func_tbl[];
extern const T_U8 gg_pin_filter_count_tbl[];
#endif

static TFP_VOID_VOID g_pin_change_handle_tbl[E_KER_PIN_COUNT];

static void kerPinScan(void);

static TE_BOOL kerPinStatusChangeHandle(void* param);

static void kerPinScanTimerHandle(TE_KER_TIMER_ID e_timer_id);

void KerPinInit(void){
    KerPinUserInit();

    /* bind io pin status change handle */
    KerMsgBind(E_KER_MSG_PIN_STATUS_CHANGE,kerPinStatusChangeHandle);

    /* bind io pin scan timer handle */
    KerTimerBind(E_KER_TIMER_PIN_SCAN,kerPinScanTimerHandle);
}

void KerPinScanStart(void){
    KerTimerSetPeriod(E_KER_TIMER_PIN_SCAN,KER_PIN_SCAN_MS);
}

void KerPinScanStop(void){
    KerTimerDisable(E_KER_TIMER_PIN_SCAN);
}

void KerPinScanEnable(TE_KER_PIN_ID pin_id){
    M_Assert(pin_id < E_KER_PIN_COUNT);
    M_Assert(gg_pin_tbl[pin_id]);
    
    gg_pin_tbl[pin_id]->need_scan = 1;
    gg_pin_tbl[pin_id]->in_changing = 0;
    
}

void KerPinScanEnableAll(void){
    T_U8 i;
    
    for (i=0;i<E_KER_PIN_COUNT;i++){
        M_Assert(gg_pin_tbl[i]);
        gg_pin_tbl[i]->need_scan = 1;
    }
}

void KerPinScanDisable(TE_KER_PIN_ID pin_id){
    M_Assert(pin_id < E_KER_PIN_COUNT);
    M_Assert(gg_pin_tbl[pin_id]);

    gg_pin_tbl[pin_id]->need_scan = 0;
    gg_pin_tbl[pin_id]->in_changing = 0;
}

void KerPinScanDisableAll(void){
    T_U8 i;
    
    for (i=0;i<E_KER_PIN_COUNT;i++){
        M_Assert(gg_pin_tbl[i]);
        gg_pin_tbl[i]->need_scan = 0;
    }
}




T_U8 KerPinStatus(TE_KER_PIN_ID pin_id){
    M_Assert(pin_id < E_KER_PIN_COUNT);
    M_Assert(gg_pin_tbl[pin_id]);

    return (gg_pin_tbl[pin_id]->stable_status);
}



void KerPinSetChangeHandle(TE_KER_PIN_ID pin_id,TFP_VOID_VOID pin_change_handle){
    M_Assert(pin_id < E_KER_PIN_COUNT);
    M_Assert(pin_change_handle);

    g_pin_change_handle_tbl[pin_id] = pin_change_handle;
}



static void kerPinScan(void){
    int i;
    T_U8 pin_status;
    TS_KER_PIN* p_pin;

    for(i=0;i<E_KER_PIN_COUNT;i++){

        p_pin = gg_pin_tbl[i];
        M_Assert(p_pin);
        
        if (p_pin->need_scan){
            M_Assert(gg_pin_read_func_tbl[i]);
            pin_status = gg_pin_read_func_tbl[i]();

            if (pin_status != p_pin->stable_status){

                if (0 == p_pin->in_changing){
                    p_pin->dynamic_status = pin_status;
                    p_pin->filter_count = 0;
                    p_pin->in_changing = 1;
                    break;
                }

                if (pin_status == p_pin->dynamic_status){
                    p_pin->filter_count ++;
                }
                else{
                    p_pin->filter_count = 0;
                    p_pin->in_changing = 0;
                }

                
                /* io pin status changed */
                if (p_pin->filter_count >= gg_pin_filter_count_tbl[i]){
                    p_pin->stable_status = p_pin->dynamic_status;
                    p_pin->filter_count = 0;
                    p_pin->in_changing = 0;

                    /* send io pin status change message */
                    KerMsgSend(E_KER_MSG_PIN_STATUS_CHANGE, (void*)i);
                }
                
            }
        }
    }
}



static TE_BOOL kerPinStatusChangeHandle(void* param){
    //M_Assert(param);

    if (g_pin_change_handle_tbl[(int)param]){
        g_pin_change_handle_tbl[(int)param]();
    }

    return E_TRUE;
}


static void kerPinScanTimerHandle(TE_KER_TIMER_ID e_timer_id){
    kerPinScan();
}


