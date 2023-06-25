#include "global.h"
#include "scrcmd.h"
#include "bag.h"

extern BOOL sub_02054CB0(u16 item_id);

BOOL ScrCmd_GiveItem(struct ScriptContext* ctx) //007B
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = ScriptGetVar(ctx);
    u16 quantity = ScriptGetVar(ctx);
    u16* item_was_added = ScriptGetVarPointer(ctx);
    struct Bag* bag = Save_Bag_Get(fieldSystem->saveData);

    *item_was_added = (u16)Bag_AddItem(bag, item_id, quantity, HEAP_ID_4);

    return FALSE;
}

BOOL ScrCmd_TakeItem(struct ScriptContext* ctx) //007C
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = ScriptGetVar(ctx);
    u16 quantity = ScriptGetVar(ctx);
    u16* item_was_taken = ScriptGetVarPointer(ctx);
    struct Bag* bag = Save_Bag_Get(fieldSystem->saveData);

    *item_was_taken = (u16)Bag_TakeItem(bag, item_id, quantity, HEAP_ID_4);

    return FALSE;
}

BOOL ScrCmd_HasSpaceForItem(struct ScriptContext* ctx) //007D
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = ScriptGetVar(ctx);
    u16 quantity = ScriptGetVar(ctx);
    u16* has_space = ScriptGetVarPointer(ctx);
    struct Bag* bag = Save_Bag_Get(fieldSystem->saveData);

    *has_space = (u16)Bag_HasSpaceForItem(bag, item_id, quantity, HEAP_ID_4);

    return FALSE;
}

BOOL ScrCmd_HasItem(struct ScriptContext* ctx) //007E
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = ScriptGetVar(ctx);
    u16 quantity = ScriptGetVar(ctx);
    u16* has_item = ScriptGetVarPointer(ctx);
    struct Bag* bag = Save_Bag_Get(fieldSystem->saveData);

    *has_item = (u16)Bag_HasItem(bag, item_id, quantity, HEAP_ID_FIELD);

    return FALSE;
}

BOOL ScrCmd_ItemIdIsTMOrHM(struct ScriptContext* ctx) //007F
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = ScriptGetVar(ctx);
    u16* is_tm_or_hm = ScriptGetVarPointer(ctx);

    *is_tm_or_hm = (u16)sub_02054CB0(item_id);

    return FALSE;
}

BOOL ScrCmd_GetItemPocketId(struct ScriptContext* ctx) //0080
{
    struct FieldSystem *fieldSystem = ctx->fieldSystem;

    u16 item_id = ScriptGetVar(ctx);
    u16* pocket = ScriptGetVarPointer(ctx);

    *pocket = (u16)GetItemAttr(item_id, ITEMATTR_POCKET, HEAP_ID_FIELD);

    return FALSE;
}

BOOL ScrCmd_Unk0081(struct ScriptContext* ctx) //0081 - todo: DummyGiveItem?
{
#pragma unused(ctx)
    return FALSE;
}

BOOL ScrCmd_Unk0082(struct ScriptContext* ctx) //0082 - todo: DummyHasItem?
{
#pragma unused(ctx)
    return FALSE;
}
