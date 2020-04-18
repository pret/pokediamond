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
	.incbin "baserom.nds", 0x38432D4, 0xC48
	.incbin "baserom.nds", 0x3843F1C, 0xE0
	.incbin "baserom.nds", 0x3843FFC, 0x4CFC
	.incbin "baserom.nds", 0x3848CF8, 0x35C
	.incbin "baserom.nds", 0x3849054, 0x190
	.incbin "baserom.nds", 0x38491E4, 0xC48
	.incbin "baserom.nds", 0x3849E2C, 0xE0
	.incbin "baserom.nds", 0x3849F0C, 0x47C0
	.incbin "baserom.nds", 0x384E6CC, 0x35C
	.incbin "baserom.nds", 0x384EA28, 0x190
	.incbin "baserom.nds", 0x384EBB8, 0xC40
	.incbin "baserom.nds", 0x384F7F8, 0xE0
	.incbin "baserom.nds", 0x384F8D8, 0x47BC
	.incbin "baserom.nds", 0x3854094, 0x35C
	.incbin "baserom.nds", 0x38543F0, 0x190
	.incbin "baserom.nds", 0x3854580, 0xC48
	.incbin "baserom.nds", 0x38551C8, 0xE0
	.incbin "baserom.nds", 0x38552A8, 0x4DC4
	.incbin "baserom.nds", 0x385A06C, 0x35C
	.incbin "baserom.nds", 0x385A3C8, 0x190
