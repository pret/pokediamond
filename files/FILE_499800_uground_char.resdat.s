	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x499800, 0x4C
	.balign 512, 255
