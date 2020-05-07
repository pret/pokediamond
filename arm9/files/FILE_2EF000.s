	.include "asm/macros.inc"
	.section .text
	.incbin "baserom.nds", 0x2EF000, 0x2540
	.section .bss
	.space 0x120

