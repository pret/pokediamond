	.text

	.global FileAllocationTable
FileAllocationTable:
	.incbin "baserom.nds", 0x337A00, 0xB20
