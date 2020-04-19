	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x207DE00, 0x534
	.balign 512, 255
