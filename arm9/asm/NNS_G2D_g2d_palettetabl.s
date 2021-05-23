	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G2dGetPaletteTableValue
NNS_G2dGetPaletteTableValue: ; 0x020B10B0
	mov r1, r1, lsl #0x1
	ldrh r0, [r0, r1]
	bx lr
	arm_func_end NNS_G2dGetPaletteTableValue
