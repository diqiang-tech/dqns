#ifndef KER_COMM_H
#define KER_COMM_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../volatile/ker_comm_user.h"


typedef TE_COMM_RET_CODE(* TFP_KER_COMM_PARSE_HANDLE)(T_U8 comm_cmd,T_U8* p_data,T_U16 data_len);
typedef void(*TFP_KER_COMM_SEND)(T_U8 comm_cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack);


typedef union{
    struct{
        T_U8 is_ack:1;
        T_U8 need_ack:1;
        T_U8 na:6;
    }control_byte_bits_struct;
    T_U8 control_byte_bits;
}TU_KER_COMM_CONTROL_BYTE;

typedef union{
    struct{
        T_U16 is_writing_parse_buffer:1;
        T_U16 is_waiting_ack:1;
        T_U16 remain_retry_counts:3;
        T_U16 na:11;
    }comm_status_bits_struct;
    T_U16 comm_status_bits;
}TU_KER_COMM_STATUS;

/* communication data structure describe one communication channel */
typedef struct{    
    TS_RING_QUEUE* p_ring_queue;/* buffer used by comm rx isr */
    T_U8* parse_buffer;        
    TFP_KER_COMM_PARSE_HANDLE* p_parse_handle_table;/* parse handle table pointer */
    TFP_VOID_UCHAR ReceiveByteFunc;/* receive byte call back function */    
    TFP_KER_COMM_PARSE_HANDLE CommParseFunc;/* parse handle */    
    TFP_KER_COMM_SEND CommSendFunc;/* send packet func */
    T_U16 write_idx_of_parse_buffer;/* write index of parse_buffer, range in[0,parse_buffer_size-1]  */
    TU_KER_COMM_STATUS comm_status;
}TS_KER_COMM_INFO;


#define M_KerCommSetParseHandle(comm_channel,cmd,parse_handle) do{\
    (KerCommObj(comm_channel)->p_parse_handle_table)[(T_U8)cmd] = parse_handle;\
}while(0)


void KerCommInit(void);
TS_KER_COMM_INFO* KerCommObj(TE_KER_COMM_CHANNEL  e_comm_channel);
void KerCommRxHandle(TE_KER_COMM_CHANNEL e_comm_channel);
void KerCommParseHandle(TE_KER_COMM_CHANNEL e_comm_channel,T_U8 cmd,T_U8* p_data,T_U16 data_len);
void KerCommSend(TE_KER_COMM_CHANNEL e_comm_channel,T_U8 comm_cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack);
void KerCommSetParseHandle(TE_KER_COMM_CHANNEL e_comm_channel,T_U8 cmd,TFP_KER_COMM_PARSE_HANDLE parse_handle);


#ifdef __cplusplus
}
#endif


#endif

