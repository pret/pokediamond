#ifndef POKEDIAMOND_UNK_02016B94_H
#define POKEDIAMOND_UNK_02016B94_H

#include "NNS_g2d.h"
#include "global.h"
#include "GX_layers.h"
#include "MI_uncompress.h"
#include "OS_cache.h"
#include "gx.h"
#include "heap.h"
#include "math_util.h"

struct BgTemplate
{
    u32 unk00;
    u32 unk04;
    u32 bufferSize;
    u32 unk0c;

    u8 unk10;
    u8 colorMode;
    u8 screenBase;
    u8 charBase;
    u8 bgExtPltt;
    u8 priority;
    u8 areaOver;
    u8 unk17; // probably paddding
    u32 mosaic;
};

struct Bg
{
    void *tilemapBuffer;
    u32 bufferSize;
    u32 unk10;

    fx32 hOffset;
    fx32 vOffset;

    u8 mode;
    u8 size;
    u8 colorMode;
    u8 tileSize;
    u16 rotation;
    u16 unk22; // probably padding
    fx32 xScale;
    fx32 yScale;
    fx32 centerX;
    fx32 centerY;
};

struct BgConfig
{
    u32 heap_id;
    u16 scrollScheduled;
    u16 bufferTransferScheduled;
    struct Bg bgs[8];
};

struct Bitmap
{
    const u8 *pixels;
    u16 width;
    u16 height;
};

struct WindowTemplate
{
    u8 bgId;
    u8 tilemapLeft;
    u8 tilemapTop;
    u8 width;
    u8 height;
    u8 paletteNum;
    u16 baseTile;
};

struct Window
{
    struct BgConfig *bgConfig;
    u8 bgId;
    u8 tilemapLeft;
    u8 tilemapTop;
    u8 width;
    u8 height;
    u8 paletteNum;
    u16 baseTile : 15;
    u16 unk0b_15 : 1;
    void *pixelBuffer;
};

struct BgConfig *FUN_02016B94(u32 heap_id);
u32 FUN_02016BB8(u32 *param0);
void FUN_02016BBC(const struct GraphicsModes *modes);
void FUN_02016BF4(const struct GraphicsModes *param0, u32 param1);
void FUN_02016C18(
    struct BgConfig *param0, u8 param1, const struct BgTemplate *template, u8 bgMode);
void FUN_020170F4(struct BgConfig *config, u8 bgId, u32 attr, u8 value);
u8 FUN_020177DC(u8 param0, u32 param1);
void GetBgScreenDimensions(u32 screenSize, u8 *width_p, u8 *height_p);
void FUN_020178A0(struct BgConfig *bgConfig, u32 bgId);
void FUN_020178BC(u32 bgId, u16 priority);
void ToggleBgLayer(u32 bgId, GX_LayerToggle toggle);
void FUN_020179E0(struct BgConfig *bgConfig, u32 bgId, u32 param2, fx32 val);
fx32 FUN_02017B48(struct BgConfig *param0, u32 param1);
fx32 FUN_02017B54(struct BgConfig *param0, u32 param1);
void FUN_02017B60(struct BgConfig *param0,
    u32 param1,
    u32 param2,
    fx32 param3,
    struct Mtx22 *param4,
    fx32 param5,
    fx32 param6);
void Bg_SetPosText(struct Bg *bg, u32 op, fx32 val);
void FUN_02017BD0(struct BgConfig *param0,
    u32 param1,
    struct Mtx22 *param2,
    fx32 param3,
    fx32 param4);
void FUN_02017C6C(struct BgConfig *param0, u32 param1);
void FUN_02017C98(const void *param0, void *param1, u32 param2);
void FUN_02017CD0(struct BgConfig *param0, u32 param1);
void FUN_02017CE8(
    struct BgConfig *param0, u32 param1, u32 *param2, u32 param3, u32 param4);
void LoadBgVramScr(u32 bgId, void *buffer_p, u32 offset, u32 size);
void FUN_02017DFC(struct BgConfig *param0, u32 param1, void *param2, u32 param3);
void BG_LoadCharTilesData(
    struct BgConfig *bgConfig, u32 bgId, u32 *charData, u32 offset, u32 numTiles);
void BG_LoadCharPixelData(
    struct BgConfig *bgConfig, u32 bgId, u32 *charData, u32 size, u32 offset);
void LoadBgVramChar(u32 bgId, void *buffer_p, u32 offset, u32 size);
void BG_ClearCharDataRange(u32 bgId, u32 size, u32 offset, u32 heap_id);
void BG_FillCharDataRange(
    struct BgConfig *param0, u32 bgId, u32 fillValue, u32 count, u32 offset);
