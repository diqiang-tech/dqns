#ifndef UDM_TYPES_H
#define UDM_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../common/c_defs.h"

#define UDM_OPEN_MODE_R    1
#define UDM_OPEN_MODE_W 2
#define UDM_OPEN_MODE_RW 3

typedef T_U8 T_UDM_DEVICE_HANDLE;
typedef T_U8 T_UDM_START_ADDR;
typedef T_U8 T_UDM_LEN;
typedef T_U8 T_UDM_OPEN_MODE;


typedef enum{
    E_UDM_OK,
    E_UDM_ERROR_NOT_EXIST,
    E_UDM_ERROR_BUSY,
}TE_UDM_RET_CODE;


#ifdef __cplusplus
}
#endif

#endif