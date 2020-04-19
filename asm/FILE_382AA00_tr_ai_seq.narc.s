	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x382AA00, 0xA5D0
	.balign 512, 255
