	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3949800, 0x117C8
	.balign 512, 255
