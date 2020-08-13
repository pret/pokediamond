#ifndef POKEDIAMOND_BAG_H
#define POKEDIAMOND_BAG_H

#include "itemtool.h"

struct Bag
{
    struct ItemSlot items[NUM_BAG_ITEMS];
    struct ItemSlot keyItems[NUM_BAG_KEY_ITEMS];
    struct ItemSlot TMsHMs[NUM_BAG_TMS_HMS];
    struct ItemSlot mail[NUM_BAG_MAIL];
    struct ItemSlot medicine[NUM_BAG_MEDICINE];
    struct ItemSlot berries[NUM_BAG_BERRIES];
    struct ItemSlot balls[NUM_BAG_BALLS];
    struct ItemSlot battleItems[NUM_BAG_BATTLE_ITEMS];
    u32 registeredItem;
};

#endif //POKEDIAMOND_BAG_H
