#include "global.h"
#include "MI_memory.h"
#include "heap.h"
#include "main.h"

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
extern int FUN_0202D858(u16 param0);
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
    u8 unk000[2][38];
    // u8 unk026[38];
    u8 unk04c[264];
    u8 unk154[2][192];
    // u8 unk214[192];
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
    u8 unk620[0x8];
    u16 unk628;
    u8 unk62A[0x2];
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
    u8 unk689;
    u8 unk68A;
    u8 unk68B;
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
        UNK_021C59F4.unk04->unk154[0][i] = 0xee;
        UNK_021C59F4.unk04->unk154[1][i] = 0xee;
    }

    MI_CpuFill8(&UNK_021C59F4.unk04->unk04c, 0, 0x42 << 2);
    FUN_0202D394(&UNK_021C59F4.unk04->unk464, &UNK_021C59F4.unk04->unk04c, 0x42 << 2);

    UNK_021C59F4.unk04->unk000[0][0] = 0xff;
    UNK_021C59F4.unk04->unk000[1][0] = 0xff;

    for (i = 1; i < 0x26; i++)
    {
        UNK_021C59F4.unk04->unk000[0][i] = 0xee;
        UNK_021C59F4.unk04->unk000[1][i] = 0xee;
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
        UNK_021C59F4.unk04->unk154[0][i] = 0xee;
        UNK_021C59F4.unk04->unk154[1][i] = 0xee;
    }

    MI_CpuFill8(&UNK_021C59F4.unk04->unk04c, 0, 0x42 << 2);
    FUN_0202D394(&UNK_021C59F4.unk04->unk464, &UNK_021C59F4.unk04->unk04c, 0x42 << 2);

    UNK_021C59F4.unk04->unk000[0][0] = 0xff;
    UNK_021C59F4.unk04->unk000[1][0] = 0xff;

    for (i = 1; i < 0x26; i++)
    {
        UNK_021C59F4.unk04->unk000[0][i] = 0xee;
        UNK_021C59F4.unk04->unk000[1][i] = 0xee;
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

extern u32 FUN_0202E66C(u32 param0, u32 param1);

THUMB_FUNC u32 FUN_0202F950(u32 param0, u32 param1, u32 param2) {
    u32 ret = 1;
    if (FUN_02033534() < 0x13)
    {
        ret = FUN_0202E66C(param0, param1);
    }

    FUN_0202F150(param0, param2);

    UNK_02105D58 = 4;

    return ret;  
}

extern u16 FUN_02031190();
extern void FUN_02031088();





THUMB_FUNC void FUN_0202F984() {
    u32 r4 = 0;
    if (FUN_02031190() == 0 ) {
        if (UNK_02105D59 != 4) {
            return;
        }
    } else {
        if (UNK_02105D58 != 4) {
            return;
        }
    }

    if (UNK_021C59F4.unk04->unk67D == 2) {
        UNK_021C59F4.unk04->unk67D = 0;
        r4 = 1;
    }

    if (UNK_021C59F4.unk04->unk67D == 3) {
        UNK_021C59F4.unk04->unk67D = 1;
        r4 = 1;
    }

    if (r4 != 0) {
        FUN_0202F5A4();
    }
    FUN_02031088();
}




THUMB_FUNC void FUN_0202F9E0(u32 param0) {
    u8 r2 = UNK_021C59F4.unk04->unk67D;
    if (r2 == 0 && param0 == 1) {
        UNK_021C59F4.unk04->unk67D = 3;
    } else if (r2 == 1 && param0 == 0) {
        UNK_021C59F4.unk04->unk67D = 2;
    }
}


THUMB_FUNC void FUN_0202FA10() {
    FUN_0202F9E0(1);
}


THUMB_FUNC void FUN_0202FA1C() {
    FUN_0202F9E0(0);
}



THUMB_FUNC u8 FUN_0202FA28() {
    u8 ret = UNK_021C59F4.unk04->unk67D;
    if (ret == 2){
        return 1;
    } else if (ret == 3) {
        return 0;
    }

    return ret;
}

THUMB_FUNC u32 FUN_0202FA48() {
    if (FUN_0202FA28() == 1) {
        return 1;
    }

    return 0;
}

extern void MOD04_021D83C0();
extern u32 FUN_0202E784();
extern void FUN_020314D0();
extern void FUN_0202DBA4();
extern void FUN_0200CAB4(u32 param0);
extern void FUN_0202D824(u32 *param0);

THUMB_FUNC void FUN_0202FA5C() {
    u32 r4 = 0;
    if (UNK_021C59F4.unk04 != 0) {
        if (FUN_02033534() >= 0x13) {
            MOD04_021D83C0();
            r4 = 1;
        } else {
            if (FUN_0202E784() != 0) {
                r4 = 1;
            }
        }
    }

    if (r4 != 0) {
        FUN_020314D0();
        FUN_0202DBA4();
        UNK_021C59F4.unk00 = 0;

        FUN_0200CAB4(UNK_021C59F4.unk04->unk548);
        UNK_021C59F4.unk04->unk548 = 0;
        FreeToHeap(UNK_021C59F4.unk04->unk45C);
        FreeToHeap(UNK_021C59F4.unk04->unk460);
        FreeToHeap(UNK_021C59F4.unk04->unk458);
        FreeToHeap(UNK_021C59F4.unk04->unk454);
        FUN_0202D824(UNK_021C59F4.unk04->unk56C);
        FUN_0202D824(UNK_021C59F4.unk04->unk54C);
        FreeToHeap(UNK_021C59F4.unk04);
        UNK_021C59F4.unk04 = NULL;
    }
}

extern u32 FUN_0202E9E8(u32 param0);

THUMB_FUNC u32 FUN_0202FB18(u32 param0) {
    return FUN_0202E9E8(param0);
}


extern void FUN_0203050C();
extern void FUN_0202FEEC();
extern u32 FUN_0202F03C();
extern u32 FUN_0202EE24();



THUMB_FUNC void FUN_0202FB20() {
    if (UNK_021C59F4.unk00 != 0) {
        FUN_0203050C();
        if ((FUN_02031190() == 0 && FUN_02030E7C(0) != 0) || FUN_02031280() != 0){
            FUN_0202FEEC();
        }

        UNK_021C59F4.unk00 = 0;
    }
}

THUMB_FUNC void FUN_0202FB58() {
    if (FUN_0202F03C() != 0) {
        if (FUN_02031190() == 0 ) {
            if (FUN_0202EE24() == 0) {
                FUN_0202FA5C();
            }
        } else {
            FUN_0202FA5C();
        }
    }
}

extern void FUN_02031CDC();
extern void FUN_02030674();
extern void FUN_0202FCCC();
extern void FUN_02030DA4();
extern void FUN_02030074();
extern void FUN_02030DFC();
extern void FUN_0202EBD0(u16 param0);
extern void FUN_0202ED70(u32 param0);
extern void FUN_020335F4(u32 param0);
extern void FUN_020315A4();



THUMB_FUNC u32 FUN_0202FB80() {
    FUN_02031CDC();

    if (UNK_021C59F4.unk04 != NULL) {
        if (UNK_021C59F4.unk04->unk68A == 0) {
            UNK_021C59F4.unk00 = 0;
            FUN_0202F984();
            UNK_021C59F4.unk04->unk628 |= gMain.unk44 & 0x7FFF;
            FUN_02030674();
            FUN_0202FCCC();

            UNK_021C59F4.unk04->unk628 &= 2<<0xe;
            if (FUN_0202FA28() == 0) {
                FUN_02030DA4();
            }

            if ((FUN_02031190() == 0 && FUN_02030E7C(0) != 0) || FUN_02031280() != 0){
                FUN_02030074();
            }

            if (FUN_02031190() == 0 || FUN_0202FA28() == 1 || FUN_02031280() != 0) {
                FUN_02030DFC();
            }

            UNK_021C59F4.unk00 = 1;
        }


        FUN_0202ED70(UNK_021C59F4.unk04->unk65C);

        if (FUN_02031190() == 0) {
            FUN_0202F8D4();
        }

        FUN_0202FB58();
    } else {
        FUN_0202ED70(0);
    }


    FUN_020335F4(0);
    FUN_020315A4();

    return 1;
}


THUMB_FUNC void FUN_0202FC60() {
    u8 r4 = UNK_021C59F4.unk00;

    UNK_021C59F4.unk00 = 0;

    if (UNK_021C59F4.unk04 != NULL) {
        FUN_0202F2F0();
    }

    UNK_021C59F4.unk00 = r4;
}


THUMB_FUNC void FUN_0202FC80() {
    u8 r4 = UNK_021C59F4.unk00;

    UNK_021C59F4.unk00 = 0;

    if (UNK_021C59F4.unk04 != NULL) {
        UNK_021C59F4.unk04->unk67D = 1;
        FUN_0202F2F0();
    }

    UNK_021C59F4.unk00 = r4;
}


extern void FUN_0202E538();


THUMB_FUNC void FUN_0202FCA8() {
    u8 r4 = UNK_021C59F4.unk00;

    UNK_021C59F4.unk00 = 0;

    if (UNK_021C59F4.unk04 != NULL) {
        FUN_0202F2F0();
        FUN_0202E538();
    }

    UNK_021C59F4.unk00 = r4;
}


extern u32 MOD04_021D78FC(void *param0, u32 param1);
extern u32 FUN_0202CBD4();
extern u32 FUN_02030930(void *param0);



THUMB_FUNC void FUN_0202FCCC() {
    if (UNK_021C59F4.unk04->unk683 != 0 ) {
        if (FUN_02033534() >= 0x13) {
            if (UNK_021C59F4.unk04->unk687 == 0 || MOD04_021D78FC(UNK_021C59F4.unk04, 0x26) == 0) {
                return;
            }

            UNK_021C59F4.unk04->unk683 = 0;
            return;
        }

        if (FUN_0202CBD4() != 4 || FUN_02030E7C(FUN_02031190()) == 0) {
            if (FUN_02031280() == 0) {
                return;
            }
        }

        UNK_02105D58 = 0;
        FUN_0203050C();
        if (UNK_02105D58 == 0) {
            return;
        }

        UNK_021C59F4.unk04->unk683 = 0;
        return;
    }


    if (FUN_02033534() >= 0x13) {
        if (UNK_021C59F4.unk04->unk687 == 0) {
            return;
        }

        if (UNK_021C59F4.unk04->unk630 != 0){
            if ((int)UNK_021C59F4.unk04->unk634 > 3) {
                return;
            }

            if (UNK_02105D58 == 4) {
                FUN_02030930(UNK_021C59F4.unk04);
                UNK_02105D58 = 2;
            }
        } else {
            if (UNK_02105D58 == 4) {
                if (FUN_02030930(UNK_021C59F4.unk04) == 0) {
                    return;
                }

                UNK_02105D58 = 2;
            }
        }


        if (MOD04_021D78FC(UNK_021C59F4.unk04, 0x26) == 0) {
            return;
        }

        UNK_02105D58 = 4;
        UNK_021C59F4.unk04->unk634++;
        return;
    }


    if (FUN_0202CBD4() != 4 || FUN_02030E7C(FUN_02031190()) == 0) {
        if (FUN_02031280() == 0) {
             return;
        }
    }

    if (UNK_02105D58 != 4) {
        return;
    }



    //nonmatching
    if ((int)UNK_021C59F4.unk04->unk634 > 3) {
        return;
    }

    FUN_02030930(&UNK_021C59F4.unk04->unk000[UNK_021C59F4.unk04->unk67F]);

    FUN_02030930(&UNK_021C59F4.unk04->unk000[1-UNK_021C59F4.unk04->unk67F]);

    UNK_02105D58 = 0;
    FUN_0203050C();
}

extern int FUN_02031228(u16 param0);
extern void FUN_0202D4BC(void *param0);
extern int FUN_0202D400(u32 param0, u32 param1, u32 param2);






#ifdef NONMATCHING
THUMB_FUNC u32 FUN_0202FE2C(int param0) {

    // these 3 variables are shuffled on the stack, everything else matches
    int st4 = 0;
    int stc = FUN_02031228(FUN_02033534());
    int st8 = FUN_0202D858(FUN_02033534()) + 1;


    for (int r7 = 0; r7 < st8 ; r7++) {

        FUN_0202D4BC(&UNK_021C59F4.unk04->unk47C[r7]);

        if (FUN_02030E7C(r7) != 0) {
            UNK_021C59F4.unk04->unk154[param0][r7*stc] = 0xe;
        }

        FUN_0202D400(&UNK_021C59F4.unk04->unk47C[r7], &UNK_021C59F4.unk04->unk154[param0][r7*stc], stc);

        if (UNK_021C59F4.unk04->unk154[param0][r7*stc] == 0xe) {
            st4++;
        }
    }

    if (st4 == st8) {
        return 0;
    }

    return 1;
}
#else
THUMB_FUNC asm u32 FUN_0202FE2C(int param0) {
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	str r0, [sp, #0xc]
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r0, r0, #0x1
	mov r7, #0x0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _0202FED0
	ldr r0, [sp, #0x0]
	mov r1, #0xc0
	add r6, r0, #0x0
	add r4, r7, #0x0
	add r5, r7, #0x0
	mul r6, r1
_0202FE66:
	ldr r0, =UNK_021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, =0x0000047C
	add r0, r1, r0
	add r0, r0, r4
	bl FUN_0202D4BC
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202FE90
	ldr r0, =UNK_021C59F4
	mov r1, #0xe
	ldr r0, [r0, #0x4]
	add r0, r6, r0
	add r2, r5, r0
	mov r0, #0x55
	lsl r0, r0, #0x2
	strb r1, [r2, r0]
_0202FE90:
	ldr r0, =UNK_021C59F4
	mov r2, #0x55
	ldr r1, [r0, #0x4]
	ldr r0, =0x0000047C
	lsl r2, r2, #0x2
	add r0, r1, r0
	add r1, r1, r2
	add r1, r1, r6
	ldr r2, [sp, #0xc]
	add r0, r0, r4
	add r1, r1, r5
	bl FUN_0202D400
	ldr r0, =UNK_021C59F4
	ldr r0, [r0, #0x4]
	add r0, r6, r0
	add r1, r5, r0
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0xe
	bne _0202FEC2
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0202FEC2:
	ldr r0, [sp, #0xc]
	add r7, r7, #0x1
	add r5, r5, r0
	ldr r0, [sp, #0x8]
	add r4, #0xc
	cmp r7, r0
	blt _0202FE66
_0202FED0:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	cmp r1, r0
	bne _0202FEDE
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0202FEDE:
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
}
#endif



