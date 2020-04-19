	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x283BE00, 0x132D50
	.balign 512, 255
