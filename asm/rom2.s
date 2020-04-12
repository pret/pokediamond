/* rom.s TODO: Disassemble */

.section .text

.incbin "baserom.nds", 0x4E0C, 0xEB7C0

	.global sub_20EC5CC
sub_20EC5CC:
.incbin "baserom.nds", 0xF05CC, 0xC8

	.global sub_20EC694
sub_20EC694:
.incbin "baserom.nds", 0xF0694, 0x1b090
