#include "global.h"
#include "SPI_pm.h"
#include "OS_interrupt.h"
#include "OS_system.h"
#include "CARD_backup.h"
#include "CARD_pullOut.h"
#include "CTRDG_common.h"
#include "PAD_pad.h"
#include "main.h"
#include "poke_overlay.h"

extern struct Unk21C48B8 gUnknown21C48B8;

struct Unk2106FA0 gBacklightTop;

extern BOOL FUN_02006234(struct Unk21DBE18 *, s32 *, int);
extern BOOL FUN_02006290(int);
extern void FUN_02006260(int);
extern BOOL FUN_02033678(void);
extern int FUN_020335B8(void);
extern BOOL FUN_0202FB80(void);
extern void FUN_02000FE8(void);
extern void FUN_02016464(void);

void FUN_02000F4C(int arg0, int arg1);
void FUN_02000FE8(void);

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
    OS_WaitIrq(TRUE, OS_IE_V_BLANK);
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
extern void seedr_MT(int);
extern void seedr_LC(int);

void InitializeMainRNG(void)
{
    struct Unk21C4818 spC;
    struct Unk21C4828 sp0;
    FUN_0201265C(&spC, &sp0);
    {
        int r4 = gUnknown21C48B8.unk2C;
        int r5 = ((sp0.unk4 + sp0.unk8) << 24) + (spC.unk0 + ((256 * spC.unk4 * spC.unk8) << 16) + (sp0.unk0 << 16));
        seedr_MT(r4 + r5);
        seedr_LC(r4 + r5);
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
