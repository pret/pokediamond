	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _dflt
_dflt: ; 0x020EA038
	ands r2, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r0, #0x0
	.global __d_itod_common
__d_itod_common:
	mov r1, #0x0
	bxeq lr
	mov r3, #0x400
	add r3, r3, #0x1e
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
	movs r1, r0
	mov r0, r1, lsl #0x15
	add r1, r1, r1
	orr r1, r2, r1, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	bx lr
	arm_func_end _dflt

	arm_func_start _dfltu
_dfltu: ; 0x020EA078
	cmp r0, #0x0
	.global __d_utod_common
__d_utod_common:
	mov r1, #0x0
	bxeq lr
	mov r3, #0x400
	add r3, r3, #0x1e
	bmi _020EA09C
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
_020EA09C:
	mov r1, r0
	mov r0, r1, lsl #0x15
	add r1, r1, r1
	mov r1, r1, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	bx lr
	arm_func_end _dfltu
