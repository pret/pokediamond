	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x385A600, 0x380
	.balign 512, 255
