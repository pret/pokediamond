#include "unk_020061E8.h"

#include "global.h"

#include "heap.h"
#include "unk_0200CA44.h"

extern struct TextPrinter *sub_0201B6C8(void);

SysTask *sub_020061E8(SysTaskFunc func, u32 r1, u32 r2, HeapID heapId) {
    void *r4;
    if (r1 != 0) {
        r4 = AllocFromHeap(heapId, r1);
        if (r4 == 0) {
            return NULL;
        }
        memset(r4, 0, r1);
    } else {
        r4 = NULL;
    }
    return SysTask_CreateOnMainQueue(func, r4, r2);
}

void sub_0200621C(SysTask *sysTask) {
    struct TextPrinter *textPrinter = sub_0201B6C8();
    if (textPrinter != NULL) {
        FreeToHeap(textPrinter);
    }
    SysTask_Destroy(sysTask);
}
