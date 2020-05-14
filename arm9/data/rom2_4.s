	.include "asm/macros.inc"
	.include "global.inc"

	/* rom2.s TODO: Disassemble */

	.section .data

	/* 0x0210683C */
	.global Unk_0210683C
Unk_0210683C: ; 0x0210683C
	.incbin "baserom.nds", 0x10A83C, 0x4

	.global Unk_02106840
Unk_02106840: ; 0x02106840
	.incbin "baserom.nds", 0x10A840, 0xC0

	.global Unk_02106900
Unk_02106900: ; 0x02106900
	.incbin "baserom.nds", 0x10A900, 0x100

	.global Unk_02106A00
Unk_02106A00: ; 0x02106A00
	.incbin "baserom.nds", 0x10AA00, 0x4

	.global Unk_02106A04
Unk_02106A04: ; 0x02106A04
	.incbin "baserom.nds", 0x10aa04, 0x18

	.global UNK_02106A1C
UNK_02106A1C: ; 0x02106A1C
	.incbin "baserom.nds", 0x10aa1c, 0x4

	.global UNK_02106A20
UNK_02106A20: ; 0x02106A20
	.incbin "baserom.nds", 0x10aa20, 0x30

	.global UNK_02106A50
UNK_02106A50: ; 0x02106A50
	.incbin "baserom.nds", 0x10aa50, 0x4

	.global UNK_02106A54
UNK_02106A54: ; 0x02106A54
	.incbin "baserom.nds", 0x10aa54, 0x4

	.global UNK_02106A58
UNK_02106A58: ; 0x02106A58
	.incbin "baserom.nds", 0x10aa58, 0x4c

	.global UNK_02106AA4
UNK_02106AA4: ; 0x02106AA4
	.incbin "baserom.nds", 0x10aaa4, 0x4c

	.global UNK_02106AF0
UNK_02106AF0: ; 0x02106AF0
	.incbin "baserom.nds", 0x10aaf0, 0x4c

	.global UNK_02106B3C
UNK_02106B3C: ; 0x02106B3C
	.incbin "baserom.nds", 0x10ab3c, 0x38

	.global UNK_02106B74
UNK_02106B74: ; 0x02106B74
	.incbin "baserom.nds", 0x10ab74, 0x4

	.global UNK_02106B78
UNK_02106B78: ; 0x02106B78
	.incbin "baserom.nds", 0x10ab78, 0x4

	.global UNK_02106B7C
UNK_02106B7C: ; 0x02106B7C
	.incbin "baserom.nds", 0x10ab7c, 0x8

	.global UNK_02106B84
UNK_02106B84: ; 0x02106B84
	.incbin "baserom.nds", 0x10ab84, 0x4

	.global UNK_02106B88
UNK_02106B88: ; 0x02106B88
	.incbin "baserom.nds", 0x10ab88, 0x4

	.global UNK_02106B8C
UNK_02106B8C: ; 0x02106B8C
	.incbin "baserom.nds", 0x10ab8c, 0x8

	.global UNK_02106B94
UNK_02106B94: ; 0x02106B94
	.incbin "baserom.nds", 0x10ab94, 0x8

	.global UNK_02106B9C
UNK_02106B9C: ; 0x02106B9C
	.incbin "baserom.nds", 0x10ab9c, 0x10

	.global UNK_02106BAC
UNK_02106BAC: ; 0x02106BAC
	.incbin "baserom.nds", 0x10abac, 0x20

	.global UNK_02106BCC
UNK_02106BCC: ; 0x02106BCC
	.incbin "baserom.nds", 0x10abcc, 0xc0

	.global UNK_02106C8C
UNK_02106C8C: ; 0x02106C8C
	.incbin "baserom.nds", 0x10ac8c, 0xc

	.global UNK_02106C98
UNK_02106C98: ; 0x02106C98
	.incbin "baserom.nds", 0x10ac98, 0xc

	.global UNK_02106CA4
UNK_02106CA4: ; 0x02106CA4
	.incbin "baserom.nds", 0x10aca4, 0xc

	.global UNK_02106CB0
UNK_02106CB0: ; 0x02106CB0
	.incbin "baserom.nds", 0x10acb0, 0x10

	.global UNK_02106CC0
UNK_02106CC0: ; 0x02106CC0
	.incbin "baserom.nds", 0x10acc0, 0x58

	.global UNK_02106D18
UNK_02106D18: ; 0x02106D18
	.incbin "baserom.nds", 0x10ad18, 0x88

	.global UNK_02106DA0
UNK_02106DA0: ; 0x02106DA0
	.incbin "baserom.nds", 0x10ada0, 0x8

	.global UNK_02106DA8
UNK_02106DA8: ; 0x02106DA8
	.incbin "baserom.nds", 0x10ada8, 0x8

	.global UNK_02106DB0
UNK_02106DB0: ; 0x02106DB0
	.incbin "baserom.nds", 0x10adb0, 0x8

	.global UNK_02106DB8
UNK_02106DB8: ; 0x02106DB8
	.incbin "baserom.nds", 0x10adb8, 0x4

	.global UNK_02106DBC
UNK_02106DBC: ; 0x02106DBC
	.incbin "baserom.nds", 0x10adbc, 0x4

	.global UNK_02106DC0
UNK_02106DC0: ; 0x02106DC0
	.incbin "baserom.nds", 0x10adc0, 0x8

	.global UNK_02106DC8
UNK_02106DC8: ; 0x02106DC8
	.incbin "baserom.nds", 0x10adc8, 0x8

	.global UNK_02106DD0
UNK_02106DD0: ; 0x02106DD0
	.incbin "baserom.nds", 0x10add0, 0x4

	.global UNK_02106DD4
