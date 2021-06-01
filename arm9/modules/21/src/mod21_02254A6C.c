#include "global.h"
#include "heap.h"
#include "mod21_02254A6C.h"
#include "MI_memory.h"

extern void MOD20_022536F4(u32 *param0, u32 param1);
extern u32 MOD20_02252D34(void);
extern void *GfGfxLoader_GetScrnData(u32 param0, u32 param1, u32 param2, void *param3, u32 param4);
extern void MOD20_022537E0(void *param0, u32 param1, void *param2, u32 param3, void *param4, u32 param5, u32 param6);

UnkOverlayStruct1 const MOD21_02254DAC[] = {
        { 0, MOD21_02254B60, 0 },
        { 1, MOD21_02254BF4, 0 },
        { 2, MOD21_02254C14, 0 },
        { 3, MOD21_02254C40, 0 },
        { 0, NULL, 0 }
};

extern BOOL MOD20_02253794(void *param0, u32 param1);
extern BOOL MOD20_022537B8(void *param0);
extern UnkStruct02254A6C *MOD20_022538A0(void *param0);
extern BOOL MOD20_02253888(void *param0, void *param1);

//todo datatype
u8 const MOD21_02254D90[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

extern void FUN_02016C18(u32 param0, u32 param1, void *param2, u32 param3);
extern void GfGfxLoader_LoadCharData(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
extern void GfGfxLoader_LoadScrnData(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
extern void MOD20_02252D7C(u32 param0, u32 param1);
extern void FUN_02017CD0(u32 param0, u32 param1);
extern void FUN_020178A0(u32 param0, u32 param1);

extern void FUN_02018170(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 *param6, u8 param7, u32 param8, u32 param9, u32 param10);

extern void MOD11_02252DB4(u32 param0, u32 param1);

THUMB_FUNC BOOL MOD21_02254A6C(UnkStruct02254A6C *param0, void *param1)
{
    UnkStruct02254A6C *strct = (UnkStruct02254A6C *)AllocFromHeap(8, 3 << 8);
    u32 sp4;
    if (strct != NULL)
    {
        MOD20_022536F4(strct->Unk08, 8);
        strct->Unk00 = param1;
        strct->Unk04 = MOD20_02252D34();
        void *res = GfGfxLoader_GetScrnData(12, 0x19, 1, &sp4, 8);
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
    UnkStruct02254A6C *strct = MOD20_022538A0(param1);
    FUN_02016C18(strct->Unk04, 6, MOD21_02254D90, 0);
    GfGfxLoader_LoadCharData(12, 23, strct->Unk04, 6, 0, 0, 1, 8);
    GfGfxLoader_LoadScrnData(12, 24, strct->Unk04, 6, 0, 0, 1, 8);
    MOD20_02252D7C(0, 0);
    MOD21_02254C5C(strct);
    FUN_02017CD0(strct->Unk04, 6);
    u32 r3 = reg_GXS_DB_DISPCNT;
    u32 r2 = reg_GXS_DB_DISPCNT;
    vu32 tmp = r3; //unused? wtf
    u32 r0 = ~0x1F00 & r2;
    r2 = r3 << 19; //cast with shift? can't replicate both though
    r3 = r2 >> 27;
    r2 = 4 | r3;
    r2 <<= 8;
    r0 |= r2;
    reg_GXS_DB_DISPCNT = r0;
    return MOD21_02254B4C(param1);
}

THUMB_FUNC BOOL MOD21_02254BF4(u32 param0, void *param1)
{
#pragma unused (param0)
    UnkStruct02254A6C *strct = MOD20_022538A0(param1);
    MOD21_02254C5C(strct);
    FUN_02017CD0(strct->Unk04, 6);
    return MOD21_02254B4C(param1);
}

THUMB_FUNC BOOL MOD21_02254C14(u32 param0, void *param1)
{
#pragma unused (param0)
    UnkStruct02254A6C *strct = MOD20_022538A0(param1);
    if (strct->Unk00->Unk0C)
    {
        MOD11_02252DB4(0, 0);
    }
    else
    {
        MOD20_02252D7C(0, 0);
    }
    return MOD21_02254B4C(param1);
}

THUMB_FUNC BOOL MOD21_02254C40(u32 param0, void *param1)
{
#pragma unused (param0)
    UnkStruct02254A6C *strct = MOD20_022538A0(param1);
    FUN_020178A0(strct->Unk04, 6);
    return MOD21_02254B4C(param1);
}

THUMB_FUNC void MOD21_02254C5C(UnkStruct02254A6C *param0)
{
    u32 tmp = (u32)param0->Unk00->Unk00;
    reg_CP_DIVCNT = 0;
    (*(vu32 *)REG_DIV_NUMER_ADDR) = tmp;
    reg_CP_DIV_DENOM = 10;
    while (reg_CP_DIVCNT & ((u32)&reg_CP_DIVCNT >> 0xb)) { }

    u32 regaddr = (u32)&reg_CP_DIV_RESULT_L;
    u32 divResult = *(u32 *)regaddr;
    while (reg_CP_DIVCNT & (regaddr >> 0xb)) { }

    u32 divRemRes = reg_CP_DIVREM_RESULT_L;
    FUN_02018170(param0->Unk04, 6, 3, 7, 4, 9, param0->Unk30, (u8)(divResult << 2), 0, 40, 9);
    FUN_02018170(param0->Unk04, 6, 8, 7, 4, 9, param0->Unk30, (u8)(divRemRes << 2), 0, 40, 9);

    tmp = param0->Unk00->Unk04;
    reg_CP_DIVCNT = 0;
    (*(vu32 *)REG_DIV_NUMER_ADDR) = tmp;
    reg_CP_DIV_DENOM = 10;

    while (reg_CP_DIVCNT & ((u32)&reg_CP_DIVCNT >> 0xb)) { }

    divResult = *(u32 *)regaddr;
    while (reg_CP_DIVCNT & (regaddr >> 0xb)) { }

    divRemRes = reg_CP_DIVREM_RESULT_L;
    FUN_02018170(param0->Unk04, 6, 15, 7, 4, 9, param0->Unk30, (u8)(divResult << 2), 0, 40, 9);
    FUN_02018170(param0->Unk04, 6, 20, 7, 4, 9, param0->Unk30, (u8)(divRemRes << 2), 0, 40, 9);
}
