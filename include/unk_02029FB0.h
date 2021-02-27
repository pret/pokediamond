#ifndef POKEDIAMOND_UNK_02029FB0_H
#define POKEDIAMOND_UNK_02029FB0_H

#include "save_block_2.h"
#include "pokedex.h"
struct UnkStruct_02029FB0
{
    u8 unk[0x14C];
};

struct UnkStruct_02029FB0 * FUN_02029FC8(struct SaveBlock2 * sav2);
void FUN_0202A1C4(struct UnkStruct_02029FB0 * unk, struct Pokedex * pokedex, u16 species);

#endif //POKEDIAMOND_UNK_02029FB0_H
