	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3860E00, 0x194
	.balign 512, 255
