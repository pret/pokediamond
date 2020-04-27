	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x297600, 0x8A0
	.balign 512, 255
