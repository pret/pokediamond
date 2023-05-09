#include "scrcmd.h"
#include "bag.h"

extern BOOL FUN_02054CB0(u16 item_id);

THUMB_FUNC BOOL ScrCmd_GiveItem(struct ScriptContext* ctx) //007B
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* item_was_added = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(fieldSystem->saveBlock2);

    *item_was_added = (u16)Bag_AddItem(bag, item_id, quantity, 4);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeItem(struct ScriptContext* ctx) //007C
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* item_was_taken = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(fieldSystem->saveBlock2);

    *item_was_taken = (u16)Bag_TakeItem(bag, item_id, quantity, 4);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasSpaceForItem(struct ScriptContext* ctx) //007D
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* has_space = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(fieldSystem->saveBlock2);

    *has_space = (u16)Bag_HasSpaceForItem(bag, item_id, quantity, 4);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasItem(struct ScriptContext* ctx) //007E
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* has_item = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(fieldSystem->saveBlock2);

    *has_item = (u16)Bag_HasItem(bag, item_id, quantity, 11);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ItemIdIsTMOrHM(struct ScriptContext* ctx) //007F
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* is_tm_or_hm = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

    *is_tm_or_hm = (u16)FUN_02054CB0(item_id);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetItemPocketId(struct ScriptContext* ctx) //0080
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
    u16* pocket = GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));

    *pocket = (u16)GetItemAttr(item_id, ITEMATTR_POCKET, 11);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0081(struct ScriptContext* ctx) //0081 - todo: DummyGiveItem?
{
#pragma unused(ctx)
    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_Unk0082(struct ScriptContext* ctx) //0082 - todo: DummyHasItem?
{
#pragma unused(ctx)
    return FALSE;
}