UNK_02106DD4: ; 0x02106DD4
	.incbin "baserom.nds", 0x10add4, 0x4

	.global UNK_02106DD8
UNK_02106DD8: ; 0x02106DD8
	.incbin "baserom.nds", 0x10add8, 0x4

	.global UNK_02106DDC
UNK_02106DDC: ; 0x02106DDC
	.incbin "baserom.nds", 0x10addc, 0x4

	.global UNK_02106DE0
UNK_02106DE0: ; 0x02106DE0
	.incbin "baserom.nds", 0x10ade0, 0x4

	.global UNK_02106DE4
UNK_02106DE4: ; 0x02106DE4
	.incbin "baserom.nds", 0x10ade4, 0xc

	.global UNK_02106DF0
UNK_02106DF0: ; 0x02106DF0
	.incbin "baserom.nds", 0x10adf0, 0xc

	.global UNK_02106DFC
UNK_02106DFC: ; 0x02106DFC
	.incbin "baserom.nds", 0x10adfc, 0xc

	.global UNK_02106E08
UNK_02106E08: ; 0x02106E08
	.incbin "baserom.nds", 0x10ae08, 0x8

	.global UNK_02106E10
UNK_02106E10: ; 0x02106E10
	.incbin "baserom.nds", 0x10ae10, 0x8

	.global UNK_02106E18
UNK_02106E18: ; 0x02106E18
	.incbin "baserom.nds", 0x10ae18, 0xc

	.global UNK_02106E24
UNK_02106E24: ; 0x02106E24
	.incbin "baserom.nds", 0x10ae24, 0xc

	.global UNK_02106E30
UNK_02106E30: ; 0x02106E30
	.incbin "baserom.nds", 0x10ae30, 0x8

	.global UNK_02106E38
UNK_02106E38: ; 0x02106E38
	.incbin "baserom.nds", 0x10ae38, 0x8

	.global UNK_02106E40
UNK_02106E40: ; 0x02106E40
	.incbin "baserom.nds", 0x10ae40, 0x4

	.global UNK_02106E44
UNK_02106E44: ; 0x02106E44
	.incbin "baserom.nds", 0x10ae44, 0x4

	.global UNK_02106E48
UNK_02106E48: ; 0x02106E48
	.incbin "baserom.nds", 0x10ae48, 0x40

	.global UNK_02106E88
UNK_02106E88: ; 0x02106E88
	.incbin "baserom.nds", 0x10ae88, 0x30

	.global UNK_02106EB8
UNK_02106EB8: ; 0x02106EB8
	.incbin "baserom.nds", 0x10aeb8, 0x28

	.global UNK_02106EE0
UNK_02106EE0: ; 0x02106EE0
	.incbin "baserom.nds", 0x10aee0, 0x18

	.global UNK_02106EF8
UNK_02106EF8: ; 0x02106EF8
	.incbin "baserom.nds", 0x10aef8, 0x10

	.global UNK_02106F08
UNK_02106F08: ; 0x02106F08
	.incbin "baserom.nds", 0x10af08, 0x8

	.global UNK_02106F10
UNK_02106F10: ; 0x02106F10
	.incbin "baserom.nds", 0x10af10, 0x8

	.global UNK_02106F18
UNK_02106F18: ; 0x02106F18
	.incbin "baserom.nds", 0x10af18, 0x8

	.global UNK_02106F20
UNK_02106F20: ; 0x02106F20
	.incbin "baserom.nds", 0x10af20, 0x8

	.global UNK_02106F28
UNK_02106F28: ; 0x02106F28
	.incbin "baserom.nds", 0x10af28, 0x4

	.global UNK_02106F2C
UNK_02106F2C: ; 0x02106F2C
	.incbin "baserom.nds", 0x10af2c, 0x4

	.global UNK_02106F30
UNK_02106F30: ; 0x02106F30
	.incbin "baserom.nds", 0x10af30, 0x4

	.global UNK_02106F34
UNK_02106F34: ; 0x02106F34
	.incbin "baserom.nds", 0x10af34, 0x4

	.global UNK_02106F38
UNK_02106F38: ; 0x02106F38
	.incbin "baserom.nds", 0x10af38, 0x4

	.global UNK_02106F3C
UNK_02106F3C: ; 0x02106F3C
	.incbin "baserom.nds", 0x10af3c, 0x4

	.global UNK_02106F40
UNK_02106F40: ; 0x02106F40
	.incbin "baserom.nds", 0x10af40, 0x4

	.global UNK_02106F44
UNK_02106F44: ; 0x02106F44
	.incbin "baserom.nds", 0x10af44, 0x4

	.global UNK_02106F48
UNK_02106F48: ; 0x02106F48
	.incbin "baserom.nds", 0x10af48, 0x4

	.global UNK_02106F4C
UNK_02106F4C: ; 0x02106F4C
	.incbin "baserom.nds", 0x10af4c, 0x4

	.global UNK_02106F50
UNK_02106F50: ; 0x02106F50
	.incbin "baserom.nds", 0x10af50, 0x4

	.global UNK_02106F54
UNK_02106F54: ; 0x02106F54
	.incbin "baserom.nds", 0x10af54, 0x4

	.global UNK_02106F58
UNK_02106F58: ; 0x02106F58
	.incbin "baserom.nds", 0x10af58, 0x4

	.global UNK_02106F5C
UNK_02106F5C: ; 0x02106F5C
	.incbin "baserom.nds", 0x10af5c, 0x28

	.global SDK_OVERLAY_DIGEST
SDK_OVERLAY_DIGEST: ; 0x02106F84
	.global SDK_OVERLAY_DIGEST_END
SDK_OVERLAY_DIGEST_END:
	.incbin "baserom.nds", 0x10af84, 0x1C
