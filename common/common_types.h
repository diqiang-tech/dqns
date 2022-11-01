#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifdef __cplusplus
 extern "C" {
#endif


typedef void(*TFP_VOID_VOID)(void);
typedef void(*TFP_VOID_VOID_STAR)(void* p);
typedef void*(*TFP_VOID_STAR_VOID_STAR)(void* p);
typedef void(*TFP_VOID_UCHAR)(unsigned char uch);
typedef unsigned char(*TFP_U8_VOID)(void);



typedef enum{
    E_OFF,
    E_ON
}TE_SWITCH;

#ifdef __cplusplus
}
#endif

    
#endif 
