	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x33AE00, 0x824
	.balign 512, 255
