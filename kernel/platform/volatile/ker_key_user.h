#ifndef KER_KEY_USER_H
#define KER_KEY_USER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "../../../common/common.h"
//#include "drv_key.h"

#define KEY_SCAN_MS  10

/* counting every KEY_SCAN_MS ms */
/* anti shake */
#define KEY_RELEASE_COUNT_MAX  4
#define KEY_PRESS_COUNT_MAX    4
#define KER_FILTER_COUNT_MAX 4
/* 1s */
#define KEY_LONG_PRESS1_COUNT_MAX  (1000/KEY_SCAN_MS)
/* 2s */
#define KEY_LONG_PRESS2_COUNT_MAX  (1500/KEY_SCAN_MS)
/* 4s */
#define KEY_LONG_PRESS3_COUNT_MAX  (2000/KEY_SCAN_MS)
/* 30s */
#define KEY_STUCK_COUNT_MAX        (30000/KEY_SCAN_MS)

typedef TE_BOOL (*TFP_KEY_HANDLE)(void);

/*<dqns_gen_key_bits_type_begin>*/
typedef T_U8 T_KER_KEY_BITS;
/*<dqns_gen_key_bits_type_end>*/

typedef T_U16 T_KER_KEY_FLAGS;

typedef union{
    struct{
        T_KER_KEY_FLAGS already_send_press_msg_flag:1;
        T_KER_KEY_FLAGS already_send_long_press1_flag:1;
        T_KER_KEY_FLAGS already_send_long_press2_flag:1;
        T_KER_KEY_FLAGS already_send_long_press3_flag:1;
        T_KER_KEY_FLAGS already_send_key_stuck_flag:1;
        T_KER_KEY_FLAGS need_care_long_press1_flag:1;
        T_KER_KEY_FLAGS need_care_long_press2_flag:1;
        T_KER_KEY_FLAGS need_care_long_press3_flag:1;
        T_KER_KEY_FLAGS need_care_stuck_flag:1;
        T_KER_KEY_FLAGS na:7;        
    }key_flags_struct;
    T_KER_KEY_FLAGS key_flags;
}TU_KER_KEY_FLAG;

typedef struct{
    T_U16 press_counter;
    T_U8 release_counter;    
    T_U8 filter_counts;
    T_KER_KEY_BITS key_bit;
    T_KER_KEY_BITS key_combine_bits;
    TU_KER_KEY_FLAG key_flag;
}TS_KER_KEY;

typedef enum{
    E_KEY_MSG_TYPE_PRESS,
    E_KEY_MSG_TYPE_LONG_PRESS_1,
    E_KEY_MSG_TYPE_LONG_PRESS_2,
    E_KEY_MSG_TYPE_LONG_PRESS_3,
    E_KEY_MSG_TYPE_RELEASE,
    E_KEY_MSG_TYPE_STUCK,
    E_KEY_MSG_TYPE_COUNT
}TE_KER_KEY_MSG_TYPE;


typedef enum{
    /*<dqns_gen_key_id_begin>*/
    E_KER_KEY_RUN_STOP,    //启停按键
    E_KER_KEY_LEVEL,    //档位按键
    E_KER_KEY_SMART,    //智能按键
    E_KER_KEY_EQ,    //electronic quality电量按键
    /*<dqns_gen_key_id_end>*/
    E_KER_KEY_COUNT
}TE_KER_KEYS;


/* Key bits information struct. */
typedef union{
    struct{
        /*<dqns_gen_union_key_bits_begin>*/
        T_KER_KEY_BITS run_stop:1;	//启停按键
        T_KER_KEY_BITS level:1;	//档位按键
        T_KER_KEY_BITS smart:1;	//智能按键
        T_KER_KEY_BITS eq:1;	//electronic quality电量按键
        T_KER_KEY_BITS na:4;
        /*<dqns_gen_union_key_bits_end>*/
    }key_bits_struc;
    T_KER_KEY_BITS key_bits;
}TU_KER_KEY_BITS;



typedef enum{
    /*<dqns_gen_combine_key_id_begin>*/
    E_KER_KEY_COMBINE_DUMMY,    //level+smart
    /*<dqns_gen_combine_key_id_end>*/
    E_KER_KEY_COMBINE_COUNT    
}TE_KER_COMBINE_KEYS;

typedef struct{
    TE_KER_COMBINE_KEYS combine_key;    
    T_KER_KEY_BITS combine_key_bits;
}TS_KER_COMBINE_KEY_BITS;

void KerKeyUserInit(void);
T_KER_KEY_BITS KerKeyUserBits(void);

#ifdef __cplusplus
}
#endif

#endif

