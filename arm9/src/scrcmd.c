#include "global.h"
#include "scrcmd.h"
#include "PAD_pad.h"
#include "bag.h"
#include "bg_window.h"
#include "camera.h"
#include "constants/items.h"
#include "fashion_case.h"
#include "main.h"
#include "options.h"
#include "party.h"
#include "player_data.h"
#include "render_window.h"
#include "seal.h"
#include "task.h"
#include "text.h"
#include "text_02054590.h"
#include "unk_0200CA44.h"
#include "unk_0204AF24.h"
#include "unk_0205EC84.h"
#include "unk_0208890C.h"

extern void *FieldSysGetAttrAddr(struct FieldSystem* fieldSystem, enum ScriptEnvField id);
extern ScriptContext *CreateScriptContext(struct FieldSystem* fieldSystem, u16 id);
extern u8 FUN_02058448(LocalMapObject *lastInteracted);
extern void FlagSet(struct FieldSystem *fieldSystem, u16 flag);
extern void FlagClear(struct FieldSystem *fieldSystem, u16 flag);
extern u8 FlagCheck(struct FieldSystem *fieldSystem, u16 flag);
extern void TrainerFlagSet(struct FieldSystem *fieldSystem, u16 flag);
extern void TrainerFlagClear(struct FieldSystem *fieldSystem, u16 flag);
extern u8 TrainerFlagCheck(struct FieldSystem *fieldSystem, u16 flag);
extern void MOD05_ShowMessageInField(struct ScriptContext *ctx, struct MsgData *msgData, u16 id);
extern void MOD05_021E2BD0(struct ScriptContext *ctx, struct MsgData *msgData, u16 msgId, u32 param4, void *param5);
extern void MOD05_021E2C58(struct ScriptContext *ctx, u16 typ, u16 id, u16 word1, s16 word2, u8 param5);
extern MessageFormat *MOD06_02244210(struct SaveBlock2 *sav, u16 poke, u16 sex, u8 flag, u8 *unk);
extern void MOD05_021E2CBC(struct ScriptContext *ctx, MessageFormat *messageFormat, u8 param2, u32 param3);
extern void MOD05_021E2BB8(void *param0, struct ScriptContext *ctx);
extern u32 FUN_02058488(LocalMapObject *lastInteracted);
extern BOOL FUN_02030F40(void);
extern void FUN_02055304(struct PlayerAvatar *playerAvatar, u32 param1);
extern void FUN_02039460(struct FieldSystem *arg);
extern u32 FUN_02058510(LocalMapObject *event, u32 param1);
extern void MOD05_021E8128(u32 param0, u8 type, u16 map);
extern void MOD05_021E8130(u32 param0, u32 param1);
extern void MOD05_021E8158(struct FieldSystem *fieldSystem);
extern struct Window * MOD05_021E8140(u32 param0);
extern BOOL MOD05_021E8148(u32 param0);
extern void MOD05_021E8144(u32 param0);
extern u32 Std_CreateYesNoMenu(struct BgConfig *param0, u8 **param1, u32 param2, u32 param3, u32 param4);
extern u32 FUN_020021AC(u32 param0, u32 param1);
extern u32 MOD05_021E1BF8(struct FieldSystem *fieldSystem, u8 param1, u8 param2, u8 param3, u8 param4, u16 *param5, MessageFormat *messageFormat, struct Window *window, struct MsgData *msgData);
extern void MOD05_021E1C4C(u32 param0, u32 param1, u32 param2);
extern void MOD05_021E1C54(u32 param0);
extern u32 FUN_02052714(u32 param0);
extern void MOD05_021E1ECC(u32 param0);
extern u32 MOD05_021E1F34(struct FieldSystem *fieldSystem, u8 param1, u8 param2, u8 param3, u8 param4, u16 *param5, MessageFormat *messageFormat, struct Window *window, struct MsgData *msgData);
extern void MOD05_021E1F58(u32 param0, u8 param1, u8 param2, u8 param3);
extern void MOD05_021E1F60(u32 param0);
extern void MOD05_021E26CC(u32 param0, u8 param1);
extern void MOD05_021E2B80(u32 param0, u8 param1);
extern void MOD05_021E2B9C(u32 param0, u8 param1);
extern u32 FUN_0205AEA4(LocalMapObject *event, const void *ptr);
extern u32 FUN_02058B2C(LocalMapObject *event);
extern u32 FUN_02058B4C(LocalMapObject *event);
extern LocalMapObject *FUN_020580B4(u32 param0, u32 param1);
extern LocalMapObject *FUN_02058060(u32 param0, u16 eventId);
extern BOOL FUN_0205AEF0(u32 param0);
extern void FUN_0205AEFC(u32 param0);
extern void FUN_02058780(u32 param0);
extern LocalMapObject *FUN_020553A0(struct PlayerAvatar *playerAvatar);
extern u32 FUN_0205AE28(LocalMapObject *event);
extern void FUN_02058908(LocalMapObject *event);
extern u32 FUN_02058854(LocalMapObject *event);
extern LocalMapObject *FUN_0205E7C4(LocalMapObject *event);
extern void FUN_02058914(LocalMapObject *event);
extern void FUN_020587B0(u32 param0);
extern u32 FUN_02034B64(struct FieldSystem *fieldSystem);
extern u32 FUN_02034B6C(struct FieldSystem *fieldSystem);
extern u32 FUN_020575D4(u32 param0, u16 eventVar, u32 param2, u32 mapId, u32 param4);
extern void FUN_02057688(LocalMapObject *event);
extern LocalMapObject *FUN_0205753C(u32 param0, u16 x, u16 y, u16 z, u32 param4, u32 param5, u32 mapId);
extern u32 FUN_02059D1C(LocalMapObject *target);
extern LocalMapObject *FUN_0205889C(LocalMapObject *target, u32 param1);
extern LocalMapObject *FUN_020588B8(LocalMapObject *target, u32 param1);
extern struct Vecx32 *FUN_02058B7C(LocalMapObject *target);
extern void MOD05_021EF5E0(struct Vecx32 *target, u32 param1);
extern void FUN_02057654(LocalMapObject *target);
extern u32 PlayerAvatar_GetFacingDirection(struct PlayerAvatar *playerAvatar);
extern u32 FUN_02059E74(u32 direction);
extern void MOD05_021F1EC0(LocalMapObject *event, u32 param1);
extern u16 GetPlayerXCoord(struct PlayerAvatar *playerAvatar);
extern u16 GetPlayerYCoord(struct PlayerAvatar *playerAvatar);
extern void FUN_02058BB4(LocalMapObject *event, struct Vecx32 *param1);
extern void FUN_02058994(LocalMapObject *event, u8 value);
extern void FUN_02058E90(LocalMapObject *event, u16 movement);
extern u16 FUN_02058480(LocalMapObject *event);
extern void FUN_02058EB0(LocalMapObject *event, u32 param1);
extern u16 FUN_02029E0C(struct SealCase *sealCase);
extern u16 SealCase_CountSealOccurrenceAnywhere(struct SealCase *sealCase, u16 sealId);
extern void FUN_02029D44(struct SealCase *sealCase, u16 sealId, s16 amount);
extern PartyMenuAppData *FUN_020379F8(u32 param0, struct FieldSystem *fieldSystem);
extern PartyMenuAppData *FUN_02037A1C(u32 param0, struct FieldSystem *fieldSystem);
extern PartyMenuAppData *FUN_02037B44(struct TaskManager *taskManager, u32 param1);
extern u16 FUN_02037A40(PartyMenuAppData *partyMenu);
extern u16 FUN_02037A70(PartyMenuAppData *partyMenu);
extern void *FUN_02037BB0(u32 param0, struct FieldSystem *fieldSystem, u16 param2, u16 param3, u16 param4, u16 param5);
extern void *FUN_02037C00(u32 param0, struct FieldSystem *fieldSystem, u16 param2);
extern u16 FUN_02037A78(void *runningAppData);
extern u16 MOD05_021E1858(struct FieldSystem *fieldSystem, LocalMapObject *event, u16 param2);
extern u32 FUN_02029048(u32 param0);
extern void FUN_02028AD4(u32 *param0, u32 param1, u32 param2);
extern void FUN_0204AF3C(struct TaskManager *taskManager);
extern SaveFashionData *Save_FashionData_Get(struct SaveBlock2 *save);
extern BOOL CheckPortraitSlotFull(SaveFashionData *fashionData, u32 portraitSlot);
extern BOOL CheckContestPortraitSlotFull(SaveFashionData *fashionData, u32 portraitSlot);
extern void MOD05_021F02C4(struct FieldSystem *fieldSystem);
extern void FUN_0206F3B8(struct TaskManager *taskManager);
extern u16 FUN_02031190(void);
extern void Script_SetMonSeenFlagBySpecies(struct FieldSystem *fieldSystem, u16 species);
extern void MOD05_021E1374(struct TaskManager *taskManager, MessageFormat *messageFormat, u16 *ptr);
extern void MOD05_021E1994(FieldSystem *fieldSystem, LocalMapObject *lastInteracted);
extern void FUN_0208A338(struct TaskManager *taskManager);
extern void FUN_020380CC(struct TaskManager *taskManager, u16 *param1, struct SaveBlock2 *save, u16 partyPos, u16 param4);
extern void FUN_02038130(FieldSystem *fieldSystem, FashionAppData *fashionData);
extern u32 FUN_02027008(SaveFashionData *fashionData, u32 param1);
extern void FUN_02027478(u32 param0, u16 param1);
extern void ShowGeonetScreen(FieldSystem *fieldSystem);
extern void ShowSealCapsuleEditor(TaskManager *taskManager, struct SaveBlock2 *save);
extern void FUN_0205F7A0(FieldSystem *fieldSystem, TownMapAppData *townMap, u32 param2); //TownMap_Init?
extern void FUN_02037E90(FieldSystem *fieldSystem, TownMapAppData *townMap); //ShowTownMap?
extern u32 FUN_02028048(struct SaveBlock2 *save);
extern u32 FUN_020281B8(u32 param0);
extern void FUN_02037FE4(FieldSystem *fieldSystem, ScrCmdUnkStruct01D9 *param1);
extern void LaunchStoragePCInterface(FieldSystem *fieldSystem, PCBoxAppData *pcBoxAppData);
extern void FUN_020383F8(FieldSystem *fieldSystem);
extern void FUN_02065344(FieldSystem *fieldSystem);
extern void FUN_020383D8(TaskManager *taskManager);
extern void *FUN_0203842C(FieldSystem *fieldSystem);
extern void Task_GameClear(TaskManager *taskManager);

