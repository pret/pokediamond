	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43DA00, 0x228
	.balign 512, 255
