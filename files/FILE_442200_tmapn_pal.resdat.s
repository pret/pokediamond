	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x442200, 0x4C
	.balign 512, 255
