	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0xF4D400, 0x1A5C
	.balign 512, 255
