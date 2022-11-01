
#include "ker_comm.h"

extern  const TS_KER_COMM_INFO* cgg_comm_info[E_KER_COMM_ID_COUNT];


void KerCommInit(void){
    KerCommUserInit();
}

TS_KER_COMM_INFO* KerCommObj(TE_KER_COMM_CHANNEL  e_comm_channel){
    M_Assert(e_comm_channel < E_KER_COMM_ID_COUNT);

    return (TS_KER_COMM_INFO*)cgg_comm_info[e_comm_channel];
}


void KerCommRxHandle(TE_KER_COMM_CHANNEL e_comm_channel){
    TS_KER_COMM_INFO* p_comm_obj;
    T_U8 rx_char = 0;

    M_Assert(e_comm_channel < E_KER_COMM_ID_COUNT);

    p_comm_obj = KerCommObj(e_comm_channel);

    M_Assert(p_comm_obj);
    if (RingQueueIsEmpty(p_comm_obj->p_ring_queue) == E_FALSE){
        M_RingQueueGet(p_comm_obj->p_ring_queue, &rx_char, T_U8);
        p_comm_obj->ReceiveByteFunc(rx_char);
    }

    
}

/* abstract parse handle used by rx handle */
void KerCommParseHandle(TE_KER_COMM_CHANNEL e_comm_channel,T_U8 cmd,T_U8* p_data,T_U16 data_len){
    TS_KER_COMM_INFO* p_comm_info;

    M_Assert(e_comm_channel < E_KER_COMM_ID_COUNT);
    M_Assert(p_data);

    p_comm_info = KerCommObj(e_comm_channel);

    M_Assert(p_comm_info);
    
    
    if (E_COMM_RET_OK != p_comm_info->CommParseFunc(cmd,p_data,data_len)){
        // TODO:
        /* need to do something when encounter error ? */
    }    
}

void KerCommSend(TE_KER_COMM_CHANNEL e_comm_channel,T_U8 comm_cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack){
    TS_KER_COMM_INFO* p_comm_info;

    M_Assert(e_comm_channel < E_KER_COMM_ID_COUNT);
    M_Assert(p_data);

    p_comm_info = KerCommObj(e_comm_channel);

    M_Assert(p_comm_info);

    p_comm_info->CommSendFunc(comm_cmd,p_data,data_len,need_ack);
}


void KerCommSetParseHandle(TE_KER_COMM_CHANNEL e_comm_channel,T_U8 cmd,TFP_KER_COMM_PARSE_HANDLE parse_handle){
    TS_KER_COMM_INFO* p_comm;

    p_comm = KerCommObj(e_comm_channel);

    M_Assert(p_comm);

    p_comm->p_parse_handle_table[(T_U8)cmd] = parse_handle;
    
}


