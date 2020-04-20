	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x408C00, 0x48
	.balign 512, 255
