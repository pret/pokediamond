#include "global.h"
#include "bg_window.h"
#include "filesystem.h"
#include "font.h"
#include "game_init.h"
#include "GX_layers.h"
#include "main.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0613.h"
#include "PAD_pad.h"
#include "string16.h"
#include "text.h"
#include "wfc_user_info_warning.h"
#include "brightness.h"
#include "render_window.h"

extern void SetMasterBrightnessNeutral(BOOL set_brightness_on_bottom_screen);
extern void sub_0200E3A0(BOOL set_brightness_on_bottom_screen, s32);

static const struct WindowTemplate sWFCWarningMsgWindowTemplate = {
    .bgId = GF_BG_LYR_MAIN_0,
    .tilemapLeft = 3,
    .tilemapTop = 3,
    .width = 26,
    .height = 18,
    .paletteNum = 0x01,
    .baseTile = 0x23,
};

static const struct GraphicsModes sWFCWarningMsgGraphicsModes = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

static const struct BgTemplate sWFCWarningMsgBgTemplate = {
    .x = 0,
    .y = 0,
    .bufferSize = 0x800,
    .baseTile = 0,
    .size = GF_BG_SCR_SIZE_256x256,
    .colorMode = GX_BG_COLORMODE_16,
    .screenBase = GX_BG_SCRBASE_0x0000,
    .charBase = GX_BG_CHARBASE_0x18000,
    .bgExtPltt = GX_BG_EXTPLTT_01,
    .priority = 1,
    .areaOver = GX_BG_AREAOVER_XLU,
    .unk17 = 0,
    .mosaic = FALSE,
};

static const struct GraphicsBanks sWFCWarningMsgGraphicsBanks = {
    .bg = GX_VRAM_BG_256_AB,
    .bgextpltt = GX_VRAM_BGEXTPLTT_NONE,
    .subbg = GX_VRAM_SUB_BG_NONE,
    .subbgextpltt = GX_VRAM_SUB_BGEXTPLTT_NONE,
    .obj = GX_VRAM_OBJ_NONE,
    .objextpltt = GX_VRAM_OBJEXTPLTT_NONE,
    .subobj = GX_VRAM_SUB_OBJ_NONE,
    .subobjextpltt = GX_VRAM_SUB_OBJEXTPLTT_NONE,
    .tex = GX_VRAM_TEX_NONE,
    .texpltt = GX_VRAM_TEXPLTT_NONE,
};

void ShowWFCUserInfoWarning(u32 heap_id, u32 a1)
{
#pragma unused(a1)
    struct Window window;

    sub_0200E3A0(PM_LCD_TOP, 0);
    sub_0200E3A0(PM_LCD_BOTTOM, 0);

    sub_02015EF4();
    Main_SetVBlankIntrCB(NULL, NULL);
    Main_SetHBlankIntrCB(NULL, NULL);

    GX_DisableEngineALayers();
    GX_DisableEngineBLayers();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    SetKeyRepeatTimers(4, 8);

    gSystem.screensFlipped = 0;

    GX_SwapDisplay();
    G2_BlendNone();
    G2S_BlendNone();
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);
    GX_SetBanks(&sWFCWarningMsgGraphicsBanks);

    struct BgConfig* bg_config = BgConfig_Alloc(heap_id);

    SetBothScreensModesAndDisable(&sWFCWarningMsgGraphicsModes);

    InitBgFromTemplate(bg_config, 0, &sWFCWarningMsgBgTemplate, 0);
    BgClearTilemapBufferAndCommit(bg_config, GF_BG_LYR_MAIN_0);
    LoadUserFrameGfx1(bg_config, GF_BG_LYR_MAIN_0, 0x01F7, 2, 0, heap_id);
    LoadFontPal0(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_1, heap_id);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, heap_id);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, GX_RGB(1, 1, 27));
    BG_SetMaskColor(GF_BG_LYR_SUB_0, GX_RGB(1, 1, 27));

    struct MsgData* warning_messages_data = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0613_bin, heap_id);
    struct String* warning_message = String_New(384, heap_id);
    ResetAllTextPrinters();
    AddWindow(bg_config, &window, &sWFCWarningMsgWindowTemplate);
    FillWindowPixelRect(&window, 0xF, 0, 0, 208, 144);
    DrawFrameAndWindow1(&window, FALSE, 0x01F7, 2);

    ReadMsgDataIntoString(warning_messages_data, narc_0613_00015, warning_message); // Your Nintendo Wi-Fi Connection User Information may have been erased...
    AddTextPrinterParameterized(&window, 0, warning_message, 0, 0, 0, 0);
    String_Delete(warning_message);

    GX_BothDispOn();
    SetMasterBrightnessNeutral(PM_LCD_TOP);
    SetMasterBrightnessNeutral(PM_LCD_BOTTOM);
    SetBlendBrightness(0, 0x3F, 3);

    while (TRUE)
    {
        u16 pressed_buttons = PAD_Read();

        HandleDSLidAction();

        if (pressed_buttons & PAD_BUTTON_A)
        {
            break;
        }

        OS_WaitIrq(TRUE, OS_IE_V_BLANK);
    }

    RemoveWindow(&window);
    DestroyMsgData(warning_messages_data);

    ToggleBgLayer(GF_BG_LYR_MAIN_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_0, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GX_LAYER_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GX_LAYER_TOGGLE_OFF);

    FreeBgTilemapBuffer(bg_config, GF_BG_LYR_MAIN_0);
    FreeToHeap(bg_config);
}
