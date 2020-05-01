//
// Created by mart on 4/23/20.
//

#include "function_target.h"
#include "OS_system.h"

ARM_FUNC asm OSIntrMode OS_EnableInterrupts() {
    mrs r0, cpsr
    bic r1, r0, #HW_PSR_DISABLE_IRQ
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_DISABLE_IRQ
    bx lr
}

ARM_FUNC asm OSIntrMode OS_DisableInterrupts() {
    mrs     r0, cpsr
    orr     r1, r0, #HW_PSR_DISABLE_IRQ
    msr     cpsr_c, r1
    and     r0, r0, #HW_PSR_DISABLE_IRQ
    bx      lr
}

ARM_FUNC asm OSIntrMode OS_RestoreInterrupts(OSIntrMode state) {
    mrs     r1, cpsr
    bic     r2, r1, #HW_PSR_DISABLE_IRQ
    orr     r2, r2, r0
    msr     cpsr_c, r2
    and     r0, r1, #HW_PSR_DISABLE_IRQ
    bx      lr
}

ARM_FUNC asm OSIntrMode OS_DisableInterrupts_IrqAndFiq() {
    mrs r0, cpsr
    orr r1, r0, #HW_PSR_DISABLE_IRQ_FIQ
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_DISABLE_IRQ_FIQ
    bx lr
}

ARM_FUNC asm OSIntrMode OS_RestoreInterrupts_IrqAndFiq(OSIntrMode state) {
    mrs r1, cpsr
    bic r2, r1, #HW_PSR_DISABLE_IRQ_FIQ
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #HW_PSR_DISABLE_IRQ_FIQ
    bx lr
}

ARM_FUNC asm OSIntrMode OS_GetCpsrIrq() {
    mrs r0, cpsr
    and r0, r0, #HW_PSR_DISABLE_IRQ
    bx lr
}

ARM_FUNC asm OSProcMode OS_GetProcMode() {
    mrs r0, cpsr
    and r0, r0, #HW_PSR_CPU_MODE_MASK
    bx lr
}

ARM_FUNC asm void OS_SpinWait() {
    subs r0, r0, #0x4
    bhs OS_SpinWait
    bx lr
}

ARM_FUNC void OS_WaitVBlankIntr() {
    SVC_WaitByLoop(0x1);
    OS_WaitIrq(TRUE, OS_IE_V_BLANK);
}
