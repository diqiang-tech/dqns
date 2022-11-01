#include "ker_msg_user.h"


static TS_RING_QUEUE g_msg_ring_queue;
static TS_KER_MSG g_msg_ring_queue_buffer[KER_MSG_RING_QUEUE_SIZE];
static TFP_MSG_FUNC g_msg_func_table[E_KER_MSG_COUNT];

static TS_MSG_PUMP g_msg_pump;

void KerMsgUserInit(void){

    RingQueueInit(&g_msg_ring_queue,g_msg_ring_queue_buffer,KER_MSG_RING_QUEUE_SIZE);
    g_msg_pump.msg_count = E_KER_MSG_COUNT;
    g_msg_pump.p_msg_ring_queue = &g_msg_ring_queue;
    g_msg_pump.pp_msg_func = g_msg_func_table;

}

TS_MSG_PUMP * KerMsgUserMsgPumpObj(void){

    return (&g_msg_pump);
}

