	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _d2f
_d2f:
	and r2, r1, #0x80000000
	mov r12, r1, lsr #0x14
	bics r12, r12, #0x800
	beq _020E9ED4
	mov r3, r12, lsl #0x15
	cmn r3, #0x200000
	bhs _020E9EB8
	subs r12, r12, #0x380
	bls _020E9EE4
	cmp r12, #0xff
	bge _020E9F54
	mov r1, r1, lsl #0xc
	orr r3, r2, r1, lsr #0x9
	orr r3, r3, r0, lsr #0x1d
	movs r1, r0, lsl #0x3
	orr r0, r3, r12, lsl #0x17
	bxeq lr
	tst r1, #0x80000000
	bxeq lr
	movs r1, r1, lsl #0x1
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020E9EB8:
	orrs r3, r0, r1, lsl #0xc
	bne _020E9ECC
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
_020E9ECC:
	mvn r0, #0x80000000
	bx lr
_020E9ED4:
	orrs r3, r0, r1, lsl #0xc
	bne __f_underflow
	.global __f_result_zero
__f_result_zero:
	mov r0, r2
	bx lr
_020E9EE4:
	cmn r12, #0x17
	beq _020E9F38
	bmi __f_underflow
	mov r1, r1, lsl #0xb
	orr r1, r1, #0x80000000
	mov r3, r1, lsr #0x8
	orr r3, r3, r0, lsr #0x1d
	rsb r12, r12, #0x1
	movs r1, r0, lsl #0x3
	orr r0, r2, r3, lsr r12
	rsb r12, r12, #0x20
	mov r3, r3, lsl r12
	orrne r3, r3, #0x1
	movs r1, r3
	bxeq lr
	tst r1, #0x80000000
	bxeq lr
	movs r1, r1, lsl #0x1
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
_020E9F38:
	orr r0, r0, r1, lsl #0xc
	.global __f_very_tiny_result
__f_very_tiny_result:
	movs r1, r0
	mov r0, r2
	addne r0, r0, #0x1
	bx lr
	.global __f_underflow
__f_underflow:
	mov r0, r2
	bx lr
_020E9F54:
	mov r0, #0xff000000
	orr r0, r2, r0, lsr #0x1
	bx lr
	arm_func_end _d2f
