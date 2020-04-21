	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B4A00, 0x46000
	.balign 512, 255
