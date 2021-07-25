#ifndef POKEDIAMOND_HEAP_H
#define POKEDIAMOND_HEAP_H

#include "global.h"
#include "nitro/OS_arena_shared.h"
#include "NNS_FND_expheap.h"
#include "NNS_FND_allocator.h"

struct HeapParam
{
    u32 size;
    OSArenaId arena;
};

void InitHeapSystem(const struct HeapParam *templates, u32 nTemplates, u32 totalNumHeaps, u32 pre_size);
s32 FindFirstAvailableHeapHandle();
BOOL CreateHeap(u32 parent, u32 child, u32 size);
BOOL CreateHeapAtEnd(u32 parent, u32 child, u32 size);
BOOL CreateHeapInternal(u32 parent, u32 child, u32 size, s32 alignment);
void DestroyHeap(u32 heap_id);
void *AllocFromHeapInternal(NNSFndHeapHandle heap, u32 size, s32 alignment, u32 heap_id);
void AllocFail();
void *AllocFromHeap(u32 heap_id, u32 size);
void *AllocFromHeapAtEnd(u32 heap_id, u32 size);
void FreeToHeap(void *ptr);
void FreeToHeapExplicit(u32 heap_id, void * ptr);
u32 GF_ExpHeap_FndGetTotalFreeSize(u32 heap_id);
void GF_ExpHeap_FndInitAllocator(NNSFndAllocator * pAllocator, u32 heap_id, int alignment);
void ReallocFromHeap(void *ptr, u32 newSize);
BOOL GF_heap_c_dummy_return_true(u32 heap_id);

#endif //POKEDIAMOND_HEAP_H
