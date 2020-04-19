	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x295A00, 0x940
	.balign 512, 255
