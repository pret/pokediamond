	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1EFA400, 0x10B8
	.balign 512, 255
