
		.include "asm/macros.inc"
		.include "global.inc"

	.section .rodata

	; 0x020EC710
	.incbin "baserom.nds", 0xF0710, 0x3F8 ; this does not seem to be code
