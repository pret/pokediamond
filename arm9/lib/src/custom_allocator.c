#include "global.h"

typedef void * (* AllocFunc)(u32 size);
typedef void (* FreeFunc)(void * ptr);

static FreeFunc sDestructor;
static AllocFunc sAllocator;

// Custom allocator
ARM_FUNC void* CallCustomAllocator(u32 size)
{
    if (sAllocator != NULL)
        return sAllocator(size);
    else
        return OS_AllocFromHeap(OS_ARENA_MAIN, -1, size);
}

// Custom destructor
ARM_FUNC void CallCustomDestructor(void * ptr)
{
    if (sDestructor != NULL)
        sDestructor(ptr);
    else
        OS_FreeToHeap(OS_ARENA_MAIN, -1, ptr);
}

// Custom alloc/free setter
ARM_FUNC void SetCustomAllocatorAndDestructor(AllocFunc allocator, FreeFunc destructor)
{
    sAllocator = allocator;
    sDestructor = destructor;
}
