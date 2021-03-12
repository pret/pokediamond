	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD66_021D74E0
MOD66_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl OverlayManager_GetField18
	mov r2, #2
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x11
	lsl r2, r2, #0x10
	bl FUN_0201681C
	add r0, r4, #0
	mov r1, #0xe4
	mov r2, #0x11
	bl OverlayManager_CreateAndGetData
	mov r1, #0
	mov r2, #0xe4
	add r4, r0, #0
	bl memset
	ldr r0, _021D7534 ; =0x00000139
	str r5, [r4, #0x2c]
	ldrb r0, [r5, r0]
	cmp r0, #3
	bhs _021D7516
	b _021D7518
_021D7516:
	mov r0, #0
_021D7518:
	strb r0, [r4]
	mov r0, #0x4f
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	mov r1, #0
	add r2, r1, #0
	strh r0, [r4, #2]
	mov r0, #0x11
	str r0, [r4, #4]
	mov r0, #0x37
	bl FUN_0200433C
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7534: .word 0x00000139
	thumb_func_end MOD66_021D74E0

	thumb_func_start MOD66_021D7538
MOD66_021D7538: ; 0x021D7538
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #8
	bhi _021D75AA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7552: ; jump table
	.short _021D7564 - _021D7552 - 2 ; case 0
	.short _021D756C - _021D7552 - 2 ; case 1
	.short _021D75AA - _021D7552 - 2 ; case 2
	.short _021D7574 - _021D7552 - 2 ; case 3
	.short _021D7582 - _021D7552 - 2 ; case 4
	.short _021D75AA - _021D7552 - 2 ; case 5
	.short _021D7590 - _021D7552 - 2 ; case 6
	.short _021D75A6 - _021D7552 - 2 ; case 7
	.short _021D759E - _021D7552 - 2 ; case 8
_021D7564:
	bl MOD66_021D7A88
	str r0, [r4, #8]
	b _021D75AA
_021D756C:
	bl MOD66_021D7AB0
	str r0, [r4, #8]
	b _021D75AA
_021D7574:
	bl MOD66_021D7AE8
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD66_021D77C4
	b _021D75AA
_021D7582:
	bl MOD66_021D7AFC
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD66_021D77C4
	b _021D75AA
_021D7590:
	bl MOD66_021D7B38
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD66_021D77C4
	b _021D75AA
_021D759E:
	bl MOD66_021D7B94
	str r0, [r4, #8]
	b _021D75AA
_021D75A6:
	mov r0, #1
	pop {r4, pc}
_021D75AA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD66_021D7538

	thumb_func_start MOD66_021D75B0
MOD66_021D75B0: ; 0x021D75B0
	push {r4, lr}
	add r4, r0, #0
	bl OverlayManager_GetData
	add r0, r4, #0
	bl OverlayManager_FreeData
	mov r0, #0x11
	bl FUN_020168D0
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD66_021D75B0

	thumb_func_start MOD66_021D75C8
MOD66_021D75C8: ; 0x021D75C8
	push {r4, lr}
	add r4, r0, #0
	ldrb r2, [r4]
	mov r1, #0x24
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D75FC ; =0x021D95E8
	ldr r1, [r1, r3]
	cmp r1, #0
	beq _021D75DE
	blx r1
_021D75DE:
	bl FUN_020AEEB8
	add r0, r4, #0
	bl MOD66_021D9220
	ldr r0, [r4, #0x28]
	bl FUN_0201AB60
	ldr r3, _021D7600 ; =0x027E0000
	ldr r1, _021D7604 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_021D75FC: .word MOD66_021D95E8
_021D7600: .word 0x027E0000
_021D7604: .word 0x00003FF8
	thumb_func_end MOD66_021D75C8

	thumb_func_start MOD66_021D7608
MOD66_021D7608: ; 0x021D7608
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7624 ; =0x021D95A0
	add r3, sp, #0
	mov r2, #5
_021D7612:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7612
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7624: .word MOD66_021D95A0
	thumb_func_end MOD66_021D7608

	thumb_func_start MOD66_021D7628
MOD66_021D7628: ; 0x021D7628
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021D763C
	cmp r0, #1
	beq _021D76E4
	cmp r0, #2
	beq _021D7710
	b _021D772E
_021D763C:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7738 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D773C ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	ldr r0, [r4, #0x2c]
	ldr r1, [r0]
	cmp r1, #0
	bne _021D767C
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _021D767C
	mov r0, #3
	str r0, [r4, #0x20]
	mov r0, #0x1b
	str r0, [r4, #0x24]
	b _021D7694
_021D767C:
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #5
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x2c]
	ldr r1, [r0, #4]
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r0, r0, #5
	str r0, [r4, #0x24]
_021D7694:
	ldr r0, [r4, #0x20]
	ldr r2, _021D7740 ; =0x0000017E
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x24]
	mov r1, #0x1a
	str r0, [r4, #0x1c]
	ldr r3, [r4, #4]
	mov r0, #1
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0x80
	str r0, [r1]
	mov r2, #0x8b
	ldr r3, [r4, #4]
	mov r0, #1
	mov r1, #0x1a
	lsl r2, r2, #2
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0x84
	str r0, [r1]
	ldr r1, [r4, #4]
	mov r0, #0x16
	bl String_ctor
	add r1, r4, #0
	add r1, #0x88
	str r0, [r1]
	ldr r0, [r4, #4]
	bl FUN_020345A8
	str r0, [r4, #0x30]
	ldr r0, _021D7744 ; =0x021D9AA0
	ldr r1, [r4, #4]
	bl MOD66_021D94A4
	str r0, [r4, #0x40]
	b _021D772E
_021D76E4:
	bl MOD66_021D7608
	ldr r0, [r4, #4]
	bl FUN_02016B94
	str r0, [r4, #0x28]
	ldr r1, [r4, #0x28]
	add r0, r4, #0
	bl MOD66_021D77E4
	add r0, r4, #0
	bl MOD66_021D78B4
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	add r0, r4, #0
	bl MOD66_021D913C
	b _021D772E
_021D7710:
	ldr r0, _021D7748 ; =MOD66_021D75C8
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	ldrb r1, [r4]
	mov r0, #0x24
	add r2, r1, #0
	mul r2, r0
	ldr r0, _021D774C ; =0x021D95D8
	ldr r0, [r0, r2]
	str r0, [r4, #0x38]
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
_021D772E:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D7738: .word 0xFFFFE0FF
_021D773C: .word 0x04001000
_021D7740: .word 0x0000017E
_021D7744: .word MOD66_021D9AA0
_021D7748: .word MOD66_021D75C8
_021D774C: .word MOD66_021D95D8
	thumb_func_end MOD66_021D7628

	thumb_func_start MOD66_021D7750
MOD66_021D7750: ; 0x021D7750
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_0201CD04
	mov r0, #0x1f
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #0x1f
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	add r0, r5, #0
	bl MOD66_021D91F4
	add r0, r5, #0
	bl MOD66_021D7A34
	mov r4, #0
_021D7782:
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x28]
	lsr r1, r1, #0x18
	bl FUN_020178A0
	add r4, r4, #1
	cmp r4, #8
	blt _021D7782
	ldr r0, [r5, #0x28]
	bl FreeToHeap
	ldr r0, [r5, #0x40]
	bl MOD66_021D9544
	ldr r0, [r5, #0x30]
	bl FUN_020345DC
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	bl String_dtor
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	bl DestroyMsgData
	add r5, #0x80
	ldr r0, [r5]
	bl DestroyMsgData
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD66_021D7750

	thumb_func_start MOD66_021D77C4
MOD66_021D77C4: ; 0x021D77C4
	push {r4, lr}
	add r4, r0, #0
	ldrb r2, [r4]
	mov r1, #0x24
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D77E0 ; =0x021D95E0
	ldr r1, [r1, r3]
	blx r1
	add r0, r4, #0
	bl MOD66_021D9214
	pop {r4, pc}
	nop
_021D77E0: .word MOD66_021D95E0
	thumb_func_end MOD66_021D77C4

	thumb_func_start MOD66_021D77E4
MOD66_021D77E4: ; 0x021D77E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xf4
	ldr r4, _021D78AC ; =0x021D9590
	add r3, sp, #4
	str r0, [sp]
	add r6, r1, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r4, _021D78B0 ; =0x021D9634
	add r3, sp, #0x14
	mov r2, #0x1c
_021D7806:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7806
	mov r4, #0
	add r7, r4, #0
	add r5, sp, #0x14
_021D7814:
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, r5, #0
	mov r3, #0
	bl FUN_02016C18
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r4, r4, #1
	bl FUN_02018744
	add r7, r7, #1
	add r5, #0x1c
	cmp r7, #8
	blt _021D7814
	ldr r3, [sp]
	mov r0, #0
	ldr r3, [r3, #4]
	mov r1, #0x20
	add r2, r0, #0
	bl FUN_02017F18
	ldr r3, [sp]
	mov r0, #1
	ldr r3, [r3, #4]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [sp]
	mov r0, #2
	ldr r3, [r3, #4]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [sp]
	mov r0, #3
	ldr r3, [r3, #4]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [sp]
	mov r0, #4
	ldr r3, [r3, #4]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [sp]
	mov r0, #5
	ldr r3, [r3, #4]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [sp]
	mov r0, #6
	ldr r3, [r3, #4]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r3, [sp]
	mov r0, #7
	ldr r3, [r3, #4]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	add sp, #0xf4
	pop {r4, r5, r6, r7, pc}
	nop
_021D78AC: .word MOD66_021D9590
_021D78B0: .word MOD66_021D9634
	thumb_func_end MOD66_021D77E4

	thumb_func_start MOD66_021D78B4
MOD66_021D78B4: ; 0x021D78B4
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r1, [r5, #4]
	mov r0, #0x11
	bl NARC_ctor
	add r4, r0, #0
	mov r0, #0x13
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #4]
	add r2, r4, #0
	mov r3, #0x11
	bl FUN_02079B60
	mov r0, #0x14
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #4]
	add r2, r4, #0
	mov r3, #0x11
	bl FUN_02079B60
	mov r0, #0x15
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #4]
	add r2, r4, #0
	mov r3, #0x11
	bl FUN_02079B60
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #4]
	add r2, r4, #0
	mov r3, #0x11
	bl FUN_02079B60
	mov r0, #1
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	ldr r1, [r5, #4]
	add r2, r4, #0
	mov r3, #0x11
	bl FUN_02079B60
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x18
	add r3, #0xb8
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0x98
	str r0, [r1]
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x16
	add r3, #0xbc
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0x9c
	str r0, [r1]
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x17
	add r3, #0xc0
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0xa0
	str r0, [r1]
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x19
	add r3, #0xc4
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0xa4
	str r0, [r1]
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x1a
	add r3, #0xc8
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0xa8
	str r0, [r1]
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x1b
	add r3, #0xcc
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0xac
	str r0, [r1]
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x1c
	add r3, #0xd0
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0xb0
	str r0, [r1]
	ldr r0, [r5, #4]
	add r3, r5, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x11
	mov r2, #0x1d
	add r3, #0xd4
	bl FUN_02079C40
	add r1, r5, #0
	add r1, #0xb4
	str r0, [r1]
	add r0, r4, #0
	bl NARC_dtor
	mov r1, #0x1e
	ldr r2, [r5, #4]
	mov r0, #0
	lsl r1, r1, #4
	bl FUN_02002ED0
	mov r1, #0x1e
	ldr r2, [r5, #4]
	mov r0, #4
	lsl r1, r1, #4
	bl FUN_02002ED0
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD66_021D78B4

	thumb_func_start MOD66_021D7A34
MOD66_021D7A34: ; 0x021D7A34
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xb4
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xac
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl FreeToHeap
	add r4, #0x98
	ldr r0, [r4]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD66_021D7A34

	thumb_func_start MOD66_021D7A88
MOD66_021D7A88: ; 0x021D7A88
	push {r4, lr}
	add r4, r0, #0
	bl MOD66_021D7628
	cmp r0, #1
	beq _021D7A98
	mov r0, #0
	pop {r4, pc}
_021D7A98:
	ldrb r2, [r4]
	mov r1, #0x24
	add r0, r4, #0
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7AAC ; =0x021D95C8
	ldr r1, [r1, r3]
	blx r1
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D7AAC: .word MOD66_021D95C8
	thumb_func_end MOD66_021D7A88

	thumb_func_start MOD66_021D7AB0
MOD66_021D7AB0: ; 0x021D7AB0
	push {r4, lr}
	add r4, r0, #0
	ldrb r2, [r4]
	mov r1, #0x24
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7AE0 ; =0x021D95CC
	ldr r1, [r1, r3]
	blx r1
	cmp r0, #1
	beq _021D7ACA
	mov r0, #1
	pop {r4, pc}
_021D7ACA:
	ldrb r2, [r4]
	mov r1, #0x24
	add r0, r4, #0
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7AE4 ; =0x021D95D0
	ldr r1, [r1, r3]
	blx r1
	mov r0, #3
	pop {r4, pc}
	nop
_021D7AE0: .word MOD66_021D95CC
_021D7AE4: .word MOD66_021D95D0
	thumb_func_end MOD66_021D7AB0

	thumb_func_start MOD66_021D7AE8
MOD66_021D7AE8: ; 0x021D7AE8
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7AF6
	mov r0, #4
	pop {r3, pc}
_021D7AF6:
	mov r0, #3
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD66_021D7AE8

	thumb_func_start MOD66_021D7AFC
MOD66_021D7AFC: ; 0x021D7AFC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x38]
	blx r1
	cmp r0, #1
	beq _021D7B1C
	ldrb r2, [r4]
	mov r1, #0x24
	add r0, r4, #0
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7B30 ; =0x021D95DC
	ldr r1, [r1, r3]
	blx r1
	mov r0, #4
	pop {r4, pc}
_021D7B1C:
	ldrb r2, [r4]
	mov r1, #0x24
	add r0, r4, #0
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7B34 ; =0x021D95D4
	ldr r1, [r1, r3]
	blx r1
	mov r0, #6
	pop {r4, pc}
	.align 2, 0
_021D7B30: .word MOD66_021D95DC
_021D7B34: .word MOD66_021D95D4
	thumb_func_end MOD66_021D7AFC

	thumb_func_start MOD66_021D7B38
MOD66_021D7B38: ; 0x021D7B38
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7B76
	mov r1, #0
	ldr r0, _021D7B8C ; =0x04000050
	add r2, r1, #0
	mov r3, #0x1f
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	add sp, #4
	mov r0, #8
	pop {r3, r4, pc}
_021D7B76:
	ldrb r2, [r4]
	mov r1, #0x24
	add r0, r4, #0
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7B90 ; =0x021D95DC
	ldr r1, [r1, r3]
	blx r1
	mov r0, #6
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D7B8C: .word 0x04000050
_021D7B90: .word MOD66_021D95DC
	thumb_func_end MOD66_021D7B38

	thumb_func_start MOD66_021D7B94
MOD66_021D7B94: ; 0x021D7B94
	push {r4, lr}
	add r4, r0, #0
	ldrb r2, [r4]
	mov r1, #0x24
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D7BB0 ; =0x021D95E4
	ldr r1, [r1, r3]
	blx r1
	add r0, r4, #0
	bl MOD66_021D7750
	mov r0, #7
	pop {r4, pc}
	.align 2, 0
_021D7BB0: .word MOD66_021D95E4
	thumb_func_end MOD66_021D7B94

	thumb_func_start MOD66_021D7BB4
MOD66_021D7BB4: ; 0x021D7BB4
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0x11
	ldr r0, [r4, #4]
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #4
	str r0, [r4, #0x34]
	bl memset
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD66_021D7BB4

	thumb_func_start MOD66_021D7BD4
MOD66_021D7BD4: ; 0x021D7BD4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x34]
	bl MOD66_021D89B8
	ldrb r0, [r5]
	cmp r0, #2
	beq _021D7BEA
	add r0, r5, #0
	bl MOD66_021D8E34
_021D7BEA:
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl MOD66_021D9350
	add r0, r5, #0
	bl MOD66_021D8670
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD66_021D7BD4

	thumb_func_start MOD66_021D7C04
MOD66_021D7C04: ; 0x021D7C04
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x34]
	ldr r1, [r4]
	cmp r1, #0
	beq _021D7C16
	cmp r1, #1
	beq _021D7C60
	b _021D7CA2
_021D7C16:
	ldr r1, [r5, #0x18]
	str r1, [r4, #0x18]
	ldr r1, [r5, #0x1c]
	str r1, [r4, #0x1c]
	mov r1, #0
	mvn r1, r1
	str r1, [r4, #0x20]
	ldr r1, [r4, #0x18]
	lsl r2, r1, #4
	add r1, r4, #0
	sub r2, #0x68
	add r1, #0x8c
	str r2, [r1]
	ldr r1, [r4, #0x1c]
	lsl r2, r1, #4
	add r1, r4, #0
	sub r2, #0x60
	add r1, #0x90
	str r2, [r1]
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x8c
	add r2, #0x90
	ldr r1, [r1]
	ldr r2, [r2]
	bl MOD66_021D8BF0
	add r0, r5, #0
	bl MOD66_021D8554
	ldrb r0, [r5]
	cmp r0, #2
	beq _021D7CA2
	add r0, r5, #0
	bl MOD66_021D8CD0
	b _021D7CA2
_021D7C60:
	bl MOD66_021D8838
	add r0, r5, #0
	bl MOD66_021D8AF4
	ldr r0, [r5, #4]
	add r1, r5, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	mov r2, #0x49
	ldr r3, [r5, #0x2c]
	lsl r2, r2, #2
	add r2, r3, r2
	ldr r0, [r0]
	ldr r1, [r1]
	mov r3, #0x14
	bl MOD66_021D9228
	add r1, r4, #0
	add r1, #0x9c
	str r0, [r1]
	add r0, r5, #0
	bl MOD66_021D818C
	add r0, r5, #0
	bl MOD66_021D8140
	mov r0, #0
	str r0, [r4]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7CA2:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD66_021D7C04

	thumb_func_start MOD66_021D7CAC
MOD66_021D7CAC: ; 0x021D7CAC
	push {lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [r0, #0x14]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, [r0, #4]
	mov r2, #0x25
	str r0, [sp, #8]
	add r0, r1, #0
	mov r1, #0x11
	bl FUN_0200E1D0
	ldr r0, _021D7CF0 ; =0x0000068F
	bl FUN_020054C8
	mov r0, #0
	bl FUN_0200E394
	mov r0, #1
	bl FUN_0200E394
	mov r1, #4
	ldr r0, _021D7CF4 ; =0x04000050
	mov r2, #8
	mov r3, #0x1c
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	mov r0, #0
	add sp, #0xc
	pop {pc}
	.align 2, 0
_021D7CF0: .word 0x0000068F
_021D7CF4: .word 0x04000050
	thumb_func_end MOD66_021D7CAC

	thumb_func_start MOD66_021D7CF8
MOD66_021D7CF8: ; 0x021D7CF8
	push {lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [r0, #0x14]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, [r0, #4]
	mov r1, #0x10
	str r0, [sp, #8]
	mov r0, #2
	mov r2, #0x24
	bl FUN_0200E1D0
	mov r0, #0x69
	lsl r0, r0, #4
	bl FUN_020054C8
	mov r0, #0
	add sp, #0xc
	pop {pc}
	thumb_func_end MOD66_021D7CF8

	thumb_func_start MOD66_021D7D24
MOD66_021D7D24: ; 0x021D7D24
	push {lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [r0, #0x14]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, [r0, #4]
	mov r1, #0x11
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, _021D7D64 ; =0x0000068F
	bl FUN_020054C8
	mov r0, #0
	bl FUN_0200E394
	mov r1, #4
	ldr r0, _021D7D68 ; =0x04000050
	mov r2, #8
	mov r3, #0x1c
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	mov r0, #0
	add sp, #0xc
	pop {pc}
	nop
_021D7D64: .word 0x0000068F
_021D7D68: .word 0x04000050
	thumb_func_end MOD66_021D7D24

	thumb_func_start MOD66_021D7D6C
MOD66_021D7D6C: ; 0x021D7D6C
	push {lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [r0, #0x14]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, [r0, #4]
	mov r1, #0x10
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #0x69
	lsl r0, r0, #4
	bl FUN_020054C8
	mov r0, #0
	add sp, #0xc
	pop {pc}
	thumb_func_end MOD66_021D7D6C

	thumb_func_start MOD66_021D7D98
MOD66_021D7D98: ; 0x021D7D98
	push {r3, lr}
	ldr r1, [r0, #0x34]
	ldrb r3, [r1, #0x14]
	cmp r3, #1
	bhi _021D7DB6
	ldr r1, _021D7DCC ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #2
	tst r1, r2
	beq _021D7DB6
	ldr r0, _021D7DD0 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #1
	pop {r3, pc}
_021D7DB6:
	cmp r3, #1
	bls _021D7DBE
	mov r0, #0
	pop {r3, pc}
_021D7DBE:
	ldr r1, _021D7DCC ; =gMain
	ldr r1, [r1, #0x44]
	bl MOD66_021D8054
	mov r0, #0
	pop {r3, pc}
	nop
_021D7DCC: .word gMain
_021D7DD0: .word 0x000005DD
	thumb_func_end MOD66_021D7D98

	thumb_func_start MOD66_021D7DD4
MOD66_021D7DD4: ; 0x021D7DD4
	push {r3, lr}
	ldr r1, [r0, #0x34]
	ldrb r1, [r1, #0x14]
	cmp r1, #1
	bhi _021D7E0E
	ldr r2, _021D7E24 ; =gMain
	ldr r3, [r2, #0x48]
	mov r2, #1
	tst r2, r3
	beq _021D7DFE
	bl MOD66_021D90F0
	cmp r0, #0
	beq _021D7DFA
	ldr r0, _021D7E28 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #1
	pop {r3, pc}
_021D7DFA:
	mov r0, #0
	pop {r3, pc}
_021D7DFE:
	mov r2, #2
	tst r2, r3
	beq _021D7E0E
	ldr r0, _021D7E28 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #1
	pop {r3, pc}
_021D7E0E:
	cmp r1, #1
	bls _021D7E16
	mov r0, #0
	pop {r3, pc}
_021D7E16:
	ldr r1, _021D7E24 ; =gMain
	ldr r1, [r1, #0x44]
	bl MOD66_021D8054
	mov r0, #0
	pop {r3, pc}
	nop
_021D7E24: .word gMain
_021D7E28: .word 0x000005DD
	thumb_func_end MOD66_021D7DD4

	thumb_func_start MOD66_021D7E2C
MOD66_021D7E2C: ; 0x021D7E2C
	push {r3, lr}
	ldr r2, _021D7E4C ; =gMain
	mov r1, #2
	ldr r3, [r2, #0x48]
	tst r1, r3
	beq _021D7E42
	ldr r0, _021D7E50 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #1
	pop {r3, pc}
_021D7E42:
	ldr r1, [r2, #0x44]
	bl MOD66_021D8054
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021D7E4C: .word gMain
_021D7E50: .word 0x000005DD
	thumb_func_end MOD66_021D7E2C

	thumb_func_start MOD66_021D7E54
MOD66_021D7E54: ; 0x021D7E54
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x34]
	mov r1, #1
	ldrb r2, [r4, #0x12]
	tst r1, r2
	beq _021D7E80
	ldrb r1, [r4, #0x15]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, #2
	blo _021D7E94
	bl MOD66_021D8140
	mov r0, #0
	strb r0, [r4, #0x12]
	strh r0, [r4, #0x16]
	ldrb r1, [r4, #0x15]
	mov r0, #0xf
	bic r1, r0
	strb r1, [r4, #0x15]
	b _021D7E94
_021D7E80:
	ldrb r1, [r4, #0x10]
	cmp r1, #1
	bne _021D7E94
	ldrh r1, [r4, #0x16]
	cmp r1, #1
	bne _021D7E94
	ldr r2, [r4, #0x20]
	mov r1, #0
	bl MOD66_021D8480
_021D7E94:
	add r0, r5, #0
	bl MOD66_021D8380
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD66_021D7E54

	thumb_func_start MOD66_021D7EA0
MOD66_021D7EA0: ; 0x021D7EA0
	push {r3, lr}
	add r1, r0, #0
	ldr r0, [r1, #0x34]
	ldrb r1, [r1]
	add r0, #0x9c
	ldr r0, [r0]
	bl MOD66_021D945C
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD66_021D7EA0

	thumb_func_start MOD66_021D7EB4
MOD66_021D7EB4: ; 0x021D7EB4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r1, r6, #0
	add r1, #0x94
	ldr r5, [r1]
	add r1, r6, #0
	add r1, #0x90
	ldr r7, [r1]
	add r1, r6, #0
	add r1, #0x8c
	ldr r1, [r1]
	ldr r4, [r6, #0x34]
	cmp r1, #0
	bne _021D7ED8
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D7ED8:
	add r1, r6, #0
	mov r2, #0
	add r1, #0x8c
	str r2, [r1]
	cmp r5, #0
	bne _021D7EF8
	add r4, #0x58
	add r1, r4, #0
	bl MOD66_021D82B8
	add r0, r6, #0
	bl MOD66_021D8494
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D7EF8:
	add r1, r4, #0
	add r1, #0x58
	add r2, r5, #0
	bl MOD66_021D82B8
	add r0, r6, #0
	add r0, #0x88
	ldr r0, [r0]
	bl StringSetEmpty
	ldr r2, [r4, #0x18]
	ldr r3, [r4, #0x1c]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD66_021D81B4
	ldrh r0, [r5, #4]
	ldr r2, _021D7FA0 ; =0x0000013B
	mov r1, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrh r0, [r5, #6]
	mov r3, #0xe
	str r0, [sp, #4]
	ldr r0, [r6, #4]
	str r0, [sp, #8]
	ldr r0, [r6, #0x28]
	bl FUN_0200D300
	ldrh r0, [r5, #4]
	cmp r0, #1
	bhi _021D7F40
	add r7, r4, #0
	add r7, #0x38
	b _021D7F44
_021D7F40:
	add r7, r4, #0
	add r7, #0x48
_021D7F44:
	str r7, [r4, #0x78]
	ldrb r0, [r4, #0x15]
	mov r1, #0xf0
	ldr r2, _021D7FA0 ; =0x0000013B
	bic r0, r1
	ldrh r1, [r5, #4]
	mov r3, #0xe
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r4, #0x15]
	ldrh r0, [r5, #4]
	mov r1, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	add r0, r7, #0
	bl FUN_0200D6F8
	add r0, r7, #0
	mov r1, #0xf
	bl FUN_02019620
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r6, #0x88
	ldr r2, [r6]
	add r0, r7, #0
	mov r1, #1
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl CopyWindowToVram
	add r4, #0x58
	add r0, r4, #0
	bl CopyWindowToVram
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7FA0: .word 0x0000013B
	thumb_func_end MOD66_021D7EB4

	thumb_func_start MOD66_021D7FA4
MOD66_021D7FA4: ; 0x021D7FA4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #1
	sub r0, r0, r6
	ldr r1, _021D7FF4 ; =0x021D9720
	lsl r0, r0, #2
	add r0, r1, r0
	bl FUN_02020988
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _021D7FC8
	cmp r6, #1
	bne _021D7FCE
_021D7FC8:
	add sp, #8
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021D7FCE:
	mov r1, #0x12
	add r0, sp, #4
	strh r1, [r0]
	add r0, sp, #4
	str r0, [sp]
	ldr r3, _021D7FF8 ; =gMain + 0x40
	ldr r0, [r5, #0x28]
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #5
	bl FUN_0201AFBC
	cmp r0, #0
	beq _021D7FEE
	mov r4, #0
	mvn r4, r4
_021D7FEE:
	add r0, r4, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D7FF4: .word MOD66_021D9720
_021D7FF8: .word gMain + 0x40
	thumb_func_end MOD66_021D7FA4

	thumb_func_start MOD66_021D7FFC
MOD66_021D7FFC: ; 0x021D7FFC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5, #0x2c]
	ldr r0, _021D8050 ; =0x00000139
	ldr r4, [r5, #0x34]
	ldrb r0, [r1, r0]
	cmp r0, #2
	bne _021D8010
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8010:
	bl FUN_02020A98
	cmp r0, #0
	ldrb r0, [r4, #0x14]
	beq _021D803E
	cmp r0, #0
	bne _021D804C
	ldrb r1, [r4, #0x10]
	add r0, r5, #0
	bl MOD66_021D7FA4
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _021D804C
	ldrb r1, [r4, #0x10]
	add r0, r5, #0
	bl MOD66_021D8E70
	mov r0, #3
	strb r0, [r4, #0x14]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D803E:
	cmp r0, #3
	beq _021D8046
	cmp r0, #1
	bne _021D804C
_021D8046:
	ldrb r0, [r4, #0x14]
	sub r0, r0, #1
	strb r0, [r4, #0x14]
_021D804C:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8050: .word 0x00000139
	thumb_func_end MOD66_021D7FFC

	thumb_func_start MOD66_021D8054
MOD66_021D8054: ; 0x021D8054
	push {r3, r4, r5, lr}
	ldr r4, [r0, #0x34]
	add r5, r1, #0
	ldrb r1, [r4, #0x11]
	cmp r1, #0
	beq _021D8084
	mov r0, #0xf0
	tst r0, r5
	bne _021D813C
	ldrb r2, [r4, #0x15]
	lsl r0, r2, #0x1c
	lsr r1, r0, #0x1c
	cmp r1, #1
	bne _021D813C
	mov r0, #0xf
	bic r2, r0
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0xf
	and r0, r1
	orr r0, r2
	strb r0, [r4, #0x15]
	pop {r3, r4, r5, pc}
_021D8084:
	bl MOD66_021D7FFC
	cmp r0, #0
	bne _021D813C
	mov r0, #0xf0
	tst r0, r5
	bne _021D80B0
	ldrb r2, [r4, #0x15]
	lsl r0, r2, #0x1c
	lsr r1, r0, #0x1c
	cmp r1, #1
	bne _021D813C
	mov r0, #0xf
	bic r2, r0
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0xf
	and r0, r1
	orr r0, r2
	strb r0, [r4, #0x15]
	pop {r3, r4, r5, pc}
_021D80B0:
	mov r0, #0x40
	tst r0, r5
	beq _021D80C8
	ldr r0, [r4, #0x1c]
	cmp r0, #7
	blt _021D80C8
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	ldrb r1, [r4, #0x11]
	mov r0, #8
	orr r0, r1
	strb r0, [r4, #0x11]
_021D80C8:
	mov r0, #0x80
	tst r0, r5
	beq _021D80E0
	ldr r0, [r4, #0x1c]
	cmp r0, #0x1b
	bgt _021D80E0
	add r0, r0, #1
	str r0, [r4, #0x1c]
	ldrb r1, [r4, #0x11]
	mov r0, #4
	orr r0, r1
	strb r0, [r4, #0x11]
_021D80E0:
	mov r0, #0x10
	tst r0, r5
	beq _021D80F8
	ldr r0, [r4, #0x18]
	cmp r0, #0x1b
	bgt _021D80F8
	add r0, r0, #1
	str r0, [r4, #0x18]
	ldrb r1, [r4, #0x11]
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #0x11]
_021D80F8:
	mov r0, #0x20
	tst r0, r5
	beq _021D8110
	ldr r0, [r4, #0x18]
	cmp r0, #2
	blt _021D8110
	sub r0, r0, #1
	str r0, [r4, #0x18]
	ldrb r1, [r4, #0x11]
	mov r0, #2
	orr r0, r1
	strb r0, [r4, #0x11]
_021D8110:
	mov r0, #3
	strb r0, [r4, #0x13]
	ldrb r1, [r4, #0x11]
	mov r0, #0x80
	orr r0, r1
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _021D8128
	ldrh r0, [r4, #0x16]
	add r0, r0, #1
	b _021D812A
_021D8128:
	mov r0, #0
_021D812A:
	strh r0, [r4, #0x16]
	mov r0, #0
	strb r0, [r4, #0x12]
	ldrb r1, [r4, #0x15]
	mov r0, #0xf
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #0x15]
_021D813C:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD66_021D8054

	thumb_func_start MOD66_021D8140
MOD66_021D8140: ; 0x021D8140
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x34]
	ldr r1, [r4, #0x1c]
	str r1, [sp]
	add r1, r4, #0
	ldr r2, [r4, #0x20]
	ldr r3, [r4, #0x18]
	add r1, #0x28
	bl MOD66_021D820C
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x18]
	ldr r3, [r4, #0x1c]
	bl MOD66_021D93F4
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _021D818A
	add r1, r4, #0
	add r1, #0xa0
	ldr r1, [r1]
	ldr r2, [r4, #0x20]
	add r0, r5, #0
	bl MOD66_021D8480
	ldr r0, [r5, #0x28]
	mov r1, #4
	bl FUN_0201AC68
	ldr r0, [r5, #0x28]
	mov r1, #5
	bl FUN_0201AC68
_021D818A:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD66_021D8140

	thumb_func_start MOD66_021D818C
MOD66_021D818C: ; 0x021D818C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x34]
	ldr r0, [r4, #0x20]
	str r0, [r4, #0x24]
	ldr r0, [r5, #0x30]
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x1c]
	bl FUN_020345F0
	str r0, [r4, #0x20]
	ldrh r3, [r5, #2]
	ldr r0, [r5, #0x40]
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x1c]
	bl MOD66_021D9558
	add r4, #0xa0
	str r0, [r4]
	pop {r3, r4, r5, pc}
	thumb_func_end MOD66_021D818C

	thumb_func_start MOD66_021D81B4
MOD66_021D81B4: ; 0x021D81B4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	cmp r1, #0
	beq _021D81CA
	add r0, r1, #0
	ldr r1, [r4, #4]
	add r4, #0x88
	ldr r2, [r4]
	bl FUN_02064E60
	pop {r3, r4, r5, pc}
_021D81CA:
	ldr r5, _021D8204 ; =0x021D97B4
	mov r1, #0
_021D81CE:
	ldrh r0, [r5]
	cmp r2, r0
	bne _021D81EC
	ldrh r0, [r5, #2]
	cmp r3, r0
	bne _021D81EC
	ldr r0, _021D8208 ; =0x021D97B8
	lsl r1, r1, #3
	ldr r0, [r0, r1]
	ldr r1, [r4, #4]
	add r4, #0x88
	ldr r2, [r4]
	bl FUN_02064E60
	pop {r3, r4, r5, pc}
_021D81EC:
	add r1, r1, #1
	add r5, #8
	cmp r1, #0xd
	blo _021D81CE
	ldr r1, [r4, #4]
	add r4, #0x88
	ldr r2, [r4]
	mov r0, #0
	bl FUN_02064E60
	pop {r3, r4, r5, pc}
	nop
_021D8204: .word MOD66_021D97B4
_021D8208: .word MOD66_021D97B8
	thumb_func_end MOD66_021D81B4

	thumb_func_start MOD66_021D820C
MOD66_021D820C: ; 0x021D820C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r0, #0x88
	ldr r0, [r0]
	add r4, r1, #0
	ldr r6, [r5, #0x34]
	add r7, r2, #0
	str r3, [sp, #0x10]
	bl StringSetEmpty
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	add r6, #0xa0
	ldr r0, [r6]
	cmp r0, #0
	beq _021D8278
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x28]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD66_021D81B4
	ldrb r0, [r5]
	cmp r0, #1
	bne _021D8248
	mov r3, #0x7a
	b _021D825C
_021D8248:
	add r1, r5, #0
	add r1, #0x88
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xd0
	sub r0, r1, r0
	lsr r3, r0, #1
_021D825C:
	mov r0, #6
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D82B4 ; =0x00010200
	add r2, r5, #0
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	add r2, #0x88
	ldr r2, [r2]
	add r0, r4, #0
	bl AddTextPrinterParameterized2
_021D8278:
	ldrb r0, [r5]
	cmp r0, #1
	bne _021D82AA
	add r5, #0x84
	ldr r0, [r5]
	mov r1, #0
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D82B4 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl String_dtor
_021D82AA:
	add r0, r4, #0
	bl CopyWindowToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D82B4: .word 0x00010200
	thumb_func_end MOD66_021D820C

	thumb_func_start MOD66_021D82B8
MOD66_021D82B8: ; 0x021D82B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	bne _021D82DC
	add r0, r6, #0
	mov r1, #0
	bl FUN_02019620
	add r0, r6, #0
	bl CopyWindowToVram
	add r0, r6, #0
	bl FUN_02019570
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_021D82DC:
	add r0, r6, #0
	mov r1, #0
	bl FUN_02019620
	ldrh r1, [r4, #8]
	ldr r0, _021D8378 ; =0x0000FFFF
	cmp r1, r0
	beq _021D832C
	ldr r2, [r5, #0x2c]
	ldrh r0, [r4, #0x16]
	add r2, #0x5c
	ldrb r0, [r2, r0]
	lsl r2, r0, #0x1e
	lsr r2, r2, #0x1e
	beq _021D8300
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1e
	beq _021D832C
_021D8300:
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	bl NewString_ReadMsgData
	add r7, r0, #0
	ldrh r0, [r4, #0xe]
	mov r1, #0
	add r2, r7, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D837C ; =0x00010200
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldrh r3, [r4, #0xc]
	add r0, r6, #0
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
_021D832C:
	ldrh r1, [r4, #0xa]
	ldr r0, _021D8378 ; =0x0000FFFF
	cmp r1, r0
	beq _021D8372
	ldr r2, [r5, #0x2c]
	ldrh r0, [r4, #0x16]
	add r2, #0x5c
	ldrb r0, [r2, r0]
	lsl r2, r0, #0x1a
	lsr r2, r2, #0x1e
	beq _021D8348
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	beq _021D8372
_021D8348:
	add r5, #0x84
	ldr r0, [r5]
	bl NewString_ReadMsgData
	add r5, r0, #0
	ldrh r0, [r4, #0x12]
	mov r1, #0
	add r2, r5, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D837C ; =0x00010200
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldrh r3, [r4, #0x10]
	add r0, r6, #0
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl String_dtor
_021D8372:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8378: .word 0x0000FFFF
_021D837C: .word 0x00010200
	thumb_func_end MOD66_021D82B8

	thumb_func_start MOD66_021D8380
MOD66_021D8380: ; 0x021D8380
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	ldr r5, [r6, #0x34]
	mov r4, #5
	ldrb r1, [r5, #0x13]
	cmp r1, #0
	beq _021D847C
	sub r0, r1, #1
	strb r0, [r5, #0x13]
	cmp r1, #3
	bne _021D83F0
	ldr r1, [r5, #0x18]
	add r0, r4, #0
	mov r2, #7
	add r3, r1, #0
	mul r3, r2
	add r3, #0x19
	lsl r1, r3, #0x10
	ldr r3, [r5, #0x1c]
	add r0, #0xff
	mul r2, r3
	sub r2, #0x22
	lsl r2, r2, #0x10
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	add r0, r4, #0
	add r0, #0xff
	mov r1, #1
	ldr r0, [r5, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	add r0, r6, #0
	bl MOD66_021D818C
	ldr r0, [r5, #0x18]
	ldr r7, [r5, #0x1c]
	str r0, [sp, #4]
	ldr r0, [r6, #0x30]
	ldr r1, [sp, #4]
	add r2, r7, #0
	bl FUN_020345F0
	add r1, r5, #0
	add r2, r0, #0
	ldr r3, [sp, #4]
	add r0, r6, #0
	add r1, #0x28
	str r7, [sp]
	bl MOD66_021D820C
	add r4, r4, #1
_021D83F0:
	ldrb r1, [r5, #0x11]
	mov r0, #8
	tst r0, r1
	beq _021D8406
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	sub r1, r0, r4
	add r0, r5, #0
	add r0, #0x90
	str r1, [r0]
_021D8406:
	ldrb r1, [r5, #0x11]
	mov r0, #4
	tst r0, r1
	beq _021D841C
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	add r1, r0, r4
	add r0, r5, #0
	add r0, #0x90
	str r1, [r0]
_021D841C:
	ldrb r1, [r5, #0x11]
	mov r0, #1
	tst r0, r1
	beq _021D8432
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r0, r4
	add r0, r5, #0
	add r0, #0x8c
	str r1, [r0]
_021D8432:
	ldrb r1, [r5, #0x11]
	mov r0, #2
	tst r0, r1
	beq _021D8448
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	sub r1, r0, r4
	add r0, r5, #0
	add r0, #0x8c
	str r1, [r0]
_021D8448:
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0x8c
	add r2, #0x90
	ldr r1, [r1]
	ldr r2, [r2]
	add r0, r6, #0
	bl MOD66_021D8BF0
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	bne _021D847C
	mov r0, #1
	strb r0, [r5, #0x12]
	mov r2, #0
	strb r2, [r5, #0x11]
	ldr r1, [r5, #0x24]
	ldr r0, [r5, #0x20]
	cmp r1, r0
	beq _021D847C
	add r5, #0x9c
	ldr r0, [r5]
	sub r1, r2, #1
	add r3, r2, #0
	bl MOD66_021D93F4
_021D847C:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD66_021D8380

	thumb_func_start MOD66_021D8480
MOD66_021D8480: ; 0x021D8480
	add r3, r0, #0
	add r3, #0x90
	str r2, [r3]
	add r2, r0, #0
	add r2, #0x94
	str r1, [r2]
	mov r1, #1
	add r0, #0x8c
	str r1, [r0]
	bx lr
	thumb_func_end MOD66_021D8480

	thumb_func_start MOD66_021D8494
MOD66_021D8494: ; 0x021D8494
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r4, [r6, #0x34]
	mov r1, #0
	ldr r5, [r4, #0x78]
	str r1, [r4, #0x78]
	cmp r5, #0
	beq _021D84C6
	add r0, r5, #0
	bl FUN_02019620
	add r0, r5, #0
	bl FUN_02019570
	ldrb r1, [r4, #0x15]
	add r0, r5, #0
	mov r2, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	bl FUN_0200D7A0
	ldr r0, [r6, #0x28]
	mov r1, #4
	bl FUN_0201AC68
_021D84C6:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD66_021D8494

	thumb_func_start MOD66_021D84C8
MOD66_021D84C8: ; 0x021D84C8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r0, #0
	add r0, #0xcc
	add r5, r1, #0
	ldr r0, [r0]
	mov r1, #0xc
	str r1, [sp]
	mov r1, #2
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	mov r3, #0
	str r3, [sp, #0xc]
	mov r1, #7
	str r1, [sp, #0x10]
	ldrh r1, [r0]
	mov r2, #0xa
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #5
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x28]
	bl FUN_020181EC
	add r4, #0x84
	ldr r0, [r4]
	mov r1, #1
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x50
	sub r4, r1, r0
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8550 ; =0x00010200
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r5, #0
	lsr r3, r4, #1
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl CopyWindowToVram
	add r0, r6, #0
	bl String_dtor
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_021D8550: .word 0x00010200
	thumb_func_end MOD66_021D84C8

	thumb_func_start MOD66_021D8554
MOD66_021D8554: ; 0x021D8554
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r4, [r5, #0x34]
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1d
	str r0, [sp, #4]
	mov r3, #3
	str r3, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	mov r0, #0xea
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	add r1, r4, #0
	ldr r0, [r5, #0x28]
	add r1, #0x28
	mov r2, #1
	bl FUN_02019064
	mov r0, #3
	str r0, [sp]
	mov r0, #0x15
	str r0, [sp, #4]
	mov r2, #4
	add r1, r4, #0
	str r2, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	ldr r0, _021D8660 ; =0x000003AB
	add r1, #0x38
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	mov r3, #9
	bl FUN_02019064
	mov r0, #3
	str r0, [sp]
	mov r0, #0x1c
	str r0, [sp, #4]
	mov r2, #4
	add r1, r4, #0
	str r2, [sp, #8]
	mov r0, #0xe
	str r0, [sp, #0xc]
	ldr r0, _021D8664 ; =0x0000033B
	add r1, #0x48
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	mov r3, #2
	bl FUN_02019064
	mov r0, #8
	str r0, [sp]
	mov r0, #0x1c
	str r0, [sp, #4]
	mov r0, #0xe
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _021D8668 ; =0x000001B3
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	add r1, #0x58
	mov r2, #4
	mov r3, #1
	bl FUN_02019064
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	ldr r0, _021D866C ; =0x0000019F
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x28]
	add r1, #0x68
	mov r2, #4
	mov r3, #0xb
	bl FUN_02019064
	add r0, r4, #0
	add r0, #0x28
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x38
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x68
	mov r1, #0
	bl FUN_02019620
	add r0, r4, #0
	add r0, #0x28
	bl CopyWindowToVram
	add r0, r4, #0
	add r0, #0x38
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0x48
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0x58
	bl FUN_02019570
	add r4, #0x68
	add r0, r4, #0
	bl FUN_02019570
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021D8660: .word 0x000003AB
_021D8664: .word 0x0000033B
_021D8668: .word 0x000001B3
_021D866C: .word 0x0000019F
	thumb_func_end MOD66_021D8554

	thumb_func_start MOD66_021D8670
MOD66_021D8670: ; 0x021D8670
	push {r3, r4, r5, lr}
	ldr r4, [r0, #0x34]
	mov r5, #0
	add r4, #0x28
_021D8678:
	lsl r0, r5, #4
	add r0, r4, r0
	bl FUN_02019178
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #5
	blo _021D8678
	pop {r3, r4, r5, pc}
	thumb_func_end MOD66_021D8670

	thumb_func_start MOD66_021D868C
MOD66_021D868C: ; 0x021D868C
	push {r4, r5, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r4, r1, #0
	cmp r2, #0
	beq _021D86CA
	add r0, #0xd0
	ldr r0, [r0]
	mov r1, #0x20
	str r1, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	mov r2, #0
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldrh r1, [r0]
	add r3, r2, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #5
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x28]
	bl FUN_02018170
_021D86CA:
	add r0, r5, #0
	add r0, #0xcc
	ldr r0, [r0]
	mov r2, #6
	str r2, [sp]
	mov r1, #7
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	add r1, r4, #0
	mul r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	ldrh r1, [r0]
	mov r2, #0xd
	mov r3, #0xa
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #5
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x28]
	bl FUN_020181EC
	add sp, #0x1c
	pop {r4, r5, pc}
	thumb_func_end MOD66_021D868C

	thumb_func_start MOD66_021D870C
MOD66_021D870C: ; 0x021D870C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	lsl r0, r1, #2
	str r1, [sp, #0x1c]
	mov r1, #6
	add r2, r0, #0
	mul r2, r1
	ldr r1, _021D8834 ; =0x021D9754
	add r3, r0, #1
	add r6, r1, r2
	mov r1, #6
	add r2, r3, #0
	mul r2, r1
	ldr r1, _021D8834 ; =0x021D9754
	mov r4, #6
	add r3, r1, r2
	add r1, r0, #2
	mul r4, r1
	ldr r1, _021D8834 ; =0x021D9754
	add r0, r0, #3
	add r4, r1, r4
	mov r1, #6
	mul r1, r0
	ldr r0, _021D8834 ; =0x021D9754
	str r1, [sp, #0x20]
	add r7, r0, r1
	add r0, r5, #0
	add r0, #0xc0
	ldrb r1, [r3, #4]
	ldr r0, [r0]
	str r1, [sp]
	ldrb r1, [r3, #5]
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	ldr r1, _021D8834 ; =0x021D9754
	ldrb r1, [r1, r2]
	str r1, [sp, #0xc]
	ldrb r1, [r3, #1]
	str r1, [sp, #0x10]
	ldrh r1, [r0]
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #2
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldrb r2, [r3, #2]
	ldrb r3, [r3, #3]
	ldr r0, [r5, #0x28]
	bl FUN_02018170
	add r0, r5, #0
	add r0, #0xd4
	ldrb r1, [r7, #4]
	ldr r0, [r0]
	ldr r2, _021D8834 ; =0x021D9754
	str r1, [sp]
	ldrb r1, [r7, #5]
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	ldr r1, [sp, #0x20]
	ldrb r1, [r2, r1]
	str r1, [sp, #0xc]
	ldrb r1, [r7, #1]
	str r1, [sp, #0x10]
	ldrh r1, [r0]
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #6
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldrb r2, [r7, #2]
	ldrb r3, [r7, #3]
	ldr r0, [r5, #0x28]
	bl FUN_020181EC
	ldr r0, [sp, #0x1c]
	cmp r0, #2
	beq _021D882E
	add r0, r5, #0
	add r0, #0xc0
	ldrb r1, [r6, #4]
	ldr r0, [r0]
	str r1, [sp]
	ldrb r1, [r6, #5]
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	ldrb r1, [r6]
	str r1, [sp, #0xc]
	ldrb r1, [r6, #1]
	str r1, [sp, #0x10]
	ldrh r1, [r0]
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #3
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldrb r2, [r6, #2]
	ldrb r3, [r6, #3]
	ldr r0, [r5, #0x28]
	bl FUN_02018170
	add r0, r5, #0
	add r0, #0xd4
	ldrb r1, [r4, #4]
	ldr r0, [r0]
	str r1, [sp]
	ldrb r1, [r4, #5]
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	ldrb r1, [r4]
	str r1, [sp, #0xc]
	ldrb r1, [r4, #1]
	str r1, [sp, #0x10]
	ldrh r1, [r0]
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #7
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldrb r2, [r4, #2]
	ldrb r3, [r4, #3]
	ldr r0, [r5, #0x28]
	bl FUN_020181EC
_021D882E:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021D8834: .word MOD66_021D9754
	thumb_func_end MOD66_021D870C

	thumb_func_start MOD66_021D8838
MOD66_021D8838: ; 0x021D8838
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	add r0, #0xb8
	ldr r0, [r0]
	mov r1, #0x20
	str r1, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	mov r2, #0
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldrh r1, [r0]
	add r3, r2, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #2
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x28]
	bl FUN_02018170
	add r0, r4, #0
	add r0, #0xbc
	mov r2, #0
	ldr r0, [r0]
	mov r1, #0x20
	str r1, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldrh r1, [r0]
	add r3, r2, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #3
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x28]
	bl FUN_02018170
	ldrb r0, [r4]
	cmp r0, #1
	beq _021D88DE
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	mov r1, #2
	str r1, [sp]
	mov r1, #3
	add r2, r0, #0
	str r1, [sp, #4]
	add r2, #0xc
	str r2, [sp, #8]
	mov r2, #0
	str r2, [sp, #0xc]
	mov r3, #0x15
	str r3, [sp, #0x10]
	ldrh r2, [r0]
	lsl r2, r2, #0x15
	lsr r2, r2, #0x18
	str r2, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r2, #0x10
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x28]
	bl FUN_02018170
_021D88DE:
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MOD66_021D868C
	add r0, r4, #0
	add r0, #0xc8
	mov r2, #0
	ldr r0, [r0]
	mov r1, #0x40
	str r1, [sp]
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldrh r1, [r0]
	add r3, r2, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #6
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x28]
	bl FUN_020181EC
	add r0, r4, #0
	add r0, #0xc4
	mov r2, #0
	ldr r0, [r0]
	mov r1, #0x40
	str r1, [sp]
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldrh r1, [r0]
	add r3, r2, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldrh r0, [r0, #2]
	mov r1, #7
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x28]
	bl FUN_020181EC
	ldrh r1, [r4, #2]
	mov r0, #1
	tst r0, r1
	beq _021D895C
	add r0, r4, #0
	mov r1, #0
	bl MOD66_021D870C
_021D895C:
	ldrh r1, [r4, #2]
	mov r0, #2
	tst r0, r1
	beq _021D896C
	add r0, r4, #0
	mov r1, #1
	bl MOD66_021D870C
_021D896C:
	ldrh r1, [r4, #2]
	mov r0, #4
	tst r0, r1
	beq _021D897C
	add r0, r4, #0
	mov r1, #2
	bl MOD66_021D870C
_021D897C:
	ldrh r1, [r4, #2]
	mov r0, #8
	tst r0, r1
	beq _021D898C
	add r0, r4, #0
	mov r1, #3
	bl MOD66_021D870C
_021D898C:
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #3
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #5
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #6
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #7
	bl FUN_0201AC68
	add sp, #0x1c
	pop {r3, r4, pc}
	thumb_func_end MOD66_021D8838

	thumb_func_start MOD66_021D89B8
MOD66_021D89B8: ; 0x021D89B8
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	mov r1, #6
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x28]
	mov r1, #7
	mov r2, #3
	mov r3, #0
	bl FUN_020179E0
	mov r2, #0
	ldr r0, [r4, #0x28]
	mov r1, #6
	add r3, r2, #0
	bl FUN_020179E0
	mov r2, #0
	ldr r0, [r4, #0x28]
	mov r1, #7
	add r3, r2, #0
	bl FUN_020179E0
	mov r1, #0
	str r1, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r1, #1
	add r3, r2, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r1, #2
	add r3, r2, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r1, #3
	add r3, r2, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r1, #4
	add r3, r2, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r1, #5
	add r3, r2, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r1, #6
	add r3, r2, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x28]
	mov r1, #7
	add r3, r2, #0
	bl FUN_02018540
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #3
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #4
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #5
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #6
	bl FUN_0201AC68
	ldr r0, [r4, #0x28]
	mov r1, #7
	bl FUN_0201AC68
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD66_021D89B8

	thumb_func_start MOD66_021D8AF4
MOD66_021D8AF4: ; 0x021D8AF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, _021D8BE4 ; =0x021D981C
	ldr r4, [r5, #0x34]
	bl FUN_0200BE38
	mov r1, #1
	lsl r1, r1, #8
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r1, #1
	lsl r1, r1, #8
	ldr r0, [r4, r1]
	lsl r1, r1, #4
	bl FUN_020200D8
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #0x80
	mov r2, #0x6c
	bl FUN_0200C6E4
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, _021D8BE8 ; =0x021D9844
	bl FUN_0200BE38
	mov r1, #0x41
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x41
	lsl r0, r0, #2
	mov r1, #2
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r1, [r4, #0x18]
	mov r0, #0x41
	lsl r0, r0, #2
	mov r2, #7
	add r3, r1, #0
	mul r3, r2
	add r3, #0x19
	lsl r1, r3, #0x10
	ldr r3, [r4, #0x1c]
	ldr r0, [r4, r0]
	mul r2, r3
	sub r2, #0x22
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, _021D8BEC ; =0x021D986C
	bl FUN_0200BE38
	mov r1, #0x42
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200A0
	ldr r1, [r5, #0x2c]
	mov r0, #0x42
	ldr r1, [r1, #0xc]
	lsl r0, r0, #2
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020208
	ldr r1, [r4, #0x18]
	mov r0, #0x42
	lsl r0, r0, #2
	mov r2, #7
	add r3, r1, #0
	mul r3, r2
	add r3, #0x19
	lsl r1, r3, #0x10
	ldr r3, [r4, #0x1c]
	ldr r0, [r4, r0]
	mul r2, r3
	sub r2, #0x22
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8BE4: .word MOD66_021D981C
_021D8BE8: .word MOD66_021D9844
_021D8BEC: .word MOD66_021D986C
	thumb_func_end MOD66_021D8AF4

	thumb_func_start MOD66_021D8BF0
MOD66_021D8BF0: ; 0x021D8BF0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #8
	bge _021D8C16
	ldr r0, [r5, #0x28]
	mov r1, #6
	mov r2, #0
	mov r3, #8
	bl FUN_0201AEE4
	ldr r0, [r5, #0x28]
	mov r1, #7
	mov r2, #0
	mov r3, #8
	bl FUN_0201AEE4
	b _021D8C4A
_021D8C16:
	cmp r4, #0xf8
	ldr r0, [r5, #0x28]
	ble _021D8C34
	mov r1, #6
	mov r2, #0
	mov r3, #0xf8
	bl FUN_0201AEE4
	ldr r0, [r5, #0x28]
	mov r1, #7
	mov r2, #0
	mov r3, #0xf8
	bl FUN_0201AEE4
	b _021D8C4A
_021D8C34:
	mov r1, #6
	mov r2, #0
	add r3, r4, #0
	bl FUN_0201AEE4
	ldr r0, [r5, #0x28]
	mov r1, #7
	mov r2, #0
	add r3, r4, #0
	bl FUN_0201AEE4
_021D8C4A:
	cmp r6, #0x50
	bge _021D8C68
	ldr r0, [r5, #0x28]
	mov r1, #6
	mov r2, #3
	mov r3, #0x50
	bl FUN_0201AEE4
	ldr r0, [r5, #0x28]
	mov r1, #7
	mov r2, #3
	mov r3, #0x50
	bl FUN_0201AEE4
	pop {r4, r5, r6, pc}
_021D8C68:
	mov r3, #0x13
	lsl r3, r3, #4
	cmp r6, r3
	ldr r0, [r5, #0x28]
	ble _021D8C8A
	mov r1, #6
	mov r2, #3
	bl FUN_0201AEE4
	mov r3, #0x13
	ldr r0, [r5, #0x28]
	mov r1, #7
	mov r2, #3
	lsl r3, r3, #4
	bl FUN_0201AEE4
	pop {r4, r5, r6, pc}
_021D8C8A:
	mov r1, #6
	mov r2, #3
	add r3, r6, #0
	bl FUN_0201AEE4
	ldr r0, [r5, #0x28]
	mov r1, #7
	mov r2, #3
	add r3, r6, #0
	bl FUN_0201AEE4
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD66_021D8BF0

	thumb_func_start MOD66_021D8CA4
MOD66_021D8CA4: ; 0x021D8CA4
	push {r4, r5}
	ldr r5, [r0]
	mov r4, #0
	cmp r5, #0
	ble _021D8CC8
_021D8CAE:
	ldr r3, [r0, #0xc]
	cmp r1, r3
	bne _021D8CC0
	ldr r3, [r0, #0x10]
	cmp r2, r3
	bne _021D8CC0
	add r0, r4, #0
	pop {r4, r5}
	bx lr
_021D8CC0:
	add r4, r4, #1
	add r0, #0x10
	cmp r4, r5
	blt _021D8CAE
_021D8CC8:
	mov r0, #0
	mvn r0, r0
	pop {r4, r5}
	bx lr
	thumb_func_end MOD66_021D8CA4

	thumb_func_start MOD66_021D8CD0
MOD66_021D8CD0: ; 0x021D8CD0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	ldr r0, [r6, #0x34]
	mov r1, #0
	str r0, [sp, #8]
	add r0, #0xa4
	mov r2, #0x5c
	bl MI_CpuFill8
	mov r0, #0
	ldr r7, [sp, #8]
	str r0, [sp, #4]
	str r0, [sp]
	ldr r0, [sp, #8]
	add r7, #0xa4
	str r0, [sp, #0xc]
	add r0, #0xb0
	str r0, [sp, #0xc]
_021D8CF6:
	ldr r1, [r6, #0x2c]
	ldr r0, [sp]
	add r1, #0x20
	add r4, r1, r0
	ldrh r0, [r4, #0xa]
	cmp r0, #0
	beq _021D8DAA
	ldr r1, [r4]
	ldr r0, [r6, #0x20]
	cmp r1, r0
	bne _021D8D14
	ldr r2, [r4, #4]
	ldr r0, [r6, #0x24]
	cmp r2, r0
	beq _021D8D9A
_021D8D14:
	ldr r2, [r4, #4]
	add r0, r7, #0
	bl MOD66_021D8CA4
	cmp r0, #0
	bge _021D8D32
	ldr r0, [sp, #8]
	add r0, #0xa4
	ldr r1, [r0]
	ldr r0, [r7]
	lsl r1, r1, #4
	add r0, r0, #1
	str r0, [r7]
	ldr r0, [sp, #0xc]
	b _021D8D36
_021D8D32:
	lsl r1, r0, #4
	ldr r0, [sp, #0xc]
_021D8D36:
	add r5, r0, r1
	ldr r0, [r4]
	str r0, [r5]
	ldr r0, [r4, #4]
	str r0, [r5, #4]
	ldrh r0, [r4, #8]
	cmp r0, #3
	bls _021D8D4A
	mov r0, #0
	b _021D8D50
_021D8D4A:
	lsl r1, r0, #1
	ldr r0, _021D8DD4 ; =0x021D9718
	ldrh r0, [r0, r1]
_021D8D50:
	strh r0, [r5, #8]
	ldr r0, [sp, #4]
	add r1, r6, #0
	strb r0, [r5, #0xa]
	mov r0, #1
	strb r0, [r5, #0xb]
	add r0, r6, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, _021D8DD8 ; =0x021D972C
	bl FUN_0200BE38
	str r0, [r5, #0xc]
	ldr r2, [r5]
	mov r1, #7
	mul r1, r2
	add r1, #0x19
	lsl r1, r1, #0x10
	ldr r3, [r5, #4]
	mov r2, #7
	mul r2, r3
	sub r2, #0x22
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	ldr r0, [r5, #0xc]
	mov r1, #2
	bl FUN_02020310
	ldr r0, [r5, #0xc]
	mov r1, #0
	bl FUN_020200A0
_021D8D9A:
	ldr r0, [sp]
	add r0, #0xc
	str r0, [sp]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #5
	blt _021D8CF6
_021D8DAA:
	ldr r0, [sp, #8]
	add r0, #0xa4
	ldr r0, [r0]
	cmp r0, #0
	beq _021D8DD0
	sub r1, r0, #1
	ldr r0, [sp, #8]
	mov r2, #1
	add r0, #0xae
	strb r1, [r0]
	ldr r1, [sp, #8]
	ldr r0, _021D8DDC ; =MOD66_021D8DE0
	add r1, #0xa4
	bl FUN_0200CA44
	ldr r1, [sp, #8]
	add r1, #0xa8
	str r1, [sp, #8]
	str r0, [r1]
_021D8DD0:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8DD4: .word MOD66_021D9718
_021D8DD8: .word MOD66_021D972C
_021D8DDC: .word MOD66_021D8DE0
	thumb_func_end MOD66_021D8CD0

	thumb_func_start MOD66_021D8DE0
MOD66_021D8DE0: ; 0x021D8DE0
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #8]
	add r1, r0, #1
	strh r1, [r4, #8]
	mov r1, #0x1a
	bl _s32_div_f
	cmp r1, #0
	bgt _021D8E30
	ldrb r0, [r4, #0xb]
	mov r1, #0
	lsl r0, r0, #4
	add r0, r4, r0
	ldr r0, [r0, #0x18]
	bl FUN_020200A0
	ldrb r0, [r4, #0xa]
	mov r1, #1
	lsl r0, r0, #4
	add r0, r4, r0
	ldr r0, [r0, #0x18]
	bl FUN_020200A0
	ldrb r0, [r4, #0xa]
	strb r0, [r4, #0xb]
	ldr r1, [r4]
	ldrb r2, [r4, #0xa]
	sub r0, r1, #1
	add r0, r2, r0
	bl _s32_div_f
	strb r1, [r4, #0xa]
	mov r0, #0x41
	ldrh r1, [r4, #8]
	lsl r0, r0, #2
	cmp r1, r0
	bls _021D8E30
	mov r0, #1
	strh r0, [r4, #8]
_021D8E30:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD66_021D8DE0

	thumb_func_start MOD66_021D8E34
MOD66_021D8E34: ; 0x021D8E34
	push {r4, r5, r6, lr}
	ldr r6, [r0, #0x34]
	add r0, r6, #0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	beq _021D8E46
	bl FUN_0200CAB4
_021D8E46:
	add r0, r6, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r4, #0
	cmp r0, #0
	ble _021D8E6C
	add r5, r6, #0
_021D8E54:
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl FUN_0200BC14
	add r0, r6, #0
	add r0, #0xa4
	ldr r0, [r0]
	add r4, r4, #1
	add r5, #0x10
	cmp r4, r0
	blt _021D8E54
_021D8E6C:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD66_021D8E34

	thumb_func_start MOD66_021D8E70
MOD66_021D8E70: ; 0x021D8E70
	push {r4, lr}
	add r3, r0, #0
	ldr r4, [r3, #0x34]
	mov r2, #0
	str r2, [r4, #4]
	str r2, [r4, #8]
	cmp r1, #0
	bne _021D8E90
	ldr r0, _021D8EA0 ; =MOD66_021D8EA8
	add r1, r3, #0
	bl FUN_0200CA44
	mov r1, #0x43
	lsl r1, r1, #2
	str r0, [r4, r1]
	pop {r4, pc}
_021D8E90:
	ldr r0, _021D8EA4 ; =MOD66_021D9020
	add r1, r3, #0
	bl FUN_0200CA44
	mov r1, #0x43
	lsl r1, r1, #2
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_021D8EA0: .word MOD66_021D8EA8
_021D8EA4: .word MOD66_021D9020
	thumb_func_end MOD66_021D8E70

	thumb_func_start MOD66_021D8EA8
MOD66_021D8EA8: ; 0x021D8EA8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	ldr r4, [r5, #0x34]
	add r6, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #4
	bls _021D8EBA
	b _021D9014
_021D8EBA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8EC6: ; jump table
	.short _021D8ED0 - _021D8EC6 - 2 ; case 0
	.short _021D8F04 - _021D8EC6 - 2 ; case 1
	.short _021D8F40 - _021D8EC6 - 2 ; case 2
	.short _021D8F7C - _021D8EC6 - 2 ; case 3
	.short _021D8FF2 - _021D8EC6 - 2 ; case 4
_021D8ED0:
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_02020208
	ldr r0, _021D9018 ; =0x000005E4
	bl FUN_020054C8
	ldr r0, [r4, #4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021D8F04:
	ldr r1, [r4, #8]
	mov r0, #0x1f
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1f
	sub r2, r2, r3
	ror r2, r0
	add r0, r3, r2
	beq _021D8F2C
	add r3, r1, r3
	ldr r1, _021D901C ; =0x021D9714
	asr r2, r3, #1
	ldrb r1, [r1, r2]
	add r0, r5, #0
	mov r2, #0
	bl MOD66_021D868C
	ldr r0, [r5, #0x28]
	mov r1, #5
	bl FUN_0201AC68
_021D8F2C:
	ldr r1, [r4, #8]
	add r0, r1, #1
	str r0, [r4, #8]
	cmp r1, #7
	ble _021D9014
	ldr r0, [r4, #4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021D8F40:
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r3, #0
	str r3, [r5, #0x14]
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	mov r1, #0xd
	str r0, [sp, #8]
	mov r0, #4
	mov r2, #2
	bl FUN_0200E1D0
	ldr r0, [r4, #4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021D8F7C:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9014
	mov r0, #1
	strb r0, [r4, #0x10]
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x28]
	mov r1, #4
	add r3, r2, #0
	bl FUN_02018540
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x28]
	mov r1, #5
	add r3, r2, #0
	bl FUN_02018540
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x68
	bl MOD66_021D84C8
	add r0, r5, #0
	bl MOD66_021D818C
	add r0, r5, #0
	bl MOD66_021D8140
	mov r3, #0
	str r3, [r5, #0x14]
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	mov r1, #0xd
	str r0, [sp, #8]
	mov r0, #4
	mov r2, #5
	bl FUN_0200E1D0
	ldr r0, [r4, #4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021D8FF2:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9014
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #4]
	ldrb r0, [r4, #0x14]
	sub r0, r0, #2
	strb r0, [r4, #0x14]
	add r0, r6, #0
	bl FUN_0200CAB4
	mov r0, #0x43
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_021D9014:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D9018: .word 0x000005E4
_021D901C: .word MOD66_021D9714
	thumb_func_end MOD66_021D8EA8

	thumb_func_start MOD66_021D9020
MOD66_021D9020: ; 0x021D9020
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	ldr r4, [r5, #0x34]
	add r6, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D903C
	cmp r0, #1
	beq _021D9066
	cmp r0, #2
	beq _021D90C4
	add sp, #0x10
	pop {r4, r5, r6, pc}
_021D903C:
	mov r3, #0
	str r3, [r5, #0x14]
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	mov r1, #0xd
	str r0, [sp, #8]
	mov r0, #4
	mov r2, #2
	bl FUN_0200E1D0
	ldr r0, _021D90EC ; =0x00000691
	bl FUN_020054C8
	ldr r0, [r4, #4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021D9066:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D90E8
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x28]
	mov r1, #4
	add r3, r2, #0
	bl FUN_02018540
	add r0, r5, #0
	mov r1, #0
	mov r2, #1
	bl MOD66_021D868C
	ldr r0, [r5, #0x28]
	mov r1, #4
	bl FUN_0201AC68
	ldr r0, [r5, #0x28]
	mov r1, #5
	bl FUN_0201AC68
	mov r3, #0
	str r3, [r5, #0x14]
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	mov r1, #0xd
	str r0, [sp, #8]
	mov r0, #4
	mov r2, #5
	bl FUN_0200E1D0
	ldr r0, [r4, #4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021D90C4:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D90E8
	mov r0, #0
	strb r0, [r4, #0x10]
	str r0, [r4, #4]
	str r0, [r4, #8]
	ldrb r0, [r4, #0x14]
	sub r0, r0, #2
	strb r0, [r4, #0x14]
	add r0, r6, #0
	bl FUN_0200CAB4
	mov r0, #0x43
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_021D90E8:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D90EC: .word 0x00000691
	thumb_func_end MOD66_021D9020

	thumb_func_start MOD66_021D90F0
MOD66_021D90F0: ; 0x021D90F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x34]
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	cmp r0, #0
	bne _021D9104
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9104:
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x18]
	ldr r3, [r4, #0x1c]
	bl MOD66_021D9390
	cmp r0, #0
	beq _021D911E
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bne _021D9122
_021D911E:
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D9122:
	ldr r1, [r5, #0x2c]
	mov r0, #1
	str r0, [r1, #0x10]
	ldr r2, [r4, #0x18]
	ldr r1, [r5, #0x2c]
	str r2, [r1, #0x14]
	ldr r2, [r4, #0x1c]
	ldr r1, [r5, #0x2c]
	str r2, [r1, #0x18]
	ldr r2, [r4, #0x20]
	ldr r1, [r5, #0x2c]
	str r2, [r1, #0x1c]
	pop {r3, r4, r5, pc}
	thumb_func_end MOD66_021D90F0

	thumb_func_start MOD66_021D913C
MOD66_021D913C: ; 0x021D913C
	push {r4, r5, r6, lr}
	sub sp, #0x50
	add r4, r0, #0
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	ldr r1, [r4, #4]
	mov r0, #0x20
	bl FUN_0201C24C
	ldr r0, [r4, #4]
	bl FUN_0200BB14
	add r1, r4, #0
	add r1, #0xd8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	bl FUN_0200BB34
	add r1, r4, #0
	add r1, #0xdc
	add r2, sp, #0x30
	ldr r5, _021D91E8 ; =0x021D98C4
	str r0, [r1]
	ldmia r5!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	ldr r6, _021D91EC ; =0x021D9894
	stmia r2!, {r0, r1}
	add r5, sp, #0x1c
	ldmia r6!, {r0, r1}
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r1, r3, #0
	str r0, [r5]
	add r0, r4, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r3, #0x20
	bl FUN_0200BB6C
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x1c
	bl FUN_0200BBF0
	ldr r5, _021D91F0 ; =0x021D98A8
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	add r0, #0xd8
	add r4, #0xdc
	ldr r0, [r0]
	ldr r1, [r4]
	bl FUN_0200BD20
	add sp, #0x50
	pop {r4, r5, r6, pc}
	nop
_021D91E8: .word MOD66_021D98C4
_021D91EC: .word MOD66_021D9894
_021D91F0: .word MOD66_021D98A8
	thumb_func_end MOD66_021D913C

	thumb_func_start MOD66_021D91F4
MOD66_021D91F4: ; 0x021D91F4
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r0, #0xd8
	add r1, #0xdc
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_0200BCE0
	add r4, #0xd8
	ldr r0, [r4]
	bl FUN_0200BD04
	bl FUN_0201C29C
	pop {r4, pc}
	thumb_func_end MOD66_021D91F4

	thumb_func_start MOD66_021D9214
MOD66_021D9214: ; 0x021D9214
	ldr r3, _021D921C ; =FUN_0200BC1C
	add r0, #0xdc
	ldr r0, [r0]
	bx r3
	.align 2, 0
_021D921C: .word FUN_0200BC1C
	thumb_func_end MOD66_021D9214

	thumb_func_start MOD66_021D9220
MOD66_021D9220: ; 0x021D9220
	ldr r3, _021D9224 ; =FUN_0200BC30
	bx r3
	.align 2, 0
_021D9224: .word FUN_0200BC30
	thumb_func_end MOD66_021D9220

	thumb_func_start MOD66_021D9228
MOD66_021D9228: ; 0x021D9228
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r5, [sp, #0x28]
	str r0, [sp]
	str r1, [sp, #4]
	add r0, r5, #0
	mov r1, #0xc
	str r2, [sp, #8]
	add r4, r3, #0
	bl AllocFromHeap
	add r7, r0, #0
	mov r0, #0
	strb r0, [r7]
	strb r0, [r7, #1]
	strb r0, [r7, #2]
	strb r0, [r7, #3]
	strb r0, [r7, #4]
	strb r0, [r7, #5]
	strb r0, [r7, #6]
	strb r0, [r7, #7]
	strb r0, [r7, #8]
	strb r0, [r7, #9]
	strb r0, [r7, #0xa]
	strb r0, [r7, #0xb]
	strh r4, [r7]
	ldrh r2, [r7]
	mov r1, #0x1c
	add r0, r5, #0
	mul r1, r2
	bl AllocFromHeap
	str r0, [r7, #8]
	ldrh r3, [r7]
	mov r2, #0x1c
	mov r1, #0
	mul r2, r3
	bl memset
	ldrh r0, [r7]
	mov r6, #0
	ldr r5, _021D9344 ; =0x021D990C
	cmp r0, #0
	ble _021D933E
	str r6, [sp, #0xc]
_021D9282:
	ldr r0, [r7, #8]
	ldr r1, [sp, #0xc]
	ldr r2, [r5]
	add r4, r0, r1
	str r2, [r0, r1]
	ldrb r0, [r5, #8]
	ldr r1, [sp, #4]
	ldr r2, _021D9348 ; =0x021D98E4
	strb r0, [r4, #8]
	ldrb r0, [r5, #9]
	strb r0, [r4, #9]
	ldrh r0, [r5, #0xa]
	strh r0, [r4, #0xa]
	ldr r0, [r5, #0xc]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x10]
	str r0, [r4, #0x10]
	ldr r0, [sp, #8]
	ldrb r0, [r0, r6]
	str r0, [r4, #0x14]
	ldr r0, [sp]
	bl FUN_0200BE38
	str r0, [r4, #0x18]
	mov r1, #1
	bl FUN_020200A0
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021D92CC
	ldrb r2, [r4, #9]
	ldr r0, [r4, #0x18]
	add r2, r2, #5
	add r1, r2, r1
	bl FUN_02020248
	b _021D92E2
_021D92CC:
	ldrh r1, [r4, #0xa]
	ldr r0, _021D934C ; =0x0000FFFF
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _021D92E2
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_020200A0
_021D92E2:
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _021D92FA
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D9308
_021D92FA:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D9308:
	bl _ffix
	add r1, r0, #0
	ldr r0, [r4, #0x18]
	bl FUN_020201E4
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x10]
	add r1, #0x19
	sub r2, #0x22
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x18]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	ldr r0, [sp, #0xc]
	add r5, #0x14
	add r0, #0x1c
	str r0, [sp, #0xc]
	add r0, r6, #1
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldrh r0, [r7]
	cmp r6, r0
	blt _021D9282
_021D933E:
	add r0, r7, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9344: .word MOD66_021D990C
_021D9348: .word MOD66_021D98E4
_021D934C: .word 0x0000FFFF
	thumb_func_end MOD66_021D9228

	thumb_func_start MOD66_021D9350
MOD66_021D9350: ; 0x021D9350
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrh r0, [r5]
	mov r6, #0
	cmp r0, #0
	ble _021D9380
	add r4, r6, #0
_021D935E:
	ldr r0, [r5, #8]
	mov r1, #0
	add r7, r0, r4
	ldr r0, [r7, #0x18]
	add r2, r1, #0
	bl FUN_0202008C
	ldr r0, [r7, #0x18]
	bl FUN_0201FFC8
	add r0, r6, #1
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	ldrh r0, [r5]
	add r4, #0x1c
	cmp r6, r0
	blt _021D935E
_021D9380:
	ldr r0, [r5, #8]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD66_021D9350

	thumb_func_start MOD66_021D9390
MOD66_021D9390: ; 0x021D9390
	push {r3, r4, r5, r6}
	ldrh r5, [r0]
	mov r4, #0
	cmp r5, #0
	ble _021D93EC
	ldr r0, [r0, #8]
_021D939C:
	ldr r6, [r0]
	cmp r6, r1
	bne _021D93E0
	ldrh r6, [r0, #0xa]
	cmp r6, #3
	bhi _021D93E0
	add r6, r6, r6
	add r6, pc
	ldrh r6, [r6, #6]
	lsl r6, r6, #0x10
	asr r6, r6, #0x10
	add pc, r6
_021D93B4: ; jump table
	.short _021D93BC - _021D93B4 - 2 ; case 0
	.short _021D93C0 - _021D93B4 - 2 ; case 1
	.short _021D93CC - _021D93B4 - 2 ; case 2
	.short _021D93D8 - _021D93B4 - 2 ; case 3
_021D93BC:
	pop {r3, r4, r5, r6}
	bx lr
_021D93C0:
	cmp r2, #9
	bne _021D93E0
	cmp r3, #0x1c
	bne _021D93E0
	pop {r3, r4, r5, r6}
	bx lr
_021D93CC:
	cmp r2, #0x1a
	bne _021D93E0
	cmp r3, #0x12
	bne _021D93E0
	pop {r3, r4, r5, r6}
	bx lr
_021D93D8:
	cmp r2, #0x1a
	bne _021D93E0
	cmp r3, #0x11
	beq _021D93EE
_021D93E0:
	add r4, r4, #1
	lsl r4, r4, #0x10
	asr r4, r4, #0x10
	add r0, #0x1c
	cmp r4, r5
	blt _021D939C
_021D93EC:
	mov r0, #0
_021D93EE:
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
	thumb_func_end MOD66_021D9390

	thumb_func_start MOD66_021D93F4
MOD66_021D93F4: ; 0x021D93F4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bne _021D93FE
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D93FE:
	bl MOD66_021D9390
	add r4, r0, #0
	beq _021D940C
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _021D9426
_021D940C:
	ldr r3, [r5, #4]
	cmp r3, #0
	beq _021D9420
	ldrb r1, [r3, #9]
	ldr r0, [r3, #0x18]
	add r2, r1, #5
	ldr r1, [r3, #0x14]
	add r1, r2, r1
	bl FUN_02020248
_021D9420:
	mov r0, #0
	str r0, [r5, #4]
	pop {r3, r4, r5, pc}
_021D9426:
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021D9434
	mov r0, #0
	strb r0, [r5, #2]
	strb r0, [r5, #3]
	b _021D9450
_021D9434:
	ldrh r2, [r4, #0xa]
	ldr r0, _021D9458 ; =0x0000FFFE
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _021D9450
	ldrb r2, [r1, #9]
	ldr r0, [r1, #0x18]
	ldr r1, [r1, #0x14]
	add r2, r2, #5
	add r1, r2, r1
	bl FUN_02020248
_021D9450:
	str r4, [r5, #4]
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021D9458: .word 0x0000FFFE
	thumb_func_end MOD66_021D93F4

	thumb_func_start MOD66_021D945C
MOD66_021D945C: ; 0x021D945C
	push {r4, lr}
	add r4, r0, #0
	ldr r3, [r4, #4]
	cmp r3, #0
	beq _021D94A0
	cmp r1, #1
	bne _021D94A0
	ldrb r0, [r4, #3]
	cmp r0, #0
	ldr r0, [r3, #0x18]
	bne _021D947C
	ldrb r1, [r3, #9]
	add r1, #8
	bl FUN_02020248
	b _021D9488
_021D947C:
	ldrb r1, [r3, #9]
	add r2, r1, #5
	ldr r1, [r3, #0x14]
	add r1, r2, r1
	bl FUN_02020248
_021D9488:
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	ldrb r0, [r4, #2]
	cmp r0, #0x10
	bne _021D94A0
	mov r0, #0
	strb r0, [r4, #2]
	ldrb r1, [r4, #3]
	mov r0, #1
	eor r0, r1
	strb r0, [r4, #3]
_021D94A0:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD66_021D945C

	thumb_func_start MOD66_021D94A4
MOD66_021D94A4: ; 0x021D94A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r5, r0, #0
	add r0, sp, #4
	add r4, r1, #0
	bl FS_InitFile
	add r0, sp, #4
	add r1, r5, #0
	bl FS_OpenFile
	cmp r0, #0
	bne _021D94C8
	bl ErrorHandling
	add sp, #0x4c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D94C8:
	add r0, sp, #4
	add r1, sp, #0
	mov r2, #4
	bl FS_ReadFile
	cmp r0, #0
	bge _021D94DA
	bl ErrorHandling
_021D94DA:
	add r0, r4, #0
	mov r1, #8
	bl AllocFromHeap
	add r6, r0, #0
	mov r0, #0
	strb r0, [r6]
	strb r0, [r6, #1]
	strb r0, [r6, #2]
	strb r0, [r6, #3]
	strb r0, [r6, #4]
	strb r0, [r6, #5]
	strb r0, [r6, #6]
	strb r0, [r6, #7]
	ldr r2, [sp]
	mov r1, #0x18
	add r0, r4, #0
	mul r1, r2
	bl AllocFromHeap
	str r0, [r6, #4]
	ldr r3, [sp]
	mov r2, #0x18
	mov r1, #0
	mul r2, r3
	bl memset
	ldr r0, [sp]
	mov r4, #0
	str r0, [r6]
	cmp r0, #0
	ble _021D9536
	add r5, r4, #0
_021D951C:
	ldr r0, [r6, #4]
	mov r2, #0x18
	add r7, r0, r5
	add r0, sp, #4
	add r1, r7, #0
	bl FS_ReadFile
	strh r4, [r7, #0x16]
	ldr r0, [r6]
	add r4, r4, #1
	add r5, #0x18
	cmp r4, r0
	blt _021D951C
_021D9536:
	add r0, sp, #4
	bl FS_CloseFile
	add r0, r6, #0
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD66_021D94A4

	thumb_func_start MOD66_021D9544
MOD66_021D9544: ; 0x021D9544
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD66_021D9544

	thumb_func_start MOD66_021D9558
MOD66_021D9558: ; 0x021D9558
	push {r3, r4, r5, r6}
	ldr r6, [r0]
	mov r5, #0
	cmp r6, #0
	ble _021D9588
	ldr r0, [r0, #4]
_021D9564:
	ldrh r4, [r0]
	cmp r4, r1
	bne _021D9580
	ldrh r4, [r0, #2]
	cmp r4, r2
	bne _021D9580
	ldrh r1, [r0, #0x14]
	cmp r1, #0
	beq _021D958A
	tst r1, r3
	bne _021D958A
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
_021D9580:
	add r5, r5, #1
	add r0, #0x18
	cmp r5, r6
	blt _021D9564
_021D9588:
	mov r0, #0
_021D958A:
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
	thumb_func_end MOD66_021D9558

	.rodata
	.global MOD66_021D9590
MOD66_021D9590: ; 0x021D9590
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D95A0
MOD66_021D95A0: ; 0x021D95A0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D95C8
MOD66_021D95C8: ; 0x021D95C8
	.word MOD66_021D7BB4

	.global MOD66_021D95CC
MOD66_021D95CC: ; 0x021D95CC
	.word MOD66_021D7C04

	.global MOD66_021D95D0
MOD66_021D95D0: ; 0x021D95D0
	.word MOD66_021D7CAC

	.global MOD66_021D95D4
MOD66_021D95D4: ; 0x021D95D4
	.word MOD66_021D7CF8

	.global MOD66_021D95D8
MOD66_021D95D8: ; 0x021D95D8
	.word MOD66_021D7D98

	.global MOD66_021D95DC
MOD66_021D95DC: ; 0x021D95DC
	.word MOD66_021D7E54

	.global MOD66_021D95E0
MOD66_021D95E0: ; 0x021D95E0
	.word MOD66_021D7EA0

	.global MOD66_021D95E4
MOD66_021D95E4: ; 0x021D95E4
	.word MOD66_021D7BD4

	.global MOD66_021D95E8
MOD66_021D95E8: ; 0x021D95E8
	.word MOD66_021D7EB4, MOD66_021D7BB4, MOD66_021D7C04, MOD66_021D7CAC
	.word MOD66_021D7CF8, MOD66_021D7DD4, MOD66_021D7E54, MOD66_021D7EA0
	.word MOD66_021D7BD4, MOD66_021D7EB4, MOD66_021D7BB4, MOD66_021D7C04
	.word MOD66_021D7D24, MOD66_021D7D6C, MOD66_021D7E2C, MOD66_021D7E54
	.word MOD66_021D7EA0, MOD66_021D7BD4, MOD66_021D7EB4

	.global MOD66_021D9634
MOD66_021D9634: ; 0x021D9634
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x1A, 0x04, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x16, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D9714
MOD66_021D9714: ; 0x021D9714
	.byte 0x01, 0x02, 0x01, 0x00

	.global MOD66_021D9718
MOD66_021D9718: ; 0x021D9718
	.byte 0x00, 0x00, 0x02, 0x00, 0x03, 0x00, 0x01, 0x00

	.global MOD66_021D9720
MOD66_021D9720: ; 0x021D9720
	.byte 0x00, 0xBF, 0x00, 0xFF, 0x50, 0x88, 0x68, 0x98, 0xFF, 0x00, 0x00, 0x00

	.global MOD66_021D972C
MOD66_021D972C: ; 0x021D972C
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D9754
MOD66_021D9754: ; 0x021D9754
	.byte 0x05, 0x00, 0x03, 0x01, 0x02, 0x03, 0x05, 0x03, 0x03, 0x02, 0x02, 0x02, 0x08, 0x00, 0x03, 0x10
	.byte 0x04, 0x04, 0x08, 0x04, 0x03, 0x10, 0x04, 0x04, 0x00, 0x00, 0x06, 0x01, 0x02, 0x03, 0x00, 0x03
	.byte 0x06, 0x02, 0x02, 0x02, 0x00, 0x00, 0x08, 0x10, 0x04, 0x04, 0x00, 0x04, 0x08, 0x10, 0x04, 0x04
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x05, 0x16, 0x0D, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x08, 0x30, 0x2A, 0x05, 0x06, 0x02, 0x00, 0x1A, 0x00, 0x03, 0x03, 0x02, 0x03
	.byte 0x1B, 0x00, 0x02, 0x09, 0x04, 0x00, 0x39, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x39, 0x0C, 0x04, 0x13

	.global MOD66_021D97B4
MOD66_021D97B4: ; 0x021D97B4
	.byte 0x0B, 0x00, 0x13, 0x00

	.global MOD66_021D97B8
MOD66_021D97B8: ; 0x021D97B8
	.byte 0xCF, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x14, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x15, 0x00
	.byte 0xCF, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x16, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00
	.byte 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0E, 0x00
	.byte 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0F, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x00
	.byte 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x11, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x12, 0x00
	.byte 0xCF, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x13, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x14, 0x00, 0x0C, 0x00
	.byte 0x42, 0x01, 0x00, 0x00

	.global MOD66_021D981C
MOD66_021D981C: ; 0x021D981C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D9844
MOD66_021D9844: ; 0x021D9844
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D986C
MOD66_021D986C: ; 0x021D986C
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D9894
MOD66_021D9894: ; 0x021D9894
	.byte 0x05, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD66_021D98A8
MOD66_021D98A8: ; 0x021D98A8
	.word MOD66_021D9ACC, MOD66_021D9AB4, MOD66_021D9AFC, MOD66_021D9AE4
	.word 0x00000000, 0x00000000, MOD66_021D9B14

	.global MOD66_021D98C4
MOD66_021D98C4: ; 0x021D98C4
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD66_021D98E4
MOD66_021D98E4: ; 0x021D98E4
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD66_021D990C
MOD66_021D990C: ; 0x021D990C
	.byte 0x9B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00
	.byte 0xBD, 0x00, 0x00, 0x00, 0xA2, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x23, 0x00, 0x00, 0x00, 0xB6, 0x00, 0x00, 0x00, 0xAA, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0xB1, 0x01, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00
	.byte 0xBA, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00
	.byte 0x70, 0x00, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x8C, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0xC9, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00
	.byte 0x21, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x9D, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x03, 0x01, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00
	.byte 0x78, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00
	.byte 0xB2, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00
	.byte 0x96, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00
	.byte 0x02, 0x01, 0x00, 0x00, 0xB9, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00, 0xA5, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00
	.byte 0xBC, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x05, 0x01, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00
	.byte 0x5B, 0x00, 0x00, 0x00, 0x88, 0x01, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x06, 0x01, 0x01, 0x00
	.byte 0x3F, 0x00, 0x00, 0x00, 0xC4, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x06, 0x01, 0x02, 0x00, 0xB6, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00
	.byte 0x44, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0xB6, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00

	.data
	.global MOD66_021D9AA0
MOD66_021D9AA0: ; 0x021D9AA0
	.byte 0x64, 0x61, 0x74, 0x61, 0x2F, 0x74, 0x6D, 0x61, 0x70, 0x5F, 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x2E
	.byte 0x64, 0x61, 0x74, 0x00

	.global MOD66_021D9AB4
MOD66_021D9AB4: ; 0x021D9AB4
	.byte 0x64, 0x61, 0x74, 0x61, 0x2F, 0x74, 0x6D, 0x61, 0x70, 0x6E, 0x5F, 0x70
	.byte 0x61, 0x6C, 0x2E, 0x72, 0x65, 0x73, 0x64, 0x61, 0x74, 0x00, 0x00, 0x00

	.global MOD66_021D9ACC
MOD66_021D9ACC: ; 0x021D9ACC
	.byte 0x64, 0x61, 0x74, 0x61
	.byte 0x2F, 0x74, 0x6D, 0x61, 0x70, 0x6E, 0x5F, 0x63, 0x68, 0x72, 0x2E, 0x72, 0x65, 0x73, 0x64, 0x61
	.byte 0x74, 0x00, 0x00, 0x00

	.global MOD66_021D9AE4
MOD66_021D9AE4: ; 0x021D9AE4
	.byte 0x64, 0x61, 0x74, 0x61, 0x2F, 0x74, 0x6D, 0x61, 0x70, 0x6E, 0x5F, 0x63
	.byte 0x61, 0x6E, 0x6D, 0x2E, 0x72, 0x65, 0x73, 0x64, 0x61, 0x74, 0x00, 0x00

	.global MOD66_021D9AFC
MOD66_021D9AFC: ; 0x021D9AFC
	.byte 0x64, 0x61, 0x74, 0x61
	.byte 0x2F, 0x74, 0x6D, 0x61, 0x70, 0x6E, 0x5F, 0x63, 0x65, 0x6C, 0x6C, 0x2E, 0x72, 0x65, 0x73, 0x64
	.byte 0x61, 0x74, 0x00, 0x00

	.global MOD66_021D9B14
MOD66_021D9B14: ; 0x021D9B14
	.byte 0x64, 0x61, 0x74, 0x61, 0x2F, 0x74, 0x6D, 0x61, 0x70, 0x6E, 0x5F, 0x63
	.byte 0x65, 0x6C, 0x61, 0x63, 0x74, 0x2E, 0x63, 0x6C, 0x64, 0x61, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
