	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D6C800, 0x1180
	.balign 512, 255
