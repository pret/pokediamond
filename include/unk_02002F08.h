#ifndef POKEDIAMOND_UNK_02002F08_H
#define POKEDIAMOND_UNK_02002F08_H

#include "global.h"
#include "gf_gfx_loader.h"
#include "string16.h"


struct PlttData
{
    u16 r:5; // red
    u16 g:5; // green
    u16 b:5; // blue
    u16 unused_15:1;
};

struct PaletteFadeControl
{
    u16 selectedPalettes;

    u16 delay : 6;
    u16 y : 5;
    u16 targetY : 5;

    u16 blendColor : 15;
    u16 yDec : 1;

    u16 deltaY : 4;
    u16 delayCounter : 6;
    u16 unk06_a : 6;
};

struct Palette
{
    u16 *unfadedBuf;
    u16 *fadedBuf;
    u32 bufSize;
    struct PaletteFadeControl fadeCtrl;
};

struct PaletteData
{
    struct Palette pltt[14];

    u16 unk118_0 : 2;
    u16 activeFadePalettes : 14;
    u16 unk11a_0 : 14;
    u16 unk11a_e : 1;
    u16 unk11a_f : 1;
    u8 unk11c;
    u8 unk11d;
    u16 unk11e;
};

s32 FUN_02002F08(u32 param0, struct String *str, u32 param2);
u32 FUN_02002F40(u32 param0, struct String *str, u32 param2, u32 param3);
u32 FUN_02002F58(const u16 *str);
u32 FUN_02002F90(struct String *str);
s32 FUN_02002F9C(u32 param0, struct String *str);
struct PaletteData *FUN_02002FD0(u32 heap_id);
void FUN_02002FEC(struct PaletteData *ptr);
void PaletteData_SetBuffers(struct PaletteData *paletteData, u32 index, void *unfadedBuf, void *fadedBuf, u32 size);
void PaletteData_AllocBuffers(struct PaletteData *paletteData, u32 index, u32 size, u32 heap_id);
void PaletteData_FreeBuffers(struct PaletteData *paletteData, u32 index);
void PaletteData_LoadPalette(struct PaletteData *paletteData, const void *src, u32 index, u32 offset, u16 size);
void PaletteData_LoadFromNarc(struct PaletteData *paletteData, NarcId narcId, s32 memberId, u32 heap_id, u32 index, u32 size, u16 offset, u16 param7);
void PaletteData_LoadNarc(struct PaletteData *paletteData, NarcId narcId, s32 memberId, u32 heap_id, u32 index, u32 size, u16 offset);

#endif // POKEDIAMOND_UNK_02002F08_H
