#define IN_MAIN_C

#include "global.h"
#include "SPI_pm.h"
#include "CARD_backup.h"
#include "CARD_pullOut.h"
#include "CTRDG_common.h"
#include "PAD_pad.h"
#include "main.h"
#include "game_init.h"
#include "poke_overlay.h"
#include "player_data.h"
#include "sound.h"
#include "timer3.h"

FS_EXTERN_OVERLAY(MODULE_52);
FS_EXTERN_OVERLAY(MODULE_63);

#define SOFT_RESET_KEY (PAD_BUTTON_L | PAD_BUTTON_R | PAD_BUTTON_START | PAD_BUTTON_SELECT)

struct Unk2106FA0 gBacklightTop;

extern BOOL OverlayManager_new(struct Unk21DBE18 *, s32 *, int);
extern BOOL OverlayManager_Run(int);
extern void OverlayManager_delete(int);
extern BOOL FUN_02033678(void);
extern u32 FUN_020335B8(void);
extern BOOL FUN_0202FB80(void);

extern void InitSystemForTheGame(void);
extern void InitGraphicMemory(void);
extern void FUN_02022294(void);
extern void GF_InitRTCWork(void);
extern void FUN_02002C14(void);
extern void FUN_02002C50(int, int);
extern struct SaveBlock2 * SaveBlock2_new(void);
extern void * FUN_02029EF8(struct SaveBlock2 *);
extern int FUN_020337E8(int);
extern void FUN_02034188(int, int);
extern int FUN_020227FC(struct SaveBlock2 *);
extern void FUN_02089D90(int);
extern void FUN_0200A2AC(void);
extern void FUN_02015E30(void);
extern void FUN_0201B5CC(void *);
extern void GF_RTC_UpdateOnFrame(void);
extern void FUN_02015E60(void);
extern void FUN_020222C4(void);
extern void FUN_0200A318(void);
extern void FUN_0200E2D8(void);

extern struct Unk21DBE18 MOD63_021DBE18;
extern struct Unk21DBE18 MOD52_021D76C8;

extern u8 SDK_STATIC_BSS_START[];

const int gGameVersion = GAME_VERSION;
const int gGameLanguage = GAME_LANGUAGE;

THUMB_FUNC void NitroMain(void)
{
    InitSystemForTheGame();
    InitGraphicMemory();
    FUN_020163BC();
    FUN_02016438(0);

    PM_GetBackLight((PMBackLightSwitch *)SDK_STATIC_BSS_START, NULL);

    FUN_02022294();
    GF_InitRTCWork();
    FUN_02000DF4();
    FUN_02002C14();
    FUN_02002C50(0, 3);
    FUN_02002C50(1, 3);
    FUN_02002C50(3, 3);
    gBacklightTop.unk18 = -1;
    gBacklightTop.unk20 = SaveBlock2_new();
    InitSoundData(FUN_02029EF8(gBacklightTop.unk20), Sav2_PlayerData_GetOptionsAddr(gBacklightTop.unk20));
    Init_Timer3();
    if (FUN_020337E8(3) == 3)
        FUN_02034188(3, 0);
    if (FUN_020227FC(gBacklightTop.unk20) == 0)
    {
        FUN_02089D90(0);
    }
    else
    {
        switch (OS_GetResetParameter())
        {
        case 0:
            // Title Demo
            gBacklightTop.unk1C = 0;
            RegisterMainOverlay(FS_OVERLAY_ID(MODULE_63), &MOD63_021DBE18);
            break;
        case 1:
            // Reset transition?
            gBacklightTop.unk1C = 1;
            RegisterMainOverlay(FS_OVERLAY_ID(MODULE_52), &MOD52_021D76C8);
            break;
        default:
            GF_ASSERT(0);
            break;
        }
    }
    gMain.unk6C = 1;
    gMain.unk30 = 0;
    InitializeMainRNG();
    FUN_0200A2AC();
    FUN_02015E30();
    gBacklightTop.unk4 = 0;
    for (;;)
    {
        FUN_02000EE8();
        HandleDSLidAction();
        FUN_02016464();
        if ((gMain.unk38 & SOFT_RESET_KEY) == SOFT_RESET_KEY && !gMain.unk68) // soft reset?
        {
            DoSoftReset(0); // soft reset?
        }
        if (FUN_0202FB80())
        {
            Main_RunOverlayManager();
            FUN_0201B5CC(gMain.unk18);
            FUN_0201B5CC(gMain.unk24);
            if (!gMain.unk30)
            {
                OS_WaitIrq(1, 1);
                gMain.unk2C++;
            }
        }
        GF_RTC_UpdateOnFrame();
        FUN_02015E60();
        FUN_020222C4();
        FUN_0201B5CC(gMain.unk24);
        OS_WaitIrq(1, 1);
        gMain.unk2C++;
        gMain.unk30 = 0;
        FUN_0200A318();
        FUN_0200E2D8();
        if (gMain.vBlankIntr)
            gMain.vBlankIntr(gMain.vBlankIntrArg);
        DoSoundUpdateFrame();
        FUN_0201B5CC(gMain.unk20);
    }
}

