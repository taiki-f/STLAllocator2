#pragma once

#include    <stddef.h>

typedef bool            Bool;
typedef unsigned char*  Ptr;
typedef void            (*ProcPtr)(void);
typedef void            Void;
typedef void*           VoidPtr;
typedef char*           Str;
typedef char            Str16[16];
typedef char            Str32[32];
typedef char            Str64[64];
typedef char            Str128[128];
typedef char            Str256[256];
typedef signed char     Char;
typedef signed short    Short;
typedef signed int      Long;
typedef signed long     DLong;
typedef signed int      Int;
typedef unsigned char   U_Char;
typedef unsigned short  U_Short;
typedef unsigned int    U_Long;
typedef unsigned long   U_DLong;
typedef unsigned int    U_Int;
typedef unsigned char   Byte;
typedef unsigned short  Word;
typedef unsigned int    DWord;
typedef unsigned long   DDWord;
typedef signed int      Fixed;          // 整数型32ビット固定小数点(1.19.12)
typedef signed short    HalfFixed;      // 整数型16ビット固定小数点(1.3.12)
typedef signed int      Fixed16;        // 整数型32ビット固定小数点(1.23.8)
typedef signed short    HalfFixed16;    // 整数型16ビット固定小数点(1.7.8)
typedef float           Float;
typedef double          Double;
typedef float           Vector[4];
typedef size_t          SizeT;

typedef struct
{
    U_Char r, g, b, a;
} Color, *ColorPeek;
typedef struct
{
    Long r, g, b, a;
} LColor, *LColorPeek;
typedef struct
{
    int x, y;
} Point, *PointPeek;
typedef struct
{
    int x, y, w, h;
} Rect, *RectPeek;
typedef struct
{
    int sx, sy, ex, ey;
} Region, *RegionPeek;
typedef struct
{
    Short x, y;
} SPoint, *SPointPeek;
typedef struct
{
    Short x, y, w, h;
} SRect, *SRectPeek;
typedef struct
{
    Short sx, sy, ex, ey;
} SRegion, *SRegionPeek;
typedef struct
{
    Float x, y;
} FPoint, *FPointPeek;
typedef struct
{
    Float x, y, w, h;
} FRect, *FRectPeek;
typedef struct
{
    Float sx, sy, ex, ey;
} FRegion, *FRegionPeek;
typedef struct
{
    Float x, y, z;
} FPoint3D, *FPoint3DPeek;
typedef struct
{
    Float w, h;
} FSize3D, *FSize3DPeek;
typedef struct
{
    Word  year;
    Word  month;
    Word  day;
    Word  hour;
    Word  minute;
    Word  second;
    DWord microsecond;
} Clock, *ClockPeek;


#define Global
#define Local
#define Static      static
#define Extern      extern
#define Const       const
#define Void        void

#define SUCCESS     (1)
#define MISS        (0)

#ifndef TRUE
#define TRUE        true
#endif
#ifndef FALSE
#define FALSE       false
#endif

// インクルードの順番によってはDXLibでエラーになるので使わないようにする
//#define Private     static
//#ifndef Size
//#define Size        size_t
//#endif

#define _AR16_      __attribute__((aligned(16)))
#define _AR128_     __attribute__((aligned(128)))

#define MOS_NO_ENTRY    (-1)        // 未登録の定義

#define FIXED_ONE       (1<<12)
#define HALFFIXED_ONE   (1<<8)

#define PI          (3.141592653590f)
#define PI_H        (1.570796326795f)
#define PI_D        (6.283185307180f)

#define INV_255     (0.003922f) // 1.0f/255.0f       255で割るときに使用する
