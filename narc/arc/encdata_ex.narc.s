	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000724 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000006C ; chunk size
	.short 12 ; number of files
	.balign 4
	.word 0x00000000, 0x00000004
	.word 0x00000004, 0x00000430
	.word 0x00000430, 0x00000448
	.word 0x00000448, 0x00000460
	.word 0x00000460, 0x00000478
	.word 0x00000478, 0x00000490
	.word 0x00000490, 0x000004A8
	.word 0x000004A8, 0x000004C0
	.word 0x000004C0, 0x00000500
	.word 0x00000500, 0x00000580
	.word 0x00000580, 0x00000600
	.word 0x00000600, 0x00000690

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000698 ; chunk size
	.incbin "baserom.nds", 0x3841E94, 0x4
	.incbin "baserom.nds", 0x3841E98, 0x42C
	.incbin "baserom.nds", 0x38422C4, 0x18
	.incbin "baserom.nds", 0x38422DC, 0x18
	.incbin "baserom.nds", 0x38422F4, 0x18
	.incbin "baserom.nds", 0x384230C, 0x18
	.incbin "baserom.nds", 0x3842324, 0x18
	.incbin "baserom.nds", 0x384233C, 0x18
	.incbin "baserom.nds", 0x3842354, 0x40
	.incbin "baserom.nds", 0x3842394, 0x80
	.incbin "baserom.nds", 0x3842414, 0x80
	.incbin "baserom.nds", 0x3842494, 0x90
