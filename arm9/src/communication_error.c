#include "global.h"
#include "bg_window.h"
#include "communication_error.h"
#include "game_init.h"
#include "MI_dma.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0200.h"
#include "text.h"
#include "brightness.h"
#include "render_window.h"

extern void SetMasterBrightnessNeutral(BOOL set_brightness_on_bottom_screen);
extern void sub_0200E3A0(BOOL set_brightness_on_bottom_screen, s32);

static const struct WindowTemplate sCommunicationErrorWindowTemplate = {
    .bgId = GF_BG_LYR_MAIN_0,
    .tilemapLeft = 3,
    .tilemapTop = 3,
    .width = 26,
    .height = 18,
    .paletteNum = 0x01,
    .baseTile = 0x23,
};

static const struct GraphicsModes sCommunicationErrorGraphicsModes = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

static const struct BgTemplate sCommunicationErrorBgTemplate = {
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

static const struct GraphicsBanks sCommunicationErrorGraphicsBanks = {
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

static void VBlankIntr(void);

static void VBlankIntr(void)
{
    DTCM.intr_check |= OS_IE_V_BLANK;
    MI_WaitDma(GX_DEFAULT_DMAID);
}

void ShowCommunicationError(u32 heap_id, u32 error, u32 error_code)
{
    struct Window window;
    
    u32 error_message_no;
    switch (error)
    {
        default:
        case 0:
            error_message_no = narc_0200_00001; //A communication error has occurred. If you were in the Union Room...
            break;
        case 1:
            error_message_no = narc_0200_00002; //An error occurred while attempting to communicate. ({STRVAR_1 54, 0}) Please turn off the power...
            break;
        case 2:
            error_message_no = narc_0200_00003; //A communication error has occurred. You will be returned to the title screen...
            break;
        case 3:
            error_message_no = narc_0200_00004; //The GTS is extremely busy now. Please wait a while and try again.
            break;
        case 4:
            error_message_no = narc_0200_00005; //An error occurred while attempting\nto communicate.\nPlease turn off the power...
            break;
    }

    sub_0200E3A0(PM_LCD_TOP, 0);
    sub_0200E3A0(PM_LCD_BOTTOM, 0);

    OS_DisableIrqMask(OS_IE_V_BLANK);
    OS_SetIrqFunction(OS_IE_V_BLANK, VBlankIntr);
    OS_EnableIrqMask(OS_IE_V_BLANK);

    Main_SetVBlankIntrCB(NULL, NULL);
    Main_SetHBlankIntrCB(NULL, NULL);

    GX_DisableEngineALayers();
    GX_DisableEngineBLayers();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    SetKeyRepeatTimers(4, 8);

    gSystem.screensFlipped = FALSE;

    GX_SwapDisplay();
    G2_BlendNone();
    G2S_BlendNone();
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);
    GX_SetBanks(&sCommunicationErrorGraphicsBanks);

    struct BgConfig* bg_config = BgConfig_Alloc(heap_id);

    SetBothScreensModesAndDisable(&sCommunicationErrorGraphicsModes);

    InitBgFromTemplate(bg_config, 0, &sCommunicationErrorBgTemplate, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(bg_config, GF_BG_LYR_MAIN_0);
    LoadUserFrameGfx1(bg_config, GF_BG_LYR_MAIN_0, 0x01F7, 2, 0, heap_id);
    LoadFontPal0(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_1, heap_id);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, heap_id);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, GX_RGB(1, 1, 27));
    BG_SetMaskColor(GF_BG_LYR_SUB_0, GX_RGB(1, 1, 27));

    struct MsgData* error_message_data = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0200_bin, heap_id);
    struct String* error_message_str = String_New(384, heap_id);
    struct String* tmp_str = String_New(384, heap_id);
    ResetAllTextPrinters();
    MessageFormat* messageFormat = MessageFormat_New(heap_id);

    AddWindow(bg_config, &window, &sCommunicationErrorWindowTemplate);
    FillWindowPixelRect(&window, 0xF, 0, 0, 208, 144);
    DrawFrameAndWindow1(&window, FALSE, 0x01F7, 2);

    BufferIntegerAsString(messageFormat, 0, (s32)error_code, 5, PRINTING_MODE_LEADING_ZEROS, TRUE);
    ReadMsgDataIntoString(error_message_data, error_message_no, tmp_str);
    StringExpandPlaceholders(messageFormat, error_message_str, tmp_str);

    AddTextPrinterParameterized(&window, 0, error_message_str, 0, 0, 0, NULL);
    String_Delete(error_message_str);
    // BUG: tmp_str is never destroyed.

    GX_BothDispOn();
    SetMasterBrightnessNeutral(PM_LCD_TOP);
    SetMasterBrightnessNeutral(PM_LCD_BOTTOM);
    SetBlendBrightness(0, 0x3F, 3);

    RemoveWindow(&window);
    DestroyMsgData(error_message_data);
    MessageFormat_Delete(messageFormat);
    FreeToHeap(bg_config);
}
