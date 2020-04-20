	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000394C ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000006C ; chunk size
	.short 12 ; number of files
	.balign 4
	.word 0x00000000, 0x0000009F
	.word 0x000000A0, 0x00000147
	.word 0x00000148, 0x00000D88
	.word 0x00000D88, 0x00000FB0
	.word 0x00000FB0, 0x000015D4
	.word 0x000015D4, 0x00001BF8
	.word 0x00001BF8, 0x0000221C
	.word 0x0000221C, 0x00002840
	.word 0x00002840, 0x00002E64
	.word 0x00002E64, 0x00002ED4
	.word 0x00002ED4, 0x00003294
	.word 0x00003294, 0x000038B8

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000038C0 ; chunk size
	.incbin "baserom.nds", 0x58FA94, 0x38B8
	.balign 512, 255
