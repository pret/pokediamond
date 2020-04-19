	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D61C00, 0x14F4
	.balign 512, 255
