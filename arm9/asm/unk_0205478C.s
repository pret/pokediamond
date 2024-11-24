	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F5C14
UNK_020F5C14: ; 0x020F5C14
	.byte 0x00, 0x00, 0x02, 0x02, 0x00, 0x02, 0x02, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start sub_0205478C
sub_0205478C: ; 0x0205478C
	cmp r0, #0x2
	bne _02054794
	mov r0, #0x1
	bx lr
_02054794:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054798
sub_02054798: ; 0x02054798
	cmp r0, #0x3
	bne _020547A0
	mov r0, #0x1
	bx lr
_020547A0:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547A4
sub_020547A4: ; 0x020547A4
	cmp r0, #0x80
	bne _020547AC
	mov r0, #0x1
	bx lr
_020547AC:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547B0
sub_020547B0: ; 0x020547B0
	cmp r0, #0x69
	bne _020547B8
	mov r0, #0x1
	bx lr
_020547B8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547BC
sub_020547BC: ; 0x020547BC
	cmp r0, #0x62
	bne _020547C4
	mov r0, #0x1
	bx lr
_020547C4:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547C8
sub_020547C8: ; 0x020547C8
	cmp r0, #0x63
	bne _020547D0
	mov r0, #0x1
	bx lr
_020547D0:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547D4
sub_020547D4: ; 0x020547D4
	cmp r0, #0x64
	bne _020547DC
	mov r0, #0x1
	bx lr
_020547DC:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547E0
sub_020547E0: ; 0x020547E0
	cmp r0, #0x65
	bne _020547E8
	mov r0, #0x1
	bx lr
_020547E8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547EC
sub_020547EC: ; 0x020547EC
	cmp r0, #0x6c
	bne _020547F4
	mov r0, #0x1
	bx lr
_020547F4:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020547F8
sub_020547F8: ; 0x020547F8
	cmp r0, #0x6d
	bne _02054800
	mov r0, #0x1
	bx lr
_02054800:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054804
sub_02054804: ; 0x02054804
	cmp r0, #0x6e
	bne _0205480C
	mov r0, #0x1
	bx lr
_0205480C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054810
sub_02054810: ; 0x02054810
	cmp r0, #0x6f
	bne _02054818
	mov r0, #0x1
	bx lr
_02054818:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_0205481C
sub_0205481C: ; 0x0205481C
	ldr r1, _0205482C ; =UNK_020F5C14
	ldrb r1, [r1, r0]
	mov r0, #0x1
	tst r1, r0
	bne _02054828
	mov r0, #0x0
_02054828:
	bx lr
	nop
_0205482C: .word UNK_020F5C14

	thumb_func_start sub_02054830
sub_02054830: ; 0x02054830
	cmp r0, #0x21
	bne _02054838
	mov r0, #0x1
	bx lr
_02054838:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_0205483C
sub_0205483C: ; 0x0205483C
	cmp r0, #0x17
	bne _02054844
	mov r0, #0x1
	bx lr
_02054844:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054848
sub_02054848: ; 0x02054848
	cmp r0, #0x3a
	bne _02054850
	mov r0, #0x1
	bx lr
_02054850:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054854
sub_02054854: ; 0x02054854
	cmp r0, #0x3b
	bne _0205485C
	mov r0, #0x1
	bx lr
_0205485C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054860
sub_02054860: ; 0x02054860
	cmp r0, #0x39
	bne _02054868
	mov r0, #0x1
	bx lr
_02054868:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_0205486C
sub_0205486C: ; 0x0205486C
	cmp r0, #0x38
	bne _02054874
	mov r0, #0x1
	bx lr
_02054874:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054878
sub_02054878: ; 0x02054878
	cmp r0, #0x83
	bne _02054880
	mov r0, #0x1
	bx lr
_02054880:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054884
sub_02054884: ; 0x02054884
	cmp r0, #0x85
	bne _0205488C
	mov r0, #0x1
	bx lr
_0205488C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054890
sub_02054890: ; 0x02054890
	cmp r0, #0x56
	bne _02054898
	mov r0, #0x1
	bx lr
