	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D6DA00, 0x2C5C
	.balign 512, 255
