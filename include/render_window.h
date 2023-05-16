#ifndef POKEDIAMOND_UNK_0200CABC_H
#define POKEDIAMOND_UNK_0200CABC_H

#include "global.h"
#include "bg_window.h"
#include "pokemon.h"
#include "unk_02008DEC.h"

typedef struct WaitingIcon {
    struct Window *window;
    u8 unk004[9][0x80];
    u16 fillValue;
    u8 unk486;
    u8 unk487 : 7;
    u8 unk488 : 2;
} WaitingIcon;

struct UnkStruct_0200CABC_2
{
    u32 unk000;
    u8 unk004[0x12c];
    struct UnkStruct_02008DEC_1 *unk130;
    struct UnkStruct_02008DEC_1 *unk134;
    u8 unk138[0x2a];
    u16 unk162;
    u32 *unk164;
    struct BgConfig *bgConfig;
    u8 bgId;
    u8 x;
    u8 y;
    u8 unk16f;
};

struct UnkStruct_0200CABC_3
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
};

u32 FUN_0200CABC(struct BgConfig *bgConfig, u32 layer, u32 numTiles, u32 param3, u32 heap_id);
s32 FUN_0200CAFC(void);
void FUN_0200CB00(
    struct BgConfig *bg_config, u32 layer, u32 num_tiles, u32 param3, u8 frame_id, u32 heap_id);
void DrawFrame1(struct BgConfig *bgConfig,
    u8 bgId,
    u8 x,
    u8 y,
    u8 width,
    u8 height,
    u8 paletteNum,
    u16 fillValue);
void DrawFrameAndWindow1(struct Window *window, BOOL copy_to_vram, u16 fill_value, u8 palette_num);
void ClearFrameAndWindow1(struct Window *window, BOOL copy_to_vram);
s32 FUN_0200CD60(s32 param0);
s32 FUN_0200CD64(s32 param0);
void FUN_0200CD68(
    struct BgConfig *bg_config, u32 layer, u32 param2, u32 param3, u8 frame_id, u32 heap_id);
void DrawFrame2(struct BgConfig *bgConfig,
    u8 bgId,
    u8 x,
    u8 y,
    u8 width,
    u8 height,
    u8 paletteNum,
    u16 fillValue);
void DrawWindowFrame2(struct Window *window, u32 fill_value, u32 palette_num);
void DrawFrameAndWindow2(struct Window *window, BOOL copy_to_vram, u16 fill_value, u8 palette_num);
void ClearFrameAndWindow2(struct Window *window, BOOL param1);
void BlitRect4Bit(u8 *srcPixels,
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
    u16 height);
void FUN_0200D18C(struct Window *window, u16 fill_value);
void FUN_0200D274(
    struct BgConfig *bg_config, u8 bg_id, u16 param2, u8 param3, u8 param4, u32 heap_id);
void FUN_0200D300(struct BgConfig *bg_config,
    u8 bg_id,
    u16 numtiles,
    u8 param3,
    u8 param4,
    u16 param5,
    u32 heap_id);
void FUN_0200D378(
    struct BgConfig *bg_config, u8 bg_id, u16 numtiles, u8 param3, u16 param4, u32 heap_id);
void DrawFrame3(struct BgConfig *bgConfig,
    u8 bgId,
    u8 x,
    u8 y,
    u8 width,
    u8 height,
    u8 paletteNum,
    u16 fillValue);
void DrawWindowCorner(struct Window *window, u16 fillValue, u8 paletteNum);
void DrawFrameAndWindow3(struct Window *window, BOOL copy_to_vram, u16 fillValue, u8 paletteNum, u8 param4);
void ClearFrameAndWindow3(struct Window *window, u8 param1, BOOL copy_to_vram);
WaitingIcon *WaitingIcon_new(struct Window *window, u32 param1);
void FUN_0200D980(WaitingIcon *waitingIcon, u32 param1);
void FUN_0200DB7C(u32 param0, void *param1);
void FUN_0200DBE8(u32 param0, void *param1);
void FUN_0200DBFC(WaitingIcon *waitingIcon);
void FUN_0200DC24(WaitingIcon *waitingIcon);
u8 *FUN_0200DC4C(struct BgConfig *bg_config, u8 bg_id, u8 param2, u8 param3, u8 param4, u16 param5, u16 param6, u8 param7, s32 param8);
u8 *FUN_0200DCA4(struct BgConfig *bg_config,
    u8 bg_id,
    u8 param2,
    u8 param3,
    u8 param4,
    u16 param5,
    struct Pokemon *param6,
    s32 param7);
void FUN_0200DCF8(u32 param0, void *param1);
struct UnkStruct_0200CABC_2 *FUN_0200DD70(struct BgConfig *bg_config, u8 bg_id, u8 param2, u8 param3, u32 param4);
void FUN_0200DDAC(struct UnkStruct_0200CABC_2 *param0, u32 param1);
void FUN_0200DDD8(struct UnkStruct_0200CABC_2 *param0);
void FUN_0200DE30(struct UnkStruct_0200CABC_2 *param0, u8 param1, u8 param2);
void FUN_0200DE80(struct UnkStruct_0200CABC_2 *param0, u16 param1, u8 param2);
void FUN_0200DEC0(struct UnkStruct_0200CABC_2 *param0, struct Pokemon *param1);
void FUN_0200DEF4(struct UnkStruct_0200CABC_2 *param0, struct SomeDrawPokemonStruct *param1);
void DrawFramed10x10Square(struct UnkStruct_0200CABC_2 *param0, u8 paletteNum, u16 fillValue);
void ClearFramed10x10Square(struct UnkStruct_0200CABC_2 *param0);

#endif // POKEDIAMOND_UNK_0200CABC_H
