#ifndef POKEDIAMOND_UNK_02029FB0_H
#define POKEDIAMOND_UNK_02029FB0_H

struct Pokedex;

struct UnkStruct_02029FB0
{
    u32 unk_00[0x2C];
    u16 unk_B0[0x4D];
};

struct UnkStruct_02029FB0 * FUN_02029FC8(struct SaveBlock2 * sav2);
void FUN_0202A1C4(struct UnkStruct_02029FB0 * unk, struct Pokedex * pokedex, u16 species);

#endif //POKEDIAMOND_UNK_02029FB0_H
