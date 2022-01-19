#include "global.h"
#include "bg_window.h"
#include "GX_layers.h"
#include "game_init.h"
#include "gx.h"
#include "heap.h"

const u8 sTilemapWidthByBufferSize[] = {
    [GF_BG_SCR_SIZE_128x128]   = 0x10,
    [GF_BG_SCR_SIZE_256x256]   = 0x20,
    [GF_BG_SCR_SIZE_256x512]   = 0x20,
    [GF_BG_SCR_SIZE_512x256]   = 0x20,
    [GF_BG_SCR_SIZE_512x512]   = 0x20,
    [GF_BG_SCR_SIZE_1024x1024] = 0x20,
};

void (*const sScheduleWindowCopyToVramFuncs[])(struct Window *) = {
    ScheduleWindowCopyToVram_TextMode,
    ScheduleWindowCopyToVram_AffineMode,
    ScheduleWindowCopyToVram_TextMode,
};

void (*const sClearWindowTilemapAndCopyToVramFuncs[])(struct Window *) = {
    ClearWindowTilemapAndCopyToVram_TextMode,
    ClearWindowTilemapAndCopyToVram_AffineMode,
    ClearWindowTilemapAndCopyToVram_TextMode,
};

void (*const sClearWindowTilemapAndScheduleTransferFuncs[])(struct Window *) = {
    ClearWindowTilemapAndScheduleTransfer_TextMode,
    ClearWindowTilemapAndScheduleTransfer_AffineMode,
    ClearWindowTilemapAndScheduleTransfer_TextMode,
};

void (*const sPutWindowTilemapFuncs[])(struct Window *) = {
    PutWindowTilemap_TextMode,
    PutWindowTilemap_AffineMode,
    PutWindowTilemap_TextMode,
};

void (*const sCopyWindowToVramFuncs[])(struct Window *) = {
    CopyWindowToVram_TextMode,
    CopyWindowToVram_AffineMode,
    CopyWindowToVram_TextMode,
};

void (*const sClearWindowTilemapFuncs[])(struct Window *) = {
    ClearWindowTilemapText,
    ClearWindowTilemapAffine,
    ClearWindowTilemapText,
};

THUMB_FUNC struct BgConfig *BgConfig_Alloc(u32 heap_id)
{
    struct BgConfig *ptr = AllocFromHeap(heap_id, sizeof(struct BgConfig));
    memset(ptr, 0, sizeof(struct BgConfig));
    ptr->heap_id = heap_id;
    ptr->scrollScheduled = 0;
    ptr->bufferTransferScheduled = 0;

    return ptr;
}

THUMB_FUNC u32 BgConfig_GetHeapId(struct BgConfig *bgConfig)
{
    return bgConfig->heap_id;
}

THUMB_FUNC void SetBothScreensModesAndDisable(const struct GraphicsModes *modes)
{
    GX_SetGraphicsMode(modes->dispMode, modes->bgMode, modes->_2d3dMode);
    GXS_SetGraphicsMode(modes->subMode);
    GX_SetBGScrOffset(0);
    GX_SetBGCharOffset(0);

    GX_DisableEngineALayers();
    GX_DisableEngineBLayers();
}

THUMB_FUNC void SetScreenModeAndDisable(const struct GraphicsModes *gfxModes, u32 whichScreen)
{
    if (whichScreen == 0)
    {
        GX_SetGraphicsMode(gfxModes->dispMode, gfxModes->bgMode, gfxModes->_2d3dMode);
        GX_DisableEngineALayers();
    }
    else
    {
        GXS_SetGraphicsMode(gfxModes->subMode);
        GX_DisableEngineBLayers();
    }
}

THUMB_FUNC void InitBgFromTemplate(
    struct BgConfig *bgConfig, u8 bgId, const struct BgTemplate *template, u8 bgMode)
{
    u8 screenSize = TranslateGFBgModePairToGXScreenSize(template->size, bgMode);
    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_0_F, GX_LAYER_TOGGLE_ON);
        G2_SetBG0Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2_SetBG0Priority(template->priority);
        G2_BG0Mosaic(template->mosaic);
        break;

    case GF_BG_LYR_MAIN_1:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_1_F, GX_LAYER_TOGGLE_ON);
        G2_SetBG1Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2_SetBG1Priority(template->priority);
        G2_BG1Mosaic(template->mosaic);
        break;

    case GF_BG_LYR_MAIN_2:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_2_F, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            G2_SetBG2ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            G2_SetBG2ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            G2_SetBG2Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2_SetBG2Priority(template->priority);
        G2_BG2Mosaic(template->mosaic);
        break;

    case GF_BG_LYR_MAIN_3:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_3_F, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            G2_SetBG3ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            G2_SetBG3ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            G2_SetBG3Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2_SetBG3Priority(template->priority);
        G2_BG3Mosaic(template->mosaic);
        break;

    case GF_BG_LYR_SUB_0:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_0_F, GX_LAYER_TOGGLE_ON);
        G2S_SetBG0Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2S_SetBG0Priority(template->priority);
        G2S_BG0Mosaic(template->mosaic);
        break;

    case GF_BG_LYR_SUB_1:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_1_F, GX_LAYER_TOGGLE_ON);
        G2S_SetBG1Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2S_SetBG1Priority(template->priority);
        G2S_BG1Mosaic(template->mosaic);
        break;

    case GF_BG_LYR_SUB_2:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_2_F, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            G2S_SetBG2ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            G2S_SetBG2ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            G2S_SetBG2Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2S_SetBG2Priority(template->priority);
        G2S_BG2Mosaic(template->mosaic);
        break;

    case GF_BG_LYR_SUB_3:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_3_F, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            G2S_SetBG3ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            G2S_SetBG3ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            G2S_SetBG3Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2S_SetBG3Priority(template->priority);
        G2S_BG3Mosaic(template->mosaic);
        break;
    }

    bgConfig->bgs[bgId].rotation = 0;
    bgConfig->bgs[bgId].xScale = FX32_ONE;
    bgConfig->bgs[bgId].yScale = FX32_ONE;
    bgConfig->bgs[bgId].centerX = 0;
    bgConfig->bgs[bgId].centerY = 0;

    if (template->bufferSize != 0)
    {
        bgConfig->bgs[bgId].tilemapBuffer = AllocFromHeap(bgConfig->heap_id, template->bufferSize);

        MI_CpuClear16(bgConfig->bgs[bgId].tilemapBuffer, template->bufferSize);

        bgConfig->bgs[bgId].bufferSize = template->bufferSize;
        bgConfig->bgs[bgId].baseTile = template->baseTile;
    }
    else
    {
        bgConfig->bgs[bgId].tilemapBuffer = NULL;
        bgConfig->bgs[bgId].bufferSize = 0;
        bgConfig->bgs[bgId].baseTile = 0;
    }

    bgConfig->bgs[bgId].size = template->size;
    bgConfig->bgs[bgId].mode = bgMode;
    bgConfig->bgs[bgId].colorMode = template->colorMode;

    if (bgMode == GF_BG_TYPE_TEXT && template->colorMode == GX_BG_COLORMODE_16)
    {
        bgConfig->bgs[bgId].tileSize = 0x20;
    }
    else
    {
        bgConfig->bgs[bgId].tileSize = 0x40;
    }

    BgSetPosTextAndCommit(bgConfig, bgId, BG_POS_OP_SET_X, template->x);
    BgSetPosTextAndCommit(bgConfig, bgId, BG_POS_OP_SET_Y, template->y);
}

THUMB_FUNC void SetBgControlParam(struct BgConfig *config, u8 bgId, u32 attr, u8 value)
{
    if (attr == GF_BG_CNT_SET_COLOR_MODE)
    {
        config->bgs[bgId].colorMode = value;
    }

    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        GXBg01Control bg0cnt = G2_GetBG0Control();
        if (attr == GF_BG_CNT_SET_SCREEN_BASE)
        {
            bg0cnt.screenBase = value;
        }
        else if (attr == GF_BG_CNT_SET_CHAR_BASE)
        {
            bg0cnt.charBase = value;
        }

        G2_SetBG0Control(bg0cnt.screenSize, config->bgs[bgId].colorMode, bg0cnt.screenBase, bg0cnt.charBase, bg0cnt.bgExtPltt);
        break;
    case GF_BG_LYR_MAIN_1:
        GXBg01Control bg1cnt = G2_GetBG1Control();
        if (attr == GF_BG_CNT_SET_SCREEN_BASE)
        {
            bg1cnt.screenBase = value;
        }
        else if (attr == GF_BG_CNT_SET_CHAR_BASE)
        {
            bg1cnt.charBase = value;
        }

        G2_SetBG1Control(bg1cnt.screenSize, config->bgs[bgId].colorMode, bg1cnt.screenBase, bg1cnt.charBase, bg1cnt.bgExtPltt);
        break;
    case GF_BG_LYR_MAIN_2:
        switch (config->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            GXBg23ControlText bg2cnt_tx = G2_GetBG2ControlText();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg2cnt_tx.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg2cnt_tx.charBase = value;
            }

            G2_SetBG2ControlText(bg2cnt_tx.screenSize, config->bgs[bgId].colorMode, bg2cnt_tx.screenBase, bg2cnt_tx.charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            GXBg23ControlAffine bg2cnt_aff = G2_GetBG2ControlAffine();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg2cnt_aff.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg2cnt_aff.charBase = value;
            }

            G2_SetBG2ControlAffine(bg2cnt_aff.screenSize, bg2cnt_aff.areaOver, bg2cnt_aff.screenBase,
                                   bg2cnt_aff.charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            GXBg23Control256x16Pltt bg2cnt_256x16pltt = G2_GetBG2Control256x16Pltt();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg2cnt_256x16pltt.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg2cnt_256x16pltt.charBase = value;
            }

            G2_SetBG2Control256x16Pltt(bg2cnt_256x16pltt.screenSize, bg2cnt_256x16pltt.areaOver,
                                       bg2cnt_256x16pltt.screenBase, bg2cnt_256x16pltt.charBase);
            break;
        }
        break;
    case GF_BG_LYR_MAIN_3:
        switch (config->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            GXBg23ControlText bg3cnt_tx = G2_GetBG3ControlText();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg3cnt_tx.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg3cnt_tx.charBase = value;
            }

            G2_SetBG3ControlText(bg3cnt_tx.screenSize, config->bgs[bgId].colorMode, bg3cnt_tx.screenBase, bg3cnt_tx.charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            GXBg23ControlAffine bg3cnt_aff = G2_GetBG3ControlAffine();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg3cnt_aff.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg3cnt_aff.charBase = value;
            }

            G2_SetBG3ControlAffine(bg3cnt_aff.screenSize, bg3cnt_aff.areaOver, bg3cnt_aff.screenBase,
                                   bg3cnt_aff.charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            GXBg23Control256x16Pltt bg3cnt_256x16pltt = G2_GetBG3Control256x16Pltt();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg3cnt_256x16pltt.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg3cnt_256x16pltt.charBase = value;
            }

            G2_SetBG3Control256x16Pltt(bg3cnt_256x16pltt.screenSize, bg3cnt_256x16pltt.areaOver,
                                       bg3cnt_256x16pltt.screenBase, bg3cnt_256x16pltt.charBase);
            break;
        }
        break;
    case GF_BG_LYR_SUB_0:
        GXBg01Control bg0cntsub = G2S_GetBG0Control();
        if (attr == GF_BG_CNT_SET_SCREEN_BASE)
        {
            bg0cntsub.screenBase = value;
        }
        else if (attr == GF_BG_CNT_SET_CHAR_BASE)
        {
            bg0cntsub.charBase = value;
        }

        G2S_SetBG0Control(bg0cntsub.screenSize, config->bgs[bgId].colorMode, bg0cntsub.screenBase, bg0cntsub.charBase, bg0cntsub.bgExtPltt);
        break;
    case GF_BG_LYR_SUB_1:
        GXBg01Control bg1cntsub = G2S_GetBG1Control();
        if (attr == GF_BG_CNT_SET_SCREEN_BASE)
        {
            bg1cntsub.screenBase = value;
        }
        else if (attr == GF_BG_CNT_SET_CHAR_BASE)
        {
            bg1cntsub.charBase = value;
        }

        G2S_SetBG1Control(bg1cntsub.screenSize, config->bgs[bgId].colorMode, bg1cntsub.screenBase, bg1cntsub.charBase, bg1cntsub.bgExtPltt);
        break;
    case GF_BG_LYR_SUB_2:
        switch (config->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            GXBg23ControlText bg2cntsub_tx = G2S_GetBG2ControlText();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg2cntsub_tx.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg2cntsub_tx.charBase = value;
            }

            G2S_SetBG2ControlText(bg2cntsub_tx.screenSize, config->bgs[bgId].colorMode, bg2cntsub_tx.screenBase, bg2cntsub_tx.charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            GXBg23ControlAffine bg2cntsub_aff = G2S_GetBG2ControlAffine();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg2cntsub_aff.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg2cntsub_aff.charBase = value;
            }

            G2S_SetBG2ControlAffine(bg2cntsub_aff.screenSize, bg2cntsub_aff.areaOver, bg2cntsub_aff.screenBase,
                                   bg2cntsub_aff.charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            GXBg23Control256x16Pltt bg2cntsub_256x16pltt = G2S_GetBG2Control256x16Pltt();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg2cntsub_256x16pltt.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg2cntsub_256x16pltt.charBase = value;
            }

            G2S_SetBG2Control256x16Pltt(bg2cntsub_256x16pltt.screenSize, bg2cntsub_256x16pltt.areaOver,
                                       bg2cntsub_256x16pltt.screenBase, bg2cntsub_256x16pltt.charBase);
            break;
        }
        break;
    case GF_BG_LYR_SUB_3:
        switch (config->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            GXBg23ControlText bg3cntsub_tx = G2S_GetBG3ControlText();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg3cntsub_tx.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg3cntsub_tx.charBase = value;
            }

            G2S_SetBG3ControlText(bg3cntsub_tx.screenSize, config->bgs[bgId].colorMode, bg3cntsub_tx.screenBase, bg3cntsub_tx.charBase);
            break;
        case GF_BG_TYPE_AFFINE:
            GXBg23ControlAffine bg3cntsub_aff = G2S_GetBG3ControlAffine();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg3cntsub_aff.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg3cntsub_aff.charBase = value;
            }

            G2S_SetBG3ControlAffine(bg3cntsub_aff.screenSize, bg3cntsub_aff.areaOver, bg3cntsub_aff.screenBase,
                                   bg3cntsub_aff.charBase);
            break;
        case GF_BG_TYPE_256x16PLTT:
            GXBg23Control256x16Pltt bg3cntsub_256x16pltt = G2S_GetBG3Control256x16Pltt();
            if (attr == GF_BG_CNT_SET_SCREEN_BASE)
            {
                bg3cntsub_256x16pltt.screenBase = value;
            }
            else if (attr == GF_BG_CNT_SET_CHAR_BASE)
            {
                bg3cntsub_256x16pltt.charBase = value;
            }

            G2S_SetBG3Control256x16Pltt(bg3cntsub_256x16pltt.screenSize, bg3cntsub_256x16pltt.areaOver,
                                       bg3cntsub_256x16pltt.screenBase, bg3cntsub_256x16pltt.charBase);
            break;
        }
        break;
    }
}

