#ifndef POKEDIAMOND_CUSTOM_ALLOCATOR_H
#define POKEDIAMOND_CUSTOM_ALLOCATOR_H

#include "nitro/types.h"

typedef void * (* AllocFunc)(u32 size);
typedef void (* FreeFunc)(void * ptr);

void* CallCustomAllocator(u32 size);
void CallCustomDestructor(void * ptr);
void SetCustomAllocatorAndDestructor(AllocFunc allocator, FreeFunc destructor);

#endif //POKEDIAMOND_CUSTOM_ALLOCATOR_H
