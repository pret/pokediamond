#define IN_MAIN_C

#include "main.h"

#include "global.h"

#include "CARD_backup.h"
#include "CARD_pullOut.h"
#include "CTRDG_common.h"
#include "PAD_pad.h"
#include "SPI_pm.h"
#include "brightness.h"
#include "communication_error.h"
#include "font.h"
#include "game_init.h"
#include "heap.h"
#include "overlay_52.h"
#include "player_data.h"
#include "poke_overlay.h"
#include "save_data_read_error.h"
#include "sound.h"
#include "timer3.h"
#include "unk_0202F150.h"
#include "unk_02031734.h"
#include "wfc_user_info_warning.h"

FS_EXTERN_OVERLAY(OVERLAY_52);
FS_EXTERN_OVERLAY(OVERLAY_63);

#define SOFT_RESET_KEY (PAD_BUTTON_L | PAD_BUTTON_R | PAD_BUTTON_START | PAD_BUTTON_SELECT)

s32 UNK_02016FA4;
PMBackLightSwitch gBacklightTop;
struct UnkStruct_02016FA8 UNK_02016FA8;

extern void sub_02022294(void);
extern void GF_InitRTCWork(void);
extern int sub_020337E8(int);
extern void PlayTimerInit(void);
extern void sub_0201B5CC(void *);
extern void GF_RTC_UpdateOnFrame(void);
extern void PlayTimerUpdate(void);
extern void sub_020222C4(void);
extern void sub_0200E2D8(void);

extern struct OverlayManagerTemplate ov63_021DBE18;

extern u8 SDK_STATIC_BSS_START[];

const int gGameLanguage = GAME_LANGUAGE;
const int gGameVersion = GAME_VERSION;

__declspec(noreturn) void NitroMain(void) {
    InitSystemForTheGame();
    InitGraphicMemory();
    InitKeypadAndTouchpad();
    sub_02016438(0);

    PM_GetBackLight(&gBacklightTop, NULL);

    sub_02022294();
    GF_InitRTCWork();
    sub_02000DF4();
    sub_02002C14();
    sub_02002C50(0, HEAP_ID_MAIN);
    sub_02002C50(1, HEAP_ID_MAIN);
    sub_02002C50(3, HEAP_ID_MAIN);
    UNK_02016FA8.unk10 = -1;
    UNK_02016FA8.save = SaveData_New();
    InitSoundData(Save_Chatot_Get(UNK_02016FA8.save), Save_PlayerData_GetOptionsAddr(UNK_02016FA8.save));
    Init_Timer3();
    if (sub_020337E8(3) == 3) {
        ShowWFCUserInfoWarning(HEAP_ID_MAIN, 0);
    }
    if (sub_020227FC(UNK_02016FA8.save) == 0) {
        ShowSaveDataReadError(HEAP_ID_DEFAULT);
    } else {
        switch (OS_GetResetParameter()) {
        case 0:
            // Title Demo
            UNK_02016FA8.unk14 = 0;
            RegisterMainOverlay(FS_OVERLAY_ID(OVERLAY_63), &ov63_021DBE18);
            break;
        case 1:
            // Reset transition?
            UNK_02016FA8.unk14 = 1;
            RegisterMainOverlay(FS_OVERLAY_ID(OVERLAY_52), &ov52_021D76C8);
            break;
        default:
            GF_ASSERT(0);
            break;
        }
    }
    gSystem.unk6C = 1;
    gSystem.unk30 = 0;
    InitializeMainRNG();
    ScreenBrightnessData_InitAll();
    PlayTimerInit();
    UNK_02016FA4 = 0;
    for (;;) {
        sub_02000EE8();
        HandleDSLidAction();
        ReadKeypadAndTocuhpad();
        if ((gSystem.heldKeysRaw & SOFT_RESET_KEY) == SOFT_RESET_KEY && !gSystem.softResetDisabled) // soft reset?
        {
            DoSoftReset(0); // soft reset?
        }
        if (sub_0202FB80()) {
            Main_RunOverlayManager();
            sub_0201B5CC(gSystem.unk18);
            sub_0201B5CC(gSystem.unk24);
            if (!gSystem.unk30) {
                OS_WaitIrq(1, 1);
                gSystem.unk2C++;
            }
        }
        GF_RTC_UpdateOnFrame();
        PlayTimerUpdate();
        sub_020222C4();
        sub_0201B5CC(gSystem.unk24);
        OS_WaitIrq(1, 1);
        gSystem.unk2C++;
        gSystem.unk30 = 0;
        DoAllScreenBrightnessTransitionStep();
        sub_0200E2D8();
        if (gSystem.vBlankIntr) {
            gSystem.vBlankIntr(gSystem.vBlankIntrArg);
        }
        DoSoundUpdateFrame();
        sub_0201B5CC(gSystem.unk20);
    }
}

void sub_02000DF4(void) {
    UNK_02016FA8.mainOverlayId = SDK_OVERLAY_INVALID_ID;
    UNK_02016FA8.overlayManager = NULL;
    UNK_02016FA8.queuedMainOverlayId = SDK_OVERLAY_INVALID_ID; // overlay invalid
    UNK_02016FA8.template = NULL;
}

