#include "global.h"
#include "NNS_FND_expheap.h"

typedef struct NNSiMemRegion {
    void* start;
    void* end;
} NNSiMemRegion;

static inline u16 GetAlignmentForMBlock(NNSiFndExpHeapMBlockHead* block)
{
    return NNSi_FndGetBitValue(block->attribute, 8, 7);
}

static inline void* GetMemPtrForMBlock(NNSiFndExpHeapMBlockHead* block)
{
    return AddU32ToPtr(block, sizeof(NNSiFndExpHeapMBlockHead));
}

static inline void* GetMBlockEndAddr(NNSiFndExpHeapMBlockHead* block)
{
    return AddU32ToPtr(GetMemPtrForMBlock(block), block->blockSize);
}

void GetRegionOfMBlock(NNSiMemRegion* region, NNSiFndExpHeapMBlockHead* block)
{
    region->start = SubU32ToPtr(block, GetAlignmentForMBlock(block));
    region->end = GetMBlockEndAddr(block);
}

NNSiFndExpHeapMBlockHead* RemoveMBlock(NNSiFndExpMBlockList* list, NNSiFndExpHeapMBlockHead* block)
{
    NNSiFndExpHeapMBlockHead* const prev = block->pMBHeadPrev;
    NNSiFndExpHeapMBlockHead* const next = block->pMBHeadNext;

    if (prev != NULL)
    {
        prev->pMBHeadNext = next;
    }
    else
    {
        list->head = next;
    }

    if (next != NULL)
    {
        next->pMBHeadPrev = prev;
    }
    else
    {
        list->tail = prev;
    }

    return prev;
}

NNSiFndExpHeapMBlockHead* InsertMBlock(NNSiFndExpMBlockList* list, NNSiFndExpHeapMBlockHead* target, NNSiFndExpHeapMBlockHead* prev)
{
    NNSiFndExpHeapMBlockHead* next;
    target->pMBHeadPrev = prev;
    if (prev != NULL)
    {
        next = prev->pMBHeadNext;
        prev->pMBHeadNext = target;
    }
    else
    {
        next = list->head;
        list->head = target;
    }
    target->pMBHeadNext = next;
    if (next != NULL)
    {
        next->pMBHeadPrev = target;
    }
    else
    {
        list->tail = target;
    }

    return target;
}

NNSiFndExpHeapMBlockHead* InitMBlock(const NNSiMemRegion* pRegion, u16 signature)
{
    NNSiFndExpHeapMBlockHead* block = pRegion->start;
    block->signature = signature;
    block->attribute = 0;
    block->blockSize = GetOffsetFromPtr(GetMemPtrForMBlock(block), pRegion->end);
    block->pMBHeadPrev = NULL;
    block->pMBHeadNext = NULL;
    return block;
}
