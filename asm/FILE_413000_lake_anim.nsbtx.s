	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x413000, 0x1150
	.balign 512, 255
