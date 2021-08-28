#include "global.h"
#include "render_window.h"
#include "filesystem.h"
#include "gf_gfx_loader.h"
#include "graphic/field_board.naix"
#include "graphic/winframe.naix"
#include "pokemon.h"
#include "render_text.h"
#include "unk_020061E8.h"
#include "unk_0200BB14.h"
#include "unk_0200CA44.h"
#include "unk_02006D98.h"

const struct UnkStruct_0200CABC_3 UNK_020ECE88 = {
    10,
    0,
    10,
    10,
};

const struct UnkStruct_0200CABC_3 UNK_020ECE98 = {
    0,
    0,
    10,
    10,
};

extern void FUN_02020130(u32 param0, u32 param1);
extern u32 FUN_0202022C(u32 param0);
extern void FUN_020201E4(u32 param0, u32 param1);
extern void FUN_0201FDEC(u32 param0);
extern void MOD05_021D99F8(struct UnkStruct_0200CABC_2 *param0);
extern void *FUN_0201B6C8(BOOL);
extern void MOD05_021D959C(
    struct UnkStruct_0200CABC_2 *param0, void *param1, u32 param2, u32 param3);
extern void MOD05_021D967C(struct UnkStruct_0200CABC_2 *param0,
    NarcId narcId,
    s32 memberId,
    u32 param3,
    u32 param4,
    u32 param5,
    u32 param6);
extern void MOD05_021D96F4(
    struct UnkStruct_0200CABC_2 *param0, NarcId narcId, s32 memberId, u32 param3, u32 param4);
extern void MOD05_021D9708(
    struct UnkStruct_0200CABC_2 *param0, NarcId narcId, s32 memberId, u32 param3, u32 param4);
extern void MOD05_021D971C(struct UnkStruct_0200CABC_2 *param0,
    NarcId narcId,
    s32 memberId,
    u32 param3,
    u32 param4,
    u32 param5);
extern u32 *MOD05_021D9820(struct UnkStruct_0200CABC_2 *param0, void *);
extern void FUN_02012400(u16, u16, u16, void *, void *);
extern u32 NNS_G2dGetImageLocation(u32, u32);
extern void *FUN_02012470(u16, u16, u16);
extern u32 NNS_G2dGetImagePaletteLocation(u32, u32);

THUMB_FUNC u32 FUN_0200CABC(
    struct BgConfig *bgConfig, u32 layer, u32 numTiles, u32 param3, u32 heap_id)
{
    if (param3 == 0)
    {
        return GfGfxLoader_LoadCharData(NARC_GRAPHIC_WINFRAME,
            NARC_winframe_narc_0000_NCGR,
            bgConfig,
            layer,
            numTiles,
            0,
            FALSE,
            heap_id);
    }

    return GfGfxLoader_LoadCharData(NARC_GRAPHIC_WINFRAME,
        NARC_winframe_narc_0001_NCGR,
        bgConfig,
        layer,
        numTiles,
        0,
        FALSE,
        heap_id);
}

THUMB_FUNC s32 FUN_0200CAFC(void)
{
    return NARC_winframe_narc_0024_NCLR;
}

THUMB_FUNC void FUN_0200CB00(
    struct BgConfig *bg_config, u32 layer, u32 num_tiles, u32 param3, u8 param4, u32 heap_id)
{
    s32 r1;
    if (param4 != 0)
    {
        r1 = NARC_winframe_narc_0001_NCGR;
    }
    else
    {
        r1 = NARC_winframe_narc_0000_NCGR;
    }

    GfGfxLoader_LoadCharData(
        NARC_GRAPHIC_WINFRAME, r1, bg_config, layer, num_tiles, 0, FALSE, heap_id);

    if (param4 == 2)
    {
        r1 = NARC_winframe_narc_0045_NCLR;
    }
    else
    {
        r1 = NARC_winframe_narc_0024_NCLR;
    }

    if (layer < 4)
    {
        GfGfxLoader_GXLoadPal(NARC_GRAPHIC_WINFRAME, r1, 0, param3 << 5, 32, heap_id);
        return;
    }

    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_WINFRAME, r1, 4, param3 << 5, 32, heap_id);
}

