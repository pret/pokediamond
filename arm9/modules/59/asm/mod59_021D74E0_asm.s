	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD59_021D7564
MOD59_021D7564: ; 0x021D7564
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r5]
	add r4, r0, #0
	mov r6, #0
	cmp r1, #5
	bls _021D757A
	b _021D76AC
_021D757A:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7586: ; jump table
	.short _021D7592 - _021D7586 - 2 ; case 0
	.short _021D75FA - _021D7586 - 2 ; case 1
	.short _021D7642 - _021D7586 - 2 ; case 2
	.short _021D7668 - _021D7586 - 2 ; case 3
	.short _021D7690 - _021D7586 - 2 ; case 4
	.short _021D76AA - _021D7586 - 2 ; case 5
_021D7592:
	add r0, r6, #0
	add r1, r6, #0
	bl FUN_0200E3A0
	mov r0, #1
	add r1, r6, #0
	bl FUN_0200E3A0
	add r0, r6, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	add r0, r6, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D76B4 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D76B8 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	add r0, r4, #0
	bl MOD59_021D778C
	add r0, r4, #0
	bl MOD59_021D79F8
	add r0, r4, #0
	bl MOD59_021D7A4C
	ldr r0, _021D76BC ; =MOD59_021D7724
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	bl FUN_0201E788
	mov r0, #1
	str r0, [r5]
	b _021D76AC
_021D75FA:
	bl MOD59_021D8920
	cmp r0, #1
	bne _021D761E
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #2
	str r0, [r5]
_021D761E:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021D76AC
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #3
	str r0, [r5]
	b _021D76AC
_021D7642:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D76AC
	add r0, r4, #0
	bl MOD59_021D7A34
	add r0, r4, #0
	bl MOD59_021D796C
	add r0, r4, #0
	bl MOD59_021D7A5C
	add r0, r6, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r6, #1
	b _021D76AC
_021D7668:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D76AC
	add r0, r4, #0
	bl MOD59_021D7A34
	add r0, r4, #0
	bl MOD59_021D796C
	add r0, r4, #0
	bl MOD59_021D7A5C
	add r0, r6, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #4
	str r0, [r5]
	b _021D76AC
