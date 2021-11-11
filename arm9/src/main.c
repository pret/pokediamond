#define IN_MAIN_C

#include "global.h"
#include "SPI_pm.h"
#include "CARD_backup.h"
#include "CARD_pullOut.h"
#include "CTRDG_common.h"
#include "communication_error.h"
#include "PAD_pad.h"
#include "main.h"
#include "game_init.h"
#include "poke_overlay.h"
#include "player_data.h"
#include "save_data_read_error.h"
#include "sound.h"
#include "timer3.h"
#include "unk_02031734.h"
#include "unk_0202F150.h"
#include "wfc_user_info_warning.h"
#include "module_52.h"
#include "font.h"
#include "brightness.h"

FS_EXTERN_OVERLAY(MODULE_52);
FS_EXTERN_OVERLAY(MODULE_63);

#define SOFT_RESET_KEY (PAD_BUTTON_L | PAD_BUTTON_R | PAD_BUTTON_START | PAD_BUTTON_SELECT)

s32 UNK_02016FA4;
PMBackLightSwitch gBacklightTop;
struct UnkStruct_02016FA8 UNK_02016FA8;

extern void FUN_02022294(void);
extern void GF_InitRTCWork(void);
extern int FUN_020337E8(int);
extern void PlayTimerInit(void);
extern void FUN_0201B5CC(void *);
extern void GF_RTC_UpdateOnFrame(void);
extern void PlayTimerUpdate(void);
extern void FUN_020222C4(void);
extern void FUN_0200E2D8(void);

extern struct Unk21DBE18 MOD63_021DBE18;

extern u8 SDK_STATIC_BSS_START[];

const int gGameLanguage = GAME_LANGUAGE;
const int gGameVersion = GAME_VERSION;

__declspec(noreturn)
THUMB_FUNC void NitroMain(void)
{
    InitSystemForTheGame();
    InitGraphicMemory();
    InitKeypadAndTouchpad();
    FUN_02016438(0);

    PM_GetBackLight(&gBacklightTop, NULL);

    FUN_02022294();
    GF_InitRTCWork();
    FUN_02000DF4();
    FUN_02002C14();
    FUN_02002C50(0, 3);
    FUN_02002C50(1, 3);
    FUN_02002C50(3, 3);
    UNK_02016FA8.unk10 = -1;
    UNK_02016FA8.unk18 = SaveBlock2_new();
    InitSoundData(Sav2_Chatot_get(UNK_02016FA8.unk18), Sav2_PlayerData_GetOptionsAddr(UNK_02016FA8.unk18));
    Init_Timer3();
    if (FUN_020337E8(3) == 3)
        ShowWFCUserInfoWarning(3, 0);
    if (FUN_020227FC(UNK_02016FA8.unk18) == 0)
    {
        ShowSaveDataReadError(0);
    }
    else
    {
        switch (OS_GetResetParameter())
        {
        case 0:
            // Title Demo
            UNK_02016FA8.unk14 = 0;
            RegisterMainOverlay(FS_OVERLAY_ID(MODULE_63), &MOD63_021DBE18);
            break;
        case 1:
            // Reset transition?
            UNK_02016FA8.unk14 = 1;
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
    InitAllScreenBrightnessData();
    PlayTimerInit();
    UNK_02016FA4 = 0;
    for (;;)
    {
        FUN_02000EE8();
        HandleDSLidAction();
        ReadKeypadAndTocuhpad();
        if ((gMain.heldKeysRaw & SOFT_RESET_KEY) == SOFT_RESET_KEY && !gMain.softResetDisabled) // soft reset?
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
        PlayTimerUpdate();
        FUN_020222C4();
        FUN_0201B5CC(gMain.unk24);
        OS_WaitIrq(1, 1);
        gMain.unk2C++;
        gMain.unk30 = 0;
        DoAllScreenBrightnessTransitionStep();
        FUN_0200E2D8();
        if (gMain.vBlankIntr)
            gMain.vBlankIntr(gMain.vBlankIntrArg);
        DoSoundUpdateFrame();
        FUN_0201B5CC(gMain.unk20);
    }
}

THUMB_FUNC void FUN_02000DF4(void)
{
    UNK_02016FA8.unk0 = SDK_OVERLAY_INVALID_ID;
    UNK_02016FA8.unk4 = NULL;
    UNK_02016FA8.unk8 = SDK_OVERLAY_INVALID_ID; // overlay invalid
    UNK_02016FA8.unkC = NULL;
}

THUMB_FUNC void Main_RunOverlayManager(void)
{
    if (UNK_02016FA8.unk4 == NULL)
    {
        if (UNK_02016FA8.unkC == NULL)
            return;
        if (UNK_02016FA8.unk8 != SDK_OVERLAY_INVALID_ID)
            HandleLoadOverlay(UNK_02016FA8.unk8, 0);
        UNK_02016FA8.unk0 = UNK_02016FA8.unk8;
        UNK_02016FA8.unk4 = OverlayManager_new(UNK_02016FA8.unkC, &UNK_02016FA8.unk10, 0);
        UNK_02016FA8.unk8 = SDK_OVERLAY_INVALID_ID;
        UNK_02016FA8.unkC = NULL;
    }
    if (OverlayManager_Run(UNK_02016FA8.unk4))
    {
        OverlayManager_delete(UNK_02016FA8.unk4);
        UNK_02016FA8.unk4 = NULL;
        if (UNK_02016FA8.unk0 != SDK_OVERLAY_INVALID_ID)
            UnloadOverlayByID(UNK_02016FA8.unk0);
    }
}

THUMB_FUNC void RegisterMainOverlay(FSOverlayID id, const struct Unk21DBE18 * arg1)
{
    GF_ASSERT(UNK_02016FA8.unkC == NULL);
    UNK_02016FA8.unk8 = id;
    UNK_02016FA8.unkC = arg1;
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

__declspec(noreturn)
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

THUMB_FUNC void FUN_02000F4C(u32 arg0, u32 arg1)
{
    if (arg1 == 3)
    {
        ShowCommunicationError(0, 3, 0);
    }
    else if (arg0 == 0)
    {
        ShowCommunicationError(0, 2, 0);
    }
    else
    {
        ShowCommunicationError(0, 0, 0);
    }
    FUN_02032DAC();
    while (1)
    {
        HandleDSLidAction();
        ReadKeypadAndTocuhpad();
        if (gMain.newKeys & 1)
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
                UNK_02016FA4 = 1;
            }
            {
                int r1 = UNK_02016FA4;
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
                        r1 = UNK_02016FA4 = 1;
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
            PM_SetBackLight(PM_LCD_ALL, gBacklightTop);
    }
}