void BG_LoadPlttData(u32 bgId, void *plttData, u32 size, u32 offset);
void BG_SetMaskColor(u32 bgId, u32 value);
u16 GetTileMapIndexFromCoords(u8 x, u8 y, u8 screenSize);
u16 GetSrcTileMapIndexFromCoords(u8 x, u8 y, u8 width, u8 height);
void LoadRectToBgTilemapRect(struct BgConfig *bgConfig,
                             u32 bgId,
                             void *src,
                             u8 dstX,
                             u8 dstY,
                             u8 width,
                             u8 height);
void CopyToBgTilemapRect(struct BgConfig *bgConfig,
                         u32 bgId,
                         u8 dstX,
                         u8 dstY,
                         u8 dstWidth,
                         u8 dstHeight,
                         void *src,
                         u8 srcX,
                         u8 srcY,
                         u8 srcWidth,
                         u8 srcHeight);
void CopyRectToBgTilemapRect(struct BgConfig *bgConfig,
                         u32 bgId,
                         u8 dstX,
                         u8 dstY,
                         u8 dstWidth,
                         u8 dstHeight,
                         void *src,
                         u8 srcX,
                         u8 srcY,
                         u8 srcWidth,
                         u8 srcHeight);
void CopyBgTilemapRectText(struct Bg *bg,
                           u8 dstX,
                           u8 dstY,
                           u8 dstWidth,
                           u8 dstHeight,
                           u16 *src,
                           u8 srcX,
                           u8 srcY,
                           u8 srcWidth,
                           u8 srcHeight,
                           u8 adjustForSrcDims);
void CopyBgTilemapRectAffine(struct Bg *bg,
                             u8 dstX,
                             u8 dstY,
                             u8 dstWidth,
                             u8 dstHeight,
                             u8 *src,
                             u8 srcX,
                             u8 srcY,
                             u8 srcWidth,
                             u8 srcHeight,
                             u8 adjustForSrcDims);
void FillBgTilemapRect(struct BgConfig *bgConfig,
                       u32 bgId,
                       u16 fillValue,
                       u8 x,
                       u8 y,
                       u8 width,
                       u8 height,
                       u8 paletteNum);
void FillBgTilemapRectText(struct Bg *bg,
                                     u16 fillValue,
                                     u8 x,
                                     u8 y,
                                     u8 width,
                                     u8 height,
                                     u8 paletteNum);
void FillBgTilemapRectAffine(
    struct Bg *bg, u8 fillValue, u8 x, u8 y, u8 width, u8 height);
void BgTilemapRectChangePalette(struct BgConfig *bgConfig,
                                u32 bgId,
                                u8 x,
                                u8 y,
                                u8 width,
                                u8 height,
                                u8 paletteNum);
void FUN_02018744(struct BgConfig *param0, u32 param1);
void FUN_02018768(struct BgConfig *param0, u32 param1, u16 param2);
void FUN_0201878C(struct BgConfig *param0, u32 param1, u16 param2);
void *FUN_020187B0(u32 param0);
void FUN_02018808(u8 *param0, u32 param1, u8 (*param2)[2], u8 param3);
u8 (*FUN_02018848(u8 *param0, u32 param1, u8 param2, u32 heap_id))[2];
void *GetBgTilemapBuffer(struct BgConfig *bgConfig, u8 bgId);
u16 FUN_02018878(struct BgConfig *param0, u32 param1);
u8 GetBgPriority(struct BgConfig *bgConfig, u32 bgId);
void BlitBitmapRect4Bit(const struct Bitmap *src,
                        const struct Bitmap *dst,
                        u16 srcX,
                        u16 srcY,
                        u16 dstX,
                        u16 dstY,
                        u16 width,
                        u16 height,
                        u16 colorKey);
void BlitBitmapRect8Bit(const struct Bitmap *src,
                        const struct Bitmap *dst,
                        u16 srcX,
                        u16 srcY,
                        u16 dstX,
                        u16 dstY,
                        u16 width,
                        u16 height,
                        u16 colorKey);
void FillBitmapRect4Bit(
    struct Bitmap *surface, u16 x, u16 y, u16 width, u16 height, u8 fillValue);
void FillBitmapRect8Bit(
    struct Bitmap *surface, u16 x, u16 y, u16 width, u16 height, u8 fillValue);
struct Window *AllocWindows(u32 heap_id, s32 size);
void InitWindow(struct Window *window);
BOOL WindowIsInUse(struct Window *window);
void AddWindowParameterized(struct BgConfig *param0,
                            struct Window *window,
                            u8 bgId,
                            u8 tilemapLeft,
                            u8 tilemapTop,
                            u8 width,
                            u8 height,
                            u8 paletteNum,
                            u16 baseTile);
