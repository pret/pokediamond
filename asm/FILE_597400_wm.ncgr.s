	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x597400, 0x240
	.balign 512, 255
