	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43CA00, 0xD7
	.balign 512, 255
