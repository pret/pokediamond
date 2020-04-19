	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DE8600, 0x29C
	.balign 512, 255
