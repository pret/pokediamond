	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0001A130 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000134 ; chunk size
	.short 37 ; number of files
	.balign 4
	.word 0x00000000, 0x000000C0
	.word 0x000000C0, 0x00000180
	.word 0x00000180, 0x00000240
	.word 0x00000240, 0x00000300
	.word 0x00000300, 0x000003C0
	.word 0x000003C0, 0x00000480
	.word 0x00000480, 0x00000540
	.word 0x00000540, 0x00000600
	.word 0x00000600, 0x000006C0
	.word 0x000006C0, 0x00000780
	.word 0x00000780, 0x00000840
	.word 0x00000840, 0x00000900
	.word 0x00000900, 0x00004540
	.word 0x00004540, 0x00005180
	.word 0x00005180, 0x00005DC0
	.word 0x00005DC0, 0x00008A00
	.word 0x00008A00, 0x0000BA40
	.word 0x0000BA40, 0x0000C680
	.word 0x0000C680, 0x0000D2C0
	.word 0x0000D2C0, 0x0000FB00
	.word 0x0000FB00, 0x00012340
	.word 0x00012340, 0x00013380
	.word 0x00013380, 0x000143C0
	.word 0x000143C0, 0x00015000
	.word 0x00015000, 0x00015624
	.word 0x00015624, 0x00015C48
	.word 0x00015C48, 0x0001626C
	.word 0x0001626C, 0x00016890
	.word 0x00016890, 0x00016EB4
	.word 0x00016EB4, 0x000174D8
	.word 0x000174D8, 0x00017AFC
	.word 0x00017AFC, 0x00018120
	.word 0x00018120, 0x00018744
	.word 0x00018744, 0x00018D68
	.word 0x00018D68, 0x0001938C
	.word 0x0001938C, 0x000199B0
	.word 0x000199B0, 0x00019FD4

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00019FDC ; chunk size
	.incbin "baserom.nds", 0x1EDB75C, 0x19FD4
	.balign 512, 255
