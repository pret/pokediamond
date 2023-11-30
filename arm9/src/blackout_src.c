#include "blackout.h"
#include "bg_window.h"
#include "graphic/font.naix"
#include "gf_gfx_loader.h"

/*static*/ void Blackout_InitDisplays(BgConfig *bgConfig);

static const struct GraphicsBanks Blackout_GraphicsBanks = {
    .bg = GX_VRAM_BG_128_B,
    .bgextpltt = GX_VRAM_BGEXTPLTT_NONE,
    .subbg = GX_VRAM_SUB_BG_128_C,
    .subbgextpltt = GX_VRAM_SUB_BGEXTPLTT_NONE,
    .obj = GX_VRAM_OBJ_64_E,
    .objextpltt = GX_VRAM_OBJEXTPLTT_NONE,
    .subobj = GX_VRAM_SUB_OBJ_16_I,
    .subobjextpltt = GX_VRAM_SUB_OBJEXTPLTT_NONE,
    .tex = GX_VRAM_TEX_0_A,
    .texpltt = GX_VRAM_TEXPLTT_01_FG,
};

static const struct GraphicsModes Blackout_GraphicsModes = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

static const BgTemplate Blackout_BgTemplate = {
    .x = 0,
    .y = 0,
    .bufferSize = 0x800,
    .baseTile = 0,
    .size = GF_BG_SCR_SIZE_256x256,
    .colorMode = GX_BG_COLORMODE_16,
    .screenBase = GX_BG_SCRBASE_0xf800,
    .charBase = GX_BG_CHARBASE_0x00000,
    .bgExtPltt = GX_BG_EXTPLTT_01,
    .priority = 1,
    .areaOver = GX_BG_AREAOVER_XLU,
    .dummy = 0,
    .mosaic = FALSE
};

/*static*/ const WindowTemplate Blackout_WindowTemplate = {
    .bgId = GF_BG_LYR_MAIN_3,
    .left = 4,
    .top = 5,
    .width = 25,
    .height = 15,
    .palette = 13,
    .baseTile = 0x01
};

/*static*/ void Blackout_InitDisplays(BgConfig *bgConfig) {
    GfGfx_SetBanks(&Blackout_GraphicsBanks);
    SetBothScreensModesAndDisable(&Blackout_GraphicsModes);
    InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_3, &Blackout_BgTemplate, GF_BG_TYPE_TEXT);
    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_FONT, NARC_font_narc_0006_NCLR, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_OFFSET_13, 0x20, HEAP_ID_FIELD);
}
