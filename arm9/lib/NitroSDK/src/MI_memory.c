#include "MI_memory.h"
#include "code32.h"

asm void MIi_CpuClear16(register u16 data, register void *destp, register u32 size)
{
    mov r3, #0

_020CE1CC:
    cmp r3, r2
    strlth r0, [r1, r3]
    addlt r3, r3, #2
    blt _020CE1CC

    bx lr
}

asm void MIi_CpuCopy16(register const void *srcp, register void *destp, register u32 size)
{
    mov r12, #0

_020CE1CC:
    cmp r12, r2
    ldrlth r3, [r0, r12]
    strlth r3, [r1, r12]
    addlt r12, r12, #2
    blt _020CE1CC

    bx lr
}

asm void MIi_CpuClear32(register u32 data, register void *destp, register u32 size)
{
    add r12, r1, r2

_020CE200:
    cmp r1, r12
    stmltia r1!, {r0}
    blt _020CE200
    bx lr
}

asm void MIi_CpuCopy32(register const void *srcp, register void *destp, register u32 size)
{
    add r12, r1, r2

_020CE214:
    cmp r1, r12
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt _020CE214
    bx lr
}

asm void MIi_CpuSend32(register const void *srcp, volatile void *destp, u32 size)
{
    add r12, r0, r2

_020CE22C:
    cmp r0, r12
    ldmltia r0!, {r2}
    strlt r2, [r1]
    blt _020CE22C

    bx lr
}

asm void MIi_CpuClearFast(register u32 data, register void *destp, register u32 size)
{
    stmfd sp!, {r4-r9}

    add r9, r1, r2
    mov r12, r2, lsr #5
    add r12, r1, r12, lsl #5

    mov r2, r0
    mov r3, r2
    mov r4, r2
    mov r5, r2
    mov r6, r2
    mov r7, r2
    mov r8, r2

_020CE26C:
    cmp r1, r12
    stmltia r1!, {r0, r2-r8}
    blt _020CE26C
_020CE278:
    cmp r1, r9
    stmltia r1!, {r0}
    blt _020CE278

    ldmfd sp!, {r4-r9}
    bx lr
}

asm void MIi_CpuCopyFast(register const void *srcp, register void *destp, register u32 size)
{
    stmfd sp!, {r4-r10}

    add r10, r1, r2
    mov r12, r2, lsr #5
    add r12, r1, r12, lsl #5

_020CE29C:
    cmp r1, r12
    ldmltia r0!, {r2-r9}
    stmltia r1!, {r2-r9}
    blt _020CE29C
_020CE2AC:
    cmp r1, r10
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt _020CE2AC

    ldmfd sp!, {r4-r10}
    bx lr
}

asm void MI_Copy32B(register const void *pSrc, register void *pDest)
{
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3}
    stmia r1!, {r2, r3}

    bx lr
}

asm void MI_Copy36B(register const void *pSrc, register void *pDest)
{
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}

    bx lr
}

asm void MI_Copy48B(register const void *pSrc, register void *pDest)
{
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}

    bx lr
}

asm void MI_Copy64B(register const void *pSrc, register void *pDest)
{
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0!, {r2, r3, r12}
    stmia r1!, {r2, r3, r12}
    ldmia r0, {r0, r2, r3, r12}
    stmia r1!, {r0, r2, r3, r12}

    bx lr
}

asm void MI_CpuFill8(register void *dstp, register u8 data, register u32 size)
{
    cmp r2, #0
    bxeq lr

    tst r0, #1
    beq _020CE378
    ldrh r12, [r0, #-1]
    and r12, r12, #0x00ff
    orr r3, r12, r1, lsl #8
    strh r3, [r0, #-1]
    add r0, r0, #1
    subs r2, r2, #1
    bxeq lr

_020CE378:
    cmp r2, #2
    bcc _020CE3C0
    orr r1, r1, r1, lsl #8
    tst r0, #2
    beq _020CE398
    strh r1, [r0], #2
    subs r2, r2, #2
    bxeq lr

_020CE398:
    orr r1, r1, r1, lsl #16
    bics r3, r2, #3
    beq _020CE3B8
    sub r2, r2, r3
    add r12, r3, r0

_020CE3AC:
    str r1, [r0], #4
    cmp r0, r12
    bcc _020CE3AC

_020CE3B8:
    tst r2, #2
    strneh r1, [r0], #2

_020CE3C0:
    tst r2, #1
    bxeq lr
    ldrh r3, [r0]
    and r3, r3, #0xff00
    and r1, r1, #0x00ff
    orr r1, r1, r3
    strh r1, [r0]
    bx lr
}

asm void MI_CpuCopy8(register const void *srcp, register void *dstp, register u32 size)
{
    cmp r2, #0
    bxeq lr

    tst r1, #1
    beq _020CE420
    ldrh r12, [r1, #-1]
    and r12, r12, #0x00ff
    tst r0, #1
    ldrneh r3, [r0, #-1]
    movne r3, r3, lsr #8
    ldreqh r3, [r0]
    orr r3, r12, r3, lsl #8
    strh r3, [r1, #-1]
    add r0, r0, #1
    add r1, r1, #1
    subs r2, r2, #1
    bxeq lr

_020CE420:
    eor r12, r1, r0
    tst r12, #1
    beq _020CE474

    bic r0, r0, #1
    ldrh r12, [r0], #2
    mov r3, r12, lsr #8
    subs r2, r2, #2
    bcc _020CE458

_020CE440:
    ldrh r12, [r0], #2
    orr r12, r3, r12, lsl #8
    strh r12, [r1], #2
    mov r3, r12, lsr #16
    subs r2, r2, #2
    bcs _020CE440

_020CE458:
    tst r2, #1
    bxeq lr
    ldrh r12, [r1]
    and r12, r12, #0xff00
    orr r12, r12, r3
    strh r12, [r1]
    bx lr

_020CE474:
    tst r12, #2
    beq _020CE4A0

    bics r3, r2, #1
    beq _020CE4EC
    sub r2, r2, r3
    add r12, r3, r1

_020CE48C:
    ldrh r3, [r0], #2
    strh r3, [r1], #2
    cmp r1, r12
    bcc _020CE48C
    b _020CE4EC

_020CE4A0:
    cmp r2, #2
    bcc _020CE4EC
    tst r1, #2
    beq _020CE4C0
    ldrh r3, [r0], #2
    strh r3, [r1], #2
    subs r2, r2, #2
    bxeq lr

_020CE4C0:
    bics r3, r2, #3
    beq _020CE4E0
    sub r2, r2, r3
    add r12, r3, r1

_020CE4D0:
    ldr r3, [r0], #4
    str r3, [r1], #4
    cmp r1, r12
    bcc _020CE4D0

_020CE4E0:
    tst r2, #2
    ldrneh r3, [r0], #2
    strneh r3, [r1], #2

_020CE4EC:
    tst r2, #1
    bxeq lr
    ldrh r2, [r1]
    ldrh r0, [r0]
    and r2, r2, #0xff00
    and r0, r0, #0x00ff
    orr r0, r2, r0
    strh r0, [r1]

    bx lr
}

#include "code16.h" //following func is thumb

asm void MI_Zero36B(register void *pDest)
{
    mov r1, #0
    mov r2, #0
    mov r3, #0
    stmia r0!, {r1, r2, r3}
    stmia r0!, {r1, r2, r3}
    stmia r0!, {r1, r2, r3}

    bx lr
}
