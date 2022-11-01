#include "stack.h"

void  StackInit(TS_STACK* p_stack,void* p_stack_buffer,T_U8 size)
{    
    M_Assert(p_stack);
    M_Assert(p_stack_buffer);

    p_stack->sp = 0;
    p_stack->size = size;    
    p_stack->p_buffer = p_stack_buffer;        
    
}

/***********************************************
* Description:
*
*       Inorder to adjust is stack empty or not.
*
* Prototype:    StackIsEmpty
*
* Argument:
*
*       p_stack: point to stack data structure
*   
* 
* Return:TE_BOOL
*    
*    E_TRUE:means stack is empty
*    E_FALSE:means stack is not empty
*
*
* END OF FUNCTION HEADER
************************************************/
TE_BOOL StackIsEmpty(TS_STACK* p_stack)
{
    M_Assert(p_stack);
    
    if (0 == p_stack->sp){
        return E_TRUE;
    }

    return E_FALSE;
}

/***********************************************
* Description:
*
*       Inorder to adjust is stack full or not.
*
* Prototype:    StackIsFull
*
* Argument:
*
*       p_stack: point to stack data structure
*   
* 
* Return:TE_BOOL
*    
*    E_TRUE:means stack is full
*    E_FALSE:means stack is not full
*
*
* END OF FUNCTION HEADER
************************************************/
TE_BOOL StackIsFull(TS_STACK* p_stack)
{ 
    M_Assert(p_stack);
    
    if (p_stack->size == p_stack->sp){
        return E_TRUE;
    }

    return E_FALSE;
}


