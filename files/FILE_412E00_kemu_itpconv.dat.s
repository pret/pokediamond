	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x412E00, 0x14
	.balign 512, 255
