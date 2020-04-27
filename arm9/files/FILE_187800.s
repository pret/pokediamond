	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x187800, 0x1B760
	.balign 512, 255
