#ifndef POKEDIAMOND_MOD59_021D74E0_H
#define POKEDIAMOND_MOD59_021D74E0_H

#include "nitro/types.h"
#include "options.h"
#include "save_block_2.h"
#include "main.h"

typedef struct MOD59_OverlayData
{
    u32 heap_id;
    struct SaveBlock2 *sav2;
    struct Options *options;
    u32 Unk0C;
    u32 Unk10;
    u32 Unk14;
    u8 padding[0x58];
    u32 Unk70;
    u32 Unk74;
    u8 padding2[0x10];
    u8 Unk88;
    u8 Unk89;
    u8 Unk8A;
    u8 Unk8B;
    u8 padding3[4];
    u32 Unk90;
    //TODO pad to 0xb4
} MOD59_OverlayData;

BOOL MOD59_Init(struct UnkStruct_02006234 *param0);

#endif //POKEDIAMOND_MOD59_021D74E0_H
