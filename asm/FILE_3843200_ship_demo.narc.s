	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3843200, 0x17358
	.balign 512, 255
