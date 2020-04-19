	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x33F800, 0x7362C
	.balign 512, 255