u8 UNK_021C5A0C[4];

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
static LocalMapObject *FUN_0203B120(struct FieldSystem *fieldSystem, u16 eventId);
static BOOL IsAllMovementFinished(struct ScriptContext *ctx);
static void FUN_0203B174(struct FieldSystem *fieldSystem, u32 param1, void *param2);
static void FUN_0203B1A8(u32 param0, UnkStruct_0203B174 *param1);
static BOOL FUN_0203B218(struct ScriptContext *ctx);
/*static*/ BOOL FUN_0203BB90(ScriptContext *ctx);
static BOOL FUN_0203BBBC(ScriptContext *ctx);
/*static*/ BOOL FUN_0203BC04(ScriptContext *ctx);
static BOOL CheckPortraitSlotFullInternal(struct FieldSystem *fieldSystem, BOOL isContest, u32 portraitSlot);
static FashionAppData *FUN_0203BC6C(u32 heapId, struct FieldSystem *fieldSystem, BOOL isContest, u32 portraitSlot);
static BOOL FUN_0203BE9C(ScriptContext *ctx);

extern u8 sScriptConditionTable[6][3];

BOOL ScrCmd_Nop(struct ScriptContext *ctx) //0000
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Dummy(struct ScriptContext *ctx) //0001
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_End(struct ScriptContext *ctx) //0002
{
    StopScript(ctx);
    return FALSE;
}

BOOL ScrCmd_Wait(struct ScriptContext *ctx) //0003
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

static BOOL RunPauseTimer(struct ScriptContext *ctx)
{
    u16* VarPointer = GetVarPointer(ctx->fieldSystem, (u16)ctx->data[0]);
    *VarPointer = (u16)(*VarPointer - 1);
    return !(*VarPointer);
}

BOOL ScrCmd_DebugWatch(struct ScriptContext *ctx) //01F9
{
    ScriptGetVar(ctx);
    return FALSE;
}

BOOL ScrCmd_LoadByte(struct ScriptContext *ctx) //0004
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadByte(ctx);
    return FALSE;
}

BOOL ScrCmd_LoadWord(struct ScriptContext *ctx) //0005
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = ScriptReadWord(ctx);
    return FALSE;
}

BOOL ScrCmd_LoadByteFromAddr(struct ScriptContext *ctx) //0006
{
    u8 index = ScriptReadByte(ctx);
    ctx->data[index] = *(u8 *)ScriptReadWord(ctx);
    return FALSE;
}

BOOL ScrCmd_WriteByteToAddr(struct ScriptContext *ctx) //0007
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = ScriptReadByte(ctx);
    return FALSE;
}

BOOL ScrCmd_SetPtrByte(struct ScriptContext *ctx) //0008
{
    u8* ptr = (u8*)ScriptReadWord(ctx);
    *ptr = (u8)ctx->data[ScriptReadByte(ctx)];
    return FALSE;
}

BOOL ScrCmd_CopyLocal(struct ScriptContext *ctx) //0009
{
    u8 index_store = ScriptReadByte(ctx);
    u8 index_load = ScriptReadByte(ctx);
    ctx->data[index_store] = ctx->data[index_load];
    return FALSE;
}

BOOL ScrCmd_CopyByte(struct ScriptContext *ctx) //000A
{
    u8 *target = (u8 *)ScriptReadWord(ctx);
    u8 *source = (u8 *)ScriptReadWord(ctx);
    *target = *source;
    return FALSE;
}

static u32 Compare(u16 a, u16 b)
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

BOOL ScrCmd_CompareLocalToLocal(struct ScriptContext *ctx) //000B
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

BOOL ScrCmd_CompareLocalToValue(struct ScriptContext *ctx) //000C
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

BOOL ScrCmd_CompareLocalToAddr(struct ScriptContext *ctx) //000D
{
    u8 a = (u8)ctx->data[ScriptReadByte(ctx)];
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

BOOL ScrCmd_CompareAddrToLocal(struct ScriptContext *ctx) //000E
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ctx->data[ScriptReadByte(ctx)];
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

BOOL ScrCmd_CompareAddrToValue(struct ScriptContext *ctx) //000F
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = (u8)ScriptReadByte(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

BOOL ScrCmd_CompareAddrToAddr(struct ScriptContext *ctx) //0010
{
    u8 a = *(u8*)ScriptReadWord(ctx);
    u8 b = *(u8*)ScriptReadWord(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

BOOL ScrCmd_CompareVarToValue(struct ScriptContext *ctx) //0011
{
    u16 a = *ScriptGetVarPointer(ctx);
    u16 b = ScriptReadHalfword(ctx);
    ctx->comparisonResult = (u8)Compare(a, b);
    return FALSE;
}

BOOL ScrCmd_CompareVarToVar(struct ScriptContext *ctx) //0012
{
    u16 *a = ScriptGetVarPointer(ctx);
    u16 *b = ScriptGetVarPointer(ctx);
    ctx->comparisonResult = (u8)Compare(*a, *b);
    return FALSE;
}

BOOL ScrCmd_RunScript(struct ScriptContext *ctx) //0013
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *activeScriptContextsNumber = (u8 *)FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_ACTIVE_SCRIPTCONTEXT_COUNT);
    ScriptContext **scriptContext1 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SCRIPT_CONTEXT_1);
    u16 id = ScriptReadHalfword(ctx);

    *scriptContext1 = CreateScriptContext(fieldSystem, id);
    (*activeScriptContextsNumber)++;
    return TRUE;
}

BOOL ScrCmd_RunScriptWait(struct ScriptContext *ctx) //0014
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *unk1 = (u8 *)FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_UNKNOWN_05);
    u8 *activeScriptContextsNumber = (u8 *)FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_ACTIVE_SCRIPTCONTEXT_COUNT);
    ScriptContext **scriptContext1 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SCRIPT_CONTEXT_1);

    u16 id = ScriptReadHalfword(ctx);
    *unk1 = 1;
    *scriptContext1 = CreateScriptContext(fieldSystem, id);
    (*activeScriptContextsNumber)++;

    SetupNativeScript(ctx, FUN_02039CC8);
    return TRUE;
}

static BOOL FUN_02039CC8(struct ScriptContext *ctx)
{
    u8* unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_UNKNOWN_05);

    if (*unk == 0)
    {
        return TRUE;
    }
    return FALSE;
}

BOOL ScrCmd_RestartCurrentScript(struct ScriptContext *ctx) //0015
{
    u8* unk = (u8 *)FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_UNKNOWN_05);

    *unk = 0;
    return FALSE;
}

BOOL ScrCmd_GoTo(struct ScriptContext *ctx) //0016
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptJump(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

BOOL ScrCmd_ObjectGoTo(struct ScriptContext *ctx) //0017
{
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u8 id = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);
    if (FUN_02058448(*lastInteracted) == id)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

BOOL ScrCmd_BgGoTo(struct ScriptContext *ctx) //0018
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

BOOL ScrCmd_DirectionGoTo(struct ScriptContext *ctx) //0019
{
    u32 *playerDirection = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_FACING_DIRECTION);
    u8 dir = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (*playerDirection == dir)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

BOOL ScrCmd_Call(struct ScriptContext *ctx) //001A
{
    s32 offset = (s32)ScriptReadWord(ctx);
    ScriptCall(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

BOOL ScrCmd_Return(struct ScriptContext *ctx) //001B
{
    ScriptReturn(ctx);
    return FALSE;
}

BOOL ScrCmd_GoToIf(struct ScriptContext *ctx) //001C
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptJump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

BOOL ScrCmd_CallIf(struct ScriptContext *ctx) //001D
{
    u8 compareType = ScriptReadByte(ctx);
    s32 offset = (s32)ScriptReadWord(ctx);

    if (sScriptConditionTable[compareType][ctx->comparisonResult] == TRUE)
    {
        ScriptCall(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

BOOL ScrCmd_SetFlag(struct ScriptContext *ctx) //001E
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptReadHalfword(ctx);
    FlagSet(fieldSystem, flag);
    return FALSE;
}

BOOL ScrCmd_ClearFlag(struct ScriptContext *ctx) //001F
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptReadHalfword(ctx);
    FlagClear(fieldSystem, flag);
    return FALSE;
}

BOOL ScrCmd_CheckFlag(struct ScriptContext *ctx) //0020
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptReadHalfword(ctx);
    ctx->comparisonResult = FlagCheck(fieldSystem, flag);
    return FALSE;
}

BOOL ScrCmd_CheckFlagVar(struct ScriptContext *ctx) //0021
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *wk1 = ScriptGetVarPointer(ctx);
    u16 *wk2 = ScriptGetVarPointer(ctx);
    *wk2 = FlagCheck(fieldSystem, *wk1);
    return FALSE;
}

BOOL ScrCmd_SetFlagVar(struct ScriptContext *ctx) //0022
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *wk = ScriptGetVarPointer(ctx);
    FlagSet(fieldSystem, *wk);
    return FALSE;
}

BOOL ScrCmd_SetTrainerFlag(struct ScriptContext *ctx) //0023
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptGetVar(ctx);
    TrainerFlagSet(fieldSystem, flag);
    return FALSE;
}