_02054898:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_0205489C
sub_0205489C: ; 0x0205489C
	cmp r0, #0x57
	bne _020548A4
	mov r0, #0x1
	bx lr
_020548A4:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548A8
sub_020548A8: ; 0x020548A8
	cmp r0, #0x58
	bne _020548B0
	mov r0, #0x1
	bx lr
_020548B0:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548B4
sub_020548B4: ; 0x020548B4
	cmp r0, #0x59
	bne _020548BC
	mov r0, #0x1
	bx lr
_020548BC:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548C0
sub_020548C0: ; 0x020548C0
	cmp r0, #0x6a
	bne _020548C8
	mov r0, #0x1
	bx lr
_020548C8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548CC
sub_020548CC: ; 0x020548CC
	cmp r0, #0x6b
	bne _020548D4
	mov r0, #0x1
	bx lr
_020548D4:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548D8
sub_020548D8: ; 0x020548D8
	cmp r0, #0x5e
	bne _020548E0
	mov r0, #0x1
	bx lr
_020548E0:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548E4
sub_020548E4: ; 0x020548E4
	cmp r0, #0x5f
	bne _020548EC
	mov r0, #0x1
	bx lr
_020548EC:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548F0
sub_020548F0: ; 0x020548F0
	cmp r0, #0x20
	bne _020548F8
	mov r0, #0x1
	bx lr
_020548F8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020548FC
sub_020548FC: ; 0x020548FC
	cmp r0, #0x4b
	bne _02054904
	mov r0, #0x1
	bx lr
_02054904:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054908
sub_02054908: ; 0x02054908
	cmp r0, #0x4c
	bne _02054910
	mov r0, #0x1
	bx lr
_02054910:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054914
sub_02054914: ; 0x02054914
	cmp r0, #0xe0
	bne _0205491C
	mov r0, #0x1
	bx lr
_0205491C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054920
sub_02054920: ; 0x02054920
	cmp r0, #0xea
	bne _02054928
	mov r0, #0x1
	bx lr
_02054928:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_0205492C
sub_0205492C: ; 0x0205492C
	cmp r0, #0xe1
	bne _02054934
	mov r0, #0x1
	bx lr
_02054934:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054938
sub_02054938: ; 0x02054938
	cmp r0, #0xe2
	bne _02054940
	mov r0, #0x1
	bx lr
_02054940:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054944
sub_02054944: ; 0x02054944
	cmp r0, #0xe4
	bne _0205494C
	mov r0, #0x1
	bx lr
_0205494C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054950
sub_02054950: ; 0x02054950
	cmp r0, #0xe5
	bne _02054958
	mov r0, #0x1
	bx lr
_02054958:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_0205495C
sub_0205495C: ; 0x0205495C
	cmp r0, #0xeb
	bne _02054964
	mov r0, #0x1
	bx lr
_02054964:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054968
sub_02054968: ; 0x02054968
	cmp r0, #0xec
	bne _02054970
	mov r0, #0x1
	bx lr
_02054970:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054974
sub_02054974: ; 0x02054974
	cmp r0, #0xa4
	beq _0205497C
	cmp r0, #0xa5
	bne _02054980
_0205497C:
	mov r0, #0x1
	bx lr
_02054980:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054984
sub_02054984: ; 0x02054984
	cmp r0, #0xa5
	bne _0205498C
	mov r0, #0x1
	bx lr
_0205498C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054990
sub_02054990: ; 0x02054990
	cmp r0, #0xa6
	beq _02054998
	cmp r0, #0xa7
	bne _0205499C
_02054998:
	mov r0, #0x1
	bx lr
_0205499C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020549A0
sub_020549A0: ; 0x020549A0
	cmp r0, #0xa7
	bne _020549A8
	mov r0, #0x1
	bx lr
_020549A8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020549AC
sub_020549AC: ; 0x020549AC
	add r0, #0x5f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r3, #0x0
	cmp r0, #0x7
	bhi _020549C6
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	mov r0, #0x87
	tst r0, r2
	beq _020549C6
	add r3, r1, #0x0
