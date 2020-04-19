	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B3C00, 0x2B
	.balign 512, 255
