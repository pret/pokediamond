	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00019C74 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000144 ; chunk size
	.short 39 ; number of files
	.balign 4
	.word 0x00000000, 0x0000055C
	.word 0x0000055C, 0x00000708
	.word 0x00000708, 0x00004738
	.word 0x00004738, 0x00004960
	.word 0x00004960, 0x00004A50
	.word 0x00004A50, 0x00004B28
	.word 0x00004B28, 0x00004C58
	.word 0x00004C58, 0x00006898
	.word 0x00006898, 0x00006AC0
	.word 0x00006AC0, 0x000072E4
	.word 0x000072E4, 0x00007B08
	.word 0x00007B08, 0x00008B48
	.word 0x00008B48, 0x00008D70
	.word 0x00008D70, 0x00009394
	.word 0x00009394, 0x000095BC
	.word 0x000095BC, 0x0000FB3C
	.word 0x0000FB3C, 0x0000FD64
	.word 0x0000FD64, 0x000105A4
	.word 0x000105A4, 0x000107CC
	.word 0x000107CC, 0x0001083B
	.word 0x0001083C, 0x000108A7
	.word 0x000108A8, 0x00010958
	.word 0x00010958, 0x000109C7
	.word 0x000109C8, 0x00010A43
	.word 0x00010A44, 0x000113F4
	.word 0x000113F4, 0x00011463
	.word 0x00011464, 0x000114E7
	.word 0x000114E8, 0x00011998
	.word 0x00011998, 0x00011A17
	.word 0x00011A18, 0x00011AAB
	.word 0x00011AAC, 0x000134DC
	.word 0x000134DC, 0x00013704
	.word 0x00013704, 0x00013C60
	.word 0x00013C60, 0x00013E0C
	.word 0x00013E0C, 0x00017E3C
	.word 0x00017E3C, 0x00018064
	.word 0x00018064, 0x00018488
	.word 0x00018488, 0x000198C8
	.word 0x000198C8, 0x00019B08

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00019B10 ; chunk size
	.incbin "baserom.nds", 0x1DA636C, 0x19B08
	.balign 512, 255
