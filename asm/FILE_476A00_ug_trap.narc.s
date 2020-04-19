	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x476A00, 0x1DBAC
	.balign 512, 255
