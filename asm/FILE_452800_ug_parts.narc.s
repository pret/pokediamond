	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x452800, 0x2079C
	.balign 512, 255
