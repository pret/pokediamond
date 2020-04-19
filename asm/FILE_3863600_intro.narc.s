	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3863600, 0x1B38C
	.balign 512, 255
