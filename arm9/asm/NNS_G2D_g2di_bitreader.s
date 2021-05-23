	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020B76B0
FUN_020B76B0: ; 0x020B76B0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrsb r2, [r0, #0x4]
	ldrb r12, [r0, #0x5]
	mov r4, r1
	cmp r2, r4
	subge r1, r2, r4
	movge r5, r12, lsr r1
	strgeb r1, [r0, #0x4]
	bge _020B7704
	ldr r3, [r0, #0x0]
	sub r1, r4, r2
	add r2, r3, #0x1
	str r2, [r0, #0x0]
	ldrb r2, [r3, #0x0]
	mov r5, r12, lsl r1
	strb r2, [r0, #0x5]
	mov r2, #0x8
	strb r2, [r0, #0x4]
	bl FUN_020B76B0
	orr r5, r0, r5
_020B7704:
	rsb r0, r4, #0x8
	mov r1, #0xff
	and r0, r5, r1, asr r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end FUN_020B76B0

