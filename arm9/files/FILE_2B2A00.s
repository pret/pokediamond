	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2B2A00, 0x4AC0
	.balign 512, 255
