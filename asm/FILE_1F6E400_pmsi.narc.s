	.include "asm/macros.inc"
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
	.incbin "baserom.nds", 0x1F6E504, 0x3060
	.balign 512, 255
