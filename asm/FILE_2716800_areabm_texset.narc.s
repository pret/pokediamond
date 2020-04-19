	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2716800, 0x1254B4
	.balign 512, 255