_020549C6:
	add r0, r3, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_020549CC
sub_020549CC: ; 0x020549CC
	cmp r0, #0xa8
	bne _020549D4
	mov r0, #0x1
	bx lr
_020549D4:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020549D8
sub_020549D8: ; 0x020549D8
	cmp r0, #0xa1
	bne _020549E0
	mov r0, #0x1
	bx lr
_020549E0:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020549E4
sub_020549E4: ; 0x020549E4
	cmp r0, #0xa2
	bne _020549EC
	mov r0, #0x1
	bx lr
_020549EC:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020549F0
sub_020549F0: ; 0x020549F0
	cmp r0, #0xa3
	bne _020549F8
	mov r0, #0x1
	bx lr
_020549F8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020549FC
sub_020549FC: ; 0x020549FC
	cmp r0, #0xd9
	beq _02054A04
	cmp r0, #0xda
	bne _02054A08
_02054A04:
	mov r0, #0x1
	bx lr
_02054A08:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054A0C
sub_02054A0C: ; 0x02054A0C
	cmp r0, #0xd9
	bne _02054A14
	mov r0, #0x1
	bx lr
_02054A14:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054A18
sub_02054A18: ; 0x02054A18
	cmp r0, #0xda
	bne _02054A20
	mov r0, #0x1
	bx lr
_02054A20:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054A24
sub_02054A24: ; 0x02054A24
	cmp r0, #0xd7
	bne _02054A2C
	mov r0, #0x1
	bx lr
_02054A2C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054A30
sub_02054A30: ; 0x02054A30
	cmp r0, #0xd8
	bne _02054A38
	mov r0, #0x1
	bx lr
_02054A38:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054A3C
sub_02054A3C: ; 0x02054A3C
	cmp r0, #0x8
	bne _02054A44
	mov r0, #0x1
	bx lr
_02054A44:
	mov r0, #0x0
	bx lr

	thumb_func_start MetatileBehavior_IsWaterfall
MetatileBehavior_IsWaterfall: ; 0x02054A48
	cmp r0, #0x13
	bne _02054A50
	mov r0, #0x1
	bx lr
_02054A50:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054A54
sub_02054A54: ; 0x02054A54
	cmp r0, #0xdb
	bne _02054A5C
	mov r0, #0x1
	bx lr
_02054A5C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054A60
sub_02054A60: ; 0x02054A60
	add r0, #0xce
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r3, #0x0
	cmp r0, #0x17
	bhi _02054A7A
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02054A80 ; =0x0080000D
	tst r0, r2
	beq _02054A7A
	add r3, r1, #0x0
_02054A7A:
	add r0, r3, #0x0
	bx lr
	nop
_02054A80: .word 0x0080000D

	thumb_func_start sub_02054A84
sub_02054A84: ; 0x02054A84
	add r0, #0xcd
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r3, #0x0
	cmp r0, #0x16
	bhi _02054A9E
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02054AA4 ; =0x00400019
	tst r0, r2
	beq _02054A9E
	add r3, r1, #0x0
_02054A9E:
	add r0, r3, #0x0
	bx lr
	nop
_02054AA4: .word 0x00400019

	thumb_func_start sub_02054AA8
sub_02054AA8: ; 0x02054AA8
	add r0, #0xcf
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r3, #0x0
	cmp r0, #0x19
	bhi _02054AC2
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02054AC8 ; =0x02000051
	tst r0, r2
	beq _02054AC2
	add r3, r1, #0x0
_02054AC2:
	add r0, r3, #0x0
	bx lr
	nop
_02054AC8: .word 0x02000051

	thumb_func_start sub_02054ACC
sub_02054ACC: ; 0x02054ACC
	add r0, #0xd0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r3, #0x0
	cmp r0, #0x1a
	bhi _02054AE6
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02054AEC ; =0x04000051
	tst r0, r2
	beq _02054AE6
	add r3, r1, #0x0
