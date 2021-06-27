#include "OS_exception.h"

#include "global.h"
#include "OS_protectionUnit.h"
#include "mmap.h"

static OSiExContext OSi_ExContext;

static OSExceptionHandler OSi_UserExceptionHandler;
static void *OSi_UserExceptionHandlerArg;

static void *OSi_DebuggerHandler = NULL;

#define HW_EXCEP_VECTOR_BUF_FOR_DEBUGGER 0x027ffd9c

static void OSi_GetAndDisplayContext(void);
static void OSi_SetExContext(void);
static void OSi_DisplayExContext(void);

ARM_FUNC void OS_InitException(void)
{
    if (0x2600000 <= *(u32 *)HW_EXCEP_VECTOR_BUF_FOR_DEBUGGER
        && *(u32 *)HW_EXCEP_VECTOR_BUF_FOR_DEBUGGER < 0x2800000)
    {
        OSi_DebuggerHandler = *(void **)HW_EXCEP_VECTOR_BUF_FOR_DEBUGGER;
    }
    else
    {
        OSi_DebuggerHandler = NULL;
    }

    if (!OSi_DebuggerHandler)
    {
        *(u32 *)(HW_EXCEP_VECTOR_BUF_FOR_DEBUGGER) = (u32)OSi_ExceptionHandler;

        *(u32 *)(HW_EXCP_VECTOR_BUF) = (u32)OSi_ExceptionHandler;
    }

    OSi_UserExceptionHandler = NULL;
}

ARM_FUNC asm void OSi_ExceptionHandler(void)
{
    ldr r12, =OSi_DebuggerHandler
    ldr r12, [r12]
    cmp r12, #0
    movne lr, pc
    bxne r12

    ldr r12, =HW_ITCM_END
    stmfd r12!, {r0-r3, sp, lr}

    and r0, sp, #1
    mov sp, r12

    mrs r1, cpsr
    and r1, r1, #0x1f

    teq r1, #0x17
    bne _020CCA38
    bl OSi_GetAndDisplayContext
    b _020CCA44

_020CCA38:
    teq r1, #0x1b
    bne _020CCA44
    bl OSi_GetAndDisplayContext

_020CCA44:
    ldr r12, =OSi_DebuggerHandler
    ldr r12, [r12]
    cmp r12, #0

_020CCA50:
    beq _020CCA50

_020CCA54:
    mov r0, r0
    b _020CCA54

    ldmfd sp!, {r0-r3, r12, lr}
    mov sp, r12
    bx lr
}

ARM_FUNC static asm void OSi_GetAndDisplayContext(void)
{
    stmfd sp!, {r0, lr}

    bl OSi_SetExContext
    bl OSi_DisplayExContext

    ldmfd sp!, {r0, lr}
    bx lr
}

ARM_FUNC static asm void OSi_SetExContext(void)
{
    ldr r1, =OSi_ExContext;

    mrs r2, cpsr
    str r2, [r1, #OSiExContext.debug[1]]

    str r0, [r1, #OSiExContext.exinfo]

    ldr r0, [r12, #0]
    str r0, [r1, #4]
    ldr r0, [r12, #4]
    str r0, [r1, #8]
    ldr r0, [r12, #8]
    str r0, [r1, #12]
    ldr r0, [r12, #12]
    str r0, [r1, #16]
    ldr r2, [r12, #16]
    bic r2, r2, #1

    add r0, r1, #20
    stmia r0, {r4-r11}

    str r12, [r1, #OSiExContext.debug[0]]

    ldr r0, [r2, #0]
    str r0, [r1, #OSiExContext.cp15]
    ldr r3, [r2, #4]
    str r3, [r1, #0]
    ldr r0, [r2, #8]
    str r0, [r1, #52]
    ldr r0, [r2, #12]
    str r0, [r1, #64]

    mrs r0, cpsr
    orr r3, r3, #0x80
    bic r3, r3, #0x20
    msr cpsr_cxsf, r3

    str sp, [r1, #56]
    str lr, [r1, #60]
    mrs r2, spsr

    str r2, [r1, #OSiExContext.debug[3]]

    msr cpsr_cxsf, r0
    bx lr
}

ARM_FUNC static void OSi_DisplayExContext(void)
{
    if (OSi_UserExceptionHandler)
    {
        asm
        {
            mov r0, sp
            ldr r1, =0x9f
            msr CPSR_cxsf, r1
            mov sp, r0
        }

        OS_EnableProtectionUnit();

        ((void (*)(u32, void *))OSi_UserExceptionHandler)((u32)&OSi_ExContext, OSi_UserExceptionHandlerArg);

        OS_DisableProtectionUnit();
    }
}
