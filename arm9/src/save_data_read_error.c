#include "global.h"
#include "bg_window.h"
#include "brightness.h"
#include "game_init.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "save_data_read_error.h"
#include "text.h"

extern void FUN_02002ED0(enum GFBgLayer layer, u32 base_addr, u32 heap_id);
extern void FUN_0200CB00(struct BgConfig* bg_config, enum GFBgLayer layer, u32 num_tiles, u32, u8, u32 heap_id);
extern void FUN_0200CCA4(struct Window* window, BOOL copy_to_vram, u16 fill_value, u32 palette_num);
extern void FUN_0200E394(BOOL set_brightness_on_bottom_screen);
extern void FUN_0200E3A0(BOOL set_brightness_on_bottom_screen, s32);

const struct WindowTemplate gSaveDataReadErrorWindowTemplate = {
    .bgId = GF_BG_LYR_MAIN_0,
    .tilemapLeft = 3,
    .tilemapTop = 3,
    .width = 26,
    .height = 18,
    .paletteNum = 0x01,
    .baseTile = 0x23,
};

const struct GraphicsModes gSaveDataReadErrorGraphicsModes = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

const struct BgTemplate gSaveDataReadErrorBgTemplate = {
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

const struct GraphicsBanks gSaveDataReadErrorGraphicsBanks = {
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

THUMB_FUNC void ShowSaveDataReadError(u32 heap_id)
{
    struct Window window;

    FUN_0200E3A0(PM_LCD_TOP, 0);
    FUN_0200E3A0(PM_LCD_BOTTOM, 0);

    Main_SetVBlankIntrCB(NULL, NULL);
    FUN_02015F34(NULL, NULL);

    GX_DisableEngineALayers();
    GX_DisableEngineBLayers();
    reg_GX_DISPCNT &= ~REG_GX_DISPCNT_DISPLAY_MASK;
    reg_GXS_DB_DISPCNT &= ~REG_GX_DISPCNT_DISPLAY_MASK;

    SetKeyRepeatTimers(4, 8);

    gMain.unk65 = 0;

    GX_SwapDisplay();
    reg_G2_BLDCNT = 0;
    reg_G2S_DB_BLDCNT = 0;
    reg_GX_DISPCNT &= ~(REG_GX_DISPCNT_OW_MASK | REG_GX_DISPCNT_W1_MASK | REG_GX_DISPCNT_W0_MASK);
    reg_GXS_DB_DISPCNT &= ~(REG_GXS_DB_DISPCNT_OW_MASK | REG_GXS_DB_DISPCNT_W1_MASK | REG_GXS_DB_DISPCNT_W0_MASK);
    GX_SetBanks(&gSaveDataReadErrorGraphicsBanks);

    struct BgConfig* bg_config = BgConfig_Alloc(heap_id);

    SetBothScreensModesAndDisable(&gSaveDataReadErrorGraphicsModes);

    InitBgFromTemplate(bg_config, 0, &gSaveDataReadErrorBgTemplate, 0);
    BgClearTilemapBufferAndCommit(bg_config, 0);
    FUN_0200CB00(bg_config, GF_BG_LYR_MAIN_0, 0x01F7, 2, 0, heap_id);
    FUN_02002ED0(GF_BG_LYR_MAIN_0, 0x20, heap_id);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, heap_id);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, 0x6C21);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, 0x6C21);

    struct MsgData* msg_data = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, NARC_msg_narc_0005_bin, heap_id);
    struct String* str = String_ctor(384, heap_id);

    FUN_0201BD5C();

    AddWindow(bg_config, &window, &gSaveDataReadErrorWindowTemplate);
    FillWindowPixelRect(&window, 0xF, 0, 0, 208, 144);
    FUN_0200CCA4(&window, FALSE, 0x01F7, 2);

    ReadMsgDataIntoString(msg_data, 0, str);
    AddTextPrinterParameterized(&window, 0, str, 0, 0, 0, NULL);
    String_dtor(str);

    GX_BothDispOn();
    FUN_0200E394(PM_LCD_TOP);
    FUN_0200E394(PM_LCD_BOTTOM);
    SetBrightness(0, 0x3F, 3);

    while (TRUE)
    {
        HandleDSLidAction();
        OS_WaitIrq(TRUE, OS_IE_V_BLANK);
    }
}
