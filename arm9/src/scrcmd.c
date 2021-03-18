#include "scrcmd.h"
#include "unk_0204639C.h"

extern u16 *GetVarPointer(struct UnkSavStruct80* arg, u16);
extern u16 VarGet(struct UnkSavStruct80* arg, u16 wk);
extern void *FUN_02039438(struct UnkSavStruct80* arg, u32 id);
extern void *CreateScriptContext(struct UnkSavStruct80* arg, u16 id);
extern u8 FUN_02058448(u32 param0);
extern void FlagSet(struct UnkSavStruct80 *arg, u16 flag);
extern void FlagClear(struct UnkSavStruct80 *arg, u16 flag);
extern u8 FlagCheck(struct UnkSavStruct80 *arg, u16 flag);
extern void TrainerFlagSet(struct UnkSavStruct80 *arg, u16 flag);
extern void TrainerFlagClear(struct UnkSavStruct80 *arg, u16 flag);
extern u8 TrainerFlagCheck(struct UnkSavStruct80 *arg, u16 flag);
extern void MOD05_ShowMessageInField(struct ScriptContext *ctx, struct MsgData *msgData, u16 id);
extern void MOD05_021E2BD0(struct ScriptContext *ctx, struct MsgData *msgData, u16 msgId, u32 param4, void *param5);
extern BOOL FUN_0203A2F0(struct ScriptContext *ctx);
extern void MOD05_021E2C58(struct ScriptContext *ctx, u16 typ, u16 id, u16 word1, s16 word2, u8 param5);

static BOOL RunPauseTimer(struct ScriptContext* ctx);
static u32 Compare(u16 a, u16 b);
static BOOL FUN_02039CC8(struct ScriptContext* ctx);

extern u8 sScriptConditionTable[6][3];

