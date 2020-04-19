	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000069E4 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000006C ; chunk size
	.short 12 ; number of files
	.balign 4
	.word 0x00000000, 0x000001AE
	.word 0x000001B0, 0x0000033C
	.word 0x0000033C, 0x0000177C
	.word 0x0000177C, 0x000023BC
	.word 0x000023BC, 0x00003CEC
	.word 0x00003CEC, 0x00004F9C
	.word 0x00004F9C, 0x0000515E
	.word 0x00005160, 0x000053AA
	.word 0x000053AC, 0x000058BF
	.word 0x000058C0, 0x00005D07
	.word 0x00005D08, 0x0000632C
	.word 0x0000632C, 0x00006950

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00006958 ; chunk size
	.incbin "baserom.nds", 0x0, 0x1AE
	.incbin "baserom.nds", 0x1B0, 0x18C
	.incbin "baserom.nds", 0x33C, 0x1440
	.incbin "baserom.nds", 0x177C, 0xC40
	.incbin "baserom.nds", 0x23BC, 0x1930
	.incbin "baserom.nds", 0x3CEC, 0x12B0
	.incbin "baserom.nds", 0x4F9C, 0x1C2
	.incbin "baserom.nds", 0x5160, 0x24A
	.incbin "baserom.nds", 0x53AC, 0x513
	.incbin "baserom.nds", 0x58C0, 0x447
	.incbin "baserom.nds", 0x5D08, 0x624
	.incbin "baserom.nds", 0x632C, 0x624
	.balign 4, 255
