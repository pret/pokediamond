#include "global.h"
#include "unk_0202F150.h"
#include "unk_02031480.h"
#include "unk_02031734.h"
#include "unk_0202E29C.h"

u8 UNK_021C59F4;
struct UnkStruct0202F150 *UNK_021C59F8;

vu8 UNK_02105D59 = 4;
vu8 UNK_02105D58 = 4;

extern void sub_0202D7D8(u8 *param0, u32 param1, struct UnkStruct0202F150_sub1 *param2);
extern u32 sub_0200CA60(void (*param0)(), u32 param1, u32 param2);
extern void sub_0202D394(struct UnkStruct0202F150_sub1 *param0, u8 *param1, u32 param2);
extern void sub_0202D804(u8 *param0);
extern void sub_0202D330(void (*param0)(int));
extern void ov04_021D83C0();
extern void sub_0202DBA4();
extern void sub_0200CAB4(u32 param0);
extern void sub_0202D824(u8 *param0);
extern u32 ov04_021D78FC(void *param0, u32 param1);
extern u32 sub_0202CBD4();
extern void sub_0202D4BC(void *param0);
extern int sub_0202D400(struct UnkStruct0202F150_sub1 *param0, void *param1, u32 param2);
extern u32 sub_0202D0D0(u8 *param0, u16 param1, u32 param2, void (*param3)(u32));
extern u32 ov04_021D79B4(void *param0, u32 param1);
extern void sub_0202D3A4(struct UnkStruct0202F150_sub1 *param0, u8 *param1, u32 param2, u32 param3);
extern int sub_0202D498(void *param0);
extern u16 sub_0202CB8C();
extern s64 _ll_mul(s64, s64);
extern u32 sub_0202D4E4(u8 *param0);
extern u32 sub_0202D760(u8 *param0, int *param1, u32 param2);
extern u32 sub_0202D684(u8 *param0, u32 param1, u8 *param2, u32 param3, u32 param4, u32 param5);
extern void sub_0202D934(u32 param0, u32 param1, u32 param2, void *param3);
extern int sub_0202D478(struct UnkStruct0202F150_sub1 *param0);
extern u32 sub_0202D41C(struct UnkStruct0202F150_sub1 *param0);
extern s16 sub_0202D9A0(u32 param0);
extern u32 sub_0202DA04(u32 param0);
extern void *sub_0202DA40(u32 param0, u32 param1, u16 param2);
extern u32 ov04_021D8018();
extern u16 sub_0202D19C();
extern void GF_RTC_CopyDateTime(RTCDate *, RTCTime *);
extern void sub_0202D830(u8 *param0, u32 param1);
extern u32 ov04_021D8624();

u32 sub_0202F150(u32 param0, u32 param1)
{
    u32 r4 = 0;
    UNK_021C59F4 = 0;
    if (param0 != 0)
    {
        int res = sub_0202D858((u16)sub_02033534()) + 1;

        if (UNK_021C59F8 != 0)
        {
            return 1;
        }

        sub_02031480(0xf);
        struct UnkStruct0202F150 *ptr =
            (struct UnkStruct0202F150 *)AllocFromHeap(0xf, sizeof(struct UnkStruct0202F150));
        UNK_021C59F8 = ptr;
        MI_CpuFill8(ptr, 0, 0x68C);

        UNK_021C59F8->unk658 = param1 + 0x40;
        UNK_021C59F8->unk67D = 0;
        UNK_021C59F8->unk67E = 0x1b;

        UNK_021C59F8->unk45C = AllocFromHeap(0xf, UNK_021C59F8->unk658 << 1);

        UNK_021C59F8->unk460 = AllocFromHeap(0xf, UNK_021C59F8->unk658);

        UNK_021C59F8->unk458 = AllocFromHeap(0xf, res * UNK_021C59F8->unk658);

        UNK_021C59F8->unk454 = AllocFromHeap(0xf, res * UNK_021C59F8->unk658);

        if (sub_02033534() == 0xa)
        {
            sub_0202D7D8(UNK_021C59F8->unk54C, 0x64, &UNK_021C59F8->unk464);
            sub_0202D7D8(UNK_021C59F8->unk56C, 0x32 << 4, &UNK_021C59F8->unk4DC);
        }
        else
        {
            sub_0202D7D8(UNK_021C59F8->unk54C, 0x14, &UNK_021C59F8->unk464);
            sub_0202D7D8(UNK_021C59F8->unk56C, 0x1b + 0xfd, &UNK_021C59F8->unk4DC);
        }
    }
    else
    {

        r4 = 1;
        GF_ASSERT(UNK_021C59F8 != 0);
    }

    UNK_021C59F8->unk65C = 0;

    for (int i = 0; i < 4; i++)
    {
        UNK_021C59F8->unk677[i] = 0xff;
    }

    if (r4 == 0)
    {
        sub_0202F2F0();
    }

    sub_020312BC(UNK_021C59F8->unk5F8);

    if (r4 == 0)
    {
        u32 res2 = sub_0200CA60(sub_0202FB20, 0, 0);

        UNK_021C59F8->unk548 = res2;
    }

    UNK_021C59F8->unk687 = 0;

    return 1;
}

void sub_0202F2F0()
{
    UNK_021C59F8->unk62C = 0;
    UNK_021C59F8->unk62D = 0;
    UNK_021C59F8->unk67F = 0;
    UNK_021C59F8->unk680 = 0;

    int res = sub_0202D858((u16)sub_02033534()) + 1;

    MI_CpuFill8(UNK_021C59F8->unk458, 0, UNK_021C59F8->unk658 * res);

    int i;
    for (i = 0; i < res; i++)
    {
        sub_0202D394(&UNK_021C59F8->unk4E8[i],
            UNK_021C59F8->unk458 + i * UNK_021C59F8->unk658,
            UNK_021C59F8->unk658);
    }

    MI_CpuFill8(UNK_021C59F8->unk454, 0, UNK_021C59F8->unk658 * res);

    for (i = 0; i < res; i++)
    {
        sub_0202D394(&UNK_021C59F8->unk47C[i],
            UNK_021C59F8->unk454 + i * UNK_021C59F8->unk658,
            UNK_021C59F8->unk658);
    }

    MI_CpuFill8(&UNK_021C59F8->unk2D4, 0, 6 << 6);
    sub_0202D394(&UNK_021C59F8->unk4DC, UNK_021C59F8->unk2D4, 6 << 6);

    for (i = 0; i < 0xc0; i++)
    {
        UNK_021C59F8->unk154[0][i] = 0xee;
        UNK_021C59F8->unk154[1][i] = 0xee;
    }

    MI_CpuFill8(&UNK_021C59F8->unk04c, 0, 0x42 << 2);
    sub_0202D394(&UNK_021C59F8->unk464, UNK_021C59F8->unk04c, 0x42 << 2);

    UNK_021C59F8->unk000[0][0] = 0xff;
    UNK_021C59F8->unk000[1][0] = 0xff;

    for (i = 1; i < 0x26; i++)
    {
        UNK_021C59F8->unk000[0][i] = 0xee;
        UNK_021C59F8->unk000[1][i] = 0xee;
    }

    MI_CpuFill8(UNK_021C59F8->unk45C, 0, UNK_021C59F8->unk658 << 1);

    sub_0202D394(
        &UNK_021C59F8->unk470, UNK_021C59F8->unk45C, UNK_021C59F8->unk658 * 2);

    UNK_021C59F8->unk684 = 0;
    UNK_021C59F8->unk685 = 0;

    for (i = 0; i < 8; i++)
    {
        UNK_021C59F8->unk65F[i] = 0;
        UNK_021C59F8->unk667[i] = 1;
        UNK_021C59F8->unk66F[i] = 1;
        UNK_021C59F8->unk610[i] = 0;

        UNK_021C59F8->unk58C[i].unk0a = 0xee;
        UNK_021C59F8->unk58C[i].unk08 = 0xffff;
        UNK_021C59F8->unk58C[i].unk04 = 0;
        UNK_021C59F8->unk58C[i].unk00 = 0;

        UNK_021C59F8->unk638[i] = 0;
    }

    UNK_021C59F8->unk634 = 0;
    UNK_021C59F8->unk630 = 1;
    UNK_021C59F8->unk5F6 = 0xee;
    UNK_021C59F8->unk5F4 = 0xffff;
    UNK_021C59F8->unk5F0 = 0;
    UNK_021C59F8->unk5EC = 0;
    UNK_021C59F8->unk682 = 1;
    UNK_021C59F8->unk683 = 1;

    UNK_02105D59 = 4;
    UNK_02105D58 = 4;

    sub_0202D804(UNK_021C59F8->unk54C);
    sub_0202D804(UNK_021C59F8->unk56C);

    UNK_021C59F8->unk688 = 0;
}

