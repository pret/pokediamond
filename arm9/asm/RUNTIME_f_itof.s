	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _fflt
_fflt: ; 0x020EB534
	ands r2, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r0, #0x0
	.global __f_itof_common
__f_itof_common:
	bxeq lr
	clz r3, r0
	movs r0, r0, lsl r3
	rsb r3, r3, #0x9e
	ands r1, r0, #0xff
	add r0, r0, r0
	orr r0, r2, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bxeq lr
	tst r1, #0x80
	bxeq lr
	ands r3, r1, #0x7f
	andeqs r3, r0, #0x1
	addne r0, r0, #0x1
	bx lr

	arm_func_start _ffltu
_ffltu: ; 0x020EB57C
	cmp r0, #0x0
	.global __f_utof_common
__f_utof_common:
	bxeq lr
	mov r3, #0x9e
	bmi _020EB598
	clz r12, r0
	movs r0, r0, lsl r12
	sub r3, r3, r12
_020EB598:
	ands r2, r0, #0xff
	add r0, r0, r0
	mov r0, r0, lsr #0x9
	orr r0, r0, r3, lsl #0x17
	bxeq lr
	tst r2, #0x80
	bxeq lr
	ands r1, r2, #0x7f
	andeqs r1, r0, #0x1
	addne r0, r0, #0x1
	bx lr
