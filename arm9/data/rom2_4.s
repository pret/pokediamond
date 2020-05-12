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
	.incbin "baserom.nds", 0x10AA04, 0x580

	.global SDK_OVERLAY_DIGEST
SDK_OVERLAY_DIGEST: ; 0x02106F84
	.global SDK_OVERLAY_DIGEST_END
SDK_OVERLAY_DIGEST_END:
	.incbin "baserom.nds", 0x10af84, 0x1C
