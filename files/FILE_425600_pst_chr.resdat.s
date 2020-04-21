	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x425600, 0x424
	.balign 512, 255
