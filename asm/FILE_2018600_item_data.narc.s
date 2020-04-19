	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2018600, 0x4C2C
	.balign 512, 255
