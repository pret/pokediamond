	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x451E00, 0xD6
	.balign 512, 255
