	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x383E200, 0x3AB8
	.balign 512, 255
