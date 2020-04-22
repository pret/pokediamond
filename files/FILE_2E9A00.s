	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2E9A00, 0x5580
	.balign 512, 255
