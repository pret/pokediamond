	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43E600, 0x228
	.balign 512, 255
