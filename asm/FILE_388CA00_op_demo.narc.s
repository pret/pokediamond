	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x388CA00, 0x97188
	.balign 512, 255
