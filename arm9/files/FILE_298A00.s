	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x298A00, 0xFC0
	.section .bss
	.space 0x20
