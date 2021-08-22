	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD70_021D74E0
MOD70_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	mov r2, #1
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x3c
	lsl r2, r2, #0xe
	bl CreateHeap
	mov r2, #7
	mov r0, #3
	mov r1, #0x3d
	lsl r2, r2, #0xe
	bl CreateHeap
	add r0, r5, #0
	mov r1, #0xdc
	mov r2, #0x3c
	bl OverlayManager_CreateAndGetData
	add r4, r0, #0
	beq _021D7558
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r1, r4, #0
	add r1, #0xcc
	str r0, [r1]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xd4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xcc
	ldr r0, [r0]
	bl Sav2_HOF_GetNumRecords
	add r1, r4, #0
	add r1, #0xd0
	str r0, [r1]
	add r1, r4, #0
	add r1, #0xcc
	ldr r1, [r1]
	add r0, r4, #0
	bl MOD70_021D7724
	add r0, r4, #0
	add r1, r4, #0
	bl MOD70_021D77CC
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	mov r1, #0
	bl MOD70_021D7930
	add r4, #0xd8
	str r0, [r4]
_021D7558:
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD70_021D74E0

	thumb_func_start MOD70_021D755C
MOD70_021D755C: ; 0x021D755C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl MOD70_021D78A0
	add r0, r4, #0
	bl MOD70_021D7760
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0x3d
	bl DestroyHeap
	mov r0, #0x3c
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD70_021D755C

	thumb_func_start MOD70_021D758C
MOD70_021D758C: ; 0x021D758C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, #0xd8
	ldr r0, [r0]
	cmp r0, #0
	beq _021D75B8
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl MOD70_021D7958
	cmp r0, #0
	bne _021D75B0
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D75B0:
	add r0, r4, #0
	mov r1, #0
	add r0, #0xd8
	str r1, [r0]
_021D75B8:
	ldr r0, [r5]
	cmp r0, #0
	beq _021D75C4
	cmp r0, #1
	beq _021D768A
	b _021D768E
