	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F457C
UNK_020F457C: ; 0x020F457C
	.byte 0x0C, 0x00

	.global UNK_020F457E
UNK_020F457E: ; 0x020F457E
	.byte 0x5D, 0x04, 0x0D, 0x00, 0x5D, 0x04, 0x0E, 0x00, 0x5D, 0x04, 0x0F, 0x00, 0x5D, 0x04, 0x10, 0x00
	.byte 0x5D, 0x04, 0x11, 0x00, 0x5D, 0x04, 0x12, 0x00, 0x5D, 0x04, 0x13, 0x00, 0x5D, 0x04, 0x14, 0x00
	.byte 0x70, 0x04, 0x15, 0x00, 0x70, 0x04, 0x16, 0x00, 0x70, 0x04, 0x17, 0x00, 0x70, 0x04, 0x18, 0x00
	.byte 0x62, 0x04, 0xFF, 0xFF, 0x64, 0x04, 0x19, 0x00, 0x5C, 0x04, 0x1A, 0x00, 0x61, 0x04, 0x1A, 0x00
	.byte 0x5E, 0x04, 0xFF, 0xFF, 0x5E, 0x04, 0x1A, 0x00, 0x65, 0x04, 0x19, 0x00, 0x66, 0x04, 0xFF, 0xFF
	.byte 0x5C, 0x04, 0x1B, 0x00, 0x63, 0x04, 0x1C, 0x00, 0x6E, 0x04, 0x1C, 0x00, 0x60, 0x04, 0x1D, 0x00
	.byte 0x5F, 0x04, 0x1D, 0x00, 0x5F, 0x04, 0x1E, 0x00, 0x5F, 0x04, 0x1E, 0x00, 0x5C, 0x04, 0x1D, 0x00
	.byte 0x62, 0x04, 0xFF, 0xFF, 0x5F, 0x04, 0xFF, 0xFF, 0x5C, 0x04

	.text

	thumb_func_start sub_02047500
