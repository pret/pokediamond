	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2D9E00, 0x52C0
	.balign 512, 255
