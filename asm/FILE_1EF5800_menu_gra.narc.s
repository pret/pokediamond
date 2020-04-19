	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1EF5800, 0x4B70
	.balign 512, 255
