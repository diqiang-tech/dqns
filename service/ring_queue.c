#include "ring_queue.h"

void RingQueueInit(TS_RING_QUEUE *p_ring_queue,void* p_ring_queue_buffer,T_U8 size)
{    
    M_Assert(p_ring_queue);
    M_Assert(p_ring_queue_buffer);

    p_ring_queue->front = 0;
    p_ring_queue->rear = 0;
    p_ring_queue->size = size;
    p_ring_queue->count = 0;
    p_ring_queue->p_buffer = p_ring_queue_buffer;
        
    
}

/***********************************************
* Description:
*
*       In order to adjust is a ring queue empty.
*
* Prototype:    RingQueueIsEmpty
*
* Argument:
*
*       p_ring_queue: point to ring queue data structure
* 
* Return:TE_BOOL
*
*       E_TRUE:means ring queue is empty
*       E_FALSE:means ring queue is not empty
*
* END OF FUNCTION HEADER
************************************************/
TE_BOOL RingQueueIsEmpty(TS_RING_QUEUE *p_ring_queue)
{
    M_Assert(p_ring_queue);
    
    if (p_ring_queue->front == p_ring_queue->rear){
        return E_TRUE;
    }

    return E_FALSE;
}

/***********************************************
* Description:
*
*       In order to adjust is a ring queue full.
*
* Prototype:    RingQueueIsFull
*
* Argument:
*
*       p_ring_queue: point to ring queue data structure
* 
* Return:TE_BOOL
*
*       E_TRUE:means ring queue is full
*      E_FALSE:means ring queue is not full
*
* END OF FUNCTION HEADER
************************************************/

TE_BOOL RingQueueIsFull(TS_RING_QUEUE *p_ring_queue)
{ 
    M_Assert(p_ring_queue);
    
    if (((p_ring_queue->rear+1) % p_ring_queue->size) == p_ring_queue->front){
        return E_TRUE;
    }

    return E_FALSE;
}


