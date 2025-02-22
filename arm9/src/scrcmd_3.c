#include "global.h"

#include "heap.h"
#include "map_header.h"
#include "party.h"
#include "pokedex.h"
#include "pokemon_storage_system.h"
#include "save_vars_flags.h"
#include "scrcmd.h"
#include "sav_chatot.h"

extern void *FieldSysGetAttrAddr(FieldSystem *fieldSystem, u8 idx);
extern SaveFashionData *Save_FashionData_Get(SaveData *save);

extern void sub_02082140(void *param1, u8 param2);
extern void sub_02082158(void *param1, u8 param2);
extern BOOL sub_0205ED0C(SaveVarsFlags *state);
extern void *sub_02081214(void *param1);
extern void sub_02082630(void *param1, SaveData *save, u32 mapSec, u32 *param4);
extern void sub_020814E8(void *param1);
extern void sub_0208201C(void *param1, u16 param2, MessageFormat *msgFormat, u16 param4);
extern void sub_02082034(void *param1, u16 param2, MessageFormat *msgFormat, u16 param4);
extern void sub_0208206C(void *param1, u16 param2, MessageFormat *msgFormat, u16 param4);
extern void sub_02081DC4(void *param1);
extern void sub_02081EB8(void *param1);
extern void sub_02080E0C(TaskManager *taskManager, void *param2);
extern void sub_02082090(void *param1, MessageFormat *msgFormat, u16 param3);
extern void sub_020820B8(void *param1, MessageFormat *msgFormat, u16 param3);
extern void sub_020820DC(void *param1, MessageFormat *msgFormat, u16 param3);
extern u16 sub_0208213C(void *param1);
extern void sub_0208210C(void *param1, MessageFormat *msgFormat, u16 param3);
extern u16 sub_0208217C(void *param1);
extern u16 sub_02082190(void *param1);
extern u16 sub_020821B4(void *param1);
extern u16 sub_020821C4(void *param1, u16 param2);
extern u16 sub_020821DC(void *param1, u16 param2);
extern u16 sub_020821F0(void *param1);
extern void sub_02082214(void *param1, u16 *param2, u16 *param3, u16 *param4, u16 *param5);
extern u16 sub_02082254(void *param1);
extern void sub_02082284(void *param1, MessageFormat *msgFormat, u16 param3, s32 param4);
extern u16 sub_020822F0(void *param1);
extern void sub_0208223C(void *param1);
extern void sub_0208224C(void *param1);
extern void sub_02082444(void *param1, u16 param2);
extern BOOL sub_02082508(void *param1);

extern void ov05_021F4608(u32 param1);
extern void ov05_021F45E8(u32 param1);

extern void sub_020825A0(void *param1, u32 *param2, u32 *param3, u32 *param4, u32 *param5, u32 *param6);

extern void ov06_0224D3E8(TaskManager *taskManager);

static BOOL sub_0203FEF4(ScriptContext *ctx);
static BOOL sub_020401F0(ScriptContext *ctx);
static BOOL sub_02040618(ScriptContext *ctx);


BOOL ScrCmd_Unk00F8(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02082140(*miscDataPtr, ScriptGetVar(ctx));

    return FALSE;
}

BOOL ScrCmd_Unk00F9(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    ctx->data[0] = ScriptGetVar(ctx);

    SetupNativeScript(ctx, sub_0203FEF4);

    return TRUE;
}

static BOOL sub_0203FEF4(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02082158(*miscDataPtr, ctx->data[0]);
}

BOOL ScrCmd_Unk00FA(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    PlayerProfile *player = Save_PlayerData_GetProfile(FieldSystem_GetSaveData(ctx->fieldSystem));
    u32 var1 = ScriptGetVar(ctx);
    u32 var2 = ScriptGetVar(ctx);
    u32 var3 = ScriptGetVar(ctx);
    u32 monSlot = ScriptGetVar(ctx);
    Pokemon *pokemon = Party_GetMonByIndex(SaveArray_Party_Get(ctx->fieldSystem->saveData), monSlot);
    String *str = PlayerProfile_GetPlayerName_NewString(player, HEAP_ID_4);
    UnkStruct_Scrcmd3 unk;

    unk.unk0 = var2;
    unk.unk1 = var1;
    unk.unk2 = var3;

    unk.unk3 = sub_0205ED0C(Save_VarsFlags_Get(ctx->fieldSystem->saveData));

    unk.nationalDexFlag = Pokedex_GetNatDexFlag(Save_Pokedex_Get(ctx->fieldSystem->saveData));
    unk.monSlot = monSlot;

    unk.pokemon = pokemon;
    unk.playerName = str;
    unk.profile = player;

    unk.saveFashionData = Save_FashionData_Get(ctx->fieldSystem->saveData);
    unk.options = Save_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveData);
    unk.saveData = ctx->fieldSystem->saveData;
    unk.chatotSoundClip = Save_Chatot_Get(ctx->fieldSystem->saveData);

    *miscDataPtr = sub_02081214(&unk);

    String_Delete(str);

    return FALSE;
}

