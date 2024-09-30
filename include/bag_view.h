#ifndef POKEDIAMOND_BAG_VIEW_H
#define POKEDIAMOND_BAG_VIEW_H

#include "bag_cursor.h"
#include "itemtool.h"
#include "player_data.h"
#include "save.h"

enum ItemUseError {
    ITEMUSEERROR_OKAY       = 0, // no error
    ITEMUSEERROR_NODISMOUNT = 1, // can't get off bike
    ITEMUSEERROR_NOFOLLOWER = 2, // have a companion

    ITEMUSEERROR_OAKSWORDS = -1u,
};

typedef struct BagViewPocket {
    ItemSlot *slot;
    u8 padding[0x4];
    u8 pocket;
    u8 padding2[0x3];
} BagViewPocket; // total size = 0xC

typedef struct BagView {
    SaveData *saveData;
    BagViewPocket pockets[8];
    u8 unk64;
    u8 unk65;
    u16 unk66;
    u16 unk68;
    u8 padding[0x2];
    BagCursor *cursor;
    void *unk70;
    u8 unk74;
    u8 unk75;
    u16 unk76_0 : 1;
    u16 unk76_1 : 15;
} BagView; // total size = 0x78

BagView *BagView_New(u8 heapId);
u32 BagView_sizeof(void);
void sub_0206E30C(BagView *bagView, u8 r1);
void sub_0206E314(BagView *bagView, SaveData *save, u8 r2, BagCursor *cursor);
void BagView_SetItem(BagView *bagView, ItemSlot *slot, u8 pocket, u8 idx);
void sub_0206E340(BagView *bagView);
void sub_0206E354(BagView *bagView, void *r1);
void sub_0206E358(BagView *bagView, u8 r1);
void sub_0206E360(BagView *bagView, u16 r1);
u16 sub_0206E37C(BagView *bagView);
u16 sub_0206E384(BagView *bagView);
u8 sub_0206E38C(BagView *bagView);
u8 sub_0206E394(BagView *bagView);
BOOL TryFormatRegisteredKeyItemUseMessage(SaveData *saveData, String *dest, u32 itemId, HeapID heapId);
void GetItemUseErrorMessage(PlayerProfile *playerProfile, String *dest, u16 itemId, enum ItemUseError code, HeapID heapId);

#endif // POKEDIAMOND_BAG_VIEW_H
