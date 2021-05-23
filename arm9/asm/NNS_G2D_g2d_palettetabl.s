	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020B10B0
FUN_020B10B0: ; 0x020B10B0
	mov r1, r1, lsl #0x1
	ldrh r0, [r0, r1]
	bx lr
	arm_func_end FUN_020B10B0

