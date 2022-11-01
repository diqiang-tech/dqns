#ifndef LOOP_QUEUE_H
#define LOOP_QUEUE_H

#ifdef __cplusplus 
extern "C"{
#endif


#include "../common/common.h"

/*------------- loop queue -------------  */
typedef struct
{
    T_U16 front;
    T_U16 rear;
    T_U16 size;  /* capacity */
    T_U16 count; /* current member count */
    void* p_buffer;
}TS_LOOP_QUEUE;


#define M_LoopQueuePut(p_loop_queue,data,data_type) do{\
    if (p_loop_queue->count < p_loop_queue->size){\
        ((data_type *)(p_loop_queue->p_buffer))[p_loop_queue->rear] = data;\
        p_loop_queue->rear = (p_loop_queue->rear + 1) % p_loop_queue->size;\
        p_loop_queue->count ++;\
    }\
    else{\
        ((data_type *)(p_loop_queue->p_buffer))[p_loop_queue->rear] = data;\
        p_loop_queue->rear = (p_loop_queue->rear + 1) % p_loop_queue->size;\
        p_loop_queue->front = (p_loop_queue->front + 1) % p_loop_queue->size;\
    }\
}while(0)


#define M_LoopQueueFront(p_loop_queue,p_data,data_type) do{\
        *(p_data) = ((data_type *)(p_loop_queue->p_buffer))[p_loop_queue->front];\
}while(0)

#define M_LoopQueueRear(p_loop_queue,p_data,data_type) do{\
        if (p_loop_queue->rear > 0){\
            * (p_data) = ((data_type *)(p_loop_queue->p_buffer))[p_loop_queue->rear-1];\
        }\
        else if (0 == p_loop_queue->rear){\
            * (p_data) = ((data_type *)(p_loop_queue->p_buffer))[p_loop_queue->size -1];\
        }\
}while(0)

    
void  LoopQueueInit(TS_LOOP_QUEUE *p_loop_queue,void* p_loop_queue_buffer,T_U16 size);
TE_BOOL LoopQueueIsEmpty(TS_LOOP_QUEUE *p_loop_queue);
TE_BOOL LoopQueueIsFull(TS_LOOP_QUEUE *p_loop_queue);
T_U8 LoopQueueItemCount(TS_LOOP_QUEUE *p_loop_queue);

#ifdef __cplusplus 
}
#endif


#endif

