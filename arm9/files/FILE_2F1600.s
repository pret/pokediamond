	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2F1600, 0xE2A0
	.balign 512, 255
