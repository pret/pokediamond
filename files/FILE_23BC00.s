	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x23BC00, 0x28500
	.balign 512, 255
