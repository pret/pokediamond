	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D64600, 0x8134
	.balign 512, 255
