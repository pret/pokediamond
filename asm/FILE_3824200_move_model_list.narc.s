	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3824200, 0x264
	.balign 512, 255
