#include "global.h"
#include "heap.h"
#include "party.h"
#include "player_data.h"
#include "pokemon.h"
#include "save_block_2.h"
#include "unk_0202C144.h"
#include "constants/items.h"

#pragma thumb on

BOOL MonNotFaintedOrEgg(struct Pokemon * pokemon)
{
    if (GetMonData(pokemon, MON_DATA_HP, NULL) == 0)
        return FALSE;
    if (GetMonData(pokemon, MON_DATA_IS_EGG, NULL))
        return FALSE;   
    return TRUE;
}

BOOL GiveMon(u32 heap_id, struct SaveBlock2 * sav2, u16 species, u8 level, u16 item, u32 mapSec, u32 encounterType)
{
    u32 ptr;
    struct PlayerData * data = Sav2_PlayerData_GetProfileAddr(sav2);
    struct PlayerParty * party = SavArray_PlayerParty_get(sav2);
    struct Pokemon * mon = AllocMonZeroed(heap_id);
    ZeroMonData(mon);
    CreateMon(mon, species, level, 32, 0, 0, OT_ID_PLAYER_ID, 0);
    FUN_0206A014(mon, data, ITEM_POKE_BALL, mapSec, encounterType, heap_id);
    ptr = item;
    SetMonData(mon, MON_DATA_HELD_ITEM, &ptr);
    BOOL isAdded = AddMonToParty(party, mon);
    if (isAdded)
    {
        FUN_0202C144(sav2, mon);
    }
    FreeToHeap(mon);
    return isAdded;
}
