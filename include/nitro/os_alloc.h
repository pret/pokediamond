//
// Created by mart on 4/23/20.
//

#ifndef POKEDIAMOND_OS_ALLOC_H
#define POKEDIAMOND_OS_ALLOC_H

#include "types.h"
#include "os_arena.h"

typedef int OSHeapHandle;

typedef struct Cell Cell;

struct Cell {
    Cell* prev;
    Cell* next;
    long size;
};

typedef struct {
    long size;
    Cell *free;
    Cell *allocated;
} HeapDesc;

typedef struct {
    volatile OSHeapHandle currentHeap;
    int numHeaps;
    void* arenaStart;
    void* arenaEnd;
    HeapDesc* heapArray;
} OSHeapInfo;

void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void *ptr);
void* OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size);

#endif //POKEDIAMOND_OS_ALLOC_H
