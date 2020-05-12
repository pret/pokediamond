	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x290000, 0x560
	.section .bss
	.space 0x20
