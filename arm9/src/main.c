#include "global.h"
#include "main.h"

extern struct Unk2106FA0 gBacklightTop;
extern struct Unk2106FA0 gBacklightTop_2; // same as the first one, it's referenced twice in the constant pool...
extern struct Unk21C48B8 gUnknown21C48B8;

extern s32 gUnk027FFC20;
extern struct { 
    s32 unk0;
    s32 unk4;
    u8 unk8;
} gUnk021C4918;

extern void PM_GetBackLight();
extern void OS_WaitIrq();
extern void FUN_02016438(s32);

extern const s32 CONST_3F; // 0x0000003F
extern const s32 CONST_34; // 0x00000034

extern struct Unk21DBE18 gUnk021DBE18; 
extern struct Unk21DBE18 gUnk021D76C8;


THUMB_FUNC void NitroMain(void)
{
    InitSystemForTheGame();
    InitGraphicMemory();
    FUN_020163BC();
    FUN_02016438(0);

    PM_GetBackLight(&gBacklightTop_2, 0); 

    FUN_02022294();
    FUN_0201259C();
    FUN_02000DF4();
    FUN_02002C14();
    FUN_02002C50(0, 3);
    FUN_02002C50(1, 3);
    FUN_02002C50(3, 3);
    gBacklightTop.unk18 = -1;
    gBacklightTop.unk20 = FUN_0202254C();
    FUN_02003B98(FUN_02029EF8(gBacklightTop.unk20), LoadPlayerDataAddress(gBacklightTop.unk20));
    FUN_02020AFC();
    if (FUN_020337E8(3) == 3)
        FUN_02034188(3, 0);
    if (FUN_020227FC(gBacklightTop.unk20) == 0)
    {
        FUN_02089D90(0);
    }
    else
    {
        switch (gUnk027FFC20)
        {
        case 0:
            gBacklightTop.unk1C = 0;
            FUN_02000E7C(&CONST_3F, &gUnk021DBE18);
            break;
        case 1:
            gBacklightTop.unk1C = 1;
            FUN_02000E7C(&CONST_34, &gUnk021D76C8);
            break;
        default:
            ErrorHandling();
            break;
        }
    }
    gUnknown21C48B8.unk6C = 1;
    gUnknown21C48B8.unk30 = 0;
    FUN_02000FA4();
    FUN_0200A2AC();
    FUN_02015E30();
    gBacklightTop.unk4 = 0;
    for (;;)
    {
        FUN_02000EE8();
        FUN_02000FE8();
        FUN_02016464();
        if ((gUnknown21C48B8.unk38 & 0x30C) == 0x30C && !gUnk021C4918.unk8) // soft reset?
        {
            FUN_02000F18(0); // soft reset?
        }
        if (FUN_0202FB80())
        {
            FUN_02000E0C();
            FUN_0201B5CC(gUnknown21C48B8.unk18);
            FUN_0201B5CC(gUnknown21C48B8.unk24);
            if (!gUnknown21C48B8.unk30)
            {
                OS_WaitIrq(1, 1);
                gUnknown21C48B8.unk2C++;
            }
        }
        FUN_020125D4();
        FUN_02015E60();
        FUN_020222C4();
        FUN_0201B5CC(gUnknown21C48B8.unk24);
        OS_WaitIrq(1, 1);
        gUnknown21C48B8.unk2C++;
        gUnknown21C48B8.unk30 = 0;
        FUN_0200A318();
        FUN_0200E2D8();
        if (gUnknown21C48B8.unk0)
            gUnknown21C48B8.unk0(gUnknown21C48B8.unk4);
        FUN_02003C10();
        FUN_0201B5CC(gUnknown21C48B8.unk20);
    }
}