_021D7690:
	ldr r0, [r4, #0x14]
	bl OverlayManager_Run
	cmp r0, #1
	bne _021D76AC
	ldr r0, [r4, #0x14]
	bl OverlayManager_delete
	add r0, r6, #0
	str r0, [r4, #0x14]
	mov r0, #5
	str r0, [r5]
	b _021D76AC
_021D76AA:
	str r6, [r5]
_021D76AC:
	add r0, r6, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D76B4: .word 0xFFFFE0FF
_021D76B8: .word 0x04001000
_021D76BC: .word MOD59_021D7724
	thumb_func_end MOD59_021D7564

	thumb_func_start MOD59_021D76C0
MOD59_021D76C0: ; 0x021D76C0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r5, [r4]
	bl Sav2_PlayerData_GetProfileAddr
	ldr r1, [r4, #0x70]
	ldr r1, [r1, #0x18]
	bl PlayerName_StringToFlat
	ldr r0, [r4, #4]
	bl Sav2_PlayerData_GetProfileAddr
	ldr r1, [r4, #0x70]
	ldr r1, [r1, #4]
	bl PlayerProfile_SetTrainerGender
	ldr r0, [r4, #4]
	bl FUN_02024EB4
	ldr r1, [r4, #0x74]
	ldr r1, [r1, #0x18]
	bl FUN_02024EF4
	ldr r0, [r4, #0x70]
	bl FUN_02077AC4
	ldr r0, [r4, #0x74]
	bl FUN_02077AC4
	add r0, r6, #0
	bl OverlayManager_FreeData
	add r0, r5, #0
	bl FUN_020168D0
	ldr r0, _021D771C ; =SDK_OVERLAY_MODULE_52_ID
	ldr r1, _021D7720 ; =MOD52_021D76D8
	bl RegisterMainOverlay
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_021D771C: .word SDK_OVERLAY_MODULE_52_ID
_021D7720: .word MOD52_021D76D8
	thumb_func_end MOD59_021D76C0

	thumb_func_start MOD59_021D7724
MOD59_021D7724: ; 0x021D7724
	ldr r3, _021D772C ; =FUN_0201AB60
	ldr r0, [r0, #0x18]
	bx r3
	nop
_021D772C: .word FUN_0201AB60
	thumb_func_end MOD59_021D7724

	thumb_func_start MOD59_021D7730
MOD59_021D7730: ; 0x021D7730
	push {r3, r4}
	ldr r2, _021D7788 ; =gMain + 0x40
	mov r0, #0
	ldrh r1, [r2, #0x20]
	cmp r1, #0
	beq _021D7784
	ldrh r3, [r2, #0x1c]
	mov r1, #1
	lsl r1, r1, #8
	cmp r3, r1
	bhs _021D7784
	ldrh r2, [r2, #0x1e]
	cmp r2, #0xc0
	bhs _021D7784
	cmp r3, #0x80
	bhs _021D7758
	mov r1, #0x80
	sub r1, r1, r3
	lsl r1, r1, #0x10
	b _021D775C
_021D7758:
	sub r3, #0x80
	lsl r1, r3, #0x10
_021D775C:
	lsr r3, r1, #0x10
	cmp r2, #0x64
	bhs _021D776A
	mov r1, #0x64
	sub r1, r1, r2
	lsl r1, r1, #0x10
	b _021D776E
_021D776A:
	sub r2, #0x64
	lsl r1, r2, #0x10
_021D776E:
	lsr r4, r1, #0x10
	add r2, r3, #0
	add r1, r4, #0
	mul r2, r3
	mul r1, r4
	add r2, r2, r1
	mov r1, #1
	lsl r1, r1, #8
	cmp r2, r1
	bgt _021D7784
	mov r0, #1
_021D7784:
	pop {r3, r4}
	bx lr
	.align 2, 0
_021D7788: .word gMain + 0x40
	thumb_func_end MOD59_021D7730

	thumb_func_start MOD59_021D778C
MOD59_021D778C: ; 0x021D778C
	push {r3, r4, r5, lr}
	sub sp, #0x78
	ldr r5, _021D7954 ; =0x021D9F18
	add r4, r0, #0
	add r3, sp, #0x50
	mov r2, #5
_021D7798:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7798
	add r0, sp, #0x50
	bl FUN_0201E66C
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0x40
	ldr r5, _021D7958 ; =0x021D9DCC
	str r0, [r4, #0x18]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D795C ; =0x021D9EA0
	add r3, sp, #0x24
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	mov r0, #0xf
	strb r0, [r2, #0x12]
	mov r0, #6
	strb r0, [r2, #0x13]
	ldr r0, [r4, #0x18]
	add r3, r1, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_02018744
	mov r0, #0xe
	add r2, sp, #0x24
	strb r0, [r2, #0x12]
	mov r0, #5
	strb r0, [r2, #0x13]
	ldr r0, [r4, #0x18]
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_02018744
	mov r0, #0xd
	add r2, sp, #0x24
	strb r0, [r2, #0x12]
	mov r0, #4
	strb r0, [r2, #0x13]
	ldr r0, [r4, #0x18]
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_02018744
	mov r0, #0xc
	add r2, sp, #0x24
	strb r0, [r2, #0x12]
	mov r1, #3
	strb r1, [r2, #0x13]
	ldr r0, [r4, #0x18]
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #3
	bl FUN_02018744
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4]
	ldr r2, _021D7960 ; =0x000003E2
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	mov r3, #4
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4]
	ldr r2, _021D7964 ; =0x000003D9
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	mov r3, #3
	bl FUN_0200CB00
	ldr r2, [r4]
	mov r0, #0
	mov r1, #0xa0
	bl FUN_02002ED0
	ldr r2, [r4]
	mov r0, #0
	mov r1, #0xc0
	bl FUN_02002EEC
	ldr r5, _021D7968 ; =0x021D9EBC
	add r3, sp, #8
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0xf
	str r0, [r3]
	add r0, sp, #8
	strb r1, [r0, #0x12]
	mov r1, #6
	strb r1, [r0, #0x13]
	ldr r0, [r4, #0x18]
	mov r1, #4
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #4
	bl FUN_02018744
	mov r1, #0xe
	add r0, sp, #8
	strb r1, [r0, #0x12]
	mov r1, #5
	strb r1, [r0, #0x13]
	ldr r0, [r4, #0x18]
	add r2, sp, #8
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #5
	bl FUN_02018744
	mov r1, #0xd
	add r0, sp, #8
	strb r1, [r0, #0x12]
	mov r1, #4
	strb r1, [r0, #0x13]
	ldr r0, [r4, #0x18]
	mov r1, #6
	add r2, sp, #8
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #6
	bl FUN_02018744
	mov r1, #0xc
	add r0, sp, #8
	strb r1, [r0, #0x12]
	mov r1, #3
	strb r1, [r0, #0x13]
	ldr r0, [r4, #0x18]
	mov r1, #7
	add r2, sp, #8
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #7
	bl FUN_02018744
	mov r0, #0
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #1
	mov r1, #0
	bl FUN_0201797C
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	mov r0, #3
	mov r1, #0
	bl FUN_0201797C
	mov r0, #4
	mov r1, #0
	bl FUN_0201797C
	mov r0, #5
	mov r1, #0
	bl FUN_0201797C
	mov r0, #6
	mov r1, #0
	bl FUN_0201797C
	mov r0, #7
	mov r1, #0
	bl FUN_0201797C
	add r0, r4, #0
	bl MOD59_021D8058
	mov r0, #0
	str r0, [r4, #0x78]
	add sp, #0x78
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7954: .word MOD59_021D9F18
_021D7958: .word MOD59_021D9DCC
_021D795C: .word MOD59_021D9EA0
_021D7960: .word 0x000003E2
_021D7964: .word 0x000003D9
_021D7968: .word MOD59_021D9EBC
	thumb_func_end MOD59_021D778C

	thumb_func_start MOD59_021D796C
MOD59_021D796C: ; 0x021D796C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #1
	mov r1, #0
	bl FUN_0201797C
	mov r0, #2
	mov r1, #0
	bl FUN_0201797C
	mov r0, #3
	mov r1, #0
	bl FUN_0201797C
	mov r0, #4
	mov r1, #0
	bl FUN_0201797C
	mov r0, #5
	mov r1, #0
	bl FUN_0201797C
	mov r0, #6
	mov r1, #0
	bl FUN_0201797C
	mov r0, #7
	mov r1, #0
	bl FUN_0201797C
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	mov r1, #7
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD59_021D796C

	thumb_func_start MOD59_021D79F8
MOD59_021D79F8: ; 0x021D79F8
	push {r4, lr}
	add r4, r0, #0
	ldr r2, _021D7A30 ; =0x00000155
	ldr r3, [r4]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	str r0, [r4, #0x4c]
	bl FUN_0201BD5C
	mov r0, #0
	ldr r3, [r4]
	add r1, r0, #0
	mov r2, #6
	bl FUN_020142EC
	str r0, [r4, #0x60]
	ldr r0, [r4]
	bl ScrStrBufs_new
	str r0, [r4, #0x64]
	mov r0, #0
	str r0, [r4, #0x50]
	str r0, [r4, #0x54]
	str r0, [r4, #0x2c]
	pop {r4, pc}
	nop
_021D7A30: .word 0x00000155
	thumb_func_end MOD59_021D79F8

	thumb_func_start MOD59_021D7A34
MOD59_021D7A34: ; 0x021D7A34
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x64]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x60]
	bl FUN_020143D0
	ldr r0, [r4, #0x4c]
	bl DestroyMsgData
	pop {r4, pc}
	thumb_func_end MOD59_021D7A34

	thumb_func_start MOD59_021D7A4C
MOD59_021D7A4C: ; 0x021D7A4C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02014590
	str r0, [r4, #0x68]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD59_021D7A4C

	thumb_func_start MOD59_021D7A5C
MOD59_021D7A5C: ; 0x021D7A5C
	ldr r3, _021D7A64 ; =FUN_020145A8
	ldr r0, [r0, #0x68]
	bx r3
	nop
_021D7A64: .word FUN_020145A8
	thumb_func_end MOD59_021D7A5C

	thumb_func_start MOD59_021D7A68
MOD59_021D7A68: ; 0x021D7A68
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r3, r0, #0
	add r6, r2, #0
	mov r5, #0
	cmp r4, #6
	bhi _021D7A92
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7A84: ; jump table
	.short _021D7A92 - _021D7A84 - 2 ; case 0
	.short _021D7A98 - _021D7A84 - 2 ; case 1
	.short _021D7A9E - _021D7A84 - 2 ; case 2
	.short _021D7A92 - _021D7A84 - 2 ; case 3
	.short _021D7AA4 - _021D7A84 - 2 ; case 4
	.short _021D7AAA - _021D7A84 - 2 ; case 5
	.short _021D7AB0 - _021D7A84 - 2 ; case 6
_021D7A92:
	mov r1, #1
	mov r0, #0
	b _021D7AB4
_021D7A98:
	mov r1, #2
	add r0, r5, #0
	b _021D7AB4
_021D7A9E:
	mov r1, #4
	add r0, r5, #0
	b _021D7AB4
_021D7AA4:
	mov r1, #1
	add r0, r1, #0
	b _021D7AB4
_021D7AAA:
	mov r1, #2
	mov r0, #1
	b _021D7AB4
_021D7AB0:
	mov r1, #4
	mov r0, #1
_021D7AB4:
	ldr r2, [r3, #0x78]
	cmp r2, #3
	bls _021D7ABC
	b _021D7BDE
_021D7ABC:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D7AC8: ; jump table
	.short _021D7AD0 - _021D7AC8 - 2 ; case 0
	.short _021D7B2C - _021D7AC8 - 2 ; case 1
	.short _021D7B7C - _021D7AC8 - 2 ; case 2
	.short _021D7BD0 - _021D7AC8 - 2 ; case 3
_021D7AD0:
	cmp r6, #0
	bne _021D7B1A
	mov r2, #0
	str r2, [r3, #0x7c]
	add r2, r3, #0
	mov r6, #0x10
	add r2, #0x80
	str r6, [r2]
	mov r2, #1
	str r2, [r3, #0x78]
	cmp r0, #0
	bne _021D7AFC
	add r0, r3, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r2, #0xe
	str r0, [sp]
	ldr r0, _021D7BE4 ; =0x04000050
	ldr r3, [r3, #0x7c]
	bl G2x_SetBlendAlpha_
	b _021D7B0E
_021D7AFC:
	add r0, r3, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r2, #0xe
	str r0, [sp]
	ldr r0, _021D7BE8 ; =0x04001050
	ldr r3, [r3, #0x7c]
	bl G2x_SetBlendAlpha_
_021D7B0E:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	mov r1, #1
	bl FUN_0201797C
	b _021D7BDE
_021D7B1A:
	mov r0, #0x10
	str r0, [r3, #0x7c]
	add r0, r3, #0
	mov r1, #0
	add r0, #0x80
	str r1, [r0]
	mov r0, #2
	str r0, [r3, #0x78]
	b _021D7BDE
_021D7B2C:
	add r2, r3, #0
	add r2, #0x80
	ldr r2, [r2]
	cmp r2, #0
	beq _021D7B76
	ldr r2, [r3, #0x7c]
	add r2, r2, #1
	str r2, [r3, #0x7c]
	add r2, r3, #0
	add r2, #0x80
	ldr r2, [r2]
	sub r4, r2, #1
	add r2, r3, #0
	add r2, #0x80
	str r4, [r2]
	cmp r0, #0
	bne _021D7B62
	add r0, r3, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r2, #0xe
	str r0, [sp]
	ldr r0, _021D7BE4 ; =0x04000050
	ldr r3, [r3, #0x7c]
	bl G2x_SetBlendAlpha_
	b _021D7BDE
_021D7B62:
	add r0, r3, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r2, #0xe
	str r0, [sp]
	ldr r0, _021D7BE8 ; =0x04001050
	ldr r3, [r3, #0x7c]
	bl G2x_SetBlendAlpha_
	b _021D7BDE
_021D7B76:
	mov r0, #3
	str r0, [r3, #0x78]
	b _021D7BDE
_021D7B7C:
	ldr r2, [r3, #0x7c]
	cmp r2, #0
	beq _021D7BC0
	sub r2, r2, #1
	str r2, [r3, #0x7c]
	add r2, r3, #0
	add r2, #0x80
	ldr r2, [r2]
	add r4, r2, #1
	add r2, r3, #0
	add r2, #0x80
	str r4, [r2]
	cmp r0, #0
	bne _021D7BAC
	add r0, r3, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r2, #0xe
	str r0, [sp]
	ldr r0, _021D7BE4 ; =0x04000050
	ldr r3, [r3, #0x7c]
	bl G2x_SetBlendAlpha_
	b _021D7BDE
_021D7BAC:
	add r0, r3, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r2, #0xe
	str r0, [sp]
	ldr r0, _021D7BE8 ; =0x04001050
	ldr r3, [r3, #0x7c]
	bl G2x_SetBlendAlpha_
	b _021D7BDE
_021D7BC0:
	mov r0, #3
	str r0, [r3, #0x78]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	mov r1, #0
	bl FUN_0201797C
	b _021D7BDE
_021D7BD0:
	ldr r0, _021D7BE4 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r0, _021D7BE8 ; =0x04001050
	mov r5, #1
	strh r1, [r0]
	str r1, [r3, #0x78]
_021D7BDE:
	add r0, r5, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D7BE4: .word 0x04000050
_021D7BE8: .word 0x04001050
	thumb_func_end MOD59_021D7A68

	thumb_func_start MOD59_021D7BEC
MOD59_021D7BEC: ; 0x021D7BEC
	add r2, r0, #0
	add r2, #0x90
	ldr r2, [r2]
	cmp r2, r1
	bge _021D7C06
	add r1, r0, #0
	add r1, #0x90
	ldr r1, [r1]
	add r0, #0x90
	add r1, r1, #1
	str r1, [r0]
	mov r0, #0
	bx lr
_021D7C06:
	mov r1, #0
	add r0, #0x90
	str r1, [r0]
	mov r0, #1
	bx lr
	thumb_func_end MOD59_021D7BEC

	thumb_func_start MOD59_021D7C10
MOD59_021D7C10: ; 0x021D7C10
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	lsl r0, r2, #0x18
	add r4, r1, #0
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	lsl r1, r4, #0x18
	mov r2, #0
	ldr r0, [r5, #0x18]
	lsr r1, r1, #0x18
	add r3, r2, #0
	bl FUN_020186B4
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x18]
	lsr r1, r1, #0x18
	bl FUN_02017CD0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD59_021D7C10

	thumb_func_start MOD59_021D7C44
MOD59_021D7C44: ; 0x021D7C44
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5, #0x50]
	add r7, r1, #0
	mov r4, #0
	cmp r0, #0
	beq _021D7C5E
	cmp r0, #1
	beq _021D7D1C
	cmp r0, #2
	beq _021D7D36
	b _021D7D54
_021D7C5E:
	add r1, r5, #0
	ldr r0, [r5, #0x18]
	ldr r2, _021D7D5C ; =0x021D9DB8
	add r1, #0x1c
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	add r0, r5, #0
	add r2, r4, #0
	add r0, #0x1c
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	add r0, r5, #0
	ldr r2, _021D7D60 ; =0x000003E2
	add r0, #0x1c
	add r1, r4, #0
	mov r3, #4
	bl FUN_0200D0BC
	mov r0, #1
	bl FUN_02002B60
	add r0, r4, #0
	bl FUN_02002B7C
	mov r0, #1
	ldr r1, [r5]
	lsl r0, r0, #0xa
	bl String_ctor
	add r6, r0, #0
	mov r0, #1
	ldr r1, [r5]
	lsl r0, r0, #0xa
	bl String_ctor
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0x4c]
	add r1, r7, #0
	add r2, r6, #0
	bl ReadMsgDataIntoString
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r2, [r5, #0x70]
	add r3, r5, #0
	add r3, #0x84
	ldr r0, [r5, #0x64]
	ldr r2, [r2, #0x18]
	ldr r3, [r3]
	add r1, r4, #0
	bl BufferString
	mov r1, #1
	str r1, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r2, [r5, #0x74]
	ldr r0, [r5, #0x64]
	ldr r2, [r2, #0x18]
	add r3, r4, #0
	bl BufferString
	ldr r0, [r5, #0x64]
	ldr r1, [r5, #0x5c]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	ldr r0, [r5, #8]
	bl FUN_02024FF4
	add r3, r4, #0
	str r3, [sp]
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r5, #0
	ldr r2, [r5, #0x5c]
	add r0, #0x1c
	mov r1, #1
	bl AddTextPrinterParameterized
	str r0, [r5, #0x58]
	mov r0, #1
	str r0, [r5, #0x50]
	b _021D7D54
_021D7D1C:
	ldr r0, [r5, #0x58]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D7D54
	ldr r0, [r5, #0x5c]
	bl String_dtor
	mov r0, #2
	str r0, [r5, #0x50]
	b _021D7D54
_021D7D36:
	cmp r2, #0
	bne _021D7D46
	ldr r0, _021D7D64 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	and r0, r1
	cmp r0, #1
	bne _021D7D54
_021D7D46:
	add r0, r5, #0
	add r0, #0x1c
	bl FUN_02019178
	mov r0, #0
	str r0, [r5, #0x50]
	mov r4, #1
_021D7D54:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021D7D5C: .word MOD59_021D9DB8
_021D7D60: .word 0x000003E2
_021D7D64: .word gMain
	thumb_func_end MOD59_021D7C44

	thumb_func_start MOD59_021D7D68
MOD59_021D7D68: ; 0x021D7D68
	push {r3, lr}
	cmp r2, #0
	bne _021D7D74
	ldr r0, _021D7D78 ; =0x000005DC
	bl FUN_020054C8
_021D7D74:
	pop {r3, pc}
	nop
_021D7D78: .word 0x000005DC
	thumb_func_end MOD59_021D7D68

	thumb_func_start MOD59_021D7D7C
MOD59_021D7D7C: ; 0x021D7D7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #0x2c]
	add r4, r2, #0
	cmp r0, #0
	beq _021D7D94
	cmp r0, #1
	beq _021D7E4C
	b _021D7E96
_021D7D94:
	cmp r1, #0
	beq _021D7DA0
	cmp r1, #1
	beq _021D7DA8
	cmp r1, #2
	beq _021D7DB0
_021D7DA0:
	ldr r2, _021D7E9C ; =0x021D9DA8
	ldr r4, _021D7EA0 ; =0x021D9E0C
	mov r6, #2
	b _021D7DC4
_021D7DA8:
	ldr r2, _021D7EA4 ; =0x021D9DB0
	ldr r4, _021D7EA8 ; =0x021D9E58
	mov r6, #3
	b _021D7DC4
_021D7DB0:
	ldr r0, _021D7EAC ; =gGameVersion
	ldr r2, _021D7EB0 ; =0x021D9DA0
	ldrb r0, [r0]
	cmp r0, #0xa
	bne _021D7DC0
	ldr r4, _021D7EB4 ; =0x021D9F40
	mov r6, #5
	b _021D7DC4
_021D7DC0:
	ldr r4, _021D7EB8 ; =0x021D9F68
	mov r6, #5
_021D7DC4:
	add r1, r5, #0
	ldr r0, [r5, #0x18]
	add r1, #0x30
	bl FUN_02019150
	ldr r1, [r5]
	add r0, r6, #0
	bl ListMenu_ctor
	mov r7, #0
	str r0, [r5, #0x44]
	cmp r6, #0
	ble _021D7DF2
_021D7DDE:
	ldr r0, [r5, #0x44]
	ldr r1, [r5, #0x4c]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl ListMenu_ItemFromMsgData
	add r7, r7, #1
	add r4, #8
	cmp r7, r6
	blt _021D7DDE
_021D7DF2:
	ldr r4, _021D7EBC ; =0x021D9EF8
	add r3, sp, #4
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5, #0x44]
	str r0, [sp, #4]
	lsl r0, r6, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #4
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	ldr r0, _021D7EC0 ; =MOD59_021D7D68
	mov r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x30
	str r0, [sp, #0x10]
	ldr r3, [r5]
	add r0, r2, #0
	lsl r3, r3, #0x18
	add r2, r1, #0
	lsr r3, r3, #0x18
	bl FUN_020010A8
	str r0, [r5, #0x40]
	ldr r0, [sp, #0x10]
	ldr r2, _021D7EC4 ; =0x000003D9
	mov r1, #1
	mov r3, #3
	bl FUN_0200CCA4
	add r0, r5, #0
	add r0, #0x30
	bl FUN_020191D0
	mov r0, #1
	str r0, [r5, #0x2c]
	b _021D7E96
_021D7E4C:
	ldr r0, [r5, #0x40]
	bl FUN_02001204
	mov r1, #0
	mvn r1, r1
	str r0, [r5, #0x48]
	cmp r0, r1
	beq _021D7E96
	sub r1, r1, #1
	cmp r0, r1
	bne _021D7E66
	cmp r4, #1
	beq _021D7E96
_021D7E66:
	add r0, r5, #0
	add r0, #0x30
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r5, #0
	add r0, #0x30
	bl FUN_02019178
	mov r1, #0
	ldr r0, [r5, #0x40]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, [r5, #0x44]
	bl ListMenu_dtor
	ldr r0, _021D7EC8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0
	str r0, [r5, #0x2c]
	mov r0, #1
	str r0, [sp]
_021D7E96:
	ldr r0, [sp]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7E9C: .word MOD59_021D9DA8
_021D7EA0: .word MOD59_021D9E0C
_021D7EA4: .word MOD59_021D9DB0
_021D7EA8: .word MOD59_021D9E58
_021D7EAC: .word gGameVersion
_021D7EB0: .word MOD59_021D9DA0
_021D7EB4: .word MOD59_021D9F40
_021D7EB8: .word MOD59_021D9F68
_021D7EBC: .word MOD59_021D9EF8
_021D7EC0: .word MOD59_021D7D68
_021D7EC4: .word 0x000003D9
_021D7EC8: .word 0x000005DC
	thumb_func_end MOD59_021D7D7C

	thumb_func_start MOD59_021D7ECC
MOD59_021D7ECC: ; 0x021D7ECC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	str r1, [sp, #0x10]
	ldr r1, [r4, #0x54]
	add r6, r2, #0
	add r7, r3, #0
	mov r5, #0
	cmp r1, #5
	bls _021D7EE2
	b _021D803C
_021D7EE2:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7EEE: ; jump table
	.short _021D7EFA - _021D7EEE - 2 ; case 0
	.short _021D7FD8 - _021D7EEE - 2 ; case 1
	.short _021D7FE4 - _021D7EEE - 2 ; case 2
	.short _021D7FF6 - _021D7EEE - 2 ; case 3
	.short _021D8016 - _021D7EEE - 2 ; case 4
	.short _021D8028 - _021D7EEE - 2 ; case 5
_021D7EFA:
	add r0, r5, #0
	add r1, r5, #0
	bl FUN_0201797C
	mov r0, #1
	ldr r1, [r4]
	lsl r0, r0, #0xa
	bl String_ctor
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x4c]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, #0x5c]
	bl ReadMsgDataIntoString
	cmp r6, #1
	add r0, sp, #0x14
	bne _021D7F7C
	ldr r1, _021D8044 ; =0x021D9D90
	ldrh r2, [r1, #8]
	strh r2, [r0]
	ldrh r2, [r1, #0xa]
	strh r2, [r0, #2]
	ldrh r2, [r1, #0xc]
	ldrh r1, [r1, #0xe]
	strh r2, [r0, #4]
	strh r1, [r0, #6]
	ldr r0, [r4, #0x5c]
	bl FUN_02002F90
	mov r1, #0xc
	sub r2, r1, r0
	add r1, sp, #0x14
	strb r2, [r1, #2]
	lsl r0, r0, #1
	strb r0, [r1, #4]
	add r1, r4, #0
	ldr r0, [r4, #0x18]
	add r1, #0x1c
	add r2, sp, #0x14
	bl FUN_02019150
	add r1, r5, #0
	mov r0, #0xc0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x1c
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	add r1, r5, #0
	str r1, [sp]
	ldr r0, _021D8048 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x1c
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	b _021D7FCC
_021D7F7C:
	ldr r1, _021D8044 ; =0x021D9D90
	add r2, sp, #0x14
	ldrh r3, [r1]
	strh r3, [r0]
	ldrh r3, [r1, #2]
	strh r3, [r0, #2]
	ldrh r3, [r1, #4]
	ldrh r1, [r1, #6]
	strh r3, [r0, #4]
	strh r1, [r0, #6]
	ldr r1, [sp, #0x30]
	strb r7, [r0, #2]
	strb r1, [r0, #4]
	add r1, r4, #0
	ldr r0, [r4, #0x18]
	add r1, #0x1c
	bl FUN_02019150
	add r1, r5, #0
	mov r0, #0xc0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x1c
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	add r1, r5, #0
	str r1, [sp]
	ldr r0, _021D804C ; =0x000F0200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x5c]
	add r0, #0x1c
	add r3, r1, #0
	bl AddTextPrinterParameterized2
_021D7FCC:
	ldr r0, [r4, #0x5c]
	bl String_dtor
	mov r0, #1
	str r0, [r4, #0x54]
	b _021D803C
_021D7FD8:
	add r0, #0x1c
	bl FUN_020191D0
	mov r0, #2
	str r0, [r4, #0x54]
	b _021D803C
_021D7FE4:
	add r1, r5, #0
	add r2, r5, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D803C
	mov r0, #3
	str r0, [r4, #0x54]
	b _021D803C
_021D7FF6:
	ldr r0, _021D8050 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	and r0, r1
	cmp r0, #1
	beq _021D800A
	mov r0, #2
	and r0, r1
	cmp r0, #2
	bne _021D803C
_021D800A:
	ldr r0, _021D8054 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #4
	str r0, [r4, #0x54]
	b _021D803C
_021D8016:
	add r1, r5, #0
	mov r2, #1
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D803C
	mov r0, #5
	str r0, [r4, #0x54]
	b _021D803C
_021D8028:
	add r0, #0x1c
	bl FUN_02019178
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	add r0, r5, #0
	str r0, [r4, #0x54]
	mov r5, #1
_021D803C:
	add r0, r5, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D8044: .word MOD59_021D9D90
_021D8048: .word 0x00010200
_021D804C: .word 0x000F0200
_021D8050: .word gMain
_021D8054: .word 0x000005DC
	thumb_func_end MOD59_021D7ECC

	thumb_func_start MOD59_021D8058
MOD59_021D8058: ; 0x021D8058
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	add r5, r0, #0
	str r1, [sp, #8]
	ldr r0, [r5]
	mov r3, #3
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x18]
	mov r0, #0x7d
	bl FUN_0200687C
	mov r0, #0
	ldr r3, [r5]
	mov r1, #0x20
	add r2, r0, #0
	bl FUN_02017F18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #0x17
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x18]
	mov r0, #0x7d
	mov r3, #7
	bl FUN_0200687C
	ldr r0, _021D80F8 ; =gGameVersion
	ldrb r0, [r0]
	cmp r0, #0xa
	bne _021D80A6
	mov r1, #1
	mov r4, #0x18
	b _021D80AA
_021D80A6:
	mov r1, #2
	mov r4, #0x19
_021D80AA:
	mov r0, #0x60
	str r0, [sp]
	ldr r0, [r5]
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x7d
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #0xa0
	str r0, [sp]
	ldr r0, [r5]
	add r1, r4, #0
	str r0, [sp, #4]
	mov r0, #0x7d
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	add r0, r5, #0
	bl MOD59_021D80FC
	add r0, r5, #0
	bl MOD59_021D8140
	add r0, r5, #0
	bl MOD59_021D8234
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D80F8: .word gGameVersion
	thumb_func_end MOD59_021D8058

	thumb_func_start MOD59_021D80FC
MOD59_021D80FC: ; 0x021D80FC
	push {r4, r5, lr}
	sub sp, #0x24
	ldr r5, _021D813C ; =0x021D9E1C
	add r3, r0, #0
	ldmia r5!, {r0, r1}
	add r4, sp, #0x10
	add r2, r4, #0
	stmia r4!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	str r0, [r4]
	add r0, r3, #0
	add r0, #0x88
	ldrb r1, [r0]
	cmp r1, #5
	bhs _021D8138
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r3]
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r1, [r2, r1]
	ldr r2, [r3, #0x18]
	mov r0, #0x7d
	mov r3, #3
	bl FUN_020068C8
_021D8138:
	add sp, #0x24
	pop {r4, r5, pc}
	.align 2, 0
_021D813C: .word MOD59_021D9E1C
	thumb_func_end MOD59_021D80FC

	thumb_func_start MOD59_021D8140
MOD59_021D8140: ; 0x021D8140
	push {r3, r4, r5, lr}
	sub sp, #0x68
	ldr r5, _021D8230 ; =0x021D9F90
	add r4, r0, #0
	add r3, sp, #0x10
	mov r2, #0xb
_021D814C:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D814C
	add r0, r4, #0
	add r0, #0x89
	ldrb r1, [r0]
	cmp r1, #0
	beq _021D81BE
	cmp r1, #0xc
	bhs _021D81BE
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	lsl r2, r1, #3
	str r0, [sp, #0xc]
	add r1, sp, #0x10
	ldr r1, [r1, r2]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	mov r3, #1
	bl FUN_0200687C
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [r4]
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0x89
	ldrb r1, [r1]
	mov r0, #0x7d
	mov r3, #0xe0
	lsl r2, r1, #3
	add r1, sp, #0x14
	ldr r1, [r1, r2]
	mov r2, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	mov r3, #1
	bl FUN_020068C8
	add r0, r4, #0
	mov r1, #1
	mov r2, #7
	bl MOD59_021D7C10
_021D81BE:
	add r0, r4, #0
	add r0, #0x8a
	ldrb r1, [r0]
	cmp r1, #0
	beq _021D822A
	cmp r1, #0xc
	bhs _021D822A
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	lsl r2, r1, #3
	str r0, [sp, #0xc]
	add r1, sp, #0x10
	ldr r1, [r1, r2]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [r4]
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0x8a
	ldrb r1, [r1]
	mov r0, #0x7d
	add r3, r0, #0
	lsl r2, r1, #3
	add r1, sp, #0x14
	ldr r1, [r1, r2]
	mov r2, #0
	add r3, #0x83
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x16
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	mov r3, #2
	bl FUN_020068C8
	add r0, r4, #0
	mov r1, #2
	mov r2, #8
	bl MOD59_021D7C10
_021D822A:
	add sp, #0x68
	pop {r3, r4, r5, pc}
	nop
_021D8230: .word MOD59_021D9F90
	thumb_func_end MOD59_021D8140

	thumb_func_start MOD59_021D8234
MOD59_021D8234: ; 0x021D8234
	push {r4, r5, lr}
	sub sp, #0x24
	ldr r5, _021D829C ; =0x021D9E30
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x10
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	add r0, #0x8b
	ldrb r1, [r0]
	cmp r1, #5
	bhs _021D8296
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	ldr r1, [r2, r1]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	mov r3, #7
	bl FUN_020068C8
	add r0, r4, #0
	add r0, #0x8b
	ldrb r0, [r0]
	cmp r0, #1
	bne _021D8288
	add r0, r4, #0
	mov r1, #7
	mov r2, #3
	bl MOD59_021D7C10
	add sp, #0x24
	pop {r4, r5, pc}
_021D8288:
	cmp r0, #2
	bne _021D8296
	add r0, r4, #0
	mov r1, #7
	mov r2, #2
	bl MOD59_021D7C10
_021D8296:
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D829C: .word MOD59_021D9E30
	thumb_func_end MOD59_021D8234

	thumb_func_start MOD59_021D82A0
MOD59_021D82A0: ; 0x021D82A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	mov r2, #0
	str r2, [sp]
	str r2, [sp, #4]
	add r5, r0, #0
	ldr r1, _021D83EC ; =0x000001BE
	str r2, [sp, #8]
	add r0, sp, #0x10
	mov r3, #2
	bl FUN_02068C00
	ldr r0, [r5]
	mov r1, #0xc8
	bl AllocFromHeap
	add r7, r0, #0
	ldr r2, _021D83F0 ; =0x021D9FE8
	mov r1, #0
	add r3, r7, #0
_021D82C8:
	ldrb r0, [r2]
	add r1, r1, #1
	add r2, r2, #1
	add r0, r0, #1
	strh r0, [r3]
	add r3, r3, #2
	cmp r1, #0x64
	blt _021D82C8
	add r1, sp, #0x10
	ldrh r0, [r1]
	ldrh r1, [r1, #2]
	ldr r2, [r5]
	bl FUN_0201244C
	add r1, sp, #0x10
	add r4, r0, #0
	ldrh r0, [r1]
	ldrh r1, [r1, #4]
	ldr r2, [r5]
	bl FUN_02012470
	mov r2, #0
	add r6, r0, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #9
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x18]
	mov r1, #2
	add r3, r2, #0
	bl FUN_02018540
	mov r3, #0xb
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5, #0x18]
	mov r1, #2
	add r2, r7, #0
	bl FUN_02018148
	add r0, r5, #0
	mov r1, #2
	mov r2, #9
	bl MOD59_021D7C10
	ldr r3, [r5]
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	mov r0, #1
	str r0, [sp]
	mov r3, #0x32
	ldr r0, [r5, #0x18]
	mov r1, #2
	add r2, r4, #0
	lsl r3, r3, #6
	bl FUN_02017E14
	mov r3, #0x20
	add r2, r3, #0
	mov r0, #2
	add r1, r6, #0
	add r3, #0xe0
	bl FUN_02017FB4
	mov r3, #0x12
	ldr r1, _021D83F4 ; =0x021D9ED8
	mov r0, #2
	mov r2, #0x20
	lsl r3, r3, #4
	bl FUN_02017FB4
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x18]
	mov r1, #5
	add r3, r2, #0
	bl FUN_02018540
	mov r0, #7
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5, #0x18]
	mov r1, #5
	add r2, r7, #0
	mov r3, #0xb
	bl FUN_02018148
	add r0, r5, #0
	mov r1, #5
	mov r2, #0xa
	bl MOD59_021D7C10
	ldr r3, [r5]
	mov r0, #5
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	mov r0, #1
	str r0, [sp]
	mov r3, #0x32
	ldr r0, [r5, #0x18]
	mov r1, #5
	add r2, r4, #0
	lsl r3, r3, #6
	bl FUN_02017E14
	mov r0, #5
	add r1, r6, #0
	mov r2, #0x20
	lsl r3, r0, #6
	bl FUN_02017FB4
	mov r0, #5
	ldr r1, _021D83F4 ; =0x021D9ED8
	mov r2, #0x20
	lsl r3, r0, #6
	bl FUN_02017FB4
	add r0, r6, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FreeToHeap
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D83EC: .word 0x000001BE
_021D83F0: .word MOD59_021D9FE8
_021D83F4: .word MOD59_021D9ED8
	thumb_func_end MOD59_021D82A0

	thumb_func_start MOD59_021D83F8
MOD59_021D83F8: ; 0x021D83F8
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x26
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	mov r3, #6
	bl FUN_020068C8
	add r0, r4, #0
	mov r1, #6
	mov r2, #9
	bl MOD59_021D7C10
	mov r0, #0x60
	str r0, [sp]
	ldr r0, [r4]
	mov r1, #0x27
	str r0, [sp, #4]
	mov r0, #0x7d
	mov r2, #4
	mov r3, #0xe0
	bl FUN_02006930
	ldr r3, [r4]
	mov r0, #6
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0x1e
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	mov r3, #6
	bl FUN_0200687C
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD59_021D83F8

	thumb_func_start MOD59_021D8460
MOD59_021D8460: ; 0x021D8460
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r6, #0
	cmp r2, #0
	bne _021D849C
	ldr r0, [r5, #0x18]
	bl FUN_02017B48
	cmp r0, #0
	beq _021D8498
	cmp r0, #0
	ldr r0, [r5, #0x18]
	ble _021D848A
	lsl r1, r4, #0x18
	lsr r1, r1, #0x18
	mov r2, #2
	mov r3, #4
	bl FUN_020179E0
	b _021D84E2
_021D848A:
	lsl r1, r4, #0x18
	lsr r1, r1, #0x18
	mov r2, #1
	mov r3, #4
	bl FUN_020179E0
	b _021D84E2
_021D8498:
	mov r6, #1
	b _021D84E2
_021D849C:
	cmp r2, #1
	bne _021D84C2
	ldr r0, [r5, #0x18]
	bl FUN_02017B48
	add r1, r6, #0
	sub r1, #0x30
	cmp r0, r1
	beq _021D84BE
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x18]
	lsr r1, r1, #0x18
	mov r2, #2
	mov r3, #4
	bl FUN_020179E0
	b _021D84E2
_021D84BE:
	mov r6, #1
	b _021D84E2
_021D84C2:
	cmp r2, #2
	bne _021D84E2
	ldr r0, [r5, #0x18]
	bl FUN_02017B48
	cmp r0, #0
	beq _021D84E0
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x18]
	lsr r1, r1, #0x18
	mov r2, #1
	mov r3, #4
	bl FUN_020179E0
	b _021D84E2
_021D84E0:
	mov r6, #1
_021D84E2:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD59_021D8460

	thumb_func_start MOD59_021D84E8
MOD59_021D84E8: ; 0x021D84E8
	add r1, r0, #0
	mov r2, #0
	add r1, #0x8c
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0x8d
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0x8e
	strb r2, [r1]
	add r0, #0x8f
	strb r2, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD59_021D84E8

	thumb_func_start MOD59_021D8504
MOD59_021D8504: ; 0x021D8504
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r4, r0, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D858E
	add r0, r4, #0
	add r0, #0x8d
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D8526
	add r0, r4, #0
	add r0, #0x8d
	ldrb r0, [r0]
	sub r1, r0, #1
	b _021D8546
_021D8526:
	add r0, r4, #0
	add r0, #0x8c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x8c
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x8c
	ldrb r1, [r0]
	mov r0, #3
	and r1, r0
	add r0, r4, #0
	add r0, #0x8c
	strb r1, [r0]
	mov r1, #4
_021D8546:
	add r0, r4, #0
	add r0, #0x8d
	strb r1, [r0]
	mov r0, #0xa
	str r0, [sp]
	ldr r0, _021D860C ; =0x04000050
	mov r1, #4
	mov r2, #8
	mov r3, #6
	bl G2x_SetBlendAlpha_
	ldr r5, _021D8610 ; =0x021D9DEC
	add r3, sp, #0x20
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	add r1, r4, #0
	str r0, [sp, #0xc]
	add r1, #0x8c
	ldrb r1, [r1]
	mov r0, #0x7d
	mov r3, #1
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	ldr r2, [r4, #0x18]
	bl FUN_0200687C
	add sp, #0x30
	pop {r3, r4, r5, pc}
_021D858E:
	add r0, r4, #0
	add r0, #0x8f
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D85A2
	add r0, r4, #0
	add r0, #0x8f
	ldrb r0, [r0]
	sub r1, r0, #1
	b _021D85C2
_021D85A2:
	add r0, r4, #0
	add r0, #0x8e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x8e
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x8e
	ldrb r1, [r0]
	mov r0, #3
	and r1, r0
	add r0, r4, #0
	add r0, #0x8e
	strb r1, [r0]
	mov r1, #4
_021D85C2:
	add r0, r4, #0
	add r0, #0x8f
	strb r1, [r0]
	mov r0, #0xa
	str r0, [sp]
	ldr r0, _021D860C ; =0x04000050
	mov r1, #2
	mov r2, #8
	mov r3, #6
	bl G2x_SetBlendAlpha_
	ldr r5, _021D8614 ; =0x021D9DFC
	add r3, sp, #0x10
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	add r1, r4, #0
	str r0, [sp, #0xc]
	add r1, #0x8e
	ldrb r1, [r1]
	mov r0, #0x7d
	mov r3, #2
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	ldr r2, [r4, #0x18]
	bl FUN_0200687C
	add sp, #0x30
	pop {r3, r4, r5, pc}
	nop
_021D860C: .word 0x04000050
_021D8610: .word MOD59_021D9DEC
_021D8614: .word MOD59_021D9DFC
	thumb_func_end MOD59_021D8504

	thumb_func_start MOD59_021D8618
MOD59_021D8618: ; 0x021D8618
	ldr r0, _021D8620 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	bx lr
	.align 2, 0
_021D8620: .word 0x04000050
	thumb_func_end MOD59_021D8618

	thumb_func_start MOD59_021D8624
MOD59_021D8624: ; 0x021D8624
	add r1, r0, #0
	mov r2, #0
	add r1, #0x94
	str r2, [r1]
	add r0, #0x98
	str r2, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD59_021D8624

	thumb_func_start MOD59_021D8634
MOD59_021D8634: ; 0x021D8634
	push {r4, r5, r6, lr}
	sub sp, #0x40
	add r3, r0, #0
	add r0, #0x98
	ldr r0, [r0]
	mov r4, #0
	cmp r0, #0
	beq _021D864E
	add r0, r3, #0
	add r0, #0x98
	ldr r0, [r0]
	sub r1, r0, #1
	b _021D865E
_021D864E:
	add r0, r3, #0
	add r0, #0x94
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r3, #0
	add r0, #0x94
	str r1, [r0]
	mov r1, #8
_021D865E:
	add r0, r3, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r3, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D8674
	ldr r6, _021D86B4 ; =0x021D9E88
	add r5, sp, #0x28
	b _021D8678
_021D8674:
	ldr r6, _021D86B8 ; =0x021D9E70
	add r5, sp, #0x10
_021D8678:
	add r2, r5, #0
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	add r0, r3, #0
	add r0, #0x94
	ldr r0, [r0]
	lsl r0, r0, #2
	ldr r1, [r2, r0]
	cmp r1, #0xff
	bne _021D8698
	mov r4, #1
	b _021D86AE
_021D8698:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r3]
	str r0, [sp, #0xc]
	ldr r2, [r3, #0x18]
	mov r0, #0x7d
	mov r3, #1
	bl FUN_0200687C
_021D86AE:
	add r0, r4, #0
	add sp, #0x40
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D86B4: .word MOD59_021D9E88
_021D86B8: .word MOD59_021D9E70
	thumb_func_end MOD59_021D8634

	thumb_func_start MOD59_021D86BC
MOD59_021D86BC: ; 0x021D86BC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r0, #0
	ldr r0, [r6]
	mov r7, #0
	cmp r0, #5
	bls _021D86CC
	b _021D890A
_021D86CC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D86D8: ; jump table
	.short _021D86E4 - _021D86D8 - 2 ; case 0
	.short _021D8728 - _021D86D8 - 2 ; case 1
	.short _021D87A6 - _021D86D8 - 2 ; case 2
	.short _021D87E0 - _021D86D8 - 2 ; case 3
	.short _021D887C - _021D86D8 - 2 ; case 4
	.short _021D88F8 - _021D86D8 - 2 ; case 5
_021D86E4:
	ldr r0, [r4, #0x18]
	mov r1, #2
	add r2, r7, #0
	add r3, r7, #0
	bl FUN_020179E0
	mov r2, #3
	add r3, r2, #0
	ldr r0, [r4, #0x18]
	mov r1, #2
	sub r3, #0x6b
	bl FUN_020179E0
	mov r0, #2
	add r1, r7, #0
	bl FUN_020178BC
	mov r0, #5
	mov r1, #1
	bl FUN_0201797C
	add r0, r4, #0
	add r2, r7, #0
	add r0, #0xa8
	str r2, [r0]
	add r0, r4, #0
	mov r1, #8
	add r0, #0xac
	str r1, [r0]
	add r4, #0xb0
	str r2, [r4]
	mov r0, #1
	str r0, [r6]
	b _021D890A
_021D8728:
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_02017B48
	ldr r0, [r4, #0x18]
	mov r1, #5
	bl FUN_02017B54
	add r1, r4, #0
	add r1, #0xb0
	ldr r3, [r1]
	add r1, r4, #0
	add r1, #0xac
	ldr r2, [r1]
	lsl r1, r2, #3
	add r1, r2, r1
	add r2, r3, #0
	mul r2, r1
	lsl r1, r3, #3
	add r1, r3, r1
	mul r1, r3
	lsr r3, r1, #0x1f
	add r3, r1, r3
	asr r1, r3, #1
	sub r5, r2, r1
	cmp r0, #0x58
	bge _021D8792
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	mov r2, #1
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xb0
	str r1, [r0]
	mov r1, #2
	ldr r0, [r4, #0x18]
	add r3, r1, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x18]
	mov r1, #5
	mov r2, #1
	mov r3, #2
	bl FUN_020179E0
	ldr r0, [r4, #0x18]
	mov r1, #5
	mov r2, #3
	add r3, r5, #0
	bl FUN_020179E0
	b _021D890A
_021D8792:
	mov r0, #5
	add r1, r7, #0
	bl FUN_0201797C
	mov r0, #0x1e
	add r4, #0xb0
	str r0, [r4]
	mov r0, #2
	str r0, [r6]
	b _021D890A
_021D87A6:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	cmp r0, #0
	beq _021D87BE
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	add r4, #0xb0
	sub r0, r0, #1
	str r0, [r4]
	b _021D890A
_021D87BE:
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	add r0, r4, #0
	add r2, r7, #0
	add r0, #0xa8
	str r2, [r0]
	add r0, r4, #0
	mov r1, #9
	add r0, #0xac
	str r1, [r0]
	add r4, #0xb0
	str r2, [r4]
	mov r0, #3
	str r0, [r6]
	b _021D890A
_021D87E0:
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_02017B48
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_02017B54
	add r0, r4, #0
	add r0, #0xb0
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0xac
	ldr r2, [r0]
	lsl r0, r2, #3
	add r0, r2, r0
	lsl r2, r1, #3
	add r2, r1, r2
	mul r0, r1
	mul r2, r1
	lsr r1, r2, #0x1f
	add r1, r2, r1
	sub r0, #0x68
	asr r1, r1, #1
	sub r5, r0, r1
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	ble _021D8846
	cmp r5, #0
	bgt _021D8846
	ldr r0, [r4, #0x18]
	mov r1, #2
	mov r2, #3
	add r3, r7, #0
	bl FUN_020179E0
	add r0, r4, #0
	add r2, r7, #0
	add r0, #0xa8
	str r2, [r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xac
	str r1, [r0]
	add r4, #0xb0
	str r2, [r4]
	mov r0, #4
	str r0, [r6]
	b _021D890A
_021D8846:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	mov r2, #1
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xb0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xa8
	str r5, [r0]
	ldr r0, [r4, #0x18]
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
	asr r5, r5, #1
	cmp r5, #0x90
	ble _021D886E
	mov r5, #0x90
_021D886E:
	ldr r0, [r4, #0x18]
	mov r1, #2
	mov r2, #3
	add r3, r5, #0
	bl FUN_020179E0
	b _021D890A
_021D887C:
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_02017B48
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl FUN_02017B54
	add r0, r4, #0
	add r0, #0xb0
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0xac
	ldr r2, [r0]
	lsl r0, r2, #3
	add r0, r2, r0
	lsl r2, r1, #3
	add r2, r1, r2
	mul r2, r1
	mul r0, r1
	lsr r1, r2, #0x1f
	add r1, r2, r1
	asr r1, r1, #1
	sub r5, r0, r1
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	ble _021D88CC
	cmp r5, #0
	bgt _021D88CC
	ldr r0, [r4, #0x18]
	mov r1, #2
	mov r2, #3
	add r3, r7, #0
	bl FUN_020179E0
	mov r0, #5
	str r0, [r6]
	b _021D890A
_021D88CC:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	mov r2, #1
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xb0
	str r1, [r0]
	mov r1, #2
	ldr r0, [r4, #0x18]
	add r3, r1, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x18]
	mov r1, #2
	mov r2, #3
	add r3, r5, #0
	bl FUN_020179E0
	add r4, #0xa8
	str r5, [r4]
	b _021D890A
_021D88F8:
	ldr r0, _021D8910 ; =0x000001BE
	bl FUN_02005578
	add r0, r4, #0
	mov r1, #2
	mov r2, #8
	bl MOD59_021D7C10
	mov r7, #1
_021D890A:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8910: .word 0x000001BE
	thumb_func_end MOD59_021D86BC

	thumb_func_start MOD59_021D8914
MOD59_021D8914: ; 0x021D8914
	ldr r3, _021D891C ; =FUN_020178BC
	mov r0, #2
	mov r1, #1
	bx r3
	.align 2, 0
_021D891C: .word FUN_020178BC
	thumb_func_end MOD59_021D8914

	thumb_func_start MOD59_021D8920
MOD59_021D8920: ; 0x021D8920
	push {r4, r5, r6, lr}
	sub sp, #0x30
	add r4, r0, #0
	ldr r1, [r4, #0xc]
	mov r5, #0
	cmp r1, #0x6d
	bls _021D8932
	bl _021D985C
_021D8932:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D893E: ; jump table
	.short _021D8A1A - _021D893E - 2 ; case 0
	.short _021D8A5A - _021D893E - 2 ; case 1
	.short _021D8A76 - _021D893E - 2 ; case 2
	.short _021D8A92 - _021D893E - 2 ; case 3
	.short _021D8ADE - _021D893E - 2 ; case 4
	.short _021D8AEE - _021D893E - 2 ; case 5
	.short _021D8B02 - _021D893E - 2 ; case 6
	.short _021D8B16 - _021D893E - 2 ; case 7
	.short _021D8B60 - _021D893E - 2 ; case 8
	.short _021D8B80 - _021D893E - 2 ; case 9
	.short _021D8BA0 - _021D893E - 2 ; case 10
	.short _021D8BD8 - _021D893E - 2 ; case 11
	.short _021D8BE8 - _021D893E - 2 ; case 12
	.short _021D8C02 - _021D893E - 2 ; case 13
	.short _021D8C16 - _021D893E - 2 ; case 14
	.short _021D8C30 - _021D893E - 2 ; case 15
	.short _021D8C44 - _021D893E - 2 ; case 16
	.short _021D8C5E - _021D893E - 2 ; case 17
	.short _021D8C72 - _021D893E - 2 ; case 18
	.short _021D8C98 - _021D893E - 2 ; case 19
	.short _021D8CA8 - _021D893E - 2 ; case 20
	.short _021D8CBC - _021D893E - 2 ; case 21
	.short _021D8CF8 - _021D893E - 2 ; case 22
	.short _021D8D1C - _021D893E - 2 ; case 23
	.short _021D8D3E - _021D893E - 2 ; case 24
	.short _021D8D7C - _021D893E - 2 ; case 25
	.short _021D8D94 - _021D893E - 2 ; case 26
	.short _021D8DD6 - _021D893E - 2 ; case 27
	.short _021D8DEA - _021D893E - 2 ; case 28
	.short _021D8E34 - _021D893E - 2 ; case 29
	.short _021D8E44 - _021D893E - 2 ; case 30
	.short _021D8E58 - _021D893E - 2 ; case 31
	.short _021D8E90 - _021D893E - 2 ; case 32
	.short _021D8EA0 - _021D893E - 2 ; case 33
	.short _021D8EBE - _021D893E - 2 ; case 34
	.short _021D8ED6 - _021D893E - 2 ; case 35
	.short _021D8EF0 - _021D893E - 2 ; case 36
	.short _021D8F0A - _021D893E - 2 ; case 37
	.short _021D8F24 - _021D893E - 2 ; case 38
	.short _021D8F3E - _021D893E - 2 ; case 39
	.short _021D8F5E - _021D893E - 2 ; case 40
	.short _021D8F7E - _021D893E - 2 ; case 41
	.short _021D8F92 - _021D893E - 2 ; case 42
	.short _021D8FA6 - _021D893E - 2 ; case 43
	.short _021D8FC6 - _021D893E - 2 ; case 44
	.short _021D900C - _021D893E - 2 ; case 45
	.short _021D901C - _021D893E - 2 ; case 46
	.short _021D9030 - _021D893E - 2 ; case 47
	.short _021D9062 - _021D893E - 2 ; case 48
	.short _021D90CE - _021D893E - 2 ; case 49
	.short _021D90E2 - _021D893E - 2 ; case 50
	.short _021D9106 - _021D893E - 2 ; case 51
	.short _021D913E - _021D893E - 2 ; case 52
	.short _021D9178 - _021D893E - 2 ; case 53
	.short _021D9192 - _021D893E - 2 ; case 54
	.short _021D91E4 - _021D893E - 2 ; case 55
	.short _021D9208 - _021D893E - 2 ; case 56
	.short _021D921A - _021D893E - 2 ; case 57
	.short _021D922A - _021D893E - 2 ; case 58
	.short _021D9244 - _021D893E - 2 ; case 59
	.short _021D925C - _021D893E - 2 ; case 60
	.short _021D926C - _021D893E - 2 ; case 61
	.short _021D927E - _021D893E - 2 ; case 62
	.short _021D9290 - _021D893E - 2 ; case 63
	.short _021D92CA - _021D893E - 2 ; case 64
	.short _021D92DC - _021D893E - 2 ; case 65
	.short _021D92EE - _021D893E - 2 ; case 66
	.short _021D930A - _021D893E - 2 ; case 67
	.short _021D9384 - _021D893E - 2 ; case 68
	.short _021D9396 - _021D893E - 2 ; case 69
	.short _021D93AE - _021D893E - 2 ; case 70
	.short _021D93C0 - _021D893E - 2 ; case 71
	.short _021D93D8 - _021D893E - 2 ; case 72
	.short _021D93F8 - _021D893E - 2 ; case 73
	.short _021D942A - _021D893E - 2 ; case 74
	.short _021D944A - _021D893E - 2 ; case 75
	.short _021D945C - _021D893E - 2 ; case 76
	.short _021D9476 - _021D893E - 2 ; case 77
	.short _021D94DE - _021D893E - 2 ; case 78
	.short _021D94EC - _021D893E - 2 ; case 79
	.short _021D950C - _021D893E - 2 ; case 80
	.short _021D954E - _021D893E - 2 ; case 81
	.short _021D956E - _021D893E - 2 ; case 82
	.short _021D9586 - _021D893E - 2 ; case 83
	.short _021D9598 - _021D893E - 2 ; case 84
	.short _021D95AA - _021D893E - 2 ; case 85
	.short _021D95BC - _021D893E - 2 ; case 86
	.short _021D95D4 - _021D893E - 2 ; case 87
	.short _021D95E6 - _021D893E - 2 ; case 88
	.short _021D95F8 - _021D893E - 2 ; case 89
	.short _021D960A - _021D893E - 2 ; case 90
	.short _021D9672 - _021D893E - 2 ; case 91
	.short _021D9684 - _021D893E - 2 ; case 92
	.short _021D9696 - _021D893E - 2 ; case 93
	.short _021D96DE - _021D893E - 2 ; case 94
	.short _021D96EC - _021D893E - 2 ; case 95
	.short _021D96FE - _021D893E - 2 ; case 96
	.short _021D9738 - _021D893E - 2 ; case 97
	.short _021D974C - _021D893E - 2 ; case 98
	.short _021D9764 - _021D893E - 2 ; case 99
	.short _021D9788 - _021D893E - 2 ; case 100
	.short _021D9798 - _021D893E - 2 ; case 101
	.short _021D97B2 - _021D893E - 2 ; case 102
	.short _021D97CC - _021D893E - 2 ; case 103
	.short _021D97DC - _021D893E - 2 ; case 104
	.short _021D9812 - _021D893E - 2 ; case 105
	.short _021D982A - _021D893E - 2 ; case 106
	.short _021D983A - _021D893E - 2 ; case 107
	.short _021D9848 - _021D893E - 2 ; case 108
	.short _021D985A - _021D893E - 2 ; case 109
_021D8A1A:
	ldr r1, _021D8D70 ; =0x00000405
	mov r0, #2
	mov r2, #1
	bl FUN_0200433C
	ldr r0, _021D8D70 ; =0x00000405
	add r1, r5, #0
	bl FUN_02005350
	add r0, r5, #0
	mov r1, #1
	bl FUN_0201797C
	mov r0, #7
	mov r1, #1
	bl FUN_0201797C
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #1
	str r0, [r4, #0xc]
	bl _021D985C
_021D8A5A:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8B22
	add r0, r4, #0
	mov r1, #0x28
	bl MOD59_021D7BEC
	cmp r0, #1
	bne _021D8B22
	mov r0, #2
	str r0, [r4, #0xc]
	bl _021D985C
_021D8A76:
	add r1, r5, #0
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D8B22
	mov r0, #3
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	bl _021D985C
_021D8A92:
	ldr r0, _021D8D70 ; =0x00000405
	bl FUN_0200521C
	add r0, r4, #0
	mov r1, #1
	add r0, #0x89
	strb r1, [r0]
	add r0, r4, #0
	add r1, r5, #0
	add r0, #0x8a
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8140
	mov r0, #3
	mov r1, #1
	bl FUN_0201797C
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201797C
	mov r0, #0x10
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #1
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r5, #0
	bl FUN_0200E1D0
	mov r0, #4
	str r0, [r4, #0xc]
	bl _021D985C
_021D8ADE:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8B22
	mov r0, #5
	str r0, [r4, #0xc]
	bl _021D985C
_021D8AEE:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D8B22
	mov r0, #6
	str r0, [r4, #0xc]
	bl _021D985C
_021D8B02:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D8460
	cmp r0, #1
	bne _021D8B22
	mov r0, #7
	str r0, [r4, #0xc]
	bl _021D985C
_021D8B16:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D7D7C
	cmp r0, #1
	beq _021D8B26
_021D8B22:
	bl _021D985C
_021D8B26:
	ldr r0, [r4, #0x48]
	cmp r0, #1
	beq _021D8B38
	cmp r0, #2
	beq _021D8B44
	cmp r0, #3
	beq _021D8B58
	bl _021D985C
_021D8B38:
	mov r0, #0xa
	str r0, [r4, #0x10]
	mov r0, #8
	str r0, [r4, #0xc]
	bl _021D985C
_021D8B44:
	mov r0, #0x1f
	str r0, [r4, #0x10]
	mov r0, #8
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	bl _021D985C
_021D8B58:
	mov r0, #0x29
	str r0, [r4, #0xc]
	bl _021D985C
_021D8B60:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r5, #0
	add r3, r5, #0
	bl FUN_0200E1D0
	mov r0, #9
	str r0, [r4, #0xc]
	bl _021D985C
_021D8B80:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8C84
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	mov r0, #1
	add r1, r5, #0
	bl FUN_0201797C
	ldr r0, [r4, #0x10]
	str r0, [r4, #0xc]
	bl _021D985C
_021D8BA0:
	add r1, r4, #0
	mov r2, #1
	add r1, #0x88
	strb r2, [r1]
	bl MOD59_021D80FC
	add r0, r4, #0
	mov r1, #1
	add r0, #0x8b
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8234
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0xb
	str r0, [r4, #0xc]
	bl _021D985C
_021D8BD8:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8C84
	mov r0, #0xc
	str r0, [r4, #0xc]
	bl _021D985C
_021D8BE8:
	mov r1, #0x12
	str r1, [sp]
	mov r1, #2
	add r2, r5, #0
	mov r3, #3
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8C84
	mov r0, #0xd
	str r0, [r4, #0xc]
	bl _021D985C
_021D8C02:
	add r1, r4, #0
	mov r2, #2
	add r1, #0x88
	strb r2, [r1]
	bl MOD59_021D80FC
	mov r0, #0xe
	str r0, [r4, #0xc]
	bl _021D985C
_021D8C16:
	mov r1, #0xc
	str r1, [sp]
	mov r1, #3
	add r2, r5, #0
	mov r3, #7
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8C84
	mov r0, #0xf
	str r0, [r4, #0xc]
	bl _021D985C
_021D8C30:
	add r1, r4, #0
	mov r2, #3
	add r1, #0x88
	strb r2, [r1]
	bl MOD59_021D80FC
	mov r0, #0x10
	str r0, [r4, #0xc]
	bl _021D985C
_021D8C44:
	mov r1, #0xc
	str r1, [sp]
	mov r1, #4
	add r2, r5, #0
	add r3, r1, #0
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8C84
	mov r0, #0x11
	str r0, [r4, #0xc]
	bl _021D985C
_021D8C5E:
	mov r1, #6
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D8C84
	mov r0, #0x12
	str r0, [r4, #0xc]
	bl _021D985C
_021D8C72:
	mov r1, #0xa
	str r1, [sp]
	mov r1, #5
	add r2, r5, #0
	mov r3, #4
	bl MOD59_021D7ECC
	cmp r0, #1
	beq _021D8C88
_021D8C84:
	bl _021D985C
_021D8C88:
	mov r0, #0x13
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	bl _021D985C
_021D8C98:
	add r0, r5, #0
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0x14
	str r0, [r4, #0xc]
	bl _021D985C
_021D8CA8:
	mov r1, #7
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D8DA0
	mov r0, #0x15
	str r0, [r4, #0xc]
	bl _021D985C
_021D8CBC:
	ldr r6, _021D8D74 ; =0x021D9E44
	add r3, sp, #0x1c
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [r4, #0x68]
	bl FUN_020145C8
	mov r0, #6
	mov r1, #1
	bl FUN_0201797C
	add r0, r4, #0
	mov r1, #3
	add r0, #0x8b
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8234
	mov r0, #0x16
	str r0, [r4, #0xc]
	bl _021D985C
_021D8CF8:
	ldr r0, _021D8D78 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _021D8D08
	mov r0, #0x1b
	str r0, [r4, #0xc]
	bl _021D985C
_021D8D08:
	ldr r0, [r4, #0x68]
	bl FUN_02014630
	sub r0, r0, #3
	cmp r0, #1
	bhi _021D8DA0
	mov r0, #0x17
	str r0, [r4, #0xc]
	bl _021D985C
_021D8D1C:
	ldr r0, [r4, #0x68]
	bl FUN_02014630
	cmp r0, #1
	beq _021D8D2E
	cmp r0, #2
	beq _021D8D36
	bl _021D985C
_021D8D2E:
	mov r0, #0x18
	str r0, [r4, #0xc]
	bl _021D985C
_021D8D36:
	mov r0, #0x1a
	str r0, [r4, #0xc]
	bl _021D985C
_021D8D3E:
	mov r1, #6
	mov r2, #1
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D8DA0
	ldr r0, [r4, #0x68]
	bl FUN_020146C4
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x19
	str r0, [r4, #0xc]
	bl _021D985C
	.align 2, 0
_021D8D70: .word 0x00000405
_021D8D74: .word MOD59_021D9E44
_021D8D78: .word gMain
_021D8D7C:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8DA0
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	mov r0, #0x1c
	str r0, [r4, #0xc]
	bl _021D985C
_021D8D94:
	mov r1, #6
	mov r2, #1
	bl MOD59_021D7A68
	cmp r0, #1
	beq _021D8DA4
_021D8DA0:
	bl _021D985C
_021D8DA4:
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	ldr r0, [r4, #0x68]
	bl FUN_020146C4
	add r0, r4, #0
	mov r1, #1
	add r0, #0x88
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D80FC
	add r0, r4, #0
	mov r1, #1
	add r0, #0x8b
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8234
	mov r0, #0xc
	str r0, [r4, #0xc]
	bl _021D985C
_021D8DD6:
	mov r1, #8
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D8EB2
	mov r0, #0x16
	str r0, [r4, #0xc]
	bl _021D985C
_021D8DEA:
	add r1, r4, #0
	add r1, #0x88
	strb r5, [r1]
	bl MOD59_021D80FC
	add r0, r4, #0
	add r1, r5, #0
	add r0, #0x8b
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8234
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201797C
	add r2, r5, #0
	ldr r0, [r4, #0x18]
	mov r1, #1
	add r3, r2, #0
	bl FUN_020179E0
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x1d
	str r0, [r4, #0xc]
	bl _021D985C
_021D8E34:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8EB2
	mov r0, #0x1e
	str r0, [r4, #0xc]
	bl _021D985C
_021D8E44:
	mov r1, #9
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D8EB2
	mov r0, #6
	str r0, [r4, #0xc]
	bl _021D985C
_021D8E58:
	add r1, r4, #0
	mov r2, #4
	add r1, #0x88
	strb r2, [r1]
	bl MOD59_021D80FC
	add r0, r4, #0
	mov r1, #2
	add r0, #0x8b
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8234
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x20
	str r0, [r4, #0xc]
	bl _021D985C
_021D8E90:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8EB2
	mov r0, #0x21
	str r0, [r4, #0xc]
	bl _021D985C
_021D8EA0:
	mov r1, #6
	str r1, [sp]
	mov r1, #0xa
	mov r2, #1
	mov r3, #9
	bl MOD59_021D7ECC
	cmp r0, #1
	beq _021D8EB6
_021D8EB2:
	bl _021D985C
_021D8EB6:
	mov r0, #0x22
	str r0, [r4, #0xc]
	bl _021D985C
_021D8EBE:
	mov r3, #8
	mov r1, #0xb
	mov r2, #1
	str r3, [sp]
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8FCE
	mov r0, #0x23
	str r0, [r4, #0xc]
	bl _021D985C
_021D8ED6:
	mov r1, #6
	str r1, [sp]
	mov r1, #0xc
	mov r2, #1
	mov r3, #9
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8FCE
	mov r0, #0x24
	str r0, [r4, #0xc]
	bl _021D985C
_021D8EF0:
	mov r1, #0xe
	str r1, [sp]
	mov r1, #0xd
	mov r2, #1
	mov r3, #5
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8FCE
	mov r0, #0x25
	str r0, [r4, #0xc]
	bl _021D985C
_021D8F0A:
	mov r1, #4
	str r1, [sp]
	mov r1, #0xe
	mov r2, #1
	mov r3, #0xa
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8FCE
	mov r0, #0x26
	str r0, [r4, #0xc]
	bl _021D985C
_021D8F24:
	mov r1, #0xc
	str r1, [sp]
	mov r1, #0xf
	mov r2, #1
	mov r3, #6
	bl MOD59_021D7ECC
	cmp r0, #1
	bne _021D8FCE
	mov r0, #0x27
	str r0, [r4, #0xc]
	bl _021D985C
_021D8F3E:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r5, #0
	add r3, r5, #0
	bl FUN_0200E1D0
	mov r0, #0x28
	str r0, [r4, #0xc]
	bl _021D985C
_021D8F5E:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D8FCE
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	add r0, r5, #0
	mov r1, #1
	bl FUN_0201797C
	mov r0, #0x1c
	str r0, [r4, #0xc]
	bl _021D985C
_021D8F7E:
	mov r1, #1
	mov r2, #2
	bl MOD59_021D8460
	cmp r0, #1
	bne _021D8FCE
	mov r0, #0x2a
	str r0, [r4, #0xc]
	bl _021D985C
_021D8F92:
	mov r1, #0x10
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D8FCE
	mov r0, #0x2b
	str r0, [r4, #0xc]
	bl _021D985C
_021D8FA6:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, r5, #0
	str r0, [sp, #8]
	mov r0, #4
	add r2, r5, #0
	add r3, r5, #0
	bl FUN_0200E1D0
	mov r0, #0x2c
	str r0, [r4, #0xc]
	bl _021D985C
_021D8FC6:
	bl FUN_0200E308
	cmp r0, #1
	beq _021D8FD2
_021D8FCE:
	bl _021D985C
_021D8FD2:
	add r0, r4, #0
	bl MOD59_021D83F8
	add r0, r4, #0
	mov r1, #4
	add r0, #0x8b
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8234
	mov r0, #6
	mov r1, #1
	bl FUN_0201797C
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	mov r0, #4
	add r3, r5, #0
	bl FUN_0200E1D0
	mov r0, #0x2d
	str r0, [r4, #0xc]
	bl _021D985C
_021D900C:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D90DA
	mov r0, #0x2e
	str r0, [r4, #0xc]
	bl _021D985C
_021D901C:
	mov r1, #0x11
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D90DA
	mov r0, #0x2f
	str r0, [r4, #0xc]
	bl _021D985C
_021D9030:
	bl MOD59_021D7730
	cmp r0, #1
	bne _021D9054
	add r0, r4, #0
	add r1, r5, #0
	add r0, #0x94
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x98
	str r1, [r0]
	ldr r0, [r4, #0x18]
	bl FUN_02018744
	mov r0, #0x30
	str r0, [r4, #0xc]
	bl _021D985C
_021D9054:
	ldr r0, _021D9370 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _021D90DA
	mov r0, #0x31
	str r0, [r4, #0xc]
	b _021D985C
_021D9062:
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	beq _021D9078
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	add r4, #0x98
	sub r0, r0, #1
	str r0, [r4]
	b _021D985C
_021D9078:
	ldr r6, _021D9374 ; =0x021D9DC0
	add r3, sp, #0x10
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	lsl r0, r0, #2
	ldr r1, [r2, r0]
	ldr r0, _021D9378 ; =0x0000FFFF
	cmp r1, r0
	bne _021D90A2
	ldr r0, _021D937C ; =0x00000706
	bl FUN_020054C8
	mov r0, #0x32
	str r0, [r4, #0xc]
	b _021D985C
_021D90A2:
	mov r0, #0x20
	str r0, [sp]
	str r5, [sp, #4]
	str r5, [sp, #8]
	ldr r0, [r4]
	mov r3, #6
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x18]
	mov r0, #0x7d
	bl FUN_0200687C
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x94
	str r1, [r0]
	mov r0, #4
	add r4, #0x98
	str r0, [r4]
	b _021D985C
_021D90CE:
	mov r1, #0x12
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	beq _021D90DC
_021D90DA:
	b _021D985C
_021D90DC:
	mov r0, #0x2f
	str r0, [r4, #0xc]
	b _021D985C
_021D90E2:
	mov r0, #1
	mov r1, #0x10
	add r2, r5, #0
	mov r3, #0xb
	str r0, [sp]
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	mov r1, #0x10
	add r2, r5, #0
	mov r3, #0xd
	bl FUN_0200A208
	mov r0, #0x33
	str r0, [r4, #0xc]
	b _021D985C
_021D9106:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _021D91F6
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	bne _021D91F6
	mov r0, #1
	add r1, r5, #0
	mov r2, #0x10
	mov r3, #0xb
	str r0, [sp]
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r5, #0
	mov r2, #0x10
	mov r3, #0xd
	bl FUN_0200A208
	mov r0, #0x34
	str r0, [r4, #0xc]
	b _021D985C
_021D913E:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _021D91F6
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	bne _021D91F6
	mov r0, #1
	str r0, [sp]
	mov r0, #4
	mov r1, #0x10
	add r2, r5, #0
	mov r3, #0xb
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	mov r1, #0x10
	add r2, r5, #0
	mov r3, #0xd
	bl FUN_0200A208
	mov r0, #0x35
	str r0, [r4, #0xc]
	b _021D985C
_021D9178:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _021D91F6
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	bne _021D91F6
	mov r0, #0x36
	str r0, [r4, #0xc]
	b _021D985C
_021D9192:
	bl MOD59_021D82A0
	mov r0, #6
	add r1, r5, #0
	bl FUN_0201797C
	add r0, r4, #0
	add r1, r5, #0
	add r0, #0x94
	str r1, [r0]
	add r1, r4, #0
	add r0, r4, #0
	add r1, #0x94
	bl MOD59_021D86BC
	add r0, r4, #0
	add r1, r5, #0
	add r0, #0x8b
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8234
	mov r0, #1
	str r0, [sp]
	mov r0, #0x10
	add r1, r5, #0
	add r2, r0, #0
	mov r3, #0xb
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #0x10
	add r1, r5, #0
	add r2, r0, #0
	mov r3, #0xd
	bl FUN_0200A208
	mov r0, #0x37
	str r0, [r4, #0xc]
	b _021D985C
_021D91E4:
	add r1, r4, #0
	add r1, #0x94
	bl MOD59_021D86BC
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	beq _021D91F8
_021D91F6:
	b _021D985C
_021D91F8:
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x38
	str r0, [r4, #0xc]
	b _021D985C
_021D9208:
	add r1, r4, #0
	add r1, #0x94
	bl MOD59_021D86BC
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x39
	str r0, [r4, #0xc]
	b _021D985C
_021D921A:
	mov r1, #0x28
	bl MOD59_021D7BEC
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x3a
	str r0, [r4, #0xc]
	b _021D985C
_021D922A:
	mov r1, #0x13
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D92FA
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	mov r0, #0x3b
	str r0, [r4, #0xc]
	b _021D985C
_021D9244:
	mov r1, #2
	mov r2, #1
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D92FA
	add r0, r4, #0
	bl MOD59_021D8914
	mov r0, #0x3c
	str r0, [r4, #0xc]
	b _021D985C
_021D925C:
	mov r1, #0x1e
	bl MOD59_021D7BEC
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x3d
	str r0, [r4, #0xc]
	b _021D985C
_021D926C:
	mov r1, #0x14
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x3e
	str r0, [r4, #0xc]
	b _021D985C
_021D927E:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x3f
	str r0, [r4, #0xc]
	b _021D985C
_021D9290:
	bl MOD59_021D84E8
	add r0, r4, #0
	mov r1, #2
	add r0, #0x89
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #6
	add r0, #0x8a
	strb r1, [r0]
	add r0, r4, #0
	bl MOD59_021D8140
	add r2, r5, #0
	add r3, r2, #0
	ldr r0, [r4, #0x18]
	mov r1, #1
	sub r3, #0x30
	bl FUN_020179E0
	ldr r0, [r4, #0x18]
	mov r1, #2
	add r2, r5, #0
	mov r3, #0x30
	bl FUN_020179E0
	mov r0, #0x40
	str r0, [r4, #0xc]
	b _021D985C
_021D92CA:
	mov r1, #1
	add r2, r5, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x41
	str r0, [r4, #0xc]
	b _021D985C
_021D92DC:
	mov r1, #2
	add r2, r5, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D92FA
	mov r0, #0x42
	str r0, [r4, #0xc]
	b _021D985C
_021D92EE:
	mov r1, #0x15
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	beq _021D92FC
_021D92FA:
	b _021D985C
_021D92FC:
	add r0, r4, #0
	add r1, r5, #0
	add r0, #0x84
	str r1, [r0]
	mov r0, #0x43
	str r0, [r4, #0xc]
	b _021D985C
_021D930A:
	ldr r0, _021D9370 ; =gMain
	mov r1, #1
	ldr r0, [r0, #0x48]
	and r1, r0
	cmp r1, #1
	bne _021D933C
	mov r0, #6
	str r0, [r4, #0x7c]
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0x80
	str r1, [r0]
	mov r0, #2
	str r0, [r4, #0x78]
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D9336
	mov r0, #0x44
	str r0, [r4, #0xc]
	b _021D985C
_021D9336:
	mov r0, #0x46
	str r0, [r4, #0xc]
	b _021D985C
_021D933C:
	mov r1, #0x20
	and r1, r0
	cmp r1, #0x20
	beq _021D934C
	mov r1, #0x10
	and r0, r1
	cmp r0, #0x10
	bne _021D9368
_021D934C:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D935A
	mov r1, #1
	b _021D935C
_021D935A:
	mov r1, #0
_021D935C:
	add r0, r4, #0
	add r0, #0x84
	str r1, [r0]
	ldr r0, _021D9380 ; =0x000005DC
	bl FUN_020054C8
_021D9368:
	add r0, r4, #0
	bl MOD59_021D8504
	b _021D985C
	.align 2, 0
_021D9370: .word gMain
_021D9374: .word MOD59_021D9DC0
_021D9378: .word 0x0000FFFF
_021D937C: .word 0x00000706
_021D9380: .word 0x000005DC
_021D9384:
	mov r1, #2
	mov r2, #1
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D9414
	mov r0, #0x45
	str r0, [r4, #0xc]
	b _021D985C
_021D9396:
	mov r1, #1
	add r2, r5, #0
	bl MOD59_021D8460
	cmp r0, #1
	bne _021D9414
	add r0, r4, #0
	bl MOD59_021D8618
	mov r0, #0x48
	str r0, [r4, #0xc]
	b _021D985C
_021D93AE:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D9414
	mov r0, #0x47
	str r0, [r4, #0xc]
	b _021D985C
_021D93C0:
	mov r1, #2
	add r2, r5, #0
	bl MOD59_021D8460
	cmp r0, #1
	bne _021D9414
	add r0, r4, #0
	bl MOD59_021D8618
	mov r0, #0x48
	str r0, [r4, #0xc]
	b _021D985C
_021D93D8:
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D93E4
	mov r1, #0x16
	b _021D93E6
_021D93E4:
	mov r1, #0x17
_021D93E6:
	add r0, r4, #0
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D9414
	mov r0, #0x49
	str r0, [r4, #0xc]
	b _021D985C
_021D93F8:
	add r1, r5, #0
	add r2, r5, #0
	bl MOD59_021D7D7C
	cmp r0, #1
	bne _021D9414
	ldr r1, [r4, #0x48]
	sub r0, r5, #2
	cmp r1, r0
	beq _021D941C
	cmp r1, #1
	beq _021D9416
	cmp r1, #2
	beq _021D941C
_021D9414:
	b _021D985C
_021D9416:
	mov r0, #0x4b
	str r0, [r4, #0xc]
	b _021D985C
_021D941C:
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_02018744
	mov r0, #0x4a
	str r0, [r4, #0xc]
	b _021D985C
_021D942A:
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D9436
	mov r1, #1
	b _021D9438
_021D9436:
	mov r1, #2
_021D9438:
	add r0, r4, #0
	mov r2, #1
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D9530
	mov r0, #0x3f
	str r0, [r4, #0xc]
	b _021D985C
_021D944A:
	mov r1, #0x18
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D9530
	mov r0, #0x4c
	str r0, [r4, #0xc]
	b _021D985C
_021D945C:
	add r0, #0x84
	ldr r1, [r0]
	ldr r0, [r4, #0x70]
	str r1, [r0, #4]
	ldr r0, _021D9778 ; =UNK_020FA5FC
	ldr r1, [r4, #0x70]
	ldr r2, [r4]
	bl OverlayManager_new
	str r0, [r4, #0x14]
	mov r0, #0x4d
	str r0, [r4, #0xc]
	b _021D985C
_021D9476:
	add r0, r5, #0
	mov r1, #1
	bl FUN_0201797C
	mov r0, #3
	mov r1, #1
	bl FUN_0201797C
	mov r0, #7
	mov r1, #1
	bl FUN_0201797C
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D94AE
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201797C
	add r2, r5, #0
	ldr r0, [r4, #0x18]
	mov r1, #1
	add r3, r2, #0
	bl FUN_020179E0
	b _021D94C2
_021D94AE:
	mov r0, #2
	mov r1, #1
	bl FUN_0201797C
	add r2, r5, #0
	ldr r0, [r4, #0x18]
	mov r1, #2
	add r3, r2, #0
	bl FUN_020179E0
_021D94C2:
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	mov r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x4e
	str r0, [r4, #0xc]
	b _021D985C
_021D94DE:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D9530
	mov r0, #0x4f
	str r0, [r4, #0xc]
	b _021D985C
_021D94EC:
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D94F8
	mov r1, #0x19
	b _021D94FA
_021D94F8:
	mov r1, #0x1a
_021D94FA:
	add r0, r4, #0
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D9530
	mov r0, #0x50
	str r0, [r4, #0xc]
	b _021D985C
_021D950C:
	add r1, r5, #0
	add r2, r5, #0
	bl MOD59_021D7D7C
	cmp r0, #1
	bne _021D9530
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	ldr r1, [r4, #0x48]
	sub r0, r5, #2
	cmp r1, r0
	beq _021D953C
	cmp r1, #1
	beq _021D9532
	cmp r1, #2
	beq _021D953C
_021D9530:
	b _021D985C
_021D9532:
	mov r0, #0x52
	str r0, [r4, #0x10]
	mov r0, #0x51
	str r0, [r4, #0xc]
	b _021D985C
_021D953C:
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x18]
	bl StringSetEmpty
	mov r0, #0x3f
	str r0, [r4, #0x10]
	mov r0, #0x51
	str r0, [r4, #0xc]
	b _021D985C
_021D954E:
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0
	bne _021D955A
	mov r1, #1
	b _021D955C
_021D955A:
	mov r1, #2
_021D955C:
	add r0, r4, #0
	mov r2, #1
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D9616
	ldr r0, [r4, #0x10]
	str r0, [r4, #0xc]
	b _021D985C
_021D956E:
	add r1, r4, #0
	mov r2, #1
	add r1, #0x89
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x8a
	strb r5, [r1]
	bl MOD59_021D8140
	mov r0, #0x53
	str r0, [r4, #0xc]
	b _021D985C
_021D9586:
	mov r1, #1
	add r2, r5, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D9616
	mov r0, #0x54
	str r0, [r4, #0xc]
	b _021D985C
_021D9598:
	mov r1, #0x1b
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D9616
	mov r0, #0x55
	str r0, [r4, #0xc]
	b _021D985C
_021D95AA:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D9616
	mov r0, #0x56
	str r0, [r4, #0xc]
	b _021D985C
_021D95BC:
	add r1, r4, #0
	mov r2, #0xa
	add r1, #0x89
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x8a
	strb r5, [r1]
	bl MOD59_021D8140
	mov r0, #0x57
	str r0, [r4, #0xc]
	b _021D985C
_021D95D4:
	mov r1, #1
	add r2, r5, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D9616
	mov r0, #0x58
	str r0, [r4, #0xc]
	b _021D985C
_021D95E6:
	mov r1, #0x1c
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D9616
	mov r0, #0x59
	str r0, [r4, #0xc]
	b _021D985C
_021D95F8:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D8460
	cmp r0, #1
	bne _021D9616
	mov r0, #0x5a
	str r0, [r4, #0xc]
	b _021D985C
_021D960A:
	mov r1, #2
	mov r2, #1
	bl MOD59_021D7D7C
	cmp r0, #1
	beq _021D9618
_021D9616:
	b _021D985C
_021D9618:
	ldr r0, [r4, #0x48]
	cmp r0, #5
	bhi _021D971A
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D962A: ; jump table
	.short _021D985C - _021D962A - 2 ; case 0
	.short _021D9636 - _021D962A - 2 ; case 1
	.short _021D963C - _021D962A - 2 ; case 2
	.short _021D963C - _021D962A - 2 ; case 3
	.short _021D963C - _021D962A - 2 ; case 4
	.short _021D963C - _021D962A - 2 ; case 5
_021D9636:
	mov r0, #0x5c
	str r0, [r4, #0xc]
	b _021D985C
_021D963C:
	ldr r1, _021D977C ; =gGameVersion
	ldrb r1, [r1]
	cmp r1, #0xa
	bne _021D964C
	sub r0, r0, #1
	lsl r1, r0, #3
	ldr r0, _021D9780 ; =0x021D9F40
	b _021D9652
_021D964C:
	sub r0, r0, #1
	lsl r1, r0, #3
	ldr r0, _021D9784 ; =0x021D9F68
_021D9652:
	ldr r1, [r0, r1]
	ldr r0, [r4, #0x4c]
	bl NewString_ReadMsgData
	add r6, r0, #0
	ldr r0, [r4, #0x74]
	add r1, r6, #0
	ldr r0, [r0, #0x18]
	bl StringCopy
	add r0, r6, #0
	bl String_dtor
	mov r0, #0x5b
	str r0, [r4, #0xc]
	b _021D985C
_021D9672:
	mov r1, #1
	mov r2, #2
	bl MOD59_021D8460
	cmp r0, #1
	bne _021D971A
	mov r0, #0x5f
	str r0, [r4, #0xc]
	b _021D985C
_021D9684:
	ldr r0, _021D9778 ; =UNK_020FA5FC
	ldr r1, [r4, #0x74]
	ldr r2, [r4]
	bl OverlayManager_new
	str r0, [r4, #0x14]
	mov r0, #0x5d
	str r0, [r4, #0xc]
	b _021D985C
_021D9696:
	add r0, r5, #0
	mov r1, #1
	bl FUN_0201797C
	mov r0, #3
	mov r1, #1
	bl FUN_0201797C
	mov r0, #7
	mov r1, #1
	bl FUN_0201797C
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201797C
	add r2, r5, #0
	ldr r0, [r4, #0x18]
	mov r1, #1
	add r3, r2, #0
	bl FUN_020179E0
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x5e
	str r0, [r4, #0xc]
	b _021D985C
_021D96DE:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D971A
	mov r0, #0x5f
	str r0, [r4, #0xc]
	b _021D985C
_021D96EC:
	mov r1, #0x1d
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D971A
	mov r0, #0x60
	str r0, [r4, #0xc]
	b _021D985C
_021D96FE:
	add r1, r5, #0
	add r2, r5, #0
	bl MOD59_021D7D7C
	cmp r0, #1
	bne _021D971A
	ldr r1, [r4, #0x48]
	sub r0, r5, #2
	cmp r1, r0
	beq _021D972A
	cmp r1, #1
	beq _021D971C
	cmp r1, #2
	beq _021D972A
_021D971A:
	b _021D985C
_021D971C:
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	mov r0, #0x61
	str r0, [r4, #0xc]
	b _021D985C
_021D972A:
	ldr r0, [r4, #0x74]
	ldr r0, [r0, #0x18]
	bl StringSetEmpty
	mov r0, #0x58
	str r0, [r4, #0xc]
	b _021D985C
_021D9738:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D7A68
	cmp r0, #1
	beq _021D9746
	b _021D985C
_021D9746:
	mov r0, #0x62
	str r0, [r4, #0xc]
	b _021D985C
_021D974C:
	add r1, r4, #0
	mov r2, #1
	add r1, #0x89
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x8a
	strb r5, [r1]
	bl MOD59_021D8140
	mov r0, #0x63
	str r0, [r4, #0xc]
	b _021D985C
_021D9764:
	mov r1, #1
	add r2, r5, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D985C
	mov r0, #0x64
	str r0, [r4, #0xc]
	b _021D985C
	nop
_021D9778: .word UNK_020FA5FC
_021D977C: .word gGameVersion
_021D9780: .word MOD59_021D9F40
_021D9784: .word MOD59_021D9F68
_021D9788:
	mov r1, #0x1e
	bl MOD59_021D7BEC
	cmp r0, #1
	bne _021D985C
	mov r0, #0x65
	str r0, [r4, #0xc]
	b _021D985C
_021D9798:
	mov r1, #0x1e
	mov r2, #1
	bl MOD59_021D7C44
	cmp r0, #1
	bne _021D985C
	add r0, r5, #0
	mov r1, #0x32
	bl FUN_020053CC
	mov r0, #0x66
	str r0, [r4, #0xc]
	b _021D985C
_021D97B2:
	mov r1, #1
	add r2, r1, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D985C
	ldr r0, [r4, #0x18]
	add r1, r5, #0
	bl FUN_02018744
	mov r0, #0x67
	str r0, [r4, #0xc]
	b _021D985C
_021D97CC:
	mov r1, #0x1e
	bl MOD59_021D7BEC
	cmp r0, #1
	bne _021D985C
	mov r0, #0x68
	str r0, [r4, #0xc]
	b _021D985C
_021D97DC:
	add r1, r4, #0
	add r1, #0x84
	ldr r1, [r1]
	cmp r1, #0
	bne _021D97FA
	add r1, r4, #0
	mov r2, #2
	add r1, #0x89
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x8a
	strb r5, [r1]
	bl MOD59_021D8140
	b _021D980C
_021D97FA:
	add r1, r4, #0
	mov r2, #6
	add r1, #0x89
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x8a
	strb r5, [r1]
	bl MOD59_021D8140
_021D980C:
	mov r0, #0x69
	str r0, [r4, #0xc]
	b _021D985C
_021D9812:
	mov r1, #1
	add r2, r5, #0
	bl MOD59_021D7A68
	cmp r0, #1
	bne _021D985C
	add r0, r4, #0
	bl MOD59_021D8624
	mov r0, #0x6a
	str r0, [r4, #0xc]
	b _021D985C
_021D982A:
	mov r1, #0x1e
	bl MOD59_021D7BEC
	cmp r0, #1
	bne _021D985C
	mov r0, #0x6b
	str r0, [r4, #0xc]
	b _021D985C
_021D983A:
	bl MOD59_021D8634
	cmp r0, #1
	bne _021D985C
	mov r0, #0x6c
	str r0, [r4, #0xc]
	b _021D985C
_021D9848:
	ldr r0, _021D9864 ; =0x021D9DDC
	ldr r2, [r4]
	add r1, r5, #0
	bl OverlayManager_new
	str r0, [r4, #0x14]
	mov r0, #0x6d
	str r0, [r4, #0xc]
	b _021D985C
_021D985A:
	mov r5, #1
_021D985C:
	add r0, r5, #0
	add sp, #0x30
	pop {r4, r5, r6, pc}
	nop
_021D9864: .word MOD59_021D9DDC
	thumb_func_end MOD59_021D8920

	.rodata

	.global MOD59_021D9D90
MOD59_021D9D90: ; 0x021D9D90
	.byte 0x00, 0x08, 0x00, 0x18, 0x18, 0x05, 0x2D, 0x01, 0x00, 0x04, 0x00, 0x18, 0x18, 0x05, 0x2D, 0x01

	.global MOD59_021D9DA0
MOD59_021D9DA0: ; 0x021D9DA0
	.byte 0x00, 0x02, 0x03, 0x0E, 0x0A, 0x05, 0xE1, 0x02

	.global MOD59_021D9DA8
MOD59_021D9DA8: ; 0x021D9DA8
	.byte 0x00, 0x02, 0x03, 0x06, 0x04, 0x05, 0x55, 0x03

	.global MOD59_021D9DB0
MOD59_021D9DB0: ; 0x021D9DB0
	.byte 0x00, 0x01, 0x03, 0x10, 0x06, 0x05, 0x0D, 0x03

	.global MOD59_021D9DB8
MOD59_021D9DB8: ; 0x021D9DB8
	.byte 0x00, 0x02, 0x13, 0x1B, 0x04, 0x06, 0x6D, 0x03

	.global MOD59_021D9DC0
MOD59_021D9DC0: ; 0x021D9DC0
	.byte 0x1F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00

	.global MOD59_021D9DCC
MOD59_021D9DCC: ; 0x021D9DCC
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021D9DDC
MOD59_021D9DDC: ; 0x021D9DDC
	.word MOD59_021D9868, MOD59_021D9898, MOD59_021D99F8, 0xFFFFFFFF

	.global MOD59_021D9DEC
MOD59_021D9DEC: ; 0x021D9DEC
	.byte 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00

	.global MOD59_021D9DFC
MOD59_021D9DFC: ; 0x021D9DFC
	.byte 0x0D, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global MOD59_021D9E0C
MOD59_021D9E0C: ; 0x021D9E0C
	.byte 0x22, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global MOD59_021D9E1C
MOD59_021D9E1C: ; 0x021D9E1C
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00

	.global MOD59_021D9E30
MOD59_021D9E30: ; 0x021D9E30
	.byte 0x1A, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00
	.byte 0x1D, 0x00, 0x00, 0x00

	.global MOD59_021D9E44
MOD59_021D9E44: ; 0x021D9E44
	.byte 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0C, 0x08, 0x00, 0x00

	.global MOD59_021D9E58
MOD59_021D9E58: ; 0x021D9E58
	.byte 0x1F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x21, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global MOD59_021D9E70
MOD59_021D9E70: ; 0x021D9E70
	.byte 0x0D, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00
	.byte 0x2F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD59_021D9E88
MOD59_021D9E88: ; 0x021D9E88
	.byte 0x08, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00
	.byte 0x2B, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00

	.global MOD59_021D9EA0
MOD59_021D9EA0: ; 0x021D9EA0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021D9EBC
MOD59_021D9EBC: ; 0x021D9EBC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021D9ED8
MOD59_021D9ED8: ; 0x021D9ED8
	.byte 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A
	.byte 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A, 0x3C, 0x6A

	.global MOD59_021D9EF8
MOD59_021D9EF8: ; 0x021D9EF8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021D9F18
MOD59_021D9F18: ; 0x021D9F18
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD59_021D9F40
MOD59_021D9F40: ; 0x021D9F40
	.byte 0x24, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x26, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x28, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD59_021D9F68
MOD59_021D9F68: ; 0x021D9F68
	.byte 0x24, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x2A, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x2C, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD59_021D9F90
MOD59_021D9F90: ; 0x021D9F90
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x0D, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00

	.global MOD59_021D9FE8
MOD59_021D9FE8: ; 0x021D9FE8
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x40, 0x41, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D
	.byte 0x0E, 0x0F, 0x42, 0x43, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x44, 0x45, 0x18, 0x19
	.byte 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x46, 0x47, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	.byte 0x48, 0x49, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x4A, 0x4B, 0x30, 0x31, 0x32, 0x33
	.byte 0x34, 0x35, 0x36, 0x37, 0x4C, 0x4D, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x4E, 0x4F
	.byte 0x50, 0x51, 0x52, 0x53, 0x58, 0x59, 0x5A, 0x5B, 0x60, 0x61, 0x54, 0x55, 0x56, 0x57, 0x5C, 0x5D
	.byte 0x5E, 0x5F, 0x62, 0x63
