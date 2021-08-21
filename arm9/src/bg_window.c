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

#ifdef NONMATCHING
THUMB_FUNC void CopyGlyphToWindow(
    struct Window *window, u32 *param1, u32 param2, u32 param3, u16 param4, u16 param5, u32 param6)
{
    u32 str330 = param6;
    u32 *st0 = param1;
    u16 st5c = param4;

    void *st278 = window->unk0c;
    u16 st58 = window->width << 3;

    int st8 = st58 - st5c;

    if (st8 >= param2)
    {
        st8 = param2;
    }

    int st4 = (u16)(window->height << 3) - param5;
    u16 st48 = param5;

    if (st4 >= param3)
    {
        st4 = param3;
    }

    u8 r4 = 0;
    if (st8 > 8)
    {
        r4 |= 1;
    }

    if (st4 > 8)
    {
        r4 |= 2;
    }

    if (window->unk0b_15 == 0)
    {
        switch (r4)
        {
        case 0:
            u8 st70 = param6;
            for (u32 st274 = 0; st274 < st4; st274++)
            {
                u32 st6c = (st58 + (st58 & 7)) >> 3;

                u32 st26c = st0[0];
                u8 st270 = (u8)((st70 >> st274) & 1);
                u32 r2 = st5c;

                for (u32 r1 = 0; r1 < st8; r1++)
                {
                    u32 r3 = st5c << 2;
                    u32 st68 = ((st48 << 2) & 0x3fe0) * st6c;
                    u32 r7 = (st48 << 2) & 0x1c;
                    u32 st64 = (((st48 + 1) << 2) & 0x3fe0) * st6c;
                    u32 st60 = ((st48 + 1) << 2) & 0x1c;
                    u32 r4 = r1;

                    void *st27c = st278 + ((r2 >> 1) & 3) + (r3 & 0x3fe0);
                    u8 *r0 = st27c + st68;

                    u8 r5 = (u8)((st26c >> r4) & 0xf);
                    if (r5 != 0)
                    {
                        u32 st280 = (r5 << ((r2 & 1) << 2));
                        u32 st284 = r0[r7];

                        u8 r5 = ((0xf0 >> ((r2 & 1) << 2)) & st284) | st280;
                        r0[r7] = r5;

                        if (st270 != 0)
                        {
                            *(u8 *)(st27c + st64 + st60) = r5;
                        }
                    }

                    r4 += 4;
                    r3 += 4;
                    r2 += 1;
                }

                if (st270 != 0)
                {
                    st48 += 2;
                }
                else
                {
                    st48++;
                }

                st0++;
            }

            break;

        case 1:
            u32 *st25c = st0;
            u32 st264 = st48;
            u8 st54 = param6;
            u8 st84 = param6;

            for (u32 st268 = 0; st268 < st4; st268++)
            {
                u32 st80 = (st58 + (st58 & 7)) >> 3;

                u32 st258 = *st25c;
                u32 r2 = st5c;
                u8 st260 = (st84 >> st268) & 1;
                u32 r3 = st5c << 2;
                u32 st7c = ((st264 << 2) & 0x3fe0) * st80;
                u32 r7 = (st264 << 2) & 0x1c;
                u32 st78 = (((st264 + 1) << 2) & 0x3fe0) * st80;
                u32 st74 = ((st264 + 1) << 2) & 0x1c;
                u32 r4 = 0;

                for (u32 r1 = 0; r1 < 8; r1++)
                {
                    void *st288 = st278 + ((r2 >> 1) & 3) + (r3 & 0x3fe0);
                    u8 *r0 = st288 + st7c;
                    u8 r5 = (st258 >> r4) & 0xf;
                    if (r5 != 0)
                    {
                        u32 st28c = r5 << ((r2 & 1) << 2);
                        u32 st290 = r0[r7];
                        u8 r5 = ((0xf0 >> ((r2 & 1) << 2)) & st290) | st28c;
                        r0[r7] = r5;

                        if (st260 != 0)
                        {
                            *(u8 *)(st288 + st78 + st74) = r5;
                        }
                    }

                    r4 += 4;
                    r3 += 4;
                    r2++;
                }

                if (st260 != 0)
                {
                    st264 += 2;
                }
                else
                {
                    st264++;
                }

                st25c++;
            }

            st0 += 0x20;
            u8 st98 = st54;

            for (u32 st254 = 0; st254 < st4; st254++)
            {
                st5c += 8;
                u32 st94 = (st58 + (st58 & 7)) >> 3;

                //_02019A00
            }

            break;

        case 2:
            // TODO
            break;
        case 3:
            // TODO
            break;
        }
    }
    else
    {
        // TODO: _0201A12C
    }
}
#else
asm void CopyGlyphToWindow(
    struct Window *window, const char *param1, u16 param2, u16 param3, u16 param4, u16 param5, u16 param6)
{
    // clang-format off
	push {r4-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x118
	add r5, r0, #0x0
	ldr r0, [sp, #0x330]
	str r1, [sp, #0x0]
	str r0, [sp, #0x330]
	add r1, sp, #0x318
	ldrh r1, [r1, #0x10]
	ldr r0, [r5, #0xc]
	str r1, [sp, #0x5c]
	ldrb r1, [r5, #0x7]
	str r0, [sp, #0x278]
	ldrb r0, [r5, #0x8]
	lsl r1, r1, #0x13
	lsr r4, r1, #0x10
	ldr r1, [sp, #0x5c]
	lsl r0, r0, #0x13
	sub r1, r4, r1
	lsr r0, r0, #0x10
	str r4, [sp, #0x58]
	str r1, [sp, #0x8]
	cmp r1, r2
	blt _0201977E
	str r2, [sp, #0x8]
_0201977E:
	add r1, sp, #0x318
	ldrh r1, [r1, #0x14]
	sub r0, r0, r1
	str r1, [sp, #0x48]
	str r0, [sp, #0x4]
	cmp r0, r3
	blt _0201978E
	str r3, [sp, #0x4]
_0201978E:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	cmp r0, #0x8
	ble _0201979E
	mov r0, #0x1
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0201979E:
	ldr r0, [sp, #0x4]
	cmp r0, #0x8
	ble _020197AC
	mov r0, #0x2
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_020197AC:
	ldrh r0, [r5, #0xa]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1f
	beq _020197B8
	bl _0201A12C
_020197B8:
	cmp r4, #0x3
	bls _020197C0
	bl _0201A8BC
_020197C0:
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020197CC:
	lsl r6, r0, #0
	lsl r0, r1, #4
	lsl r0, r3, #12
	lsl r0, r7, #20
	// jump table (using 16-bit offset)
	// .short _020197D4 - _020197CC - 2; case 0
	// .short _020198D6 - _020197CC - 2; case 1
	// .short _02019AE6 - _020197CC - 2; case 2
	// .short _02019D06 - _020197CC - 2; case 3
_020197D4:
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x70]
	mov r0, #0x0
	str r0, [sp, #0x274]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bgt _020197EA
	bl _0201A8BC
_020197EA:
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x6c]
_020197F6:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x70]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x26c]
	ldr r0, [sp, #0x274]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x270]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _020198AA
	ble _020198AA
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x6c]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x68]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x6c]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x64]
	str r0, [sp, #0x60]
_02019848:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x68]
	str r5, [sp, #0x27c]
	add r0, r5, r0
	ldr r5, [sp, #0x26c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _0201989C
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x280]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x284]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x284]
	and r6, r5
	ldr r5, [sp, #0x280]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x270]
	cmp r0, #0x0
	beq _0201989C
	ldr r6, [sp, #0x27c]
	ldr r0, [sp, #0x64]
	add r6, r6, r0
	ldr r0, [sp, #0x60]
	strb r5, [r0, r6]
_0201989C:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019848
_020198AA:
	ldr r0, [sp, #0x270]
	cmp r0, #0x0
	beq _020198B8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _020198BE
_020198B8:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_020198BE:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x274]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x274]
	cmp r1, r0
	blt _020197F6
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_020198D6:
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x25c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x264]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x54]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x84]
	mov r0, #0x0
	str r0, [sp, #0x268]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _020199D2
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x80]
_02019902:
	ldr r0, [sp, #0x25c]
	ldr r1, [sp, #0x84]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x258]
	ldr r0, [sp, #0x268]
	ldr r6, [sp, #0x80]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x260]
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x264]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x264]
	str r6, [sp, #0x7c]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x80]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x78]
	str r0, [sp, #0x74]
_0201994C:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x7c]
	str r5, [sp, #0x288]
	add r0, r5, r0
	ldr r5, [sp, #0x258]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _020199A0
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x28c]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x290]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x290]
	and r6, r5
	ldr r5, [sp, #0x28c]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x260]
	cmp r0, #0x0
	beq _020199A0
	ldr r6, [sp, #0x288]
	ldr r0, [sp, #0x78]
	add r6, r6, r0
	ldr r0, [sp, #0x74]
	strb r5, [r0, r6]
_020199A0:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _0201994C
	ldr r0, [sp, #0x260]
	cmp r0, #0x0
	beq _020199BA
	ldr r0, [sp, #0x264]
	add r0, r0, #0x2
	str r0, [sp, #0x264]
	b _020199C0
_020199BA:
	ldr r0, [sp, #0x264]
	add r0, r0, #0x1
	str r0, [sp, #0x264]
_020199C0:
	ldr r0, [sp, #0x25c]
	add r0, r0, #0x4
	str r0, [sp, #0x25c]
	ldr r0, [sp, #0x268]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x268]
	cmp r1, r0
	blt _02019902
_020199D2:
	ldr r0, [sp, #0x0]
	add r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x54]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x98]
	mov r0, #0x0
	str r0, [sp, #0x254]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bgt _020199EE
	bl _0201A8BC
_020199EE:
	ldr r0, [sp, #0x5c]
	mov r1, #0x7
	add r0, #0x8
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x94]
_02019A00:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x98]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x24c]
	ldr r0, [sp, #0x254]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x250]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x294]
	sub r0, #0x8
	str r0, [sp, #0x294]
	cmp r0, #0x0
	ble _02019ABA
	ble _02019ABA
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x94]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x90]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x94]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x8c]
	str r0, [sp, #0x88]
_02019A58:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x90]
	str r5, [sp, #0x298]
	add r0, r5, r0
	ldr r5, [sp, #0x24c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019AAC
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x29c]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2a0]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2a0]
	and r6, r5
	ldr r5, [sp, #0x29c]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x250]
	cmp r0, #0x0
	beq _02019AAC
	ldr r6, [sp, #0x298]
	ldr r0, [sp, #0x8c]
	add r6, r6, r0
	ldr r0, [sp, #0x88]
	strb r5, [r0, r6]
_02019AAC:
	ldr r0, [sp, #0x294]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019A58
_02019ABA:
	ldr r0, [sp, #0x250]
	cmp r0, #0x0
	beq _02019AC8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _02019ACE
_02019AC8:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019ACE:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x254]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x254]
	cmp r1, r0
	blt _02019A00
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_02019AE6:
	ldr r0, [sp, #0x0]
	mov r1, #0x7
	str r0, [sp, #0x23c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x244]
	mov r0, #0x0
	str r0, [sp, #0x248]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xa8]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x40]
_02019B06:
	ldr r0, [sp, #0x23c]
	ldr r1, [sp, #0xa8]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x238]
	ldr r0, [sp, #0x248]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x240]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _02019BC2
	ble _02019BC2
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x244]
	ldr r6, [sp, #0x40]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x244]
	str r6, [sp, #0xa4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x40]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xa0]
	str r0, [sp, #0x9c]
_02019B58:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
// 	b _02019B6C
// 	nop
// _02019B68: .word 0x00003FE0
// _02019B6C:
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xa4]
	str r5, [sp, #0x2a4]
	add r0, r5, r0
	ldr r5, [sp, #0x238]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019BB4
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2a8]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2ac]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2ac]
	and r6, r5
	ldr r5, [sp, #0x2a8]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x240]
	cmp r0, #0x0
	beq _02019BB4
	ldr r6, [sp, #0x2a4]
	ldr r0, [sp, #0xa0]
	add r6, r6, r0
	ldr r0, [sp, #0x9c]
	strb r5, [r0, r6]
_02019BB4:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019B58
_02019BC2:
	ldr r0, [sp, #0x240]
	cmp r0, #0x0
	beq _02019BD0
	ldr r0, [sp, #0x244]
	add r0, r0, #0x2
	str r0, [sp, #0x244]
	b _02019BD6
_02019BD0:
	ldr r0, [sp, #0x244]
	add r0, r0, #0x1
	str r0, [sp, #0x244]
_02019BD6:
	ldr r0, [sp, #0x23c]
	add r0, r0, #0x4
	str r0, [sp, #0x23c]
	ldr r0, [sp, #0x248]
	add r0, r0, #0x1
	str r0, [sp, #0x248]
	cmp r0, #0x8
	blt _02019B06
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	add r0, #0x40
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x48]
	mov r1, #0x1
	add r0, #0x8
	str r0, [sp, #0x48]
_02019BF6:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _02019C04
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019C04:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _02019BF6
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xb8]
	mov r0, #0x0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	bgt _02019C24
	bl _0201A8BC
_02019C24:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0xb8]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x230]
	ldr r0, [sp, #0x20]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x234]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _02019CD8
	ble _02019CD8
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x40]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xb4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x40]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xb0]
	str r0, [sp, #0xac]
_02019C76:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xb4]
	str r5, [sp, #0x2b0]
	add r0, r5, r0
	ldr r5, [sp, #0x230]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019CCA
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2b4]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2b8]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2b8]
	and r6, r5
	ldr r5, [sp, #0x2b4]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x234]
	cmp r0, #0x0
	beq _02019CCA
	ldr r6, [sp, #0x2b0]
	ldr r0, [sp, #0xb0]
	add r6, r6, r0
	ldr r0, [sp, #0xac]
	strb r5, [r0, r6]
_02019CCA:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019C76
_02019CD8:
	ldr r0, [sp, #0x234]
	cmp r0, #0x0
	beq _02019CE6
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _02019CEC
_02019CE6:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019CEC:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x20]
	cmp r0, r1
	blt _02019C24
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_02019D06:
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x220]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x228]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x22c]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x38]
_02019D2A:
	ldr r0, [sp, #0x220]
	ldr r1, [sp, #0x3c]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x21c]
	ldr r0, [sp, #0x22c]
	ldr r6, [sp, #0x38]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x224]
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x228]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x228]
	str r6, [sp, #0xc4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	str r3, [sp, #0x34]
	add r4, r1, #0x0
	str r5, [sp, #0xc0]
	str r0, [sp, #0xbc]
_02019D76:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xc4]
	str r5, [sp, #0x2bc]
	add r0, r5, r0
	ldr r5, [sp, #0x21c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019DCA
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2c0]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2c4]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2c4]
	and r6, r5
	ldr r5, [sp, #0x2c0]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x224]
	cmp r0, #0x0
	beq _02019DCA
	ldr r6, [sp, #0x2bc]
	ldr r0, [sp, #0xc0]
	add r6, r6, r0
	ldr r0, [sp, #0xbc]
	strb r5, [r0, r6]
_02019DCA:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _02019D76
	ldr r0, [sp, #0x224]
	cmp r0, #0x0
	beq _02019DE4
	ldr r0, [sp, #0x228]
	add r0, r0, #0x2
	str r0, [sp, #0x228]
	b _02019DEA
_02019DE4:
	ldr r0, [sp, #0x228]
	add r0, r0, #0x1
	str r0, [sp, #0x228]
_02019DEA:
	ldr r0, [sp, #0x220]
	add r0, r0, #0x4
	str r0, [sp, #0x220]
	ldr r0, [sp, #0x22c]
	add r0, r0, #0x1
	str r0, [sp, #0x22c]
	cmp r0, #0x8
	blt _02019D2A
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x20c]
	add r0, #0x20
	str r0, [sp, #0x20c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x214]
	mov r0, #0x0
	str r0, [sp, #0x218]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0xd4]
	add r0, #0x8
	str r0, [sp, #0xd4]
_02019E12:
	ldr r0, [sp, #0x20c]
	ldr r1, [sp, #0x3c]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0xd4]
	str r0, [sp, #0x208]
	ldr r0, [sp, #0x218]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x210]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x2c8]
	sub r0, #0x8
	str r0, [sp, #0x2c8]
	cmp r0, #0x0
	ble _02019ECC
	ble _02019ECC
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x214]
	ldr r6, [sp, #0x38]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x214]
	str r6, [sp, #0xd0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xcc]
	str r0, [sp, #0xc8]
_02019E6A:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xd0]
	str r5, [sp, #0x2cc]
	add r0, r5, r0
	ldr r5, [sp, #0x208]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019EBE
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2d0]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2d4]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2d4]
	and r6, r5
	ldr r5, [sp, #0x2d0]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x210]
	cmp r0, #0x0
	beq _02019EBE
	ldr r6, [sp, #0x2cc]
	ldr r0, [sp, #0xcc]
	add r6, r6, r0
	ldr r0, [sp, #0xc8]
	strb r5, [r0, r6]
_02019EBE:
	ldr r0, [sp, #0x2c8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019E6A
_02019ECC:
	ldr r0, [sp, #0x210]
	cmp r0, #0x0
	beq _02019EDA
	ldr r0, [sp, #0x214]
	add r0, r0, #0x2
	str r0, [sp, #0x214]
	b _02019EE0
_02019EDA:
	ldr r0, [sp, #0x214]
	add r0, r0, #0x1
	str r0, [sp, #0x214]
_02019EE0:
	ldr r0, [sp, #0x20c]
	add r0, r0, #0x4
	str r0, [sp, #0x20c]
	ldr r0, [sp, #0x218]
	add r0, r0, #0x1
	str r0, [sp, #0x218]
	cmp r0, #0x8
	blt _02019E12
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	str r0, [sp, #0x1fc]
	add r0, #0x40
	str r0, [sp, #0x1fc]
	ldr r0, [sp, #0x48]
	mov r1, #0x1
	add r0, #0x8
	str r0, [sp, #0x48]
	str r0, [sp, #0x204]
_02019F04:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _02019F12
	ldr r0, [sp, #0x204]
	add r0, r0, #0x1
	str r0, [sp, #0x204]
_02019F12:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _02019F04
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	str r0, [sp, #0x50]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xe4]
	mov r0, #0x0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A008
_02019F30:
	ldr r0, [sp, #0x1fc]
	ldr r1, [sp, #0xe4]
	ldr r0, [r0, #0x0]
	ldr r6, [sp, #0x38]
	str r0, [sp, #0x1f8]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x200]
	ldr r0, [sp, #0x204]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x204]
	str r6, [sp, #0xe0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	ldr r3, [sp, #0x34]
	add r4, r1, #0x0
	str r5, [sp, #0xdc]
	str r0, [sp, #0xd8]
_02019F78:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
// 	b _02019F8C
// 	nop
// _02019F88: .word 0x00003FE0
// _02019F8C:
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xe0]
	str r5, [sp, #0x2d8]
	add r0, r5, r0
	ldr r5, [sp, #0x1f8]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019FD4
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2dc]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2e0]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2e0]
	and r6, r5
	ldr r5, [sp, #0x2dc]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x200]
	cmp r0, #0x0
	beq _02019FD4
	ldr r6, [sp, #0x2d8]
	ldr r0, [sp, #0xdc]
	add r6, r6, r0
	ldr r0, [sp, #0xd8]
	strb r5, [r0, r6]
_02019FD4:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _02019F78
	ldr r0, [sp, #0x200]
	cmp r0, #0x0
	beq _02019FEE
	ldr r0, [sp, #0x204]
	add r0, r0, #0x2
	str r0, [sp, #0x204]
	b _02019FF4
_02019FEE:
	ldr r0, [sp, #0x204]
	add r0, r0, #0x1
	str r0, [sp, #0x204]
_02019FF4:
	ldr r0, [sp, #0x1fc]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x1fc]
	ldr r0, [sp, #0x1c]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1c]
	cmp r0, r1
	blt _02019F30
_0201A008:
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	add r0, #0x60
	str r0, [sp, #0x0]
	mov r1, #0x1
_0201A012:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _0201A020
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A020:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _0201A012
	ldr r0, [sp, #0x50]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xf4]
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	bgt _0201A03E
	bl _0201A8BC
_0201A03E:
	ldr r0, [sp, #0x5c]
	add r0, #0x8
	str r0, [sp, #0x5c]
_0201A044:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0xf4]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x1f0]
	ldr r0, [sp, #0x18]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1f4]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x2e4]
	sub r0, #0x8
	str r0, [sp, #0x2e4]
	cmp r0, #0x0
	ble _0201A0FE
	ble _0201A0FE
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x38]
	lsl r5, r0, #0x2
	ldr r0, =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xf0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xec]
	str r0, [sp, #0xe8]
_0201A09C:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xf0]
	str r5, [sp, #0x2e8]
	add r0, r5, r0
	ldr r5, [sp, #0x1f0]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _0201A0F0
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2ec]
	ldrb r5, [r0, r7]
	mov r12, r5
	mov r5, #0xf0
	asr r5, r6
	mov r6, r12
	and r6, r5
	ldr r5, [sp, #0x2ec]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x1f4]
	cmp r0, #0x0
	beq _0201A0F0
	ldr r6, [sp, #0x2e8]
	ldr r0, [sp, #0xec]
	add r6, r6, r0
	ldr r0, [sp, #0xe8]
	strb r5, [r0, r6]
_0201A0F0:
	ldr r0, [sp, #0x2e4]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _0201A09C
_0201A0FE:
	ldr r0, [sp, #0x1f4]
	cmp r0, #0x0
	beq _0201A10C
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A112
_0201A10C:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A112:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x18]
	cmp r0, r1
	blt _0201A044
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_0201A12C: // 0x0201A12C
	lsl r1, r2, #0x2
	mul r1, r3
	ldr r3, [r5, #0x0]
	ldrb r2, [r5, #0x9]
	ldr r0, [sp, #0x0]
	ldr r3, [r3, #0x0]
	lsl r1, r1, #0x3
	bl Convert4bppTo8bpp
	str r0, [sp, #0x1ec]
	cmp r4, #0x3
	bhi _0201A21E
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0201A150:

	lsl r6, r0, #0
	lsl r6, r1, #3
	lsl r0, r7, #9
	lsl r4, r3, #16
	// jump table (using 16-bit offset)
	// .short _0201A158 - _0201A150 - 2; case 0
	// .short _0201A220 - _0201A150 - 2; case 1
	// .short _0201A3CA - _0201A150 - 2; case 2
	// .short _0201A56E - _0201A150 - 2; case 3
_0201A158:
	ldr r0, [sp, #0x330]
	ldr r7, [sp, #0x1ec]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10c]
	mov r0, #0x0
	str r0, [sp, #0x1e8]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A21E
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x108]
_0201A178:
	ldr r1, [sp, #0x10c]
	ldr r0, [sp, #0x1e8]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x310]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A1FC
	ble _0201A1FC
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x108]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x100]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x104]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x108]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0xfc]
	str r0, [sp, #0xf8]
_0201A1C4:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x104]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A1F0
	ldr r0, [sp, #0x100]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x310]
	cmp r0, #0x0
	beq _0201A1F0
	ldr r0, [sp, #0xfc]
	add r2, r3, r0
	ldr r0, [sp, #0xf8]
	strb r1, [r0, r2]
_0201A1F0:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A1C4
_0201A1FC:
	ldr r0, [sp, #0x310]
	cmp r0, #0x0
	beq _0201A20A
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A210
_0201A20A:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A210:
	ldr r0, [sp, #0x1e8]
	add r7, #0x8
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1e8]
	cmp r1, r0
	blt _0201A178
_0201A21E:
	b _0201A8B6
_0201A220:
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	str r0, [sp, #0x1e0]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x124]
	mov r0, #0x0
	str r0, [sp, #0x1e4]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A2E6
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x120]
_0201A24A:
	ldr r1, [sp, #0x124]
	ldr r0, [sp, #0x1e4]
	ldr r5, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x30c]
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1e0]
	ldr r2, [sp, #0x120]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x118]
	ldr r0, [sp, #0x1e0]
	str r2, [sp, #0x11c]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x120]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	mov r4, #0x0
	str r2, [sp, #0x114]
	str r0, [sp, #0x110]
_0201A28E:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x11c]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A2BA
	ldr r0, [sp, #0x118]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x30c]
	cmp r0, #0x0
	beq _0201A2BA
	ldr r0, [sp, #0x114]
	add r2, r3, r0
	ldr r0, [sp, #0x110]
	strb r1, [r0, r2]
_0201A2BA:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A28E
	ldr r0, [sp, #0x30c]
	cmp r0, #0x0
	beq _0201A2D2
	ldr r0, [sp, #0x1e0]
	add r0, r0, #0x2
	str r0, [sp, #0x1e0]
	b _0201A2D8
_0201A2D2:
	ldr r0, [sp, #0x1e0]
	add r0, r0, #0x1
	str r0, [sp, #0x1e0]
_0201A2D8:
	ldr r0, [sp, #0x1e4]
	add r7, #0x8
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1e4]
	cmp r1, r0
	blt _0201A24A
_0201A2E6:
	ldr r0, [sp, #0x1ec]
	str r0, [sp, #0x308]
	add r0, #0x40
	str r0, [sp, #0x308]
	ldr r0, [sp, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x13c]
	mov r0, #0x0
	str r0, [sp, #0x1dc]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A3C8
	ldr r0, [sp, #0x5c]
	mov r1, #0x7
	add r0, #0x8
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x138]
_0201A312:
	ldr r1, [sp, #0x13c]
	ldr r0, [sp, #0x1dc]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1d8]
	ldr r5, [sp, #0x5c]
	cmp r7, #0x0
	ble _0201A398
	ble _0201A398
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x138]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x130]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x134]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x138]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x12c]
	str r0, [sp, #0x128]
_0201A360:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x134]
	add r2, r3, r0
	ldr r0, [sp, #0x308]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A38E
	ldr r0, [sp, #0x130]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1d8]
	cmp r0, #0x0
	beq _0201A38E
	ldr r0, [sp, #0x12c]
	add r2, r3, r0
	ldr r0, [sp, #0x128]
	strb r1, [r0, r2]
_0201A38E:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A360
_0201A398:
	ldr r0, [sp, #0x1d8]
	cmp r0, #0x0
	beq _0201A3B0
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A3B6
// 	nop
// _0201A3A8: .word 0x00003FE0
// _0201A3AC: .word 0x00007FC0
_0201A3B0:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A3B6:
	ldr r0, [sp, #0x308]
	add r0, #0x8
	str r0, [sp, #0x308]
	ldr r0, [sp, #0x1dc]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1dc]
	cmp r1, r0
	blt _0201A312
_0201A3C8:
	b _0201A8B6
_0201A3CA:
	ldr r0, [sp, #0x48]
	mov r1, #0x7
	str r0, [sp, #0x1d0]
	mov r0, #0x0
	str r0, [sp, #0x1d4]
	ldr r0, [sp, #0x330]
	ldr r7, [sp, #0x1ec]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x150]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x30]
_0201A3E8:
	ldr r1, [sp, #0x150]
	ldr r0, [sp, #0x1d4]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x304]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A46C
	ble _0201A46C
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1d0]
	ldr r2, [sp, #0x30]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x148]
	ldr r0, [sp, #0x1d0]
	str r2, [sp, #0x14c]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x30]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x144]
	str r0, [sp, #0x140]
_0201A434:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x14c]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A460
	ldr r0, [sp, #0x148]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x304]
	cmp r0, #0x0
	beq _0201A460
	ldr r0, [sp, #0x144]
	add r2, r3, r0
	ldr r0, [sp, #0x140]
	strb r1, [r0, r2]
_0201A460:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A434
_0201A46C:
	ldr r0, [sp, #0x304]
	cmp r0, #0x0
	beq _0201A47A
	ldr r0, [sp, #0x1d0]
	add r0, r0, #0x2
	str r0, [sp, #0x1d0]
	b _0201A480
_0201A47A:
	ldr r0, [sp, #0x1d0]
	add r0, r0, #0x1
	str r0, [sp, #0x1d0]
_0201A480:
	ldr r0, [sp, #0x1d4]
	add r7, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1d4]
	cmp r0, #0x8
	blt _0201A3E8
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	add r0, #0x8
	str r0, [sp, #0x48]
	add r7, #0x80
	mov r0, #0x0
	mov r2, #0x1
_0201A49A:
	ldr r1, [sp, #0x330]
	asr r1, r0
	tst r1, r2
	beq _0201A4A8
	ldr r1, [sp, #0x48]
	add r1, r1, #0x1
	str r1, [sp, #0x48]
_0201A4A8:
	add r0, r0, #0x1
	cmp r0, #0x8
	blt _0201A49A
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x164]
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A56C
_0201A4C4:
	ldr r1, [sp, #0x164]
	ldr r0, [sp, #0x14]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x300]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A548
	ble _0201A548
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x30]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x15c]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x160]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x30]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x158]
	str r0, [sp, #0x154]
_0201A510:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x160]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A53C
	ldr r0, [sp, #0x15c]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x300]
	cmp r0, #0x0
	beq _0201A53C
	ldr r0, [sp, #0x158]
	add r2, r3, r0
	ldr r0, [sp, #0x154]
	strb r1, [r0, r2]
_0201A53C:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A510
_0201A548:
	ldr r0, [sp, #0x300]
	cmp r0, #0x0
	beq _0201A556
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A55C
_0201A556:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A55C:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x1
	sub r1, #0x8
	add r7, #0x8
	str r0, [sp, #0x14]
	cmp r0, r1
	blt _0201A4C4
_0201A56C:
	b _0201A8B6
_0201A56E:
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	str r0, [sp, #0x1c8]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x1cc]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x28]
_0201A590:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1cc]
	ldr r5, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2fc]
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1c8]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x170]
	ldr r0, [sp, #0x1c8]
	str r2, [sp, #0x174]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	mov r4, #0x0
	str r6, [sp, #0x24]
	str r2, [sp, #0x16c]
	str r0, [sp, #0x168]
_0201A5D6:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x174]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A602
	ldr r0, [sp, #0x170]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x2fc]
	cmp r0, #0x0
	beq _0201A602
	ldr r0, [sp, #0x16c]
	add r2, r3, r0
	ldr r0, [sp, #0x168]
	strb r1, [r0, r2]
_0201A602:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A5D6
	ldr r0, [sp, #0x2fc]
	cmp r0, #0x0
	beq _0201A61A
	ldr r0, [sp, #0x1c8]
	add r0, r0, #0x2
	str r0, [sp, #0x1c8]
	b _0201A620
_0201A61A:
	ldr r0, [sp, #0x1c8]
	add r0, r0, #0x1
	str r0, [sp, #0x1c8]
_0201A620:
	ldr r0, [sp, #0x1cc]
	add r7, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1cc]
	cmp r0, #0x8
	blt _0201A590
	ldr r0, [sp, #0x1ec]
	str r0, [sp, #0x2f8]
	add r0, #0x40
	str r0, [sp, #0x2f8]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x1c0]
	mov r0, #0x0
	str r0, [sp, #0x1c4]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0x188]
	add r0, #0x8
	str r0, [sp, #0x188]
_0201A644:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1c4]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1bc]
	ldr r5, [sp, #0x188]
	cmp r7, #0x0
	ble _0201A6CA
	ble _0201A6CA
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1c0]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x180]
	ldr r0, [sp, #0x1c0]
	str r2, [sp, #0x184]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x17c]
	str r0, [sp, #0x178]
_0201A692:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x184]
	add r2, r3, r0
	ldr r0, [sp, #0x2f8]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A6C0
	ldr r0, [sp, #0x180]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1bc]
	cmp r0, #0x0
	beq _0201A6C0
	ldr r0, [sp, #0x17c]
	add r2, r3, r0
	ldr r0, [sp, #0x178]
	strb r1, [r0, r2]
_0201A6C0:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A692
_0201A6CA:
	ldr r0, [sp, #0x1bc]
	cmp r0, #0x0
	beq _0201A6D8
	ldr r0, [sp, #0x1c0]
	add r0, r0, #0x2
	str r0, [sp, #0x1c0]
	b _0201A6DE
_0201A6D8:
	ldr r0, [sp, #0x1c0]
	add r0, r0, #0x1
	str r0, [sp, #0x1c0]
_0201A6DE:
	ldr r0, [sp, #0x2f8]
	add r0, #0x8
	str r0, [sp, #0x2f8]
	ldr r0, [sp, #0x1c4]
	add r0, r0, #0x1
	str r0, [sp, #0x1c4]
	cmp r0, #0x8
	blt _0201A644
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	add r0, #0x8
	add r7, #0x80
	str r0, [sp, #0x48]
	str r0, [sp, #0x1b8]
	mov r0, #0x0
	mov r2, #0x1
_0201A6FE:
	ldr r1, [sp, #0x330]
	asr r1, r0
	tst r1, r2
	beq _0201A70C
	ldr r1, [sp, #0x1b8]
	add r1, r1, #0x1
	str r1, [sp, #0x1b8]
_0201A70C:
	add r0, r0, #0x1
	cmp r0, #0x8
	blt _0201A6FE
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	str r0, [sp, #0x44]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x19c]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A7CE
_0201A72A:
	ldr r1, [sp, #0x19c]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x28]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2f4]
	ldr r0, [sp, #0x1b8]
	mov r3, #0x38
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
// 	b _0201A74C
// 	nop
// _0201A748: .word 0x00007FC0
// _0201A74C:
	ldr r5, [sp, #0x5c]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x194]
	ldr r0, [sp, #0x1b8]
	str r2, [sp, #0x198]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	ldr r6, [sp, #0x24]
	mov r4, #0x0
	str r2, [sp, #0x190]
	str r0, [sp, #0x18c]
_0201A774:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x198]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A7A0
	ldr r0, [sp, #0x194]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x2f4]
	cmp r0, #0x0
	beq _0201A7A0
	ldr r0, [sp, #0x190]
	add r2, r3, r0
	ldr r0, [sp, #0x18c]
	strb r1, [r0, r2]
_0201A7A0:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A774
	ldr r0, [sp, #0x2f4]
	cmp r0, #0x0
	beq _0201A7B8
	ldr r0, [sp, #0x1b8]
	add r0, r0, #0x2
	str r0, [sp, #0x1b8]
	b _0201A7BE
_0201A7B8:
	ldr r0, [sp, #0x1b8]
	add r0, r0, #0x1
	str r0, [sp, #0x1b8]
_0201A7BE:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x1
	sub r1, #0x8
	add r7, #0x8
	str r0, [sp, #0x10]
	cmp r0, r1
	blt _0201A72A
_0201A7CE:
	ldr r0, [sp, #0x1ec]
	mov r2, #0x0
	str r0, [sp, #0x2f0]
	add r0, #0xc0
	str r0, [sp, #0x2f0]
	mov r1, #0x1
_0201A7DA:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _0201A7E8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A7E8:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _0201A7DA
	ldr r0, [sp, #0x44]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1b0]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A8B6
	ldr r0, [sp, #0x5c]
	add r0, #0x8
	str r0, [sp, #0x5c]
_0201A808:
	ldr r1, [sp, #0x1b0]
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1b4]
	ldr r5, [sp, #0x5c]
	cmp r7, #0x0
	ble _0201A88E
	ble _0201A88E
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x1a8]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x1ac]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x1a4]
	str r0, [sp, #0x1a0]
_0201A856:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x1ac]
	add r2, r3, r0
	ldr r0, [sp, #0x2f0]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A884
	ldr r0, [sp, #0x1a8]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1b4]
	cmp r0, #0x0
	beq _0201A884
	ldr r0, [sp, #0x1a4]
	add r2, r3, r0
	ldr r0, [sp, #0x1a0]
	strb r1, [r0, r2]
_0201A884:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A856
_0201A88E:
	ldr r0, [sp, #0x1b4]
	cmp r0, #0x0
	beq _0201A89C
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A8A2
_0201A89C:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A8A2:
	ldr r0, [sp, #0x2f0]
	ldr r1, [sp, #0x4]
	add r0, #0x8
	str r0, [sp, #0x2f0]
	ldr r0, [sp, #0xc]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, r1
	blt _0201A808
_0201A8B6:
	ldr r0, [sp, #0x1ec]
	bl FreeToHeap
_0201A8BC: // 0x0201A8BC
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
    // clang-format on
}
#endif

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
