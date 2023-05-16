#include "scrcmd.h"
#include "daycare.h"
#include "party.h"
#include "message_format.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem*, int idx);

extern void MOD05_021EC57C(struct PlayerParty* party, u8 idx, struct DayCare* daycare, struct SaveBlock2* sav2);
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

THUMB_FUNC BOOL ScrCmd_GetDaycarePokemonNames(struct ScriptContext* ctx) //016D
{
    struct SaveBlock2* sav2 = ctx->fieldSystem->saveBlock2;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct DayCare* daycare = Sav2_DayCare_get(sav2);

    MOD05_021ED4E0(daycare, *messageFormat);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetDaycareStatus(struct ScriptContext* ctx) //016E
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct SaveBlock2* sav2 = fieldSystem->saveBlock2;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = MOD05_021ED5EC(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_DeleteDaycareEgg(struct ScriptContext* ctx) //01A8
{
    struct DayCare* daycare = SavArray_get(ctx->fieldSystem->saveBlock2, 8);
    MOD05_021ECD64(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveDaycareEgg(struct ScriptContext* ctx) //01A9
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct DayCare* daycare = SavArray_get(fieldSystem->saveBlock2, 8);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct SaveBlock2* sav2 = ScriptEnvironment_GetSav2Ptr(ctx->fieldSystem);
    struct PlayerData* player = Sav2_PlayerData_GetProfileAddr(sav2);

    MOD05_DayCare_GiveEggToPlayer(daycare, party, player);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A4(struct ScriptContext* ctx) //01A4
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct SaveBlock2* sav2 = fieldSystem->saveBlock2;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct DayCare* daycare = SavArray_get(sav2, 8);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);

    *ret_ptr = MOD05_021EC71C(party, *messageFormat, daycare, (u8)idx);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01AA(struct ScriptContext* ctx) //01AA
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct SaveBlock2* sav2 = fieldSystem->saveBlock2;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = MOD05_021EC854(daycare, (u8)idx, *messageFormat);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetDaycareLevel(struct ScriptContext* ctx) //01AE
{
    struct SaveBlock2* sav2 = ctx->fieldSystem->saveBlock2;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = MOD05_021EC864(daycare, idx, *messageFormat);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01AF(struct ScriptContext* ctx) //01AF
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 unused = ScriptReadHalfword(ctx);
    u16 idx = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);

    *ret_ptr = MOD05_021ED5C4(party, idx, *messageFormat);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01B0(struct ScriptContext* ctx) //01B0
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct SaveBlock2* sav2 = fieldSystem->saveBlock2;
    u16 idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SavArray_PlayerParty_get(fieldSystem->saveBlock2);
    struct DayCare* daycare = SavArray_get(sav2, 8);

    MOD05_021EC57C(party, (u8)idx, daycare, sav2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01BC(struct ScriptContext* ctx) //01BC
{
    struct SaveBlock2* sav2 = ctx->fieldSystem->saveBlock2;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 idx1 = ScriptGetVar(ctx);
    u16 idx2 = ScriptGetVar(ctx);
    u16 idx3 = ScriptGetVar(ctx);
    u16 idx4 = ScriptGetVar(ctx);
    struct DayCare* daycare = Sav2_DayCare_get(sav2);

    MOD05_021ED52C(daycare, (u8)idx1, (u8)idx2, (u8)idx3, (u8)idx4, *messageFormat);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01BE(struct ScriptContext* ctx) //01BE
{
    struct SaveBlock2* sav2 = ctx->fieldSystem->saveBlock2;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = (u16)MOD05_021ED644(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01BF(struct ScriptContext* ctx) //01BF - todo: SaveEggPID?
{
    struct SaveBlock2* sav2 = ctx->fieldSystem->saveBlock2;
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = (u16)Sav2_DayCare_GetEggPID(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A5(struct ScriptContext* ctx) //01A5
{
    u16* unused = ScriptGetVarPointer(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A6(struct ScriptContext* ctx) //01A6
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A7(struct ScriptContext* ctx) //01A7
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01AD(struct ScriptContext* ctx) //01AD
{
    u16* unused = ScriptGetVarPointer(ctx);
    return FALSE;
}
