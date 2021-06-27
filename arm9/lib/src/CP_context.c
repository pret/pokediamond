#include "CP_context.h"
#include "function_target.h"
#include "registers.h"

ARM_FUNC asm void CP_SaveContext(register CPContext *context)
{
    ldr r1, =REG_DIV_NUMER_ADDR
    stmfd sp!, {r4}
    ldmia r1, {r2-r4, r12}
    stmia r0!, {r2-r4, r12}
    ldrh r12, [r1, #-16]

    add r1, r1, #40
    ldmia r1, {r2-r3}
    stmia r0!, {r2-r3}

    and r12, r12, #3
    ldrh r2, [r1, #-8]
    strh r12, [r0]
    and r2, r2, #1
    strh r2, [r0, #2]
    ldmfd sp!, {r4}

    bx lr
}

ARM_FUNC asm void CPi_RestoreContext(register const CPContext *context)
{
    stmfd sp!, {r4}
    ldr r1, =REG_DIV_NUMER_ADDR
    ldmia r0, {r2-r4, r12}
    stmia r1, {r2-r4, r12}
    ldrh r2, [r0, #24] //CPContext.div_mode
    ldrh r3, [r0, #26] //CPContext.sqrt_mode

    strh r2, [r1, #-16]
    strh r3, [r1, #32]

    add r0, r0, #16 //CPContext.sqrt
    add r1, r1, #40

    ldmia r0, {r2-r3}
    stmia r1, {r2-r3}

    ldmfd sp!, {r4}

    bx lr
}
