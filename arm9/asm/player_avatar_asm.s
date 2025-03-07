	.include "asm/macros.inc"
	.include "global.inc"

	.extern PlayerAvatar_SetFlagsBits
	.extern PlayerAvatar_ClearFlagsBits
	.extern PlayerAvatar_GetFlagsBitsMask

	.text

	thumb_func_start sub_02055408
sub_02055408: ; 0x02055408
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start sub_0205540C
sub_0205540C: ; 0x0205540C
	str r1, [r0, #0x20]
	bx lr

	thumb_func_start sub_02055410
sub_02055410: ; 0x02055410
	ldr r3, _02055418 ; =sub_020556F4
	mov r1, #0x0
	str r1, [r0, #0x20]
	bx r3
	.balign 4
_02055418: .word sub_020556F4

	thumb_func_start sub_0205541C
sub_0205541C: ; 0x0205541C
	ldr r3, [r0, #0x20]
	add r1, r3, r1
	str r1, [r0, #0x20]
	cmp r1, r2
	ble _02055428
	str r2, [r0, #0x20]
_02055428:
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start sub_0205542C
sub_0205542C: ; 0x0205542C
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start sub_02055430
sub_02055430: ; 0x02055430
	ldr r0, [r0, #0x24]
	bx lr

	thumb_func_start sub_02055434
sub_02055434: ; 0x02055434
	str r1, [r0, #0x28]
	bx lr

	thumb_func_start sub_02055438
sub_02055438: ; 0x02055438
	ldr r0, [r0, #0x28]
	bx lr

	thumb_func_start sub_0205543C
sub_0205543C: ; 0x0205543C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl sub_0205542C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02055434
	pop {r3-r5, pc}

	thumb_func_start sub_02055450
sub_02055450: ; 0x02055450
	str r1, [r0, #0x30]
	bx lr

	thumb_func_start sub_02055454
sub_02055454: ; 0x02055454
	ldr r0, [r0, #0x30]
	bx lr

	thumb_func_start PlayerAvatar_SetPlayerSaveData
PlayerAvatar_SetPlayerSaveData: ; 0x02055458
	str r1, [r0, #0x34]
	bx lr

	thumb_func_start sub_0205545C
sub_0205545C: ; 0x0205545C
	ldr r0, [r0, #0x34]
	bx lr

	thumb_func_start sub_02055460
sub_02055460: ; 0x02055460
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start sub_02055464
sub_02055464: ; 0x02055464
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start sub_02055468
sub_02055468: ; 0x02055468
	mov r1, #0x0
	strh r1, [r0, #0x0]
	strh r1, [r0, #0x2]
	str r1, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start sub_02055474
sub_02055474: ; 0x02055474
	cmp r0, #0x0
	beq _02055482
	ldrh r0, [r0, #0x2]
	cmp r0, #0x1
	bne _02055482
	mov r0, #0x1
	bx lr
_02055482:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02055488
sub_02055488: ; 0x02055488
	cmp r1, #0x1
	bne _02055492
	mov r1, #0x1
	strh r1, [r0, #0x2]
	bx lr
_02055492:
	mov r1, #0x0
	strh r1, [r0, #0x2]
	bx lr

	thumb_func_start sub_02055498
sub_02055498: ; 0x02055498
	cmp r0, #0x0
	bne _020554A0
	mov r0, #0x0
	bx lr
_020554A0:
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start sub_020554A4
sub_020554A4: ; 0x020554A4
	cmp r0, #0x0
	beq _020554AA
	strh r1, [r0, #0x0]
_020554AA:
	bx lr

	thumb_func_start sub_020554AC
sub_020554AC: ; 0x020554AC
	push {r4, lr}
	add r4, r1, #0x0
	bl sub_0205545C
	add r1, r4, #0x0
	bl sub_020554A4
	pop {r4, pc}

	thumb_func_start sub_020554BC
sub_020554BC: ; 0x020554BC
	push {r3, lr}
	bl sub_0205545C
	bl sub_02055498
	pop {r3, pc}

	thumb_func_start PlayerSaveData_GetState
PlayerSaveData_GetState: ; 0x020554C8
	cmp r0, #0x0
	beq _020554D0
	ldr r0, [r0, #0x4]
	bx lr
_020554D0:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020554D4
sub_020554D4: ; 0x020554D4
	cmp r0, #0x0
	beq _020554DA
	str r1, [r0, #0x4]
_020554DA:
	bx lr

	thumb_func_start sub_020554DC
sub_020554DC: ; 0x020554DC
	push {r4, lr}
	add r4, r1, #0x0
	bl sub_0205545C
	add r1, r4, #0x0
	bl sub_020554D4
	pop {r4, pc}

	thumb_func_start sub_020554EC
sub_020554EC: ; 0x020554EC
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	bl PlayerAvatar_GetMapObject
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl LocalMapObject_SetPositionFromVectorAndDirection
	add r0, r5, #0x0
	mov r1, #0x0
	bl PlayerAvatar_SetUnk10
	add r0, r5, #0x0
	mov r1, #0x0
	bl PlayerAvatar_SetUnk14
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02055514
sub_02055514: ; 0x02055514
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r4, r3, #0x0
	bl PlayerAvatar_GetMapObject
	add r1, r6, #0x0
	mov r2, #0x0
	add r3, r7, #0x0
	str r4, [sp, #0x0]
	bl MapObject_SetPositionFromXYZAndDirection
	add r0, r5, #0x0
	mov r1, #0x0
	bl PlayerAvatar_SetUnk10
	add r0, r5, #0x0
	mov r1, #0x0
	bl PlayerAvatar_SetUnk14
	pop {r3-r7, pc}

	thumb_func_start sub_02055540
sub_02055540: ; 0x02055540
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	bl PlayerAvatar_GetMapObject
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl MapObject_CopyPositionVector
	add r0, r4, #0x0
	add r1, sp, #0x0
	str r5, [sp, #0x4]
	bl MapObject_SetPositionVector
	add sp, #0xc
	pop {r4-r5, pc}

	thumb_func_start PlayerAvatar_ToggleAutomaticHeightUpdating
PlayerAvatar_ToggleAutomaticHeightUpdating: ; 0x02055560
	push {r4, lr}
	add r4, r1, #0x0
	bl PlayerAvatar_GetMapObject
	cmp r4, #0x1
	bne _02055574
	mov r1, #0x0
	bl MapObject_SetIgnoreHeights
	pop {r4, pc}
_02055574:
	mov r1, #0x1
	bl MapObject_SetIgnoreHeights
	pop {r4, pc}

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

	thumb_func_start sub_020556F4
sub_020556F4: ; 0x020556F4
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
