#include "MI_uncompress.h"
#include "code32.h"

asm void MI_UncompressLZ8(register const void *srcp, register void *destp)
{
    stmfd sp!, {r4-r6, lr}

    ldr r5, [r0], #4
    mov r2, r5, lsr #8

_020CE534:
    cmp r2, #0
    ble _020CE5B4

    ldrb lr, [r0], #1
    mov r4, #8

_020CE544:
    subs r4, r4, #1
    blt _020CE534

    tst lr, #0x80
    bne _020CE568

    ldrb r6, [r0], #1
    swpb r6, r6, [r1]
    add r1, r1, #1
    sub r2, r2, #1
    b _020CE5A4

_020CE568:
    ldrb r5, [r0, #0]
    mov r6, #3
    add r3, r6, r5, asr #4
    ldrb r6, [r0], #1
    and r5, r6, #0xf
    mov r12, r5, lsl #8
    ldrb r6, [r0], #1
    orr r5, r6, r12
    add r12, r5, #1
    sub r2, r2, r3

_020CE590:
    ldrb r5, [r1, -r12]
    swpb r5, r5, [r1]
    add r1, r1, #1
    subs r3, r3, #1
    bgt _020CE590

_020CE5A4:
    cmp r2, #0
    movgt lr, lr, lsl #1
    bgt _020CE544
    b _020CE534

_020CE5B4:
    ldmfd sp!, {r4-r6, lr}
    bx lr
}
