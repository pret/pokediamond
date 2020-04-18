	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00002A74 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000074 ; chunk size
	.short 13 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000575
	.word 0x00000578, 0x000007BA
	.word 0x000007BC, 0x00000AFE
	.word 0x00000B00, 0x00000C21
	.word 0x00000C24, 0x00000E22
	.word 0x00000E24, 0x00000F44
	.word 0x00000F44, 0x000017B4
	.word 0x000017B4, 0x0000197E
	.word 0x00001980, 0x00001B46
	.word 0x00001B48, 0x000024EC
	.word 0x000024EC, 0x000027B9
	.word 0x000027BC, 0x000029D7

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000029E0 ; chunk size
	.incbin "baserom.nds", 0x442C9C, 0x228
	.incbin "baserom.nds", 0x442EC4, 0x34D
	.incbin "baserom.nds", 0x443214, 0x242
	.incbin "baserom.nds", 0x443458, 0x342
	.incbin "baserom.nds", 0x44379C, 0x121
	.incbin "baserom.nds", 0x4438C0, 0x1FE
	.incbin "baserom.nds", 0x443AC0, 0x120
	.incbin "baserom.nds", 0x443BE0, 0x870
	.incbin "baserom.nds", 0x444450, 0x1CA
	.incbin "baserom.nds", 0x44461C, 0x1C6
	.incbin "baserom.nds", 0x4447E4, 0x9A4
	.incbin "baserom.nds", 0x445188, 0x2CD
	.incbin "baserom.nds", 0x445458, 0x21B
