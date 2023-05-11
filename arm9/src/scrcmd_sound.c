#include "scrcmd.h"
#include "unk_020040F4.h"
#include "sound_chatot.h"

//todo make compatible with the headers

extern BOOL FUN_02005CBC(void);
extern void PlaySound(u16);
extern void FUN_0204AB20(struct FieldSystem *fieldSystem, u16);
extern u16 FUN_0204ABA8(struct FieldSystem *fieldSystem, u32);
extern void FUN_0200521C(u16);
extern void FUN_02005308(u32, u16);
extern void FUN_02005350(u32, u32);
extern void FUN_0200538C(u32, u16, u32);
extern void FUN_020053CC(u16, u16);
extern BOOL FUN_02005404(void);
extern u16 FUN_02005410(u16);
extern void PlaySE(u16);
extern void FUN_020054F0(u16, u32);
extern BOOL FUN_02005508(u16);
extern void FUN_02005578(u16);
extern BOOL FUN_02005670(void);

THUMB_FUNC BOOL ScrCmd_Unk02AE(struct ScriptContext *ctx) //02AE
{
    u16 unk0 = ScriptReadHalfword(ctx);
    u16 *unk1 = ScriptGetVarPointer(ctx);

    *unk1 = FUN_02005410(unk0);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlayBgm(struct ScriptContext *ctx) //0050
{
    FUN_0200521C(ScriptReadHalfword(ctx));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_StopBgm(struct ScriptContext *ctx) //0051
{
    ScriptReadHalfword(ctx);
    u32 unk0 = FUN_02004124();
    FUN_02005350(unk0, 0);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlayDefaultBgm(struct ScriptContext *ctx) //0052
{
    u16 unk0 = FUN_0204ABA8(ctx->fieldSystem, *ctx->fieldSystem->mapId);
    FUN_0200521C(unk0);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0053(struct ScriptContext *ctx) //0053 - todo: SetMusic? SpecialMusic?
{
    FUN_0204AB20(ctx->fieldSystem, ScriptReadHalfword(ctx));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FadeOutBgm(struct ScriptContext *ctx) //0054
{
    u16 unk1 = ScriptReadHalfword(ctx);
    u16 unk2 = ScriptReadHalfword(ctx);

    FUN_020053CC(unk1, unk2);
    SetupNativeScript(ctx, FUN_02041464);

    return TRUE;
}

THUMB_FUNC BOOL FUN_02041464(struct ScriptContext* ctx)
{
#pragma unused(ctx)

    if(!FUN_02005404())
        return TRUE;
    else
        return FALSE;
}

THUMB_FUNC BOOL ScrCmd_FadeInBgm(struct ScriptContext* ctx) //0055
{
    u16 unk = ScriptReadHalfword(ctx);

    FUN_0200538C(0x7F, unk, 0);
    SetupNativeScript(ctx, FUN_02041464);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk0056(struct ScriptContext* ctx) //0056
{

    u8 PtrIndx0 = ScriptReadByte(ctx);

    u8 PtrIndx1 = ScriptReadByte(ctx);

    FUN_020047C8(PtrIndx0, PtrIndx1);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0057(struct ScriptContext* ctx) //0057 - todo: PlayFieldBgm?
{
    FUN_02005308(4, ScriptReadHalfword(ctx));
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0058(struct ScriptContext* ctx) //0058
{
    u8 PtrIndx0 = ScriptReadByte(ctx);
    FUN_020040F4(PtrIndx0);
    return FALSE;
}


THUMB_FUNC BOOL ScrCmd_PlayFanfare(struct ScriptContext* ctx) //0049
{
    u16 sound = ScriptGetVar(ctx);
    PlaySE(sound);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_StopFanfare(struct ScriptContext* ctx) //004A
{
    u16 unk = ScriptGetVar(ctx);
    FUN_020054F0(unk, 0);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlayFanfareWait(struct ScriptContext* ctx) //004B
{
    u16 unk = ScriptGetVar(ctx);

    ctx->data[0] = unk;
    SetupNativeScript(ctx, FUN_02041540);

    return TRUE;
}

THUMB_FUNC BOOL FUN_02041540(struct ScriptContext* ctx)
{
    if(!FUN_02005508((u16)ctx->data[0]))
        return TRUE;
    else
        return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlayCry(struct ScriptContext* ctx) //004C
{
    u16 unk0 = ScriptGetVar(ctx);
    u16 unused = ScriptGetVar(ctx);
    FUN_02005578(unk0);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlayCryWait(struct ScriptContext* ctx) //004D
{
    SetupNativeScript(ctx, FUN_02041598);
    return TRUE;
}

THUMB_FUNC BOOL FUN_02041598(struct ScriptContext* ctx)
{
#pragma unused(ctx)

    if(!FUN_02005670())
        return TRUE;
    else
        return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlaySound(struct ScriptContext* ctx) //004E
{
    u16 bgm_id = ScriptReadHalfword(ctx);
    PlaySound(bgm_id);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_PlaySoundWait(struct ScriptContext* ctx) //004F
{
    SetupNativeScript(ctx, FUN_020415CC);
    return TRUE;
}

THUMB_FUNC BOOL FUN_020415CC(struct ScriptContext* ctx)
{
#pragma unused(ctx)
    if (!FUN_02005CBC())
        return TRUE;
    else
        return FALSE;
}

THUMB_FUNC BOOL ScrCmd_CheckChatotCry(struct ScriptContext* ctx) //0059
{
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    struct SaveChatotSoundClip* chatotSoundClip = Sav2_Chatot_get(ctx->fieldSystem->saveBlock2);
    if (Chatot_checkCry(chatotSoundClip) == 1)
    {
        *ret_ptr = 1;
        return FALSE;
    }
    else
    {
        *ret_ptr = 0;
        return FALSE;
    }
}

THUMB_FUNC BOOL ScrCmd_StartChatotRecord(struct ScriptContext* ctx) //005A
{
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    if (Chatot_startRecording() == 0)
    {
        *ret_ptr = 1;
        return FALSE;
    }
    else
    {
        *ret_ptr = 0;
        return FALSE;
    }
}

THUMB_FUNC BOOL ScrCmd_StopChatotRecord(struct ScriptContext* ctx) //005B
{
#pragma unused(ctx)
    Chatot_stopRecording();
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_SaveChatotCry(struct ScriptContext* ctx) //005C
{
    struct SaveChatotSoundClip* chatotSoundClip = Sav2_Chatot_get(ctx->fieldSystem->saveBlock2);
    Chatot_saveRecording(chatotSoundClip);

    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_Unk005D(struct ScriptContext* ctx) //005D - todo: LoadSpearPillarAudio?
{
#pragma unused(ctx)
    FUN_0200433C(0x3F, 0, 0);
    return TRUE;
}

THUMB_FUNC BOOL ScrCmd_SetVolume(struct ScriptContext* ctx) //0283
{
    u16 unk1 = ScriptGetVar(ctx);
    u16 unk2 = ScriptGetVar(ctx);

    FUN_0200488C(unk1, unk2);

    return FALSE;
}
