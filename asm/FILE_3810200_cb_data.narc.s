	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3810200, 0xED8C
	.balign 512, 255
