/* rom1.5.s TODO: Disassemble */
	.include "asm/macros.inc"
	.section .text

	arm_func_start FUN_0208AC14
FUN_0208AC14:
	.incbin "baserom.nds", 0x8EC14, 0x3EFF8
