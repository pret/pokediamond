	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DFE00, 0x19260
	.balign 512, 255
