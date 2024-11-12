#include "list_menu_items.h"

#include "global.h"

#include "heap.h"
#include "msgdata.h"

void ListMenuItems_DestroyMenuStrings(struct ListMenuItem *items);

struct ListMenuItem *ListMenuItems_New(u32 count, HeapID heapId) {
    s32 i;
    struct ListMenuItem *ret = AllocFromHeap(heapId, (count + 1) * sizeof(struct ListMenuItem));
    if (ret != NULL) {
        for (i = 0; i < count; i++) {
            ret[i].text = NULL;
            ret[i].value = 0;
        }
        ret[i].text = (struct String *)-1u;
        ret[i].value = (s32)heapId;
    }
    return ret;
}

void ListMenuItems_Delete(struct ListMenuItem *items) {
    ListMenuItems_DestroyMenuStrings(items);
    FreeToHeap(items);
}

void ListMenuItems_AppendFromMsgData(struct ListMenuItem *items, struct MsgData *msgData, u32 msgNo, s32 value) {
    HeapID heapId;
    struct ListMenuItem *newItem = ListMenuItems_SeekEnd(items, &heapId);
    if (newItem != NULL) {
        newItem->text = NewString_ReadMsgData(msgData, msgNo);
        newItem->value = value;
    }
}

void ListMenuItems_AddItem(struct ListMenuItem *items, struct String *str, s32 value) {
    HeapID heapId;
    struct ListMenuItem *newItem = ListMenuItems_SeekEnd(items, &heapId);
    if (newItem != NULL) {
        newItem->text = StringDup(str, heapId);
        newItem->value = value;
    }
}

void ListMenuItems_CopyItem(struct ListMenuItem *items, struct ListMenuItem *src) {
    HeapID heapId;
    struct ListMenuItem *newItem = ListMenuItems_SeekEnd(items, &heapId);
    if (newItem != NULL) {
        newItem->text = src->text;
        newItem->value = src->value;
    }
}

struct ListMenuItem *ListMenuItems_SeekEnd(struct ListMenuItem *items, HeapID *heapIdPtr) {
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
    *heapIdPtr = (HeapID)items->value;
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
