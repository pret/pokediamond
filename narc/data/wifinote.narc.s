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
	.incbin "baserom.nds", 0x0, 0x9F
	.incbin "baserom.nds", 0xA0, 0xA7
	.incbin "baserom.nds", 0x148, 0xC40
	.incbin "baserom.nds", 0xD88, 0x228
	.incbin "baserom.nds", 0xFB0, 0x624
	.incbin "baserom.nds", 0x15D4, 0x624
	.incbin "baserom.nds", 0x1BF8, 0x624
	.incbin "baserom.nds", 0x221C, 0x624
	.incbin "baserom.nds", 0x2840, 0x624
	.incbin "baserom.nds", 0x2E64, 0x70
	.incbin "baserom.nds", 0x2ED4, 0x3C0
	.incbin "baserom.nds", 0x3294, 0x624
	.balign 4, 255
