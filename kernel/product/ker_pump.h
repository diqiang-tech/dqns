#ifndef KER_PUMP_H
#define KER_PUMP_H

#ifdef __cplusplus
extern "C"{
#endif


#include "../../common/common.h"

typedef enum{
    E_KER_PUMP_LEVEL_1,
    E_KER_PUMP_LEVEL_2,
    E_KER_PUMP_LEVEL_3,
    E_KER_PUMP_LEVEL_COUNT,
}TE_KER_PUMP_LEVEL;

typedef enum{
    E_KER_PUMP_MODE_NORMAL,
    E_KER_PUMP_MODE_SMART,
    E_KER_PUMP_MODE_COUNT,
}TE_KER_PUMP_MODE;

void KerPumpInit(void);
void KerPumpRun(void);
void KerPumpStop(void);
TE_BOOL KerPumpIsRun(void);
void KerPumpSetLevel(TE_KER_PUMP_LEVEL e_pump_level);
void KerPumpSwitchLevel(void);
TE_KER_PUMP_LEVEL KerPumpLevel(void);
void KerPumpSetMode(TE_KER_PUMP_MODE e_pump_mode);
void KerPumpSwitchMode(void);
TE_KER_PUMP_MODE KerPumpMode(void);




#ifdef __cplusplus
}
#endif



#endif


