	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E94E00, 0x7E14
	.balign 512, 255
