#include "function_target.h"
#include "OS_system.h"
#include "OS_spinLock.h"

ARM_FUNC asm OSIntrMode OS_EnableInterrupts(void)
{
    mrs	r0, CPSR
    bic	r1, r0, #HW_PSR_DISABLE_IRQ
    msr	CPSR_c, r1
    and	r0, r0, #HW_PSR_DISABLE_IRQ
    bx	lr
}

ARM_FUNC asm OSIntrMode OS_DisableInterrupts(void)
{
    mrs	r0, CPSR
    orr	r1, r0, #HW_PSR_DISABLE_IRQ
    msr	CPSR_c, r1
    and	r0, r0, #HW_PSR_DISABLE_IRQ
    bx	lr
}

ARM_FUNC asm OSIntrMode OS_RestoreInterrupts(register OSIntrMode state)
{
    mrs	r1, CPSR
    bic	r2, r1, #HW_PSR_DISABLE_IRQ
    orr	r2, r2, r0
    msr	CPSR_c, r2
    and	r0, r1, #HW_PSR_DISABLE_IRQ
    bx	lr
}

ARM_FUNC asm OSIntrMode OS_DisableInterrupts_IrqAndFiq(void)
{
    mrs	r0, CPSR
    orr	r1, r0, #HW_PSR_DISABLE_IRQ_FIQ
    msr	CPSR_c, r1
    and	r0, r0, #HW_PSR_DISABLE_IRQ_FIQ
    bx	lr
}

ARM_FUNC asm OSIntrMode OS_RestoreInterrupts_IrqAndFiq(register OSIntrMode state)
{
    mrs	r1, CPSR
    bic	r2, r1, #HW_PSR_DISABLE_IRQ_FIQ
    orr	r2, r2, r0
    msr	CPSR_c, r2
    and	r0, r1, #HW_PSR_DISABLE_IRQ_FIQ
    bx	lr
}

ARM_FUNC asm OSProcMode OS_GetProcMode(void)
{
    mrs	r0, CPSR
    and	r0, r0, #HW_PSR_CPU_MODE_MASK
    bx	lr
}

ARM_FUNC void OS_SpinWait(u32 cycle)
{
    FUN_037F8CB4((s32)cycle / 4);
}
