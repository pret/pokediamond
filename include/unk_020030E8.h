#include "global.h"
#include "filesystem.h"
#include "unk_02002F08.h"

void FUN_02003108(struct PaletteData *param0, u32 param1, u16 param2, u32 param3);
void CopyPaletteFromNarc(NarcId narcId, s32 memberId, u32 heap_id, u32 size, u16 offset, void *dest);
void PaletteData_CopyPalette(
    struct PaletteData *param0, u32 param1, u16 param2, u32 param3, u16 param4, u16 param5);
u16 *PaletteData_GetUnfadedBuf(struct PaletteData *param0, u32 param1);
u16 *PaletteData_GetFadedBuf(struct PaletteData *param0, u32 param1);
u32 FUN_02003210(struct PaletteData *param0,
    u16 param1,
    u16 param2,
    s16 param3,
    u8 param6,
    u8 param7,
    u16 param8);
u8 IsPaletteSelected(u16 param0, u16 param1);
void FUN_02003328(struct PaletteData *param0, u16 param1);
void FUN_02003368(s32 param0, struct Palette *param1, u16 *param2);
void FUN_020033A4(struct PaletteFadeControl *param0,
    u16 param1,
    s16 param2,
    u8 param3,
    u8 param4,
    u16 param5);
void FUN_02003464(u32 param0, struct PaletteData *param1);
void FUN_02003500(struct PaletteData *param0);
void FUN_02003520(struct PaletteData *param0);
void FUN_02003540(struct PaletteData *param0, u8 param1, u32 param2);
void FUN_0200359C(struct PaletteData *param0, u32 param1, u32 param2);
void FUN_020035F8(u16 *param0, u16 *param1, struct PaletteFadeControl *param2, u32 param3);
void FUN_02003684(
    struct PaletteData *param0, u8 param1, struct PaletteFadeControl *param2);
void FUN_0200372C(struct PaletteData *param0);
u16 FUN_020038E4(struct PaletteData *param0);
void FUN_020038F0(struct PaletteData *param0, u32 param1);
void PaletteData_FillPalette(
    struct PaletteData *param0, u32 param1, u32 param2, u16 param3, u16 param4, u16 param5);
void BlendPalette(u16 *param0, u16 *param1, u16 param2, u8 param3, u16 param4);
void BlendPaletteUnfaded(
    struct PaletteData *param0, u32 param1, u16 param2, u16 param3, u8 param4, u16 param5);
void BlendPalettes(u16 *param0, u16 *param1, u16 param2, u8 param3, u16 param4);
void BlendPalettesUnfaded(struct PaletteData *param0, u32 param1, u16 param2, u8 param3, u16 param4);
void TintPalette_CustomTone(u16 *param0, u32 param1, u32 param2, u32 param3, u32 param4);
void FUN_02003B40(struct PaletteData *param0,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 param4,
    u32 param5,
    u16 param6,
    u32 param7,
    u32 param8,
    u32 param9);
