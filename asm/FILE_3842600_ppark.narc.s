	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3842600, 0xBCC
	.balign 512, 255
