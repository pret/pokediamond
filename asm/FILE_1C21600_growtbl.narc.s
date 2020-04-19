	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C21600, 0xD14
	.balign 512, 255
