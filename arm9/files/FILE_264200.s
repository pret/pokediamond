	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x264200, 0x6E80
	.balign 512, 255
