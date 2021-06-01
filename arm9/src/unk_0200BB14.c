#include "global.h"
#include "unk_0200BB14.h"
#include "game_init.h"
#include "heap.h"

extern void FUN_0201D060(u32 *param0, u32 param1, u32 param2);
extern void FUN_0201E00C(u32 param0, u32 param1);
extern void NNS_G2dInitOamManagerModule();
extern void FUN_02009EAC(u32 param0,
    u32 param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8);
extern u32 FUN_0201C328(u32 param0, u32 param1);
extern void FUN_0201D168();
extern void FUN_0201E0BC();
extern u32 FUN_02008C9C(u32 param0, void *param1, u32 param2);
extern void FUN_0201FFC8(u32 param0);
extern void FUN_0201FDEC(u32 param0);
extern void FUN_02009F80();
extern void FUN_0201C348();
extern void FUN_0201FD58(u32 param0);
extern void FUN_02008C80(u32 param0);
extern u32 FUN_02009660(u32 *param0, s32 param1);
extern void FUN_020096B4(u32 param0);
extern void FUN_02009C30(u32 *param0);
extern void FUN_02009E28(u32 *param0);
extern void FUN_02009448(u32 *param0);
extern void FUN_02008E2C(u32 param0);
extern void FUN_0201C350(u32 param0);
extern void FUN_0201D12C();
extern void FUN_0201E08C();
extern void FUN_02009FA0();
extern u32 FUN_0200965C(s32 param0);
extern void FUN_02009668(void *param0, u32 param1, u32 param2);
extern u32 FUN_020096CC(u32 param0);
extern u32 FUN_02008DEC(u32 param0, s32 param1, u32 param2);
extern u32 *FUN_02009424(u32 param0, u32 param1);
extern u32 FUN_020093A8(u32 param0, u32 param1, u32 *param2, u32 param3);
extern void FUN_02009A90(u32 *param0);
extern void FUN_02009D34(u32 *param0);
extern u32 FUN_02008BE0(
    void *param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
extern u32 FUN_0201FE94(struct UnkStruct4 *param0);
extern void FUN_02020130(u32 param0, u32 param1);
extern void FUN_02020248(u32 param0, u32 param1);
extern u32 FUN_0200945C(u32 param0, s32 param1);
extern u32 FUN_02008F34(
    u32 param0, u32 param1, u32 param2, u32 param3, s32 param4, u32 param5, u32 param6);
extern void FUN_02009B04(u32 param0);
extern u32 FUN_02008FEC(
    u32 param0, u32 param1, u32 param2, u32 param3, s32 param4, u32 param5, u32 param6, u32 param7);
extern u32 FUN_02009D68(u32 param0);
extern u32 FUN_02009E88(u32 param0, u32 param1);
extern void FUN_02003108(u32 param0, u32 param1, u16 param2, u32 param3);
extern void FUN_02008AA4(struct UnkStruct7 *param0,
    s32 param1,
    s32 param2,
    s32 param3,
    s32 param4,
    s32 param5,
    s32 param6,
    u32 param7,
    u32 param8,
    u32 param9,
    u32 param10,
    u32 param11,
    u32 param12,
    u32 param13,
    u32 param14);
extern u8 FUN_020202A0(u32 param0);
extern u32 FUN_020094F0(u32 param0, u32 param1);
extern u32 FUN_02009E54(u32 param0, u32 param1);
extern void FUN_02009CDC(u32 param0);
extern u32 FUN_020090AC(
    u32 param0, u32 param1, u32 param2, u32 param3, s32 param4, u32 param5, u32 param6);
extern u32 FUN_02009530(u32 param0);
extern void FUN_02009490(u32 param0, u32 param1);
extern void FUN_0201D324(u32 param0);
extern void FUN_0201E1C8(u32 param0);
extern void FUN_020201E4(u32 param0, u32 param1);
extern u32 FUN_020201DC(u32 param0);
extern void FUN_020200BC(u32 param0, u32 param1);
extern void FUN_020200D8(u32 param0, u32 param1);
extern u32 FUN_02020388(u32 param0);
extern void FUN_02020208(u32 param0);
extern void FUN_0202022C(u32 param0);
extern void FUN_020200A0(u32 param0, u32 param1);
extern u8 FUN_02020128(u32 param0);
extern void FUN_020202A8(u32 param0, u32 param1);
extern u8 FUN_02020300(u32 param0);
extern void FUN_02020238(u32 param0, u8 param1);
extern u8 FUN_02020240(u32 param0);
extern void FUN_02020310(u32 param0, u32 param1);
extern u16 FUN_0202032C(u32 param0);
extern u32 FUN_02020380(u32 param0);
extern void FUN_02020044(u32 param0, u32 *param1);
extern u32 *FUN_0202011C(u32 param0, u16 *param1, u16 *param2);
extern void FUN_020200EC(u32 param0, u32 param1);
extern u32 *FUN_02020120(u32 param0);
extern void FUN_02020064(u32 param0, s32 *param1);
extern void FUN_02020088(u32 param0, u16 param1);
extern u16 FUN_02020124(u32 param0);
extern void FUN_02020100(u32 param0, u32 param1);
extern void FUN_02020054(u32 param0, u32 *param1);
extern void FUN_02020358(u32 param0, u32 param1);
extern void FUN_02020398(u32 param0, u32 param1);
extern void FUN_02009AC4(u32 param0);
extern void FUN_02009B78(u32 param0);
extern void FUN_020090FC(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
extern void FUN_02009BE8(u32 param0);
extern void FUN_02009168(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
extern void FUN_02009DE0(u32 param0);

THUMB_FUNC struct UnkStruct1 *FUN_0200BB14(u32 heap_id)
{
    struct UnkStruct1 *ptr = AllocFromHeap(heap_id, sizeof(struct UnkStruct1));
    if (ptr == NULL)
    {
        return NULL;
    }

    ptr->unk000 = heap_id;
    ptr->unk004 = 0;
    ptr->unk008 = 1;

    return ptr;
}

THUMB_FUNC struct UnkStruct2 *FUN_0200BB34(struct UnkStruct1 *param0)
{
    GF_ASSERT(param0 != NULL);

    struct UnkStruct2 *ptr = AllocFromHeap(param0->unk000, sizeof(struct UnkStruct2));
    if (ptr == NULL)
    {
        return NULL;
    }

    param0->unk004++;

    for (int i = 0; i < 6; i++)
    {
        ptr->unk0c[i] = 0;
    }

    return ptr;
}

THUMB_FUNC u32 FUN_0200BB68(u32 param0)
{
    return param0 + 0x10;
}

THUMB_FUNC u32 FUN_0200BB6C(struct UnkStruct1 *param0, u32 *param1, u32 *param2, u32 param3)
{
    GF_ASSERT(param0 != NULL);

    if (param0 == NULL)
    {
        return 0;
    }

    u32 st14[4] = { param2[0], param2[1], param2[2], param0->unk000 };

    FUN_0201D060(st14, param2[3], param2[4]);
    FUN_0201E00C(param3, param0->unk000);
    NNS_G2dInitOamManagerModule();

    if (param0->unk008 == 1)
    {
        FUN_02009EAC(param1[0],
            param1[1],
            param1[2],
            param1[3],
            param1[4],
            param1[5],
            param1[6],
            param1[7],
            param0->unk000);
    }

    param0->unk00c = FUN_0201C328(0x20, param0->unk000);
    FUN_0201D168();
    FUN_0201E0BC();

    return 1;
}

THUMB_FUNC u32 FUN_0200BBF0(struct UnkStruct1 *param0, struct UnkStruct2 *param1, u32 param2)
{
    if (param0 == NULL || param1 == NULL)
    {
        return 0;
    }

    param1->unk00 = FUN_02008C9C(param2, param0->unk010, param0->unk000);

    return 1;
}

THUMB_FUNC void FUN_0200BC14(u32 param0)
{
    FUN_0201FFC8(param0);
}

THUMB_FUNC void FUN_0200BC1C(u32 *param0)
{
    GF_ASSERT(param0 != NULL);

    FUN_0201FDEC(*param0);
}

THUMB_FUNC void FUN_0200BC30()
{
    FUN_02009F80();
}

THUMB_FUNC void FUN_0200BC38()
{
    FUN_0201C348();
}

THUMB_FUNC void FUN_0200BC40(struct UnkStruct2 *param0)
{
    FUN_0201FD58(param0->unk00);
}

THUMB_FUNC void FUN_0200BC4C(struct UnkStruct2 *param0)
{
    if (param0->unk04 != 0)
    {
        FUN_02008C80(param0->unk04);
    }
}

THUMB_FUNC void FUN_0200BC5C(struct UnkStruct2 *param0)
{
    for (int i = 0; i < (int)param0->unk54; i++)
    {
        FUN_020096B4(FUN_02009660(param0->unk08, i));
    }

    FreeToHeap(param0->unk08);
    FUN_02009C30(param0->unk24[0]);
    FUN_02009E28(param0->unk24[1]);

    for (int i = 0; i < (int)param0->unk54; i++)
    {
        FUN_02009448(param0->unk24[i]);
        FUN_02008E2C(param0->unk0c[i]);
    }
}

THUMB_FUNC void FUN_0200BCB0(u32 *param0)
{
    FUN_0201C350(param0[3]);
    FUN_0201D12C();
    FUN_0201E08C();

    if (param0[2] == 1)
    {
        FUN_02009FA0();
    }
}

THUMB_FUNC void FUN_0200BCD0(struct UnkStruct1 *param0, struct UnkStruct2 *param1)
{
    param0->unk004--;
    FreeToHeap(param1);
}

THUMB_FUNC void FUN_0200BCE0(struct UnkStruct1 *param0, struct UnkStruct2 *param1)
{
    FUN_0200BC40(param1);
    FUN_0200BC4C(param1);
    FUN_0200BC5C(param1);
    FUN_0200BCD0(param0, param1);
}

THUMB_FUNC void FUN_0200BD04(u32 *param0)
{
    GF_ASSERT(param0[1] == 0);
    FUN_0200BCB0(param0);
    FreeToHeap(param0);
}

THUMB_FUNC u32 FUN_0200BD20(
    struct UnkStruct1 *param0, struct UnkStruct2 *param1, const char **param2)
{
    int st14 = 6;
    const char **st10 = param2;

    if (param0 == NULL || param1 == NULL)
    {
        return 0;
    }

    if (param2[4] == 0)
    {
        st14 = 4;
    }

    param1->unk54 = st14;
    u32 r2 = FUN_0200965C(st14);
    param1->unk08 = AllocFromHeap(param0->unk000, r2 * st14);

    for (int i = 0; i < st14; i++)
    {
        u32 st18 = FUN_02009660(param1->unk08, i);
        void *st1c = FUN_020161A4(param0->unk000, st10[i]);

        FUN_02009668(st1c, st18, param0->unk000);
        FreeToHeap(st1c);
    }

    for (int i = 0; i < st14; i++)
    {
        param1->unk0c[i] =
            FUN_02008DEC(FUN_020096CC(FUN_02009660(param1->unk08, i)), i, param0->unk000);
    }

    for (int i = 0; i < st14; i++)
    {
        u32 st20 = FUN_02009660(param1->unk08, i);
        param1->unk24[i] = FUN_02009424(FUN_020096CC(st20), param0->unk000);
        param1->unk3c[i] = FUN_020093A8(param1->unk0c[i], st20, param1->unk24[i], param0->unk000);
    }

    FUN_02009A90(param1->unk24[0]);
    FUN_02009D34(param1->unk24[1]);
    void *r6 = FUN_020161A4(param0->unk000, st10[6]);
    param1->unk04 = FUN_02008BE0(r6,
        param0->unk000,
        param1->unk0c[0],
        param1->unk0c[1],
        param1->unk0c[2],
        param1->unk0c[3],
        param1->unk0c[4],
        param1->unk0c[5]);
    FreeToHeap(r6);

    return 1;
}

THUMB_FUNC u32 FUN_0200BE38(u32 *param0, u32 *param1, struct UnkStruct3 *param2)
{
    return FUN_0200BE74(param0,
        param1,
        param2->unk00,
        param2->unk04,
        param2->unk06,
        param2->unk04,
        param2->unk0a,
        param2->unk0c,
        param2->unk10,
        param2->unk14,
        param2->unk18,
        param2->unk1c,
        param2->unk20,
        param2->unk24);
}

THUMB_FUNC u32 FUN_0200BE74(u32 *param0,
    u32 *param1,
    u32 param2,
    s16 param3,
    s16 param4,
    s16 param5,
    u16 param6,
    u32 param7,
    u32 param8,
    u32 param9,
    u32 param10,
    u32 param11,
    u32 param12,
    u32 param13)
{
#pragma unused(param10)
#pragma unused(param11)
#pragma unused(param12)
#pragma unused(param13)

    struct UnkStruct4 st0;
    st0.unk00 = param1[0];
    st0.unk04 = &(*(struct UnkStruct7 **)(param1[1]))[param2];

    float r0;
    if (param3 > 0)
    {
        r0 = ((float)(param3 << 0xc) + (float)0.5);
    }
    else
    {
        r0 = ((float)(param3 << 0xc) - (float)0.5);
    }
    st0.unk08 = (s32)r0;

    if (param4 > 0)
    {
        r0 = ((float)(param4 << 0xc) + (float)0.5);
    }
    else
    {
        r0 = ((float)(param4 << 0xc) - (float)0.5);
    }
    st0.unk0c = (s32)r0;

    if (param5 > 0)
    {
        r0 = ((float)(param5 << 0xc) + (float)0.5);
    }
    else
    {
        r0 = ((float)(param5 << 0xc) - (float)0.5);
    }
    st0.unk10 = (s32)r0;

    if (param9 == 2)
    {
        st0.unk0c += 0xC0000;
    }

    st0.unk14 = 0x1000;
    st0.unk18 = 0x1000;
    st0.unk1c = 0x1000;
    st0.unk20 = 0;
    st0.unk24 = param7;
    st0.unk28 = param9;
    st0.unk2c = param0[0];

    u32 r4 = FUN_0201FE94(&st0);
    if (r4 != 0)
    {
        FUN_02020130(r4, param6);

        FUN_02020248(r4, param8);
    }

    return r4;
}

THUMB_FUNC u32 FUN_0200BF60(struct UnkStruct1 *param0, struct UnkStruct2 *param1, u32 *param2)
{
    struct UnkStruct1 *st0 = param0;
    int i;
    int st4 = 6;

    if (st0 == NULL || param1 == NULL)
    {
        return 0;
    }

    if (param2[4] == 0 || param2[5] == 0)
    {
        st4 = 4;
    }

    param1->unk54 = st4;

    for (i = 0; i < st4; i++)
    {
        param1->unk0c[i] = FUN_02008DEC(param2[i], i, st0->unk000);
    }

    for (i = 0; i < st4; i++)
    {
        if (param2[i] != 0)
        {
            param1->unk24[i] = FUN_02009424(param2[i], st0->unk000);
            param1->unk3c[i] = 0;

            for (int j = 0; j < (int)((u32 *)param1->unk24[i])[1]; j++)
            {
                ((u32 *)(((u32 *)param1->unk24[i])[0]))[j] = 0;
            }
        }
    }

    return 1;
}

THUMB_FUNC u32 FUN_0200C00C(
    u32 *param0, struct UnkStruct2 *param1, u32 param2, u32 param3, u32 param4, u32 param5, s32 param6)
{
    if (FUN_0200945C(param1->unk0c[0], param6) == 0)
    {
        return 0;
    }

    u32 r5 = FUN_02008F34(param1->unk0c[0], param2, param3, param4, param6, param5, param0[0]);
    if (r5 != 0)
    {
        FUN_02009B04(r5);
        FUN_0200C474(param1->unk24[0], r5);
        return 1;
    }

    GF_AssertFail();
    if (r5 != 0)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC s32 FUN_0200C06C(u32 *param0,
    struct UnkStruct2 *param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    s32 param7)
{
    if (FUN_0200945C(param1->unk0c[1], param7) == 0)
    {
        return -1;
    }

    u32 r5 = FUN_02008FEC(param1->unk0c[1], param2, param3, param4, param7, param6, param5, param0[0]);
    if (r5 != 0)
    {
        GF_ASSERT(FUN_02009D68(r5) == 1);
        FUN_0200C474(param1->unk24[1], r5);
        return (s8)FUN_02009E88(r5, param6);
    }

    GF_AssertFail();
    return -1;
}

THUMB_FUNC u8 FUN_0200C0DC(u32 param0,
    u32 param1,
    u32 *param2,
    struct UnkStruct2 *param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8,
    s32 param9)
{
    s32 r4 = FUN_0200C06C(param2, param3, param4, param5, param6, param7, param8, param9);
    if (r4 != -1)
    {
        FUN_02003108(param0, param1, (u16)(r4 << 4), param7 << 5);
    }

    return (u8)r4;
}

THUMB_FUNC u32 FUN_0200C124(
    u32 *param0, struct UnkStruct2 *param1, u32 param2, u32 param3, u32 param4, s32 param5)
{
    return FUN_0200C404(param0, param1, param2, param3, param4, 2, param5);
}

THUMB_FUNC u32 FUN_0200C13C(
    u32 *param0, struct UnkStruct2 *param1, u32 param2, u32 param3, u32 param4, s32 param5)
{
    return FUN_0200C404(param0, param1, param2, param3, param4, 3, param5);
}

THUMB_FUNC struct UnkStruct5 *FUN_0200C154(
    struct UnkStruct1 *param0, struct UnkStruct2 *param1, u32 *param2)
{
    struct UnkStruct4 st44;
    s32 st2c[6];

    struct UnkStruct5 *ptr = AllocFromHeap(param0->unk000, sizeof(struct UnkStruct5));
    if (ptr == NULL)
    {
        return 0;
    }

    ptr->unk08 = AllocFromHeap(param0->unk000, sizeof(struct UnkStruct6));
    if (ptr->unk08 == 0)
    {
        return 0;
    }

    ptr->unk08->unk0 = AllocFromHeap(param0->unk000, sizeof(struct UnkStruct7));
    ptr->unk04 = ptr->unk08->unk0;
    if (ptr->unk08->unk0 == NULL)
    {
        if (ptr->unk08 != NULL)
        {
            FreeToHeap(ptr->unk08);
        }

        return 0;
    }

    for (int i = 0; i < 6; i++)
    {
        st2c[i] = (s32)param2[5 + i];
    }

    if (param1->unk0c[4] == 0 || param1->unk0c[5] == 0)
    {
        st2c[4] = -1;
        st2c[5] = -1;
    }
    else
    {
        if (st2c[4] != -1 && FUN_0200945C(param1->unk0c[4], st2c[4]) == 0)
        {
            st2c[4] = -1;
        }

        if (st2c[5] != -1 && FUN_0200945C(param1->unk0c[5], st2c[5]) == 0)
        {
            st2c[5] = -1;
        }
    }

    FUN_02008AA4(ptr->unk04,
        st2c[0],
        st2c[1],
        st2c[2],
        st2c[3],
        st2c[4],
        st2c[5],
        param2[12],
        param2[11],
        param1->unk0c[0],
        param1->unk0c[1],
        param1->unk0c[2],
        param1->unk0c[3],
        param1->unk0c[4],
        param1->unk0c[5]);

    st44.unk00 = param1->unk00;
    st44.unk04 = ptr->unk04;
    float r0;
    if (((s16 *)param2)[0] > 0)
    {
        r0 = ((float)(((s16 *)param2)[0] << 0xc) + (float)0.5);
    }
    else
    {
        r0 = ((float)(((s16 *)param2)[0] << 0xc) - (float)0.5);
    }
    st44.unk08 = (s32)r0;

    if (((s16 *)param2)[1] > 0)
    {
        r0 = ((float)(((s16 *)param2)[1] << 0xc) + (float)0.5);
    }
    else
    {
        r0 = ((float)(((s16 *)param2)[1] << 0xc) - (float)0.5);
    }
    st44.unk0c = (s32)r0;

    if (((s16 *)param2)[2] > 0)
    {
        r0 = ((float)(((s16 *)param2)[2] << 0xc) + (float)0.5);
    }
    else
    {
        r0 = ((float)(((s16 *)param2)[2] << 0xc) - (float)0.5);
    }
    st44.unk10 = (s32)r0;

    if (param2[4] == 2)
    {
        st44.unk0c += 0xC0000;
    }

    st44.unk14 = 0x1000;
    st44.unk18 = 0x1000;
    st44.unk1c = 0x1000;
    st44.unk20 = 0;
    st44.unk24 = param2[2];
    st44.unk28 = param2[4];
    st44.unk2c = param0->unk000;

    ptr->unk00 = FUN_0201FE94(&st44);
    ptr->unk0c = param2[12];

    if (ptr->unk00 != 0)
    {
        u8 r6 = FUN_020202A0(ptr->unk00);

        FUN_02020130(ptr->unk00, ((u16 *)param2)[3]);
        FUN_02020248(ptr->unk00, r6 + param2[3]);
    }
    else
    {
        GF_AssertFail();
    }

    return ptr;
}

THUMB_FUNC u32 FUN_0200C334(u32 *param0, u32 param1)
{
    return FUN_02009E54(FUN_020094F0(param0[4], param1), 0);
}

THUMB_FUNC u32 FUN_0200C344(u32 *param0, u32 param1, u32 param2)
{
    return FUN_02009E88(FUN_020094F0(param0[4], param1), param2);
}

THUMB_FUNC u32 FUN_0200C358(struct UnkStruct2 *param0, u32 param1)
{
    return FUN_0200C4F4(param0->unk0c[0], param0->unk24[0], param1);
}

THUMB_FUNC u32 FUN_0200C368(struct UnkStruct2 *param0, u32 param1)
{
    return FUN_0200C548(param0->unk0c[1], param0->unk24[1], param1);
}

THUMB_FUNC u32 FUN_0200C378(struct UnkStruct2 *param0, u32 param1)
{
    return FUN_0200C4A8(param0->unk0c[2], param0->unk24[2], param1);
}

THUMB_FUNC u32 FUN_0200C388(struct UnkStruct2 *param0, u32 param1)
{
    return FUN_0200C4A8(param0->unk0c[3], param0->unk24[3], param1);
}

THUMB_FUNC void FUN_0200C398(struct UnkStruct1 *param0, struct UnkStruct2 *param1)
{
    FUN_0200BC40(param1);
    FUN_02009C30(param1->unk24[0]);
    FUN_02009E28(param1->unk24[1]);

    for (int i = 0; i < (int)param1->unk54; i++)
    {
        FUN_02009448(param1->unk24[i]);
        FUN_02008E2C(param1->unk0c[i]);
    }

    FUN_0200BCD0(param0, param1);
}

THUMB_FUNC void FUN_0200C3DC(u32 *param0)
{
    if (param0[3] != 0)
    {
        FUN_02009CDC(*(u32 *)param0[1]);
    }

    FUN_0201FFC8(param0[0]);
    FUN_02008C80(param0[2]);
    FreeToHeap(param0);
}

THUMB_FUNC u32 FUN_0200C404(
    u32 *param0, struct UnkStruct2 *param1, u32 param2, u32 param3, u32 param4, u32 param5, s32 param6)
{
    if (FUN_0200945C(param1->unk0c[param5], param6) == 0)
    {
        return 0;
    }

    u32 r5 = FUN_020090AC(param1->unk0c[param5], param2, param3, param4, param6, param5, param0[0]);
    if (r5 != 0)
    {
        u32 r4 = FUN_0200C474(param1->unk24[param5], r5);
        GF_ASSERT(r4 == 1);
        return r4;
    }
    GF_AssertFail();
    if (r5 != 0)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC u32 FUN_0200C474(u32 *param0, u32 param1)
{
    for (int i = 0; i < (int)param0[1]; i++)
    {
        if (((u32 *)param0[0])[i] == 0)
        {
            ((u32 *)param0[0])[i] = param1;
            param0[2]++;
            return TRUE;
        }
    }

    return FALSE;
}

THUMB_FUNC u32 FUN_0200C4A8(u32 param0, u32 *param1, u32 param2)
{
    for (int i = 0; i < (int)param1[1]; i++)
    {
        if (((u32 *)param1[0])[i] != 0)
        {
            u32 r0 = FUN_02009530(((u32 *)param1[0])[i]);
            if (r0 == param2)
            {

                FUN_02009490(param0, ((u32 *)param1[0])[i]);
                ((u32 *)param1[0])[i] = 0;
                param1[2]--;

                return 1;
            }
        }
    }

    return 0;
}

THUMB_FUNC u32 FUN_0200C4F4(u32 param0, u32 *param1, u32 param2)
{
    for (int i = 0; i < (int)param1[1]; i++)
    {
        if (((u32 *)param1[0])[i] != 0)
        {
            u32 r0 = FUN_02009530(((u32 *)param1[0])[i]);
            if (r0 == param2)
            {
                FUN_0201D324(param2);

                FUN_02009490(param0, ((u32 *)param1[0])[i]);
                ((u32 *)param1[0])[i] = 0;
                param1[2]--;

                return 1;
            }
        }
    }

    return 0;
}

THUMB_FUNC u32 FUN_0200C548(u32 param0, u32 *param1, u32 param2)
{
    for (int i = 0; i < (int)param1[1]; i++)
    {
        if (((u32 *)param1[0])[i] != 0)
        {
            u32 r0 = FUN_02009530(((u32 *)param1[0])[i]);
            if (r0 == param2)
            {
                FUN_0201E1C8(param2);

                FUN_02009490(param0, ((u32 *)param1[0])[i]);
                ((u32 *)param1[0])[i] = 0;
                param1[2]--;

                return 1;
            }
        }
    }

    return 0;
}

THUMB_FUNC void FUN_0200C59C(u32 param0)
{
    FUN_020201E4(param0, 0x1000);
}

THUMB_FUNC void FUN_0200C5A8(u32 *param0)
{
    FUN_0200C59C(param0[0]);
}

THUMB_FUNC void FUN_0200C5B4(u32 *param0, u32 param1)
{
    FUN_020201E4(param0[0], param1);
}

THUMB_FUNC void FUN_0200C5C0(u32 *param0, u32 param1)
{
    FUN_02020130(param0[0], param1);
}

THUMB_FUNC u32 FUN_0200C5CC(u32 *param0)
{
    return FUN_020201DC(param0[0]);
}

THUMB_FUNC void FUN_0200C5D8(u32 param0, u32 param1)
{
    FUN_020200BC(param0, param1);
}

THUMB_FUNC void FUN_0200C5E0(u32 *param0, u32 param1)
{
    FUN_0200C5D8(param0[0], param1);
}

THUMB_FUNC void FUN_0200C5EC(u32 param0, u32 param1)
{
    FUN_020200D8(param0, param1);
}

THUMB_FUNC void FUN_0200C5F4(u32 *param0, u32 param1)
{
    FUN_0200C5EC(*param0, param1);
}

THUMB_FUNC u32 FUN_0200C600(u32 param0)
{
    return FUN_02020388(param0);
}

THUMB_FUNC u32 FUN_0200C608(u32 *param0)
{
    return FUN_0200C600(*param0);
}

THUMB_FUNC void FUN_0200C614(u32 param0)
{
    FUN_02020208(param0);
}

THUMB_FUNC void FUN_0200C61C(u32 *param0)
{
    FUN_0200C614(*param0);
}

THUMB_FUNC void FUN_0200C628(u32 param0)
{
    FUN_0202022C(param0);
}

THUMB_FUNC void FUN_0200C630(u32 *param0)
{
    FUN_0200C628(*param0);
}

THUMB_FUNC void FUN_0200C63C(u32 param0, u32 param1)
{
    FUN_020200A0(param0, param1);
}

THUMB_FUNC void FUN_0200C644(u32 *param0, u32 param1)
{
    FUN_0200C63C(*param0, param1);
}

THUMB_FUNC u8 FUN_0200C650(u32 param0)
{
    return FUN_02020128(param0);
}

THUMB_FUNC u8 FUN_0200C658(u32 *param0)
{
    return FUN_0200C650(*param0);
}

THUMB_FUNC void FUN_0200C664(u32 param0, u32 param1)
{
    FUN_02020248(param0, param1);
}

THUMB_FUNC void FUN_0200C66C(u32 *param0, u32 param1)
{
    FUN_0200C664(*param0, param1);
}

THUMB_FUNC void FUN_0200C678(u32 param0, u32 param1)
{
    FUN_020202A8(param0, param1);
}

THUMB_FUNC void FUN_0200C680(u32 *param0, u32 param1)
{
    FUN_0200C678(*param0, param1);
}

THUMB_FUNC u8 FUN_0200C68C(u32 *param0)
{
    return FUN_02020300(*param0);
}

THUMB_FUNC void FUN_0200C698(u32 param0, u32 param1)
{
    FUN_02020238(param0, (u8)param1);
}

THUMB_FUNC u8 FUN_0200C6A4(u32 *param0)
{
    return FUN_02020240(*param0);
}

THUMB_FUNC void FUN_0200C6B0(u32 *param0, u32 param1)
{
    FUN_0200C698(*param0, param1);
}

THUMB_FUNC void FUN_0200C6BC(u32 param0, u32 param1)
{
    FUN_02020310(param0, param1);
}

THUMB_FUNC void FUN_0200C6C4(u32 *param0, u32 param1)
{
    FUN_0200C6BC(*param0, param1);
}

THUMB_FUNC u16 FUN_0200C6D0(u32 param0)
{
    return FUN_0202032C(param0);
}

THUMB_FUNC u16 FUN_0200C6D8(u32 *param0)
{
    return FUN_0200C6D0(*param0);
}

THUMB_FUNC void FUN_0200C6E4(u32 param0, u32 param1, u32 param2)
{
    u32 st0[3];
    st0[0] = param1 << 12;
    st0[1] = param2 << 12;
    if (FUN_02020380(param0) == 2)
    {
        st0[1] += 0xc0000;
    }
    st0[2] = 0;

    FUN_02020044(param0, st0);
}

THUMB_FUNC void FUN_0200C714(u32 *param0, u32 param1, u32 param2)
{
    FUN_0200C6E4(*param0, param1, param2);
}

THUMB_FUNC void FUN_0200C720(u32 param0, u32 param1, u32 param2, u32 param3)
{
    u32 st0[3];

    st0[0] = param1 << 12;
    st0[1] = param2 << 12;
    if (FUN_02020380(param0) == 2)
    {
        st0[1] += param3;
    }
    st0[2] = 0;

    FUN_02020044(param0, st0);
}

THUMB_FUNC void FUN_0200C750(u32 *param0, u32 param1, u32 param2, u32 param3)
{
    FUN_0200C720(*param0, param1, param2, param3);
}

THUMB_FUNC void FUN_0200C75C(u32 param0, u16 *param1, u16 *param2)
{
    u32 *r4 = FUN_0202011C(param0, param1, param2);

    param1[0] = (u16)((int)(r4[0] + ((u32)((int)r4[0] >> 0xb) >> 0x14)) >> 0xc);

    if (FUN_02020380(param0) == 2)
    {
        u32 r1 = r4[1] - 0xc0000;

        param2[0] = (u16)((int)(r1 + ((u32)((int)r1 >> 0xb) >> 0x14)) >> 0xc);

        return;
    }

    param2[0] = (u16)((int)(r4[1] + ((u32)((int)r4[1] >> 0xb) >> 0x14)) >> 0xc);
}

THUMB_FUNC void FUN_0200C7A0(u32 *param0, u16 *param1, u16 *param2)
{
    FUN_0200C75C(*param0, param1, param2);
}

THUMB_FUNC void FUN_0200C7AC(u32 param0, u16 *param1, u16 *param2, u32 param3)
{
    u32 *r4 = FUN_0202011C(param0, param1, param2);

    param1[0] = (u16)((int)(r4[0] + ((u32)((int)r4[0] >> 0xb) >> 0x14)) >> 0xc);

    if (FUN_02020380(param0) == 2)
    {
        u32 r1 = r4[1] - param3;

        param2[0] = (u16)((int)(r1 + ((u32)((int)r1 >> 0xb) >> 0x14)) >> 0xc);

        return;
    }

    param2[0] = (u16)((int)(r4[1] + ((u32)((int)r4[1] >> 0xb) >> 0x14)) >> 0xc);
}

THUMB_FUNC void FUN_0200C7F0(u32 *param0, u16 *param1, u16 *param2, u32 param3)
{
    FUN_0200C7AC(*param0, param1, param2, param3);
}

THUMB_FUNC void FUN_0200C7FC(u32 param0, u16 *param1, u16 *param2)
{
    u32 st0[3];

    u32 *r0 = FUN_0202011C(param0, param1, param2);

    st0[0] = r0[0] + ((u32)param1 << 0xc);
    st0[1] = r0[1] + ((u32)param2 << 0xc);
    st0[2] = r0[2];

    FUN_02020044(param0, st0);
}

THUMB_FUNC void FUN_0200C82C(u32 *param0, u16 *param1, u16 *param2)
{
    FUN_0200C7FC(*param0, param1, param2);
}

THUMB_FUNC void FUN_0200C838(u32 param0, u32 param1)
{
    FUN_020200EC(param0, param1);
}

THUMB_FUNC void FUN_0200C840(u32 *param0, u32 param1)
{
    FUN_0200C838(*param0, param1);
}

THUMB_FUNC void FUN_0200C84C(u32 param0, f32 param1, f32 param2)
{
    s32 *r4 = FUN_02020120(param0);

    r4[0] = (s32)(param1 * 0x1000);
    r4[1] = (s32)(param2 * 0x1000);

    FUN_02020064(param0, r4);
}

THUMB_FUNC void FUN_0200C884(u32 *param0, f32 param1, f32 param2)
{
    FUN_0200C84C(*param0, param1, param2);
}

THUMB_FUNC void FUN_0200C890(u32 param0, u16 param1)
{
    FUN_02020088(param0, param1);
}

THUMB_FUNC void FUN_0200C898(u32 *param0, u16 param1)
{
    FUN_0200C890(*param0, param1);
}

THUMB_FUNC void FUN_0200C8A4(u32 param0, u32 param1)
{
    u16 r0 = FUN_02020124(param0);
    r0 += param1;
    FUN_02020088(param0, r0);
}

THUMB_FUNC void FUN_0200C8BC(u32 *param0, u32 param1)
{
    FUN_0200C8A4(*param0, param1);
}

THUMB_FUNC void FUN_0200C8C8(u32 param0, u32 param1)
{
    FUN_02020100(param0, param1);
}

THUMB_FUNC void FUN_0200C8D0(u32 *param0, u32 param1)
{
    FUN_0200C8C8(*param0, param1);
}

THUMB_FUNC void FUN_0200C8DC(u32 *param0, u32 param1, u32 param2)
{
    u32 st0[3];
    st0[0] = param1 << 12;
    st0[1] = param2 << 12;
    st0[2] = 0;

    FUN_02020054(*param0, st0);
}

THUMB_FUNC void FUN_0200C8F8(u32 *param0, u32 param1)
{
    FUN_02020358(*param0, param1);
}

THUMB_FUNC void FUN_0200C904(u32 param0, u32 param1)
{
    FUN_02020398(param0, param1);
}

THUMB_FUNC void FUN_0200C90C(u32 *param0, u32 param1)
{
    FUN_0200C904(*param0, param1);
}

THUMB_FUNC u32 FUN_0200C918(
    u32 *param0, struct UnkStruct2 *param1, u32 param2, u32 param3, u32 param4, u32 param5, s32 param6)
{
    if (FUN_0200945C(param1->unk0c[0], param6) == 0)
    {
        return 0;
    }

    u32 r5 = FUN_02008F34(param1->unk0c[0], param2, param3, param4, param6, param5, param0[0]);
    if (r5 != 0)
    {
        FUN_02009AC4(r5);
        FUN_0200C474(param1->unk24[0], r5);

        return 1;
    }

    GF_AssertFail();
    if (r5 != 0)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC u32 FUN_0200C978(
    u32 *param0, struct UnkStruct2 *param1, u32 param2, u32 param3, u32 param4, u32 param5, s32 param6)
{
    if (FUN_0200945C(param1->unk0c[0], param6) == 0)
    {
        return 0;
    }

    u32 r5 = FUN_02008F34(param1->unk0c[0], param2, param3, param4, param6, param5, param0[0]);
    if (r5 != 0)
    {
        FUN_02009B78(r5);
        FUN_0200C474(param1->unk24[0], r5);

        return 1;
    }

    GF_AssertFail();
    if (r5 != 0)
    {
        return 1;
    }

    return 0;
}

THUMB_FUNC void FUN_0200C9D8(
    u32 *param0, u32 *param1, u32 param2, u32 param3, u32 param4, u32 param5)
{
    u32 r6 = FUN_020094F0(param1[3], param5);
    FUN_020090FC(param1[3], r6, param2, param3, param4, param0[0]);

    FUN_02009BE8(r6);
}

THUMB_FUNC void FUN_0200CA0C(
    u32 *param0, u32 *param1, u32 param2, u32 param3, u32 param4, u32 param5)
{
    u32 r6 = FUN_020094F0(param1[4], param5);
    FUN_02009168(param1[4], r6, param2, param3, param4, param0[0]);

    FUN_02009DE0(r6);
}

THUMB_FUNC u32 FUN_0200CA40(u32 *param0)
{
    return *param0;
}
