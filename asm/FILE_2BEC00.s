	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2BEC00, 0x2440
	.balign 512, 255