THUMB_FUNC void DrawFrame1(struct BgConfig *bgConfig,
    u8 bgId,
    u8 x,
    u8 y,
    u8 width,
    u8 height,
    u8 paletteNum,
    u16 fillValue)
{
    FillBgTilemapRect(bgConfig, bgId, fillValue, (u8)(x - 1), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 1), x, (u8)(y - 1), width, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 2), (u8)(x + width), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 3), (u8)(x - 1), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 5), (u8)(x + width), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 6), (u8)(x - 1), (u8)(y + height), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 7), x, (u8)(y + height), width, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 8), (u8)(x + width), (u8)(y + height), 1, 1, paletteNum);
}

THUMB_FUNC void DrawFrameAndWindow1(
    struct Window *window, BOOL copy_to_vram, u16 fill_value, u8 palette_num)
{
    DrawFrame1(window->bgConfig,
        GetWindowBgId(window),
        GetWindowX(window),
        GetWindowY(window),
        GetWindowWidth(window),
        GetWindowHeight(window),
        palette_num,
        fill_value);

    if (!copy_to_vram)
    {
        CopyWindowToVram(window);
    }
}

THUMB_FUNC void ClearFrameAndWindow1(struct Window *window, BOOL copy_to_vram)
{

    FillBgTilemapRect(window->bgConfig,
        GetWindowBgId(window),
        0,
        (u8)(GetWindowX(window) - 1),
        (u8)(GetWindowY(window) - 1),
        (u8)(GetWindowWidth(window) + 2),
        (u8)(GetWindowHeight(window) + 2),
        0);

    if (!copy_to_vram)
    {
        ClearWindowTilemapAndCopyToVram(window);
    }
}

THUMB_FUNC s32 FUN_0200CD60(s32 param0)
{
    return param0 + 2;
}

THUMB_FUNC s32 FUN_0200CD64(s32 param0)
{
    return param0 + 25;
}

THUMB_FUNC void FUN_0200CD68(
    struct BgConfig *param0, u32 param1, u32 param2, u32 param3, u8 param4, u32 param5)
{

    GfGfxLoader_LoadCharData(
        NARC_GRAPHIC_WINFRAME, FUN_0200CD60(param4), param0, param1, param2, 0, FALSE, param5);

    if (param1 < 4)
    {
        GfGfxLoader_GXLoadPal(
            NARC_GRAPHIC_WINFRAME, FUN_0200CD64(param4), 0, param3 << 5, 32, param5);
        return;
    }

    GfGfxLoader_GXLoadPal(NARC_GRAPHIC_WINFRAME, FUN_0200CD64(param4), 4, param3 << 5, 32, param5);
}

THUMB_FUNC void DrawFrame2(struct BgConfig *bgConfig,
    u8 bgId,
    u8 x,
    u8 y,
    u8 width,
    u8 height,
    u8 paletteNum,
    u16 fillValue)
{
    FillBgTilemapRect(bgConfig, bgId, fillValue, (u8)(x - 2), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 1), (u8)(x - 1), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 2), x, (u8)(y - 1), width, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 3), (u8)(x + width), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 4), (u8)(x + width + 1), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 5), (u8)(x + width + 2), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 6), (u8)(x - 2), y, 1, height, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 7), (u8)(x - 1), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 9), (u8)(x + width), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 10), (u8)(x + width + 1), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 11), (u8)(x + width + 2), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 12), (u8)(x - 2), (u8)(y + height), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 13), (u8)(x - 1), (u8)(y + height), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 14), x, (u8)(y + height), width, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 15), (u8)(x + width), (u8)(y + height), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig,
        bgId,
        (u16)(fillValue + 16),
        (u8)(x + width + 1),
        (u8)(y + height),
        1,
        1,
        paletteNum);
    FillBgTilemapRect(bgConfig,
        bgId,
        (u16)(fillValue + 17),
        (u8)(x + width + 2),
        (u8)(y + height),
        1,
        1,
        paletteNum);
}