_021D75C4:
	ldr r0, _021D7694 ; =gMain
	mov r1, #2
	ldr r0, [r0, #0x48]
	add r2, r0, #0
	tst r2, r1
	beq _021D75E0
	add r0, r4, #0
	mov r1, #1
	bl MOD70_021D7698
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D768E
_021D75E0:
	mov r2, #1
	add r3, r0, #0
	tst r3, r2
	beq _021D75F8
	ldr r0, [r4, #0x1c]
	mov r1, #4
	eor r0, r2
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD70_021D7698
	b _021D768E
_021D75F8:
	mov r2, #0x20
	tst r2, r0
	beq _021D7612
	add r0, r4, #0
	bl MOD70_021D76AC
	cmp r0, #0
	beq _021D768E
	add r0, r4, #0
	mov r1, #3
	bl MOD70_021D7698
	b _021D768E
_021D7612:
	mov r2, #0x10
	tst r2, r0
	beq _021D762C
	add r0, r4, #0
	bl MOD70_021D76E8
	cmp r0, #0
	beq _021D768E
	add r0, r4, #0
	mov r1, #3
	bl MOD70_021D7698
	b _021D768E
_021D762C:
	mov r2, #0x40
	tst r2, r0
	beq _021D765C
	ldr r0, [r4, #0x18]
	sub r0, r0, #1
	str r0, [r4, #0x18]
	bpl _021D7654
	add r0, r4, #0
	bl MOD70_021D76AC
	cmp r0, #0
	beq _021D768E
	ldr r0, [r4, #0x14]
	mov r1, #3
	sub r0, r0, #1
	str r0, [r4, #0x18]
	add r0, r4, #0
	bl MOD70_021D7698
	b _021D768E
_021D7654:
	add r0, r4, #0
	bl MOD70_021D7698
	b _021D768E
_021D765C:
	mov r2, #0x80
	tst r0, r2
	beq _021D768E
	ldr r0, [r4, #0x18]
	add r2, r0, #1
	str r2, [r4, #0x18]
	ldr r0, [r4, #0x14]
	cmp r2, r0
	blt _021D7682
	add r0, r4, #0
	bl MOD70_021D76E8
	cmp r0, #0
	beq _021D768E
	add r0, r4, #0
	mov r1, #3
	bl MOD70_021D7698
	b _021D768E
_021D7682:
	add r0, r4, #0
	bl MOD70_021D7698
	b _021D768E
_021D768A:
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D768E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D7694: .word gMain
	thumb_func_end MOD70_021D758C

	thumb_func_start MOD70_021D7698
MOD70_021D7698: ; 0x021D7698
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl MOD70_021D7930
	add r4, #0xd8
	str r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD70_021D7698

	thumb_func_start MOD70_021D76AC
MOD70_021D76AC: ; 0x021D76AC
	push {r3, lr}
	add r1, r0, #0
	add r1, #0xd4
	ldr r1, [r1]
	add r2, r1, #1
	add r1, r0, #0
	add r1, #0xd4
	str r2, [r1]
	add r1, r0, #0
	add r1, #0xd4
	ldr r2, [r1]
	add r1, r0, #0
	add r1, #0xd0
	ldr r1, [r1]
	cmp r2, r1
	blt _021D76D4
	add r1, r0, #0
	mov r2, #0
	add r1, #0xd4
	str r2, [r1]
_021D76D4:
	add r1, r0, #0
	add r2, r0, #0
	add r1, #0xcc
	add r2, #0xd4
	ldr r1, [r1]
	ldr r2, [r2]
	bl MOD70_021D777C
	mov r0, #1
	pop {r3, pc}
	thumb_func_end MOD70_021D76AC

	thumb_func_start MOD70_021D76E8
MOD70_021D76E8: ; 0x021D76E8
	push {r3, lr}
	add r1, r0, #0
	add r1, #0xd4
	ldr r1, [r1]
	sub r2, r1, #1
	add r1, r0, #0
	add r1, #0xd4
	str r2, [r1]
	add r1, r0, #0
	add r1, #0xd4
	ldr r1, [r1]
	cmp r1, #0
	bge _021D7710
	add r1, r0, #0
	add r1, #0xd0
	ldr r1, [r1]
	sub r2, r1, #1
	add r1, r0, #0
	add r1, #0xd4
	str r2, [r1]
_021D7710:
	add r1, r0, #0
	add r2, r0, #0
	add r1, #0xcc
	add r2, #0xd4
	ldr r1, [r1]
	ldr r2, [r2]
	bl MOD70_021D777C
	mov r0, #1
	pop {r3, pc}
	thumb_func_end MOD70_021D76E8

	thumb_func_start MOD70_021D7724
MOD70_021D7724: ; 0x021D7724
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	str r1, [sp, #4]
	mov r4, #0
	add r5, r0, #0
	mov r6, #0xc
	mov r7, #0x3c
_021D7734:
	add r0, r6, #0
	add r1, r7, #0
	bl String_ctor
	str r0, [r5, #0x20]
	mov r0, #8
	mov r1, #0x3c
	bl String_ctor
	str r0, [r5, #0x24]
	add r4, r4, #1
	add r5, #0x1c
	cmp r4, #6
	blt _021D7734
	ldr r0, [sp]
	mov r2, #0
	ldr r1, [sp, #4]
	str r2, [r0, #0x1c]
	bl MOD70_021D777C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD70_021D7724

	thumb_func_start MOD70_021D7760
MOD70_021D7760: ; 0x021D7760
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D7766:
	ldr r0, [r5, #0x20]
	bl String_dtor
	ldr r0, [r5, #0x24]
	bl String_dtor
	add r4, r4, #1
	add r5, #0x1c
	cmp r4, #6
	blt _021D7766
	pop {r3, r4, r5, pc}
	thumb_func_end MOD70_021D7760

	thumb_func_start MOD70_021D777C
MOD70_021D777C: ; 0x021D777C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r6, r0, #0
	str r2, [sp]
	add r0, r7, #0
	add r1, r2, #0
	bl Sav2_HOF_TranslateRecordIdx
	str r0, [r6]
	ldr r1, [sp]
	add r0, r7, #0
	bl Sav2_HOF_RecordCountMons
	str r0, [r6, #0x14]
	ldr r1, [sp]
	add r0, r7, #0
	add r2, r6, #4
	bl Sav2_HOF_GetClearDate
	ldr r0, [r6, #0x14]
	mov r4, #0
	cmp r0, #0
	ble _021D77C4
	add r5, r6, #0
	add r5, #0x20
_021D77AE:
	ldr r1, [sp]
	add r0, r7, #0
	add r2, r4, #0
	add r3, r5, #0
	bl Sav2_HOF_GetMonStatsByIndexPair
	ldr r0, [r6, #0x14]
	add r4, r4, #1
	add r5, #0x1c
	cmp r4, r0
	blt _021D77AE
_021D77C4:
	mov r0, #0
	str r0, [r6, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD70_021D777C

	thumb_func_start MOD70_021D77CC
MOD70_021D77CC: ; 0x021D77CC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r1, #0
	add r5, r0, #0
	ldr r1, _021D7894 ; =0x00000E1C
	mov r0, #0x3d
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D788C
	str r5, [r4]
	str r6, [r4, #4]
	mov r0, #0x3d
	bl BgConfig_Alloc
	str r0, [r4, #0x10]
	bl NNS_G2dInitOamManagerModule
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x3d
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r4, #0
	mov r0, #0x40
	add r1, #0x38
	mov r2, #0x3d
	bl FUN_02008C9C
	str r0, [r4, #0x34]
	ldr r2, _021D7898 ; =0x00000139
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x3d
	bl NewMsgDataFromNarc
	mov r2, #6
	lsl r2, r2, #6
	str r0, [r4, r2]
	mov r0, #1
	mov r1, #0x1a
	sub r2, #0x16
	mov r3, #0x3d
	bl NewMsgDataFromNarc
	mov r2, #0x61
	lsl r2, r2, #2
	str r0, [r4, r2]
	mov r0, #1
	mov r1, #0x1a
	add r2, #0xc8
	mov r3, #0x3d
	bl NewMsgDataFromNarc
	mov r1, #0x62
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x3d
	bl ScrStrBufs_new
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, #0x8c
	add r0, r1, #0
	mov r1, #0x3d
	bl String_ctor
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r1, #0x90
	add r0, r1, #0
	mov r1, #0x3d
	bl String_ctor
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x3d
	bl AllocMonZeroed
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, _021D789C ; =MOD70_021D790C
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
_021D788C:
	add r0, r4, #0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021D7894: .word 0x00000E1C
_021D7898: .word 0x00000139
_021D789C: .word MOD70_021D790C
	thumb_func_end MOD70_021D77CC

	thumb_func_start MOD70_021D78A0
MOD70_021D78A0: ; 0x021D78A0
	push {r4, lr}
	add r4, r0, #0
	beq _021D790A
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ScrStrBufs_delete
	mov r0, #0x62
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl DestroyMsgData
	ldr r0, [r4, #0x34]
	bl FUN_0201FD58
	bl DeinitOamData
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
_021D790A:
	pop {r4, pc}
	thumb_func_end MOD70_021D78A0

	thumb_func_start MOD70_021D790C
MOD70_021D790C: ; 0x021D790C
	push {r3, lr}
	ldr r0, [r0, #0x34]
	bl FUN_0201FDEC
	bl ApplyAndResetOamManagerBuffer
	ldr r3, _021D7928 ; =0x027E0000
	ldr r1, _021D792C ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_021D7928: .word 0x027E0000
_021D792C: .word 0x00003FF8
	thumb_func_end MOD70_021D790C

	thumb_func_start MOD70_021D7930
MOD70_021D7930: ; 0x021D7930
	push {r3, lr}
	add r2, r1, #0
	str r2, [r0, #0xc]
	mov r1, #0
	lsl r3, r2, #2
	str r1, [r0, #8]
	ldr r2, _021D7954 ; =0x021D82E0
	add r1, r0, #0
	ldr r2, [r2, r3]
	add r1, #8
	blx r2
	cmp r0, #0
	bne _021D794E
	mov r0, #1
	pop {r3, pc}
_021D794E:
	mov r0, #0
	pop {r3, pc}
	nop
_021D7954: .word MOD70_021D82E0
	thumb_func_end MOD70_021D7930

	thumb_func_start MOD70_021D7958
MOD70_021D7958: ; 0x021D7958
	push {r3, lr}
	ldr r2, [r0, #0xc]
	add r1, r0, #0
	lsl r3, r2, #2
	ldr r2, _021D796C ; =0x021D82E0
	add r1, #8
	ldr r2, [r2, r3]
	blx r2
	pop {r3, pc}
	nop
_021D796C: .word MOD70_021D82E0
	thumb_func_end MOD70_021D7958

	thumb_func_start MOD70_021D7970
MOD70_021D7970: ; 0x021D7970
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _021D7984
	cmp r1, #1
	beq _021D79AC
	b _021D79BA
_021D7984:
	bl MOD70_021D7AF4
	add r0, r5, #0
	bl MOD70_021D7F70
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3d
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D79BA
_021D79AC:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D79BA
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D79BA:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD70_021D7970

	thumb_func_start MOD70_021D79C0
MOD70_021D79C0: ; 0x021D79C0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D79D4
	cmp r0, #1
	beq _021D79FA
	b _021D7A14
_021D79D4:
	ldr r0, _021D7A1C ; =0x0000060E
	bl PlaySE
	mov r1, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3d
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D7A14
_021D79FA:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7A14
	add r0, r5, #0
	bl MOD70_021D7FC4
	add r0, r5, #0
	bl MOD70_021D7C10
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D7A14:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021D7A1C: .word 0x0000060E
	thumb_func_end MOD70_021D79C0

	thumb_func_start MOD70_021D7A20
MOD70_021D7A20: ; 0x021D7A20
	push {r3, r4, r5, r6, r7, lr}
	ldr r7, [r0, #4]
	str r0, [sp]
	ldr r0, [r7, #0x14]
	mov r4, #0
	cmp r0, #0
	ble _021D7A82
	ldr r5, [sp]
	add r6, r7, #0
_021D7A32:
	ldr r0, [r7, #0x18]
	cmp r4, r0
	bne _021D7A5E
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020398
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020310
	mov r0, #1
	bl FUN_02005E80
	ldrh r0, [r6, #0x30]
	bl FUN_02005578
	b _021D7A76
_021D7A5E:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020398
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #1
	bl FUN_02020310
_021D7A76:
	ldr r0, [r7, #0x14]
	add r4, r4, #1
	add r5, r5, #4
	add r6, #0x1c
	cmp r4, r0
	blt _021D7A32
_021D7A82:
	ldr r0, [sp]
	bl MOD70_021D7D98
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD70_021D7A20

	thumb_func_start MOD70_021D7A8C
MOD70_021D7A8C: ; 0x021D7A8C
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #3
	bhi _021D7AD6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7AA2: ; jump table
	.short _021D7AAA - _021D7AA2 - 2 ; case 0
	.short _021D7AB6 - _021D7AA2 - 2 ; case 1
	.short _021D7AC2 - _021D7AA2 - 2 ; case 2
	.short _021D7ACE - _021D7AA2 - 2 ; case 3
_021D7AAA:
	bl MOD70_021D7CC0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D7AD6
_021D7AB6:
	bl MOD70_021D820C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D7AD6
_021D7AC2:
	bl MOD70_021D80C8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D7AD6
_021D7ACE:
	bl MOD70_021D7CB0
	mov r0, #1
	pop {r4, pc}
_021D7AD6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD70_021D7A8C

	thumb_func_start MOD70_021D7ADC
MOD70_021D7ADC: ; 0x021D7ADC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D7AF0 ; =0x000005DC
	bl PlaySE
	add r0, r4, #0
	bl MOD70_021D7D98
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D7AF0: .word 0x000005DC
	thumb_func_end MOD70_021D7ADC

	thumb_func_start MOD70_021D7AF4
MOD70_021D7AF4: ; 0x021D7AF4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _021D7BF8 ; =0x021D8284
	bl GX_SetBanks
	ldr r2, _021D7BFC ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	ldr r0, _021D7C00 ; =0x021D823C
	bl SetBothScreensModesAndDisable
	ldr r0, [r5, #0x10]
	ldr r2, _021D7C04 ; =0x021D8268
	mov r1, #1
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r5, #0x10]
	ldr r2, _021D7C08 ; =0x021D824C
	mov r1, #2
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x3d
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x10]
	mov r0, #0x65
	mov r3, #2
	bl GfGfxLoader_LoadCharData
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3d
	str r0, [sp, #0xc]
	ldr r2, [r5, #0x10]
	mov r0, #0x65
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x3d
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x65
	mov r1, #2
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r2, #0
	str r2, [sp]
	mov r1, #1
	ldr r0, [r5, #0x10]
	add r3, r1, #0
	bl BG_FillCharDataRange
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r5, #0x10]
	mov r1, #1
	add r3, r2, #0
	bl FillBgTilemapRect
	add r0, r5, #0
	mov r1, #1
	bl MOD70_021D7C2C
	add r4, r0, #0
	add r0, r5, #0
	bl MOD70_021D7CB0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x3d
	str r0, [sp, #4]
	lsl r2, r4, #0x10
	ldr r0, [r5, #0x10]
	mov r1, #1
	lsr r2, r2, #0x10
	mov r3, #2
	bl FUN_0200CB00
	add r0, r5, #0
	lsl r2, r4, #0x10
	add r0, #0x14
	mov r1, #0
	lsr r2, r2, #0x10
	mov r3, #2
	bl DrawFrameAndWindow1
	add r0, r5, #0
	lsl r2, r4, #0x10
	add r0, #0x24
	mov r1, #0
	lsr r2, r2, #0x10
	mov r3, #2
	bl DrawFrameAndWindow1
	ldr r0, [r5, #0x10]
	mov r1, #1
	bl BgCommitTilemapBufferToVram
	mov r3, #8
	ldr r0, _021D7C0C ; =0x04000050
	mov r1, #0
	mov r2, #6
	str r3, [sp]
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7BF8: .word MOD70_021D8284
_021D7BFC: .word 0x04000304
_021D7C00: .word MOD70_021D823C
_021D7C04: .word MOD70_021D8268
_021D7C08: .word MOD70_021D824C
_021D7C0C: .word 0x04000050
	thumb_func_end MOD70_021D7AF4

	thumb_func_start MOD70_021D7C10
MOD70_021D7C10: ; 0x021D7C10
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl MOD70_021D7C98
	pop {r4, pc}
	thumb_func_end MOD70_021D7C10

	thumb_func_start MOD70_021D7C2C
MOD70_021D7C2C: ; 0x021D7C2C
	push {r4, r5, lr}
	sub sp, #0x14
	mov r2, #1
	add r5, r0, #0
	str r2, [sp]
	mov r0, #0x1e
	str r0, [sp, #4]
	mov r0, #2
	add r4, r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r1, r5, #0
	ldr r0, [r5, #0x10]
	add r1, #0x14
	add r3, r2, #0
	bl AddWindowParameterized
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1e
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x3c
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r1, r5, #0
	mov r2, #1
	ldr r0, [r5, #0x10]
	add r1, #0x24
	add r3, r2, #0
	bl AddWindowParameterized
	add r0, r5, #0
	add r0, #0x14
	bl PutWindowTilemap
	add r5, #0x24
	add r0, r5, #0
	bl PutWindowTilemap
	add r4, #0xb4
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD70_021D7C2C

	thumb_func_start MOD70_021D7C98
MOD70_021D7C98: ; 0x021D7C98
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x14
_021D7CA0:
	add r0, r5, #0
	bl RemoveWindow
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #2
	blt _021D7CA0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD70_021D7C98

	thumb_func_start MOD70_021D7CB0
MOD70_021D7CB0: ; 0x021D7CB0
	push {r4, lr}
	add r4, r0, #0
	bl MOD70_021D7CE8
	add r0, r4, #0
	bl MOD70_021D7D98
	pop {r4, pc}
	thumb_func_end MOD70_021D7CB0

	thumb_func_start MOD70_021D7CC0
MOD70_021D7CC0: ; 0x021D7CC0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x14
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r0, #0x24
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r0, #0x14
	bl CopyWindowPixelsToVram_TextMode
	add r4, #0x24
	add r0, r4, #0
	bl CopyWindowPixelsToVram_TextMode
	pop {r4, pc}
	thumb_func_end MOD70_021D7CC0

	thumb_func_start MOD70_021D7CE8
MOD70_021D7CE8: ; 0x021D7CE8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x63
	lsl r0, r0, #2
	add r6, r5, #0
	ldr r0, [r5, r0]
	ldr r2, [r4]
	mov r3, #4
	add r6, #0x14
	bl BufferIntegerAsString
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x63
	lsl r0, r0, #2
	mov r2, #0x7d
	ldr r3, [r4, #4]
	lsl r2, r2, #4
	add r2, r3, r2
	ldr r0, [r5, r0]
	mov r3, #4
	bl BufferIntegerAsString
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, [r4, #8]
	mov r1, #2
	bl BufferMonthNameAbbr
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, [r4, #0xc]
	mov r1, #3
	mov r3, #2
	bl BufferIntegerAsString
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r5, r2]
	add r2, #0x10
	ldr r2, [r5, r2]
	mov r1, #0
	bl ReadMsgDataIntoString
	mov r2, #0x63
	lsl r2, r2, #2
	add r1, r2, #0
	ldr r0, [r5, r2]
	add r1, #8
	add r2, r2, #4
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	add r0, r6, #0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r1, [sp, #8]
	add r2, #0x95
	ldr r2, [r5, r2]
	add r0, r6, #0
	add r3, r1, #0
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl CopyWindowPixelsToVram_TextMode
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD70_021D7CE8

	thumb_func_start MOD70_021D7D98
MOD70_021D7D98: ; 0x021D7D98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r0, #0x1c
	ldr r1, [r4, #0x18]
	add r2, r4, #0
	mul r0, r1
	add r2, #0x20
	add r7, r2, r0
	add r0, r5, #0
	str r0, [sp, #0xc]
	add r0, #0x24
	mov r1, #0xf
	str r0, [sp, #0xc]
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _021D7DC8
	cmp r0, #1
	bne _021D7DC6
	b _021D7F1C
_021D7DC6:
	b _021D7F66
_021D7DC8:
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [sp, #0xc]
	ldr r2, [r7]
	add r3, r1, #0
	bl AddTextPrinterParameterized
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r5, r2]
	add r2, #0x10
	ldr r2, [r5, r2]
	mov r1, #5
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r1, [sp, #8]
	add r2, #0x91
	ldr r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r3, #0x48
	bl AddTextPrinterParameterized
	mov r2, #0x61
	lsl r2, r2, #2
	ldr r0, [r5, r2]
	add r2, #0xc
	ldrh r1, [r7, #0x10]
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r1, [sp, #8]
	add r2, #0x91
	ldr r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r3, #0x5e
	bl AddTextPrinterParameterized
	ldrh r0, [r7, #0x10]
	ldr r1, [r7, #8]
	bl GetGenderBySpeciesAndPersonality
	cmp r0, #0
	beq _021D7E3A
	cmp r0, #1
	beq _021D7E4C
	b _021D7E5E
_021D7E3A:
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r5, r2]
	add r2, #0x10
	ldr r2, [r5, r2]
	mov r1, #3
	bl ReadMsgDataIntoString
	b _021D7E68
_021D7E4C:
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r5, r2]
	add r2, #0x10
	ldr r2, [r5, r2]
	mov r1, #4
	bl ReadMsgDataIntoString
	b _021D7E68
_021D7E5E:
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl StringSetEmpty
_021D7E68:
	mov r1, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r1, [sp, #8]
	add r2, #0x91
	ldr r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r3, #0xae
	bl AddTextPrinterParameterized
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r5, r2]
	add r2, #0x10
	ldr r2, [r5, r2]
	mov r1, #1
	bl ReadMsgDataIntoString
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x63
	lsl r0, r0, #2
	ldrb r2, [r7, #0x12]
	ldr r0, [r5, r0]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	mov r2, #0x63
	lsl r2, r2, #2
	add r1, r2, #0
	ldr r0, [r5, r2]
	add r1, #8
	add r2, r2, #4
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r1, [sp, #8]
	add r2, #0x95
	ldr r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r3, #0xc2
	bl AddTextPrinterParameterized
	mov r2, #6
	lsl r2, r2, #6
	ldr r0, [r5, r2]
	add r2, #0x10
	ldr r2, [r5, r2]
	mov r1, #2
	bl ReadMsgDataIntoString
	mov r0, #0x10
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	add r2, #0x91
	ldr r0, [sp, #0xc]
	ldr r2, [r5, r2]
	add r3, r1, #0
	bl AddTextPrinterParameterized
	mov r1, #0x19
	lsl r1, r1, #4
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	ldr r0, [sp, #0xc]
	ldr r2, [r7, #4]
	bl AddTextPrinterParameterized
	b _021D7F66
_021D7F1C:
	mov r4, #0
_021D7F1E:
	ldrh r1, [r7, #0x14]
	cmp r1, #0
	beq _021D7F66
	mov r0, #0x62
	mov r2, #0x19
	lsl r0, r0, #2
	lsl r2, r2, #4
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	lsr r0, r4, #0x1f
	add r0, r4, r0
	asr r0, r0, #1
	lsl r0, r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	mov r2, #0x19
	str r0, [sp, #8]
	lsl r2, r2, #4
	mov r3, #1
	add r6, r4, #0
	and r6, r3
	mov r3, #0x60
	ldr r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r1, #0
	mul r3, r6
	bl AddTextPrinterParameterized
	add r4, r4, #1
	add r7, r7, #2
	cmp r4, #4
	blt _021D7F1E
_021D7F66:
	ldr r0, [sp, #0xc]
	bl CopyWindowPixelsToVram_TextMode
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD70_021D7D98

	thumb_func_start MOD70_021D7F70
MOD70_021D7F70: ; 0x021D7F70
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0x3d
	str r0, [sp]
	mov r0, #0x1b
	mov r1, #0x29
	mov r2, #0
	add r3, sp, #8
	bl GfGfxLoader_GetCellBank
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x3d
	str r0, [sp]
	mov r0, #0x1b
	mov r1, #0x2a
	mov r2, #0
	add r3, sp, #4
	bl GfGfxLoader_GetAnimBank
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r1, #0x20
	mov r2, #0x32
	mov r0, #0
	add r1, r4, r1
	lsl r2, r2, #6
	bl MIi_CpuClearFast
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	add r0, r4, #0
	bl MOD70_021D7FF8
	add r0, r4, #0
	bl MOD70_021D80C8
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD70_021D7F70

	thumb_func_start MOD70_021D7FC4
MOD70_021D7FC4: ; 0x021D7FC4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0x16
	mov r4, #0
	add r5, r7, #0
	lsl r6, r6, #4
_021D7FD0:
	ldr r0, [r5, r6]
	cmp r0, #0
	beq _021D7FDA
	bl FUN_0201FFC8
_021D7FDA:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _021D7FD0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl FreeToHeap
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD70_021D7FC4

	thumb_func_start MOD70_021D7FF8
MOD70_021D7FF8: ; 0x021D7FF8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x94
	mov r3, #0
	add r5, r0, #0
	str r1, [sp, #0x7c]
	str r2, [sp, #0x80]
	str r3, [sp, #0x74]
	str r3, [sp, #0x84]
	str r3, [sp, #0x88]
	str r3, [sp, #0x8c]
	add r0, sp, #0x90
	strb r3, [r0]
	add r0, sp, #0x2c
	str r0, [sp, #0x70]
	add r0, sp, #0x18
	str r0, [sp, #0x78]
	ldr r0, [r5, #0x34]
	mov r1, #0x28
	str r0, [sp, #0x50]
	add r0, sp, #0x70
	str r0, [sp, #0x54]
	mov r0, #1
	str r0, [sp, #0x68]
	mov r0, #0x3d
	str r3, [sp, #0x60]
	str r0, [sp, #0x6c]
	str r0, [sp]
	add r2, r3, #0
	mov r0, #0x1b
	add r3, sp, #0x14
	bl GfGfxLoader_GetCharData
	str r0, [sp, #0xc]
	mov r0, #0x1b
	mov r1, #0x27
	add r2, sp, #0x10
	mov r3, #0x3d
	bl GfGfxLoader_GetPlttData
	mov r4, #0
	ldr r6, _021D80C4 ; =0x021D82AC
	str r0, [sp, #8]
	str r4, [sp, #4]
	add r7, r4, #0
_021D8050:
	add r0, sp, #0x2c
	bl NNS_G2dInitImageProxy
	add r0, sp, #0x18
	bl NNS_G2dInitImagePaletteProxy
	ldr r0, [sp, #0x14]
	add r1, r4, #0
	mov r2, #1
	add r3, sp, #0x2c
	bl NNS_G2dLoadImage1DMapping
	ldr r0, [sp, #0x10]
	add r1, r7, #0
	mov r2, #1
	add r3, sp, #0x18
	bl NNS_G2dLoadPalette
	ldr r0, [r6]
	lsl r0, r0, #0xc
	str r0, [sp, #0x58]
	ldr r0, [r6, #4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x5c]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #0x64]
	add r0, sp, #0x50
	bl FUN_0201FF84
	mov r1, #0x16
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x32
	lsl r0, r0, #6
	add r4, r4, r0
	ldr r0, [sp, #4]
	add r7, #0x20
	add r0, r0, #1
	add r6, #8
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r0, #6
	blt _021D8050
	ldr r0, [sp, #8]
	bl FreeToHeap
	ldr r0, [sp, #0xc]
	bl FreeToHeap
	add sp, #0x94
	pop {r4, r5, r6, r7, pc}
	nop
_021D80C4: .word MOD70_021D82AC
	thumb_func_end MOD70_021D7FF8

	thumb_func_start MOD70_021D80C8
MOD70_021D80C8: ; 0x021D80C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r7, r0, #0
	ldr r0, [r7, #4]
	mov r4, #0
	str r0, [sp, #0x20]
	ldr r0, [r0, #0x14]
	cmp r0, #0
	bgt _021D80DC
	b _021D81E4
_021D80DC:
	ldr r5, [sp, #0x20]
	str r4, [sp, #0x18]
	add r0, r5, #0
	str r0, [sp, #0x1c]
	add r0, #0x33
	str r0, [sp, #0x1c]
	mov r0, #0x67
	lsl r0, r0, #2
	add r0, r7, r0
	str r4, [sp, #0x14]
	add r6, r7, #0
	str r0, [sp, #0x24]
_021D80F4:
	mov r0, #1
	str r0, [sp]
	ldr r0, [r5, #0x28]
	add r2, r5, #0
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r5, #0x2c]
	add r2, #0x32
	str r0, [sp, #0xc]
	mov r0, #0x66
	lsl r0, r0, #2
	ldrh r1, [r5, #0x30]
	ldrb r2, [r2]
	ldr r0, [r7, r0]
	mov r3, #0x20
	bl CreateMon
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	ldr r2, [sp, #0x1c]
	mov r1, #0x70
	bl SetMonData
	mov r1, #0x66
	lsl r1, r1, #2
	ldr r1, [r7, r1]
	add r0, sp, #0x28
	mov r2, #2
	bl FUN_02068B68
	ldr r0, [sp, #0x24]
	add r1, sp, #0x28
	str r0, [sp]
	ldr r0, [r5, #0x28]
	ldr r3, _021D8208 ; =0x021D822C
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	ldrh r0, [r5, #0x30]
	mov r2, #0x3d
	str r0, [sp, #0x10]
	add r0, sp, #0x28
	ldrh r0, [r0]
	ldrh r1, [r1, #2]
	bl FUN_02012530
	mov r1, #0x32
	ldr r0, [sp, #0x24]
	lsl r1, r1, #6
	bl DC_FlushRange
	mov r2, #0x32
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x18]
	lsl r2, r2, #6
	bl GX_LoadOBJ
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3d
	str r0, [sp, #4]
	add r0, sp, #0x28
	add r1, sp, #0x28
	ldrh r0, [r0]
	ldrh r1, [r1, #4]
	ldr r3, [sp, #0x14]
	mov r2, #1
	bl GfGfxLoader_GXLoadPal
	ldr r0, [sp, #0x20]
	ldr r0, [r0, #0x18]
	cmp r4, r0
	bne _021D81A8
	mov r0, #1
	bl FUN_02005E80
	ldrh r0, [r5, #0x30]
	bl FUN_02005578
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	mov r1, #0
	bl FUN_02020398
	b _021D81B4
_021D81A8:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	mov r1, #1
	bl FUN_02020398
_021D81B4:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r0, #0x1c
	str r0, [sp, #0x1c]
	mov r0, #0x32
	lsl r0, r0, #6
	add r0, r1, r0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r4, r4, #1
	add r0, #0x20
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	add r5, #0x1c
	ldr r0, [r0, #0x14]
	add r6, r6, #4
	cmp r4, r0
	blt _021D80F4
_021D81E4:
	cmp r4, #6
	bge _021D8202
	lsl r0, r4, #2
	mov r6, #0x16
	add r5, r7, r0
	mov r7, #0
	lsl r6, r6, #4
_021D81F2:
	ldr r0, [r5, r6]
	add r1, r7, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _021D81F2
_021D8202:
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8208: .word MOD70_021D822C
	thumb_func_end MOD70_021D80C8

	thumb_func_start MOD70_021D820C
MOD70_021D820C: ; 0x021D820C
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	mov r6, #0x16
	add r5, r0, #0
	add r7, r4, #0
	lsl r6, r6, #4
_021D8218:
	ldr r0, [r5, r6]
	add r1, r7, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _021D8218
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD70_021D820C

	.rodata
	.global MOD70_021D822C
MOD70_021D822C: ; 0x021D822C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD70_021D823C
MOD70_021D823C: ; 0x021D823C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD70_021D824C
MOD70_021D824C: ; 0x021D824C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD70_021D8268
MOD70_021D8268: ; 0x021D8268
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD70_021D8284
MOD70_021D8284: ; 0x021D8284
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD70_021D82AC
MOD70_021D82AC: ; 0x021D82AC
	.byte 0x78, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00
	.byte 0xC8, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00
	.byte 0xD8, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00

	.data
	.global MOD70_021D82E0
MOD70_021D82E0: ; 0x021D82E0
	.word MOD70_021D7970, MOD70_021D79C0, MOD70_021D7A20, MOD70_021D7A8C
	.word MOD70_021D7ADC

	.bss
