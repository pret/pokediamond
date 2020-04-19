	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x385D400, 0x16C
	.balign 512, 255
