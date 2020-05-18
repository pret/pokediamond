	.include "asm/macros.inc"
	.include "global.inc"

	/* rom2.s TODO: Disassemble */

	.section .rodata

	/* 0x02103FE4 */

	.global UNK_02103FE4
UNK_02103FE4: ; 0x02103FE4
	.incbin "baserom.nds", 0x107fe4, 0x4

	.global UNK_02103FE8
UNK_02103FE8: ; 0x02103FE8
	.incbin "baserom.nds", 0x107fe8, 0xc

	.global UNK_02103FF4
UNK_02103FF4: ; 0x02103FF4
	.incbin "baserom.nds", 0x107ff4, 0x10

	.global UNK_02104004
UNK_02104004: ; 0x02104004
	.incbin "baserom.nds", 0x108004, 0x8

	.global UNK_0210400C
UNK_0210400C: ; 0x0210400C
	.incbin "baserom.nds", 0x10800c, 0x3c

	.global UNK_02104048
UNK_02104048: ; 0x02104048
	.incbin "baserom.nds", 0x108048, 0x3c

	.global UNK_02104084
UNK_02104084: ; 0x02104084
	.incbin "baserom.nds", 0x108084, 0x8

	.global UNK_0210408C
UNK_0210408C: ; 0x0210408C
	.incbin "baserom.nds", 0x10808c, 0x3c

	.global UNK_021040C8
UNK_021040C8: ; 0x021040C8
	.incbin "baserom.nds", 0x1080c8, 0x8

	.global UNK_021040D0
UNK_021040D0: ; 0x021040D0
	.incbin "baserom.nds", 0x1080d0, 0x3c

	.global UNK_0210410C
UNK_0210410C: ; 0x0210410C
	.incbin "baserom.nds", 0x10810c, 0x3c

	.global UNK_02104148
UNK_02104148: ; 0x02104148
	.incbin "baserom.nds", 0x108148, 0x8

	.global UNK_02104150
UNK_02104150: ; 0x02104150
	.incbin "baserom.nds", 0x108150, 0x3c

	.global UNK_0210418C
UNK_0210418C: ; 0x0210418C
	.incbin "baserom.nds", 0x10818c, 0x3c

	.global UNK_021041C8
UNK_021041C8: ; 0x021041C8
	.incbin "baserom.nds", 0x1081c8, 0x8

	.global UNK_021041D0
UNK_021041D0: ; 0x021041D0
	.incbin "baserom.nds", 0x1081d0, 0x3c

	.global UNK_0210420C
UNK_0210420C: ; 0x0210420C
	.incbin "baserom.nds", 0x10820c, 0x80

	.global UNK_0210428C
UNK_0210428C: ; 0x0210428C
	.incbin "baserom.nds", 0x10828c, 0x80

	.global UNK_0210430C
UNK_0210430C: ; 0x0210430C
	.incbin "baserom.nds", 0x10830c, 0x100

	.global UNK_0210440C
UNK_0210440C: ; 0x0210440C
	.incbin "baserom.nds", 0x10840c, 0x28

	.global UNK_02104434
UNK_02104434: ; 0x02104434
	.incbin "baserom.nds", 0x108434, 0x5

	.global UNK_02104439
UNK_02104439: ; 0x02104439
	.incbin "baserom.nds", 0x108439, 0x10b

	.global UNK_02104544
UNK_02104544: ; 0x02104544
	.incbin "baserom.nds", 0x108544, 0x200

	.global UNK_02104744
UNK_02104744: ; 0x02104744
	.incbin "baserom.nds", 0x108744, 0x10

	.global UNK_02104754
UNK_02104754: ; 0x02104754
	.incbin "baserom.nds", 0x108754, 0x10

	.global UNK_02104764
UNK_02104764: ; 0x02104764
	.incbin "baserom.nds", 0x108764, 0x10

	.section .data
	; 0x02104780
	.global UNK_02104780
UNK_02104780: ; 0x02104780
	.incbin "baserom.nds", 0x108780, 0x1c

	.global UNK_0210479C
UNK_0210479C: ; 0x0210479C
	.incbin "baserom.nds", 0x10879c, 0xc

	.global UNK_021047A8
UNK_021047A8: ; 0x021047A8
	.incbin "baserom.nds", 0x1087a8, 0x10

	.global UNK_021047B8
UNK_021047B8: ; 0x021047B8
	.incbin "baserom.nds", 0x1087b8, 0x10

	.global UNK_021047C8
UNK_021047C8: ; 0x021047C8
	.incbin "baserom.nds", 0x1087c8, 0x14

	.global UNK_021047DC
UNK_021047DC: ; 0x021047DC
	.incbin "baserom.nds", 0x1087dc, 0x14

	.global UNK_021047F0
UNK_021047F0: ; 0x021047F0
	.incbin "baserom.nds", 0x1087f0, 0x14

	.global UNK_02104804
UNK_02104804: ; 0x02104804
	.incbin "baserom.nds", 0x108804, 0x14

	.global UNK_02104818
UNK_02104818: ; 0x02104818
	.incbin "baserom.nds", 0x108818, 0x14

	.global UNK_0210482C
UNK_0210482C: ; 0x0210482C
	.incbin "baserom.nds", 0x10882c, 0x14

	.global UNK_02104840
UNK_02104840: ; 0x02104840
	.incbin "baserom.nds", 0x108840, 0x14

	.global UNK_02104854
UNK_02104854: ; 0x02104854
	.incbin "baserom.nds", 0x108854, 0x14

	.global UNK_02104868
UNK_02104868: ; 0x02104868
	.incbin "baserom.nds", 0x108868, 0x14

	.global UNK_0210487C
UNK_0210487C: ; 0x0210487C
	.incbin "baserom.nds", 0x10887c, 0x14

	.global UNK_02104890
UNK_02104890: ; 0x02104890
	.incbin "baserom.nds", 0x108890, 0x14

	.global UNK_021048A4
UNK_021048A4: ; 0x021048A4
	.incbin "baserom.nds", 0x1088a4, 0x14

	.global UNK_021048B8
