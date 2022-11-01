#ifndef APP_STATE_DEBUG_H
#define APP_STATE_DEBUG_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../common/common.h"
#include "../../kernel/platform/stable/ker_timer.h"
#include "../../kernel/platform/stable/ker_msg.h"
#include "../../kernel/platform/stable/ker_fsm.h"
#include "../../kernel/platform/stable/ker_key.h"

void AppStateDebugInit(void);

#ifdef __cplusplus
}
#endif

#endif
