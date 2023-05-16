#include "scrcmd.h"
#include "coins.h"

extern void * FieldSysGetAttrAddr(struct FieldSystem* arg, u8 idx);

extern u32 MOD05_021E2950(struct FieldSystem* arg, u8, u8);
extern void MOD05_021E29B4(u16 *unk);
extern void MOD05_021E29C8(struct FieldSystem *arg, u16 *unk);

THUMB_FUNC BOOL ScrCmd_ShowCoinBox(struct ScriptContext * ctx) //0075
{
    struct FieldSystem* sav_ptr = ctx->fieldSystem;
    u32 unk1 = ScriptGetVar(ctx);
    u32 unk2 = ScriptGetVar(ctx);
    u16 ** unk_ret_ptr = FieldSysGetAttrAddr(sav_ptr, 0x26);

    u32 unk3 = MOD05_021E2950(ctx->fieldSystem, (u8)unk1, (u8)unk2);
    *unk_ret_ptr = (u16 *)unk3;

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HideCoinBox(struct ScriptContext * ctx) //0076
{
    u16 ** unk = FieldSysGetAttrAddr(ctx->fieldSystem, 0x26);
    MOD05_021E29B4(*unk);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_UpdateCoinBox(struct ScriptContext * ctx) //0077
{
    u16 ** unk = FieldSysGetAttrAddr(ctx->fieldSystem, 0x26);
    MOD05_021E29C8(ctx->fieldSystem, *unk);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetCoins(struct ScriptContext * ctx) //0078 - todo: CheckCoins instead?
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 * ret_ptr = ScriptGetVarPointer(ctx);

    *ret_ptr = CheckCoins(coins_ptr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveCoins(struct ScriptContext * ctx) //0079
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 amount = ScriptGetVar(ctx);

    GiveCoins(coins_ptr, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeCoinsImmediate(struct ScriptContext * ctx) //0080 - todo: TakeCoins instead?
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 amount = ScriptGetVar(ctx);

    TakeCoins(coins_ptr, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeCoinsAddress(struct ScriptContext * ctx) //02A8 - todo: TakeCoinsVar instead?
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 * amount = ScriptGetVarPointer(ctx);

    TakeCoins(coins_ptr, *amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasEnoughCoinsImmediate(struct ScriptContext * ctx) //0274 - todo: CanAffordCoins?
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(fieldSystem);
    // Created, but discarded.
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(fieldSystem->saveBlock2);
    u16 * ret_ptr = ScriptGetVarPointer(ctx);

    u32 amount = ScriptReadWord(ctx);
    u16 coins = CheckCoins(coins_ptr);

    if (coins < amount)
    {
        *ret_ptr = 0;
    }
    else
    {
        *ret_ptr = 1;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasEnoughCoinsAddress(struct ScriptContext * ctx) //02A9 - todo: CanAffordCoinsVar?
{
    struct FieldSystem* fieldSystem = ctx->fieldSystem;
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(fieldSystem);
    // Created, but discarded
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(fieldSystem->saveBlock2);
    u16 * ret_ptr = ScriptGetVarPointer(ctx);

    u16 amount = *ScriptGetVarPointer(ctx);
    u16 coins = CheckCoins(coins_ptr);

    if (coins < amount)
    {
        *ret_ptr = 0;
    }
    else
    {
        *ret_ptr = 1;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CanGiveCoins(struct ScriptContext * ctx) //0276
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 * ret_ptr = ScriptGetVarPointer(ctx);
    u16 amount = ScriptGetVar(ctx);

    *ret_ptr = (u16)CanGiveCoins(coins_ptr, amount);

    return FALSE;
}