BOOL ScrCmd_ClearTrainerFlag(struct ScriptContext *ctx) //0024
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptGetVar(ctx);
    TrainerFlagClear(fieldSystem, flag);
    return FALSE;
}

BOOL ScrCmd_CheckTrainerFlag(struct ScriptContext *ctx) //0025
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 flag = ScriptGetVar(ctx);
    ctx->comparisonResult = TrainerFlagCheck(fieldSystem, flag);
    return FALSE;
}

BOOL ScrCmd_AddVar(struct ScriptContext *ctx) //0026
{
    u16 *wk1 = ScriptGetVarPointer(ctx);
    u16 wk2 = ScriptGetVar(ctx);
    *wk1 = (u16)(*wk1 + wk2);
    return FALSE;
}

BOOL ScrCmd_SubVar(struct ScriptContext *ctx) //0027
{
    u16 *wk1 = ScriptGetVarPointer(ctx);
    u16 wk2 = ScriptGetVar(ctx);
    *wk1 = (u16)(*wk1 - wk2);
    return FALSE;
}

BOOL ScrCmd_SetVar(struct ScriptContext *ctx) //0028
{
    u16 *wk = ScriptGetVarPointer(ctx);
    *wk = ScriptReadHalfword(ctx);
    return FALSE;
}

BOOL ScrCmd_CopyVar(struct ScriptContext *ctx) //0029
{
    u16 *wk1 = ScriptGetVarPointer(ctx);
    u16 *wk2 = ScriptGetVarPointer(ctx);
    *wk1 = *wk2;
    return FALSE;
}

BOOL ScrCmd_SetOrCopyVar(struct ScriptContext *ctx) //002A - todo: better name
{
    u16 *wk1 = ScriptGetVarPointer(ctx);
    u16 wk2 = ScriptGetVar(ctx);
    *wk1 = wk2;
    return FALSE;
}

BOOL ScrCmd_Message(struct ScriptContext *ctx) //002B - todo: MessageAll?
{
    u8 id = ScriptReadByte(ctx);
    MOD05_ShowMessageInField(ctx, ctx->msgData, id);
    return FALSE;
}

BOOL ScrCmd_MessageFrom(struct ScriptContext *ctx) //01FA - todo: MessageAllFromNarc?
{
    u16 arc = ScriptGetVar(ctx);
    u16 msg = ScriptGetVar(ctx);
    struct MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, arc, 32);
    MOD05_ShowMessageInField(ctx, msgData, msg);
    DestroyMsgData(msgData);
    return FALSE;
}

BOOL ScrCmd_MessageFrom2(struct ScriptContext *ctx) //01FB - todo: MessageFromNarc?
{
    u16 arc = ScriptGetVar(ctx);
    u16 msg = ScriptGetVar(ctx);
    struct MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, arc, 32);
    MOD05_021E2BD0(ctx, msgData, msg, 1, NULL);
    DestroyMsgData(msgData);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

BOOL ScrCmd_Unk01FC(struct ScriptContext *ctx) //01FC
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    s16 word2 = (s16)ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 0xff);
    return FALSE;
}

BOOL ScrCmd_Unk01FD(struct ScriptContext *ctx) //01FD
{
    u16 typ = ScriptReadHalfword(ctx);
    u16 id = ScriptReadHalfword(ctx);
    u16 word1 = ScriptReadHalfword(ctx);
    s16 word2 = (s16)ScriptReadHalfword(ctx);

    MOD05_021E2C58(ctx, typ, id, word1, word2, 1);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

BOOL ScrCmd_Unk01FE(struct ScriptContext *ctx) //01FE
{
    u8 id = ScriptReadByte(ctx);

    if (ctx->fieldSystem->unkA8 == NULL)
    {
        return FALSE;
    }

    u16 *unkArr = ctx->fieldSystem->unkA8->unk90[id].unk0;
    if (unkArr[0] == 0xFFFF)
    {
        struct MsgData *msgdata = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 0x22b, 32);
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

BOOL ScrCmd_Unk01FF(struct ScriptContext *ctx) //01FF
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 msg = ScriptReadByte(ctx);
    u16 poke = ScriptGetVar(ctx);
    u16 sex = ScriptReadHalfword(ctx);
    u8 flag = ScriptReadByte(ctx);
    u8 unk = 0;

    MessageFormat *messageFormat = MOD06_02244210(fieldSystem->saveBlock2, poke, sex, flag, &unk);
    MOD05_021E2CBC(ctx, messageFormat, (u8)(msg + unk), 1);
    MessageFormat_Delete(messageFormat);

    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

BOOL ScrCmd_MessageUnown(struct ScriptContext *ctx) //026D
{
    struct UnkStruct_0203A288 myLocalStruct;
    u16 msg = ScriptReadHalfword(ctx);

    MOD05_021E2BB8(&myLocalStruct, ctx);
    myLocalStruct.unk2 = 3;

    MOD05_021E2BD0(ctx, ctx->msgData, msg, 0, &myLocalStruct);
    SetupNativeScript(ctx, FUN_0203A2F0);

    return TRUE;
}

BOOL ScrCmd_Unk002C(struct ScriptContext *ctx) //002C - todo: Message?
{
    u8 msg = ScriptReadByte(ctx);
    MOD05_021E2BD0(ctx, ctx->msgData, msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

/*static*/ BOOL FUN_0203A2F0(struct ScriptContext *ctx)
{
    u8 *textPrinterNumber = (u8 *)FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_TEXT_PRINTER_NUMBER);
    return FUN_020546C8(*textPrinterNumber);
}

BOOL ScrCmd_Unk002D(struct ScriptContext *ctx) //002D - todo: MessageFromVar? MessageFlex?
{
    u16 msg = ScriptGetVar(ctx);
    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

BOOL ScrCmd_Unk02C0(struct ScriptContext *ctx) //02C0
{
    struct UnkStruct_0203A288 myLocalStruct;
    u16 msg = ScriptGetVar(ctx);

    MOD05_021E2BB8(&myLocalStruct, ctx);
    myLocalStruct.unk1 = 1;

    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 1, &myLocalStruct);
    SetupNativeScript(ctx, FUN_0203A2F0);

    return TRUE;
}

BOOL ScrCmd_Unk002E(struct ScriptContext *ctx) //002E - todo: MessageWait? MessageNoSkip?
{
    u16 msg = ScriptGetVar(ctx);
    MOD05_021E2BD0(ctx, ctx->msgData, (u8)msg, 0, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

BOOL ScrCmd_Unk020C(struct ScriptContext *ctx) //020C
{
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u8 msg = (u8)FUN_02058488(*lastInteracted);
    MOD05_021E2BD0(ctx, ctx->msgData, msg, 1, NULL);
    SetupNativeScript(ctx, FUN_0203A2F0);
    return TRUE;
}

BOOL ScrCmd_Unk002F(struct ScriptContext *ctx) //002F
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

BOOL ScrCmd_WaitButtonAB(struct ScriptContext *ctx) //0030
{
    SetupNativeScript(ctx, FUN_0203A46C);
    return TRUE;
}

static BOOL FUN_0203A46C(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    if (gSystem.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
    {
        return TRUE;
    }
    return FALSE;
}

BOOL ScrCmd_WaitButtonABTime(struct ScriptContext *ctx) //0190
{
    ctx->data[0] = ScriptGetVar(ctx);
    SetupNativeScript(ctx, FUN_0203A4AC);
    return TRUE;
}

static BOOL FUN_0203A4AC(struct ScriptContext *ctx)
{
    if (gSystem.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
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

BOOL ScrCmd_WaitButton(struct ScriptContext *ctx) //0031
{
    SetupNativeScript(ctx, FUN_0203A4E0);
    return TRUE;
}

static BOOL FUN_0203A4E0(struct ScriptContext *ctx)
{
    if (gSystem.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
    {
        return TRUE;
    }
    else if (gSystem.newKeys & PAD_KEY_UP)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 0);
    }
    else if (gSystem.newKeys & PAD_KEY_DOWN)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 1);
    }
    else if (gSystem.newKeys & PAD_KEY_LEFT)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 2);
    }
    else if (gSystem.newKeys & PAD_KEY_RIGHT)
    {
        FUN_02055304(ctx->fieldSystem->playerAvatar, 3);
    }
    else if (gSystem.newKeys & PAD_BUTTON_X)
    {
        FUN_02039460(ctx->fieldSystem);
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

BOOL ScrCmd_WaitButtonABPad(struct ScriptContext *ctx) //0032
{
    SetupNativeScript(ctx, FUN_0203A570);
    return TRUE;
}

static BOOL FUN_0203A570(struct ScriptContext *ctx)
{
#pragma unused(ctx)
    if (gSystem.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B)) {
        return TRUE;
    }
    else if (gSystem.newKeys & (PAD_KEY_RIGHT | PAD_KEY_LEFT | PAD_KEY_UP | PAD_KEY_DOWN)) {
        return TRUE;
    }
    return FALSE;
}

BOOL ScrCmd_Unk0033(struct ScriptContext *ctx) //0033 - todo: OpenMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *unk = (u8 *)FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_UNKNOWN_06);
    FUN_020545B8(fieldSystem->bgConfig, (struct Window *)FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_WINDOW), 3);
    FUN_02054608((struct Window *)FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_WINDOW), Save_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveBlock2));
    *unk = 1;
    return FALSE;
}

