	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B4200, 0x2D
	.balign 512, 255
