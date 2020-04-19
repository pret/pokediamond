	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F71600, 0xE5C4
	.balign 512, 255
