//
// Created by mart on 4/12/20.
//

#ifndef POKEDIAMOND_OS_H
#define POKEDIAMOND_OS_H

#include "types.h"
#include "consts.h"

typedef enum {
    OS_PROCMODE_USER=16,
    OS_PROCMODE_FIQ=17,
    OS_PROCMODE_IRQ=18,
    OS_PROCMODE_SVC=19,
    OS_PROCMODE_ABORT=23,
    OS_PROCMODE_UNDEF=27,
    OS_PROCMODE_SYS=31
} OSProcMode;

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

typedef enum {
    OS_INTRMODE_IRQ_DISABLE = HW_PSR_IRQ_DISABLE,
    OS_INTRMODE_IRQ_ENABLE = 0
} OSIntrMode_Irq;

typedef enum {
    OS_INTRMODE_FIQ_DISABLE = HW_PSR_FIQ_DISABLE,
    OS_INTRMODE_FIQ_ENABLE = 0
} OSIntrMode_Fiq;

typedef union {
    OSIntrMode_Fiq mode_fiq;
    OSIntrMode_Irq mode_irq;
} OSIntrMode;

typedef struct {
    void   *lo[OS_ARENA_MAX];
    void   *hi[OS_ARENA_MAX];
    u16     initialized;
    u8      padding[2];
} OSArenaInfo;

OSProcMode OS_GetProcMode();
OSIntrMode OS_DisableInterrupts();
OSIntrMode OS_RestoreInterrupts(register OSIntrMode state);

void* OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align);
void* OS_AllocFromArenaHi(OSArenaId id, u32 size, u32 align);

void OS_SetArenaHi(OSArenaId id, void *newHi);
void OS_SetArenaLo(OSArenaId id, void *newLo);

void* OS_GetArenaHi(OSArenaId id);
void* OS_GetArenaLo(OSArenaId id);

#endif //POKEDIAMOND_OS_H
