	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x412400, 0x824
	.balign 512, 255
