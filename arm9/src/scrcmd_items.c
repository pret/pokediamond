#include "scrcmd.h"
#include "bag.h"

extern BOOL FUN_02054CB0(u16 item_id);

THUMB_FUNC BOOL ScrCmd_GiveItem(struct ScriptContext* ctx) //007B
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;

    u16 item_id = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* item_was_added = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(sav_ptr->saveBlock2);

    *item_was_added = (u16)Bag_AddItem(bag, item_id, quantity, 4);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_TakeItem(struct ScriptContext* ctx) //007C
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;

    u16 item_id = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* item_was_taken = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(sav_ptr->saveBlock2);

    *item_was_taken = (u16)Bag_TakeItem(bag, item_id, quantity, 4);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasSpaceForItem(struct ScriptContext* ctx) //007D
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;

    u16 item_id = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* has_space = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(sav_ptr->saveBlock2);

    *has_space = (u16)Bag_HasSpaceForItem(bag, item_id, quantity, 4);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_HasItem(struct ScriptContext* ctx) //007E
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;

    u16 item_id = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16 quantity = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* has_item = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));
    struct Bag* bag = Sav2_Bag_get(sav_ptr->saveBlock2);

    *has_item = (u16)Bag_HasItem(bag, item_id, quantity, 11);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_ItemIdIsTMOrHM(struct ScriptContext* ctx) //007F
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;

    u16 item_id = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* is_tm_or_hm = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

    *is_tm_or_hm = (u16)FUN_02054CB0(item_id);

    return FALSE;
}

THUMB_FUNC BOOL ScrCmd_GetItemPocketId(struct ScriptContext* ctx) //0080
{
    struct UnkSavStruct80* sav_ptr = ctx->unk80;

    u16 item_id = VarGet(ctx->unk80, ScriptReadHalfword(ctx));
    u16* pocket = GetVarPointer(ctx->unk80, ScriptReadHalfword(ctx));

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
