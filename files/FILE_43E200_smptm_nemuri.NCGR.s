	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43E200, 0x230
	.balign 512, 255
