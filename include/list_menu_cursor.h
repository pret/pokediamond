#ifndef POKEDIAMOND_LIST_MENU_CURSOR_H
#define POKEDIAMOND_LIST_MENU_CURSOR_H

#include "bg_window.h"

// TODO: Move to its own header, and fill it out
struct ListMenuCursor
{
    // ???
};

extern struct ListMenuCursor * ListMenuCursorNew(u32 heap_id);
extern void ListMenuUpdateCursorObj(struct ListMenuCursor *, struct Window *, u8 x, u8 y);
extern void ListMenuCursorSetColor(struct ListMenuCursor *, u32);
extern void DestroyListMenuCursorObj(struct ListMenuCursor *);

#endif // POKEDIAMOND_LIST_MENU_CURSOR_H
