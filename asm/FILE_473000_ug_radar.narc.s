	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x473000, 0x3868
	.balign 512, 255