BOOL ScrCmd_CloseMessageBox(struct ScriptContext* ctx) //0034
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct Window *window = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_WINDOW);
    u8 *unk2 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_UNKNOWN_06);
    ClearFrameAndWindow2(window, 0);
    RemoveWindow(window);
    *unk2 = 0;
    return FALSE;
}

BOOL ScrCmd_Unk0035(struct ScriptContext* ctx) //0035 - todo: FreezeMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct Window *window = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_WINDOW);
    u8 *unk2 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_UNKNOWN_06);
    RemoveWindow(window);
    *unk2 = 0;
    return FALSE;
}

BOOL ScrCmd_ScrollBg(struct ScriptContext* ctx) //003C
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *xval = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8008);
    u16 *xcnt = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8004);
    u16 *xdir = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8009);
    u16 *yval = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_800A);
    u16 *ycnt = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8005);
    u16 *ydir = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_800B);

    *xval = ScriptReadByte(ctx);
    *xcnt = ScriptReadByte(ctx);
    *xdir = ScriptReadByte(ctx);
    *yval = ScriptReadByte(ctx);
    *ycnt = ScriptReadByte(ctx);
    *ydir = ScriptReadByte(ctx);

    SetupNativeScript(ctx, FUN_0203A6C8);
    return TRUE;
}

static BOOL FUN_0203A6C8(struct ScriptContext* ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *xval = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8008);
    u16 *xdir = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8009);
    u16 *yval = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_800A);
    u16 *ydir = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_800B);
    u16 *xcnt = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8004);
    u16 *ycnt = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_SPECIAL_VAR_8005);

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

BOOL ScrCmd_CreateMessageBox(struct ScriptContext* ctx) //003C
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    struct String **stringBuffer1 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_STRING_BUFFER_1);
    struct String **stringBuffer0 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_STRING_BUFFER_0);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 typ, msg;
    u16 wk, map;

    msg = ScriptReadByte(ctx);
    typ = ScriptReadByte(ctx);
    map = ScriptReadHalfword(ctx);
    wk = ScriptReadHalfword(ctx);

    if (map == 0) {
        LocalMapObject **lastInteracted = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_LAST_INTERACTED);
        map = (u16)FUN_02058510(*lastInteracted, 0);
    }

    MOD05_021E8128(fieldSystem->unk60, typ, map);
    MOD05_021E8130(fieldSystem->unk60, 1);
    MOD05_021E8158(fieldSystem);
    ReadMsgDataIntoString(ctx->msgData, msg, *stringBuffer1);
    StringExpandPlaceholders(*messageFormat, *stringBuffer0, *stringBuffer1);
    AddTextPrinterParameterized(MOD05_021E8140(fieldSystem->unk60), 1, *stringBuffer0, 0, 0, 0, NULL);

    return TRUE;
}

BOOL ScrCmd_Unk0037(struct ScriptContext *ctx) //0037 - todo: SetTextBoard? ColourMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 typ = ScriptReadByte(ctx);
    u16 map = ScriptReadHalfword(ctx);

    MOD05_021E8128(fieldSystem->unk60, typ, map);
    MOD05_021E8130(fieldSystem->unk60, 1);

    return TRUE;
}

BOOL ScrCmd_Unk0038(struct ScriptContext *ctx) //0038 - todo: ShowMessageBox?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 req = ScriptReadByte(ctx);
    MOD05_021E8130(fieldSystem->unk60, req);
    return TRUE;
}

BOOL ScrCmd_Unk0039(struct ScriptContext *ctx) //0039 - todo: MessageBoxWait? WaitMessageBox?
{
    if (MOD05_021E8148(ctx->fieldSystem->unk60) == TRUE)
    {
        return FALSE;
    }

    SetupNativeScript(ctx, FUN_0203A8A0);
    return TRUE;
}

static BOOL FUN_0203A8A0(struct ScriptContext *ctx)
{
    if (MOD05_021E8148(ctx->fieldSystem->unk60) == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL ScrCmd_Unk003A(struct ScriptContext *ctx) //003A - todo: CreateMessageBoxText?
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *printerNumber = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_TEXT_PRINTER_NUMBER);
    struct String **stringBuffer1 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_STRING_BUFFER_1);
    struct String **stringBuffer0 = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_STRING_BUFFER_0);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);

    u8 msg = ScriptReadByte(ctx);
    u16 wk = ScriptReadHalfword(ctx);

    ReadMsgDataIntoString(ctx->msgData, msg, *stringBuffer1);
    StringExpandPlaceholders(*messageFormat, *stringBuffer0, *stringBuffer1);

    *printerNumber = (u8)FUN_02054658(MOD05_021E8140(fieldSystem->unk60), *stringBuffer0, Save_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveBlock2), 1);
    ctx->data[0] = wk;
    SetupNativeScript(ctx, FUN_0203A94C);
    return TRUE;
}

static BOOL FUN_0203A94C(struct ScriptContext *ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u8 *printerNumber = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_TEXT_PRINTER_NUMBER);
    u16 *varPtr = GetVarPointer(fieldSystem, (u16)ctx->data[0]);
    MOD05_021E8144(fieldSystem->unk60);

    u32 tmp = 0xFFFF;
    if (FUN_020546C8(*printerNumber) == TRUE)
    {
        *varPtr = 2;
        return TRUE;
    }

    if (gSystem.newKeys & PAD_KEY_UP)
    {
        tmp = 0;
    }
    else if (gSystem.newKeys & PAD_KEY_DOWN)
    {
        tmp = 1;
    }
    else if (gSystem.newKeys & PAD_KEY_LEFT)
    {
        tmp = 2;
    }
    else if (gSystem.newKeys & PAD_KEY_RIGHT)
    {
        tmp = 3;
    }

    if (tmp != 0xFFFF)
    {
        FUN_0201BD7C(*printerNumber);
        FUN_02055304(ctx->fieldSystem->playerAvatar, tmp);
        *varPtr = 0;
        return TRUE;
    }
    else
    {
        if (gSystem.newKeys & PAD_BUTTON_X)
        {
            FUN_0201BD7C(*printerNumber);
            *varPtr = 1;
            return TRUE;
        }
        return FALSE;
    }
}

BOOL ScrCmd_Unk003B(struct ScriptContext *ctx) //003B - todo: CloseMessageBox?
{
    ctx->data[0] = ScriptReadHalfword(ctx);

    SetupNativeScript(ctx, FUN_0203AA0C);
    return TRUE;
}

static BOOL FUN_0203AA0C(struct ScriptContext *ctx)
{
    u16 *unk = GetVarPointer(ctx->fieldSystem, (u16)ctx->data[0]);

    u32 tmp = 0xFFFF;
    if (gSystem.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B))
    {
        *unk = 0;
        return TRUE;
    }
    else if (gSystem.newKeys & PAD_KEY_UP)
    {
        tmp = 0;
    }
    else if (gSystem.newKeys & PAD_KEY_DOWN)
    {
        tmp = 1;
    }
    else if (gSystem.newKeys & PAD_KEY_LEFT)
    {
        tmp = 2;
    }
    else if (gSystem.newKeys & PAD_KEY_RIGHT)
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
        if (gSystem.newKeys & PAD_BUTTON_X)
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

BOOL ScrCmd_Menu(struct ScriptContext *ctx) //003C
{
    FUN_02039460(ctx->fieldSystem);
    return FALSE;
}

BOOL ScrCmd_YesNoMenu(struct ScriptContext *ctx) //003E
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_LIST_MENU_2D);
    u16 wk = ScriptReadHalfword(ctx);
    LoadUserFrameGfx1(fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, 985, 11, 0, 4);
    *unk = Std_CreateYesNoMenu(fieldSystem->bgConfig, &UNK_020F34E0, 985, 11, 4);
    ctx->data[0] = wk;
    SetupNativeScript(ctx, FUN_0203AB00);
    return TRUE;
}

static BOOL FUN_0203AB00(struct ScriptContext *ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_LIST_MENU_2D);
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

BOOL ScrCmd_ShowWaitingIcon(struct ScriptContext *ctx) { //018D
    struct Window *window = (struct Window *)FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_WINDOW);
    WaitingIcon **waitingIcon = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_WAITING_ICON);
    *waitingIcon = WaitingIcon_New(window, 994);
    return FALSE;
}

BOOL ScrCmd_HideWaitingIcon(struct ScriptContext *ctx) //018E
{
    WaitingIcon **waitingIcon = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_WAITING_ICON);
    FUN_0200DBFC(*waitingIcon);
    return FALSE;
}

BOOL ScrCmd_Unk0040(struct ScriptContext *ctx) //0040
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MENU_WINDOW);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);
    u16 unk7 = ScriptReadHalfword(ctx);
    u16 *ptr = GetVarPointer(fieldSystem, unk7);
    struct Window *window = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_WINDOW);
    *unk = MOD05_021E1BF8(fieldSystem, unk3, unk4, unk5, unk6, ptr, *messageFormat, window, NULL);
    ctx->data[0] = unk7;
    return TRUE;
}

