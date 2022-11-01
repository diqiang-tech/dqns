#ifndef KER_KEY_H
#define KER_KEY_H

#ifdef __cplusplus
extern "C"{
#endif 

#include "../volatile/ker_key_user.h"

/* external functions */
void KerKeyInit(void);
void KerKeyScanStart(void);
void KerKeyScanStop(void);
void KerKeyBind(TE_KER_KEYS e_key,TE_KER_KEY_MSG_TYPE e_key_msg_type,TFP_KEY_HANDLE key_handle_func);
void KerKeyCombineBind(TE_KER_COMBINE_KEYS e_combine_key,TFP_KEY_HANDLE key_handle_func);
void KerKeyCleanAllHandle(void);

#ifdef __cplusplus
}
#endif 

#endif

