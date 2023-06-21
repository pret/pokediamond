#include "global.h"
#include "pokedex.h"
#include "poketch.h"
#include "unk_02029FB0.h"
#include "unk_0202C144.h"

void FUN_0202C144(struct SaveData * save, struct Pokemon * mon)
{
    u32 is_egg = GetMonData(mon, MON_DATA_IS_EGG, NULL);
    if (!is_egg)
    {
        struct Pokedex * pokedex = Save_Pokedex_Get(save);
        struct GameStats * unk = Save_GameStats_Get(save);
        u32 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
        GameStats_IncSpeciesCaught(unk, pokedex, (u16) species);
        Pokedex_SetMonCaughtFlag(pokedex, mon);

        struct Poketch * poketch = Save_Poketch_Get(save);
        Save_Poketch_PokemonHistoryAddMon(poketch, &mon->box);
    }
}
