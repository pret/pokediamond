#include "global.h"
#include "save_block_2.h"
#include "pokedex.h"
#include "pokemon.h"
#include "unk_0206BB28.h"

BOOL SaveArray_IsNatDexEnabled(struct SaveBlock2 * sav2)
{
    return Pokedex_IsNatDexEnabled(Save_Pokedex_Get(sav2));
}

BOOL Pokedex_IsNatDexEnabled(struct Pokedex * pokedex)
{
    return Pokedex_GetNatDexFlag(pokedex) == TRUE;
}

u32 FUN_0206BB48(BOOL isNationalDex, u32 species)
{
    if (!isNationalDex)
        species = SpeciesToSinnohDexNo((u16)species);
    return species;
}

