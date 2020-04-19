	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x225E200, 0x4E844
	.balign 512, 255
