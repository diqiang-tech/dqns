#ifndef KER_ADC_USER_H
#define KER_ADC_USER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "common.h"
#include "drv_adc.h"



#define KER_ADC_SCAN_MS    100
#define KER_ADC_BAT_VOLTAGE_PERIOD_MS   5000
#define KER_ADC_DRIVE_CURRENT_PERIOD_MS 1000


void KerAdcUserInit(void);

#ifdef __cplusplus
}
#endif


#endif

