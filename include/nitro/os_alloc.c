//
// Created by mart on 4/23/20.
//

#include "os_alloc.h"
#include "consts.h"
#include "os_system.h"
#include "os_protectionRegion.h"

extern BOOL OSi_MainExArenaEnabled;
extern BOOL OSi_Initialized;  // TODO: located at 0x021d36f0
extern u32 SDK_MAIN_ARENA_LO; // TODO: technically this should be defined in the lcf
extern u32 SDK_SECTION_ARENA_EX_START; // TODO: technically this should be defined in the lcf
extern u32 SDK_SECTION_ARENA_ITCM_START; // TODO: technically this should be defined in the lcf
extern u32 SDK_SECTION_ARENA_DTCM_START; // TODO: technically this should be defined in the lcf
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

#ifdef MATCH_ASM
asm void* OS_AllocFromArenaHi(OSArenaId id, u32 size, u32 align) {
    stmdb sp!,{ r4-r6, lr }
    mov r4,r0
    mov r6,r1
    mov r5,r2
    bl OS_GetArenaHi
    cmp r0,#0x0
    moveq r0,#0x0
    ldmeqia sp!,{ r4-r6, lr }
    bxeq lr
    sub r1,r5,#0x1
    mvn r2,r1
    and r0,r0,r2
    sub r1,r0,r6
    mov r0,r4
    and r5,r1,r2
    bl OS_GetArenaLo
    cmp r5,r0
    movcc r0,#0x0
    ldmccia sp!,{ r4-r6, lr }
    bxcc lr
    mov r0,r4
    mov r1,r5
    bl OS_SetArenaHi
    mov r0,r5
    ldmia sp!,{ r4-r6, lr }
    bx lr
}
#else
void* OS_AllocFromArenaHi(OSArenaId id, u32 size, u32 align) {
    void* ptr;
    u8* arenaHi;

    arenaHi = OS_GetArenaHi(id);
    if (!arenaHi) {
        return NULL;
    }

    arenaHi = (u8 *)OSi_TRUNC(arenaHi, align);
    arenaHi -= size;
    arenaHi = ptr = (void *)OSi_TRUNC(arenaHi, align);

    if (arenaHi < (u8*)OS_GetArenaLo(id)) {
        return NULL;
    }

    OS_SetArenaHi(id, arenaHi);

    return ptr;
}
#endif

#ifdef MATCH_ASM
asm void* OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align) {
    stmdb sp!,{ r4-r7, lr }
    sub sp,sp,#0x4
    mov r7,r0
    mov r6,r1
    mov r5,r2
    bl OS_GetArenaLo
    cmp r0,#0x0
    addeq sp,sp,#0x4
    moveq r0,#0x0
    ldmeqia sp!,{ r4-r7, lr }
    bxeq lr
    add r0,r0,r5
    sub r1,r5,#0x1
    mvn r2,r1
    sub r0,r0,#0x1
    and r4,r2,r0
    add r0,r4,r6
    add r0,r0,r5
    sub r1,r0,#0x1
    mov r0,r7
    and r5,r2,r1
    bl OS_GetArenaHi
    cmp r5,r0
    addhi sp,sp,#0x4
    movhi r0,#0x0
    ldmhiia sp!,{ r4-r7, lr }
    bxhi lr
    mov r0,r7
    mov r1,r5
    bl OS_SetArenaLo
    mov r0,r4
    add sp,sp,#0x4
    ldmia sp!,{ r4-r7, lr }
    bx lr
}
#else
void* OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align) {
    void* ptr;
    u8* arenaLo;
    ptr = OS_GetArenaLo(id);
    if (!ptr) {
        return NULL;
    }
    arenaLo = ptr = (void *)OSi_ROUND(ptr, align);
    arenaLo += size;
    arenaLo = (u8 *)OSi_ROUND(arenaLo, align);
    if (arenaLo > (u8*)OS_GetArenaHi(id)) {
        return NULL;
    }
    OS_SetArenaLo(id, arenaLo);

    return ptr;
}
#endif

