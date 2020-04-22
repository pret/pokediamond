	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x424200, 0x13C
	.balign 512, 255
