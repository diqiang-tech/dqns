#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus 
extern "C"{
#endif

#include "../common/common.h"

/*------------- stack -------------  */
typedef struct
{
    T_U8 sp;    
    T_U8 size;  /* capacity */    
    void* p_buffer;
}TS_STACK;

#define M_StackPush(p_stack,data,data_type) do{\
    ((data_type *)(p_stack->p_buffer))[p_stack->sp++] = data;\
}while(0)


#define M_StackPop(p_stack,p_data,data_type) do{\
    * (p_data) = ((data_type *)(p_stack->p_buffer))[--p_stack->sp];\
}while(0)


void  StackInit(TS_STACK* p_stack,void* p_stack_buffer,T_U8 size);
TE_BOOL StackIsEmpty(TS_STACK* p_stack);
TE_BOOL StackIsFull(TS_STACK* p_stack);

#ifdef __cplusplus 
}
#endif


#endif

