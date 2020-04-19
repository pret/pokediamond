	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43EE00, 0x250
	.balign 512, 255
