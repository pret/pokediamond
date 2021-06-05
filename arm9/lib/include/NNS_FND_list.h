#ifndef GUARD_NNS_FND_LIST_H
#define GUARD_NNS_FND_LIST_H

typedef struct
{
    void*       prevObject;     // Pointer to the previous linked object.
    void*       nextObject;     // Pointer to the next linked object.

} NNSFndLink;

typedef struct
{
    void*       headObject;     // Pointer for the object linked to the top of the list.
    void*       tailObject;     // Pointer for the object linked to the end of the list.
    u16         numObjects;     // Number of objects linked in the list.
    u16         offset;         // Offset for NNSFndLink type structure member.

} NNSFndList;

#endif //GUARD_NNS_FND_LIST_H
