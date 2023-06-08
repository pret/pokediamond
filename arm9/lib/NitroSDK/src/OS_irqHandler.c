#include "OS_irqHandler.h"
#include "OS_system.h"
#include "OS_thread.h"
#include "sections.h"
#include "CP_context.h"
#include "code32.h"

OSThreadQueue OSi_IrqThreadQueue = { NULL, NULL };

#pragma section ITCM begin
asm void OS_IrqHandler(void)
{
    stmfd sp!, {lr}
    mov ip, #0x04000000
    add ip, ip, #0x210
    ldr r1, [ip, #-8]
    cmp r1, #0
    ldmeqfd sp!, {pc}
    ldmia ip, {r1, r2}
    ands r1, r1, r2
    ldmeqfd sp!, {pc}
    mov r3, #0x80000000
_01FF8028:
    clz r0, r1
    bics r1, r1, r3, lsr r0
    bne _01FF8028
    mov r1, r3, lsr r0
    str r1, [ip, #0x4]
    rsbs r0, r0, #0x1f
    ldr r1, =OS_IRQTable
    ldr r0, [r1, r0, lsl #2]
    ldr lr, =OS_IrqHandler_ThreadSwitch
    bx r0
}

asm void OS_IrqHandler_ThreadSwitch(void)
{
    ldr ip, =OSi_IrqThreadQueue
    mov r3, #0x0
    ldr ip, [ip]
    mov r2, #0x1
    cmp ip, #0x0
    beq _01FF80A8
_01FF8070:
    str r2, [ip, #0x64]
    str r3, [ip, #0x78]
    str r3, [ip, #0x7c]
    ldr r0, [ip, #0x80]
    str r3, [ip, #0x80]
    mov ip, r0
    cmp ip, #0x0
    bne _01FF8070
    ldr ip, =OSi_IrqThreadQueue
    str r3, [ip]
    str r3, [ip, #0x4]
    ldr ip, =OSi_ThreadInfo
    mov r1, #0x1
    strh r1, [ip]
_01FF80A8:
    ldr ip, =OSi_ThreadInfo
    ldrh r1, [ip]
    cmp r1, #0x0
    ldreq pc, [sp], #0x4
    mov r1, #0x0
    strh r1, [ip]
    mov r3, #0xd2
    msr CPSR_c, r3
    add r2, ip, #0x8
    ldr r1, [r2]
_01FF80D0:
    cmp r1, #0x0
    ldrneh r0, [r1, #0x64]
    cmpne r0, #0x1
    ldrne r1, [r1, #0x68]
    bne _01FF80D0
    cmp r1, #0x0
    bne _01FF80F8
_01FF80EC:
    mov r3, #0x92
    msr CPSR_c, r3
    ldr pc, [sp], #0x4
_01FF80F8:
    ldr r0, [ip, #0x4]
    cmp r1, r0
    beq _01FF80EC
    ldr r3, [ip, #0xC]
    cmp r3, #0x0
    beq _01FF8120
    stmdb sp!, {r0, r1, ip}
    mov lr, pc
    bx r3
    ldmia sp!, {r0, r1, ip}
_01FF8120:
    str r1, [ip, #0x4]
    mrs r2, SPSR
    str r2, [r0, #0x0]!
    stmdb sp!, {r0, r1}
    add r0, r0, #0x0
    add r0, r0, #0x48
    ldr r1, =CP_SaveContext
    blx r1
    ldmia sp!, {r0, r1}
    ldmib sp!, {r2, r3}
    stmib r0!, {r2, r3}
    ldmib sp!, {r2, r3, ip, lr}
    stmib r0!, {r2-r14}^
    stmib r0!, {lr}
    mov r3, #0xd3
    msr CPSR_c, r3
    stmib r0!, {sp}
    stmfd sp!, {r1}
    add r0, r1, #0x0
    add r0, r0, #0x48
    ldr r1, =CPi_RestoreContext
    blx r1
    ldmfd sp!, {r1}
    ldr sp, [r1, #0x44]
    mov r3, #0xd2
    msr CPSR_c, r3
    ldr r2, [r1, #0x0]!
    msr SPSR_fc, r2
    ldr lr, [r1, #0x40]
    ldmib r1!, {r0-r14}^
    nop
    stmda sp!, {r0, r1, r2, r3, ip, lr}
    ldmfd sp!, {pc}
}
#pragma section ITCM end

void OS_WaitIrq(BOOL clear, OSIrqMask irqFlags)
{
    OSIntrMode lastIntrMode = OS_DisableInterrupts();
    if (clear)
    {
        OS_ClearIrqCheckFlag(irqFlags);
    }
    (void)OS_RestoreInterrupts(lastIntrMode);

    while (!(OS_GetIrqCheckFlag() & irqFlags))
    {
        OS_SleepThread(&OSi_IrqThreadQueue);
    }
}
