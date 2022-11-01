#ifndef DOUBLE_LINK_H
#define DOUBLE_LINK_H

#ifdef __cplusplus 
extern "C"{
#endif


#include "../common/common.h"


/* static double link table */
typedef struct{
    T_U32 data;
    T_U8 prior;
    T_U8 next;
}TS_DOUBLE_LINK_NODE;

typedef struct{
    T_U8 count; /* current node count */
    T_U8 size;  /* correspond alarm count */
    T_U8 head_index; /* first node index in node array */
    TS_DOUBLE_LINK_NODE * p_node; /* node array */
}TS_DOUBLE_LINK;




void DoubleLinkInit(TS_DOUBLE_LINK * p_double_link,T_U8 size,TS_DOUBLE_LINK_NODE * p_node); 
T_U32 DoubleLinkInsert(TS_DOUBLE_LINK * p_double_link,T_U32 data);
T_U32 DoubleLinkDel(TS_DOUBLE_LINK * p_double_link,T_U32 data);
T_U8 DoubleLinkFind(TS_DOUBLE_LINK * p_double_link,T_U32 data);
T_U8 DoubleLinkNotUse(TS_DOUBLE_LINK * p_double_link);
T_U32 DoubleLinkFirstData(TS_DOUBLE_LINK * p_double_link);
T_U8 DoubleLinkNodeCount(TS_DOUBLE_LINK * p_double_link);


#ifdef __cplusplus 
}
#endif


#endif

