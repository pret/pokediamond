	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x392A200, 0x595C
	.balign 512, 255
