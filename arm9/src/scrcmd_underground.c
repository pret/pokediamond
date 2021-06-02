#include "scrcmd.h"

extern BOOL FUN_02025D6C(void*, u16);
extern BOOL FUN_02025D94(void*, u16);
extern BOOL FUN_02026298(void*, u16);
extern void* FUN_02026CC4(struct SaveBlock2* sav2);
extern BOOL FUN_020260C4(void*, u16, u16);

THUMB_FUNC BOOL ScrCmd_GiveSecretBaseDecoration(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk2 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_02025D6C(unk2, unk1);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeSecretBaseDecoration(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasSpaceForDecoration(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk2 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_02025D94(unk2, unk1);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetDecorationCount(struct ScriptContext* ctx) //somewhat unsure on name, was originally CheckGoods
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveUndergroundTrap(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk2 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_02026298(unk2, unk1);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeUndergroundTrap(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasSpaceForTrap(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetTrapCount(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveTreasure(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unused3 = FUN_02026CC4(sav2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeTreasure(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasSpaceForTreasure(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetTreasureCount(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GiveUndergroundSphere(struct ScriptContext* ctx)
{
    struct SaveBlock2* sav2 = ctx->unk80->saveBlock2;
    u16 unk1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unk2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    void* unk3 = FUN_02026CC4(sav2);

    *ret_ptr = (u16)FUN_020260C4(unk3, unk1, unk2);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeUndergroundSphere(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasSpaceForSphere(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetSphereCount(struct ScriptContext* ctx)
{
    u16 unused1 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 unused2 = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* ret_ptr = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    return FALSE;
}
