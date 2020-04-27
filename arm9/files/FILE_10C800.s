	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x10C800, 0x20
	.balign 512, 255