THUMB_FUNC BOOL ScrCmd_Nop(struct ScriptContext* ctx)
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Dummy(struct ScriptContext* ctx)
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_End(struct ScriptContext* ctx)
{
    StopScript(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Wait(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* arg = ctx->unk80;
    u16 num = ScriptReadHalfword(ctx);
    u16 wk = ScriptReadHalfword(ctx);
    u16* VarPointer = GetVarPointer(arg, wk);
    *VarPointer = num;
    ctx->data[0] = wk;
    SetupNativeScript(ctx, RunPauseTimer);
    return TRUE;
}

THUMB_FUNC static BOOL RunPauseTimer(struct ScriptContext* ctx)
{
    u16* VarPointer = GetVarPointer(ctx->unk80, (u16)ctx->data[0]);
    *VarPointer = (u16)(*VarPointer - 1);
    return !(*VarPointer);
}

THUMB_FUNC BOOL ScrCmd_DebugWatch(struct ScriptContext* ctx)
{
    u16 wk = ScriptReadHalfword(ctx);
    VarGet(ctx->unk80, wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadByte(struct ScriptContext* ctx)
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadByte(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadWord(struct ScriptContext* ctx)
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadWord(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadByteFromAddr(struct ScriptContext* ctx)
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = *(u8 *)ScriptReadWord(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WriteByteToAddr(struct ScriptContext* ctx)
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = ScriptReadByte(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetPtrByte(struct ScriptContext* ctx)
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = (u8)ctx->data[ScriptReadByte(ctx)];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyLocal(struct ScriptContext* ctx)
{
    u8 index_store = ScriptReadByte(ctx);
    u8 index_load = ScriptReadByte(ctx);
    ctx->data[index_store] = ctx->data[index_load];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyByte(struct ScriptContext* ctx)
{
    u8 *target = (u8 *)ScriptReadWord(ctx);
    u8 *source = (u8 *)ScriptReadWord(ctx);
    *target = *source;
    return FALSE;
}

THUMB_FUNC static u32 Compare(u16 a, u16 b)
{
    if (a < b)
    {
        return 0;
    }
    else if (a == b)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

THUMB_FUNC BOOL ScrCmd_CompareLocalToLocal(struct ScriptContext* ctx)
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareLocalToValue(struct ScriptContext* ctx)
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareLocalToAddr(struct ScriptContext* ctx)
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToLocal(struct ScriptContext* ctx)
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToValue(struct ScriptContext* ctx)
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToAddr(struct ScriptContext* ctx)
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareVarToValue(struct ScriptContext* ctx)
{
    u16 a = *GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 b = ScriptReadHalfword(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareVarToVar(struct ScriptContext* ctx)
{
    u16 *a = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 *b = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    ctx->comparisonResult = (u8)Compare(*a, *b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_RunScript(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* unk80 = ctx->unk80;
    u8 *unk1 = (u8 *)FUN_02039438(unk80, 0x7);
    u32 **unk2 = (u32 **)FUN_02039438(unk80, 0xe);
    u16 id = ScriptReadHalfword(ctx);

    *unk2 = CreateScriptContext(unk80, id);
    *unk1 = (u8)(*unk1 + 1);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_RunScriptWait(struct ScriptContext* ctx)
{
    struct UnkSavStruct80* unk80 = ctx->unk80;
    u8 *unk1 = (u8 *)FUN_02039438(unk80, 0x5);
    u8 *unk2 = (u8 *)FUN_02039438(unk80, 0x7);
    u32 **unk3 = (u32 **)FUN_02039438(unk80, 0xe);

    u16 id = ScriptReadHalfword(ctx);
    *unk1 = 1;
    *unk3 = CreateScriptContext(unk80, id);
    *unk2 = (u8)(*unk2 + 1);

    SetupNativeScript(ctx, FUN_02039CC8);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_02039CC8(struct ScriptContext* ctx)
{
    u8* unk = FUN_02039438(ctx->unk80, 0x5);

    if (*unk == 0)
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_RestartCurrentScript(struct ScriptContext* ctx)
{
    u8* unk = (u8 *)FUN_02039438(ctx->unk80, 0x5);

    *unk = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GoTo(struct ScriptContext* ctx)
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptJump(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ObjectGoTo(struct ScriptContext* ctx)
{
    u32* unk = FUN_02039438(ctx->unk80, 0xa);
    u8 id = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);
    if (FUN_02058448(*unk) == id)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_BgGoTo(struct ScriptContext* ctx)
{
    u32 bgId = FUN_02046534(ctx->unk74);
    u8 id = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (bgId == id)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_DirectionGoTo(struct ScriptContext* ctx)
{
    u32 *playerDirection = FUN_02039438(ctx->unk80, 0x9);
    u8 dir = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (*playerDirection == dir)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Call(struct ScriptContext* ctx)
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptCall(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Return(struct ScriptContext* ctx)
{
    ScriptReturn(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GoToIf(struct ScriptContext* ctx)
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CallIf(struct ScriptContext* ctx)
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptCall(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetFlag(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    FlagSet(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ClearFlag(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    FlagClear(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckFlag(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    ctx->comparisonResult = FlagCheck(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckFlagVar(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 *wk2 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    *wk2 = FlagCheck(unk80, *wk1);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetFlagVar(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 *wk = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    FlagSet(unk80, *wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetTrainerFlag(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    TrainerFlagSet(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ClearTrainerFlag(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    TrainerFlagClear(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckTrainerFlag(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    ctx->comparisonResult = TrainerFlagCheck(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_AddVar(struct ScriptContext* ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = (u16)(*wk1 + wk2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SubVar(struct ScriptContext* ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = (u16)(*wk1 - wk2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetVar(struct ScriptContext* ctx)
{
    u16 *wk = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    *wk = ScriptReadHalfword(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyVar(struct ScriptContext* ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 *wk2 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = *wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetOrCopyVar(struct ScriptContext* ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Message(struct ScriptContext* ctx)
{
    u8 id = ScriptReadByte(ctx);
    MOD05_ShowMessageInField(ctx, ctx->msgData, id);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_MessageFrom(struct ScriptContext* ctx)
{
    u16 arc = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 msg = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct MsgData *msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, arc, 32);
    MOD05_ShowMessageInField(ctx, msgData, msg);
    DestroyMsgData(msgData);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_MessageFrom2(struct ScriptContext* ctx)
{
    u16 arc = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 msg = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct MsgData *msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, arc, 32);
    MOD05_021E2BD0(ctx, msgData, msg, 1, NULL);
    DestroyMsgData(msgData);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FC(struct ScriptContext* ctx)
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    u16 word2 = ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 0xff);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FD(struct ScriptContext* ctx)
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    u16 word2 = ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 1);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FE(struct ScriptContext* ctx)
{
    u8 id = ScriptReadByte(ctx);

    if (ctx->unk80->unkA8 == NULL)
    {
        return FALSE;
    }

    u16 *unkArr = ctx->unk80->unkA8->unk90[id].unk0;
    if (unkArr[0] == 0xFFFF)
    {
        struct MsgData *msgdata = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 0x22b, 32);
        MOD05_021E2BD0(ctx, msgdata, unkArr[1], 1, NULL);
        DestroyMsgData(msgdata);
    }
    else
    {
        MOD05_021E2C58(ctx, unkArr[0], unkArr[1], unkArr[2], (s16)unkArr[3], 1);
    }
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}
