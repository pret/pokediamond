	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2715000, 0x3E4
	.balign 512, 255
