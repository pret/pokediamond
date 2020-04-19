	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28CC00, 0x600
	.balign 512, 255