THUMB_FUNC u8 TranslateGFBgModePairToGXScreenSize(u8 size, u32 bgMode)
{
    switch (bgMode)
    {
    case GF_BG_TYPE_TEXT:

        if (size == GF_BG_SCR_SIZE_256x256)
        {
            return GX_BG_SCRSIZE_TEXT_256x256;
        }
        else if (size == GF_BG_SCR_SIZE_256x512)
        {
            return GX_BG_SCRSIZE_TEXT_256x512;
        }
        else if (size == GF_BG_SCR_SIZE_512x256)
        {
            return GX_BG_SCRSIZE_TEXT_512x256;
        }
        else if (size == GF_BG_SCR_SIZE_512x512)
        {
            return GX_BG_SCRSIZE_TEXT_512x512;
        }
        break;

    case GF_BG_TYPE_AFFINE:

        if (size == GF_BG_SCR_SIZE_128x128)
        {
            return GX_BG_SCRSIZE_AFFINE_128x128;
        }
        else if (size == GF_BG_SCR_SIZE_256x256)
        {
            return GX_BG_SCRSIZE_AFFINE_256x256;
        }
        else if (size == GF_BG_SCR_SIZE_512x512)
        {
            return GX_BG_SCRSIZE_AFFINE_512x512;
        }
        else if (size == GF_BG_SCR_SIZE_1024x1024)
        {
            return GX_BG_SCRSIZE_AFFINE_1024x1024;
        }
        break;

    case GF_BG_TYPE_256x16PLTT:

        if (size == GF_BG_SCR_SIZE_128x128)
        {
            return GX_BG_SCRSIZE_256x16PLTT_128x128;
        }
        else if (size == GF_BG_SCR_SIZE_256x256)
        {
            return GX_BG_SCRSIZE_256x16PLTT_256x256;
        }
        else if (size == GF_BG_SCR_SIZE_512x512)
        {
            return GX_BG_SCRSIZE_256x16PLTT_512x512;
        }
        else if (size == GF_BG_SCR_SIZE_1024x1024)
        {
            return GX_BG_SCRSIZE_256x16PLTT_1024x1024;
        }
        break;
    }

    return GX_BG_SCRSIZE_TEXT_256x256; // GX_BG_SCRSIZE_AFFINE_128x128; GX_BG_SCRSIZE_256x16PLTT_128x128;
}

THUMB_FUNC void GetBgScreenDimensions(u32 screenSize, u8 *width_p, u8 *height_p)
{
    switch (screenSize)
    {
    case GF_BG_SCR_SIZE_128x128:
        *width_p = 0x10;
        *height_p = 0x10;
        break;
    case GF_BG_SCR_SIZE_256x256:
        *width_p = 0x20;
        *height_p = 0x20;
        break;
    case GF_BG_SCR_SIZE_256x512:
        *width_p = 0x20;
        *height_p = 0x40;
        break;
    case GF_BG_SCR_SIZE_512x256:
        *width_p = 0x40;
        *height_p = 0x20;
        break;
    case GF_BG_SCR_SIZE_512x512:
        *width_p = 0x40;
        *height_p = 0x40;
        break;
    case GF_BG_SCR_SIZE_1024x1024:
        *width_p = 0x80;
        *height_p = 0x80;
        break;
    }
}

THUMB_FUNC void FreeBgTilemapBuffer(struct BgConfig *bgConfig, u32 bgId)
{
    if (bgConfig->bgs[bgId].tilemapBuffer != NULL)
    {
        FreeToHeap(bgConfig->bgs[bgId].tilemapBuffer);
        bgConfig->bgs[bgId].tilemapBuffer = NULL;
    }
}

THUMB_FUNC void SetBgPriority(u32 bgId, u16 priority)
{
    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        G2_SetBG0Priority(priority);
        break;
    case GF_BG_LYR_MAIN_1:
        G2_SetBG1Priority(priority);
        break;
    case GF_BG_LYR_MAIN_2:
        G2_SetBG2Priority(priority);
        break;
    case GF_BG_LYR_MAIN_3:
        G2_SetBG3Priority(priority);
        break;
    case GF_BG_LYR_SUB_0:
        G2S_SetBG0Priority(priority);
        break;
    case GF_BG_LYR_SUB_1:
        G2S_SetBG1Priority(priority);
        break;
    case GF_BG_LYR_SUB_2:
        G2S_SetBG2Priority(priority);
        break;
    case GF_BG_LYR_SUB_3:
        G2S_SetBG3Priority(priority);
        break;
    }
}

THUMB_FUNC void ToggleBgLayer(u32 bgId, GX_LayerToggle toggle)
{
    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_0_F, toggle);
        break;
    case GF_BG_LYR_MAIN_1:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_1_F, toggle);
        break;
    case GF_BG_LYR_MAIN_2:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_2_F, toggle);
        break;
    case GF_BG_LYR_MAIN_3:
        GX_EngineAToggleLayers(GF_BG_LYR_MAIN_3_F, toggle);
        break;
    case GF_BG_LYR_SUB_0:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_0_F, toggle);
        break;
    case GF_BG_LYR_SUB_1:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_1_F, toggle);
        break;
    case GF_BG_LYR_SUB_2:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_2_F, toggle);
        break;
    case GF_BG_LYR_SUB_3:
        GX_EngineBToggleLayers(GF_BG_LYR_SUB_3_F, toggle);
        break;
    }
}

THUMB_FUNC void BgSetPosTextAndCommit(struct BgConfig *bgConfig, u32 bgId, u32 op, fx32 val)
{
    Bg_SetPosText(&bgConfig->bgs[bgId], op, val);

    u32 x = (u32)bgConfig->bgs[bgId].hOffset;
    u32 y = (u32)bgConfig->bgs[bgId].vOffset;
    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        G2_SetBG0Offset(x, y);
        break;
    case GF_BG_LYR_MAIN_1:
        G2_SetBG1Offset(x, y);
        break;
    case GF_BG_LYR_MAIN_2:
        if (bgConfig->bgs[GF_BG_LYR_MAIN_2].mode == 0)
        {
            G2_SetBG2Offset(x, y);
        }
        else
        {
            BgAffineReset(bgConfig, GF_BG_LYR_MAIN_2);
        }

        break;
    case GF_BG_LYR_MAIN_3:
        if (bgConfig->bgs[GF_BG_LYR_MAIN_3].mode == 0)
        {
            G2_SetBG3Offset(x, y);
        }
        else
        {
            BgAffineReset(bgConfig, GF_BG_LYR_MAIN_3);
        }
        break;
    case GF_BG_LYR_SUB_0:
        G2S_SetBG0Offset(x, y);
        break;
    case GF_BG_LYR_SUB_1:
        G2S_SetBG1Offset(x, y);
        break;
    case GF_BG_LYR_SUB_2:
        if (bgConfig->bgs[GF_BG_LYR_SUB_2].mode == 0)
        {
            G2S_SetBG2Offset(x, y);
        }
        else
        {
            BgAffineReset(bgConfig, GF_BG_LYR_SUB_2);
        }
        break;
    case GF_BG_LYR_SUB_3:
        if (bgConfig->bgs[GF_BG_LYR_SUB_3].mode == 0)
        {
            G2S_SetBG3Offset(x, y);
        }
        else
        {
            BgAffineReset(bgConfig, GF_BG_LYR_SUB_3);
        }
        break;
    }
}

THUMB_FUNC fx32 Bg_GetXpos(struct BgConfig *bgConfig, u32 bgId)
{
    return bgConfig->bgs[bgId].hOffset;
}

THUMB_FUNC fx32 Bg_GetYpos(struct BgConfig *bgConfig, u32 bgId)
{
    return bgConfig->bgs[bgId].vOffset;
}

THUMB_FUNC void Bg_SetTextDimAndAffineParams(struct BgConfig *bgConfig,
                                             u32 bgId,
                                             u32 txOp,
                                             fx32 txVal,
                                             struct Mtx22 *mtx,
                                             fx32 centerX,
                                             fx32 centerY)
{
    Bg_SetPosText(&bgConfig->bgs[bgId], txOp, txVal);
    SetBgAffine(bgConfig, bgId, mtx, centerX, centerY);
}

THUMB_FUNC void Bg_SetPosText(struct Bg *bg, u32 op, fx32 val)
{
    switch (op)
    {
    case BG_POS_OP_SET_X:
        bg->hOffset = val;
        break;
    case BG_POS_OP_ADD_X:
        bg->hOffset += val;
        break;
    case BG_POS_OP_SUB_X:
        bg->hOffset -= val;
        break;
    case BG_POS_OP_SET_Y:
        bg->vOffset = val;
        break;
    case BG_POS_OP_ADD_Y:
        bg->vOffset += val;
        break;
    case BG_POS_OP_SUB_Y:
        bg->vOffset -= val;
        break;
    }
}

THUMB_FUNC void SetBgAffine(
    struct BgConfig *bgConfig, u32 bgId, struct Mtx22 *mtx, fx32 centerX, fx32 centerY)
{
    switch (bgId)
    {
    case GF_BG_LYR_MAIN_2:
        G2_SetBG2Affine(mtx, centerX, centerY, bgConfig->bgs[bgId].hOffset, bgConfig->bgs[bgId].vOffset);
        break;
    case GF_BG_LYR_MAIN_3:
        G2_SetBG3Affine(mtx, centerX, centerY, bgConfig->bgs[bgId].hOffset, bgConfig->bgs[bgId].vOffset);
        break;
    case GF_BG_LYR_SUB_2:
        G2S_SetBG2Affine(mtx, centerX, centerY, bgConfig->bgs[bgId].hOffset, bgConfig->bgs[bgId].vOffset);
        break;
    case GF_BG_LYR_SUB_3:
        G2S_SetBG3Affine(mtx, centerX, centerY, bgConfig->bgs[bgId].hOffset, bgConfig->bgs[bgId].vOffset);
        break;
    }
}

THUMB_FUNC void BgAffineReset(struct BgConfig *bgConfig, u32 bgId)
{
    struct Mtx22 mtx;
    MTX22_2DAffine(&mtx, 0, FX32_ONE, FX32_ONE, 0);
    SetBgAffine(bgConfig, bgId, &mtx, 0, 0);
}

