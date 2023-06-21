#include "global.h"
#include "overlay_19.h"
#include "heap.h"
#include "gx.h"
#include "gf_gfx_loader.h"
#include "bg_window.h"
#include "graphic/poketch.naix"

const struct BgTemplate ov19_02252508 = {
    .x = 0,
    .y = 0,
    .bufferSize = 0x800,
    .baseTile = 0x000,
    .size = GF_BG_SCR_SIZE_256x256,
    .colorMode = GF_BG_CLR_4BPP,
    .screenBase = 12,
    .charBase = 0,
    .priority = 0,
    .areaOver = 0,
    .mosaic = 0
};

void ov19_02252440(struct BgConfig * bgConfig)
{
    CreateHeap(3, 8, 0x18000);
    GXS_SetGraphicsMode(GX_BGMODE_0);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
    InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_0, &ov19_02252508, GF_BG_TYPE_TEXT);
    GfGfxLoader_LoadCharData(NARC_GRAPHIC_POKETCH, NARC_poketch_narc_0010_NCGR_lz, bgConfig, GF_BG_LYR_SUB_0, 0, 0, TRUE, 8);
    GfGfxLoader_LoadScrnData(NARC_GRAPHIC_POKETCH, NARC_poketch_narc_0011_NSCR_lz, bgConfig, GF_BG_LYR_SUB_0, 0, 0, TRUE, 8);
    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_POKETCH, NARC_poketch_narc_0012_NCLR, GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_OFFSET_0, 0x20, 8);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);
    GXS_SetVisiblePlane(GX_PLANEMASK_BG0);
}

void ov19_022524F4(struct BgConfig * bgConfig)
{
    FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_0);
    DestroyHeap(8);
}

BOOL ov19_02252504(struct BgConfig * bgConfig)
{
#pragma unused(bgConfig)
    return TRUE;
}
