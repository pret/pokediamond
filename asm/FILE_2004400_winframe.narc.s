	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2004400, 0x88E4
	.balign 512, 255
