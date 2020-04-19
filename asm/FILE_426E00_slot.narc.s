	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x426E00, 0x15944
	.balign 512, 255
