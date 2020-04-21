	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x33EA00, 0xD04
	.balign 512, 255
