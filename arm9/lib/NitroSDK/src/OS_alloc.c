//
// Created by mart on 4/23/20.
//
#include "function_target.h"
#include "OS_alloc.h"
#include "consts.h"
#include "OS_system.h"

void* OSiHeapInfo[OS_ARENA_MAX];

ARM_FUNC Cell* DLAddFront(Cell* list, Cell* cell)
{
    cell->next = list;
    cell->prev = NULL;

    if (list != NULL)
        list->prev = cell;
    return cell;
}

ARM_FUNC Cell* DLExtract(Cell* list, Cell* cell)
{
    if (cell->next) {
        cell->next->prev = cell->prev;
    }
    if (cell->prev == NULL) {
        list = cell->next;
    } else {
        cell->prev->next = cell->next;
    }
    return list;
}

ARM_FUNC Cell *DLInsert(Cell *original, Cell *inserted)
{
    Cell *prevCell = NULL;
    Cell *nextCell = original;


    for (nextCell = original, prevCell = NULL; nextCell; prevCell = nextCell, nextCell = nextCell->next)
    {
        if (inserted <= nextCell)
            break;
    }

    inserted->next = nextCell;
    inserted->prev = prevCell;

    if (nextCell != NULL)
    {
        nextCell->prev = inserted;
        Cell * temp = (Cell *)((char *)inserted + inserted->size);
        if (temp == nextCell)
        {
            inserted->size += nextCell->size;
            nextCell = nextCell->next;
            inserted->next = nextCell;
            if (nextCell != NULL)
                nextCell->prev = inserted;
        }
    }

    if (prevCell != NULL)
    {
        prevCell->next = inserted;
        Cell * temp = (Cell *)((char *)prevCell + prevCell->size);

        if (temp != inserted)
            return original;

        prevCell->size += inserted->size;
        prevCell->next = nextCell;
        if (nextCell != NULL)
            nextCell->prev = prevCell;

        return original;
    }

    return inserted;
}

#define HEADERSIZE OSi_ROUND(sizeof(Cell), 32)
#define MINOBJSIZE (HEADERSIZE+32)

ARM_FUNC void* OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size) {
    OSHeapInfo* heapInfo;
    HeapDesc* hd;
    Cell* cell;
    Cell* newCell;
    long leftoverSize;

    OSIntrMode enabled = OS_DisableInterrupts();
    heapInfo = OSiHeapInfo[id];
    if (!heapInfo) {
        (void)OS_RestoreInterrupts(enabled);
        return NULL;
    }

    if (heap < 0) {
        heap = heapInfo->currentHeap;
    }

    hd = &heapInfo->heapArray[heap];

    size += HEADERSIZE;
    size = OSi_ROUND(size, 32);

    for (cell = hd->free; cell != NULL; cell = cell->next) {
        if ((long)size <= cell->size) {
            break;
        }
    }

    if (cell == NULL) {
        (void)OS_RestoreInterrupts(enabled);
        return NULL;
    }

    leftoverSize = cell->size - (long)size;
    if (leftoverSize < MINOBJSIZE) {
        hd->free = DLExtract(hd->free, cell);
    } else {
        cell->size = (long)size;

        newCell = (Cell *) ((char *)cell + size);
        newCell->size = leftoverSize;

        newCell->prev = cell->prev;
        newCell->next = cell->next;

        if (newCell->next != NULL) {
            newCell->next->prev = newCell;
        }

        if (newCell->prev != NULL) {
            newCell->prev->next = newCell;
        } else {
            hd->free = newCell;
        }
    }

    hd->allocated = DLAddFront(hd->allocated, cell);

    (void)OS_RestoreInterrupts(enabled);
    return (void *)((char *)cell + HEADERSIZE);
}

ARM_FUNC void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void* ptr) {
    OSHeapInfo *heapInfo;
    HeapDesc *hd;
    Cell   *cell;

    OSIntrMode enabled = OS_DisableInterrupts();
    heapInfo = OSiHeapInfo[id];

    if (heap < 0) {
        heap = heapInfo->currentHeap;
    }

    cell = (Cell *) ((char *)ptr - HEADERSIZE);
    hd = &heapInfo->heapArray[heap];

    hd->allocated = DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell);

    (void)OS_RestoreInterrupts(enabled);
}
