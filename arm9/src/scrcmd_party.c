#include "constants/moves.h"
#include "itemtool.h"
#include "map_header.h"
#include "module_05.h"
#include "party.h"
#include "save_block_2.h"
#include "scrcmd.h"
#include "script_pokemon_util.h"
#include "task.h"
#include "unk_02015CC0.h"
#include "unk_02022504.h"
#include "unk_0207FC5C.h"

extern u16 FUN_02054DEC(struct SaveBlock2* sav2);

THUMB_FUNC BOOL ScrCmd_GiveMon(struct ScriptContext* ctx) //0096 - todo: GivePokemon?
{
    u32 mapSec = MapHeader_GetMapSec(*(ctx->fieldSystem->mapId));
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 species = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 level = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 item = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 * varPtr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty * party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    *varPtr = (u16)GiveMon(11, fieldSystem->saveBlock2, species, (u8)level, item, mapSec, 12);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonSpecies(struct ScriptContext* ctx) //0198 - todo: GetPartyPokemonSpecies?
{
    u32 species;
    u16* ret_ptr;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* mon_slot = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, *mon_slot);

    BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
    if (party_mon_is_egg == FALSE)
    {
        species = GetMonData(party_mon, MON_DATA_SPECIES, NULL);
    }
    else
    {
        species = SPECIES_NONE;
    }

    *ret_ptr = (u16)species;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckPartyMonOTID(struct ScriptContext* ctx) //0199 - todo: CheckPartyPokemonTraded?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct SaveBlock2* sav2 = ScriptEnvironment_GetSav2Ptr(fieldSystem);
    struct PlayerData* player = Sav2_PlayerData_GetProfileAddr(sav2);

    u16* mon_slot = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, *mon_slot);

    u16 party_mon_otid = (u16)GetMonData(party_mon, MON_DATA_OTID, NULL);
    u16 player_otid = (u16)PlayerProfile_GetTrainerID(player);
    if (party_mon_otid == player_otid)
    {
        *ret_ptr = 0;
    }
    else
    {
        *ret_ptr = 1;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveEgg(struct ScriptContext* ctx) //0097
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct PlayerData* player = Sav2_PlayerData_GetProfileAddr(fieldSystem->saveBlock2);
    u16 species = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 unk = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    u8 party_count = (u8)GetPartyCount(party);

    if (party_count < PARTY_SIZE)
    {
        struct Pokemon* egg = AllocMonZeroed(11);
        ZeroMonData(egg);

        s32 met_loc = FUN_02015CF8(1, unk);
        MOD05_SetEggStats(egg, species, 1, player, 3, met_loc);

        AddMonToParty(party, egg);
        FreeToHeap(egg);
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetPartyMonMove(struct ScriptContext* ctx) //0098 - todo: ReplacePartyPokemonMove?
{
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 move_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 move = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);

    PartyMonSetMoveInSlot(party, mon_slot, move_slot, move);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PartyMonHasMove(struct ScriptContext* ctx) //0099
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 required_move = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = 0;

    BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
    if (party_mon_is_egg)
    {
        return FALSE;
    }

    if (required_move == GetMonData(party_mon, MON_DATA_MOVE1, NULL) ||
        required_move == GetMonData(party_mon, MON_DATA_MOVE2, NULL) ||
        required_move == GetMonData(party_mon, MON_DATA_MOVE3, NULL) ||
        required_move == GetMonData(party_mon, MON_DATA_MOVE4, NULL))
    {
        *ret_ptr = 1;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FindPartyMonWithMove(struct ScriptContext* ctx) //009A - todo: CheckMoveInParty?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 required_move = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u8 party_count = (u8)GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    u8 i;
    for (i = 0, *ret_ptr = PARTY_SIZE; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
        if (party_mon_is_egg == FALSE)
        {
            if (required_move == GetMonData(party_mon, MON_DATA_MOVE1, NULL) ||
                required_move == GetMonData(party_mon, MON_DATA_MOVE2, NULL) ||
                required_move == GetMonData(party_mon, MON_DATA_MOVE3, NULL) ||
                required_move == GetMonData(party_mon, MON_DATA_MOVE4, NULL))
            {
                *ret_ptr = i;
                break;
            }
        }
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SurvivePsn(struct ScriptContext* ctx) //01F7
{
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = (u16)SurvivePoisoning(party_mon);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountPartyMonsAtOrBelowLevel(struct ScriptContext* ctx) //01F6
{
    u8 party_count;
    u8 i;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 highest_level = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    party_count = (u8)GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    u8 mons;
    for (i = 0, mons = 0, *ret_ptr = 0; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
        if (party_mon_is_egg == FALSE)
        {
            u32 party_mon_level = GetMonData(party_mon, MON_DATA_LEVEL, NULL);
            if (party_mon_level <= highest_level)
            {
                mons++;
            }
        }
    }

    *ret_ptr = mons;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonLevel(struct ScriptContext* ctx) //0278
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = 0;

    BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
    if (party_mon_is_egg == FALSE)
    {
        *ret_ptr = (u16)GetMonData(party_mon, MON_DATA_LEVEL, NULL);
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonNature(struct ScriptContext* ctx) //0212
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u8 party_count = (u8)GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    if (mon_slot >= party_count)
    {
        *ret_ptr = 0;
        return FALSE;
    }

    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
    if (party_mon_is_egg)
    {
        *ret_ptr = 0;
        return FALSE;
    }

    *ret_ptr = GetMonNature(party_mon);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FindPartyMonWithNature(struct ScriptContext* ctx) //0213 - todo: CheckNatureInParty
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 required_nature = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u8 party_count = (u8)GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    u8 i;
    for (i = 0, *ret_ptr = 0xFF; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
        if (party_mon_is_egg == FALSE)
        {
            u8 party_mon_nature = GetMonNature(party_mon);
            if (required_nature == party_mon_nature)
            {
                *ret_ptr = i;
                break;
            }
        }
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonFriendship(struct ScriptContext* ctx) //01B9
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = (u16)GetMonData(party_mon, MON_DATA_FRIENDSHIP, NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_AddPartyMonFriendship(struct ScriptContext* ctx) //01BA
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 friendship_to_add = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 map_sec = MapHeader_GetMapSec(*ctx->fieldSystem->mapId);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    u16 friendship = (u16)GetMonData(party_mon, MON_DATA_FRIENDSHIP, NULL);

    if (friendship_to_add != 0)
    {
        u16 party_mon_held_item = (u16)GetMonData(party_mon, MON_DATA_HELD_ITEM, NULL);
        u32 held_item_hold_effect = GetItemAttr(party_mon_held_item, ITEMATTR_HOLD_EFFECT, 11);
        if (held_item_hold_effect == HOLD_EFFECT_FRIENDSHIP_UP)
        {
            friendship_to_add = (u16)((friendship_to_add * 150) / 100);
        }

        u32 party_mon_pokeball = GetMonData(party_mon, MON_DATA_POKEBALL, NULL);
        if (party_mon_pokeball == ITEM_LUXURY_BALL)
        {
            friendship_to_add++;
        }

        u32 party_mon_egg_met_location = GetMonData(party_mon, MON_DATA_EGG_MET_LOCATION, NULL);
        if (map_sec == party_mon_egg_met_location)
        {
            friendship_to_add++;
        }
    }

    friendship += friendship_to_add;
    if (friendship > 0xFF)
    {
        friendship = 0xFF;
    }

    SetMonData(party_mon, MON_DATA_FRIENDSHIP, &friendship);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SubtractPartyMonFriendship(struct ScriptContext* ctx) //01BB
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 friendship_to_deplete = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    u16 friendship = (u16)GetMonData(party_mon, MON_DATA_FRIENDSHIP, NULL);
    if (friendship_to_deplete > friendship)
    {
        friendship = 0;
    }
    else
    {
        friendship -= friendship_to_deplete;
    }

    SetMonData(party_mon, MON_DATA_FRIENDSHIP, &friendship);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonContestCondition(struct ScriptContext* ctx) //0281
{
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 contest_condition_id = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = (u16)GetMonData(party_mon, MON_DATA_COOL + contest_condition_id, NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetLeadingPartyMonSlot(struct ScriptContext* ctx) //0247
{
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

    *ret_ptr = FUN_02054DEC(ctx->fieldSystem->saveBlock2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonTypes(struct ScriptContext* ctx) //0248
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* type1 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* type2 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *type1 = (u16)GetMonData(party_mon, MON_DATA_TYPE_1, NULL);
    *type2 = (u16)GetMonData(party_mon, MON_DATA_TYPE_2, NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountPartyMons(struct ScriptContext* ctx) //0177
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);

    *ret_ptr = (u16)GetPartyCount(party);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountPartyMons_OmitEggs(struct ScriptContext* ctx) //019A
{
    u32 non_egg_mons;
    s32 i;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    s32 party_count = GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    for (i = 0, non_egg_mons = 0; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
        if (party_mon_is_egg == FALSE)
        {
            non_egg_mons++;
        }

    }

    *ret_ptr = (u16)non_egg_mons;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountAvailablePartyMons_IgnoreSlot(struct ScriptContext* ctx) //019B
{
    u16 slot_to_ignore;
    s32 party_count;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    slot_to_ignore = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    party_count = GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    u32 available_mons;
    s32 i;
    for (i = 0, available_mons = 0; i < party_count; i++)
    {
        if (i != slot_to_ignore)
        {
            struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
            struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

            BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
            if (party_mon_is_egg == FALSE)
            {
                u32 party_mon_hp = GetMonData(party_mon, MON_DATA_HP, NULL);
                if (party_mon_hp != 0)
                {
                    available_mons++;
                }
            }
        }
    }

    *ret_ptr = (u16)available_mons;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountAvailablePartyAndPCMons(struct ScriptContext* ctx) //019C
{
    s32 party_count;
    struct PCStorage* pc;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    pc = GetStoragePCPointer(fieldSystem->saveBlock2);
    party_count = GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    u32 mons;
    s32 i;
    for (i = 0, mons = 0; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
        if (party_mon_is_egg == FALSE)
        {
            u32 party_mon_hp = GetMonData(party_mon, MON_DATA_HP, NULL);
            if (party_mon_hp != 0)
            {
                mons++;
            }
        }
    }

    *ret_ptr = (u16)(mons + PCStorage_CountMonsInAllBoxes(pc));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyEggCount(struct ScriptContext* ctx) //019D
{
    s32 party_count;
    u32 eggs_in_party;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    party_count = GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    s32 i;
    for (i = 0, eggs_in_party = 0; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
        if (party_mon_is_egg)
        {
            eggs_in_party++;
        }
    }

    *ret_ptr = (u16)eggs_in_party;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckPartyForPokerus(struct ScriptContext* ctx) //0119
{
    u16 party_count;
    u16 i;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    party_count = (u16)GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    for (i = 0, *ret_ptr = 0; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_has_pokerus = (BOOL)GetMonData(party_mon, MON_DATA_POKERUS, NULL);
        if (party_mon_has_pokerus)
        {
            *ret_ptr = 1;
            break;
        }
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonGender(struct ScriptContext* ctx) //011A
{
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = (u16)GetMonData(party_mon, MON_DATA_GENDER, NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountPartyMonMoves(struct ScriptContext* ctx) //01C8
{
    struct Pokemon* party_mon;
    u8 moves;

    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    party_mon = GetPartyMonByIndex(party, mon_slot);

    BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
    if (party_mon_is_egg)
    {
        *ret_ptr = 0;
        return FALSE;
    }

    moves = 0;

    u32 move1 = GetMonData(party_mon, MON_DATA_MOVE1, NULL);
    if (move1 != MOVE_NONE)
    {
        moves++;
    }

    u32 move2 = GetMonData(party_mon, MON_DATA_MOVE2, NULL);
    if (move2 != MOVE_NONE)
    {
        moves++;
    }

    u32 move3 = GetMonData(party_mon, MON_DATA_MOVE3, NULL);
    if (move3 != MOVE_NONE)
    {
        moves++;
    }

    u32 move4 = GetMonData(party_mon, MON_DATA_MOVE4, NULL);
    if (move4 != MOVE_NONE)
    {
        moves++;
    }

    *ret_ptr = moves;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ForgetPartyMonMove(struct ScriptContext* ctx) //01C9
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 move_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    FUN_020699A4(party_mon, move_slot);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonMove(struct ScriptContext* ctx) //01CA
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 move_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = (u16)GetMonData(party_mon, MON_DATA_MOVE1 + move_slot, NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPartyMonHeldItem(struct ScriptContext* ctx) //01EE
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = (u16)GetMonData(party_mon, MON_DATA_HELD_ITEM, NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ResetPartyMonHeldItem(struct ScriptContext* ctx) //01F0
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    u16 party_mon_held_item = ITEM_NONE;
    SetMonData(party_mon, MON_DATA_HELD_ITEM, &party_mon_held_item);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckPartyForSpecies(struct ScriptContext* ctx) //01C0
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 species = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u8 party_count = (u8)GetPartyCount(SavArray_PlayerParty_get(fieldSystem->saveBlock2));

    u8 i;
    for (i = 0, *ret_ptr = 0; i < party_count; i++)
    {
        struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
        struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

        BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
        if (party_mon_is_egg == FALSE)
        {
            u16 party_mon_species = (u16)GetMonData(party_mon, MON_DATA_SPECIES, NULL);
            if (species == party_mon_species)
            {
                *ret_ptr = 1;
                break;
            }
        }
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountPartyMonRibbons(struct ScriptContext* ctx) //022E
{
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    u16 ribbon_idx;
    u16 ribbons;
    for (ribbon_idx = 0, ribbons = 0; ribbon_idx < 80; ribbon_idx++)
    {
        BOOL party_mon_has_ribbon = (BOOL)GetMonData(party_mon, FUN_0207FC5C((u8)ribbon_idx, 0), NULL);
        if (party_mon_has_ribbon)
        {
            ribbons++;
        }
    }

    *ret_ptr = ribbons;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CountTotalPartyRibbons(struct ScriptContext* ctx) //022F
{
    struct PlayerParty* party;
    u16 ribbon_idx;
    u16 ribbons;

    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 party_count = (u16)GetPartyCount(SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2));
    party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);

    for (ribbon_idx = 0, ribbons = 0; ribbon_idx < 80; ribbon_idx++)
    {
        for (u16 i = 0; i < party_count; i++)
        {
            struct Pokemon* party_mon = GetPartyMonByIndex(party, i);

            BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
            if (party_mon_is_egg)
            {
                // BUG: This `break` should be a `continue`, as any party mons after a detected
                //      egg would have their ribbons ignored.
                break;
            }

            BOOL party_mon_has_ribbon = (BOOL)GetMonData(party_mon, FUN_0207FC5C((u8)ribbon_idx, 0), NULL);
            if (party_mon_has_ribbon)
            {
                ribbons++;
                break;
            }
        }
    }

    *ret_ptr = ribbons;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PartyMonHasRibbon(struct ScriptContext* ctx) //0230
{
    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 ribbon_idx = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    *ret_ptr = (u16)GetMonData(party_mon, FUN_0207FC5C((u8)ribbon_idx, 0), NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GivePartyMonRibbon(struct ScriptContext* ctx) //0231
{
    u16 mon_slot = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 ribbon_idx = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u8 mon_has_ribbon = TRUE;
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* party_mon = GetPartyMonByIndex(party, mon_slot);

    SetMonData(party_mon, (s32)FUN_0207FC5C((u8)ribbon_idx, 0), &mon_has_ribbon);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckPartyForBadEgg(struct ScriptContext* ctx) //02B7
{
    u16 ribbon_idx;

    u16* ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 party_count = (u16)GetPartyCount(SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2));
    struct PlayerParty* party = SavArray_PlayerParty_get(ctx->fieldSystem->saveBlock2);

    // BUG: Probably a copy-paste fail. Checks if your party has a Bad Egg in it,
    //      80 times.
    for (ribbon_idx = 0; ribbon_idx < 80; ribbon_idx++)
    {
        for (u16 i = 0; i < party_count; i++)
        {
            struct Pokemon* party_mon = GetPartyMonByIndex(party, i);
            BOOL party_mon_is_egg = (BOOL)GetMonData(party_mon, MON_DATA_IS_EGG, NULL);
            if (party_mon_is_egg)
            {
                BOOL party_mon_is_bad_egg = (BOOL)GetMonData(party_mon, MON_DATA_CHECKSUM_FAILED, NULL);
                if (party_mon_is_bad_egg)
                {
                    *ret_ptr = 1;
                    return FALSE;
                }
            }
        }
    }

    *ret_ptr = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk00A0(struct ScriptContext* ctx) //00A0 - todo: DummyCountPartyPokemon
{
#pragma unused(ctx)
    return FALSE;
}
