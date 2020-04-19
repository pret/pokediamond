	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D70800, 0x359D8
	.balign 512, 255
