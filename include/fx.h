#ifndef GUARD_FX_H
#define GUARD_FX_H

#define FX32_INT_MASK     0xFFFFF000
#define FX32_INT_ABS_MASK 0x7FFFF000
#define FX32_FRAC_MASK    0x00000FFF
#define FX32_INT_SHIFT    0xC

#define FX64_INT_MASK     0xFFFFFFFFFFFFF000
#define FX64_INT_ABS_MASK 0x7FFFFFFFFFFFF000
#define FX64_FRAC_MASK    0x0000000000000FFF
#define FX64_INT_SHIFT    0xC


#define FX32_INT(x)       (((x) & FX32_INT_MASK) >> FX32_INT_SHIFT)
#define FX32_INT_ABS(x)   (((x) & FX32_INT_ABS_MASK) >> FX32_INT_SHIFT)
#define FX32_FRAC(x)      ((x) & FX32_FRAC_MASK)

#define FX64_INT(x)       (((x) & FX64_INT_MASK) >> FX64_INT_SHIFT)
#define FX64_INT_ABS(x)   (((x) & FX64_INT_ABS_MASK) >> FX64_INT_SHIFT)
#define FX64_FRAC(x)      ((x) & FX64_FRAC_MASK)



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

void FX_Init();
s32 FX_Modf(s32 x, s32 *iptr);
s32 FX_Inv(s32 x);
u16 FX_Atan(s32 x);
u16 FX_Atan2(s32 x, s32 y);

//Vec
void VEC_Add(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst);
void VEC_Subtract(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst);
void VEC_Fx16Add(struct Vecx16 *x, struct Vecx16 *y, struct Vecx16 *dst);
s32 VEC_DotProduct(struct Vecx32 *x, struct Vecx32 *y);

#endif //GUARD_FX_H
