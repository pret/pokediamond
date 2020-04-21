	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2ADA00, 0x1080
	.balign 512, 255