THUMB_FUNC void CopyOrUncompressTilemapData(const void *src, void *dest, u32 size)
{
    if (size == 0)
    {
        MI_UncompressLZ8(src, dest);
        return;
    }

    if (((u32)src % 4) == 0 && ((u32)dest % 4) == 0 && ((u16)size % 4) == 0)
    {
        MI_CpuCopy32(src, dest, size);
        return;
    }

    MI_CpuCopy16(src, dest, size);
}

THUMB_FUNC void BgCommitTilemapBufferToVram(struct BgConfig *bgConfig, u32 bgId)
{
    BgCopyOrUncompressTilemapBufferRangeToVram(bgConfig,
                                               bgId,
                                               bgConfig->bgs[bgId].tilemapBuffer,
                                               bgConfig->bgs[bgId].bufferSize,
                                               bgConfig->bgs[bgId].baseTile);
}

THUMB_FUNC void BgCopyOrUncompressTilemapBufferRangeToVram(
    struct BgConfig *bgConfig, u32 bgId, u32 *src, u32 size, u32 tileOffset)
{
    if (size == 0)
    {
        void *tilemapBuffer = bgConfig->bgs[bgId].tilemapBuffer;
        if (tilemapBuffer != 0)
        {
            CopyOrUncompressTilemapData(src, tilemapBuffer, size);
            LoadBgVramScr(bgId, tilemapBuffer, bgConfig->bgs[bgId].baseTile * 2, bgConfig->bgs[bgId].bufferSize);
            return;
        }

        u32 uncompSize = src[0] >> 8;
        void *ptr = AllocFromHeapAtEnd(bgConfig->heap_id, uncompSize);
        CopyOrUncompressTilemapData(src, ptr, size);
        LoadBgVramScr(bgId, ptr, tileOffset * 2, uncompSize);
        FreeToHeap(ptr);
        return;
    }

    LoadBgVramScr(bgId, src, tileOffset * 2, size);
}

THUMB_FUNC void LoadBgVramScr(u32 bgId, void *buffer_p, u32 offset, u32 size)
{
    DC_FlushRange(buffer_p, size);

    switch (bgId)
    {
    case 0:
        GX_LoadBG0Scr(buffer_p, offset, size);
        break;
    case 1:
        GX_LoadBG1Scr(buffer_p, offset, size);
        break;
    case 2:
        GX_LoadBG2Scr(buffer_p, offset, size);
        break;
    case 3:
        GX_LoadBG3Scr(buffer_p, offset, size);
        break;
    case 4:
        GXS_LoadBG0Scr(buffer_p, offset, size);
        break;
    case 5:
        GXS_LoadBG1Scr(buffer_p, offset, size);
        break;
    case 6:
        GXS_LoadBG2Scr(buffer_p, offset, size);
        break;
    case 7:
        GXS_LoadBG3Scr(buffer_p, offset, size);
        break;
    }
}

THUMB_FUNC void BG_LoadScreenTilemapData(
    struct BgConfig *bgConfig, u32 bgId, void *src, u32 numTiles)
{
    CopyOrUncompressTilemapData(src, bgConfig->bgs[bgId].tilemapBuffer, numTiles);
}

THUMB_FUNC void BG_LoadCharTilesData(
    struct BgConfig *bgConfig, u32 bgId, u32 *charData, u32 offset, u32 numTiles)
{
    if (bgConfig->bgs[bgId].colorMode == GX_BG_COLORMODE_16)
    {
        BG_LoadCharPixelData(bgConfig, bgId, charData, offset, numTiles << 5);
        return;
    }
    BG_LoadCharPixelData(bgConfig, bgId, charData, offset, numTiles << 6);
}

THUMB_FUNC void BG_LoadCharPixelData(
    struct BgConfig *bgConfig, u32 bgId, u32 *charData, u32 size, u32 offset)
{
    if (size == 0)
    {

        u32 uncompressedSize = charData[0] >> 8;
        void *ptr = AllocFromHeapAtEnd(bgConfig->heap_id, uncompressedSize);
        CopyOrUncompressTilemapData(charData, ptr, size);
        LoadBgVramChar(bgId, ptr, offset, uncompressedSize);
        FreeToHeap(ptr);
        return;
    }

    LoadBgVramChar(bgId, charData, offset, size);
}

THUMB_FUNC void LoadBgVramChar(u32 bgId, void *buffer_p, u32 offset, u32 size)
{
    DC_FlushRange(buffer_p, size);

    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        GX_LoadBG0Char(buffer_p, offset, size);
        break;
    case GF_BG_LYR_MAIN_1:
        GX_LoadBG1Char(buffer_p, offset, size);
        break;
    case GF_BG_LYR_MAIN_2:
        GX_LoadBG2Char(buffer_p, offset, size);
        break;
    case GF_BG_LYR_MAIN_3:
        GX_LoadBG3Char(buffer_p, offset, size);
        break;
    case GF_BG_LYR_SUB_0:
        GXS_LoadBG0Char(buffer_p, offset, size);
        break;
    case GF_BG_LYR_SUB_1:
        GXS_LoadBG1Char(buffer_p, offset, size);
        break;
    case GF_BG_LYR_SUB_2:
        GXS_LoadBG2Char(buffer_p, offset, size);
        break;
    case GF_BG_LYR_SUB_3:
        GXS_LoadBG3Char(buffer_p, offset, size);
        break;
    }
}

THUMB_FUNC void BG_ClearCharDataRange(u32 bgId, u32 size, u32 offset, u32 heap_id)
{
    void *ptr = AllocFromHeapAtEnd(heap_id, size);
    memset(ptr, 0, size);

    LoadBgVramChar(bgId, ptr, offset, size);
    FreeToHeapExplicit(heap_id, ptr);
}

THUMB_FUNC void BG_FillCharDataRange(
    struct BgConfig *param0, u32 bgId, u32 fillValue, u32 count, u32 offset)
{
    void *st4;
    u32 size = count * param0->bgs[bgId].tileSize;
    u32 r5 = fillValue;
    st4 = AllocFromHeapAtEnd(param0->heap_id, size);

    if (param0->bgs[bgId].tileSize == 0x20)
    {
        r5 = (r5 << 0xc | r5 << 0x8 | r5 << 0x4 | r5);
        r5 |= r5 << 0x10;
    }
    else
    {
        r5 = r5 << 0x18 | r5 << 0x10 | r5 << 8 | r5;
    }

    MI_CpuFillFast(st4, r5, size);

    LoadBgVramChar((u8)bgId, st4, param0->bgs[bgId].tileSize * offset, size);
    FreeToHeap(st4);
}

THUMB_FUNC void BG_LoadPlttData(u32 bgId, void *plttData, u32 size, u32 offset)
{
    DC_FlushRange(plttData, size);
    if (bgId < GF_BG_LYR_MAIN_CNT)
    {
        GX_LoadBGPltt(plttData, offset, size);
        return;
    }

    GXS_LoadBGPltt(plttData, offset, size);
}

THUMB_FUNC void BG_SetMaskColor(u32 bgId, u32 value)
{
    BG_LoadPlttData(bgId, &value, 2, 0);
}

THUMB_FUNC u16 GetTileMapIndexFromCoords(u8 x, u8 y, u8 screenSize)
{
    switch (screenSize)
    {
    case GF_BG_SCR_SIZE_128x128:
        return (u16)(x + (y << 4));
    case GF_BG_SCR_SIZE_256x256:
    case GF_BG_SCR_SIZE_256x512:
        return (u16)(x + (y << 5));
    case GF_BG_SCR_SIZE_512x256:
        return (u16)((x & 0x1f) + ((y + (x & ~0x1f)) << 5));
    case GF_BG_SCR_SIZE_512x512:
        u16 res = (u16)(((u16)((x >> 5) + (y >> 5) * 2)) << 10);
        res += (x & 0x1f) + ((y & 0x1f) << 5);
        return res;
    case GF_BG_SCR_SIZE_1024x1024:
        return 0;
    }

    return x;
}

THUMB_FUNC u16 GetSrcTileMapIndexFromCoords(u8 x, u8 y, u8 width, u8 height)
{
    u8 coordType = 0;
    u16 r3 = 0;
    s16 r4 = (s16)(width - 32);
    s16 r5 = (s16)(height - 32);

    if (((u32)x >> 5) != 0)
    {
        coordType++;
    }

    if (((u32)y >> 5) != 0)
    {
        coordType += 2;
    }

    switch (coordType)
    {
    case 0:
        if (r4 >= 0)
        {
            r3 += x + (y << 5);
        }
        else
        {
            r3 += x + y * width;
        }
        break;
    case 1:
        if (r5 >= 0)
        {
            r3 += 0x400;
        }
        else
        {
            r3 += (height << 5);
        }

        r3 += (x & 0x1f) + y * r4;
        break;
    case 2:
        r3 += width << 5;
        if (r4 >= 0)
        {
            r3 += x + ((y & 0x1f) << 5);
        }
        else
        {
            r3 += x + (y & 0x1f) * width;
        }
        break;
    case 3:
        r3 += (width + r5) << 5;
        r3 += (x & 0x1f) + (y & 0x1f) * r4;
        break;
    }

    return r3;
}

THUMB_FUNC void LoadRectToBgTilemapRect(struct BgConfig *bgConfig,
                                        u32 bgId,
                                        void *src,
                                        u8 dstX,
                                        u8 dstY,
                                        u8 width,
                                        u8 height)
{
    CopyToBgTilemapRect(bgConfig, bgId, dstX, dstY, width, height, src, 0, 0, width, height);
}

THUMB_FUNC void CopyToBgTilemapRect(struct BgConfig *bgConfig,
                                    u32 bgId,
                                    u8 dstX,
                                    u8 dstY,
                                    u8 dstWidth,
                                    u8 dstHeight,
                                    void *src,
                                    u8 srcX,
                                    u8 srcY,
                                    u8 srcWidth,
                                    u8 srcHeight)
{
    if (bgConfig->bgs[bgId].mode != 1)
    {
        CopyBgTilemapRectText(&bgConfig->bgs[bgId],
                              dstX,
                              dstY,
                              dstWidth,
                              dstHeight,
                              (u16 *) src,
                              srcX,
                              srcY,
                              srcWidth,
                              srcHeight,
                              0);
    }
    else
    {
        CopyBgTilemapRectAffine(&bgConfig->bgs[bgId],
                                dstX,
                                dstY,
                                dstWidth,
                                dstHeight,
                                (u8 *) src,
                                srcX,
                                srcY,
                                srcWidth,
                                srcHeight,
                                0);
    }
}

THUMB_FUNC void CopyRectToBgTilemapRect(struct BgConfig *bgConfig,
                                    u32 bgId,
                                    u8 dstX,
                                    u8 dstY,
                                    u8 dstWidth,
                                    u8 dstHeight,
                                    void *src,
                                    u8 srcX,
                                    u8 srcY,
                                    u8 srcWidth,
                                    u8 srcHeight)
{
    if (bgConfig->bgs[bgId].mode != 1)
    {
        CopyBgTilemapRectText(&bgConfig->bgs[bgId],
                              dstX,
                              dstY,
                              dstWidth,
                              dstHeight,
                              (u16 *) src,
                              srcX,
                              srcY,
                              srcWidth,
                              srcHeight,
                              TRUE);
    }
    else
    {
        CopyBgTilemapRectAffine(&bgConfig->bgs[bgId],
                                dstX,
                                dstY,
                                dstWidth,
                                dstHeight,
                                (u8 *) src,
                                srcX,
                                srcY,
                                srcWidth,
                                srcHeight,
                                TRUE);
    }
}

THUMB_FUNC void CopyBgTilemapRectText(struct Bg *bg,
                                      u8 dstX,
                                      u8 dstY,
                                      u8 dstWidth,
                                      u8 dstHeight,
                                      u16 *src,
                                      u8 srcX,
                                      u8 srcY,
                                      u8 srcWidth,
                                      u8 srcHeight,
                                      u8 adjustForSrcDims)
{
    u16 *tilemapBuffer = bg->tilemapBuffer;

    if (tilemapBuffer == 0)
    {
        return;
    }

    u8 screenWidth;
    u8 screenHeight;
    GetBgScreenDimensions(bg->size, &screenWidth, &screenHeight);

    u8 i;
    u8 j;
    if (adjustForSrcDims == 0)
    {
        for (i = 0; i < dstHeight; i++)
        {

            if (dstY + i >= screenHeight)
            {
                break;
            }

            if (srcY + i >= srcHeight)
            {
                break;
            }

            for (j = 0; j < dstWidth; j++)
            {

                if (dstX + j >= screenWidth)
                {
                    break;
                }

                if (srcX + j >= srcWidth)
                {
                    break;
                }

                ((u16 *)tilemapBuffer)[GetTileMapIndexFromCoords((u8) (dstX + j), (u8) (dstY + i), bg->size)] =
                    src[srcX + srcWidth * (srcY + i) + j];
            }
        }
    }
    else
    {
        for (i = 0; i < dstHeight; i++)
        {

            if (dstY + i >= screenHeight)
            {
                break;
            }

            if (srcY + i >= srcHeight)
            {
                break;
            }

            for (j = 0; j < dstWidth; j++)
            {

                if (dstX + j >= screenWidth)
                {
                    break;
                }

                if (srcX + j >= srcWidth)
                {
                    break;
                }

                ((u16 *)tilemapBuffer)[GetTileMapIndexFromCoords((u8) (dstX + j), (u8) (dstY + i), bg->size)] =
                    src[GetSrcTileMapIndexFromCoords((u8) (srcX + j), (u8) (srcY + i), srcWidth, srcHeight)];
            }
        }
    }
}

