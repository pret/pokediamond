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

static inline void* GetMBlockHeadPtr(void* block)
{
    return SubU32ToPtr(block, sizeof(NNSiFndExpHeapMBlockHead));
}

static inline void* GetMBlockEndAddr(NNSiFndExpHeapMBlockHead* block)
{
    return AddU32ToPtr(GetMemPtrForMBlock(block), block->blockSize);
}

static inline u16 GetAllocMode(NNSiFndExpHeapHead* pExHeapHd)
{
    return NNSi_FndGetBitValue(pExHeapHd->feature, 0, 1);
}

static inline void SetAllocMode(NNSiFndExpHeapHead* pExHeapHd, u16 mode)
{
    NNSi_FndSetBitValue(pExHeapHd->feature, 0, 1, mode);
}

static inline NNSiFndExpHeapHead* GetExpHeapHeadPtrFromHeapHead(NNSiFndHeapHead* pHHead)
{
    return AddU32ToPtr(pHHead, sizeof(NNSiFndHeapHead));
}

static inline NNSiFndExpHeapHead* GetExpHeapHeadPtrFromHandle(NNSFndHeapHandle heap)
{
    return GetExpHeapHeadPtrFromHeapHead(heap);
}

static inline NNSiFndHeapHead* GetHeapHeadPtrFromExpHeapHead(NNSiFndExpHeapHead* pEHHead)
{
    return SubU32ToPtr(pEHHead, sizeof(NNSiFndHeapHead));
}

ARM_FUNC void GetRegionOfMBlock(NNSiMemRegion* region, NNSiFndExpHeapMBlockHead* block)
{
    region->start = SubU32ToPtr(block, GetAlignmentForMBlock(block));
    region->end = GetMBlockEndAddr(block);
}

ARM_FUNC NNSiFndExpHeapMBlockHead* RemoveMBlock(NNSiFndExpMBlockList* list, NNSiFndExpHeapMBlockHead* block)
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

ARM_FUNC NNSiFndExpHeapMBlockHead* InsertMBlock(NNSiFndExpMBlockList* list, NNSiFndExpHeapMBlockHead* target, NNSiFndExpHeapMBlockHead* prev)
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

ARM_FUNC NNSiFndExpHeapMBlockHead* InitMBlock(const NNSiMemRegion* pRegion, u16 signature)
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

ARM_FUNC NNSiFndHeapHead* InitExpHeap(void* startAddress, void* endAddress, u16 optFlag)
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

ARM_FUNC void* AllocUsedBlockFromFreeBlock(NNSiFndExpHeapHead* pEHHead, NNSiFndExpHeapMBlockHead* pMBHeadFree, void* mblock, u32 size, u16 direction)
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

ARM_FUNC void* AllocFromHead(NNSiFndHeapHead* pHeapHd, u32 size, int alignment)
{
    NNSiFndExpHeapHead* pExpHeapHd = GetExpHeapHeadPtrFromHeapHead(pHeapHd);
    const BOOL bAllocFirst = GetAllocMode(pExpHeapHd) == 0;
    NNSiFndExpHeapMBlockHead* pMBlkHd = NULL;
    NNSiFndExpHeapMBlockHead* pMBlkHdFound = NULL;
    u32 foundSize = 0xFFFFFFFF;
    void* foundMBlock = NULL;

    for (pMBlkHd = pExpHeapHd->mbFreeList.head; pMBlkHd; pMBlkHd = pMBlkHd->pMBHeadNext)
    {
        void *const mblock = GetMemPtrForMBlock(pMBlkHd);
        void *const reqMBlock = NNSi_FndRoundUpPtr(mblock, alignment);
        const u32 offset = GetOffsetFromPtr(mblock, reqMBlock);
        if (pMBlkHd->blockSize >= size + offset && foundSize > pMBlkHd->blockSize)
        {
            pMBlkHdFound = pMBlkHd;
            foundSize = pMBlkHd->blockSize;
            foundMBlock = reqMBlock;
            if (bAllocFirst || foundSize == size)
                break;
        }
    }

    if (!pMBlkHdFound)
        return NULL;

    return AllocUsedBlockFromFreeBlock(pExpHeapHd, pMBlkHdFound, foundMBlock, size, 0);
}

ARM_FUNC void* AllocFromTail(NNSiFndHeapHead* pHeapHd, u32 size, int alignment)
{
    NNSiFndExpHeapHead* pExpHeapHd = GetExpHeapHeadPtrFromHeapHead(pHeapHd);
    const BOOL bAllocFirst = GetAllocMode(pExpHeapHd) == 0;
    NNSiFndExpHeapMBlockHead* pMBlkHd = NULL;
    NNSiFndExpHeapMBlockHead* pMBlkHdFound = NULL;
    u32 foundSize = 0xFFFFFFFF;
    void* foundMBlock = NULL;

    for (pMBlkHd = pExpHeapHd->mbFreeList.tail; pMBlkHd; pMBlkHd = pMBlkHd->pMBHeadPrev)
    {
        void *const mblock = GetMemPtrForMBlock(pMBlkHd);
        void *const mBlockEnd = AddU32ToPtr(mblock, pMBlkHd->blockSize);
        void *const reqMBlock = NNSi_FndRoundDownPtr(SubU32ToPtr(mBlockEnd, size), alignment);
        if (ComparePtr(reqMBlock, mblock) >= 0 && foundSize > pMBlkHd->blockSize)
        {
            pMBlkHdFound = pMBlkHd;
            foundSize = pMBlkHd->blockSize;
            foundMBlock = reqMBlock;
            if (bAllocFirst || foundSize == size)
                break;
        }
    }

    if (!pMBlkHdFound)
        return NULL;

    return AllocUsedBlockFromFreeBlock(pExpHeapHd, pMBlkHdFound, foundMBlock, size, 1);
}