BOOL ScrCmd_Unk00FB(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var = ScriptGetVar(ctx);
    u32 sec = MapHeader_GetMapSec(ctx->fieldSystem->location->mapId);
    SaveData *saveData = ctx->fieldSystem->saveData;

    sub_02082630(*miscDataPtr, saveData, sec, ctx->fieldSystem->unk98);

    sub_020814E8(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk00FC(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var1 = ScriptGetVar(ctx);
    u16 var2 = ScriptGetVar(ctx);

    sub_0208201C(*miscDataPtr, var1, *msgFormat, var2);

    return FALSE;
}

BOOL ScrCmd_Unk00FD(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var1 = ScriptGetVar(ctx);
    u16 var2 = ScriptGetVar(ctx);

    sub_02082034(*miscDataPtr, var1, *msgFormat, var2);

    return FALSE;
}

BOOL ScrCmd_Unk00FE(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var1 = ScriptGetVar(ctx);
    u16 var2 = ScriptGetVar(ctx);

    sub_0208206C(*miscDataPtr, var1, *msgFormat, var2);

    return FALSE;
}

BOOL ScrCmd_Unk00FF(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 num = ScriptGetVar(ctx);
    u16 idx = ScriptGetVar(ctx);

    BufferIntegerAsString(*msgFormat, idx, num, 1, PRINTING_MODE_LEFT_ALIGN, TRUE);

    return FALSE;
}

BOOL ScrCmd_Unk0100(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02081DC4(*miscDataPtr);

    SetupNativeScript(ctx, sub_020401F0);

    return TRUE;
}

static BOOL sub_020401F0(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02081EB8(*miscDataPtr);
}

BOOL ScrCmd_Unk0101(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02080E0C(ctx->taskManager, *miscDataPtr);

    return TRUE;
}

BOOL ScrCmd_Unk0102(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_02082090(*miscDataPtr, *msgFormat, var);

    return FALSE;
}

BOOL ScrCmd_Unk0103(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_020820B8(*miscDataPtr, *msgFormat, var);

    return FALSE;
}

BOOL ScrCmd_Unk0104(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_020820DC(*miscDataPtr, *msgFormat, var);

    return FALSE;
}

BOOL ScrCmd_Unk0105(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_0208213C(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk0106(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_0208210C(*miscDataPtr, *msgFormat, var);

    return FALSE;
}

BOOL ScrCmd_Unk0107(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_0208217C(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk0108(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_02082190(*miscDataPtr);

    return FALSE;
}
BOOL ScrCmd_Unk0109(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_020821B4(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk010A(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var1 = ScriptGetVar(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);

    *var2 = sub_020821C4(*miscDataPtr, var1);

    return FALSE;
}

BOOL ScrCmd_Unk010B(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var1 = ScriptGetVar(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);

    *var2 = sub_020821DC(*miscDataPtr, var1);

    return FALSE;
}

BOOL ScrCmd_Unk010C(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_020821F0(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk0110(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var1 = ScriptGetVarPointer(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);
    u16 *var3 = ScriptGetVarPointer(ctx);
    u16 *var4 = ScriptGetVarPointer(ctx);

    sub_02082214(*miscDataPtr, var1, var2, var3, var4);

    return FALSE;
}

BOOL ScrCmd_Unk010D(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_02082254(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk010E(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msgFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_02082284(*miscDataPtr, *msgFormat, var, 11);

    return FALSE;
}

BOOL ScrCmd_Unk010F(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_020822F0(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk0117(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_0208223C(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk0118(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_0208224C(*miscDataPtr);

    return FALSE;
}

BOOL ScrCmd_Unk0111(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var = ScriptGetVar(ctx);

    sub_02082444(*miscDataPtr, var);

    return FALSE;
}

BOOL ScrCmd_Unk0112(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    SetupNativeScript(ctx, sub_02040618);

    return TRUE;
}

static BOOL sub_02040618(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    return sub_02082508(*miscDataPtr) == TRUE;
}

BOOL ScrCmd_Unk0113(ScriptContext *ctx) {
    ov05_021F4608(ctx->fieldSystem->unk04->unk1C);

    return FALSE;
}

BOOL ScrCmd_Unk0114(ScriptContext *ctx) {
    ov05_021F45E8(ctx->fieldSystem->unk04->unk1C);

    return FALSE;
}

BOOL ScrCmd_Unk0115(ScriptContext *ctx) {
    void **miscDataPtr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);
    u32 temp;
    u32 t1;
    u32 t2;
    u32 t3;
    u32 t4;

    sub_020825A0(*miscDataPtr, &temp, &t1, &t2, &t3, &t4);

    if (t1 == 1 || t2 == 1 || t3 == 1 || t4 == 1) {
        *var = 1;
    } else {
        *var = 0;
    }

    return FALSE;
}

BOOL ScrCmd_Unk0116(ScriptContext *ctx) {
    ov06_0224D3E8(ctx->taskManager);

    return TRUE;
}