void sub_0202F5A4()
{
    UNK_021C59F8->unk62C = 0;
    UNK_021C59F8->unk62D = 0;

    int res = sub_0202D858((u16)sub_02033534()) + 1;

    MI_CpuFill8(UNK_021C59F8->unk458, 0, UNK_021C59F8->unk658 * res);

    int i;
    for (i = 0; i < res; i++)
    {
        sub_0202D394(&UNK_021C59F8->unk4E8[i],
            UNK_021C59F8->unk458 + i * UNK_021C59F8->unk658,
            UNK_021C59F8->unk658);
    }

    MI_CpuFill8(UNK_021C59F8->unk454, 0, UNK_021C59F8->unk658 * res);

    for (i = 0; i < res; i++)
    {
        sub_0202D394(&UNK_021C59F8->unk47C[i],
            UNK_021C59F8->unk454 + i * UNK_021C59F8->unk658,
            UNK_021C59F8->unk658);
    }

    MI_CpuFill8(&UNK_021C59F8->unk2D4, 0, 6 << 6);
    sub_0202D394(&UNK_021C59F8->unk4DC, UNK_021C59F8->unk2D4, 6 << 6);

    for (i = 0; i < 0xc0; i++)
    {
        UNK_021C59F8->unk154[0][i] = 0xee;
        UNK_021C59F8->unk154[1][i] = 0xee;
    }

    MI_CpuFill8(&UNK_021C59F8->unk04c, 0, 0x42 << 2);
    sub_0202D394(&UNK_021C59F8->unk464, UNK_021C59F8->unk04c, 0x42 << 2);

    UNK_021C59F8->unk000[0][0] = 0xff;
    UNK_021C59F8->unk000[1][0] = 0xff;

    for (i = 1; i < 0x26; i++)
    {
        UNK_021C59F8->unk000[0][i] = 0xee;
        UNK_021C59F8->unk000[1][i] = 0xee;
    }

    MI_CpuFill8(UNK_021C59F8->unk45C, 0, UNK_021C59F8->unk658 << 1);
    sub_0202D394(
        &UNK_021C59F8->unk470, UNK_021C59F8->unk45C, UNK_021C59F8->unk658 * 2);

    UNK_021C59F8->unk684 = 0;
    UNK_021C59F8->unk685 = 0;

    for (i = 0; i < 8; i++)
    {
        UNK_021C59F8->unk65F[i] = 0;
        UNK_021C59F8->unk667[i] = 1;
        UNK_021C59F8->unk66F[i] = 1;
        UNK_021C59F8->unk610[i] = 0;

        UNK_021C59F8->unk58C[i].unk0a = 0xee;
        UNK_021C59F8->unk58C[i].unk08 = 0xffff;
        UNK_021C59F8->unk58C[i].unk04 = 0;
        UNK_021C59F8->unk58C[i].unk00 = 0;
    }

    UNK_021C59F8->unk630 = 1;
    UNK_021C59F8->unk5F6 = 0xee;
    UNK_021C59F8->unk5F4 = 0xffff;
    UNK_021C59F8->unk5F0 = 0;
    UNK_021C59F8->unk5EC = 0;
    UNK_021C59F8->unk682 = 1;
    UNK_021C59F8->unk683 = 1;

    sub_0202D804(UNK_021C59F8->unk54C);
    sub_0202D804(UNK_021C59F8->unk56C);

    UNK_021C59F8->unk688 = 0;
}

void sub_0202F820(int param0)
{
    UNK_021C59F8->unk65F[param0] = 0;

    UNK_021C59F8->unk667[param0] = 1;

    UNK_021C59F8->unk638[param0] = 0;

    UNK_021C59F8->unk66F[param0] = 1;

    sub_0202D394(&UNK_021C59F8->unk47C[param0],
        UNK_021C59F8->unk454 + param0 * UNK_021C59F8->unk658,
        UNK_021C59F8->unk658);

    sub_0202D394(&UNK_021C59F8->unk4E8[param0],
        UNK_021C59F8->unk458 + param0 * UNK_021C59F8->unk658,
        UNK_021C59F8->unk658);

    UNK_021C59F8->unk58C[param0].unk0a = 0xee;
    UNK_021C59F8->unk58C[param0].unk08 = 0xffff;
    UNK_021C59F8->unk58C[param0].unk04 = 0;
    UNK_021C59F8->unk58C[param0].unk00 = 0;
}

void sub_0202F8D4()
{
    for (int i = 1; i < 8; i++)
    {
        if (sub_02030E7C((u16)i) == 0 && UNK_021C59F8->unk667[i] == 0 && sub_02031280() == 0)
        {
            sub_0202F820(i);
        }
    }
}

void sub_0202F910(int param0)
{
    sub_0202F820(param0);
}

BOOL sub_0202F918(u32 param0, u32 param1, u32 param2, u32 param3)
{
    BOOL ret = TRUE;
    if (sub_02033534() < 0x13)
    {
        ret = sub_0202E5F8(param0, param1, param3);
        sub_0202D330(sub_0202F910);
    }

    sub_0202F150(param0, param2);

    return ret;
}

u32 sub_0202F950(u32 param0, u32 param1, u32 param2)
{
    u32 ret = 1;
    if (sub_02033534() < 0x13)
    {
        ret = sub_0202E66C(param0, param1);
    }

    sub_0202F150(param0, param2);

    UNK_02105D58 = 4;

    return ret;
}

void sub_0202F984()
{
    u32 r4 = 0;
    if (sub_02031190() == 0)
    {
        if (UNK_02105D59 != 4)
        {
            return;
        }
    }
    else
    {
        if (UNK_02105D58 != 4)
        {
            return;
        }
    }

    if (UNK_021C59F8->unk67D == 2)
    {
        UNK_021C59F8->unk67D = 0;
        r4 = 1;
    }

    if (UNK_021C59F8->unk67D == 3)
    {
        UNK_021C59F8->unk67D = 1;
        r4 = 1;
    }

    if (r4 != 0)
    {
        sub_0202F5A4();
    }
    sub_02031088();
}

void sub_0202F9E0(u32 param0)
{
    u8 r2 = UNK_021C59F8->unk67D;
    if (r2 == 0 && param0 == 1)
    {
        UNK_021C59F8->unk67D = 3;
    }
    else if (r2 == 1 && param0 == 0)
    {
        UNK_021C59F8->unk67D = 2;
    }
}

void sub_0202FA10()
{
    sub_0202F9E0(1);
}

void sub_0202FA1C()
{
    sub_0202F9E0(0);
}

