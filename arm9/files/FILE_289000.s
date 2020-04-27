	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x289000, 0x560
	.balign 512, 255
