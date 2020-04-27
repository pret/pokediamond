	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2C5C00, 0x3EC0
	.balign 512, 255
