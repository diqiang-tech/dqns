
#include "ker_io.h"
#include "ker_msg.h"
#include "ker_timer.h"

#if 1
extern TS_KER_IO_PIN* gg_io_pin_tbl[];
extern TFP_U8_VOID gg_io_pin_read_func_tbl[];
extern const T_U8 gg_io_pin_filter_count_tbl[];

extern TS_KER_IO_PORT* gg_io_port_tbl[];
extern TFP_U8_VOID gg_io_port_read_func_tbl[];
extern const T_U8 gg_io_port_filter_count_tbl[];
#endif

static TFP_VOID_VOID g_pin_change_handle_tbl[E_KER_IO_PIN_COUNT];
static TFP_VOID_VOID g_port_change_handle_tbl[E_KER_IO_PORT_COUNT];

static void kerIOPinScan(void);
static void kerIOPortScan(void);

static TE_BOOL kerIOPinStatusChangeHandle(void* param);
static TE_BOOL kerIOPortValueChangeHandle(void* param);

static void kerIOPinScanTimerHandle(TE_KER_TIMER_ID e_timer_id);
static void kerIOPortScanTimerHandle(TE_KER_TIMER_ID e_timer_id);

void KerIOInit(void){
    KerIOUserInit();

    /* bind io pin status change handle */
    KerMsgBind(E_KER_MSG_IO_PIN_STATUS_CHANGE,kerIOPinStatusChangeHandle);
    /* bind io port value change handle */
    KerMsgBind(E_KER_MSG_IO_PORT_VALUE_CHANGE,kerIOPortValueChangeHandle);

    /* bind io pin scan timer handle */
    KerTimerBind(E_KER_TIMER_IO_PIN_SCAN,kerIOPinScanTimerHandle);
    /* bing io port scan timer handle */
    KerTimerBind(E_KER_TIMER_IO_PORT_SCAN,kerIOPortScanTimerHandle);
}

void KerIOPinScanStart(void){
    KerTimerSetPeriod(E_KER_TIMER_IO_PIN_SCAN,KER_IO_PIN_SCAN_MS);   
}

void KerIOPinScanStop(void){
    KerTimerDisable(E_KER_TIMER_IO_PIN_SCAN);                
}


void KerIOPortScanStart(void){
    KerTimerSetPeriod(E_KER_TIMER_IO_PORT_SCAN,KER_IO_PORT_SCAN_MS);    
}

void KerIOPortScanStop(void){
    KerTimerDisable(E_KER_TIMER_IO_PORT_SCAN);    
}


void KerIOPinScanEnable(TE_KER_IO_PIN_ID io_pin_id){
    M_Assert(io_pin_id < E_KER_IO_PIN_COUNT);
    M_Assert(gg_io_pin_tbl[io_pin_id]);    
    
    gg_io_pin_tbl[io_pin_id]->need_scan = 1;
    gg_io_pin_tbl[io_pin_id]->in_changing = 0;
    
}

void KerIOPinScanEnableAll(void){
    T_U8 i;
    
    for (i=0;i<E_KER_IO_PIN_COUNT;i++){
        M_Assert(gg_io_pin_tbl[i]);
        gg_io_pin_tbl[i]->need_scan = 1;
    }
}

void KerIOPortScanEnable(TE_KER_IO_PORT_ID io_port_id){
    M_Assert(io_port_id < E_KER_IO_PORT_COUNT);
    M_Assert(gg_io_port_tbl[io_port_id]);    
    
    gg_io_port_tbl[io_port_id]->need_scan = 1;
    
}

void KerIOPortScanEnableAll(void){
    T_U8 i;
    
    for (i=0;i<E_KER_IO_PORT_COUNT;i++){
        M_Assert(gg_io_port_tbl[i]);
        gg_io_port_tbl[i]->need_scan = 1;
    }
}


void KerIOPinScanDisable(TE_KER_IO_PIN_ID io_pin_id){
    M_Assert(io_pin_id < E_KER_IO_PIN_COUNT);
    M_Assert(gg_io_pin_tbl[io_pin_id]);

    gg_io_pin_tbl[io_pin_id]->need_scan = 0;    
    gg_io_pin_tbl[io_pin_id]->in_changing = 0;
}

void KerIOPinScanDisableAll(void){
    T_U8 i;
    
    for (i=0;i<E_KER_IO_PIN_COUNT;i++){
        M_Assert(gg_io_pin_tbl[i]);
        gg_io_pin_tbl[i]->need_scan = 0;
    }
}

void KerIOPortScanDisable(TE_KER_IO_PORT_ID io_port_id){
    M_Assert(io_port_id < E_KER_IO_PORT_COUNT);
    M_Assert(gg_io_port_tbl[io_port_id]);

    gg_io_port_tbl[io_port_id]->need_scan = 0;        
}

void KerIOPortScanDisableAll(void){
    T_U8 i;
    
    for (i=0;i<E_KER_IO_PORT_COUNT;i++){
        M_Assert(gg_io_port_tbl[i]);
        gg_io_port_tbl[i]->need_scan = 0;
    }
}


