#include "global.h"
#include "bag_view.h"
#include "coins.h"
#include "constants/items.h"
#include "constants/seal_constants.h"
#include "fashion_case.h"
#include "heap.h"
#include "message_format.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0007.h"
#include "msgdata/msg/narc_0199.h"
#include "player_data.h"
#include "seal.h"
#include "unk_0202A1E0.h"

extern u32 *FUN_0202708C(SaveFashionData *);
extern u32 FUN_02027168(u32 *);
extern u16 FUN_02027184(u32 *);
extern SaveFashionData *Save_FashionData_Get(struct SaveData *save);
extern u8 SealCase_CountSealOccurrenceAnywhere(struct SealCase *, u32);

static u32 GetCoinCount(struct SaveData *save);
static u32 GetSealCount(struct SaveData *save);

struct BagView *BagView_New(u8 heap_id)
{
    struct BagView *ptr = AllocFromHeap(heap_id, sizeof(struct BagView));

    memset(ptr, 0, sizeof(struct BagView));

    return ptr;
}

u32 BagView_sizeof()
{
    return sizeof(struct BagView);
}

void FUN_0206E30C(struct BagView *bag_view, u8 r1)
{
    bag_view->unk65 = r1;
}

void FUN_0206E314(
    struct BagView *bag_view, struct SaveData *save, u8 r2, struct UnkStruct_0206F164 *r3)
{
    FUN_0206E30C(bag_view, r2);

    bag_view->save = save;
    bag_view->unk6C = r3;
    bag_view->unk66 = 0;
}

void BagView_SetItem(struct BagView *bag_view, struct ItemSlot *slot, u8 pocket, u8 idx)
{
    bag_view->slots[idx].slot = slot;
    bag_view->slots[idx].pocket = pocket;
}

void FUN_0206E340(struct BagView *bag_view)
{
    bag_view->unk76 = 1;
}

void FUN_0206E354(struct BagView *bag_view, u32 r1)
{
    bag_view->unk70 = r1;
}

void FUN_0206E358(struct BagView *bag_view, u8 r1)
{
    bag_view->unk74 = r1;
}

void FUN_0206E360(struct BagView *bag_view, u16 r1)
{
    bag_view->unk76_2 = r1;
}

u16 FUN_0206E37C(struct BagView *bag_view)
{
    return bag_view->unk66;
}

u16 FUN_0206E384(struct BagView *bag_view)
{
    return bag_view->unk68;
}

u8 FUN_0206E38C(struct BagView *bag_view)
{
    return bag_view->unk74;
}

u8 FUN_0206E394(struct BagView *bag_view)
{
    return bag_view->unk75;
}

static u32 GetCoinCount(struct SaveData *save)
{
    return (u32)CheckCoins(Save_PlayerData_GetCoinsAddr(save));
}

static u32 GetSealCount(struct SaveData *save)
{
    struct SealCase *seal_case = Save_SealCase_Get(save);
    u32 i;
    u32 count = 0;

    for (i = SEAL_MIN; i <= SEAL_MAX; ++i)
    {
        count += SealCase_CountSealOccurrenceAnywhere(seal_case, i);
    }

    return count;
}

//todo: do these match up with HG?
u32 FUN_0206E3C8(struct SaveData *save)
{
    return FUN_02027168(FUN_0202708C(Save_FashionData_Get(save)));
}

u32 FUN_0206E3D8(struct SaveData *save)
{
    return FUN_02027184(FUN_0202708C(Save_FashionData_Get(save)));
}

u32 FUN_0206E3E8(struct SaveData *save)
{
    return SaveStruct23_Substruct2_SetField_0x0(SaveStruct23_GetSubstruct2(save), 0, DATA_GET);
}

BOOL TryFormatRegisteredKeyItemUseMessage(struct SaveData *save, struct String *dest, u32 item_id, u32 heap_id)
{
    struct MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_MSGDATA_MSG, NARC_msg_narc_0007_bin, heap_id);
    MessageFormat *messageFormat = MessageFormat_New(heap_id);
    struct String *string;

    if (item_id == ITEM_NONE)
    {
        string = NewString_ReadMsgData(msgData, narc_0007_00099); // A Key Item in the Bag can be assigned to this button for instant use.
    }
    else if (item_id == ITEM_POINT_CARD)
    {
        string = NewString_ReadMsgData(msgData, narc_0007_00097); // Saved Battle Points {STRVAR_1 53, 0}BP

        BufferIntegerAsString(messageFormat, 0, FUN_0206E3E8(save), 4, PRINTING_MODE_LEFT_ALIGN, TRUE);
    }
    else if (item_id == ITEM_SEAL_CASE)
    {
        string = NewString_ReadMsgData(msgData, narc_0007_00092); // Seals: {STRVAR_1 53, 0}

        BufferIntegerAsString(messageFormat, 0, GetSealCount(save), 4, PRINTING_MODE_LEFT_ALIGN, TRUE);
    }
    else if (item_id == ITEM_FASHION_CASE)
    {
        string = NewString_ReadMsgData(msgData, narc_0007_00093); // Accessories: {STRVAR_1 52, 0} Backdrops: {STRVAR_1 51, 1}

        BufferIntegerAsString(messageFormat, 0, FUN_0206E3C8(save), 3, PRINTING_MODE_LEFT_ALIGN, TRUE);
        BufferIntegerAsString(messageFormat, 1, FUN_0206E3D8(save), 2, PRINTING_MODE_LEFT_ALIGN, TRUE);
    }
    else if (item_id == ITEM_COIN_CASE)
    {
        string = NewString_ReadMsgData(msgData, narc_0007_00057); // Your Coins: {STRVAR_1 54, 0}

        BufferIntegerAsString(messageFormat, 0, GetCoinCount(save), 5, PRINTING_MODE_LEFT_ALIGN, TRUE);
    }
    else
    {
        MessageFormat_Delete(messageFormat);
        DestroyMsgData(msgData);

        return FALSE;
    }

    StringExpandPlaceholders(messageFormat, dest, string);
    String_Delete(string);
    MessageFormat_Delete(messageFormat);
    DestroyMsgData(msgData);

    return TRUE;
}

void FUN_0206E51C( //todo: sync with HG
    struct PlayerData *playerData, struct String *dest, u32 r2, u32 r3, u32 heap_id)
{
#pragma unused(r2)
    struct MsgData *msgData;

    switch (r3)
    {
    case 1:
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0007_bin, heap_id);

        ReadMsgDataIntoString(msgData, narc_0007_00056, dest); // You can’t dismount your Bike here.
        DestroyMsgData(msgData);
        return;
    case 2:
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0007_bin, heap_id);

        ReadMsgDataIntoString(msgData, narc_0007_00111, dest); // It can’t be used when you have someone with you.
        DestroyMsgData(msgData);
        return;
    default:
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0199_bin, heap_id);
        MessageFormat *messageFormat = MessageFormat_New(heap_id);
        struct String *src = NewString_ReadMsgData(msgData, narc_0199_00036); // Rowan’s words echoed... {STRVAR_1 3, 0}! There’s a time and place for everything! But not now.

        BufferPlayersName(messageFormat, 0, playerData);
        StringExpandPlaceholders(messageFormat, dest, src);
        String_Delete(src);
        MessageFormat_Delete(messageFormat);
        DestroyMsgData(msgData);
        return;
    }
}
