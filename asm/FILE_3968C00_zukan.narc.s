	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3968C00, 0x11D1C
	.balign 512, 255
