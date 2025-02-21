#include "global.h"

#include "heap.h"
#include "map_header.h"
#include "party.h"
#include "pokedex.h"
#include "pokemon_storage_system.h"
#include "save_vars_flags.h"
#include "scrcmd.h"

extern void *FieldSysGetAttrAddr(struct FieldSystem *, u8 idx);
extern SaveFashionData *Save_FashionData_Get(SaveData *save);

extern void sub_02082140(void *, u8);
extern void sub_02082158(void *, u8);
extern BOOL sub_0205ED0C(struct SaveVarsFlags *state);
extern void *sub_02081214(void *);
extern void sub_02082630(void *, SaveData *, u32, u32 *);
extern void sub_020814E8(void *);
extern void sub_0208201C(void *, u16, MessageFormat *, u16);
extern void sub_02082034(void *, u16, MessageFormat *, u16);
extern void sub_0208206C(void *, u16, MessageFormat *, u16);
extern void sub_02081DC4(void *);
extern void sub_02081EB8(void *);
extern void sub_02080E0C(TaskManager *, void *);
extern void sub_02082090(void *, MessageFormat *, u16);
extern void sub_020820B8(void *, MessageFormat *, u16);
extern void sub_020820DC(void *, MessageFormat *, u16);
extern u16 sub_0208213C(void *);
extern void sub_0208210C(void *, void *, u16);
extern u16 sub_0208217C(void *);
extern u16 sub_02082190(void *);
extern u16 sub_020821B4(void *);
extern u16 sub_020821C4(void *, u16);
extern u16 sub_020821DC(void *, u16);
extern u16 sub_020821F0(void *);
extern void sub_02082214(void *, u16 *, u16 *, u16 *, u16 *);
extern u16 sub_02082254(void *);
extern void sub_02082284(void *, MessageFormat *, u16, s32);
extern u16 sub_020822F0(void *);
extern void sub_0208223C(void *);
extern void sub_0208224C(void *);
extern void sub_02082444(void *, u16);
extern BOOL sub_02082508(void *);

extern void ov05_021F4608(u32);
extern void ov05_021F45E8(u32);

extern void sub_020825A0(void *, u32 *, u32 *, u32 *, u32 *, u32 *);

extern void ov06_0224D3E8(TaskManager *);

typedef struct unk_scrcmd_3 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 nationalDexFlag;
    u8 monSlot;
    u8 unk6;
    Pokemon *pokemon;
    String *playerName;
    PlayerProfile *profile;
    SaveFashionData *saveFashionData;
    Options *options;
    struct SaveData *saveData;
    struct SaveChatotSoundClip *chatotSoundClip;
} unk_scrcmd_3;

