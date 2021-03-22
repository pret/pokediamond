#include "scrcmd.h"
#include "coins.h"

extern u16 VarGet(struct UnkSavStruct80* arg, u16);
extern u16* GetVarPointer(struct UnkSavStruct80* arg, u16);
extern struct SaveBlock2 * ScriptEnvironment_GetSav2Ptr(struct UnkSavStruct80* unk);

extern void * FUN_02039438(struct UnkSavStruct80* arg, u8 idx);

extern u32 MOD05_021E2950(struct UnkSavStruct80* arg, u8, u8);
extern MOD05_021E29B4();
extern MOD05_021E29C8();

THUMB_FUNC BOOL ScrCmd_Unk0075(struct ScriptContext * ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    u32 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u32 unk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 ** unk_ret_ptr = FUN_02039438(sav_ptr, 0x26);

    u32 unk3 = MOD05_021E2950(ctx->unk80, (u8)unk1, (u8)unk2);
    *unk_ret_ptr = unk3;

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0076(struct ScriptContext * ctx)
{
    u16 ** unk = FUN_02039438(ctx->unk80, 0x26);
    MOD05_021E29B4(*unk);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0077(struct ScriptContext * ctx)
{
    u16 ** unk = FUN_02039438(ctx->unk80, 0x26);
    MOD05_021E29C8(ctx->unk80, *unk);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetCoins(struct ScriptContext * ctx)
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->unk80->saveBlock2);
    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    *ret_ptr = CheckCoins(coins_ptr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveCoins(struct ScriptContext * ctx)
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->unk80->saveBlock2);
    u16 amount = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

    GiveCoins(coins_ptr, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeCoinsImmediate(struct ScriptContext * ctx)
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->unk80->saveBlock2);
    u16 amount = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

    TakeCoins(coins_ptr, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeCoinsAddress(struct ScriptContext * ctx)
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->unk80->saveBlock2);
    u16 * amount = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    TakeCoins(coins_ptr, *amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasEnoughCoinsImmediate(struct ScriptContext * ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(sav_ptr);
    // Created, but discarded.
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(sav_ptr->saveBlock2);
    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

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

THUMB_FUNC BOOL ScrCmd_HasEnoughCoinsAddress(struct ScriptContext * ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(sav_ptr);
    // Created, but discarded
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(sav_ptr->saveBlock2);
    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    u16 amount = *(u16*)GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
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

THUMB_FUNC BOOL ScrCmd_CanGiveCoins(struct ScriptContext * ctx)
{
    u16 * coins_ptr = Sav2_PlayerData_GetCoinsAddr(ctx->unk80->saveBlock2);
    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 amount = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

    *ret_ptr = CanGiveCoins(coins_ptr, amount);

    return FALSE;
}
