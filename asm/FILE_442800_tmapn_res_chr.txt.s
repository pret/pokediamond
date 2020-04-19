	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x442800, 0xDC
	.balign 512, 255
