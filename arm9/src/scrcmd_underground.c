#include "global.h"
#include "scrcmd.h"

extern BOOL sub_02025D6C(void*, u16);
extern BOOL sub_02025D94(void*, u16);
extern BOOL sub_02026298(void*, u16);
extern void* sub_02026CC4(struct SaveData* save);
extern BOOL sub_020260C4(void*, u16, u16);

/* Given the amount of dummy functions in this file, I believe this is a debug file of some kind */

BOOL ScrCmd_GiveSecretBaseDecoration(struct ScriptContext* ctx) //0083
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    u16 unk1 = ScriptGetVar(ctx);
    u16 unused = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    void* unk2 = sub_02026CC4(save);

    *ret_ptr = (u16)sub_02025D6C(unk2, unk1);

    return FALSE;
}

BOOL ScrCmd_TakeSecretBaseDecoration(struct ScriptContext* ctx) //0084
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_HasSpaceForDecoration(struct ScriptContext* ctx) //0085
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    u16 unk1 = ScriptGetVar(ctx);
    u16 unused = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    void* unk2 = sub_02026CC4(save);

    *ret_ptr = (u16)sub_02025D94(unk2, unk1);

    return FALSE;
}

BOOL ScrCmd_GetDecorationCount(struct ScriptContext* ctx) //0086 - somewhat unsure on name, was originally CheckGoods
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_GiveUndergroundTrap(struct ScriptContext* ctx) //0087
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    u16 unk1 = ScriptGetVar(ctx);
    u16 unused = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    void* unk2 = sub_02026CC4(save);

    *ret_ptr = (u16)sub_02026298(unk2, unk1);

    return FALSE;
}

BOOL ScrCmd_TakeUndergroundTrap(struct ScriptContext* ctx) //0088
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_HasSpaceForTrap(struct ScriptContext* ctx) //0089
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_GetTrapCount(struct ScriptContext* ctx) //008A
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_GiveTreasure(struct ScriptContext* ctx) //008B
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    void* unused3 = sub_02026CC4(save);

    return FALSE;
}

BOOL ScrCmd_TakeTreasure(struct ScriptContext* ctx) //008C
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_HasSpaceForTreasure(struct ScriptContext* ctx) //008D
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_GetTreasureCount(struct ScriptContext* ctx) //008E
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_GiveUndergroundSphere(struct ScriptContext* ctx) //008F
{
    struct SaveData* save = ctx->fieldSystem->saveData;
    u16 unk1 = ScriptGetVar(ctx);
    u16 unk2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    void* unk3 = sub_02026CC4(save);

    *ret_ptr = (u16)sub_020260C4(unk3, unk1, unk2);

    return FALSE;
}

BOOL ScrCmd_TakeUndergroundSphere(struct ScriptContext* ctx) //0090
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_HasSpaceForSphere(struct ScriptContext* ctx) //0091
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}

BOOL ScrCmd_GetSphereCount(struct ScriptContext* ctx) //0092
{
    u16 unused1 = ScriptGetVar(ctx);
    u16 unused2 = ScriptGetVar(ctx);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    return FALSE;
}