UNK_021048B8: ; 0x021048B8
	.incbin "baserom.nds", 0x1088b8, 0x14

	.global UNK_021048CC
UNK_021048CC: ; 0x021048CC
	.incbin "baserom.nds", 0x1088cc, 0x14

	.global UNK_021048E0
UNK_021048E0: ; 0x021048E0
	.incbin "baserom.nds", 0x1088e0, 0x14

	.global UNK_021048F4
UNK_021048F4: ; 0x021048F4
	.incbin "baserom.nds", 0x1088f4, 0x14

	.global UNK_02104908
UNK_02104908: ; 0x02104908
	.incbin "baserom.nds", 0x108908, 0x14

	.global UNK_0210491C
UNK_0210491C: ; 0x0210491C
	.incbin "baserom.nds", 0x10891c, 0x14

	.global UNK_02104930
UNK_02104930: ; 0x02104930
	.incbin "baserom.nds", 0x108930, 0x14

	.global UNK_02104944
UNK_02104944: ; 0x02104944
	.incbin "baserom.nds", 0x108944, 0x14

	.global UNK_02104958
UNK_02104958: ; 0x02104958
	.incbin "baserom.nds", 0x108958, 0x18

	.global UNK_02104970
UNK_02104970: ; 0x02104970
	.incbin "baserom.nds", 0x108970, 0x18

	.global UNK_02104988
UNK_02104988: ; 0x02104988
	.incbin "baserom.nds", 0x108988, 0x18

	.global UNK_021049A0
UNK_021049A0: ; 0x021049A0
	.incbin "baserom.nds", 0x1089a0, 0x18

	.global UNK_021049B8
UNK_021049B8: ; 0x021049B8
	.incbin "baserom.nds", 0x1089b8, 0x18

	.global UNK_021049D0
UNK_021049D0: ; 0x021049D0
	.incbin "baserom.nds", 0x1089d0, 0x18

	.global UNK_021049E8
UNK_021049E8: ; 0x021049E8
	.incbin "baserom.nds", 0x1089e8, 0x18

	.global UNK_02104A00
UNK_02104A00: ; 0x02104A00
	.incbin "baserom.nds", 0x108a00, 0x18

	.global UNK_02104A18
UNK_02104A18: ; 0x02104A18
	.incbin "baserom.nds", 0x108a18, 0x18

	.global UNK_02104A30
UNK_02104A30: ; 0x02104A30
	.incbin "baserom.nds", 0x108a30, 0x18

	.global UNK_02104A48
UNK_02104A48: ; 0x02104A48
	.incbin "baserom.nds", 0x108a48, 0x18

	.global UNK_02104A60
UNK_02104A60: ; 0x02104A60
	.incbin "baserom.nds", 0x108a60, 0x18

	.global UNK_02104A78
UNK_02104A78: ; 0x02104A78
	.incbin "baserom.nds", 0x108a78, 0x18

	.global UNK_02104A90
UNK_02104A90: ; 0x02104A90
	.incbin "baserom.nds", 0x108a90, 0x18

	.global UNK_02104AA8
UNK_02104AA8: ; 0x02104AA8
	.incbin "baserom.nds", 0x108aa8, 0x18

	.global UNK_02104AC0
UNK_02104AC0: ; 0x02104AC0
	.incbin "baserom.nds", 0x108ac0, 0x18

	.global UNK_02104AD8
UNK_02104AD8: ; 0x02104AD8
	.incbin "baserom.nds", 0x108ad8, 0x18

	.global UNK_02104AF0
UNK_02104AF0: ; 0x02104AF0
	.incbin "baserom.nds", 0x108af0, 0x18

	.global UNK_02104B08
UNK_02104B08: ; 0x02104B08
	.incbin "baserom.nds", 0x108b08, 0x18

	.global UNK_02104B20
UNK_02104B20: ; 0x02104B20
	.incbin "baserom.nds", 0x108b20, 0x18

	.global UNK_02104B38
UNK_02104B38: ; 0x02104B38
	.incbin "baserom.nds", 0x108b38, 0x18

	.global UNK_02104B50
UNK_02104B50: ; 0x02104B50
	.incbin "baserom.nds", 0x108b50, 0x18

	.global UNK_02104B68
UNK_02104B68: ; 0x02104B68
	.incbin "baserom.nds", 0x108b68, 0x18

	.global UNK_02104B80
UNK_02104B80: ; 0x02104B80
	.incbin "baserom.nds", 0x108b80, 0x18

	.global UNK_02104B98
UNK_02104B98: ; 0x02104B98
	.incbin "baserom.nds", 0x108b98, 0x18

	.global UNK_02104BB0
UNK_02104BB0: ; 0x02104BB0
	.incbin "baserom.nds", 0x108bb0, 0x18

	.global UNK_02104BC8
UNK_02104BC8: ; 0x02104BC8
	.incbin "baserom.nds", 0x108bc8, 0x18

	.global UNK_02104BE0
UNK_02104BE0: ; 0x02104BE0
	.incbin "baserom.nds", 0x108be0, 0x18

	.global UNK_02104BF8
UNK_02104BF8: ; 0x02104BF8
	.incbin "baserom.nds", 0x108bf8, 0x18

	.global UNK_02104C10
UNK_02104C10: ; 0x02104C10
	.incbin "baserom.nds", 0x108c10, 0x18

	.global UNK_02104C28
UNK_02104C28: ; 0x02104C28
	.incbin "baserom.nds", 0x108c28, 0x18

	.global UNK_02104C40
UNK_02104C40: ; 0x02104C40
	.incbin "baserom.nds", 0x108c40, 0x18

	.global UNK_02104C58
UNK_02104C58: ; 0x02104C58
	.incbin "baserom.nds", 0x108c58, 0x18

	.global UNK_02104C70
UNK_02104C70: ; 0x02104C70
	.incbin "baserom.nds", 0x108c70, 0x18

	.global UNK_02104C88
UNK_02104C88: ; 0x02104C88
	.incbin "baserom.nds", 0x108c88, 0x18

	.global UNK_02104CA0
