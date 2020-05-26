	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start SOCLi_RoundUp4
SOCLi_RoundUp4:
	add r0, r0, #0x3
	bic r0, r0, #0x3
	bx lr
