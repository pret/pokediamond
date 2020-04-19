	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x283000, 0x100
	.balign 512, 255
