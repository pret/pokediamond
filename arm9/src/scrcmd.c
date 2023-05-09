#include "scrcmd.h"
#include "PAD_pad.h"
#include "bg_window.h"
#include "camera.h"
#include "main.h"
#include "options.h"
#include "player_data.h"
#include "render_window.h"
#include "task.h"
#include "text.h"
#include "text_02054590.h"
#include "unk_0200CA44.h"
#include "unk_0205EC84.h"

extern void *FUN_02039438(struct FieldSystem* fieldSystem, u32 id);
extern void *CreateScriptContext(struct FieldSystem* fieldSystem, u16 id);
extern u8 FUN_02058448(u32 param0);
extern void FlagSet(struct FieldSystem *fieldSystem, u16 flag);
extern void FlagClear(struct FieldSystem *fieldSystem, u16 flag);
extern u8 FlagCheck(struct FieldSystem *fieldSystem, u16 flag);
extern void TrainerFlagSet(struct FieldSystem *fieldSystem, u16 flag);
extern void TrainerFlagClear(struct FieldSystem *fieldSystem, u16 flag);
extern u8 TrainerFlagCheck(struct FieldSystem *fieldSystem, u16 flag);
extern void MOD05_ShowMessageInField(struct ScriptContext *ctx, struct MsgData *msgData, u16 id);
extern void MOD05_021E2BD0(struct ScriptContext *ctx, struct MsgData *msgData, u16 msgId, u32 param4, void *param5);
extern void MOD05_021E2C58(struct ScriptContext *ctx, u16 typ, u16 id, u16 word1, s16 word2, u8 param5);
extern struct ScrStrBufs *MOD06_02244210(struct SaveBlock2 *sav, u16 poke, u16 sex, u8 flag, u8 *unk);
extern void MOD05_021E2CBC(struct ScriptContext *ctx, struct ScrStrBufs *str, u8 param2, u32 param3);
extern void MOD05_021E2BB8(void *param0, struct ScriptContext *ctx);
extern u32 FUN_02058488(u32 param0);
extern BOOL FUN_02030F40(void);
extern void FUN_02055304(struct PlayerAvatar *playerAvatar, u32 param1);
extern void FUN_02039460(struct FieldSystem *arg);
extern u32 FUN_02058510(u32 param0, u32 param1);
extern void MOD05_021E8128(u32 param0, u8 type, u16 map);
extern void MOD05_021E8130(u32 param0, u32 param1);
extern void MOD05_021E8158(struct FieldSystem *fieldSystem);
extern struct Window * MOD05_021E8140(u32 param0);
extern BOOL MOD05_021E8148(u32 param0);
extern void MOD05_021E8144(u32 param0);
extern u32 Std_CreateYesNoMenu(struct BgConfig *param0, u8 **param1, u32 param2, u32 param3, u32 param4);
extern u32 FUN_020021AC(u32 param0, u32 param1);
extern u32 MOD05_021E1BF8(struct FieldSystem *fieldSystem, u8 param1, u8 param2, u8 param3, u8 param4, u16 *param5, u32 param6, u32 *param7, struct MsgData *msgData);
extern void MOD05_021E1C4C(u32 param0, u32 param1, u32 param2);
extern void MOD05_021E1C54(u32 param0);
extern u32 FUN_02052714(u32 param0);
extern void MOD05_021E1ECC(u32 param0);
extern u32 MOD05_021E1F34(struct FieldSystem *fieldSystem, u8 param1, u8 param2, u8 param3, u8 param4, u16 *param5, u32 param6, u32 *param7, struct MsgData *msgData);
extern void MOD05_021E1F58(u32 param0, u8 param1, u8 param2, u8 param3);
extern void MOD05_021E1F60(u32 param0);
extern void MOD05_021E26CC(u32 param0, u8 param1);
extern void MOD05_021E2B80(u32 param0, u8 param1);
extern void MOD05_021E2B9C(u32 param0, u8 param1);
extern u32 FUN_0205AEA4(struct Vecx32 *param0, const void *ptr);
extern u32 FUN_02058B2C(struct Vecx32 *param0);
extern u32 FUN_02058B4C(struct Vecx32 *param0);
extern struct Vecx32 *FUN_020580B4(u32 param0, u32 param1);
extern struct Vecx32 *FUN_02058060(u32 param0, u32 param1);
extern BOOL FUN_0205AEF0(u32 param0);
extern void FUN_0205AEFC(u32 param0);
extern void FUN_02058780(u32 param0);
extern struct Vecx32 *FUN_020553A0(struct PlayerAvatar *playerAvatar); //get player position?
extern u32 FUN_0205AE28(struct Vecx32 *param0);
extern void FUN_02058908(struct Vecx32 *param0);
extern u32 FUN_02058854(struct Vecx32 *param0);
extern struct Vecx32 *FUN_0205E7C4(struct Vecx32 *param0);
extern void FUN_02058914(struct Vecx32 *param0);
extern void FUN_020587B0(u32 param0);
extern u32 FUN_02034B64(struct FieldSystem *fieldSystem);
extern u32 FUN_02034B6C(struct FieldSystem *fieldSystem);
extern u32 FUN_020575D4(u32 param0, u16 eventVar, u32 param2, u32 mapId, u32 param4);
extern void FUN_02057688(struct Vecx32 *param0);
extern struct Vecx32 *FUN_0205753C(u32 param0, u16 x, u16 y, u16 z, u32 param4, u32 param5, u32 mapId);
extern u32 FUN_02059D1C(struct Vecx32 *target);
extern struct Vecx32 *FUN_0205889C(struct Vecx32 *target, u32 param1);
extern struct Vecx32 *FUN_020588B8(struct Vecx32 *target, u32 param1);
extern struct Vecx32 *FUN_02058B7C(struct Vecx32 *target);
extern void MOD05_021EF5E0(struct Vecx32 *target, u32 param1);
extern void FUN_02057654(struct Vecx32 *target);
extern u32 PlayerAvatar_GetFacingDirection(struct PlayerAvatar *playerAvatar);
extern u32 FUN_02059E74(u32 direction);
extern void MOD05_021F1EC0(struct Vecx32 *param0, u32 param1);

