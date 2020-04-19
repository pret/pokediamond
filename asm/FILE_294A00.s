	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x294A00, 0x9C0
	.balign 512, 255
