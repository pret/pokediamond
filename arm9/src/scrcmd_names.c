#include "global.h"
#include "event_data.h"
#include "itemtool.h"
#include "message_format.h"
#include "nutdata.h"
#include "party.h"
#include "player_data.h"
#include "pokemon.h"
#include "scrcmd.h"
#include "unk_02024E64.h"
#include "unk_02064E4C.h"
#include "unk_0207FC5C.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem* fieldSystem, int idx);

extern u32 FUN_020536D0(u32 gender, u32 avatar, u32 a2);
extern u32 FUN_0205F388(struct ScriptState* state);
extern u32 FUN_0205F398(struct ScriptState* state);
extern struct PCStorage* GetStoragePCPointer(struct SaveData* save);
extern u32 FUN_0205F3C0(struct ScriptState* state);
extern u32 FUN_02054C14(u32 number);

BOOL ScrCmd_GetPlayerName(struct ScriptContext* ctx) //00CD - todo: BufferPlayerName? TextPlayerName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    struct SaveData* save = ScriptEnvironment_GetSavePtr(fieldSystem);
    struct PlayerData* player = Save_PlayerData_GetProfileAddr(save);

    BufferPlayersName(*messageFormat, idx, player);

    return FALSE;
}

BOOL ScrCmd_GetRivalName(struct ScriptContext* ctx) //00CE - todo: BufferRivalName? TextRivalName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);

    BufferRivalsName(*messageFormat, idx, fieldSystem->saveData);

    return FALSE;
}

BOOL ScrCmd_GetFriendName(struct ScriptContext* ctx) //00CF - todo: BufferFriendName? TextFriendName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);

    BufferFriendsName(*messageFormat, idx, fieldSystem->saveData);

    return FALSE;
}

BOOL ScrCmd_GetPokemonName(struct ScriptContext* ctx) //00D0 - todo: BufferPartyPokemonName? TextPartyPokemonName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);
    struct Pokemon* mon = GetPartyMonByIndex(party, mon_idx);

    BufferBoxMonSpeciesName(*messageFormat, idx, &mon->box);

    return FALSE;
}

BOOL ScrCmd_GetItemName(struct ScriptContext* ctx) //00D1 - todo: BufferItemName? TextItemName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 item = ScriptGetVar(ctx);

    BufferItemName(*messageFormat, idx, item);

    return FALSE;
}

BOOL ScrCmd_GetPocketName(struct ScriptContext* ctx) //00D2 - todo: BufferPocketName? TextPocketName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 pocket = ScriptGetVar(ctx);

    BufferPocketName(*messageFormat, idx, pocket);

    return FALSE;
}

BOOL ScrCmd_GetTMHMMoveName(struct ScriptContext* ctx) //00D3 - todo: BufferTMHMName? BufferMachineName? TextTMHMName? TextMachineName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 tmhm = ScriptGetVar(ctx);
    u16 move = TMHMGetMove(tmhm);

    BufferMoveName(*messageFormat, idx, move);

    return FALSE;
}

BOOL ScrCmd_GetMoveName(struct ScriptContext* ctx) //00D4 - todo: BufferMoveName? TextMoveName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 move = ScriptGetVar(ctx);

    BufferMoveName(*messageFormat, idx, move);

    return FALSE;
}

BOOL ScrCmd_Unk00D5(struct ScriptContext* ctx) //00D5 - todo: BufferNumber? TextNumber?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 unk = ScriptGetVar(ctx);
    u32 digits = FUN_02054C14(unk);

    BufferIntegerAsString(*messageFormat, idx, unk, digits, PRINTING_MODE_RIGHT_ALIGN, TRUE);

    return FALSE;
}

