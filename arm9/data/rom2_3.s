	.include "asm/macros.inc"
	.include "global.inc"

	/* rom2.s TODO: Disassemble */

	.section .rodata

	/* 0x02103FE4 */
	.incbin "baserom.nds", 0x107FE4, 0x790

	.section .data
	; 0x02104780
	.incbin "baserom.nds", 0x108780, 0x2098
	.global OSi_IrqCallbackInfoIndex
OSi_IrqCallbackInfoIndex: ; 0x02106818
	.incbin "baserom.nds", 0x10A818, 0x10
	.global OSi_ConsoleTypeCache
OSi_ConsoleTypeCache: ; 0x02106828
	.incbin "baserom.nds", 0x10A828, 0x4


