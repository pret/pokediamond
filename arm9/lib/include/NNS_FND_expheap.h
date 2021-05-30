#ifndef GUARD_NNS_FND_EXPHEAP_H
#define GUARD_NNS_FND_EXPHEAP_H

#include "NNS_FND_heapcommon.h"

NNSFndHeapHandle NNS_FndCreateExpHeapEx(void *startAddress, u32 size, u32 optFlag);
void *NNS_FndAllocFromExpHeapEx(void *param0, u32 param1, s32 param2);
void NNS_FndDestroyExpHeap();
void NNS_FndFreeToExpHeap(void *ptr1, void *ptr2);
u32 NNS_FndGetTotalFreeSizeForExpHeap(void *param0);
void NNS_FndInitAllocatorForExpHeap(u32 param0, void *param1, u32 param2);
u32 NNS_FndGetSizeForMBlockExpHeap(void *param0);
void NNS_FndResizeForMBlockExpHeap(void *ptr1, void *ptr2, u32 param2);

#endif //GUARD_NNS_FND_EXPHEAP_H
