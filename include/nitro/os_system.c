//
// Created by mart on 4/23/20.
//

#include "os_system.h"

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

OSProcMode OS_GetProcMode() {
    __asm {
    mrs r0, cpsr
    and r0, r0, #HW_PSR_CPU_MODE_MASK
    bx lr
    }
}