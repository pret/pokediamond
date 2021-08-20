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

static inline void SetAllocDirForMBlock(NNSiFndExpHeapMBlockHead* pEHMBHead, u16 direction)
{
    NNSi_FndSetBitValue(pEHMBHead->attribute, 15, 1, direction);
}

static inline void SetAlignmentForMBlock(NNSiFndExpHeapMBlockHead* pEHMBHead, u16 alignment)
{
    NNSi_FndSetBitValue(pEHMBHead->attribute, 8, 7, alignment);
}

static inline void SetGroupIDForMBlock(NNSiFndExpHeapMBlockHead* pEHMBHead, u16 groupID)
{
    NNSi_FndSetBitValue(pEHMBHead->attribute, 0, 8, groupID);
}

static inline void* GetMemPtrForMBlock(NNSiFndExpHeapMBlockHead* block)
{
    return AddU32ToPtr(block, sizeof(NNSiFndExpHeapMBlockHead));
}

static inline void* GetMBlockEndAddr(NNSiFndExpHeapMBlockHead* block)
{
    return AddU32ToPtr(GetMemPtrForMBlock(block), block->blockSize);
}

static inline void SetAllocMode(NNSiFndExpHeapHead* pExHeapHd, u16 mode)
{
    NNSi_FndSetBitValue(pExHeapHd->feature, 0, 1, mode);
}

static inline NNSiFndExpHeapHead* GetExpHeapHeadPtrFromHeapHead(NNSiFndHeapHead* pHHead)
{
    return AddU32ToPtr(pHHead, sizeof(NNSiFndHeapHead));
}

static inline NNSiFndHeapHead* GetHeapHeadPtrFromExpHeapHead(NNSiFndExpHeapHead* pEHHead)
{
    return SubU32ToPtr(pEHHead, sizeof(NNSiFndHeapHead));
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

static inline NNSiFndExpHeapMBlockHead* InitFreeMBlock(const NNSiMemRegion* region)
{
    return InitMBlock(region, 0x4652);
}

NNSiFndHeapHead* InitExpHeap(void* startAddress, void* endAddress, u16 optFlag)
{
    NNSiFndHeapHead* pHeapHd = (NNSiFndHeapHead*)startAddress;
    NNSiFndExpHeapHead* pExpHeapHd = GetExpHeapHeadPtrFromHeapHead(pHeapHd);
    NNSi_FndInitHeapHead(pHeapHd, 0x45585048, AddU32ToPtr(pExpHeapHd, sizeof(NNSiFndExpHeapHead)), endAddress, optFlag);
    pExpHeapHd->groupID = 0;
    pExpHeapHd->feature = 0;
    SetAllocMode(pExpHeapHd, 0);

    NNSiFndExpHeapMBlockHead* pMBHead;
    NNSiMemRegion region;

    region.start = pHeapHd->heapStart;
    region.end = pHeapHd->heapEnd;
    pMBHead = InitFreeMBlock(&region);

    pExpHeapHd->mbFreeList.head = pMBHead;
    pExpHeapHd->mbFreeList.tail = pMBHead;
    pExpHeapHd->mbUsedList.head = NULL;
    pExpHeapHd->mbUsedList.tail = NULL;

    return pHeapHd;
}

static inline void AppendMBlock(NNSiFndExpMBlockList* list, NNSiFndExpHeapMBlockHead* block)
{
    (void) InsertMBlock(list, block, list->tail);
}

void* AllocUsedBlockFromFreeBlock(NNSiFndExpHeapHead* pEHHead, NNSiFndExpHeapMBlockHead* pMBHeadFree, void* mblock, u32 size, u16 direction)
{
    NNSiMemRegion freeRgnT;
    NNSiMemRegion freeRgnB;
    NNSiFndExpHeapMBlockHead* pMBHeadFreePrev;

    GetRegionOfMBlock(&freeRgnT, pMBHeadFree);

    freeRgnB.end = freeRgnT.end;
    freeRgnB.start = AddU32ToPtr(mblock, size);
    freeRgnT.end = SubU32ToPtr(mblock, sizeof(NNSiFndExpHeapMBlockHead));

    pMBHeadFreePrev = RemoveMBlock(&pEHHead->mbFreeList, pMBHeadFree);

    if (GetOffsetFromPtr(freeRgnT.start, freeRgnT.end) < sizeof(NNSiFndExpHeapMBlockHead))
    {
        freeRgnT.end = freeRgnT.start;
    }
    else
    {
        pMBHeadFreePrev = InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&freeRgnT), pMBHeadFreePrev);
    }
    if (GetOffsetFromPtr(freeRgnB.start, freeRgnB.end) < sizeof(NNSiFndExpHeapMBlockHead))
    {
        freeRgnB.start= freeRgnB.end;
    }
    else
    {
        (void)InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&freeRgnB), pMBHeadFreePrev);
    }

    FillAllocMemory(GetHeapHeadPtrFromExpHeapHead(pEHHead), freeRgnT.end, GetOffsetFromPtr(freeRgnT.end, freeRgnB.start));

    NNSiFndExpHeapMBlockHead* pMBHeadNewUsed;
    NNSiMemRegion region;

    region.start = SubU32ToPtr(mblock, sizeof(NNSiFndExpHeapMBlockHead));
    region.end = freeRgnB.start;

    pMBHeadNewUsed = InitMBlock(&region, 0x5544);
    SetAllocDirForMBlock(pMBHeadNewUsed, direction);
    SetAlignmentForMBlock(pMBHeadNewUsed, (u16)GetOffsetFromPtr(freeRgnT.end, pMBHeadNewUsed));
    SetGroupIDForMBlock(pMBHeadNewUsed, pEHHead->groupID);
    AppendMBlock(&pEHHead->mbUsedList, pMBHeadNewUsed);

    return mblock;
}
