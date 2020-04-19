	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1FB2A00, 0x14F10
	.balign 512, 255