extern u8 UNK_021C5A0C[4];

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
static BOOL FUN_0203AD2C(struct ScriptContext *ctx);
static BOOL FUN_0203AD78(struct ScriptContext *ctx);
static struct Vecx32 *FUN_0203B120(struct FieldSystem *fieldSystem, u16 param1);
static BOOL FUN_0203B158(struct ScriptContext *ctx);
static void FUN_0203B174(struct FieldSystem *fieldSystem, u32 param1, void *param2);
static void FUN_0203B1A8(u32 param0, UnkStruct_0203B174 *param1);
static BOOL FUN_0203B218(struct ScriptContext *ctx);

extern u8 sScriptConditionTable[6][3];

THUMB_FUNC BOOL ScrCmd_Nop(struct ScriptContext *ctx) //0000
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Dummy(struct ScriptContext *ctx) //0001
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_End(struct ScriptContext *ctx) //0002
{
    StopScript(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Wait(struct ScriptContext *ctx) //0003
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 num = ScriptReadHalfword(ctx);
    u16 wk = ScriptReadHalfword(ctx);
    u16* VarPointer = GetVarPointer(fieldSystem, wk);
    *VarPointer = num;
    ctx->data[0] = wk;
    SetupNativeScript(ctx, RunPauseTimer);
    return TRUE;
}

THUMB_FUNC static BOOL RunPauseTimer(struct ScriptContext *ctx)
{
    u16* VarPointer = GetVarPointer(ctx->fieldSystem, (u16)ctx->data[0]);
    *VarPointer = (u16)(*VarPointer - 1);
    return !(*VarPointer);
}

THUMB_FUNC BOOL ScrCmd_DebugWatch(struct ScriptContext *ctx) //01F9
{
    u16 wk = ScriptReadHalfword(ctx);
    VarGet(ctx->fieldSystem, wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadByte(struct ScriptContext *ctx) //0004
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadByte(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadWord(struct ScriptContext *ctx) //0005
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadWord(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LoadByteFromAddr(struct ScriptContext *ctx) //0006
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = *(u8 *)ScriptReadWord(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WriteByteToAddr(struct ScriptContext *ctx) //0007
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = ScriptReadByte(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetPtrByte(struct ScriptContext *ctx) //0008
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = (u8)ctx->data[ScriptReadByte(ctx)];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyLocal(struct ScriptContext *ctx) //0009
{
    u8 index_store = ScriptReadByte(ctx);
    u8 index_load = ScriptReadByte(ctx);
    ctx->data[index_store] = ctx->data[index_load];
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyByte(struct ScriptContext *ctx) //000A
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

THUMB_FUNC BOOL ScrCmd_CompareLocalToLocal(struct ScriptContext *ctx) //000B
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareLocalToValue(struct ScriptContext *ctx) //000C
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareLocalToAddr(struct ScriptContext *ctx) //000D
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToLocal(struct ScriptContext *ctx) //000E
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToValue(struct ScriptContext *ctx) //000F
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareAddrToAddr(struct ScriptContext *ctx) //0010
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareVarToValue(struct ScriptContext *ctx) //0011
{
    u16 a = *GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 b = ScriptReadHalfword(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CompareVarToVar(struct ScriptContext *ctx) //0012
{
    u16 *a = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 *b = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    ctx->comparisonResult = (u8)Compare(*a, *b);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_RunScript(struct ScriptContext *ctx) //0013
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *unk1 = (u8 *)FUN_02039438(fieldSystem, 0x7);
    u32 **unk2 = (u32 **)FUN_02039438(fieldSystem, 0xe);
    u16 id = ScriptReadHalfword(ctx);

    *unk2 = CreateScriptContext(fieldSystem, id);
    *unk1 = (u8)(*unk1 + 1);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_RunScriptWait(struct ScriptContext *ctx) //0014
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *unk1 = (u8 *)FUN_02039438(fieldSystem, 0x5);
    u8 *unk2 = (u8 *)FUN_02039438(fieldSystem, 0x7);
    u32 **unk3 = (u32 **)FUN_02039438(fieldSystem, 0xe);

    u16 id = ScriptReadHalfword(ctx);
    *unk1 = 1;
    *unk3 = CreateScriptContext(fieldSystem, id);
    *unk2 = (u8)(*unk2 + 1);

    SetupNativeScript(ctx, FUN_02039CC8);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_02039CC8(struct ScriptContext *ctx)
{
    u8* unk = FUN_02039438(ctx->fieldSystem, 0x5);

    if (*unk == 0)
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_RestartCurrentScript(struct ScriptContext *ctx) //0015
{
    u8* unk = (u8 *)FUN_02039438(ctx->fieldSystem, 0x5);

    *unk = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GoTo(struct ScriptContext *ctx) //0016
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptJump(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ObjectGoTo(struct ScriptContext *ctx) //0017
{
    u32* unk = FUN_02039438(ctx->fieldSystem, 0xa);
    u8 id = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);
    if (FUN_02058448(*unk) == id)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_BgGoTo(struct ScriptContext *ctx) //0018
{
    u32 bgId = FUN_02046534(ctx->taskManager);
    u8 id = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (bgId == id)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_DirectionGoTo(struct ScriptContext *ctx) //0019
{
    u32 *playerDirection = FUN_02039438(ctx->fieldSystem, 0x9);
    u8 dir = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (*playerDirection == dir)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Call(struct ScriptContext *ctx) //001A
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptCall(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Return(struct ScriptContext *ctx) //001B
{
    ScriptReturn(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GoToIf(struct ScriptContext *ctx) //001C
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CallIf(struct ScriptContext *ctx) //001D
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptCall(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetFlag(struct ScriptContext *ctx) //001E
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptReadHalfword(ctx);
    FlagSet(fieldSystem, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ClearFlag(struct ScriptContext *ctx) //001F
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptReadHalfword(ctx);
    FlagClear(fieldSystem, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckFlag(struct ScriptContext *ctx) //0020
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptReadHalfword(ctx);
    ctx->comparisonResult = FlagCheck(fieldSystem, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckFlagVar(struct ScriptContext *ctx) //0021
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *wk1 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 *wk2 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    *wk2 = FlagCheck(fieldSystem, *wk1);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetFlagVar(struct ScriptContext *ctx) //0022
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *wk = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    FlagSet(fieldSystem, *wk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetTrainerFlag(struct ScriptContext *ctx) //0023
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    TrainerFlagSet(fieldSystem, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ClearTrainerFlag(struct ScriptContext *ctx) //0024
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    TrainerFlagClear(fieldSystem, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckTrainerFlag(struct ScriptContext *ctx) //0025
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    ctx->comparisonResult = TrainerFlagCheck(fieldSystem, flag);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_AddVar(struct ScriptContext *ctx) //0026
{
    u16 *wk1 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    *wk1 = (u16)(*wk1 + wk2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SubVar(struct ScriptContext *ctx) //0027
{
    u16 *wk1 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    *wk1 = (u16)(*wk1 - wk2);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetVar(struct ScriptContext *ctx) //0028
{
    u16 *wk = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    *wk = ScriptReadHalfword(ctx);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CopyVar(struct ScriptContext *ctx) //0029
{
    u16 *wk1 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 *wk2 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    *wk1 = *wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_SetOrCopyVar(struct ScriptContext *ctx) //002A - todo: better name
{
    u16 *wk1 = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 wk2 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    *wk1 = wk2;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Message(struct ScriptContext *ctx) //002B - todo: MessageAll?
{
    u8 id = ScriptReadByte(ctx);
    MOD05_ShowMessageInField(ctx, ctx->msgData, id);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_MessageFrom(struct ScriptContext *ctx) //01FA - todo: MessageAllFromNarc?
{
    u16 arc = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 msg = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct MsgData *msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, arc, 32);
    MOD05_ShowMessageInField(ctx, msgData, msg);
    DestroyMsgData(msgData);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_MessageFrom2(struct ScriptContext *ctx) //01FB - todo: MessageFromNarc?
{
    u16 arc = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 msg = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct MsgData *msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, arc, 32);
    MOD05_021E2BD0(ctx, msgData, msg, 1, NULL);
    DestroyMsgData(msgData);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FC(struct ScriptContext *ctx) //01FC
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    s16 word2 = (s16)ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 0xff);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FD(struct ScriptContext *ctx) //01FD
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    s16 word2 = (s16)ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 1);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk01FE(struct ScriptContext *ctx) //01FE
{
    u8 id = ScriptReadByte(ctx);

    if (ctx->fieldSystem->unkA8 == NULL)
    {
        return FALSE;
    }

    u16 *unkArr = ctx->fieldSystem->unkA8->unk90[id].unk0;
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

THUMB_FUNC BOOL ScrCmd_Unk01FF(struct ScriptContext *ctx) //01FF
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 msg = ScriptReadByte(ctx);
    u16 poke = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 sex = ScriptReadHalfword(ctx);
    u8 flag = ScriptReadByte(ctx);
    u8 unk = 0;

    struct ScrStrBufs *str = MOD06_02244210(fieldSystem->saveBlock2, poke, sex, flag, &unk);
    MOD05_021E2CBC(ctx, str, (u8)(msg + unk), 1);
    ScrStrBufs_delete(str);

    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_MessageUnown(struct ScriptContext *ctx) //026D
{
    struct UnkStruct_0203A288 myLocalStruct;
    u16 msg = ScriptReadHalfword(ctx);

    MOD05_021E2BB8(&myLocalStruct, ctx);
    myLocalStruct.unk2 = 3;

    MOD05_021E2BD0(ctx, ctx->msgData, msg, 0, &myLocalStruct);
    SetupNativeScript(ctx, FUN_0203A2F0);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk002C(struct ScriptContext *ctx) //002C - todo: Message?
{
    u8 msg = ScriptReadByte(ctx);
    MOD05_021E2BD0(ctx, ctx->msgData, msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC /*static*/ BOOL FUN_0203A2F0(struct ScriptContext *ctx)
{
    u8 *unk = (u8 *)FUN_02039438(ctx->fieldSystem, 3);
    return FUN_020546C8(*unk);
}

THUMB_FUNC BOOL ScrCmd_Unk002D(struct ScriptContext *ctx) //002D - todo: MessageFromVar? MessageFlex?
{
    u16 msg = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk02C0(struct ScriptContext *ctx) //02C0
{
    struct UnkStruct_0203A288 myLocalStruct;
    u16 msg = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));

    MOD05_021E2BB8(&myLocalStruct, ctx);
    myLocalStruct.unk1 = 1;

    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 1, &myLocalStruct);
    SetupNativeScript(ctx, FUN_0203A2F0);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk002E(struct ScriptContext *ctx) //002E - todo: MessageWait? MessageNoSkip?
{
    u16 msg = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 0, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk020C(struct ScriptContext *ctx) //020C
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0xa);
    u8 msg = (u8)FUN_02058488(*unk);
    MOD05_021E2BD0(ctx, ctx->msgData, msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk002F(struct ScriptContext *ctx) //002F
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

THUMB_FUNC BOOL ScrCmd_WaitButtonAB(struct ScriptContext *ctx) //0030
{
    SetupNativeScript(ctx, FUN_0203A46C);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A46C(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    if (gMain.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_WaitButtonABTime(struct ScriptContext *ctx) //0190
{
    ctx->data[0] = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    SetupNativeScript(ctx, FUN_0203A4AC);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A4AC(struct ScriptContext *ctx)
{
    if (gMain.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
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

THUMB_FUNC BOOL ScrCmd_WaitButton(struct ScriptContext *ctx) //0031
{
    SetupNativeScript(ctx, FUN_0203A4E0);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A4E0(struct ScriptContext *ctx)
{
    if (gMain.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
    {
        return TRUE;
    }
    else if (gMain.newKeys & PAD_KEY_UP)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 0);
    }
    else if (gMain.newKeys & PAD_KEY_DOWN)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 1);
    }
    else if (gMain.newKeys & PAD_KEY_LEFT)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 2);
    }
    else if (gMain.newKeys & PAD_KEY_RIGHT)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 3);
    }
    else if (gMain.newKeys & PAD_BUTTON_X)
    {
        FUN_02039460(ctx->fieldSystem);
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_WaitButtonABPad(struct ScriptContext *ctx) //0032
{
    SetupNativeScript(ctx, FUN_0203A570);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A570(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    if (gMain.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
    {
        return TRUE;
    }
    else if (gMain.newKeys & (PAD_KEY_RIGHT | PAD_KEY_LEFT | PAD_KEY_UP | PAD_KEY_DOWN))
    {
        return TRUE;
    }
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0033(struct ScriptContext *ctx) //0033 - todo: OpenMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *unk = (u8 *)FUN_02039438(fieldSystem, 6);
    FUN_020545B8(fieldSystem->bgConfig, (struct Window *)FUN_02039438(fieldSystem, 1), 3);
    FUN_02054608((struct Window *)FUN_02039438(fieldSystem, 1), Sav2_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveBlock2));
    *unk = 1;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CloseMessageBox(struct ScriptContext* ctx) //0034
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct Window *unk = FUN_02039438(fieldSystem, 0x1);
    u8 *unk2 = FUN_02039438(fieldSystem, 0x6);
    ClearFrameAndWindow2(unk, 0);
    RemoveWindow(unk);
    *unk2 = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0035(struct ScriptContext* ctx) //0035 - todo: FreezeMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct Window *unk = FUN_02039438(fieldSystem, 0x1);
    u8 *unk2 = FUN_02039438(fieldSystem, 0x6);
    RemoveWindow(unk);
    *unk2 = 0;
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ScrollBg(struct ScriptContext* ctx) //003C
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *xval = FUN_02039438(fieldSystem, 0x31);
    u16 *xcnt = FUN_02039438(fieldSystem, 0x2d);
    u16 *xdir = FUN_02039438(fieldSystem, 0x32);
    u16 *yval = FUN_02039438(fieldSystem, 0x33);
    u16 *ycnt = FUN_02039438(fieldSystem, 0x2e);
    u16 *ydir = FUN_02039438(fieldSystem, 0x34);

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
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *xval = FUN_02039438(fieldSystem, 0x31);
    u16 *xdir = FUN_02039438(fieldSystem, 0x32);
    u16 *yval = FUN_02039438(fieldSystem, 0x33);
    u16 *ydir = FUN_02039438(fieldSystem, 0x34);
    u16 *xcnt = FUN_02039438(fieldSystem, 0x2d);
    u16 *ycnt = FUN_02039438(fieldSystem, 0x2e);

    if (*xcnt == 0 && *ycnt == 0)
    {
        return TRUE;
    }

    if (*xval != 0)
    {
        if (*xdir == 0)
        {
            BgSetPosTextAndCommit(fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, BG_POS_OP_ADD_X, *xval);
        }
        else
        {
            BgSetPosTextAndCommit(fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, BG_POS_OP_SUB_X, *xval);
        }
    }

    if (*yval != 0)
    {
        if (*ydir == 0)
        {
            BgSetPosTextAndCommit(fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, BG_POS_OP_ADD_Y, *yval);
        }
        else
        {
            BgSetPosTextAndCommit(fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, BG_POS_OP_SUB_Y, *yval);
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

THUMB_FUNC BOOL ScrCmd_CreateMessageBox(struct ScriptContext* ctx) //003C
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct String **unk1 = FUN_02039438(fieldSystem, 0x11);
    struct String **unk2 = FUN_02039438(fieldSystem, 0x10);
    struct ScrStrBufs **unk3 = FUN_02039438(fieldSystem, 0x0f);
    u8 typ, msg;
    u16 wk, map;

    msg = ScriptReadByte(ctx);
    typ = ScriptReadByte(ctx);
    map = ScriptReadHalfword(ctx);
    wk = ScriptReadHalfword(ctx);

    if (map == 0)
    {
        u32 *unk4 = FUN_02039438(fieldSystem, 10);
        map = (u16)FUN_02058510(*unk4, 0);
    }

    MOD05_021E8128(fieldSystem->unk60, typ, map);
    MOD05_021E8130(fieldSystem->unk60, 1);
    MOD05_021E8158(fieldSystem);
    ReadMsgDataIntoString(ctx->msgData, msg, *unk1);
    StringExpandPlaceholders(*unk3, *unk2, *unk1);
    AddTextPrinterParameterized(MOD05_021E8140(fieldSystem->unk60), 1, *unk2, 0, 0, 0, NULL);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0037(struct ScriptContext *ctx) //0037 - todo: SetTextBoard? ColourMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 typ = ScriptReadByte(ctx);
    u16 map = ScriptReadHalfword(ctx);

    MOD05_021E8128(fieldSystem->unk60, typ, map);
    MOD05_021E8130(fieldSystem->unk60, 1);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0038(struct ScriptContext *ctx) //0038 - todo: ShowMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 req = ScriptReadByte(ctx);
    MOD05_021E8130(fieldSystem->unk60, req);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0039(struct ScriptContext *ctx) //0039 - todo: MessageBoxWait? WaitMessageBox?
{
    if (MOD05_021E8148(ctx->fieldSystem->unk60) == TRUE)
    {
        return FALSE;
    }

    SetupNativeScript(ctx, FUN_0203A8A0);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A8A0(struct ScriptContext *ctx)
{
    if (MOD05_021E8148(ctx->fieldSystem->unk60) == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk003A(struct ScriptContext *ctx) //003A - todo: CreateMessageBoxText?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *unk1 = FUN_02039438(fieldSystem, 3);
    struct String **unk2 = FUN_02039438(fieldSystem, 17);
    struct String **unk3 = FUN_02039438(fieldSystem, 16);
    struct ScrStrBufs **unk4 = FUN_02039438(fieldSystem, 15);

    u8 msg = ScriptReadByte(ctx);
    u16 wk = ScriptReadHalfword(ctx);

    ReadMsgDataIntoString(ctx->msgData, msg, *unk2);
    StringExpandPlaceholders(*unk4, *unk3, *unk2);

    *unk1 = (u8)FUN_02054658(MOD05_021E8140(fieldSystem->unk60), *unk3, Sav2_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveBlock2), 1);
    ctx->data[0] = wk;
    SetupNativeScript(ctx, FUN_0203A94C);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203A94C(struct ScriptContext *ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *unk1 = FUN_02039438(fieldSystem, 3);
    u16 *varPtr = GetVarPointer(fieldSystem, (u16)ctx->data[0]);
    MOD05_021E8144(fieldSystem->unk60);

    u32 tmp = 0xFFFF;
    if (FUN_020546C8(*unk1) == TRUE)
    {
        *varPtr = 2;
        return TRUE;
    }

    if (gMain.newKeys & PAD_KEY_UP)
    {
        tmp = 0;
    }
    else if (gMain.newKeys & PAD_KEY_DOWN)
    {
        tmp = 1;
    }
    else if (gMain.newKeys & PAD_KEY_LEFT)
    {
        tmp = 2;
    }
    else if (gMain.newKeys & PAD_KEY_RIGHT)
    {
        tmp = 3;
    }

    if (tmp != 0xFFFF)
    {
        FUN_0201BD7C(*unk1);
        FUN_02055304(ctx->fieldSystem->playerAvatar, tmp);
        *varPtr = 0;
        return TRUE;
    }
    else
    {
        if (gMain.newKeys & PAD_BUTTON_X)
        {
            FUN_0201BD7C(*unk1);
            *varPtr = 1;
            return TRUE;
        }
        return FALSE;
    }
}

THUMB_FUNC BOOL ScrCmd_Unk003B(struct ScriptContext *ctx) //003B - todo: CloseMessageBox?
{
    ctx->data[0] = ScriptReadHalfword(ctx);

    SetupNativeScript(ctx, FUN_0203AA0C);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203AA0C(struct ScriptContext *ctx)
{
    u16 *unk = GetVarPointer(ctx->fieldSystem, (u16)ctx->data[0]);

    u32 tmp = 0xFFFF;
    if (gMain.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
    {
        *unk = 0;
        return TRUE;
    }
    else if (gMain.newKeys & PAD_KEY_UP)
    {
        tmp = 0;
    }
    else if (gMain.newKeys & PAD_KEY_DOWN)
    {
        tmp = 1;
    }
    else if (gMain.newKeys & PAD_KEY_LEFT)
    {
        tmp = 2;
    }
    else if (gMain.newKeys & PAD_KEY_RIGHT)
    {
        tmp = 3;
    }

    if (tmp != 0xFFFF)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, tmp);
        *unk = 0;
        return TRUE;
    }
    else
    {
        if (gMain.newKeys & PAD_BUTTON_X)
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

THUMB_FUNC BOOL ScrCmd_Menu(struct ScriptContext *ctx) //003C
{
    FUN_02039460(ctx->fieldSystem);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_YesNoMenu(struct ScriptContext *ctx) //003E
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FUN_02039438(fieldSystem, 2);
    u16 wk = ScriptReadHalfword(ctx);
    FUN_0200CB00(fieldSystem->bgConfig, 3, 985, 11, 0, 4);
    *unk = Std_CreateYesNoMenu(fieldSystem->bgConfig, &UNK_020F34E0, 985, 11, 4);
    ctx->data[0] = wk;
    SetupNativeScript(ctx, FUN_0203AB00);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203AB00(struct ScriptContext *ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FUN_02039438(fieldSystem, 2);
    u16 *ptr = GetVarPointer(fieldSystem, (u16)ctx->data[0]);
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

THUMB_FUNC BOOL ScrCmd_ShowSaveClock(struct ScriptContext *ctx) //018D
{
    struct Window *unk = (struct Window *)FUN_02039438(ctx->fieldSystem, 1);
    struct UnkStruct_0200CABC_1 **unk2 = (struct UnkStruct_0200CABC_1 **)FUN_02039438(ctx->fieldSystem, 18);
    *unk2 = FUN_0200D858(unk, 994);
    return FALSE;
}


THUMB_FUNC BOOL ScrCmd_HideSaveClock(struct ScriptContext *ctx) //018E
{
    struct UnkStruct_0200CABC_1 **unk = (struct UnkStruct_0200CABC_1 **)FUN_02039438(ctx->fieldSystem, 18);
    FUN_0200DBFC(*unk);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0040(struct ScriptContext *ctx) //0040
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FUN_02039438(fieldSystem, 0);
    u32 *unk2 = FUN_02039438(fieldSystem, 15);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);
    u16 unk7 = ScriptReadHalfword(ctx);
    u16 *ptr = GetVarPointer(fieldSystem, unk7);
    u32 *unk8 = FUN_02039438(ctx->fieldSystem, 1);
    *unk = MOD05_021E1BF8(fieldSystem, unk3, unk4, unk5, unk6, ptr, *unk2, unk8, NULL);
    ctx->data[0] = unk7;
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0041(struct ScriptContext *ctx) //0041
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FUN_02039438(fieldSystem, 0);
    u32 *unk2 = FUN_02039438(fieldSystem, 15);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);
    u16 unk7 = ScriptReadHalfword(ctx);
    u16 *ptr = GetVarPointer(fieldSystem, unk7);
    u32 *unk8 = FUN_02039438(ctx->fieldSystem, 1);
    *unk = MOD05_021E1BF8(fieldSystem, unk3, unk4, unk5, unk6, ptr, *unk2, unk8, ctx->msgData);
    ctx->data[0] = unk7;
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0042(struct ScriptContext *ctx) //0042
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    u8 unk2 = ScriptReadByte(ctx);
    u8 unk3 = ScriptReadByte(ctx);
    MOD05_021E1C4C(*unk, unk2, unk3);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk029D(struct ScriptContext *ctx) //029D
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FUN_02039438(fieldSystem, 0);
    u16 unk2 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 unk3 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    MOD05_021E1C4C(*unk, unk2, unk3);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0043(struct ScriptContext *ctx) //0043
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    MOD05_021E1C54(*unk);
    SetupNativeScript(ctx, FUN_0203AD2C);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203AD2C(struct ScriptContext *ctx)
{
    u16 *varPtr = GetVarPointer(ctx->fieldSystem, (u16)ctx->data[0]);
    if (*varPtr == 0xEEEE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

THUMB_FUNC BOOL ScrCmd_Unk02B9(struct ScriptContext *ctx) //02B9
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    MOD05_021E1C54(*unk);
    SetupNativeScript(ctx, FUN_0203AD78);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203AD78(struct ScriptContext *ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *varPtr = GetVarPointer(fieldSystem, (u16)ctx->data[0]);
    u32 *unk = FUN_02039438(fieldSystem, 0);

    if (*varPtr == 0xEEEE)
    {
        if (FUN_02052714(fieldSystem->unk78))
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

THUMB_FUNC BOOL ScrCmd_Unk0044(struct ScriptContext *ctx) //0044
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FUN_02039438(fieldSystem, 0);
    u32 *unk2 = FUN_02039438(fieldSystem, 15);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);

    u16 halfWord = ScriptReadHalfword(ctx);
    u16 *varPtr = GetVarPointer(fieldSystem, halfWord);
    u32 *unk7 = FUN_02039438(ctx->fieldSystem, 1);
    *unk = MOD05_021E1F34(fieldSystem, unk3, unk4, unk5, unk6, varPtr, *unk2, unk7, NULL);
    ctx->data[0] = halfWord;
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0045(struct ScriptContext *ctx) //0045
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FUN_02039438(fieldSystem, 0);
    u32 *unk2 = FUN_02039438(fieldSystem, 15);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);

    u16 halfWord = ScriptReadHalfword(ctx);
    u16 *varPtr = GetVarPointer(fieldSystem, halfWord);
    u32 *unk7 = FUN_02039438(ctx->fieldSystem, 1);
    *unk = MOD05_021E1F34(fieldSystem, unk3, unk4, unk5, unk6, varPtr, *unk2, unk7, ctx->msgData);
    ctx->data[0] = halfWord;
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0046(struct ScriptContext *ctx) //0046 - todo: AddListOption?
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    u16 unk2 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 unk3 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 unk4 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    MOD05_021E1F58(*unk, (u8)unk2, (u8)unk3, (u8)unk4);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0047(struct ScriptContext *ctx) //0047 - todo: ShowList?
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    MOD05_021E1F60(*unk);
    SetupNativeScript(ctx, FUN_0203AD2C);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0048(struct ScriptContext *ctx) //0048
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    MOD05_021E26CC(*unk, ScriptReadByte(ctx));
    SetupNativeScript(ctx, FUN_0203AD2C);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk02CF(struct ScriptContext *ctx) //02CF
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    MOD05_021E2B80(*unk, ScriptReadByte(ctx));
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk02D0(struct ScriptContext *ctx) //02D0
{
    u32 *unk = FUN_02039438(ctx->fieldSystem, 0);
    MOD05_021E2B9C(*unk, ScriptReadByte(ctx));
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk005E(struct ScriptContext *ctx) //005E - todo: ApplyMovement?
{
    u16 unk = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u32 unk2 = ScriptReadWord(ctx);

    struct Vecx32 *unk3 = FUN_0203B120(ctx->fieldSystem, unk);
    GF_ASSERT(unk3);

    u32 unk4 = FUN_0205AEA4(unk3, ctx->scriptPtr + unk2);
    u8 *unk5 = FUN_02039438(ctx->fieldSystem, 4);
    (*unk5)++;

    FUN_0203B174(ctx->fieldSystem, unk4, NULL);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk02A1(struct ScriptContext *ctx) //02A1
{
    struct Vecx32 *unk3; //has to be defined first to match
    u16 unk0 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 unk1 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 unk2 = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));

    unk3 = FUN_0203B120(ctx->fieldSystem, unk0);

    GF_ASSERT(unk3);

    u16 *unk4 = AllocFromHeap(4, 0x100);
    u16 unk5 = (u16)FUN_02058B2C(unk3);
    u16 unk6 = (u16)FUN_02058B4C(unk3);

    u32 pos = 0;

    if (unk5 < unk1)
    {
        unk4[0] = 15;
        pos++;
        unk4[1] = (u16)(unk1 - unk5);
    }
    else if (unk5 > unk1)
    {
        unk4[0] = 14;
        pos++;
        unk4[1] = (u16)(unk5 - unk1);
    }

    if (unk6 < unk2)
    {
        unk4[pos * 2] = 12;
        unk4[pos * 2 + 1] = (u16)(unk2 - unk6);
        pos++;
    }
    else if (unk6 > unk2)
    {
        unk4[pos * 2] = 13;
        unk4[pos * 2 + 1] = (u16)(unk6 - unk2);
        pos++;
    }

    unk4[pos * 2] = 254;
    unk4[pos * 2 + 1] = 0;

    u32 unk7 = FUN_0205AEA4(unk3, unk4);
    u8 *unk8 = FUN_02039438(ctx->fieldSystem, 4);

    (*unk8)++;

    FUN_0203B174(ctx->fieldSystem, unk7, unk4);
    return FALSE;
}

THUMB_FUNC static struct Vecx32 *FUN_0203B120(struct FieldSystem *arg, u16 param1)
{
    if (param1 == 242)
    {
        return FUN_020580B4(arg->unk34, 48);
    }
    else if (param1 == 241)
    {
        struct Vecx32 **res = (struct Vecx32 **)FUN_02039438(arg, 11);
        return *res;
    }
    else
    {
        return FUN_02058060(arg->unk34, param1);
    }
}

THUMB_FUNC BOOL ScrCmd_WaitForMovement(struct ScriptContext *ctx) //005F
{
    SetupNativeScript(ctx, FUN_0203B158);
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203B158(struct ScriptContext *ctx)
{
    u8 *unk = FUN_02039438(ctx->fieldSystem, 4);
    return *unk == 0 ? TRUE : FALSE;
}

THUMB_FUNC static void FUN_0203B174(struct FieldSystem *arg, u32 param1, void *param2)
{
    UnkStruct_0203B174 *unkStruct = (UnkStruct_0203B174 *)AllocFromHeap(4, sizeof(UnkStruct_0203B174));
    if (unkStruct == NULL)
    {
        GF_AssertFail();
        return;
    }
    unkStruct->fieldSystem = arg;
    unkStruct->Unk04 = param1;
    unkStruct->Unk08 = param2;
    unkStruct->Unk00 = FUN_0200CA44((void (*)(u32, void *))FUN_0203B1A8, unkStruct, 0);
}

THUMB_FUNC void FUN_0203B1A8(u32 param0, UnkStruct_0203B174 *param1)
{
    //is it tho?
#pragma unused(param0)
    u8 *res = (u8 *)FUN_02039438(param1->fieldSystem, 4);

    if (FUN_0205AEF0(param1->Unk04) != TRUE)
    {
        return;
    }

    FUN_0205AEFC(param1->Unk04);
    FUN_0200CAB4((s32)param1->Unk00);

    if (param1->Unk08 != NULL)
    {
        FreeToHeap(param1->Unk08);
    }

    FreeToHeap(param1);

    u8 resVal = *res;
    if (resVal == 0)
    {
        GF_AssertFail();
        return;
    }
    *res = --resVal;
}

THUMB_FUNC BOOL ScrCmd_LockAllEvents(struct ScriptContext *ctx) //0060
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *res = (u32 *)FUN_02039438(fieldSystem, 10);

    if (*res == 0)
    {
        FUN_02058780(fieldSystem->unk34);
    }
    else
    {
        ScrCmd_LockAllEvents2(ctx);
    }
    return TRUE;
}

THUMB_FUNC static BOOL FUN_0203B218(struct ScriptContext *ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct Vecx32 **unk0 = (struct Vecx32 **)FUN_02039438(fieldSystem, 10);
    struct Vecx32 *unk1 = FUN_020553A0(fieldSystem->playerAvatar);
    if (UNK_021C5A0C[0] & 1)
    {
        if (FUN_0205AE28(unk1) == 1)
        {
            FUN_02058908(unk1);
            UNK_021C5A0C[0] &= 0xfe;
        }
    }
    if (UNK_021C5A0C[0] & 4)
    {
        if (FUN_02058854(*unk0) == 0)
        {
            FUN_02058908(*unk0);
            UNK_021C5A0C[0] &= 0xfb;
        }
    }
    if (UNK_021C5A0C[0] & 2)
    {
        struct Vecx32 *unk2 = FUN_020580B4(fieldSystem->unk34, 48);
        if (FUN_02058854(unk2) == 0)
        {
            FUN_02058908(unk2);
            UNK_021C5A0C[0] &= 0xfd;
        }
    }
    if (UNK_021C5A0C[0] & 8)
    {
        struct Vecx32 *unk3 = FUN_0205E7C4(*unk0);
        if (FUN_02058854(unk3) == 0)
        {
            FUN_02058908(unk3);
            UNK_021C5A0C[0] &= 0xf7;
        }
    }
    if (UNK_021C5A0C[0] == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

THUMB_FUNC BOOL ScrCmd_LockAllEvents2(struct ScriptContext *ctx) //02B4
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct Vecx32 **unk0 = (struct Vecx32 **)FUN_02039438(fieldSystem, 10);
    struct Vecx32 *unk1 = FUN_020553A0(fieldSystem->playerAvatar);
    struct Vecx32 *unk2 = FUN_020580B4(fieldSystem->unk34, 48);
    struct Vecx32 *unk3 = FUN_0205E7C4(*unk0);
    u32 unk34 = fieldSystem->unk34;
    UNK_021C5A0C[0] = 0;

    FUN_02058780(unk34);
    if (FUN_0205AE28(unk1) == 0)
    {
        UNK_021C5A0C[0] |= 1;
        FUN_02058914(unk1);
    }
    if (FUN_02058854(*unk0) != 0)
    {
        UNK_021C5A0C[0] |= 4;
        FUN_02058914(*unk0);
    }
    if (unk2 != NULL)
    {
        struct ScriptState *state = SavArray_Flags_get(fieldSystem->saveBlock2);
        if (FUN_0205ED3C(state) == TRUE)
        {
            if (FUN_02058854(unk2) != 0)
            {
                UNK_021C5A0C[0] |= 2;
                FUN_02058914(unk2);
            }
        }
    }
    if (unk3 != NULL)
    {
        if (FUN_02058854(unk3) != 0)
        {
            UNK_021C5A0C[0] |= 8;
            FUN_02058914(unk3);
        }
    }
    SetupNativeScript(ctx, FUN_0203B218);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_ReleaseAllEvents(struct ScriptContext *ctx) //0061
{
    FUN_020587B0(ctx->fieldSystem->unk34);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_LockEvent(struct ScriptContext *ctx) //0062
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptReadHalfword(ctx);
    FUN_02058908(FUN_02058060(fieldSystem->unk34, eventId));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ReleaseEvent(struct ScriptContext *ctx) //0063
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptReadHalfword(ctx);
    FUN_02058914(FUN_02058060(fieldSystem->unk34, eventId));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_AddOverworldEvent(struct ScriptContext *ctx) //0064
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptReadHalfword(ctx);
    u16 eventVar = VarGet(ctx->fieldSystem, eventId);
    u32 unk0 = FUN_02034B64(fieldSystem);
    u32 unk1 = FUN_02034B6C(fieldSystem);
    u32 res = FUN_020575D4(fieldSystem->unk34, eventVar, unk0, *fieldSystem->mapId, unk1);

    GF_ASSERT(res);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_RemoveOverworldEvent(struct ScriptContext *ctx) //0065
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptReadHalfword(ctx);
    u16 eventVar = VarGet(ctx->fieldSystem, eventId);
    FUN_02057688(FUN_02058060(fieldSystem->unk34, eventVar));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_LockCamera(struct ScriptContext *ctx) //0066
{
    u16 x = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 y = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct Vecx32 **targetPtr = FUN_02039438(ctx->fieldSystem, 0xb);
    *targetPtr = FUN_0205753C(ctx->fieldSystem->unk34, x, y, 0, 0x2000, 0, *ctx->fieldSystem->mapId);
    FUN_02059D1C(*targetPtr);
    FUN_0205889C(*targetPtr, 1);
    FUN_020588B8(*targetPtr, 0);
    struct Vecx32 *modifiedTarget = FUN_02058B7C(*targetPtr);
    MOD05_021EF5E0(modifiedTarget, ctx->fieldSystem->unk24);
    Camera_SetFixedTarget(modifiedTarget, ctx->fieldSystem->cameraWork);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ReleaseCamera(struct ScriptContext *ctx) //0067
{
    struct Vecx32 **targetPtr = FUN_02039438(ctx->fieldSystem, 0xb);
    FUN_02057654(*targetPtr);
    struct Vecx32 *modifiedTarget = FUN_02058B7C(FUN_02058060(ctx->fieldSystem->unk34, 0xff));
    MOD05_021EF5E0(modifiedTarget, ctx->fieldSystem->unk24);
    Camera_SetFixedTarget(modifiedTarget, ctx->fieldSystem->cameraWork);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FacePlayer(struct ScriptContext *ctx) //0068
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 unk0 = FUN_02059E74(PlayerAvatar_GetFacingDirection(fieldSystem->playerAvatar));
    struct Vecx32 **unk1 = FUN_02039438(fieldSystem, 10);

    if (*unk1 == NULL)
    {
        return FALSE;
    }

    MOD05_021F1EC0(*unk1, unk0);
    return FALSE;
}
