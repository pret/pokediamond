#ifndef POKEDIAMOND_ARM9_OS_ALLOC_H
#define POKEDIAMOND_ARM9_OS_ALLOC_H

#include "nitro/types.h"
#include "OS_arena.h"
#include "nitro/OS_alloc_shared.h"

Cell* DLAddFront(Cell* list, Cell* cell);
Cell* DLExtract(Cell* list, Cell* cell);
Cell *DLInsert(Cell *original, Cell *inserted);
void* OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size);
void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void *ptr);

#endif //POKEDIAMOND_ARM9_OS_ALLOC_H
