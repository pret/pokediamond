#ifndef GUARD_FX_H
#define GUARD_FX_H

#include "nitro/FX_types.h"
#include "GX_g3_util.h"

//FX
void FX_Init();
fx32 FX_Modf(fx32 x, fx32 *iptr);

//Atan
u16 FX_Atan(fx32 x);
u16 FX_Atan2(fx32 x, fx32 y);

//Vec
void VEC_Add(const struct Vecx32 *a, const struct Vecx32 *b, struct Vecx32 *dst);
void VEC_Subtract(const struct Vecx32 *a, const struct Vecx32 *b, struct Vecx32 *dst);
void VEC_Fx16Add(struct Vecx16 *x, struct Vecx16 *y, struct Vecx16 *dst);
fx32 VEC_DotProduct(const struct Vecx32 *a, const struct Vecx32 *b);
fx32 VEC_Fx16DotProduct(struct Vecx16 *a, struct Vecx16 *b);
void VEC_CrossProduct(const struct Vecx32 *a, const struct Vecx32 *b, struct Vecx32 *dst);
void VEC_Fx16CrossProduct(struct Vecx16 *a, struct Vecx16 *b, struct Vecx16 *dst);
fx32 VEC_Mag(struct Vecx32 *a);
void VEC_Normalize(const struct Vecx32 *a, struct Vecx32 *dst);
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
void MTX_ScaleApply43(struct Mtx43 *mtx, struct Mtx43 *dst, fx32 x, fx32 y, fx32 z);
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

// Trig
extern const fx16 FX_SinCosTable_[];

static inline fx16 FX_SinIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1)];
}

static inline fx16 FX_CosIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1) + 1];
}

static inline fx32 FX32_CAST(s64 res)
{
    return (fx32)res;
}

static inline fx32 FX_MulInline(fx32 v1, fx32 v2)
{
    return FX32_CAST(((s64)v1 * v2 + 0x800LL) >> FX32_INT_SHIFT);
}

#define FX_Mul(v1, v2) FX_MulInline(v1, v2)

static inline void VEC_Set(struct Vecx32 * vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline void MTX_LookAt(const VecFx32 * camPos, const VecFx32 * camUp, const VecFx32 * target, MtxFx43 * mtx)
{
    G3i_LookAt_(camPos, camUp, target, FALSE, mtx);
}

static inline void MTX_Perspective(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 n, fx32 f, MtxFx44 * mtx)
{
    G3i_PerspectiveW_(fovySin, fovyCos, aspect, n, f, FX32_ONE, FALSE, mtx);
}

static inline void MTX_Ortho(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, MtxFx44 * mtx)
{
    G3i_OrthoW_(t, b, l, r, n, f, FX32_ONE, FALSE, mtx);
}

#endif //GUARD_FX_H
