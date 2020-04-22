	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x10CC00, 0x386E0
	.balign 512, 255
