#include "scrcmd.h"

extern BOOL FUN_02025D6C(void*, u16);
extern BOOL FUN_02025D94(void*, u16);
extern BOOL FUN_02026298(void*, u16);
extern void* FUN_02026CC4(struct SaveBlock2* sav2);
extern BOOL FUN_020260C4(void*, u16, u16);

THUMB_FUNC BOOL ScrCmd_Unk0083(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk2 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_02025D6C(unk2, unk1);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0084(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0085(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk2 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_02025D94(unk2, unk1);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0086(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0087(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk2 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_02026298(unk2, unk1);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0088(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0089(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk008A(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk008B(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unused3 = FUN_02026CC4(sav2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk008C(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk008D(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk008E(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk008F(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk3 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_020260C4(unk3, unk1, unk2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0090(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0091(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0092(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}
