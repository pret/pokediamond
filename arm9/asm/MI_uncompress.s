    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start MI_UncompressLZ8
MI_UncompressLZ8: ; 0x020CE528
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r0], #0x4
	mov r2, r5, lsr #0x8
_020CE534:
	cmp r2, #0x0
	ble _020CE5B4
	ldrb lr, [r0], #0x1
	mov r4, #0x8
_020CE544:
	subs r4, r4, #0x1
	blt _020CE534
	tst lr, #0x80
	bne _020CE568
	ldrb r6, [r0], #0x1
	.word 0xE1416096
	add r1, r1, #0x1
	sub r2, r2, #0x1
	b _020CE5A4
_020CE568:
	ldrb r5, [r0, #0x0]
	mov r6, #0x3
	add r3, r6, r5, asr #0x4
	ldrb r6, [r0], #0x1
	and r5, r6, #0xf
	mov r12, r5, lsl #0x8
	ldrb r6, [r0], #0x1
	orr r5, r6, r12
	add r12, r5, #0x1
	sub r2, r2, r3
_020CE590:
	ldrb r5, [r1, -r12]
	.word 0xE1415095
	add r1, r1, #0x1
	subs r3, r3, #0x1
	bgt _020CE590
_020CE5A4:
	cmp r2, #0x0
	movgt lr, lr, lsl #0x1
	bgt _020CE544
	b _020CE534
_020CE5B4:
	ldmia sp!, {r4-r6,lr}
	bx lr
