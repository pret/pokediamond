#include "global.h"
#include "bg_window.h"
#include "communication_error.h"
#include "game_init.h"
#include "MI_dma.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "text.h"
#include "brightness.h"
#include "render_window.h"

extern void FUN_0200E394(BOOL set_brightness_on_bottom_screen);
extern void FUN_0200E3A0(BOOL set_brightness_on_bottom_screen, s32);

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

THUMB_FUNC void FUN_02033F50(void)
{
    DTCM.intr_check |= 1;
    MI_WaitDma(3);
}

THUMB_FUNC void ShowCommunicationError(u32 heap_id, u32 error, u32 error_code)
{
    struct Window window;
    
    u32 error_message_no;
    switch (error)
    {
        default:
        case 0:
            error_message_no = 1;
            break;
        case 1:
            error_message_no = 2;
            break;
        case 2:
            error_message_no = 3;
            break;
        case 3:
            error_message_no = 4;
            break;
        case 4:
            error_message_no = 5;
            break;
    }

    FUN_0200E3A0(PM_LCD_TOP, 0);
    FUN_0200E3A0(PM_LCD_BOTTOM, 0);

    OS_DisableIrqMask(OS_IE_V_BLANK);
    OS_SetIrqFunction(OS_IE_V_BLANK, FUN_02033F50);
    OS_EnableIrqMask(OS_IE_V_BLANK);

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
    GX_SetBanks(&sCommunicationErrorGraphicsBanks);

    struct BgConfig* bg_config = BgConfig_Alloc(heap_id);

    SetBothScreensModesAndDisable(&sCommunicationErrorGraphicsModes);

    InitBgFromTemplate(bg_config, 0, &sCommunicationErrorBgTemplate, 0);
    BgClearTilemapBufferAndCommit(bg_config, 0);
    FUN_0200CB00(bg_config, GF_BG_LYR_MAIN_0, 0x01F7, 2, 0, heap_id);
    FUN_02002ED0(GF_BG_LYR_MAIN_0, 0x20, heap_id);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, heap_id);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, 0x6C21);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, 0x6C21);

    struct MsgData* error_message_data = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, NARC_msg_narc_0200_bin, heap_id);
    struct String* error_message_str = String_ctor(384, heap_id);
    struct String* tmp_str = String_ctor(384, heap_id);
    FUN_0201BD5C();
    struct ScrStrBufs* mgr = ScrStrBufs_new(heap_id);

    AddWindow(bg_config, &window, &sCommunicationErrorWindowTemplate);
    FillWindowPixelRect(&window, 0xF, 0, 0, 208, 144);
    DrawFrameAndWindow1(&window, FALSE, 0x01F7, 2);

    BufferIntegerAsString(mgr, 0, (s32)error_code, 5, 2, 1);
    ReadMsgDataIntoString(error_message_data, error_message_no, tmp_str);
    StringExpandPlaceholders(mgr, error_message_str, tmp_str);

    AddTextPrinterParameterized(&window, 0, error_message_str, 0, 0, 0, NULL);
    String_dtor(error_message_str);
    // BUG: tmp_str is never destroyed.

    GX_BothDispOn();
    FUN_0200E394(PM_LCD_TOP);
    FUN_0200E394(PM_LCD_BOTTOM);
    SetBrightness(0, 0x3F, 3);

    RemoveWindow(&window);
    DestroyMsgData(error_message_data);
    ScrStrBufs_delete(mgr);
    FreeToHeap(bg_config);
}
