#include "consts.h"
#include "OS_alloc.h"
#include "OS_system.h"
#include "code32.h"

void* OSiHeapInfo[OS_ARENA_MAX];

Cell* DLAddFront(Cell* list, Cell* cell)
{
    cell->next = list;
    cell->prev = NULL;

    if (list != NULL)
        list->prev = cell;
    return cell;
}

Cell* DLExtract(Cell* list, Cell* cell)
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

Cell *DLInsert(Cell *original, Cell *inserted)
{
    Cell *prevCell;
    Cell *nextCell;

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

void* OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size)
{
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

void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void* ptr)
{
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

OSHeapHandle OS_SetCurrentHeap(OSArenaId id, OSHeapHandle heap)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    OSHeapInfo *heapInfo = OSiHeapInfo[id];
    OSHeapHandle prev = heapInfo->currentHeap;
    heapInfo->currentHeap = heap;

    (void)OS_RestoreInterrupts(enabled);
    return prev;
}

void *OS_InitAlloc(OSArenaId id, void *arenaStart, void *arenaEnd, s32 maxHeaps)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    OSHeapInfo *heapInfo = arenaStart;
    OSiHeapInfo[id] = heapInfo;

    u32 arraySize = sizeof(HeapDesc) * maxHeaps;
    heapInfo->heapArray = (void *)((u32)arenaStart + sizeof(OSHeapInfo));
    heapInfo->numHeaps = maxHeaps;

    for (OSHeapHandle i = 0; i < heapInfo->numHeaps; i++)
    {
        HeapDesc *hd = &heapInfo->heapArray[i];

        hd->size = -1;
        hd->free = hd->allocated = NULL;
    }

    heapInfo->currentHeap = -1;

    arenaStart = (void *)((char *)heapInfo->heapArray + arraySize);
    arenaStart = (void *)OSi_ROUND(arenaStart, 32);

    heapInfo->arenaStart = arenaStart;
    heapInfo->arenaEnd = (void *)OSi_TRUNC(arenaEnd, 32);

    (void)OS_RestoreInterrupts(enabled);
    return heapInfo->arenaStart;
}

OSHeapHandle OS_CreateHeap(OSArenaId id, void *start, void *end)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    OSHeapInfo *heapInfo = OSiHeapInfo[id];

    start = (void *)OSi_ROUND(start, 32);
    end = (void *)OSi_TRUNC(end, 32);

    for (OSHeapHandle heap = 0; heap < heapInfo->numHeaps; heap++)
    {
        HeapDesc *hd = &heapInfo->heapArray[heap];
        if (hd->size < 0)
        {
            hd->size = (s8 *)end - (s8 *)start;

            Cell *cell = (Cell *)start;
            cell->prev = NULL;
            cell->next = NULL;
            cell->size = hd->size;

            hd->free = cell;
            hd->allocated = 0;

            (void)OS_RestoreInterrupts(enabled);
            return heap;
        }
    }

    (void)OS_RestoreInterrupts(enabled);
    return -1;
}

//wtf nintendo is this shit
#define OSi_CHECK(exp)                      \
    do                                      \
    {                                       \
        if (!(exp))                         \
        {                                   \
            goto exit_OS_CheckHeap;         \
        }                                   \
    } while (0)

s32 OS_CheckHeap(OSArenaId id, OSHeapHandle heap)
{
    OSHeapInfo *heapInfo;
    HeapDesc *hd;
    Cell *cell;
    s32 total = 0;
    s32 free = 0;
    s32 retValue = -1;
    OSIntrMode enabled = OS_DisableInterrupts();

    heapInfo = OSiHeapInfo[id];

    if (heap == (OSHeapHandle)-1)
    {
        heap = heapInfo->currentHeap;
    }

    OSi_CHECK(heapInfo->heapArray);
    OSi_CHECK(0 <= heap && heap < heapInfo->numHeaps);

    hd = &heapInfo->heapArray[heap];
    OSi_CHECK(0 <= hd->size);

    OSi_CHECK(hd->allocated == NULL || hd->allocated->prev == NULL);
    for (cell = hd->allocated; cell; cell = cell->next)
    {
        OSi_CHECK(OSi_InRange(cell, heapInfo->arenaStart, heapInfo->arenaEnd));
        OSi_CHECK(OSi_OFFSET(cell, 32) == 0);
        OSi_CHECK(cell->next == NULL || cell->next->prev == cell);
        OSi_CHECK(MINOBJSIZE <= cell->size);
        OSi_CHECK(OSi_OFFSET(cell->size, 32) == 0);

        total += cell->size;
        OSi_CHECK(0 < total && total <= hd->size);
    }

    OSi_CHECK(hd->free == NULL || hd->free->prev == NULL);
    for (cell = hd->free; cell; cell = cell->next)
    {
        OSi_CHECK(OSi_InRange(cell, heapInfo->arenaStart, heapInfo->arenaEnd));
        OSi_CHECK(OSi_OFFSET(cell, 32) == 0);
        OSi_CHECK(cell->next == NULL || cell->next->prev == cell);
        OSi_CHECK(MINOBJSIZE <= cell->size);
        OSi_CHECK(OSi_OFFSET(cell->size, 32) == 0);
        OSi_CHECK(cell->next == NULL || (s8 *)cell + cell->size < (s8 *)cell->next);

        total += cell->size;
        free += cell->size - HEADERSIZE;

        OSi_CHECK(0 < total && total <= hd->size);
    }

    OSi_CHECK(total == hd->size);
    retValue = free;

exit_OS_CheckHeap:
    (void)OS_RestoreInterrupts(enabled);
    return retValue;
}
