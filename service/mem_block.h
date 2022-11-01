#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

#ifdef __cplusplus 
extern "C"{
#endif

#include "../common/common.h"

#define MAX_MEM_BLOCK_COUNTS    32

/*------------- mem block -------------  */
typedef struct
{
    T_U32 block_used_bits;
    T_U8 total_block_counts;
    T_U8 remain_block_counts;
    T_U16 every_block_bytes;
    void* p_mem_buffer;
}TS_MEM_BLOCK;


void  MemBlockInit(TS_MEM_BLOCK* p_mem_block,T_U8 total_block_counts,T_U16 every_block_bytes,void* p_mem_buffer);
void* MemBlockGet(TS_MEM_BLOCK* p_mem_block);
T_U8 MemBlockRelease(TS_MEM_BLOCK* p_mem_block,void* p_block);


#ifdef __cplusplus 
}
#endif


#endif

