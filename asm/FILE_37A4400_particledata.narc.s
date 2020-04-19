	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x37A4400, 0x85FC
	.balign 512, 255
