	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x33E400, 0x228
	.balign 512, 255
