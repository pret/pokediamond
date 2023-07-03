#ifndef POKEDIAMOND_BAG_H
#define POKEDIAMOND_BAG_H

#include "bag_cursor.h"
#include "bag_view.h"
#include "itemtool.h"
#include "save.h"

typedef struct Bag {
    ItemSlot items[NUM_BAG_ITEMS];
    ItemSlot keyItems[NUM_BAG_KEY_ITEMS];
    ItemSlot TMsHMs[NUM_BAG_TMS_HMS];
    ItemSlot mail[NUM_BAG_MAIL];
    ItemSlot medicine[NUM_BAG_MEDICINE];
    ItemSlot berries[NUM_BAG_BERRIES];
    ItemSlot balls[NUM_BAG_BALLS];
    ItemSlot battleItems[NUM_BAG_BATTLE_ITEMS];
    u32 registeredItem;
} Bag;

u32 Save_Bag_sizeof(void);
Bag *Save_Bag_New(HeapID heapId);
void Save_Bag_Init(Bag *bag);
void Save_Bag_Copy(const Bag *src, Bag *dest);
u32 Bag_GetRegisteredItem(Bag *bag);
void Bag_SetRegisteredItem(Bag *bag, u32 item);
BOOL Bag_HasSpaceForItem(Bag *bag, u16 itemId, u16 quantity, HeapID heapId);
BOOL Bag_AddItem(Bag *bag, u16 itemId, u16 quantity, HeapID heapId);
BOOL Bag_TakeItem(Bag *bag, u16 itemId, u16 quantity, HeapID heapId);
BOOL Pocket_TakeItem(ItemSlot *slots, u32 count, u16 itemId, u16 quantity);
BOOL Bag_HasItem(Bag *bag, u16 itemId, u16 quantity, HeapID heapId);
BOOL Bag_PocketNotEmpty(Bag *bag, u32 pocket);
u16 Bag_GetQuantity(Bag *bag, u16 itemId, HeapID heapId);
u16 Pocket_GetQuantity(ItemSlot *slots, u32 count, u16 itemId);
void SortPocket(ItemSlot *slots, u32 count);
BagView * Bag_CreateView(Bag *bag, const u8 *pockets, HeapID heapId);
ItemSlot *Bag_GetPocketSlotN(Bag *bag, u8 pocket, u32 slot);
Bag *Save_Bag_Get(SaveData *saveData);

#endif //POKEDIAMOND_BAG_H
