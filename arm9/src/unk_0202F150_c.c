#include "global.h"
#include "MI_memory.h"
#include "heap.h"

struct
{
    u8 unk00;
    struct UnkStruct1 *unk04;
} UNK_021C59F4;

// struct UnkStruct2 {
//     u8 unk00;
//     u8 unk01;
// };

u8 UNK_02105D58 = 4;
u8 UNK_02105D59 = 4;

extern int FUN_02033534();
extern u32 FUN_0202D858(u16 param0);
extern void FUN_02031480(u32 param0);
extern void FUN_0202D7D8(u32 *param0, u32 param1, u32 param2);
extern void FUN_0202F2F0();
extern void FUN_020312BC(u32 param0);
extern void FUN_0202FB20();

extern u32 FUN_0200CA60(void (*param0)(), u32 param1, u32 param2);
extern void FUN_0202D394(u32 param0, u32 param1, u32 param2);

extern void FUN_0202D804(u32 *param0);
extern u32 FUN_02030E7C(u16 param0);

struct UnkStruct1
{
    u8 unk000[38];
    u8 unk026[38];
    u8 unk04c[264];
    u8 unk154[192];
    u8 unk214[192];
    u8 unk2D4[384];
    u32 unk454;
    u32 unk458;
    u32 unk45C;
    u32 unk460;
    u32 unk464;
    u8 unk468[0x8];
    u32 unk470;
    u8 unk474[0x8];
    struct
    {
        u32 unk00;
        u32 unk04;
        u32 unk08;
    } unk47C[8];
    u32 unk4DC;
    u8 unk4E0[0x8];
    struct
    {
        u32 unk00;
        u32 unk04;
        u32 unk08;
    } unk4E8[8];
    u32 unk548;
    u8 unk54C[32];
    u8 unk56C[32];
    struct
    {
        u32 unk00;
        u32 unk04;
        u16 unk08;
        u8 unk0a;
        u8 unk0b;
    } unk58C[8];
    u32 unk5EC;
    u32 unk5F0;
    u16 unk5F4;
    u8 unk5F6;
    u8 unk5F7;
    u32 unk5F8;
    u8 unk5FC[0x14];
    u16 unk610[8];
    u8 unk620[0xc];
    u8 unk62C;
    u8 unk62D;
    u8 unk62E[0x2];
    u32 unk630;
    u32 unk634;
    u32 unk638[8];
    u32 unk658;
    u16 unk65C;
    u8 unk65E;
    u8 unk65F[8];
    u8 unk667[8];
    u8 unk66F[8];
    u8 unk677[4];
    u8 unk67B[0x2];
    u8 unk67D;
    u8 unk67E;
    u8 unk67F;
    u8 unk680;
    u8 unk681;
    u8 unk682;
    u8 unk683;
    u8 unk684;
    u8 unk685;
    u8 unk686;
    u8 unk687;
    u8 unk688;
    u8 unk689[0x3];
};

