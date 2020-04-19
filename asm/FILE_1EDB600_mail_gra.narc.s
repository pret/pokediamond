	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1EDB600, 0x1A130
	.balign 512, 255
