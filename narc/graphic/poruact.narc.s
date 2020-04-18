	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000014AC ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000010C ; chunk size
	.short 32 ; number of files
	.balign 4
	.word 0x00000000, 0x00000830
	.word 0x00000830, 0x0000089B
	.word 0x0000089C, 0x0000090B
	.word 0x0000090C, 0x00000966
	.word 0x00000968, 0x000009C2
	.word 0x000009C4, 0x00000A1E
	.word 0x00000A20, 0x00000A7A
	.word 0x00000A7C, 0x00000AD6
	.word 0x00000AD8, 0x00000B32
	.word 0x00000B34, 0x00000B8E
	.word 0x00000B90, 0x00000BEA
	.word 0x00000BEC, 0x00000C46
	.word 0x00000C48, 0x00000CA2
	.word 0x00000CA4, 0x00000CFE
	.word 0x00000D00, 0x00000D5A
	.word 0x00000D5C, 0x00000DB6
	.word 0x00000DB8, 0x00000E12
	.word 0x00000E14, 0x00000E6E
	.word 0x00000E70, 0x00000ECA
	.word 0x00000ECC, 0x00000F26
	.word 0x00000F28, 0x00000F82
	.word 0x00000F84, 0x00000FDE
	.word 0x00000FE0, 0x0000103A
	.word 0x0000103C, 0x00001096
	.word 0x00001098, 0x000010F2
	.word 0x000010F4, 0x0000114E
	.word 0x00001150, 0x000011AA
	.word 0x000011AC, 0x00001206
	.word 0x00001208, 0x00001262
	.word 0x00001264, 0x000012BE
	.word 0x000012C0, 0x0000131A
	.word 0x0000131C, 0x00001376

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00001380 ; chunk size
	.incbin "baserom.nds", 0x1F86734, 0x830
	.incbin "baserom.nds", 0x1F86F64, 0x6B
	.incbin "baserom.nds", 0x1F86FD0, 0x6F
	.incbin "baserom.nds", 0x1F87040, 0x5A
	.incbin "baserom.nds", 0x1F8709C, 0x5A
	.incbin "baserom.nds", 0x1F870F8, 0x5A
	.incbin "baserom.nds", 0x1F87154, 0x5A
	.incbin "baserom.nds", 0x1F871B0, 0x5A
	.incbin "baserom.nds", 0x1F8720C, 0x5A
	.incbin "baserom.nds", 0x1F87268, 0x5A
	.incbin "baserom.nds", 0x1F872C4, 0x5A
	.incbin "baserom.nds", 0x1F87320, 0x5A
	.incbin "baserom.nds", 0x1F8737C, 0x5A
	.incbin "baserom.nds", 0x1F873D8, 0x5A
	.incbin "baserom.nds", 0x1F87434, 0x5A
	.incbin "baserom.nds", 0x1F87490, 0x5A
	.incbin "baserom.nds", 0x1F874EC, 0x5A
	.incbin "baserom.nds", 0x1F87548, 0x5A
	.incbin "baserom.nds", 0x1F875A4, 0x5A
	.incbin "baserom.nds", 0x1F87600, 0x5A
	.incbin "baserom.nds", 0x1F8765C, 0x5A
	.incbin "baserom.nds", 0x1F876B8, 0x5A
	.incbin "baserom.nds", 0x1F87714, 0x5A
	.incbin "baserom.nds", 0x1F87770, 0x5A
	.incbin "baserom.nds", 0x1F877CC, 0x5A
	.incbin "baserom.nds", 0x1F87828, 0x5A
	.incbin "baserom.nds", 0x1F87884, 0x5A
	.incbin "baserom.nds", 0x1F878E0, 0x5A
	.incbin "baserom.nds", 0x1F8793C, 0x5A
	.incbin "baserom.nds", 0x1F87998, 0x5A
	.incbin "baserom.nds", 0x1F879F4, 0x5A
	.incbin "baserom.nds", 0x1F87A50, 0x5A
