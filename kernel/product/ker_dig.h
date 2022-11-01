#ifndef KER_DIG_H
#define KER_DIG_H

#ifdef __cplusplus
extern "C"{
#endif


#include "../../common/common.h"

#define KER_DIG_FRESH_PERIOD_MS 200
#define KER_DIG_RETURN_ONCE_MS 3000
typedef enum{
    E_KER_DIG_SHOW_NONE,
    E_KER_DIG_SHOW_POST,
    E_KER_DIG_SHOW_PRESSURE,
    E_KER_DIG_SHOW_EQ,
    E_KER_DIG_SHOW_LEVEL,
    E_KER_DIG_SHOW_ERROR,
    E_KER_DIG_SHOW_DEBUG,
    E_KER_DIG_SHOW_COUNT,
}TE_KER_DIG_SHOW_TYPE;

void KerDigInit(void);
void KerDigShow(TE_KER_DIG_SHOW_TYPE e_dig_show_type);
void KerDigShowPre(void);
TE_KER_DIG_SHOW_TYPE KerDigShowType(void);
TE_KER_DIG_SHOW_TYPE KerDigPreShowType(void);


#ifdef __cplusplus
}
#endif



#endif


