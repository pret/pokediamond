	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D63200, 0x1250
	.balign 512, 255
