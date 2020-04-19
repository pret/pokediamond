	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1EFB600, 0x78C4
	.balign 512, 255
