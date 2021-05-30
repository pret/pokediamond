#ifndef GUARD_NNS_FND_ALLOCATOR_H
#define GUARD_NNS_FND_ALLOCATOR_H

#include "NNS_FND_heapcommon.h"

typedef struct NNSFndAllocator NNSFndAllocator;

typedef void*   (*NNSFndFuncAllocatorAlloc)(
    NNSFndAllocator*    pAllocator,
    u32                 size);

typedef void    (*NNSFndFuncAllocatorFree)(
    NNSFndAllocator*    pAllocator,
    void*               memBlock);

typedef struct NNSFndAllocatorFunc NNSFndAllocatorFunc;

struct NNSFndAllocatorFunc
{
    NNSFndFuncAllocatorAlloc    pfAlloc;
    NNSFndFuncAllocatorFree     pfFree;
};

struct NNSFndAllocator
{
    NNSFndAllocatorFunc const * pFunc;
    void*                       pHeap;
    u32                         heapParam1;
    u32                         heapParam2;
};

void NNS_FndInitAllocatorForExpHeap(NNSFndAllocator * pAllocator, NNSFndHeapHandle heap, int alignment);

#endif //GUARD_NNS_FND_ALLOCATOR_H
