	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x253C200, 0x1D45CC
	.balign 512, 255
