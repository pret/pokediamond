	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000005A4 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000006C ; chunk size
	.short 12 ; number of files
	.balign 4
	.word 0x00000000, 0x0000006B
	.word 0x0000006C, 0x000000D7
	.word 0x000000D8, 0x00000143
	.word 0x00000144, 0x000001AF
	.word 0x000001B0, 0x0000021B
	.word 0x0000021C, 0x00000287
	.word 0x00000288, 0x000002F3
	.word 0x000002F4, 0x0000035F
	.word 0x00000360, 0x000003CB
	.word 0x000003CC, 0x00000437
	.word 0x00000438, 0x000004A3
	.word 0x000004A4, 0x0000050F

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000518 ; chunk size
	.incbin "baserom.nds", 0x0, 0x6B
	.incbin "baserom.nds", 0x6C, 0x6B
	.incbin "baserom.nds", 0xD8, 0x6B
	.incbin "baserom.nds", 0x144, 0x6B
	.incbin "baserom.nds", 0x1B0, 0x6B
	.incbin "baserom.nds", 0x21C, 0x6B
	.incbin "baserom.nds", 0x288, 0x6B
	.incbin "baserom.nds", 0x2F4, 0x6B
	.incbin "baserom.nds", 0x360, 0x6B
	.incbin "baserom.nds", 0x3CC, 0x6B
	.incbin "baserom.nds", 0x438, 0x6B
	.incbin "baserom.nds", 0x4A4, 0x6B
	.balign 4, 255
