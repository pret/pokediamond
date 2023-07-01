#ifndef POKEDIAMOND_BAG_H
#define POKEDIAMOND_BAG_H

#include "bag_cursor.h"
#include "bag_view.h"
#include "itemtool.h"
#include "save.h"

typedef struct Bag {
    struct ItemSlot items[NUM_BAG_ITEMS];
    struct ItemSlot keyItems[NUM_BAG_KEY_ITEMS];
    struct ItemSlot TMsHMs[NUM_BAG_TMS_HMS];
    struct ItemSlot mail[NUM_BAG_MAIL];
    struct ItemSlot medicine[NUM_BAG_MEDICINE];
    struct ItemSlot berries[NUM_BAG_BERRIES];
    struct ItemSlot balls[NUM_BAG_BALLS];
    struct ItemSlot battleItems[NUM_BAG_BATTLE_ITEMS];
    u32 registeredItem;
} Bag;

u32 Save_Bag_sizeof(void);
struct Bag * Save_Bag_New(HeapID heapId);
void Save_Bag_Init(struct Bag * bag);
void Save_Bag_Copy(const struct Bag * src, struct Bag * dest);
u32 Bag_GetRegisteredItem(struct Bag * bag);
void Bag_SetRegisteredItem(struct Bag * bag, u32 item);
u32 Bag_GetItemPocket(struct Bag * bag, u16 item_id, struct ItemSlot ** slot_p, u32 * count_p, HeapID heapId);
struct ItemSlot * Pocket_GetItemSlotForAdd(struct ItemSlot * slots, u32 count, u16 item_id, u16 quantity, u16 maxquantity);
struct ItemSlot * Bag_GetItemSlotForAdd(struct Bag * bag, u16 item_id, u16 quantity, HeapID heapId);
BOOL Bag_HasSpaceForItem(struct Bag * bag, u16 item_id, u16 quantity, HeapID heapId);
BOOL Bag_AddItem(struct Bag * bag, u16 item_id, u16 quantity, HeapID heapId);
struct ItemSlot * Pocket_GetItemSlotForRemove(struct ItemSlot * slots, u32 count, u16 item_id, u16 quantity);
struct ItemSlot * Bag_GetItemSlotForRemove(struct Bag * bag, u16 item_id, u16 quantity, HeapID heapId);
BOOL Bag_TakeItem(struct Bag * bag, u16 item_id, u16 quantity, HeapID heapId);
BOOL Pocket_TakeItem(struct ItemSlot * slots, u32 count, u16 item_id, u16 quantity);
BOOL Bag_HasItem(struct Bag * bag, u16 item_id, u16 quantity, HeapID heapId);
BOOL Bag_PocketNotEmpty(struct Bag * bag, u32 pocket);
u16 Bag_GetQuantity(struct Bag * bag, u16 item_id, HeapID heapId);
u16 Pocket_GetQuantity(struct ItemSlot * slots, u32 count, u16 item_id);
void SwapItemSlots(struct ItemSlot * a, struct ItemSlot * b);
void PocketCompaction(struct ItemSlot * slots, u32 count);
void SortPocket(struct ItemSlot * slots, u32 count);
struct BagView * CreateBagView(struct Bag * bag, const u8 * pockets, HeapID heapId);
struct ItemSlot * Bag_GetPocketSlotN(struct Bag * bag, u32 pocket, u32 slot);
struct Bag * Save_Bag_Get(struct SaveData * save);
struct BagCursor * sub_0206F164(HeapID heapId);
void sub_0206F17C(struct BagCursor * a0, u32 a1, u8 * a2, u8 * a3);
u16 sub_0206F18C(struct BagCursor * a0);
void sub_0206F190(struct BagCursor * a0, u32 a1, u8 a2, u8 a3);
void sub_0206F19C(struct BagCursor * a0, u16 a1);
void sub_0206F1A0(struct BagCursor * a0, u32 a1, u8 * a2, u8 * a3);
u16 sub_0206F1AC(struct BagCursor * a0);
u16 sub_0206F1B0(struct BagCursor * a0);
u16 sub_0206F1B4(struct BagCursor * a0);
void sub_0206F1B8(struct BagCursor * a0, u32 a1, u8 a2, u8 a3);
void sub_0206F1C0(struct BagCursor * a0);
void sub_0206F1E4(struct BagCursor * a0, u16 a1, u16 a2);
void sub_0206F1EC(struct BagCursor * a0, u16 a1);

#endif //POKEDIAMOND_BAG_H
