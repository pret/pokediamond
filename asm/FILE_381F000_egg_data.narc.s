	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x381F000, 0x2AFC
	.balign 512, 255
