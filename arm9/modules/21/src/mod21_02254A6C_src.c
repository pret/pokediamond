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
