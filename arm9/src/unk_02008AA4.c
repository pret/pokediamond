#include "global.h"
#include "unk_02008AA4.h"
#include "GX_vramcnt.h"
#include "heap.h"
#include "unk_0200BB14.h"
#include "unk_02008DEC.h"
#include "oam.h"

extern void sub_0202134C(void *, u32);
extern u32 sub_0201FCB0(u32 *);
extern void sub_02021390(u32, u32 *);
extern void sub_0201D194(u32, u32, u32);
extern void sub_0201E068(u32, u32);

void sub_02008AA4(struct UnkStruct_0200BB14_sub *param0,
    s32 param1,
    s32 param2,
    s32 param3,
    s32 param4,
    s32 param5,
    s32 param6,
    u32 param7,
    u32 param8,
    struct UnkStruct_02008DEC_1 *param9,
    struct UnkStruct_02008DEC_1 *param10,
    struct UnkStruct_02008DEC_1 *param11,
    struct UnkStruct_02008DEC_1 *param12,
    struct UnkStruct_02008DEC_1 *param13,
    struct UnkStruct_02008DEC_1 *param14)
{
    struct UnkStruct_02008DEC_sub *r7;
    struct UnkStruct_02008DEC_sub *st14;
    struct UnkStruct_02008DEC_sub *st10;

    struct UnkStruct_02008DEC_sub *stc = NULL;
    struct UnkStruct_02008DEC_sub *r4 = NULL;
    struct UnkStruct_02008DEC_sub *st8 = NULL;

    GF_ASSERT(param9);
    GF_ASSERT(param10);
    GF_ASSERT(param12);
    GF_ASSERT(param11);
    GF_ASSERT(param0);

    r7 = sub_020094F0(param9, param1);
    GF_ASSERT(r7);

    st14 = sub_020094F0(param10, param2);
    GF_ASSERT(st14);

    st10 = sub_020094F0(param11, param3);
    GF_ASSERT(st10);

    if (param12 != 0 && param4 != -1)
    {
        stc = sub_020094F0(param12, param4);
        GF_ASSERT(stc);
    }

    if (param13 != 0)
    {
        if (param5 != -1)
        {
            r4 = sub_020094F0(param13, param5);
        }

        if (param6 != -1)
        {
            st8 = sub_020094F0(param14, param6);
        }
    }

    u32 r6;
    if (param7 != 0)
    {
        r6 = sub_02009C80(r7, st10);
        GF_ASSERT(r6);

        param0->unk04 = sub_02009544(r7);
    }
    else
    {
        r6 = sub_02009C5C(r7);
        GF_ASSERT(r6);

        param0->unk04 = 0;
    }

    param0->unk08 = sub_02009E54(st14, r6);
    param0->unk00 = r6;
    param0->unk0C = sub_02009574(st10);

    if (stc != 0)
    {
        param0->unk10 = sub_0200958C(stc);
    }
    else
    {
        param0->unk10 = 0;
    }

    if (r4 != 0)
    {
        param0->unk14 = sub_020095A4(r4);
        param0->unk18 = sub_020095BC(st8);
    }
    else
    {
        param0->unk14 = 0;
        param0->unk18 = 0;
    }

    param0->unk1C = param7;
    param0->unk20 = (u8)param8;
}

struct UnkStruct_02008AA4_1 *sub_02008BE0(struct UnkStruct_02008AA4_2 *param0,
    u32 param1,
    struct UnkStruct_02008DEC_1 *param2,
    struct UnkStruct_02008DEC_1 *param3,
    struct UnkStruct_02008DEC_1 *param4,
    struct UnkStruct_02008DEC_1 *param5,
    struct UnkStruct_02008DEC_1 *param6,
    struct UnkStruct_02008DEC_1 *param7)
{

    s32 r4 = 0;
    while (param0[r4].unk00 != -2)
    {
        r4++;
    }

    struct UnkStruct_02008AA4_1 *r6 = AllocFromHeap(param1, sizeof(struct UnkStruct_02008AA4_1));
    r6->unk00 = AllocFromHeap(param1, r4 * sizeof(struct UnkStruct_0200BB14_sub));
    r6->unk04 = r4;

    for (int r7 = 0; r7 < r6->unk04; r7++)
    {
        sub_02008AA4(&r6->unk00[r7],
            param0[r7].unk00,
            param0[r7].unk04,
            param0[r7].unk08,
            param0[r7].unk0C,
            param0[r7].unk10,
            param0[r7].unk14,
            param0[r7].unk18,
            param0[r7].unk1C,
            param2,
            param3,
            param4,
            param5,
            param6,
            param7);
    }

    return r6;
}

void sub_02008C80(struct UnkStruct_02008AA4_1 *param0)
{
    GF_ASSERT(param0);

    if (param0->unk00 != NULL)
    {
        FreeToHeap(param0->unk00);
    }
    FreeToHeap(param0);
}

u32 sub_02008C9C(u32 param0, void *param1, u32 param2)
{
    sub_0202134C(param1, 0xFFFFF000);

    u32 st10[3];
    u32 st0[4];

    st0[0] = 0;
    st0[1] = 0;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;
    sub_02009FD8(param1 + 0x98, st0, 1, (u32)param1);

    st0[0] = 0;
    st0[1] = 0xC0000;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;

    sub_02009FD8(param1 + 0xe0, st0, 2, (u32)param1);

    st10[0] = param0;
    st10[1] = (u32)param1;
    st10[2] = param2;

    return sub_0201FCB0(st10);
}

void sub_02008D04(u32 param0, u32 param1, u32 param2)
{
    u32 st0[4];
    st0[0] = param1;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;
    st0[1] = param2;
    sub_02021390(param0 + 0x98, st0);
}

void sub_02008D24(u32 param0, u32 param1, u32 param2)
{
    u32 st0[4];
    st0[0] = param1;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;
    st0[1] = param2;
    sub_02021390(param0 + 0xe0, st0);
}

void sub_02008D44(u32 param0, u32 param1)
{
    switch (param1)
    {
        case 0x10:
            if (GX_GetBankForOBJ() == 0x40 || GX_GetBankForOBJ() == 0x20)
            {
                sub_0201D194(0x3E00, 0x200, param0);
                return;
            }

            sub_0201D194(0x7E00, 0x200, param0);
            return;
        case 0x00100010:
            sub_0201D194(0xfe00, 0x200, param0);
            return;
        case 0x00200010:
            if (GX_GetBankForOBJ() == 0x30 || GX_GetBankForOBJ() == 0x50)
            {
                sub_0201D194(0x13E00, 0x200, param0);
                return;
            }
            sub_0201D194(0x1FE00, 0x200, param0);
            return;
    }

    GF_AssertFail();
}

void sub_02008DDC(u32 param0)
{
    sub_0201E068(0xC000, param0);
}
