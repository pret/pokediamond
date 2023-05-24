	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start fabs
fabs: ; 0x020E823C
	stmdb sp!, {r0-r3}
	add r2, sp, #0x0
	ldr r1, [r2, #0x4]
	ldr r0, [sp, #0x0]
	bic r1, r1, #0x80000000
	str r1, [r2, #0x4]
	add sp, sp, #0x10
	bx lr
	arm_func_end fabs
