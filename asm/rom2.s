/* rom2.s TODO: Disassemble */

.section .text

.incbin "baserom.nds", 0xD9914, 0x16CB8

	.global FUN_020EC5CC
FUN_020EC5CC:
.incbin "baserom.nds", 0xF05CC, 0xC8

	.global FUN_020EC694
FUN_020EC694:
.incbin "baserom.nds", 0xF0694, 0x1b090
