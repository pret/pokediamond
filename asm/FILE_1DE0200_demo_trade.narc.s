	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DE0200, 0x7B18
	.balign 512, 255
