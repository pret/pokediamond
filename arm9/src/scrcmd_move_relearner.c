#include "scrcmd.h"
#include "heap.h"
#include "party.h"
#include "unk_020377F0.h"
#include "unk_02088DD8.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem*, int idx);

extern struct UnkStruct_02037CF0* FUN_02037CF0(u32 heap_id, struct FieldSystem*, u8);
extern u8 FUN_02037D5C(struct UnkStruct_02037CF0*);
extern void FUN_02038864(struct FieldSystem*, MoveRelearner *moveRelearner);
extern BOOL FUN_0203BC04(struct ScriptContext* ctx);

THUMB_FUNC BOOL ScrCmd_Unk01C6(struct ScriptContext* ctx) { //01C6 - todo: MoveInfo?
    u16 unk = ScriptGetVar(ctx);
    struct UnkStruct_02037CF0 **runningAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    *runningAppData = FUN_02037CF0(32, ctx->fieldSystem, (u8)unk);

    SetupNativeScript(ctx, FUN_0203BC04);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk01C7(struct ScriptContext* ctx) { //01C7 - todo: StoreMove?
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct UnkStruct_02037CF0 **runningAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    GF_ASSERT(*runningAppData != NULL);

    *ret_ptr = FUN_02037D5C(*runningAppData);
    if (*ret_ptr == 4)
    {
        *ret_ptr = 0xFF;
    }

    FreeToHeap(*runningAppData);
    *runningAppData = NULL;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk021E(struct ScriptContext* ctx) //021E
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk021F(struct ScriptContext* ctx) { //021F
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);
    u16 *eligibleMoves = GetEligibleLevelUpMoves(pokemon, 32);

    *ret_ptr = (u16)FUN_02088EF8(eligibleMoves);
    FreeToHeap(eligibleMoves);

    return FALSE;
}

THUMB_FUNC void FUN_02045E74(struct ScriptContext* ctx, u8 a1, struct Pokemon* pokemon, u16 *eligibleMoves) {
    MoveRelearner **moveRelearnerPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    MoveRelearner *moveRelearner = FUN_02088DD8(32);
    *moveRelearnerPtr = moveRelearner;

    moveRelearner->pokemon = pokemon;

    struct SaveBlock2* sav2 = ScriptEnvironment_GetSavePtr(ctx->fieldSystem);
    moveRelearner->player = Save_PlayerData_GetProfileAddr(sav2);

    moveRelearner->options = Save_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveBlock2);
    moveRelearner->eligibleMoves = eligibleMoves;
    moveRelearner->unk15 = a1;
    FUN_02038864(ctx->fieldSystem, moveRelearner);

    SetupNativeScript(ctx, FUN_0203BC04);
    FreeToHeap(eligibleMoves);
}

THUMB_FUNC BOOL ScrCmd_Unk0220(struct ScriptContext* ctx) //0220
{
#pragma unused(ctx)
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0221(struct ScriptContext* ctx) //0221 - todo: RememberMove?
{
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(ctx->fieldSystem->saveBlock2);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);
    u16 *eligibleMoves  = GetEligibleLevelUpMoves(pokemon, 32);

    FUN_02045E74(ctx, 1, pokemon, eligibleMoves);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0224(struct ScriptContext* ctx) //0224 - todo: TeachMove?
{
    u16 mon_idx = ScriptGetVar(ctx);
    u16 move = ScriptGetVar(ctx);
    struct PlayerParty *party = SaveArray_PlayerParty_Get(ctx->fieldSystem->saveBlock2);
    struct Pokemon *pokemon = GetPartyMonByIndex(party, mon_idx);

    u16 *eligibleMoves = AllocFromHeap(32, 2 * sizeof(u16));
    eligibleMoves[0] = move;
    eligibleMoves[1] = 0xFFFF;

    FUN_02045E74(ctx, 0, pokemon, eligibleMoves);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0222(struct ScriptContext* ctx) //0222 - todo: DummyMoveCmd?
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0223(struct ScriptContext* ctx) //0223 - todo: RememberMoveResponse? - destroys the MoveRelearner - find better name
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    MoveRelearner **moveRelearnerPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    MoveRelearner *moveRelearner = *moveRelearnerPtr;

    GF_ASSERT(moveRelearner != NULL);

    if (moveRelearner->unk16 == 0)
    {
        *ret_ptr = 0;
    }
    else
    {
        *ret_ptr = 0xFF;
    }

    FUN_02088DF0(moveRelearner);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0225(struct ScriptContext* ctx) //0225 - todo: TeachMoveResponse? - destroys the MoveRelearner - find better name
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    MoveRelearner **moveRelearnerPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    MoveRelearner *moveRelearner = *moveRelearnerPtr;

    GF_ASSERT(moveRelearner != NULL);

    if (moveRelearner->unk16 == 0)
    {
        *ret_ptr = 0;
    }
    else
    {
        *ret_ptr = 0xFF;
    }

    FUN_02088DF0(moveRelearner);
    return FALSE;
}
