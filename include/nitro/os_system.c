//
// Created by mart on 4/23/20.
//

#include "os_system.h"

asm OSIntrMode OS_DisableInterrupts() {
    mrs     r0, cpsr
    orr     r1, r0, #HW_PSR_IRQ_DISABLE
    msr     cpsr_c, r1
    and     r0, r0, #HW_PSR_IRQ_DISABLE
    bx      lr
}

asm OSIntrMode OS_RestoreInterrupts(OSIntrMode state) {
    mrs     r1, cpsr
    bic     r2, r1, #HW_PSR_IRQ_DISABLE
    orr     r2, r2, r0
    msr     cpsr_c, r2
    and     r0, r1, #HW_PSR_IRQ_DISABLE
    bx      lr
}

asm OSProcMode OS_GetProcMode() {
    mrs r0, cpsr
    and r0, r0, #HW_PSR_CPU_MODE_MASK
    bx lr
}