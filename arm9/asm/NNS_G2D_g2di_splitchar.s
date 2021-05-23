	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020B7718
FUN_020B7718: ; 0x020B7718
	ldr r1, [r0, #0x0]
	ldrh r2, [r1], #0x2
	str r1, [r0, #0x0]
	mov r0, r2
	bx lr
	arm_func_end FUN_020B7718

