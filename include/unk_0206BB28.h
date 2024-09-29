#ifndef POKEDIAMOND_UNK_0206BB28_H
#define POKEDIAMOND_UNK_0206BB28_H

#include "pokedex.h"
#include "pokemon.h"
#include "save.h"

BOOL SaveArray_IsNatDexEnabled(struct SaveData *save);
BOOL Pokedex_IsNatDexEnabled(struct Pokedex *pokedex);
u32 Pokedex_ConvertToCurrentDexNo(BOOL isNationalDex, u32 species);

#endif // POKEDIAMOND_UNK_0206BB28_H