THUMB_FUNC void DrawWindowFrame2(struct Window *window, u32 fill_value, u32 palette_num)
{
    DrawFrame2(window->bgConfig,
        GetWindowBgId(window),
        GetWindowX(window),
        GetWindowY(window),
        GetWindowWidth(window),
        GetWindowHeight(window),
        (u8)palette_num,
        (u16)fill_value);
}

THUMB_FUNC void DrawFrameAndWindow2(
    struct Window *window, BOOL copy_to_vram, u16 fill_value, u8 palette_num)
{
    DrawWindowFrame2(window, fill_value, palette_num);
    if (!copy_to_vram)
    {
        CopyWindowToVram(window);
    }

    FUN_0200D18C(window, fill_value);
}

THUMB_FUNC void ClearFrameAndWindow2(struct Window *window, BOOL param1)
{
    FillBgTilemapRect(window->bgConfig,
        GetWindowBgId(window),
        0,
        (u8)(GetWindowX(window) - 2),
        (u8)(GetWindowY(window) - 1),
        (u8)(GetWindowWidth(window) + 5),
        (u8)(GetWindowHeight(window) + 2),
        0);

    if (!param1)
    {
        ClearWindowTilemapAndCopyToVram(window);
    }
}

THUMB_FUNC void BlitRect4Bit(u8 *srcPixels,
    u16 srcX,
    u16 srcY,
    u16 srcWidth,
    u16 srcHeight,
    u8 *dstPixels,
    u16 dstWidth,
    u16 dstHeight,
    u16 dstX,
    u16 dstY,
    u16 width,
    u16 height)
{
    struct Bitmap src;
    src.pixels = srcPixels;
    src.width = srcWidth;
    src.height = srcHeight;

    struct Bitmap dst;
    dst.pixels = dstPixels;
    dst.width = dstWidth;
    dst.height = dstHeight;

    BlitBitmapRect4Bit(&src, &dst, srcX, srcY, dstX, dstY, width, height, 0);
}

THUMB_FUNC void FUN_0200D18C(struct Window *window, u16 fill_value)
{
    u32 heap_id = BgConfig_GetHeapId(window->bgConfig);
    u8 bg_id = GetWindowBgId(window);

    void *ptr = AllocFromHeap(heap_id, 0x180);
    void *charptr = BgGetCharPtr(bg_id);

    NNSG2dCharacterData *pCharData;
    void *st30;
    void *st2c;
    st2c = GfGfxLoader_GetCharData(
        NARC_GRAPHIC_WINFRAME, NARC_winframe_narc_0022_NCGR, FALSE, &pCharData, heap_id);
    st30 = pCharData->pRawData;

    for (u8 i = 0; i < 3; i++)
    {
        memcpy(ptr + (i << 7), charptr + ((fill_value + 10) << 5), 0x20);
        memcpy(ptr + ((i << 7) + 0x20), charptr + ((fill_value + 11) << 5), 0x20);
        memcpy(ptr + ((i << 7) + 0x40), charptr + ((fill_value + 10) << 5), 0x20);
        memcpy(ptr + ((i << 7) + 0x60), charptr + ((fill_value + 11) << 5), 0x20);
    }

    BlitRect4Bit(st30, 4, 0, 12, 0x30, ptr, 12, 0x30, 1, 0, 12, 0x30);
    BG_LoadCharTilesData(window->bgConfig, bg_id, ptr, 0x180, (u32)(fill_value + 18));
    FUN_02002840(fill_value);
    FreeToHeap(st2c);
    FreeToHeap(ptr);
}

THUMB_FUNC void FUN_0200D274(
    struct BgConfig *bg_config, u8 bg_id, u16 param2, u8 param3, u8 param4, u32 heap_id)
{

    NNSG2dCharacterData *pCharData;
    void *stc = GfGfxLoader_GetCharData(
        NARC_GRAPHIC_WINFRAME, FUN_0200CD60(param4), FALSE, &pCharData, heap_id);
    u8 *ptr = AllocFromHeap(heap_id, 0x240);
    memcpy(ptr, pCharData->pRawData, 0x240);

