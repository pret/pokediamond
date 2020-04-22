	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x26B200, 0x17CE0
	.balign 512, 255
