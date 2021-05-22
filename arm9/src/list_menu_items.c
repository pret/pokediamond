#include "global.h"
#include "list_menu_items.h"
#include "msgdata.h"
#include "heap.h"

void ListMenuItems_DestroyMenuStrings(struct ListMenuItem * items);
struct ListMenuItem * ListMenuItems_SeekEnd(struct ListMenuItem * items, s32 * idx_p);

THUMB_FUNC struct ListMenuItem * ListMenuItems_ctor(u32 count, u32 heap_id)
{
    s32 i;
    struct ListMenuItem * ret = AllocFromHeap(heap_id, (count + 1) * sizeof(struct ListMenuItem));
    if (ret != NULL)
    {
        for (i = 0; i < count; i++)
        {
            ret[i].text = NULL;
            ret[i].value = 0;
        }
        ret[i].text = (struct String *)-1u;
        ret[i].value = heap_id;
    }
    return ret;
}

THUMB_FUNC void ListMenuItems_dtor(struct ListMenuItem * items)
{
    ListMenuItems_DestroyMenuStrings(items);
    FreeToHeap(items);
}

THUMB_FUNC void ListMenuItems_AppendFromMsgData(struct ListMenuItem * items, struct MsgData * msgData, u32 msgNo, s32 value)
{
    s32 heap_id;
    struct ListMenuItem * newItem = ListMenuItems_SeekEnd(items, &heap_id);
    if (newItem != NULL)
    {
        newItem->text = NewString_ReadMsgData(msgData, msgNo);
        newItem->value = value;
    }
}

THUMB_FUNC void ListMenuItems_AddItem(struct ListMenuItem * items, struct String * str, s32 value)
{
    s32 heap_id;
    struct ListMenuItem * newItem = ListMenuItems_SeekEnd(items, &heap_id);
    if (newItem != NULL)
    {
        newItem->text = StringDup(str, heap_id);
        newItem->value = value;
    }
}

THUMB_FUNC void ListMenuItems_CopyItem(struct ListMenuItem * items, struct ListMenuItem * src)
{
    s32 heap_id;
    struct ListMenuItem * newItem = ListMenuItems_SeekEnd(items, &heap_id);
    if (newItem != NULL)
    {
        newItem->text = src->text;
        newItem->value = src->value;
    }
}

THUMB_FUNC struct ListMenuItem * ListMenuItems_SeekEnd(struct ListMenuItem * items, s32 * heap_id_p)
{
    struct ListMenuItem * ret;
    for (; items->text != NULL; items++)
    {
        if (items->text == (struct String *)-1u)
        {
            GF_ASSERT(0);
            return NULL;
        }
    }
    ret = items;
    for (; items->text != (struct String *)-1u; items++)
        ;
    *heap_id_p = items->value;
    return ret;
}

THUMB_FUNC void ListMenuItems_DestroyMenuStrings(struct ListMenuItem * items)
{
    s32 i;
    for (i = 0; items[i].text != (struct String *)-1u; i++)
    {
        if (items[i].text == NULL)
            break;
        String_dtor(items[i].text);
        items[i].text = NULL;
    }
}
