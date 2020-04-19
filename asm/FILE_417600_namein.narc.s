	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x417600, 0x3F58
	.balign 512, 255
