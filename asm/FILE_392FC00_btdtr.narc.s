	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x392FC00, 0x83C0
	.balign 512, 255
