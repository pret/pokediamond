#include "scrcmd.h"
#include "event_data.h"
#include "itemtool.h"
#include "nutdata.h"
#include "party.h"
#include "pokemon.h"
#include "player_data.h"
#include "script_buffers.h"
#include "unk_02024E64.h"
#include "unk_02064E4C.h"
#include "unk_0207FC5C.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem* fieldSystem, int idx);

extern u32 FUN_020536D0(u32 gender, u32 avatar, u32 a2);
extern u32 FUN_0205F388(struct ScriptState* state);
extern u32 FUN_0205F398(struct ScriptState* state);
extern struct PCStorage* GetStoragePCPointer(struct SaveBlock2* sav2);
extern u32 FUN_0205F3C0(struct ScriptState* state);
extern u32 FUN_02054C14(u32 number);

THUMB_FUNC BOOL ScrCmd_GetPlayerName(struct ScriptContext* ctx) //00CD - todo: BufferPlayerName? TextPlayerName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    struct SaveBlock2* sav2 = ScriptEnvironment_GetSav2Ptr(fieldSystem);
    struct PlayerData* player = Sav2_PlayerData_GetProfileAddr(sav2);

    BufferPlayersName(*mgr, idx, player);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetRivalName(struct ScriptContext* ctx) //00CE - todo: BufferRivalName? TextRivalName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);

    BufferRivalsName(*mgr, idx, fieldSystem->saveBlock2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetFriendName(struct ScriptContext* ctx) //00CF - todo: BufferFriendName? TextFriendName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);

    BufferFriendsName(*mgr, idx, fieldSystem->saveBlock2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPokemonName(struct ScriptContext* ctx) //00D0 - todo: BufferPartyPokemonName? TextPartyPokemonName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* mon = GetPartyMonByIndex(party, mon_idx);

    BufferBoxMonSpeciesName(*mgr, idx, &mon->box);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetItemName(struct ScriptContext* ctx) //00D1 - todo: BufferItemName? TextItemName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 item = ScriptGetVar(ctx);

    BufferItemName(*mgr, idx, item);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPocketName(struct ScriptContext* ctx) //00D2 - todo: BufferPocketName? TextPocketName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 pocket = ScriptGetVar(ctx);

    BufferPocketName(*mgr, idx, pocket);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetTMHMMoveName(struct ScriptContext* ctx) //00D3 - todo: BufferTMHMName? BufferMachineName? TextTMHMName? TextMachineName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 tmhm = ScriptGetVar(ctx);
    u16 move = TMHMGetMove(tmhm);

    BufferMoveName(*mgr, idx, move);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetMoveName(struct ScriptContext* ctx) //00D4 - todo: BufferMoveName? TextMoveName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 move = ScriptGetVar(ctx);

    BufferMoveName(*mgr, idx, move);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk00D5(struct ScriptContext* ctx) //00D5 - todo: BufferNumber? TextNumber?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 unk = ScriptGetVar(ctx);
    u32 digits = FUN_02054C14(unk);

    BufferIntegerAsString(*mgr, idx, unk, digits, 1, TRUE);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0280(struct ScriptContext* ctx) //0280 - todo: BufferNumberSpecial? need more info
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 unk = ScriptGetVar(ctx);
    u8 unk2 = ScriptReadByte(ctx);
    u8 digits = ScriptReadByte(ctx);
    if (unk2 == 0)
    {
        digits = (u8)FUN_02054C14(unk);
    }

    BufferIntegerAsString(*mgr, idx, unk, digits, unk2, TRUE);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPokemonNickname(struct ScriptContext* ctx) //00D6 - todo: BufferPartyPokemonNickname? TextPartyPokemonNickname?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);

    BufferBoxMonNickname(*mgr, idx, &pokemon->box);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0251(struct ScriptContext* ctx) //0251 - todo: BufferBoxPokemonNickname? TextBoxPokemonNickname?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct PCStorage* pc = GetStoragePCPointer(fieldSystem->saveBlock2);
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 box_mon_idx = ScriptGetVar(ctx);
    s32 box_no = box_mon_idx / 30;
    s32 slot_no = box_mon_idx % 30;
    struct BoxPokemon* box_mon = PCStorage_GetMonByIndexPair(pc, box_no, slot_no);

    BufferBoxMonNickname(*mgr, idx, box_mon);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPoketchAppName(struct ScriptContext* ctx) //00D7 - todo: BufferPoketchAppName? TextPoketchAppName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 app = ScriptGetVar(ctx);

    BufferPoketchAppName(*mgr, idx, app);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetTrainerClassName(struct ScriptContext* ctx) //00D8 - todo: BufferTrainerClassName? TextTrainerClassName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 trainer_class = ScriptGetVar(ctx);

    BufferTrainerClassName(*mgr, idx, trainer_class);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk00D9(struct ScriptContext* ctx) //00D9 - todo: BufferPlayerTrainerClassName? TextPlayerTrainerClassName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct SaveBlock2* sav2 = ScriptEnvironment_GetSav2Ptr(fieldSystem);
    struct PlayerData* player = Sav2_PlayerData_GetProfileAddr(sav2);
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u32 gender = PlayerProfile_GetTrainerGender(player);
    u32 avatar = PlayerProfile_GetAvatar(player);
    u32 trainer_class = FUN_020536D0(gender, avatar, 2);

    BufferTrainerClassNameWithArticle(*mgr, idx, trainer_class);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk00DA(struct ScriptContext* ctx) //00DA - todo: BufferPokemonSpeciesName? TextPokemonSpeciesName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 msg_no = ScriptGetVar(ctx);
    u16 unk1 = ScriptReadHalfword(ctx);
    u8 unk2 = ScriptReadByte(ctx);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*mgr, idx, str, unk1, unk2, 2);
    String_dtor(str);

    return FALSE;
}

