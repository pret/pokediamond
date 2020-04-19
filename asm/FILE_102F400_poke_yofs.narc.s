	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x102F400, 0x22C
	.balign 512, 255
