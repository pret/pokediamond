	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x57FC00, 0xF8A8
	.balign 512, 255
