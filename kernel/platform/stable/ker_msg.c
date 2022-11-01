#include "ker_msg.h"

//#include "ui_screen.h"

/* includes states */


#ifdef USE_UI
static void KerMsgDeliverToControl(TE_KER_MSG_ID msg_id, void* param);
#endif


//extern struct TS_CONTROL;
//extern TS_CONTROL* UiScreenFocusControl(void);

   
/***********************************************
* Description:
*    Msg's kernel module initialization.
*
* Prototype:    KerMsgInit
*
* Argument:void
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerMsgInit(void){
    KerMsgUserInit();
}


/***********************************************
* Description:
*    Message pump machine.
*
* Prototype:    KerMsgPump
*
* Argument:void
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerMsgPump(void){

    TS_KER_MSG msg;
    TS_MSG_PUMP * 	p_msg_pump_obj = 0;
    p_msg_pump_obj = KerMsgUserMsgPumpObj();

    if (E_FALSE == RingQueueIsEmpty(p_msg_pump_obj->p_msg_ring_queue)){
        M_RingQueueGet(p_msg_pump_obj->p_msg_ring_queue,&msg,TS_KER_MSG);    

        #ifdef _DEBUG_
        if (msg.msg_id != E_KER_MSG_NEED_CARE_ADC){
            M_Trace("Get Message %d,parameter is %d\n",msg.msg_id,(T_U32)msg.param);
        }
        #endif

        if ((msg.msg_id != E_KER_MSG_NULL) &&
            (msg.msg_id < E_KER_MSG_COUNT)){

            //if(g_msg_func_table[msg.msg_id]){
            if(p_msg_pump_obj->pp_msg_func[msg.msg_id]) {
                /* if function handle return E_FALSE means ,need to deliver the msg to current screen's focused control */
                if (E_FALSE == (p_msg_pump_obj->pp_msg_func[msg.msg_id])(msg.param)){
                    #ifdef USE_UI
                    KerMsgDeliverToControl(msg.msg_id,msg.param);
                    #endif
                }
            }
        }
	}
}



/***********************************************
* Description:
*    Message send function.
*
* Prototype:    KerMsgSend
*
* Argument:
*    msg_id:message id
*    param:parameter with corresponding message
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerMsgSend(TE_KER_MSG_ID msg_id, void* param){
    TS_KER_MSG msg;
    TS_MSG_PUMP * p_msg_pump_obj = 0;
        
    msg.msg_id = msg_id;
    msg.param= param;    

    p_msg_pump_obj = KerMsgUserMsgPumpObj();
    
    
    if (E_FALSE == RingQueueIsFull(p_msg_pump_obj->p_msg_ring_queue)){
        M_RingQueuePut(p_msg_pump_obj->p_msg_ring_queue,msg,TS_KER_MSG);
    }
}


/***********************************************
* Description:
*    Message callback function bind function.
*
* Prototype:    KerMsgBind
*
* Argument:
*    e_msg_id:message id
*    p_msg_func:message callback function pointer
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerMsgBind(TE_KER_MSG_ID e_msg_id,TFP_MSG_FUNC p_msg_func){

    TS_MSG_PUMP * 	p_msg_pump_obj = 0;

    p_msg_pump_obj = KerMsgUserMsgPumpObj();
    
    p_msg_pump_obj->pp_msg_func[e_msg_id] = p_msg_func;
}


/***********************************************
* Description:
*    Clear all message callback function.
*
* Prototype:    KerMsgClearAllHandles
*
* Argument:void
*
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void KerMsgClearAllHandles(void){
    T_U8 i;
    TS_MSG_PUMP * 	p_msg_pump_obj = 0;

    p_msg_pump_obj = KerMsgUserMsgPumpObj();
    
    for(i=0;i<p_msg_pump_obj->msg_count;++i){
        p_msg_pump_obj->pp_msg_func[i] = NULL;
    }
}

#ifdef USE_UI
static void KerMsgDeliverToControl(TE_KER_MSG_ID msg_id, void* param)
{
    UiScreenFocusControl()->OnMsg(msg_id,param);
}
#endif


TE_BOOL KerMsgIsQueueEmpty(void){

    TS_MSG_PUMP * p_msg_pump_obj = 0;

    p_msg_pump_obj = KerMsgUserMsgPumpObj();

    return (RingQueueIsEmpty(p_msg_pump_obj->p_msg_ring_queue));
}

