#include "global.h"
#include "main.h"
#include "fx.h"

void VEC_Add(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *dst){
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
    dst->z = a->z + b->z;
}

void VEC_Subtract(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *dst){
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
    dst->z = a->z - b->z;
}

void VEC_Fx16Add(struct Vecx16 *a, struct Vecx16 *b, struct Vecx16 *dst){
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
    dst->z = a->z + b->z;
}

s32 VEC_DotProduct(struct Vecx32 *a, struct Vecx32 *b){
    return ((s64)a->x * b->x + (s64)a->y * b->y + (s64)a->z * b->z + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT;
}

s32 VEC_Fx16DotProduct(struct Vecx16 *a, struct Vecx16 *b){
    s32 temp1, temp2;
    temp1 = (a->x * b->x) + (a->y * b->y);
    temp2 = (a->z * b->z) + (1 << (FX64_INT_SHIFT - 1));
    return (s32)(((s64)temp1 + temp2) >> FX64_INT_SHIFT);
}

void VEC_CrossProduct(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *dst){
    s32 x, y, z;
    x = (s32)(((s64)a->y * b->z - (s64)a->z * b->y + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT);
    y = (s32)(((s64)a->z * b->x - (s64)a->x * b->z + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT);
    z = (s32)(((s64)a->x * b->y - (s64)a->y * b->x + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT);
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

void VEC_Fx16CrossProduct(struct Vecx16 *a, struct Vecx16 *b, struct Vecx16 *dst){
    s32 x, y, z;
    x = ((a->y * b->z - a->z * b->y + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT);
    y = ((a->z * b->x - a->x * b->z + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT);
    z = ((a->x * b->y - a->y * b->x + (1 << (FX64_INT_SHIFT - 1))) >> FX64_INT_SHIFT);
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

#define HW_REG_DIVCNT              0x04000280
#define HW_REG_DIV_NUMER           0x04000290
#define HW_REG_DIV_DENOM           0x04000298
#define HW_REG_DIV_RESULT          0x040002A0
#define HW_REG_DIVREM_RESULT       0x040002A8

#define HW_REG_SQRTCNT             0x040002B0
#define HW_REG_SQRT_RESULT         0x040002B4
#define HW_REG_SQRT_PARAM          0x040002B8

#define SETREG16(x, y)             ((*(vu16 *)x) = y)
#define SETREG32(x, y)             ((*(vu32 *)x) = y)
#define SETREG64(x, y)             ((*(vu64 *)x) = y)
#define READREG16(x)               (*(vu16 *)x)
#define READREG32(x)               (*(vu32 *)x)
#define READREG64(x)               (*(vu64 *)x)

s32 VEC_Mag(struct Vecx32 *a){
    s64 l2 = (s64)a->x * a->x;
    l2 += (s64)a->y * a->y;
    l2 += (s64)a->z * a->z;
    SETREG16(HW_REG_SQRTCNT, 0x1);
    SETREG64(HW_REG_SQRT_PARAM, l2 * 4);
    while (READREG16(HW_REG_SQRTCNT) & 0x8000); //wait for coprocessor to finish
    return ((s32)READREG32(HW_REG_SQRT_RESULT) + 1) >> 1;
}

void VEC_Normalize(struct Vecx32 *a, struct Vecx32 *dst){
    s64 l2 = (s64)a->x * a->x;
    l2 += (s64)a->y * a->y;
    l2 += (s64)a->z * a->z;
    //1/sqrt(l) is computed by calculating sqrt(l)*(1/l)
    SETREG16(HW_REG_DIVCNT, 0x2);
    SETREG64(HW_REG_DIV_NUMER, 0x0100000000000000);
    SETREG64(HW_REG_DIV_DENOM, l2);
    SETREG16(HW_REG_SQRTCNT, 0x1);
    SETREG64(HW_REG_SQRT_PARAM, l2 * 4);
    while (READREG16(HW_REG_SQRTCNT) & 0x8000); //wait for sqrt to finish
    s32 sqrtresult = READREG32(HW_REG_SQRT_RESULT);
    while (READREG16(HW_REG_DIVCNT) & 0x8000); //wait for division to finish
    l2 = READREG64(HW_REG_DIV_RESULT);
    l2 = sqrtresult * l2;
    dst->x = (l2 * a->x + (1LL << (0x2D - 1))) >> 0x2D;
    dst->y = (l2 * a->y + (1LL << (0x2D - 1))) >> 0x2D;
    dst->z = (l2 * a->z + (1LL << (0x2D - 1))) >> 0x2D;
}

void VEC_Fx16Normalize(struct Vecx16 *a, struct Vecx16 *dst){
    s64 l2 = a->x * a->x;
    l2 += a->y * a->y;
    l2 += a->z * a->z;
    //1/sqrt(l) is computed by calculating sqrt(l)*(1/l)
    SETREG16(HW_REG_DIVCNT, 0x2);
    SETREG64(HW_REG_DIV_NUMER, 0x0100000000000000);
    SETREG64(HW_REG_DIV_DENOM, l2);
    SETREG16(HW_REG_SQRTCNT, 0x1);
    SETREG64(HW_REG_SQRT_PARAM, l2 * 4);
    while (READREG16(HW_REG_SQRTCNT) & 0x8000); //wait for sqrt to finish
    s32 sqrtresult = READREG32(HW_REG_SQRT_RESULT);
    while (READREG16(HW_REG_DIVCNT) & 0x8000); //wait for division to finish
    l2 = READREG64(HW_REG_DIV_RESULT);
    l2 = sqrtresult * l2;
    dst->x = (l2 * a->x + (1LL << (0x2D - 1))) >> 0x2D;
    dst->y = (l2 * a->y + (1LL << (0x2D - 1))) >> 0x2D;
    dst->z = (l2 * a->z + (1LL << (0x2D - 1))) >> 0x2D;
}

void VEC_MultAdd(s32 factor, struct Vecx32  *a, struct Vecx32 *b, struct Vecx32 *dst){
    dst->x = (s32)(((s64)factor * a->x) >> FX32_INT_SHIFT) + b->x;
    dst->y = (s32)(((s64)factor * a->y) >> FX32_INT_SHIFT) + b->y;
    dst->z = (s32)(((s64)factor * a->z) >> FX32_INT_SHIFT) + b->z;
}
