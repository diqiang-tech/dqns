
#ifndef KER_PIN_H
#define KER_PIN_H

#ifdef __cplusplus
extern "C"{
#endif


#include "../volatile/ker_pin_user.h"

typedef struct{
    T_U8 need_scan:1;
    T_U8 in_changing:1;
    T_U8 filter_count:4;
    T_U8 stable_status:1;
    T_U8 dynamic_status:1;
}TS_KER_PIN;




#define M_KerPinInit(p_pin,scan,changing,count,s_status,d_status) do{\
    M_Assert(p_pin);\
    p_pin->need_scan = scan;\
    p_pin->in_changing = changing;\
    p_pin->filter_count = count;\
    p_pin->stable_status = s_status;\
    p_pin->dynamic_status = d_status;\
}while(0)


void KerPinInit(void);

void KerPinScanStart(void);
void KerPinScanStop(void);
void KerPinScanEnable(TE_KER_PIN_ID pin_id);
void KerPinScanDisable(TE_KER_PIN_ID pin_id);
void KerPinScanEnableAll(void);
void KerPinScanDisableAll(void);

T_U8 KerPinStatus(TE_KER_PIN_ID pin_id);

void KerPinSetChangeHandle(TE_KER_PIN_ID pin_id,TFP_VOID_VOID pin_change_handle);

#ifdef __cplusplus
}
#endif


#endif

