#ifndef C_DEFS_H
#define C_DEFS_H

#ifdef __cplusplus
 extern "C" {
#endif


#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif


#ifndef NULL
#define NULL 0
#endif


typedef char              T_S8;
typedef unsigned char     T_U8;
typedef signed short      T_S16;
typedef unsigned short    T_U16;
typedef signed long       T_S32;
typedef unsigned long     T_U32;
typedef signed long       T_SWord;
typedef unsigned long     T_UWord;
typedef signed long long int    T_S64;
typedef unsigned long long int T_U64;

typedef unsigned long 	  T_UMcu;
typedef signed long   	  T_SMcu;

typedef enum{
    E_FALSE,
    E_TRUE
}TE_BOOL;


#define MAX_T_S8    0x7F
#define MIN_T_S8    (-128)
#define MAX_T_S16   0x7FFF
#define MIN_T_S16   (-32768)
#define MAX_T_S32   0x7FFFFFFF
#define MIN_T_S32   (-2147483647L - 1)
#define MAX_T_S64   0x7FFFFFFFFFFFFFFF
#define MIN_T_S64   (-9223372036854775807LL - 1)

#define MAX_T_U8    0xFF
#define MIN_T_U8    0
#define MAX_T_U16   0xFFFF
#define MIN_T_U16   0
#define MAX_T_U32   0xFFFFFFFF
#define MIN_T_U32   0
#define MAX_T_U64   0xFFFFFFFFFFFFFFFF
#define MIN_T_U64   0



typedef char T_CHAR;


#define LITTLE_ENDIAN


#ifdef BIG_ENDIAN

typedef struct{
    T_U8   high;
    T_U8   low;
} TS_U16_BYTES;

typedef union{
    TS_U16_BYTES    bytes;
    T_U16           word;
}TU_U16;

typedef struct{
    TU_U16   high;
    TU_U16   low;
}TS_U32_WORDS;

typedef struct{
    T_U8   highest;
    T_U8   higher;
    T_U8   lower;
    T_U8   lowest; // least significant
}TS_U32_BYTES;

#elif defined(LITTLE_ENDIAN)

typedef struct{
    T_U8   low;
    T_U8   high;
}TS_U16_BYTES;

typedef union{
    TS_U16_BYTES   bytes;
    T_U16          word;
}TU_U16;

typedef struct{
    TU_U16   low;
    TU_U16   high;
}TS_U32_WORDS;

typedef struct{
    T_U8   lowest;  // least significant.
    T_U8   lower;
    T_U8   higher;
    T_U8   highest;
}TS_U32_BYTES;


typedef union{
    TS_U32_BYTES   bytes;
    T_U8           byte_array[4];
    TS_U32_WORDS   shorts;
    T_U32    dword;
}TU_T_U32;



#endif  


#ifdef __cplusplus
}
#endif


#endif /* C_DEFS_H */
