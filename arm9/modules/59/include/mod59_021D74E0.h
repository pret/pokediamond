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
    u32 Unk0C;
    u32 Unk10;
    struct UnkStruct_02006234 *Unk14;
    struct BgConfig *bgConfig;
    u8 padding[0x10];
    u32 Unk2C;
    u8 padding2[0x1C];
    struct MsgData *msgData;
    u32 Unk50;
    u32 Unk54;
    u8 padding3[0x8];
    u32 Unk60; // unknown if this is the right type, possibly a pointer instead?
    struct ScrStrBufs *strBufs;
    u8 padding4[0x8];
    struct MOD59_UnkPlayerStruct *playerStruct;
    struct MOD59_UnkPlayerStruct *rivalStruct;
    u32 Unk78;
    u8 padding5[0xC];
    u8 Unk88;
    u8 Unk89;
    u8 Unk8A;
    u8 Unk8B;
    u8 padding6[4];
    u32 Unk90;
    u8 padding7[32];
} MOD59_OverlayData;

BOOL MOD59_Init(struct UnkStruct_02006234 *param0);
BOOL MOD59_021D7564(struct UnkStruct_02006234 *param0, u32 *param1);
BOOL MOD59_021D76C0(struct UnkStruct_02006234 *param0);
void MOD59_021D7724(MOD59_OverlayData *data);
BOOL MOD59_021D7730(void);
void MOD59_SetupBg(MOD59_OverlayData *data);
void MOD59_DestroyBg(MOD59_OverlayData *data);
void MOD59_SetupMsg(MOD59_OverlayData *data);

#endif //POKEDIAMOND_MOD59_021D74E0_H