sub_02047500: ; 0x02047500
	push {r4, lr}
	ldr r4, [r0, #0x0]
	mov r1, #0x1
	tst r1, r4
	beq _02047546
	add r0, #0x5d
	ldrb r0, [r0, #0x0]
	bl sub_020475C0
	mov r1, #0x80
	tst r1, r4
	beq _0204752A
	cmp r0, #0x1c
	beq _02047558
	mov r0, #0x2
	tst r0, r4
	beq _02047526
	mov r0, #0x1a
	pop {r4, pc}
_02047526:
	mov r0, #0x18
	pop {r4, pc}
_0204752A:
	add r1, r0, #0x0
	sub r1, #0x15
	cmp r1, #0x2
	bls _02047558
	mov r1, #0x2
	tst r1, r4
	beq _0204753C
	mov r0, #0x1a
	pop {r4, pc}
_0204753C:
	mov r1, #0x4
	tst r1, r4
	beq _02047558
	mov r0, #0x19
	pop {r4, pc}
_02047546:
	ldr r0, [r0, #0x8]
	bl sub_02047668
	cmp r0, #0x1e
	blo _02047558
	mov r1, #0x2
	tst r1, r4
	beq _02047558
	mov r0, #0x1b
_02047558:
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0204755C
sub_0204755C: ; 0x0204755C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x1f
	blo _0204756A
	bl GF_AssertFail
_0204756A:
	ldr r0, _02047580 ; =UNK_020F457C
	lsl r1, r5, #0x2
	ldrh r0, [r0, r1]
	ldr r1, _02047584 ; =0x0000FFFF
	cmp r0, r1
	bne _0204757C
	add r0, r4, #0x0
	bl ov05_021E495C
_0204757C:
	pop {r3-r5, pc}
	nop
_02047580: .word UNK_020F457C
_02047584: .word 0x0000FFFF

	thumb_func_start sub_02047588
sub_02047588: ; 0x02047588
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x1f
	blo _02047594
	bl GF_AssertFail
_02047594:
	ldr r0, _0204759C ; =UNK_020F457E
	lsl r1, r4, #0x2
	ldrh r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_0204759C: .word UNK_020F457E

	thumb_func_start sub_020475A0
sub_020475A0: ; 0x020475A0
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02047500
	add r1, r4, #0x0
	bl sub_0204755C
	pop {r4, pc}

	thumb_func_start sub_020475B0
sub_020475B0: ; 0x020475B0
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02047500
	add r1, r4, #0x0
	bl sub_02047588
	pop {r4, pc}

	thumb_func_start sub_020475C0
sub_020475C0: ; 0x020475C0
	sub r0, #0x3e
	mov r1, #0x1d
	cmp r0, #0x23
	bhi _02047662
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020475D4: ; jump table (using 16-bit offset)
	.short _0204761C - _020475D4 - 2; case 0
	.short _02047650 - _020475D4 - 2; case 1
	.short _02047634 - _020475D4 - 2; case 2
	.short _0204763C - _020475D4 - 2; case 3
	.short _02047640 - _020475D4 - 2; case 4
	.short _02047644 - _020475D4 - 2; case 5
	.short _02047648 - _020475D4 - 2; case 6
	.short _0204764C - _020475D4 - 2; case 7
	.short _02047662 - _020475D4 - 2; case 8
	.short _02047662 - _020475D4 - 2; case 9
	.short _02047658 - _020475D4 - 2; case 10
	.short _0204765C - _020475D4 - 2; case 11
	.short _02047620 - _020475D4 - 2; case 12
	.short _02047624 - _020475D4 - 2; case 13
	.short _02047628 - _020475D4 - 2; case 14
	.short _0204762C - _020475D4 - 2; case 15
	.short _02047630 - _020475D4 - 2; case 16
	.short _02047638 - _020475D4 - 2; case 17
	.short _02047662 - _020475D4 - 2; case 18
	.short _02047662 - _020475D4 - 2; case 19
	.short _02047662 - _020475D4 - 2; case 20
	.short _02047662 - _020475D4 - 2; case 21
	.short _02047662 - _020475D4 - 2; case 22
	.short _02047662 - _020475D4 - 2; case 23
	.short _02047654 - _020475D4 - 2; case 24
	.short _02047658 - _020475D4 - 2; case 25
	.short _02047658 - _020475D4 - 2; case 26
	.short _0204765C - _020475D4 - 2; case 27
	.short _02047662 - _020475D4 - 2; case 28
	.short _02047662 - _020475D4 - 2; case 29
	.short _02047662 - _020475D4 - 2; case 30
	.short _02047662 - _020475D4 - 2; case 31
	.short _02047662 - _020475D4 - 2; case 32
	.short _02047662 - _020475D4 - 2; case 33
	.short _02047662 - _020475D4 - 2; case 34
	.short _02047660 - _020475D4 - 2; case 35
_0204761C:
	mov r1, #0x0
	b _02047662
_02047620:
	mov r1, #0x1
	b _02047662
_02047624:
	mov r1, #0x2
	b _02047662
_02047628:
	mov r1, #0x3
	b _02047662
_0204762C:
	mov r1, #0x4
	b _02047662
_02047630:
	mov r1, #0x5
	b _02047662
_02047634:
	mov r1, #0x6
	b _02047662
_02047638:
	mov r1, #0x7
	b _02047662
_0204763C:
	mov r1, #0x8
	b _02047662
_02047640:
	mov r1, #0x9
	b _02047662
_02047644:
	mov r1, #0xa
	b _02047662
_02047648:
	mov r1, #0xb
	b _02047662
_0204764C:
	mov r1, #0xc
	b _02047662
_02047650:
	mov r1, #0xd
	b _02047662
_02047654:
	mov r1, #0x17
	b _02047662
_02047658:
	mov r1, #0x16
	b _02047662
_0204765C:
	mov r1, #0x15
	b _02047662
_02047660:
	mov r1, #0x1c
_02047662:
	add r0, r1, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02047668
sub_02047668: ; 0x02047668
	push {r4, lr}
	mov r4, #0x1e
	bl GetFirstAliveMonInParty_CrashIfNone
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020476C8 ; =0x000001DF
	sub r0, r0, r1
	cmp r0, #0xe
	bhi _020476C4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204768C: ; jump table (using 16-bit offset)
	.short _020476B2 - _0204768C - 2; case 0
	.short _020476BA - _0204768C - 2; case 1
	.short _020476B6 - _0204768C - 2; case 2
	.short _020476BA - _0204768C - 2; case 3
	.short _020476BE - _0204768C - 2; case 4
	.short _020476BE - _0204768C - 2; case 5
	.short _020476B2 - _0204768C - 2; case 6
	.short _020476B2 - _0204768C - 2; case 7
	.short _020476B2 - _0204768C - 2; case 8
	.short _020476AE - _0204768C - 2; case 9
	.short _020476C4 - _0204768C - 2; case 10
	.short _020476C4 - _0204768C - 2; case 11
	.short _020476B2 - _0204768C - 2; case 12
	.short _020476AA - _0204768C - 2; case 13
	.short _020476C2 - _0204768C - 2; case 14
_020476AA:
	mov r4, #0xe
	b _020476C4
_020476AE:
	mov r4, #0x14
	b _020476C4
_020476B2:
	mov r4, #0x13
	b _020476C4
_020476B6:
	mov r4, #0x11
	b _020476C4
_020476BA:
	mov r4, #0x10
	b _020476C4
_020476BE:
	mov r4, #0xf
	b _020476C4
_020476C2:
	mov r4, #0x12
_020476C4:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_020476C8: .word 0x000001DF
