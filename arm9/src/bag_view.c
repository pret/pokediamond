#include "global.h"
#include "bag_view.h"
#include "coins.h"
#include "constants/items.h"
#include "heap.h"
#include "msgdata.h"
#include "player_data.h"
#include "script_buffers.h"
#include "seal.h"

extern u32 *FUN_0202708C(u32 *);
extern u32 FUN_02027168(u32 *);
extern u16 FUN_02027184(u32 *);
extern u32 *FUN_02027E24(struct SaveBlock2 *sav2);
extern u8 FUN_02029E2C(struct SealCase *, u32);
extern u32 FUN_0202A8D8(struct SaveBlock2 *);
extern u16 FUN_0202A3B4(u32, u32, u32);

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

THUMB_FUNC u32 FUN_0206E39C(struct SaveBlock2 *sav2)
{
    return (u32)CheckCoins(Sav2_PlayerData_GetCoinsAddr(sav2));
}

THUMB_FUNC u32 FUN_0206E3A8(struct SaveBlock2 *sav2)
{
    struct SealCase *seal_case = Sav2_SealCase_get(sav2);
    u32 i;
    u32 count = 0;

    for (i = 1; i <= 0x50; ++i)
    {
        count += FUN_02029E2C(seal_case, i);
    }

    return count;
}

THUMB_FUNC u32 FUN_0206E3C8(struct SaveBlock2 *sav2)
{
    return FUN_02027168(FUN_0202708C(FUN_02027E24(sav2)));
}

THUMB_FUNC u32 FUN_0206E3D8(struct SaveBlock2 *sav2)
{
    return FUN_02027184(FUN_0202708C(FUN_02027E24(sav2)));
}

THUMB_FUNC u32 FUN_0206E3E8(struct SaveBlock2 *sav2)
{
    return FUN_0202A3B4(FUN_0202A8D8(sav2), 0, 0);
}

THUMB_FUNC BOOL FUN_0206E3F8(struct SaveBlock2 *sav2, struct String *dest, u32 item_id, u32 heap_id)
{
    struct MsgData *msgData = NewMsgDataFromNarc(0, NARC_MSGDATA_MSG, 7, heap_id);
    struct ScrStrBufs *scrStrBufs = ScrStrBufs_new(heap_id);
    struct String *string;

    if (item_id == ITEM_NONE)
    {
        string = NewString_ReadMsgData(msgData, 0x63);
    }
    else if (item_id == ITEM_POINT_CARD)
    {
        string = NewString_ReadMsgData(msgData, 0x61);

        BufferIntegerAsString(scrStrBufs, 0, FUN_0206E3E8(sav2), 4, 0, TRUE);
    }
    else if (item_id == ITEM_SEAL_CASE)
    {
        string = NewString_ReadMsgData(msgData, 0x5C);

        BufferIntegerAsString(scrStrBufs, 0, FUN_0206E3A8(sav2), 4, 0, TRUE);
    }
    else if (item_id == ITEM_FASHION_CASE)
    {
        string = NewString_ReadMsgData(msgData, 0x5D);

        BufferIntegerAsString(scrStrBufs, 0, FUN_0206E3C8(sav2), 3, 0, TRUE);
        BufferIntegerAsString(scrStrBufs, 1, FUN_0206E3D8(sav2), 2, 0, TRUE);
    }
    else if (item_id == ITEM_COIN_CASE)
    {
        string = NewString_ReadMsgData(msgData, 0x39);

        BufferIntegerAsString(scrStrBufs, 0, FUN_0206E39C(sav2), 5, 0, TRUE);
    }
    else
    {
        ScrStrBufs_delete(scrStrBufs);
        DestroyMsgData(msgData);

        return FALSE;
    }

    StringExpandPlaceholders(scrStrBufs, dest, string);
    String_dtor(string);
    ScrStrBufs_delete(scrStrBufs);
    DestroyMsgData(msgData);

    return TRUE;
}

THUMB_FUNC void FUN_0206E51C(
    struct PlayerData *playerData, struct String *dest, u32 r2, u32 r3, u32 heap_id)
{
#pragma unused(r2)
    struct MsgData *msgData;

    switch (r3)
    {
    case 1:
        msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 7, heap_id);

        ReadMsgDataIntoString(msgData, 0x38, dest);
        DestroyMsgData(msgData);
        return;
    case 2:
        msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 7, heap_id);

        ReadMsgDataIntoString(msgData, 0x6F, dest);
        DestroyMsgData(msgData);
        return;
    default:
        msgData = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 0xC7, heap_id);
        struct ScrStrBufs *scrStrBufs = ScrStrBufs_new(heap_id);
        struct String *src = NewString_ReadMsgData(msgData, 0x24);

        BufferPlayersName(scrStrBufs, 0, playerData);
        StringExpandPlaceholders(scrStrBufs, dest, src);
        String_dtor(src);
        ScrStrBufs_delete(scrStrBufs);
        DestroyMsgData(msgData);
        return;
    }
}
