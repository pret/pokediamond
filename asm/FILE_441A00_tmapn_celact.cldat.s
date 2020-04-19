	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x441A00, 0xC0
	.balign 512, 255
