	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x102EC00, 0x22C
	.balign 512, 255
