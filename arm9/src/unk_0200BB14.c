#include "global.h"
#include "unk_0200BB14.h"
#include "game_init.h"
#include "heap.h"
#include "unk_02008AA4.h"
#include "unk_02008DEC.h"
#include "oam.h"

extern void sub_0201D060(u32 *param0, u32 param1, u32 param2);
extern void sub_0201E00C(u32 param0, HeapID heapId);
extern void NNS_G2dInitOamManagerModule();
extern u32 sub_0201C328(u32 param0, u32 param1);
extern void sub_0201D168();
extern void sub_0201E0BC();
extern void sub_0201FFC8(u32 param0);
extern void sub_0201FDEC(u32 param0);
extern void sub_0201C348();
extern void sub_0201FD58(u32 param0);
extern void sub_0201C350(u32 param0);
extern void sub_0201D12C();
extern void sub_0201E08C();
extern u32 sub_0201FE94(struct UnkStruct_0200BB14_4 *param0);
extern void sub_02020130(u32 param0, u32 param1);
extern void sub_02020248(u32 param0, u32 param1);
extern void sub_02003108(u32 param0, u32 param1, u16 param2, u32 param3);
extern u8 sub_020202A0(u32 param0);
extern void sub_0201D324(u32 param0);
extern void sub_0201E1C8(u32 param0);
extern void sub_020201E4(u32 param0, u32 param1);
extern u32 sub_020201DC(u32 param0);
extern void sub_020200BC(u32 param0, u32 param1);
extern void sub_020200D8(u32 param0, u32 param1);
extern u32 sub_02020388(u32 param0);
extern void sub_02020208(u32 param0);
extern void sub_0202022C(u32 param0);
extern void sub_020200A0(u32 param0, u32 param1);
extern u8 sub_02020128(u32 param0);
extern void sub_020202A8(u32 param0, u32 param1);
extern u8 sub_02020300(u32 param0);
extern void sub_02020238(u32 param0, u8 param1);
extern u8 sub_02020240(u32 param0);
extern void sub_02020310(u32 param0, u32 param1);
extern u16 sub_0202032C(u32 param0);
extern u32 sub_02020380(u32 param0);
extern void sub_02020044(u32 param0, u32 *param1);
extern u32 *sub_0202011C(u32 param0, u16 *param1, u16 *param2);
extern void sub_020200EC(u32 param0, u32 param1);
extern u32 *sub_02020120(u32 param0);
extern void sub_02020064(u32 param0, s32 *param1);
extern void sub_02020088(u32 param0, u16 param1);
extern u16 sub_02020124(u32 param0);
extern void sub_02020100(u32 param0, u32 param1);
extern void sub_02020054(u32 param0, u32 *param1);
extern void sub_02020358(u32 param0, u32 param1);
extern void sub_02020398(u32 param0, u32 param1);

struct UnkStruct_0200BB14_1 *sub_0200BB14(HeapID heapId)
{
    struct UnkStruct_0200BB14_1 *ptr = AllocFromHeap(heapId, sizeof(struct UnkStruct_0200BB14_1));
    if (ptr == NULL)
    {
        return NULL;
    }

    ptr->heapId = heapId;
    ptr->unk004 = 0;
    ptr->unk008 = 1;

    return ptr;
}

struct UnkStruct_0200BB14_2 *sub_0200BB34(struct UnkStruct_0200BB14_1 *param0)
{
    GF_ASSERT(param0 != NULL);

    struct UnkStruct_0200BB14_2 *ptr =
        AllocFromHeap(param0->heapId, sizeof(struct UnkStruct_0200BB14_2));
    if (ptr == NULL)
    {
        return NULL;
    }

    param0->unk004++;

    for (s32 i = 0; i < 6; i++)
    {
        ptr->unk0c[i] = 0;
    }

    return ptr;
}

u32 sub_0200BB68(u32 param0)
{
    return param0 + 0x10;
}

