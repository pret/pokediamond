	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x29E800, 0x3040
	.balign 512, 255
