//
// Created by mart on 4/23/20.
//

#include "os_alloc.h"
#include "consts.h"
#include "os_system.h"

extern u32 OS_GetConsoleType();
extern Cell* DLInsert(Cell* list, Cell* cell);
extern Cell* DLAddFront(Cell* list, Cell* cell);

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

#ifdef MATCH_ASM
asm static Cell* DLExtract(Cell* list, Cell* cell)
{
    ldr r3, [r1, #0x4]
    cmp r3, #0x0
    ldrne r2, [r1, #0x0]
    strne r2, [r3, #0x0]
    ldr r2, [r1, #0x0]
    cmp r2, #0x0
    ldreq r0, [r1, #0x4]
    ldrne r1, [r1, #0x4]
    strne r1, [r2, #0x4]
    bx lr
}
#else
static Cell* DLExtract(Cell* list, Cell* cell)
{
    if (cell->next) {
        cell->prev = cell->next->prev;
    }
    if (cell->prev) {
        cell->prev->next = cell->next;
        return list;
    }
    else {
        return cell->next;
    }
}
#endif

#define HEADERSIZE OSi_ROUND(sizeof(Cell), 32)
#define MINOBJSIZE (HEADERSIZE+32)

#ifdef MATCH_ASM
asm void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void* ptr) {
    stmdb sp!, {r4-r7, lr}
    sub sp,sp,#0x4
    mov r7,r0
    mov r5,r1
    mov r4,r2
    bl OS_DisableInterrupts
    ldr r1,=OSiHeapInfo
    mov r6,r0
    ldr r0,[r1,r7,lsl #0x2]
    cmp r5,#0x0
    ldrlt r5,[r0,#0x0]
    ldr r1,[r0,#0x10]
    mov r0,#0xc
    mla r7,r5,r0,r1
    sub r4,r4,#0x20
    ldr r0,[r7,#0x8]
    mov r1,r4
    bl DLExtract
    str r0,[r7,#0x8]
    ldr r0,[r7,#0x4]
    mov r1,r4
    bl DLInsert
    str r0,[r7,#0x4]
    mov r0,r6
    bl OS_RestoreInterrupts
    add sp,sp,#0x4
    ldmia sp!,{ r4-r7, lr }
    bx lr
}
#else
void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void* ptr) {
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

    OS_RestoreInterrupts(enabled);
}
#endif

#ifdef MATCH_ASM
asm void* OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size) {
    stmdb sp!, {r4-r7,lr}
    sub sp, sp, #0x4
    mov r6, r0
    mov r5, r1
    mov r7, r2
    bl OS_DisableInterrupts
    ldr r1, =OSiHeapInfo
    mov r4, r0
    ldr r1, [r1, r6, lsl #0x2]
    cmp r1, #0x0
    bne _020CC7AC
    bl OS_RestoreInterrupts
    add sp, sp, #0x4
    mov r0, #0x0
    ldmia sp!, {r4-r7,lr}
    bx lr
_020CC7AC:
    cmp r5, #0x0
    ldrlt r5, [r1, #0x0]
    ldr r1, [r1, #0x10]
    mov r0, #0xc
    mla r6, r5, r0, r1
    ldr r0, [r6, #0x4]
    add r1, r7, #0x20
    add r1, r1, #0x1f
    mov r5, r0
    cmp r0, #0x0
    bic r7, r1, #0x1f
    beq _020CC7F4
_020CC7DC:
    ldr r1, [r5, #0x8]
    cmp r7, r1
    ble _020CC7F4
    ldr r5, [r5, #0x4]
    cmp r5, #0x0
    bne _020CC7DC
_020CC7F4:
    cmp r5, #0x0
    bne _020CC814
    mov r0, r4
    bl OS_RestoreInterrupts
    add sp, sp, #0x4
    mov r0, #0x0
    ldmia sp!, {r4-r7,lr}
    bx lr
_020CC814:
    ldr r1, [r5, #0x8]
    sub r1, r1, r7
    cmp r1, #0x40
    bhs _020CC834
    mov r1, r5
    bl DLExtract
    str r0, [r6, #0x4]
    b _020CC86C
_020CC834:
    str r7, [r5, #0x8]
    add r2, r5, r7
    str r1, [r2, #0x8]
    ldr r0, [r5, #0x0]
    str r0, [r5, r7]
    ldr r0, [r5, #0x4]
    str r0, [r2, #0x4]
    ldr r0, [r2, #0x4]
    cmp r0, #0x0
    strne r2, [r0, #0x0]
    ldr r0, [r2, #0x0]
    cmp r0, #0x0
    strne r2, [r0, #0x4]
    streq r2, [r6, #0x4]
_020CC86C:
    ldr r0, [r6, #0x8]
    mov r1, r5
    bl DLAddFront
    str r0, [r6, #0x8]
    mov r0, r4
    bl OS_RestoreInterrupts
    add r0, r5, #0x20
    add sp, sp, #0x4
    ldmia sp!, {r4-r7,lr}
    bx lr
}
#else
void* OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size) {
    OSHeapInfo* heapInfo;
    HeapDesc* hd;
    Cell* cell;
    Cell* newCell;
    long leftoverSize;

    OSIntrMode enabled = OS_DisableInterrupts();
    heapInfo = OSiHeapInfo[id];
    if (!heapInfo) {
        OS_RestoreInterrupts(enabled);
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
        OS_RestoreInterrupts(enabled);
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

    OS_RestoreInterrupts(enabled);
    return (void *)((char *)cell + HEADERSIZE);
}
#endif