THUMB_FUNC struct String* FUN_02040AE4(u32 msg_no, u32 heap_id) //todo: GetPokemonSpeciesName?
{
    struct MsgData* msg_data = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 362, heap_id); //todo change to NAIX
    struct String* ret = NewString_ReadMsgData(msg_data, msg_no);
    DestroyMsgData(msg_data);

    return ret;
}

THUMB_FUNC BOOL ScrCmd_GetPlayerStarterName(struct ScriptContext* ctx) //00DB - todo: BufferPlayerStarterSpecies?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SavArray_Flags_get(ctx->fieldSystem->saveBlock2);
    u32 msg_no = FUN_0205F388(state);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*mgr, idx, str, 0, 1, 2);
    String_dtor(str);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetRivalStarterName(struct ScriptContext* ctx) //00DC - todo: BufferRivalStarterSpecies?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SavArray_Flags_get(ctx->fieldSystem->saveBlock2);
    u32 msg_no = FUN_0205F398(state);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*mgr, idx, str, 0, 1, 2);
    String_dtor(str);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetCounterpartStarterName(struct ScriptContext* ctx) //00DD - todo: BufferFriendStarterSpecies?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SavArray_Flags_get(ctx->fieldSystem->saveBlock2);
    u32 msg_no = FUN_0205F3C0(state);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*mgr, idx, str, 0, 1, 2);
    String_dtor(str);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetDecorationName(struct ScriptContext* ctx) //00DF - todo: BufferDecorationName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 decoration = ScriptGetVar(ctx);

    BufferDecorationName(*mgr, idx, decoration);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetUndergroundTrapName(struct ScriptContext* ctx) //00E0 - todo: BufferUndergroundTrapName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_trap = ScriptGetVar(ctx);

    BufferUndergroundTrapName(*mgr, idx, underground_trap);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetUndergroundItemName(struct ScriptContext* ctx) //00E1 - todo: BufferUndergroundItemName? BufferTreasureName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_item = ScriptGetVar(ctx);

    BufferUndergroundItemName(*mgr, idx, underground_item);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetMapName(struct ScriptContext* ctx) //00E2 - todo: BufferMapName?
{
    struct String* str = String_ctor(22, 4);
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 map_no = ScriptGetVar(ctx);

    FUN_02064E60(map_no, 4, str);
    BufferString(*mgr, idx, str, 0, 1, 2);
    String_dtor(str);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetBerryName(struct ScriptContext* ctx) //017B - todo: BufferBerryName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 berry = ScriptGetVar(ctx);
    u16 unk = ScriptGetVar(ctx);
    struct String* nut_name = GetNutName((u16)(berry - FIRST_BERRY_IDX), 32);

    BufferString(*mgr, idx, nut_name, 0, unk < 2, 2);
    String_dtor(nut_name);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetNatureName(struct ScriptContext* ctx) //017C - todo: BufferNatureName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 nature = ScriptGetVar(ctx);

    BufferNatureName(*mgr, idx, nature);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetFashionName(struct ScriptContext* ctx) //0261 - todo: BufferAccessoryName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 fashion = ScriptGetVar(ctx);

    BufferFashionName(*mgr, idx, fashion);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetWhiteRockInscription(struct ScriptContext* ctx) //0272 - todo: BufferWhiteRockInscription?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    struct String* str = String_ctor(11, 11);
    struct UnkStruct_02024E64* unk = FUN_02024EB4(ctx->fieldSystem->saveBlock2);
    u16* unk_buffer = FUN_02024F0C(unk);

    CopyU16ArrayToString(str, unk_buffer);
    BufferString(*mgr, idx, str, 0, 0, gGameLanguage);
    String_dtor(str);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetPokemonMoveName(struct ScriptContext* ctx) //01CB - todo: BufferPartyPokemonMoveName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    u16 mon_move_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);
    u16 move = (u16)GetMonData(pokemon, MON_DATA_MOVE1 + mon_move_idx, NULL);

    BufferMoveName(*mgr, idx, move);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetRibbonName(struct ScriptContext* ctx) //0232 - todo: BufferRibbonName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u8 unk = (u8)ScriptGetVar(ctx);
    u16 ribbon = (u16)FUN_0207FC5C(unk, 3);

    BufferRibbonNameOrDesc(*mgr, idx, ribbon);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetSealName(struct ScriptContext* ctx) //02B3 - todo: BufferSealName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 seal = ScriptGetVar(ctx);

    BufferSealName(*mgr, idx, (u16)(seal - 1));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetItemNameWithIndefArticle(struct ScriptContext* ctx) //02C4 - todo: BufferIndefItemName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 item = ScriptGetVar(ctx);

    BufferItemNameWithIndefArticle(*mgr, idx, item);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetItemNamePlural(struct ScriptContext* ctx) //02C5 - todo: BufferPluralItemName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 item = ScriptGetVar(ctx);

    BufferItemNamePlural(*mgr, idx, item);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetDecorationNameWithArticle(struct ScriptContext* ctx) //02C6 - todo: BufferIndefDecorationName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 decoration = ScriptGetVar(ctx);

    BufferDecorationNameWithArticle(*mgr, idx, decoration);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetUndergroundTrapNameWithArticle(struct ScriptContext* ctx) //02C7 - todo: BufferIndefTrapName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_trap = ScriptGetVar(ctx);

    BufferUndergroundTrapNameWithArticle(*mgr, idx, underground_trap);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetUndergroundItemNameWithArticle(struct ScriptContext* ctx) //02C8 - todo: BufferIndefUndergroundItemName? BufferIndefTreasureName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_item = ScriptGetVar(ctx);

    BufferUndergroundItemNameWithArticle(*mgr, idx, underground_item);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk02C9(struct ScriptContext* ctx) //02C9 - todo: BufferIndefSpeciesName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 species = ScriptGetVar(ctx);
    u16 unused1 = ScriptReadHalfword(ctx);
    u8 unused2 = ScriptReadByte(ctx);

    BufferSpeciesNameWithArticle(*mgr, idx, species);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk02CA(struct ScriptContext* ctx) //02CA - todo: BufferIndefFriendStarterSpecies?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SavArray_Flags_get(ctx->fieldSystem->saveBlock2);
    u32 species = FUN_0205F3C0(state);

    BufferSpeciesNameWithArticle(*mgr, idx, species);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetFashionNameWithArticle(struct ScriptContext* ctx) //02CB - todo: BufferIndefAccessoryName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 fashion = ScriptGetVar(ctx);

    BufferFashionNameWithArticle(*mgr, idx, fashion);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk02CC(struct ScriptContext* ctx) //02CC - todo: BufferIndefTrainerClassName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 trainer_class = ScriptGetVar(ctx);

    BufferTrainerClassNameWithArticle(*mgr, idx, trainer_class);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetSealNamePlural(struct ScriptContext* ctx) //02CD - todo: BufferPluralSealName?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);
    u16 seal = ScriptGetVar(ctx);

    BufferSealNamePlural(*mgr, idx, (u16)(seal - 1));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CapitalizeFirstChar(struct ScriptContext* ctx) //02CE - todo CapitalizeText?
{
    struct ScrStrBufs** mgr = FieldSysGetAttrAddr(ctx->fieldSystem, 15);
    u8 idx = ScriptReadByte(ctx);

    ScrStrBufs_UpperFirstChar(*mgr, idx);

    return FALSE;
}
