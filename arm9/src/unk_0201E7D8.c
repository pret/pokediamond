#include "global.h"
#include "fx.h"

struct UnkStruct_0201E7D8_64
{
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    struct Vecx32 * unk_20;
};

struct UnkStruct_0201E7D8
{
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    fx32 unk_10;
    struct Vecx32 unk_14;
    struct Vecx32 unk_20;
    fx32 unk_2C;
    fx32 unk_30;
    fx32 unk_34;
    fx32 unk_38;
    u16 unk_3C;
    u16 unk_3E;
    u8 filler_40[6];
    u16 unk_46;
    u8 filler_48[12];
    u32 unk_54;
    u32 unk_58;
    u32 unk_5C;
    u32 unk_60;
    struct UnkStruct_0201E7D8_64 * unk_64;
};

BOOL UNK_02105BB8 = TRUE;
void * UNK_021C59A4;

THUMB_FUNC void FUN_0201E7D8(struct UnkStruct_0201E7D8 * a0)
{
    u16 r4 = -a0->unk_3C;
    a0->unk_14.x = FX_Mul(FX_Mul(FX_SinIdx(a0->unk_3E), a0->unk_38), FX_CosIdx(a0->unk_3C));
    a0->unk_14.z = FX_Mul(FX_Mul(FX_CosIdx(a0->unk_3E), a0->unk_38), FX_CosIdx(a0->unk_3C));
    a0->unk_14.y = FX_Mul(FX_SinIdx(r4), a0->unk_38);
    VEC_Add(&a0->unk_14, &a0->unk_20, &a0->unk_14);
}

THUMB_FUNC void FUN_0201E8B8(struct UnkStruct_0201E7D8 * a0)
{
    u16 r4 = -a0->unk_3C;
    a0->unk_20.x = -FX_Mul(FX_Mul(FX_SinIdx(a0->unk_3E), a0->unk_38), FX_CosIdx(a0->unk_3C));
    a0->unk_20.z = -FX_Mul(FX_Mul(FX_CosIdx(a0->unk_3E), a0->unk_38), FX_CosIdx(a0->unk_3C));
    a0->unk_20.y = -FX_Mul(FX_SinIdx(r4), a0->unk_38);
    VEC_Add(&a0->unk_20, &a0->unk_14, &a0->unk_20);
}

THUMB_FUNC void FUN_0201E99C(u16 a0, struct UnkStruct_0201E7D8 * a1)
{
    a1->unk_46 = a0;
    a1->unk_00 = FX_SinIdx(a0);
    a1->unk_04 = FX_CosIdx(a0);
    a1->unk_08 = FX32_CONST(1.33333333);
    a1->unk_0C = FX32_CONST(150);
    a1->unk_10 = FX32_CONST(900);
    a1->unk_2C = 0;
    a1->unk_30 = FX32_ONE;
    a1->unk_34 = 0;
    a1->unk_54 = 0;
    a1->unk_58 = 0;
    a1->unk_5C = 0;
    a1->unk_60 = 0;
    a1->unk_64 = NULL;
}

THUMB_FUNC void FUN_0201E9E8(struct UnkStruct_0201E7D8 * a0, struct Vecx32 * a1)
{
    if (a0->unk_58 == 0)
        a1->x = 0;
    if (a0->unk_5C == 0)
        a1->y = 0;
    if (a0->unk_60 == 0)
        a1->z = 0;
}

THUMB_FUNC void FUN_0201EA08(struct UnkStruct_0201E7D8 * a0, struct Vecx32 * a1, struct Vecx32 * a2)
{
    s32 * r7;
    s32 * sp0;
    if (a0->unk_64 == NULL)
    {
        *a2 = *a1;
    }
    else
    {
        r7 = &a0->unk_64->unk_04;
        sp0 = &a0->unk_64->unk_08;
        if (a0->unk_64->unk_10 == 0)
        {
            *a2 = *a1;
            if (*r7 == a0->unk_64->unk_0C)
                a0->unk_64->unk_10 = 1;
        }
        else
        {
            *a2 = a0->unk_64->unk_20[a0->unk_64->unk_04];
        }
        *r7 = (*r7 + 1) % a0->unk_64->unk_00;
        a0->unk_64->unk_20[*sp0] = *a1;
        *sp0 = (*sp0 + 1) % a0->unk_64->unk_00;
        if (a0->unk_64->unk_14 == 0)
            a2->x = a1->x;
        if (a0->unk_64->unk_18 == 0)
            a2->y = a1->y;
        if (a0->unk_64->unk_1C == 0)
            a2->z = a1->z;
    }
}
