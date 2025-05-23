	.include "asm/macros.inc"
	.include "global.inc"

	.extern PlayerAvatar_SetFlagsBits
	.extern PlayerAvatar_ClearFlagsBits
	.extern PlayerAvatar_GetFlagsBitsMask

	.text

	thumb_func_start sub_0205557C
sub_0205557C: ; 0x0205557C
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl PlayerAvatar_GetMapObject
	add r4, r0, #0x0
	cmp r5, #0x1
	bne _02055598
	mov r1, #0x0
	bl MapObject_SetIgnoreHeights
	add r0, r4, #0x0
	bl sub_02059D1C
	pop {r3-r5, pc}
_02055598:
	mov r1, #0x1
	bl MapObject_SetIgnoreHeights
	pop {r3-r5, pc}

	thumb_func_start PlayerAvatar_GetSpriteByStateAndGender
PlayerAvatar_GetSpriteByStateAndGender: ; 0x020555A0
	push {r3, lr}
	cmp r1, #0x0
	bne _020555F2
	cmp r0, #0x9
	bhi _0205563E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020555B6: ; jump table (using 16-bit offset)
	.short _020555CA - _020555B6 - 2; case 0
	.short _020555CE - _020555B6 - 2; case 1
	.short _020555D2 - _020555B6 - 2; case 2
	.short _020555D6 - _020555B6 - 2; case 3
	.short _020555DA - _020555B6 - 2; case 4
	.short _020555DE - _020555B6 - 2; case 5
	.short _020555E2 - _020555B6 - 2; case 6
	.short _020555E6 - _020555B6 - 2; case 7
	.short _020555EA - _020555B6 - 2; case 8
	.short _020555EE - _020555B6 - 2; case 9
_020555CA:
	mov r0, #0x0
	pop {r3, pc}
_020555CE:
	mov r0, #0x15
	pop {r3, pc}
_020555D2:
	mov r0, #0xb2
	pop {r3, pc}
_020555D6:
	mov r0, #0xb0
	pop {r3, pc}
_020555DA:
	mov r0, #0xb4
	pop {r3, pc}
_020555DE:
	mov r0, #0xba
	pop {r3, pc}
_020555E2:
	mov r0, #0xbc
	pop {r3, pc}
_020555E6:
	mov r0, #0xc4
	pop {r3, pc}
_020555EA:
	mov r0, #0xc6
	pop {r3, pc}
_020555EE:
	mov r0, #0xc8
	pop {r3, pc}
_020555F2:
	cmp r0, #0x9
	bhi _0205563E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02055602: ; jump table (using 16-bit offset)
	.short _02055616 - _02055602 - 2; case 0
	.short _0205561A - _02055602 - 2; case 1
	.short _0205561E - _02055602 - 2; case 2
	.short _02055622 - _02055602 - 2; case 3
	.short _02055626 - _02055602 - 2; case 4
	.short _0205562A - _02055602 - 2; case 5
	.short _0205562E - _02055602 - 2; case 6
	.short _02055632 - _02055602 - 2; case 7
	.short _02055636 - _02055602 - 2; case 8
	.short _0205563A - _02055602 - 2; case 9
_02055616:
	mov r0, #0x61
	pop {r3, pc}
_0205561A:
	mov r0, #0x62
	pop {r3, pc}
_0205561E:
	mov r0, #0xb3
	pop {r3, pc}
_02055622:
	mov r0, #0xb1
	pop {r3, pc}
_02055626:
	mov r0, #0xb5
	pop {r3, pc}
_0205562A:
	mov r0, #0xbb
	pop {r3, pc}
_0205562E:
	mov r0, #0xbd
	pop {r3, pc}
_02055632:
	mov r0, #0xc5
	pop {r3, pc}
_02055636:
	mov r0, #0xc7
	pop {r3, pc}
_0205563A:
	mov r0, #0xc9
	pop {r3, pc}
_0205563E:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02055648
sub_02055648: ; 0x02055648
	push {r3, lr}
	cmp r0, #0x9
	bhi _02055690
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205565A: ; jump table (using 16-bit offset)
	.short _0205566E - _0205565A - 2; case 0
	.short _02055672 - _0205565A - 2; case 1
	.short _02055676 - _0205565A - 2; case 2
	.short _02055690 - _0205565A - 2; case 3
	.short _0205567A - _0205565A - 2; case 4
	.short _02055690 - _0205565A - 2; case 5
	.short _0205567E - _0205565A - 2; case 6
	.short _02055682 - _0205565A - 2; case 7
	.short _02055686 - _0205565A - 2; case 8
	.short _0205568A - _0205565A - 2; case 9
_0205566E:
	mov r0, #0x1
	pop {r3, pc}
_02055672:
	mov r0, #0x2
	pop {r3, pc}
_02055676:
	mov r0, #0x4
	pop {r3, pc}
_0205567A:
	mov r0, #0x10
	pop {r3, pc}
_0205567E:
	mov r0, #0x20
	pop {r3, pc}
_02055682:
	mov r0, #0x40
	pop {r3, pc}
_02055686:
	mov r0, #0x80
	pop {r3, pc}
_0205568A:
	mov r0, #0x1
	lsl r0, r0, #0x8
	pop {r3, pc}
