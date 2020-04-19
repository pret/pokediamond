	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x22ACC00, 0x245810
	.balign 512, 255