BOOL sub_0200BB6C(
    struct UnkStruct_0200BB14_1 *param0, u32 *param1, u32 *param2, u32 param3)
{
    GF_ASSERT(param0 != NULL);

    if (param0 == NULL)
    {
        return FALSE;
    }

    u32 st14[4] = { param2[0], param2[1], param2[2], param0->heapId };

    sub_0201D060(st14, param2[3], param2[4]);
    sub_0201E00C(param3, param0->heapId);
    NNS_G2dInitOamManagerModule();

    if (param0->unk008 == 1)
    {
        sub_02009EAC(param1[0],
            param1[1],
            param1[2],
            param1[3],
            param1[4],
            param1[5],
            param1[6],
            param1[7],
            param0->heapId);
    }

    param0->unk00c = sub_0201C328(0x20, param0->heapId);
    sub_0201D168();
    sub_0201E0BC();

    return TRUE;
}

BOOL sub_0200BBF0(
    struct UnkStruct_0200BB14_1 *param0, struct UnkStruct_0200BB14_2 *param1, u32 param2)
{
    if (param0 == NULL || param1 == NULL)
    {
        return FALSE;
    }

    param1->unk00 = sub_02008C9C(param2, param0->unk010, param0->heapId);

    return TRUE;
}

void sub_0200BC14(u32 param0)
{
    sub_0201FFC8(param0);
}

void sub_0200BC1C(u32 *param0)
{
    GF_ASSERT(param0 != NULL);

    sub_0201FDEC(*param0);
}

void sub_0200BC30()
{
    ApplyAndResetOamManagerBuffer();
}

void sub_0200BC38()
{
    sub_0201C348();
}

void sub_0200BC40(struct UnkStruct_0200BB14_2 *param0)
{
    sub_0201FD58(param0->unk00);
}

void sub_0200BC4C(struct UnkStruct_0200BB14_2 *param0)
{
    if (param0->unk04 != 0)
    {
        sub_02008C80(param0->unk04);
    }
}

void sub_0200BC5C(struct UnkStruct_0200BB14_2 *param0)
{
    for (s32 i = 0; i < param0->unk54; i++)
    {
        sub_020096B4(sub_02009660(param0->unk08, i));
    }

    FreeToHeap(param0->unk08);
    sub_02009C30(param0->unk24[0]);
    sub_02009E28(param0->unk24[1]);

    for (s32 i = 0; i < param0->unk54; i++)
    {
        sub_02009448(param0->unk24[i]);
        sub_02008E2C(param0->unk0c[i]);
    }
}

void sub_0200BCB0(u32 *param0)
{
    sub_0201C350(param0[3]);
    sub_0201D12C();
    sub_0201E08C();

    if (param0[2] == 1)
    {
        DeinitOamData();
    }
}

void sub_0200BCD0(
    struct UnkStruct_0200BB14_1 *param0, struct UnkStruct_0200BB14_2 *param1)
{
    param0->unk004--;
    FreeToHeap(param1);
}

void sub_0200BCE0(
    struct UnkStruct_0200BB14_1 *param0, struct UnkStruct_0200BB14_2 *param1)
{
    sub_0200BC40(param1);
    sub_0200BC4C(param1);
    sub_0200BC5C(param1);
    sub_0200BCD0(param0, param1);
}

void sub_0200BD04(u32 *param0)
{
    GF_ASSERT(param0[1] == 0);
    sub_0200BCB0(param0);
    FreeToHeap(param0);
}

BOOL sub_0200BD20(
    struct UnkStruct_0200BB14_1 *param0, struct UnkStruct_0200BB14_2 *param1, const char **param2)
{
    s32 st14 = 6;
    const char **st10 = param2;

    if (param0 == NULL || param1 == NULL)
    {
        return FALSE;
    }

    if (param2[4] == 0)
    {
        st14 = 4;
    }

    param1->unk54 = st14;
    u32 r2 = sub_0200965C();
    param1->unk08 = AllocFromHeap(param0->heapId, r2 * st14);

