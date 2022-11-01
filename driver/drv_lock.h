#ifndef DRV_LOCK_H
#define DRV_LOCK_H

#ifdef __cplusplus
extern "C"{
#endif


#include "../common/common.h"

void DrvLockInit(void);
T_U8 DrvLockStatus(void);

#ifdef __cplusplus
}
#endif



#endif


