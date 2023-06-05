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
#include "player_data.h"
#include "seal.h"
#include "unk_0202A1E0.h"

extern u32 *FUN_0202708C(SaveFashionData *);
extern u32 FUN_02027168(u32 *);
extern u16 FUN_02027184(u32 *);
extern SaveFashionData *Save_FashionData_Get(struct SaveBlock2 *sav2);
extern u8 SealCase_CountSealOccurrenceAnywhere(struct SealCase *, u32);

static u32 GetCoinCount(struct SaveBlock2 *sav2);
static u32 GetSealCount(struct SaveBlock2 *sav2);

THUMB_FUNC struct BagView *BagView_New(u8 heap_id)
{
    struct BagView *ptr = AllocFromHeap(heap_id, sizeof(struct BagView));

    memset(ptr, 0, sizeof(struct BagView));

    return ptr;
}

THUMB_FUNC u32 BagView_sizeof()
{
    return sizeof(struct BagView);
}

THUMB_FUNC void FUN_0206E30C(struct BagView *bag_view, u8 r1)
{
    bag_view->unk65 = r1;
}

THUMB_FUNC void FUN_0206E314(
    struct BagView *bag_view, struct SaveBlock2 *sav2, u8 r2, struct UnkStruct_0206F164 *r3)
{
    FUN_0206E30C(bag_view, r2);

    bag_view->sav2 = sav2;
    bag_view->unk6C = r3;
    bag_view->unk66 = 0;
}

THUMB_FUNC void BagView_SetItem(struct BagView *bag_view, struct ItemSlot *slot, u8 pocket, u8 idx)
{
    bag_view->slots[idx].slot = slot;
    bag_view->slots[idx].pocket = pocket;
}

THUMB_FUNC void FUN_0206E340(struct BagView *bag_view)
{
    bag_view->unk76 = 1;
}

THUMB_FUNC void FUN_0206E354(struct BagView *bag_view, u32 r1)
{
    bag_view->unk70 = r1;
}

THUMB_FUNC void FUN_0206E358(struct BagView *bag_view, u8 r1)
{
    bag_view->unk74 = r1;
}

THUMB_FUNC void FUN_0206E360(struct BagView *bag_view, u16 r1)
{
    bag_view->unk76_2 = r1;
}

THUMB_FUNC u16 FUN_0206E37C(struct BagView *bag_view)
{
    return bag_view->unk66;
}

THUMB_FUNC u16 FUN_0206E384(struct BagView *bag_view)
{
    return bag_view->unk68;
}

THUMB_FUNC u8 FUN_0206E38C(struct BagView *bag_view)
{
    return bag_view->unk74;
}

THUMB_FUNC u8 FUN_0206E394(struct BagView *bag_view)
{
    return bag_view->unk75;
}

THUMB_FUNC static u32 GetCoinCount(struct SaveBlock2 *sav2)
{
    return (u32)CheckCoins(Save_PlayerData_GetCoinsAddr(sav2));
}

THUMB_FUNC static u32 GetSealCount(struct SaveBlock2 *sav2)
{
    struct SealCase *seal_case = Save_SealCase_Get(sav2);
    u32 i;
    u32 count = 0;

    for (i = SEAL_MIN; i <= SEAL_MAX; ++i)
    {
        count += SealCase_CountSealOccurrenceAnywhere(seal_case, i);
    }

    return count;
}

//todo: do these match up with HG?
THUMB_FUNC u32 FUN_0206E3C8(struct SaveBlock2 *sav2)
{
    return FUN_02027168(FUN_0202708C(Save_FashionData_Get(sav2)));
}

THUMB_FUNC u32 FUN_0206E3D8(struct SaveBlock2 *sav2)
{
    return FUN_02027184(FUN_0202708C(Save_FashionData_Get(sav2)));
}

THUMB_FUNC u32 FUN_0206E3E8(struct SaveBlock2 *sav2)
{
    return SaveStruct23_Substruct2_SetField_0x0(SaveStruct23_GetSubstruct2(sav2), 0, DATA_GET);
}

THUMB_FUNC BOOL TryFormatRegisteredKeyItemUseMessage(struct SaveBlock2 *sav2, struct String *dest, u32 item_id, u32 heap_id)
{
    struct MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_MSGDATA_MSG, NARC_msg_narc_0007_bin, heap_id);
    MessageFormat *messageFormat = MessageFormat_New(heap_id);
    struct String *string;

    if (item_id == ITEM_NONE)
    {
        string = NewString_ReadMsgData(msgData, 0x63);
    }
    else if (item_id == ITEM_POINT_CARD)
    {
        string = NewString_ReadMsgData(msgData, 0x61);

        BufferIntegerAsString(messageFormat, 0, FUN_0206E3E8(sav2), 4, PRINTING_MODE_LEFT_ALIGN, TRUE);
    }
    else if (item_id == ITEM_SEAL_CASE)
    {
        string = NewString_ReadMsgData(msgData, 0x5C);

        BufferIntegerAsString(messageFormat, 0, GetSealCount(sav2), 4, PRINTING_MODE_LEFT_ALIGN, TRUE);
    }
    else if (item_id == ITEM_FASHION_CASE)
    {
        string = NewString_ReadMsgData(msgData, 0x5D);

        BufferIntegerAsString(messageFormat, 0, FUN_0206E3C8(sav2), 3, PRINTING_MODE_LEFT_ALIGN, TRUE);
        BufferIntegerAsString(messageFormat, 1, FUN_0206E3D8(sav2), 2, PRINTING_MODE_LEFT_ALIGN, TRUE);
    }
    else if (item_id == ITEM_COIN_CASE)
    {
        string = NewString_ReadMsgData(msgData, 0x39);

        BufferIntegerAsString(messageFormat, 0, GetCoinCount(sav2), 5, PRINTING_MODE_LEFT_ALIGN, TRUE);
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

THUMB_FUNC void FUN_0206E51C( //todo: sync with HG
    struct PlayerData *playerData, struct String *dest, u32 r2, u32 r3, u32 heap_id)
{
#pragma unused(r2)
    struct MsgData *msgData;

    switch (r3)
    {
    case 1:
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 7, heap_id);

        ReadMsgDataIntoString(msgData, 0x38, dest);
        DestroyMsgData(msgData);
        return;
    case 2:
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 7, heap_id);

        ReadMsgDataIntoString(msgData, 0x6F, dest);
        DestroyMsgData(msgData);
        return;
    default:
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, 0xC7, heap_id);
        MessageFormat *messageFormat = MessageFormat_New(heap_id);
        struct String *src = NewString_ReadMsgData(msgData, 0x24);

        BufferPlayersName(messageFormat, 0, playerData);
        StringExpandPlaceholders(messageFormat, dest, src);
        String_Delete(src);
        MessageFormat_Delete(messageFormat);
        DestroyMsgData(msgData);
        return;
    }
}