THUMB_FUNC u32 FUN_0202F150(u32 param0, u32 param1)
{
    u32 r4 = 0;
    UNK_021C59F4.unk00 = 0;
    if (param0 != 0)
    {
        u32 res = FUN_0202D858(FUN_02033534()) + 1;

        if (UNK_021C59F4.unk04 != 0)
        {
            return 1;
        }

        FUN_02031480(0xf);
        struct UnkStruct1 *ptr = (struct UnkStruct1 *)AllocFromHeap(0xf, 0x68C);
        UNK_021C59F4.unk04 = ptr;
        MI_CpuFill8(ptr, 0, 0x68C);

        UNK_021C59F4.unk04->unk658 = param1 + 0x40;
        UNK_021C59F4.unk04->unk67D = 0;
        UNK_021C59F4.unk04->unk67E = 0x1b;

        UNK_021C59F4.unk04->unk45C = AllocFromHeap(0xf, UNK_021C59F4.unk04->unk658 << 1);

        UNK_021C59F4.unk04->unk460 = AllocFromHeap(0xf, UNK_021C59F4.unk04->unk658);

        UNK_021C59F4.unk04->unk458 = AllocFromHeap(0xf, res * UNK_021C59F4.unk04->unk658);

        UNK_021C59F4.unk04->unk454 = AllocFromHeap(0xf, res * UNK_021C59F4.unk04->unk658);

        if (FUN_02033534() == 0xa)
        {
            FUN_0202D7D8(UNK_021C59F4.unk04->unk54C, 0x64, &UNK_021C59F4.unk04->unk464);
            FUN_0202D7D8(UNK_021C59F4.unk04->unk56C, 0x32 << 4, &UNK_021C59F4.unk04->unk4DC);
        }
        else
        {
            FUN_0202D7D8(UNK_021C59F4.unk04->unk54C, 0x14, &UNK_021C59F4.unk04->unk464);
            FUN_0202D7D8(UNK_021C59F4.unk04->unk56C, 0x1b + 0xfd, &UNK_021C59F4.unk04->unk4DC);
        }
    }
    else
    {

        r4 = 1;
        if (UNK_021C59F4.unk04 == 0)
        {
            ErrorHandling();
        }
    }

    UNK_021C59F4.unk04->unk65C = 0;

    for (int i = 0; i < 4; i++)
    {
        UNK_021C59F4.unk04->unk677[i] = 0xff;
    }

    if (r4 == 0)
    {
        FUN_0202F2F0();
    }

    FUN_020312BC(&UNK_021C59F4.unk04->unk5F8);

    if (r4 == 0)
    {
        u32 res2 = FUN_0200CA60(FUN_0202FB20, 0, 0);

        UNK_021C59F4.unk04->unk548 = res2;
    }

    UNK_021C59F4.unk04->unk687 = 0;

    return 1;
}

THUMB_FUNC void FUN_0202F2F0()
{
    UNK_021C59F4.unk04->unk62C = 0;
    UNK_021C59F4.unk04->unk62D = 0;
    UNK_021C59F4.unk04->unk67F = 0;
    UNK_021C59F4.unk04->unk680 = 0;

    s32 res = FUN_0202D858(FUN_02033534()) + 1;

    MI_CpuFill8(UNK_021C59F4.unk04->unk458, 0, UNK_021C59F4.unk04->unk658 * res);

    int i;
    for (i = 0; i < res; i++)
    {
        FUN_0202D394(&UNK_021C59F4.unk04->unk4E8[i],
            UNK_021C59F4.unk04->unk458 + i * UNK_021C59F4.unk04->unk658,
            UNK_021C59F4.unk04->unk658);
    }

    MI_CpuFill8(UNK_021C59F4.unk04->unk454, 0, UNK_021C59F4.unk04->unk658 * res);

    for (i = 0; i < res; i++)
    {
        FUN_0202D394(&UNK_021C59F4.unk04->unk47C[i],
            UNK_021C59F4.unk04->unk454 + i * UNK_021C59F4.unk04->unk658,
            UNK_021C59F4.unk04->unk658);
    }

    MI_CpuFill8(&UNK_021C59F4.unk04->unk2D4, 0, 6 << 6);
    FUN_0202D394(&UNK_021C59F4.unk04->unk4DC, &UNK_021C59F4.unk04->unk2D4, 6 << 6);

    for (i = 0; i < 0xc0; i++)
    {
        UNK_021C59F4.unk04->unk154[i] = 0xee;
        UNK_021C59F4.unk04->unk214[i] = 0xee;
    }

    MI_CpuFill8(&UNK_021C59F4.unk04->unk04c, 0, 0x42 << 2);
    FUN_0202D394(&UNK_021C59F4.unk04->unk464, &UNK_021C59F4.unk04->unk04c, 0x42 << 2);

    UNK_021C59F4.unk04->unk000[0] = 0xff;
    UNK_021C59F4.unk04->unk026[0] = 0xff;

    for (i = 1; i < 0x26; i++)
    {
        UNK_021C59F4.unk04->unk000[i] = 0xee;
        UNK_021C59F4.unk04->unk026[i] = 0xee;
    }

    MI_CpuFill8(UNK_021C59F4.unk04->unk45C, 0, UNK_021C59F4.unk04->unk658 << 1);

    FUN_0202D394(
        &UNK_021C59F4.unk04->unk470, UNK_021C59F4.unk04->unk45C, UNK_021C59F4.unk04->unk658 * 2);

    UNK_021C59F4.unk04->unk684 = 0;
    UNK_021C59F4.unk04->unk685 = 0;

    for (i = 0; i < 8; i++)
    {
        UNK_021C59F4.unk04->unk65F[i] = 0;
        UNK_021C59F4.unk04->unk667[i] = 1;
        UNK_021C59F4.unk04->unk66F[i] = 1;
        UNK_021C59F4.unk04->unk610[i] = 0;

        UNK_021C59F4.unk04->unk58C[i].unk0a = 0xee;
        UNK_021C59F4.unk04->unk58C[i].unk08 = 0xffff;
        UNK_021C59F4.unk04->unk58C[i].unk04 = 0;
        UNK_021C59F4.unk04->unk58C[i].unk00 = 0;

        UNK_021C59F4.unk04->unk638[i] = 0;
    }

    UNK_021C59F4.unk04->unk634 = 0;
    UNK_021C59F4.unk04->unk630 = 1;
    UNK_021C59F4.unk04->unk5F6 = 0xee;
    UNK_021C59F4.unk04->unk5F4 = 0xffff;
    UNK_021C59F4.unk04->unk5F0 = 0;
    UNK_021C59F4.unk04->unk5EC = 0;
    UNK_021C59F4.unk04->unk682 = 1;
    UNK_021C59F4.unk04->unk683 = 1;

    UNK_02105D59 = 4;
    UNK_02105D58 = 4;

    FUN_0202D804(UNK_021C59F4.unk04->unk54C);
    FUN_0202D804(UNK_021C59F4.unk04->unk56C);

    UNK_021C59F4.unk04->unk688 = 0;
}