#ifdef MATCH_ASM
asm void OS_SetArenaLo(OSArenaId id, void* newLo) {
    mov r0,r0, lsl #0x2
    add r0,r0,#0x2700000
    add r0,r0,#0xff000
    str r1,[r0,#0xda0]
    bx lr
}
#else
void OS_SetArenaLo(OSArenaId id, void* newLo) {
    OSi_GetArenaInfo().lo[id] = newLo;
}
#endif

#ifdef MATCH_ASM
asm void OS_SetArenaHi(OSArenaId id, void* newHi) {
    mov r0,r0, lsl #0x2
    add r0,r0,#0x2700000
    add r0,r0,#0xff000
    str r1,[r0,#0xdc4]
    bx lr
}
#else
void OS_SetArenaHi(OSArenaId id, void* newHi) {
    OSi_GetArenaInfo().lo[id] = newHi;
}
#endif

#ifdef MATCH_ASM
asm void* OS_GetInitArenaLo(OSArenaId id) {
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020CC3DC
_020CC330:
	b _020CC34C
	b _020CC3DC
	b _020CC35C
	b _020CC39C
	b _020CC3AC
	b _020CC3BC
	b _020CC3CC
_020CC34C:
	add sp, sp, #0x4
	ldr r0, =SDK_MAIN_ARENA_LO
	ldmfd sp!, {lr}
	bx lr
_020CC35C:
	ldr r0, =OSi_MainExArenaEnabled
	ldr r0, [r0]
	cmp r0, #0x0
	beq _020CC37C
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _020CC38C
_020CC37C:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020CC38C:
	add sp, sp, #0x4
	ldr r0, =SDK_SECTION_ARENA_EX_START
	ldmfd sp!, {lr}
	bx lr
_020CC39C:
	add sp, sp, #0x4
	ldr r0, =SDK_SECTION_ARENA_ITCM_START
	ldmfd sp!, {lr}
	bx lr
_020CC3AC:
	add sp, sp, #0x4
	ldr r0, =SDK_SECTION_ARENA_DTCM_START
	ldmfd sp!, {lr}
	bx lr
_020CC3BC:
	add sp, sp, #0x4
	ldr r0, =HW_SHARED_ARENA_LO_DEFAULT
	ldmfd sp!, {lr}
	bx lr
_020CC3CC:
	add sp, sp, #0x4
	ldr r0, =OSi_WRAM_MAIN_ARENA_LO_DEFAULT
	ldmfd sp!, {lr}
	bx lr
_020CC3DC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
}
#else
void* OS_GetInitArenaLo(OSArenaId id) {
    switch (id) {
        case OS_ARENA_MAIN:
            return (void *)SDK_MAIN_ARENA_LO;
        case OS_ARENA_MAINEX:
            if (!OSi_MainExArenaEnabled || (OS_GetConsoleType() & OS_CONSOLE_SIZE_MASK) == OS_CONSOLE_SIZE_4MB) {
                return NULL;
            } else {
                return (void *)SDK_SECTION_ARENA_EX_START;
            }
        case OS_ARENA_ITCM:
            return (void *)SDK_SECTION_ARENA_ITCM_START;
        case OS_ARENA_DTCM:
            return (void *)SDK_SECTION_ARENA_DTCM_START;
        case OS_ARENA_SHARED:
            return (void *)HW_SHARED_ARENA_LO_DEFAULT;
        case OS_ARENA_WRAM_MAIN:
            return (void *)OSi_WRAM_MAIN_ARENA_LO_DEFAULT;
        default:
            return NULL;
    }
}
#endif

#ifdef MATCH_ASM
asm void* OS_GetInitArenaHi(OSArenaId id) {
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020CC508
_020CC41C:
	b _020CC438
	b _020CC508
	b _020CC448
	b _020CC488
	b _020CC498
	b _020CC4E8
	b _020CC4F8
_020CC438:
	add sp, sp, #0x4
	ldr r0, =OSi_MAIN_ARENA_HI_DEFAULT
	ldmfd sp!, {lr}
	bx lr
_020CC448:
	ldr r0, =OSi_MainExArenaEnabled
	ldr r0, [r0]
	cmp r0, #0x0
	beq _020CC468
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _020CC478
_020CC468:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020CC478:
	add sp, sp, #0x4
	mov r0, #OSi_MAINEX_ARENA_HI_DEFAULT
	ldmfd sp!, {lr}
	bx lr
_020CC488:
	add sp, sp, #0x4
	mov r0, #HW_ITCM_ARENA_HI_DEFAULT
	ldmfd sp!, {lr}
	bx lr
_020CC498:
	ldr r0, =0x027E0000
	ldr r1, =0x00000000
	ldr r2, =0x00000400
	add r3, r0, #0x3f80
	cmp r1, #0x0
	sub r2, r3, r2
	bne _020CC4CC
	ldr r1, =0x027E0080
	add sp, sp, #0x4
	cmp r0, r1
	movcc r0, r1
	ldmfd sp!, {lr}
	bx lr
_020CC4CC:
	cmp r1, #0x0
	ldrlt r0, =0x027E0080
	add sp, sp, #0x4
	sublt r0, r0, r1
	subge r0, r2, r1
	ldmfd sp!, {lr}
	bx lr
_020CC4E8:
	add sp, sp, #0x4
	ldr r0, =HW_SHARED_ARENA_HI_DEFAULT
	ldmfd sp!, {lr}
	bx lr
_020CC4F8:
	add sp, sp, #0x4
	ldr r0, =OSi_WRAM_MAIN_ARENA_HI_DEFAULT;
	ldmfd sp!, {lr}
	bx lr
_020CC508:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
}
#else
void* OS_GetInitArenaHi(OSArenaId id) {
    switch (id) {
        case OS_ARENA_MAIN:
            return (void *)OSi_MAIN_ARENA_HI_DEFAULT;
        case OS_ARENA_MAINEX:
            if (!OSi_MainExArenaEnabled || (OS_GetConsoleType() & OS_CONSOLE_SIZE_MASK) == OS_CONSOLE_SIZE_4MB) {
                return (void *)0;
            } else {
                return (void *)OSi_MAINEX_ARENA_HI_DEFAULT;
            }
        case OS_ARENA_ITCM:
            return (void *)HW_ITCM_ARENA_HI_DEFAULT;
        case OS_ARENA_DTCM:
            return (void *)0x027e0080; //todo pretty sure this is incorrect, no constant and doesn't match
        case OS_ARENA_SHARED:
            return (void *)HW_SHARED_ARENA_HI_DEFAULT;
        case OS_ARENA_WRAM_MAIN:
            return (void *)OSi_WRAM_MAIN_ARENA_HI_DEFAULT;
        default:
            return NULL;
    }
}
#endif

#ifdef MATCH_ASM
asm void* OS_GetArenaLo(OSArenaId id) {
    mov r0,r0, lsl #0x2
    add r0,r0,#0x2700000
    add r0,r0,#0xff000
    ldr r0,[r0,#0xda0]
    bx lr
}
#else
void* OS_GetArenaLo(OSArenaId id) {
    return OSi_GetArenaInfo().lo[id];
}
#endif

#ifdef MATCH_ASM
asm void* OS_GetArenaHi(OSArenaId id) {
    mov r0,r0, lsl #0x2
    add r0,r0,#0x2700000
    add r0,r0,#0xff000
    ldr r0,[r0,#0xdc4]
    bx lr
}
#else
void* OS_GetArenaHi(OSArenaId id) {
    return OSi_GetArenaInfo().hi[id];
}
#endif

#ifdef MATCH_ASM
asm void OS_InitArenaEx() {
    stmdb sp!,{ lr }
    sub sp,sp,#0x4
    mov r0,#0x2
    bl OS_GetInitArenaHi
    mov r1,r0
    mov r0,#0x2
    bl OS_SetArenaHi
    mov r0,#0x2
    bl OS_GetInitArenaLo
    mov r1,r0
    mov r0,#0x2
    bl OS_SetArenaLo
    ldr r0, =OSi_MainExArenaEnabled
    ldr r0,[r0,#0x0]
    cmp r0,#0x0
    beq _020CC5B8
    bl OS_GetConsoleType
    and r0,r0,#0x3
    cmp r0,#0x1
    addne sp,sp,#0x4
    ldmneia sp!,{ lr }
    bxne lr
_020CC5B8:
    ldr r0, =0x0200002b
    bl OS_SetProtectionRegion1
    ldr r0, =0x023e0021
    bl OS_SetProtectionRegion2
    add sp,sp,#0x4
    ldmia sp!,{ lr }
    bx lr
}
#else
void OS_InitArenaEx() { //todo figure out what compiler settings will get this to match
    OS_SetArenaHi(2, OS_GetInitArenaHi(OS_ARENA_MAINEX));
    OS_SetArenaLo(2, OS_GetInitArenaLo(OS_ARENA_MAINEX));

    if (!OSi_MainExArenaEnabled || (OS_GetConsoleType() & OS_CONSOLE_SIZE_MASK) == OS_CONSOLE_SIZE_4MB) {
        OS_SetProtectionRegion(1, HW_MAIN_MEM, 4MB);
        OS_SetProtectionRegion(2, HW_MAIN_MEM_MAIN_END, 128KB);
    }
}
#endif

#ifdef MATCH_ASM
asm void OS_InitArena() {
    stmdb sp!,{ lr }
    sub sp,sp,#0x4
    ldr r1, =OSi_Initialized
    ldr r0,[r1,#0x0]
    cmp r0,#0x0
    addne sp,sp,#0x4
    ldmneia sp!,{ lr }
    bxne lr
    mov r2,#0x1
    mov r0,#0x0
    str r2,[r1,#0x0]
    bl OS_GetInitArenaHi
    mov r1,r0
    mov r0,#0x0
    bl OS_SetArenaHi
    mov r0,#0x0
    bl OS_GetInitArenaLo
    mov r1,r0
    mov r0,#0x0
    bl OS_SetArenaLo
    mov r0,#0x2
    mov r1,#0x0
    bl OS_SetArenaLo
    mov r0,#0x2
    mov r1,#0x0
    bl OS_SetArenaHi
    mov r0,#0x3
    bl OS_GetInitArenaHi
    mov r1,r0
    mov r0,#0x3
    bl OS_SetArenaHi
    mov r0,#0x3
    bl OS_GetInitArenaLo
    mov r1,r0
    mov r0,#0x3
    bl OS_SetArenaLo
    mov r0,#0x4
    bl OS_GetInitArenaHi
    mov r1,r0
    mov r0,#0x4
    bl OS_SetArenaHi
    mov r0,#0x4
    bl OS_GetInitArenaLo
    mov r1,r0
    mov r0,#0x4
    bl OS_SetArenaLo
    mov r0,#0x5
    bl OS_GetInitArenaHi
    mov r1,r0
    mov r0,#0x5
    bl OS_SetArenaHi
    mov r0,#0x5
    bl OS_GetInitArenaLo
    mov r1,r0
    mov r0,#0x5
    bl OS_SetArenaLo
    mov r0,#0x6
    bl OS_GetInitArenaHi
    mov r1,r0
    mov r0,#0x6
    bl OS_SetArenaHi
    mov r0,#0x6
    bl OS_GetInitArenaLo
    mov r1,r0
    mov r0,#0x6
    bl OS_SetArenaLo
    add sp,sp,#0x4
    ldmia sp!,{ lr }
    bx lr
}
#else
void OS_InitArena() {
    if (OSi_Initialized) {
        return;
    }
    OSi_Initialized = TRUE;

    OS_SetArenaHi(OS_ARENA_MAIN, OS_GetInitArenaHi(OS_ARENA_MAIN));
    OS_SetArenaLo(OS_ARENA_MAIN, OS_GetInitArenaLo(OS_ARENA_MAIN));

    OS_SetArenaLo(OS_ARENA_MAINEX, (void *)0);
    OS_SetArenaHi(OS_ARENA_MAINEX, (void *)0);

    OS_SetArenaHi(OS_ARENA_ITCM, OS_GetInitArenaHi(OS_ARENA_ITCM));
    OS_SetArenaLo(OS_ARENA_ITCM, OS_GetInitArenaLo(OS_ARENA_ITCM));

    OS_SetArenaHi(OS_ARENA_DTCM, OS_GetInitArenaHi(OS_ARENA_DTCM));
    OS_SetArenaLo(OS_ARENA_DTCM, OS_GetInitArenaLo(OS_ARENA_DTCM));

    OS_SetArenaHi(OS_ARENA_SHARED, OS_GetInitArenaHi(OS_ARENA_SHARED));
    OS_SetArenaLo(OS_ARENA_SHARED, OS_GetInitArenaLo(OS_ARENA_SHARED));

    OS_SetArenaHi(OS_ARENA_WRAM_MAIN, OS_GetInitArenaHi(OS_ARENA_WRAM_MAIN));
    OS_SetArenaLo(OS_ARENA_WRAM_MAIN, OS_GetInitArenaLo(OS_ARENA_WRAM_MAIN));
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