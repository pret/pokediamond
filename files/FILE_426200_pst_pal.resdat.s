	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x426200, 0xAC
	.balign 512, 255
