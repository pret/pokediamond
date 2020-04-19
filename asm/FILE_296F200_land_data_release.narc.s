	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x296F200, 0xE17F2C
	.balign 512, 255
