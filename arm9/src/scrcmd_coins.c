#include "global.h"

#include "coins.h"
#include "scrcmd.h"

extern void *FieldSysGetAttrAddr(struct FieldSystem *arg, u8 idx);

extern Window *ov05_021E2950(struct FieldSystem *arg, u8 xVal, u8 yVal);
extern void ov05_021E29B4(Window *coinBox);
extern void ov05_021E29C8(struct FieldSystem *arg, Window *coinBox);

BOOL ScrCmd_ShowCoinBox(struct ScriptContext *ctx) // 0075
{
    struct FieldSystem *sav_ptr = ctx->fieldSystem;
    u16 xVal = ScriptGetVar(ctx);
    u16 yVal = ScriptGetVar(ctx);
    Window **coinBoxPtr = (Window **)FieldSysGetAttrAddr(sav_ptr, SCRIPTENV_COIN_BOX);

    Window *coinBox = ov05_021E2950(ctx->fieldSystem, (u8)xVal, (u8)yVal);
    *coinBoxPtr = coinBox;

    return FALSE;
}

BOOL ScrCmd_HideCoinBox(struct ScriptContext *ctx) // 0076
{
    Window **coinBoxPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_COIN_BOX);
    ov05_021E29B4(*coinBoxPtr);

    return FALSE;
}

BOOL ScrCmd_UpdateCoinBox(struct ScriptContext *ctx) // 0077
{
    Window **coinBoxPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_COIN_BOX);
    ov05_021E29C8(ctx->fieldSystem, *coinBoxPtr);

    return FALSE;
}

BOOL ScrCmd_GetCoins(struct ScriptContext *ctx) // 0078 - todo: Coins_GetValue instead?
{
    u16 *coins_ptr = Save_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveData);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);

    *ret_ptr = Coins_GetValue(coins_ptr);

    return FALSE;
}

BOOL ScrCmd_GiveCoins(struct ScriptContext *ctx) // 0079
{
    u16 *coins_ptr = Save_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveData);
    u16 amount = ScriptGetVar(ctx);

    Coins_Add(coins_ptr, amount);

    return FALSE;
}

BOOL ScrCmd_TakeCoinsImmediate(struct ScriptContext *ctx) // 0080 - todo: Coins_Subtract instead?
{
    u16 *coins_ptr = Save_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveData);
    u16 amount = ScriptGetVar(ctx);

    Coins_Subtract(coins_ptr, amount);

    return FALSE;
}

BOOL ScrCmd_TakeCoinsAddress(struct ScriptContext *ctx) // 02A8 - todo: TakeCoinsVar instead?
{
    u16 *coins_ptr = Save_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveData);
    u16 *amount = ScriptGetVarPointer(ctx);

    Coins_Subtract(coins_ptr, *amount);

    return FALSE;
}

BOOL ScrCmd_HasEnoughCoinsImmediate(struct ScriptContext *ctx) // 0274 - todo: CanAffordCoins?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct SaveData *save = FieldSystem_GetSaveData(fieldSystem);
    // Created, but discarded.
    PlayerProfile *player = Save_PlayerData_GetProfile(save);
    u16 *coins_ptr = Save_PlayerData_GetCoinsAddr(fieldSystem->saveData);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);

    u32 amount = ScriptReadWord(ctx);
    u16 coins = Coins_GetValue(coins_ptr);

    if (coins < amount) {
        *ret_ptr = 0;
    } else {
        *ret_ptr = 1;
    }

    return FALSE;
}

BOOL ScrCmd_HasEnoughCoinsAddress(struct ScriptContext *ctx) // 02A9 - todo: CanAffordCoinsVar?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct SaveData *save = FieldSystem_GetSaveData(fieldSystem);
    // Created, but discarded
    PlayerProfile *player = Save_PlayerData_GetProfile(save);
    u16 *coins_ptr = Save_PlayerData_GetCoinsAddr(fieldSystem->saveData);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);

    u16 amount = *ScriptGetVarPointer(ctx);
    u16 coins = Coins_GetValue(coins_ptr);

    if (coins < amount) {
        *ret_ptr = 0;
    } else {
        *ret_ptr = 1;
    }

    return FALSE;
}

BOOL ScrCmd_CanGiveCoins(struct ScriptContext *ctx) // 0276
{
    u16 *coins_ptr = Save_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveData);
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    u16 amount = ScriptGetVar(ctx);

    *ret_ptr = (u16)Coins_CanAdd(coins_ptr, amount);

    return FALSE;
}
