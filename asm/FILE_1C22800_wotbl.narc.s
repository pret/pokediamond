	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C22800, 0x4940
	.balign 512, 255