UNK_02104CA0: ; 0x02104CA0
	.incbin "baserom.nds", 0x108ca0, 0x18

	.global UNK_02104CB8
UNK_02104CB8: ; 0x02104CB8
	.incbin "baserom.nds", 0x108cb8, 0x18

	.global UNK_02104CD0
UNK_02104CD0: ; 0x02104CD0
	.incbin "baserom.nds", 0x108cd0, 0x18

	.global UNK_02104CE8
UNK_02104CE8: ; 0x02104CE8
	.incbin "baserom.nds", 0x108ce8, 0x18

	.global UNK_02104D00
UNK_02104D00: ; 0x02104D00
	.incbin "baserom.nds", 0x108d00, 0x18

	.global UNK_02104D18
UNK_02104D18: ; 0x02104D18
	.incbin "baserom.nds", 0x108d18, 0x1c

	.global UNK_02104D34
UNK_02104D34: ; 0x02104D34
	.incbin "baserom.nds", 0x108d34, 0x1c

	.global UNK_02104D50
UNK_02104D50: ; 0x02104D50
	.incbin "baserom.nds", 0x108d50, 0x1c

	.global UNK_02104D6C
UNK_02104D6C: ; 0x02104D6C
	.incbin "baserom.nds", 0x108d6c, 0x1c

	.global UNK_02104D88
UNK_02104D88: ; 0x02104D88
	.incbin "baserom.nds", 0x108d88, 0x1c

	.global UNK_02104DA4
UNK_02104DA4: ; 0x02104DA4
	.incbin "baserom.nds", 0x108da4, 0x1c

	.global UNK_02104DC0
UNK_02104DC0: ; 0x02104DC0
	.incbin "baserom.nds", 0x108dc0, 0x1c

	.global UNK_02104DDC
UNK_02104DDC: ; 0x02104DDC
	.incbin "baserom.nds", 0x108ddc, 0x1c

	.global UNK_02104DF8
UNK_02104DF8: ; 0x02104DF8
	.incbin "baserom.nds", 0x108df8, 0x1c

	.global UNK_02104E14
UNK_02104E14: ; 0x02104E14
	.incbin "baserom.nds", 0x108e14, 0x1c

	.global UNK_02104E30
UNK_02104E30: ; 0x02104E30
	.incbin "baserom.nds", 0x108e30, 0x1c

	.global UNK_02104E4C
UNK_02104E4C: ; 0x02104E4C
	.incbin "baserom.nds", 0x108e4c, 0x1c

	.global UNK_02104E68
UNK_02104E68: ; 0x02104E68
	.incbin "baserom.nds", 0x108e68, 0x1c

	.global UNK_02104E84
UNK_02104E84: ; 0x02104E84
	.incbin "baserom.nds", 0x108e84, 0x1c

	.global UNK_02104EA0
UNK_02104EA0: ; 0x02104EA0
	.incbin "baserom.nds", 0x108ea0, 0x1c

	.global UNK_02104EBC
UNK_02104EBC: ; 0x02104EBC
	.incbin "baserom.nds", 0x108ebc, 0x1c

	.global UNK_02104ED8
UNK_02104ED8: ; 0x02104ED8
	.incbin "baserom.nds", 0x108ed8, 0x1c

	.global UNK_02104EF4
UNK_02104EF4: ; 0x02104EF4
	.incbin "baserom.nds", 0x108ef4, 0x1c

	.global UNK_02104F10
UNK_02104F10: ; 0x02104F10
	.incbin "baserom.nds", 0x108f10, 0x1c

	.global UNK_02104F2C
UNK_02104F2C: ; 0x02104F2C
	.incbin "baserom.nds", 0x108f2c, 0x1c

	.global UNK_02104F48
UNK_02104F48: ; 0x02104F48
	.incbin "baserom.nds", 0x108f48, 0x1c

	.global UNK_02104F64
UNK_02104F64: ; 0x02104F64
	.incbin "baserom.nds", 0x108f64, 0x1c

	.global UNK_02104F80
UNK_02104F80: ; 0x02104F80
	.incbin "baserom.nds", 0x108f80, 0x20

	.global UNK_02104FA0
UNK_02104FA0: ; 0x02104FA0
	.incbin "baserom.nds", 0x108fa0, 0x20

	.global UNK_02104FC0
UNK_02104FC0: ; 0x02104FC0
	.incbin "baserom.nds", 0x108fc0, 0x20

	.global UNK_02104FE0
UNK_02104FE0: ; 0x02104FE0
	.incbin "baserom.nds", 0x108fe0, 0x20

	.global UNK_02105000
UNK_02105000: ; 0x02105000
	.incbin "baserom.nds", 0x109000, 0x20

	.global UNK_02105020
UNK_02105020: ; 0x02105020
	.incbin "baserom.nds", 0x109020, 0x20

	.global UNK_02105040
UNK_02105040: ; 0x02105040
	.incbin "baserom.nds", 0x109040, 0x20

	.global UNK_02105060
UNK_02105060: ; 0x02105060
	.incbin "baserom.nds", 0x109060, 0x20

	.global UNK_02105080
UNK_02105080: ; 0x02105080
	.incbin "baserom.nds", 0x109080, 0x20

	.global UNK_021050A0
UNK_021050A0: ; 0x021050A0
	.incbin "baserom.nds", 0x1090a0, 0x20

	.global UNK_021050C0
UNK_021050C0: ; 0x021050C0
	.incbin "baserom.nds", 0x1090c0, 0x20

	.global UNK_021050E0
UNK_021050E0: ; 0x021050E0
	.incbin "baserom.nds", 0x1090e0, 0x20

	.global UNK_02105100
UNK_02105100: ; 0x02105100
	.incbin "baserom.nds", 0x109100, 0x20

	.global UNK_02105120
UNK_02105120: ; 0x02105120
	.incbin "baserom.nds", 0x109120, 0x20

	.global UNK_02105140
UNK_02105140: ; 0x02105140
	.incbin "baserom.nds", 0x109140, 0x20

	.global UNK_02105160
