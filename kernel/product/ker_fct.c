#include "ker_fct.h"
#include "../platform/stable/ker_msg.h"

void KerFctInit(void){
}
void KerFctRun(void){
    //fct测试ok
    KerMsgSend(E_KER_MSG_POST, (void*)(0));
}




