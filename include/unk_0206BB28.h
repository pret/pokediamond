#ifndef POKEDIAMOND_UNK_0206BB28_H
#define POKEDIAMOND_UNK_0206BB28_H

#include "save_block_2.h"
#include "pokedex.h"
#include "pokemon.h"

BOOL SavArray_IsNatDexEnabled(struct SaveBlock2 * sav2);
BOOL Pokedex_IsNatDexEnabled(struct Pokedex * pokedex);
u32 FUN_0206BB48(BOOL isNationalDex, u32 species);

#endif //POKEDIAMOND_UNK_0206BB28_H
