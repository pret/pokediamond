	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x424000, 0xC4
	.balign 512, 255