    for (u32 r3 = 0; r3 < 0x240; r3++)
    {
        u8 r6 = (u8)(ptr[r3] >> 4);
        u8 r2 = (u8)(ptr[r3] & 0xf);
        if (r6 == 0)
        {
            r6 = param3;
        }
        if (r2 == 0)
        {
            r2 = param3;
        }

        ptr[r3] = (u8)(r2 | (r6 << 4));
    }

    BG_LoadCharTilesData(bg_config, bg_id, (u32 *)ptr, 0x240, param2);
    FreeToHeap(stc);
    FreeToHeap(ptr);
}

THUMB_FUNC void FUN_0200D300(struct BgConfig *bg_config,
    u8 bg_id,
    u16 numtiles,
    u8 param3,
    u8 param4,
    u16 param5,
    u32 heap_id)
{
    GfGfxLoader_LoadCharData(NARC_GRAPHIC_FIELD_BOARD,
        NARC_field_board_narc_0000_NCGR,
        bg_config,
        bg_id,
        numtiles,
        0x3C0,
        FALSE,
        heap_id);

    NNSG2dPaletteData *pPltData;
    void *st14;
    st14 = AllocAndReadWholeNarcMemberByIdPair(
        NARC_GRAPHIC_FIELD_BOARD, NARC_field_board_narc_0001_NCLR, heap_id);
    NNS_G2dGetUnpackedPaletteData(st14, &pPltData);
    BG_LoadPlttData(bg_id, pPltData->pRawData + param4 * 0x20, 0x20, (u16)(param3 << 5));
    FreeToHeapExplicit(heap_id, st14);

    if (param4 <= 1)
    {
        FUN_0200D378(bg_config, bg_id, (u16)(numtiles + 30), param4, param5, heap_id);
    }
}

THUMB_FUNC void FUN_0200D378(
    struct BgConfig *bg_config, u8 bg_id, u16 numtiles, u8 param3, u16 param4, u32 heap_id)
{
    if (param3 == 0)
    {
        param4 += 33;
    }
    else
    {
        param4 += 2;
    }

    GfGfxLoader_LoadCharData(
        NARC_GRAPHIC_FIELD_BOARD, param4, bg_config, bg_id, numtiles, 0x300, FALSE, heap_id);
}

THUMB_FUNC void DrawFrame3(struct BgConfig *bgConfig,
    u8 bgId,
    u8 x,
    u8 y,
    u8 width,
    u8 height,
    u8 paletteNum,
    u16 fillValue)
{
    FillBgTilemapRect(bgConfig, bgId, fillValue, (u8)(x - 9), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 1), (u8)(x - 8), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig,
        bgId,
        (u16)(fillValue + 2),
        (u8)(x - 7),
        (u8)(y - 1),
        (u8)(width + 7),
        1,
        paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 3), (u8)(x + width), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 4), (u8)(x + width + 1), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 5), (u8)(x + width + 2), (u8)(y - 1), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 6), (u8)(x - 9), y, 1, height, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 7), (u8)(x - 8), y, 1, height, paletteNum);
    FillBgTilemapRect(bgConfig, bgId, (u16)(fillValue + 8), (u8)(x - 1), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 9), (u8)(x + width), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 10), (u8)(x + width + 1), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 11), (u8)(x + width + 2), y, 1, height, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 12), (u8)(x - 9), (u8)(y + height), 1, 1, paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 13), (u8)(x - 8), (u8)(y + height), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig,
        bgId,
        (u16)(fillValue + 14),
        (u8)(x - 7),
        (u8)(y + height),
        (u8)(width + 7),
        1,
        paletteNum);
    FillBgTilemapRect(
        bgConfig, bgId, (u16)(fillValue + 15), (u8)(x + width), (u8)(y + height), 1, 1, paletteNum);
    FillBgTilemapRect(bgConfig,
        bgId,
        (u16)(fillValue + 16),
        (u8)(x + width + 1),
        (u8)(y + height),
        1,
        1,
        paletteNum);
    FillBgTilemapRect(bgConfig,
        bgId,
        (u16)(fillValue + 17),
        (u8)(x + width + 2),
        (u8)(y + height),
        1,
        1,
        paletteNum);
}

