#include "global.h"

#include "daycare.h"
#include "message_format.h"
#include "party.h"
#include "scrcmd.h"

extern void *FieldSysGetAttrAddr(struct FieldSystem *, int idx);

extern void ov05_021EC57C(struct Party *party, u8 idx, struct Daycare *daycare, struct SaveData *save);
extern u16 ov05_021EC71C(struct Party *party, MessageFormat *messageFormat, struct Daycare *daycare, u8 idx);
extern u16 ov05_021EC854(struct Daycare *daycare, u8 idx, MessageFormat *messageFormat);
extern u8 ov05_021EC864(struct Daycare *daycare, int idx, MessageFormat *messageFormat);
extern void ov05_021ECD64(struct Daycare *daycare);
extern void ov05_Daycare_GiveEggToPlayer(struct Daycare *daycare, struct Party *party, PlayerProfile *player);
extern void ov05_021ED4E0(struct Daycare *daycare, MessageFormat *messageFormat);
extern void ov05_021ED52C(struct Daycare *daycare, u8 idx1, u8 idx2, u8 idx3, u8 idx4, MessageFormat *messageFormat);
extern u16 ov05_021ED5C4(struct Party *party, int idx, MessageFormat *messageFormat);
extern u16 ov05_021ED5EC(struct Daycare *daycare);
extern u32 ov05_021ED644(struct Daycare *daycare);

BOOL ScrCmd_GetDaycarePokemonNames(struct ScriptContext *ctx) // 016D
{
    struct SaveData *save = ctx->fieldSystem->saveData;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct Daycare *daycare = Save_Daycare_Get(save);

    ov05_021ED4E0(daycare, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_GetDaycareStatus(struct ScriptContext *ctx) // 016E
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct SaveData *save = fieldSystem->saveData;
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct Daycare *daycare = SaveArray_Get(save, 8);

    *ret_ptr = ov05_021ED5EC(daycare);

    return FALSE;
}

BOOL ScrCmd_DeleteDaycareEgg(struct ScriptContext *ctx) // 01A8
{
    struct Daycare *daycare = SaveArray_Get(ctx->fieldSystem->saveData, 8);
    ov05_021ECD64(daycare);

    return FALSE;
}

BOOL ScrCmd_GiveDaycareEgg(struct ScriptContext *ctx) // 01A9
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct Daycare *daycare = SaveArray_Get(fieldSystem->saveData, 8);
    struct Party *party = SaveArray_Party_Get(fieldSystem->saveData);
    struct SaveData *save = FieldSystem_GetSaveData(ctx->fieldSystem);
    PlayerProfile *player = Save_PlayerData_GetProfileAddr(save);

    ov05_Daycare_GiveEggToPlayer(daycare, party, player);

    return FALSE;
}

BOOL ScrCmd_Unk01A4(struct ScriptContext *ctx) // 01A4
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct SaveData *save = fieldSystem->saveData;
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct Daycare *daycare = SaveArray_Get(save, 8);
    struct Party *party = SaveArray_Party_Get(fieldSystem->saveData);

    *ret_ptr = ov05_021EC71C(party, *messageFormat, daycare, (u8)idx);

    return FALSE;
}

BOOL ScrCmd_Unk01AA(struct ScriptContext *ctx) // 01AA
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    struct SaveData *save = fieldSystem->saveData;
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct Daycare *daycare = SaveArray_Get(save, 8);

    *ret_ptr = ov05_021EC854(daycare, (u8)idx, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_GetDaycareLevel(struct ScriptContext *ctx) // 01AE
{
    struct SaveData *save = ctx->fieldSystem->saveData;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    u16 idx = ScriptGetVar(ctx);
    struct Daycare *daycare = SaveArray_Get(save, 8);

    *ret_ptr = ov05_021EC864(daycare, idx, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_Unk01AF(struct ScriptContext *ctx) // 01AF
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 unused = ScriptReadHalfword(ctx);
    u16 idx = ScriptGetVar(ctx);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct Party *party = SaveArray_Party_Get(fieldSystem->saveData);

    *ret_ptr = ov05_021ED5C4(party, idx, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_Unk01B0(struct ScriptContext *ctx) // 01B0
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct SaveData *save = fieldSystem->saveData;
    u16 idx = ScriptGetVar(ctx);
    struct Party *party = SaveArray_Party_Get(fieldSystem->saveData);
    struct Daycare *daycare = SaveArray_Get(save, 8);

    ov05_021EC57C(party, (u8)idx, daycare, save);

    return FALSE;
}

BOOL ScrCmd_Unk01BC(struct ScriptContext *ctx) // 01BC
{
    struct SaveData *save = ctx->fieldSystem->saveData;
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 idx1 = ScriptGetVar(ctx);
    u16 idx2 = ScriptGetVar(ctx);
    u16 idx3 = ScriptGetVar(ctx);
    u16 idx4 = ScriptGetVar(ctx);
    struct Daycare *daycare = Save_Daycare_Get(save);

    ov05_021ED52C(daycare, (u8)idx1, (u8)idx2, (u8)idx3, (u8)idx4, *messageFormat);

    return FALSE;
}

BOOL ScrCmd_Unk01BE(struct ScriptContext *ctx) // 01BE
{
    struct SaveData *save = ctx->fieldSystem->saveData;
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct Daycare *daycare = SaveArray_Get(save, 8);

    *ret_ptr = (u16)ov05_021ED644(daycare);

    return FALSE;
}

BOOL ScrCmd_Unk01BF(struct ScriptContext *ctx) // 01BF - todo: SaveEggPID?
{
    struct SaveData *save = ctx->fieldSystem->saveData;
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct Daycare *daycare = SaveArray_Get(save, 8);

    *ret_ptr = (u16)Save_Daycare_GetEggPID(daycare);

    return FALSE;
}

BOOL ScrCmd_Unk01A5(struct ScriptContext *ctx) // 01A5
{
    u16 *unused = ScriptGetVarPointer(ctx);
    return FALSE;
}

BOOL ScrCmd_Unk01A6(struct ScriptContext *ctx) // 01A6
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Unk01A7(struct ScriptContext *ctx) // 01A7
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Unk01AD(struct ScriptContext *ctx) // 01AD
{
    u16 *unused = ScriptGetVarPointer(ctx);
    return FALSE;
}
