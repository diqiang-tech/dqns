

#include "ker_comm_ext.h"
#include "../stable/ker_comm.h"
#include "../stable/ker_timer.h"


//extern UART_HandleTypeDef huart1;

T_U8 gg_comm_rx_ext_flag;
// comm package

/* ------ rx ext ring queue buffer ------ */
static T_U8 g_rx_ext_buffer[KER_COMM_RX_EXT_RING_QUEUE_SIZE];
/* ------ ring queue ------ */
static TS_RING_QUEUE g_rx_ext_ring_queue;

/* ------ rx ext parse buffer ------ */
static T_U8 g_rx_ext_parse_buffer[KER_COMM_RX_EXT_PARSE_BUFFER_SIZE];


/* ------ rx ext cmd parse table ------ */
static TFP_KER_COMM_PARSE_HANDLE g_rx_ext_parse_handle_table[E_KER_COMM_CMD_RX_EXT_COUNT];


/* ------ comm information structure ------ */
TS_KER_COMM_INFO gg_comm_ext;


/* ------ rx handle ------ */
static void KerCommExtRxHandle(T_U8 uch);/* um */

/* ------ parse handle ------ */
static TE_COMM_RET_CODE KerCommExtParseHandle(T_U8 cmd,T_U8* p_data,T_U16 data_len);

/* ------ send func ------ */
static void KerCommExtSend(T_U8 cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack);

/* ------ rx timeout timer handle ------ */
static void KerCommExtRxTimeout(TE_KER_TIMER_ID e_time_id);

/* ------ wait dwin ack timeout timer handle ------ */
static void KerCommExtWaitAckTimeout(TE_KER_TIMER_ID e_time_id);


void KerCommExtInit(void){
    /* init ring queue */
    RingQueueInit(&g_rx_ext_ring_queue,(void*)g_rx_ext_buffer,KER_COMM_RX_EXT_RING_QUEUE_SIZE);

    /* init comm obj */
    gg_comm_ext.p_ring_queue = (&g_rx_ext_ring_queue);
    gg_comm_ext.parse_buffer = g_rx_ext_parse_buffer;
    gg_comm_ext.p_parse_handle_table = g_rx_ext_parse_handle_table;
    gg_comm_ext.ReceiveByteFunc = KerCommExtRxHandle;
    gg_comm_ext.CommParseFunc = KerCommExtParseHandle;
    gg_comm_ext.CommSendFunc = KerCommExtSend;
    gg_comm_ext.write_idx_of_parse_buffer = 0;
    gg_comm_ext.comm_status.comm_status_bits = 0;
    
    /* bind rx timeout timer handle */
    KerTimerBind(E_KER_TIMER_RX_TIMEOUT,KerCommExtRxTimeout);
    /* bind rx ack timeout timer handle */
    KerTimerBind(E_KER_TIMER_WAIT_ACK_TIMEOUT,KerCommExtWaitAckTimeout);
    
}



/* rx ext handle */
/* frame format: 0x02,cmd,Length(from next byte to last byte include crc16),......,Checksum(crc16) 0x03*/
static void KerCommExtRxHandle(T_U8 uch){
}



/* dwin parse handle */
static TE_COMM_RET_CODE KerCommExtParseHandle(T_U8 cmd,T_U8* p_data,T_U16 data_len)
{
    TE_KER_COMM_CMD_RX_EXT e_cmd;
    TE_COMM_RET_CODE comm_ret_code;

    T_U8 check_sum;

    M_Assert(p_data);

    e_cmd = (TE_KER_COMM_CMD_RX_EXT)cmd;

    if (e_cmd >= E_KER_COMM_CMD_RX_EXT_COUNT){
        return E_COMM_RET_UNKNOW_CMD;
    }

    if (data_len < 2){
        return E_COMM_RET_INVALID_PKT;
    }


    //------check crc

    check_sum = UtilityGenCheckSum(p_data,data_len-1);

    if (check_sum != p_data[data_len-1]){
        return E_COMM_RET_INVALID_CRC;
    }
    
    comm_ret_code = gg_comm_ext.p_parse_handle_table[cmd](cmd,p_data,data_len);
        
    return comm_ret_code;
}


static void KerCommExtSend(T_U8 cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack){
}



static void KerCommExtRxTimeout(TE_KER_TIMER_ID e_time_id){
    (void)e_time_id;
    gg_comm_ext.comm_status.comm_status_bits_struct.is_writing_parse_buffer = 0;
    gg_comm_ext.write_idx_of_parse_buffer = 0;
}


//receive dwin's ack timeout handle
static void KerCommExtWaitAckTimeout(TE_KER_TIMER_ID e_time_id){
    //T_U8 para = 0;
    #if 0
    if (1 == gg_comm_ext.is_wait_ack){
        if (gg_comm_ext.remain_retry_counts > 0){

            para = gg_comm_ext.cur_send_para;
            KerCommExtSend(gg_comm_ext.cur_send_cmd,&para,7,E_FALSE,E_TRUE);
        }
        else{
			
            KerCommSendOver(E_COMM_CHANNEL_EXT);
            
        }
    }
	#endif
        
}

