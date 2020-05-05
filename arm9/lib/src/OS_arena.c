//
// Created by red031000 on 2020-04-27.
//
#include "function_target.h"
#include "consts.h"
#include "OS_arena.h"
#include "OS_protectionRegion.h"
#include "OS_emulator.h"

extern BOOL OSi_MainExArenaEnabled;
extern BOOL OSi_Initialized;  // TODO: located at 0x021d36f0
void SDK_MAIN_ARENA_LO(); // TODO: technically this should be defined in the lcf
extern void SDK_SECTION_ARENA_EX_START(); // TODO: technically this should be defined in the lcf
extern void SDK_SECTION_ARENA_ITCM_START(); // TODO: technically this should be defined in the lcf
extern void SDK_SECTION_ARENA_DTCM_START(); // TODO: technically this should be defined in the lcf
extern void SDK_IRQ_STACKSIZE(); // TODO: technically this should be defined in the lcf
extern void SDK_SYS_STACKSIZE(); // TODO: technically this should be defined in the lcf

ARM_FUNC void OS_InitArena() {
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

ARM_FUNC void OS_InitArenaEx() {
    OS_SetArenaHi(2, OS_GetInitArenaHi(OS_ARENA_MAINEX));
    OS_SetArenaLo(2, OS_GetInitArenaLo(OS_ARENA_MAINEX));

    if (!OSi_MainExArenaEnabled || (OS_GetConsoleType() & OS_CONSOLE_SIZE_MASK) == OS_CONSOLE_SIZE_4MB) {
        OS_SetProtectionRegion(1, HW_MAIN_MEM, 4MB);
        OS_SetProtectionRegion(2, HW_MAIN_MEM_MAIN_END, 128KB);
    }
}

ARM_FUNC void* OS_GetArenaHi(OSArenaId id) {
    return OSi_GetArenaInfo().hi[id];
}

ARM_FUNC void* OS_GetArenaLo(OSArenaId id) {
    return OSi_GetArenaInfo().lo[id];
}

ARM_FUNC void* OS_GetInitArenaHi(OSArenaId id) {
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
            u32 irqStackLo = (u32)HW_DTCM_IRQ_STACK_END - (s32)SDK_IRQ_STACKSIZE;
            u32 sysStackLo;

            if (!(s32)SDK_SYS_STACKSIZE) {
                sysStackLo = HW_DTCM;
                if (sysStackLo < (u32)SDK_SECTION_ARENA_DTCM_START) {
                    sysStackLo = (u32)SDK_SECTION_ARENA_DTCM_START;
                }
            }
            else if ((s32)SDK_SYS_STACKSIZE < 0) {
                sysStackLo = (u32)SDK_SECTION_ARENA_DTCM_START - (s32)SDK_SYS_STACKSIZE;
            }
            else {
                sysStackLo = irqStackLo - (s32)SDK_SYS_STACKSIZE;
            }
            return (void*)sysStackLo;
        case OS_ARENA_SHARED:
            return (void *)HW_SHARED_ARENA_HI_DEFAULT;
        case OS_ARENA_WRAM_MAIN:
            return (void *)OSi_WRAM_MAIN_ARENA_HI_DEFAULT;
        default:
            return NULL;
    }
}

ARM_FUNC void* OS_GetInitArenaLo(OSArenaId id) {
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

ARM_FUNC void OS_SetArenaHi(OSArenaId id, void* newHi) {
    OSi_GetArenaInfo().hi[id] = newHi;
}

ARM_FUNC void OS_SetArenaLo(OSArenaId id, void* newLo) {
    OSi_GetArenaInfo().lo[id] = newLo;
}

ARM_FUNC void* OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align) {
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

ARM_FUNC void* OS_AllocFromArenaHi(OSArenaId id, u32 size, u32 align) {
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
