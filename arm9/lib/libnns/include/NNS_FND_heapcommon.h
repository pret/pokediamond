#ifndef GUARD_NNS_FND_HEAPCOMMON_H
#define GUARD_NNS_FND_HEAPCOMMON_H

#include "NNS_FND_list.h"

#define NNS_FND_HEAP_DEFAULT_ALIGNMENT          4

typedef struct NNSiFndHeapHead NNSiFndHeapHead;

typedef s32 NNSiIntPtr;
typedef u32 NNSiUIntPtr;

#define NNSi_FndGetBitValue(data, st, bits) (((data) >>(st)) & ((1 <<(bits)) -1))
#define NNSi_FndSetBitValue(data, st, bits, val) do { \
    u32 maskBits = (u32)((1 << (bits)) - 1);          \
    u32 newVal = (val) & maskBits;                    \
    (void)(maskBits <<= st);                          \
    (data) &= ~maskBits;                              \
    (data) |= newVal << (st);                         \
} while (FALSE);

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

static inline NNSiUIntPtr NNSiGetUIntPtr(const void* ptr)
{
    return (NNSiUIntPtr)ptr;
}

static inline u32 GetOffsetFromPtr(const void* start, const void* end)
{
    return NNSiGetUIntPtr(end) - NNSiGetUIntPtr(start);
}

static inline void* AddU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) + val );
}

static inline const void* AddU32ToCPtr(const void* ptr, u32 val)
{
    return (const void*)( NNSiGetUIntPtr(ptr) + val );
}

static inline void* SubU32ToPtr(void* ptr, u32 val)
{
    return (void*)(NNSiGetUIntPtr(ptr) - val);
}

static inline const void* SubU32ToCPtr(const void* ptr, u32 val)
{
    return (const void*)(NNSiGetUIntPtr(ptr) - val);
}

static inline int ComparePtr(const void* a, const void* b)
{
    const u8* wa = a;
    const u8* wb = b;

    return wa - wb;
}


static inline u16 GetOptForHeap(const NNSiFndHeapHead* pHeapHd)
{
    return (u16)NNSi_FndGetBitValue(pHeapHd->attribute, 0, 8);
}

static inline void SetOptForHeap(
    NNSiFndHeapHead*    pHeapHd,
    u16                 optFlag
    )
{
    NNSi_FndSetBitValue(pHeapHd->attribute, 0, 8, optFlag);
}

#endif //GUARD_NNS_FND_HEAPCOMMON_H