THUMB_FUNC void CopyBgTilemapRectAffine(struct Bg *bg,
                                        u8 dstX,
                                        u8 dstY,
                                        u8 dstWidth,
                                        u8 dstHeight,
                                        u8 *src,
                                        u8 srcX,
                                        u8 srcY,
                                        u8 srcWidth,
                                        u8 srcHeight,
                                        u8 adjustForSrcDims)
{
    void *tilemapBuffer = bg->tilemapBuffer;

    if (tilemapBuffer == 0)
    {
        return;
    }

    u8 screenWidth;
    u8 screenHeight;
    GetBgScreenDimensions(bg->size, &screenWidth, &screenHeight);

    u8 i;
    u8 j;
    if (adjustForSrcDims == 0)
    {
        for (i = 0; i < dstHeight; i++)
        {

            if (dstY + i >= screenHeight)
            {
                break;
            }

            if (srcY + i >= srcHeight)
            {
                break;
            }

            for (j = 0; j < dstWidth; j++)
            {

                if (dstX + j >= screenWidth)
                {
                    break;
                }

                if (srcX + j >= srcWidth)
                {
                    break;
                }

                ((u8 *)tilemapBuffer)[GetTileMapIndexFromCoords((u8) (dstX + j), (u8) (dstY + i), bg->size)] =
                    src[srcX + srcWidth * (srcY + i) + j];
            }
        }
    }
    else
    {
        for (i = 0; i < dstHeight; i++)
        {

            if (dstY + i >= screenHeight)
            {
                break;
            }

            if (srcY + i >= srcHeight)
            {
                break;
            }

            for (j = 0; j < dstWidth; j++)
            {

                if (dstX + j >= screenWidth)
                {
                    break;
                }

                if (srcX + j >= srcWidth)
                {
                    break;
                }

                ((u8 *)tilemapBuffer)[GetTileMapIndexFromCoords((u8) (dstX + j), (u8) (dstY + i), bg->size)] =
                    src[GetSrcTileMapIndexFromCoords((u8) (srcX + j), (u8) (srcY + i), srcWidth, srcHeight)];
            }
        }
    }
}

THUMB_FUNC void FillBgTilemapRect(struct BgConfig *bgConfig,
                                  u8 bgId,
                                  u16 fillValue,
                                  u8 x,
                                  u8 y,
                                  u8 width,
                                  u8 height,
                                  u8 paletteNum)
{
    if (bgConfig->bgs[bgId].mode != 1)
    {

        FillBgTilemapRectText(&bgConfig->bgs[bgId], fillValue, x, y, width, height, paletteNum);
    }
    else
    {
        FillBgTilemapRectAffine(&bgConfig->bgs[bgId], (u8) fillValue, x, y, width, height);
    }
}

THUMB_FUNC void FillBgTilemapRectText(struct Bg *bg,
                                                u16 fillValue,
                                                u8 x,
                                                u8 y,
                                                u8 width,
                                                u8 height,
                                                u8 paletteNum)
{
    void *tilemapBuffer = bg->tilemapBuffer;

    if (tilemapBuffer != 0)
    {

        u8 screenWidth;
        u8 screenHeight;
        GetBgScreenDimensions(bg->size, &screenWidth, &screenHeight);

        u8 i;
        u8 j;
        for (i = y; i < y + height; i++)
        {
            if (i >= screenHeight)
            {
                break;
            }

            for (j = x; j < x + width; j++)
            {
                if (j >= screenWidth)
                {
                    break;
                }

                u16 idx = GetTileMapIndexFromCoords(j, i, bg->size);

                if (paletteNum == 0x11)
                {
                    ((u16 *)tilemapBuffer)[idx] = fillValue;
                }
                else if (paletteNum == 0x10)
                {
                    ((u16 *)tilemapBuffer)[idx] = (u16)((((u16 *)tilemapBuffer)[idx] & 0xF000) + fillValue);
                }
                else
                {
                    ((u16 *)tilemapBuffer)[idx] = (u16)((paletteNum << 0xc) + fillValue);
                }
            }
        }
    }
}

THUMB_FUNC void FillBgTilemapRectAffine(
    struct Bg *bg, u8 fillValue, u8 x, u8 y, u8 width, u8 height)
{
    void *tilemapBuffer = bg->tilemapBuffer;

    if (tilemapBuffer != 0)
    {

        u8 screenWidth;
        u8 screenHeight;
        GetBgScreenDimensions(bg->size, &screenWidth, &screenHeight);

        u8 i;
        u8 j;
        for (i = y; i < y + height; i++)
        {
            if (i >= screenHeight)
            {
                break;
            }

            for (j = x; j < x + width; j++)
            {
                if (j >= screenWidth)
                {
                    break;
                }

                ((u8 *)tilemapBuffer)[GetTileMapIndexFromCoords(j, i, bg->size)] = fillValue;
            }
        }
    }
}

THUMB_FUNC void BgTilemapRectChangePalette(struct BgConfig *bgConfig,
                                           u32 bgId,
                                           u8 x,
                                           u8 y,
                                           u8 width,
                                           u8 height,
                                           u8 paletteNum)
{
    void *tilemapBuffer = bgConfig->bgs[bgId].tilemapBuffer;

    if (tilemapBuffer != NULL)
    {
        u8 screenWidth;
        u8 screenHeight;
        GetBgScreenDimensions(bgConfig->bgs[bgId].size, &screenWidth, &screenHeight);

        u8 i;
        u8 j;
        for (i = y; i < y + height; i++)
        {
            if (i >= screenHeight)
            {
                break;
            }

            for (j = x; j < x + width; j++)
            {
                if (j >= screenWidth)
                {
                    break;
                }

                u16 idx = GetTileMapIndexFromCoords(j, i, bgConfig->bgs[bgId].size);
                ((u16 *)tilemapBuffer)[idx] = (u16)((((u16 *)tilemapBuffer)[idx] & 0xfff) | (paletteNum << 0xc));
            }
        }
    }
}

THUMB_FUNC void BgClearTilemapBufferAndCommit(struct BgConfig *bgConfig, u32 bgId)
{
    if (bgConfig->bgs[bgId].tilemapBuffer != NULL)
    {
        MI_CpuClear16(bgConfig->bgs[bgId].tilemapBuffer, bgConfig->bgs[bgId].bufferSize);
        BgCommitTilemapBufferToVram(bgConfig, bgId);
    }
}

THUMB_FUNC void BgFillTilemapBufferAndCommit(struct BgConfig *bgConfig, u32 bgId, u16 fillValue)
{
    if (bgConfig->bgs[bgId].tilemapBuffer != NULL)
    {
        MI_CpuFill16(bgConfig->bgs[bgId].tilemapBuffer, fillValue, bgConfig->bgs[bgId].bufferSize);
        BgCommitTilemapBufferToVram(bgConfig, bgId);
    }
}

THUMB_FUNC void BgFillTilemapBufferAndSchedule(struct BgConfig *bgConfig, u32 bgId, u16 fillValue)
{
    if (bgConfig->bgs[bgId].tilemapBuffer != NULL)
    {
        MI_CpuFill16(bgConfig->bgs[bgId].tilemapBuffer, fillValue, bgConfig->bgs[bgId].bufferSize);
        ScheduleBgTilemapBufferTransfer(bgConfig, bgId);
    }
}

THUMB_FUNC void *BgGetCharPtr(u32 bgId)
{
    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        return G2_GetBG0CharPtr();
    case GF_BG_LYR_MAIN_1:
        return G2_GetBG1CharPtr();
    case GF_BG_LYR_MAIN_2:
        return G2_GetBG2CharPtr();
    case GF_BG_LYR_MAIN_3:
        return G2_GetBG3CharPtr();
    case GF_BG_LYR_SUB_0:
        return G2S_GetBG0CharPtr();
    case GF_BG_LYR_SUB_1:
        return G2S_GetBG1CharPtr();
    case GF_BG_LYR_SUB_2:
        return G2S_GetBG2CharPtr();
    case GF_BG_LYR_SUB_3:
        return G2S_GetBG3CharPtr();
    }

    return NULL;
}

THUMB_FUNC void Convert4bppTo8bppInternal(u8 *src4bpp, u32 size, u8 (*dest8bpp), u8 paletteNum)
{
    paletteNum <<= 4;
    for (u32 i = 0; i < size; i++)
    {
        dest8bpp[i * 2 + 0] = (u8)(src4bpp[i] & 0xf);
        if (dest8bpp[i * 2 + 0] != 0)
        {
            dest8bpp[i * 2 + 0] += paletteNum;
        }

        dest8bpp[i * 2 + 1] = (u8)((src4bpp[i] >> 4) & 0xf);
        if (dest8bpp[i * 2 + 1] != 0)
        {
            dest8bpp[i * 2 + 1] += paletteNum;
        }
    }
}

THUMB_FUNC u8 *Convert4bppTo8bpp(u8 *src4Bpp, u32 size, u8 paletteNum, u32 heap_id)
{
    u8 *ptr = (u8*)AllocFromHeap(heap_id, size * 2);

    Convert4bppTo8bppInternal(src4Bpp, size, ptr, paletteNum);

    return ptr;
}

THUMB_FUNC void *GetBgTilemapBuffer(struct BgConfig *bgConfig, u8 bgId)
{
    return bgConfig->bgs[bgId].tilemapBuffer;
}

THUMB_FUNC u16 GetBgAffineRotation(struct BgConfig *bgConfig, u32 bgId)
{
    return bgConfig->bgs[bgId].rotation;
}

THUMB_FUNC u8 GetBgPriority(struct BgConfig *bgConfig, u32 bgId)
{
    switch (bgId)
    {
    case GF_BG_LYR_MAIN_0:
        return G2_GetBG0Control().priority;
    case GF_BG_LYR_MAIN_1:
        return G2_GetBG1Control().priority;
    case GF_BG_LYR_MAIN_2:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            return G2_GetBG2ControlText().priority;
        case GF_BG_TYPE_AFFINE:
            return G2_GetBG2ControlAffine().priority;
        case GF_BG_TYPE_256x16PLTT:
            return G2_GetBG2Control256x16Pltt().priority;
        }
        break;
    case GF_BG_LYR_MAIN_3:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            return G2_GetBG3ControlText().priority;
        case GF_BG_TYPE_AFFINE:
            return G2_GetBG3ControlAffine().priority;
        case GF_BG_TYPE_256x16PLTT:
            return G2_GetBG3Control256x16Pltt().priority;
        }
        break;

    case GF_BG_LYR_SUB_0:
        return G2S_GetBG0Control().priority;
    case GF_BG_LYR_SUB_1:
        return G2S_GetBG1Control().priority;

    case GF_BG_LYR_SUB_2:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            return G2S_GetBG2ControlText().priority;
        case GF_BG_TYPE_AFFINE:
            return G2S_GetBG2ControlAffine().priority;
        case GF_BG_TYPE_256x16PLTT:
            return G2S_GetBG2Control256x16Pltt().priority;
        }
        break;
    case GF_BG_LYR_SUB_3:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case GF_BG_TYPE_TEXT:
            return G2S_GetBG3ControlText().priority;
        case GF_BG_TYPE_AFFINE:
            return G2S_GetBG3ControlAffine().priority;
        case GF_BG_TYPE_256x16PLTT:
            return G2S_GetBG3Control256x16Pltt().priority;
        }
        break;
    }

    return 0;
}

// TODO: Utilize these three macros below. They are already used in CopyGlyphToWindow.
#define GetPixelAddressFromBlit4bpp(ptr, x, y, width) ((u8 *)((ptr) + (((x) >> 1) & 3) + (((x) << 2) & 0x3FE0) + ((((y) << 2) & 0x3FE0) * (width)) + (((u32)(((y) << 2) & 0x1C)))))
#define GetPixelAddressFromBlit8bpp(ptr, x, y, width) ((u8 *)((ptr) + ((x) & 7) + (((x) << 3) & 0x7FC0) + ((((y) << 3) & 0x7FC0) * (width)) + (((u32)(((y) << 3) & 0x38)))))

