#ifndef POKEDIAMOND_PALETTE_H
#define POKEDIAMOND_PALETTE_H

#include "global.h"

#include "filesystem.h"
#include "unk_0200CA44.h"

struct PlttData {
    u16 r         : 5; // red
    u16 g         : 5; // green
    u16 b         : 5; // blue
    u16 unused_15 : 1;
};

struct PaletteFadeControl {
    u16 selectedPalettes;

    u16 delay   : 6;
    u16 y       : 5;
    u16 targetY : 5;

    u16 blendColor : 15;
    u16 yDec       : 1;

    u16 deltaY       : 4;
    u16 delayCounter : 6;
    u16 unk06_a      : 6;
};

struct Palette {
    u16 *unfadedBuf;
    u16 *fadedBuf;
    u32 bufSize;
    struct PaletteFadeControl fadeCtrl;
};

struct PaletteData {
    struct Palette pltt[14];

    u16 unk118_0           : 2;
    u16 activeFadePalettes : 14;
    u16 unk11a_0           : 14;
    u16 unk11a_e           : 1;
    u16 unk11a_f           : 1;
    u8 unk11c;
    u8 unk11d;
    u16 unk11e;
};

struct PaletteData *sub_02002FD0(HeapID heapId);
void sub_02002FEC(struct PaletteData *ptr);
void PaletteData_SetBuffers(
    struct PaletteData *paletteData, u32 index, void *unfadedBuf, void *fadedBuf, u32 size);
void PaletteData_AllocBuffers(struct PaletteData *paletteData, u32 index, u32 size, HeapID heapId);
void PaletteData_FreeBuffers(struct PaletteData *paletteData, u32 index);
void PaletteData_LoadPalette(
    struct PaletteData *paletteData, const void *src, u32 index, u32 offset, u16 size);
void PaletteData_LoadFromNarc(struct PaletteData *paletteData,
    NarcId narcId,
    s32 memberId,
    HeapID heapId,
    u32 index,
    u32 size,
    u16 offset,
    u16 param7);
void PaletteData_LoadNarc(struct PaletteData *paletteData,
    NarcId narcId,
    s32 memberId,
    HeapID heapId,
    u32 index,
    u32 size,
    u16 offset);
void sub_02003108(struct PaletteData *paletteData, u32 index, u16 offset, u32 size);
void CopyPaletteFromNarc(
    NarcId narcId, s32 memberId, HeapID heapId, u32 size, u16 offset, void *dest);
void PaletteData_CopyPalette(struct PaletteData *paletteData,
    u32 srcIdx,
    u16 srcOffset,
    u32 destIdx,
    u16 destOffset,
    u16 size);
u16 *PaletteData_GetUnfadedBuf(struct PaletteData *paletteData, u32 index);
u16 *PaletteData_GetFadedBuf(struct PaletteData *paletteData, u32 index);
u32 sub_02003210(struct PaletteData *paletteData,
    u16 param1,
    u16 param2,
    s16 delay,
    u8 startY,
    u8 targetY,
    u16 color);
u8 IsPaletteSelected(u16 selectedPalettes, u16 index);
void sub_02003328(struct PaletteData *param0, u16 param1);
void sub_02003368(s32 param0, struct Palette *param1, u16 *param2);
void sub_020033A4(struct PaletteFadeControl *paletteFade,
    u16 selectedPalettes,
    s16 delay,
    u8 startY,
    u8 targetY,
    u16 color);
void sub_02003464(SysTask *task, struct PaletteData *param1);
void sub_02003500(struct PaletteData *param0);
void sub_02003520(struct PaletteData *param0);
void sub_02003540(struct PaletteData *paletteData, u8 index, u32 param2);
void sub_0200359C(struct PaletteData *paletteData, u32 index, u32 param2);
void sub_020035F8(u16 *src, u16 *dest, struct PaletteFadeControl *fadeCtrl, u32 numEntries);
void sub_02003684(struct PaletteData *paletteData, u8 index, struct PaletteFadeControl *fadeCtrl);
void sub_0200372C(struct PaletteData *paletteData);
u16 sub_020038E4(struct PaletteData *paletteData);
void sub_020038F0(struct PaletteData *paletteData, u32 param1);
void PaletteData_FillPalette(struct PaletteData *paletteData,
    u32 index,
    u32 selection,
    u16 value,
    u16 startOffset,
    u16 endOffset);
void BlendPalette(u16 *src, u16 *dest, u16 numEntries, u8 coeff, u16 blendColor);
void BlendPaletteUnfaded(struct PaletteData *paletteData,
    u32 index,
    u16 offset,
    u16 numEntries,
    u8 coeff,
    u16 blendColor);
void BlendPalettes(u16 *src, u16 *dest, u16 selectedPalettes, u8 coeff, u16 blendColor);
void BlendPalettesUnfaded(
    struct PaletteData *paletteData, u32 index, u16 selectedPalettes, u8 coeff, u16 blendColor);
void TintPalette_CustomTone(u16 *palette, s32 count, s32 rTone, s32 gTone, s32 bTone);
void sub_02003B40(struct PaletteData *paletteData,
    NarcId narcId,
    s32 memberId,
    HeapID heapId,
    u32 index,
    u32 size,
    u16 offset,
    s32 rTone,
    s32 gTone,
    s32 bTone);

#endif // POKEDIAMOND_PALETTE_H
