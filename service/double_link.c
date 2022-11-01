#include "double_link.h"


/***********************************************
* Description: double link init
*
* Argument:
*   p_double_link:point to double link initi struct
*   size:capacity of the node array
*   p_node:node array address
*
* Return:
*
************************************************/
void DoubleLinkInit(TS_DOUBLE_LINK * p_double_link,T_U8 size,TS_DOUBLE_LINK_NODE * p_node){
    T_U8 i;
    
    M_Assert(p_double_link);
    M_Assert(p_node);

    for (i=0;i<size;i++){
        p_node[i].data = MAX_T_U32;
        p_node[i].prior = MAX_T_U8;
        p_node[i].next = MAX_T_U8;
    }

    p_double_link->count = 0;
    p_double_link->size = size;
    p_double_link->head_index = 0xFF;/* means null link */
    p_double_link->p_node = p_node;  /* static node array address */
}


/***********************************************
* Description:insert a node as a new first node
*
* Argument:
*   p_double_link:point to double link struct
*   data:node's data
*
* Return:if success will return data, if failure will return -1
*
************************************************/
T_U32 DoubleLinkInsert(TS_DOUBLE_LINK * p_double_link,T_U32 data){
    T_U8 index;
    T_U8 head_index;
    
    M_Assert(p_double_link);   

    if (p_double_link->count < p_double_link->size){
        /* find a node unused in node array */
        index = DoubleLinkNotUse(p_double_link);
        head_index = p_double_link->head_index;
        /* init new node */
        p_double_link->p_node[index].data = data;
        p_double_link->p_node[index].prior = MAX_T_U8; /* means first node */        
        p_double_link->p_node[index].next = head_index;
        /* if before have node in the link */
        if (head_index < p_double_link->size){
            p_double_link->p_node[head_index].prior = index;
        }
        p_double_link->head_index = index;

        /* node count ++ */
        p_double_link->count ++;

        return data;
    }

    return MAX_T_U32;
    
}


/***********************************************
* Description:delete a node
*
* Argument:
*   p_double_link:point to a double link struct
*   data:node's data
*
* Return:if success will return the node's data, if failure will return -1
*
************************************************/
T_U32 DoubleLinkDel(TS_DOUBLE_LINK * p_double_link,T_U32 data){
    T_U8 index;
    T_U8 temp_index;
    T_U32 return_data = MAX_T_U32;
    
    M_Assert(p_double_link);

    index = DoubleLinkFind(p_double_link,data);

    /* can't find the node you want to delete */
    if (0xFF == index){
        return MAX_T_U32;
    }

    /* this is a only node */
    if (p_double_link->p_node[index].prior == 0xFF &&
        p_double_link->p_node[index].next == 0xFF){
        return_data = p_double_link->p_node[index].data;
        p_double_link->p_node[index].data = MAX_T_U32;

        
    }
    /* this is the first node */
    else if (p_double_link->p_node[index].prior == 0xFF &&
             p_double_link->p_node[index].next != 0xFF){

        p_double_link->head_index = p_double_link->p_node[index].next;
        temp_index = p_double_link->p_node[index].next;
        p_double_link->head_index = temp_index;
        /* delete the node */
        return_data = p_double_link->p_node[index].data;
        p_double_link->p_node[index].data = MAX_T_U32;
        p_double_link->p_node[index].prior = MAX_T_U8;
        p_double_link->p_node[index].next = MAX_T_U8;

        
    }
    /* this is the tail node */
    else if (p_double_link->p_node[index].next == 0xFF &&
             p_double_link->p_node[index].prior < p_double_link->size){
        temp_index = p_double_link->p_node[index].prior;
        return_data = p_double_link->p_node[index].data;
        /* delete the node */    
        p_double_link->p_node[index].prior = MAX_T_U8;
        p_double_link->p_node[index].next = MAX_T_U8;
        p_double_link->p_node[index].data = MAX_T_U32;

        p_double_link->p_node[temp_index].next = MAX_T_U8;
    }
    /* normal node */
    else if (p_double_link->p_node[index].prior < p_double_link->size &&
             p_double_link->p_node[index].next < p_double_link->size &&
             p_double_link->p_node[index].data != MAX_T_U32){
        return_data = p_double_link->p_node[index].data;
        /* relink */
        temp_index = p_double_link->p_node[index].prior;
        p_double_link->p_node[temp_index].next = p_double_link->p_node[index].next;
        temp_index = p_double_link->p_node[index].next;
        p_double_link->p_node[temp_index].prior = p_double_link->p_node[index].prior;
        /* delete the node */
        p_double_link->p_node[index].prior = MAX_T_U8;
        p_double_link->p_node[index].next = MAX_T_U8;
        p_double_link->p_node[index].data = MAX_T_U32;
    }

    p_double_link->count -- ;
    return return_data;    
    
}



/***********************************************
* Description:find a node 
*
* Argument:
*   p_double_link:point to a double link struct
*   data:node's data
*
* Return:node 's index in the node array
*
************************************************/
T_U8 DoubleLinkFind(TS_DOUBLE_LINK * p_double_link,T_U32 data)
{
    T_U8 head_index;
    T_U8 index;
    T_U8 i;
    
    M_Assert(p_double_link);
    M_Assert(p_double_link->count <= p_double_link->size);    /* assure link logic is ok */
    //M_Assert(p_double_link->head_index < p_double_link->size);/* assure hade_index is not abnormal */
    M_Assert(data != MAX_T_U32);  /* -1 is reset status data,can't be used */

    if (p_double_link->count > 0){
        head_index = p_double_link->head_index;

        index = head_index;        

        for (i= 0;i<p_double_link->size;i++){
            if (p_double_link->p_node[index].data == data){
                return index;
            }
            /* already in the tail node ,so can't finde the node you want. */
            else if (MAX_T_U8 == p_double_link->p_node[index].next){
                return MAX_T_U8;
            }

            index = p_double_link->p_node[index].next;
        }        
    }
    
    return MAX_T_U8;
}



/***********************************************
* Description:find a index not be used in node array
*
* Argument:
*   p_double_link:point to double link struct
*
* Return:if failure will return 0xFF,if success will return index that you want.
*
************************************************/
T_U8 DoubleLinkNotUse(TS_DOUBLE_LINK * p_double_link){
    T_U8 i;

    M_Assert(p_double_link);

    if (p_double_link->count < p_double_link->size){
        for (i=0;i<p_double_link->size;i++){
            if (MAX_T_U32 == p_double_link->p_node[i].data){
                return i;
            }
        }
    }

    return MAX_T_U8;
}


/***********************************************
* Description:get the first node's data
*
* Argument:
*   p_double_link:point to double link struct
*
* Return:first node's data,if have no node will return -1
*
************************************************/
T_U32 DoubleLinkFirstData(TS_DOUBLE_LINK * p_double_link){
    T_U8 index;
    
    M_Assert(p_double_link);

    if (p_double_link->count > 0){
        index = p_double_link->head_index;
        return (p_double_link->p_node[index].data);
    }

    return MAX_T_U32;
}


T_U8 DoubleLinkNodeCount(TS_DOUBLE_LINK * p_double_link){
    M_Assert(p_double_link);

    return (p_double_link->count);
}



