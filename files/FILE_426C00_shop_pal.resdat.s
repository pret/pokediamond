	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x426C00, 0x4C
	.balign 512, 255
