#include "global.h"

typedef void * (* AllocFunc)(u32 size);
typedef void (* FreeFunc)(void * ptr);

AllocFunc gUnk021C8C70;
FreeFunc gUnk021C8C74;

// Custom allocator
ARM_FUNC void* FUN_020910A4(u32 size)
{
    if (gUnk021C8C70 != NULL)
        return gUnk021C8C70(size);
    else
        return OS_AllocFromHeap(OS_ARENA_MAIN, -1, size);
}

// Custom destructor
ARM_FUNC void FUN_0209105C(void * ptr)
{
    if (gUnk021C8C74 != NULL)
        gUnk021C8C74(ptr);
    else
        OS_FreeToHeap(OS_ARENA_MAIN, -1, ptr);
}

// Custom alloc/free setter
ARM_FUNC void SetCustomAllocator(AllocFunc allocator, FreeFunc destructor)
{
    gUnk021C8C70 = allocator;
    gUnk021C8C74 = destructor;
}