BOOL ScrCmd_Unk00F8(struct ScriptContext *ctx);
BOOL ScrCmd_Unk00F9(struct ScriptContext *ctx);
BOOL sub_0203FEF4(struct ScriptContext *ctx);
BOOL ScrCmd_Unk00FA(struct ScriptContext *ctx);
BOOL ScrCmd_Unk00FB(struct ScriptContext *ctx);
BOOL ScrCmd_Unk00FC(struct ScriptContext *ctx);
BOOL ScrCmd_Unk00FD(struct ScriptContext *ctx);
BOOL ScrCmd_Unk00FE(struct ScriptContext *ctx);
BOOL ScrCmd_Unk00FF(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0100(struct ScriptContext *ctx);
BOOL sub_020401F0(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0101(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0102(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0103(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0104(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0105(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0106(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0107(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0108(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0109(struct ScriptContext *ctx);
BOOL ScrCmd_Unk010A(struct ScriptContext *ctx);
BOOL ScrCmd_Unk010B(struct ScriptContext *ctx);
BOOL ScrCmd_Unk010C(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0110(struct ScriptContext *ctx);
BOOL ScrCmd_Unk010D(struct ScriptContext *ctx);
BOOL ScrCmd_Unk010E(struct ScriptContext *ctx);
BOOL ScrCmd_Unk010F(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0117(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0118(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0111(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0112(struct ScriptContext *ctx);
BOOL sub_02040618(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0113(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0114(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0115(struct ScriptContext *ctx);
BOOL ScrCmd_Unk0116(struct ScriptContext *ctx);

BOOL ScrCmd_Unk00F8(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02082140(*misc_data_ptr, ScriptGetVar(ctx));

    return FALSE;
}

BOOL ScrCmd_Unk00F9(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    ctx->data[0] = ScriptGetVar(ctx);

    SetupNativeScript(ctx, sub_0203FEF4);

    return TRUE;
}

BOOL sub_0203FEF4(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02082158(*misc_data_ptr, ctx->data[0]);
}

BOOL ScrCmd_Unk00FA(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    PlayerProfile *player = Save_PlayerData_GetProfile(FieldSystem_GetSaveData(ctx->fieldSystem));
    u32 var1 = ScriptGetVar(ctx);
    u32 var2 = ScriptGetVar(ctx);
    u32 var3 = ScriptGetVar(ctx);
    u32 mon_slot = ScriptGetVar(ctx);
    Pokemon *pokemon = Party_GetMonByIndex(SaveArray_Party_Get(ctx->fieldSystem->saveData), mon_slot);
    String *str = PlayerProfile_GetPlayerName_NewString(player, HEAP_ID_4);
    unk_scrcmd_3 unk;

    unk.unk0 = var2;
    unk.unk1 = var1;
    unk.unk2 = var3;

    unk.unk3 = sub_0205ED0C(Save_VarsFlags_Get(ctx->fieldSystem->saveData));

    unk.nationalDexFlag = Pokedex_GetNatDexFlag(Save_Pokedex_Get(ctx->fieldSystem->saveData));
    unk.monSlot = mon_slot;

    unk.pokemon = pokemon;
    unk.playerName = str;
    unk.profile = player;

    unk.saveFashionData = Save_FashionData_Get(ctx->fieldSystem->saveData);
    unk.options = Save_PlayerData_GetOptionsAddr(ctx->fieldSystem->saveData);
    unk.saveData = ctx->fieldSystem->saveData;
    unk.chatotSoundClip = Save_Chatot_Get(ctx->fieldSystem->saveData);

    *misc_data_ptr = sub_02081214(&unk);

    String_Delete(str);

    return FALSE;
}

BOOL ScrCmd_Unk00FB(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var = ScriptGetVar(ctx);
    u32 sec = MapHeader_GetMapSec(ctx->fieldSystem->location->mapId);
    SaveData *save_data = ctx->fieldSystem->saveData;

    sub_02082630(*misc_data_ptr, save_data, sec, ctx->fieldSystem->unk98);

    sub_020814E8(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk00FC(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var1 = ScriptGetVar(ctx);
    u16 var2 = ScriptGetVar(ctx);

    sub_0208201C(*misc_data_ptr, var1, *msg_format, var2);

    return FALSE;
}

BOOL ScrCmd_Unk00FD(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var1 = ScriptGetVar(ctx);
    u16 var2 = ScriptGetVar(ctx);

    sub_02082034(*misc_data_ptr, var1, *msg_format, var2);

    return FALSE;
}

BOOL ScrCmd_Unk00FE(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var1 = ScriptGetVar(ctx);
    u16 var2 = ScriptGetVar(ctx);

    sub_0208206C(*misc_data_ptr, var1, *msg_format, var2);

    return FALSE;
}

BOOL ScrCmd_Unk00FF(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 num = ScriptGetVar(ctx);
    u16 idx = ScriptGetVar(ctx);

    BufferIntegerAsString(*msg_format, idx, num, 1, PRINTING_MODE_LEFT_ALIGN, TRUE);

    return FALSE;
}

BOOL ScrCmd_Unk0100(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02081DC4(*misc_data_ptr);

    SetupNativeScript(ctx, sub_020401F0);

    return TRUE;
}

BOOL sub_020401F0(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02081EB8(*misc_data_ptr);
}

BOOL ScrCmd_Unk0101(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_02080E0C(ctx->taskManager, *misc_data_ptr);

    return TRUE;
}

BOOL ScrCmd_Unk0102(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_02082090(*misc_data_ptr, *msg_format, var);

    return FALSE;
}

BOOL ScrCmd_Unk0103(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_020820B8(*misc_data_ptr, *msg_format, var);

    return FALSE;
}

BOOL ScrCmd_Unk0104(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_020820DC(*misc_data_ptr, *msg_format, var);

    return FALSE;
}

BOOL ScrCmd_Unk0105(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_0208213C(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk0106(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_0208210C(*misc_data_ptr, *msg_format, var);

    return FALSE;
}

BOOL ScrCmd_Unk0107(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_0208217C(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk0108(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_02082190(*misc_data_ptr);

    return FALSE;
}
BOOL ScrCmd_Unk0109(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_020821B4(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk010A(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var1 = ScriptGetVar(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);

    *var2 = sub_020821C4(*misc_data_ptr, var1);

    return FALSE;
}

BOOL ScrCmd_Unk010B(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var1 = ScriptGetVar(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);

    *var2 = sub_020821DC(*misc_data_ptr, var1);

    return FALSE;
}

BOOL ScrCmd_Unk010C(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_020821F0(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk0110(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var1 = ScriptGetVarPointer(ctx);
    u16 *var2 = ScriptGetVarPointer(ctx);
    u16 *var3 = ScriptGetVarPointer(ctx);
    u16 *var4 = ScriptGetVarPointer(ctx);

    sub_02082214(*misc_data_ptr, var1, var2, var3, var4);

    return FALSE;
}

BOOL ScrCmd_Unk010D(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_02082254(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk010E(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    MessageFormat **msg_format = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
    u16 var = ScriptGetVar(ctx);

    sub_02082284(*misc_data_ptr, *msg_format, var, 11);

    return FALSE;
}

BOOL ScrCmd_Unk010F(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);

    *var = sub_020822F0(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk0117(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_0208223C(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk0118(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    sub_0208224C(*misc_data_ptr);

    return FALSE;
}

BOOL ScrCmd_Unk0111(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 var = ScriptGetVar(ctx);

    sub_02082444(*misc_data_ptr, var);

    return FALSE;
}

BOOL ScrCmd_Unk0112(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    SetupNativeScript(ctx, sub_02040618);

    return TRUE;
}

BOOL sub_02040618(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);

    return sub_02082508(*misc_data_ptr) == TRUE ? TRUE : FALSE;
}

BOOL ScrCmd_Unk0113(struct ScriptContext *ctx) {
    ov05_021F4608(ctx->fieldSystem->unk04->unk1C);

    return FALSE;
}

BOOL ScrCmd_Unk0114(struct ScriptContext *ctx) {
    ov05_021F45E8(ctx->fieldSystem->unk04->unk1C);

    return FALSE;
}

BOOL ScrCmd_Unk0115(struct ScriptContext *ctx) {
    void **misc_data_ptr = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MISC_DATA_PTR);
    u16 *var = ScriptGetVarPointer(ctx);
    u32 temp;
    u32 t1;
    u32 t2;
    u32 t3;
    u32 t4;

    sub_020825A0(*misc_data_ptr, &temp, &t1, &t2, &t3, &t4);

    if (t1 == 1 || t2 == 1 || t3 == 1 || t4 == 1) {
        *var = 1;
    } else {
        *var = 0;
    }

    return FALSE;
}

BOOL ScrCmd_Unk0116(struct ScriptContext *ctx) {
    ov06_0224D3E8(ctx->taskManager);

    return TRUE;
}
