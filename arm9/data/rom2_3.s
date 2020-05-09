	.include "asm/macros.inc"
	.include "global.inc"

	/* rom2.s TODO: Disassemble */

	.section .rodata

	/* 0x02103FE4 */
	.incbin "baserom.nds", 0x107FE4, 0x790

	.section .data
	.incbin "baserom.nds", 0x108780, 0x20ac
