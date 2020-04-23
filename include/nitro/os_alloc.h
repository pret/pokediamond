//
// Created by mart on 4/23/20.
//

#ifndef POKEDIAMOND_OS_ALLOC_H
#define POKEDIAMOND_OS_ALLOC_H

#include "types.h"

typedef enum {
    OS_ARENA_MAIN = 0,
    OS_ARENA_MAIN_SUBPRIV = 1,
    OS_ARENA_MAINEX = 2,
    OS_ARENA_ITCM = 3,
    OS_ARENA_DTCM = 4,
    OS_ARENA_SHARED = 5,
    OS_ARENA_WRAM_MAIN = 6,
    OS_ARENA_WRAM_SUB = 7,
    OS_ARENA_WRAM_SUBPRIV = 8,
    OS_ARENA_MAX = 9
} OSArenaId;

typedef struct {
    void* lo[OS_ARENA_MAX];
    void* hi[OS_ARENA_MAX];
    u16 initialized;
    u8 padding[2];
} OSArenaInfo;

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

void* OSiHeapInfo[OS_ARENA_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

void* OS_AllocFromArenaHi(OSArenaId id, u32 size, u32 align);
void* OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align);
void OS_SetArenaLo(OSArenaId id, void *newLo);
void OS_SetArenaHi(OSArenaId id, void *newHi);
void* OS_GetInitArenaLo(OSArenaId id);
void* OS_GetInitArenaHi(OSArenaId id);
void* OS_GetArenaLo(OSArenaId id);
void* OS_GetArenaHi(OSArenaId id);
void OS_InitArenaEx();
void OS_InitArena();
void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void *ptr);
void* OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size);

#endif //POKEDIAMOND_OS_ALLOC_H