UNK_02105160: ; 0x02105160
	.incbin "baserom.nds", 0x109160, 0x20

	.global UNK_02105180
UNK_02105180: ; 0x02105180
	.incbin "baserom.nds", 0x109180, 0x20

	.global UNK_021051A0
UNK_021051A0: ; 0x021051A0
	.incbin "baserom.nds", 0x1091a0, 0x20

	.global UNK_021051C0
UNK_021051C0: ; 0x021051C0
	.incbin "baserom.nds", 0x1091c0, 0x20

	.global UNK_021051E0
UNK_021051E0: ; 0x021051E0
	.incbin "baserom.nds", 0x1091e0, 0x20

	.global UNK_02105200
UNK_02105200: ; 0x02105200
	.incbin "baserom.nds", 0x109200, 0x20

	.global UNK_02105220
UNK_02105220: ; 0x02105220
	.incbin "baserom.nds", 0x109220, 0x20

	.global UNK_02105240
UNK_02105240: ; 0x02105240
	.incbin "baserom.nds", 0x109240, 0x20

	.global UNK_02105260
UNK_02105260: ; 0x02105260
	.incbin "baserom.nds", 0x109260, 0x20

	.global UNK_02105280
UNK_02105280: ; 0x02105280
	.incbin "baserom.nds", 0x109280, 0x20

	.global UNK_021052A0
UNK_021052A0: ; 0x021052A0
	.incbin "baserom.nds", 0x1092a0, 0x24

	.global UNK_021052C4
UNK_021052C4: ; 0x021052C4
	.incbin "baserom.nds", 0x1092c4, 0x24

	.global UNK_021052E8
UNK_021052E8: ; 0x021052E8
	.incbin "baserom.nds", 0x1092e8, 0x24

	.global UNK_0210530C
UNK_0210530C: ; 0x0210530C
	.incbin "baserom.nds", 0x10930c, 0x24

	.global UNK_02105330
UNK_02105330: ; 0x02105330
	.incbin "baserom.nds", 0x109330, 0x24

	.global UNK_02105354
UNK_02105354: ; 0x02105354
	.incbin "baserom.nds", 0x109354, 0x24

	.global UNK_02105378
UNK_02105378: ; 0x02105378
	.incbin "baserom.nds", 0x109378, 0x24

	.global UNK_0210539C
UNK_0210539C: ; 0x0210539C
	.incbin "baserom.nds", 0x10939c, 0x24

	.global UNK_021053C0
UNK_021053C0: ; 0x021053C0
	.incbin "baserom.nds", 0x1093c0, 0x24

	.global UNK_021053E4
UNK_021053E4: ; 0x021053E4
	.incbin "baserom.nds", 0x1093e4, 0x24

	.global UNK_02105408
UNK_02105408: ; 0x02105408
	.incbin "baserom.nds", 0x109408, 0x24

	.global UNK_0210542C
UNK_0210542C: ; 0x0210542C
	.incbin "baserom.nds", 0x10942c, 0x28

	.global UNK_02105454
UNK_02105454: ; 0x02105454
	.incbin "baserom.nds", 0x109454, 0x28

	.global UNK_0210547C
UNK_0210547C: ; 0x0210547C
	.incbin "baserom.nds", 0x10947c, 0x28

	.global UNK_021054A4
UNK_021054A4: ; 0x021054A4
	.incbin "baserom.nds", 0x1094a4, 0x28

	.global UNK_021054CC
UNK_021054CC: ; 0x021054CC
	.incbin "baserom.nds", 0x1094cc, 0x28

	.global UNK_021054F4
UNK_021054F4: ; 0x021054F4
	.incbin "baserom.nds", 0x1094f4, 0x28

	.global UNK_0210551C
UNK_0210551C: ; 0x0210551C
	.incbin "baserom.nds", 0x10951c, 0x28

	.global UNK_02105544
UNK_02105544: ; 0x02105544
	.incbin "baserom.nds", 0x109544, 0x28

	.global UNK_0210556C
UNK_0210556C: ; 0x0210556C
	.incbin "baserom.nds", 0x10956c, 0x28

	.global UNK_02105594
UNK_02105594: ; 0x02105594
	.incbin "baserom.nds", 0x109594, 0x28

	.global UNK_021055BC
UNK_021055BC: ; 0x021055BC
	.incbin "baserom.nds", 0x1095bc, 0x2c

	.global UNK_021055E8
UNK_021055E8: ; 0x021055E8
	.incbin "baserom.nds", 0x1095e8, 0x2c

	.global UNK_02105614
UNK_02105614: ; 0x02105614
	.incbin "baserom.nds", 0x109614, 0x2c

	.global UNK_02105640
UNK_02105640: ; 0x02105640
	.incbin "baserom.nds", 0x109640, 0x2c

	.global UNK_0210566C
UNK_0210566C: ; 0x0210566C
	.incbin "baserom.nds", 0x10966c, 0x2c

	.global UNK_02105698
UNK_02105698: ; 0x02105698
	.incbin "baserom.nds", 0x109698, 0x30

	.global UNK_021056C8
UNK_021056C8: ; 0x021056C8
	.incbin "baserom.nds", 0x1096c8, 0x30

	.global UNK_021056F8
UNK_021056F8: ; 0x021056F8
	.incbin "baserom.nds", 0x1096f8, 0x30

	.global UNK_02105728
UNK_02105728: ; 0x02105728
	.incbin "baserom.nds", 0x109728, 0x34

	.global UNK_0210575C
UNK_0210575C: ; 0x0210575C
	.incbin "baserom.nds", 0x10975c, 0x34

	.global UNK_02105790
UNK_02105790: ; 0x02105790
	.incbin "baserom.nds", 0x109790, 0x34

	.global UNK_021057C4
UNK_021057C4: ; 0x021057C4
	.incbin "baserom.nds", 0x1097c4, 0x34

	.global UNK_021057F8
UNK_021057F8: ; 0x021057F8
	.incbin "baserom.nds", 0x1097f8, 0x38

	.global UNK_02105830
