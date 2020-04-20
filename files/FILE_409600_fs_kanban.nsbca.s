	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x409600, 0x7F4
	.balign 512, 255
