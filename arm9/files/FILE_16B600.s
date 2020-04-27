	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x16B600, 0x18D80
	.balign 512, 255
