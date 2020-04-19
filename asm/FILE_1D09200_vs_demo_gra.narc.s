	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D09200, 0x5180
	.balign 512, 255
