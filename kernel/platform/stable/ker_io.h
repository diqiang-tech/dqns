
#ifndef KER_IO_H
#define KER_IO_H

#ifdef __cplusplus
extern "C"{
#endif


#include "ker_io_user.h"

typedef struct{
    T_U8 need_scan:1;
    T_U8 in_changing:1;
    T_U8 filter_count:4;
    T_U8 stable_status:1;
    T_U8 dynamic_status:1;
}TS_KER_IO_PIN;

typedef struct{
    T_U32 need_scan:1;
    T_U32 in_changing:1;
    T_U32 filter_count:14;
    T_U32 stable_value:8;
    T_U32 dynamic_value:8;
}TS_KER_IO_PORT;


#define M_KerIOPinInit(p_io_pin,scan,changing,count,s_status,d_status) do{\
    M_Assert(p_io_pin);\
    p_io_pin->need_scan = scan;\
    p_io_pin->in_changing = changing;\
    p_io_pin->filter_count = count;\
    p_io_pin->stable_status = s_status;\
    p_io_pin->dynamic_status = d_status;\
}while(0)


#define M_KerIOPortInit(p_io_port,scan,changing,count,s_value,d_value) do{\
    M_Assert(p_io_port);\
    p_io_port->need_scan = scan;\
    p_io_port->in_changing = changing;\
    p_io_port->filter_count = count;\
    p_io_port->stable_value = s_value;\
    p_io_port->dynamic_value = d_value;\
}while(0)

void KerIOInit(void);

void KerIOPinScanStart(void);
void KerIOPinScanStop(void);
void KerIOPinScanEnable(TE_KER_IO_PIN_ID io_pin_id);
void KerIOPinScanDisable(TE_KER_IO_PIN_ID io_pin_id);
void KerIOPinScanEnableAll(void);
void KerIOPinScanDisableAll(void);

void KerIOPortScanStart(void);
void KerIOPortScanStop(void);
void KerIOPortScanEnable(TE_KER_IO_PORT_ID io_port_id);
void KerIOPortScanDisable(TE_KER_IO_PORT_ID io_port_id);
void KerIOPortScanEnableAll(void);
void KerIOPortScanDisableAll(void);


T_U8 KerIOPinStatus(TE_KER_IO_PIN_ID io_pin_id);
T_U8 KerIOPortValue(TE_KER_IO_PORT_ID io_port_id);

void KerIOSetPinChangeHandle(TE_KER_IO_PIN_ID io_pin_id,TFP_VOID_VOID pin_change_handle);
void KerIOSetPortChangeHandle(TE_KER_IO_PORT_ID io_port_id,TFP_VOID_VOID port_change_handle);


#ifdef __cplusplus
}
#endif


#endif

