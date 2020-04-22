	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43DE00, 0x6F
	.balign 512, 255
