	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1AD200, 0x20
	.balign 512, 255
