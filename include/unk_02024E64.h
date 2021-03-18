#ifndef POKEDIAMOND_UNK_02024E64_H
#define POKEDIAMOND_UNK_02024E64_H

#include "global.h"
#include "MI_memory.h"
#include "save_block_2.h"
#include "string16.h"

struct UnkStruct_02024E64 {
    u8 unk0[0xE][0x80];
    u8 unk700[0x24];
    u16 rival_name_buf[0x8];
    u16 unk734[0xB];
    u8 unk74A[2]; // might be padding
};

THUMB_FUNC u32 FUN_02024E64();
THUMB_FUNC void FUN_02024E6C(struct UnkStruct_02024E64 *param0);
THUMB_FUNC struct UnkStruct_02024E64 *FUN_02024EB4(struct SaveBlock2 *sav2);
THUMB_FUNC void *FUN_02024EC0(struct SaveBlock2 *sav2);
THUMB_FUNC struct UnkStruct_02024E64 *FUN_02024ECC(struct SaveBlock2 *sav2);
THUMB_FUNC void *FUN_02024ED8(struct SaveBlock2 *sav2);
THUMB_FUNC u16 *GetRivalNamePtr(struct UnkStruct_02024E64 *unk);
THUMB_FUNC void RivalsNameToU16Array(struct UnkStruct_02024E64 *unk, struct String *str);
THUMB_FUNC u16 *FUN_02024F0C(struct UnkStruct_02024E64 *unk);
THUMB_FUNC void FUN_02024F18(struct UnkStruct_02024E64 *unk, struct String *str);

#endif
