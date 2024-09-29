#include "unk_0206BB28.h"

#include "global.h"

#include "pokedex.h"
#include "pokemon.h"
#include "save.h"

BOOL SaveArray_IsNatDexEnabled(struct SaveData *save) {
    return Pokedex_IsNatDexEnabled(Save_Pokedex_Get(save));
}

BOOL Pokedex_IsNatDexEnabled(struct Pokedex *pokedex) {
    return Pokedex_GetNatDexFlag(pokedex) == TRUE;
}

u32 Pokedex_ConvertToCurrentDexNo(BOOL isNationalDex, u32 species) {
    if (!isNationalDex) {
        species = SpeciesToSinnohDexNo((u16)species);
    }
    return species;
}
