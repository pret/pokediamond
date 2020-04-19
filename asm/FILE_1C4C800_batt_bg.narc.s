	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C4C800, 0x9C47C
	.balign 512, 255
