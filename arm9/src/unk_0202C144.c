#include "global.h"
#include "pokemon.h"
#include "pokedex.h"
#include "save_block_2.h"
#include "unk_02029FBO.h"
#include "poketch.h"

THUMB_FUNC void FUN_0202C144(struct SaveBlock2 *sav2, struct Pokemon *pokemon) {
    if (GetMonData(pokemon, MON_DATA_IS_EGG, NULL) == 0)
    {
        struct Pokedex *pokedex = Sav2_Pokedex_get(sav2);
        void *unkSavStruct = FUN_02029FC8(sav2); /* SavArray_get(sav2, 20) */

        FUN_0202A1C4(unkSavStruct, pokedex, GetMonData(pokemon, MON_DATA_SPECIES, NULL));
        Pokedex_SetMonCaughtFlag(pokedex, pokemon);
        Sav2_Poketch_PokemonHistoryAddMon(Sav2_Poketch_get(sav2), &pokemon->box);
    }
} 