	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x49A000, 0x34
	.balign 512, 255
