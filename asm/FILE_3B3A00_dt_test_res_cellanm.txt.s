	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3B3A00, 0x26
	.balign 512, 255
