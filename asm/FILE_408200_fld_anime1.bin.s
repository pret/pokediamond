	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x408200, 0x48
	.balign 512, 255
