#include "ker_comm_pc.h"
#include "../stable/ker_comm.h"
#include "../stable/ker_timer.h"

/* ------ rx pc ring queue buffer ------ */
static T_U8 g_rx_pc_buffer[KER_COMM_RX_PC_RING_QUEUE_SIZE];
/* ------ ring queue ------ */
static TS_RING_QUEUE g_rx_pc_ring_queue;

/* ------ rx pc parse buffer ------ */
static T_U8 g_rx_pc_parse_buffer[KER_COMM_RX_PC_PARSE_BUFFER_SIZE];

/* ------ rx pc cmd parse table ------ */
static TFP_KER_COMM_PARSE_HANDLE g_rx_pc_parse_handle_table[E_KER_COMM_CMD_RX_PC_COUNT];

/* ------ pc comm information structure ------ */
TS_KER_COMM_INFO gg_comm_pc;

/* ------ rx handle ------ */
static void KerCommPcRxHandle(T_U8 uch);

/* ------ parse handle ------ */
static TE_COMM_RET_CODE KerCommPcParseHandle(T_U8 cmd,T_U8* p_data,T_U16 data_len);

/* ------ send func ------ */
static void KerCommPcSend(T_U8 cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack);

/* ------ rx timeout timer handle ------ */
static void KerCommPcRxTimeout(TE_KER_TIMER_ID e_time_id);

/* ------ wait ack timeout timer handle ------ */
static void KerCommPcWaitAckTimeout(TE_KER_TIMER_ID e_time_id);

void KerCommPcInit(void){
    /* init ring queue */
    RingQueueInit(&g_rx_pc_ring_queue,(void*)g_rx_pc_buffer,KER_COMM_RX_PC_RING_QUEUE_SIZE);

    /* init comm obj */
    gg_comm_pc.p_ring_queue = (&g_rx_pc_ring_queue);
    gg_comm_pc.parse_buffer = g_rx_pc_parse_buffer;
    gg_comm_pc.p_parse_handle_table = g_rx_pc_parse_handle_table;
    gg_comm_pc.ReceiveByteFunc = KerCommPcRxHandle;
    gg_comm_pc.CommParseFunc = KerCommPcParseHandle;
    gg_comm_pc.CommSendFunc = KerCommPcSend;
    gg_comm_pc.write_idx_of_parse_buffer = 0;
    gg_comm_pc.comm_status.comm_status_bits = 0;

    /* bind rx timeout timer handle */
    KerTimerBind(E_KER_TIMER_RX_PC_TIMEOUT,KerCommPcRxTimeout);
    /* bind rx ack timeout timer handle */
    KerTimerBind(E_KER_TIMER_WAIT_PC_ACK_TIMEOUT,KerCommPcWaitAckTimeout);
}

static void KerCommPcRxHandle(T_U8 uch){
    
}

static TE_COMM_RET_CODE KerCommPcParseHandle(T_U8 cmd,T_U8* p_data,T_U16 data_len){
    return E_COMM_RET_OK;
    
}

static void KerCommPcSend(T_U8 cmd,T_U8* p_data,T_U16 data_len,TE_BOOL need_ack){
    
}

static void KerCommPcRxTimeout(TE_KER_TIMER_ID e_time_id){
    (void)e_time_id;
    
}

static void KerCommPcWaitAckTimeout(TE_KER_TIMER_ID e_time_id){
    (void)e_time_id;
    
}
