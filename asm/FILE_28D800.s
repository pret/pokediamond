	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28D800, 0x4A0
	.balign 512, 255