_02055690:
	bl GF_AssertFail
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start sub_02055698
sub_02055698: ; 0x02055698
	ldr r0, [r0, #0x38]
	bx lr

	thumb_func_start sub_0205569C
sub_0205569C: ; 0x0205569C
	push {r3, lr}
	cmp r1, #0x1
	bne _020556AA
	mov r1, #0x1
	bl PlayerAvatar_SetFlagsBits
	pop {r3, pc}
_020556AA:
	mov r1, #0x1
	bl PlayerAvatar_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020556B4
sub_020556B4: ; 0x020556B4
	push {r3, lr}
	mov r1, #0x1
	bl PlayerAvatar_GetFlagsBitsMask
	cmp r0, #0x0
	beq _020556C4
	mov r0, #0x1
	pop {r3, pc}
_020556C4:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_020556C8
sub_020556C8: ; 0x020556C8
	push {r3, lr}
	cmp r1, #0x1
	bne _020556D6
	mov r1, #0x2
	bl PlayerAvatar_SetFlagsBits
	pop {r3, pc}
_020556D6:
	mov r1, #0x2
	bl PlayerAvatar_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020556E0
sub_020556E0: ; 0x020556E0
	push {r3, lr}
	mov r1, #0x2
	bl PlayerAvatar_GetFlagsBitsMask
	cmp r0, #0x0
	beq _020556F0
	mov r0, #0x1
	pop {r3, pc}
_020556F0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start PlayerAvatar_SetFlag2
PlayerAvatar_SetFlag2: ; 0x020556F4
	push {r3, lr}
	cmp r1, #0x1
	bne _02055702
	mov r1, #0x4
	bl PlayerAvatar_SetFlagsBits
	pop {r3, pc}
_02055702:
	mov r1, #0x4
	bl PlayerAvatar_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205570C
sub_0205570C: ; 0x0205570C
	push {r3, lr}
	mov r1, #0x4
	bl PlayerAvatar_GetFlagsBitsMask
	cmp r0, #0x0
	beq _0205571C
	mov r0, #0x1
	pop {r3, pc}
_0205571C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_02055720
sub_02055720: ; 0x02055720
	push {r3, lr}
	cmp r1, #0x1
	bne _0205572E
	mov r1, #0x8
	bl PlayerAvatar_SetFlagsBits
	pop {r3, pc}
_0205572E:
	mov r1, #0x8
	bl PlayerAvatar_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02055738
sub_02055738: ; 0x02055738
	push {r3, lr}
	mov r1, #0x8
	bl PlayerAvatar_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02055748
	mov r0, #0x1
	pop {r3, pc}
_02055748:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_0205574C
sub_0205574C: ; 0x0205574C
	push {r3, lr}
	cmp r1, #0x1
	bne _0205575A
	mov r1, #0x10
	bl PlayerAvatar_SetFlagsBits
	pop {r3, pc}
_0205575A:
	mov r1, #0x10
	bl PlayerAvatar_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02055764
sub_02055764: ; 0x02055764
	push {r3, lr}
	mov r1, #0x10
	bl PlayerAvatar_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02055774
	mov r0, #0x1
	pop {r3, pc}
_02055774:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_02055778
sub_02055778: ; 0x02055778
	push {r3, lr}
	cmp r1, #0x1
	bne _02055786
	mov r1, #0x20
	bl PlayerAvatar_SetFlagsBits
	pop {r3, pc}
_02055786:
	mov r1, #0x20
	bl PlayerAvatar_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02055790
sub_02055790: ; 0x02055790
	push {r3, lr}
	mov r1, #0x20
	bl PlayerAvatar_GetFlagsBitsMask
	cmp r0, #0x0
	beq _020557A0
	mov r0, #0x1
	pop {r3, pc}
_020557A0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_020557A4
sub_020557A4: ; 0x020557A4
	ldr r3, _020557AC ; =PlayerAvatar_SetFlagsBits
	mov r1, #0x40
	bx r3
	nop
_020557AC: .word PlayerAvatar_SetFlagsBits

	thumb_func_start sub_020557B0
sub_020557B0: ; 0x020557B0
	ldr r3, _020557B8 ; =PlayerAvatar_ClearFlagsBits
	mov r1, #0x40
	bx r3
	nop
_020557B8: .word PlayerAvatar_ClearFlagsBits

	thumb_func_start sub_020557BC
sub_020557BC: ; 0x020557BC
	push {r3, lr}
	mov r1, #0x40
	bl PlayerAvatar_GetFlagsBitsMask
	cmp r0, #0x0
	beq _020557CC
	mov r0, #0x1
	pop {r3, pc}
_020557CC:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_020557D0
sub_020557D0: ; 0x020557D0
	push {r3, lr}
	cmp r1, #0x1
	bne _020557DE
	mov r1, #0x80
	bl PlayerAvatar_SetFlagsBits
	pop {r3, pc}
_020557DE:
	mov r1, #0x80
	bl PlayerAvatar_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020557E8
sub_020557E8: ; 0x020557E8
	ldr r3, _020557F0 ; =PlayerAvatar_GetFlagsBitsMask
	mov r1, #0x80
	bx r3
	nop
_020557F0: .word PlayerAvatar_GetFlagsBitsMask
