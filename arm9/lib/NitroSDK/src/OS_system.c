#include "OS_system.h"
#include "OS_irqHandler.h"
#include "syscall.h"
#include "code32.h"

asm OSIntrMode OS_EnableInterrupts(void)
{
    mrs r0, cpsr
    bic r1, r0, #HW_PSR_DISABLE_IRQ
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_DISABLE_IRQ
    bx lr
}

asm OSIntrMode OS_DisableInterrupts(void)
{
    mrs r0, cpsr
    orr r1, r0, #HW_PSR_DISABLE_IRQ
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_DISABLE_IRQ
    bx lr
}

asm OSIntrMode OS_RestoreInterrupts(OSIntrMode state)
{
    mrs r1, cpsr
    bic r2, r1, #HW_PSR_DISABLE_IRQ
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #HW_PSR_DISABLE_IRQ
    bx lr
}

asm OSIntrMode OS_DisableInterrupts_IrqAndFiq(void)
{
    mrs r0, cpsr
    orr r1, r0, #HW_PSR_DISABLE_IRQ_FIQ
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_DISABLE_IRQ_FIQ
    bx lr
}

asm OSIntrMode OS_RestoreInterrupts_IrqAndFiq(OSIntrMode state)
{
    mrs r1, cpsr
    bic r2, r1, #HW_PSR_DISABLE_IRQ_FIQ
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #HW_PSR_DISABLE_IRQ_FIQ
    bx lr
}

asm OSIntrMode OS_GetCpsrIrq(void)
{
    mrs r0, cpsr
    and r0, r0, #HW_PSR_DISABLE_IRQ
    bx lr
}

asm OSProcMode OS_GetProcMode(void)
{
    mrs r0, cpsr
    and r0, r0, #HW_PSR_CPU_MODE_MASK
    bx lr
}

asm void OS_SpinWait(u32 cycles)
{
    subs r0, r0, #0x4
    bhs OS_SpinWait
    bx lr
}

void OS_WaitVBlankIntr(void)
{
    SVC_WaitByLoop(0x1);
    OS_WaitIrq(TRUE, OS_IE_VBLANK);
}
