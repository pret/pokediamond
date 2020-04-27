	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x298000, 0x600
	.balign 512, 255
