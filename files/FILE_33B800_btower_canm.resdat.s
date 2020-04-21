	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x33B800, 0x34
	.balign 512, 255
