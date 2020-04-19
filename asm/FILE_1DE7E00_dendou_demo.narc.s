	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DE7E00, 0x61C
	.balign 512, 255
