#include "scrcmd.h"
#include "player_data.h"

extern u16 VarGet(struct UnkSavStruct80* arg, u16);
extern u16* GetVarPointer(struct UnkSavStruct80* arg, u16);
extern struct SaveBlock2 * ScriptEnvironment_GetSav2Ptr(struct UnkSavStruct80* unk);

extern void * FUN_02039438(struct UnkSavStruct80* arg, u8 idx);

extern u32 MOD05_021E27E8(struct UnkSavStruct80* arg, u8, u8);
extern void MOD05_021E288C(u32 *);
extern void MOD05_021E28A0(struct UnkSavStruct80* arg, u32 *);

THUMB_FUNC BOOL ScrCmd_GiveMoney(struct ScriptContext * ctx)
{
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(ctx->unk80);
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);

    u32 amount = ScriptReadWord(ctx);
    PlayerProfile_AddMoney(player, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeMoneyImmediate(struct ScriptContext * ctx)
{
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(ctx->unk80);
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);

    u32 amount = ScriptReadWord(ctx);
    PlayerProfile_SubMoney(player, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeMoneyAddress(struct ScriptContext * ctx)
{
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(ctx->unk80);
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);

    u32 amount = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    PlayerProfile_SubMoney(player, amount);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasEnoughMoneyImmediate(struct ScriptContext * ctx)
{
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(ctx->unk80);
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);
    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    u32 amount = ScriptReadWord(ctx);
    u32 money = PlayerProfile_GetMoney(player);

    if (money < amount)
    {
        *ret_ptr = 0;
    }
    else
    {
        *ret_ptr = 1;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasEnoughMoneyAddress(struct ScriptContext * ctx)
{
    struct SaveBlock2 * sav2 = ScriptEnvironment_GetSav2Ptr(ctx->unk80);
    struct PlayerData * player = Sav2_PlayerData_GetProfileAddr(sav2);
    u16 * ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    u32 amount = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u32 money = PlayerProfile_GetMoney(player);

    if (money < amount)
    {
        *ret_ptr = 0;
    }
    else
    {
        *ret_ptr = 1;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0072(struct ScriptContext * ctx)
{
    struct UnkSavStruct80 * sav_ptr = ctx->unk80;
    u32 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u32 unk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u32 *unk_ret_ptr = FUN_02039438(sav_ptr, 0x27);

    *unk_ret_ptr = MOD05_021E27E8(ctx->unk80, (u8)unk1, (u8)unk2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0073(struct ScriptContext * ctx)
{
    u32 ** unk = FUN_02039438(ctx->unk80, 0x27);
    MOD05_021E288C(*unk);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0074(struct ScriptContext * ctx)
{
    u32 ** unk = FUN_02039438(ctx->unk80, 0x27);
    MOD05_021E28A0(ctx->unk80, *unk);

    return FALSE;
}
