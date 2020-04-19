	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C32600, 0x2584
	.balign 512, 255