    for (s32 i = 0; i < st14; i++)
    {
        struct UnkStruct_02008DEC_2 *st18 = sub_02009660(param1->unk08, i);
        void *st1c = AllocAndReadFile(param0->heapId, st10[i]);

        sub_02009668(st1c, st18, param0->heapId);
        FreeToHeap(st1c);
    }

    for (s32 i = 0; i < st14; i++)
    {
        param1->unk0c[i] =
            sub_02008DEC(sub_020096CC(sub_02009660(param1->unk08, i)), i, param0->heapId);
    }

    for (s32 i = 0; i < st14; i++)
    {
        struct UnkStruct_02008DEC_2 *st20 = sub_02009660(param1->unk08, i);
        param1->unk24[i] = sub_02009424(sub_020096CC(st20), param0->heapId);
        param1->unk3c[i] = sub_020093A8(param1->unk0c[i], st20, param1->unk24[i], param0->heapId);
    }

    sub_02009A90(param1->unk24[0]);
    sub_02009D34(param1->unk24[1]);
    struct UnkStruct_02008AA4_2 *r6 = AllocAndReadFile(param0->heapId, st10[6]);
    param1->unk04 = sub_02008BE0(r6,
        param0->heapId,
        param1->unk0c[0],
        param1->unk0c[1],
        param1->unk0c[2],
        param1->unk0c[3],
        param1->unk0c[4],
        param1->unk0c[5]);
    FreeToHeap(r6);

    return TRUE;
}

