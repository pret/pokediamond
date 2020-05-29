#ifndef GUARD_MAIN_H
#define GUARD_MAIN_H

#include "FS_overlay.h"
#include "SPI_pm.h"
#include "structs.h"

struct UnkStruct_02006234;

struct Unk21DBE18
{
    BOOL (*unk0)(struct UnkStruct_02006234 *, u32 *);
    BOOL (*unk4)(struct UnkStruct_02006234 *, u32 *);
    BOOL (*unk8)(struct UnkStruct_02006234 *, u32 *);
    FSOverlayID ovly;
};

struct UnkStruct_02006234
{
    struct Unk21DBE18 ovly_mgr;
    u32 unk10;
    u32 unk14;
    int * unk18;
    void * unk1C;
    u32 unk20;
    u32 unk24;
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
    struct UnkStruct_021C59C8 * unk20;
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
    u32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 filler3C[0xC];
    s32 unk48;
    u8 filler4C[0x20];
    s32 unk6C;
};

struct UnkStruct_021C4918 {
    s32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 padding[3];
};

extern struct UnkStruct_021C4918 gUnk021C4918;

extern struct Unk2106FA0 gBacklightTop;
extern struct Unk2106FA0 gBacklightTop_2; // same as the first one, it's referenced twice in the constant pool...

void NitroMain(void);

extern struct Unk21C48B8 gUnknown21C48B8;

void FUN_02000DF4(void);
void FUN_02000E0C(void);
void FUN_02000E7C(FSOverlayID id, struct Unk21DBE18 * arg1);
void FUN_02000E9C(void);
void FUN_02000EC8(u32 parameter);
void FUN_02000EE8(void);
void DoSoftReset(u32 parameter);
void FUN_02000F4C(u32 arg0, u32 arg1);
void InitializeMainRNG(void);
void FUN_02000FE8(void);

#endif //GUARD_MAIN_H
