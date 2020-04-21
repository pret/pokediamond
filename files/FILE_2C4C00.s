	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2C4C00, 0xE20
	.balign 512, 255
