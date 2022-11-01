
#ifndef INIT_H
#define INIT_H

#ifdef __cplusplus
extern "C"{
#endif



/* ------ include head files for driver layer ------ */
#include "../driver/drv_debug.h"
#include "../driver/drv_lock.h"


/* ------ include head files for kernel layer of platform ------ */
#include "../kernel/platform/stable/ker_pin.h"
#include "../kernel/platform/stable/ker_timer.h"
#include "../kernel/platform/stable/ker_msg.h"
#include "../kernel/platform/stable/ker_key.h"
#include "../kernel/platform/stable/ker_fsm.h"
#include "../kernel/platform/stable/ker_comm.h"

/* ------ include head files for kernel layer of product ------ */
#include "../kernel/product/ker_dig.h"
#include "../kernel/product/ker_fct.h"
#include "../kernel/product/ker_pump.h"



/* ------ include head files for udm ------ */
#include "../udm/stable/udm_api.h"


/* ------ include head files for ui ------ */



/* ------ include head files for application layer ------ */
#include "../app/state/app_state.h"


void Init(void);

#ifdef __cplusplus
}
#endif


#endif

