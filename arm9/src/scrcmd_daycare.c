#include "global.h"
#include "scrcmd.h"
#include "daycare.h"
#include "party.h"
#include "message_format.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem*, int idx);

extern void MOD05_021EC57C(struct PlayerParty* party, u8 idx, struct DayCare* daycare, struct SaveData* save);
extern u16 MOD05_021EC71C(struct PlayerParty* party, MessageFormat *messageFormat, struct DayCare* daycare, u8 idx);
extern u16 MOD05_021EC854(struct DayCare* daycare, u8 idx, MessageFormat *messageFormat);
extern u8 MOD05_021EC864(struct DayCare* daycare, int idx, MessageFormat *messageFormat);
extern void MOD05_021ECD64(struct DayCare* daycare);
extern void MOD05_DayCare_GiveEggToPlayer(struct DayCare* daycare, struct PlayerParty* party, struct PlayerData* player);
extern void MOD05_021ED4E0(struct DayCare* daycare, MessageFormat *messageFormat);
extern void MOD05_021ED52C(struct DayCare* daycare, u8 idx1, u8 idx2, u8 idx3, u8 idx4, MessageFormat *messageFormat);
extern u16 MOD05_021ED5C4(struct PlayerParty* party, int idx, MessageFormat *messageFormat);
extern u16 MOD05_021ED5EC(struct DayCare* daycare);
extern u32 MOD05_021ED644(struct DayCare* daycare);

BOOL ScrCmd_GetDaycarePokemonNames(struct ScriptContext* ctx) //016D
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct DayCare* daycare = Save_DayCare_Get(save);

    MOD05_021ED4E0(daycare, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_GetDaycareStatus(struct ScriptContext* ctx) //016E
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct SaveData* save = fieldSystem->saveData;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct DayCare* daycare = SaveArray_Get(save, 8);

    *ret_ptr = MOD05_021ED5EC(daycare);

    return FALSE;
}

BOOL ScrCmd_DeleteDaycareEgg(struct ScriptContext* ctx) //01A8
{
    struct DayCare* daycare = SaveArray_Get(ctx->fieldSystem->saveData, 8);
    MOD05_021ECD64(daycare);

    return FALSE;
}

BOOL ScrCmd_GiveDaycareEgg(struct ScriptContext* ctx) //01A9
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct DayCare* daycare = SaveArray_Get(fieldSystem->saveData, 8);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);
    struct SaveData* save = ScriptEnvironment_GetSavePtr(ctx->fieldSystem);
    struct PlayerData* player = Save_PlayerData_GetProfileAddr(save);

    MOD05_DayCare_GiveEggToPlayer(daycare, party, player);

    return FALSE;
}

BOOL ScrCmd_Unk01A4(struct ScriptContext* ctx) //01A4
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct SaveData* save = fieldSystem->saveData;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct DayCare* daycare = SaveArray_Get(save, 8);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);

    *ret_ptr = MOD05_021EC71C(party, *messageFormat, daycare, (u8)idx);

    return FALSE;
}

BOOL ScrCmd_Unk01AA(struct ScriptContext* ctx) //01AA
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct SaveData* save = fieldSystem->saveData;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct DayCare* daycare = SaveArray_Get(save, 8);

    *ret_ptr = MOD05_021EC854(daycare, (u8)idx, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_GetDaycareLevel(struct ScriptContext* ctx) //01AE
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct DayCare* daycare = SaveArray_Get(save, 8);

    *ret_ptr = MOD05_021EC864(daycare, idx, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_Unk01AF(struct ScriptContext* ctx) //01AF
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 unused = ScriptReadHalfword(ctx);
    u16 idx = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);

    *ret_ptr = MOD05_021ED5C4(party, idx, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_Unk01B0(struct ScriptContext* ctx) //01B0
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct SaveData* save = fieldSystem->saveData;
    u16 idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(fieldSystem->saveData);
    struct DayCare* daycare = SaveArray_Get(save, 8);

    MOD05_021EC57C(party, (u8)idx, daycare, save);

    return FALSE;
}

BOOL ScrCmd_Unk01BC(struct ScriptContext* ctx) //01BC
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 idx1 = ScriptGetVar(ctx);
    u16 idx2 = ScriptGetVar(ctx);
    u16 idx3 = ScriptGetVar(ctx);
    u16 idx4 = ScriptGetVar(ctx);
    struct DayCare* daycare = Save_DayCare_Get(save);

    MOD05_021ED52C(daycare, (u8)idx1, (u8)idx2, (u8)idx3, (u8)idx4, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_Unk01BE(struct ScriptContext* ctx) //01BE
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct DayCare* daycare = SaveArray_Get(save, 8);

    *ret_ptr = (u16)MOD05_021ED644(daycare);

    return FALSE;
}

BOOL ScrCmd_Unk01BF(struct ScriptContext* ctx) //01BF - todo: SaveEggPID?
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct DayCare* daycare = SaveArray_Get(save, 8);

    *ret_ptr = (u16)Save_DayCare_GetEggPID(daycare);

    return FALSE;
}

BOOL ScrCmd_Unk01A5(struct ScriptContext* ctx) //01A5
{
    u16* unused = ScriptGetVarPointer(ctx);
    return FALSE;
}

BOOL ScrCmd_Unk01A6(struct ScriptContext* ctx) //01A6
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Unk01A7(struct ScriptContext* ctx) //01A7
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Unk01AD(struct ScriptContext* ctx) //01AD
{
    u16* unused = ScriptGetVarPointer(ctx);
    return FALSE;
}
