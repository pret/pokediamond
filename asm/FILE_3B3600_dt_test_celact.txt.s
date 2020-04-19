	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B3600, 0x36
	.balign 512, 255
