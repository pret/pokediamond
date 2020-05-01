#ifndef GUARD_FX_H
#define GUARD_FX_H

#define FX32_INT_MASK     0xFFFFF000
#define FX32_INT_ABS_MASK 0x7FFFF000
#define FX32_FRAC_MASK    0x00000FFF

#define FX32_INT_SHIFT    0xC
#define FX64_INT_SHIFT    0xC

#define FX32_INT(x)       (((x) & FX32_INT_MASK) >> FX32_INT_SHIFT)
#define FX32_INT_ABS(x)   (((x) & FX32_INT_ABS_MASK) >> FX32_INT_SHIFT)
#define FX32_FRAC(x)      ((x) & FX32_FRAC_MASK)

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
