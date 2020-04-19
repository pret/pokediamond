	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x49A200, 0xA234
	.balign 512, 255
