#include "ker_timer_user.h"

static TS_KER_TIMER g_timer_list[E_KER_TIMER_COUNT];


TS_KER_TIMER * KerTimerUserGetTimerList(void){
    
    return g_timer_list;
}

