	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x294000, 0x900
	.balign 512, 255
