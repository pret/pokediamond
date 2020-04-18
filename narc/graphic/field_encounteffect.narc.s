	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00009708 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000DC ; chunk size
	.short 26 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000450
	.word 0x00000450, 0x00000C80
	.word 0x00000C80, 0x00000CEF
	.word 0x00000CF0, 0x00000D5B
	.word 0x00000D5C, 0x00002D8C
	.word 0x00002D8C, 0x00002E51
	.word 0x00002E54, 0x00002F25
	.word 0x00002F28, 0x00004F58
	.word 0x00004F58, 0x00004FC7
	.word 0x00004FC8, 0x00005043
	.word 0x00005044, 0x0000526C
	.word 0x0000526C, 0x00005EAC
	.word 0x00005EAC, 0x000062D0
	.word 0x000062D0, 0x000064F8
	.word 0x000064F8, 0x00007D28
	.word 0x00007D28, 0x000080BA
	.word 0x000080BC, 0x0000822E
	.word 0x00008230, 0x00008458
	.word 0x00008458, 0x00008680
	.word 0x00008680, 0x000088A8
	.word 0x000088A8, 0x00008AD0
	.word 0x00008AD0, 0x00008CF8
	.word 0x00008CF8, 0x00009528
	.word 0x00009528, 0x00009593
	.word 0x00009594, 0x00009603

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000960C ; chunk size
	.incbin "baserom.nds", 0x1E69D04, 0x228
	.incbin "baserom.nds", 0x1E69F2C, 0x228
	.incbin "baserom.nds", 0x1E6A154, 0x830
	.incbin "baserom.nds", 0x1E6A984, 0x6F
	.incbin "baserom.nds", 0x1E6A9F4, 0x6B
	.incbin "baserom.nds", 0x1E6AA60, 0x2030
	.incbin "baserom.nds", 0x1E6CA90, 0xC5
	.incbin "baserom.nds", 0x1E6CB58, 0xD1
	.incbin "baserom.nds", 0x1E6CC2C, 0x2030
	.incbin "baserom.nds", 0x1E6EC5C, 0x6F
	.incbin "baserom.nds", 0x1E6ECCC, 0x7B
	.incbin "baserom.nds", 0x1E6ED48, 0x228
	.incbin "baserom.nds", 0x1E6EF70, 0xC40
	.incbin "baserom.nds", 0x1E6FBB0, 0x424
	.incbin "baserom.nds", 0x1E6FFD4, 0x228
	.incbin "baserom.nds", 0x1E701FC, 0x1830
	.incbin "baserom.nds", 0x1E71A2C, 0x392
	.incbin "baserom.nds", 0x1E71DC0, 0x172
	.incbin "baserom.nds", 0x1E71F34, 0x228
	.incbin "baserom.nds", 0x1E7215C, 0x228
	.incbin "baserom.nds", 0x1E72384, 0x228
	.incbin "baserom.nds", 0x1E725AC, 0x228
	.incbin "baserom.nds", 0x1E727D4, 0x228
	.incbin "baserom.nds", 0x1E729FC, 0x830
	.incbin "baserom.nds", 0x1E7322C, 0x6B
	.incbin "baserom.nds", 0x1E73298, 0x6F
