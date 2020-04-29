	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start G3_EndMakeDL
G3_EndMakeDL: ; 0x020C9B18
	ldr r3, [r0, #0x0]
	ldr r2, [r0, #0x8]
	cmp r2, r3
	moveq r0, #0x0
	bxeq lr
	and r1, r3, #0x3
	cmp r1, #0x3
	addls pc, pc, r1, lsl #0x2
	b _020C9B8C
_020C9B3C:
	b _020C9B4C
_020C9B40:
	b _020C9B54
_020C9B44:
	b _020C9B64
_020C9B48:
	b _020C9B78
_020C9B4C:
	sub r0, r3, r2
	bx lr
_020C9B54:
	add r1, r3, #0x1
	str r1, [r0, #0x0]
	mov r1, #0x0
	strb r1, [r3, #0x0]
_020C9B64:
	ldr r3, [r0, #0x0]
	mov r1, #0x0
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	strb r1, [r3, #0x0]
_020C9B78:
	ldr r3, [r0, #0x0]
	mov r1, #0x0
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	strb r1, [r3, #0x0]
_020C9B8C:
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	beq _020C9BB0
	ldr r3, [r0, #0x4]
	mov r1, #0x0
	add r2, r3, #0x4
	str r2, [r0, #0x4]
	str r1, [r3, #0x0]
	str r1, [r0, #0x10]
_020C9BB0:
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x8]
	sub r0, r1, r0
	bx lr

	arm_func_start G3_BeginMakeDL
G3_BeginMakeDL: ; 0x020C9BC8
	str r2, [r0, #0xc]
	str r1, [r0, #0x8]
	str r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x10]
	bx lr