u32 sub_0200BE38(u32 *param0, u32 *param1, struct UnkStruct_0200BB14_3 *param2)
{
    return sub_0200BE74(param0,
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

u32 sub_0200BE74(u32 *param0,
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

    struct UnkStruct_0200BB14_4 st0;
    st0.unk00 = param1[0];
    st0.unk04 = &(*(struct UnkStruct_0200BB14_sub **)(param1[1]))[param2];

    f32 r0;
    if (param3 > 0)
    {
        r0 = ((f32)(param3 * 0x1000) + (f32)0.5);
    }
    else
    {
        r0 = ((f32)(param3 * 0x1000) - (f32)0.5);
    }
    st0.unk08 = (s32)r0;

    if (param4 > 0)
    {
        r0 = ((f32)(param4 * 0x1000) + (f32)0.5);
    }
    else
    {
        r0 = ((f32)(param4 * 0x1000) - (f32)0.5);
    }
    st0.unk0c = (s32)r0;

    if (param5 > 0)
    {
        r0 = ((f32)(param5 * 0x1000) + (f32)0.5);
    }
    else
    {
        r0 = ((f32)(param5 * 0x1000) - (f32)0.5);
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

    u32 r4 = sub_0201FE94(&st0);
    if (r4 != 0)
    {
        sub_02020130(r4, param6);

        sub_02020248(r4, param8);
    }

    return r4;
}

BOOL sub_0200BF60(
    struct UnkStruct_0200BB14_1 *param0, struct UnkStruct_0200BB14_2 *param1, s32 *param2)
{
    struct UnkStruct_0200BB14_1 *st0 = param0;
    s32 i;
    s32 st4 = 6;

    if (st0 == NULL || param1 == NULL)
    {
        return FALSE;
    }

    if (param2[4] == 0 || param2[5] == 0)
    {
        st4 = 4;
    }

    param1->unk54 = st4;

    for (i = 0; i < st4; i++)
    {
        param1->unk0c[i] = sub_02008DEC(param2[i], i, st0->heapId);
    }

    for (i = 0; i < st4; i++)
    {
        if (param2[i] != 0)
        {
            param1->unk24[i] = sub_02009424(param2[i], st0->heapId);
            param1->unk3c[i] = 0;

            for (s32 j = 0; j < param1->unk24[i]->unk04; j++)
            {
                param1->unk24[i]->unk00[j] = NULL;
            }
        }
    }

    return TRUE;
}

BOOL sub_0200C00C(HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5,
    s32 param6)
{
    if (sub_0200945C(param1->unk0c[0], param6) == 0)
    {
        return FALSE;
    }

    struct UnkStruct_02008DEC_sub *r5 = sub_02008F34(param1->unk0c[0], param2, param3, param4, param6, param5, *heapId);
    if (r5 != NULL)
    {
        sub_02009B04(r5);
        sub_0200C474(param1->unk24[0], r5);
        return TRUE;
    }

    GF_ASSERT(0);
    return r5 != NULL ? TRUE : FALSE;
}

s32 sub_0200C06C(HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5,
    u32 param6,
    s32 param7)
{
    if (sub_0200945C(param1->unk0c[1], param7) == 0)
    {
        return -1;
    }

    struct UnkStruct_02008DEC_sub * r5 =
        sub_02008FEC(param1->unk0c[1], param2, param3, param4, param7, param6, param5, *heapId);
    if (r5 != NULL)
    {
        GF_ASSERT(sub_02009D68(r5) == 1);
        sub_0200C474(param1->unk24[1], r5);
        return (s8)sub_02009E88(r5, param6);
    }

    GF_ASSERT(FALSE);
    return -1;
}

u8 sub_0200C0DC(u32 param0,
    u32 param1,
    HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param3,
    NarcId param4,
    s32 param5,
    BOOL param6,
    u32 param7,
    u32 param8,
    s32 param9)
{
    s32 r4 = sub_0200C06C(heapId, param3, param4, param5, param6, param7, param8, param9);
    if (r4 != -1)
    {
        sub_02003108(param0, param1, (u16)(r4 << 4), param7 << 5);
    }

    return (u8)r4;
}

BOOL sub_0200C124(HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    s32 param5)
{
    return sub_0200C404(heapId, param1, param2, param3, param4, 2, param5);
}

BOOL sub_0200C13C(HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    s32 param5)
{
    return sub_0200C404(heapId, param1, param2, param3, param4, 3, param5);
}

struct UnkStruct_0200BB14_5 *sub_0200C154(
    struct UnkStruct_0200BB14_1 *param0, struct UnkStruct_0200BB14_2 *param1, u32 *param2)
{
    struct UnkStruct_0200BB14_4 st44;
    s32 st2c[6];

    struct UnkStruct_0200BB14_5 *ptr =
        AllocFromHeap(param0->heapId, sizeof(struct UnkStruct_0200BB14_5));
    if (ptr == NULL)
    {
        return NULL;
    }

    ptr->unk08 = AllocFromHeap(param0->heapId, sizeof(struct UnkStruct_0200BB14_6));
    if (ptr->unk08 == 0)
    {
        return NULL;
    }

    ptr->unk08->unk0 = AllocFromHeap(param0->heapId, sizeof(struct UnkStruct_0200BB14_sub));
    ptr->unk04 = ptr->unk08->unk0;
    if (ptr->unk08->unk0 == NULL)
    {
        if (ptr->unk08 != NULL)
        {
            FreeToHeap(ptr->unk08);
        }

        return NULL;
    }

    for (s32 i = 0; i < 6; i++)
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
        if (st2c[4] != -1 && sub_0200945C(param1->unk0c[4], st2c[4]) == 0)
        {
            st2c[4] = -1;
        }

        if (st2c[5] != -1 && sub_0200945C(param1->unk0c[5], st2c[5]) == 0)
        {
            st2c[5] = -1;
        }
    }

    sub_02008AA4(ptr->unk04,
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
    f32 r0;
    if (((s16 *)param2)[0] > 0)
    {
        r0 = ((f32)(((s16 *)param2)[0] << 0xc) + (f32)0.5);
    }
    else
    {
        r0 = ((f32)(((s16 *)param2)[0] << 0xc) - (f32)0.5);
    }
    st44.unk08 = (s32)r0;

    if (((s16 *)param2)[1] > 0)
    {
        r0 = ((f32)(((s16 *)param2)[1] << 0xc) + (f32)0.5);
    }
    else
    {
        r0 = ((f32)(((s16 *)param2)[1] << 0xc) - (f32)0.5);
    }
    st44.unk0c = (s32)r0;

    if (((s16 *)param2)[2] > 0)
    {
        r0 = ((f32)(((s16 *)param2)[2] << 0xc) + (f32)0.5);
    }
    else
    {
        r0 = ((f32)(((s16 *)param2)[2] << 0xc) - (f32)0.5);
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
    st44.unk2c = param0->heapId;

    ptr->unk00 = sub_0201FE94(&st44);
    ptr->unk0c = param2[12];

    if (ptr->unk00 != 0)
    {
        u8 r6 = sub_020202A0(ptr->unk00);

        sub_02020130(ptr->unk00, ((u16 *)param2)[3]);
        sub_02020248(ptr->unk00, r6 + param2[3]);
    }
    else
    {
        GF_ASSERT(0);
    }

    return ptr;
}

u32 sub_0200C334(struct UnkStruct_02008DEC_1 **param0, s32 param1)
{
    return sub_02009E54(sub_020094F0(param0[4], param1), 0);
}

s32 sub_0200C344(struct UnkStruct_02008DEC_1 **param0, s32 param1, u32 param2)
{
    return sub_02009E88(sub_020094F0(param0[4], param1), param2);
}

BOOL sub_0200C358(struct UnkStruct_0200BB14_2 *param0, u32 param1)
{
    return sub_0200C4F4(param0->unk0c[0], param0->unk24[0], param1);
}

BOOL sub_0200C368(struct UnkStruct_0200BB14_2 *param0, u32 param1)
{
    return sub_0200C548(param0->unk0c[1], param0->unk24[1], param1);
}

BOOL sub_0200C378(struct UnkStruct_0200BB14_2 *param0, u32 param1)
{
    return sub_0200C4A8(param0->unk0c[2], param0->unk24[2], param1);
}

BOOL sub_0200C388(struct UnkStruct_0200BB14_2 *param0, u32 param1)
{
    return sub_0200C4A8(param0->unk0c[3], param0->unk24[3], param1);
}

void sub_0200C398(
    struct UnkStruct_0200BB14_1 *param0, struct UnkStruct_0200BB14_2 *param1)
{
    sub_0200BC40(param1);
    sub_02009C30(param1->unk24[0]);
    sub_02009E28(param1->unk24[1]);

    for (s32 i = 0; i < param1->unk54; i++)
    {
        sub_02009448(param1->unk24[i]);
        sub_02008E2C(param1->unk0c[i]);
    }

    sub_0200BCD0(param0, param1);
}

void sub_0200C3DC(u32 *param0)
{
    if (param0[3] != 0)
    {
        sub_02009CDC(*(u32 *)param0[1]);
    }

    sub_0201FFC8(param0[0]);
    sub_02008C80((struct UnkStruct_02008AA4_1 *)param0[2]);
    FreeToHeap(param0);
}

BOOL sub_0200C404(HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5,
    s32 param6)
{
    if (sub_0200945C(param1->unk0c[param5], param6) == 0)
    {
        return FALSE;
    }

    struct UnkStruct_02008DEC_sub *r5 = sub_020090AC(param1->unk0c[param5], param2, param3, param4, param6, param5, *heapId);
    if (r5 != NULL)
    {
        BOOL r4 = sub_0200C474(param1->unk24[param5], r5);
        GF_ASSERT(r4 == TRUE);
        return r4;
    }
    GF_ASSERT(0);
    return r5 != NULL ? TRUE : FALSE;
}

BOOL sub_0200C474(struct UnkStruct_02008DEC_5 *param0, struct UnkStruct_02008DEC_sub *param1)
{
    for (s32 i = 0; i < param0->unk04; i++)
    {
        if (param0->unk00[i] == NULL)
        {
            param0->unk00[i] = param1;
            param0->unk08++;
            return TRUE;
        }
    }

    return FALSE;
}

BOOL sub_0200C4A8(struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_5 *param1, u32 param2)
{
    for (s32 i = 0; i < param1->unk04; i++)
    {
        if (param1->unk00[i] != 0)
        {
            s32 r0 = sub_02009530(param1->unk00[i]);
            if (r0 == param2)
            {

                sub_02009490(param0, param1->unk00[i]);
                param1->unk00[i] = NULL;
                param1->unk08--;

                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL sub_0200C4F4(struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_5 *param1, u32 param2)
{
    for (s32 i = 0; i < param1->unk04; i++)
    {
        if (param1->unk00[i] != NULL)
        {
            s32 r0 = sub_02009530(param1->unk00[i]);
            if (r0 == param2)
            {
                sub_0201D324(param2);

                sub_02009490(param0, param1->unk00[i]);
                param1->unk00[i] = NULL;
                param1->unk08--;

                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL sub_0200C548(struct UnkStruct_02008DEC_1 *param0, struct UnkStruct_02008DEC_5 *param1, u32 param2)
{
    for (s32 i = 0; i < param1->unk04; i++)
    {
        if (param1->unk00[i] != 0)
        {
            s32 r0 = sub_02009530(param1->unk00[i]);
            if (r0 == param2)
            {
                sub_0201E1C8(param2);

                sub_02009490(param0, param1->unk00[i]);
                param1->unk00[i] = NULL;
                param1->unk08--;

                return TRUE;
            }
        }
    }

    return FALSE;
}

void sub_0200C59C(u32 param0)
{
    sub_020201E4(param0, 0x1000);
}

void sub_0200C5A8(u32 *param0)
{
    sub_0200C59C(param0[0]);
}

void sub_0200C5B4(u32 *param0, u32 param1)
{
    sub_020201E4(param0[0], param1);
}

void sub_0200C5C0(u32 *param0, u32 param1)
{
    sub_02020130(param0[0], param1);
}

u32 sub_0200C5CC(u32 *param0)
{
    return sub_020201DC(param0[0]);
}

void sub_0200C5D8(u32 param0, u32 param1)
{
    sub_020200BC(param0, param1);
}

void sub_0200C5E0(u32 *param0, u32 param1)
{
    sub_0200C5D8(param0[0], param1);
}

void sub_0200C5EC(u32 param0, u32 param1)
{
    sub_020200D8(param0, param1);
}

void sub_0200C5F4(u32 *param0, u32 param1)
{
    sub_0200C5EC(*param0, param1);
}

u32 sub_0200C600(u32 param0)
{
    return sub_02020388(param0);
}

u32 sub_0200C608(u32 *param0)
{
    return sub_0200C600(*param0);
}

void sub_0200C614(u32 param0)
{
    sub_02020208(param0);
}

void sub_0200C61C(u32 *param0)
{
    sub_0200C614(*param0);
}

void sub_0200C628(u32 param0)
{
    sub_0202022C(param0);
}

void sub_0200C630(u32 *param0)
{
    sub_0200C628(*param0);
}

void sub_0200C63C(u32 param0, u32 param1)
{
    sub_020200A0(param0, param1);
}

void sub_0200C644(u32 *param0, u32 param1)
{
    sub_0200C63C(*param0, param1);
}

u8 sub_0200C650(u32 param0)
{
    return sub_02020128(param0);
}

u8 sub_0200C658(u32 *param0)
{
    return sub_0200C650(*param0);
}

void sub_0200C664(u32 param0, u32 param1)
{
    sub_02020248(param0, param1);
}

void sub_0200C66C(u32 *param0, u32 param1)
{
    sub_0200C664(*param0, param1);
}

void sub_0200C678(u32 param0, u32 param1)
{
    sub_020202A8(param0, param1);
}

void sub_0200C680(u32 *param0, u32 param1)
{
    sub_0200C678(*param0, param1);
}

u8 sub_0200C68C(u32 *param0)
{
    return sub_02020300(*param0);
}

void sub_0200C698(u32 param0, u32 param1)
{
    sub_02020238(param0, (u8)param1);
}

u8 sub_0200C6A4(u32 *param0)
{
    return sub_02020240(*param0);
}

void sub_0200C6B0(u32 *param0, u32 param1)
{
    sub_0200C698(*param0, param1);
}

void sub_0200C6BC(u32 param0, u32 param1)
{
    sub_02020310(param0, param1);
}

void sub_0200C6C4(u32 *param0, u32 param1)
{
    sub_0200C6BC(*param0, param1);
}

u16 sub_0200C6D0(u32 param0)
{
    return sub_0202032C(param0);
}

u16 sub_0200C6D8(u32 *param0)
{
    return sub_0200C6D0(*param0);
}

void sub_0200C6E4(u32 param0, u32 param1, u32 param2)
{
    u32 st0[3];
    st0[0] = param1 << 12;
    st0[1] = param2 << 12;
    if (sub_02020380(param0) == 2)
    {
        st0[1] += 0xc0000;
    }
    st0[2] = 0;

    sub_02020044(param0, st0);
}

void sub_0200C714(u32 *param0, u32 param1, u32 param2)
{
    sub_0200C6E4(*param0, param1, param2);
}

void sub_0200C720(u32 param0, u32 param1, u32 param2, u32 param3)
{
    u32 st0[3];

    st0[0] = param1 << 12;
    st0[1] = param2 << 12;
    if (sub_02020380(param0) == 2)
    {
        st0[1] += param3;
    }
    st0[2] = 0;

    sub_02020044(param0, st0);
}

void sub_0200C750(u32 *param0, u32 param1, u32 param2, u32 param3)
{
    sub_0200C720(*param0, param1, param2, param3);
}

void sub_0200C75C(u32 param0, u16 *param1, u16 *param2)
{
    s32 *r4 = sub_0202011C(param0, param1, param2);

    param1[0] = (u16)(r4[0] / 0x1000);

    if (sub_02020380(param0) == 2)
    {
        s32 r1 = r4[1] - 0xc0000;

        param2[0] = (u16)(r1 / 0x1000);

        return;
    }

    param2[0] = (u16)(r4[1] / 0x1000);
}

void sub_0200C7A0(u32 *param0, u16 *param1, u16 *param2)
{
    sub_0200C75C(*param0, param1, param2);
}

void sub_0200C7AC(u32 param0, u16 *param1, u16 *param2, s32 param3)
{
    s32 *r4 = sub_0202011C(param0, param1, param2);

    param1[0] = (u16)(r4[0] / 0x1000);

    if (sub_02020380(param0) == 2)
    {
        s32 r1 = r4[1] - param3;

        param2[0] = (u16)(r1 / 0x1000);

        return;
    }

    param2[0] = (u16)(r4[1] / 0x1000);
}

void sub_0200C7F0(u32 *param0, u16 *param1, u16 *param2, s32 param3)
{
    sub_0200C7AC(*param0, param1, param2, param3);
}

void sub_0200C7FC(u32 param0, u16 *param1, u16 *param2)
{
    u32 st0[3];

    u32 *r0 = sub_0202011C(param0, param1, param2);

    st0[0] = r0[0] + ((u32)param1 << 0xc);
    st0[1] = r0[1] + ((u32)param2 << 0xc);
    st0[2] = r0[2];

    sub_02020044(param0, st0);
}

void sub_0200C82C(u32 *param0, u16 *param1, u16 *param2)
{
    sub_0200C7FC(*param0, param1, param2);
}

void sub_0200C838(u32 param0, u32 param1)
{
    sub_020200EC(param0, param1);
}

void sub_0200C840(u32 *param0, u32 param1)
{
    sub_0200C838(*param0, param1);
}

void sub_0200C84C(u32 param0, f32 param1, f32 param2)
{
    s32 *r4 = sub_02020120(param0);

    r4[0] = (s32)(param1 * 0x1000);
    r4[1] = (s32)(param2 * 0x1000);

    sub_02020064(param0, r4);
}

void sub_0200C884(u32 *param0, f32 param1, f32 param2)
{
    sub_0200C84C(*param0, param1, param2);
}

void sub_0200C890(u32 param0, u16 param1)
{
    sub_02020088(param0, param1);
}

void sub_0200C898(u32 *param0, u16 param1)
{
    sub_0200C890(*param0, param1);
}

void sub_0200C8A4(u32 param0, u32 param1)
{
    u16 r0 = sub_02020124(param0);
    r0 += param1;
    sub_02020088(param0, r0);
}

void sub_0200C8BC(u32 *param0, u32 param1)
{
    sub_0200C8A4(*param0, param1);
}

void sub_0200C8C8(u32 param0, u32 param1)
{
    sub_02020100(param0, param1);
}

void sub_0200C8D0(u32 *param0, u32 param1)
{
    sub_0200C8C8(*param0, param1);
}

void sub_0200C8DC(u32 *param0, u32 param1, u32 param2)
{
    u32 st0[3];
    st0[0] = param1 << 12;
    st0[1] = param2 << 12;
    st0[2] = 0;

    sub_02020054(*param0, st0);
}

void sub_0200C8F8(u32 *param0, u32 param1)
{
    sub_02020358(*param0, param1);
}

void sub_0200C904(u32 param0, u32 param1)
{
    sub_02020398(param0, param1);
}

void sub_0200C90C(u32 *param0, u32 param1)
{
    sub_0200C904(*param0, param1);
}

BOOL sub_0200C918(HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5,
    s32 param6)
{
    if (sub_0200945C(param1->unk0c[0], param6) == 0)
    {
        return FALSE;
    }

    struct UnkStruct_02008DEC_sub *r5 = sub_02008F34(param1->unk0c[0], param2, param3, param4, param6, param5, *heapId);
    if (r5 != NULL)
    {
        sub_02009AC4(r5);
        sub_0200C474(param1->unk24[0], r5);

        return TRUE;
    }

    GF_ASSERT(FALSE);
    return r5 != NULL ? TRUE : FALSE;
}

BOOL sub_0200C978(HeapID *heapId,
    struct UnkStruct_0200BB14_2 *param1,
    NarcId param2,
    s32 param3,
    BOOL param4,
    u32 param5,
    s32 param6)
{
    if (sub_0200945C(param1->unk0c[0], param6) == 0)
    {
        return FALSE;
    }

    struct UnkStruct_02008DEC_sub *r5 = sub_02008F34(param1->unk0c[0], param2, param3, param4, param6, param5, *heapId);
    if (r5 != NULL)
    {
        sub_02009B78(r5);
        sub_0200C474(param1->unk24[0], r5);

        return TRUE;
    }

    GF_ASSERT(FALSE);
    return r5 != NULL ? TRUE : FALSE;
}

void sub_0200C9D8(
    HeapID *heapId, struct UnkStruct_02008DEC_1 **param1, NarcId param2, s32 param3, BOOL param4, s32 param5)
{
    struct UnkStruct_02008DEC_sub *r6 = sub_020094F0(param1[3], param5);
    sub_020090FC(param1[3], r6, param2, param3, param4, *heapId);

    sub_02009BE8(r6);
}

void sub_0200CA0C(
    HeapID *heapId, struct UnkStruct_02008DEC_1 **param1, NarcId param2, s32 param3, BOOL param4, s32 param5)
{
    struct UnkStruct_02008DEC_sub *r6 = sub_020094F0(param1[4], param5);
    sub_02009168(param1[4], r6, param2, param3, param4, *heapId);

    sub_02009DE0(r6);
}

u32 sub_0200CA40(u32 *param0)
{
    return *param0;
}
