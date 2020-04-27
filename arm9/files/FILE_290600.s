	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x290600, 0xB40
	.balign 512, 255
