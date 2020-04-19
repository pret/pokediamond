	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00017358 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000AC ; chunk size
	.short 20 ; number of files
	.balign 4
	.word 0x00000000, 0x00000C48
	.word 0x00000C48, 0x00000D28
	.word 0x00000D28, 0x00005A24
	.word 0x00005A24, 0x00005D80
	.word 0x00005D80, 0x00005F10
	.word 0x00005F10, 0x00006B58
	.word 0x00006B58, 0x00006C38
	.word 0x00006C38, 0x0000B3F8
	.word 0x0000B3F8, 0x0000B754
	.word 0x0000B754, 0x0000B8E4
	.word 0x0000B8E4, 0x0000C524
	.word 0x0000C524, 0x0000C604
	.word 0x0000C604, 0x00010DC0
	.word 0x00010DC0, 0x0001111C
	.word 0x0001111C, 0x000112AC
	.word 0x000112AC, 0x00011EF4
	.word 0x00011EF4, 0x00011FD4
	.word 0x00011FD4, 0x00016D98
	.word 0x00016D98, 0x000170F4
	.word 0x000170F4, 0x00017284

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0001728C ; chunk size
	.incbin "baserom.nds", 0x0, 0xC48
	.incbin "baserom.nds", 0xC48, 0xE0
	.incbin "baserom.nds", 0xD28, 0x4CFC
	.incbin "baserom.nds", 0x5A24, 0x35C
	.incbin "baserom.nds", 0x5D80, 0x190
	.incbin "baserom.nds", 0x5F10, 0xC48
	.incbin "baserom.nds", 0x6B58, 0xE0
	.incbin "baserom.nds", 0x6C38, 0x47C0
	.incbin "baserom.nds", 0xB3F8, 0x35C
	.incbin "baserom.nds", 0xB754, 0x190
	.incbin "baserom.nds", 0xB8E4, 0xC40
	.incbin "baserom.nds", 0xC524, 0xE0
	.incbin "baserom.nds", 0xC604, 0x47BC
	.incbin "baserom.nds", 0x10DC0, 0x35C
	.incbin "baserom.nds", 0x1111C, 0x190
	.incbin "baserom.nds", 0x112AC, 0xC48
	.incbin "baserom.nds", 0x11EF4, 0xE0
	.incbin "baserom.nds", 0x11FD4, 0x4DC4
	.incbin "baserom.nds", 0x16D98, 0x35C
	.incbin "baserom.nds", 0x170F4, 0x190
	.balign 4, 255
