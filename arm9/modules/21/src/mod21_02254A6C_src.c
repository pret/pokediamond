#include "global.h"
#include "heap.h"
#include "mod21_02254A6C.h"
#include "MI_memory.h"

extern void MOD20_022536F4(u32 *param0, u32 param1);
extern u32 MOD20_02252D34(void);
extern void *FUN_02006BDC(u32 param0, u32 param1, u32 param2, void *param3, u32 param4);
extern void MOD20_022537E0(void *param0, u32 param1, void *param2, u32 param3, void *param4, u32 param5, u32 param6);
extern void MOD21_02254DAC(void);
extern BOOL MOD20_02253794(void *param0, u32 param1);
extern BOOL MOD20_022537B8(void *param0);
extern UnkStruct02254B60 *MOD20_022538A0(void *param0);
extern BOOL MOD20_02253888(void *param0, void *param1);

extern void MOD21_02254D90(void);

extern void FUN_02016C18(u32 param0, u32 param1, void *param2, u32 param3);
extern void FUN_0200687C(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
extern void FUN_020068C8(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
extern void MOD20_02252D7C(u32 param0, u32 param1);
extern void MOD21_02254C5C(UnkStruct02254B60 *param0);
extern void FUN_02017CD0(u32 param0, u32 param1);

THUMB_FUNC BOOL MOD21_02254A6C(UnkStruct02254A6C *param0, void *param1)
{
    UnkStruct02254A6C *strct = (UnkStruct02254A6C *)AllocFromHeap(8, 3 << 8);
    u32 sp4;
    if (strct != NULL)
    {
        MOD20_022536F4(strct->Unk08, 8);
        strct->Unk00 = param1;
        strct->Unk04 = MOD20_02252D34();
        void *res = FUN_02006BDC(12, 0x19, 1, &sp4, 8);
        if (res == 0)
        {
            FreeToHeap(strct);
            return FALSE;
        }
        MOD21_02254AD4((void *)(sp4 + 0xc), strct->Unk30);
        FreeToHeap(res);
        param0->Unk00 = strct;
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC void MOD21_02254AD4(void *param0, void *param1)
{
    s32 i = 0;
    for (u32 r6 = 9 << 6; i < 9; r6 -= 0x30)
    {
        MI_CpuCopy16(param0, param1, 0x40);
        MI_CpuCopy16((void *)((u32)param0 + r6), (void *)((u32)param1 + 0x40), 0x10);
        i++;
        param0 = (void *)((u32)param0 + 0x40);
        param1 = (void *)((u32)param1 + 0x50);
    }
}

THUMB_FUNC void MOD21_02254B04(void *param0)
{
    if (param0 != NULL)
    {
        FreeToHeap(param0);
    }
}

THUMB_FUNC void MOD21_02254B10(u32 *param0, u32 param1)
{
    MOD20_022537E0(MOD21_02254DAC, param1, param0, *param0, (void *)(param0 + 2), 2, 8);
}

THUMB_FUNC BOOL MOD21_02254B34(void *param0, u32 param1)
{
    return MOD20_02253794((void *)((u32)param0 + 8), param1);
}

THUMB_FUNC BOOL MOD21_02254B40(void *param0)
{
    return MOD20_022537B8((void *)((u32)param0 + 8));
}

THUMB_FUNC BOOL MOD21_02254B4C(void *param0)
{
    return MOD20_02253888((void *)((u32)MOD20_022538A0(param0) + 8), param0);
}

THUMB_FUNC BOOL MOD21_02254B60(u32 param0, void *param1)
{
#pragma unused (param0)
    UnkStruct02254B60 *strct = MOD20_022538A0(param1);
    FUN_02016C18(strct->Unk04, 6, MOD21_02254D90, 0);
    FUN_0200687C(12, 23, strct->Unk04, 6, 0, 0, 1, 8);
    FUN_020068C8(12, 24, strct->Unk04, 6, 0, 0, 1, 8);
    MOD20_02252D7C(0, 0);
    MOD21_02254C5C(strct);
    FUN_02017CD0(strct->Unk04, 6);
    u32 r3 = reg_GXS_DB_DISPCNT;
    u32 r2 = reg_GXS_DB_DISPCNT;
    vu32 tmp = r3; //unused? wtf
    u32 r0 = ~0x1F00 & r2;
    r2 = r3 << 0x13;
    r3 = r2 >> 0x1b;
    r2 = 4 | r3;
    r2 <<= 8;
    r0 |= r2;
    reg_GXS_DB_DISPCNT = r0;
    return MOD21_02254B4C(param1);
}