u8 sub_0202FA28()
{
    u8 ret = UNK_021C59F8->unk67D;
    if (ret == 2)
    {
        return 1;
    }
    else if (ret == 3)
    {
        return 0;
    }

    return ret;
}

u32 sub_0202FA48()
{
    if (sub_0202FA28() == 1)
    {
        return 1;
    }

    return 0;
}

void sub_0202FA5C()
{
    u32 r4 = 0;
    if (UNK_021C59F8 != 0)
    {
        if (sub_02033534() >= 0x13)
        {
            ov04_021D83C0();
            r4 = 1;
        }
        else
        {
            if (sub_0202E784())
            {
                r4 = 1;
            }
        }
    }

    if (r4 != 0)
    {
        sub_020314D0();
        sub_0202DBA4();
        UNK_021C59F4 = 0;

        sub_0200CAB4(UNK_021C59F8->unk548);
        UNK_021C59F8->unk548 = 0;
        FreeToHeap(UNK_021C59F8->unk45C);
        FreeToHeap(UNK_021C59F8->unk460);
        FreeToHeap(UNK_021C59F8->unk458);
        FreeToHeap(UNK_021C59F8->unk454);
        sub_0202D824(UNK_021C59F8->unk56C);
        sub_0202D824(UNK_021C59F8->unk54C);
        FreeToHeap(UNK_021C59F8);
        UNK_021C59F8 = NULL;
    }
}

u32 sub_0202FB18(u32 param0)
{
    return sub_0202E9E8(param0);
}

void sub_0202FB20()
{
    if (UNK_021C59F4 != 0)
    {
        sub_0203050C();
        if ((sub_02031190() == 0 && sub_02030E7C(0) != 0) || sub_02031280() != 0)
        {
            sub_0202FEEC();
        }

        UNK_021C59F4 = 0;
    }
}

void sub_0202FB58()
{
    if (sub_0202F03C() != 0)
    {
        if (sub_02031190() == 0)
        {
            if (sub_0202EE24() == 0)
            {
                sub_0202FA5C();
            }
        }
        else
        {
            sub_0202FA5C();
        }
    }
}

BOOL sub_0202FB80()
{
    sub_02031CDC();

    if (UNK_021C59F8 != NULL)
    {
        if (UNK_021C59F8->unk68A == 0)
        {
            UNK_021C59F4 = 0;
            sub_0202F984();
            UNK_021C59F8->unk628 |= gSystem.heldKeys & 0x7FFF;
            sub_02030674();
            sub_0202FCCC();

            UNK_021C59F8->unk628 &= 2 << 0xe;
            if (sub_0202FA28() == 0)
            {
                sub_02030DA4();
            }

            if ((sub_02031190() == 0 && sub_02030E7C(0) != 0) || sub_02031280() != 0)
            {
                sub_02030074();
            }

            if (sub_02031190() == 0 || sub_0202FA28() == 1 || sub_02031280() != 0)
            {
                sub_02030DFC();
            }

            UNK_021C59F4 = 1;
        }

        sub_0202ED70(UNK_021C59F8->unk65C);

        if (sub_02031190() == 0)
        {
            sub_0202F8D4();
        }

        sub_0202FB58();
    }
    else
    {
        sub_0202ED70(0);
    }

    sub_020335F4(0);
    sub_020315A4();

    return TRUE;
}

void sub_0202FC60()
{
    u8 r4 = UNK_021C59F4;

    UNK_021C59F4 = 0;

    if (UNK_021C59F8 != NULL)
    {
        sub_0202F2F0();
    }

    UNK_021C59F4 = r4;
}

void sub_0202FC80()
{
    u8 r4 = UNK_021C59F4;

    UNK_021C59F4 = 0;

    if (UNK_021C59F8 != NULL)
    {
        UNK_021C59F8->unk67D = 1;
        sub_0202F2F0();
    }

    UNK_021C59F4 = r4;
}

void sub_0202FCA8()
{
    u8 r4 = UNK_021C59F4;

    UNK_021C59F4 = 0;

    if (UNK_021C59F8 != NULL)
    {
        sub_0202F2F0();
        sub_0202E538();
    }

    UNK_021C59F4 = r4;
}

void sub_0202FCCC()
{
    if (UNK_021C59F8->unk683 != 0)
    {
        if (sub_02033534() >= 0x13)
        {
            if (UNK_021C59F8->unk687 == 0 || ov04_021D78FC(UNK_021C59F8, 0x26) == 0)
            {
                return;
            }

            UNK_021C59F8->unk683 = 0;
            return;
        }

        if (sub_0202CBD4() != 4 || sub_02030E7C(sub_02031190()) == 0)
        {
            if (sub_02031280() == 0)
            {
                return;
            }
        }

        UNK_02105D58 = 0;
        sub_0203050C();
        if (UNK_02105D58 == 0)
        {
            return;
        }

        UNK_021C59F8->unk683 = 0;
        return;
    }

    if (sub_02033534() >= 0x13)
    {
        if (UNK_021C59F8->unk687 == 0)
        {
            return;
        }

        if (UNK_021C59F8->unk630 != 0)
        {
            if ((int)UNK_021C59F8->unk634 > 3)
            {
                return;
            }

            if (UNK_02105D58 == 4)
            {
                sub_02030930(UNK_021C59F8->unk000[0]);
                UNK_02105D58 = 2;
            }
        }
        else
        {
            if (UNK_02105D58 == 4)
            {
                if (sub_02030930(UNK_021C59F8->unk000[0]) == 0)
                {
                    return;
                }

                UNK_02105D58 = 2;
            }
        }

        if (ov04_021D78FC(UNK_021C59F8, 0x26) == 0)
        {
            return;
        }

        UNK_02105D58 = 4;
        UNK_021C59F8->unk634++;
        return;
    }

    if (sub_0202CBD4() != 4 || sub_02030E7C(sub_02031190()) == 0)
    {
        if (sub_02031280() == 0)
        {
            return;
        }
    }

    if (UNK_02105D58 != 4)
    {
        return;
    }

    // nonmatching
    if ((int)UNK_021C59F8->unk634 > 3)
    {
        return;
    }

    sub_02030930(UNK_021C59F8->unk000[UNK_021C59F8->unk67F]);

    sub_02030930(UNK_021C59F8->unk000[1 - UNK_021C59F8->unk67F]);

    UNK_02105D58 = 0;
    sub_0203050C();
}

