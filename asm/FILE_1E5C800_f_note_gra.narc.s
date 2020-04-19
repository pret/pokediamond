	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E5C800, 0x297C
	.balign 512, 255
