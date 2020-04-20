	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x440200, 0x1114
	.balign 512, 255
