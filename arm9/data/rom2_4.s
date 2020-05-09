	.include "asm/macros.inc"
	.include "global.inc"

	/* rom2.s TODO: Disassemble */

	.section .data

	/* 0x0210683C */
	.incbin "baserom.nds", 0x10a83C, 0x764
