	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x339C00, 0x7E8
	.balign 512, 255
