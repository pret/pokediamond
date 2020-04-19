	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DC0000, 0x1BB20
	.balign 512, 255