THUMB_FUNC void DrawWindowCorner(struct Window *window, u16 fillValue, u8 paletteNum)
{
    u16 i, j;
    u16 x, y;
    u8 bg_id;

    bg_id = GetWindowBgId(window);
    x = (u16)(GetWindowX(window) - 7);
    y = GetWindowY(window);

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 6; j++)
        {
            FillBgTilemapRect(window->bgConfig,
                bg_id,
                (u16)(fillValue + 6 * i + j),
                (u8)(x + j),
                (u8)(y + i),
                1,
                1,
                paletteNum);
        }
    }
}

THUMB_FUNC void DrawFrameAndWindow3(
    struct Window *window, BOOL copy_to_vram, u16 fillValue, u8 paletteNum, u8 param4)
{
    u8 bg_id = GetWindowBgId(window);
    if (param4 <= 1)
    {
        DrawFrame3(window->bgConfig,
            bg_id,
            GetWindowX(window),
            GetWindowY(window),
            GetWindowWidth(window),
            GetWindowHeight(window),
            paletteNum,
            fillValue);
        DrawWindowCorner(window, (u16)(fillValue + 30), paletteNum);
    }
    else
    {
        DrawFrame2(window->bgConfig,
            bg_id,
            GetWindowX(window),
            GetWindowY(window),
            GetWindowWidth(window),
            GetWindowHeight(window),
            paletteNum,
            fillValue);
    }

    if (!copy_to_vram)
    {
        CopyWindowToVram(window);
    }

    FUN_0200D18C(window, fillValue);
}

THUMB_FUNC void ClearFrameAndWindow3(struct Window *window, u8 param1, BOOL copy_to_vram)
{
    u8 bg_id = GetWindowBgId(window);
    if (param1 <= 1)
    {
        FillBgTilemapRect(window->bgConfig,
            bg_id,
            0,
            (u8)(GetWindowX(window) - 9),
            (u8)(GetWindowY(window) - 1),
            (u8)(GetWindowWidth(window) + 11),
            (u8)(GetWindowHeight(window) + 2),
            0);
    }
    else
    {
        FillBgTilemapRect(window->bgConfig,
            bg_id,
            0,
            (u8)(GetWindowX(window) - 2),
            (u8)(GetWindowY(window) - 1),
            (u8)(GetWindowWidth(window) + 4),
            (u8)(GetWindowHeight(window) + 2),
            0);
    }

    if (!copy_to_vram)
    {
        ClearWindowTilemapAndCopyToVram(window);
    }
}

THUMB_FUNC struct UnkStruct_0200CABC_1 *FUN_0200D858(struct Window *window, u32 param1)
{
    u32 heap_id = BgConfig_GetHeapId(window->bgConfig);
    void *charptr = BgGetCharPtr(GetWindowBgId(window));

    struct UnkStruct_0200CABC_1 *ptr = AllocFromHeap(heap_id, sizeof(struct UnkStruct_0200CABC_1));
    memcpy(ptr->unk004[8], charptr + (param1 + 18) * 32, 0x80);
    void *ptr2 = AllocFromHeap(heap_id, 0x80);
    memcpy(ptr2, charptr + (param1 + 10) * 32, 0x20);
    memcpy(ptr2 + 0x20, charptr + (param1 + 11) * 32, 0x20);
    memcpy(ptr2 + 0x40, charptr + (param1 + 10) * 32, 0x20);
    memcpy(ptr2 + 0x60, charptr + (param1 + 11) * 32, 0x20);

    for (u8 i = 0; i < 8; i++)
    {
        memcpy(ptr->unk004[i], ptr2, 0x80);
    }
    FreeToHeap(ptr2);

    NNSG2dCharacterData *pCharData;
    void *r5 = GfGfxLoader_GetCharData(
        NARC_GRAPHIC_WINFRAME, NARC_winframe_narc_0023_NCGR, FALSE, &pCharData, heap_id);
    BlitRect4Bit(
        pCharData->pRawData, 0, 0, 0x10, 0x80, ptr->unk004[0], 0x10, 0x80, 0, 0, 0x10, 0x80);
    FreeToHeap(r5);

    ptr->unk000 = window;
    ptr->fillValue = (u16)param1;
    ptr->unk486 = 0;
    ptr->unk487 = 0;
    ptr->unk488 = 0;

    FUN_0200CA60(FUN_0200DB7C, ptr, 0);
    FUN_0200D980(ptr, 1);

    return ptr;
}

