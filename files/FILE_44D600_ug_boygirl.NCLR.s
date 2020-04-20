	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x44D600, 0x228
	.balign 512, 255