UNK_02105830: ; 0x02105830
	.incbin "baserom.nds", 0x109830, 0x38

	.global UNK_02105868
UNK_02105868: ; 0x02105868
	.incbin "baserom.nds", 0x109868, 0x38

	.global UNK_021058A0
UNK_021058A0: ; 0x021058A0
	.incbin "baserom.nds", 0x1098a0, 0x248

	.global UNK_02105AE8
UNK_02105AE8: ; 0x02105AE8
	.incbin "baserom.nds", 0x109ae8, 0x10

	.global UNK_02105AF8
UNK_02105AF8: ; 0x02105AF8
	.incbin "baserom.nds", 0x109af8, 0x8

	.global UNK_02105B00
UNK_02105B00: ; 0x02105B00
	.incbin "baserom.nds", 0x109b00, 0x8

	.global UNK_02105B08
UNK_02105B08: ; 0x02105B08
	.incbin "baserom.nds", 0x109b08, 0x8

	.global UNK_02105B10
UNK_02105B10: ; 0x02105B10
	.incbin "baserom.nds", 0x109b10, 0x8

	.global UNK_02105B18
UNK_02105B18: ; 0x02105B18
	.incbin "baserom.nds", 0x109b18, 0x8

	.global UNK_02105B20
UNK_02105B20: ; 0x02105B20
	.incbin "baserom.nds", 0x109b20, 0x8

	.global UNK_02105B28
UNK_02105B28: ; 0x02105B28
	.incbin "baserom.nds", 0x109b28, 0x8

	.global UNK_02105B30
UNK_02105B30: ; 0x02105B30
	.incbin "baserom.nds", 0x109b30, 0x8

	.global UNK_02105B38
UNK_02105B38: ; 0x02105B38
	.incbin "baserom.nds", 0x109b38, 0x8

	.global UNK_02105B40
UNK_02105B40: ; 0x02105B40
	.incbin "baserom.nds", 0x109b40, 0x8

	.global UNK_02105B48
UNK_02105B48: ; 0x02105B48
	.incbin "baserom.nds", 0x109b48, 0x30

	.global UNK_02105B78
UNK_02105B78: ; 0x02105B78
	.incbin "baserom.nds", 0x109b78, 0x30

	.global UNK_02105BA8
UNK_02105BA8: ; 0x02105BA8
	.incbin "baserom.nds", 0x109ba8, 0x4

	.global UNK_02105BAC
UNK_02105BAC: ; 0x02105BAC
	.incbin "baserom.nds", 0x109bac, 0x8

	.global UNK_02105BB4
UNK_02105BB4: ; 0x02105BB4
	.incbin "baserom.nds", 0x109bb4, 0x4

	.global UNK_02105BB8
UNK_02105BB8: ; 0x02105BB8
	.incbin "baserom.nds", 0x109bb8, 0x4

	.global UNK_02105BBC
UNK_02105BBC: ; 0x02105BBC
	.incbin "baserom.nds", 0x109bbc, 0x18

	.global UNK_02105BD4
UNK_02105BD4: ; 0x02105BD4
	.incbin "baserom.nds", 0x109bd4, 0xa0

	.global UNK_02105C74
UNK_02105C74: ; 0x02105C74
	.incbin "baserom.nds", 0x109c74, 0x64

	.global UNK_02105CD8
UNK_02105CD8: ; 0x02105CD8
	.incbin "baserom.nds", 0x109cd8, 0x7c

	.global UNK_02105D54
UNK_02105D54: ; 0x02105D54
	.incbin "baserom.nds", 0x109d54, 0x4

	.global UNK_02105D58
UNK_02105D58: ; 0x02105D58
	.incbin "baserom.nds", 0x109d58, 0x4

	.global UNK_02105D5C
UNK_02105D5C: ; 0x02105D5C
	.incbin "baserom.nds", 0x109d5c, 0x8

	.global UNK_02105D64
UNK_02105D64: ; 0x02105D64
	.incbin "baserom.nds", 0x109d64, 0x1

	.global UNK_02105D65
UNK_02105D65: ; 0x02105D65
	.incbin "baserom.nds", 0x109d65, 0x7

	.global UNK_02105D6C
UNK_02105D6C: ; 0x02105D6C
	.incbin "baserom.nds", 0x109d6c, 0x1

	.global UNK_02105D6D
UNK_02105D6D: ; 0x02105D6D
	.incbin "baserom.nds", 0x109d6d, 0x7

	.global UNK_02105D74
UNK_02105D74: ; 0x02105D74
	.incbin "baserom.nds", 0x109d74, 0x14

	.global UNK_02105D88
UNK_02105D88: ; 0x02105D88
	.incbin "baserom.nds", 0x109d88, 0x10

	.global UNK_02105D98
UNK_02105D98: ; 0x02105D98
	.incbin "baserom.nds", 0x109d98, 0x10

	.global UNK_02105DA8
UNK_02105DA8: ; 0x02105DA8
	.incbin "baserom.nds", 0x109da8, 0x10

	.global UNK_02105DB8
UNK_02105DB8: ; 0x02105DB8
	.incbin "baserom.nds", 0x109db8, 0x4

	.global UNK_02105DBC
UNK_02105DBC: ; 0x02105DBC
	.incbin "baserom.nds", 0x109dbc, 0x10

	.global UNK_02105DCC
UNK_02105DCC: ; 0x02105DCC
	.incbin "baserom.nds", 0x109dcc, 0x10

	.global UNK_02105DDC
UNK_02105DDC: ; 0x02105DDC
	.incbin "baserom.nds", 0x109ddc, 0x10

	.global UNK_02105DEC
UNK_02105DEC: ; 0x02105DEC
	.incbin "baserom.nds", 0x109dec, 0x8

	.global UNK_02105DF4
UNK_02105DF4: ; 0x02105DF4
	.incbin "baserom.nds", 0x109df4, 0x1c

	.global UNK_02105E10
