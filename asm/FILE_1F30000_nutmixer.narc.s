	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F30000, 0x2C2F4
	.balign 512, 255
