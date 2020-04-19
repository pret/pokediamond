	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D60200, 0x1910
	.balign 512, 255