_02054AE6:
	add r0, r3, #0x0
	bx lr
	nop
_02054AEC: .word 0x04000051

	thumb_func_start sub_02054AF0
sub_02054AF0: ; 0x02054AF0
	cmp r0, #0x16
	bne _02054AF8
	mov r0, #0x1
	bx lr
_02054AF8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054AFC
sub_02054AFC: ; 0x02054AFC
	ldr r1, _02054B10 ; =UNK_020F5C14
	ldrb r1, [r1, r0]
	mov r0, #0x2
	tst r0, r1
	beq _02054B0A
	mov r0, #0x1
	bx lr
_02054B0A:
	mov r0, #0x0
	bx lr
	nop
_02054B10: .word UNK_020F5C14

	thumb_func_start sub_02054B14
sub_02054B14: ; 0x02054B14
	cmp r0, #0x86
	bne _02054B1C
	mov r0, #0x1
	bx lr
_02054B1C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B20
sub_02054B20: ; 0x02054B20
	cmp r0, #0x16
	beq _02054B28
	cmp r0, #0x10
	bne _02054B2C
_02054B28:
	mov r0, #0x1
	bx lr
_02054B2C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B30
sub_02054B30: ; 0x02054B30
	cmp r0, #0x40
	bne _02054B38
	mov r0, #0x1
	bx lr
_02054B38:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B3C
sub_02054B3C: ; 0x02054B3C
	cmp r0, #0x41
	bne _02054B44
	mov r0, #0x1
	bx lr
_02054B44:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B48
sub_02054B48: ; 0x02054B48
	cmp r0, #0x42
	bne _02054B50
	mov r0, #0x1
	bx lr
_02054B50:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B54
sub_02054B54: ; 0x02054B54
	cmp r0, #0x43
	bne _02054B5C
	mov r0, #0x1
	bx lr
_02054B5C:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B60
sub_02054B60: ; 0x02054B60
	cmp r0, #0x67
	bne _02054B68
	mov r0, #0x1
	bx lr
_02054B68:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B6C
sub_02054B6C: ; 0x02054B6C
	cmp r0, #0x70
	bne _02054B74
	mov r0, #0x1
	bx lr
_02054B74:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054B78
sub_02054B78: ; 0x02054B78
	add r0, #0x8f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0xc
	bhi _02054B86
	mov r0, #0x1
	bx lr
_02054B86:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02054B8C
sub_02054B8C: ; 0x02054B8C
	add r0, #0x8d
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r3, #0x0
	cmp r0, #0x9
	bhi _02054BA6
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02054BAC ; =0x00000221
	tst r0, r2
	beq _02054BA6
	add r3, r1, #0x0
_02054BA6:
	add r0, r3, #0x0
	bx lr
	nop
_02054BAC: .word 0x00000221

	thumb_func_start sub_02054BB0
sub_02054BB0: ; 0x02054BB0
	add r0, #0x8c
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r3, #0x0
	cmp r0, #0x9
	bhi _02054BCA
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r0
	ldr r0, _02054BD0 ; =0x00000221
	tst r0, r2
	beq _02054BCA
	add r3, r1, #0x0
_02054BCA:
	add r0, r3, #0x0
	bx lr
	nop
_02054BD0: .word 0x00000221

	thumb_func_start sub_02054BD4
sub_02054BD4: ; 0x02054BD4
	cmp r0, #0x75
	bne _02054BDC
	mov r0, #0x1
	bx lr
_02054BDC:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_02054BE0
sub_02054BE0: ; 0x02054BE0
	add r0, #0x8a
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x3
	bhi _02054BEE
	mov r0, #0x1
	bx lr
_02054BEE:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02054BF4
sub_02054BF4: ; 0x02054BF4
	add r0, #0x86
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x3
	bhi _02054C02
	mov r0, #0x1
	bx lr
_02054C02:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02054C08
sub_02054C08: ; 0x02054C08
	cmp r0, #0xff
	bne _02054C10
	mov r0, #0x1
	bx lr
_02054C10:
	mov r0, #0x0
	bx lr
