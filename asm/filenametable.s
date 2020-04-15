	.text
	.global FileNameTable
FileNameTable:
	.incbin "baserom.nds", 0x336400, 0x157F
