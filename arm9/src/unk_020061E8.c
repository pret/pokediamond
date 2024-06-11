#include "global.h"
#include "heap.h"
#include "unk_0200CA44.h"
#include "unk_020061E8.h"

extern struct TextPrinter *sub_0201B6C8(void);

SysTask *sub_020061E8(SysTaskFunc func, u32 r1, u32 r2, HeapID heapId)
{
    void * r4;
    if(r1 != 0)
    {
        r4 = AllocFromHeap(heapId, r1);
        if(r4 == 0)
        {
            return NULL;
        }
        memset(r4, 0, r1);
    }
    else
    {
        r4 = NULL;
    }
    return SysTask_CreateOnMainQueue(func, r4, r2);
}

void sub_0200621C(s32 r4)
{
    struct TextPrinter * r0 = sub_0201B6C8();
    if(r0 != NULL)
    {
        FreeToHeap(r0);
    }
    sub_0200CAB4(r4);
}
