#include "scrcmd.h"

extern void* FUN_02029EF8(struct SaveBlock2* sav2);
extern u32 FUN_02005D20(void *);
extern void FUN_02005E6C(void *);
extern void FUN_0200433C(u32, u32, u32);
extern u32 FUN_02005E28(void);
extern void FUN_02005E64(void);
extern BOOL FUN_02005CBC(void);
extern void PlayBGM(u16);
extern u32 FUN_02004124(u16);
extern void FUN_0204AB20(struct UnkSavStruct80 *ctx, u16);
extern u16 FUN_0204ABA8(struct UnkSavStruct80 *ctx, u32);
extern void FUN_0200521C(u16);
extern void FUN_02005308(u32, u16);
extern void FUN_02005350(u32, u32);
extern void FUN_0200538C(u32, u16, u32);
extern void FUN_020053CC(u16, u16);
extern BOOL FUN_02005404(void);
extern u16 FUN_02005410(u16);
extern void FUN_020054C8(u16);
extern void FUN_020054F0(u16, u32);
extern void FUN_020047C8(u8, u8);
extern void FUN_020040F4(u8);
extern BOOL FUN_02005508(u16);
extern void FUN_02005578(u16);
extern BOOL FUN_02005670(void);
extern void FUN_0200488C(u16, u16);


THUMB_FUNC BOOL FUN_020413C0(struct ScriptContext *ctx)
{
    u16 unk0;
    u16 *unk1;

    unk0 = ScriptReadHalfword(ctx);
    unk1 = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    *unk1 = FUN_02005410(unk0);

    return FALSE;
}

THUMB_FUNC BOOL FUN_020413E8(struct ScriptContext *ctx)
{
    FUN_0200521C(ScriptReadHalfword(ctx));
    return FALSE;
}

THUMB_FUNC BOOL FUN_020413F8(struct ScriptContext *ctx)
{
    u32 unk0 = FUN_02004124(ScriptReadHalfword(ctx));
    FUN_02005350(unk0, 0);
    return FALSE;
}

THUMB_FUNC BOOL FUN_0204140C(struct ScriptContext *ctx)
{
    u16 unk0 = FUN_0204ABA8(ctx->unk80, *ctx->unk80->mapId);
    FUN_0200521C(unk0);
    return FALSE;
}

THUMB_FUNC BOOL FUN_02041424(struct ScriptContext *ctx)
{
    FUN_0204AB20(ctx->unk80, ScriptReadHalfword(ctx));
    return FALSE;
}

THUMB_FUNC BOOL FUN_0204143C(struct ScriptContext* ctx)
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

THUMB_FUNC BOOL FUN_02041478(struct ScriptContext* ctx)
{
    u16 unk = ScriptReadHalfword(ctx);

    FUN_0200538C(0x7F, unk, 0);
    SetupNativeScript(ctx, FUN_02041464);

    return TRUE;
}

THUMB_FUNC BOOL FUN_0204149C(struct ScriptContext* ctx)
{

    u8 PtrIndx0 = ScriptReadByte(ctx);

    u8 PtrIndx1 = ScriptReadByte(ctx);

    FUN_020047C8(PtrIndx0, PtrIndx1);
    return FALSE;
}

THUMB_FUNC BOOL FUN_020414B8(struct ScriptContext *ctx)
{
    FUN_02005308(4, ScriptReadHalfword(ctx));
    return FALSE;
}

THUMB_FUNC BOOL FUN_020414CC(struct ScriptContext* ctx)
{
    u8 PtrIndx0 = ScriptReadByte(ctx);
    FUN_020040F4(PtrIndx0);
    return FALSE;
}


THUMB_FUNC BOOL FUN_020414E0(struct ScriptContext* ctx)
{
    u16 unk = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    FUN_020054C8(unk);
    return FALSE;
}

THUMB_FUNC BOOL FUN_020414FC(struct ScriptContext* ctx)
{
    u16 unk = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    FUN_020054F0(unk, 0);
    return FALSE;
}

THUMB_FUNC BOOL FUN_02041518(struct ScriptContext* ctx)
{
    u16 unk = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

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

THUMB_FUNC BOOL FUN_02041558(struct ScriptContext* ctx)
{
    u16 unk0 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    FUN_02005578(unk0);
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_waitcry(struct ScriptContext* ctx)
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

THUMB_FUNC BOOL ScrCmd_playbgm(struct ScriptContext* ctx)
{
    u16 bgm_id = ScriptReadHalfword(ctx);
    PlayBGM(bgm_id);

    return FALSE;
}

THUMB_FUNC BOOL FUN_020415BC(struct ScriptContext* ctx)
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

THUMB_FUNC BOOL FUN_020415E0(struct ScriptContext* ctx)
{
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    void* unk = FUN_02029EF8(ctx->unk80->saveBlock2);
    if (FUN_02005D20(unk) == 1)
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

THUMB_FUNC BOOL FUN_02041618(struct ScriptContext* ctx)
{
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    if (FUN_02005E28() == 0)
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

THUMB_FUNC BOOL FUN_02041644(struct ScriptContext* ctx)
{
#pragma unused(ctx)
    FUN_02005E64();
    return TRUE;
}

THUMB_FUNC BOOL FUN_02041650(struct ScriptContext* ctx)
{
    void* unk = FUN_02029EF8(ctx->unk80->saveBlock2);
    FUN_02005E6C(unk);

    return TRUE;
}

THUMB_FUNC BOOL FUN_02041664(struct ScriptContext* ctx)
{
#pragma unused(ctx)
    FUN_0200433C(0x3F, 0, 0);
    return TRUE;
}

THUMB_FUNC BOOL FUN_02041674(struct ScriptContext* ctx)
{
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));

    FUN_0200488C(unk1, unk2);

    return FALSE;
}

