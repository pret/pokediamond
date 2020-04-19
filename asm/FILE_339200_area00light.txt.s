	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x339200, 0x822
	.balign 512, 255
