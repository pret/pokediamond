	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x416C00, 0x578
	.balign 512, 255