BOOL ScrCmd_Unk0041(struct ScriptContext *ctx) //0041
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MENU_WINDOW);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);
    u16 unk7 = ScriptReadHalfword(ctx);
    u16 *ptr = GetVarPointer(fieldSystem, unk7);
    struct Window *window = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_WINDOW);
    *unk = MOD05_021E1BF8(fieldSystem, unk3, unk4, unk5, unk6, ptr, *messageFormat, window, ctx->msgData);
    ctx->data[0] = unk7;
    return TRUE;
}

BOOL ScrCmd_Unk0042(struct ScriptContext *ctx) //0042
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    u8 unk2 = ScriptReadByte(ctx);
    u8 unk3 = ScriptReadByte(ctx);
    MOD05_021E1C4C(*unk, unk2, unk3);
    return FALSE;
}

BOOL ScrCmd_Unk029D(struct ScriptContext *ctx) //029D
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MENU_WINDOW);
    u16 unk2 = ScriptGetVar(ctx);
    u16 unk3 = ScriptGetVar(ctx);
    MOD05_021E1C4C(*unk, unk2, unk3);
    return FALSE;
}

BOOL ScrCmd_Unk0043(struct ScriptContext *ctx) //0043
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    MOD05_021E1C54(*unk);
    SetupNativeScript(ctx, FUN_0203AD2C);
    return TRUE;
}

static BOOL FUN_0203AD2C(struct ScriptContext *ctx)
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

BOOL ScrCmd_Unk02B9(struct ScriptContext *ctx) //02B9
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    MOD05_021E1C54(*unk);
    SetupNativeScript(ctx, FUN_0203AD78);
    return TRUE;
}

static BOOL FUN_0203AD78(struct ScriptContext *ctx)
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 *varPtr = GetVarPointer(fieldSystem, (u16)ctx->data[0]);
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MENU_WINDOW);

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

BOOL ScrCmd_Unk0044(struct ScriptContext *ctx) //0044
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MENU_WINDOW);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);

    u16 halfWord = ScriptReadHalfword(ctx);
    u16 *varPtr = GetVarPointer(fieldSystem, halfWord);
    struct Window *window = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_WINDOW);
    *unk = MOD05_021E1F34(fieldSystem, unk3, unk4, unk5, unk6, varPtr, *messageFormat, window, NULL);
    ctx->data[0] = halfWord;
    return TRUE;
}

BOOL ScrCmd_Unk0045(struct ScriptContext *ctx) //0045
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 *unk = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MENU_WINDOW);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u8 unk3 = ScriptReadByte(ctx);
    u8 unk4 = ScriptReadByte(ctx);
    u8 unk5 = ScriptReadByte(ctx);
    u8 unk6 = ScriptReadByte(ctx);

    u16 halfWord = ScriptReadHalfword(ctx);
    u16 *varPtr = GetVarPointer(fieldSystem, halfWord);
    struct Window *window = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_WINDOW);
    *unk = MOD05_021E1F34(fieldSystem, unk3, unk4, unk5, unk6, varPtr, *messageFormat, window, ctx->msgData);
    ctx->data[0] = halfWord;
    return TRUE;
}

BOOL ScrCmd_Unk0046(struct ScriptContext *ctx) //0046 - todo: AddListOption?
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    u16 unk2 = ScriptGetVar(ctx);
    u16 unk3 = ScriptGetVar(ctx);
    u16 unk4 = ScriptGetVar(ctx);
    MOD05_021E1F58(*unk, (u8)unk2, (u8)unk3, (u8)unk4);
    return FALSE;
}

BOOL ScrCmd_Unk0047(struct ScriptContext *ctx) //0047 - todo: ShowList?
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    MOD05_021E1F60(*unk);
    SetupNativeScript(ctx, FUN_0203AD2C);
    return TRUE;
}

BOOL ScrCmd_Unk0048(struct ScriptContext *ctx) //0048
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    MOD05_021E26CC(*unk, ScriptReadByte(ctx));
    SetupNativeScript(ctx, FUN_0203AD2C);
    return TRUE;
}

BOOL ScrCmd_Unk02CF(struct ScriptContext *ctx) //02CF
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    MOD05_021E2B80(*unk, ScriptReadByte(ctx));
    return TRUE;
}

BOOL ScrCmd_Unk02D0(struct ScriptContext *ctx) //02D0
{
    u32 *unk = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MENU_WINDOW);
    MOD05_021E2B9C(*unk, ScriptReadByte(ctx));
    return TRUE;
}

BOOL ScrCmd_Unk005E(struct ScriptContext *ctx) //005E - todo: ApplyMovement?
{
    u16 unk = ScriptGetVar(ctx);
    u32 unk2 = ScriptReadWord(ctx);

    LocalMapObject *event = FUN_0203B120(ctx->fieldSystem, unk);
    GF_ASSERT(event);

    u32 unk4 = FUN_0205AEA4(event, ctx->scriptPtr + unk2);
    u8 *movementCounter = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ACTIVE_MOVEMENT_COUNTER);
    (*movementCounter)++;

    FUN_0203B174(ctx->fieldSystem, unk4, NULL);
    return FALSE;
}

BOOL ScrCmd_Unk02A1(struct ScriptContext *ctx) { //02A1
    LocalMapObject *event; //has to be defined first to match
    u16 unk0 = ScriptGetVar(ctx);
    u16 unk1 = ScriptGetVar(ctx);
    u16 unk2 = ScriptGetVar(ctx);

    event = FUN_0203B120(ctx->fieldSystem, unk0);

    GF_ASSERT(event);

    u16 *unk4 = AllocFromHeap(4, 0x100);
    u16 xVal = (u16)FUN_02058B2C(event);
    u16 yVal = (u16)FUN_02058B4C(event);

    u32 pos = 0;

    if (xVal < unk1) {
        unk4[0] = 15;
        pos++;
        unk4[1] = (u16)(unk1 - xVal);
    }
    else if (xVal > unk1) {
        unk4[0] = 14;
        pos++;
        unk4[1] = (u16)(xVal - unk1);
    }

    if (yVal < unk2) {
        unk4[pos * 2] = 12;
        unk4[pos * 2 + 1] = (u16)(unk2 - yVal);
        pos++;
    }
    else if (yVal > unk2) {
        unk4[pos * 2] = 13;
        unk4[pos * 2 + 1] = (u16)(yVal - unk2);
        pos++;
    }

    unk4[pos * 2] = 254;
    unk4[pos * 2 + 1] = 0;

    u32 unk7 = FUN_0205AEA4(event, unk4);
    u8 *movementCounter = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ACTIVE_MOVEMENT_COUNTER);

    (*movementCounter)++;

    FUN_0203B174(ctx->fieldSystem, unk7, unk4);
    return FALSE;
}

static LocalMapObject *FUN_0203B120(struct FieldSystem *fieldSystem, u16 eventId)
{
    if (eventId == 242)
    {
        return FUN_020580B4(fieldSystem->unk34, 48);
    }
    else if (eventId == 241)
    {
        LocalMapObject **cameraTarget = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_CAMERA_TARGET);
        return *cameraTarget;
    }
    else
    {
        return FUN_02058060(fieldSystem->unk34, eventId);
    }
}

BOOL ScrCmd_WaitForMovement(struct ScriptContext *ctx) //005F
{
    SetupNativeScript(ctx, IsAllMovementFinished);
    return TRUE;
}

static BOOL IsAllMovementFinished(struct ScriptContext *ctx)
{
    u8 *movCounter = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_ACTIVE_MOVEMENT_COUNTER);
    return *movCounter == 0;
}

static void FUN_0203B174(struct FieldSystem *fieldSystem, u32 param1, void *param2)
{
    UnkStruct_0203B174 *unkStruct = (UnkStruct_0203B174 *)AllocFromHeap(4, sizeof(UnkStruct_0203B174));
    if (unkStruct == NULL)
    {
        GF_AssertFail();
        return;
    }
    unkStruct->fieldSystem = fieldSystem;
    unkStruct->Unk04 = param1;
    unkStruct->Unk08 = param2;
    unkStruct->Unk00 = FUN_0200CA44((void (*)(u32, void *))FUN_0203B1A8, unkStruct, 0);
}

void FUN_0203B1A8(u32 param0, UnkStruct_0203B174 *param1) {
    //is it tho?
#pragma unused(param0)
    u8 *movementCounter = (u8 *)FieldSysGetAttrAddr(param1->fieldSystem, SCRIPTENV_ACTIVE_MOVEMENT_COUNTER);

    if (FUN_0205AEF0(param1->Unk04) != TRUE) {
        return;
    }

    FUN_0205AEFC(param1->Unk04);
    FUN_0200CAB4((s32)param1->Unk00);

    if (param1->Unk08 != NULL) {
        FreeToHeap(param1->Unk08);
    }

    FreeToHeap(param1);

    if (*movementCounter == 0) {
        GF_ASSERT(FALSE);
    } else {
        (*movementCounter)--;
    }
}

BOOL ScrCmd_LockAllEvents(struct ScriptContext *ctx) //0060
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_LAST_INTERACTED);

    if (*lastInteracted == NULL) {
        FUN_02058780(fieldSystem->unk34);
    }
    else {
        ScrCmd_LockAllEvents2(ctx);
    }
    return TRUE;
}

