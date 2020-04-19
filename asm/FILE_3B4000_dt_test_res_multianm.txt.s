	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B4000, 0x10
	.balign 512, 255
