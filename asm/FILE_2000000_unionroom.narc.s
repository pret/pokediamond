	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2000000, 0x1210
	.balign 512, 255
