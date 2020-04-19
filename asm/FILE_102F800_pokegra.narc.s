	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x102F800, 0xB3BA74
	.balign 512, 255
