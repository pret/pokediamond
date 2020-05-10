#ifndef GUARD_MAIN_H
#define GUARD_MAIN_H

#include "FS_overlay.h"
#include "SPI_pm.h"

struct Unk21DBE18
{
    u8 filler_00[16];
};

struct Unk2106FA0
{
    PMBackLightSwitch unk0;
    s32 unk4;
    FSOverlayID unk8;
    s32 unkC;
    FSOverlayID unk10;
    struct Unk21DBE18 * unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
};

struct Unk21C4818
{
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

struct Unk21C4828
{
    u32 unk0;
    u32 unk4;
    u32 unk8;
};

struct Unk21C48B8
{
    void (*unk0)(s32);
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 filler3C[0xC];
    s32 unk48;
    u8 filler4C[0x20];
    s32 unk6C;
};

extern struct Unk2106FA0 gBacklightTop;
extern struct Unk2106FA0 gBacklightTop_2; // same as the first one, it's referenced twice in the constant pool...

#endif //GUARD_MAIN_H
