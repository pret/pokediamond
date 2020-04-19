	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x379AE00, 0x5D24
	.balign 512, 255