THUMB_FUNC void FUN_0202F5A4()
{
    UNK_021C59F4.unk04->unk62C = 0;
    UNK_021C59F4.unk04->unk62D = 0;

    s32 res = FUN_0202D858(FUN_02033534()) + 1;

    MI_CpuFill8(UNK_021C59F4.unk04->unk458, 0, UNK_021C59F4.unk04->unk658 * res);

    int i;
    for (i = 0; i < res; i++)
    {
        FUN_0202D394(&UNK_021C59F4.unk04->unk4E8[i],
            UNK_021C59F4.unk04->unk458 + i * UNK_021C59F4.unk04->unk658,
            UNK_021C59F4.unk04->unk658);
    }

    MI_CpuFill8(UNK_021C59F4.unk04->unk454, 0, UNK_021C59F4.unk04->unk658 * res);

    for (i = 0; i < res; i++)
    {
        FUN_0202D394(&UNK_021C59F4.unk04->unk47C[i],
            UNK_021C59F4.unk04->unk454 + i * UNK_021C59F4.unk04->unk658,
            UNK_021C59F4.unk04->unk658);
    }

    MI_CpuFill8(&UNK_021C59F4.unk04->unk2D4, 0, 6 << 6);
    FUN_0202D394(&UNK_021C59F4.unk04->unk4DC, &UNK_021C59F4.unk04->unk2D4, 6 << 6);

    for (i = 0; i < 0xc0; i++)
    {
        UNK_021C59F4.unk04->unk154[i] = 0xee;
        UNK_021C59F4.unk04->unk214[i] = 0xee;
    }

    MI_CpuFill8(&UNK_021C59F4.unk04->unk04c, 0, 0x42 << 2);
    FUN_0202D394(&UNK_021C59F4.unk04->unk464, &UNK_021C59F4.unk04->unk04c, 0x42 << 2);

    UNK_021C59F4.unk04->unk000[0] = 0xff;
    UNK_021C59F4.unk04->unk026[0] = 0xff;

    for (i = 1; i < 0x26; i++)
    {
        UNK_021C59F4.unk04->unk000[i] = 0xee;
        UNK_021C59F4.unk04->unk026[i] = 0xee;
    }

    MI_CpuFill8(UNK_021C59F4.unk04->unk45C, 0, UNK_021C59F4.unk04->unk658 << 1);
    FUN_0202D394(
        &UNK_021C59F4.unk04->unk470, UNK_021C59F4.unk04->unk45C, UNK_021C59F4.unk04->unk658 * 2);

    UNK_021C59F4.unk04->unk684 = 0;
    UNK_021C59F4.unk04->unk685 = 0;

    for (i = 0; i < 8; i++)
    {
        UNK_021C59F4.unk04->unk65F[i] = 0;
        UNK_021C59F4.unk04->unk667[i] = 1;
        UNK_021C59F4.unk04->unk66F[i] = 1;
        UNK_021C59F4.unk04->unk610[i] = 0;

        UNK_021C59F4.unk04->unk58C[i].unk0a = 0xee;
        UNK_021C59F4.unk04->unk58C[i].unk08 = 0xffff;
        UNK_021C59F4.unk04->unk58C[i].unk04 = 0;
        UNK_021C59F4.unk04->unk58C[i].unk00 = 0;
    }

    UNK_021C59F4.unk04->unk630 = 1;
    UNK_021C59F4.unk04->unk5F6 = 0xee;
    UNK_021C59F4.unk04->unk5F4 = 0xffff;
    UNK_021C59F4.unk04->unk5F0 = 0;
    UNK_021C59F4.unk04->unk5EC = 0;
    UNK_021C59F4.unk04->unk682 = 1;
    UNK_021C59F4.unk04->unk683 = 1;

    FUN_0202D804(UNK_021C59F4.unk04->unk54C);
    FUN_0202D804(UNK_021C59F4.unk04->unk56C);

    UNK_021C59F4.unk04->unk688 = 0;
}

