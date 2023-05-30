#ifndef GUARD_NNS_FND_EXPHEAP_H
#define GUARD_NNS_FND_EXPHEAP_H

#include "NNS_FND_heapcommon.h"

typedef struct NNSiFndExpHeapMBlockHead NNSiFndExpHeapMBlockHead;

struct NNSiFndExpHeapMBlockHead
{
    u16                         signature;      // Signature
    u16                         attribute;      // Attribute
    // [8:groupID]
    // [7:alignment]
    // [1:temporary flag]

    u32                         blockSize;      // Block size (data area only)

    NNSiFndExpHeapMBlockHead*   pMBHeadPrev;    // Previous block
    NNSiFndExpHeapMBlockHead*   pMBHeadNext;    // Next block
};

typedef struct NNSiFndExpMBlockList NNSiFndExpMBlockList;

struct NNSiFndExpMBlockList
{
    NNSiFndExpHeapMBlockHead*   head;   // Pointer for memory block linked to header
    NNSiFndExpHeapMBlockHead*   tail;   // Pointer to the memory block linked to the tail of the expanded heap
};

typedef struct NNSiFndExpHeapHead NNSiFndExpHeapHead;

struct NNSiFndExpHeapHead
{
    NNSiFndExpMBlockList        mbFreeList;     // Free list
    NNSiFndExpMBlockList        mbUsedList;     // Used list

    u16                         groupID;        // Current group ID (lower 8 bits only)
    u16                         feature;        // Attribute
};

typedef struct NNSiMemRegion {
    void* start;
    void* end;
} NNSiMemRegion;

NNSFndHeapHandle NNS_FndCreateExpHeapEx(void *startAddress, u32 size, u16 optFlag);
void *NNS_FndAllocFromExpHeapEx(NNSFndHeapHandle heap, u32 size, int alignment);
void NNS_FndDestroyExpHeap(NNSFndHeapHandle heap);
void NNS_FndFreeToExpHeap(NNSFndHeapHandle heap, void *memBlock);
u32 NNS_FndGetTotalFreeSizeForExpHeap(NNSFndHeapHandle heap);
u32 NNS_FndGetSizeForMBlockExpHeap(const void *memBlock);
u32 NNS_FndResizeForMBlockExpHeap(NNSFndHeapHandle heap, void *memBlock, u32 size);
NNSiFndExpHeapMBlockHead* InsertMBlock(NNSiFndExpMBlockList* list, NNSiFndExpHeapMBlockHead* target, NNSiFndExpHeapMBlockHead* prev);
NNSiFndExpHeapMBlockHead* InitMBlock(const NNSiMemRegion* pRegion, u16 signature);
NNSiFndHeapHead* InitExpHeap(void* startAddress, void* endAddress, u16 optFlag);
void* AllocUsedBlockFromFreeBlock(NNSiFndExpHeapHead* pEHHead, NNSiFndExpHeapMBlockHead* pMBHeadFree, void* mblock, u32 size, u16 direction);
void GetRegionOfMBlock(NNSiMemRegion* region, NNSiFndExpHeapMBlockHead* block);
void* AllocFromHead(NNSiFndHeapHead* pHeapHd, u32 size, int alignment);
void* AllocFromTail(NNSiFndHeapHead* pHeapHd, u32 size, int alignment);
BOOL RecycleRegion(NNSiFndExpHeapHead* pEHHead, const NNSiMemRegion* pRegion);
NNSiFndExpHeapMBlockHead* RemoveMBlock(NNSiFndExpMBlockList* list, NNSiFndExpHeapMBlockHead* block);

#define             NNS_FndCreateExpHeap(startAddress, size) \
                        NNS_FndCreateExpHeapEx(startAddress, size, 0)
#define             NNS_FndAllocFromExpHeap(heap, size) \
                        NNS_FndAllocFromExpHeapEx(heap, size, NNS_FND_HEAP_DEFAULT_ALIGNMENT)


#endif //GUARD_NNS_FND_EXPHEAP_H
