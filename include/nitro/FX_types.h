#ifndef GUARD_FX_TYPES_H
#define GUARD_FX_TYPES_H

#include "nitro/types.h"


typedef s16 fx16;
typedef s32 fx32;
typedef s64 fx64;
typedef s64 fx64c;

#define FX16_INT_MASK              0xF000
#define FX16_INT_ABS_MASK          0x7000
#define FX16_FRAC_MASK             0x0FFF
#define FX16_INT_SHIFT             0xC

#define FX32_INT_MASK              0xFFFFF000
#define FX32_INT_ABS_MASK          0x7FFFF000
#define FX32_FRAC_MASK             0x00000FFF
#define FX32_INT_SHIFT             0xC

#define FX64_INT_MASK              0xFFFFFFFFFFFFF000
#define FX64_INT_ABS_MASK          0x7FFFFFFFFFFFF000
#define FX64_FRAC_MASK             0x0000000000000FFF
#define FX64_INT_SHIFT             0xC

#define FX64C_INT_MASK             0xFFFFFFFF00000000
#define FX64C_INT_ABS_MASK         0x7FFFFFFF00000000
#define FX64C_FRAC_MASK            0x00000000FFFFFFFF
#define FX64C_INT_SHIFT            0x20

#define FX_INT(TYPE, x)            (((x) & TYPE ## _INT_MASK) >> TYPE ## _INT_SHIFT)
#define FX_INT_ABS(TYPE, x)        (((x) & TYPE ## _INT_ABS_MASK) >> TYPE ## _INT_SHIFT)
#define FX_FRAC(TYPE, x)           ((x) & TYPE ## _FRAC_MASK)

#define FX16_INT(x)                FX_INT(FX16, x)
#define FX16_INT_ABS(x)            FX_INT_ABS(FX16, x)
#define FX16_FRAC(x)               FX_FRAC(FX16, x)

#define FX32_INT(x)                FX_INT(FX32, x)
#define FX32_INT_ABS(x)            FX_INT_ABS(FX32, x)
#define FX32_FRAC(x)               FX_FRAC(FX32, x)

#define FX64_INT(x)                FX_INT(FX64, x)
#define FX64_INT_ABS(x)            FX_INT_ABS(FX64, x)
#define FX64_FRAC(x)               FX_FRAC(FX64, x)

#define FX64C_INT(x)               FX_INT(FX64C, x)
#define FX64C_INT_ABS(x)           FX_INT_ABS(FX64C, x)
#define FX64C_FRAC(x)              FX_FRAC(FX64C, x)

//TODO: clean up these macros
#define FX32_MUL_NO_ROUND(a, b)      ((fx32)(((fx64)(a) * (b)) >> FX32_INT_SHIFT))
#define FX32_MUL(a, b)               ((fx32)((((fx64)(a) * (b) + (1 << (FX32_INT_SHIFT - 1))) >> FX32_INT_SHIFT)))
#define FX32_MUL_ADD_MUL(a, b, c, d) ((fx32)(((fx64)(a) * (b) + (fx64)c * d) >> FX32_INT_SHIFT))
//the extra term here is for rounding
#define FX32_MUL_SUB_MUL(a, b, c, d) ((fx32)(((fx64)(a) * (b) - (fx64)c * d + (1 << (FX32_INT_SHIFT - 1))) >> FX32_INT_SHIFT))

#define FX_MUL_FX32_FX64C(a, b)      ((fx32)((((a) * (b) + ((fx64)1 << (FX64C_INT_SHIFT - 1))) >> FX64C_INT_SHIFT)))

#define FX_FX16_TO_F32(x) ((f32)((x) / (f32)(1 << FX16_SHIFT)))
#define FX_F32_TO_FX16(x) ((fx16)(((x) > 0) ? \
                                     ((x) * (1 << FX16_INT_SHIFT) + 0.5f ) : \
                                     ((x) * (1 << FX16_INT_SHIFT) - 0.5f )))
#define FX_FX32_TO_F32(x) ((f32)((x) / (f32)(1 << FX32_INT_SHIFT)))
#define FX_F32_TO_FX32(x) ((fx32)(((x) > 0) ? \
                                     ((x) * (1 << FX32_INT_SHIFT) + 0.5f ) : \
                                     ((x) * (1 << FX32_INT_SHIFT) - 0.5f )))
#define FX16_CONST(x) FX_F32_TO_FX16(x)
#define FX32_CONST(x) FX_F32_TO_FX32(x)

#define FX16_ONE ((fx16)0x1000)
#define FX32_ONE ((fx32)0x00001000L)

typedef struct Vecx32
{
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Vecx16
{
    fx16 x;
    fx16 y;
    fx16 z;
} VecFx16;

//Matrices are indexed as [column][row]
typedef struct Mtx44
{
    fx32 _[16];
} MtxFx44;

typedef struct Mtx43
{
    fx32 _[12];
} MtxFx43;

typedef struct Mtx33
{
    fx32 _[9];
} MtxFx33;

typedef struct Mtx22
{
    fx32 _[4];
} MtxFx22;

#endif //GUARD_FX_TYPES_H
