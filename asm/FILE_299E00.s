	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x299E00, 0x2480
	.balign 512, 255
