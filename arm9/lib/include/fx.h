#ifndef GUARD_FX_H
#define GUARD_FX_H

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

struct Vecx32
{
    fx32 x;
    fx32 y;
    fx32 z;
};

struct Vecx16
{
    fx16 x;
    fx16 y;
    fx16 z;
};

//Matrices are indexed as [column][row]
struct Mtx44
{
    fx32 _[16];
};

struct Mtx43
{
    fx32 _[12];
};

struct Mtx33
{
    fx32 _[9];
};

struct Mtx22
{
    fx32 _[4];
};

//FX
void FX_Init();
fx32 FX_Modf(fx32 x, fx32 *iptr);

//Atan
u16 FX_Atan(fx32 x);
u16 FX_Atan2(fx32 x, fx32 y);

//Vec
void VEC_Add(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst);
void VEC_Subtract(struct Vecx32 *x, struct Vecx32 *y, struct Vecx32 *dst);
void VEC_Fx16Add(struct Vecx16 *x, struct Vecx16 *y, struct Vecx16 *dst);
fx32 VEC_DotProduct(struct Vecx32 *x, struct Vecx32 *y);
fx32 VEC_Fx16DotProduct(struct Vecx16 *a, struct Vecx16 *b);
void VEC_CrossProduct(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *dst);
void VEC_Fx16CrossProduct(struct Vecx16 *a, struct Vecx16 *b, struct Vecx16 *dst);
fx32 VEC_Mag(struct Vecx32 *a);
void VEC_Normalize(struct Vecx32 *a, struct Vecx32 *dst);
void VEC_Fx16Normalize(struct Vecx16 *a, struct Vecx16 *dst);
void VEC_MultAdd(fx32 factor, struct Vecx32  *a, struct Vecx32 *b, struct Vecx32 *dst);

//CP
fx32 FX_Div(fx32 numerator, fx32 denominator);
fx32 FX_Inv(fx32 x);
fx32 FX_Sqrt(fx32 x);
fx64 FX_GetDivResultFx64c();
fx32 FX_GetDivResult();
void FX_InvAsync(fx32 x);
fx32 FX_GetSqrtResult();
void FX_DivAsync(fx32 numerator, fx32 denominator);
fx32 FX_DivS32(fx32 numerator, fx32 denominator);
fx32 FX_ModS32(fx32 num, fx32 mod);

//Mtx
//The functions ending in underscores seem to be in assembly originally
//Mtx44
void MTX_TransApply44(struct Mtx44 *mtx, struct Mtx44 *dst, fx32 x, fx32 y, fx32 z);
void MTX_Concat44(struct Mtx44 *a, struct Mtx44 *b, struct Mtx44 *c);
void MTX_Identity44_(struct Mtx44 *dst);
void MTX_Copy44To43_(struct Mtx44 *src, struct Mtx43 *dst);
void MTX_RotX44_(struct Mtx44 *mtx, fx32 sinphi, fx32 cosphi);
void MTX_RotY44_(struct Mtx44 *mtx, fx32 sinphi, fx32 cosphi);
void MTX_RotZ44_(struct Mtx44 *mtx, fx32 sinphi, fx32 cosphi);

//Mtx43
void MTX_ScaleApply33(struct Mtx33 *mtx, struct Mtx33 *dst, fx32 x, fx32 y, fx32 z);
fx32 MTX_Inverse43(struct Mtx43 *mtx, struct Mtx43 *inv);
void MTX_Concat43(struct Mtx43 *a, struct Mtx43 *b, struct Mtx43 *c);
void MTX_MultVec43(struct Vecx32 *vec, struct Mtx43 *mtx, struct Vecx32 *dst);
void MTX_Identity43_(struct Mtx43 *mtx);
void MTX_Copy43To44_(struct Mtx43 *src, struct Mtx44 *dst);
void MTX_Scale43_(struct Mtx43 *dst, fx32 x, fx32 y, fx32 z);
void MTX_RotX43_(struct Mtx43 *mtx, fx32 sinphi, fx32 cosphi);
void MTX_RotY43_(struct Mtx43 *mtx, fx32 sinphi, fx32 cosphi);

//Mtx33
void MTX_ScaleApply33(struct Mtx33 *mtx, struct Mtx33 *dst, fx32 x, fx32 y, fx32 z);
void MTX_Concat33(struct Mtx33 *a, struct Mtx33 *b, struct Mtx33 *c);
void MTX_MultVec33(struct Vecx32 *vec, struct Mtx33 *mtx, struct Vecx32 *dst);
void MTX_Identity33_(struct Mtx33 *mtx);
void MTX_RotX33_(struct Mtx33 *mtx, fx32 sinphi, fx32 cosphi);
void MTX_RotY33_(struct Mtx33 *mtx, fx32 sinphi, fx32 cosphi);
void MTX_RotZ33_(struct Mtx33 *mtx, fx32 sinphi, fx32 cosphi);

//Mtx22
void MTX_ScaleApply22(struct Mtx22 *mtx, struct Mtx22 *dst, fx32 x, fx32 y);
void MTX_Identity22_(struct Mtx22 *mtx);
void MTX_Rot22_(struct Mtx22 *mtx, fx32 sinphi, fx32 cosphi);

#endif //GUARD_FX_H