void AddTextWindowTopLeftCorner(struct BgConfig *param0,
                                struct Window *window,
                                u8 width,
                                u8 height,
                                u16 baseTile,
                                u8 paletteNum);
void AddWindow(struct BgConfig *bgConfig,
               struct Window *window,
               const struct WindowTemplate *template);
void RemoveWindow(struct Window *window);
void WindowArray_dtor(struct Window *windows, int count);
void CopyWindowToVram(struct Window *window);
void FUN_02019220(struct Window *window);
void PutWindowTilemap(struct Window *window);
void PutWindowTilemapRectAnchoredTopLeft(struct Window *window, u8 width, u8 height);
void FUN_020192B8(struct Window *window);
void PutWindowTilemap_TextMode(struct Window *param0);
void PutWindowTilemap_AffineMode(struct Window *window);
void ClearWindowTilemapText(struct Window *window);
void ClearWindowTilemapAffine(struct Window *window);
void CopyWindowToVram_TextMode(struct Window *window);
void FUN_020194C8(struct Window *window);
void CopyWindowToVram_AffineMode(struct Window *window);
void FUN_0201951C(struct Window *window);
void FUN_02019548(struct Window *window);
void FUN_02019570(struct Window *window);
void FUN_0201958C(struct Window *window);
void FUN_020195A8(struct Window *window);
void FUN_020195D0(struct Window *window);
void FUN_020195E4(struct Window *window);
void FUN_0201960C(struct Window *window);
void FillWindowPixelBuffer(struct Window *window, u8 param1);
void BlitBitmapRectToWindow(struct Window *window,
    const void *src,
    u16 srcX,
    u16 srcY,
    u16 srcWidth,
    u16 srcHeight,
    u16 dstX,
    u16 dstY,
    u16 dstWidth,
    u16 dstHeight);
void BlitBitmapRect(struct Window *window,
    void *param1,
    u16 param2,
    u16 param3,
    u16 param4,
    u16 param5,
    u16 param6,
    u16 param7,
    u16 param8,
    u16 param9,
    u16 param10);
void FillWindowPixelRect(struct Window *window, u8 fillValue, u16 x, u16 y, u16 width, u16 height);
void CopyGlyphToWindow(
    struct Window * window,
    const char * src,
    u16 srcWidth,
    u16 srcHeight,
    u16 width,
    u16 height,
    u16 glyph
);
void ScrollWindow(struct Window *window, u32 param1, u8 param2, u8 param3);
void ScrollWindow4bpp(struct Window *window, u32 param1, u8 param2, u8 fillValue);
void ScrollWindow8bpp(struct Window *window, u32 param1, u8 param2, u8 fillValue);
u8 GetWindowBgId(struct Window *window);
u8 GetWindowWidth(struct Window *window);
u8 GetWindowHeight(struct Window *window);
u8 GetWindowX(struct Window *window);
u8 GetWindowY(struct Window *window);
void MoveWindowX(struct Window *window, u8 x);
void MoveWindowY(struct Window *window, u8 y);
void SetWindowPaletteNum(struct Window *window, u8 paletteNum);
NNSG2dCharacterData * LoadCharacterDataFromFile(void **char_ret, u32 heap_id, const char *path);
NNSG2dPaletteData * LoadPaletteDataFromFile(void **pltt_ret, u32 heap_id, const char *path);
void DoScheduledBgGpuUpdates(struct BgConfig *bgConfig);
void DoScheduledBgTilemapBufferTransfers(struct BgConfig *bgConfig);
void ScheduleBgTilemapBufferTransfer(struct BgConfig *bgConfig, u32 bgId);
void ApplyScheduledBgPosUpdate(struct BgConfig *bgConfig);
void ScheduleSetBgPosText(struct BgConfig *bgConfig, u32 bgId, u32 op, fx32 value);
void ScheduleSetBgAffineRotation(struct BgConfig *bgConfig, u32 bgId, u32 op, u16 value);
void Bg_SetAffineRotation(struct Bg *bg, u32 op, u16 val);
void ScheduleSetBgAffinePos(struct BgConfig *bgConfig, u32 bgId, u32 op, fx32 value);
void Bg_SetAffinePos(struct Bg *bg, u32 op, fx32 val);
u32 FUN_0201AFBC(struct BgConfig *bgConfig, u8 bgId, u8 x, u8 y, u16 *src);
void FUN_0201B118(struct BgConfig *param0, u8 param1, u8 *param2);

#endif // POKEDIAMOND_UNK_02016B94_H
