	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2A1A00, 0x47A0
	.balign 512, 255
