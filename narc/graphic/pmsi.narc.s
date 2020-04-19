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
	.incbin "baserom.nds", 0x0, 0x136
	.incbin "baserom.nds", 0x138, 0xC9
	.incbin "baserom.nds", 0x204, 0x263
	.incbin "baserom.nds", 0x468, 0x151
	.incbin "baserom.nds", 0x5BC, 0x133
	.incbin "baserom.nds", 0x6F0, 0x6F
	.incbin "baserom.nds", 0x760, 0x214
	.incbin "baserom.nds", 0x974, 0x1BE
	.incbin "baserom.nds", 0xB34, 0x1E2
	.incbin "baserom.nds", 0xD18, 0x784
	.incbin "baserom.nds", 0x149C, 0x5A
	.incbin "baserom.nds", 0x14F8, 0x11E
	.incbin "baserom.nds", 0x1618, 0xD4
	.incbin "baserom.nds", 0x16EC, 0xD3
	.incbin "baserom.nds", 0x17C0, 0xD7
	.incbin "baserom.nds", 0x1898, 0xD7
	.incbin "baserom.nds", 0x1970, 0xD7
	.incbin "baserom.nds", 0x1A48, 0xD7
	.incbin "baserom.nds", 0x1B20, 0xD7
	.incbin "baserom.nds", 0x1BF8, 0xD7
	.incbin "baserom.nds", 0x1CD0, 0xC29
	.incbin "baserom.nds", 0x28FC, 0x7C
	.incbin "baserom.nds", 0x2978, 0xBB
	.incbin "baserom.nds", 0x2A34, 0xAD
	.incbin "baserom.nds", 0x2AE4, 0x500
	.incbin "baserom.nds", 0x2FE4, 0x7C
	.balign 4, 255
