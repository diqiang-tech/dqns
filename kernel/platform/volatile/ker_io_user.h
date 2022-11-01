#ifndef KER_IO_USER_H
#define KER_IO_USER_H

#ifdef __cplusplus
extern "C"{
#endif


#include "common.h"



//left ear pin status
#define IO_PIN_STATUS_LeftEarClose 0
#define IO_PIN_STATUS_LeftEarOpen  1

//right ear pin status
#define IO_PIN_STATUS_RightEarClose 0
#define IO_PIN_STATUS_RightEarOpen  1

//pca pin status
#define IO_PIN_STATUS_PcaConnect    0
#define IO_PIN_STATUS_PcaDisconnect 1



#define KER_IO_PIN_SCAN_MS     20
#define KER_IO_PORT_SCAN_MS    5

/* ------------- pin status filter count ------------- */
#define IO_PIN_LeftEarStatus_FILTER_COUNT       5
#define IO_PIN_RightEarStatus_FILTER_COUNT      5
#define IO_PIN_PcaConnectStatus_FILTER_COUNT    5


/* ------------- port status filter count ------------- */
#define IO_PORT_CAM_FILTER_COUNT  4

typedef enum{    
    E_IO_PIN_LeftEarStatus,
    E_IO_PIN_RightEarStatus,
    E_IO_PIN_PcaConnectStatus,
    
    E_KER_IO_PIN_COUNT
}TE_KER_IO_PIN_ID;

typedef enum{
    E_KER_IO_PORT_CAM,
        
    E_KER_IO_PORT_COUNT
}TE_KER_IO_PORT_ID;



#if 0
extern TS_KER_IO_PIN* gg_io_pin_tbl[];
extern TFP_U8_VOID gg_io_pin_read_func_tbl[];
extern const T_U8 gg_io_pin_filter_count_tbl[];

extern TS_KER_IO_PORT* gg_io_port_tbl[];
extern TFP_U8_VOID gg_io_port_read_func_tbl[];
extern const T_U8 gg_io_port_filter_count_tbl[];
#endif

void KerIOUserInit(void);

#ifdef __cplusplus
}
#endif

#endif

