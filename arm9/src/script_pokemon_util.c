#include "global.h"
#include "heap.h"
#include "party.h"
#include "player_data.h"
#include "pokemon.h"
#include "save_block_2.h"
#include "unk_02015CC0.h"
#include "unk_0202C144.h"
#include "module_05.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/script_pokemon_util.h"

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

/* Seems to have something to do with Manaphy Egg*/
BOOL GiveEgg(u32 heapId, struct SaveBlock2 * sav2, u16 species, int level, int metLocIndex, int a3)
{
#pragma unused(heapId)
    struct PlayerData * data = Sav2_PlayerData_GetProfileAddr(sav2);
    struct PlayerParty * party = SavArray_PlayerParty_get(sav2);
    struct Pokemon * mon = AllocMonZeroed(32);
    ZeroMonData(mon);
    MOD05_SetEggStats(mon, species, level, data, 4, FUN_02015CF8(metLocIndex, a3));
    BOOL isAdded = AddMonToParty(party, mon);
    FreeToHeap(mon);
    return isAdded;
}

void PartyMonSetMoveInSlot(struct PlayerParty * party, int partySlot, int moveSlot, u16 move)
{
    struct Pokemon * mon = GetPartyMonByIndex(party, partySlot);
    MonSetMoveInSlot(mon, move, (u8)moveSlot);
}

int GetIdxOfFirstPartyMonWithMove(struct PlayerParty * party, int move)
{
    int partyCount = GetPartyCount(party);

    for (int i = 0; i < partyCount; i++)
    {
        struct Pokemon * mon = GetPartyMonByIndex(party, i);
        
        if (GetMonData(mon, MON_DATA_IS_EGG, NULL))
            continue;
        if (GetMonData(mon, MON_DATA_MOVE1, NULL) == move
            || GetMonData(mon, MON_DATA_MOVE2, NULL) == move
            || GetMonData(mon, MON_DATA_MOVE3, NULL) == move
            || GetMonData(mon, MON_DATA_MOVE4, NULL) == move)
            return i;
    }
    return 0xFF;
}

int CountAlivePokemon(struct PlayerParty * party)
{
    int partyCount = GetPartyCount(party);
    int i;
    int aliveCount = 0;

    for (i = 0; i < partyCount; i++)
    {
        struct Pokemon * mon = GetPartyMonByIndex(party, i);
        
        if(MonNotFaintedOrEgg(mon))
            aliveCount++;
    }
    return aliveCount;
}

struct Pokemon * GetFirstAliveMonInParty_CrashIfNone(struct PlayerParty * party)
{
    int i;
    int partyCount = GetPartyCount(party);

    for (i = 0; i < partyCount; i++)
    {
        struct Pokemon * mon = GetPartyMonByIndex(party, i);
        
        if(MonNotFaintedOrEgg(mon))
            return mon;
    }
    ErrorHandling();
    return 0;
}

struct Pokemon * GetFirstNonEggInParty(struct PlayerParty * party)
{
    u16 i;
    u16 partyCount = (u16)GetPartyCount(party);

    for (i = 0; i < partyCount; i++)
    {
        struct Pokemon * mon = GetPartyMonByIndex(party, i);

        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL))
            return mon;
    }
    return 0;
}

BOOL HasEnoughAlivePokemonForDoubleBattle(struct PlayerParty * party)
{
    return (CountAlivePokemon(party) >= 2);
}

void GiveAllMonsTheSinnohChampRibbon(struct PlayerParty * party)
{
    u8 var = 1;
    int partyCount = GetPartyCount(party);
    

    for (int i = 0; i < partyCount; i++)
    {
        struct Pokemon * mon = GetPartyMonByIndex(party, i);
        
        if (GetMonData(mon, MON_DATA_IS_EGG, NULL))
            continue;

        SetMonData(mon, MON_DATA_SINNOH_CHAMP_RIBBON, &var);
    }
}

int ApplyPoisonStep(struct PlayerParty * party, int location)
{
    u32 hp;
    int numPoisoned = 0;
    int numHealed = 0;
    int partyCount = GetPartyCount(party);   

    for (int i = 0; i < partyCount; i++)
    {
        struct Pokemon * mon = GetPartyMonByIndex(party, i);
        
        if(!MonNotFaintedOrEgg(mon))
            continue;

        if (!(GetMonData(mon, MON_DATA_STATUS, NULL) & 0x88))
            continue;

        hp = GetMonData(mon, MON_DATA_HP, NULL);
        if (hp > 1)
            hp--;
        SetMonData(mon, MON_DATA_HP, &hp);
        if (hp == 1)
        {
            numHealed++;
            MonApplyFriendshipMod(mon, FRIENDSHIP_EVENT_HEAL_FIELD_PSN, (u32)location);
        }
        numPoisoned++;
    }

    if (numHealed != 0)
        return FLDPSN_HEAL;
    
    if (numPoisoned != 0)
        return FLDPSN_PSN;
    
    return FLDPSN_NONE;
}

BOOL SurvivePoisoning(struct Pokemon * mon)
{
    int status;
    if (GetMonData(mon, MON_DATA_STATUS, NULL) & 0x88)
    {
        if (GetMonData(mon, MON_DATA_HP, NULL) == 1)
        {
            status = 0;
            SetMonData(mon, MON_DATA_STATUS, &status);
            return TRUE;
        }
    }
    return FALSE;
}
