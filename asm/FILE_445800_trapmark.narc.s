	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x445800, 0x264
	.balign 512, 255
