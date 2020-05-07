	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x2DF200, 0xA720
	.section .bss
	.space 0x160

