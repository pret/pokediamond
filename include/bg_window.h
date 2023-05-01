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
    u32 x;
    u32 y;
    u32 bufferSize;
    u32 baseTile;

    u8 size;
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
    u32 baseTile;

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
    u16 colorMode : 1;
    void *pixelBuffer;
};

enum GFBppMode
{
    GF_BG_CLR_4BPP = 0,
    GF_BG_CLR_8BPP,
};

enum GFBgLayer
{
    GF_BG_LYR_MAIN_0 = 0,
    GF_BG_LYR_MAIN_1,
    GF_BG_LYR_MAIN_2,
    GF_BG_LYR_MAIN_3,
    GF_BG_LYR_SUB_0,
    GF_BG_LYR_SUB_1,
    GF_BG_LYR_SUB_2,
    GF_BG_LYR_SUB_3,
    GF_BG_LYR_MAIN_CNT = 4,
    GF_BG_LYR_SUB_CNT = 4,
    GF_BG_LYR_MAIN_FIRST = GF_BG_LYR_MAIN_0,
    GF_BG_LYR_SUB_FIRST = GF_BG_LYR_SUB_0,

    GF_BG_LYR_MAIN_0_F = 1 << (GF_BG_LYR_MAIN_0 - GF_BG_LYR_MAIN_FIRST),
    GF_BG_LYR_MAIN_1_F = 1 << (GF_BG_LYR_MAIN_1 - GF_BG_LYR_MAIN_FIRST),
    GF_BG_LYR_MAIN_2_F = 1 << (GF_BG_LYR_MAIN_2 - GF_BG_LYR_MAIN_FIRST),
    GF_BG_LYR_MAIN_3_F = 1 << (GF_BG_LYR_MAIN_3 - GF_BG_LYR_MAIN_FIRST),
    GF_BG_LYR_SUB_0_F = 1 << (GF_BG_LYR_SUB_0 - GF_BG_LYR_SUB_FIRST),
    GF_BG_LYR_SUB_1_F = 1 << (GF_BG_LYR_SUB_1 - GF_BG_LYR_SUB_FIRST),
    GF_BG_LYR_SUB_2_F = 1 << (GF_BG_LYR_SUB_2 - GF_BG_LYR_SUB_FIRST),
    GF_BG_LYR_SUB_3_F = 1 << (GF_BG_LYR_SUB_3 - GF_BG_LYR_SUB_FIRST),

    GF_BG_LYR_UNALLOC = 0xFF,
};

enum GFBgType
{
    GF_BG_TYPE_TEXT = 0,
    GF_BG_TYPE_AFFINE,
    GF_BG_TYPE_256x16PLTT,
};

enum GFBgCntSet
{
    GF_BG_CNT_SET_COLOR_MODE = 0,
    GF_BG_CNT_SET_SCREEN_BASE,
    GF_BG_CNT_SET_CHAR_BASE,
};

enum GFBgScreenSize
{
    GF_BG_SCR_SIZE_128x128 = 0,
    GF_BG_SCR_SIZE_256x256,
    GF_BG_SCR_SIZE_256x512,
    GF_BG_SCR_SIZE_512x256,
    GF_BG_SCR_SIZE_512x512,
    GF_BG_SCR_SIZE_1024x1024
};

enum BgPosAdjustOp
{
    // Text layers
    BG_POS_OP_SET_X = 0,
    BG_POS_OP_ADD_X,
    BG_POS_OP_SUB_X,
    BG_POS_OP_SET_Y,
    BG_POS_OP_ADD_Y,
    BG_POS_OP_SUB_Y,

    // Affine layers
    BG_POS_OP_SET_ROT = 0,
    BG_POS_OP_ADD_ROT,
    BG_POS_OP_SUB_ROT,
    BG_POS_OP_SET_CENTERX = 9,
    BG_POS_OP_ADD_CENTERX,
    BG_POS_OP_SUB_CENTERX,
    BG_POS_OP_SET_CENTERY,
    BG_POS_OP_ADD_CENTERY,
    BG_POS_OP_SUB_CENTERY,
};

struct BgConfig *BgConfig_Alloc(u32 heap_id);
u32 BgConfig_GetHeapId(struct BgConfig *bgConfig);
void SetBothScreensModesAndDisable(const struct GraphicsModes *modes);
void SetScreenModeAndDisable(const struct GraphicsModes *gfxModes, u32 whichScreen);
void InitBgFromTemplate(
    struct BgConfig *bgConfig, u8 bgId, const struct BgTemplate *template, u8 bgMode);
