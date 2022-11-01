#include "loop_queue.h"


/***********************************************
* Description:
*
*    Initialize loop queue.
*
* Prototype:    LoopQueueInit
*
* Argument:
*
*    p_loop_queue: point to loop queue data structure
*    p_loop_queue_buffer:point to loop queue buffer
*    size:size of loop queue buffer
*   
* Return:void
*
* END OF FUNCTION HEADER
************************************************/
void LoopQueueInit(TS_LOOP_QUEUE *p_loop_queue,void* p_loop_queue_buffer,T_U16 size)
{    
    M_Assert(p_loop_queue);
    M_Assert(p_loop_queue_buffer);

    p_loop_queue->front = 0;
    p_loop_queue->rear = 0;
    p_loop_queue->size = size;
    p_loop_queue->count = 0;
    p_loop_queue->p_buffer = p_loop_queue_buffer;
	memset(p_loop_queue_buffer,0,size);
        
    
}

/***********************************************
* Description:
*
*       In order to adjust is a loop queue empty.
*
* Prototype:    LoopQueueIsEmpty
*
* Argument:
*
*       p_loop_queue: point to loop queue data structure
* 
* Return:TE_BOOL
*
*       E_TRUE:means loop queue is empty
*       E_FALSE:means loop queue is not empty
*
* END OF FUNCTION HEADER
************************************************/
TE_BOOL LoopQueueIsEmpty(TS_LOOP_QUEUE *p_loop_queue)
{
    M_Assert(p_loop_queue);
    
    if (p_loop_queue->front == p_loop_queue->rear &&
        0 == p_loop_queue->count){
        return E_TRUE;
    }

    return E_FALSE;
}

/***********************************************
* Description:
*
*       In order to adjust is a loop queue full.
*
* Prototype:    LoopQueueIsFull
*
* Argument:
*
*       p_loop_queue: point to loop queue data structure
* 
* Return:TE_BOOL
*
*       E_TRUE:means loop queue is full
*       E_FALSE:means loop queue is not full
*
* END OF FUNCTION HEADER
************************************************/

TE_BOOL LoopQueueIsFull(TS_LOOP_QUEUE *p_loop_queue)
{ 
    M_Assert(p_loop_queue);
    
    if (p_loop_queue->front == p_loop_queue->rear &&
        p_loop_queue->size == p_loop_queue->count){
        return E_TRUE;
    }

    return E_FALSE;
}

/***********************************************
* Description:
*
*       In order to get loop queue's item count, max value is size
*
* Prototype:    LoopQueueItemCount
*
* Argument:
*
*       p_loop_queue: point to loop queue data structure
* 
* Return:T_U8
*
*       indicate loop queue's item count ,the max value is loop queue's size
*
* END OF FUNCTION HEADER
************************************************/
T_U8 LoopQueueItemCount(TS_LOOP_QUEUE *p_loop_queue)
{
    M_Assert(p_loop_queue);

    return (p_loop_queue->count);
}


