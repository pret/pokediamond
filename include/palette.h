#ifndef POKEDIAMOND_PALETTE_H
#define POKEDIAMOND_PALETTE_H

#include "global.h"
#include "filesystem.h"
#include "unk_02002F08.h"

void FUN_02003108(struct PaletteData *paletteData, u32 index, u16 offset, u32 size);
void CopyPaletteFromNarc(
    NarcId narcId, s32 memberId, u32 heap_id, u32 size, u16 offset, void *dest);
void PaletteData_CopyPalette(struct PaletteData *paletteData,
    u32 srcIdx,
    u16 srcOffset,
    u32 destIdx,
    u16 destOffset,
    u16 size);
u16 *PaletteData_GetUnfadedBuf(struct PaletteData *paletteData, u32 index);
u16 *PaletteData_GetFadedBuf(struct PaletteData *paletteData, u32 index);
u32 FUN_02003210(struct PaletteData *paletteData,
    u16 param1,
    u16 param2,
    s16 delay,
    u8 startY,
    u8 targetY,
    u16 color);
u8 IsPaletteSelected(u16 selectedPalettes, u16 index);
void FUN_02003328(struct PaletteData *param0, u16 param1);
void FUN_02003368(s32 param0, struct Palette *param1, u16 *param2);
void FUN_020033A4(struct PaletteFadeControl *paletteFade,
    u16 selectedPalettes,
    s16 delay,
    u8 startY,
    u8 targetY,
    u16 color);
void FUN_02003464(u32 param0, struct PaletteData *param1);
void FUN_02003500(struct PaletteData *param0);
void FUN_02003520(struct PaletteData *param0);
void FUN_02003540(struct PaletteData *paletteData, u8 index, u32 param2);
void FUN_0200359C(struct PaletteData *paletteData, u32 index, u32 param2);
void FUN_020035F8(u16 *src, u16 *dest, struct PaletteFadeControl *fadeCtrl, u32 numEntries);
void FUN_02003684(struct PaletteData *paletteData, u8 index, struct PaletteFadeControl *fadeCtrl);
void FUN_0200372C(struct PaletteData *paletteData);
u16 FUN_020038E4(struct PaletteData *paletteData);
void FUN_020038F0(struct PaletteData *paletteData, u32 param1);
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
void TintPalette_CustomTone(u16 *palette, u32 count, u32 rTone, u32 gTone, u32 bTone);
void FUN_02003B40(struct PaletteData *paletteData,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 index,
    u32 size,
    u16 offset,
    u32 rTone,
    u32 gTone,
    u32 bTone);

#endif // POKEDIAMOND_PALETTE_H
