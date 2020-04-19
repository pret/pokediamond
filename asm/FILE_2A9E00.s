	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2A9E00, 0x2C20
	.balign 512, 255
