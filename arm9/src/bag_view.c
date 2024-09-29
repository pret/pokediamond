#include "bag_view.h"

#include "global.h"

#include "constants/items.h"
#include "constants/seal_constants.h"

#include "msgdata/msg.naix"
#include "msgdata/msg/narc_0007.h"
#include "msgdata/msg/narc_0199.h"

#include "coins.h"
#include "fashion_case.h"
#include "heap.h"
#include "message_format.h"
#include "msgdata.h"
#include "player_data.h"
#include "seal.h"
#include "unk_0202A1E0.h"

extern FashionCase *Save_FashionData_GetFashionCase(SaveFashionData *);
extern u32 FashionCase_CountAccessories(FashionCase *fashionCase);
extern u16 FashionCase_CountWallpapers(FashionCase *fashionCase);
extern SaveFashionData *Save_FashionData_Get(SaveData *save);
extern u8 SealCase_CountSealOccurrenceAnywhere(SealCase *, u32);

static u16 GetCoinCount(SaveData *saveData);
static u32 GetSealCount(SaveData *saveData);
static u32 GetNumFashionAccessories(SaveData *saveData);
static u32 GetNumFashionBackgrounds(SaveData *saveData);
static u32 GetNumBattlePoints(SaveData *saveData);

BagView *BagView_New(u8 heapId) {
    BagView *ptr = AllocFromHeap((HeapID)heapId, sizeof(BagView));
    memset(ptr, 0, sizeof(BagView));
    return ptr;
}

u32 BagView_sizeof(void) {
    return sizeof(BagView);
}

void sub_0206E30C(BagView *bagView, u8 r1) {
    bagView->unk65 = r1;
}

void sub_0206E314(BagView *bagView, SaveData *save, u8 r2, BagCursor *cursor) {
    sub_0206E30C(bagView, r2);

    bagView->saveData = save;
    bagView->cursor   = cursor;
    bagView->unk66    = 0;
}

void BagView_SetItem(BagView *bagView, ItemSlot *slot, u8 pocket, u8 idx) {
    bagView->pockets[idx].slot   = slot;
    bagView->pockets[idx].pocket = pocket;
}

void sub_0206E340(BagView *bagView) {
    bagView->unk76_0 = TRUE;
}

void sub_0206E354(BagView *bagView, void *r1) {
    bagView->unk70 = r1;
}

void sub_0206E358(BagView *bagView, u8 r1) {
    bagView->unk74 = r1;
}

void sub_0206E360(BagView *bagView, u16 r1) {
    bagView->unk76_1 = r1;
}

u16 sub_0206E37C(BagView *bagView) {
    return bagView->unk66;
}

u16 sub_0206E384(BagView *bagView) {
    return bagView->unk68;
}

u8 sub_0206E38C(BagView *bagView) {
    return bagView->unk74;
}

u8 sub_0206E394(BagView *bagView) {
    return bagView->unk75;
}

static u16 GetCoinCount(SaveData *saveData) {
    return CheckCoins(Save_PlayerData_GetCoinsAddr(saveData));
}

static u32 GetSealCount(SaveData *saveData) {
    SealCase *sealCase = Save_SealCase_Get(saveData);
    u32 i;
    u32 count = 0;

    for (i = SEAL_MIN; i <= SEAL_MAX; i++) {
        count += SealCase_CountSealOccurrenceAnywhere(sealCase, i);
    }

    return count;
}

static u32 GetNumFashionAccessories(SaveData *saveData) {
    return FashionCase_CountAccessories(Save_FashionData_GetFashionCase(Save_FashionData_Get(saveData)));
}

static u32 GetNumFashionBackgrounds(SaveData *saveData) {
    return FashionCase_CountWallpapers(Save_FashionData_GetFashionCase(Save_FashionData_Get(saveData)));
}

static u32 GetNumBattlePoints(SaveData *saveData) {
    return FrontierData_BattlePointAction(Save_FrontierData_Get(saveData), 0, DATA_GET);
}

BOOL TryFormatRegisteredKeyItemUseMessage(SaveData *saveData, String *dest, u32 itemId, HeapID heapId) {
    MsgData *msgData             = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_MSGDATA_MSG, NARC_msg_narc_0007_bin, heapId);
    MessageFormat *messageFormat = MessageFormat_New(heapId);
    String *string;

    if (itemId == ITEM_NONE) {
        string = NewString_ReadMsgData(msgData, narc_0007_00099); // A Key Item in the Bag can be assigned to this button for instant use.
    } else if (itemId == ITEM_POINT_CARD) {
        string = NewString_ReadMsgData(msgData, narc_0007_00097); // Saved Battle Points: {STRVAR_1 53, 0}BP
        BufferIntegerAsString(messageFormat, 0, GetNumBattlePoints(saveData), 4, PRINTING_MODE_LEFT_ALIGN, TRUE);
    } else if (itemId == ITEM_SEAL_CASE) {
        string = NewString_ReadMsgData(msgData, narc_0007_00092); // Seals: {STRVAR_1 53, 0}
        BufferIntegerAsString(messageFormat, 0, GetSealCount(saveData), 4, PRINTING_MODE_LEFT_ALIGN, TRUE);
    } else if (itemId == ITEM_FASHION_CASE) {
        string = NewString_ReadMsgData(msgData, narc_0007_00093); // Accessories: {STRVAR_1 52, 0} Backdrops: {STRVAR_1 51, 1}
        BufferIntegerAsString(messageFormat, 0, GetNumFashionAccessories(saveData), 3, PRINTING_MODE_LEFT_ALIGN, TRUE);
        BufferIntegerAsString(messageFormat, 1, GetNumFashionBackgrounds(saveData), 2, PRINTING_MODE_LEFT_ALIGN, TRUE);
    } else if (itemId == ITEM_COIN_CASE) {
        string = NewString_ReadMsgData(msgData, narc_0007_00057); // Your Coins: {STRVAR_1 54, 0}
        BufferIntegerAsString(messageFormat, 0, GetCoinCount(saveData), 5, PRINTING_MODE_LEFT_ALIGN, TRUE);
    } else {
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

void GetItemUseErrorMessage(PlayerProfile *playerProfile, String *dest, u16 itemId, enum ItemUseError code, HeapID heapId) {
#pragma unused(itemId)
    MsgData *msgData;

    switch (code) {
    case ITEMUSEERROR_NODISMOUNT:
        // You can’t dismount your Bike here.
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0007_bin, heapId);
        ReadMsgDataIntoString(msgData, narc_0007_00056, dest);
        DestroyMsgData(msgData);
        break;
    case ITEMUSEERROR_NOFOLLOWER:
        // It can’t be used when you have someone with you.
        msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0007_bin, heapId);
        ReadMsgDataIntoString(msgData, narc_0007_00111, dest);
        DestroyMsgData(msgData);
        break;
    default:
        // Rowan’s words echoed... {STRVAR_1 3, 0}! There’s a time and place for everything! But not now.
        msgData                      = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_MSGDATA_MSG, NARC_msg_narc_0199_bin, heapId);
        MessageFormat *messageFormat = MessageFormat_New(heapId);
        String *src                  = NewString_ReadMsgData(msgData, narc_0199_00036);
        BufferPlayersName(messageFormat, 0, playerProfile);
        StringExpandPlaceholders(messageFormat, dest, src);
        String_Delete(src);
        MessageFormat_Delete(messageFormat);
        DestroyMsgData(msgData);
        break;
    }
}
