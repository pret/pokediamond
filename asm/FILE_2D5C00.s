	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2D5C00, 0x1E20
	.balign 512, 255
