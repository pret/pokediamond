/* rom2.s TODO: Disassemble */

.section .text

.incbin "baserom.nds", 0x8EC14, 0x619B8

	.global sub_020EC5CC
sub_020EC5CC:
.incbin "baserom.nds", 0xF05CC, 0xC8

	.global sub_020EC694
sub_020EC694:
.incbin "baserom.nds", 0xF0694, 0x1b090
