	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x43EA00, 0x250
	.balign 512, 255
