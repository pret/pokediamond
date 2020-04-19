	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x33BE00, 0x34
	.balign 512, 255