UNK_02105E10: ; 0x02105E10
	.incbin "baserom.nds", 0x109e10, 0x4c

	.global UNK_02105E5C
UNK_02105E5C: ; 0x02105E5C
	.incbin "baserom.nds", 0x109e5c, 0x8

	.global UNK_02105E64
UNK_02105E64: ; 0x02105E64
	.incbin "baserom.nds", 0x109e64, 0x10

	.global UNK_02105E74
UNK_02105E74: ; 0x02105E74
	.incbin "baserom.nds", 0x109e74, 0xc

	.global UNK_02105E80
UNK_02105E80: ; 0x02105E80
	.incbin "baserom.nds", 0x109e80, 0x14

	.global UNK_02105E94
UNK_02105E94: ; 0x02105E94
	.incbin "baserom.nds", 0x109e94, 0x1c

	.global UNK_02105EB0
UNK_02105EB0: ; 0x02105EB0
	.incbin "baserom.nds", 0x109eb0, 0x18

	.global UNK_02105EC8
UNK_02105EC8: ; 0x02105EC8
	.incbin "baserom.nds", 0x109ec8, 0x8

	.global UNK_02105ED0
UNK_02105ED0: ; 0x02105ED0
	.incbin "baserom.nds", 0x109ed0, 0x8

	.global UNK_02105ED8
UNK_02105ED8: ; 0x02105ED8
	.incbin "baserom.nds", 0x109ed8, 0x1c

	.global UNK_02105EF4
UNK_02105EF4: ; 0x02105EF4
	.incbin "baserom.nds", 0x109ef4, 0x1c

	.global UNK_02105F10
UNK_02105F10: ; 0x02105F10
	.incbin "baserom.nds", 0x109f10, 0x1c

	.global UNK_02105F2C
UNK_02105F2C: ; 0x02105F2C
	.incbin "baserom.nds", 0x109f2c, 0x1c

	.global UNK_02105F48
UNK_02105F48: ; 0x02105F48
	.incbin "baserom.nds", 0x109f48, 0x1c

	.global UNK_02105F64
UNK_02105F64: ; 0x02105F64
	.incbin "baserom.nds", 0x109f64, 0x1c

	.global UNK_02105F80
UNK_02105F80: ; 0x02105F80
	.incbin "baserom.nds", 0x109f80, 0x1c

	.global UNK_02105F9C
UNK_02105F9C: ; 0x02105F9C
	.incbin "baserom.nds", 0x109f9c, 0xc

	.global UNK_02105FA8
UNK_02105FA8: ; 0x02105FA8
	.incbin "baserom.nds", 0x109fa8, 0x14

	.global UNK_02105FBC
UNK_02105FBC: ; 0x02105FBC
	.incbin "baserom.nds", 0x109fbc, 0xc

	.global UNK_02105FC8
UNK_02105FC8: ; 0x02105FC8
	.incbin "baserom.nds", 0x109fc8, 0x1c

	.global UNK_02105FE4
UNK_02105FE4: ; 0x02105FE4
	.incbin "baserom.nds", 0x109fe4, 0x14

	.global UNK_02105FF8
UNK_02105FF8: ; 0x02105FF8
	.incbin "baserom.nds", 0x109ff8, 0x18

	.global UNK_02106010
UNK_02106010: ; 0x02106010
	.incbin "baserom.nds", 0x10a010, 0x18

	.global UNK_02106028
UNK_02106028: ; 0x02106028
	.incbin "baserom.nds", 0x10a028, 0x18

	.global UNK_02106040
UNK_02106040: ; 0x02106040
	.incbin "baserom.nds", 0x10a040, 0x18

	.global UNK_02106058
UNK_02106058: ; 0x02106058
	.incbin "baserom.nds", 0x10a058, 0x14

	.global UNK_0210606C
UNK_0210606C: ; 0x0210606C
	.incbin "baserom.nds", 0x10a06c, 0x64

	.global UNK_021060D0
UNK_021060D0: ; 0x021060D0
	.incbin "baserom.nds", 0x10a0d0, 0x14

	.global UNK_021060E4
UNK_021060E4: ; 0x021060E4
	.incbin "baserom.nds", 0x10a0e4, 0x14

	.global UNK_021060F8
UNK_021060F8: ; 0x021060F8
	.incbin "baserom.nds", 0x10a0f8, 0x14

	.global UNK_0210610C
UNK_0210610C: ; 0x0210610C
	.incbin "baserom.nds", 0x10a10c, 0x18

	.global UNK_02106124
UNK_02106124: ; 0x02106124
	.incbin "baserom.nds", 0x10a124, 0x18

	.global UNK_0210613C
UNK_0210613C: ; 0x0210613C
	.incbin "baserom.nds", 0x10a13c, 0xc

	.global UNK_02106148
UNK_02106148: ; 0x02106148
	.incbin "baserom.nds", 0x10a148, 0xc

	.global UNK_02106154
UNK_02106154: ; 0x02106154
	.incbin "baserom.nds", 0x10a154, 0x4

	.global UNK_02106158
UNK_02106158: ; 0x02106158
	.incbin "baserom.nds", 0x10a158, 0x8

	.global UNK_02106160
UNK_02106160: ; 0x02106160
	.incbin "baserom.nds", 0x10a160, 0x8

	.global UNK_02106168
UNK_02106168: ; 0x02106168
	.incbin "baserom.nds", 0x10a168, 0x8

	.global UNK_02106170
UNK_02106170: ; 0x02106170
	.incbin "baserom.nds", 0x10a170, 0x1c

	.global UNK_0210618C
UNK_0210618C: ; 0x0210618C
	.incbin "baserom.nds", 0x10a18c, 0x10

	.global UNK_0210619C
UNK_0210619C: ; 0x0210619C
	.incbin "baserom.nds", 0x10a19c, 0x24

	.global UNK_021061C0
UNK_021061C0: ; 0x021061C0
	.incbin "baserom.nds", 0x10a1c0, 0x4

	.global UNK_021061C4
UNK_021061C4: ; 0x021061C4
	.incbin "baserom.nds", 0x10a1c4, 0x18

	.global UNK_021061DC
