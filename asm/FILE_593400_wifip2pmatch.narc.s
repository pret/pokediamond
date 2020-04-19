	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x593400, 0x3E14
	.balign 512, 255
