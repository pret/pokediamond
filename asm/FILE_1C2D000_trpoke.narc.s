	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C2D000, 0x5594
	.balign 512, 255
