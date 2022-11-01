#ifndef APP_STATE_RUN_SMART_H
#define APP_STATE_RUN_SMART_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../common/common.h"
#include "../../kernel/platform/stable/ker_timer.h"
#include "../../kernel/platform/stable/ker_msg.h"
#include "../../kernel/platform/stable/ker_fsm.h"
#include "../../kernel/platform/stable/ker_key.h"
#include "../../kernel/platform/stable/ker_pin.h"

#include "../../kernel/product/ker_dig.h"
#include "../../kernel/product/ker_pump.h"

void AppStateRunSmartInit(void);

#ifdef __cplusplus
}
#endif

#endif
