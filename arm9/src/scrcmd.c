#include "scrcmd.h"

extern u16 *GetVarPointer(struct UnkStruct_0204639C* arg, u16);
extern u16 VarGet(struct UnkStruct_0204639C* arg, u16 wk);

static BOOL RunPauseTimer(struct ScriptContext* ctx);
static u32 Compare(u16 a, u16 b);

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
    struct UnkStruct_0204639C* arg = ctx->unk80;
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
