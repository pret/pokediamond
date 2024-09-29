#include "global.h"

#include "constants/sndseq.h"

#include "scrcmd.h"
#include "sound_chatot.h"
#include "unk_020040F4.h"
#include "unk_020051F4.h"

// todo make compatible with the headers

extern BOOL sub_02005CBC(void);
extern void FieldSystem_SetSavedMusicId(struct FieldSystem *fieldSystem, u16);
extern u16 sub_0204ABA8(struct FieldSystem *fieldSystem, u32);
extern u16 sub_02005410(u16);
extern BOOL sub_02005670(void);

BOOL ScrCmd_Unk02AE(struct ScriptContext *ctx) // 02AE
{
    u16 unk0  = ScriptReadHalfword(ctx);
    u16 *unk1 = ScriptGetVarPointer(ctx);

    *unk1 = sub_02005410(unk0);

    return FALSE;
}

BOOL ScrCmd_PlayBgm(struct ScriptContext *ctx) // 0050
{
    sub_0200521C(ScriptReadHalfword(ctx));
    return FALSE;
}

BOOL ScrCmd_StopBgm(struct ScriptContext *ctx) // 0051
{
    ScriptReadHalfword(ctx);
    u16 unk0 = sub_02004124();
    sub_02005350(unk0, 0);
    return FALSE;
}

BOOL ScrCmd_PlayDefaultBgm(struct ScriptContext *ctx) // 0052
{
    u16 unk0 = sub_0204ABA8(ctx->fieldSystem, ctx->fieldSystem->location->mapId);
    sub_0200521C(unk0);
    return FALSE;
}

BOOL ScrCmd_Unk0053(struct ScriptContext *ctx) // 0053 - todo: SetMusic? SpecialMusic?
{
    FieldSystem_SetSavedMusicId(ctx->fieldSystem, ScriptReadHalfword(ctx));
    return FALSE;
}

BOOL ScrCmd_FadeOutBgm(struct ScriptContext *ctx) // 0054
{
    u16 unk1 = ScriptReadHalfword(ctx);
    u16 unk2 = ScriptReadHalfword(ctx);

    GF_SndStartFadeOutBGM(unk1, unk2);
    SetupNativeScript(ctx, sub_02041464);

    return TRUE;
}

BOOL sub_02041464(struct ScriptContext *ctx) {
#pragma unused(ctx)

    if (GF_SndGetFadeTimer() == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

BOOL ScrCmd_FadeInBgm(struct ScriptContext *ctx) // 0055
{
    u16 unk = ScriptReadHalfword(ctx);

    sub_0200538C(0x7F, unk, 0);
    SetupNativeScript(ctx, sub_02041464);

    return TRUE;
}

BOOL ScrCmd_Unk0056(struct ScriptContext *ctx) // 0056
{

    u8 PtrIndx0 = ScriptReadByte(ctx);

    u8 PtrIndx1 = ScriptReadByte(ctx);

    sub_020047C8(PtrIndx0, PtrIndx1);
    return FALSE;
}

BOOL ScrCmd_Unk0057(struct ScriptContext *ctx) // 0057 - todo: PlayFieldBgm?
{
    sub_02005308(4, ScriptReadHalfword(ctx));
    return FALSE;
}

BOOL ScrCmd_Unk0058(struct ScriptContext *ctx) // 0058
{
    u8 PtrIndx0 = ScriptReadByte(ctx);
    sub_020040F4(PtrIndx0);
    return FALSE;
}

BOOL ScrCmd_PlayFanfare(struct ScriptContext *ctx) // 0049
{
    u16 sound = ScriptGetVar(ctx);
    PlaySE(sound);
    return FALSE;
}

BOOL ScrCmd_StopFanfare(struct ScriptContext *ctx) // 004A
{
    u16 unk = ScriptGetVar(ctx);
    sub_020054F0(unk, 0);
    return FALSE;
}

BOOL ScrCmd_PlayFanfareWait(struct ScriptContext *ctx) // 004B
{
    u16 unk = ScriptGetVar(ctx);

    ctx->data[0] = unk;
    SetupNativeScript(ctx, sub_02041540);

    return TRUE;
}

BOOL sub_02041540(struct ScriptContext *ctx) {
    if (sub_02005508((u16)ctx->data[0]) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

BOOL ScrCmd_PlayCry(struct ScriptContext *ctx) // 004C
{
    u16 unk0   = ScriptGetVar(ctx);
    u16 unused = ScriptGetVar(ctx);
    sub_02005578(unk0);
    return FALSE;
}

BOOL ScrCmd_PlayCryWait(struct ScriptContext *ctx) // 004D
{
    SetupNativeScript(ctx, sub_02041598);
    return TRUE;
}

BOOL sub_02041598(struct ScriptContext *ctx) {
#pragma unused(ctx)

    if (!sub_02005670()) {
        return TRUE;
    } else {
        return FALSE;
    }
}

BOOL ScrCmd_PlaySound(struct ScriptContext *ctx) // 004E
{
    u16 bgm_id = ScriptReadHalfword(ctx);
    PlaySound(bgm_id);

    return FALSE;
}

BOOL ScrCmd_PlaySoundWait(struct ScriptContext *ctx) // 004F
{
    SetupNativeScript(ctx, sub_020415CC);
    return TRUE;
}

BOOL sub_020415CC(struct ScriptContext *ctx) {
#pragma unused(ctx)
    if (!sub_02005CBC()) {
        return TRUE;
    } else {
        return FALSE;
    }
}

BOOL ScrCmd_CheckChatotCry(struct ScriptContext *ctx) // 0059
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);

    struct SaveChatotSoundClip *chatotSoundClip = Save_Chatot_Get(ctx->fieldSystem->saveData);
    if (Chatot_checkCry(chatotSoundClip) == 1) {
        *ret_ptr = 1;
        return FALSE;
    } else {
        *ret_ptr = 0;
        return FALSE;
    }
}

BOOL ScrCmd_StartChatotRecord(struct ScriptContext *ctx) // 005A
{
    u16 *ret_ptr = ScriptGetVarPointer(ctx);

    if (Chatot_startRecording() == 0) {
        *ret_ptr = 1;
        return FALSE;
    } else {
        *ret_ptr = 0;
        return FALSE;
    }
}

BOOL ScrCmd_StopChatotRecord(struct ScriptContext *ctx) // 005B
{
#pragma unused(ctx)
    Chatot_stopRecording();
    return TRUE;
}

BOOL ScrCmd_SaveChatotCry(struct ScriptContext *ctx) // 005C
{
    struct SaveChatotSoundClip *chatotSoundClip = Save_Chatot_Get(ctx->fieldSystem->saveData);
    Chatot_saveRecording(chatotSoundClip);

    return TRUE;
}

BOOL ScrCmd_Unk005D(struct ScriptContext *ctx) // 005D - todo: LoadSpearPillarAudio?
{
#pragma unused(ctx)
    sub_0200433C(0x3F, SEQ_PV001, 0);
    return TRUE;
}

BOOL ScrCmd_SetVolume(struct ScriptContext *ctx) // 0283
{
    u16 unk1 = ScriptGetVar(ctx);
    u16 unk2 = ScriptGetVar(ctx);

    sub_0200488C(unk1, unk2);

    return FALSE;
}