BOOL ScrCmd_Unk0280(struct ScriptContext* ctx) //0280 - todo: BufferNumberSpecial? need more info
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 unk = ScriptGetVar(ctx);
    enum PrintingMode printingMode = (enum PrintingMode)ScriptReadByte(ctx);
    u8 digits = ScriptReadByte(ctx);
    if (printingMode == PRINTING_MODE_LEFT_ALIGN)
    {
        digits = (u8)FUN_02054C14(unk);
    }

    BufferIntegerAsString(*messageFormat, idx, unk, digits, printingMode, TRUE);

    return FALSE;
}

BOOL ScrCmd_GetPokemonNickname(struct ScriptContext* ctx) //00D6 - todo: BufferPartyPokemonNickname? TextPartyPokemonNickname?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);

    BufferBoxMonNickname(*messageFormat, idx, &pokemon->box);

    return FALSE;
}

BOOL ScrCmd_Unk0251(struct ScriptContext* ctx) //0251 - todo: BufferBoxPokemonNickname? TextBoxPokemonNickname?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct PCStorage* pc = GetStoragePCPointer(fieldSystem->saveData);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 box_mon_idx = ScriptGetVar(ctx);
    s32 box_no = box_mon_idx / 30;
    s32 slot_no = box_mon_idx % 30;
    struct BoxPokemon* box_mon = PCStorage_GetMonByIndexPair(pc, box_no, slot_no);

    BufferBoxMonNickname(*messageFormat, idx, box_mon);

    return FALSE;
}

BOOL ScrCmd_GetPoketchAppName(struct ScriptContext* ctx) //00D7 - todo: BufferPoketchAppName? TextPoketchAppName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 app = ScriptGetVar(ctx);

    BufferPoketchAppName(*messageFormat, idx, app);

    return FALSE;
}

BOOL ScrCmd_GetTrainerClassName(struct ScriptContext* ctx) //00D8 - todo: BufferTrainerClassName? TextTrainerClassName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 trainer_class = ScriptGetVar(ctx);

    BufferTrainerClassName(*messageFormat, idx, trainer_class);

    return FALSE;
}

BOOL ScrCmd_Unk00D9(struct ScriptContext* ctx) //00D9 - todo: BufferPlayerTrainerClassName? TextPlayerTrainerClassName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct SaveData* save = ScriptEnvironment_GetSavePtr(fieldSystem);
    struct PlayerData* player = Save_PlayerData_GetProfileAddr(save);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u32 gender = PlayerProfile_GetTrainerGender(player);
    u32 avatar = PlayerProfile_GetAvatar(player);
    u32 trainer_class = FUN_020536D0(gender, avatar, 2);

    BufferTrainerClassNameWithArticle(*messageFormat, idx, trainer_class);

    return FALSE;
}

BOOL ScrCmd_Unk00DA(struct ScriptContext* ctx) //00DA - todo: BufferPokemonSpeciesName? TextPokemonSpeciesName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 msg_no = ScriptGetVar(ctx);
    u16 unk1 = ScriptReadHalfword(ctx);
    u8 unk2 = ScriptReadByte(ctx);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*messageFormat, idx, str, unk1, unk2, 2);
    String_Delete(str);

    return FALSE;
}

struct String* FUN_02040AE4(u32 msg_no, u32 heap_id) //todo: GetPokemonSpeciesName?
{
    struct MsgData* msg_data = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 362, heap_id); //todo change to NAIX
    struct String* ret = NewString_ReadMsgData(msg_data, msg_no);
    DestroyMsgData(msg_data);

    return ret;
}

BOOL ScrCmd_GetPlayerStarterName(struct ScriptContext* ctx) //00DB - todo: BufferPlayerStarterSpecies?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SaveArray_Flags_Get(ctx->fieldSystem->saveData);
    u32 msg_no = FUN_0205F388(state);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*messageFormat, idx, str, 0, 1, 2);
    String_Delete(str);

    return FALSE;
}

BOOL ScrCmd_GetRivalStarterName(struct ScriptContext* ctx) //00DC - todo: BufferRivalStarterSpecies?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SaveArray_Flags_Get(ctx->fieldSystem->saveData);
    u32 msg_no = FUN_0205F398(state);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*messageFormat, idx, str, 0, 1, 2);
    String_Delete(str);

    return FALSE;
}

