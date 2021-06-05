	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _ll_mul
_ll_mul: ; 0x020EBC30
	stmdb sp!, {r4-r5,lr}
	umull r5, r4, r0, r2
	mla r4, r0, r3, r4
	mla r4, r2, r1, r4
	mov r1, r4
	mov r0, r5
	ldmia sp!, {r4-r5,lr}
	bx lr
