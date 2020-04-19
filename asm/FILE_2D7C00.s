	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2D7C00, 0x1BE0
	.balign 512, 255
