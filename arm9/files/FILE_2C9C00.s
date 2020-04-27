	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2C9C00, 0x20
	.balign 512, 255
