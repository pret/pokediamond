#include "global.h"
#include "save_block_2.h"
#include "pokedex.h"
#include "pokemon.h"
#include "unk_0206BB28.h"

#pragma thumb on

BOOL FUN_0206BB28(struct SaveBlock2 * sav2)
{
    return FUN_0206BB34(Sav2_Pokedex_get(sav2));
}

BOOL FUN_0206BB34(struct Pokedex * pokedex)
{
    return Pokedex_GetNatDexFlag(pokedex) == TRUE;
}

u32 FUN_0206BB48(BOOL isNationalDex, u32 species)
{
    if (!isNationalDex)
        species = SpeciesToSinnohDexNo((u16)species);
    return species;
}

