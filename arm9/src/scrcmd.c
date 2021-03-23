#include "scrcmd.h"
#include "unk_0204639C.h"
#include "main.h"
#include "options.h"
#include "player_data.h"
#include "text.h"

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
extern void MOD05_021E2C58(struct ScriptContext *ctx, u16 typ, u16 id, u16 word1, s16 word2, u8 param5);
extern struct ScrStrBufs *MOD06_02244210(struct SaveBlock2 *sav, u16 poke, u16 sex, u8 flag, u8 *unk);
extern void MOD05_021E2CBC(struct ScriptContext *ctx, struct ScrStrBufs *str, u8 param2, u32 param3);
extern void MOD05_021E2BB8(void *param0, struct ScriptContext *ctx);
extern BOOL FUN_020546C8(u8 param0);
extern u32 FUN_02058488(u32 param0);
extern BOOL FUN_02030F40(void);
extern void FUN_02055304(u32 param0, u32 param1);
extern void FUN_02039460(struct UnkSavStruct80 *arg);
extern void FUN_020545B8(u32 param0, u8 *param1, u32 param2);
extern void FUN_02054608(u8 *param0, struct Options *options);
extern void FUN_0200D0E0(u32 *param0, u32 param1);
extern void FUN_02019178(u32 *param0);
extern void FUN_020179E0(u32 param0, u32 param1, u32 param2, u16 val);
extern u32 FUN_02058510(u32 param0, u32 param1);
extern void MOD05_021E8128(u32 param0, u8 type, u16 map);
extern void MOD05_021E8130(u32 param0, u32 param1);
extern void MOD05_021E8158(struct UnkSavStruct80 *unk80);
extern u32 MOD05_021E8140(u32 param0);
extern BOOL MOD05_021E8148(u32 param0);
extern u8 FUN_02054658(u32 param0, struct String *str, struct Options *opt, u32 param3);
extern void MOD05_021E8144(u32 param0);
extern void FUN_0200CB00(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
extern u32 Std_CreateYesNoMenu(u32 param0, u8 **param1, u32 param2, u32 param3, u32 param4);
extern u32 FUN_020021AC(u32 param0, u32 param1);
extern u32 FUN_0200D858(u32 *param0, u32 param1);
extern void FUN_0200DBFC(u32 param0);
extern u32 MOD05_021E1BF8(struct UnkSavStruct80 *arg, u8 param1, u8 param2, u8 param3, u8 param4, u16 *param5, u32 param6, u32 *param7, struct MsgData *msgData);
extern void MOD05_021E1C4C(u32 param0, u32 param1, u32 param2);
extern void MOD05_021E1C54(u32 param0);
extern u32 FUN_02052714(u32 param0);
extern void MOD05_021E1ECC(u32 param0);

extern u8 *UNK_020F34E0;

static BOOL RunPauseTimer(struct ScriptContext *ctx);
static u32 Compare(u16 a, u16 b);
static BOOL FUN_02039CC8(struct ScriptContext *ctx);
/*static*/ BOOL FUN_0203A2F0(struct ScriptContext *ctx);
static BOOL FUN_0203A46C(struct ScriptContext *ctx);
static BOOL FUN_0203A4AC(struct ScriptContext *ctx);
static BOOL FUN_0203A4E0(struct ScriptContext *ctx);
static BOOL FUN_0203A570(struct ScriptContext *ctx);
static BOOL FUN_0203A6C8(struct ScriptContext *ctx);
static BOOL FUN_0203A8A0(struct ScriptContext *ctx);
static BOOL FUN_0203A94C(struct ScriptContext *ctx);
static BOOL FUN_0203AA0C(struct ScriptContext *ctx);
static BOOL FUN_0203AB00(struct ScriptContext *ctx);
/*static*/ BOOL FUN_0203AD2C(struct ScriptContext *ctx);
static BOOL FUN_0203AD78(struct ScriptContext *ctx);

extern u8 sScriptConditionTable[6][3];

THUMB_FUNC BOOL ScrCmd_Nop(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Dummy(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_End(struct ScriptContext *ctx)
{
    StopScript(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Wait(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *arg = ctx->unk80;
    u16 num = ScriptReadHalfword(ctx);
    u16 wk = ScriptReadHalfword(ctx);
    u16* VarPointer = GetVarPointer(arg, wk);
    *VarPointer = num;
    ctx->data[0] = wk;
    SetupNativeScript(ctx, RunPauseTimer);
    return TRUE;
}

THUMB_FUNC static BOOL RunPauseTimer(struct ScriptContext *ctx)
{
    u16* VarPointer = GetVarPointer(ctx->unk80, (u16)ctx->data[0]);
    *VarPointer = (u16)(*VarPointer - 1);
    return !(*VarPointer);
}

THUMB_FUNC BOOL ScrCmd_DebugWatch(struct ScriptContext *ctx)
{
    u16 wk = ScriptReadHalfword(ctx);
    VarGet(ctx->unk80, wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadByte(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadByte(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadWord(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadWord(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadByteFromAddr(struct ScriptContext *ctx)
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = *(u8 *)ScriptReadWord(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WriteByteToAddr(struct ScriptContext *ctx)
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = ScriptReadByte(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetPtrByte(struct ScriptContext *ctx)
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = (u8)ctx->data[ScriptReadByte(ctx)];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyLocal(struct ScriptContext *ctx)
{
    u8 index_store = ScriptReadByte(ctx);
    u8 index_load = ScriptReadByte(ctx);
    ctx->data[index_store] = ctx->data[index_load];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyByte(struct ScriptContext *ctx)
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

THUMB_FUNC BOOL ScrCmd_CompareLocalToLocal(struct ScriptContext *ctx)
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareLocalToValue(struct ScriptContext *ctx)
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareLocalToAddr(struct ScriptContext *ctx)
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToLocal(struct ScriptContext *ctx)
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToValue(struct ScriptContext *ctx)
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToAddr(struct ScriptContext *ctx)
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareVarToValue(struct ScriptContext *ctx)
{
    u16 a = *GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 b = ScriptReadHalfword(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareVarToVar(struct ScriptContext *ctx)
{
    u16 *a = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 *b = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    ctx->comparisonResult = (u8)Compare(*a, *b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_RunScript(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u8 *unk1 = (u8 *)FUN_02039438(unk80, 0x7);
    u32 **unk2 = (u32 **)FUN_02039438(unk80, 0xe);
    u16 id = ScriptReadHalfword(ctx);

    *unk2 = CreateScriptContext(unk80, id);
    *unk1 = (u8)(*unk1 + 1);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_RunScriptWait(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
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

THUMB_FUNC static BOOL FUN_02039CC8(struct ScriptContext *ctx)
{
    u8* unk = FUN_02039438(ctx->unk80, 0x5);

    if (*unk == 0)
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_RestartCurrentScript(struct ScriptContext *ctx)
{
    u8* unk = (u8 *)FUN_02039438(ctx->unk80, 0x5);

    *unk = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GoTo(struct ScriptContext *ctx)
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptJump(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ObjectGoTo(struct ScriptContext *ctx)
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

THUMB_FUNC BOOL ScrCmd_BgGoTo(struct ScriptContext *ctx)
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

THUMB_FUNC BOOL ScrCmd_DirectionGoTo(struct ScriptContext *ctx)
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

THUMB_FUNC BOOL ScrCmd_Call(struct ScriptContext *ctx)
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptCall(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Return(struct ScriptContext *ctx)
{
    ScriptReturn(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GoToIf(struct ScriptContext *ctx)
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CallIf(struct ScriptContext *ctx)
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptCall(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetFlag(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    FlagSet(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ClearFlag(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    FlagClear(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckFlag(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = ScriptReadHalfword(ctx);
    ctx->comparisonResult = FlagCheck(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckFlagVar(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 *wk2 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    *wk2 = FlagCheck(unk80, *wk1);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetFlagVar(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 *wk = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    FlagSet(unk80, *wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetTrainerFlag(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    TrainerFlagSet(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ClearTrainerFlag(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    TrainerFlagClear(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckTrainerFlag(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 flag = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    ctx->comparisonResult = TrainerFlagCheck(unk80, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_AddVar(struct ScriptContext *ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = (u16)(*wk1 + wk2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SubVar(struct ScriptContext *ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = (u16)(*wk1 - wk2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetVar(struct ScriptContext *ctx)
{
    u16 *wk = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    *wk = ScriptReadHalfword(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyVar(struct ScriptContext *ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 *wk2 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = *wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetOrCopyVar(struct ScriptContext *ctx)
{
    u16 *wk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    *wk1 = wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Message(struct ScriptContext *ctx)
{
    u8 id = ScriptReadByte(ctx);
    MOD05_ShowMessageInField(ctx, ctx->msgData, id);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_MessageFrom(struct ScriptContext *ctx)
{
    u16 arc = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 msg = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct MsgData *msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, arc, 32);
    MOD05_ShowMessageInField(ctx, msgData, msg);
    DestroyMsgData(msgData);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_MessageFrom2(struct ScriptContext *ctx)
{
    u16 arc = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 msg = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    struct MsgData *msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, arc, 32);
    MOD05_021E2BD0(ctx, msgData, msg, 1, NULL);
    DestroyMsgData(msgData);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FC(struct ScriptContext *ctx)
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    s16 word2 = (s16)ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 0xff);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FD(struct ScriptContext *ctx)
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    s16 word2 = (s16)ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 1);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FE(struct ScriptContext *ctx)
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

THUMB_FUNC BOOL ScrCmd_Unk01FF(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u8 msg = ScriptReadByte(ctx);
    u16 poke = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 sex = ScriptReadHalfword(ctx);
    u8 flag = ScriptReadByte(ctx);
    u8 unk = 0;

    struct ScrStrBufs *str = MOD06_02244210(unk80->saveBlock2, poke, sex, flag, &unk);
    MOD05_021E2CBC(ctx, str, (u8)(msg + unk), 1);
    ScrStrBufs_delete(str);

    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk026D(struct ScriptContext *ctx) //message unown font?
{
    struct UnkStruct_0203A288 myLocalStruct;
    u16 msg = ScriptReadHalfword(ctx);

    MOD05_021E2BB8(&myLocalStruct, ctx);
    myLocalStruct.unk2 = 3;

    MOD05_021E2BD0(ctx, ctx->msgData, msg, 0, &myLocalStruct);
    SetupNativeScript(ctx, FUN_0203A2F0);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk002C(struct ScriptContext *ctx)
{
    u8 msg = ScriptReadByte(ctx);
    MOD05_021E2BD0(ctx, ctx->msgData, msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC /*static*/ BOOL FUN_0203A2F0(struct ScriptContext *ctx)
{
    u8 *unk = (u8 *)FUN_02039438(ctx->unk80, 3);
    return FUN_020546C8(*unk);
}

THUMB_FUNC BOOL ScrCmd_Unk002D(struct ScriptContext *ctx)
{
    u16 msg = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk02C0(struct ScriptContext *ctx)
{
    struct UnkStruct_0203A288 myLocalStruct;
    u16 msg = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

    MOD05_021E2BB8(&myLocalStruct, ctx);
    myLocalStruct.unk1 = 1;

    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 1, &myLocalStruct);
    SetupNativeScript(ctx, FUN_0203A2F0);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk002E(struct ScriptContext *ctx)
{
    u16 msg = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 0, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk020C(struct ScriptContext *ctx)
{
    u32 *unk = FUN_02039438(ctx->unk80, 0xa);
    u8 msg = (u8)FUN_02058488(*unk);
    MOD05_021E2BD0(ctx, ctx->msgData, msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk002F(struct ScriptContext *ctx)
{
    u8 msg = ScriptReadByte(ctx);

    if (!FUN_02030F40())
    {
        MOD05_021E2BD0(ctx, ctx->msgData, msg, 1, NULL);
    }
    else
    {
        struct UnkStruct_0203A288 myLocalStruct;
        MOD05_021E2BB8(&myLocalStruct, ctx);
        myLocalStruct.unk0 = 1;
        myLocalStruct.unk1 = 1;
        MOD05_021E2BD0(ctx, ctx->msgData, msg, 0, &myLocalStruct);
    }

    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_WaitButtonAB(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, FUN_0203A46C);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A46C(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    if (gMain.unk48 & 0x3) // Mask (A | B) ?
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WaitButtonABTime(struct ScriptContext *ctx)
{
    ctx->data[0] = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    SetupNativeScript(ctx, FUN_0203A4AC);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A4AC(struct ScriptContext *ctx)
{
    if (gMain.unk48 & 0x3) // Mask (A | B) ?
    {
        return TRUE;
    }
    ctx->data[0] = ctx->data[0] - 1;

    if (ctx->data[0] == 0)
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WaitButton(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, FUN_0203A4E0);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A4E0(struct ScriptContext *ctx)
{
    if (gMain.unk48 & 3)
    {
        return TRUE;
    }
    else if (gMain.unk48 & 0x40)
    {
        FUN_02055304(ctx->unk80->unk38, 0);
    }
    else if (gMain.unk48 & 0x80)
    {
        FUN_02055304(ctx->unk80->unk38, 1);
    }
    else if (gMain.unk48 & 0x20)
    {
        FUN_02055304(ctx->unk80->unk38, 2);
    }
    else if (gMain.unk48 & 0x10)
    {
        FUN_02055304(ctx->unk80->unk38, 3);
    }
    else if (gMain.unk48 & 0x400)
    {
        FUN_02039460(ctx->unk80);
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0032(struct ScriptContext *ctx)
{
    SetupNativeScript(ctx, FUN_0203A570);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A570(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    if (gMain.unk48 & 0x3)
    {
        return TRUE;
    }
    else if (gMain.unk48 & 0xf0)
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0033(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u8 *unk = (u8 *)FUN_02039438(unk80, 6);
    FUN_020545B8(unk80->unk08, FUN_02039438(unk80, 1), 3);
    FUN_02054608(FUN_02039438(unk80, 1), Sav2_PlayerData_GetOptionsAddr(ctx->unk80->saveBlock2));
    *unk = 1;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0034(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u32 *unk = FUN_02039438(unk80, 0x1); //windowID?
    u8 *unk2 = FUN_02039438(unk80, 0x6);
    FUN_0200D0E0(unk, 0);  //clear window?
    FUN_02019178(unk);
    *unk2 = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0035(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u32 *unk = FUN_02039438(unk80, 0x1); //windowID?
    u8 *unk2 = FUN_02039438(unk80, 0x6);
    FUN_02019178(unk);
    *unk2 = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ScrollBg(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 *xval = FUN_02039438(unk80, 0x31);
    u16 *xcnt = FUN_02039438(unk80, 0x2d);
    u16 *xdir = FUN_02039438(unk80, 0x32);
    u16 *yval = FUN_02039438(unk80, 0x33);
    u16 *ycnt = FUN_02039438(unk80, 0x2e);
    u16 *ydir = FUN_02039438(unk80, 0x34);

    *xval = ScriptReadByte(ctx);
    *xcnt = ScriptReadByte(ctx);
    *xdir = ScriptReadByte(ctx);
    *yval = ScriptReadByte(ctx);
    *ycnt = ScriptReadByte(ctx);
    *ydir = ScriptReadByte(ctx);

    SetupNativeScript(ctx, FUN_0203A6C8);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A6C8(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 *xval = FUN_02039438(unk80, 0x31);
    u16 *xdir = FUN_02039438(unk80, 0x32);
    u16 *yval = FUN_02039438(unk80, 0x33);
    u16 *ydir = FUN_02039438(unk80, 0x34);
    u16 *xcnt = FUN_02039438(unk80, 0x2d);
    u16 *ycnt = FUN_02039438(unk80, 0x2e);

    if (*xcnt == 0 && *ycnt == 0)
    {
        return TRUE;
    }

    if (*xval != 0)
    {
        if (*xdir == 0)
        {
            FUN_020179E0(unk80->unk08, 3, 1, *xval);
        }
        else
        {
            FUN_020179E0(unk80->unk08, 3, 2, *xval);
        }
    }

    if (*yval != 0)
    {
        if (*ydir == 0)
        {
            FUN_020179E0(unk80->unk08, 3, 4, *yval);
        }
        else
        {
            FUN_020179E0(unk80->unk08, 3, 5, *yval);
        }
    }

    if (*xcnt != 0)
    {
        *xcnt = (u16)(*xcnt - 1);
    }

    if (*ycnt != 0)
    {
        *ycnt = (u16)(*ycnt - 1);
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CreateMessageBox(struct ScriptContext* ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    struct String **unk1 = FUN_02039438(unk80, 0x11);
    struct String **unk2 = FUN_02039438(unk80, 0x10);
    struct ScrStrBufs **unk3 = FUN_02039438(unk80, 0x0f);
    u8 typ, msg;
    u16 wk, map;

    msg = ScriptReadByte(ctx);
    typ = ScriptReadByte(ctx);
    map = ScriptReadHalfword(ctx);
    wk = ScriptReadHalfword(ctx);

    if (map == 0)
    {
        u32 *unk4 = FUN_02039438(unk80, 10);
        map = (u16)FUN_02058510(*unk4, 0);
    }

    MOD05_021E8128(unk80->unk60, typ, map);
    MOD05_021E8130(unk80->unk60, 1);
    MOD05_021E8158(unk80);
    ReadMsgDataIntoString(ctx->msgData, msg, *unk1);
    StringExpandPlaceholders(*unk3, *unk2, *unk1);
    AddTextPrinterParameterized(MOD05_021E8140(unk80->unk60), 1, (u16 *)*unk2, 0, 0, 0, NULL);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0037(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u8 typ = ScriptReadByte(ctx);
    u16 map = ScriptReadHalfword(ctx);

    MOD05_021E8128(unk80->unk60, typ, map);
    MOD05_021E8130(unk80->unk60, 1);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0038(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u8 req = ScriptReadByte(ctx);
    MOD05_021E8130(unk80->unk60, req);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0039(struct ScriptContext *ctx)
{
    if (MOD05_021E8148(ctx->unk80->unk60) == TRUE)
    {
        return FALSE;
    }

    SetupNativeScript(ctx, FUN_0203A8A0);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A8A0(struct ScriptContext *ctx)
{
    if (MOD05_021E8148(ctx->unk80->unk60) == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk003A(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u8 *unk1 = FUN_02039438(unk80, 3);
    struct String **unk2 = FUN_02039438(unk80, 17);
    struct String **unk3 = FUN_02039438(unk80, 16);
    struct ScrStrBufs **unk4 = FUN_02039438(unk80, 15);

    u8 msg = ScriptReadByte(ctx);
    u16 wk = ScriptReadHalfword(ctx);

    ReadMsgDataIntoString(ctx->msgData, msg, *unk2);
    StringExpandPlaceholders(*unk4, *unk3, *unk2);

    *unk1 = FUN_02054658(MOD05_021E8140(unk80->unk60), *unk3, Sav2_PlayerData_GetOptionsAddr(ctx->unk80->saveBlock2), 1);
    ctx->data[0] = wk;
    SetupNativeScript(ctx, FUN_0203A94C);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A94C(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u8 *unk1 = FUN_02039438(unk80, 3);
    u16 *varPtr = GetVarPointer(unk80, (u16)ctx->data[0]);
    MOD05_021E8144(unk80->unk60);

    u32 tmp = 0xFFFF;
    if (FUN_020546C8(*unk1) == TRUE)
    {
        *varPtr = 2;
        return TRUE;
    }

    if (gMain.unk48 & 0x40)
    {
        tmp = 0;
    }
    else if (gMain.unk48 & 0x80)
    {
        tmp = 1;
    }
    else if (gMain.unk48 & 0x20)
    {
        tmp = 2;
    }
    else if (gMain.unk48 & 0x10)
    {
        tmp = 3;
    }

    if (tmp != 0xFFFF)
    {
        FUN_0201BD7C(*unk1);
        FUN_02055304(ctx->unk80->unk38, tmp);
        *varPtr = 0;
        return TRUE;
    }
    else
    {
        if (gMain.unk48 & 0x400)
        {
            FUN_0201BD7C(*unk1);
            *varPtr = 1;
            return TRUE;
        }
        return FALSE;
    }
}

THUMB_FUNC BOOL ScrCmd_Unk003B(struct ScriptContext *ctx)
{
    ctx->data[0] = ScriptReadHalfword(ctx);

    SetupNativeScript(ctx, FUN_0203AA0C);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203AA0C(struct ScriptContext *ctx)
{
    u16 *unk = GetVarPointer(ctx->unk80, (u16)ctx->data[0]);

    u32 tmp = 0xFFFF;
    if (gMain.unk48 & 0x3)
    {
        *unk = 0;
        return TRUE;
    }
    else if (gMain.unk48 & 0x40)
    {
        tmp = 0;
    }
    else if (gMain.unk48 & 0x80)
    {
        tmp = 1;
    }
    else if (gMain.unk48 & 0x20)
    {
        tmp = 2;
    }
    else if (gMain.unk48 & 0x10)
    {
        tmp = 3;
    }

    if (tmp != 0xFFFF)
    {
        FUN_02055304(ctx->unk80->unk38, tmp);
        *unk = 0;
        return TRUE;
    }
    else
    {
        if (gMain.unk48 & 0x400)
        {
            *unk = 1;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

THUMB_FUNC BOOL ScrCmd_Menu(struct ScriptContext *ctx)
{
    FUN_02039460(ctx->unk80);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_YesNoMenu(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u32 *unk = FUN_02039438(unk80, 2);
    u16 wk = ScriptReadHalfword(ctx);
    FUN_0200CB00(unk80->unk08, 3, 985, 11, 0, 4);
    *unk = Std_CreateYesNoMenu(unk80->unk08, &UNK_020F34E0, 985, 11, 4);
    ctx->data[0] = wk;
    SetupNativeScript(ctx, FUN_0203AB00);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203AB00(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u32 *unk = FUN_02039438(unk80, 2);
    u16 *ptr = GetVarPointer(unk80, (u16)ctx->data[0]);
    u32 unk2 = FUN_020021AC(*unk, 4);

    if (unk2 == -1)
    {
        return FALSE;
    }

    if (unk2 == 0)
    {
        *ptr = 0;
    }
    else
    {
        *ptr = 1;
    }
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_ShowSaveClock(struct ScriptContext *ctx)
{
    u32 *unk = FUN_02039438(ctx->unk80, 1);
    u32 *unk2 = FUN_02039438(ctx->unk80, 18);
    *unk2 = FUN_0200D858(unk, 994);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HideSaveClock(struct ScriptContext *ctx)
{
    u32 *unk = FUN_02039438(ctx->unk80, 18);
    FUN_0200DBFC(*unk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0040(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u32 *unk = FUN_02039438(unk80, 0);
    u32 *unk2 = FUN_02039438(unk80, 15);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);
    u16 unk7 = ScriptReadHalfword(ctx);
    u16 *ptr = GetVarPointer(unk80, unk7);
    u32 *unk8 = FUN_02039438(ctx->unk80, 1);
    *unk = MOD05_021E1BF8(unk80, unk3, unk4, unk5, unk6, ptr, *unk2, unk8, NULL);
    ctx->data[0] = unk7;
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0041(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u32 *unk = FUN_02039438(unk80, 0);
    u32 *unk2 = FUN_02039438(unk80, 15);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);
    u16 unk7 = ScriptReadHalfword(ctx);
    u16 *ptr = GetVarPointer(unk80, unk7);
    u32 *unk8 = FUN_02039438(ctx->unk80, 1);
    *unk = MOD05_021E1BF8(unk80, unk3, unk4, unk5, unk6, ptr, *unk2, unk8, ctx->msgData);
    ctx->data[0] = unk7;
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0042(struct ScriptContext *ctx)
{
    u32 *unk = FUN_02039438(ctx->unk80, 0);
    u8 unk2 = ScriptReadByte(ctx);
    u8 unk3 = ScriptReadByte(ctx);
    MOD05_021E1C4C(*unk, unk2, unk3);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk029D(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u32 *unk = FUN_02039438(unk80, 0);
    u16 unk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unk3 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    MOD05_021E1C4C(*unk, unk2, unk3);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0043(struct ScriptContext *ctx)
{
    u32 *unk = FUN_02039438(ctx->unk80, 0);
    MOD05_021E1C54(*unk);
    SetupNativeScript(ctx, FUN_0203AD2C);
    return TRUE;
}

THUMB_FUNC BOOL FUN_0203AD2C(struct ScriptContext *ctx)
{
    u16 *varPtr = GetVarPointer(ctx->unk80, (u16)ctx->data[0]);
    if (*varPtr == 0xEEEE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

THUMB_FUNC BOOL ScrCmd_Unk02B9(struct ScriptContext *ctx)
{
    u32 *unk = FUN_02039438(ctx->unk80, 0);
    MOD05_021E1C54(*unk);
    SetupNativeScript(ctx, FUN_0203AD78);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203AD78(struct ScriptContext *ctx)
{
    struct UnkSavStruct80 *unk80 = ctx->unk80;
    u16 *varPtr = GetVarPointer(unk80, (u16)ctx->data[0]);
    u32 *unk = FUN_02039438(unk80, 0);

    if (*varPtr == 0xEEEE)
    {
        if (FUN_02052714(unk80->unk78))
        {
            *varPtr = 8;
            MOD05_021E1ECC(*unk);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return TRUE;
    }
}