THUMB_FUNC void FUN_0200D980(struct UnkStruct_0200CABC_1 *param0, u32 param1)
{
    u8 bg_id = GetWindowBgId(param0->unk000);
    u8 x = GetWindowX(param0->unk000);
    u8 y = GetWindowY(param0->unk000);
    u8 width = GetWindowWidth(param0->unk000);

    if (param1 == 2)
    {
        BG_LoadCharTilesData(param0->unk000->bgConfig,
            bg_id,
            (u32 *)param0->unk004[8],
            0x80,
            (u32)(param0->fillValue + 18));
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 10),
            (u8)(x + width + 1),
            (u8)(y + 2),
            1,
            1,
            0x10);
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 11),
            (u8)(x + width + 2),
            (u8)(y + 2),
            1,
            1,
            0x10);
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 10),
            (u8)(x + width + 1),
            (u8)(y + 3),
            1,
            1,
            0x10);
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 11),
            (u8)(x + width + 2),
            (u8)(y + 3),
            1,
            1,
            0x10);
        BgCommitTilemapBufferToVram(param0->unk000->bgConfig, bg_id);
        return;
    }

    BG_LoadCharTilesData(param0->unk000->bgConfig,
        bg_id,
        (u32 *)param0->unk004[param0->unk487],
        0x80,
        (u32)(param0->fillValue + 18));
    if (param1 != 0)
    {
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 18),
            (u8)(x + width + 1),
            (u8)(y + 2),
            1,
            1,
            0x10);
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 19),
            (u8)(x + width + 2),
            (u8)(y + 2),
            1,
            1,
            0x10);
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 20),
            (u8)(x + width + 1),
            (u8)(y + 3),
            1,
            1,
            0x10);
        FillBgTilemapRect(param0->unk000->bgConfig,
            bg_id,
            (u16)(param0->fillValue + 21),
            (u8)(x + width + 2),
            (u8)(y + 3),
            1,
            1,
            0x10);
        BgCommitTilemapBufferToVram(param0->unk000->bgConfig, bg_id);
    }
}

THUMB_FUNC void FUN_0200DB7C(u32 param0, void *param1)
{
    struct UnkStruct_0200CABC_1 *r1 = (struct UnkStruct_0200CABC_1 *)param1;

    if (r1->unk488 != 0)
    {
        if (r1->unk488 == 1)
        {
            FUN_0200D980(r1, 2);
        }
        FUN_0200CAB4((s32)param0);
        return;
    }

    r1->unk486++;
    if (r1->unk486 == 16)
    {
        r1->unk486 = 0;
        r1->unk487 = (r1->unk487 + 1) & 7;
        FUN_0200D980(r1, 0);
    }
}

THUMB_FUNC void FUN_0200DBE8(u32 param0, void *param1)
{
    FreeToHeap(param1);
    FUN_0200CAB4((s32)param0);
}

THUMB_FUNC void FUN_0200DBFC(struct UnkStruct_0200CABC_1 *param0)
{
    FUN_0200CA98(FUN_0200DBE8, param0, 0);
    param0->unk488 = 1;
}

THUMB_FUNC void FUN_0200DC24(struct UnkStruct_0200CABC_1 *param0)
{
    FUN_0200CA98(FUN_0200DBE8, param0, 0);
    param0->unk488 = 2;
}

THUMB_FUNC u8 *FUN_0200DC4C(struct BgConfig *bg_config,
    u8 bg_id,
    u8 param2,
    u8 param3,
    u8 param4,
    u16 param5,
    u16 param6,
    u8 param7,
    s32 param8)
{
    struct UnkStruct_0200CABC_2 *r4 = FUN_0200DD70(bg_config, bg_id, param2, param3, (u32)param8);
    FUN_0200DDAC(r4, (u32)param8);
    FUN_0200DDD8(r4);
    FUN_0200DE30(r4, param2, param3);
    FUN_0200DE80(r4, param6, param7);
    DrawFramed10x10Square(r4, param4, param5);
    BgCommitTilemapBufferToVram(bg_config, bg_id);

    return &r4->unk16f;
}

