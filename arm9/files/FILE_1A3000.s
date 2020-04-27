	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1A3000, 0xA1A0
	.balign 512, 255
