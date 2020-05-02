#ifndef GUARD_FX_H
#define GUARD_FX_H

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

#define FX32_INT(x)                FX_INT(FX32, x)
#define FX32_INT_ABS(x)            FX_INT_ABS(FX32, x)
#define FX32_FRAC(x)               FX_FRAC(FX32, x)

#define FX64_INT(x)                FX_INT(FX64, x)
#define FX64_INT_ABS(x)            FX_INT_ABS(FX64, x)
#define FX64_FRAC(x)               FX_FRAC(FX64, x)

#define FX64C_INT(x)               FX_INT(FX64C, x)
#define FX64C_INT_ABS(x)           FX_INT_ABS(FX64C, x)
#define FX64C_FRAC(x)              FX_FRAC(FX64C, x)



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

struct Vecx32
{
    s32 x;
    s32 y;
    s32 z;
};

struct Vecx16
{
    s16 x;
    s16 y;
    s16 z;
};

//FX
void FX_Init();
s32 FX_Modf(s32 x, s32 *iptr);

//Atan
u16 FX_Atan(s32 x);
u16 FX_Atan2(s32 x, s32 y);

//Vec
void VEC_Add(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst);
void VEC_Subtract(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst);
void VEC_Fx16Add(struct Vecx16 *x, struct Vecx16 *y, struct Vecx16 *dst);
s32 VEC_DotProduct(struct Vecx32 *x, struct Vecx32 *y);

//CP
s32 FX_Div(s32 numerator, s32 denominator);
s32 FX_Inv(s32 x);
s32 FX_Sqrt(s32 x);
s64 FX_GetDivResultFx64c();
s32 FX_GetDivResult();
void FX_InvAsync(s32 x);
s32 FX_GetSqrtResult();
void FX_DivAsync(s32 numerator, s32 denominator);
s32 FX_DivS32(s32 numerator, s32 denominator);
s32 FX_ModS32(s32 num, s32 mod);

#endif //GUARD_FX_H
