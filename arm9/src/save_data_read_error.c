#include "global.h"
#include "bg_window.h"
#include "brightness.h"
#include "constants/rgb.h"
#include "font.h"
#include "game_init.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0005.h"
#include "save_data_read_error.h"
#include "text.h"
#include "render_window.h"

extern void SetMasterBrightnessNeutral(BOOL set_brightness_on_bottom_screen);
extern void sub_0200E3A0(BOOL set_brightness_on_bottom_screen, s32);

static const struct WindowTemplate sSaveDataReadErrorWindowTemplate = {
    .bgId = GF_BG_LYR_MAIN_0,
    .left = 3,
    .top = 3,
    .width = 26,
    .height = 18,
    .palette = 1,
    .baseTile = 0x23,
};

static const struct GraphicsModes sSaveDataReadErrorGraphicsModes = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

static const struct BgTemplate sSaveDataReadErrorBgTemplate = {
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
    .dummy = 0,
    .mosaic = FALSE,
};

static const struct GraphicsBanks sSaveDataReadErrorGraphicsBanks = {
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

void ShowSaveDataReadError(HeapID heapId)
{
    struct Window window;

    sub_0200E3A0(PM_LCD_TOP, 0);
    sub_0200E3A0(PM_LCD_BOTTOM, 0);

    Main_SetVBlankIntrCB(NULL, NULL);
    Main_SetHBlankIntrCB(NULL, NULL);

    GfGfx_DisableEngineAPlanes();
    GfGfx_DisableEngineBPlanes();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    SetKeyRepeatTimers(4, 8);

    gSystem.screensFlipped = FALSE;

    GfGfx_SwapDisplay();
    G2_BlendNone();
    G2S_BlendNone();
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);
    GfGfx_SetBanks(&sSaveDataReadErrorGraphicsBanks);

    struct BgConfig* bg_config = BgConfig_Alloc(heapId);

    SetBothScreensModesAndDisable(&sSaveDataReadErrorGraphicsModes);

    InitBgFromTemplate(bg_config, 0, &sSaveDataReadErrorBgTemplate, 0);
    BgClearTilemapBufferAndCommit(bg_config, GF_BG_LYR_MAIN_0);
    LoadUserFrameGfx1(bg_config, GF_BG_LYR_MAIN_0, 0x01F7, 2, 0, heapId);
    LoadFontPal0(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_1, heapId);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, heapId);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, RGB(1, 1, 27));
    BG_SetMaskColor(GF_BG_LYR_SUB_0, RGB(1, 1, 27));

    struct MsgData* msg_data = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0005_bin, heapId);
    struct String* str = String_New(384, heapId);

    ResetAllTextPrinters();

    AddWindow(bg_config, &window, &sSaveDataReadErrorWindowTemplate);
    FillWindowPixelRect(&window, 0xF, 0, 0, 208, 144);
    DrawFrameAndWindow1(&window, FALSE, 0x01F7, 2);

    ReadMsgDataIntoString(msg_data, narc_0005_00000, str); // The data could not be read. Please turn off the power...
    AddTextPrinterParameterized(&window, 0, str, 0, 0, 0, NULL);
    String_Delete(str);

    GfGfx_BothDispOn();
    SetMasterBrightnessNeutral(PM_LCD_TOP);
    SetMasterBrightnessNeutral(PM_LCD_BOTTOM);
    SetBlendBrightness(0, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_MAIN | SCREEN_MASK_SUB);

    while (TRUE)
    {
        HandleDSLidAction();
        OS_WaitIrq(TRUE, OS_IE_VBLANK);
    }
}

void ShowGBACartRemovedError(HeapID heapId)
{
    struct Window window;

    sub_0200E3A0(PM_LCD_TOP, 0);
    sub_0200E3A0(PM_LCD_BOTTOM, 0);

    Main_SetVBlankIntrCB(NULL, NULL);
    Main_SetHBlankIntrCB(NULL, NULL);

    GfGfx_DisableEngineAPlanes();
    GfGfx_DisableEngineBPlanes();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    SetKeyRepeatTimers(4, 8);

    gSystem.screensFlipped = FALSE;

    GfGfx_SwapDisplay();
    G2_BlendNone();
    G2S_BlendNone();
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);
    GfGfx_SetBanks(&sSaveDataReadErrorGraphicsBanks);

    struct BgConfig* bg_config = BgConfig_Alloc(heapId);

    SetBothScreensModesAndDisable(&sSaveDataReadErrorGraphicsModes);

    InitBgFromTemplate(bg_config, 0, &sSaveDataReadErrorBgTemplate, 0);
    BgClearTilemapBufferAndCommit(bg_config, GF_BG_LYR_MAIN_0);
    LoadUserFrameGfx1(bg_config, GF_BG_LYR_MAIN_0, 0x01F7, 2, 0, heapId);
    LoadFontPal0(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_1, heapId);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, heapId);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, RGB(1, 1, 27));
    BG_SetMaskColor(GF_BG_LYR_SUB_0, RGB(1, 1, 27));

    struct MsgData* msg_data = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0005_bin, heapId);
    struct String* str = String_New(384, heapId);

    ResetAllTextPrinters();

    AddWindow(bg_config, &window, &sSaveDataReadErrorWindowTemplate);
    FillWindowPixelRect(&window, 0xF, 0, 0, 208, 144);
    DrawFrameAndWindow1(&window, FALSE, 0x01F7, 2);

    ReadMsgDataIntoString(msg_data, narc_0005_00001, str); // Error reading data. The GBA Game Pak was removed...
    AddTextPrinterParameterized(&window, 0, str, 0, 0, 0, NULL);
    String_Delete(str);

    GfGfx_BothDispOn();
    SetMasterBrightnessNeutral(PM_LCD_TOP);
    SetMasterBrightnessNeutral(PM_LCD_BOTTOM);
    SetBlendBrightness(0, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG0), SCREEN_MASK_MAIN | SCREEN_MASK_SUB);

    while (TRUE)
    {
        HandleDSLidAction();
        OS_WaitIrq(TRUE, OS_IE_VBLANK);
    }
}
