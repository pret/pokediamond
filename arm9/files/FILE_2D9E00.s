	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x2D9E00, 0x52C0
	.section .bss
	.space 0x40