UNK_021061DC: ; 0x021061DC
	.incbin "baserom.nds", 0x10a1dc, 0x18

	.global UNK_021061F4
UNK_021061F4: ; 0x021061F4
	.incbin "baserom.nds", 0x10a1f4, 0x18

	.global UNK_0210620C
UNK_0210620C: ; 0x0210620C
	.incbin "baserom.nds", 0x10a20c, 0xc

	.global UNK_02106218
UNK_02106218: ; 0x02106218
	.incbin "baserom.nds", 0x10a218, 0x4

	.global UNK_0210621C
UNK_0210621C: ; 0x0210621C
	.incbin "baserom.nds", 0x10a21c, 0x8

	.global UNK_02106224
UNK_02106224: ; 0x02106224
	.incbin "baserom.nds", 0x10a224, 0xc

	.global UNK_02106230
UNK_02106230: ; 0x02106230
	.incbin "baserom.nds", 0x10a230, 0xc

	.global UNK_0210623C
UNK_0210623C: ; 0x0210623C
	.incbin "baserom.nds", 0x10a23c, 0x4

	.global UNK_02106240
UNK_02106240: ; 0x02106240
	.incbin "baserom.nds", 0x10a240, 0x4

	.global UNK_02106244
UNK_02106244: ; 0x02106244
	.incbin "baserom.nds", 0x10a244, 0x4

	.global UNK_02106248
UNK_02106248: ; 0x02106248
	.incbin "baserom.nds", 0x10a248, 0x4

	.global UNK_0210624C
UNK_0210624C: ; 0x0210624C
	.incbin "baserom.nds", 0x10a24c, 0x8

	.global UNK_02106254
UNK_02106254: ; 0x02106254
	.incbin "baserom.nds", 0x10a254, 0xc

	.global UNK_02106260
UNK_02106260: ; 0x02106260
	.incbin "baserom.nds", 0x10a260, 0xc

	.global UNK_0210626C
UNK_0210626C: ; 0x0210626C
	.incbin "baserom.nds", 0x10a26c, 0xc

	.global UNK_02106278
UNK_02106278: ; 0x02106278
	.incbin "baserom.nds", 0x10a278, 0x18

	.global UNK_02106290
UNK_02106290: ; 0x02106290
	.incbin "baserom.nds", 0x10a290, 0x8

	.global UNK_02106298
UNK_02106298: ; 0x02106298
	.incbin "baserom.nds", 0x10a298, 0x8

	.global UNK_021062A0
UNK_021062A0: ; 0x021062A0
	.incbin "baserom.nds", 0x10a2a0, 0x4

	.global UNK_021062A4
UNK_021062A4: ; 0x021062A4
	.incbin "baserom.nds", 0x10a2a4, 0x4

	.global UNK_021062A8
UNK_021062A8: ; 0x021062A8
	.incbin "baserom.nds", 0x10a2a8, 0x4

	.global UNK_021062AC
UNK_021062AC: ; 0x021062AC
	.incbin "baserom.nds", 0x10a2ac, 0x40

	.global UNK_021062EC
UNK_021062EC: ; 0x021062EC
	.incbin "baserom.nds", 0x10a2ec, 0x40

	.global UNK_0210632C
UNK_0210632C: ; 0x0210632C
	.incbin "baserom.nds", 0x10a32c, 0x100

	.global UNK_0210642C
UNK_0210642C: ; 0x0210642C
	.incbin "baserom.nds", 0x10a42c, 0x1

	.global UNK_0210642D
UNK_0210642D: ; 0x0210642D
	.incbin "baserom.nds", 0x10a42d, 0x3f

	.global UNK_0210646C
UNK_0210646C: ; 0x0210646C
	.incbin "baserom.nds", 0x10a46c, 0x4

	.global UNK_02106470
UNK_02106470: ; 0x02106470
	.incbin "baserom.nds", 0x10a470, 0x20

	.global UNK_02106490
UNK_02106490: ; 0x02106490
	.incbin "baserom.nds", 0x10a490, 0x8

	.global UNK_02106498
UNK_02106498: ; 0x02106498
	.incbin "baserom.nds", 0x10a498, 0x10

	.global UNK_021064A8
UNK_021064A8: ; 0x021064A8
	.incbin "baserom.nds", 0x10a4a8, 0x10

	.global UNK_021064B8
UNK_021064B8: ; 0x021064B8
	.incbin "baserom.nds", 0x10a4b8, 0x4

	.global UNK_021064BC
UNK_021064BC: ; 0x021064BC
	.incbin "baserom.nds", 0x10a4bc, 0x4

	.global UNK_021064C0
UNK_021064C0: ; 0x021064C0
	.incbin "baserom.nds", 0x10a4c0, 0x4

	.global UNK_021064C4
UNK_021064C4: ; 0x021064C4
	.incbin "baserom.nds", 0x10a4c4, 0x4

	.global UNK_021064C8
UNK_021064C8: ; 0x021064C8
	.incbin "baserom.nds", 0x10a4c8, 0x8

	.global UNK_021064D0
UNK_021064D0: ; 0x021064D0
	.incbin "baserom.nds", 0x10a4d0, 0x14

	.global UNK_021064E4
UNK_021064E4: ; 0x021064E4
	.incbin "baserom.nds", 0x10a4e4, 0x18

	.global UNK_021064FC
UNK_021064FC: ; 0x021064FC
	.incbin "baserom.nds", 0x10a4fc, 0x18

	.global UNK_02106514
UNK_02106514: ; 0x02106514
	.incbin "baserom.nds", 0x10a514, 0x18

	.global UNK_0210652C
UNK_0210652C: ; 0x0210652C
	.incbin "baserom.nds", 0x10a52c, 0x18

	.global UNK_02106544
UNK_02106544: ; 0x02106544
	.incbin "baserom.nds", 0x10a544, 0x18

	.global UNK_0210655C
UNK_0210655C: ; 0x0210655C
	.incbin "baserom.nds", 0x10a55c, 0x14

	.global UNK_02106570
