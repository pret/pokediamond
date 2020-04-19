	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x425400, 0x1B4
	.balign 512, 255
