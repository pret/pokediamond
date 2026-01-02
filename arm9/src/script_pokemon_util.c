#include "script_pokemon_util.h"

#include "global.h"

#include "constants/items.h"
#include "constants/script_pokemon_util.h"

#include "heap.h"
#include "overlay_05.h"
#include "party.h"
#include "player_data.h"
#include "pokemon.h"
#include "save.h"
#include "unk_02015CC0.h"
#include "unk_0202C144.h"

BOOL MonNotFaintedOrEgg(struct Pokemon *pokemon) {
    if (Pokemon_GetData(pokemon, MON_DATA_HP, NULL) == 0) {
        return FALSE;
    }
    if (Pokemon_GetData(pokemon, MON_DATA_IS_EGG, NULL)) {
        return FALSE;
    }
    return TRUE;
}

BOOL GiveMon(enum HeapID heapID, struct SaveData *save, u16 species, u8 level, u16 item, u32 mapSec, u32 encounterType) {
    u32 ptr;
    PlayerProfile *data = Save_PlayerData_GetProfile(save);
    struct Party *party = SaveArray_Party_Get(save);
    struct Pokemon *mon = Pokemon_New(heapID);
    Pokemon_Init(mon);
    Pokemon_InitWithParams(mon, species, level, INIT_IVS_RANDOM, 0, 0, OT_ID_PLAYER_ID, 0);
    sub_0206A014(mon, data, ITEM_POKE_BALL, mapSec, encounterType, heapID);
    ptr = item;
    Pokemon_SetData(mon, MON_DATA_HELD_ITEM, &ptr);
    BOOL isAdded = Party_AddMon(party, mon);
    if (isAdded) {
        sub_0202C144(save, mon);
    }
    Heap_Free(mon);
    return isAdded;
}

/* Seems to have something to do with Manaphy Egg*/
BOOL GiveEgg(enum HeapID heapID, struct SaveData *save, u16 species, int level, int metLocIndex, int a3) {
#pragma unused(heapID)
    PlayerProfile *data = Save_PlayerData_GetProfile(save);
    struct Party *party = SaveArray_Party_Get(save);
    struct Pokemon *mon = Pokemon_New(HEAP_ID_32);
    Pokemon_Init(mon);
    ov05_SetEggStats(mon, species, level, data, 4, sub_02015CF8(metLocIndex, a3));
    BOOL isAdded = Party_AddMon(party, mon);
    Heap_Free(mon);
    return isAdded;
}

void PartyMonSetMoveInSlot(struct Party *party, int partySlot, int moveSlot, u16 move) {
    struct Pokemon *mon = Party_GetMonByIndex(party, partySlot);
    Pokemon_SetMoveInSlot(mon, move, (u8)moveSlot);
}

int GetIdxOfFirstPartyMonWithMove(struct Party *party, int move) {
    int partyCount = Party_GetCount(party);

    for (int i = 0; i < partyCount; i++) {
        struct Pokemon *mon = Party_GetMonByIndex(party, i);

        if (Pokemon_GetData(mon, MON_DATA_IS_EGG, NULL)) {
            continue;
        }
        if (Pokemon_GetData(mon, MON_DATA_MOVE1, NULL) == move
            || Pokemon_GetData(mon, MON_DATA_MOVE2, NULL) == move
            || Pokemon_GetData(mon, MON_DATA_MOVE3, NULL) == move
            || Pokemon_GetData(mon, MON_DATA_MOVE4, NULL) == move) {
            return i;
        }
    }
    return 0xFF;
}

int CountAlivePokemon(struct Party *party) {
    int partyCount = Party_GetCount(party);
    int i;
    int aliveCount = 0;

    for (i = 0; i < partyCount; i++) {
        struct Pokemon *mon = Party_GetMonByIndex(party, i);

        if (MonNotFaintedOrEgg(mon)) {
            aliveCount++;
        }
    }
    return aliveCount;
}

struct Pokemon *GetFirstAliveMonInParty_CrashIfNone(struct Party *party) {
    int i;
    int partyCount = Party_GetCount(party);

    for (i = 0; i < partyCount; i++) {
        struct Pokemon *mon = Party_GetMonByIndex(party, i);

        if (MonNotFaintedOrEgg(mon)) {
            return mon;
        }
    }
    GF_ASSERT(0);
    return 0;
}

struct Pokemon *GetFirstNonEggInParty(struct Party *party) {
    u16 i;
    u16 partyCount = (u16)Party_GetCount(party);

    for (i = 0; i < partyCount; i++) {
        struct Pokemon *mon = Party_GetMonByIndex(party, i);

        if (!Pokemon_GetData(mon, MON_DATA_IS_EGG, NULL)) {
            return mon;
        }
    }
    return 0;
}

BOOL HasEnoughAlivePokemonForDoubleBattle(struct Party *party) {
    return CountAlivePokemon(party) >= 2;
}

void GiveAllMonsTheSinnohChampRibbon(struct Party *party) {
    u8 var = 1;
    int partyCount = Party_GetCount(party);

    for (int i = 0; i < partyCount; i++) {
        struct Pokemon *mon = Party_GetMonByIndex(party, i);

        if (Pokemon_GetData(mon, MON_DATA_IS_EGG, NULL)) {
            continue;
        }

        Pokemon_SetData(mon, MON_DATA_SINNOH_CHAMP_RIBBON, &var);
    }
}

int ApplyPoisonStep(struct Party *party, int location) {
    u32 hp;
    int numPoisoned = 0;
    int numHealed = 0;
    int partyCount = Party_GetCount(party);

    for (int i = 0; i < partyCount; i++) {
        struct Pokemon *mon = Party_GetMonByIndex(party, i);

        if (!MonNotFaintedOrEgg(mon)) {
            continue;
        }

        if (!(Pokemon_GetData(mon, MON_DATA_STATUS, NULL) & 0x88)) {
            continue;
        }

        hp = Pokemon_GetData(mon, MON_DATA_HP, NULL);
        if (hp > 1) {
            hp--;
        }
        Pokemon_SetData(mon, MON_DATA_HP, &hp);
        if (hp == 1) {
            numHealed++;
            Pokemon_UpdateFriendship(mon, FRIENDSHIP_EVENT_POISON_SURVIVE, (u32)location);
        }
        numPoisoned++;
    }

    if (numHealed != 0) {
        return FLDPSN_HEAL;
    }

    if (numPoisoned != 0) {
        return FLDPSN_PSN;
    }

    return FLDPSN_NONE;
}

BOOL SurvivePoisoning(struct Pokemon *mon) {
    int status;
    if (Pokemon_GetData(mon, MON_DATA_STATUS, NULL) & 0x88) {
        if (Pokemon_GetData(mon, MON_DATA_HP, NULL) == 1) {
            status = 0;
            Pokemon_SetData(mon, MON_DATA_STATUS, &status);
            return TRUE;
        }
    }
    return FALSE;
}
