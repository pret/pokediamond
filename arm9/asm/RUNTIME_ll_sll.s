	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _ll_shl
_ll_shl: ; 0x020EBC50
	ands r2, r2, #0x3f
	bxeq lr
	subs r3, r2, #0x20
	bge _020EBC74
	rsb r3, r2, #0x20
	mov r1, r1, lsl r2
	orr r1, r1, r0, lsr r3
	mov r0, r0, lsl r2
	bx lr
_020EBC74:
	mov r1, r0, lsl r3
	mov r0, #0x0
	bx lr
