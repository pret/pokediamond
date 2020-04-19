	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x10CA00, 0x20
	.balign 512, 255
