#include "drv_eeprom.h"

#include "ker_msg.h"
#include "ker_timer.h"
#include "ker_adc.h"
#include "ker_log.h"


extern TS_KER_ADC* cgg_adc_tbl[];

static TFP_VOID_VOID g_adc_monitor_handle[E_DRV_ADC_ID_COUNT];


static void KerAdcScanTimerHandle(TE_KER_TIMER_ID timer_id);
static TE_BOOL KerAdcNeedCareAdcMsgHandle(void* param);


void KerAdcInit(void)
{
    KerAdcUserInit();

    /* bind adc scan handle */
    KerTimerBind(E_KER_TIMER_ADC_SCAN,KerAdcScanTimerHandle);

    /* bind care adc msg handle */
    KerMsgBind(E_KER_MSG_NEED_CARE_ADC,KerAdcNeedCareAdcMsgHandle);
}
// 用于获取静态电压
void KerAdcBatValueFirst(void)
{
	DrvAdcBatFirst();
}

T_ADC_VALUE KerAdcValue(TE_DRV_ADC_ID adc_id)
{
    M_Assert(adc_id < E_DRV_ADC_ID_COUNT);

    T_ADC_VALUE adc_value;

    adc_value = cgg_adc_tbl[adc_id]->read_func();
    return adc_value;
}

T_ADC_VALUE KerAdcTubeForceCalibration(void)
{
	T_ADC_VALUE adc_value;
	adc_value = DrvAdcTubeForceCalibration();
	return adc_value;
}

T_U8 KerAdcTubeForceCalibrationFlagGet(void)
{
	T_U8 calibration_flag = 0;
	calibration_flag = DrvAdcTubeForceCalibrationFlagGet();
	return calibration_flag;
}
void KerAdcTubeForceCalibrationFlagSet(T_U8 calibration_flag)
{
	DrvAdcTubeForceCalibrationFlagSet(calibration_flag);
}

T_U8 KerAdcTubeForceCalibrationValueGet(void)
{
	T_U8 calibration_value = 0;
	calibration_value = DrvAdcTubeForceCalibrationValueGet();
	return calibration_value;
}
void KerAdcTubeForceCalibrationValueSet(T_U8 calibration_value)
{
	DrvAdcTubeForceCalibrationValueSet(calibration_value);
}

T_U8 KerAdcTubeForceCalibrationReverseGet(void)
{
	T_U8 calibration_reverse = 0;
	calibration_reverse = DrvAdcTubeForceCalibrationReverseGet();
	return calibration_reverse;
}
void KerAdcTubeForceCalibrationReverseSet(T_U8 calibration_reverse)
{
	DrvAdcTubeForceCalibrationReverseSet(calibration_reverse);
}


T_U8 KerAdcFctForceFlagGet()
{
	T_U8 fct_force_flag = 0;
	fct_force_flag = DrvAdcFctForceFlagGet();
	return fct_force_flag;
}

T_U8 KerAdcFctForceValueGet()
{
	T_U8 fct_force_value = 0;
	fct_force_value = DrvAdcFctForceValueGet();
	return fct_force_value;
}

T_U8 KerAdcFctForceCheckSumGet()
{
	T_U8 fct_force_checksum = 0;
	fct_force_checksum = DrvAdcFctForceCheckSumGet();
	return fct_force_checksum;
}

T_U8 KerAdcFctBatFlagGet()
{
	T_U8 fct_bat_flag = 0;
	fct_bat_flag = DrvAdcFctBatFlagGet();
	return fct_bat_flag;
}

T_U8 KerAdcFctBatValueGet()
{
	T_U8 fct_bat_value = 0;
	fct_bat_value = DrvAdcFctBatValueGet();
	return fct_bat_value;
}

T_U8 KerAdcFctBatCheckSumGet()
{
    T_U8 fct_bat_checksum = 0;
	fct_bat_checksum = DrvAdcFctBatCheckSumGet();
	return fct_bat_checksum;
}


void KerAdcScanStart(void)
{
    KerTimerSetPeriod(E_KER_TIMER_ADC_SCAN,KER_ADC_SCAN_MS);
}

void KerAdcScanStop(void)
{
    KerTimerDisable(E_KER_TIMER_ADC_SCAN);
}

void KerAdcScanEnable(TE_DRV_ADC_ID adc_id)
{
    M_Assert(adc_id < E_DRV_ADC_ID_COUNT);
    cgg_adc_tbl[adc_id]->need_scan = E_TRUE;

    cgg_adc_tbl[adc_id]->cur_counts = cgg_adc_tbl[adc_id]->period_counts;
}

void KerAdcScanDisable(TE_DRV_ADC_ID adc_id)
{    
    M_Assert(adc_id < E_DRV_ADC_ID_COUNT);
    cgg_adc_tbl[adc_id]->need_scan = E_FALSE;

    cgg_adc_tbl[adc_id]->cur_counts = cgg_adc_tbl[adc_id]->period_counts;
}

void KerAdcScanEnableAll(void)
{
    int adc_idx = 0;

    for (adc_idx = 0;adc_idx < E_DRV_ADC_ID_COUNT; adc_idx++){
        cgg_adc_tbl[adc_idx]->need_scan = E_TRUE;

        cgg_adc_tbl[adc_idx]->cur_counts = cgg_adc_tbl[adc_idx]->period_counts;
    }
}

void KerAdcScanDisableAll(void)
{
    int adc_idx = 0;

    for (adc_idx = 0;adc_idx < E_DRV_ADC_ID_COUNT; adc_idx++){
        cgg_adc_tbl[adc_idx]->need_scan = E_FALSE;

        cgg_adc_tbl[adc_idx]->cur_counts = cgg_adc_tbl[adc_idx]->period_counts;
    }
}

void KerAdcSetAdcMonitorHandle(TE_DRV_ADC_ID adc_id,TFP_VOID_VOID adc_monitor_func)
{
    M_Assert(adc_id < E_DRV_ADC_ID_COUNT);
    M_Assert(adc_monitor_func);

    g_adc_monitor_handle[adc_id] = adc_monitor_func;
}


static void KerAdcScanTimerHandle(TE_KER_TIMER_ID timer_id)
{
    (void)timer_id;
    
    int adc_idx = 0;

    DrvAdcStartConvert();

    for (adc_idx = 0;adc_idx < E_DRV_ADC_ID_COUNT; adc_idx++){
        if (E_TRUE == cgg_adc_tbl[adc_idx]->need_scan){
            if (cgg_adc_tbl[adc_idx]->cur_counts){
                cgg_adc_tbl[adc_idx]->cur_counts--;

                if (0 == cgg_adc_tbl[adc_idx]->cur_counts){
                    cgg_adc_tbl[adc_idx]->cur_counts = cgg_adc_tbl[adc_idx]->period_counts;
                    cgg_adc_tbl[adc_idx]->adc_value = cgg_adc_tbl[adc_idx]->read_func();
                    KerMsgSend(E_KER_NEED_CARE_ADC,(void*)adc_idx);
                }
            }           
           
        }
    }
}

static TE_BOOL KerAdcNeedCareAdcMsgHandle(void* param)
{
    int adc_id = (int)param;

    M_Assert(adc_id < E_DRV_ADC_ID_COUNT);

    if (g_adc_monitor_handle[adc_id]){
        g_adc_monitor_handle[adc_id]();
    }
    
    return E_TRUE;
}

