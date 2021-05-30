#ifndef GUARD_NNS_FND_HEAPCOMMON_H
#define GUARD_NNS_FND_HEAPCOMMON_H

#include "NNS_FND_list.h"

typedef struct NNSiFndHeapHead NNSiFndHeapHead;

struct NNSiFndHeapHead
{
    u32             signature;

    NNSFndLink      link;
    NNSFndList      childList;

    void*           heapStart;      // Heap start address
    void*           heapEnd;        // Heap end (+1) address

    u32             attribute;      // Attribute
    // [8:Option flag]
};

typedef NNSiFndHeapHead* NNSFndHeapHandle;   // Type to represent heap handle

#endif //GUARD_NNS_FND_HEAPCOMMON_H
