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

typedef struct BgTemplate
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
} BgTemplate;

typedef struct Bg {
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
} Bg;

typedef struct BgConfig
{
    HeapID heapId;
    u16 scrollScheduled;
    u16 bufferTransferScheduled;
    Bg bgs[8];
} BgConfig;

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

typedef struct Window
{
    BgConfig *bgConfig;
    u8 bgId;
    u8 tilemapLeft;
    u8 tilemapTop;
    u8 width;
    u8 height;
    u8 paletteNum;
    u16 baseTile : 15;
    u16 colorMode : 1;
    void *pixelBuffer;
} Window;

enum GFScreen {
    SCREEN_MAIN = 0,
    SCREEN_SUB  = 1,
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

enum GFPalLoadLocation {
    GF_PAL_LOCATION_MAIN_BG = 0,
    GF_PAL_LOCATION_MAIN_OBJ,
    GF_PAL_LOCATION_MAIN_BGEXT,
    GF_PAL_LOCATION_MAIN_OBJEXT,
    GF_PAL_LOCATION_SUB_BG,
    GF_PAL_LOCATION_SUB_OBJ,
    GF_PAL_LOCATION_SUB_BGEXT,
    GF_PAL_LOCATION_SUB_OBJEXT,
};

enum GFPalSlotOffset {
    GF_PAL_SLOT_OFFSET_0 = 0x00,
    GF_PAL_SLOT_OFFSET_1 = 0x20,
    GF_PAL_SLOT_OFFSET_2 = 0x40,
    GF_PAL_SLOT_OFFSET_3 = 0x60,
    GF_PAL_SLOT_OFFSET_4 = 0x80,
    GF_PAL_SLOT_OFFSET_5 = 0xA0,
    GF_PAL_SLOT_OFFSET_6 = 0xC0,
    GF_PAL_SLOT_OFFSET_7 = 0xE0,
    GF_PAL_SLOT_OFFSET_8 = 0x100,
    GF_PAL_SLOT_OFFSET_9 = 0x120,
    GF_PAL_SLOT_OFFSET_10 = 0x140,
    GF_PAL_SLOT_OFFSET_11 = 0x160,
    GF_PAL_SLOT_OFFSET_12 = 0x180,
    GF_PAL_SLOT_OFFSET_13 = 0x1A0,
    GF_PAL_SLOT_OFFSET_14 = 0X1C0,
    GF_PAL_SLOT_OFFSET_15 = 0X1E0
};

enum GFBgType {
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

enum {
    TILE_SIZE_4BPP = 32,
    TILE_SIZE_8BPP = 64,
};

#define TILEMAP_COPY_SRC_FLAT       0  // Source dimensions are equal to dest dimensions
#define TILEMAP_COPY_SRC_RECT       1  // Dest dimensions carve out a window from source

BgConfig *BgConfig_Alloc(HeapID heapId);
HeapID BgConfig_GetHeapId(BgConfig *bgConfig);
void SetBothScreensModesAndDisable(const GraphicsModes *modes);
void SetScreenModeAndDisable(const struct GraphicsModes *gfxModes, enum GFScreen screen);
void InitBgFromTemplate(BgConfig *bgConfig, u8 bgId, const BgTemplate *template, u8 bgMode);
void SetBgControlParam(BgConfig *config, u8 bgId, enum GFBgCntSet attr, u8 value);
void FreeBgTilemapBuffer(BgConfig *bgConfig, u8 bgId);
void SetBgPriority(u8 bgId, u16 priority);
void ToggleBgLayer(u8 bgId, GXLayerToggle toggle);
void BgSetPosTextAndCommit(BgConfig *bgConfig, u8 bgId, enum BgPosAdjustOp op, fx32 val);
fx32 Bg_GetXpos(const BgConfig *bgConfig, enum GFBgLayer bgId);
fx32 Bg_GetYpos(BgConfig *bgConfig, enum GFBgLayer bgId);
void Bg_SetTextDimAndAffineParams(BgConfig *bgConfig, u8 bgId, enum BgPosAdjustOp op, fx32 value, MtxFx22 *mtx, fx32 centerX, fx32 centerY);
void SetBgAffine(BgConfig *bgConfig, u8 bgId, MtxFx22 *mtx, fx32 centerX, fx32 centerY);
void BgCommitTilemapBufferToVram(BgConfig *bgConfig, u8 bgId);
void BgCopyOrUncompressTilemapBufferRangeToVram(BgConfig *bgConfig, u8 bgId, const void *buffer, u32 bufferSize, u32 baseTile);
void BG_LoadScreenTilemapData(BgConfig *bgConfig, u8 bgId, const void *data, u32 size);
void BG_LoadCharTilesData(BgConfig *bgConfig, u8 bgId, const void *data, u32 size, u32 tileStart);
void BG_ClearCharDataRange(u8 bgId, u32 size, u32 offset, HeapID heapId);
void BG_FillCharDataRange(BgConfig *bgConfig, enum GFBgLayer bgId, u32 fillValue, u32 ntiles, u32 offset);
void BG_LoadPlttData(u32 location, void *plttData, u32 size, enum GFPalSlotOffset offset);
void BG_SetMaskColor(u8 bgId, u16 value);
void LoadRectToBgTilemapRect(BgConfig *bgConfig, u8 bgId, const void *buffer, u8 destX, u8 destY, u8 width, u8 height);
void CopyToBgTilemapRect(BgConfig *bgConfig, u8 bgId, u8 destX, u8 destY, u8 destWidth, u8 destHeight, const void *buffer, u8 srcX, u8 srcY, u8 srcWidth, u8 srcHeight);
void CopyRectToBgTilemapRect(BgConfig *bgConfig, u8 bgId, u8 destX, u8 destY, u8 destWidth, u8 destHeight, const void *buffer, u8 srcX, u8 srcY, u8 srcWidth, u8 srcHeight);
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
void FillBgTilemapRect(BgConfig *bgConfig,
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
void BgTilemapRectChangePalette(BgConfig *bgConfig,
                                u8 bgId,
                                u8 x,
                                u8 y,
                                u8 width,
                                u8 height,
                                u8 paletteNum);
void BgClearTilemapBufferAndCommit(BgConfig *bgConfig, u8 bgId);
void BgFillTilemapBufferAndCommit(BgConfig *bgConfig, u8 bgId, u16 fillValue);
void BgFillTilemapBufferAndSchedule(BgConfig *bgConfig, u8 bgId, u16 fillValue);
void *BgGetCharPtr(u8 bgId);
void Convert4bppTo8bppInternal(u8 *src4bpp, u32 size, u8 (*dest8bpp), u8 paletteNum);
u8 *Convert4bppTo8bpp(u8 *src4Bpp, u32 size, u8 paletteNum, HeapID heapId);
void *GetBgTilemapBuffer(BgConfig *bgConfig, u8 bgId);
u16 GetBgAffineRotation(BgConfig *bgConfig, u8 bgId);
u8 GetBgPriority(BgConfig *bgConfig, u8 bgId);
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
struct Window *AllocWindows(HeapID heapId, s32 size);
void InitWindow(struct Window *window);
BOOL WindowIsInUse(struct Window *window);
void AddWindowParameterized(BgConfig *param0,
                            struct Window *window,
                            u8 bgId,
                            u8 tilemapLeft,
                            u8 tilemapTop,
                            u8 width,
                            u8 height,
                            u8 paletteNum,
                            u16 baseTile);
void AddTextWindowTopLeftCorner(BgConfig *param0,
                                struct Window *window,
                                u8 width,
                                u8 height,
                                u16 baseTile,
                                u8 paletteNum);
void AddWindow(BgConfig *bgConfig,
               struct Window *window,
               const struct WindowTemplate *template);
void RemoveWindow(struct Window *window);
void WindowArray_Delete(struct Window *windows, int count);
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
NNSG2dCharacterData * LoadCharacterDataFromFile(void **char_ret, HeapID heapId, const char *path);
NNSG2dPaletteData * LoadPaletteDataFromFile(void **pltt_ret, HeapID heapId, const char *path);
void DoScheduledBgGpuUpdates(BgConfig *bgConfig);
void DoScheduledBgTilemapBufferTransfers(BgConfig *bgConfig);
void ScheduleBgTilemapBufferTransfer(BgConfig *bgConfig, u8 bgId);
void ApplyScheduledBgPosUpdate(BgConfig *bgConfig);
void ScheduleSetBgPosText(BgConfig *bgConfig, u8 bgId, u32 op, fx32 value);
void ScheduleSetBgAffineRotation(BgConfig *bgConfig, u8 bgId, u32 op, u16 value);
void Bg_SetAffineRotation(struct Bg *bg, u32 op, u16 val);
void ScheduleSetBgAffinePos(BgConfig *bgConfig, u8 bgId, u32 op, fx32 value);
void Bg_SetAffinePos(struct Bg *bg, u32 op, fx32 val);
u32 DoesPixelAtScreenXYMatchPtrVal(BgConfig *bgConfig, u8 bgId, u8 x, u8 y, u16 *src);
void ApplyFlipFlagsToTile(BgConfig *bgConfig, u8 flag, u8 *src);

#endif // POKEDIAMOND_UNK_02016B94_H