static BOOL FUN_0203B218(struct ScriptContext *ctx) {
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_LAST_INTERACTED);
    LocalMapObject *unk0 = FUN_020553A0(fieldSystem->playerAvatar);
    if (UNK_021C5A0C[0] & 1) {
        if (FUN_0205AE28(unk0) == 1) {
            FUN_02058908(unk0);
            UNK_021C5A0C[0] &= 0xfe;
        }
    }
    if (UNK_021C5A0C[0] & 4) {
        if (FUN_02058854(*lastInteracted) == 0) {
            FUN_02058908(*lastInteracted);
            UNK_021C5A0C[0] &= 0xfb;
        }
    }
    if (UNK_021C5A0C[0] & 2) {
        LocalMapObject *unk1 = FUN_020580B4(fieldSystem->unk34, 48);
        if (FUN_02058854(unk1) == 0) {
            FUN_02058908(unk1);
            UNK_021C5A0C[0] &= 0xfd;
        }
    }
    if (UNK_021C5A0C[0] & 8) {
        LocalMapObject *modifiedevent = FUN_0205E7C4(*lastInteracted);
        if (FUN_02058854(modifiedevent) == 0) {
            FUN_02058908(modifiedevent);
            UNK_021C5A0C[0] &= 0xf7;
        }
    }
    if (UNK_021C5A0C[0] == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

BOOL ScrCmd_LockAllEvents2(struct ScriptContext *ctx) { //02B4
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_LAST_INTERACTED);
    LocalMapObject *unk0 = FUN_020553A0(fieldSystem->playerAvatar);
    LocalMapObject *unk1 = FUN_020580B4(fieldSystem->unk34, 48);
    LocalMapObject *unk2 = FUN_0205E7C4(*lastInteracted);
    u32 unk34 = fieldSystem->unk34;
    UNK_021C5A0C[0] = 0;

    FUN_02058780(unk34);
    if (FUN_0205AE28(unk0) == 0) {
        UNK_021C5A0C[0] |= 1;
        FUN_02058914(unk0);
    }
    if (FUN_02058854(*lastInteracted) != 0) {
        UNK_021C5A0C[0] |= 4;
        FUN_02058914(*lastInteracted);
    }
    if (unk1 != NULL) {
        struct ScriptState *state = SaveArray_Flags_Get(fieldSystem->saveBlock2);
        if (FUN_0205ED3C(state) == TRUE) {
            if (FUN_02058854(unk1) != 0) {
                UNK_021C5A0C[0] |= 2;
                FUN_02058914(unk1);
            }
        }
    }
    if (unk2 != NULL) {
        if (FUN_02058854(unk2) != 0) {
            UNK_021C5A0C[0] |= 8;
            FUN_02058914(unk2);
        }
    }
    SetupNativeScript(ctx, FUN_0203B218);
    return TRUE;
}

BOOL ScrCmd_ReleaseAllEvents(struct ScriptContext *ctx) //0061
{
    FUN_020587B0(ctx->fieldSystem->unk34);
    return TRUE;
}

BOOL ScrCmd_LockEvent(struct ScriptContext *ctx) //0062
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptReadHalfword(ctx);
    FUN_02058908(FUN_02058060(fieldSystem->unk34, eventId));
    return FALSE;
}

BOOL ScrCmd_ReleaseEvent(struct ScriptContext *ctx) //0063
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptReadHalfword(ctx);
    FUN_02058914(FUN_02058060(fieldSystem->unk34, eventId));
    return FALSE;
}

BOOL ScrCmd_AddOverworldEvent(struct ScriptContext *ctx) //0064
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptGetVar(ctx);
    u32 unk0 = FUN_02034B64(fieldSystem);
    u32 unk1 = FUN_02034B6C(fieldSystem);
    u32 res = FUN_020575D4(fieldSystem->unk34, eventId, unk0, *fieldSystem->mapId, unk1);

    GF_ASSERT(res);
    return FALSE;
}

BOOL ScrCmd_RemoveOverworldEvent(struct ScriptContext *ctx) //0065
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptGetVar(ctx);
    FUN_02057688(FUN_02058060(fieldSystem->unk34, eventId));
    return FALSE;
}

BOOL ScrCmd_LockCamera(struct ScriptContext *ctx) //0066
{
    u16 x = ScriptGetVar(ctx);
    u16 y = ScriptGetVar(ctx);
    LocalMapObject **targetPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_CAMERA_TARGET);
    *targetPtr = FUN_0205753C(ctx->fieldSystem->unk34, x, y, 0, 0x2000, 0, *ctx->fieldSystem->mapId);
    FUN_02059D1C(*targetPtr);
    FUN_0205889C(*targetPtr, 1);
    FUN_020588B8(*targetPtr, 0);
    struct Vecx32 *position = FUN_02058B7C(*targetPtr);
    MOD05_021EF5E0(position, ctx->fieldSystem->unk24);
    Camera_SetFixedTarget(position, ctx->fieldSystem->camera);
    return FALSE;
}

BOOL ScrCmd_ReleaseCamera(struct ScriptContext *ctx) //0067
{
    LocalMapObject **targetPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_CAMERA_TARGET);
    FUN_02057654(*targetPtr);
    struct Vecx32 *position = FUN_02058B7C(FUN_02058060(ctx->fieldSystem->unk34, 0xff));
    MOD05_021EF5E0(position, ctx->fieldSystem->unk24);
    Camera_SetFixedTarget(position, ctx->fieldSystem->camera);
    return FALSE;
}

BOOL ScrCmd_FacePlayer(struct ScriptContext *ctx) //0068
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u32 unk0 = FUN_02059E74(PlayerAvatar_GetFacingDirection(fieldSystem->playerAvatar));
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_LAST_INTERACTED);

    if (*lastInteracted == NULL) {
        return FALSE;
    }

    MOD05_021F1EC0(*lastInteracted, unk0);
    return FALSE;
}

BOOL ScrCmd_GetPlayerPosition(struct ScriptContext *ctx) //0069
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 *xVar = ScriptGetVarPointer(ctx);
    u16 *yVar = ScriptGetVarPointer(ctx);

    *xVar = GetPlayerXCoord(fieldSystem->playerAvatar);
    *yVar = GetPlayerYCoord(fieldSystem->playerAvatar);

    return FALSE;
}

BOOL ScrCmd_GetOverworldEventPosition(struct ScriptContext *ctx) //006A
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 eventId = ScriptGetVar(ctx);
    LocalMapObject *event = FUN_02058060(fieldSystem->unk34, eventId);

    u16 *xVar = ScriptGetVarPointer(ctx);
    u16 *yVar = ScriptGetVarPointer(ctx);

    *xVar = (u16)FUN_02058B2C(event);
    *yVar = (u16)FUN_02058B4C(event);
    return FALSE;
}

BOOL ScrCmd_GetPlayerDirection(struct ScriptContext *ctx) //01BD
{
    u16 *directionVar = ScriptGetVarPointer(ctx);

    *directionVar = (u16)PlayerAvatar_GetFacingDirection(ctx->fieldSystem->playerAvatar);
    return FALSE;
}

BOOL ScrCmd_Unk006B(struct ScriptContext *ctx) //006B - todo: CheckPersonPosition?
{
    u16 x = ScriptGetVar(ctx);
    u16 y = ScriptGetVar(ctx);
    u16 z = ScriptGetVar(ctx);

    struct Vecx32 vector;
    vector.x = FX32_CONST(x);
    vector.y = FX32_CONST(y);
    vector.z = FX32_CONST(z);

    FUN_02058BB4(FUN_020553A0(ctx->fieldSystem->playerAvatar), &vector);
    Camera_OffsetLookAtPosAndTarget(&vector, ctx->fieldSystem->camera);
    return FALSE;
}

BOOL ScrCmd_KeepOverworldEvent(struct ScriptContext *ctx) //006C
{
    u16 eventId = ScriptGetVar(ctx);
    LocalMapObject *event = FUN_02058060(ctx->fieldSystem->unk34, eventId);
    FUN_02058994(event, ScriptReadByte(ctx));
    return FALSE;
}

BOOL ScrCmd_SetOverworldEventMovement(struct ScriptContext *ctx) //006D
{
    u16 eventId = ScriptGetVar(ctx);
    LocalMapObject *event = FUN_02058060(ctx->fieldSystem->unk34, eventId);
    u16 movement = ScriptReadHalfword(ctx);
    FUN_02058E90(event, movement);
    return FALSE;
}

BOOL ScrCmd_GetOverworldEventMovement(struct ScriptContext *ctx) //02AD
{
    u16 *variable = ScriptGetVarPointer(ctx);
    *variable = 0;
    u16 eventId = ScriptGetVar(ctx);

    LocalMapObject *event = FUN_02058060(ctx->fieldSystem->unk34, eventId);
    if (event != NULL) {
        *variable = FUN_02058480(event);
    }
    return FALSE;
}

BOOL ScrCmd_OverworldEventStopFollowing(struct ScriptContext *ctx) //006E
{
    LocalMapObject *event = FUN_020580B4(ctx->fieldSystem->unk34, 0x30);
    FUN_02058EB0(event, 0xFE);
    return FALSE;
}

BOOL ScrCmd_Unk02AB(struct ScriptContext *ctx) //02AB
{
    u16 *variable = ScriptGetVarPointer(ctx);
    struct SealCase *sealCase = Save_SealCase_Get(ctx->fieldSystem->saveBlock2);
    *variable = FUN_02029E0C(sealCase);
    return FALSE;
}

BOOL ScrCmd_GetSealCountFromId(struct ScriptContext *ctx) //0093
{
    u16 sealId = ScriptGetVar(ctx);
    u16 *variable = ScriptGetVarPointer(ctx);
    struct SealCase *sealCase = Save_SealCase_Get(ctx->fieldSystem->saveBlock2);
    *variable = SealCase_CountSealOccurrenceAnywhere(sealCase, sealId);
    return FALSE;
}

