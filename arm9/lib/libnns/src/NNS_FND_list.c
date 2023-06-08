#include "nitro.h"
#include "NNS_FND_list.h"
#include "code32.h"

#define OBJ_TO_LINK(list, obj) ((NNSFndLink*)((void*)(obj) + (list)->offset))

void NNS_FndInitList(NNSFndList* list, s32 alignment)
{
    list->headObject = NULL;
    list->tailObject = NULL;
    list->numObjects = 0;
    list->offset = (u16)alignment;
}

static void SetFirstObject(NNSFndList* list, void* object)
{
    NNSFndLink* tail = OBJ_TO_LINK(list, object);
    tail->nextObject = NULL;
    tail->prevObject = NULL;
    list->headObject = object;
    list->tailObject = object;
    list->numObjects++;
}

void NNS_FndAppendListObject(NNSFndList* list, void* object)
{
    if (list->headObject == NULL)
    {
        SetFirstObject(list, object);
    }
    else
    {
        NNSFndLink *tail = OBJ_TO_LINK(list, object);
        tail->prevObject = list->tailObject;
        tail->nextObject = NULL;
        OBJ_TO_LINK(list, list->tailObject)->nextObject = object;
        list->tailObject = object;
        list->numObjects++;
    }
}

void NNS_FndPrependListObject(NNSFndList* list, void* object)
{
    if (list->headObject == NULL)
    {
        SetFirstObject(list, object);
    }
    else
    {
        NNSFndLink *tail = OBJ_TO_LINK(list, object);
        tail->prevObject = NULL;
        tail->nextObject = list->headObject;
        OBJ_TO_LINK(list, list->headObject)->prevObject = object;
        list->headObject = object;
        list->numObjects++;
    }
}

void NNS_FndInsertListObject(NNSFndList* list, void* where, void* object)
{
    if (where == NULL)
    {
        NNS_FndAppendListObject(list, object);
    }

    else if (where == list->headObject)
    {
        NNS_FndPrependListObject(list, object);
    }
    else
    {
        NNSFndLink* tail = OBJ_TO_LINK(list, object);
        void* prevObject = OBJ_TO_LINK(list, where)->prevObject;
        NNSFndLink* head = OBJ_TO_LINK(list, prevObject);
        tail->prevObject = prevObject;
        tail->nextObject = where;
        head->nextObject = object;
        OBJ_TO_LINK(list, where)->prevObject = object;
        list->numObjects++;
    }
}

void NNS_FndRemoveListObject(NNSFndList* list, void* object)
{
    NNSFndLink* node = OBJ_TO_LINK(list, object);
    if (node->prevObject == NULL)
    {
        list->headObject = node->nextObject;
    }
    else
    {
        OBJ_TO_LINK(list, node->prevObject)->nextObject = node->nextObject;
    }
    if (node->nextObject == NULL)
    {
        list->tailObject = node->prevObject;
    }
    else
    {
        OBJ_TO_LINK(list, node->nextObject)->prevObject = node->prevObject;
    }
    node->prevObject = NULL;
    node->nextObject = NULL;
    list->numObjects--;
}

void * NNS_FndGetNextListObject(NNSFndList* list, void* object)
{
    if (object == NULL)
    {
        return list->headObject;
    }
    else
    {
        return OBJ_TO_LINK(list, object)->nextObject;
    }
}

void * NNS_FndGetPrevListObject(NNSFndList* list, void* object)
{
    if (object == NULL)
    {
        return list->tailObject;
    }
    else
    {
        return OBJ_TO_LINK(list, object)->prevObject;
    }
}
