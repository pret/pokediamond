	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x415A00, 0x1188
	.balign 512, 255
