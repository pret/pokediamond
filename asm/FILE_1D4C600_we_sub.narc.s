	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D4C600, 0x3024
	.balign 512, 255
