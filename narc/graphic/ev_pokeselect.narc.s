	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00022524 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000009C ; chunk size
	.short 18 ; number of files
	.balign 4
	.word 0x00000000, 0x000017D4
	.word 0x000017D4, 0x0000EB40
	.word 0x0000EB40, 0x0000EE44
	.word 0x0000EE44, 0x00011478
	.word 0x00011478, 0x0001177C
	.word 0x0001177C, 0x00013E08
	.word 0x00013E08, 0x0001410C
	.word 0x0001410C, 0x00016790
	.word 0x00016790, 0x0001E394
	.word 0x0001E394, 0x0001F87C
	.word 0x0001F87C, 0x0001FAAC
	.word 0x0001FAAC, 0x0001FCD4
	.word 0x0001FCD4, 0x0001FD37
	.word 0x0001FD38, 0x0001FDA7
	.word 0x0001FDA8, 0x00021DE8
	.word 0x00021DE8, 0x00022010
	.word 0x00022010, 0x00022238
	.word 0x00022238, 0x00022460

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00022468 ; chunk size
	.incbin "baserom.nds", 0x1E3A2C4, 0x17D4
	.incbin "baserom.nds", 0x1E3BA98, 0xD36C
	.incbin "baserom.nds", 0x1E48E04, 0x304
	.incbin "baserom.nds", 0x1E49108, 0x2634
	.incbin "baserom.nds", 0x1E4B73C, 0x304
	.incbin "baserom.nds", 0x1E4BA40, 0x268C
	.incbin "baserom.nds", 0x1E4E0CC, 0x304
	.incbin "baserom.nds", 0x1E4E3D0, 0x2684
	.incbin "baserom.nds", 0x1E50A54, 0x7C04
	.incbin "baserom.nds", 0x1E58658, 0x14E8
	.incbin "baserom.nds", 0x1E59B40, 0x230
	.incbin "baserom.nds", 0x1E59D70, 0x228
	.incbin "baserom.nds", 0x1E59F98, 0x63
	.incbin "baserom.nds", 0x1E59FFC, 0x6F
	.incbin "baserom.nds", 0x1E5A06C, 0x2040
	.incbin "baserom.nds", 0x1E5C0AC, 0x228
	.incbin "baserom.nds", 0x1E5C2D4, 0x228
	.incbin "baserom.nds", 0x1E5C4FC, 0x228