BOOL ScrCmd_GiveSeals(struct ScriptContext *ctx) //0094
{
    u16 sealId = ScriptGetVar(ctx);
    u16 amount = ScriptGetVar(ctx);

    struct SealCase *sealCase = Save_SealCase_Get(ctx->fieldSystem->saveBlock2);
    FUN_02029D44(sealCase, sealId, (s16)amount);
    return FALSE;
}

BOOL ScrCmd_GetPokemonForme(struct ScriptContext *ctx) //0095
{
    u16 partyPosition = ScriptGetVar(ctx);
    u16 *variable = ScriptGetVarPointer(ctx);

    struct PlayerParty *party = SaveArray_PlayerParty_Get(ctx->fieldSystem->saveBlock2);
    *variable = GetMonUnownLetter(GetPartyMonByIndex(party, partyPosition));

    return FALSE;
}

BOOL ScrCmd_ChoosePokemonMenu(struct ScriptContext *ctx) { //0191
    PartyMenuAppData **partyMenu = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    *partyMenu = FUN_020379F8(0x20, ctx->fieldSystem);
    SetupNativeScript(ctx, FUN_0203BC04);
    return TRUE;
}

BOOL ScrCmd_OpenTradeScreen(struct ScriptContext *ctx) { //02A5
    PartyMenuAppData **partyMenu = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    *partyMenu = FUN_02037A1C(0x20, ctx->fieldSystem);
    SetupNativeScript(ctx, FUN_0203BC04);
    return TRUE;
}

BOOL ScrCmd_UnionChoosePokemonMenu(struct ScriptContext *ctx) { //0192
    PartyMenuAppData **partyMenu = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    *partyMenu = FUN_02037B44(ctx->fieldSystem->taskManager, 0x20);
    return TRUE;
}

BOOL ScrCmd_GetSelectedPartySlot(struct ScriptContext *ctx) { //0193
    u16 *variable = ScriptGetVarPointer(ctx);
    PartyMenuAppData **partyMenu = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);

    GF_ASSERT(*partyMenu);
    *variable = FUN_02037A40(*partyMenu);

    if (*variable == 7) {
        *variable = 0xFF;
    }
    FreeToHeap(*partyMenu);
    *partyMenu = NULL;
    return FALSE;
}

BOOL ScrCmd_Unk0194(ScriptContext *ctx) { //0194
    void **runningAppData = (void **)FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    u16 unk0 = ScriptGetVar(ctx);
    u16 unk1 = ScriptGetVar(ctx);
    u16 unk2 = ScriptGetVar(ctx);
    u16 unk3 = ScriptGetVar(ctx);

    *runningAppData = FUN_02037BB0(0x20, ctx->fieldSystem, unk2, unk1, unk3, unk0);
    SetupNativeScript(ctx, FUN_0203BC04);
    return TRUE;
}

BOOL ScrCmd_Unk0195(ScriptContext *ctx) { //0195
    u16 *unk0 = ScriptGetVarPointer(ctx);
    u16 *unk1 = ScriptGetVarPointer(ctx);
    PartyMenuAppData **partyMenuData = (PartyMenuAppData **)FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    GF_ASSERT(*partyMenuData);

    *unk0 = FUN_02037A40(*partyMenuData);

    if (*unk0 == 7) {
        *unk0 = 0xFF;
    }

    *unk1 = FUN_02037A70(*partyMenuData);
    *unk1 = (*unk1 == 1);

    FreeToHeap(*partyMenuData);
    *partyMenuData = NULL;
    return FALSE;
}

BOOL ScrCmd_Unk0196(ScriptContext *ctx) { //0196
    void **runningAppData = (void **)FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    u16 unk0 = ScriptGetVar(ctx);

    *runningAppData = FUN_02037C00(0x20, ctx->fieldSystem, unk0);
    SetupNativeScript(ctx, FUN_0203BC04);
    return TRUE;
}

BOOL ScrCmd_Unk0197(ScriptContext *ctx) { //0197
    u16 *unk0 = ScriptGetVarPointer(ctx);
    void **runningAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);

    GF_ASSERT(*runningAppData);

    *unk0 = FUN_02037A78(*runningAppData);
    FreeToHeap(*runningAppData);
    *runningAppData = NULL;

    return FALSE;
}

BOOL ScrCmd_Unk009B(ScriptContext *ctx) { //009B
    LocalMapObject **lastInteracted = (LocalMapObject **)FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u16 unk0 = ScriptGetVar(ctx);
    u16 *unk1 = ScriptGetVarPointer(ctx);

    *unk1 = MOD05_021E1858(ctx->fieldSystem, *lastInteracted, unk0);
    return FALSE;
}

