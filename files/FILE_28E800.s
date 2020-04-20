	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x28E800, 0x9A0
	.balign 512, 255
