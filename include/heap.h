#ifndef POKEDIAMOND_HEAP_H
#define POKEDIAMOND_HEAP_H

#include "nitro/OS_arena_shared.h"

#include "global.h"

#include "NNS_FND_allocator.h"
#include "NNS_FND_expheap.h"

typedef enum HeapID {
    HEAP_ID_DEFAULT,
    HEAP_ID_1,
    HEAP_ID_2,
    HEAP_ID_MAIN,
    HEAP_ID_4,
    HEAP_ID_POKETCH_MAIN = 7,
    HEAP_ID_POKETCH_APP,
    HEAP_ID_FIELD = 11,
    HEAP_ID_15    = 15,
    HEAP_ID_32    = 32,
    HEAP_ID_49    = 49,
    HEAP_ID_76    = 76,
    HEAP_ID_77,
    HEAP_ID_INTRO    = 82,
    HEAP_ID_INTRO_TV = 83,
} HeapID;

struct HeapParam {
    u32 size;
    OSArenaId arena;
};

void InitHeapSystem(const struct HeapParam *templates, u32 nTemplates, u32 totalNumHeaps, u32 pre_size);
s32 FindFirstAvailableHeapHandle(void);
BOOL CreateHeap(u32 parent, u32 child, u32 size);
BOOL CreateHeapAtEnd(u32 parent, u32 child, u32 size);
BOOL CreateHeapInternal(u32 parent, u32 child, u32 size, s32 alignment);
void DestroyHeap(HeapID heapId);
void *AllocFromHeapInternal(NNSFndHeapHandle heap, u32 size, s32 alignment, HeapID heapId);
void AllocFail(void);
void *AllocFromHeap(HeapID heapId, u32 size);
void *AllocFromHeapAtEnd(HeapID heapId, u32 size);
void FreeToHeap(void *ptr);
void FreeToHeapExplicit(HeapID heapId, void *ptr);
u32 GF_ExpHeap_FndGetTotalFreeSize(HeapID heapId);
void GF_ExpHeap_FndInitAllocator(NNSFndAllocator *pAllocator, HeapID heapId, int alignment);
void ReallocFromHeap(void *ptr, u32 newSize);
BOOL GF_heap_c_dummy_return_true(HeapID heapId);

#endif // POKEDIAMOND_HEAP_H
