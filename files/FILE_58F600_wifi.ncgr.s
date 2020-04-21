	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x58F600, 0x240
	.balign 512, 255
