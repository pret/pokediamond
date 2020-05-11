#include "global.h"
#include "main.h"
#include "PAD_pad.h"
#include "CARD_pullOut.h"
#include "CARD_backup.h"
#include "CTRDG_common.h"
#include "poke_overlay.h"

FS_EXTERN_OVERLAY(MODULE_52);
FS_EXTERN_OVERLAY(MODULE_63);

#define SOFT_RESET_KEY (PAD_BUTTON_L | PAD_BUTTON_R | PAD_BUTTON_START | PAD_BUTTON_SELECT)

extern struct Unk21C48B8 gUnknown21C48B8;

extern struct { 
    s32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
} gUnk021C4918;

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
extern void FUN_02000E7C(FSOverlayID, struct Unk21DBE18 *);
extern void ErrorHandling(void);
extern void FUN_02000FA4(void);
extern void FUN_0200A2AC(void);
extern void FUN_02015E30(void);
extern void FUN_02000EE8(void);
extern void FUN_02000FE8(void);
extern void FUN_02016464(void);
void DoSoftReset(u32 parameter);
extern BOOL FUN_0202FB80(void);
extern void FUN_02000E0C(void);
extern void FUN_0201B5CC(int);
extern void FUN_020125D4(void);
extern void FUN_02015E60(void);
extern void FUN_020222C4(void);
extern void FUN_0200A318(void);
extern void FUN_0200E2D8(void);
extern void FUN_02003C10(void);
void FUN_02000F4C(int arg0, int arg1);
extern BOOL FUN_02006234(struct Unk21DBE18 *, s32 *, int);
extern BOOL FUN_02006290(int);
extern void FUN_02006260(int);
extern BOOL FUN_02033678(void);
extern int FUN_020335B8(void);

extern struct Unk21DBE18 gUnk021DBE18; 
extern struct Unk21DBE18 gUnk021D76C8;