BOOL ScrCmd_GetCounterpartStarterName(struct ScriptContext* ctx) //00DD - todo: BufferFriendStarterSpecies?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SaveArray_Flags_Get(ctx->fieldSystem->saveData);
    u32 msg_no = FUN_0205F3C0(state);
    struct String* str = FUN_02040AE4(msg_no, 4);

    BufferString(*messageFormat, idx, str, 0, 1, 2);
    String_Delete(str);

    return FALSE;
}

BOOL ScrCmd_GetDecorationName(struct ScriptContext* ctx) //00DF - todo: BufferDecorationName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 decoration = ScriptGetVar(ctx);

    BufferDecorationName(*messageFormat, idx, decoration);

    return FALSE;
}

BOOL ScrCmd_GetUndergroundTrapName(struct ScriptContext* ctx) //00E0 - todo: BufferUndergroundTrapName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_trap = ScriptGetVar(ctx);

    BufferUndergroundTrapName(*messageFormat, idx, underground_trap);

    return FALSE;
}

BOOL ScrCmd_GetUndergroundItemName(struct ScriptContext* ctx) //00E1 - todo: BufferUndergroundItemName? BufferTreasureName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_item = ScriptGetVar(ctx);

    BufferUndergroundItemName(*messageFormat, idx, underground_item);

    return FALSE;
}

BOOL ScrCmd_GetMapName(struct ScriptContext* ctx) //00E2 - todo: BufferMapName?
{
    struct String* str = String_New(22, 4);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 map_no = ScriptGetVar(ctx);

    FUN_02064E60(map_no, 4, str);
    BufferString(*messageFormat, idx, str, 0, 1, 2);
    String_Delete(str);

    return FALSE;
}

BOOL ScrCmd_GetBerryName(struct ScriptContext* ctx) //017B - todo: BufferBerryName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 berry = ScriptGetVar(ctx);
    u16 unk = ScriptGetVar(ctx);
    struct String* nut_name = GetNutName((u16)(berry - FIRST_BERRY_IDX), 32);

    BufferString(*messageFormat, idx, nut_name, 0, unk < 2, 2);
    String_Delete(nut_name);

    return FALSE;
}

BOOL ScrCmd_GetNatureName(struct ScriptContext* ctx) //017C - todo: BufferNatureName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 nature = ScriptGetVar(ctx);

    BufferNatureName(*messageFormat, idx, nature);

    return FALSE;
}

BOOL ScrCmd_GetFashionName(struct ScriptContext* ctx) //0261 - todo: BufferAccessoryName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 fashion = ScriptGetVar(ctx);

    BufferFashionName(*messageFormat, idx, fashion);

    return FALSE;
}

BOOL ScrCmd_GetWhiteRockInscription(struct ScriptContext* ctx) //0272 - todo: BufferWhiteRockInscription?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    struct String* str = String_New(11, 11);
    struct UnkStruct_02024E64* unk = FUN_02024EB4(ctx->fieldSystem->saveData);
    u16* unk_buffer = FUN_02024F0C(unk);

    CopyU16ArrayToString(str, unk_buffer);
    BufferString(*messageFormat, idx, str, 0, 0, gGameLanguage);
    String_Delete(str);

    return FALSE;
}

BOOL ScrCmd_GetPokemonMoveName(struct ScriptContext* ctx) //01CB - todo: BufferPartyPokemonMoveName?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    u16 mon_move_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);
    u16 move = (u16)GetMonData(pokemon, MON_DATA_MOVE1 + mon_move_idx, NULL);

    BufferMoveName(*messageFormat, idx, move);

    return FALSE;
}

BOOL ScrCmd_GetRibbonName(struct ScriptContext* ctx) //0232 - todo: BufferRibbonName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u8 unk = (u8)ScriptGetVar(ctx);
    u16 ribbon = (u16)FUN_0207FC5C(unk, 3);

    BufferRibbonNameOrDesc(*messageFormat, idx, ribbon);

    return FALSE;
}

