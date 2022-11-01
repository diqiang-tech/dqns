#ifndef KER_PIN_USER_H
#define KER_PIN_USER_H

#ifdef __cplusplus
extern "C"{
#endif


#include "../../../common/common.h"



//debug pin status
#define PIN_STATUS_DebugDisable 0
#define PIN_STATUS_DebugEnable  1

//lock pin status
#define PIN_STATUS_LockDisable 0
#define PIN_STATUS_LockEnable 1

#define KER_PIN_SCAN_MS     20


/* ------------- pin status filter count ------------- */
#define PIN_DebugStatus_FILTER_COUNT       5
#define PIN_LockStatus_FILTER_COUNT      5


typedef enum{    
    E_KER_PIN_DebugStatus,
    E_KER_PIN_LockStatus,
    E_KER_PIN_COUNT
}TE_KER_PIN_ID;


#if 0
extern TS_KER_IO_PIN* gg_io_pin_tbl[];
extern TFP_U8_VOID gg_io_pin_read_func_tbl[];
extern const T_U8 gg_io_pin_filter_count_tbl[];

extern TS_KER_IO_PORT* gg_io_port_tbl[];
extern TFP_U8_VOID gg_io_port_read_func_tbl[];
extern const T_U8 gg_io_port_filter_count_tbl[];
#endif

void KerPinUserInit(void);

#ifdef __cplusplus
}
#endif

#endif

