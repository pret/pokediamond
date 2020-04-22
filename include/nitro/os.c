//
// Created by mart on 4/12/20.
//

#include "os.h"
#include "consts.h"

OSProcMode OS_GetProcMode() {
    __asm {
        mrs r0, cpsr
        and r0, r0, #HW_PSR_CPU_MODE_MASK
        bx lr
    }
}

OSIntrMode OS_DisableInterrupts() {
    __asm {
        mrs     r0, cpsr
        orr     r1, r0, #HW_PSR_IRQ_DISABLE
        msr     cpsr_c, r1
        and     r0, r0, #HW_PSR_IRQ_DISABLE
        bx      lr
    }
}

OSIntrMode OS_RestoreInterrupts(OSIntrMode state) {
    __asm {
        mrs     r1, cpsr
        bic     r2, r1, #HW_PSR_IRQ_DISABLE
        orr     r2, r2, r0
        msr     cpsr_c, r2
        and     r0, r1, #HW_PSR_IRQ_DISABLE
        bx      lr
    }
}

void* OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align) {
#ifdef MATCH_ASM
    __asm {
        stmdb sp!,{ r4 r5 r6 r7 lr }
        sub sp,sp,#0x4
        mov r7,r0
        mov r6,r1
        mov r5,r2
        bl OS_GetArenaLo
        cmp r0,#0x0
        addeq sp,sp,#0x4
        moveq r0,#0x0
        ldmeqia sp!,{ r4 r5 r6 r7 lr }
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
        ldmhiia sp!,{ r4 r5 r6 r7 lr }
        bxhi lr
        mov r0,r7
        mov r1,r5
        bl OS_SetArenaLo
        mov r0,r4
        add sp,sp,#0x4
        ldmia sp!,{ r4 r5 r6 r7 lr }
        bx lr
    }
#else
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
#endif
}

void* OS_AllocFromArenaHi(OSArenaId id, u32 size, u32 align) {
#ifdef MATCH_ASM
    __asm {
         stmdb sp!,{ r4 r5 r6 lr }
         mov r4,r0
         mov r6,r1
         mov r5,r2
         bl OS_GetArenaHi
         cmp r0,#0x0
         moveq r0,#0x0
         ldmeqia sp!,{ r4 r5 r6 lr }
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
         ldmccia sp!,{ r4 r5 r6 lr }
         bxcc lr
         mov r0,r4
         mov r1,r5
         bl OS_SetArenaHi
         mov r0,r5
         ldmia sp!,{ r4 r5 r6 lr }
         bx lr
    };
#else
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
#endif
}

void OS_SetArenaHi(OSArenaId id, void *newHi) {
#ifdef MATCH_ASM
    __asm {
        mov r0,r0, lsl #0x2
        add r0,r0,#0x2700000
        add r0,r0,#0xff000
        str r1,[r0,#0xdc4]
        bx lr
    }
#else
    OSi_GetArenaInfo().lo[id] = newHi;
#endif
}

void OS_SetArenaLo(OSArenaId id, void *newLo) {
#ifdef MATCH_ASM
    __asm {
        mov r0,r0, lsl #0x2
        add r0,r0,#0x2700000
        add r0,r0,#0xff000
        str r1,[r0,#0xda0]
        bx lr
    }
#else
    OSi_GetArenaInfo().lo[id] = newLo;
#endif
}

void* OS_GetArenaHi(OSArenaId id) {
#ifdef MATCH_ASM
    __asm {
        mov r0,r0, lsl #0x2
        add r0,r0,#0x2700000
        add r0,r0,#0xff000
        ldr r0,[r0,#0xdc4]
        bx lr
    }
#else
    return OSi_GetArenaInfo().hi[id];
#endif
}

void* OS_GetArenaLo(OSArenaId id) {
#ifdef MATCH_ASM
    __asm {
        mov r0,r0, lsl #0x2
        add r0,r0,#0x2700000
        add r0,r0,#0xff000
        ldr r0,[r0,#0xda0]
        bx lr
    }
#else
    return OSi_GetArenaInfo().lo[id];
#endif
}