BOOL ScrCmd_GetSealName(struct ScriptContext* ctx) //02B3 - todo: BufferSealName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 seal = ScriptGetVar(ctx);

    BufferSealName(*messageFormat, idx, (u16)(seal - 1));

    return FALSE;
}

BOOL ScrCmd_GetItemNameWithIndefArticle(struct ScriptContext* ctx) //02C4 - todo: BufferIndefItemName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 item = ScriptGetVar(ctx);

    BufferItemNameWithIndefArticle(*messageFormat, idx, item);

    return FALSE;
}

BOOL ScrCmd_GetItemNamePlural(struct ScriptContext* ctx) //02C5 - todo: BufferPluralItemName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 item = ScriptGetVar(ctx);

    BufferItemNamePlural(*messageFormat, idx, item);

    return FALSE;
}

BOOL ScrCmd_GetDecorationNameWithArticle(struct ScriptContext* ctx) //02C6 - todo: BufferIndefDecorationName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 decoration = ScriptGetVar(ctx);

    BufferDecorationNameWithArticle(*messageFormat, idx, decoration);

    return FALSE;
}

BOOL ScrCmd_GetUndergroundTrapNameWithArticle(struct ScriptContext* ctx) //02C7 - todo: BufferIndefTrapName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_trap = ScriptGetVar(ctx);

    BufferUndergroundTrapNameWithArticle(*messageFormat, idx, underground_trap);

    return FALSE;
}

BOOL ScrCmd_GetUndergroundItemNameWithArticle(struct ScriptContext* ctx) //02C8 - todo: BufferIndefUndergroundItemName? BufferIndefTreasureName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 underground_item = ScriptGetVar(ctx);

    BufferUndergroundItemNameWithArticle(*messageFormat, idx, underground_item);

    return FALSE;
}

BOOL ScrCmd_Unk02C9(struct ScriptContext* ctx) //02C9 - todo: BufferIndefSpeciesName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 species = ScriptGetVar(ctx);
    u16 unused1 = ScriptReadHalfword(ctx);
    u8 unused2 = ScriptReadByte(ctx);

    BufferSpeciesNameWithArticle(*messageFormat, idx, species);

    return FALSE;
}

BOOL ScrCmd_Unk02CA(struct ScriptContext* ctx) //02CA - todo: BufferIndefFriendStarterSpecies?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    struct ScriptState* state = SaveArray_Flags_Get(ctx->fieldSystem->saveData);
    u32 species = FUN_0205F3C0(state);

    BufferSpeciesNameWithArticle(*messageFormat, idx, species);

    return FALSE;
}

BOOL ScrCmd_GetFashionNameWithArticle(struct ScriptContext* ctx) //02CB - todo: BufferIndefAccessoryName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 fashion = ScriptGetVar(ctx);

    BufferFashionNameWithArticle(*messageFormat, idx, fashion);

    return FALSE;
}

BOOL ScrCmd_Unk02CC(struct ScriptContext* ctx) //02CC - todo: BufferIndefTrainerClassName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 trainer_class = ScriptGetVar(ctx);

    BufferTrainerClassNameWithArticle(*messageFormat, idx, trainer_class);

    return FALSE;
}

BOOL ScrCmd_GetSealNamePlural(struct ScriptContext* ctx) //02CD - todo: BufferPluralSealName?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);
    u16 seal = ScriptGetVar(ctx);

    BufferSealNamePlural(*messageFormat, idx, (u16)(seal - 1));

    return FALSE;
}

BOOL ScrCmd_CapitalizeFirstChar(struct ScriptContext* ctx) //02CE - todo CapitalizeText?
{
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 idx = ScriptReadByte(ctx);

    MessageFormat_UpperFirstChar(*messageFormat, idx);

    return FALSE;
}
