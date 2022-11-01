#ifndef RING_QUEUE_H
#define RING_QUEUE_H

#ifdef __cplusplus 
extern "C"{
#endif


#include "../common/common.h"

/*------------- ring queue -------------  */
typedef struct
{
    T_U8 front;
    T_U8 rear;
    T_U8 size;  /* capacity */
    T_U8 count; /* current member count */
    void* p_buffer;
}TS_RING_QUEUE;


#define M_RingQueuePut(p_ring_queue,data,data_type) do{\
    ((data_type *)(p_ring_queue->p_buffer))[p_ring_queue->rear] = data;\
    p_ring_queue->rear = (p_ring_queue->rear + 1) % p_ring_queue->size;\
}while(0)

#define M_RingQueuePuts(p_ring_queue,data_buffer,data_len,data_type) do{\
    memcpy(&( ((data_type *)(p_ring_queue->p_buffer))[p_ring_queue->rear] ),data_buffer,data_len*sizeof(data_type));\
    p_ring_queue->rear = (p_ring_queue->rear + data_len) % p_ring_queue->size;\
}while(0)

    
#define M_RingQueueGet(p_ring_queue,p_data,data_type) do{\
    * (p_data) = ((data_type *)(p_ring_queue->p_buffer))[p_ring_queue->front];\
    p_ring_queue->front = (p_ring_queue->front +1) % p_ring_queue->size;\
}while(0)



void  RingQueueInit(TS_RING_QUEUE *p_ring_queue,void* p_ring_queue_buffer,T_U8 size);
TE_BOOL RingQueueIsEmpty(TS_RING_QUEUE *p_ring_queue);
TE_BOOL RingQueueIsFull(TS_RING_QUEUE *p_ring_queue);

#ifdef __cplusplus 
}
#endif


#endif

