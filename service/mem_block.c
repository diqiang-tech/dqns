#include "mem_block.h"



void  MemBlockInit(TS_MEM_BLOCK* p_mem_block,T_U8 total_block_counts,T_U16 every_block_bytes,void* p_mem_buffer)
{    
    M_Assert(p_mem_block);
    M_Assert(p_mem_buffer);
    M_Assert(total_block_counts <= MAX_MEM_BLOCK_COUNTS);

    p_mem_block->block_used_bits = 0;
    p_mem_block->total_block_counts = total_block_counts;
    p_mem_block->remain_block_counts = total_block_counts;
    p_mem_block->every_block_bytes = every_block_bytes;
    p_mem_block->p_mem_buffer = p_mem_buffer;
    
}


void* MemBlockGet(TS_MEM_BLOCK* p_mem_block)
{
    T_U8 i;
    T_U32 block_used_bits;
    
    M_Assert(p_mem_block);

    
    block_used_bits = p_mem_block->block_used_bits;
    
    for (i=0;i<p_mem_block->total_block_counts;i++){
            
        if (((block_used_bits >> i)&1) == 0){

            //indicate this block has been used
            p_mem_block->block_used_bits |= (1<<i);
			p_mem_block->remain_block_counts -= 1;
                
            return ((void*)((T_S32)p_mem_block->p_mem_buffer + i*p_mem_block->every_block_bytes));
        }
    }

    return ((void*)0);
}

//normal :return block no; abnormal:return MAX_T_U8
T_U8 MemBlockRelease(TS_MEM_BLOCK* p_mem_block,void* p_block)
{
    T_U8 block_no;
    
    M_Assert(p_mem_block);
    M_Assert(p_block);
    M_Assert(p_block >= p_mem_block->p_mem_buffer);

    block_no = (((T_S32)p_block-(T_S32)(p_mem_block->p_mem_buffer)))/p_mem_block->every_block_bytes;

    //indicate this block has been released
    p_mem_block->block_used_bits &= (~(1<<block_no));

    if (block_no < p_mem_block->total_block_counts){
		p_mem_block->remain_block_counts += 1;
        return block_no;
    }

    return MAX_T_U8;
}

