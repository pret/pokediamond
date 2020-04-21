	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x424600, 0x94
	.balign 512, 255
