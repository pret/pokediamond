#ifndef POKEDIAMOND_HEAP_H
#define POKEDIAMOND_HEAP_H

#include "global.h"
#include "NNS_FND_expheap.h"
#include "NNS_FND_allocator.h"

struct UnkStruct_020EDB10
{
    u32 size;
    OSArenaId arena;
};

struct UnkStruct_020166C8
{
    NNSFndHeapHandle *heapHandles;
    NNSFndHeapHandle *unk04;
    void **unk08;
    u16 *unk0c;
    u8 *heapIdxs;
    u16 totalNumHeaps;
    u16 nTemplates;
    u16 unk18;
    u16 unk1a;
};


void FUN_020166C8(const struct UnkStruct_020EDB10 *templates, u32 nTemplates, u32 totalNumHeaps, u32 pre_size);
s32 FUN_020167F4();
u32 FUN_0201681C(u32 param0, u32 heap_id, u32 param2);
u32 FUN_02016828(u32 param0, u32 param1, u32 param2);
u32 FUN_02016834(u32 param0, u32 param1, u32 size, s32 alignment);
void FUN_020168D0(u32 heap_id);
u32 *FUN_02016944(void *param0, u32 param1, s32 param2, u32 param3);
void FUN_02016988();
void *AllocFromHeap(u32 heap_id, u32 size);
void *AllocFromHeapAtEnd(u32 heap_id, u32 size);
void FreeToHeap(void *ptr);
void FreeToHeapExplicit(u32 heap_id, void * ptr);
u32 GF_ExpHeap_FndGetTotalFreeSize(u32 heap_id);
void GF_ExpHeap_FndInitAllocator(NNSFndAllocator * pAllocator, u32 heap_id, int alignment);
void ReallocFromHeap(void *ptr, u32 newSize);
u32 FUN_02016B90(u32 param0);

#endif //POKEDIAMOND_HEAP_H
