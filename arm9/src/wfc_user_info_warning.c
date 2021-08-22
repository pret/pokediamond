#include "global.h"
#include "bg_window.h"
#include "filesystem.h"
#include "game_init.h"
#include "GX_layers.h"
#include "main.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "PAD_pad.h"
#include "string16.h"
#include "text.h"
#include "wfc_user_info_warning.h"
#include "brightness.h"
#include "render_window.h"

extern void FUN_02002ED0(enum GFBgLayer layer, u32 base_addr, u32 heap_id);
extern void FUN_0200E394(BOOL set_brightness_on_bottom_screen);
extern void FUN_0200E3A0(BOOL set_brightness_on_bottom_screen, s32);

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
    .bg = 3,
    .bgextpltt = 0,
    .subbg = 0,
    .subbgextpltt = 0,
    .obj = 0,
    .objextpltt = 0,
    .subobj = 0,
    .subobjextpltt = 0,
    .tex = 0,
    .texpltt = 0,
};

THUMB_FUNC void ShowWFCUserInfoWarning(u32 heap_id, u32 a1)
{
#pragma unused(a1)
    struct Window window;

    FUN_0200E3A0(PM_LCD_TOP, 0);
    FUN_0200E3A0(PM_LCD_BOTTOM, 0);

    FUN_02015EF4();
    Main_SetVBlankIntrCB(NULL, NULL);
    FUN_02015F34(NULL, NULL);

    GX_DisableEngineALayers();
    GX_DisableEngineBLayers();
    reg_GX_DISPCNT &= ~REG_GX_DISPCNT_DISPLAY_MASK;
    reg_GXS_DB_DISPCNT &= ~REG_GX_DISPCNT_DISPLAY_MASK;

    SetKeyRepeatTimers(4, 8);

    gMain.screensFlipped = 0;

    GX_SwapDisplay();
    reg_G2_BLDCNT = 0;
    reg_G2S_DB_BLDCNT = 0;
    reg_GX_DISPCNT &= ~(REG_GX_DISPCNT_OW_MASK | REG_GX_DISPCNT_W1_MASK | REG_GX_DISPCNT_W0_MASK);
    reg_GXS_DB_DISPCNT &= ~(REG_GXS_DB_DISPCNT_OW_MASK | REG_GXS_DB_DISPCNT_W1_MASK | REG_GXS_DB_DISPCNT_W0_MASK);
    GX_SetBanks(&sWFCWarningMsgGraphicsBanks);

    struct BgConfig* bg_config = BgConfig_Alloc(heap_id);

    SetBothScreensModesAndDisable(&sWFCWarningMsgGraphicsModes);

    InitBgFromTemplate(bg_config, 0, &sWFCWarningMsgBgTemplate, 0);
    BgClearTilemapBufferAndCommit(bg_config, 0);
    FUN_0200CB00(bg_config, GF_BG_LYR_MAIN_0, 0x01F7, 2, 0, heap_id);
    FUN_02002ED0(GF_BG_LYR_MAIN_0, 0x20, heap_id);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, heap_id);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, 0x6C21);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, 0x6C21);

    struct MsgData* warning_messages_data = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, NARC_msg_narc_0613_bin, heap_id);
    struct String* warning_message = String_ctor(384, heap_id);
    FUN_0201BD5C();
    AddWindow(bg_config, &window, &sWFCWarningMsgWindowTemplate);
    FillWindowPixelRect(&window, 0xF, 0, 0, 208, 144);
    DrawFrameAndWindow1(&window, FALSE, 0x01F7, 2);

    ReadMsgDataIntoString(warning_messages_data, 15, warning_message);
    AddTextPrinterParameterized(&window, 0, warning_message, 0, 0, 0, 0);
    String_dtor(warning_message);

    GX_BothDispOn();
    FUN_0200E394(0);
    FUN_0200E394(1);
    SetBrightness(0, 0x3F, 3);

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

    FreeBgTilemapBuffer(bg_config, 0);
    FreeToHeap(bg_config);
}
