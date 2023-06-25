#include "global.h"
#include "scrcmd.h"
#include "heap.h"
#include "party.h"
#include "unk_020377F0.h"
#include "unk_02088DD8.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem*, int idx);

extern struct UnkStruct_02037CF0* sub_02037CF0(HeapID heapId, struct FieldSystem*, u8);
extern u8 sub_02037D5C(struct UnkStruct_02037CF0*);
extern void sub_02038864(struct FieldSystem*, MoveRelearner *moveRelearner);
extern BOOL sub_0203BC04(struct ScriptContext* ctx);

BOOL ScrCmd_Unk01C6(struct ScriptContext* ctx) { //01C6 - todo: MoveInfo?
    u16 unk = ScriptGetVar(ctx);
    struct UnkStruct_02037CF0 **runningAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    *runningAppData = sub_02037CF0(HEAP_ID_32, ctx->fieldSystem, (u8)unk);

    SetupNativeScript(ctx, sub_0203BC04);
    return TRUE;
}

BOOL ScrCmd_Unk01C7(struct ScriptContext* ctx) { //01C7 - todo: StoreMove?
    u16 *ret_ptr = ScriptGetVarPointer(ctx);
    struct UnkStruct_02037CF0 **runningAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    GF_ASSERT(*runningAppData != NULL);

    *ret_ptr = sub_02037D5C(*runningAppData);
    if (*ret_ptr == 4)
    {
        *ret_ptr = 0xFF;
    }

    FreeToHeap(*runningAppData);
    *runningAppData = NULL;
    return FALSE;
}

BOOL ScrCmd_Unk021E(struct ScriptContext* ctx) //021E
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Unk021F(struct ScriptContext* ctx) { //021F
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(ctx->fieldSystem->saveData);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);
    u16 *eligibleMoves = GetEligibleLevelUpMoves(pokemon, HEAP_ID_32);

    *ret_ptr = (u16)sub_02088EF8(eligibleMoves);
    FreeToHeap(eligibleMoves);

    return FALSE;
}

void sub_02045E74(struct ScriptContext* ctx, u8 a1, struct Pokemon* pokemon, u16 *eligibleMoves) {
    MoveRelearner **moveRelearnerPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    MoveRelearner *moveRelearner = sub_02088DD8(HEAP_ID_32);
    *moveRelearnerPtr = moveRelearner;

    moveRelearner->pokemon = pokemon;

    struct SaveData* save = FieldSystem_GetSaveDataPtr(ctx->fieldSystem);
    moveRelearner->player = Save_PlayerData_GetProfileAddr(save);

    moveRelearner->options = Save_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveData);
    moveRelearner->eligibleMoves = eligibleMoves;
    moveRelearner->unk15 = a1;
    sub_02038864(ctx->fieldSystem, moveRelearner);

    SetupNativeScript(ctx, sub_0203BC04);
    FreeToHeap(eligibleMoves);
}

BOOL ScrCmd_Unk0220(struct ScriptContext* ctx) //0220
{
#pragma unused(ctx)
    return TRUE;
}

BOOL ScrCmd_Unk0221(struct ScriptContext* ctx) //0221 - todo: RememberMove?
{
    u16 mon_idx = ScriptGetVar(ctx);
    struct PlayerParty* party = SaveArray_PlayerParty_Get(ctx->fieldSystem->saveData);
    struct Pokemon* pokemon = GetPartyMonByIndex(party, mon_idx);
    u16 *eligibleMoves  = GetEligibleLevelUpMoves(pokemon, HEAP_ID_32);

    sub_02045E74(ctx, 1, pokemon, eligibleMoves);
    return TRUE;
}

BOOL ScrCmd_Unk0224(struct ScriptContext* ctx) //0224 - todo: TeachMove?
{
    u16 mon_idx = ScriptGetVar(ctx);
    u16 move = ScriptGetVar(ctx);
    struct PlayerParty *party = SaveArray_PlayerParty_Get(ctx->fieldSystem->saveData);
    struct Pokemon *pokemon = GetPartyMonByIndex(party, mon_idx);

    u16 *eligibleMoves = AllocFromHeap(HEAP_ID_32, 2 * sizeof(u16));
    eligibleMoves[0] = move;
    eligibleMoves[1] = 0xFFFF;

    sub_02045E74(ctx, 0, pokemon, eligibleMoves);
    return TRUE;
}

BOOL ScrCmd_Unk0222(struct ScriptContext* ctx) //0222 - todo: DummyMoveCmd?
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Unk0223(struct ScriptContext* ctx) //0223 - todo: RememberMoveResponse? - destroys the MoveRelearner - find better name
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

    sub_02088DF0(moveRelearner);
    return FALSE;
}

BOOL ScrCmd_Unk0225(struct ScriptContext* ctx) //0225 - todo: TeachMoveResponse? - destroys the MoveRelearner - find better name
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

    sub_02088DF0(moveRelearner);
    return FALSE;
}