#define ConvertPixelsToTiles(x)    (((x) + ((x) & 7)) >> 3)

THUMB_FUNC void BlitBitmapRect4Bit(const struct Bitmap *src,
                                   const struct Bitmap *dst,
                                   u16 srcX,
                                   u16 srcY,
                                   u16 dstX,
                                   u16 dstY,
                                   u16 width,
                                   u16 height,
                                   u16 colorKey)
{
    int xEnd, yEnd;
    int multiplierSrcY, multiplierDstY;
    int loopSrcY, loopDstY;
    int loopSrcX, loopDstX;
    int toOrr, toShift;
    u8 * pixelsSrc, * pixelsDst;

    if (dst->width - dstX < width)
        xEnd = dst->width - dstX + srcX;
    else
        xEnd = width + srcX;
    if (dst->height - dstY < height)
        yEnd = dst->height - dstY + srcY;
    else
        yEnd = height + srcY;
    multiplierSrcY = (src->width + (src->width & 7)) >> 3;
    multiplierDstY = (dst->width + (dst->width & 7)) >> 3;

    if (colorKey == 0xFFFF)
    {
        for (loopSrcY = srcY, loopDstY = dstY; loopSrcY < yEnd; loopSrcY++, loopDstY++)
        {
            for (loopSrcX = srcX, loopDstX = dstX; loopSrcX < xEnd; loopSrcX++, loopDstX++)
            {
                pixelsSrc = (u8 *)(src->pixels + ((loopSrcX >> 1) & 3) + ((loopSrcX << 2) & 0x3FE0) + (((loopSrcY << 2) & 0x3FE0) * multiplierSrcY) + (((loopSrcY << 2) & 0x1C)));
                pixelsDst = (u8 *)(dst->pixels + ((loopDstX >> 1) & 3) + ((loopDstX << 2) & 0x3FE0) + (((loopDstY << 2) & 0x3FE0) * multiplierDstY) + (((loopDstY << 2) & 0x1C)));

                toOrr = (*pixelsSrc >> ((loopSrcX & 1) * 4)) & 0xF;
                toShift = (loopDstX & 1) * 4;
                *pixelsDst = ((toOrr << toShift) | (*pixelsDst & (0xF0 >> toShift)));
            }
        }
    }
    else
    {
        for (loopSrcY = srcY, loopDstY = dstY; loopSrcY < yEnd; loopSrcY++, loopDstY++)
        {
            for (loopSrcX = srcX, loopDstX = dstX; loopSrcX < xEnd; loopSrcX++, loopDstX++)
            {
                pixelsSrc = (u8 *)(src->pixels + ((loopSrcX >> 1) & 3) + ((loopSrcX << 2) & 0x3FE0) + (((loopSrcY << 2) & 0x3FE0) * multiplierSrcY) + ((u32)((loopSrcY << 2) & 0x1C)));
                pixelsDst = (u8 *)(dst->pixels + ((loopDstX >> 1) & 3) + ((loopDstX << 2) & 0x3FE0) + (((loopDstY << 2) & 0x3FE0) * multiplierDstY) + ((u32)((loopDstY << 2) & 0x1C)));

                toOrr = (*pixelsSrc >> ((loopSrcX & 1) * 4)) & 0xF;
                if (toOrr != colorKey)
                {
                    toShift = (loopDstX & 1) * 4;
                    *pixelsDst = (u8) ((toOrr << toShift) | (*pixelsDst & (0xF0 >> toShift)));
                }
            }
        }
    }
}

THUMB_FUNC void BlitBitmapRect8Bit(const struct Bitmap *src,
                                   const struct Bitmap *dst,
                                   u16 srcX,
                                   u16 srcY,
                                   u16 dstX,
                                   u16 dstY,
                                   u16 width,
                                   u16 height,
                                   u16 colorKey)
{
    int xEnd, yEnd;
    int multiplierSrcY, multiplierDstY;
    int loopSrcY, loopDstY;
    int loopSrcX, loopDstX;
    u8 * pixelsSrc, * pixelsDst;

    if (dst->width - dstX < width)
        xEnd = dst->width - dstX + srcX;
    else
        xEnd = width + srcX;
    if (dst->height - dstY < height)
        yEnd = dst->height - dstY + srcY;
    else
        yEnd = height + srcY;
    multiplierSrcY = (src->width + (src->width & 7)) >> 3;
    multiplierDstY = (dst->width + (dst->width & 7)) >> 3;

    if (colorKey == 0xFFFF)
    {
        for (loopSrcY = srcY, loopDstY = dstY; loopSrcY < yEnd; loopSrcY++, loopDstY++)
        {
            for (loopSrcX = srcX, loopDstX = dstX; loopSrcX < xEnd; loopSrcX++, loopDstX++)
            {
                pixelsSrc = (u8 *)(src->pixels + ((loopSrcX >> 0) & 7) + ((loopSrcX << 3) & 0x7FC0) + (((loopSrcY << 3) & 0x7FC0) * multiplierSrcY) + (((loopSrcY << 3) & 0x38)));
                pixelsDst = (u8 *)(dst->pixels + ((loopDstX >> 0) & 7) + ((loopDstX << 3) & 0x7FC0) + (((loopDstY << 3) & 0x7FC0) * multiplierDstY) + (((loopDstY << 3) & 0x38)));

                *pixelsDst = *pixelsSrc;
            }
        }
    }
    else
    {
        for (loopSrcY = srcY, loopDstY = dstY; loopSrcY < yEnd; loopSrcY++, loopDstY++)
        {
            for (loopSrcX = srcX, loopDstX = dstX; loopSrcX < xEnd; loopSrcX++, loopDstX++)
            {
                pixelsSrc = (u8 *)(src->pixels + ((loopSrcX >> 0) & 7) + ((loopSrcX << 3) & 0x7FC0) + (((loopSrcY << 3) & 0x7FC0) * multiplierSrcY) + (((loopSrcY << 3) & 0x38)));
                pixelsDst = (u8 *)(dst->pixels + ((loopDstX >> 0) & 7) + ((loopDstX << 3) & 0x7FC0) + (((loopDstY << 3) & 0x7FC0) * multiplierDstY) + (((loopDstY << 3) & 0x38)));

                if (*pixelsSrc != colorKey)
                    *pixelsDst = *pixelsSrc;
            }
        }
    }
}

THUMB_FUNC void FillBitmapRect4Bit(
    struct Bitmap *surface, u16 x, u16 y, u16 width, u16 height, u8 fillValue)
{

    int r6 = x + width;
    if (r6 > surface->width)
    {
        r6 = surface->width;
    }

    int r12 = y + height;
    if (r12 > surface->height)
    {
        r12 = surface->height;
    }

    int lr = (((surface->width) + (surface->width & 7)) >> 3);

    for (int i = y; i < r12; i++)
    {

        for (int j = x; j < r6; j++)
        {

            u8 *unk = (u8 *)((u8 *)surface->pixels + ((j >> 1) & 3) + ((j << 2) & 0x3fe0) +
                             (((i << 2) & 0x3fe0) * lr) + ((i << 2) & 0x1c));

            if ((j & 1) != 0)
            {
                *unk &= 0xf;
                *unk |= (fillValue << 4);
            }
            else
            {
                *unk &= 0xf0;
                *unk |= fillValue;
            }
        }
    }
}

THUMB_FUNC void FillBitmapRect8Bit(
    struct Bitmap *surface, u16 x, u16 y, u16 width, u16 height, u8 fillValue)
{

    int r6 = x + width;
    if (r6 > surface->width)
    {
        r6 = surface->width;
    }

    int r12 = y + height;
    if (r12 > surface->height)
    {
        r12 = surface->height;
    }

    int lr = (((surface->width) + (surface->width & 7)) >> 3);

    for (int i = y; i < r12; i++)
    {

        for (int j = x; j < r6; j++)
        {

            u8 *unk = (u8 *)((u8 *)surface->pixels + (j & 7) + ((j << 3) & 0x7fc0) +
                             (((i << 3) & 0x7fc0) * lr) + ((i << 3) & 0x38));

            *unk = fillValue;
        }
    }
}

THUMB_FUNC struct Window *AllocWindows(u32 heap_id, s32 size)
{
    struct Window *ptr = AllocFromHeap(heap_id, (u32)(size << 4));

    for (u16 i = 0; i < size; i++)
    {
        InitWindow(&ptr[i]);
    }

    return ptr;
}

THUMB_FUNC void InitWindow(struct Window *window)
{
    window->bgConfig = NULL;
    window->bgId = GF_BG_LYR_UNALLOC;
    window->tilemapLeft = 0;
    window->tilemapTop = 0;
    window->width = 0;
    window->height = 0;
    window->paletteNum = 0;

    window->baseTile = 0;
    window->pixelBuffer = NULL;

    window->colorMode = GF_BG_CLR_4BPP;
}

THUMB_FUNC BOOL WindowIsInUse(struct Window *window)
{
    if (window->bgConfig == NULL || window->bgId == 0xff || window->pixelBuffer == NULL)
    {
        return FALSE;
    }

    return TRUE;
}

THUMB_FUNC void AddWindowParameterized(struct BgConfig *param0,
                                       struct Window *window,
                                       u8 bgId,
                                       u8 tilemapLeft,
                                       u8 tilemapTop,
                                       u8 width,
                                       u8 height,
                                       u8 paletteNum,
                                       u16 baseTile)
{
    if (param0->bgs[bgId].tilemapBuffer == NULL)
    {
        return;
    }

    void *ptr = AllocFromHeap(param0->heap_id, (u32)(width * height * param0->bgs[bgId].tileSize));

    if (ptr == NULL)
    {
        return;
    }
    window->bgConfig = param0;
    window->bgId = bgId;
    window->tilemapLeft = tilemapLeft;
    window->tilemapTop = tilemapTop;
    window->width = width;
    window->height = height;
    window->paletteNum = paletteNum;

    window->baseTile = baseTile;
    window->pixelBuffer = ptr;

    window->colorMode = param0->bgs[bgId].colorMode == GX_BG_COLORMODE_16 ? GF_BG_CLR_4BPP : GF_BG_CLR_8BPP;
}

THUMB_FUNC void AddTextWindowTopLeftCorner(struct BgConfig *param0,
                                           struct Window *window,
                                           u8 width,
                                           u8 height,
                                           u16 baseTile,
                                           u8 paletteNum)
{
    u32 size = (u32)(width * height * 32);

    void *ptr = AllocFromHeap(param0->heap_id, size);

    paletteNum |= (paletteNum * 16);
    memset(ptr, paletteNum, size);

    if (ptr != NULL)
    {
        window->bgConfig = param0;
        window->width = width;
        window->height = height;
        window->baseTile = baseTile;
        window->pixelBuffer = ptr;
        window->colorMode = GF_BG_CLR_4BPP;
    }
}

THUMB_FUNC void AddWindow(
    struct BgConfig *bgConfig, struct Window *window, const struct WindowTemplate *template)
{

    AddWindowParameterized(bgConfig,
                           window,
                           template->bgId,
                           template->tilemapLeft,
                           template->tilemapTop,
                           template->width,
                           template->height,
                           template->paletteNum,
                           template->baseTile);
}

THUMB_FUNC void RemoveWindow(struct Window *window)
{
    FreeToHeap(window->pixelBuffer);

    window->bgConfig = NULL;
    window->bgId = 0xff;
    window->tilemapLeft = 0;
    window->tilemapTop = 0;
    window->width = 0;
    window->height = 0;
    window->paletteNum = 0;
    window->baseTile = 0;
    window->pixelBuffer = NULL;
}

THUMB_FUNC void WindowArray_dtor(struct Window *windows, int count)
{
    for (u16 i = 0; i < count; i++)
    {
        if (windows[i].pixelBuffer != NULL)
        {
            FreeToHeap(windows[i].pixelBuffer);
        }
    }

    FreeToHeap(windows);
}