ARM_FUNC BOOL RecycleRegion(NNSiFndExpHeapHead* pEHHead, const NNSiMemRegion* pRegion)
{
    NNSiFndExpHeapMBlockHead* pBlkPtrFree = NULL;
    NNSiMemRegion freeRgn = *pRegion;
    NNSiFndExpHeapMBlockHead* pBlk;
    for (pBlk = pEHHead->mbFreeList.head; pBlk; pBlk = pBlk->pMBHeadNext)
    {
        if (pBlk < (NNSiFndExpHeapMBlockHead*)pRegion->start)
        {
            pBlkPtrFree = pBlk;
            continue;
        }
        if (pBlk == pRegion->end)
        {
            freeRgn.end = GetMBlockEndAddr(pBlk);
            (void)RemoveMBlock(&pEHHead->mbFreeList, pBlk);
        }
        break;
    }
    if (pBlkPtrFree && GetMBlockEndAddr(pBlkPtrFree) == pRegion->start)
    {
        freeRgn.start = pBlkPtrFree;
        pBlkPtrFree = RemoveMBlock(&pEHHead->mbFreeList, pBlkPtrFree);
    }
    if (GetOffsetFromPtr(freeRgn.start, freeRgn.end) < sizeof(NNSiFndExpHeapMBlockHead))
        return FALSE;
    InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&freeRgn), pBlkPtrFree);
    return TRUE;
}

ARM_FUNC NNSFndHeapHandle NNS_FndCreateExpHeapEx(void *startAddress, u32 size, u16 optFlag)
{
    void* endAddress = NNSi_FndRoundDownPtr(AddU32ToPtr(startAddress, size), 4);
    startAddress = NNSi_FndRoundUpPtr(startAddress, 4);
    if (NNSiGetUIntPtr(startAddress) > NNSiGetUIntPtr(endAddress) || GetOffsetFromPtr(startAddress, endAddress) < sizeof(NNSiFndHeapHead) + sizeof(NNSiFndExpHeapHead) + sizeof(NNSiFndExpHeapMBlockHead) + 4)
        return NULL;
    return InitExpHeap(startAddress, endAddress, optFlag);
}

ARM_FUNC void NNS_FndDestroyExpHeap(NNSFndHeapHandle handle)
{
    NNSi_FndFinalizeHeap(handle);
}

ARM_FUNC void* NNS_FndAllocFromExpHeapEx(NNSFndHeapHandle handle, u32 size, int alignment)
{
    if (size == 0)
        size = 1;
    size = NNSi_FndRoundUp(size, 4);
    if (alignment >= 0)
        return AllocFromHead(handle, size, alignment);
    else
        return AllocFromTail(handle, size, -alignment);
}

/*
ARM_FUNC u32 NNS_FndResizeForMBlockExpHeap(NNSFndHeapHandle heap, void *memBlock, u32 size)
{
    NNSiFndExpHeapHead* pEHHead;
    NNSiFndExpHeapMBlockHead* pMBHead;
    pEHHead = GetExpHeapHeadPtrFromHandle(heap);
    pMBHead = GetMBlockHeadPtr(memBlock);
    size = NNSi_FndRoundUp(size, 4);
    if (size == pMBHead->blockSize)
        return size;
    if (size > pMBHead->blockSize)
    {
        void* crUsedEnd = GetMBlockEndAddr(pMBHead);
        NNSiFndExpHeapMBlockHead* block;
        for (block = pEHHead->mbFreeList.head; block; block = block->pMBHeadNext)
        {
            if (block == crUsedEnd)
                break;
        }
        if (!block || size > pMBHead->blockSize + sizeof(NNSiFndExpHeapMBlockHead) + block->blockSize)
            return 0;

        NNSiMemRegion rgnNewFree;
        void* oldFreeStart;
        NNSiFndExpHeapMBlockHead* nextBlockPrev;

        GetRegionOfMBlock(&rgnNewFree, block);
        nextBlockPrev = RemoveMBlock(&pEHHead->mbFreeList, block);
        oldFreeStart = rgnNewFree.start;
        rgnNewFree.start = AddU32ToPtr(memBlock, size);
        if (GetOffsetFromPtr(rgnNewFree.start, rgnNewFree.end) < sizeof(NNSiFndExpHeapMBlockHead))
            rgnNewFree.start = rgnNewFree.end;
        pMBHead->blockSize = GetOffsetFromPtr(memBlock, rgnNewFree.start);
        if (GetOffsetFromPtr(rgnNewFree.start, rgnNewFree.end) >= sizeof(NNSiFndExpHeapMBlockHead))
            (void)InsertMBlock(&pEHHead->mbFreeList, InitFreeMBlock(&rgnNewFree), nextBlockPrev);
        FillAllocMemory(heap, oldFreeStart, GetOffsetFromPtr(oldFreeStart, rgnNewFree.start));
    }
    else
    {
        NNSiMemRegion rgnNewFree;
        const u32 oldBlockSize = pMBHead->blockSize;
        rgnNewFree.start = AddU32ToPtr(memBlock, size);
        rgnNewFree.end = GetMBlockEndAddr(pMBHead);
        pMBHead->blockSize = size;
        if (!RecycleRegion(pEHHead, &rgnNewFree))
            pMBHead->blockSize = oldBlockSize;
    }
    return pMBHead->blockSize;
}
*/
