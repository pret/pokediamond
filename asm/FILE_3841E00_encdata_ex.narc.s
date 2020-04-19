	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3841E00, 0x724
	.balign 512, 255
