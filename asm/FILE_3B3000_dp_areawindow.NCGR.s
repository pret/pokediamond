	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B3000, 0x170
	.balign 512, 255
