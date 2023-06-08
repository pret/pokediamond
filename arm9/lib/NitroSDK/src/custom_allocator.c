#include "custom_allocator.h"

#include "nitro/types.h"
#include "OS_alloc.h"
#include "code32.h"

static FreeFunc sDestructor;
static AllocFunc sAllocator;

// Custom allocator
void* CallCustomAllocator(u32 size)
{
    if (sAllocator != NULL)
        return sAllocator(size);
    else
        return OS_AllocFromHeap(OS_ARENA_MAIN, -1, size);
}

// Custom destructor
void CallCustomDestructor(void * ptr)
{
    if (sDestructor != NULL)
        sDestructor(ptr);
    else
        OS_FreeToHeap(OS_ARENA_MAIN, -1, ptr);
}

// Custom alloc/free setter
void SetCustomAllocatorAndDestructor(AllocFunc allocator, FreeFunc destructor)
{
    sAllocator = allocator;
    sDestructor = destructor;
}
