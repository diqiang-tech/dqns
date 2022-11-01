#ifndef UDM_DEVICE_TBL_H
#define UDM_DEVICE_TBL_H

#ifdef __cplusplus
extern "C"{
#endif

#include "udm_types.h"

/*<dqns_gen_device_h_begin>*/
#include "udm_key.h"
#include "udm_led.h"
#include "udm_dig.h"
#include "udm_pump.h"
/*<dqns_gen_device_h_end>*/

typedef enum{
    /*<dqns_gen_device_id_begin>*/
    E_UDM_DEVICE_KEY,    //key device
    E_UDM_DEVICE_LED,    //led device
    E_UDM_DEVICE_DIG,    //数码管
    E_UDM_DEVICE_PUMP,    //vacumm extractor pump
    /*<dqns_gen_device_id_end>*/
    E_UDM_DEVICE_CNT
}TE_UDM_DEVICE_ID;   

typedef void (*TFP_UDM_INIT)(void);
typedef TE_UDM_RET_CODE(*TFP_UDM_OPEN)(T_UDM_OPEN_MODE open_mode);
typedef TE_UDM_RET_CODE(*TFP_UDM_CLOSE)(void);
typedef TE_UDM_RET_CODE(*TFP_UDM_READ)(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
typedef TE_UDM_RET_CODE(*TFP_UDM_WRITE)(T_UDM_START_ADDR start_addr,T_UDM_LEN len,void * p_data);
typedef TE_UDM_RET_CODE(*TFP_UDM_IOCTL)(void * p_data);

typedef struct{
    TE_UDM_DEVICE_ID e_device_id;
    TE_BOOL e_already_open;
    void * p_ioctl_data;
    TFP_UDM_INIT p_fn_init;
    TFP_UDM_OPEN p_fn_open;
    TFP_UDM_CLOSE p_fn_close;
    TFP_UDM_READ p_fn_read;
    TFP_UDM_WRITE p_fn_write;
    TFP_UDM_IOCTL p_fn_ioctl;    
}TS_UDM_DEVICE;

TS_UDM_DEVICE * UdmDeviceObj(TE_UDM_DEVICE_ID e_device_id);

#ifdef __cplusplus
}
#endif

#endif