UNK_02106570: ; 0x02106570
	.incbin "baserom.nds", 0x10a570, 0x4

	.global UNK_02106574
UNK_02106574: ; 0x02106574
	.incbin "baserom.nds", 0x10a574, 0x4

	.global UNK_02106578
UNK_02106578: ; 0x02106578
	.incbin "baserom.nds", 0x10a578, 0x18

	.global UNK_02106590
UNK_02106590: ; 0x02106590
	.incbin "baserom.nds", 0x10a590, 0x4

	.global UNK_02106594
UNK_02106594: ; 0x02106594
	.incbin "baserom.nds", 0x10a594, 0x4

	.global UNK_02106598
UNK_02106598: ; 0x02106598
	.incbin "baserom.nds", 0x10a598, 0x4

	.global UNK_0210659C
UNK_0210659C: ; 0x0210659C
	.incbin "baserom.nds", 0x10a59c, 0x4

	.global UNK_021065A0
UNK_021065A0: ; 0x021065A0
	.incbin "baserom.nds", 0x10a5a0, 0x4

	.global UNK_021065A4
UNK_021065A4: ; 0x021065A4
	.incbin "baserom.nds", 0x10a5a4, 0x4

	.global UNK_021065A8
UNK_021065A8: ; 0x021065A8
	.incbin "baserom.nds", 0x10a5a8, 0x4

	.global UNK_021065AC
UNK_021065AC: ; 0x021065AC
	.incbin "baserom.nds", 0x10a5ac, 0x4

	.global UNK_021065B0
UNK_021065B0: ; 0x021065B0
	.incbin "baserom.nds", 0x10a5b0, 0x4

	.global UNK_021065B4
UNK_021065B4: ; 0x021065B4
	.incbin "baserom.nds", 0x10a5b4, 0x4

	.global UNK_021065B8
UNK_021065B8: ; 0x021065B8
	.incbin "baserom.nds", 0x10a5b8, 0x4

	.global UNK_021065BC
UNK_021065BC: ; 0x021065BC
	.incbin "baserom.nds", 0x10a5bc, 0x4c

	.global UNK_02106608
UNK_02106608: ; 0x02106608
	.incbin "baserom.nds", 0x10a608, 0xc

	.global UNK_02106614
UNK_02106614: ; 0x02106614
	.incbin "baserom.nds", 0x10a614, 0xc

	.global UNK_02106620
UNK_02106620: ; 0x02106620
	.incbin "baserom.nds", 0x10a620, 0x10

	.global UNK_02106630
UNK_02106630: ; 0x02106630
	.incbin "baserom.nds", 0x10a630, 0x4

	.global UNK_02106634
UNK_02106634: ; 0x02106634
	.incbin "baserom.nds", 0x10a634, 0x4

	.global UNK_02106638
UNK_02106638: ; 0x02106638
	.incbin "baserom.nds", 0x10a638, 0x4

	.global UNK_0210663C
UNK_0210663C: ; 0x0210663C
	.incbin "baserom.nds", 0x10a63c, 0x4

	.global UNK_02106640
UNK_02106640: ; 0x02106640
	.incbin "baserom.nds", 0x10a640, 0x10

	.global UNK_02106650
UNK_02106650: ; 0x02106650
	.incbin "baserom.nds", 0x10a650, 0x10

	.global UNK_02106660
UNK_02106660: ; 0x02106660
	.incbin "baserom.nds", 0x10a660, 0x40

	.global UNK_021066A0
UNK_021066A0: ; 0x021066A0
	.incbin "baserom.nds", 0x10a6a0, 0x4

	.global UNK_021066A4
UNK_021066A4: ; 0x021066A4
	.incbin "baserom.nds", 0x10a6a4, 0x8

	.global UNK_021066AC
UNK_021066AC: ; 0x021066AC
	.incbin "baserom.nds", 0x10a6ac, 0x24

	.global UNK_021066D0
UNK_021066D0: ; 0x021066D0
	.incbin "baserom.nds", 0x10a6d0, 0xc

	.global UNK_021066DC
UNK_021066DC: ; 0x021066DC
	.incbin "baserom.nds", 0x10a6dc, 0xc

	.global UNK_021066E8
UNK_021066E8: ; 0x021066E8
	.incbin "baserom.nds", 0x10a6e8, 0x4

	.global UNK_021066EC
UNK_021066EC: ; 0x021066EC
	.incbin "baserom.nds", 0x10a6ec, 0x8

	.global UNK_021066F4
UNK_021066F4: ; 0x021066F4
	.incbin "baserom.nds", 0x10a6f4, 0x24

	.global UNK_02106718
UNK_02106718: ; 0x02106718
	.incbin "baserom.nds", 0x10a718, 0xc

	.global UNK_02106724
UNK_02106724: ; 0x02106724
	.incbin "baserom.nds", 0x10a724, 0xc

	.global UNK_02106730
UNK_02106730: ; 0x02106730
	.incbin "baserom.nds", 0x10a730, 0x80

	.global UNK_021067B0
UNK_021067B0: ; 0x021067B0
	.incbin "baserom.nds", 0x10a7b0, 0x20

	.global UNK_021067D0
UNK_021067D0: ; 0x021067D0
	.incbin "baserom.nds", 0x10a7d0, 0x20

	.global UNK_021067F0
UNK_021067F0: ; 0x021067F0
	.incbin "baserom.nds", 0x10a7f0, 0x20

	.global sIsDispOn
sIsDispOn: ; 0x02106810
	.incbin "baserom.nds", 0x10a810, 0x4

	.global GXi_DmaId
GXi_DmaId: ; 0x02106814
	.incbin "baserom.nds", 0x10a814, 0x4

	.global OSi_IrqCallbackInfoIndex
OSi_IrqCallbackInfoIndex: ; 0x02106818
	.incbin "baserom.nds", 0x10A818, 0x10
	.global OSi_ConsoleTypeCache
OSi_ConsoleTypeCache: ; 0x02106828
	.incbin "baserom.nds", 0x10A828, 0x4
