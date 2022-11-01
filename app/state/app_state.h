#ifndef APP_STATE_H
#define APP_STATE_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../common/common.h"

#include "../../kernel/platform/stable/ker_fsm.h"

#include "app_state_x.h"
#include "app_state_idle.h"
#include "app_state_debug.h"
#include "app_state_abnormal.h"
#include "app_state_run.h"


void AppStateInit(void);

#ifdef __cplusplus
}
#endif


#endif


