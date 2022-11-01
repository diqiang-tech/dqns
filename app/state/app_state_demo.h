#ifndef APP_STATE_DEMO_H
#define APP_STATE_DEMO_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../common/common.h"
#include "../../kernel/platform/stable/ker_timer.h"
#include "../../kernel/platform/stable/ker_msg.h"
#include "../../kernel/platform/stable/ker_fsm.h"
#include "../../kernel/platform/stable/ker_key.h"

void AppStateDemoInit(void);

#ifdef __cplusplus
}
#endif

#endif