THUMB_FUNC u8 *FUN_0200DCA4(struct BgConfig *bg_config,
    u8 bg_id,
    u8 param2,
    u8 param3,
    u8 param4,
    u16 param5,
    struct Pokemon *param6,
    s32 param7)
{
    struct UnkStruct_0200CABC_2 *r4 = FUN_0200DD70(bg_config, bg_id, param2, param3, (u32)param7);
    FUN_0200DDAC(r4, (u32)param7);
    FUN_0200DDD8(r4);
    FUN_0200DE30(r4, param2, param3);
    FUN_0200DEC0(r4, param6);
    DrawFramed10x10Square(r4, param4, param5);
    BgCommitTilemapBufferToVram(bg_config, bg_id);

    return &r4->unk16f;
}

THUMB_FUNC void FUN_0200DCF8(u32 param0, void *param1)
{
    struct UnkStruct_0200CABC_2 *unk = (struct UnkStruct_0200CABC_2 *)param1;
    switch (unk->unk16f)
    {
        case 1:
            ClearFramed10x10Square(unk);
            FUN_0200C3DC(unk->unk164);
            MOD05_021D99F8(unk);
            FUN_0200621C((s32)param0);
            return;
        case 2:
            unk->unk16f = 3;
            FUN_02020130(*unk->unk164, 1);
            break;
        case 3:
            if (FUN_0202022C(*unk->unk164) == 6)
            {
                unk->unk16f = 0;
            }
    }

    FUN_020201E4(*unk->unk164, 0x1000);
    FUN_0201FDEC(unk->unk000);
}

THUMB_FUNC struct UnkStruct_0200CABC_2 *FUN_0200DD70(
    struct BgConfig *bg_config, u8 bg_id, u8 param2, u8 param3, u32 param4)
{
    struct UnkStruct_0200CABC_2 *res = FUN_0201B6C8(FUN_020061E8(FUN_0200DCF8, 0x170, 0, param4));

    res->unk16f = 0;
    res->bgConfig = bg_config;
    res->bgId = bg_id;
    res->x = param2;
    res->y = param3;

    return res;
}

THUMB_FUNC void FUN_0200DDAC(struct UnkStruct_0200CABC_2 *param0, u32 param1)
{

    const u32 UNK_020ECEA8[] = {
        0x01,
        0x01,
        0x01,
        0x01,
        0x00,
        0x00,
    };
    MOD05_021D959C(param0, UNK_020ECEA8, 1, param1);
}

THUMB_FUNC void FUN_0200DDD8(struct UnkStruct_0200CABC_2 *param0)
{
    MOD05_021D967C(param0, NARC_GRAPHIC_WINFRAME, NARC_winframe_narc_0049_NCLR, 0, 1, 1, 0x15CD5);
    MOD05_021D96F4(param0, NARC_GRAPHIC_WINFRAME, NARC_winframe_narc_0047_NCER, 0, 0x15CD5);
    MOD05_021D9708(param0, NARC_GRAPHIC_WINFRAME, NARC_winframe_narc_0046_NANR, 0, 0x15CD5);
    MOD05_021D971C(param0, NARC_GRAPHIC_WINFRAME, NARC_winframe_narc_0048_NCGR, 0, 1, 0x15CD5);
}

THUMB_FUNC void FUN_0200DE30(struct UnkStruct_0200CABC_2 *param0, u8 param1, u8 param2)
{
    u32 UNK_020ECEC0[] = {
        0x00,
        0x00,
        0x00,
        0x00,
        0x01,
        0x015CD5,
        0x015CD5,
        0x015CD5,
        0x015CD5,
        0x00,
        0x00,
        0x00,
        0x00,
    };
    ((u16 *)UNK_020ECEC0)[0] = (u16)((param1 + 5) * 8);
    ((u16 *)UNK_020ECEC0)[1] = (u16)((param2 + 5) * 8);
    param0->unk164 = MOD05_021D9820(param0, UNK_020ECEC0);
    FUN_0201FDEC(param0->unk000);
    GX_EngineBToggleLayers(0x10, GX_LAYER_TOGGLE_ON);
}

