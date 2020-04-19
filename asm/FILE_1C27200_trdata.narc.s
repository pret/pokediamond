	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C27200, 0x5D2C
	.balign 512, 255
