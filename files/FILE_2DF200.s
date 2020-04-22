	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2DF200, 0xA720
	.balign 512, 255
