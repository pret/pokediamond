	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3787200, 0x13B44
	.balign 512, 255
