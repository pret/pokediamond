#ifndef POKEDIAMOND_BAG_CURSOR_H
#define POKEDIAMOND_BAG_CURSOR_H

#include "global.h"

#include "heap.h"

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

BagCursor *BagCursor_New(HeapID heapId);
void BagCursor_Field_PocketGetPosition(BagCursor *cursor, u32 pocket, u8 *position, u8 *scroll);
u16 BagCursor_Field_GetPocket(BagCursor *cursor);
void BagCursor_Field_PocketSetPosition(BagCursor *cursor, u32 pocket, u8 position, u8 scroll);
void BagCursor_Field_SetPocket(BagCursor *cursor, u16 pocket);
void BagCursor_Battle_PocketGetPosition(BagCursor *cursor, u32 pocket, u8 *position, u8 *scroll);
u16 BagCursor_Battle_GetLastUsedItem(BagCursor *cursor);
u16 BagCursor_Battle_GetLastUsedPocket(BagCursor *cursor);
u16 BagCursor_Battle_GetPocket(BagCursor *cursor);
void BagCursor_Battle_PocketSetPosition(BagCursor *cursor, u32 pocket, u8 position, u8 scroll);
void BagCursor_Battle_Init(BagCursor *cursor);
void BagCursor_Battle_SetLastUsedItem(BagCursor *cursor, u16 itemId, u16 pocket);
void BagCursor_Battle_SetPocket(BagCursor *cursor, u16 pocket);

#endif // POKEDIAMOND_BAG_CURSOR_H
