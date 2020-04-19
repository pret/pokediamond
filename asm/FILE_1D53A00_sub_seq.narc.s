	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D53A00, 0xC738
	.balign 512, 255