BOOL ScrCmd_DummySetWeather(ScriptContext *ctx) { //009C
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_DummyInitWeather(ScriptContext *ctx) { //009D
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_DummyUpdateWeather(ScriptContext *ctx) { //009E
#pragma unused(ctx)
    return TRUE;
}

BOOL ScrCmd_DummyGetMapPosition(ScriptContext *ctx) { //009F
#pragma unused(ctx)
    return FALSE;
}

/*static*/ BOOL FUN_0203BB90(ScriptContext *ctx) {
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    void **runningAppData = FieldSysGetAttrAddr(fieldSystem, SCRIPTENV_RUNNING_APP_DATA);

    if (FUN_0204647C(fieldSystem)) {
        return FALSE;
    }
    FreeToHeap(*runningAppData);
    *runningAppData = NULL;
    return TRUE;
}

static BOOL FUN_0203BBBC(ScriptContext *ctx) {
    struct FieldSystem *fieldSystem = ctx->fieldSystem;
    PCBoxAppData **pcBoxDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    PCBoxAppData *pcBoxData = *pcBoxDataPtr;
    if (FUN_0204647C(fieldSystem)) {
        return FALSE;
    }
    if (pcBoxData->unk08 == TRUE) {
        FUN_02028AD4(fieldSystem->unk98, FUN_02029048(11), 1);
    }
    FreeToHeap(*pcBoxDataPtr);
    *pcBoxDataPtr = NULL;
    return TRUE;
}

/*static*/ BOOL FUN_0203BC04(ScriptContext *ctx) {
    return !FUN_0204647C(ctx->fieldSystem);
}

BOOL ScrCmd_RestoreOverworld(ScriptContext *ctx) { //00A1
    FUN_0204AF84(ctx->fieldSystem->taskManager);
    return TRUE;
}

BOOL ScrCmd_TerminateOverworldProcess(ScriptContext *ctx) { //01F8
    FUN_0204AF3C(ctx->fieldSystem->taskManager);
    return TRUE;
}

static BOOL CheckPortraitSlotFullInternal(struct FieldSystem *fieldSystem, BOOL isContest, u32 portraitSlot) {
    SaveFashionData *fashionData = Save_FashionData_Get(fieldSystem->saveBlock2);
    if (!isContest) {
        if (!CheckPortraitSlotFull(fashionData, portraitSlot)) {
            return FALSE;
        }
    } else {
        if (!CheckContestPortraitSlotFull(fashionData, portraitSlot)) {
            return FALSE;
        }
    }
    return TRUE;
}

static FashionAppData *FUN_0203BC6C(u32 heapId, struct FieldSystem *fieldSystem, BOOL isContest, u32 portraitSlot) {
    SaveFashionData *fashionData = Save_FashionData_Get(fieldSystem->saveBlock2);
    if (!CheckPortraitSlotFullInternal(fieldSystem, isContest, portraitSlot)) {
        return NULL;
    }
    FashionAppData *appData = AllocFromHeap(heapId, sizeof(FashionAppData));
    __builtin__clear(appData, sizeof(FashionAppData));
    appData->fashionData = fashionData;
    appData->isContest = isContest;
    appData->portraitSlot = portraitSlot;
    return appData;
}

BOOL ScrCmd_Unk00A2(ScriptContext *ctx) { //00A2
    MOD05_021F02C4(ctx->fieldSystem);
    return TRUE;
}

BOOL ScrCmd_Unk00A3(ScriptContext *ctx) { //00A3
    FUN_0206F3B8(ctx->taskManager);
    return TRUE;
}

BOOL ScrCmd_GetDressupPortraitSlot(ScriptContext *ctx) { //00A4
    FashionAppData **runningAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    u16 *portraitSlotPtr = ScriptGetVarPointer(ctx);
    *portraitSlotPtr = (*runningAppData)->portraitSlot;
    FreeToHeap(*runningAppData);
    return FALSE;
}

BOOL ScrCmd_Unk0207(ScriptContext *ctx) { //0207
    u16 *ptr = ScriptGetVarPointer(ctx);
    *ptr = FUN_02031190();
    return TRUE;
}

BOOL ScrCmd_ShowPokemonPic(ScriptContext *ctx) { //0208
    PokepicManager **pokepicManager = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 species = ScriptGetVar(ctx);
    u16 gender = ScriptGetVar(ctx);
    LoadUserFrameGfx1(ctx->fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, 0x3D9, 11, 0, 4);
    *pokepicManager = DrawPokemonPicFromSpecies(ctx->fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, 10, 5, 11, 0x3D9, species, gender, 4);
    Script_SetMonSeenFlagBySpecies(ctx->fieldSystem, species);
    return FALSE;
}

BOOL ScrCmd_ShowPartyPokemonPic(ScriptContext *ctx) { //028C
    PokepicManager **pokepicManager = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 partyId = ScriptGetVar(ctx);
    struct Pokemon *mon = GetPartyMonByIndex(SaveArray_PlayerParty_Get(ctx->fieldSystem->saveBlock2), partyId);
    LoadUserFrameGfx1(ctx->fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, 0x3D9, 11, 0, 4);
    *pokepicManager = DrawPokemonPicFromMon(ctx->fieldSystem->bgConfig, GF_BG_LYR_MAIN_3, 10, 5, 11, 0x3D9, mon, 4);
    u32 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    Script_SetMonSeenFlagBySpecies(ctx->fieldSystem, (u16)species);
    return FALSE;
}

BOOL ScrCmd_Unk0209(ScriptContext *ctx) { //0209
    PokepicManager **pokepicManager = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    (*pokepicManager)->unk00 = 1;
    return TRUE;
}

BOOL ScrCmd_Unk028D(ScriptContext *ctx) { //028D
    PokepicManager **pokepicManager = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    (*pokepicManager)->unk00 = 2;
    return TRUE;
}

BOOL ScrCmd_Unk028E(ScriptContext *ctx) { //028E
    ctx->data[0] = ScriptReadHalfword(ctx);
    SetupNativeScript(ctx, FUN_0203BE9C);
    return TRUE;
}

static BOOL FUN_0203BE9C(ScriptContext *ctx) {
    PokepicManager **pokepicManager = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = GetVarPointer(ctx->fieldSystem, ctx->data[0]); //unused
    return (*pokepicManager)->unk00 != 3;
}

BOOL ScrCmd_Unk020A(ScriptContext *ctx) { //020A
    u16 unk0 = ScriptReadHalfword(ctx);
    MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 *ptr = GetVarPointer(ctx->fieldSystem, unk0);
    MOD05_021E1374(ctx->taskManager, *messageFormat, ptr);
    return TRUE;
}

BOOL ScrCmd_Unk020B(ScriptContext *ctx) { //020B
    LocalMapObject **lastInteracted = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    if (*lastInteracted != NULL) {
        MOD05_021E1994(ctx->fieldSystem, *lastInteracted);
    }
    return FALSE;
}

BOOL ScrCmd_Unk00A5(ScriptContext *ctx) { //00A5
    FUN_0208A338(ctx->taskManager);
    return TRUE;
}

BOOL ScrCmd_DressupPokemon(ScriptContext *ctx) { //00A6
    u16 partyPos = ScriptGetVar(ctx);
    u16 *unk0 = ScriptGetVarPointer(ctx);
    u16 unk1 = ScriptGetVar(ctx);
    FUN_020380CC(ctx->fieldSystem->taskManager, unk0, ctx->fieldSystem->saveBlock2, partyPos, unk1);
    return TRUE;
}

BOOL ScrCmd_ShowDressedPokemon(ScriptContext *ctx) { //00A7
    FashionAppData **fashionAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    u16 portraitSlot = ScriptReadHalfword(ctx);
    u16 *var = ScriptGetVarPointer(ctx);
    *fashionAppData = FUN_0203BC6C(11, ctx->fieldSystem, FALSE, portraitSlot);
    if (*fashionAppData == NULL) {
        *var = 1;
        return TRUE;
    }
    *var = 0;
    FUN_02038130(ctx->fieldSystem, *fashionAppData);
    SetupNativeScript(ctx, FUN_0203BB90);
    return TRUE;
}

BOOL ScrCmd_ShowContestPokemon(ScriptContext *ctx) { //00A8
    FashionAppData **fashionAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    u16 portraitSlot = ScriptReadHalfword(ctx);
    u16 *var = ScriptGetVarPointer(ctx);
    *fashionAppData = FUN_0203BC6C(11, ctx->fieldSystem, TRUE, portraitSlot);
    if (*fashionAppData == NULL) {
        *var = 1;
        return TRUE;
    }
    *var = 0;
    FUN_02038130(ctx->fieldSystem, *fashionAppData);
    SetupNativeScript(ctx, FUN_0203BB90);
    return TRUE;
}

BOOL ScrCmd_CheckPortraitSlot(ScriptContext *ctx) { //012E
    u16 portraitSlot = ScriptReadHalfword(ctx);
    u16 *var = ScriptGetVarPointer(ctx);
    if (CheckPortraitSlotFullInternal(ctx->fieldSystem, FALSE, portraitSlot) == TRUE) {
        *var = TRUE;
        return TRUE;
    }
    *var = FALSE;
    return TRUE;
}

BOOL ScrCmd_CheckContestPortraitSlot(ScriptContext *ctx) { //012F
    u16 portraitSlot = ScriptReadHalfword(ctx);
    u16 *var = ScriptGetVarPointer(ctx);
    if (CheckPortraitSlotFullInternal(ctx->fieldSystem, TRUE, portraitSlot) == TRUE) {
        *var = TRUE;
        return TRUE;
    }
    *var = FALSE;
    return TRUE;
}

BOOL ScrCmd_Unk0130(ScriptContext *ctx) { //0130
    u16 unk0 = ScriptGetVar(ctx);
    SaveFashionData *fashionData = Save_FashionData_Get(ctx->fieldSystem->saveBlock2);
    FUN_02027478(FUN_02027008(fashionData, 0), unk0);
    return TRUE;
}

BOOL ScrCmd_ShowGeonetScreen(ScriptContext *ctx) { //0205
    ShowGeonetScreen(ctx->fieldSystem);
    SetupNativeScript(ctx, FUN_0203BC04);
    return TRUE;
}

BOOL ScrCmd_ShowSealCapsuleEditor(ScriptContext *ctx) { //00A9
    ShowSealCapsuleEditor(ctx->taskManager, ctx->fieldSystem->saveBlock2);
    return TRUE;
}

BOOL ScrCmd_ShowTownMapScreen(ScriptContext *ctx) { //00AA
    TownMapAppData **townMap = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    *townMap = AllocFromHeap(11, sizeof(TownMapAppData));
    FUN_0205F7A0(ctx->fieldSystem, *townMap, 2); //TownMap_Init?
    FUN_02037E90(ctx->fieldSystem, *townMap); //ShowTownMap?
    SetupNativeScript(ctx, FUN_0203BB90);
    return TRUE;
}

BOOL ScrCmd_Unk01D7(ScriptContext *ctx) { //01D7 - TODO: ShowPoffinCaseScreen?
    PoffinCaseAppData **poffinCaseAppData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    u8 unk0 = ScriptReadHalfword(ctx);
    *poffinCaseAppData = FUN_02088960(ctx->fieldSystem, unk0, 11);
    SetupNativeScript(ctx, FUN_0203BB90);
    return TRUE;
}

BOOL ScrCmd_Unk01D8(ScriptContext *ctx) { //01D8
    u16 *unk0 = ScriptGetVarPointer(ctx);
    struct Bag *bag = Save_Bag_Get(ctx->fieldSystem->saveBlock2);
    if (!Bag_PocketNotEmpty(bag, POCKET_BERRIES)) {
        *unk0 = 1;
        return FALSE;
    }
    else if (FUN_020281B8(FUN_02028048(ctx->fieldSystem->saveBlock2)) >= 0x64) {
        *unk0 = 2;
        return FALSE;
    }
    *unk0 = 0;
    return FALSE;
}

BOOL ScrCmd_Unk01D9(ScriptContext *ctx) { //01D9
    u16 unk0 = ScriptGetVar(ctx);
    u16 unk1 = ScriptGetVar(ctx);
    ScrCmdUnkStruct01D9 **unkStructPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    *unkStructPtr = AllocFromHeap(11, sizeof(ScrCmdUnkStruct01D9));
    ScrCmdUnkStruct01D9 *unkStruct = *unkStructPtr;
    MI_CpuFill8(unkStruct, 0, sizeof(ScrCmdUnkStruct01D9)); //consider inlining as is in heartgold
    unkStruct->unk04 = unk0;
    unkStruct->unk06 = unk1;
    unkStruct->save = ctx->fieldSystem->saveBlock2;
    FUN_02037FE4(ctx->fieldSystem, *unkStructPtr);
    SetupNativeScript(ctx, FUN_0203BB90);
    return TRUE;
}

BOOL ScrCmd_ShowPCBoxScreen(ScriptContext *ctx) { //00AB
    PCBoxAppData **pcBoxAppDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA);
    PCBoxAppData *pcBoxAppData = AllocFromHeap(11, sizeof(PCBoxAppData)); //also seems inlined
    pcBoxAppData->save = ctx->fieldSystem->saveBlock2;
    pcBoxAppData->operation = (enum PCBoxOperation)ScriptReadByte(ctx);
    *pcBoxAppDataPtr = pcBoxAppData;
    LaunchStoragePCInterface(ctx->fieldSystem, *pcBoxAppDataPtr);
    SetupNativeScript(ctx, FUN_0203BBBC);
    return TRUE;
}

BOOL ScrCmd_Unk00AC(ScriptContext *ctx) {
    FUN_020383F8(ctx->fieldSystem);
    SetupNativeScript(ctx, FUN_0203BC04);
    return TRUE;
}

BOOL ScrCmd_Unk00AD(ScriptContext *ctx) {
    FUN_02065344(ctx->fieldSystem);
    return TRUE;
}

BOOL ScrCmd_Unk00AE(ScriptContext *ctx) {
    FUN_020383D8(ctx->fieldSystem->taskManager);
    return TRUE;
}

BOOL ScrCmd_Unk00AF(ScriptContext *ctx) {
    void **appData = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_RUNNING_APP_DATA); //todo: define an app type for this
    *appData = FUN_0203842C(ctx->fieldSystem);
    SetupNativeScript(ctx, FUN_0203BB90);
    return TRUE;
}

BOOL ScrCmd_ShowEndGameScreen(ScriptContext *ctx) {
    Task_GameClear(ctx->fieldSystem->taskManager);
    return TRUE;
}
