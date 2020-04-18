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
	.incbin "baserom.nds", 0x1EDB75C, 0xC0
	.incbin "baserom.nds", 0x1EDB81C, 0xC0
	.incbin "baserom.nds", 0x1EDB8DC, 0xC0
	.incbin "baserom.nds", 0x1EDB99C, 0xC0
	.incbin "baserom.nds", 0x1EDBA5C, 0xC0
	.incbin "baserom.nds", 0x1EDBB1C, 0xC0
	.incbin "baserom.nds", 0x1EDBBDC, 0xC0
	.incbin "baserom.nds", 0x1EDBC9C, 0xC0
	.incbin "baserom.nds", 0x1EDBD5C, 0xC0
	.incbin "baserom.nds", 0x1EDBE1C, 0xC0
	.incbin "baserom.nds", 0x1EDBEDC, 0xC0
	.incbin "baserom.nds", 0x1EDBF9C, 0xC0
	.incbin "baserom.nds", 0x1EDC05C, 0x3C40
	.incbin "baserom.nds", 0x1EDFC9C, 0xC40
	.incbin "baserom.nds", 0x1EE08DC, 0xC40
	.incbin "baserom.nds", 0x1EE151C, 0x2C40
	.incbin "baserom.nds", 0x1EE415C, 0x3040
	.incbin "baserom.nds", 0x1EE719C, 0xC40
	.incbin "baserom.nds", 0x1EE7DDC, 0xC40
	.incbin "baserom.nds", 0x1EE8A1C, 0x2840
	.incbin "baserom.nds", 0x1EEB25C, 0x2840
	.incbin "baserom.nds", 0x1EEDA9C, 0x1040
	.incbin "baserom.nds", 0x1EEEADC, 0x1040
	.incbin "baserom.nds", 0x1EEFB1C, 0xC40
	.incbin "baserom.nds", 0x1EF075C, 0x624
	.incbin "baserom.nds", 0x1EF0D80, 0x624
	.incbin "baserom.nds", 0x1EF13A4, 0x624
	.incbin "baserom.nds", 0x1EF19C8, 0x624
	.incbin "baserom.nds", 0x1EF1FEC, 0x624
	.incbin "baserom.nds", 0x1EF2610, 0x624
	.incbin "baserom.nds", 0x1EF2C34, 0x624
	.incbin "baserom.nds", 0x1EF3258, 0x624
	.incbin "baserom.nds", 0x1EF387C, 0x624
	.incbin "baserom.nds", 0x1EF3EA0, 0x624
	.incbin "baserom.nds", 0x1EF44C4, 0x624
	.incbin "baserom.nds", 0x1EF4AE8, 0x624
	.incbin "baserom.nds", 0x1EF510C, 0x624
