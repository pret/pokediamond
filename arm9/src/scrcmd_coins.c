#include "scrcmd.h"
#include "coins.h"

extern void * FUN_02039438(struct FieldSystem* arg, u8 idx);

extern u32 MOD05_021E2950(struct FieldSystem* arg, u8, u8);
extern MOD05_021E29B4();
extern MOD05_021E29C8();

THUMB_FUNC BOOL ScrCmd_ShowCoinBox(struct ScriptContext * ctx) //0075
{
    struct FieldSystem* sav_ptr = ctx->fieldSystem;
    u32 unk1 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u32 unk2 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 ** unk_ret_ptr = FUN_02039438(sav_ptr, 0x26);

    u32 unk3 = MOD05_021E2950(ctx->fieldSystem, (u8)unk1, (u8)unk2);
    *unk_ret_ptr = (u16 *)unk3;

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HideCoinBox(struct ScriptContext * ctx) //0076
{
    u16 ** unk = FUN_02039438(ctx->fieldSystem, 0x26);
    MOD05_021E29B4(*unk);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_UpdateCoinBox(struct ScriptContext * ctx) //0077
{
    u16 ** unk = FUN_02039438(ctx->fieldSystem, 0x26);
    MOD05_021E29C8(ctx->fieldSystem, *unk);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetCoins(struct ScriptContext * ctx) //0078 - todo: CheckCoins instead?
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 * ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

    *ret_ptr = CheckCoins(coins_ptr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveCoins(struct ScriptContext * ctx) //0079
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 amount = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));

    GiveCoins(coins_ptr, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeCoinsImmediate(struct ScriptContext * ctx) //0080 - todo: TakeCoins instead?
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 amount = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));

    TakeCoins(coins_ptr, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeCoinsAddress(struct ScriptContext * ctx) //02A8 - todo: TakeCoinsVar instead?
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->fieldSystem->saveBlock2);
    u16 * amount = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

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
    u16 * ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

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
    u16 * ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

    u16 amount = *(u16*)GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
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
    u16 * ret_ptr = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 amount = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));

    *ret_ptr = (u16)CanGiveCoins(coins_ptr, amount);

    return FALSE;
}