THUMB_FUNC void FUN_02000DF4(void)
{
    gBacklightTop.unk8 = (FSOverlayID)-1;
    gBacklightTop.unkC = 0;
    gBacklightTop.unk10 = (FSOverlayID)-1; // overlay invalid
    gBacklightTop.unk14 = NULL;
}

THUMB_FUNC void Main_RunOverlayManager(void)
{
    if (!gBacklightTop.unkC)
    {
        if (gBacklightTop.unk14 == NULL)
            return;
        if (gBacklightTop.unk10 != SDK_OVERLAY_INVALID_ID)
            HandleLoadOverlay(gBacklightTop.unk10, 0);
        gBacklightTop.unk8 = gBacklightTop.unk10;
        gBacklightTop.unkC = OverlayManager_new(gBacklightTop.unk14, &gBacklightTop.unk18, 0);
        gBacklightTop.unk10 = SDK_OVERLAY_INVALID_ID;
        gBacklightTop.unk14 = NULL;
    }
    if (OverlayManager_Run(gBacklightTop.unkC))
    {
        OverlayManager_delete(gBacklightTop.unkC);
        gBacklightTop.unkC = 0;
        if (gBacklightTop.unk8 != SDK_OVERLAY_INVALID_ID)
            UnloadOverlayByID(gBacklightTop.unk8);
    }
}

THUMB_FUNC void RegisterMainOverlay(FSOverlayID id, struct Unk21DBE18 * arg1)
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
    gMain.unk2C++;
    gMain.unk30 = 0;
    if (gMain.vBlankIntr != NULL)
        gMain.vBlankIntr(gMain.vBlankIntrArg);
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
    u32 r1 = FUN_020335B8();
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

extern void FUN_0200E3A0(PMLCDTarget, int);
extern BOOL FUN_02032DAC(void);

// No Return
THUMB_FUNC void DoSoftReset(u32 parameter)
{
    FUN_0200E3A0(PM_LCD_TOP, 0x7FFF);
    FUN_0200E3A0(PM_LCD_BOTTOM, 0x7FFF);
    if (FUN_02032DAC())
    {
        FUN_0202287C(FUN_020225F8());
    }
    do
    {
        HandleDSLidAction();
        FUN_02000EC8(parameter);
    } while (1);
}

extern void FUN_02033F70(int, int, int);

THUMB_FUNC void FUN_02000F4C(u32 arg0, u32 arg1)
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
        HandleDSLidAction();
        FUN_02016464();
        if (gMain.unk48 & 1)
            break;
        FUN_02000E9C();
    }
    DoSoftReset(arg0);
}

extern void GF_RTC_CopyDateTime(struct Unk21C4818 *, struct Unk21C4828 *);
extern void SetMTRNGSeed(u32);
extern void SetLCRNGSeed(u32);

THUMB_FUNC void InitializeMainRNG(void)
{
    struct Unk21C4818 spC;
    struct Unk21C4828 sp0;
    GF_RTC_CopyDateTime(&spC, &sp0);
    {
        u32 r4 = gMain.unk2C;
        u32 r5 = ((sp0.unk4 + sp0.unk8) << 24) + (spC.unk0 + ((256 * spC.unk4 * spC.unk8) << 16) + (sp0.unk0 << 16));
        SetMTRNGSeed(r4 + r5);
        SetLCRNGSeed(r4 + r5);
    }
}

extern void FUN_0201CE04(void);
extern void FUN_0201CDD0(void);

THUMB_FUNC void HandleDSLidAction(void)
{
    PMBackLightSwitch top, bottom;
    if (PAD_DetectFold())
    {
        if (!gMain.unk67)
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
                    if (gMain.unk66 && !r1)
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
