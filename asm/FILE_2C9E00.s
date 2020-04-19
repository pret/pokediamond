	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2C9E00, 0x4AE0
	.balign 512, 255
