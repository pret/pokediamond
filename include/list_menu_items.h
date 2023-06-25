#ifndef POKEDIAMOND_LIST_MENU_ITEMS_H
#define POKEDIAMOND_LIST_MENU_ITEMS_H

#include "string16.h"
#include "msgdata.h"

struct ListMenuItem
{
    struct String * text;
    s32 value;
};

struct ListMenuItem * ListMenuItems_New(u32 count, HeapID heapId);
void ListMenuItems_Delete(struct ListMenuItem * items);
void ListMenuItems_AppendFromMsgData(struct ListMenuItem * items, struct MsgData * msgData, u32 msgNo, s32 value);
void ListMenuItems_AddItem(struct ListMenuItem * items, struct String * str, s32 value);
void ListMenuItems_CopyItem(struct ListMenuItem * items, struct ListMenuItem * src);
struct ListMenuItem * ListMenuItems_SeekEnd(struct ListMenuItem * items, HeapID* heapIdPtr);
void ListMenuItems_DestroyMenuStrings(struct ListMenuItem * items);

#endif // POKEDIAMOND_LIST_MENU_ITEMS_H
