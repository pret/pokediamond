	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x499C00, 0x60
	.balign 512, 255
