#ifndef GUARD_MAIN_H
#define GUARD_MAIN_H

#include "FS_overlay.h"
#include "SPI_pm.h"
#include "save_block_2.h"

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
    s32 * unk18;
    void * unk1C;
    struct SaveBlock2 * unk20;
    u32 unk24;
};

struct Unk2106FA0
{
    PMBackLightSwitch unk0;
    s32 unk4;
    FSOverlayID unk8;
    struct UnkStruct_02006234 *unkC;
    FSOverlayID unk10;
    const struct Unk21DBE18 * unk14;
    s32 unk18;
    s32 unk1C;
    struct SaveBlock2 * unk20;
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

struct UnkStruct_021C4918 {
    s32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 padding[3];
};

struct Main
{
    void (*vBlankIntr)(void *);
    void * vBlankIntrArg;
    void (*hBlankIntr)(void *);
    void * hBlankIntrArg;
    s32 unk10;
    s32 unk14;
    void * unk18;
    void * unk1C;
    void * unk20;
    void * unk24;
    s32 unk28;
    u32 unk2C;
    s32 unk30;
    u32 unk34;
    u32 unk38;
    u32 unk3C;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    u16 unk5C;
    u16 unk5E;
    u16 unk60;
    u16 unk62;
    u8 unk64;
    u8 unk65;
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 padding_69[3];
    s32 unk6C;
};

//extern struct UnkStruct_021C4918 gMain + 0x60;

extern struct Unk2106FA0 gBacklightTop;
extern struct Unk2106FA0 gBacklightTop_2; // same as the first one, it's referenced twice in the constant pool...

void NitroMain(void);

extern struct Main gMain;

void FUN_02000DF4(void);
void Main_RunOverlayManager(void);
void RegisterMainOverlay(FSOverlayID id, const struct Unk21DBE18 * arg1);
void FUN_02000E9C(void);
void FUN_02000EC8(u32 parameter);
void FUN_02000EE8(void);
void DoSoftReset(u32 parameter);
void FUN_02000F4C(u32 arg0, u32 arg1);
void InitializeMainRNG(void);
void HandleDSLidAction(void);

#endif //GUARD_MAIN_H
