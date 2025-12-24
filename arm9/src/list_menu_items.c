#include "list_menu_items.h"

#include "global.h"

#include "heap.h"
#include "msgdata.h"

void ListMenuItems_DestroyMenuStrings(struct ListMenuItem *items);

struct ListMenuItem *ListMenuItems_New(u32 count, enum HeapID heapID) {
    s32 i;
    struct ListMenuItem *ret = Heap_Alloc(heapID, (count + 1) * sizeof(struct ListMenuItem));
    if (ret != NULL) {
        for (i = 0; i < count; i++) {
            ret[i].text = NULL;
            ret[i].value = 0;
        }
        ret[i].text = (struct String *)-1u;
        ret[i].value = (s32)heapID;
    }
    return ret;
}

void ListMenuItems_Delete(struct ListMenuItem *items) {
    ListMenuItems_DestroyMenuStrings(items);
    Heap_Free(items);
}

void ListMenuItems_AppendFromMsgData(struct ListMenuItem *items, struct MsgData *msgData, u32 msgNo, s32 value) {
    enum HeapID heapID;
    struct ListMenuItem *newItem = ListMenuItems_SeekEnd(items, &heapID);
    if (newItem != NULL) {
        newItem->text = NewString_ReadMsgData(msgData, msgNo);
        newItem->value = value;
    }
}

void ListMenuItems_AddItem(struct ListMenuItem *items, struct String *str, s32 value) {
    enum HeapID heapID;
    struct ListMenuItem *newItem = ListMenuItems_SeekEnd(items, &heapID);
    if (newItem != NULL) {
        newItem->text = StringDup(str, heapID);
        newItem->value = value;
    }
}

void ListMenuItems_CopyItem(struct ListMenuItem *items, struct ListMenuItem *src) {
    enum HeapID heapID;
    struct ListMenuItem *newItem = ListMenuItems_SeekEnd(items, &heapID);
    if (newItem != NULL) {
        newItem->text = src->text;
        newItem->value = src->value;
    }
}

struct ListMenuItem *ListMenuItems_SeekEnd(struct ListMenuItem *items, enum HeapID *heapIdPtr) {
    struct ListMenuItem *ret;
    for (; items->text != NULL; items++) {
        if (items->text == (struct String *)-1u) {
            GF_ASSERT(0);
            return NULL;
        }
    }
    ret = items;
    for (; items->text != (struct String *)-1u; items++)
        ;
    *heapIdPtr = (enum HeapID)items->value;
    return ret;
}

void ListMenuItems_DestroyMenuStrings(struct ListMenuItem *items) {
    s32 i;
    for (i = 0; items[i].text != (struct String *)-1u; i++) {
        if (items[i].text == NULL) {
            break;
        }
        String_Delete(items[i].text);
        items[i].text = NULL;
    }
}
