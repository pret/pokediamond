	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x2F1600, 0xE2A0
	.section .bss
	.space 0x1980
