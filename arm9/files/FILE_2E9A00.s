	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x2E9A00, 0x5580
	.section .bss
	.space 0xa0
