#include "nitro.h"
#include "NNS_FND_allocator.h"
#include "NNS_FND_expheap.h"

ARM_FUNC void *AllocatorAllocForExpHeap(NNSFndAllocator * pAllocator, u32 size)
{
    return NNS_FndAllocFromExpHeapEx(pAllocator->pHeap, size, pAllocator->heapParam1);
}

ARM_FUNC void AllocatorFreeForExpHeap(NNSFndAllocator * pAllocator, void *memBlock)
{
    NNS_FndFreeToExpHeap(pAllocator->pHeap, memBlock);
}

ARM_FUNC void *NNS_FndAllocFromAllocator(NNSFndAllocator * pAllocator, u32 size)
{
    return pAllocator->pFunc->pfAlloc(pAllocator, size);
}

ARM_FUNC void NNS_FndFreeToAllocator(NNSFndAllocator * pAllocator, void *memBlock)
{
    pAllocator->pFunc->pfFree(pAllocator, memBlock);
}

ARM_FUNC void NNS_FndInitAllocatorForExpHeap(NNSFndAllocator * pAllocator, NNSFndHeapHandle pHeap, int alignment)
{
    static const NNSFndAllocatorFunc pFunc = {AllocatorAllocForExpHeap, AllocatorFreeForExpHeap};
    pAllocator->pFunc = &pFunc;
    pAllocator->pHeap = pHeap;
    pAllocator->heapParam1 = alignment;
    pAllocator->heapParam2 = 0;
}
