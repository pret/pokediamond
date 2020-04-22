	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2BC400, 0x2660
	.balign 512, 255
