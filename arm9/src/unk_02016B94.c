#include "global.h"
#include "unk_02016B94.h"
#include "GX_layers.h"
#include "game_init.h"
#include "gx.h"
#include "heap.h"

const u8 UNK_020EDB30[] = {
    0x10,
    0x20,
    0x20,
    0x20,
    0x20,
    0x20,
};

void (*const UNK_020EDB5C[])(struct Window *) = {
    FUN_020194C8,
    FUN_0201951C,
    FUN_020194C8,
};

void (*const UNK_020EDB50[])(struct Window *) = {
    FUN_020195A8,
    FUN_020195E4,
    FUN_020195A8,
};

void (*const UNK_020EDB44[])(struct Window *) = {
    FUN_020195D0,
    FUN_0201960C,
    FUN_020195D0,
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

void (*const UNK_020EDB74[])(struct Window *) = {
    ClearWindowTilemapText,
    ClearWindowTilemapAffine,
    ClearWindowTilemapText,
};

THUMB_FUNC struct BgConfig *FUN_02016B94(u32 heap_id)
{
    struct BgConfig *ptr = AllocFromHeap(heap_id, sizeof(struct BgConfig));
    memset(ptr, 0, sizeof(struct BgConfig));
    ptr->heap_id = heap_id;
    ptr->scrollScheduled = 0;
    ptr->bufferTransferScheduled = 0;

    return ptr;
}

THUMB_FUNC u32 FUN_02016BB8(u32 *param0)
{
    return *param0;
}

THUMB_FUNC void FUN_02016BBC(const struct GraphicsModes *modes)
{
    GX_SetGraphicsMode(modes->dispMode, modes->bgMode, modes->_2d3dMode);
    GXS_SetGraphicsMode(modes->subMode);
    GX_SetBGScrOffset(0);
    GX_SetBGCharOffset(0);

    GX_DisableEngineALayers();
    GX_DisableEngineBLayers();
}

THUMB_FUNC void FUN_02016BF4(const struct GraphicsModes *param0, u32 param1)
{
    if (param1 == 0)
    {
        GX_SetGraphicsMode(param0->dispMode, param0->bgMode, param0->_2d3dMode);
        GX_DisableEngineALayers();
    }
    else
    {
        GXS_SetGraphicsMode(param0->subMode);
        GX_DisableEngineBLayers();
    }
}

THUMB_FUNC void FUN_02016C18(
    struct BgConfig *param0, u8 param1, const struct BgTemplate *template, u8 bgMode)
{
    u8 screenSize = FUN_020177DC(template->unk10, bgMode);
    switch (param1)
    {
    case 0:
        GX_EngineAToggleLayers(1, GX_LAYER_TOGGLE_ON);
        G2_SetBG0Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2_SetBG0Priority(template->priority);
        G2_BG0Mosaic(template->mosaic);
        break;

    case 1:
        GX_EngineAToggleLayers(2, GX_LAYER_TOGGLE_ON);
        G2_SetBG1Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2_SetBG1Priority(template->priority);
        G2_BG1Mosaic(template->mosaic);
        break;

    case 2:
        GX_EngineAToggleLayers(4, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case 0:
            G2_SetBG2ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case 1:
            G2_SetBG2ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case 2:
            G2_SetBG2Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2_SetBG2Priority(template->priority);
        G2_BG2Mosaic(template->mosaic);
        break;

    case 3:
        GX_EngineAToggleLayers(8, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case 0:
            G2_SetBG3ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case 1:
            G2_SetBG3ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case 2:
            G2_SetBG3Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2_SetBG3Priority(template->priority);
        G2_BG3Mosaic(template->mosaic);
        break;

    case 4:
        GX_EngineBToggleLayers(1, GX_LAYER_TOGGLE_ON);
        G2S_SetBG0Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2S_SetBG0Priority(template->priority);
        G2S_BG0Mosaic(template->mosaic);
        break;

    case 5:
        GX_EngineBToggleLayers(2, GX_LAYER_TOGGLE_ON);
        G2S_SetBG1Control(screenSize, template->colorMode, template->screenBase, template->charBase, template->bgExtPltt);
        G2S_SetBG1Priority(template->priority);
        G2S_BG1Mosaic(template->mosaic);
        break;

    case 6:
        GX_EngineBToggleLayers(4, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case 0:
            G2S_SetBG2ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case 1:
            G2S_SetBG2ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case 2:
            G2S_SetBG2Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2S_SetBG2Priority(template->priority);
        G2S_BG2Mosaic(template->mosaic);
        break;

    case 7:
        GX_EngineBToggleLayers(8, GX_LAYER_TOGGLE_ON);
        switch (bgMode)
        {
        default:
        case 0:
            G2S_SetBG3ControlText(screenSize, template->colorMode, template->screenBase, template->charBase);
            break;
        case 1:
            G2S_SetBG3ControlAffine(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        case 2:
            G2S_SetBG3Control256x16Pltt(screenSize, template->areaOver, template->screenBase, template->charBase);
            break;
        }
        G2S_SetBG3Priority(template->priority);
        G2S_BG3Mosaic(template->mosaic);
        break;
    }

    param0->bgs[param1].rotation = 0;
    param0->bgs[param1].xScale = FX32_ONE;
    param0->bgs[param1].yScale = FX32_ONE;
    param0->bgs[param1].centerX = 0;
    param0->bgs[param1].centerY = 0;

    if (template->bufferSize != 0)
    {
        param0->bgs[param1].tilemapBuffer = AllocFromHeap(param0->heap_id, template->bufferSize);

        MI_CpuClear16(param0->bgs[param1].tilemapBuffer, template->bufferSize);

        param0->bgs[param1].bufferSize = template->bufferSize;
        param0->bgs[param1].unk10 = template->unk0c;
    }
    else
    {
        param0->bgs[param1].tilemapBuffer = NULL;
        param0->bgs[param1].bufferSize = 0;
        param0->bgs[param1].unk10 = 0;
    }

    param0->bgs[param1].size = template->unk10;
    param0->bgs[param1].mode = bgMode;
    param0->bgs[param1].colorMode = template->colorMode;

    if (bgMode == 0 && template->colorMode == 0)
    {
        param0->bgs[param1].tileSize = 0x20;
    }
    else
    {
        param0->bgs[param1].tileSize = 0x40;
    }

    FUN_020179E0(param0, param1, 0, template->unk00);
    FUN_020179E0(param0, param1, 3, template->unk04);
}

THUMB_FUNC void FUN_020170F4(struct BgConfig *config, u8 bgId, u32 attr, u8 value)
{
    if (attr == 0)
    {
        config->bgs[bgId].colorMode = value;
    }

    switch (bgId)
    {
    case 0:
        GXBg01Control bg0cnt = G2_GetBG0Control();
        if (attr == 1)
        {
            bg0cnt.screenBase = value;
        }
        else if (attr == 2)
        {
            bg0cnt.charBase = value;
        }

        G2_SetBG0Control(bg0cnt.screenSize, config->bgs[bgId].colorMode, bg0cnt.screenBase, bg0cnt.charBase, bg0cnt.bgExtPltt);
        break;
    case 1:
        GXBg01Control bg1cnt = G2_GetBG1Control();
        if (attr == 1)
        {
            bg1cnt.screenBase = value;
        }
        else if (attr == 2)
        {
            bg1cnt.charBase = value;
        }

        G2_SetBG1Control(bg1cnt.screenSize, config->bgs[bgId].colorMode, bg1cnt.screenBase, bg1cnt.charBase, bg1cnt.bgExtPltt);
        break;
    case 2:
        switch (config->bgs[bgId].mode)
        {
        default:
        case 0:
            GXBg23ControlText bg2cnt_tx = G2_GetBG2ControlText();
            if (attr == 1)
            {
                bg2cnt_tx.screenBase = value;
            }
            else if (attr == 2)
            {
                bg2cnt_tx.charBase = value;
            }

            G2_SetBG2ControlText(bg2cnt_tx.screenSize, config->bgs[bgId].colorMode, bg2cnt_tx.screenBase, bg2cnt_tx.charBase);
            break;
        case 1:
            GXBg23ControlAffine bg2cnt_aff = G2_GetBG2ControlAffine();
            if (attr == 1)
            {
                bg2cnt_aff.screenBase = value;
            }
            else if (attr == 2)
            {
                bg2cnt_aff.charBase = value;
            }

            G2_SetBG2ControlAffine(bg2cnt_aff.screenSize, bg2cnt_aff.areaOver, bg2cnt_aff.screenBase,
                                   bg2cnt_aff.charBase);
            break;
        case 2:
            GXBg23Control256x16Pltt bg2cnt_256x16pltt = G2_GetBG2Control256x16Pltt();
            if (attr == 1)
            {
                bg2cnt_256x16pltt.screenBase = value;
            }
            else if (attr == 2)
            {
                bg2cnt_256x16pltt.charBase = value;
            }

            G2_SetBG2Control256x16Pltt(bg2cnt_256x16pltt.screenSize, bg2cnt_256x16pltt.areaOver,
                                       bg2cnt_256x16pltt.screenBase, bg2cnt_256x16pltt.charBase);
            break;
        }
        break;
    case 3:
        switch (config->bgs[bgId].mode)
        {
        default:
        case 0:
            GXBg23ControlText bg3cnt_tx = G2_GetBG3ControlText();
            if (attr == 1)
            {
                bg3cnt_tx.screenBase = value;
            }
            else if (attr == 2)
            {
                bg3cnt_tx.charBase = value;
            }

            G2_SetBG3ControlText(bg3cnt_tx.screenSize, config->bgs[bgId].colorMode, bg3cnt_tx.screenBase, bg3cnt_tx.charBase);
            break;
        case 1:
            GXBg23ControlAffine bg3cnt_aff = G2_GetBG3ControlAffine();
            if (attr == 1)
            {
                bg3cnt_aff.screenBase = value;
            }
            else if (attr == 2)
            {
                bg3cnt_aff.charBase = value;
            }

            G2_SetBG3ControlAffine(bg3cnt_aff.screenSize, bg3cnt_aff.areaOver, bg3cnt_aff.screenBase,
                                   bg3cnt_aff.charBase);
            break;
        case 2:
            GXBg23Control256x16Pltt bg3cnt_256x16pltt = G2_GetBG3Control256x16Pltt();
            if (attr == 1)
            {
                bg3cnt_256x16pltt.screenBase = value;
            }
            else if (attr == 2)
            {
                bg3cnt_256x16pltt.charBase = value;
            }

            G2_SetBG3Control256x16Pltt(bg3cnt_256x16pltt.screenSize, bg3cnt_256x16pltt.areaOver,
                                       bg3cnt_256x16pltt.screenBase, bg3cnt_256x16pltt.charBase);
            break;
        }
        break;
    case 4:
        GXBg01Control bg0cntsub = G2S_GetBG0Control();
        if (attr == 1)
        {
            bg0cntsub.screenBase = value;
        }
        else if (attr == 2)
        {
            bg0cntsub.charBase = value;
        }

        G2S_SetBG0Control(bg0cntsub.screenSize, config->bgs[bgId].colorMode, bg0cntsub.screenBase, bg0cntsub.charBase, bg0cntsub.bgExtPltt);
        break;
    case 5:
        GXBg01Control bg1cntsub = G2S_GetBG1Control();
        if (attr == 1)
        {
            bg1cntsub.screenBase = value;
        }
        else if (attr == 2)
        {
            bg1cntsub.charBase = value;
        }

        G2S_SetBG1Control(bg1cntsub.screenSize, config->bgs[bgId].colorMode, bg1cntsub.screenBase, bg1cntsub.charBase, bg1cntsub.bgExtPltt);
        break;
    case 6:
        switch (config->bgs[bgId].mode)
        {
        default:
        case 0:
            GXBg23ControlText bg2cntsub_tx = G2S_GetBG2ControlText();
            if (attr == 1)
            {
                bg2cntsub_tx.screenBase = value;
            }
            else if (attr == 2)
            {
                bg2cntsub_tx.charBase = value;
            }

            G2S_SetBG2ControlText(bg2cntsub_tx.screenSize, config->bgs[bgId].colorMode, bg2cntsub_tx.screenBase, bg2cntsub_tx.charBase);
            break;
        case 1:
            GXBg23ControlAffine bg2cntsub_aff = G2S_GetBG2ControlAffine();
            if (attr == 1)
            {
                bg2cntsub_aff.screenBase = value;
            }
            else if (attr == 2)
            {
                bg2cntsub_aff.charBase = value;
            }

            G2S_SetBG2ControlAffine(bg2cntsub_aff.screenSize, bg2cntsub_aff.areaOver, bg2cntsub_aff.screenBase,
                                   bg2cntsub_aff.charBase);
            break;
        case 2:
            GXBg23Control256x16Pltt bg2cntsub_256x16pltt = G2S_GetBG2Control256x16Pltt();
            if (attr == 1)
            {
                bg2cntsub_256x16pltt.screenBase = value;
            }
            else if (attr == 2)
            {
                bg2cntsub_256x16pltt.charBase = value;
            }

            G2S_SetBG2Control256x16Pltt(bg2cntsub_256x16pltt.screenSize, bg2cntsub_256x16pltt.areaOver,
                                       bg2cntsub_256x16pltt.screenBase, bg2cntsub_256x16pltt.charBase);
            break;
        }
        break;
    case 7:
        switch (config->bgs[bgId].mode)
        {
        default:
        case 0:
            GXBg23ControlText bg3cntsub_tx = G2S_GetBG3ControlText();
            if (attr == 1)
            {
                bg3cntsub_tx.screenBase = value;
            }
            else if (attr == 2)
            {
                bg3cntsub_tx.charBase = value;
            }

            G2S_SetBG3ControlText(bg3cntsub_tx.screenSize, config->bgs[bgId].colorMode, bg3cntsub_tx.screenBase, bg3cntsub_tx.charBase);
            break;
        case 1:
            GXBg23ControlAffine bg3cntsub_aff = G2S_GetBG3ControlAffine();
            if (attr == 1)
            {
                bg3cntsub_aff.screenBase = value;
            }
            else if (attr == 2)
            {
                bg3cntsub_aff.charBase = value;
            }

            G2S_SetBG3ControlAffine(bg3cntsub_aff.screenSize, bg3cntsub_aff.areaOver, bg3cntsub_aff.screenBase,
                                   bg3cntsub_aff.charBase);
            break;
        case 2:
            GXBg23Control256x16Pltt bg3cntsub_256x16pltt = G2S_GetBG3Control256x16Pltt();
            if (attr == 1)
            {
                bg3cntsub_256x16pltt.screenBase = value;
            }
            else if (attr == 2)
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

THUMB_FUNC u8 FUN_020177DC(u8 param0, u32 param1)
{
    switch (param1)
    {
    case 0:

        if (param0 == 1)
        {
            return GX_BG_SCRSIZE_TEXT_256x256;
        }
        else if (param0 == 2)
        {
            return GX_BG_SCRSIZE_TEXT_256x512;
        }
        else if (param0 == 3)
        {
            return GX_BG_SCRSIZE_TEXT_512x256;
        }
        else if (param0 == 4)
        {
            return GX_BG_SCRSIZE_TEXT_512x512;
        }
        break;

    case 1:

        if (param0 == 0)
        {
            return GX_BG_SCRSIZE_TEXT_256x256;
        }
        else if (param0 == 1)
        {
            return GX_BG_SCRSIZE_TEXT_512x256;
        }
        else if (param0 == 4)
        {
            return GX_BG_SCRSIZE_TEXT_256x512;
        }
        else if (param0 == 5)
        {
            return GX_BG_SCRSIZE_TEXT_512x512;
        }
        break;

    case 2:

        if (param0 == 0)
        {
            return GX_BG_SCRSIZE_TEXT_256x256;
        }
        else if (param0 == 1)
        {
            return GX_BG_SCRSIZE_TEXT_512x256;
        }
        else if (param0 == 4)
        {
            return GX_BG_SCRSIZE_TEXT_256x512;
        }
        else if (param0 == 5)
        {
            return GX_BG_SCRSIZE_TEXT_512x512;
        }
        break;
    }

    return GX_BG_SCRSIZE_TEXT_256x256;
}

THUMB_FUNC void GetBgScreenDimensions(u32 screenSize, u8 *width_p, u8 *height_p)
{
    switch (screenSize)
    {
    case 0:
        *width_p = 0x10;
        *height_p = 0x10;
        break;
    case 1:
        *width_p = 0x20;
        *height_p = 0x20;
        break;
    case 2:
        *width_p = 0x20;
        *height_p = 0x40;
        break;
    case 3:
        *width_p = 0x40;
        *height_p = 0x20;
        break;
    case 4:
        *width_p = 0x40;
        *height_p = 0x40;
        break;
    case 5:
        *width_p = 0x80;
        *height_p = 0x80;
        break;
    }
}

THUMB_FUNC void FUN_020178A0(struct BgConfig *bgConfig, u32 bgId)
{
    if (bgConfig->bgs[bgId].tilemapBuffer != NULL)
    {
        FreeToHeap(bgConfig->bgs[bgId].tilemapBuffer);
        bgConfig->bgs[bgId].tilemapBuffer = NULL;
    }
}

THUMB_FUNC void FUN_020178BC(u32 bgId, u16 priority)
{
    switch (bgId)
    {
    case 0:
        G2_SetBG0Priority(priority);
        break;
    case 1:
        G2_SetBG1Priority(priority);
        break;
    case 2:
        G2_SetBG2Priority(priority);
        break;
    case 3:
        G2_SetBG3Priority(priority);
        break;
    case 4:
        G2S_SetBG0Priority(priority);
        break;
    case 5:
        G2S_SetBG1Priority(priority);
        break;
    case 6:
        G2S_SetBG2Priority(priority);
        break;
    case 7:
        G2S_SetBG3Priority(priority);
        break;
    }
}

THUMB_FUNC void ToggleBgLayer(u32 bgId, GX_LayerToggle toggle)
{
    switch (bgId)
    {
    case 0:
        GX_EngineAToggleLayers(1, toggle);
        break;
    case 1:
        GX_EngineAToggleLayers(2, toggle);
        break;
    case 2:
        GX_EngineAToggleLayers(4, toggle);
        break;
    case 3:
        GX_EngineAToggleLayers(8, toggle);
        break;
    case 4:
        GX_EngineBToggleLayers(1, toggle);
        break;
    case 5:
        GX_EngineBToggleLayers(2, toggle);
        break;
    case 6:
        GX_EngineBToggleLayers(4, toggle);
        break;
    case 7:
        GX_EngineBToggleLayers(8, toggle);
        break;
    }
}

THUMB_FUNC void FUN_020179E0(struct BgConfig *bgConfig, u32 bgId, u32 param2, fx32 val)
{
    Bg_SetPosText(&bgConfig->bgs[bgId], param2, val);

    u32 x = (u32)bgConfig->bgs[bgId].hOffset;
    u32 y = (u32)bgConfig->bgs[bgId].vOffset;
    switch (bgId)
    {
    case 0:
        G2_SetBG0Offset(x, y);
        break;
    case 1:
        G2_SetBG1Offset(x, y);
        break;
    case 2:
        if (bgConfig->bgs[2].mode == 0)
        {
            G2_SetBG2Offset(x, y);
        }
        else
        {
            FUN_02017C6C(bgConfig, 2);
        }

        break;
    case 3:
        if (bgConfig->bgs[3].mode == 0)
        {
            G2_SetBG3Offset(x, y);
        }
        else
        {
            FUN_02017C6C(bgConfig, 3);
        }
        break;
    case 4:
        G2S_SetBG0Offset(x, y);
        break;
    case 5:
        G2S_SetBG1Offset(x, y);
        break;
    case 6:
        if (bgConfig->bgs[6].mode == 0)
        {
            G2S_SetBG2Offset(x, y);
        }
        else
        {
            FUN_02017C6C(bgConfig, 6);
        }
        break;
    case 7:
        if (bgConfig->bgs[7].mode == 0)
        {
            G2S_SetBG3Offset(x, y);
        }
        else
        {
            FUN_02017C6C(bgConfig, 7);
        }
        break;
    }
}

THUMB_FUNC fx32 FUN_02017B48(struct BgConfig *param0, u32 param1)
{
    return param0->bgs[param1].hOffset;
}

THUMB_FUNC fx32 FUN_02017B54(struct BgConfig *param0, u32 param1)
{
    return param0->bgs[param1].vOffset;
}

THUMB_FUNC void FUN_02017B60(struct BgConfig *param0,
    u32 param1,
    u32 param2,
    fx32 param3,
    struct Mtx22 *param4,
    fx32 param5,
    fx32 param6)
{
    Bg_SetPosText(&param0->bgs[param1], param2, param3);
    FUN_02017BD0(param0, param1, param4, param5, param6);
}

THUMB_FUNC void Bg_SetPosText(struct Bg *bg, u32 op, fx32 val)
{
    switch (op)
    {
    case 0:
        bg->hOffset = val;
        break;
    case 1:
        bg->hOffset += val;
        break;
    case 2:
        bg->hOffset -= val;
        break;
    case 3:
        bg->vOffset = val;
        break;
    case 4:
        bg->vOffset += val;
        break;
    case 5:
        bg->vOffset -= val;
        break;
    }
}

THUMB_FUNC void FUN_02017BD0(
    struct BgConfig *param0, u32 param1, struct Mtx22 *param2, fx32 param3, fx32 param4)
{
    switch (param1)
    {
    case 2:
        G2_SetBG2Affine(param2, param3, param4, param0->bgs[param1].hOffset, param0->bgs[param1].vOffset);
        break;
    case 3:
        G2_SetBG3Affine(param2, param3, param4, param0->bgs[param1].hOffset, param0->bgs[param1].vOffset);
        break;
    case 6:
        G2S_SetBG2Affine(param2, param3, param4, param0->bgs[param1].hOffset, param0->bgs[param1].vOffset);
        break;
    case 7:
        G2S_SetBG3Affine(param2, param3, param4, param0->bgs[param1].hOffset, param0->bgs[param1].vOffset);
        break;
    }
}

THUMB_FUNC void FUN_02017C6C(struct BgConfig *param0, u32 param1)
{
    struct Mtx22 mtx;
    MTX22_2DAffine(&mtx, 0, 0x1000, 0x1000, 0);
    FUN_02017BD0(param0, param1, &mtx, 0, 0);
}

THUMB_FUNC void FUN_02017C98(const void *param0, void *param1, u32 param2)
{
    if (param2 == 0)
    {
        MI_UncompressLZ8(param0, param1);
        return;
    }

    if (((u32)param0 % 4) == 0 && ((u32)param1 % 4) == 0 && ((u16)param2 % 4) == 0)
    {
        MI_CpuCopy32(param0, param1, param2);
        return;
    }

    MI_CpuCopy16(param0, param1, param2);
}

THUMB_FUNC void FUN_02017CD0(struct BgConfig *param0, u32 param1)
{
    FUN_02017CE8(param0,
        param1,
        param0->bgs[param1].tilemapBuffer,
        param0->bgs[param1].bufferSize,
        param0->bgs[param1].unk10);
}

THUMB_FUNC void FUN_02017CE8(
    struct BgConfig *param0, u32 param1, u32 *param2, u32 param3, u32 param4)
{
    u32 st0 = param3;
    if (param3 == 0)
    {
        void *st4 = param0->bgs[param1].tilemapBuffer;
        if (st4 != 0)
        {
            FUN_02017C98(param2, st4, param3);
            LoadBgVramScr(param1, st4, param0->bgs[param1].unk10 * 2, param0->bgs[param1].bufferSize);
            return;
        }

        u32 r7 = param2[0] >> 8;
        void *ptr = AllocFromHeapAtEnd(param0->heap_id, r7);
        FUN_02017C98(param2, ptr, st0);
        LoadBgVramScr(param1, ptr, param4 * 2, r7);
        FreeToHeap(ptr);
        return;
    }

    LoadBgVramScr(param1, param2, param4 * 2, param3);
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

THUMB_FUNC void FUN_02017DFC(
    struct BgConfig *param0, u32 param1, void *param2, u32 param3)
{
    FUN_02017C98(param2, param0->bgs[param1].tilemapBuffer, param3);
}

THUMB_FUNC void BG_LoadCharTilesData(
    struct BgConfig *bgConfig, u32 bgId, u32 *charData, u32 offset, u32 numTiles)
{
    if (bgConfig->bgs[bgId].colorMode == 0)
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
        FUN_02017C98(charData, ptr, size);
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
    case 0:
        GX_LoadBG0Char(buffer_p, offset, size);
        break;
    case 1:
        GX_LoadBG1Char(buffer_p, offset, size);
        break;
    case 2:
        GX_LoadBG2Char(buffer_p, offset, size);
        break;
    case 3:
        GX_LoadBG3Char(buffer_p, offset, size);
        break;
    case 4:
        GXS_LoadBG0Char(buffer_p, offset, size);
        break;
    case 5:
        GXS_LoadBG1Char(buffer_p, offset, size);
        break;
    case 6:
        GXS_LoadBG2Char(buffer_p, offset, size);
        break;
    case 7:
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
    if (bgId < 4)
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
    case 0:
        return (u16)(x + (y << 4));
    case 1:
    case 2:
        return (u16)(x + (y << 5));
    case 3:
        return (u16)((x & 0x1f) + ((y + (x & ~0x1f)) << 5));
    case 4:
        u16 res = (u16)(((u16)((x >> 5) + (y >> 5) * 2)) << 10);
        res += (x & 0x1f) + ((y & 0x1f) << 5);
        return res;
    case 5:
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
                                  u32 bgId,
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

THUMB_FUNC void FUN_02018744(struct BgConfig *param0, u32 param1)
{
    if (param0->bgs[param1].tilemapBuffer != NULL)
    {
        MI_CpuClear16(param0->bgs[param1].tilemapBuffer, param0->bgs[param1].bufferSize);
        FUN_02017CD0(param0, param1);
    }
}

THUMB_FUNC void FUN_02018768(struct BgConfig *param0, u32 param1, u16 param2)
{
    if (param0->bgs[param1].tilemapBuffer != NULL)
    {
        MI_CpuFill16(param0->bgs[param1].tilemapBuffer, param2, param0->bgs[param1].bufferSize);
        FUN_02017CD0(param0, param1);
    }
}

THUMB_FUNC void FUN_0201878C(struct BgConfig *param0, u32 param1, u16 param2)
{
    if (param0->bgs[param1].tilemapBuffer != NULL)
    {
        MI_CpuFill16(param0->bgs[param1].tilemapBuffer, param2, param0->bgs[param1].bufferSize);
        ScheduleBgTilemapBufferTransfer(param0, param1);
    }
}

THUMB_FUNC void *FUN_020187B0(u32 param0)
{
    switch (param0)
    {
    case 0:
        return G2_GetBG0CharPtr();
    case 1:
        return G2_GetBG1CharPtr();
    case 2:
        return G2_GetBG2CharPtr();
    case 3:
        return G2_GetBG3CharPtr();
    case 4:
        return G2S_GetBG0CharPtr();
    case 5:
        return G2S_GetBG1CharPtr();
    case 6:
        return G2S_GetBG2CharPtr();
    case 7:
        return G2S_GetBG3CharPtr();
    }

    return NULL;
}

THUMB_FUNC void FUN_02018808(u8 *param0, u32 param1, u8 (*param2)[2], u8 param3)
{
    param3 <<= 4;
    for (int i = 0; i < param1; i++)
    {
        param2[i][0] = (u8)(param0[i] & 0xf);
        if (param2[i][0] != 0)
        {
            param2[i][0] += param3;
        }

        param2[i][1] = (u8)((param0[i] >> 4) & 0xf);
        if (param2[i][1] != 0)
        {
            param2[i][1] += param3;
        }
    }
}

THUMB_FUNC u8 (*FUN_02018848(u8 *param0, u32 param1, u8 param2, u32 heap_id))[2]
{
    u8(*ptr)[2] = (u8(*)[2])AllocFromHeap(heap_id, param1 * 2);

    FUN_02018808(param0, param1, ptr, param2);

    return ptr;
}

THUMB_FUNC void *GetBgTilemapBuffer(struct BgConfig *bgConfig, u8 bgId)
{
    return bgConfig->bgs[bgId].tilemapBuffer;
}

THUMB_FUNC u16 FUN_02018878(struct BgConfig *param0, u32 param1)
{
    return param0->bgs[param1].rotation;
}

THUMB_FUNC u8 GetBgPriority(struct BgConfig *bgConfig, u32 bgId)
{
    switch (bgId)
    {
    case 0:
        return G2_GetBG0Control().priority;
    case 1:
        return G2_GetBG1Control().priority;
    case 2:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case 0:
            return G2_GetBG2ControlText().priority;
        case 1:
            return G2_GetBG2ControlAffine().priority;
        case 2:
            return G2_GetBG2Control256x16Pltt().priority;
        }
        break;
    case 3:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case 0:
            return G2_GetBG3ControlText().priority;
        case 1:
            return G2_GetBG3ControlAffine().priority;
        case 2:
            return G2_GetBG3Control256x16Pltt().priority;
        }
        break;

    case 4:
        return G2S_GetBG0Control().priority;
    case 5:
        return G2S_GetBG1Control().priority;

    case 6:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case 0:
            return G2S_GetBG2ControlText().priority;
        case 1:
            return G2S_GetBG2ControlAffine().priority;
        case 2:
            return G2S_GetBG2Control256x16Pltt().priority;
        }
        break;
    case 7:
        switch (bgConfig->bgs[bgId].mode)
        {
        default:
        case 0:
            return G2S_GetBG3ControlText().priority;
        case 1:
            return G2S_GetBG3ControlAffine().priority;
        case 2:
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
    window->bgId = 0xff;
    window->tilemapLeft = 0;
    window->tilemapTop = 0;
    window->width = 0;
    window->height = 0;
    window->paletteNum = 0;

    window->baseTile = 0;
    window->pixelBuffer = NULL;

    window->unk0b_15 = 0;
}

THUMB_FUNC BOOL WindowIsInUse(struct Window *window)
{
    if (window->bgConfig == NULL || window->bgId == 0xff || window->pixelBuffer == NULL)
    {
        return FALSE;
    }

    return TRUE;
}

enum UnkEnum1
{
    UnkEnum1_0 = 0,
    UnkEnum1_1 = 1
};

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

    enum UnkEnum1 r2;
    if (param0->bgs[bgId].colorMode == 0)
    {
        r2 = UnkEnum1_0;
    }
    else
    {
        r2 = UnkEnum1_1;
    }

    window->unk0b_15 = r2;
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
        window->unk0b_15 = 0;
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

THUMB_FUNC void FUN_02019220(struct Window *window)
{

    GF_ASSERT(window);
    GF_ASSERT(window->bgConfig);
    GF_ASSERT(window->bgId < NELEMS(window->bgConfig->bgs));
    GF_ASSERT(window->bgConfig->bgs[window->bgId].mode < NELEMS(UNK_020EDB5C));

    UNK_020EDB5C[window->bgConfig->bgs[window->bgId].mode](window);
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

THUMB_FUNC void FUN_020192B8(struct Window *window)
{
    UNK_020EDB74[window->bgConfig->bgs[window->bgId].mode](window);
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

    tilemapWidth = UNK_020EDB30[window->bgConfig->bgs[window->bgId].size];

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

    tilemapWidth = UNK_020EDB30[window->bgConfig->bgs[window->bgId].size];
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

    tilemapWidth = UNK_020EDB30[window->bgConfig->bgs[window->bgId].size];
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
    FUN_02019548(window);
    FUN_02017CE8(window->bgConfig,
        window->bgId,
        window->bgConfig->bgs[window->bgId].tilemapBuffer,
        window->bgConfig->bgs[window->bgId].bufferSize,
        window->bgConfig->bgs[window->bgId].unk10);
}

THUMB_FUNC void FUN_020194C8(struct Window *window)
{
    PutWindowTilemap_TextMode(window);
    ScheduleBgTilemapBufferTransfer(window->bgConfig, window->bgId);
    FUN_02019548(window);
}

THUMB_FUNC void CopyWindowToVram_AffineMode(struct Window *window)
{
    PutWindowTilemap_AffineMode(window);
    FUN_02017CE8(window->bgConfig,
        window->bgId,
        window->bgConfig->bgs[window->bgId].tilemapBuffer,
        window->bgConfig->bgs[window->bgId].bufferSize,
        window->bgConfig->bgs[window->bgId].unk10);

    BG_LoadCharTilesData(window->bgConfig,
        window->bgId,
        window->pixelBuffer,
        (u32)(window->width * window->height * 64),
        window->baseTile);
}

THUMB_FUNC void FUN_0201951C(struct Window *window)
{
    PutWindowTilemap_AffineMode(window);
    ScheduleBgTilemapBufferTransfer(window->bgConfig, window->bgId);
    BG_LoadCharTilesData(window->bgConfig,
        window->bgId,
        window->pixelBuffer,
        (u32)(window->width * window->height * 64),
        window->baseTile);
}

THUMB_FUNC void FUN_02019548(struct Window *window)
{
    BG_LoadCharTilesData(window->bgConfig,
        window->bgId,
        window->pixelBuffer,
        (u32)(window->width * window->height * window->bgConfig->bgs[window->bgId].tileSize),
        window->baseTile);
}

THUMB_FUNC void FUN_02019570(struct Window *window)
{
    UNK_020EDB50[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void FUN_0201958C(struct Window *window)
{
    UNK_020EDB44[window->bgConfig->bgs[window->bgId].mode](window);
}

THUMB_FUNC void FUN_020195A8(struct Window *window)
{
    ClearWindowTilemapText(window);
    FUN_02017CE8(window->bgConfig,
        window->bgId,
        window->bgConfig->bgs[window->bgId].tilemapBuffer,
        window->bgConfig->bgs[window->bgId].bufferSize,
        window->bgConfig->bgs[window->bgId].unk10);
}

THUMB_FUNC void FUN_020195D0(struct Window *window)
{
    ClearWindowTilemapText(window);
    ScheduleBgTilemapBufferTransfer(window->bgConfig, window->bgId);
}

THUMB_FUNC void FUN_020195E4(struct Window *window)
{
    ClearWindowTilemapAffine(window);
    FUN_02017CE8(window->bgConfig,
        window->bgId,
        window->bgConfig->bgs[window->bgId].tilemapBuffer,
        window->bgConfig->bgs[window->bgId].bufferSize,
        window->bgConfig->bgs[window->bgId].unk10);
}

THUMB_FUNC void FUN_0201960C(struct Window *window)
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

    if (window->bgConfig->bgs[window->bgId].colorMode == 0)
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

    if (window->bgConfig->bgs[window->bgId].colorMode == 0)
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
	bl FUN_02018848
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
    if (window->bgConfig->bgs[window->bgId].colorMode == 0)
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
    if ((bgConfig->bufferTransferScheduled & 1) != 0)
    {
        LoadBgVramScr(0, bgConfig->bgs[0].tilemapBuffer, bgConfig->bgs[0].unk10 * 2, bgConfig->bgs[0].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & 2) != 0)
    {
        LoadBgVramScr(1, bgConfig->bgs[1].tilemapBuffer, bgConfig->bgs[1].unk10 * 2, bgConfig->bgs[1].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & 4) != 0)
    {
        LoadBgVramScr(2, bgConfig->bgs[2].tilemapBuffer, bgConfig->bgs[2].unk10 * 2, bgConfig->bgs[2].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & 8) != 0)
    {
        LoadBgVramScr(3, bgConfig->bgs[3].tilemapBuffer, bgConfig->bgs[3].unk10 * 2, bgConfig->bgs[3].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & 0x10) != 0)
    {
        LoadBgVramScr(4, bgConfig->bgs[4].tilemapBuffer, bgConfig->bgs[4].unk10 * 2, bgConfig->bgs[4].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & 0x20) != 0)
    {
        LoadBgVramScr(5, bgConfig->bgs[5].tilemapBuffer, bgConfig->bgs[5].unk10 * 2, bgConfig->bgs[5].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & 0x40) != 0)
    {
        LoadBgVramScr(6, bgConfig->bgs[6].tilemapBuffer, bgConfig->bgs[6].unk10 * 2, bgConfig->bgs[6].bufferSize);
    }

    if ((bgConfig->bufferTransferScheduled & 0x80) != 0)
    {
        LoadBgVramScr(7, bgConfig->bgs[7].tilemapBuffer, bgConfig->bgs[7].unk10 * 2, bgConfig->bgs[7].bufferSize);
    }
}

THUMB_FUNC void ScheduleBgTilemapBufferTransfer(struct BgConfig *bgConfig, u32 bgId)
{
    bgConfig->bufferTransferScheduled |= 1 << bgId;
}

THUMB_FUNC void ApplyScheduledBgPosUpdate(struct BgConfig *bgConfig)
{
    if ((bgConfig->scrollScheduled & 1) != 0)
    {
        G2_SetBG0Offset(bgConfig->bgs[0].hOffset, bgConfig->bgs[0].vOffset);
    }

    if ((bgConfig->scrollScheduled & 2) != 0)
    {
        G2_SetBG1Offset(bgConfig->bgs[1].hOffset, bgConfig->bgs[1].vOffset);
    }

    if ((bgConfig->scrollScheduled & 4) != 0)
    {
        if (bgConfig->bgs[2].mode == 0)
        {
            G2_SetBG2Offset(bgConfig->bgs[2].hOffset, bgConfig->bgs[2].vOffset);
        }
        else
        {
            struct Mtx22 st38;
            MTX22_2DAffine(
                &st38, bgConfig->bgs[2].rotation, bgConfig->bgs[2].xScale, bgConfig->bgs[2].yScale, 2);
            G2_SetBG2Affine(
                &st38,
                bgConfig->bgs[2].centerX,
                bgConfig->bgs[2].centerY,
                bgConfig->bgs[2].hOffset,
                bgConfig->bgs[2].vOffset);
        }
    }

    if ((bgConfig->scrollScheduled & 8) != 0)
    {
        if (bgConfig->bgs[3].mode == 0)
        {
            G2_SetBG3Offset(bgConfig->bgs[3].hOffset, bgConfig->bgs[3].vOffset);
        }
        else
        {
            struct Mtx22 st28;
            MTX22_2DAffine(
                &st28, bgConfig->bgs[3].rotation, bgConfig->bgs[3].xScale, bgConfig->bgs[3].yScale, 2);
            G2_SetBG3Affine(
                &st28,
                bgConfig->bgs[3].centerX,
                bgConfig->bgs[3].centerY,
                bgConfig->bgs[3].hOffset,
                bgConfig->bgs[3].vOffset);
        }
    }

    if ((bgConfig->scrollScheduled & 0x10) != 0)
    {
        G2S_SetBG0Offset(bgConfig->bgs[4].hOffset, bgConfig->bgs[4].vOffset);
    }

    if ((bgConfig->scrollScheduled & 0x20) != 0)
    {
        G2S_SetBG1Offset(bgConfig->bgs[5].hOffset, bgConfig->bgs[5].vOffset);
    }

    if ((bgConfig->scrollScheduled & 0x40) != 0)
    {
        if (bgConfig->bgs[6].mode == 0)
        {
            G2S_SetBG2Offset(bgConfig->bgs[6].hOffset, bgConfig->bgs[6].vOffset);
        }
        else
        {
            struct Mtx22 st18;
            MTX22_2DAffine(
                &st18, bgConfig->bgs[6].rotation, bgConfig->bgs[6].xScale, bgConfig->bgs[6].yScale, 2);
            G2S_SetBG2Affine(
                &st18,
                bgConfig->bgs[6].centerX,
                bgConfig->bgs[6].centerY,
                bgConfig->bgs[6].hOffset,
                bgConfig->bgs[6].vOffset);
        }
    }

    if ((bgConfig->scrollScheduled & 0x80) != 0)
    {
        if (bgConfig->bgs[7].mode == 0)
        {
            G2S_SetBG3Offset(bgConfig->bgs[7].hOffset, bgConfig->bgs[7].vOffset);
        }
        else
        {
            struct Mtx22 st08;
            MTX22_2DAffine(
                &st08, bgConfig->bgs[7].rotation, bgConfig->bgs[7].xScale, bgConfig->bgs[7].yScale, 2);
            G2S_SetBG3Affine(
                &st08,
                bgConfig->bgs[7].centerX,
                bgConfig->bgs[7].centerY,
                bgConfig->bgs[7].hOffset,
                bgConfig->bgs[7].vOffset);
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
    case 0:
        bg->rotation = val;
        break;
    case 1:
        bg->rotation += val;
        break;
    case 2:
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
    case 9:
        bg->centerX = val;
        break;
    case 10:
        bg->centerX += val;
        break;
    case 11:
        bg->centerX -= val;
        break;
    case 12:
        bg->centerY = val;
        break;
    case 13:
        bg->centerY += val;
        break;
    case 14:
        bg->centerY -= val;
        break;
    }
}

THUMB_FUNC u32 FUN_0201AFBC(
    struct BgConfig *bgConfig, u8 bgId, u8 x, u8 y, u16 *src)
{
    void *st18;
    u16 r6;
    u8 st14;
    u8 st10;
    u8 r5;
    u8 i;

    if (bgConfig->bgs[bgId].tilemapBuffer == NULL)
    {
        return 0;
    }

    r6 = GetTileMapIndexFromCoords((u8) (x >> 3), (u8) (y >> 3), bgConfig->bgs[bgId].size);
    st18 = FUN_020187B0(bgId);

    st14 = (u8)(x & 7);
    st10 = (u8)(y & 7);

    if (bgConfig->bgs[bgId].colorMode == 0)
    {
        u16 *stc = bgConfig->bgs[bgId].tilemapBuffer;
        u8 *ptr = AllocFromHeapAtEnd(bgConfig->heap_id, 0x40);

        st18 += ((stc[r6] & 0x3ff) << 5);
        for (i = 0; i < 0x20; i++)
        {
            ptr[(i << 1)] = (u8)(((u8 *)st18)[i] & 0xf);
            ptr[(i << 1) + 1] = (u8)(((u8 *)st18)[i] >> 4);
        }

        FUN_0201B118(bgConfig, (u8)((stc[r6] >> 0xa) & 3), ptr);

        r5 = ptr[st14 + (st10 << 3)];
        FreeToHeap(ptr);

        if ((src[0] & (1 << r5)) != 0)
        {
            return 1;
        }
    }
    else
    {
        if (bgConfig->bgs[bgId].mode != 1)
        {
            u16 *r4 = bgConfig->bgs[bgId].tilemapBuffer;
            u8 *ptr = AllocFromHeapAtEnd(bgConfig->heap_id, 0x40);

            memcpy(ptr, st18 + ((r4[r6] & 0x3ff) << 6), 0x40);

            FUN_0201B118(bgConfig, (u8)((r4[r6] >> 0xa) & 3), ptr);

            r5 = ptr[st14 + (st10 << 3)];
            FreeToHeap(ptr);
        }
        else
        {
            r5 = ((u8 *)st18)[(((u8 *)bgConfig->bgs[bgId].tilemapBuffer)[r6] << 6) + st14 + (st10 << 3)];
        }

        while (TRUE)
        {
            if (src[0] == 0xffff)
            {
                break;
            }
            if (r5 == (u8)(src[0]))
            {
                return 1;
            }
        }
    }
    return 0;
}

THUMB_FUNC void FUN_0201B118(struct BgConfig *param0, u8 param1, u8 *param2)
{
    u8 i, j;
    if (param1 != 0)
    {
        u8 *ptr = AllocFromHeapAtEnd(param0->heap_id, 0x40);

        if ((param1 & 1) != 0)
        {
            for (i = 0; i < 8; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    ptr[i * 8 + j] = param2[i * 8 + (7 - j)];
                }
            }

            memcpy(param2, ptr, 0x40);
        }

        if ((param1 & 2) != 0)
        {
            for (i = 0; i < 8; i++)
            {
                u8 *r3 = &ptr[i * 8];
                u8 *r2 = &param2[(7 - i) * 8];
                for (u32 j = 8; j > 0; j--)
                {
                    *r3++ = *r2++;
                }
            }

            memcpy(param2, ptr, 0x40);
        }

        FreeToHeap(ptr);
    }
}
