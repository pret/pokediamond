	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00003164 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000DC ; chunk size
	.short 26 ; number of files
	.balign 4
	.word 0x00000000, 0x00000136
	.word 0x00000138, 0x00000201
	.word 0x00000204, 0x00000467
	.word 0x00000468, 0x000005B9
	.word 0x000005BC, 0x000006EF
	.word 0x000006F0, 0x0000075F
	.word 0x00000760, 0x00000974
	.word 0x00000974, 0x00000B32
	.word 0x00000B34, 0x00000D16
	.word 0x00000D18, 0x0000149C
	.word 0x0000149C, 0x000014F6
	.word 0x000014F8, 0x00001616
	.word 0x00001618, 0x000016EC
	.word 0x000016EC, 0x000017BF
	.word 0x000017C0, 0x00001897
	.word 0x00001898, 0x0000196F
	.word 0x00001970, 0x00001A47
	.word 0x00001A48, 0x00001B1F
	.word 0x00001B20, 0x00001BF7
	.word 0x00001BF8, 0x00001CCF
	.word 0x00001CD0, 0x000028F9
	.word 0x000028FC, 0x00002978
	.word 0x00002978, 0x00002A33
	.word 0x00002A34, 0x00002AE1
	.word 0x00002AE4, 0x00002FE4
	.word 0x00002FE4, 0x00003060

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00003068 ; chunk size
	.incbin "baserom.nds", 0x1F6E504, 0x136
	.incbin "baserom.nds", 0x1F6E63C, 0xC9
	.incbin "baserom.nds", 0x1F6E708, 0x263
	.incbin "baserom.nds", 0x1F6E96C, 0x151
	.incbin "baserom.nds", 0x1F6EAC0, 0x133
	.incbin "baserom.nds", 0x1F6EBF4, 0x6F
	.incbin "baserom.nds", 0x1F6EC64, 0x214
	.incbin "baserom.nds", 0x1F6EE78, 0x1BE
	.incbin "baserom.nds", 0x1F6F038, 0x1E2
	.incbin "baserom.nds", 0x1F6F21C, 0x784
	.incbin "baserom.nds", 0x1F6F9A0, 0x5A
	.incbin "baserom.nds", 0x1F6F9FC, 0x11E
	.incbin "baserom.nds", 0x1F6FB1C, 0xD4
	.incbin "baserom.nds", 0x1F6FBF0, 0xD3
	.incbin "baserom.nds", 0x1F6FCC4, 0xD7
	.incbin "baserom.nds", 0x1F6FD9C, 0xD7
	.incbin "baserom.nds", 0x1F6FE74, 0xD7
	.incbin "baserom.nds", 0x1F6FF4C, 0xD7
	.incbin "baserom.nds", 0x1F70024, 0xD7
	.incbin "baserom.nds", 0x1F700FC, 0xD7
	.incbin "baserom.nds", 0x1F701D4, 0xC29
	.incbin "baserom.nds", 0x1F70E00, 0x7C
	.incbin "baserom.nds", 0x1F70E7C, 0xBB
	.incbin "baserom.nds", 0x1F70F38, 0xAD
	.incbin "baserom.nds", 0x1F70FE8, 0x500
	.incbin "baserom.nds", 0x1F714E8, 0x7C
