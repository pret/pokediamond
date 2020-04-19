	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x451C00, 0x109
	.balign 512, 255
