	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x286C00, 0x1900
	.balign 512, 255
