#include "scrcmd.h"
#include "daycare.h"
#include "party.h"
#include "script_buffers.h"

extern void* FUN_02039438(struct UnkSavStruct80*, int idx);

extern void MOD05_021EC57C(struct PlayerParty* party, u8 idx, struct DayCare* daycare, struct SaveBlock2* sav2);
extern u16 MOD05_021EC71C(struct PlayerParty* party, struct ScrStrBufs* mgr, struct DayCare* daycare, u8 idx);
extern u16 MOD05_021EC854(struct DayCare* daycare, u8 idx, struct ScrStrBufs* mgr);
extern u8 MOD05_021EC864(struct DayCare* daycare, int idx, struct ScrStrBufs* mgr);
extern void MOD05_021ECD64(struct DayCare* daycare);
extern void MOD05_DayCare_GiveEggToPlayer(struct DayCare* daycare, struct PlayerParty* party, struct PlayerData* player);
extern void MOD05_021ED4E0(struct DayCare* daycare, struct ScrStrBufs* mgr);
extern void MOD05_021ED52C(struct DayCare* daycare, u8 idx1, u8 idx2, u8 idx3, u8 idx4, struct ScrStrBufs* mgr);
extern u16 MOD05_021ED5C4(struct PlayerParty* party, int idx, struct ScrStrBufs* mgr);
extern u16 MOD05_021ED5EC(struct DayCare* daycare);
extern u32 MOD05_021ED644(struct DayCare* daycare);

THUMB_FUNC BOOL ScrCmd_Unk016D(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    struct ScrStrBufs** mgr = FUN_02039438(ctx->unk80, 15);
    struct DayCare* daycare = Sav2_DayCare_get(sav2);

    MOD05_021ED4E0(daycare, *mgr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk016E(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct SaveBlock2* sav2 = sav_ptr->saveBlock2;
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = MOD05_021ED5EC(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A8(struct ScriptContext* ctx)
{
    struct DayCare* daycare = SavArray_get(ctx->unk80->saveBlock2, 8);
    MOD05_021ECD64(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A9(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct DayCare* daycare = SavArray_get(sav_ptr->saveBlock2, 8);
    struct PlayerParty* party = SavArray_PlayerParty_get(sav_ptr->saveBlock2);
    struct SaveBlock2* sav2 = ScriptEnvironment_GetSav2Ptr(ctx->unk80);
    struct PlayerData* player = Sav2_PlayerData_GetProfileAddr(sav2);

    MOD05_DayCare_GiveEggToPlayer(daycare, party, player);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A4(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct ScrStrBufs** mgr = FUN_02039438(sav_ptr, 15);
    struct SaveBlock2* sav2 = sav_ptr->saveBlock2;
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 idx = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct DayCare* daycare = SavArray_get(sav2, 8);
    struct PlayerParty* party = SavArray_PlayerParty_get(sav_ptr->saveBlock2);

    *ret_ptr = MOD05_021EC71C(party, *mgr, daycare, (u8)idx);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01AA(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct ScrStrBufs** mgr = FUN_02039438(sav_ptr, 15);
    struct SaveBlock2* sav2 = sav_ptr->saveBlock2;
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 idx = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = MOD05_021EC854(daycare, (u8)idx, *mgr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01AE(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    struct ScrStrBufs** mgr = FUN_02039438(ctx->unk80, 15);
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 idx = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = MOD05_021EC864(daycare, idx, *mgr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01AF(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct ScrStrBufs** mgr = FUN_02039438(ctx->unk80, 15);
    u16 unused = ScriptReadHalfword(ctx);
    u16 idx = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(sav_ptr->saveBlock2);

    *ret_ptr = MOD05_021ED5C4(party, idx, *mgr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01B0(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;
    struct SaveBlock2* sav2 = sav_ptr->saveBlock2;
    u16 idx = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct PlayerParty* party = SavArray_PlayerParty_get(sav_ptr->saveBlock2);
    struct DayCare* daycare = SavArray_get(sav2, 8);

    MOD05_021EC57C(party, (u8)idx, daycare, sav2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01BC(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    struct ScrStrBufs** mgr = FUN_02039438(ctx->unk80, 15);
    u16 idx1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 idx2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 idx3 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 idx4 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct DayCare* daycare = Sav2_DayCare_get(sav2);

    MOD05_021ED52C(daycare, (u8)idx1, (u8)idx2, (u8)idx3, (u8)idx4, *mgr);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01BE(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = (u16)MOD05_021ED644(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01BF(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct DayCare* daycare = SavArray_get(sav2, 8);

    *ret_ptr = (u16)Sav2_DayCare_GetEggPID(daycare);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A5(struct ScriptContext* ctx)
{
    u16* unused = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A6(struct ScriptContext* ctx)
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01A7(struct ScriptContext* ctx)
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01AD(struct ScriptContext* ctx)
{
    u16* unused = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    return FALSE;
}
