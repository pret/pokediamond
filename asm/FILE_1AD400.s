	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1AD400, 0x329E0
	.balign 512, 255
