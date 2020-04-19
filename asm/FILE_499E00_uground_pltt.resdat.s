	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x499E00, 0x34
	.balign 512, 255
