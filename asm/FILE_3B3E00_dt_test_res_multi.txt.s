	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B3E00, 0x10
	.balign 512, 255
