	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E73800, 0x20E58
	.balign 512, 255
