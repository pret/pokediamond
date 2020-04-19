	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E94800, 0x5A4
	.balign 512, 255