THUMB_FUNC void FUN_0202F820(u32 param0)
{
    UNK_021C59F4.unk04->unk65F[param0] = 0;

    UNK_021C59F4.unk04->unk667[param0] = 1;

    UNK_021C59F4.unk04->unk638[param0] = 0;

    UNK_021C59F4.unk04->unk66F[param0] = 1;

    FUN_0202D394(&UNK_021C59F4.unk04->unk47C[param0],
        UNK_021C59F4.unk04->unk454 + param0 * UNK_021C59F4.unk04->unk658,
        UNK_021C59F4.unk04->unk658);

    FUN_0202D394(&UNK_021C59F4.unk04->unk4E8[param0],
        UNK_021C59F4.unk04->unk458 + param0 * UNK_021C59F4.unk04->unk658,
        UNK_021C59F4.unk04->unk658);

    UNK_021C59F4.unk04->unk58C[param0].unk0a = 0xee;
    UNK_021C59F4.unk04->unk58C[param0].unk08 = 0xffff;
    UNK_021C59F4.unk04->unk58C[param0].unk04 = 0;
    UNK_021C59F4.unk04->unk58C[param0].unk00 = 0;
}

extern u32 FUN_02031280();

THUMB_FUNC void FUN_0202F8D4()
{
    for (int i = 1; i < 8; i++)
    {
        if (FUN_02030E7C(i) == 0 && UNK_021C59F4.unk04->unk667[i] == 0 && FUN_02031280() == 0)
        {
            FUN_0202F820(i);
        }
    }
}

THUMB_FUNC void FUN_0202F910(u32 param0)
{
    FUN_0202F820(param0);
}

extern u32 FUN_0202E5F8(u32 param0, u32 param1, u32 param2);
extern void FUN_0202D330(void (*param0)(u32));

THUMB_FUNC u32 FUN_0202F918(u32 param0, u32 param1, u32 param2, u32 param3)
{
    u32 ret = 1;
    if (FUN_02033534() < 0x13)
    {
        ret = FUN_0202E5F8(param0, param1, param3);
        FUN_0202D330(FUN_0202F910);
    }

    FUN_0202F150(param0, param2);

    return ret;
}