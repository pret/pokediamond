	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2712000, 0x2E18
	.balign 512, 255
