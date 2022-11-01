#include "ker_adc.h"
#include "ker_adc_user.h"

static TS_KER_ADC g_adc_tube_force;
static TS_KER_ADC g_adc_bat;
static TS_KER_ADC g_adc_bat_ds1302;
static TS_KER_ADC g_adc_drive_current;


TS_KER_ADC* cgg_adc_tbl[]={    
    &g_adc_tube_force,    // E_DRV_ADC_ID_BAT_VOLTAGE 
    &g_adc_bat,           // E_ADC_TUBE_FORCEE_ADC_MOTOR_DRIVE_CURRENT
    &g_adc_bat_ds1302,    // E_DRV_ADC_ID_DS1302_BAT_VOLTAGE 
    &g_adc_drive_current  //E_DRV_ADC_ID_MOTOR_DRIVE_CURRENT
};

#if 0
#define KER_ADC_SCAN_MS    100
#define KER_ADC_BAT_VOLTAGE_PERIOD_MS   5000
#define KER_ADC_DRIVE_CURRENT_PERIOD_MS 1000
#endif

void KerAdcUserInit(void)
{    
    M_KerAdcInit((&g_adc_tube_force),E_FALSE,0,0,0,DrvAdcTubeForce);   
    M_KerAdcInit((&g_adc_bat),E_FALSE,10,0,0,DrvAdcBat);
    M_KerAdcInit((&g_adc_bat_ds1302),E_FALSE,50,50,0,DrvAdcBatDS1302);
    M_KerAdcInit((&g_adc_drive_current),E_FALSE,10,10,0,DrvAdcDriveCurrent);    
    
}

