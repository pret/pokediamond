#include "global.h"

#include "player_data.h"
#include "scrcmd.h"

extern void *FieldSysGetAttrAddr(struct FieldSystem *fieldSystem, u8 idx);

extern Window *ov05_021E27E8(struct FieldSystem *fieldSystem, u8 xVal, u8 yVal);
extern void ov05_021E288C(Window *moneyBox);
extern void ov05_021E28A0(struct FieldSystem *fieldSystem, Window *moneyBox);

BOOL ScrCmd_GiveMoney(struct ScriptContext *ctx) // 006F
{
    struct SaveData *save = FieldSystem_GetSaveData(ctx->fieldSystem);
    PlayerProfile *player = Save_PlayerData_GetProfileAddr(save);

    u32 amount = ScriptReadWord(ctx);
    PlayerProfile_AddMoney(player, amount);

    return FALSE;
}

BOOL ScrCmd_TakeMoneyImmediate(struct ScriptContext *ctx) // 0070 - todo: TakeMoney?
{
    struct SaveData *save = FieldSystem_GetSaveData(ctx->fieldSystem);
    PlayerProfile *player = Save_PlayerData_GetProfileAddr(save);

    u32 amount = ScriptReadWord(ctx);
    PlayerProfile_SubMoney(player, amount);

    return FALSE;
}

BOOL ScrCmd_TakeMoneyAddress(struct ScriptContext *ctx) // 01A3 - todo: TakeMoneyVar?
{
    struct SaveData *save = FieldSystem_GetSaveData(ctx->fieldSystem);
    PlayerProfile *player = Save_PlayerData_GetProfileAddr(save);

    u16 amount = ScriptGetVar(ctx);
    PlayerProfile_SubMoney(player, (u32)amount);

    return FALSE;
}

BOOL ScrCmd_HasEnoughMoneyImmediate(struct ScriptContext *ctx) // 0071 - todo: CanAffordMoney?
{
    struct SaveData *save = FieldSystem_GetSaveData(ctx->fieldSystem);
    PlayerProfile *player = Save_PlayerData_GetProfileAddr(save);
    u16 *ret_ptr          = ScriptGetVarPointer(ctx);

    u32 amount = ScriptReadWord(ctx);
    u32 money  = PlayerProfile_GetMoney(player);

    if (money < amount) {
        *ret_ptr = 0;
    } else {
        *ret_ptr = 1;
    }

    return FALSE;
}

BOOL ScrCmd_HasEnoughMoneyAddress(struct ScriptContext *ctx) // 01AB - todo: CanAffordMoneyVar?
{
    struct SaveData *save = FieldSystem_GetSaveData(ctx->fieldSystem);
    PlayerProfile *player = Save_PlayerData_GetProfileAddr(save);
    u16 *ret_ptr          = ScriptGetVarPointer(ctx);

    u16 amount = ScriptGetVar(ctx);
    u32 money  = PlayerProfile_GetMoney(player);

    if (money < amount) {
        *ret_ptr = 0;
    } else {
        *ret_ptr = 1;
    }

    return FALSE;
}

BOOL ScrCmd_ShowMoneyBox(struct ScriptContext *ctx) // 0072
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 xVal                        = ScriptGetVar(ctx);
    u16 yVal                        = ScriptGetVar(ctx);
    Window **moneyBox               = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MONEY_BOX);

    *moneyBox = ov05_021E27E8(ctx->fieldSystem, (u8)xVal, (u8)yVal);

    return FALSE;
}

BOOL ScrCmd_HideMoneyBox(struct ScriptContext *ctx) // 0073
{
    Window **moneyBox = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MONEY_BOX);
    ov05_021E288C(*moneyBox);

    return FALSE;
}

BOOL ScrCmd_UpdateMoneyBox(struct ScriptContext *ctx) // 0074
{
    Window **moneyBox = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MONEY_BOX);
    ov05_021E28A0(ctx->fieldSystem, *moneyBox);

    return FALSE;
}
