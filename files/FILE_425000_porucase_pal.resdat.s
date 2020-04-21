	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x425000, 0x34
	.balign 512, 255