void Main_RunOverlayManager(void) {
    if (UNK_02016FA8.overlayManager == NULL) {
        if (UNK_02016FA8.template == NULL) {
            return;
        }
        if (UNK_02016FA8.queuedMainOverlayId != SDK_OVERLAY_INVALID_ID) {
            HandleLoadOverlay(UNK_02016FA8.queuedMainOverlayId, 0);
        }
        UNK_02016FA8.mainOverlayId = UNK_02016FA8.queuedMainOverlayId;
        UNK_02016FA8.overlayManager = OverlayManager_New(UNK_02016FA8.template, &UNK_02016FA8.unk10, HEAP_ID_DEFAULT);
        UNK_02016FA8.queuedMainOverlayId = SDK_OVERLAY_INVALID_ID;
        UNK_02016FA8.template = NULL;
    }
    if (OverlayManager_Run(UNK_02016FA8.overlayManager)) {
        OverlayManager_Delete(UNK_02016FA8.overlayManager);
        UNK_02016FA8.overlayManager = NULL;
        if (UNK_02016FA8.mainOverlayId != SDK_OVERLAY_INVALID_ID) {
            UnloadOverlayByID(UNK_02016FA8.mainOverlayId);
        }
    }
}

void RegisterMainOverlay(FSOverlayID id, const struct OverlayManagerTemplate *template) {
    GF_ASSERT(UNK_02016FA8.template == NULL);
    UNK_02016FA8.queuedMainOverlayId = id;
    UNK_02016FA8.template = template;
}

void sub_02000E9C(void) {
    sub_0202FB80();
    OS_WaitIrq(TRUE, OS_IE_VBLANK);
    gSystem.unk2C++;
    gSystem.unk30 = 0;
    if (gSystem.vBlankIntr != NULL) {
        gSystem.vBlankIntr(gSystem.vBlankIntrArg);
    }
}

void sub_02000EC8(u32 parameter) {
    if (sub_02033678() && CARD_TryWaitBackupAsync() == TRUE) {
        OS_ResetSystem(parameter);
    }
    sub_02000E9C();
}

void sub_02000EE8(void) {
    u32 r1 = sub_020335B8();
    switch (r1) {
    case 1:
        sub_02000F4C(1, r1);
        break;
    case 2:
        sub_02000F4C(0, r1);
        break;
    case 3:
        sub_02000F4C(1, r1);
        break;
    }
}

extern void sub_0200E3A0(PMLCDTarget, int);

__declspec(noreturn) void DoSoftReset(u32 parameter) {
    sub_0200E3A0(PM_LCD_TOP, 0x7FFF);
    sub_0200E3A0(PM_LCD_BOTTOM, 0x7FFF);
    if (sub_02032DAC()) {
        sub_0202287C(sub_020225F8());
    }
    do {
        HandleDSLidAction();
        sub_02000EC8(parameter);
    } while (1);
}

void sub_02000F4C(u32 arg0, u32 arg1) {
    if (arg1 == 3) {
        ShowCommunicationError(HEAP_ID_DEFAULT, 3, 0);
    } else if (arg0 == 0) {
        ShowCommunicationError(HEAP_ID_DEFAULT, 2, 0);
    } else {
        ShowCommunicationError(HEAP_ID_DEFAULT, 0, 0);
    }
    sub_02032DAC();
    while (TRUE) {
        HandleDSLidAction();
        ReadKeypadAndTocuhpad();
        if (gSystem.newKeys & 1) {
            break;
        }
        sub_02000E9C();
    }
    DoSoftReset(arg0);
}

extern void GF_RTC_CopyDateTime(struct Unk21C4818 *, struct Unk21C4828 *);
extern void SetMTRNGSeed(u32);
extern void SetLCRNGSeed(u32);

void InitializeMainRNG(void) {
    struct Unk21C4818 spC;
    struct Unk21C4828 sp0;
    GF_RTC_CopyDateTime(&spC, &sp0);
    {
        u32 r4 = gSystem.unk2C;
        u32 r5 = ((sp0.unk4 + sp0.unk8) << 24) + (spC.unk0 + ((256 * spC.unk4 * spC.unk8) << 16) + (sp0.unk0 << 16));
        SetMTRNGSeed(r4 + r5);
        SetLCRNGSeed(r4 + r5);
    }
}

extern void sub_0201CE04(void);
extern void sub_0201CDD0(void);

void HandleDSLidAction(void) {
    PMBackLightSwitch top, bottom;
    if (PAD_DetectFold()) {
        if (!gSystem.unk67) {
            sub_0201CE04();
            if (CTRDG_IsPulledOut() == TRUE) {
                UNK_02016FA4 = 1;
            }
            {
                int r1 = UNK_02016FA4;
                while (1) {
                    PMWakeUpTrigger trigger = PM_TRIGGER_COVER_OPEN | PM_TRIGGER_CARD;
                    if (gSystem.gbaCartId && !r1) {
                        trigger |= PM_TRIGGER_CARTRIDGE;
                    }
                    PM_GoSleepMode(trigger, PM_PAD_LOGIC_OR, 0);
                    if (CARD_IsPulledOut()) {
                        PM_ForceToPowerOff();
                        break;
                    } else if (PAD_DetectFold()) {
                        r1 = UNK_02016FA4 = 1;
                    } else {
                        break;
                    }
                }
                sub_0201CDD0();
                return;
            }
        } else {
            PM_GetBackLight(&top, &bottom);
            if (top == PM_BACKLIGHT_ON) {
                PM_SetBackLight(PM_LCD_ALL, PM_BACKLIGHT_OFF);
            }
        }
    } else {
        PM_GetBackLight(&top, &bottom);
        if (top == PM_BACKLIGHT_OFF) {
            PM_SetBackLight(PM_LCD_ALL, gBacklightTop);
        }
    }
}
