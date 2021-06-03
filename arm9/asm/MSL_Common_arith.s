	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start abs
abs: ; 0x020DE3F0
	cmp r0, #0x0
	rsblt r0, r0, #0x0
	bx lr
	arm_func_end abs
