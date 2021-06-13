#include "global.h"
#include "fx.h"
#include "heap.h"
#include "NNS_g3d.h"

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
    VecFx32 * unk_20;
};

struct UnkStruct_0201E7D8
{
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    fx32 unk_10;
    VecFx32 unk_14;
    VecFx32 unk_20;
    VecFx32 unk_2C;
    fx32 unk_38;
    u16 unk_3C;
    u16 unk_3E;
    u8 filler_40[6];
    u16 unk_46;
    VecFx32 unk_48;
    VecFx32 * unk_54;
    u32 unk_58;
    u32 unk_5C;
    u32 unk_60;
    struct UnkStruct_0201E7D8_64 * unk_64;
};

BOOL UNK_02105BB8 = TRUE;
struct UnkStruct_0201E7D8 * UNK_021C59A4;

void FUN_0201EF70(VecFx32 * a0, struct UnkStruct_0201E7D8 * a1);

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
    a1->unk_2C.x = 0;
    a1->unk_2C.y = FX32_ONE;
    a1->unk_2C.z = 0;
    a1->unk_54 = 0;
    a1->unk_58 = 0;
    a1->unk_5C = 0;
    a1->unk_60 = 0;
    a1->unk_64 = NULL;
}

THUMB_FUNC void FUN_0201E9E8(struct UnkStruct_0201E7D8 * a0, VecFx32 * a1)
{
    if (a0->unk_58 == 0)
        a1->x = 0;
    if (a0->unk_5C == 0)
        a1->y = 0;
    if (a0->unk_60 == 0)
        a1->z = 0;
}

THUMB_FUNC void FUN_0201EA08(struct UnkStruct_0201E7D8 * a0, VecFx32 * a1, VecFx32 * a2)
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

THUMB_FUNC void FUN_0201EABC(s32 r5, s32 r7, s32 r6, s32 sp0, struct UnkStruct_0201E7D8 * sp18)
{
    s32 i;
    struct UnkStruct_0201E7D8_64 * r4;

    if (sp18->unk_54 != 0)
    {
        GF_ASSERT(r7 + 1 <= r5);
        r4 = AllocFromHeap(sp0, sizeof(struct UnkStruct_0201E7D8_64));
        r4->unk_20 = AllocFromHeap(sp0, sizeof(VecFx32) * r5);
        for (i = 0; i < r5; i++)
        {
            r4->unk_20[i].x = 0;
            r4->unk_20[i].y = 0;
            r4->unk_20[i].z = 0;
        }
        r4->unk_00 = r5;
        r4->unk_04 = 0;
        r4->unk_08 = r7;
        r4->unk_0C = r7;
        r4->unk_10 = 0;
        r4->unk_14 = 0;
        r4->unk_18 = 0;
        r4->unk_1C = 0;
        if (r6 & 1)
            r4->unk_14 = 1;
        if (r6 & 2)
            r4->unk_18 = 1;
        if (r6 & 4)
            r4->unk_1C = 1;
        sp18->unk_64 = r4;
    }
}

THUMB_FUNC void FUN_0201EB48(struct UnkStruct_0201E7D8 * a0)
{
    if (a0->unk_64 != NULL)
    {
        FreeToHeap(a0->unk_64->unk_20);
        FreeToHeap(a0->unk_64);
        a0->unk_64 = NULL;
    }
}

THUMB_FUNC struct UnkStruct_0201E7D8 * FUN_0201EB64(u32 heap_id)
{
    return AllocFromHeap(heap_id, sizeof(struct UnkStruct_0201E7D8));
}

THUMB_FUNC void FUN_0201EB70(struct UnkStruct_0201E7D8 * a0)
{
    FreeToHeap(a0);
}

THUMB_FUNC void FUN_0201EB78(struct UnkStruct_0201E7D8 * a0, struct UnkStruct_0201E7D8 * a1)
{
    *a1 = *a0;
}

THUMB_FUNC void FUN_0201EB8C(struct UnkStruct_0201E7D8 * a0)
{
    UNK_021C59A4 = a0;
}

THUMB_FUNC void FUN_0201EB98(void)
{
    UNK_021C59A4 = NULL;
}

THUMB_FUNC void FUN_0201EBA4(void)
{
    VecFx32 sp10;
    VecFx32 sp4;
    if (UNK_021C59A4 != NULL)
    {
        if (UNK_021C59A4->unk_54 != NULL)
        {
            VEC_Subtract(UNK_021C59A4->unk_54, &UNK_021C59A4->unk_48, &sp10);
            FUN_0201E9E8(UNK_021C59A4, &sp10);
            FUN_0201EA08(UNK_021C59A4, &sp10, &sp4);
            FUN_0201EF70(&sp4, UNK_021C59A4);
            UNK_021C59A4->unk_48 = *UNK_021C59A4->unk_54;
        }
        NNS_G3dGlbLookAt(&UNK_021C59A4->unk_14, &UNK_021C59A4->unk_2C, &UNK_021C59A4->unk_20);
    }
}

THUMB_FUNC void FUN_0201EC58(VecFx32 * a, struct UnkStruct_0201E7D8 * b)
{
    b->unk_2C = *a;
}

THUMB_FUNC void FUN_0201EC68(VecFx32 * a, struct UnkStruct_0201E7D8 * b)
{
    b->unk_54 = a;
    b->unk_48 = *a;
    b->unk_58 = 1;
    b->unk_5C = 1;
    b->unk_60 = 1;
}

THUMB_FUNC void FUN_0201EC88(struct UnkStruct_0201E7D8 * a0)
{
    a0->unk_54 = NULL;
    a0->unk_58 = 0;
    a0->unk_5C = 0;
    a0->unk_60 = 0;
}
