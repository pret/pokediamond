	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x44DA00, 0x3ED8
	.balign 512, 255