THUMB_FUNC void CopyWindowToVram(struct Window *window)
{

    GF_ASSERT(window != NULL);
    GF_ASSERT(window->bgConfig != NULL);
    GF_ASSERT(window->bgId < NELEMS(window->bgConfig->bgs));
    GF_ASSERT(window->bgConfig->bgs[window->bgId].mode < NELEMS(sCopyWindowToVramFuncs));

    sCopyWindowToVramFuncs[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void ScheduleWindowCopyToVram(struct Window *window)
{

    GF_ASSERT(window);
    GF_ASSERT(window->bgConfig);
    GF_ASSERT(window->bgId < NELEMS(window->bgConfig->bgs));
    GF_ASSERT(window->bgConfig->bgs[window->bgId].mode < NELEMS(sScheduleWindowCopyToVramFuncs));

    sScheduleWindowCopyToVramFuncs[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void PutWindowTilemap(struct Window *window)
{
    sPutWindowTilemapFuncs[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void PutWindowTilemapRectAnchoredTopLeft(struct Window *window, u8 width, u8 height)
{
    u8 widthBak = window->width;
    u8 heightBak = window->height;

    window->width = width;
    window->height = height;
    sPutWindowTilemapFuncs[window->bgConfig->bgs[window->bgId].mode](window);

    window->width = widthBak;
    window->height = heightBak;
}

THUMB_FUNC void ClearWindowTilemap(struct Window *window)
{
    sClearWindowTilemapFuncs[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void PutWindowTilemap_TextMode(struct Window *param0)
{
    u32 i, j;
    u32 r3;
    u32 iCount, jCount;
    u16 *st4 = param0->bgConfig->bgs[param0->bgId].tilemapBuffer;

    if (st4 == NULL)
    {
        return;
    }

    r3 = param0->baseTile;
    jCount = (u32)(param0->tilemapLeft + param0->width);
    iCount = (u32)(param0->tilemapTop + param0->height);

    for (i = param0->tilemapTop; i < iCount; i++)
    {
        for (j = param0->tilemapLeft; j < jCount; j++)
        {
            st4[((i & 0x20) * 32) + ((j & 0x20) * 32) + ((i & 0x1f) << 5) + (j & 0x1f)] =
                (u16)(r3 | (param0->paletteNum << 12));

            r3++;
        }
    }
}

THUMB_FUNC void PutWindowTilemap_AffineMode(struct Window *window)
{
    int j, i;
    u8 *dst;

    int tileId;
    int tilemapWidth;

    if (window->bgConfig->bgs[window->bgId].tilemapBuffer == NULL)
    {
        return;
    }

    tilemapWidth = sTilemapWidthByBufferSize[window->bgConfig->bgs[window->bgId].size];

    dst = window->bgConfig->bgs[window->bgId].tilemapBuffer + window->tilemapTop * tilemapWidth + window->tilemapLeft;
    tileId = window->baseTile;

    for (i = 0; i < window->height; i++)
    {
        for (j = 0; j < window->width; j++)
        {
            dst[j] = (u8)tileId;
            tileId++;
        }
        dst += tilemapWidth;
    }
}

THUMB_FUNC void ClearWindowTilemapText(struct Window *window)
{

    u32 i, j;

    u32 yEnd, xEnd;
    u32 tilemapWidth;

    u16 *dst;

    if (window->bgConfig->bgs[window->bgId].tilemapBuffer == NULL)
    {
        return;
    }
    dst = window->bgConfig->bgs[window->bgId].tilemapBuffer;

    tilemapWidth = sTilemapWidthByBufferSize[window->bgConfig->bgs[window->bgId].size];
    xEnd = (u32)(window->tilemapLeft + window->width);
    yEnd = (u32)(window->tilemapTop + window->height);

    for (i = window->tilemapTop; i < yEnd; i++)
    {
        for (j = window->tilemapLeft; j < xEnd; j++)
        {
            dst[((i & 0x20) * 32) + ((j & 0x20) * 32) + ((i & 0x1f) * tilemapWidth) + (j & 0x1f)] = 0;
        }
    }
}

THUMB_FUNC void ClearWindowTilemapAffine(struct Window *window)
{

    int j, i;
    u8 *dstPos;

    int tilemapWidth;

    if (window->bgConfig->bgs[window->bgId].tilemapBuffer == NULL)
    {
        return;
    }

    tilemapWidth = sTilemapWidthByBufferSize[window->bgConfig->bgs[window->bgId].size];
    dstPos = window->bgConfig->bgs[window->bgId].tilemapBuffer + window->tilemapTop * tilemapWidth + window->tilemapLeft;

    for (i = 0; i < window->height; i++)
    {
        for (j = 0; j < window->width; j++)
        {
            dstPos[j] = 0;
        }
        dstPos += tilemapWidth;
    }
}

THUMB_FUNC void CopyWindowToVram_TextMode(struct Window *window)
{
    PutWindowTilemap_TextMode(window);
    CopyWindowPixelsToVram_TextMode(window);
    BgCopyOrUncompressTilemapBufferRangeToVram(window->bgConfig,
                                               window->bgId,
                                               window->bgConfig->bgs[window->bgId].tilemapBuffer,
                                               window->bgConfig->bgs[window->bgId].bufferSize,
                                               window->bgConfig->bgs[window->bgId].baseTile);
}

THUMB_FUNC void ScheduleWindowCopyToVram_TextMode(struct Window *window)
{
    PutWindowTilemap_TextMode(window);
    ScheduleBgTilemapBufferTransfer(window->bgConfig, window->bgId);
    CopyWindowPixelsToVram_TextMode(window);
}

THUMB_FUNC void CopyWindowToVram_AffineMode(struct Window *window)
{
    PutWindowTilemap_AffineMode(window);
    BgCopyOrUncompressTilemapBufferRangeToVram(window->bgConfig,
                                               window->bgId,
                                               window->bgConfig->bgs[window->bgId].tilemapBuffer,
                                               window->bgConfig->bgs[window->bgId].bufferSize,
                                               window->bgConfig->bgs[window->bgId].baseTile);

    BG_LoadCharTilesData(window->bgConfig,
        window->bgId,
        window->pixelBuffer,
        (u32)(window->width * window->height * 64),
        window->baseTile);
}

THUMB_FUNC void ScheduleWindowCopyToVram_AffineMode(struct Window *window)
{
    PutWindowTilemap_AffineMode(window);
    ScheduleBgTilemapBufferTransfer(window->bgConfig, window->bgId);
    BG_LoadCharTilesData(window->bgConfig,
        window->bgId,
        window->pixelBuffer,
        (u32)(window->width * window->height * 64),
        window->baseTile);
}

THUMB_FUNC void CopyWindowPixelsToVram_TextMode(struct Window *window)
{
    BG_LoadCharTilesData(window->bgConfig,
        window->bgId,
        window->pixelBuffer,
        (u32)(window->width * window->height * window->bgConfig->bgs[window->bgId].tileSize),
        window->baseTile);
}

THUMB_FUNC void ClearWindowTilemapAndCopyToVram(struct Window *window)
{
    sClearWindowTilemapAndCopyToVramFuncs[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void ClearWindowTilemapAndScheduleTransfer(struct Window *window)
{
    sClearWindowTilemapAndScheduleTransferFuncs[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void ClearWindowTilemapAndCopyToVram_TextMode(struct Window *window)
{
    ClearWindowTilemapText(window);
    BgCopyOrUncompressTilemapBufferRangeToVram(window->bgConfig,
                                               window->bgId,
                                               window->bgConfig->bgs[window->bgId].tilemapBuffer,
                                               window->bgConfig->bgs[window->bgId].bufferSize,
                                               window->bgConfig->bgs[window->bgId].baseTile);
}

THUMB_FUNC void ClearWindowTilemapAndScheduleTransfer_TextMode(struct Window *window)
{
    ClearWindowTilemapText(window);
    ScheduleBgTilemapBufferTransfer(window->bgConfig, window->bgId);
}

THUMB_FUNC void ClearWindowTilemapAndCopyToVram_AffineMode(struct Window *window)
{
    ClearWindowTilemapAffine(window);
    BgCopyOrUncompressTilemapBufferRangeToVram(window->bgConfig,
                                               window->bgId,
                                               window->bgConfig->bgs[window->bgId].tilemapBuffer,
                                               window->bgConfig->bgs[window->bgId].bufferSize,
                                               window->bgConfig->bgs[window->bgId].baseTile);
}

THUMB_FUNC void ClearWindowTilemapAndScheduleTransfer_AffineMode(struct Window *window)
{
    ClearWindowTilemapAffine(window);
    ScheduleBgTilemapBufferTransfer(window->bgConfig, window->bgId);
}

THUMB_FUNC void FillWindowPixelBuffer(struct Window *window, u8 param1)
{
    if (window->bgConfig->bgs[window->bgId].tileSize == 0x20)
    {
        param1 |= param1 << 4;
    }

    MI_CpuFillFast(
        window->pixelBuffer,
        (u32)((param1 << 0x18) | (param1 << 0x10) | (param1 << 0x8) | param1),
    (u32)(window->bgConfig->bgs[window->bgId].tileSize * window->width * window->height));
}

THUMB_FUNC void BlitBitmapRectToWindow(struct Window *window,
    const void *src,
    u16 srcX,
    u16 srcY,
    u16 srcWidth,
    u16 srcHeight,
    u16 dstX,
    u16 dstY,
    u16 dstWidth,
    u16 dstHeight)
{
    BlitBitmapRect(
        window, src, srcX, srcY, srcWidth, srcHeight, dstX, dstY, dstWidth, dstHeight, 0);
}

THUMB_FUNC void BlitBitmapRect(struct Window *window,
    void *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8,
    u16 param9,
    u16 param10)
{
    struct Bitmap st1c = { param1, param4, param5 };
    struct Bitmap st14 = {
        window->pixelBuffer, (u16)(window->width << 3), (u16)(window->height << 3)
    };

    if (window->bgConfig->bgs[window->bgId].colorMode == GX_BG_COLORMODE_16)
    {
        BlitBitmapRect4Bit(&st1c, &st14, param2, param3, param6, param7, param8, param9, param10);
    }
    else
    {
        BlitBitmapRect8Bit(&st1c, &st14, param2, param3, param6, param7, param8, param9, param10);
    }
}

THUMB_FUNC void FillWindowPixelRect(
    struct Window *window, u8 fillValue, u16 x, u16 y, u16 width, u16 height)
{
    struct Bitmap st8 = {
        window->pixelBuffer, (u16)(window->width << 3), (u16)(window->height << 3)
    };

    if (window->bgConfig->bgs[window->bgId].colorMode == GX_BG_COLORMODE_16)
    {
        FillBitmapRect4Bit(&st8, x, y, width, height, fillValue);
    }
    else
    {
        FillBitmapRect8Bit(&st8, x, y, width, height, fillValue);
    }
}

#define GLYPH_COPY_4BPP(glyphPixels, srcX, srcY, srcWidth, srcHeight, windowPixels, destX, destY, destWidth, table) { \
    int srcJ, dstJ, srcI, dstI, bits;                                                                                 \
    u8 toOrr;                                                                                                         \
    u8 tableFlag;                                                                                                     \
    u8 tableBit;                                                                                                      \
    u8 *dest;                                                                                                         \
    const u8 *src;                                                                                                    \
    u32 pixelData;                                                                                                    \
                                                                                                                      \
    src = glyphPixels + (srcY / 8 * 64) + (srcX / 8 * 32);                                                            \
    if (srcY == 0) {                                                                                                  \
        dstI = destY + srcY;                                                                                          \
        tableBit = table & 0xFF;                                                                                      \
    } else {                                                                                                          \
        dstI = destY + srcY;                                                                                          \
        for (srcI = 0; srcI < 8; srcI++) {                                                                            \
            if (((table >> srcI) & 1) != 0) {                                                                         \
                dstI++;                                                                                               \
            }                                                                                                         \
        }                                                                                                             \
        tableBit = table >> 8;                                                                                        \
    }                                                                                                                 \
    for (srcI = 0; srcI < srcHeight; srcI++) {                                                                        \
        pixelData = *(u32 *)src;                                                                                      \
        tableFlag = (tableBit >> srcI) & 1;                                                                           \
        for (srcJ = 0, dstJ = destX + srcX; srcJ < srcWidth; srcJ++, dstJ++) {                                        \
            dest = GetPixelAddressFromBlit4bpp(windowPixels, dstJ, dstI, destWidth);                                  \
            toOrr = (pixelData >> (srcJ * 4)) & 0xF;                                                                  \
            if (toOrr != 0) {                                                                                         \
                bits = (dstJ & 1) * 4;                                                                                \
                toOrr = (toOrr << bits) | (*dest & (0xF0 >> bits));                                                   \
                *dest = toOrr;                                                                                        \
                if (tableFlag) {                                                                                      \
                    dest = GetPixelAddressFromBlit4bpp(windowPixels, dstJ, dstI + 1, destWidth);                      \
                    *dest = toOrr;                                                                                    \
                }                                                                                                     \
            }                                                                                                         \
        }                                                                                                             \
        if (tableFlag) {                                                                                              \
            dstI += 2;                                                                                                \
        } else {                                                                                                      \
            dstI += 1;                                                                                                \
        }                                                                                                             \
        src += 4;                                                                                                     \
    }                                                                                                                 \
}

#define GLYPH_COPY_8BPP(glyphPixels, srcX, srcY, srcWidth, srcHeight, windowPixels, destX, destY, destWidth, table) { \
    int srcJ, dstJ, srcI, dstI;                                                                                       \
    u8 toOrr;                                                                                                         \
    u8 tableFlag;                                                                                                     \
    u8 tableBit;                                                                                                      \
    u8 *dest;                                                                                                         \
    const u8 *src;                                                                                                    \
    u8 *pixelData;                                                                                                    \
                                                                                                                      \
    src = glyphPixels + (srcY / 8 * 128) + (srcX / 8 * 64);                                                           \
    if (srcY == 0) {                                                                                                  \
        dstI = destY + srcY;                                                                                          \
        tableBit = table & 0xFF;                                                                                      \
    } else {                                                                                                          \
        dstI = destY + srcY;                                                                                          \
        for (srcI = 0; srcI < 8; srcI++) {                                                                            \
            if (((table >> srcI) & 1) != 0) {                                                                         \
                dstI++;                                                                                               \
            }                                                                                                         \
        }                                                                                                             \
        tableBit = table >> 8;                                                                                        \
    }                                                                                                                 \
    for (srcI = 0; srcI < srcHeight; srcI++) {                                                                        \
        pixelData = (u8 *)src;                                                                                        \
        tableFlag = (tableBit >> srcI) & 1;                                                                           \
        for (srcJ = 0, dstJ = destX + srcX; srcJ < srcWidth; srcJ++, dstJ++) {                                        \
            dest = GetPixelAddressFromBlit8bpp(windowPixels, dstJ, dstI, destWidth);                                  \
            toOrr = pixelData[srcJ];                                                                                  \
            if (toOrr != 0) {                                                                                         \
                *dest = toOrr;                                                                                        \
                if (tableFlag) {                                                                                      \
                    dest = GetPixelAddressFromBlit8bpp(windowPixels, dstJ, dstI + 1, destWidth);                      \
                    *dest = toOrr;                                                                                    \
                }                                                                                                     \
            }                                                                                                         \
        }                                                                                                             \
        if (tableFlag) {                                                                                              \
            dstI += 2;                                                                                                \
        } else {                                                                                                      \
            dstI += 1;                                                                                                \
        }                                                                                                             \
        src += 8;                                                                                                     \
    }                                                                                                                 \
}

THUMB_FUNC void CopyGlyphToWindow(struct Window *window, u8 *glyphPixels, u16 srcWidth, u16 srcHeight, u16 dstX, u16 dstY, u16 table) {
    u8 *windowPixels;
    u16 destWidth, destHeight;
    int srcRight, srcBottom;
    u8 glyphSizeParam;

    windowPixels = (u8 *)window->pixelBuffer;
    destWidth = (u16)(window->width * 8);
    destHeight = (u16)(window->height * 8);

    // Don't overflow the window
    if (destWidth - dstX < srcWidth) {
        srcRight = destWidth - dstX;
    } else {
        srcRight = srcWidth;
    }
    if (destHeight - dstY < srcHeight) {
        srcBottom = destHeight - dstY;
    } else {
        srcBottom = srcHeight;
    }

    // Get the max glyph dimensions
    // Default: 1x1
    glyphSizeParam = 0;
    if (srcRight > 8) {
        glyphSizeParam |= 1; // 2 wide
    }
    if (srcBottom > 8) {
        glyphSizeParam |= 2; // 2 high
    }

    if (window->colorMode == GF_BG_CLR_4BPP) {
        switch (glyphSizeParam) {
        case 0: // 1x1
        GLYPH_COPY_4BPP(glyphPixels, 0, 0, srcRight, srcBottom, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            return;
        case 1: // 2x1
        GLYPH_COPY_4BPP(glyphPixels, 0, 0, 8, srcBottom, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_4BPP(glyphPixels, 8, 0, srcRight - 8, srcBottom, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            return;
        case 2: // 1x2
        GLYPH_COPY_4BPP(glyphPixels, 0, 0, srcRight, 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_4BPP(glyphPixels, 0, 8, srcRight, srcBottom - 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            return;
        case 3: // 2x2
        GLYPH_COPY_4BPP(glyphPixels, 0, 0, 8, 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_4BPP(glyphPixels, 8, 0, srcRight - 8, 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_4BPP(glyphPixels, 0, 8, 8, srcBottom - 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_4BPP(glyphPixels, 8, 8, srcRight - 8, srcBottom - 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            return;
        }
    } else { // 8bpp
        u8 *convertedSrc;
        convertedSrc = Convert4bppTo8bpp(glyphPixels, srcWidth * 4 * srcHeight * 8, window->paletteNum, window->bgConfig->heap_id);
        switch (glyphSizeParam) {
        case 0: // 1x1
        GLYPH_COPY_8BPP(convertedSrc, 0, 0, srcRight, srcBottom, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            break;
        case 1: // 2x1
        GLYPH_COPY_8BPP(convertedSrc, 0, 0, 8, srcBottom, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_8BPP(convertedSrc, 8, 0, srcRight - 8, srcBottom, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            break;
        case 2: // 1x2
        GLYPH_COPY_8BPP(convertedSrc, 0, 0, srcRight, 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_8BPP(convertedSrc, 0, 8, srcRight, srcBottom - 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            break;
        case 3: // 2x2
        GLYPH_COPY_8BPP(convertedSrc, 0, 0, 8, 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_8BPP(convertedSrc, 8, 0, srcRight - 8, 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_8BPP(convertedSrc, 0, 8, 8, srcBottom - 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            GLYPH_COPY_8BPP(convertedSrc, 8, 8, srcRight - 8, srcBottom - 8, windowPixels, dstX, dstY, ConvertPixelsToTiles(destWidth), table);
            break;
        }
        FreeToHeap(convertedSrc);
    }
}

THUMB_FUNC void ScrollWindow(struct Window *window, u32 param1, u8 param2, u8 param3)
{
    if (window->bgConfig->bgs[window->bgId].colorMode == GX_BG_COLORMODE_16)
    {
        ScrollWindow4bpp(window, param1, param2, param3);
    }
    else
    {
        ScrollWindow8bpp(window, param1, param2, param3);
    }
}

THUMB_FUNC void ScrollWindow4bpp(struct Window *window, u32 param1, u8 param2, u8 fillValue)
{
    void *r2;
    int r5, r1, r3;
    int st4, stc;
    u32 st8;
    int i, j;

    r2 = window->pixelBuffer;
    st4 = (fillValue << 0x18) | (fillValue << 0x10) | (fillValue << 0x8) | fillValue;
    stc = window->height * window->width * 32;
    st8 = window->width;

    switch (param1)
    {
    case 0:
        for (i = 0; i < stc; i += 32)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                r5 = i + (j << 2);
                r1 = i + (int)(((st8 * (r3 & ~7)) | (r3 & 7)) << 2);

                if (r1 < stc)
                {
                    *(u32 *)(r2 + r5) = *(u32 *)(r2 + r1);
                }
                else
                {
                    *(u32 *)(r2 + r5) = (u32)st4;
                }

                r3++;
            }
        }

        break;
    case 1:
        r2 += stc - 4;
        for (i = 0; i < stc; i += 32)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                r5 = i + (j << 2);
                r1 = i + (int)(((st8 * (r3 & ~7)) | (r3 & 7)) << 2);

                if (r1 < stc)
                {
                    *(u32 *)(r2 - r5) = *(u32 *)(r2 - r1);
                }
                else
                {
                    *(u32 *)(r2 - r5) = (u32)st4;
                }

                r3++;
            }
        }

        break;
    case 2:
    case 3:
        break;
    }
}

THUMB_FUNC void ScrollWindow8bpp(struct Window *window, u32 param1, u8 param2, u8 fillValue)
{

    void *pixelBuffer;
    int dstOffs, srcOffs, r3;
    int st4, size;
    u32 srcWidth;
    int i, j;

    pixelBuffer = (u8 *)window->pixelBuffer;
    st4 = (fillValue << 0x18) | (fillValue << 0x10) | (fillValue << 0x8) | fillValue;
    size = window->height * window->width * 64;
    srcWidth = window->width;

    switch (param1)
    {
    case 0:
        for (i = 0; i < size; i += 64)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                dstOffs = i + (j << 3);
                srcOffs = i + (int)(((srcWidth * (r3 & ~7)) | (r3 & 7)) << 3);

                if (srcOffs < size)
                {
                    *(u32 *)(pixelBuffer + dstOffs) = *(u32 *)(pixelBuffer + srcOffs);
                }
                else
                {
                    *(u32 *)(pixelBuffer + dstOffs) = (u32)st4;
                }

                dstOffs += 4;
                srcOffs += 4;
                if (srcOffs < size + 4)
                {
                    *(u32 *)(pixelBuffer + dstOffs) = *(u32 *)(pixelBuffer + srcOffs);
                }
                else
                {
                    *(u32 *)(pixelBuffer + dstOffs) = (u32)st4;
                }

                r3++;
            }
        }

        break;
    case 1:
        pixelBuffer += size - 8;
        for (i = 0; i < size; i += 64)
        {
            r3 = param2;
            for (j = 0; j < 8; j++)
            {
                dstOffs = i + (j << 3);
                srcOffs = i + (int)(((srcWidth * (r3 & ~7)) | (r3 & 7)) << 3);

                if (srcOffs < size)
                {
                    *(u32 *)(pixelBuffer - dstOffs) = *(u32 *)(pixelBuffer - srcOffs);
                }
                else
                {
                    *(u32 *)(pixelBuffer - dstOffs) = (u32)st4;
                }

                dstOffs -= 4;
                srcOffs -= 4;
                if (srcOffs < size - 4)
                {
                    *(u32 *)(pixelBuffer - dstOffs) = *(u32 *)(pixelBuffer - srcOffs);
                }
                else
                {
                    *(u32 *)(pixelBuffer - dstOffs) = (u32)st4;
                }

                r3++;
            }
        }

        break;
    case 2:
    case 3:
        break;
    }
}

THUMB_FUNC u8 GetWindowBgId(struct Window *window)
{
    return window->bgId;
}

THUMB_FUNC u8 GetWindowWidth(struct Window *window)
{
    return window->width;
}
THUMB_FUNC u8 GetWindowHeight(struct Window *window)
{
    return window->height;
}
THUMB_FUNC u8 GetWindowX(struct Window *window)
{
    return window->tilemapLeft;
}
THUMB_FUNC u8 GetWindowY(struct Window *window)
{
    return window->tilemapTop;
}
THUMB_FUNC void MoveWindowX(struct Window *window, u8 x)
{
    window->tilemapLeft = x;
}
THUMB_FUNC void MoveWindowY(struct Window *window, u8 y)
{
    window->tilemapTop = y;
}
THUMB_FUNC void SetWindowPaletteNum(struct Window *window, u8 paletteNum)
{
    window->paletteNum = paletteNum;
}

THUMB_FUNC NNSG2dCharacterData * LoadCharacterDataFromFile(void **char_ret, u32 heap_id, const char *path)
{
    void *ptr = AllocAndReadFile(heap_id, path);
    *char_ret = ptr;
    NNSG2dCharacterData *st0;
    NNS_G2dGetUnpackedBGCharacterData(ptr, &st0);

    return st0;
}

THUMB_FUNC NNSG2dPaletteData * LoadPaletteDataFromFile(void **pltt_ret, u32 heap_id, const char *path)
{
    void *ptr = AllocAndReadFile(heap_id, path);
    *pltt_ret = ptr;
    NNSG2dPaletteData *st0;
    NNS_G2dGetUnpackedPaletteData(ptr, &st0);

    return st0;
}

THUMB_FUNC void DoScheduledBgGpuUpdates(struct BgConfig *bgConfig)
{
    ApplyScheduledBgPosUpdate(bgConfig);
    DoScheduledBgTilemapBufferTransfers(bgConfig);

    bgConfig->scrollScheduled = 0;
    bgConfig->bufferTransferScheduled = 0;
}

THUMB_FUNC void DoScheduledBgTilemapBufferTransfers(struct BgConfig *bgConfig)
{
    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_MAIN_0)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_MAIN_0, bgConfig->bgs[GF_BG_LYR_MAIN_0].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_MAIN_0].baseTile * 2, bgConfig->bgs[GF_BG_LYR_MAIN_0].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_MAIN_1)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_MAIN_1, bgConfig->bgs[GF_BG_LYR_MAIN_1].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_MAIN_1].baseTile * 2, bgConfig->bgs[GF_BG_LYR_MAIN_1].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_MAIN_2)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_MAIN_2, bgConfig->bgs[GF_BG_LYR_MAIN_2].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_MAIN_2].baseTile * 2, bgConfig->bgs[GF_BG_LYR_MAIN_2].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_MAIN_3)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_MAIN_3, bgConfig->bgs[GF_BG_LYR_MAIN_3].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_MAIN_3].baseTile * 2, bgConfig->bgs[GF_BG_LYR_MAIN_3].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_SUB_0)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_SUB_0, bgConfig->bgs[GF_BG_LYR_SUB_0].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_SUB_0].baseTile * 2, bgConfig->bgs[GF_BG_LYR_SUB_0].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_SUB_1)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_SUB_1, bgConfig->bgs[GF_BG_LYR_SUB_1].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_SUB_1].baseTile * 2, bgConfig->bgs[GF_BG_LYR_SUB_1].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_SUB_2)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_SUB_2, bgConfig->bgs[GF_BG_LYR_SUB_2].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_SUB_2].baseTile * 2, bgConfig->bgs[GF_BG_LYR_SUB_2].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & (1 << GF_BG_LYR_SUB_3)) != 0)
    {
        LoadBgVramScr(GF_BG_LYR_SUB_3, bgConfig->bgs[GF_BG_LYR_SUB_3].tilemapBuffer, bgConfig->bgs[GF_BG_LYR_SUB_3].baseTile * 2, bgConfig->bgs[GF_BG_LYR_SUB_3].bufferSize);
    }
}

THUMB_FUNC void ScheduleBgTilemapBufferTransfer(struct BgConfig *bgConfig, u32 bgId)
{
    bgConfig->bufferTransferScheduled |= 1 << bgId;
}

THUMB_FUNC void ApplyScheduledBgPosUpdate(struct BgConfig *bgConfig)
{
    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_MAIN_0)) != 0)
    {
        G2_SetBG0Offset(bgConfig->bgs[GF_BG_LYR_MAIN_0].hOffset, bgConfig->bgs[GF_BG_LYR_MAIN_0].vOffset);
    }

    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_MAIN_1)) != 0)
    {
        G2_SetBG1Offset(bgConfig->bgs[GF_BG_LYR_MAIN_1].hOffset, bgConfig->bgs[GF_BG_LYR_MAIN_1].vOffset);
    }

    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_MAIN_2)) != 0)
    {
        if (bgConfig->bgs[GF_BG_LYR_MAIN_2].mode == 0)
        {
            G2_SetBG2Offset(bgConfig->bgs[GF_BG_LYR_MAIN_2].hOffset, bgConfig->bgs[GF_BG_LYR_MAIN_2].vOffset);
        }
        else
        {
            struct Mtx22 st38;
            MTX22_2DAffine(
                &st38, bgConfig->bgs[GF_BG_LYR_MAIN_2].rotation, bgConfig->bgs[GF_BG_LYR_MAIN_2].xScale, bgConfig->bgs[GF_BG_LYR_MAIN_2].yScale, 2);
            G2_SetBG2Affine(
                &st38,
                bgConfig->bgs[GF_BG_LYR_MAIN_2].centerX,
                bgConfig->bgs[GF_BG_LYR_MAIN_2].centerY,
                bgConfig->bgs[GF_BG_LYR_MAIN_2].hOffset,
                bgConfig->bgs[GF_BG_LYR_MAIN_2].vOffset);
        }
    }

    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_MAIN_3)) != 0)
    {
        if (bgConfig->bgs[GF_BG_LYR_MAIN_3].mode == 0)
        {
            G2_SetBG3Offset(bgConfig->bgs[GF_BG_LYR_MAIN_3].hOffset, bgConfig->bgs[GF_BG_LYR_MAIN_3].vOffset);
        }
        else
        {
            struct Mtx22 st28;
            MTX22_2DAffine(
                &st28, bgConfig->bgs[GF_BG_LYR_MAIN_3].rotation, bgConfig->bgs[GF_BG_LYR_MAIN_3].xScale, bgConfig->bgs[GF_BG_LYR_MAIN_3].yScale, 2);
            G2_SetBG3Affine(
                &st28,
                bgConfig->bgs[GF_BG_LYR_MAIN_3].centerX,
                bgConfig->bgs[GF_BG_LYR_MAIN_3].centerY,
                bgConfig->bgs[GF_BG_LYR_MAIN_3].hOffset,
                bgConfig->bgs[GF_BG_LYR_MAIN_3].vOffset);
        }
    }

    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_SUB_0)) != 0)
    {
        G2S_SetBG0Offset(bgConfig->bgs[GF_BG_LYR_SUB_0].hOffset, bgConfig->bgs[GF_BG_LYR_SUB_0].vOffset);
    }

    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_SUB_1)) != 0)
    {
        G2S_SetBG1Offset(bgConfig->bgs[GF_BG_LYR_SUB_1].hOffset, bgConfig->bgs[GF_BG_LYR_SUB_1].vOffset);
    }

    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_SUB_2)) != 0)
    {
        if (bgConfig->bgs[GF_BG_LYR_SUB_2].mode == 0)
        {
            G2S_SetBG2Offset(bgConfig->bgs[GF_BG_LYR_SUB_2].hOffset, bgConfig->bgs[GF_BG_LYR_SUB_2].vOffset);
        }
        else
        {
            struct Mtx22 st18;
            MTX22_2DAffine(
                &st18, bgConfig->bgs[GF_BG_LYR_SUB_2].rotation, bgConfig->bgs[GF_BG_LYR_SUB_2].xScale, bgConfig->bgs[GF_BG_LYR_SUB_2].yScale, 2);
            G2S_SetBG2Affine(
                &st18,
                bgConfig->bgs[GF_BG_LYR_SUB_2].centerX,
                bgConfig->bgs[GF_BG_LYR_SUB_2].centerY,
                bgConfig->bgs[GF_BG_LYR_SUB_2].hOffset,
                bgConfig->bgs[GF_BG_LYR_SUB_2].vOffset);
        }
    }

    if ((bgConfig->scrollScheduled & (1 << GF_BG_LYR_SUB_3)) != 0)
    {
        if (bgConfig->bgs[GF_BG_LYR_SUB_3].mode == 0)
        {
            G2S_SetBG3Offset(bgConfig->bgs[GF_BG_LYR_SUB_3].hOffset, bgConfig->bgs[GF_BG_LYR_SUB_3].vOffset);
        }
        else
        {
            struct Mtx22 st08;
            MTX22_2DAffine(
                &st08, bgConfig->bgs[GF_BG_LYR_SUB_3].rotation, bgConfig->bgs[GF_BG_LYR_SUB_3].xScale, bgConfig->bgs[GF_BG_LYR_SUB_3].yScale, 2);
            G2S_SetBG3Affine(
                &st08,
                bgConfig->bgs[GF_BG_LYR_SUB_3].centerX,
                bgConfig->bgs[GF_BG_LYR_SUB_3].centerY,
                bgConfig->bgs[GF_BG_LYR_SUB_3].hOffset,
                bgConfig->bgs[GF_BG_LYR_SUB_3].vOffset);
        }
    }
}

