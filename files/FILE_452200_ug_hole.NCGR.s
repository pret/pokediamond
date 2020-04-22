	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x452200, 0x530
	.balign 512, 255
