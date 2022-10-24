#ifndef POKEDIAMOND_MOD59_021D74E0_H
#define POKEDIAMOND_MOD59_021D74E0_H

#include "nitro/types.h"
#include "options.h"
#include "save_block_2.h"
#include "main.h"
#include "player_data.h"

struct MOD59_UnkPlayerStruct
{
    u8 padding[0x4];
    GenderEnum gender;
    u8 padding2[0x10];
    struct String *name;
};

typedef struct MOD59_OverlayData
{
    u32 heap_id;
    struct SaveBlock2 *sav2;
    struct Options *options;
    u32 unk0C;
    u32 unk10;
    struct UnkStruct_02006234 *unk14;
    struct BgConfig *bgConfig;
    u8 filler1C[0x10];
    u32 unk2C;
    u8 filler30[0x1C];
    struct MsgData *msgData;
    u32 unk50;
    u32 unk54;
    u8 filler58[0x8];
    u32 unk60; // unknown if this is the right type, possibly a pointer instead?
    struct ScrStrBufs *strBufs;
    u32 unk68;
    u8 filler6C[0x4];
    struct MOD59_UnkPlayerStruct *playerStruct;
    struct MOD59_UnkPlayerStruct *rivalStruct;
    u32 unk78;
    u32 unk7C;
    u32 unk80;
    u8 filler84[0x4];
    u8 unk88;
    u8 unk89;
    u8 unk8A;
    u8 unk8B;
    u8 filler8C[4];
    u32 unk90;
    u8 filler94[32];
} MOD59_OverlayData;

BOOL MOD59_Init(struct UnkStruct_02006234 *param0);
BOOL MOD59_021D7564(struct UnkStruct_02006234 *param0, u32 *param1);
BOOL MOD59_021D76C0(struct UnkStruct_02006234 *param0);
void MOD59_021D7724(MOD59_OverlayData *data);
BOOL MOD59_021D7730(void);
void MOD59_SetupBg(MOD59_OverlayData *data);
void MOD59_DestroyBg(MOD59_OverlayData *data);
void MOD59_SetupMsg(MOD59_OverlayData *data);
void MOD59_DestroyMsg(MOD59_OverlayData *data);
void MOD59_021D7A4C(MOD59_OverlayData *data);
void MOD59_021D7A5C(MOD59_OverlayData *data);
BOOL MOD59_021D7A68(MOD59_OverlayData *data, u32 param1, u32 param2);

#endif //POKEDIAMOND_MOD59_021D74E0_H
