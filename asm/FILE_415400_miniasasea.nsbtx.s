	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x415400, 0x578
	.balign 512, 255
