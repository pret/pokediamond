#include "global.h"
#include "scrcmd.h"
#include "unk_02029FB0.h"

extern void* FieldSysGetAttrAddr(struct FieldSystem*, int idx);

extern u8 FUN_0204B5FC(struct FieldSystem*, LocalMapObject *berryTree);
extern void FUN_0204B57C(struct FieldSystem*, LocalMapObject *berryTree, u32 mulchVal);
extern u16 FUN_0204B63C(struct FieldSystem*, LocalMapObject *berryTree);
extern u16 FUN_0204B660(struct FieldSystem*, LocalMapObject *berryTree);
extern u16 FUN_0204B684(struct FieldSystem*, LocalMapObject *berryTree);
extern u16 FUN_0204B6A4(struct FieldSystem*, LocalMapObject *berryTree);
extern void FUN_0204B9CC(struct FieldSystem*);
extern void FUN_0204B5A8(struct FieldSystem*, LocalMapObject *berryTree, u16);
extern void FUN_0204B9A0(struct FieldSystem*);
extern void FUN_0204B4FC(struct FieldSystem*, LocalMapObject *berryTree);

BOOL ScrCmd_GetBerryTreeGrowth(struct ScriptContext* ctx) { //017D
    u16* ret_ptr = ScriptGetVarPointer(ctx);
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);

    *ret_ptr = FUN_0204B5FC(ctx->fieldSystem, *berryTree);

    return FALSE;
}

BOOL ScrCmd_GetBerryTreeType(struct ScriptContext* ctx) { //017E
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    *ret_ptr = FUN_0204B63C(ctx->fieldSystem, *berryTree);

    return FALSE;
}

BOOL ScrCmd_GetBerryTreeMulch(struct ScriptContext* ctx) { //017F
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    *ret_ptr = FUN_0204B660(ctx->fieldSystem, *berryTree);

    return FALSE;
}

BOOL ScrCmd_GetBerryTreeWater(struct ScriptContext* ctx) { //0180
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    *ret_ptr = FUN_0204B684(ctx->fieldSystem, *berryTree);

    return FALSE;
}

BOOL ScrCmd_GetBerryTreeAmount(struct ScriptContext* ctx) { //0181
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u16* ret_ptr = ScriptGetVarPointer(ctx);

    *ret_ptr = FUN_0204B6A4(ctx->fieldSystem, *berryTree);

    return FALSE;
}

BOOL ScrCmd_SetBerryTreeMulch(struct ScriptContext* ctx) { //0182
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    u16 mulchVal = ScriptGetVar(ctx);

    FUN_0204B57C(ctx->fieldSystem, *berryTree, mulchVal);

    return FALSE;
}

BOOL ScrCmd_SetBerryTreeType(struct ScriptContext* ctx) //0183 - todo: PlantBerryTree?
{
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);
    struct GameStats* gameStats = Save_GameStats_Get(ctx->fieldSystem->saveData);
    u16 treeType = ScriptGetVar(ctx);

    FUN_0204B5A8(ctx->fieldSystem, *berryTree, treeType);
    GameStats_Inc(gameStats, 3);

    return FALSE;
}

BOOL ScrCmd_Unk0184(struct ScriptContext* ctx) //0184 - todo: SetBerryTreeWater/WaterBerryTree, or just the animation?
{
    u16 unk = ScriptReadHalfword(ctx);

    switch (unk)
    {
    case 0:
        FUN_0204B9A0(ctx->fieldSystem);
        break;
    case 1:
        FUN_0204B9CC(ctx->fieldSystem);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return TRUE;
}

BOOL ScrCmd_TakeBerryTreeBerries(struct ScriptContext* ctx) //0185
{
    struct GameStats* gameStats = Save_GameStats_Get(ctx->fieldSystem->saveData);
    LocalMapObject **berryTree = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_LAST_INTERACTED);

    FUN_0204B4FC(ctx->fieldSystem, *berryTree);
    GameStats_AddSpecial(gameStats, 0);

    return FALSE;
}