#ifdef NONMATCHING
BOOL sub_0202FE2C(int param0)
{

    // these 3 variables are shuffled on the stack, everything else matches
    int stc;
    int st8;
    int r7, unused, st4 = 0;

    stc = sub_02031228(sub_02033534());
    st8 = sub_0202D858(sub_02033534()) + 1;

    for (r7 = 0; r7 < st8; r7++)
    {

        sub_0202D4BC(&UNK_021C59F8->unk47C[r7]);

        if (sub_02030E7C(r7))
        {
            UNK_021C59F8->unk154[param0][r7 * stc] = 0xe;
        }

        unused = sub_0202D400(
            &UNK_021C59F8->unk47C[r7], &UNK_021C59F8->unk154[param0][r7 * stc], stc);

        if (UNK_021C59F8->unk154[param0][r7 * stc] == 0xe)
        {
            st4++;
        }
    }

    if (st4 == st8)
    {
        return FALSE;
    }

    return TRUE;
}
#else
asm BOOL sub_0202FE2C(int param0)
{
    // clang-format off
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	bl sub_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl sub_02031228
	str r0, [sp, #0xc]
	bl sub_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl sub_0202D858
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
	bl sub_0202D4BC
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	bl sub_02030E7C
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
	bl sub_0202D400
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
    // clang-format on
}
#endif

void sub_0202FEEC()
{
    if (UNK_021C59F8 == NULL || sub_02033534() >= 0x13)
    {
        return;
    }

    int st0 = sub_02031228((u16)sub_02033534());
    int r6 = sub_0202D858((u16)sub_02033534()) + 1;

    if (UNK_02105D59 == 2 || UNK_02105D59 == 0)
    {

        UNK_02105D59++;

        if (sub_0202FA28() == 1)
        {
            sub_0202FE2C(UNK_021C59F8->unk680);
        }

        if (sub_0202CBD4() == 4 && sub_02031280() == 0)
        {

            if (sub_0202D0D0(UNK_021C59F8->unk154[UNK_021C59F8->unk680],
                    0xc0,
                    0xe,
                    sub_020304F0) == 0)
            {
                UNK_02105D59--;
            }
        }

        int i;
        if (UNK_02105D59 == 1 || UNK_02105D59 == 3)
        {
            for (i = 0; i < r6; i++)
            {
                if (sub_02030E7C((u16)i) != 0)
                {
                    UNK_021C59F8->unk638[i]++;
                }
                else if (sub_02031280() != 0 && i == 0)
                {
                    UNK_021C59F8->unk638[i]++;
                }
            }

            sub_0203026C(0, UNK_021C59F8->unk154[UNK_021C59F8->unk680], 0xc0);

            UNK_021C59F8->unk680 = (u8)(1 - UNK_021C59F8->unk680);
        }

        for (i = 0; i < r6; i++)
        {
            if (sub_02030E7C((u16)i) == 0 && sub_0202FA28() == 1)
            {
                UNK_021C59F8->unk154[UNK_021C59F8->unk680][i * st0] = 0xff;
            }
        }

        if (sub_0202CBD4() != 4 || sub_02031280() != 0)
        {
            UNK_02105D59++;
        }
    }
}

void sub_02030074()
{
    if (UNK_021C59F8->unk683 != 0)
    {
        if (sub_02033534() >= 0x13)
        {
            if (sub_02030E7C(0) != 0 && ov04_021D79B4(UNK_021C59F8->unk154, 0x4c) != 0)
            {
                UNK_021C59F8->unk683 = 0;
                return;
            }
        }
        else if (sub_0202CBD4() == 4 || sub_02031280() != 0)
        {
            sub_0202FEEC();
            if (UNK_02105D59 == 2)
            {
                UNK_021C59F8->unk683 = 0;
                return;
            }
        }
    }

    if (sub_02033534() >= 0x13)
    {
        if (sub_02030E7C(0) != 0)
        {
            if (UNK_021C59F8->unk630 != 0)
            {
                if ((int)UNK_021C59F8->unk638[1] > 3 ||
                    (int)UNK_021C59F8->unk638[0] > 3)
                {
                    return;
                }

                if (UNK_02105D59 == 4)
                {
                    if (sub_0202FA28() == 1)
                    {
                        sub_0202FE2C(0);
                    }

                    UNK_02105D59 = 2;
                }
            }
            else
            {
                if (UNK_02105D59 == 4)
                {
                    if (sub_0202FA28() == 1)
                    {
                        if (sub_0202FE2C(0) == 0)
                        {
                            return;
                        }
                    }
                }

                UNK_02105D59 = 2;
            }

            if (ov04_021D79B4(UNK_021C59F8->unk154, 0x4c) == 0)
            {
                return;
            }

            UNK_02105D59 = 4;
            UNK_021C59F8->unk638[0]++;
            UNK_021C59F8->unk638[1]++;
        }
    }
    else if (sub_0202CBD4() == 4 || sub_02031280() != 0)
    {
        if (UNK_02105D59 == 4)
        {
            for (int r4 = 1; r4 < 8; r4++)
            {
                if (sub_02030E7C((u16)r4) != 0)
                {
                    if ((int)UNK_021C59F8->unk638[r4] > 3)
                    {
                        return;
                    }
                }
                else if (r4 == 0)
                {
                    if (sub_02031280() != 0)
                    {
                        if ((int)UNK_021C59F8->unk638[0] > 3)
                        {
                            return;
                        }
                    }
                }
            }

            if (sub_0202FA28() == 0)
            {
                sub_02030A00(UNK_021C59F8->unk154[UNK_021C59F8->unk680]);
                sub_02030A00(UNK_021C59F8->unk154[1 - UNK_021C59F8->unk680]);
            }

            UNK_02105D59 = 0;
            sub_0202FEEC();
        }
    }
}

void sub_02030238(u32 param0, u8 *param1, u32 param2)
{
    if (UNK_021C59F8->unk66F[0] != 0)
    {
        UNK_021C59F8->unk634--;
        UNK_021C59F8->unk66F[0] = 0;
        return;
    }

    sub_0203026C(param0, param1, param2);
}

void sub_0203026C(u32 param0, u8 *param1, u32 param2)
{
#pragma unused(param0)
#pragma unused(param2)
    UNK_021C59F8->unk634--;
    if (param1 == 0)
    {
        return;
    }

    if (param1[0] == 0xb)
    {
        if (sub_0202FA28() == 1)
        {
            return;
        }
        param1++;
    }
    else
    {
        if (sub_0202FA28() == 0)
        {
            return;
        }
    }

    if (UNK_021C59F8->unk682 != 0)
    {
        if ((param1[0] & 1) != 0)
        {
            return;
        }
    }

    UNK_021C59F8->unk682 = 0;
    if (sub_0202FA28() == 1)
    {
        int r6 = sub_02031228((u16)sub_02033534());
        int st4 = sub_0202D858((u16)sub_02033534()) + 1;

        int r4 = 0;
        while (r4 < st4)
        {

            if (param1[0] == 0xff)
            {
                UNK_021C59F8->unk65C &= ~(1 << r4);
            }
            else
            {
                UNK_021C59F8->unk65C |= (1 << r4);
            }

            if (param1[0] == 0xff)
            {
                param1 += r6;
            }
            else if (param1[0] == 0xe)
            {
                param1 += r6;
            }
            else if (UNK_021C59F8->unk667[r4] != 0 && (param1[0] & 1) != 0)
            {
                param1 += r6;
            }
            else
            {
                param1++;
                sub_0202D3A4(&UNK_021C59F8->unk4E8[r4], param1, (u32)(r6 - 1), 0x5E6);

                param1 += r6 - 1;
                UNK_021C59F8->unk667[r4] = 0;
            }

            r4++;
        }

        return;
    }

    UNK_021C59F8->unk65C = param1[1];
    UNK_021C59F8->unk65C <<= 8;

    UNK_021C59F8->unk65C += param1[2];
    sub_0202D3A4(&UNK_021C59F8->unk470, param1 + 4, param1[3], 0x5FF);
}

void sub_020303BC(u32 param0, u8 *param1, u32 param2)
{
    if (UNK_021C59F8->unk66F[param0] != 0)
    {

        UNK_021C59F8->unk638[param0]--;
        UNK_021C59F8->unk66F[param0] = 0;
        return;
    }

    sub_020303F4(param0, param1, param2);
}

void sub_020303F4(u32 param0, u8 *param1, u32 param2)
{
#pragma unused(param2)
    UNK_021C59F8->unk638[param0]--;
    if (param1 == 0)
    {
        return;
    }

    if (UNK_021C59F8->unk667[param0] != 0 && (param1[0] & 1) != 0)
    {
        return;
    }

    UNK_021C59F8->unk667[param0] = 0;
    if (sub_0202FA28() == 1)
    {
        int r6 = sub_02031228((u16)sub_02033534());
        sub_0202D858((u16)sub_02033534());

        if ((param1[0] & 2) == 0)
        {
            sub_0202D3A4(&UNK_021C59F8->unk47C[param0], param1, (u32)r6, 0x65E);
        }

        UNK_021C59F8->unk65F[param0]++;
        return;
    }

    sub_020307E4(param1, param0);

    if ((param1[0] & 2) == 0 && sub_0202D498(&UNK_021C59F8->unk4E8[param0]) >= 0xb)
    {
        sub_0202D3A4(&UNK_021C59F8->unk4E8[param0], param1 + 1, 0xb, 0x66E);
    }
}

void sub_020304D4(u32 param0)
{
    if (param0 != 0)
    {
        UNK_02105D58++;
        return;
    }

    GF_ASSERT(0);
}

void sub_020304F0(u32 param0)
{
    if (param0 != 0)
    {
        UNK_02105D59++;
        return;
    }

    GF_ASSERT(0);
}

void sub_0203050C()
{
    if (UNK_021C59F8 == 0 || sub_02033534() >= 0x13)
    {
        return;
    }

    int r4 = sub_02031228((u16)sub_02033534());
    sub_0202D858((u16)sub_02033534());

    if (sub_02031280() != 0 && (UNK_02105D58 == 2 || UNK_02105D58 == 0))
    {
        UNK_02105D58++;
        sub_020304D4(1);

        sub_020303F4(0, UNK_021C59F8->unk000[UNK_021C59F8->unk67F], (u16)r4);

        UNK_021C59F8->unk67F = (u8)(1 - UNK_021C59F8->unk67F);
        UNK_021C59F8->unk634++;
        return;
    }

    if (sub_0202CBD4() != 4)
    {
        return;
    }

    if (sub_02030E7C(sub_02031190()) == 0)
    {
        sub_02031190();
        return;
    }

    if (UNK_02105D58 != 2 && UNK_02105D58 != 0)
    {
        return;
    }

    if (sub_02031190() != 0)
    {
        UNK_02105D58++;

        if (sub_0202D0D0(UNK_021C59F8->unk000[UNK_021C59F8->unk67F],
                (u16)r4,
                0xe,
                sub_020304D4) == 0)
        {
            UNK_02105D58--;
            return;
        }

        UNK_021C59F8->unk67F = (u8)(1 - UNK_021C59F8->unk67F);
        UNK_021C59F8->unk634++;
        return;
    }

    if ((sub_0202CB8C() & 0xFFFE) != 0)
    {
        UNK_02105D58++;
        sub_020304D4(1);

        sub_020303F4(0, UNK_021C59F8->unk000[UNK_021C59F8->unk67F], (u16)r4);

        UNK_021C59F8->unk67F = (u8)(1 - UNK_021C59F8->unk67F);
        UNK_021C59F8->unk634++;
    }
}

#ifdef NONMATCHING
void sub_02030674()
{
    u16 r4 = 0;
    if (UNK_021C59F8->unk62C == 0 || (UNK_021C59F8->unk628 & 0xf0) == 0)
    {
        return;
    }

    if (UNK_021C59F8->unk62C == 2)
    {
        if ((UNK_021C59F8->unk628 & 0x20) != 0)
        {
            r4 = r4 | 0x10;
        }

        if ((UNK_021C59F8->unk628 & 0x10) != 0)
        {
            r4 = r4 | 0x20;
        }

        if ((UNK_021C59F8->unk628 & 0x40) != 0)
        {
            r4 = r4 | 0x80;
        }

        if ((UNK_021C59F8->unk628 & 0x80) != 0)
        {
            r4 = r4 | 0x40;
        }
    }
    else
    {
        if (UNK_021C59F8->unk62E != 0)
        {
            r4 = UNK_021C59F8->unk62E;
            UNK_021C59F8->unk62D--;

            if (UNK_021C59F8->unk62D < 0)
            {
                UNK_021C59F8->unk62E = 0;
            }
        }
        else
        {
            UNK_021C59F8->unk5F8[0] =
                UNK_021C59F8->unk5F8[1] * UNK_021C59F8->unk5F8[0] +
                UNK_021C59F8->unk5F8[2];

            switch ((u32)(UNK_021C59F8->unk5F8[0] >> 0x3E) | (0 << 2))
            {
            case 0:
                r4 = 0x20;
                break;
            case 1:
                r4 = 0x10;
                break;
            case 2:
                r4 = 0x40;
                break;
            case 3:
                r4 = 0x80;
                break;
            }

            UNK_021C59F8->unk5F8[0] =
                UNK_021C59F8->unk5F8[2] +
                UNK_021C59F8->unk5F8[1] * UNK_021C59F8->unk5F8[0];
            UNK_021C59F8->unk62D = UNK_021C59F8->unk5F8[0] >> 0x3c | (0 << 4);
            UNK_021C59F8->unk62E = r4;
        }
    }

    UNK_021C59F8->unk628 &= ~0xf0;
    UNK_021C59F8->unk628 += r4;
}
#else
asm void sub_02030674()
{
    // clang-format off
	push {r3-r7, lr}
	ldr r7, =UNK_021C59F4
	mov r6, #0x0
	ldr r5, [r7, #0x4]
	ldr r2, =0x0000062C
	add r4, r6, #0x0
	ldrb r0, [r5, r2]
	cmp r0, #0x0
	beq _02030690
	sub r1, r2, #0x4
	ldrh r1, [r5, r1]
	mov r3, #0xf0
	tst r3, r1
	bne _02030692
_02030690:
	b _02030794
_02030692:
	cmp r0, #0x2
	bne _020306D0
	mov r0, #0x20
	tst r0, r1
	beq _020306A4
	mov r0, #0x10
	orr r0, r6
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306A4:
	mov r0, #0x10
	tst r0, r1
	beq _020306B2
	mov r0, #0x20
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306B2:
	mov r0, #0x40
	tst r0, r1
	beq _020306C0
	mov r0, #0x80
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306C0:
	mov r0, #0x80
	tst r0, r1
	beq _0203077E
	mov r0, #0x40
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	b _0203077E
_020306D0:
	add r0, r2, #0x2
	ldrh r0, [r5, r0]
	cmp r0, #0x0
	beq _020306F2
	add r4, r0, #0x0
	add r0, r2, #0x1
	ldrsb r0, [r5, r0]
	sub r1, r0, #0x1
	add r0, r2, #0x1
	strb r1, [r5, r0]
	ldr r1, [r7, #0x4]
	ldrsb r0, [r1, r0]
	cmp r0, #0x0
	bge _0203077E
	add r0, r2, #0x2
	strh r6, [r1, r0]
	b _0203077E
_020306F2:
	add r0, r2, #0x0
	sub r0, #0x34
	add r6, r5, r0
	sub r2, #0x34
	ldr r0, [r6, #0x8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, r2]
	ldr r3, [r6, #0x4]
	bl _ll_mul
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, [r6, #0x10]
	ldr r1, [r6, #0x14]
	add r0, r0, r3
	adc r1, r2
	ldr r2, =0x000005F8
	str r0, [r5, r2]
	mov r2, #0x0
	str r1, [r6, #0x4]
	lsr r0, r1, #0x1e
	lsl r1, r2, #0x2
	orr r1, r0
	cmp r1, #0x3
	bhi _02030746
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02030730: // jump table (using 16-bit offset)
    // huge hack to get the correct jump offset. Is there a way to write constants?
    lsl r6, r0, #0x0 // case 0
    lsl r2, r1, #0x0 // case 1
    lsl r6, r1, #0x0 // case 2
    lsl r2, r2, #0x0 // case 3

    // intended jump offset
    // .short _02030738 - _02030730 - 2; case 0
	// .short _0203073C - _02030730 - 2; case 1
	// .short _02030740 - _02030730 - 2; case 2
	// .short _02030744 - _02030730 - 2; case 3
_02030738:
	mov r4, #0x20
	b _02030746
_0203073C:
	mov r4, #0x10
	b _02030746
_02030740:
	mov r4, #0x40
	b _02030746
_02030744:
	mov r4, #0x80
_02030746:
	ldr r0, =UNK_021C59F4
	ldr r5, [r0, #0x4]
	ldr r0, =0x000005F8
	add r6, r5, r0
	ldr r0, [r6, #0x8]
	ldr r1, [r6, #0xc]
	ldr r2, [r6, #0x0]
	ldr r3, [r6, #0x4]
	bl _ll_mul
	ldr r3, [r6, #0x10]
	ldr r2, [r6, #0x14]
	add r0, r3, r0
	adc r2, r1
	ldr r1, =0x000005F8
	mov r3, #0x0
	str r0, [r5, r1]
	str r2, [r6, #0x4]
	lsr r0, r2, #0x1c
	lsl r2, r3, #0x4
	orr r2, r0
	add r0, r1, #0x0
	add r0, #0x35
	strb r2, [r5, r0]
	ldr r0, =UNK_021C59F4
	add r1, #0x36
	ldr r0, [r0, #0x4]
	strh r4, [r0, r1]
_0203077E:
	ldr r2, =UNK_021C59F4
	ldr r1, =0x00000628
	ldr r5, [r2, #0x4]
	mov r0, #0xf0
	ldrh r3, [r5, r1]
	bic r3, r0
	strh r3, [r5, r1]
	ldr r2, [r2, #0x4]
	ldrh r0, [r2, r1]
	add r0, r0, r4
	strh r0, [r2, r1]
_02030794:
	pop {r3-r7, pc}
    // clang-format on
}
#endif

void sub_020307A8()
{
    UNK_021C59F8->unk62C = 1;
}

void sub_020307BC()
{
    UNK_021C59F8->unk62C = 2;
}

void sub_020307D0()
{
    UNK_021C59F8->unk62C = 0;
}

u32 sub_020307E4(u8 *param0, u32 param1)
{
    UNK_021C59F8->unk610[param1] = 0;

    int r7 = param0[0] & 0x10;
    if (r7 == 0x10)
    {

        u8 r5 = (u8)(param0[0] & 0xc);
        if (r5 == 0)
        {
            UNK_021C59F8->unk610[param1] |= 0x40;
        }
        else if (r5 == 4)
        {
            UNK_021C59F8->unk610[param1] |= 0x80;
        }
        else if (r5 == 8)
        {
            UNK_021C59F8->unk610[param1] |= 0x20;
        }
        else if (r5 == 0xc)
        {
            UNK_021C59F8->unk610[param1] |= 0x10;
        }

        UNK_021C59F8->unk620[param1] = (u8)((param0[0] >> 5) & 0x7);
    }

    return 1;
}

void sub_0203086C()
{
}

u32 sub_02030870(u8 *param0)
{
    if (UNK_021C59F8->unk62A != 0)
    {
        return 0;
    }

    if (sub_02030FE0() == 0)
    {
        return 0;
    }

    if (UNK_021C59F8->unk681 != 0)
    {
        UNK_021C59F8->unk681--;
    }

    if ((UNK_021C59F8->unk628 & 0x40) != 0)
    {
        param0[0] |= 0x10;
        UNK_021C59F8->unk681 = 8;
    }
    else if ((UNK_021C59F8->unk628 & 0x80) != 0)
    {
        param0[0] |= 0x14;
        UNK_021C59F8->unk681 = 8;
    }
    else if ((UNK_021C59F8->unk628 & 0x20) != 0)
    {
        param0[0] |= 0x18;
        UNK_021C59F8->unk681 = 8;
    }
    else if ((UNK_021C59F8->unk628 & 0x10) != 0)
    {
        param0[0] |= 0x1c;
        UNK_021C59F8->unk681 = 8;
    }

    param0[0] |= UNK_021C59F8->unk62B << 5;

    return 0;
}

u32 sub_02030930(u8 *param0)
{
    int r5 = sub_02031228((u16)sub_02033534());
    sub_0202D858((u16)sub_02033534());

    if (UNK_021C59F8->unk684 == 0)
    {
        param0[0] = 0;
    }
    else
    {
        param0[0] = 1;
    }

    if (sub_0202FA28() == 0)
    {
        sub_02030870(param0);
    }

    UNK_021C59F8->unk684 = 0;

    if (sub_0202D4E4(UNK_021C59F8->unk54C) != 0)
    {
        param0[0] |= 2;
        if (param0[0] == 2)
        {
            return 0;
        }
    }
    else
    {
        int st0[2];
        st0[1] = r5 - 1;
        st0[0] = (int)param0 + 1;
        if (sub_0202D760(UNK_021C59F8->unk54C, st0, 1) == 0)
        {
            UNK_021C59F8->unk684 = 1;
        }

        if (sub_0202FA28() == 1)
        {
            UNK_021C59F8->unk65E++;

            param0[0] |= UNK_021C59F8->unk65E << 4 & 0xf0;
        }
    }

    return 1;
}

void sub_02030A00(u8 *param0)
{
    param0[0] = 0xb;
    if (UNK_021C59F8->unk685 == 0)
    {
        param0[1] = 0;
    }
    else
    {
        param0[1] = 1;
    }

    u16 res = sub_0202CB8C();
    param0[2] = (u8)(res >> 8);
    param0[3] = (u8)res;

    int st0[2];
    st0[1] = 0xbb;
    st0[0] = (int)param0 + 5;
    if (sub_0202D760(UNK_021C59F8->unk56C, st0, 0) != 0)
    {
        UNK_021C59F8->unk685 = 0;
        param0[4] = (u8)(0xbb - st0[1]);

        return;
    }

    UNK_021C59F8->unk685 = 1;
    param0[4] = 0xbb;
}

u32 sub_02030A78(u32 param0, u8 *param1, u32 param2)
{
    if (sub_02030E7C(sub_02031190()) == 0 && sub_02031280() == 0)
    {
        return 0;
    }

    if (sub_0202D684(UNK_021C59F8->unk54C, param0, param1, param2, 1, 0) != 0)
    {
        return 1;
    }

    if (sub_02033534() == 0xa)
    {
        sub_02031454();
    }

    return 0;
}

u32 sub_02030ADC(u32 param0, u8 *param1, u32 param2)
{
    if (sub_02030E7C(sub_02031190()) == 0 && sub_02031280() == 0)
    {
        return 0;
    }

    if (sub_0202D684(UNK_021C59F8->unk54C, param0, param1, param2, 1, 1) != 0)
    {
        return 1;
    }

    if (sub_02033534() == 0xa)
    {
        sub_02031454();
    }

    return 0;
}

u32 sub_02030B3C(u32 param0, u8 *param1, u32 param2)
{
    if (sub_02031190() != 0)
    {
        GF_ASSERT(0);
        return 0;
    }

    if (sub_02030E7C(0) == 0 && sub_02031280() == 0)
    {
        return 0;
    }

    if (sub_0202FA28() == 1)
    {
        return sub_02030A78(param0, param1, param2);
    }

    if (sub_0202D684(UNK_021C59F8->unk56C, param0, param1, param2, 1, 0) != 0)
    {
        return 1;
    }

    if (sub_02033534() == 0xa)
    {
        sub_02031454();
    }

    return 0;
}

u32 sub_02030BC4(u32 param0, u8 *param1, u32 param2)
{
    if (sub_02031190() != 0)
    {
        sub_02031454();
        return 0;
    }

    if (sub_02030E7C(0) == 0 && sub_02031280() == 0)
    {
        return 0;
    }

    if (sub_0202FA28() == 1)
    {
        return sub_02030ADC(param0, param1, param2);
    }

    if (sub_0202D684(UNK_021C59F8->unk56C, param0, param1, param2, 1, 1) != 0)
    {
        return 1;
    }

    if (sub_02033534() == 0xa)
    {
        sub_02031454();
    }

    return 0;
}

u32 sub_02030C4C(u32 param0, u8 *param1)
{
    return sub_02030BC4(param0, param1, 0);
}

int sub_02030C58()
{
    return sub_0202D498(&UNK_021C59F8->unk464);
}

void sub_02030C70(
    u32 param0, u32 param1, u32 param2, void *param3, struct UnkStruct0202F150_sub2 *param4)
{
    sub_0202D934(param0, param1, param2, param3);
    param4->unk0a = 0xee;
    param4->unk08 = 0xffff;
    param4->unk04 = 0;
    param4->unk00 = 0;
}

void sub_02030C8C(struct UnkStruct0202F150_sub1 *param0,
    u32 param1,
    void *param2,
    u32 param3,
    struct UnkStruct0202F150_sub2 *param4)
{
#pragma unused(param3)
    while (sub_0202D478(param0) != 0)
    {

        u32 r7 = param4->unk0a;
        if (r7 == 0xee)
        {
            r7 = sub_0202D41C(param0);
            if (r7 == 0xee)
            {
                continue;
            }
        }

        int st10 = param0->unk04;
        param4->unk0a = (u8)r7;
        int r4 = param4->unk08;
        if (r4 == 0xffff)
        {
            r4 = sub_0202D9A0(r7);

            if (UNK_021C59F8->unk689 != 0)
            {
                return;
            }

            if (r4 == 0xffff)
            {
                if (sub_0202D478(param0) < 1)
                {
                    param0->unk04 = (s16)st10;
                    return;
                }

                r4 = (int)sub_0202D41C(param0) << 8;
                r4 += sub_0202D41C(param0);

                st10 = param0->unk04;
            }

            param4->unk08 = (u16)r4;
        }

        if (sub_0202DA04(r7) != 0)
        {
            if (param4->unk04 == 0)
            {
                param4->unk04 = sub_0202DA40(r7, param1, param4->unk08);
            }

            int stc = sub_0202D400(param0, param2, r4 - param4->unk00);

            if (param4->unk04 != 0)
            {
                MI_CpuCopy8(param2, param4->unk04 + param4->unk00, (u32)stc);
            }

            if ((int)(param4->unk00 += stc) < (int)r4)
            {
                continue;
            }

            sub_02030C70(param1, r7, (u32)r4, param4->unk04, param4);
        }
        else
        {
            if (sub_0202D478(param0) >= r4)
            {
                sub_0202D400(param0, param2, (u32)r4);
                sub_02030C70(param1, r7, (u32)r4, param2, param4);
            }
            else
            {
                param0->unk04 = (s16)st10;
                return;
            }
        }
    }
}

void sub_02030DA4()
{
    if (UNK_021C59F8 != NULL)
    {
        if (UNK_021C59F8->unk68B == 0)
        {
            sub_0202D4BC(&UNK_021C59F8->unk470);
            if (sub_0202D478(&UNK_021C59F8->unk470) > 0)
            {
                sub_02030C8C(&UNK_021C59F8->unk470,
                    0,
                    UNK_021C59F8->unk460,
                    1,
                    (struct UnkStruct0202F150_sub2 *)&UNK_021C59F8->unk5EC);
            }
        }
    }
}

void sub_02030DFC()
{
    if (UNK_021C59F8 != NULL)
    {
        if (UNK_021C59F8->unk68B == 0)
        {
            int r7 = sub_0202D858((u16)sub_02033534()) + 1;
            int r4;
            for (r4 = 0; r4 < r7; r4++)
            {
                sub_0202D4BC(&UNK_021C59F8->unk4E8[r4]);
                if (sub_0202D478(&UNK_021C59F8->unk4E8[r4]) > 0)
                {

                    sub_02030C8C(&UNK_021C59F8->unk4E8[r4],
                        (u32)r4,
                        UNK_021C59F8->unk460,
                        0,
                        &UNK_021C59F8->unk58C[r4]);
                }
            }
        }
    }
}

BOOL sub_02030E7C(u16 param0)
{
    if (UNK_021C59F8 == NULL)
    {
        return FALSE;
    }

    if (sub_02033534() >= 0x13)
    {
        if (UNK_021C59F8->unk687 != 0 && ov04_021D8018() != 0xffffffff)
        {
            if (param0 == 0)
            {
                return TRUE;
            }

            if (param0 == 1)
            {
                return TRUE;
            }
        }

        return FALSE;
    }

    if (sub_02030F40() == 0)
    {
        return FALSE;
    }

    if (sub_0202CBD4() != 4)
    {
        return FALSE;
    }

    if (sub_02031190() == param0)
    {
        return TRUE;
    }

    if (sub_02031190() == 0)
    {
        u16 r0 = sub_0202CB8C();

        if ((r0 & (1 << param0)) != 0)
        {
            return TRUE;
        }
    }
    else
    {
        if ((UNK_021C59F8->unk65C & (1 << param0)) != 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

s32 sub_02030F20()
{
    s32 r4 = 0;
    for (int i = 0; i < 8; i++)
    {
        if (sub_02030E7C((u16)i) != 0)
        {
            r4++;
        }
    }

    return r4;
}

BOOL sub_02030F40()
{
    if (UNK_021C59F8 != NULL && sub_02033534() >= 0x13)
    {
        return TRUE;
    }

    return sub_0202EDF8();
}

void sub_02030F60(u8 param0)
{
    UNK_021C59F8->unk62B = param0;
}

u8 sub_02030F74(u32 param0)
{
    return UNK_021C59F8->unk620[param0];
}

u32 sub_02030F88(u32 param0)
{
    if (UNK_021C59F8 == NULL)
    {
        return 0;
    }

    u32 ret = UNK_021C59F8->unk610[param0];
    UNK_021C59F8->unk610[param0] = 0;

    return ret;
}

void sub_02030FA8()
{
    if (UNK_021C59F8 != NULL)
    {
        UNK_021C59F8->unk628 |= 0x8000;
    }
}

void sub_02030FC8()
{
    if (UNK_021C59F8 != NULL)
    {
        UNK_021C59F8->unk628 = 0;
    }
}

u32 sub_02030FE0()
{
    if (UNK_021C59F8 != NULL)
    {
        return (u32)(UNK_021C59F8->unk628 & 0x8000);
    }

    return 1;
}

void sub_02031000(u32 param0, u8 *param1, u32 param2)
{
    if (sub_0202FA28() == 1)
    {
        sub_0202D684(UNK_021C59F8->unk54C, param0, param1, param2, 1, 0);
        return;
    }

    sub_0202D684(UNK_021C59F8->unk56C, param0, param1, param2, 1, 0);
}

void sub_0203105C(u32 param0, u8 *param1, u32 param2)
{
    sub_0202D684(UNK_021C59F8->unk54C, param0, param1, param2, 0, 0);
}

void sub_02031088()
{
    if (UNK_021C59F8 != NULL)
    {
        if (UNK_021C59F8->unk67B != 1)
        {
            if (UNK_021C59F8->unk67B != 3)
            {
                return;
            }
        }
        else
        {
            u32 res;
            if (sub_0202FA28() == 1)
            {
                res = sub_020311D0(0xb, &UNK_021C59F8->unk67C);
            }
            else
            {
                res = sub_02030BC4(0xb, &UNK_021C59F8->unk67C, 1);
            }

            if (res == 0)
            {
                return;
            }
            UNK_021C59F8->unk67B = 2;
            return;
        }

        if (sub_020311D0(0xc, &UNK_021C59F8->unk67C) != 0)
        {
            sub_0202F9E0(UNK_021C59F8->unk67C);
            UNK_021C59F8->unk67B = 0;
        }
    }
}

void sub_0203110C(u32 param0, u32 param1, u8 *param2)
{
#pragma unused(param0)
#pragma unused(param1)
    if (sub_02031190() == 0)
    {
        UNK_021C59F8->unk67B = 1;
        UNK_021C59F8->unk67C = param2[0];
    }
}

void sub_02031134(u32 param0, u32 param1, u8 *param2)
{
#pragma unused(param0)
#pragma unused(param1)
    if (sub_02031190() != 0)
    {
        UNK_021C59F8->unk67C = param2[0];
        UNK_021C59F8->unk67B = 3;
    }
}

void sub_0203115C(u32 param0, u32 param1, u8 *param2)
{
#pragma unused(param0)
#pragma unused(param1)
    if (sub_02031190() == 0 && UNK_021C59F8->unk67B == 2)
    {
        sub_0202F9E0(*param2);
        UNK_021C59F8->unk67B = 0;
    }
}

u16 sub_02031190()
{
    if (UNK_021C59F8 != NULL)
    {
        if (sub_02033534() >= 0x13)
        {
            u32 res = ov04_021D8018();
            if (res != 0xffffffff)
            {
                return (u16)res;
            }
        }
        else
        {
            if (sub_02031280() != 0)
            {
                return 0;
            }

            return sub_0202D19C();
        }
    }

    return 0;
}

u32 sub_020311D0(u32 param0, u8 *param1)
{
    return sub_02030ADC(param0, param1, 0);
}

u32 sub_020311DC(u32 param0)
{
    return sub_02030ADC(param0, 0, 0);
}

u32 sub_020311E8()
{
    return sub_0202EE24();
}

BOOL sub_020311F0()
{
    if (sub_02031280() != 0)
    {
        return FALSE;
    }

    if (UNK_021C59F8 != NULL && UNK_021C59F8->unk689 != 0)
    {
        sub_020334E8(1, 1);
        return TRUE;
    }

    return sub_0202EE60();
}

int sub_02031228(u16 param0)
{
    if (sub_0202D858(param0) >= 5)
    {
        return 0xc;
    }

    if (sub_0202FA28() == 0)
    {
        return 0xc;
    }

    return 0x26;
}

int sub_02031248(u32 param0)
{
    return sub_0202D858((u16)param0) + 1;
}

int sub_02031258(u32 param0)
{
    return sub_0202D884((u16)param0) + 1;
}

void sub_02031268(u8 param0)
{
    if (UNK_021C59F8 != NULL)
    {
        UNK_021C59F8->unk686 = param0;
    }
}

u8 sub_02031280()
{
    if (UNK_021C59F8 != NULL)
    {
        return UNK_021C59F8->unk686;
    }

    return 0;
}

void sub_0203129C()
{
    if (sub_0202F03C() == 0 && sub_02031190() == 0)
    {
        u8 st0;
        sub_02030C4C(2, &st0);
    }

    sub_0202F05C();
}

#ifdef NONMATCHING
void sub_020312BC(s64 *param0)
{
    RTCDate st10;
    RTCTime st4;
    GF_RTC_CopyDateTime(&st10, &st4);

    gSystem.unk2C + st4.second;
    u32 r6 = st10.year << 4 + st10.month;
    u32 r5 = 0 << 4 | st10.year >> 0x1c;
    st4.second;

    u32 st0 = st10.day;
    st4.hour;
    st4.minute;

    0x00000000;
    (0x00000000 + r5) << 5;
}
#else
asm void sub_020312BC(s64 *param0)
{
    // clang-format off
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	add r0, sp, #0x10
	add r1, sp, #0x4
	bl GF_RTC_CopyDateTime
	ldr r0, =gSystem
	ldr r6, [sp, #0x10]
	mov r5, #0x0
	lsr r7, r6, #0x1c
	lsl r5, r5, #0x4
	ldr r1, [sp, #0xc]
	ldr r0, [r0, #0x2c]
	lsl r6, r6, #0x4
	add r3, r1, r0
	ldr r0, [sp, #0x18]
	orr r5, r7
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x4]
	add r6, r0, r6
	ldr r0, =0x00000000
	ldr r2, [sp, #0x8]
	adc r0, r5
	lsr r5, r6, #0x1b
	lsl r0, r0, #0x5
	orr r0, r5
	ldr r5, [sp, #0x0]
	lsl r6, r6, #0x5
	add r6, r5, r6
	ldr r5, =0x00000000
	adc r5, r0
	lsr r0, r6, #0x1b
	lsl r5, r5, #0x5
	orr r5, r0
	lsl r0, r6, #0x5
	add r6, r1, r0
	ldr r1, =0x00000000
	adc r1, r5
	lsr r0, r6, #0x1a
	lsl r1, r1, #0x6
	orr r1, r0
	lsl r0, r6, #0x6
	add r5, r2, r0
	ldr r2, =0x00000000
	adc r2, r1
	lsr r0, r5, #0x1a
	lsl r1, r2, #0x6
	orr r1, r0
	lsl r0, r5, #0x6
	add r2, r3, r0
	ldr r0, =0x00000000
	str r2, [r4, #0x0]
	adc r0, r1
	str r0, [r4, #0x4]
	ldr r1, =0x6C078965
	ldr r0, =0x5D588B65
	str r1, [r4, #0x8]
	str r0, [r4, #0xc]
	ldr r0, =0x00269EC3
	str r0, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	add sp, #0x20
	pop {r3-r7, pc}
    // clang-format on
}
#endif

void sub_02031354(u32 param0)
{
    sub_0202D830(UNK_021C59F8->unk56C, param0);
}

u32 sub_02031370()
{
    return sub_0202D4E4(UNK_021C59F8->unk56C);
}

u32 sub_02031388()
{
    return sub_0202D4E4(UNK_021C59F8->unk54C);
}

void sub_020313A0(u8 param0)
{
    UNK_021C59F8->unk687 = param0;
}

void sub_020313B4(u8 param0, u32 param1)
{
    if (UNK_021C59F8 != NULL)
    {
        UNK_021C59F8->unk677[param1] = param0;
    }
}

u32 sub_020313CC(u32 param0)
{
    if (UNK_021C59F8 != NULL)
    {
        if (UNK_021C59F8->unk677[param0] != 0xff)
        {
            return UNK_021C59F8->unk677[param0];
        }
    }

    return param0;
}

u32 sub_020313EC()
{
    if (sub_02033534() < 0x13)
    {
        return 0;
    }

    return ov04_021D8624();
}

void sub_02031400(u32 param0)
{
    if (sub_02033534() >= 0x13)
    {
        UNK_021C59F8->unk630 = param0;
        if (param0 != 0)
        {
            UNK_021C59F8->unk634 = 0;
            UNK_021C59F8->unk638[0] = 0;
            UNK_021C59F8->unk638[1] = 0;
        }
    }
}

u32 sub_02031438()
{
    if (UNK_021C59F8->unk681 != 0)
    {
        return 1;
    }

    return 0;
}

void sub_02031454()
{
    UNK_021C59F8->unk689 = 1;
}

void sub_02031468()
{
    if (UNK_021C59F8 != NULL)
    {
        UNK_021C59F8->unk68A = 1;
    }
}
