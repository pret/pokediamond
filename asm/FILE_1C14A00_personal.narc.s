	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C14A00, 0x65F8
	.balign 512, 255
