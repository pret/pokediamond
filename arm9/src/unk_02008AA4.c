#include "global.h"
#include "unk_02008AA4.h"
#include "GX_vramcnt.h"
#include "heap.h"
#include "unk_0200BB14.h"

extern u32 FUN_020094F0(u32 param0, s32 param1);
extern u32 FUN_02009C80(u32, u32);
extern u32 FUN_02009544(u32);
extern u32 FUN_02009E54(u32 param0, u32 param1);
extern u32 FUN_02009C5C(u32);
extern u32 FUN_02009574(u32);
extern u32 FUN_0200958C(u32);
extern u32 FUN_020095A4(u32);
extern u32 FUN_020095BC(u32);
extern void FUN_0202134C(void *, u32);
extern void FUN_02009FD8(void *param0, u32 *param1, u32 param2, u32 param3);
extern u32 FUN_0201FCB0(u32 *);
extern void FUN_02021390(u32, u32 *);
extern void FUN_0201D194(u32, u32, u32);
extern void FUN_0201E068(u32, u32);

THUMB_FUNC void FUN_02008AA4(struct UnkStruct_0200BB14_sub *param0,
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
    u32 param14)
{
    u32 r7;
    u32 st14;
    u32 st10;

    u32 stc = 0;
    u32 r4 = 0;
    u32 st8 = 0;

    GF_ASSERT(param9);
    GF_ASSERT(param10);
    GF_ASSERT(param12);
    GF_ASSERT(param11);
    GF_ASSERT(param0);

    r7 = FUN_020094F0(param9, param1);
    GF_ASSERT(r7);

    st14 = FUN_020094F0(param10, param2);
    GF_ASSERT(st14);

    st10 = FUN_020094F0(param11, param3);
    GF_ASSERT(st10);

    if (param12 != 0 && param4 != -1)
    {
        stc = FUN_020094F0(param12, param4);
        GF_ASSERT(stc);
    }

    if (param13 != 0)
    {
        if (param5 != -1)
        {
            r4 = FUN_020094F0(param13, param5);
        }

        if (param6 != -1)
        {
            st8 = FUN_020094F0(param14, param6);
        }
    }

    u32 r6;
    if (param7 != 0)
    {
        r6 = FUN_02009C80(r7, st10);
        GF_ASSERT(r6);

        param0->unk04 = FUN_02009544(r7);
    }
    else
    {
        r6 = FUN_02009C5C(r7);
        GF_ASSERT(r6);

        param0->unk04 = 0;
    }

    param0->unk08 = FUN_02009E54(st14, r6);
    param0->unk00 = r6;
    param0->unk0C = FUN_02009574(st10);

    if (stc != 0)
    {
        param0->unk10 = FUN_0200958C(stc);
    }
    else
    {
        param0->unk10 = 0;
    }

    if (r4 != 0)
    {
        param0->unk14 = FUN_020095A4(r4);
        param0->unk18 = FUN_020095BC(st8);
    }
    else
    {
        param0->unk14 = 0;
        param0->unk18 = 0;
    }

    param0->unk1C = param7;
    param0->unk20 = (u8)param8;
}

THUMB_FUNC struct UnkStruct_02008AA4_1 *FUN_02008BE0(struct UnkStruct_02008AA4_2 *param0,
    u32 param1,
    u32 param2,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6,
    u32 param7)
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
        FUN_02008AA4(&r6->unk00[r7],
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

THUMB_FUNC void FUN_02008C80(struct UnkStruct_02008AA4_1 *param0)
{
    GF_ASSERT(param0);

    if (param0->unk00 != NULL)
    {
        FreeToHeap(param0->unk00);
    }
    FreeToHeap(param0);
}

THUMB_FUNC u32 FUN_02008C9C(u32 param0, void *param1, u32 param2)
{
    FUN_0202134C(param1, 0xFFFFF000);

    u32 st10[3];
    u32 st0[4];

    st0[0] = 0;
    st0[1] = 0;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;
    FUN_02009FD8(param1 + 0x98, st0, 1, param1);

    st0[0] = 0;
    st0[1] = 0xC0000;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;

    FUN_02009FD8(param1 + 0xe0, st0, 2, param1);

    st10[0] = param0;
    st10[1] = (u32)param1;
    st10[2] = param2;

    return FUN_0201FCB0(st10);
}

THUMB_FUNC void FUN_02008D04(u32 param0, u32 param1, u32 param2)
{
    u32 st0[4];
    st0[0] = param1;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;
    st0[1] = param2;
    FUN_02021390(param0 + 0x98, st0);
}

THUMB_FUNC void FUN_02008D24(u32 param0, u32 param1, u32 param2)
{
    u32 st0[4];
    st0[0] = param1;
    st0[2] = 0xFF000;
    st0[3] = 0xC0000;
    st0[1] = param2;
    FUN_02021390(param0 + 0xe0, st0);
}

THUMB_FUNC void FUN_02008D44(u32 param0, u32 param1)
{
    switch (param1)
    {
        case 0x10:
            if (GX_GetBankForOBJ() == 0x40 || GX_GetBankForOBJ() == 0x20)
            {
                FUN_0201D194(0x3E00, 0x200, param0);
                return;
            }

            FUN_0201D194(0x7E00, 0x200, param0);
            return;
        case 0x00100010:
            FUN_0201D194(0xfe00, 0x200, param0);
            return;
        case 0x00200010:
            if (GX_GetBankForOBJ() == 0x30 || GX_GetBankForOBJ() == 0x50)
            {
                FUN_0201D194(0x13E00, 0x200, param0);
                return;
            }
            FUN_0201D194(0x1FE00, 0x200, param0);
            return;
    }

    GF_AssertFail();
}

THUMB_FUNC void FUN_02008DDC(u32 param0)
{
    FUN_0201E068(0xC000, param0);
}
