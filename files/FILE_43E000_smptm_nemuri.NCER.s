	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43E000, 0x63
	.balign 512, 255
