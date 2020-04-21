	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B3200, 0x228
	.balign 512, 255