T_U8 KerIOPinStatus(TE_KER_IO_PIN_ID io_pin_id){
    M_Assert(io_pin_id < E_KER_IO_PIN_COUNT);
    M_Assert(gg_io_pin_tbl[io_pin_id]);

    return (gg_io_pin_tbl[io_pin_id]->stable_status);
}

T_U8 KerIOPortValue(TE_KER_IO_PORT_ID io_port_id){
    M_Assert(io_port_id < E_KER_IO_PORT_COUNT);
    M_Assert(gg_io_port_tbl[io_port_id]);

    return (gg_io_port_tbl[io_port_id]->stable_value);
}

void KerIOSetPinChangeHandle(TE_KER_IO_PIN_ID io_pin_id,TFP_VOID_VOID pin_change_handle){
    M_Assert(io_pin_id < E_KER_IO_PIN_COUNT);
    M_Assert(pin_change_handle);

    g_pin_change_handle_tbl[io_pin_id] = pin_change_handle;
}

void KerIOSetPortChangeHandle(TE_KER_IO_PORT_ID io_port_id,TFP_VOID_VOID port_change_handle){
    M_Assert(io_port_id < E_KER_IO_PORT_COUNT);
    M_Assert(port_change_handle);

    g_port_change_handle_tbl[io_port_id] = port_change_handle;
}

static void kerIOPinScan(void){
    int i;
    T_U8 pin_status;
    TS_KER_IO_PIN* p_io_pin;

    for(i=0;i<E_KER_IO_PIN_COUNT;i++){

        p_io_pin = gg_io_pin_tbl[i];
        M_Assert(p_io_pin);
        
        if (p_io_pin->need_scan){
            M_Assert(gg_io_pin_read_func_tbl[i]);
            pin_status = gg_io_pin_read_func_tbl[i]();

            if (pin_status != p_io_pin->stable_status){               

                if (0 == p_io_pin->in_changing){
                    p_io_pin->dynamic_status = pin_status;
                    p_io_pin->filter_count = 0;
                    p_io_pin->in_changing = 1;
                    break;
                }                

                if (pin_status == p_io_pin->dynamic_status){
                    p_io_pin->filter_count ++;
                }
                else{
                    p_io_pin->filter_count = 0;
                    p_io_pin->in_changing = 0;
                }

                
                /* io pin status changed */
                if (p_io_pin->filter_count >= gg_io_pin_filter_count_tbl[i]){
                    p_io_pin->stable_status = p_io_pin->dynamic_status;
                    p_io_pin->filter_count = 0;
                    p_io_pin->in_changing = 0;

                    /* send io pin status change message */
                    KerMsgSend(E_KER_MSG_IO_PIN_STATUS_CHANGE, (void*)i);
                }
                
            }
        }
    }
}

static void kerIOPortScan(void){
    int i;
    T_U8 port_value;
    TS_KER_IO_PORT* p_io_port;

    for(i=0;i<E_KER_IO_PORT_COUNT;i++){

        p_io_port = gg_io_port_tbl[i];
        M_Assert(p_io_port);
        
        if (p_io_port->need_scan){
            M_Assert(gg_io_port_read_func_tbl[i]);
            port_value = gg_io_port_read_func_tbl[i]();

            if (port_value != p_io_port->stable_value){            

                if (0 == p_io_port->in_changing){
                    p_io_port->dynamic_value = port_value;
                    p_io_port->filter_count = 0;
                    p_io_port->in_changing = 1;
                    break;
                }                

                if (port_value == p_io_port->dynamic_value){
                    p_io_port->filter_count ++;
                }
                else{
                    p_io_port->filter_count = 0;
                    p_io_port->in_changing = 0;
                }

                
                /* io port value changed */
                if (p_io_port->filter_count >= gg_io_port_filter_count_tbl[i]){
                    p_io_port->stable_value = p_io_port->dynamic_value;
                    p_io_port->filter_count = 0;
                    p_io_port->in_changing = 0;

                    /* send io port value change message */
                    KerMsgSend(E_KER_MSG_IO_PORT_VALUE_CHANGE, (void*)i);
                }
                
            }
        }
    }
}

static TE_BOOL kerIOPinStatusChangeHandle(void* param){
    //M_Assert(param);

    if (g_pin_change_handle_tbl[(int)param]){
        g_pin_change_handle_tbl[(int)param]();
    }

    return E_TRUE;
}

static TE_BOOL kerIOPortValueChangeHandle(void* param){
    //M_Assert(param);

    if (g_port_change_handle_tbl[(int)param]){
        g_port_change_handle_tbl[(int)param]();
    }

    return E_TRUE;
}

static void kerIOPinScanTimerHandle(TE_KER_TIMER_ID e_timer_id){
    kerIOPinScan();
}

static void kerIOPortScanTimerHandle(TE_KER_TIMER_ID e_timer_id){
    kerIOPortScan();
}

