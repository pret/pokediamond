	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28C200, 0x900
	.balign 512, 255