THUMB_FUNC void ScheduleSetBgPosText(
    struct BgConfig *bgConfig, u32 bgId, u32 op, fx32 value)
{
    Bg_SetPosText(&bgConfig->bgs[bgId], op, value);
    bgConfig->scrollScheduled |= 1 << bgId;
}

THUMB_FUNC void ScheduleSetBgAffineRotation(
    struct BgConfig *bgConfig, u32 bgId, u32 op, u16 value)
{
    Bg_SetAffineRotation(&bgConfig->bgs[bgId], op, value);
    bgConfig->scrollScheduled |= 1 << bgId;
}

THUMB_FUNC void Bg_SetAffineRotation(struct Bg *bg, u32 op, u16 val)
{
    switch (op)
    {
    case BG_POS_OP_SET_ROT:
        bg->rotation = val;
        break;
    case BG_POS_OP_ADD_ROT:
        bg->rotation += val;
        break;
    case BG_POS_OP_SUB_ROT:
        bg->rotation -= val;
        break;
    }
}

THUMB_FUNC void ScheduleSetBgAffinePos(
    struct BgConfig *bgConfig, u32 bgId, u32 op, fx32 value)
{
    Bg_SetAffinePos(&bgConfig->bgs[bgId], op, value);
    bgConfig->scrollScheduled |= 1 << bgId;
}