THUMB_FUNC void FUN_0200DE80(struct UnkStruct_0200CABC_2 *param0, u16 param1, u8 param2)
{
    struct UnkStruct_02006D98 *r7 = FUN_02006D98(param0->unk162);
    struct SomeDrawPokemonStruct stc;
    FUN_02068C00(&stc, param1, param2, 2, 0, 0, 0);
    FUN_0200DEF4(param0, &stc);
    FUN_020072E8(r7);
}

THUMB_FUNC void FUN_0200DEC0(struct UnkStruct_0200CABC_2 *param0, struct Pokemon *param1)
{
    struct UnkStruct_02006D98 *r6 = FUN_02006D98(param0->unk162);
    struct SomeDrawPokemonStruct st0;
    FUN_02068B68(&st0, param1, 2);
    FUN_0200DEF4(param0, &st0);
    FUN_020072E8(r6);
}

THUMB_FUNC void FUN_0200DEF4(
    struct UnkStruct_0200CABC_2 *param0, struct SomeDrawPokemonStruct *param1)
{
    void *r4 = AllocFromHeap(param0->unk162, 0x1900);

    struct UnkStruct_0200CABC_3 st18 = UNK_020ECE98;
    FUN_02012400(param1->unk0, param1->unk2, param0->unk162, &st18, r4);

    struct UnkStruct_0200CABC_3 st8 = UNK_020ECE88;
    FUN_02012400(param1->unk0, param1->unk2, param0->unk162, &st8, r4 + 0xc80);

    u32 st4 = FUN_02009C5C(FUN_020094F0(param0->unk130, 0x15CD5));

    u32 r7 = NNS_G2dGetImageLocation(st4, 1);
    DC_FlushRange(r4, 0x1900);
    GX_LoadOBJ(r4, r7, 0x1900);
    FreeToHeap(r4);
    void *res = FUN_02012470(param1->unk0, param1->unk4, param0->unk162);

    u32 r5 =
        NNS_G2dGetImagePaletteLocation(FUN_02009E54(FUN_020094F0(param0->unk134, 0x15CD5), st4), 1);
    DC_FlushRange(res, 0x20);
    GX_LoadOBJPltt(res, r5, 0x20);
    FreeToHeap(res);
}

THUMB_FUNC void DrawFramed10x10Square(
    struct UnkStruct_0200CABC_2 *param0, u8 paletteNum, u16 fillValue)
{
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        fillValue,
        (u8)(param0->x - 1),
        (u8)(param0->y - 1),
        1,
        1,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 1),
        param0->x,
        (u8)(param0->y - 1),
        10,
        1,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 2),
        (u8)(param0->x + 10),
        (u8)(param0->y - 1),
        1,
        1,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 4),
        param0->x,
        param0->y,
        10,
        10,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 3),
        (u8)(param0->x - 1),
        param0->y,
        1,
        10,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 5),
        (u8)(param0->x + 10),
        param0->y,
        1,
        10,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 6),
        (u8)(param0->x - 1),
        (u8)(param0->y + 10),
        1,
        1,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 7),
        param0->x,
        (u8)(param0->y + 10),
        10,
        1,
        paletteNum);
    FillBgTilemapRect(param0->bgConfig,
        param0->bgId,
        (u16)(fillValue + 8),
        (u8)(param0->x + 10),
        (u8)(param0->y + 10),
        1,
        1,
        paletteNum);

    ScheduleBgTilemapBufferTransfer(param0->bgConfig, param0->bgId);
}

THUMB_FUNC void ClearFramed10x10Square(struct UnkStruct_0200CABC_2 *param0)
{
    FillBgTilemapRect(
        param0->bgConfig, param0->bgId, 0, (u8)(param0->x - 1), (u8)(param0->y - 1), 12, 12, 0);
    ScheduleBgTilemapBufferTransfer(param0->bgConfig, param0->bgId);
}
