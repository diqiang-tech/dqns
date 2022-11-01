#include "ker_dig.h"
#include "../platform/stable/ker_timer.h"

static TE_KER_DIG_SHOW_TYPE g_pre_dig_show_type;
static TE_KER_DIG_SHOW_TYPE g_cur_dig_show_type;


static void kerDigShowNone(void){
}
static void kerDigShowPost(void){
}
static void kerDigShowPressure(void){
}
static void kerDigShowEQ(void){
}

static void kerDigShowLevel(void){
}
static void kerDigShowError(void){
}
static void kerDigShowDebug(void){
}
static const TFP_VOID_VOID g_show_func_tbl[]={
    kerDigShowNone,
    kerDigShowPost,
    kerDigShowPressure,
    kerDigShowEQ,
    kerDigShowLevel,
    kerDigShowError,
    kerDigShowDebug,
};

void kerDigShowPeriod(TE_KER_TIMER_ID e_timer_id){
    if (E_KER_DIG_SHOW_PRESSURE == g_cur_dig_show_type || 
       E_KER_DIG_SHOW_EQ == g_cur_dig_show_type){
        g_show_func_tbl[g_cur_dig_show_type]();
    }
}


void KerDigInit(void){
    g_pre_dig_show_type = E_KER_DIG_SHOW_NONE;
    g_cur_dig_show_type = E_KER_DIG_SHOW_NONE;
    KerTimerBind(E_KER_TIMER_DIG_FRESH, kerDigShowPeriod);
}

void KerDigShow(TE_KER_DIG_SHOW_TYPE e_dig_show_type){
    M_Assert(e_dig_show_type<E_KER_DIG_SHOW_COUNT);
    g_pre_dig_show_type = g_cur_dig_show_type;
    g_cur_dig_show_type = e_dig_show_type;
    g_show_func_tbl[e_dig_show_type]();
}

void KerDigShowPre(void){
    KerDigShow(g_pre_dig_show_type);
}

TE_KER_DIG_SHOW_TYPE KerDigShowType(void){
    return g_cur_dig_show_type;
}

TE_KER_DIG_SHOW_TYPE KerDigPreShowType(void){
    return g_pre_dig_show_type;
}