void SetBgControlParam(struct BgConfig *config, u8 bgId, u32 attr, u8 value);
u8 TranslateGFBgModePairToGXScreenSize(u8 size, u32 bgMode);
void GetBgScreenDimensions(u32 screenSize, u8 *width_p, u8 *height_p);
void FreeBgTilemapBuffer(struct BgConfig *bgConfig, u32 bgId);
void SetBgPriority(u32 bgId, u16 priority);
void ToggleBgLayer(u32 bgId, GX_LayerToggle toggle);
void BgSetPosTextAndCommit(struct BgConfig *bgConfig, u32 bgId, u32 op, fx32 val);
fx32 Bg_GetXpos(struct BgConfig *bgConfig, u32 bgId);
fx32 Bg_GetYpos(struct BgConfig *bgConfig, u32 bgId);
void Bg_SetTextDimAndAffineParams(struct BgConfig *bgConfig,
                                  u32 bgId,
                                  u32 txOp,
                                  fx32 txVal,
                                  struct Mtx22 *mtx,
                                  fx32 centerX,
                                  fx32 centerY);
void Bg_SetPosText(struct Bg *bg, u32 op, fx32 val);
void SetBgAffine(struct BgConfig *bgConfig,
                 u32 bgId,
                 struct Mtx22 *mtx,
                 fx32 centerX,
                 fx32 centerY);
void BgAffineReset(struct BgConfig *bgConfig, u32 bgId);
void CopyOrUncompressTilemapData(const void *src, void *dest, u32 size);
void BgCommitTilemapBufferToVram(struct BgConfig *bgConfig, u32 bgId);
void BgCopyOrUncompressTilemapBufferRangeToVram(
    struct BgConfig *bgConfig, u32 bgId, u32 *src, u32 size, u32 tileOffset);
void LoadBgVramScr(u32 bgId, void *buffer_p, u32 offset, u32 size);
void BG_LoadScreenTilemapData(struct BgConfig *bgConfig, u32 bgId, void *src, u32 numTiles);
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
                       u8 bgId,
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
void BgClearTilemapBufferAndCommit(struct BgConfig *bgConfig, u32 bgId);
void BgFillTilemapBufferAndCommit(struct BgConfig *bgConfig, u32 bgId, u16 fillValue);
void BgFillTilemapBufferAndSchedule(struct BgConfig *bgConfig, u32 bgId, u16 fillValue);
void *BgGetCharPtr(u32 bgId);
void Convert4bppTo8bppInternal(u8 *src4bpp, u32 size, u8 (*dest8bpp), u8 paletteNum);
u8 *Convert4bppTo8bpp(u8 *src4Bpp, u32 size, u8 paletteNum, u32 heap_id);
void *GetBgTilemapBuffer(struct BgConfig *bgConfig, u8 bgId);
u16 GetBgAffineRotation(struct BgConfig *bgConfig, u32 bgId);
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
void ScheduleWindowCopyToVram(struct Window *window);
void PutWindowTilemap(struct Window *window);
void PutWindowTilemapRectAnchoredTopLeft(struct Window *window, u8 width, u8 height);
void ClearWindowTilemap(struct Window *window);
void PutWindowTilemap_TextMode(struct Window *param0);
void PutWindowTilemap_AffineMode(struct Window *window);
void ClearWindowTilemapText(struct Window *window);
void ClearWindowTilemapAffine(struct Window *window);
void CopyWindowToVram_TextMode(struct Window *window);
void ScheduleWindowCopyToVram_TextMode(struct Window *window);
void CopyWindowToVram_AffineMode(struct Window *window);
void ScheduleWindowCopyToVram_AffineMode(struct Window *window);
void CopyWindowPixelsToVram_TextMode(struct Window *window);
void ClearWindowTilemapAndCopyToVram(struct Window *window);
void ClearWindowTilemapAndScheduleTransfer(struct Window *window);
void ClearWindowTilemapAndCopyToVram_TextMode(struct Window *window);
void ClearWindowTilemapAndScheduleTransfer_TextMode(struct Window *window);
void ClearWindowTilemapAndCopyToVram_AffineMode(struct Window *window);
void ClearWindowTilemapAndScheduleTransfer_AffineMode(struct Window *window);
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
    u8 *glyphPixels,
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
u32 DoesPixelAtScreenXYMatchPtrVal(struct BgConfig *bgConfig, u8 bgId, u8 x, u8 y, u16 *src);
void ApplyFlipFlagsToTile(struct BgConfig *bgConfig, u8 flag, u8 *src);

#endif // POKEDIAMOND_UNK_02016B94_H
