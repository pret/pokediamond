    .section .text

	.global FileNameTable
FileNameTable:
	.incbin "baserom.nds", 0x336400, 0x3cc9c00 ; 0x157F