THUMB_FUNC void NitroMain(void)
{
    InitSystemForTheGame();
    InitGraphicMemory();
    FUN_020163BC();
    FUN_02016438(0);

    PM_GetBackLight(&gBacklightTop_2.unk0, NULL);

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
            DoSoftReset(0); // soft reset?
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

THUMB_FUNC void FUN_02000DF4(void)
{
    gBacklightTop.unk8 = -1;
    gBacklightTop.unkC = 0;
    gBacklightTop.unk10 = -1; // overlay invalid
    gBacklightTop.unk14 = NULL;
}

THUMB_FUNC void FUN_02000E0C(void)
{
    if (!gBacklightTop.unkC)
    {
        if (gBacklightTop.unk14 == NULL)
            return;
        if (gBacklightTop.unk10 != -1u)
            HandleLoadOverlay(gBacklightTop.unk10, 0);
        gBacklightTop.unk8 = gBacklightTop.unk10;
        gBacklightTop.unkC = FUN_02006234(gBacklightTop.unk14, &gBacklightTop.unk18, 0);
        gBacklightTop.unk10 = -1u;
        gBacklightTop.unk14 = NULL;
    }
    if (FUN_02006290(gBacklightTop.unkC))
    {
        FUN_02006260(gBacklightTop.unkC);
        gBacklightTop.unkC = 0;
        if (gBacklightTop.unk8 != -1u)
            UnloadOverlayByID(gBacklightTop.unk8);
    }
}

THUMB_FUNC void FUN_02000E7C(FSOverlayID id, struct Unk21DBE18 * arg1)
{
    if (gBacklightTop.unk14 != NULL)
        ErrorHandling();
    gBacklightTop.unk10 = id;
    gBacklightTop.unk14 = arg1;
}

THUMB_FUNC void FUN_02000E9C(void)
{
    FUN_0202FB80();
    OS_WaitIrq(1, 1);
    gUnknown21C48B8.unk2C++;
    gUnknown21C48B8.unk30 = 0;
    if (gUnknown21C48B8.unk0 != NULL)
        gUnknown21C48B8.unk0(gUnknown21C48B8.unk4);
}

THUMB_FUNC void FUN_02000EC8(u32 parameter)
{
    if (FUN_02033678() && CARD_TryWaitBackupAsync() == TRUE)
    {
        OS_ResetSystem(parameter);
    }
    FUN_02000E9C();
}

THUMB_FUNC void FUN_02000EE8(void)
{
    int r1 = FUN_020335B8();
    switch (r1)
    {
    case 1:
        FUN_02000F4C(1, r1);
        break;
    case 2:
        FUN_02000F4C(0, r1);
        break;
    case 3:
        FUN_02000F4C(1, r1);
        break;
    }
}

extern void FUN_0200E3A0(int, int);
extern BOOL FUN_02032DAC(void);
extern void FUN_020225F8(void);
extern void FUN_0202287C(void);

// No Return
THUMB_FUNC void DoSoftReset(u32 parameter)
{
    FUN_0200E3A0(0, 0x7FFF);
    FUN_0200E3A0(1, 0x7FFF);
    if (FUN_02032DAC())
    {
        FUN_020225F8();
        FUN_0202287C();
    }
    do
    {
        FUN_02000FE8();
        FUN_02000EC8(parameter);
    } while (1);
}

extern void FUN_02033F70(int, int, int);

THUMB_FUNC void FUN_02000F4C(int arg0, int arg1)
{
    if (arg1 == 3)
    {
        FUN_02033F70(0, 3, 0);
    }
    else if (arg0 == 0)
    {
        FUN_02033F70(0, 2, 0);
    }
    else
    {
        FUN_02033F70(0, 0, 0);
    }
    FUN_02032DAC();
    while (1)
    {
        FUN_02000FE8();
        FUN_02016464();
        if (gUnknown21C48B8.unk48 & 1)
            break;
        FUN_02000E9C();
    }
    DoSoftReset(arg0);
}

extern void FUN_0201265C(struct Unk21C4818 *, struct Unk21C4828 *);
extern void FUN_0201BA1C(int);
extern void FUN_0201B9E0(int);

void FUN_02000FA4(void)
{
    struct Unk21C4818 spC;
    struct Unk21C4828 sp0;
    FUN_0201265C(&spC, &sp0);
    {
        int r4 = gUnknown21C48B8.unk2C;
        int r5 = ((sp0.unk4 + sp0.unk8) << 24) + (spC.unk0 + ((256 * spC.unk4 * spC.unk8) << 16) + (sp0.unk0 << 16));
        FUN_0201BA1C(r4 + r5);
        FUN_0201B9E0(r4 + r5);
    }
}

extern void FUN_0201CE04(void);
extern void FUN_0201CDD0(void);

void FUN_02000FE8(void)
{
    PMBackLightSwitch top, bottom;
    if (PAD_DetectFold())
    {
        if (!gUnk021C4918.unk7)
        {
            FUN_0201CE04();
            if (CTRDG_IsPulledOut() == TRUE)
            {
                gBacklightTop.unk4 = 1;
            }
            {
                int r1 = gBacklightTop.unk4;
                while (1)
                {
                    PMWakeUpTrigger trigger = PM_TRIGGER_COVER_OPEN | PM_TRIGGER_CARD;
                    if (gUnk021C4918.unk6 && !r1)
                        trigger |= PM_TRIGGER_CARTRIDGE;
                    PM_GoSleepMode(trigger, PM_PAD_LOGIC_OR, 0);
                    if (CARD_IsPulledOut())
                    {
                        PM_ForceToPowerOff();
                        break;
                    }
                    else if (PAD_DetectFold())
                    {
                        r1 = gBacklightTop.unk4 = 1;
                    }
                    else
                        break;
                }
                FUN_0201CDD0();
                return;
            }
        }
        else
        {
            PM_GetBackLight(&top, &bottom);
            if (top == PM_BACKLIGHT_ON)
                PM_SetBackLight(PM_LCD_ALL, PM_BACKLIGHT_OFF);
        }
    }
    else
    {
        PM_GetBackLight(&top, &bottom);
        if (top == PM_BACKLIGHT_OFF)
            PM_SetBackLight(PM_LCD_ALL, gBacklightTop.unk0);
    }
}
