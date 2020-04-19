	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x395B000, 0xDBE4
	.balign 512, 255
