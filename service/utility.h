#ifndef UTILITY_H
#define UTILITY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "../common/common.h"
#include "../task/task.h"

#define MAX_NUMBER_LENGTH 8 

#ifdef _DEBUG_
    #define M_Assert    assert
    #define M_Trace printf
#else
    #define M_Assert(...)
    #define M_Trace(...)
#endif

#ifdef _ENABLE_PRINT_
    #define M_Print printf
#else
    #define M_Print(...)
#endif

typedef struct{
    T_U8 hour;
    T_U8 min;
}TS_UTILITY_HOUR_MIN;

void UtilityGenHourMin(T_U16 minutes,TS_UTILITY_HOUR_MIN* p_hour_min);

T_U8 UtilityGenU8(T_U8 from_bit,T_U8 to_bit);
T_U8 UtilityReverseU8(T_U8 be_reversed_u8);
void UtilityAsciiToDec(T_U8 *ascii, T_U8 digits, T_U8* decimal);
void UtilityAsciiToHex(T_U8 *ascii, T_U8 digits, T_U8* hexdecimal);
void UtilityDecToAscii(T_U16 decimal, T_U8 digits, T_U8 *ascii);
T_U8 UtilityDectoAsciicounts(T_U16 decimal,T_U8 *ascii );
void UtilityHexToAscii(T_U16 hexadecimal, T_U8 digits, T_U8 *ascii);
void UtilityHexToDec(T_U8 hexadecimal, T_U8 digits, T_U8 *decimal);
void UtilityIntToAsciiStr(T_U32 local_int,T_U8* p_str);
void UtilityFloatToAsciiStr(T_U32 float_number,T_U8 decimal_width, T_U8* p_str);
void UtilityDelayMs(T_S32 delay_ms);
void UtilityDelayUs(T_U32 delay_us);
void UtilityDelayMsWithMainTask(T_S32 delay_ms);
T_U8 UtilityGenCheckSum(T_U8* p_buffer,T_U8 buffer_len);
T_U8 UtilityCalCheckSum(T_U8* p_buffer,T_U8 buffer_len);
T_U16 UtilityGenCrc16(T_U8* p_data,T_U8 data_len);
T_U16 UtilityGetAverage(T_U16* p_data,T_U8 data_count);
T_U16 UtilityGetMax(T_U16* p_data,T_U8 data_count);
T_U16 UtilityGetMin(T_U16* p_data,T_U8 data_count);


#ifdef __cplusplus 
}
#endif

    
#endif 

