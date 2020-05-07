	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x2B2A00, 0x4AC0
	.section .bss
	.space 0x20

