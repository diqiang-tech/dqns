#ifndef KER_ADC_H
#define KER_ADC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "ker_adc_user.h"

typedef struct{
    TE_BOOL need_scan;
    T_U16 period_counts;
    T_U16 cur_counts;
    T_ADC_VALUE adc_value;
    TFP_ADC_VOID read_func;
}TS_KER_ADC;


#define M_KerAdcInit(p_adc,scan_or_not,period,counts,value,func) do{\
    M_Assert(p_adc);\
    p_adc->need_scan = scan_or_not;\
    p_adc->period_counts = period;\
    p_adc->cur_counts = counts;\
    p_adc->adc_value = value;\
    p_adc->read_func = func;\
}while(0)


void KerAdcInit(void);
void KerAdcBatValueFirst(void);
T_ADC_VALUE KerAdcValue(TE_DRV_ADC_ID adc_id);
T_ADC_VALUE KerAdcTubeForceCalibration(void);
T_U8 KerAdcTubeForceCalibrationFlagGet(void);
void KerAdcTubeForceCalibrationFlagSet(T_U8 calibration_flag);
T_U8 KerAdcTubeForceCalibrationValueGet(void);
void KerAdcTubeForceCalibrationValueSet(T_U8 calibration_value);
T_U8 KerAdcTubeForceCalibrationReverseGet(void);
void KerAdcTubeForceCalibrationReverseSet(T_U8 calibration_reverse);
T_U8 KerAdcFctForceFlagGet(void);
T_U8 KerAdcFctForceValueGet(void);
T_U8 KerAdcFctForceCheckSumGet(void);
T_U8 KerAdcFctBatFlagGet(void);
T_U8 KerAdcFctBatValueGet(void);
T_U8 KerAdcFctBatCheckSumGet(void);








void KerAdcScanStart(void);
void KerAdcScanStop(void);
void KerAdcScanEnable(TE_DRV_ADC_ID adc_id);
void KerAdcScanDisable(TE_DRV_ADC_ID adc_id);
void KerAdcScanEnableAll(void);
void KerAdcScanDisableAll(void);
void KerAdcSetAdcMonitorHandle(TE_DRV_ADC_ID adc_id,TFP_VOID_VOID adc_monitor_func);

#ifdef __cplusplus
}
#endif


#endif

