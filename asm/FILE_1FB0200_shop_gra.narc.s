	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1FB0200, 0x2740
	.balign 512, 255
