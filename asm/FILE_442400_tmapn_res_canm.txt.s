	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x442400, 0xAA
	.balign 512, 255
