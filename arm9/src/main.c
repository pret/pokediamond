#include "global.h"
#include "main.h"
#include "FS_overlay.h"

FS_EXTERN_OVERLAY(MODULE_52);
FS_EXTERN_OVERLAY(MODULE_63);

#define SOFT_RESET_KEY (REG_PAD_KEYINPUT_L_MASK | REG_PAD_KEYINPUT_R_MASK | REG_PAD_KEYINPUT_START_MASK | REG_PAD_KEYINPUT_SEL_MASK)

extern struct Unk2106FA0 gBacklightTop;
extern struct Unk2106FA0 gBacklightTop_2; // same as the first one, it's referenced twice in the constant pool...
extern struct Unk21C48B8 gUnknown21C48B8;

extern struct { 
    s32 unk0;
    s32 unk4;
    u8 unk8;
} gUnk021C4918;

extern void PM_GetBackLight();
extern void OS_WaitIrq();
extern void FUN_02016438(s32);
extern void InitSystemForTheGame(void);
extern void InitGraphicMemory(void);
extern void FUN_020163BC(void);
extern void FUN_02022294(void);
extern void FUN_0201259C(void);
extern void FUN_02000DF4(void);
extern void FUN_02002C14(void);
extern void FUN_02002C50(int, int);
extern int FUN_0202254C(void);
extern void FUN_02003B98(int, int);
extern int FUN_02029EF8(int);
extern int LoadPlayerDataAddress(int);
extern void FUN_02020AFC(void);
extern int FUN_020337E8(int);
extern void FUN_02034188(int, int);
extern int FUN_020227FC(int);
extern void FUN_02089D90(int);
extern void FUN_02000E7C(int, struct Unk21DBE18 *);
extern void ErrorHandling(void);
extern void FUN_02000FA4(void);
extern void FUN_0200A2AC(void);
extern void FUN_02015E30(void);
extern void FUN_02000EE8(void);
extern void FUN_02000FE8(void);
extern void FUN_02016464(void);
extern void FUN_02000F18(int);
extern BOOL FUN_0202FB80(void);
extern void FUN_02000E0C(void);
extern void FUN_0201B5CC(int);
extern void FUN_020125D4(void);
extern void FUN_02015E60(void);
extern void FUN_020222C4(void);
extern void FUN_0200A318(void);
extern void FUN_0200E2D8(void);
extern void FUN_02003C10(void);

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
        switch (*((s32 *)HW_RESET_PARAMETER_BUF))
        {
        case 0:
            gBacklightTop.unk1C = 0;
            FUN_02000E7C(FS_OVERLAY_ID(MODULE_63), &gUnk021DBE18);
            break;
        case 1:
            gBacklightTop.unk1C = 1;
            FUN_02000E7C(FS_OVERLAY_ID(MODULE_52), &gUnk021D76C8);
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
        if ((gUnknown21C48B8.unk38 & SOFT_RESET_KEY) == SOFT_RESET_KEY && !gUnk021C4918.unk8) // soft reset?
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