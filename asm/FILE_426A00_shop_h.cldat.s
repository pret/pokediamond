	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x426A00, 0x80
	.balign 512, 255
