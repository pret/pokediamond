	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x298A00, 0xFC0
	.balign 512, 255