THUMB_FUNC void Bg_SetAffinePos(struct Bg *bg, u32 op, fx32 val)
{
    switch (op)
    {
    case BG_POS_OP_SET_CENTERX:
        bg->centerX = val;
        break;
    case BG_POS_OP_ADD_CENTERX:
        bg->centerX += val;
        break;
    case BG_POS_OP_SUB_CENTERX:
        bg->centerX -= val;
        break;
    case BG_POS_OP_SET_CENTERY:
        bg->centerY = val;
        break;
    case BG_POS_OP_ADD_CENTERY:
        bg->centerY += val;
        break;
    case BG_POS_OP_SUB_CENTERY:
        bg->centerY -= val;
        break;
    }
}

THUMB_FUNC u32 DoesPixelAtScreenXYMatchPtrVal(
    struct BgConfig *bgConfig, u8 bgId, u8 x, u8 y, u16 *src)
{
    void *bgCharPtr;
    u16 tilemapIdx;
    u8 xPixOffs;
    u8 yPixOffs;
    u8 pixelValue;
    u8 i;

    if (bgConfig->bgs[bgId].tilemapBuffer == NULL)
    {
        return 0;
    }

    tilemapIdx = GetTileMapIndexFromCoords((u8) (x >> 3), (u8) (y >> 3), bgConfig->bgs[bgId].size);
    bgCharPtr = BgGetCharPtr(bgId);

    xPixOffs = (u8)(x & 7);
    yPixOffs = (u8)(y & 7);

    if (bgConfig->bgs[bgId].colorMode == GX_BG_COLORMODE_16)
    {
        u16 *tilemapBuffer = bgConfig->bgs[bgId].tilemapBuffer;
        u8 *ptr = AllocFromHeapAtEnd(bgConfig->heap_id, 0x40);

        bgCharPtr += ((tilemapBuffer[tilemapIdx] & 0x3ff) << 5);
        for (i = 0; i < 0x20; i++)
        {
            ptr[(i << 1)] = (u8)(((u8 *)bgCharPtr)[i] & 0xf);
            ptr[(i << 1) + 1] = (u8)(((u8 *)bgCharPtr)[i] >> 4);
        }

        ApplyFlipFlagsToTile(bgConfig, (u8)((tilemapBuffer[tilemapIdx] >> 0xa) & 3), ptr);

        pixelValue = ptr[xPixOffs + (yPixOffs << 3)];
        FreeToHeap(ptr);

        if ((src[0] & (1 << pixelValue)) != 0)
        {
            return 1;
        }
    }
    else
    {
        if (bgConfig->bgs[bgId].mode != GF_BG_TYPE_AFFINE)
        {
            u16 *tilemapBuffer = bgConfig->bgs[bgId].tilemapBuffer;
            u8 *ptr = AllocFromHeapAtEnd(bgConfig->heap_id, 0x40);

            memcpy(ptr, bgCharPtr + ((tilemapBuffer[tilemapIdx] & 0x3ff) << 6), 0x40);

            ApplyFlipFlagsToTile(bgConfig, (u8)((tilemapBuffer[tilemapIdx] >> 0xa) & 3), ptr);

            pixelValue = ptr[xPixOffs + (yPixOffs << 3)];
            FreeToHeap(ptr);
        }
        else
        {
            pixelValue = ((u8 *)bgCharPtr)[(((u8 *)bgConfig->bgs[bgId].tilemapBuffer)[tilemapIdx] << 6) + xPixOffs + (yPixOffs << 3)];
        }

        // BUG: Infinite loop
        while (TRUE)
        {
            if (src[0] == 0xffff)
            {
                break;
            }
            if (pixelValue == (u8)(src[0]))
            {
                return 1;
            }
        }
    }
    return 0;
}

THUMB_FUNC void ApplyFlipFlagsToTile(struct BgConfig *bgConfig, u8 flag, u8 *src)
{
    u8 i, j;
    if (flag != 0)
    {
        u8 *ptr = AllocFromHeapAtEnd(bgConfig->heap_id, 0x40);

        if ((flag & 1) != 0)
        {
            for (i = 0; i < 8; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    ptr[i * 8 + j] = src[i * 8 + (7 - j)];
                }
            }

            memcpy(src, ptr, 0x40);
        }

        if ((flag & 2) != 0)
        {
            for (i = 0; i < 8; i++)
            {
                u8 *r3 = &ptr[i * 8];
                u8 *r2 = &src[(7 - i) * 8];
                for (u32 j = 8; j > 0; j--)
                {
                    *r3++ = *r2++;
                }
            }

            memcpy(src, ptr, 0x40);
        }

        FreeToHeap(ptr);
    }
}
