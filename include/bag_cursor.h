#ifndef POKEDIAMOND_BAG_CURSOR_H
#define POKEDIAMOND_BAG_CURSOR_H

#include "global.h"

//todo: move the following to bag_cursor.h
typedef struct BagCursorField {
    u8 scroll[8];
    u8 position[8];
    u16 pocket;
    u16 padding;
} BagCursorField;

typedef struct BagCursorBattle {
    u8 scroll[5];
    u8 position[5];
    u16 lastUsedItem;
    u16 lastUsedPocket;
    u16 pocket;
} BagCursorBattle;

typedef struct BagCursor {
    BagCursorField field;
    BagCursorBattle battle;
} BagCursor;

#endif // POKEDIAMOND_BAG_CURSOR_H