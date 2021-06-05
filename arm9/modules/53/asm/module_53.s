	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD53_021D74E0
MOD53_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5]
	add r6, r0, #0
	cmp r1, #0
	beq _021D74F6
	cmp r1, #1
	bne _021D74F4
	b _021D7622
_021D74F4:
	b _021D7630
_021D74F6:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7638 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D763C ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #3
	mov r1, #0x27
	lsl r2, r2, #6
	bl CreateHeap
	ldr r1, _021D7640 ; =0x0000940C
	add r0, r6, #0
	mov r2, #0x27
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D7640 ; =0x0000940C
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x27
	bl FUN_02016B94
	str r0, [r4]
	mov r0, #0x27
	bl ScrStrBufs_new
	str r0, [r4, #0xc]
	ldr r2, _021D7644 ; =0x00000176
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x27
	bl NewMsgDataFromNarc
	str r0, [r4, #0x10]
	mov r0, #4
	mov r1, #8
	bl SetKeyRepeatTimers
	bl MOD53_021D78D0
	ldr r0, [r4]
	bl MOD53_021D78F0
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x27
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x11
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r6, #0
	bl OverlayManager_GetField18
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD53_021D7B60
	bl FUN_0201CC08
	mov r0, #2
	bl FUN_0201CC24
	ldr r0, _021D7648 ; =MOD53_021D78A8
	ldr r1, [r4]
	bl Main_SetVBlankIntrCB
	add r0, r4, #0
	bl MOD53_021D79F8
	bl MOD53_021D7C54
	add r0, r4, #0
	bl MOD53_021D7C84
	add r0, r4, #0
	bl MOD53_021D7E08
	add r0, r4, #0
	add r1, r6, #0
	bl MOD53_021D7FDC
	mov r1, #0
	mov r0, #0x34
	add r2, r1, #0
	bl FUN_0200433C
	ldr r2, _021D764C ; =0x04000304
	ldr r0, _021D7650 ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	add r0, r4, #0
	bl FUN_02083D48
	mov r0, #0
	mov r1, #1
	bl FUN_020334E8
	bl FUN_02031190
	cmp r0, #0
	bne _021D7602
	mov r0, #3
	bl FUN_02032B6C
_021D7602:
	bl FUN_02033E74
	bl FUN_02031190
	cmp r0, #0
	bne _021D761A
	mov r0, #1
	bl FUN_02052B74
	mov r0, #1
	bl FUN_0202EEB0
_021D761A:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7630
_021D7622:
	bl OverlayManager_GetData
	mov r0, #0
	str r0, [r5]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7630:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D7638: .word 0xFFFFE0FF
_021D763C: .word 0x04001000
_021D7640: .word 0x0000940C
_021D7644: .word 0x00000176
_021D7648: .word MOD53_021D78A8
_021D764C: .word 0x04000304
_021D7650: .word 0xFFFF7FFF
	thumb_func_end MOD53_021D74E0

	thumb_func_start MOD53_021D7654
MOD53_021D7654: ; 0x021D7654
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D767A
	ldr r0, _021D7750 ; =0x000093B4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D767A
	bl FUN_0202CB8C
	ldr r1, _021D7750 ; =0x000093B4
	ldr r2, [r4, r1]
	and r0, r2
	str r0, [r4, r1]
_021D767A:
	mov r0, #3
	ldr r1, [r5]
	lsl r0, r0, #8
	str r1, [r4, r0]
	ldr r1, [r5]
	add r0, r4, #0
	bl MOD53_021D93E8
	ldr r1, [r5]
	cmp r1, #3
	bhi _021D7744
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D769C: ; jump table
	.short _021D76A4 - _021D769C - 2 ; case 0
	.short _021D76D2 - _021D769C - 2 ; case 1
	.short _021D7718 - _021D769C - 2 ; case 2
	.short _021D7738 - _021D769C - 2 ; case 3
_021D76A4:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7744
	bl FUN_02031190
	cmp r0, #0
	beq _021D76CC
	bl MOD53_021D9160
	cmp r0, #2
	blt _021D7744
	mov r1, #0
	mov r0, #0x80
	add r2, r1, #0
	bl FUN_02030ADC
	mov r0, #1
	str r0, [r5]
	b _021D7744
_021D76CC:
	mov r0, #1
	str r0, [r5]
	b _021D7744
_021D76D2:
	mov r0, #0xc1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r2, r0, #3
	ldr r0, _021D7754 ; =MOD53_021D98A0
	ldr r2, [r0, r2]
	cmp r2, #0
	beq _021D76E8
	add r0, r4, #0
	blx r2
	str r0, [r5]
_021D76E8:
	mov r0, #0x9e
	lsl r0, r0, #2
	ldr r2, _021D7758 ; =0x000E0D0F
	add r0, r4, r0
	mov r1, #0
	add r3, r4, #0
	bl MOD53_021D9014
	bl FUN_02031190
	cmp r0, #0
	bne _021D770E
	add r0, r4, #0
	bl MOD53_021D928C
	ldr r1, [r5]
	cmp r1, #1
	bne _021D770E
	str r0, [r5]
_021D770E:
	ldr r0, _021D775C ; =0x00004374
	add r0, r4, r0
	bl MOD53_021D8FB8
	b _021D7744
_021D7718:
	mov r0, #0xc1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r3, r0, #3
	ldr r0, _021D7754 ; =MOD53_021D98A0
	ldr r2, [r0, r3]
	cmp r2, #0
	beq _021D7744
	ldr r0, _021D7760 ; =MOD53_021D98A0 + 4
	ldr r0, [r0, r3]
	cmp r0, #0
	beq _021D7744
	add r0, r4, #0
	blx r2
	str r0, [r5]
	b _021D7744
_021D7738:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7744
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7744:
	ldr r0, [r4, #0x34]
	bl FUN_0201FDEC
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D7750: .word 0x000093B4
_021D7754: .word MOD53_021D98A0
_021D7758: .word 0x000E0D0F
_021D775C: .word 0x00004374
_021D7760: .word MOD53_021D98A0 + 4
	thumb_func_end MOD53_021D7654

	thumb_func_start MOD53_021D7764
MOD53_021D7764: ; 0x021D7764
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl OverlayManager_GetData
	add r6, r0, #0
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r4, r0, #0
	ldr r0, [r7]
	cmp r0, #3
	bls _021D7780
	b _021D789E
_021D7780:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D778C: ; jump table
	.short _021D7794 - _021D778C - 2 ; case 0
	.short _021D7820 - _021D778C - 2 ; case 1
	.short _021D784E - _021D778C - 2 ; case 2
	.short _021D786E - _021D778C - 2 ; case 3
_021D7794:
	mov r0, #0x27
	bl FUN_020294A8
	add r1, r0, #0
	ldr r0, [r4, #4]
	mov r2, #4
	bl FUN_02028AD4
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r4, #0
	add r5, r6, #0
_021D77D8:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D77D8
	ldr r0, [r6, #0x34]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	add r0, r6, #0
	bl MOD53_021D8104
	ldr r0, [r6]
	bl MOD53_021D7B24
	bl FUN_0201CD04
	ldr r0, [r6, #0x10]
	bl DestroyMsgData
	ldr r0, [r6, #0xc]
	bl ScrStrBufs_delete
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021D789E
_021D7820:
	mov r0, #1
	bl FUN_02032B6C
	bl FUN_02031B50
	ldr r0, [r4]
	bl FUN_02052F8C
	ldr r2, _021D78A4 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	mov r0, #0
	bl FUN_02052B74
	mov r0, #0
	bl FUN_0202EEB0
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021D789E
_021D784E:
	mov r1, #0x25
	lsl r1, r1, #0xa
	ldr r1, [r6, r1]
	cmp r1, #0
	beq _021D7868
	bl FUN_0202CB8C
	cmp r0, #1
	bne _021D789E
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021D789E
_021D7868:
	add r0, r0, #1
	str r0, [r7]
	b _021D789E
_021D786E:
	mov r0, #2
	bl FUN_02032B6C
	add r0, r6, #0
	bl MOD53_021D7AE8
	ldr r0, [r6, #8]
	bl FreeToHeap
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x27
	bl DestroyHeap
	mov r0, #2
	bl FUN_02032B6C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D789E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D78A4: .word 0x04000304
	thumb_func_end MOD53_021D7764

	thumb_func_start MOD53_021D78A8
MOD53_021D78A8: ; 0x021D78A8
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201C30C
	bl FUN_02009F80
	add r0, r4, #0
	bl FUN_0201AB60
	ldr r3, _021D78C8 ; =0x027E0000
	ldr r1, _021D78CC ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_021D78C8: .word 0x027E0000
_021D78CC: .word 0x00003FF8
	thumb_func_end MOD53_021D78A8

	thumb_func_start MOD53_021D78D0
MOD53_021D78D0: ; 0x021D78D0
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D78EC ; =0x021D95A4
	add r3, sp, #0
	mov r2, #5
_021D78DA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D78DA
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D78EC: .word MOD53_021D95A4
	thumb_func_end MOD53_021D78D0

	thumb_func_start MOD53_021D78F0
MOD53_021D78F0: ; 0x021D78F0
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _021D79E0 ; =0x021D94F8
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D79E4 ; =0x021D9518
	add r3, sp, #0x70
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
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _021D79E8 ; =0x021D9550
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _021D79EC ; =0x021D956C
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D79F0 ; =0x021D9588
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _021D79F4 ; =0x021D9534
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
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x27
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x27
	bl FUN_02017F18
	add sp, #0x9c
	pop {r4, r5, pc}
	nop
_021D79E0: .word MOD53_021D94F8
_021D79E4: .word MOD53_021D9518
_021D79E8: .word MOD53_021D9550
_021D79EC: .word MOD53_021D956C
_021D79F0: .word MOD53_021D9588
_021D79F4: .word MOD53_021D9534
	thumb_func_end MOD53_021D78F0

	thumb_func_start MOD53_021D79F8
MOD53_021D79F8: ; 0x021D79F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D7ACC ; =0x0000438A
	add r6, r7, #0
	add r4, r7, r0
	mov r0, #0x38
	add r5, r7, #0
	str r0, [sp, #4]
_021D7A0E:
	mov r0, #8
	mov r1, #0x27
	bl String_ctor
	str r0, [r6, #0x14]
	ldrb r1, [r4]
	ldr r0, [sp, #4]
	bic r1, r0
	strb r1, [r4]
	ldr r0, _021D7AD0 ; =0x000043B6
	mov r1, #0
	strh r1, [r6, r0]
	mov r0, #0xcd
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp]
	add r6, r6, #4
	add r0, r0, #1
	add r4, #0xa
	add r5, #8
	str r0, [sp]
	cmp r0, #5
	blt _021D7A0E
	mov r0, #0xa
	mov r1, #0x27
	bl String_ctor
	str r0, [r7, #0x28]
	mov r0, #0x50
	mov r1, #0x27
	bl String_ctor
	str r0, [r7, #0x2c]
	ldr r0, _021D7AD4 ; =0x00004376
	mov r2, #0
	strb r2, [r7, r0]
	mov r1, #1
	add r0, r0, #1
	strb r1, [r7, r0]
	ldr r0, _021D7AD8 ; =0x000093F4
	str r1, [r7, r0]
	add r0, r0, #4
	str r2, [r7, r0]
	mov r0, #0xc6
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r7, r0]
	bl FUN_0202CB8C
	mov r1, #0xc7
	lsl r1, r1, #2
	str r0, [r7, r1]
	ldr r2, _021D7ADC ; =0x000093FC
	mov r3, #0
	str r3, [r7, r2]
	add r0, r2, #4
	str r3, [r7, r0]
	add r0, r2, #0
	sub r1, #0x18
	str r3, [r7, r1]
	add r0, #8
	str r3, [r7, r0]
	add r2, #0xc
	str r3, [r7, r2]
	bl FUN_02031190
	add r0, r7, #0
	mov r1, #4
	bl MOD53_021D93E0
	ldr r0, [r7, #0x10]
	ldr r2, [r7, #0x28]
	mov r1, #7
	bl ReadMsgDataIntoString
	mov r1, #0xf
	mov r0, #0x27
	lsl r1, r1, #0xa
	bl AllocFromHeap
	ldr r1, _021D7AE0 ; =0x000043C8
	str r0, [r7, r1]
	mov r0, #0x27
	bl FUN_02014590
	ldr r1, _021D7AE4 ; =0x000093F0
	str r0, [r7, r1]
	mov r0, #0xc5
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r7, r0]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7ACC: .word 0x0000438A
_021D7AD0: .word 0x000043B6
_021D7AD4: .word 0x00004376
_021D7AD8: .word 0x000093F4
_021D7ADC: .word 0x000093FC
_021D7AE0: .word 0x000043C8
_021D7AE4: .word 0x000093F0
	thumb_func_end MOD53_021D79F8

	thumb_func_start MOD53_021D7AE8
MOD53_021D7AE8: ; 0x021D7AE8
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _021D7B1C ; =0x000043C8
	ldr r0, [r6, r0]
	bl FreeToHeap
	ldr r0, _021D7B20 ; =0x000093F0
	ldr r0, [r6, r0]
	bl FUN_020145A8
	mov r4, #0
	add r5, r6, #0
_021D7B00:
	ldr r0, [r5, #0x14]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _021D7B00
	ldr r0, [r6, #0x2c]
	bl String_dtor
	ldr r0, [r6, #0x28]
	bl String_dtor
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D7B1C: .word 0x000043C8
_021D7B20: .word 0x000093F0
	thumb_func_end MOD53_021D7AE8

	thumb_func_start MOD53_021D7B24
MOD53_021D7B24: ; 0x021D7B24
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #3
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD53_021D7B24

	thumb_func_start MOD53_021D7B60
MOD53_021D7B60: ; 0x021D7B60
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5]
	mov r0, #0x40
	mov r1, #0
	str r0, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	mov r0, #0x4e
	add r2, r1, #0
	add r3, r1, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	mov r0, #0x4e
	mov r1, #1
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x27
	bl FUN_02002EEC
	mov r1, #0x1a
	mov r0, #4
	lsl r1, r1, #4
	mov r2, #0x27
	bl FUN_02002EEC
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	mov r1, #2
	str r0, [sp, #0xc]
	mov r0, #0x4e
	add r2, r4, #0
	add r3, r1, #0
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	str r0, [sp, #0xc]
	mov r0, #0x4e
	mov r1, #4
	add r2, r4, #0
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	str r0, [sp, #0xc]
	mov r0, #0x4e
	mov r1, #3
	add r2, r4, #0
	mov r3, #5
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	mov r1, #5
	str r0, [sp, #0xc]
	mov r0, #0x4e
	add r2, r4, #0
	add r3, r1, #0
	bl GfGfxLoader_LoadScrnData
	ldr r0, [r5, #8]
	ldr r0, [r0, #8]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD53_021D7B60

	thumb_func_start MOD53_021D7C54
MOD53_021D7C54: ; 0x021D7C54
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D7C80 ; =0x021D9508
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x27
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D7C80: .word MOD53_021D9508
	thumb_func_end MOD53_021D7C54

	thumb_func_start MOD53_021D7C84
MOD53_021D7C84: ; 0x021D7C84
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	bl NNS_G2dInitOamManagerModule
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x27
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r5, #0
	mov r0, #0x35
	add r1, #0x38
	mov r2, #0x27
	bl FUN_02008C9C
	str r0, [r5, #0x34]
	add r0, r5, #0
	mov r2, #1
	add r0, #0x38
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r7, #0x16
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #4
_021D7CCA:
	mov r0, #2
	add r1, r6, #0
	mov r2, #0x27
	bl FUN_02008DEC
	str r0, [r4, r7]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _021D7CCA
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	mov r0, #0x27
	str r0, [sp, #8]
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x4e
	mov r2, #6
	bl FUN_02008F34
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #0x27
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x4e
	add r3, r2, #0
	bl FUN_02008FEC
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x4e
	mov r2, #7
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x4e
	mov r2, #8
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x4e
	mov r2, #6
	bl FUN_02008F34
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0x27
	mov r2, #0
	sub r1, #0x1c
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x4e
	add r3, r2, #0
	bl FUN_02008FEC
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x4e
	mov r2, #7
	bl FUN_020090AC
	mov r1, #0x62
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x4e
	mov r2, #8
	bl FUN_020090AC
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0x1c
	ldr r0, [r5, r1]
	bl FUN_02009A50
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_02009A50
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD53_021D7C84

	thumb_func_start MOD53_021D7E08
MOD53_021D7E08: ; 0x021D7E08
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r2, #0x16
	str r1, [sp, #0x10]
	lsl r2, r2, #4
	ldr r0, [r5, r2]
	add r3, r1, #0
	str r0, [sp, #0x14]
	add r0, r2, #4
	ldr r0, [r5, r0]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r5, r0]
	str r0, [sp, #0x1c]
	add r0, r2, #0
	add r0, #0xc
	ldr r0, [r5, r0]
	add r2, #0x30
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r5, r2
	add r2, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	mov r1, #1
	mov r3, #0x16
	str r1, [sp]
	sub r0, r1, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r3, r3, #4
	ldr r2, [r5, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r5, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r5, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r5, r2]
	add r3, #0x54
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r5, r3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02008AA4
	ldr r0, [r5, #0x34]
	mov r6, #0
	str r0, [sp, #0x34]
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r5, r0
	str r0, [sp, #0x38]
	mov r0, #1
	lsl r0, r0, #0xc
	str r6, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x50]
	add r0, sp, #0x34
	strh r6, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x58]
	str r0, [sp, #0x5c]
	mov r0, #0x27
	str r0, [sp, #0x60]
	mov r0, #0x6d
	lsl r0, r0, #2
	add r0, r5, r0
	mov r7, #0x18
	add r4, r5, #0
	str r0, [sp, #0x2c]
_021D7EBC:
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x38]
	lsl r0, r7, #0xc
	str r0, [sp, #0x3c]
	mov r0, #1
	lsl r0, r0, #0x12
	str r0, [sp, #0x40]
	mov r0, #2
	str r0, [sp, #0x5c]
	add r0, sp, #0x34
	bl FUN_0201FE94
	mov r1, #0x76
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r6, #0
	bl FUN_02020130
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r7, #0x28
	add r4, r4, #4
	cmp r6, #5
	blt _021D7EBC
	mov r0, #0x6d
	lsl r0, r0, #2
	add r0, r5, r0
	ldr r6, _021D7FD8 ; =0x021D9600
	mov r7, #0
	add r4, r5, #0
	str r0, [sp, #0x30]
_021D7F14:
	ldr r0, [sp, #0x30]
	str r0, [sp, #0x38]
	ldrh r0, [r6]
	lsl r0, r0, #0xc
	str r0, [sp, #0x3c]
	ldrh r0, [r6, #2]
	lsl r0, r0, #0xc
	str r0, [sp, #0x40]
	add r0, sp, #0x34
	bl FUN_0201FE94
	mov r1, #0x92
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x92
	lsl r0, r0, #2
	ldrh r1, [r6, #4]
	ldr r0, [r4, r0]
	bl FUN_02020130
	cmp r7, #8
	blt _021D7F56
	mov r0, #0x92
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_02020238
_021D7F56:
	add r7, r7, #1
	add r6, r6, #6
	add r4, r4, #4
	cmp r7, #0xc
	blt _021D7F14
	mov r0, #0x92
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #6
	bl FUN_02020130
	mov r7, #6
	mov r6, #0
	mov r4, #0x20
	lsl r7, r7, #0xe
_021D7F74:
	mov r0, #1
	lsl r1, r4, #0xc
	lsl r0, r0, #0x14
	add r0, r1, r0
	str r0, [sp, #0x40]
	add r0, sp, #0x34
	str r7, [sp, #0x3c]
	bl FUN_0201FE94
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02020130
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020310
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r4, #0x20
	add r5, r5, #4
	cmp r6, #5
	blt _021D7F74
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7FD8: .word MOD53_021D9600
	thumb_func_end MOD53_021D7E08

	thumb_func_start MOD53_021D7FDC
MOD53_021D7FDC: ; 0x021D7FDC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	mov r1, #0xb6
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r7]
	add r1, r7, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0xb6
	lsl r0, r0, #2
	add r0, r7, r0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r0, #2
	str r0, [sp]
	mov r0, #0x1e
	str r0, [sp, #4]
	mov r0, #0xf
	str r0, [sp, #8]
	mov r0, #0
	mov r2, #1
	str r0, [sp, #0xc]
	str r2, [sp, #0x10]
	mov r1, #0xb2
	lsl r1, r1, #2
	ldr r0, [r7]
	add r1, r7, r1
	add r3, r2, #0
	bl FUN_02019064
	mov r0, #0xb2
	lsl r0, r0, #2
	add r0, r7, r0
	mov r1, #2
	bl FillWindowPixelBuffer
	mov r0, #0x15
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021D80F8 ; =0x000001C3
	mov r1, #0xba
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r7]
	add r1, r7, r1
	mov r2, #1
	mov r3, #0x19
	bl FUN_02019064
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r7, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r1, [r7, #0x28]
	mov r0, #1
	mov r2, #0
	mov r3, #0x30
	bl FUN_02002F40
	add r3, r0, #0
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D80FC ; =0x00070100
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0xba
	lsl r0, r0, #2
	ldr r2, [r7, #0x28]
	add r0, r7, r0
	mov r1, #1
	add r3, r3, #2
	bl AddTextPrinterParameterized2
	mov r0, #0
	str r0, [sp, #0x14]
	mov r0, #0x9e
	lsl r0, r0, #2
	mov r6, #1
	mov r4, #3
	add r5, r7, r0
_021D80A8:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r7]
	add r1, r5, #0
	mov r2, #4
	mov r3, #5
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x14]
	add r6, #0x14
	add r0, r0, #1
	add r4, r4, #4
	add r5, #0x10
	str r0, [sp, #0x14]
	cmp r0, #5
	blt _021D80A8
	mov r0, #0x9e
	lsl r0, r0, #2
	ldr r2, _021D8100 ; =0x000E0D0F
	add r0, r7, r0
	mov r1, #0
	add r3, r7, #0
	bl MOD53_021D9014
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D80F8: .word 0x000001C3
_021D80FC: .word 0x00070100
_021D8100: .word 0x000E0D0F
	thumb_func_end MOD53_021D7FDC

	thumb_func_start MOD53_021D8104
MOD53_021D8104: ; 0x021D8104
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r0, #0x9e
	lsl r0, r0, #2
	mov r4, #0
	add r5, r6, r0
_021D8110:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #5
	blt _021D8110
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	mov r0, #0xb2
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	mov r0, #0xb6
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD53_021D8104

	thumb_func_start MOD53_021D8140
MOD53_021D8140: ; 0x021D8140
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r5, r2, #0
	cmp r1, #0
	ble _021D815E
	lsl r0, r1, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D816C
_021D815E:
	lsl r0, r1, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D816C:
	bl _ffix
	sub r5, #8
	str r0, [sp]
	cmp r5, #0
	ble _021D818A
	lsl r0, r5, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _021D8198
_021D818A:
	lsl r0, r5, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_021D8198:
	bl _ffix
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD53_021D8140

	thumb_func_start MOD53_021D81B0
MOD53_021D81B0: ; 0x021D81B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _021D83AC ; =0x021D95CC
	bl FUN_02020988
	mov r1, #0
	mvn r1, r1
	str r0, [sp, #8]
	cmp r0, r1
	beq _021D81FE
	cmp r0, #0xb
	bhi _021D81FE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D81DA: ; jump table
	.short _021D81F2 - _021D81DA - 2 ; case 0
	.short _021D81F2 - _021D81DA - 2 ; case 1
	.short _021D81F2 - _021D81DA - 2 ; case 2
	.short _021D81F2 - _021D81DA - 2 ; case 3
	.short _021D81F2 - _021D81DA - 2 ; case 4
	.short _021D81F2 - _021D81DA - 2 ; case 5
	.short _021D81F2 - _021D81DA - 2 ; case 6
	.short _021D81F2 - _021D81DA - 2 ; case 7
	.short _021D821A - _021D81DA - 2 ; case 8
	.short _021D82BE - _021D81DA - 2 ; case 9
	.short _021D82BE - _021D81DA - 2 ; case 10
	.short _021D82BE - _021D81DA - 2 ; case 11
_021D81F2:
	ldr r2, _021D83B0 ; =0x00004376
	ldr r0, [sp]
	ldrb r1, [r0, r2]
	ldr r0, [sp, #8]
	cmp r1, r0
	bne _021D8200
_021D81FE:
	b _021D8316
_021D8200:
	add r1, r0, #0
	ldr r0, [sp]
	strb r1, [r0, r2]
	mov r1, #0x92
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r1, [sp, #8]
	bl MOD53_021D83DC
	ldr r0, _021D83B4 ; =0x000005DC
	bl FUN_020054C8
	b _021D8316
_021D821A:
	mov r1, #0xc1
	ldr r0, [sp]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	cmp r0, #4
	bne _021D8316
	bl FUN_02031190
	cmp r0, #0
	bne _021D8280
	bl FUN_0202CB8C
	mov r2, #0xc7
	ldr r1, [sp]
	lsl r2, r2, #2
	ldr r1, [r1, r2]
	cmp r1, r0
	beq _021D8246
	ldr r0, _021D83B8 ; =0x000005F2
	bl FUN_020054C8
	b _021D8316
_021D8246:
	bl FUN_02030F20
	bl FUN_02032B6C
	ldr r1, _021D83BC ; =0x000093F4
	ldr r0, [sp]
	mov r2, #2
	str r2, [r0, r1]
	mov r1, #1
	add r2, r1, #0
	bl MOD53_021D91C8
	ldr r0, [sp]
	mov r1, #5
	bl MOD53_021D93E0
	mov r1, #0x92
	ldr r0, [sp]
	lsl r1, r1, #2
	add r0, r0, r1
	mov r1, #1
	bl MOD53_021D840C
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021D83B4 ; =0x000005DC
	bl FUN_020054C8
	b _021D8316
_021D8280:
	ldr r1, _021D83C0 ; =0x0000438B
	ldr r0, [sp]
	ldrb r0, [r0, r1]
	cmp r0, #2
	bne _021D8292
	ldr r0, _021D83B8 ; =0x000005F2
	bl FUN_020054C8
	b _021D8316
_021D8292:
	mov r1, #1
	ldr r0, [sp]
	add r2, r1, #0
	bl MOD53_021D91C8
	ldr r0, [sp]
	mov r1, #5
	bl MOD53_021D93E0
	mov r1, #0x92
	ldr r0, [sp]
	lsl r1, r1, #2
	add r0, r0, r1
	mov r1, #1
	bl MOD53_021D840C
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021D83B4 ; =0x000005DC
	bl FUN_020054C8
	b _021D8316
_021D82BE:
	ldr r0, [sp, #8]
	ldr r5, [sp]
	str r0, [sp, #0xc]
	sub r0, #9
	mov r4, #0
	mov r7, #0x1e
	mov r6, #0x1d
	str r0, [sp, #0xc]
_021D82CE:
	ldr r0, [sp, #0xc]
	cmp r0, r4
	bne _021D82E2
	mov r0, #0x9b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl FUN_02020130
	b _021D82EE
_021D82E2:
	mov r0, #0x9b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02020130
_021D82EE:
	add r4, r4, #1
	add r7, r7, #2
	add r5, r5, #4
	add r6, r6, #2
	cmp r4, #3
	blt _021D82CE
	ldr r2, _021D83C4 ; =0x00004377
	ldr r0, [sp]
	ldrb r1, [r0, r2]
	ldr r0, [sp, #8]
	sub r0, #9
	str r0, [sp, #8]
	cmp r1, r0
	beq _021D8316
	add r1, r0, #0
	ldr r0, [sp]
	strb r1, [r0, r2]
	ldr r0, _021D83C8 ; =0x000005E5
	bl FUN_020054C8
_021D8316:
	ldr r0, _021D83CC ; =0x021D94F0
	bl FUN_02020968
	add r4, r0, #0
	bl FUN_02031190
	lsl r1, r0, #2
	ldr r0, [sp]
	add r1, r0, r1
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _021D836C
	bl FUN_02031190
	lsl r1, r0, #2
	ldr r0, [sp]
	ldr r2, _021D83D0 ; =gMain + 0x40
	add r1, r0, r1
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldrh r1, [r2, #0x1c]
	ldrh r2, [r2, #0x1e]
	bl MOD53_021D8140
	bl FUN_02031190
	lsl r1, r0, #2
	ldr r0, [sp]
	add r1, r0, r1
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
_021D836C:
	add r0, sp, #0x10
	mov r1, #4
	mov r2, #0x40
	bl FUN_0201CD38
	cmp r0, #1
	bne _021D83A6
	ldr r3, _021D83D4 ; =0x00004378
	ldr r0, [sp]
	ldr r2, [sp]
	sub r4, r3, #2
	ldrb r2, [r2, r4]
	add r0, r0, r3
	sub r4, r3, #1
	ldr r3, [sp]
	add r1, sp, #0x10
	ldrb r3, [r3, r4]
	bl MOD53_021D947C
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _021D83A6
	ldr r1, _021D83D8 ; =0x00004380
	ldr r0, [sp]
	ldrb r2, [r0, r1]
	mov r0, #0x38
	bic r2, r0
	ldr r0, [sp]
	strb r2, [r0, r1]
_021D83A6:
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}
	nop
_021D83AC: .word MOD53_021D95CC
_021D83B0: .word 0x00004376
_021D83B4: .word 0x000005DC
_021D83B8: .word 0x000005F2
_021D83BC: .word 0x000093F4
_021D83C0: .word 0x0000438B
_021D83C4: .word 0x00004377
_021D83C8: .word 0x000005E5
_021D83CC: .word MOD53_021D94F0
_021D83D0: .word gMain + 0x40
_021D83D4: .word 0x00004378
_021D83D8: .word 0x00004380
	thumb_func_end MOD53_021D81B0

	thumb_func_start MOD53_021D83DC
MOD53_021D83DC: ; 0x021D83DC
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, _021D8408 ; =0x021D9600
	add r5, r0, #0
	add r7, r1, #0
	mov r6, #0
_021D83E6:
	cmp r6, r7
	ldr r0, [r5]
	bne _021D83F6
	ldrh r1, [r4, #4]
	add r1, r1, #1
	bl FUN_02020130
	b _021D83FC
_021D83F6:
	ldrh r1, [r4, #4]
	bl FUN_02020130
_021D83FC:
	add r6, r6, #1
	add r4, r4, #6
	add r5, r5, #4
	cmp r6, #8
	blt _021D83E6
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8408: .word MOD53_021D9600
	thumb_func_end MOD53_021D83DC

	thumb_func_start MOD53_021D840C
MOD53_021D840C: ; 0x021D840C
	push {r3, lr}
	cmp r1, #1
	ldr r0, [r0, #0x20]
	bne _021D841C
	mov r1, #0x16
	bl FUN_02020130
	pop {r3, pc}
_021D841C:
	mov r1, #0x15
	bl FUN_02020130
	pop {r3, pc}
	thumb_func_end MOD53_021D840C

	thumb_func_start MOD53_021D8424
MOD53_021D8424: ; 0x021D8424
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD53_021D81B0
	bl FUN_02031190
	cmp r0, #0
	bne _021D8446
	bl MOD53_021D8FF8
	cmp r0, #1
	beq _021D844C
	add r0, r5, #0
	bl MOD53_021D90F8
	b _021D844C
_021D8446:
	add r0, r5, #0
	bl MOD53_021D90F8
_021D844C:
	add r0, r5, #0
	bl MOD53_021D8F50
	ldr r2, _021D846C ; =0x00004382
	mov r0, #0xb2
	lsl r0, r0, #2
	add r1, r5, r2
	add r2, #0x32
	add r0, r5, r0
	add r2, r5, r2
	mov r3, #1
	bl MOD53_021D8E84
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D846C: .word 0x00004382
	thumb_func_end MOD53_021D8424

	thumb_func_start MOD53_021D8470
MOD53_021D8470: ; 0x021D8470
	push {r4, lr}
	add r4, r0, #0
	bl MOD53_021D8F50
	ldr r2, _021D8490 ; =0x00004382
	mov r0, #0xb2
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0x32
	add r0, r4, r0
	add r2, r4, r2
	mov r3, #0
	bl MOD53_021D8E84
	pop {r4, pc}
	nop
_021D8490: .word 0x00004382
	thumb_func_end MOD53_021D8470

	thumb_func_start MOD53_021D8494
MOD53_021D8494: ; 0x021D8494
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	mov r1, #0x32
	lsl r1, r1, #4
	ldr r1, [r5, r1]
	cmp r1, r0
	bne _021D84B4
	add r0, r5, #0
	mov r1, #0xd
	mov r2, #0
	bl MOD53_021D91C8
	b _021D84BE
_021D84B4:
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl MOD53_021D91C8
_021D84BE:
	add r0, r5, #0
	mov r1, #2
	bl MOD53_021D93E0
	ldr r0, _021D84E4 ; =0x000005E4
	bl FUN_020054C8
	mov r1, #0x1e
	add r2, r1, #0
	ldr r0, _021D84E8 ; =0x04000050
	sub r2, #0x24
	bl G2x_SetBlendBrightness_
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D84E4: .word 0x000005E4
_021D84E8: .word 0x04000050
	thumb_func_end MOD53_021D8494

	thumb_func_start MOD53_021D84EC
MOD53_021D84EC: ; 0x021D84EC
	push {r4, lr}
	add r4, r1, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r4, pc}
	thumb_func_end MOD53_021D84EC

	thumb_func_start MOD53_021D84F8
MOD53_021D84F8: ; 0x021D84F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, _021D8524 ; =0x04000050
	mov r2, #0
	strh r2, [r1]
	add r5, r0, #0
	mov r1, #1
	bl MOD53_021D926C
	add r0, r5, #0
	mov r1, #4
	bl MOD53_021D93E0
	add r0, r5, #0
	bl MOD53_021D8470
	ldr r0, _021D8528 ; =0x00009404
	mov r1, #0
	str r1, [r5, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8524: .word 0x04000050
_021D8528: .word 0x00009404
	thumb_func_end MOD53_021D84F8

	thumb_func_start MOD53_021D852C
MOD53_021D852C: ; 0x021D852C
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	bl MOD53_021D923C
	cmp r0, #0
	beq _021D8570
	ldr r0, [r5]
	mov r1, #0x19
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0xb4
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	add r0, sp, #0
	strb r1, [r0, #0x10]
	mov r1, #6
	strb r1, [r0, #0x11]
	add r0, r5, #0
	add r1, sp, #0
	bl MOD53_021D941C
	cmp r0, #0
	bne _021D8568
	bl GF_AssertFail
_021D8568:
	add r0, r5, #0
	mov r1, #6
	bl MOD53_021D93E0
_021D8570:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, pc}
	thumb_func_end MOD53_021D852C

	thumb_func_start MOD53_021D857C
MOD53_021D857C: ; 0x021D857C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, _021D86C8 ; =0x00004380
	mov r0, #0x38
	ldrb r2, [r5, r1]
	bic r2, r0
	strb r2, [r5, r1]
	add r1, #0xb
	ldrb r0, [r5, r1]
	cmp r0, #2
	bne _021D85BA
	bl FUN_02031190
	cmp r0, #0
	beq _021D85BA
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r5, #0
	bl MOD53_021D9460
	cmp r0, #0
	beq _021D85B4
	ldr r0, _021D86CC ; =0x000005F2
	bl FUN_020054C8
_021D85B4:
	add sp, #4
	add r0, r4, #0
	pop {r3, r4, r5, r6, pc}
_021D85BA:
	bl FUN_02031190
	cmp r0, #0
	bne _021D85D6
	ldr r0, _021D86D0 ; =0x000093B4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D85D6
	add r0, r5, #0
	bl MOD53_021D8470
	add sp, #4
	add r0, r4, #0
	pop {r3, r4, r5, r6, pc}
_021D85D6:
	bl MOD53_021D9160
	add r6, r0, #0
	bl FUN_02030F20
	cmp r6, r0
	beq _021D85F0
	add r0, r5, #0
	bl MOD53_021D8470
	add sp, #4
	add r0, r4, #0
	pop {r3, r4, r5, r6, pc}
_021D85F0:
	ldr r0, _021D86D4 ; =0x000093F0
	ldr r0, [r5, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _021D8602
	cmp r0, #2
	beq _021D8672
	b _021D86BA
_021D8602:
	bl FUN_02031190
	cmp r0, #0
	bne _021D861E
	add r0, r5, #0
	mov r1, #0xd
	bl MOD53_021D93E0
	add r0, r5, #0
	mov r1, #4
	mov r2, #1
	bl MOD53_021D91C8
	b _021D8660
_021D861E:
	add r0, sp, #0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r1, #0
	add r0, sp, #0
	strb r1, [r0, #2]
	bl FUN_02031190
	add r1, sp, #0
	strb r0, [r1]
	ldr r0, _021D86D8 ; =0x000093BC
	mov r1, #1
	strb r1, [r5, r0]
	mov r1, #0
	sub r0, r0, #2
	strh r1, [r5, r0]
	add r0, r5, #0
	mov r1, #7
	bl MOD53_021D93E0
	mov r0, #0x7e
	add r1, sp, #0
	mov r2, #4
	bl FUN_02030ADC
	mov r0, #0xb6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #1
	bl FUN_0200D0E0
_021D8660:
	add r0, r5, #0
	bl MOD53_021D9440
	mov r0, #0xb2
	lsl r0, r0, #2
	add r0, r5, r0
	bl CopyWindowToVram
	b _021D86BA
_021D8672:
	add r0, r5, #0
	mov r1, #4
	bl MOD53_021D93E0
	mov r0, #0x92
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl MOD53_021D840C
	mov r0, #0xb6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r5, #0
	bl MOD53_021D9440
	mov r0, #0xb2
	lsl r0, r0, #2
	add r0, r5, r0
	bl CopyWindowToVram
	bl FUN_02031190
	cmp r0, #0
	bne _021D86BA
	bl FUN_02030F20
	add r0, r0, #1
	bl FUN_02032B6C
	ldr r0, _021D86DC ; =0x000093F4
	mov r1, #1
	str r1, [r5, r0]
_021D86BA:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021D86C8: .word 0x00004380
_021D86CC: .word 0x000005F2
_021D86D0: .word 0x000093B4
_021D86D4: .word 0x000093F0
_021D86D8: .word 0x000093BC
_021D86DC: .word 0x000093F4
	thumb_func_end MOD53_021D857C

	thumb_func_start MOD53_021D86E0
MOD53_021D86E0: ; 0x021D86E0
	push {r4, lr}
	ldr r2, _021D86FC ; =0x00004380
	add r4, r1, #0
	ldrb r3, [r0, r2]
	mov r1, #0x38
	bic r3, r1
	strb r3, [r0, r2]
	ldr r1, _021D8700 ; =0x000093BA
	mov r2, #0
	strh r2, [r0, r1]
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
_021D86FC: .word 0x00004380
_021D8700: .word 0x000093BA
	thumb_func_end MOD53_021D86E0

	thumb_func_start MOD53_021D8704
MOD53_021D8704: ; 0x021D8704
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, _021D8790 ; =0x00004380
	mov r0, #0x38
	ldrb r2, [r5, r1]
	bic r2, r0
	strb r2, [r5, r1]
	bl FUN_02030F20
	ldr r1, _021D8794 ; =0x000093B8
	ldrh r1, [r5, r1]
	cmp r1, r0
	bne _021D872C
	bl MOD53_021D9160
	ldr r1, _021D8794 ; =0x000093B8
	ldrh r2, [r5, r1]
	cmp r2, r0
	beq _021D8744
_021D872C:
	ldr r0, _021D8798 ; =0x000093BA
	mov r1, #0
	strh r1, [r5, r0]
	add r0, r5, #0
	mov r1, #9
	bl MOD53_021D93E0
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021D8744:
	add r0, r1, #2
	ldrsh r0, [r5, r0]
	add r2, r0, #1
	add r0, r1, #2
	strh r2, [r5, r0]
	ldrsh r0, [r5, r0]
	cmp r0, #0x1e
	ble _021D8784
	add r0, sp, #0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, #2]
	bl FUN_02031190
	add r1, sp, #0
	strb r0, [r1]
	mov r0, #0x7e
	add r1, sp, #0
	mov r2, #4
	bl FUN_02030ADC
	ldr r0, _021D8798 ; =0x000093BA
	mov r1, #0
	strh r1, [r5, r0]
	add r0, r5, #0
	mov r1, #0xa
	bl MOD53_021D93E0
_021D8784:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8790: .word 0x00004380
_021D8794: .word 0x000093B8
_021D8798: .word 0x000093BA
	thumb_func_end MOD53_021D8704

	thumb_func_start MOD53_021D879C
MOD53_021D879C: ; 0x021D879C
	push {r3, r4, r5, lr}
	ldr r2, _021D87D0 ; =0x00004380
	add r5, r0, #0
	ldrb r3, [r5, r2]
	add r4, r1, #0
	mov r1, #0x38
	bic r3, r1
	strb r3, [r5, r2]
	ldr r1, _021D87D4 ; =0x000093BC
	mov r2, #0
	strb r2, [r5, r1]
	mov r1, #4
	bl MOD53_021D93E0
	mov r0, #0x92
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl MOD53_021D840C
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D87D0: .word 0x00004380
_021D87D4: .word 0x000093BC
	thumb_func_end MOD53_021D879C

	thumb_func_start MOD53_021D87D8
MOD53_021D87D8: ; 0x021D87D8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #6
	mov r2, #1
	bl MOD53_021D91C8
	add r0, r5, #0
	mov r1, #0xb
	bl MOD53_021D93E0
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD53_021D87D8

	thumb_func_start MOD53_021D87F8
MOD53_021D87F8: ; 0x021D87F8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	bl MOD53_021D923C
	cmp r0, #0
	beq _021D8818
	mov r0, #0x31
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	mov r1, #0xc
	bl MOD53_021D93E0
_021D8818:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD53_021D87F8

	thumb_func_start MOD53_021D8824
MOD53_021D8824: ; 0x021D8824
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x31
	lsl r0, r0, #4
	add r4, r1, #0
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	ldr r0, [r5, r0]
	cmp r0, #0x3c
	ble _021D8854
	mov r1, #0x10
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x27
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r4, #3
_021D8854:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD53_021D8824

	thumb_func_start MOD53_021D8860
MOD53_021D8860: ; 0x021D8860
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	bl MOD53_021D923C
	cmp r0, #0
	beq _021D88A4
	ldr r0, [r5]
	mov r1, #0x19
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0xb4
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	add r0, sp, #0
	strb r1, [r0, #0x10]
	mov r1, #6
	strb r1, [r0, #0x11]
	add r0, r5, #0
	add r1, sp, #0
	bl MOD53_021D941C
	cmp r0, #0
	bne _021D889C
	bl GF_AssertFail
_021D889C:
	add r0, r5, #0
	mov r1, #0xe
	bl MOD53_021D93E0
_021D88A4:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, pc}
	thumb_func_end MOD53_021D8860

	thumb_func_start MOD53_021D88B0
MOD53_021D88B0: ; 0x021D88B0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021D8960 ; =0x000093F0
	add r6, r1, #0
	ldr r0, [r5, r0]
	bl FUN_0201466C
	add r4, r0, #0
	bl MOD53_021D9160
	mov r1, #0xc6
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	cmp r1, r0
	bne _021D88D6
	ldr r0, _021D8964 ; =0x000093B4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D88E0
_021D88D6:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r6, #0
	pop {r4, r5, r6, pc}
_021D88E0:
	cmp r4, #1
	beq _021D88EA
	cmp r4, #2
	beq _021D8916
	b _021D8954
_021D88EA:
	add r0, r5, #0
	mov r1, #0xf
	bl MOD53_021D93E0
	mov r1, #0
	mov r0, #0x7f
	add r2, r1, #0
	bl FUN_02030BC4
	mov r0, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0xc]
	mov r1, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r6, #2
	bl MOD53_021D9440
	b _021D8954
_021D8916:
	add r0, r5, #0
	mov r1, #4
	bl MOD53_021D93E0
	mov r0, #0x92
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl MOD53_021D840C
	mov r0, #0xb6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #1
	bl FUN_0200D0E0
	add r0, r5, #0
	bl MOD53_021D9440
	bl FUN_02031190
	cmp r0, #0
	bne _021D8954
	bl FUN_02030F20
	add r0, r0, #1
	bl FUN_02032B6C
	ldr r0, _021D8968 ; =0x000093F4
	mov r1, #1
	str r1, [r5, r0]
_021D8954:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	nop
_021D8960: .word 0x000093F0
_021D8964: .word 0x000093B4
_021D8968: .word 0x000093F4
	thumb_func_end MOD53_021D88B0

	thumb_func_start MOD53_021D896C
MOD53_021D896C: ; 0x021D896C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0xc]
	mov r1, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #3
	mov r2, #1
	bl MOD53_021D91C8
	add r0, r5, #0
	mov r1, #0x10
	bl MOD53_021D93E0
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD53_021D896C

	thumb_func_start MOD53_021D89A0
MOD53_021D89A0: ; 0x021D89A0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	bl MOD53_021D923C
	cmp r0, #0
	beq _021D89BE
	add r0, r5, #0
	mov r1, #0x11
	bl MOD53_021D93E0
	mov r0, #0xc8
	bl FUN_02031588
_021D89BE:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD53_021D89A0

	thumb_func_start MOD53_021D89C8
MOD53_021D89C8: ; 0x021D89C8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0xc8
	add r5, r1, #0
	bl FUN_020315D8
	cmp r0, #0
	bne _021D89E2
	bl FUN_02030F20
	cmp r0, #1
	bne _021D89FA
_021D89E2:
	mov r1, #0x10
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x27
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r5, #3
_021D89FA:
	add r0, r4, #0
	bl MOD53_021D8470
	add r0, r5, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD53_021D89C8

	thumb_func_start MOD53_021D8A08
MOD53_021D8A08: ; 0x021D8A08
	add r0, r1, #0
	bx lr
	thumb_func_end MOD53_021D8A08

	thumb_func_start MOD53_021D8A0C
MOD53_021D8A0C: ; 0x021D8A0C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #5
	mov r2, #1
	bl MOD53_021D91C8
	add r0, r5, #0
	mov r1, #0x14
	bl MOD53_021D93E0
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD53_021D8A0C

	thumb_func_start MOD53_021D8A2C
MOD53_021D8A2C: ; 0x021D8A2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	bl MOD53_021D923C
	cmp r0, #0
	beq _021D8A44
	add r0, r5, #0
	mov r1, #0xc
	bl MOD53_021D93E0
_021D8A44:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD53_021D8A2C

	thumb_func_start MOD53_021D8A50
MOD53_021D8A50: ; 0x021D8A50
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	cmp r0, #0xff
	beq _021D8A6E
	bl MOD53_021D923C
	cmp r0, #0
	bne _021D8A6E
	ldr r0, [r5, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
_021D8A6E:
	add r0, r5, #0
	mov r1, #2
	mov r2, #1
	bl MOD53_021D91C8
	add r0, r5, #0
	mov r1, #0x16
	bl MOD53_021D93E0
	ldr r0, _021D8AA8 ; =0x000005E4
	bl FUN_020054C8
	bl FUN_02031190
	cmp r0, #0
	bne _021D8A96
	add r0, r5, #0
	mov r1, #0
	bl MOD53_021D926C
_021D8A96:
	bl FUN_02030F20
	ldr r1, _021D8AAC ; =0x000093B0
	str r0, [r5, r1]
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8AA8: .word 0x000005E4
_021D8AAC: .word 0x000093B0
	thumb_func_end MOD53_021D8A50

	thumb_func_start MOD53_021D8AB0
MOD53_021D8AB0: ; 0x021D8AB0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D8AF4 ; =0x000093B0
	add r4, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D8ACE
	bl FUN_02030F20
	ldr r1, _021D8AF4 ; =0x000093B0
	ldr r2, [r5, r1]
	cmp r2, r0
	beq _021D8ACE
	mov r0, #0
	str r0, [r5, r1]
_021D8ACE:
	ldr r0, [r5, #0x30]
	bl MOD53_021D923C
	cmp r0, #0
	beq _021D8AE8
	add r0, r5, #0
	mov r1, #0x17
	bl MOD53_021D93E0
	mov r0, #0x31
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D8AE8:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8AF4: .word 0x000093B0
	thumb_func_end MOD53_021D8AB0

	thumb_func_start MOD53_021D8AF8
MOD53_021D8AF8: ; 0x021D8AF8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D8B5C ; =0x000093B0
	add r4, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D8B16
	bl FUN_02030F20
	ldr r1, _021D8B5C ; =0x000093B0
	ldr r2, [r5, r1]
	cmp r2, r0
	beq _021D8B16
	mov r0, #0
	str r0, [r5, r1]
_021D8B16:
	mov r0, #0x31
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	add r1, r1, #1
	str r1, [r5, r0]
	ldr r0, [r5, r0]
	cmp r0, #0x3c
	ble _021D8B50
	ldr r0, _021D8B5C ; =0x000093B0
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _021D8B50
	add r0, r5, #0
	bl MOD53_021D925C
	add r0, r5, #0
	mov r1, #4
	bl MOD53_021D93E0
	bl FUN_02031190
	cmp r0, #0
	bne _021D8B50
	ldr r0, _021D8B60 ; =0x000093F4
	mov r1, #1
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD53_021D926C
_021D8B50:
	add r0, r5, #0
	bl MOD53_021D8470
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D8B5C: .word 0x000093B0
_021D8B60: .word 0x000093F4
	thumb_func_end MOD53_021D8AF8

	thumb_func_start MOD53_021D8B64
MOD53_021D8B64: ; 0x021D8B64
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r0, #0
	add r6, r2, #0
	cmp r5, #0xf
	bgt _021D8B96
	bge _021D8C42
	cmp r5, #9
	bhi _021D8C4A
	add r1, r5, r5
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8B82: ; jump table
	.short _021D8C40 - _021D8B82 - 2 ; case 0
	.short _021D8B9C - _021D8B82 - 2 ; case 1
	.short _021D8C40 - _021D8B82 - 2 ; case 2
	.short _021D8BDA - _021D8B82 - 2 ; case 3
	.short _021D8C40 - _021D8B82 - 2 ; case 4
	.short _021D8C40 - _021D8B82 - 2 ; case 5
	.short _021D8C40 - _021D8B82 - 2 ; case 6
	.short _021D8C40 - _021D8B82 - 2 ; case 7
	.short _021D8C42 - _021D8B82 - 2 ; case 8
	.short _021D8C42 - _021D8B82 - 2 ; case 9
_021D8B96:
	cmp r5, #0x15
	beq _021D8BE0
	pop {r4, r5, r6, pc}
_021D8B9C:
	mov r0, #0xc1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #6
	beq _021D8BAA
	cmp r0, #0xe
	bne _021D8BB0
_021D8BAA:
	add r0, r4, #0
	bl MOD53_021D9440
_021D8BB0:
	mov r0, #0x92
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl MOD53_021D840C
	add r0, r6, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl BufferPlayersName
	mov r0, #0x32
	lsl r0, r0, #4
	str r6, [r4, r0]
	ldr r0, _021D8C4C ; =0x000093B4
	mov r1, #0
	str r1, [r4, r0]
	b _021D8C42
_021D8BDA:
	bl MOD53_021D925C
	b _021D8C42
_021D8BE0:
	ldr r0, _021D8C50 ; =0x000093BC
	ldrb r0, [r4, r0]
	cmp r0, #1
	beq _021D8C4A
	add r0, r6, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl BufferPlayersName
	bl FUN_02031190
	cmp r6, r0
	beq _021D8C4A
	bl FUN_02031190
	cmp r0, #0
	bne _021D8C14
	ldr r1, _021D8C4C ; =0x000093B4
	ldr r0, _021D8C54 ; =0x0000FFFF
	ldr r2, [r4, r1]
	eor r0, r6
	and r0, r2
	str r0, [r4, r1]
_021D8C14:
	mov r0, #0xc1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #6
	beq _021D8C22
	cmp r0, #0xe
	bne _021D8C32
_021D8C22:
	add r0, r4, #0
	bl MOD53_021D9440
	mov r0, #0xb2
	lsl r0, r0, #2
	add r0, r4, r0
	bl CopyWindowToVram
_021D8C32:
	mov r0, #0x92
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl MOD53_021D840C
	b _021D8C42
_021D8C40:
	pop {r4, r5, r6, pc}
_021D8C42:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD53_021D93E0
_021D8C4A:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8C4C: .word 0x000093B4
_021D8C50: .word 0x000093BC
_021D8C54: .word 0x0000FFFF
	thumb_func_end MOD53_021D8B64

	thumb_func_start MOD53_021D8C58
MOD53_021D8C58: ; 0x021D8C58
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r4, [sp, #0x38]
	mov ip, r1
	add r6, r2, #0
	add r7, r3, #0
	str r0, [sp, #0x18]
	ldr r3, [sp, #0x3c]
	ldr r2, [sp, #0x40]
	ldr r1, [sp, #0x44]
	cmp r4, #0
	bge _021D8C84
	neg r0, r4
	cmp r0, r2
	ble _021D8C78
	add r0, r2, #0
_021D8C78:
	ldr r5, [sp, #0x30]
	mov r4, #0
	sub r5, r5, r0
	add r6, r6, r0
	str r5, [sp, #0x30]
	sub r2, r2, r0
_021D8C84:
	cmp r3, #0
	bge _021D8C9C
	neg r0, r3
	cmp r0, r1
	ble _021D8C90
	add r0, r1, #0
_021D8C90:
	ldr r5, [sp, #0x34]
	mov r3, #0
	sub r5, r5, r0
	add r7, r7, r0
	str r5, [sp, #0x34]
	sub r1, r1, r0
_021D8C9C:
	ldr r0, [sp, #0x30]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x34]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	lsl r0, r3, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	lsl r2, r6, #0x10
	lsl r3, r7, #0x10
	ldr r0, [sp, #0x18]
	mov r1, ip
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl BlitBitmapRectToWindow
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD53_021D8C58

	thumb_func_start MOD53_021D8CD8
MOD53_021D8CD8: ; 0x021D8CD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x50]
	str r1, [sp, #0x1c]
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x54]
	str r2, [sp, #0x20]
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x50]
	str r3, [sp, #0x24]
	ldr r4, [r0]
	ldr r0, [sp, #0x54]
	ldr r5, [r0]
	add r0, r2, #0
	str r0, [sp, #0x38]
	add r0, r3, #0
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x58]
	cmp r0, #0
	bne _021D8D18
	ldr r0, [sp, #0x5c]
	cmp r0, #0
	bne _021D8D18
	ldr r0, [sp, #0x50]
	add r1, r2, #0
	str r1, [r0]
	ldr r0, [sp, #0x54]
	add r1, r3, #0
	str r1, [r0]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
_021D8D18:
	ldr r0, [sp, #0x20]
	sub r0, r0, r4
	str r0, [sp, #0x34]
	bpl _021D8D24
	neg r0, r0
	str r0, [sp, #0x34]
_021D8D24:
	ldr r0, [sp, #0x24]
	sub r7, r0, r5
	bpl _021D8D2C
	neg r7, r7
_021D8D2C:
	ldr r0, [sp, #0x34]
	cmp r0, r7
	ble _021D8DBA
	ldr r0, [sp, #0x20]
	cmp r4, r0
	ble _021D8D52
	ldr r0, [sp, #0x24]
	cmp r5, r0
	ble _021D8D44
	mov r0, #1
	str r0, [sp, #0x2c]
	b _021D8D4A
_021D8D44:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x2c]
_021D8D4A:
	str r4, [sp, #0x38]
	ldr r4, [sp, #0x20]
	ldr r5, [sp, #0x24]
	b _021D8D64
_021D8D52:
	ldr r0, [sp, #0x24]
	cmp r5, r0
	bge _021D8D5E
	mov r0, #1
	str r0, [sp, #0x2c]
	b _021D8D64
_021D8D5E:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x2c]
_021D8D64:
	mov r0, #6
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD53_021D8C58
	ldr r0, [sp, #0x34]
	add r4, r4, #1
	asr r6, r0, #1
	ldr r0, [sp, #0x38]
	cmp r4, r0
	bgt _021D8E3E
_021D8D8A:
	sub r6, r6, r7
	bpl _021D8D96
	ldr r0, [sp, #0x34]
	add r6, r6, r0
	ldr r0, [sp, #0x2c]
	add r5, r5, r0
_021D8D96:
	mov r0, #6
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD53_021D8C58
	ldr r0, [sp, #0x38]
	add r4, r4, #1
	cmp r4, r0
	ble _021D8D8A
	b _021D8E3E
_021D8DBA:
	ldr r0, [sp, #0x24]
	cmp r5, r0
	ble _021D8DDA
	ldr r0, [sp, #0x20]
	cmp r4, r0
	ble _021D8DCC
	mov r0, #1
	str r0, [sp, #0x28]
	b _021D8DD2
_021D8DCC:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x28]
_021D8DD2:
	str r5, [sp, #0x30]
	ldr r5, [sp, #0x24]
	ldr r4, [sp, #0x20]
	b _021D8DEC
_021D8DDA:
	ldr r0, [sp, #0x20]
	cmp r4, r0
	bge _021D8DE6
	mov r0, #1
	str r0, [sp, #0x28]
	b _021D8DEC
_021D8DE6:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x28]
_021D8DEC:
	mov r0, #6
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD53_021D8C58
	ldr r0, [sp, #0x30]
	add r5, r5, #1
	asr r6, r7, #1
	cmp r5, r0
	bgt _021D8E3E
_021D8E10:
	ldr r0, [sp, #0x34]
	sub r6, r6, r0
	bpl _021D8E1C
	ldr r0, [sp, #0x28]
	add r6, r6, r7
	add r4, r4, r0
_021D8E1C:
	mov r0, #6
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD53_021D8C58
	ldr r0, [sp, #0x30]
	add r5, r5, #1
	cmp r5, r0
	ble _021D8E10
_021D8E3E:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x50]
	str r1, [r0]
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x54]
	str r1, [r0]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD53_021D8CD8

	thumb_func_start MOD53_021D8E50
MOD53_021D8E50: ; 0x021D8E50
	mov r2, #0
_021D8E52:
	ldrb r3, [r0, #8]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1d
	strh r3, [r1, #2]
	ldrb r3, [r0, #8]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1d
	beq _021D8E76
	add r3, r0, r3
	sub r3, r3, #1
	ldrb r3, [r3]
	strb r3, [r1]
	ldrb r3, [r0, #8]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1d
	add r3, r0, r3
	ldrb r3, [r3, #3]
	strb r3, [r1, #1]
_021D8E76:
	add r2, r2, #1
	add r0, #0xa
	add r1, r1, #4
	cmp r2, #5
	blt _021D8E52
	bx lr
	.align 2, 0
	thumb_func_end MOD53_021D8E50

	thumb_func_start MOD53_021D8E84
MOD53_021D8E84: ; 0x021D8E84
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	str r0, [sp, #0x10]
	mov r0, #0
	str r1, [sp, #0x14]
	str r2, [sp, #0x18]
	str r3, [sp, #0x1c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	add r5, r1, #0
	add r7, r2, #0
_021D8E9A:
	ldrb r0, [r5, #8]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1d
	beq _021D8F0A
	ldrh r0, [r7, #2]
	cmp r0, #0
	beq _021D8EB4
	ldrb r0, [r7]
	sub r0, #9
	str r0, [sp, #0x2c]
	ldrb r0, [r7, #1]
	sub r0, #0x11
	str r0, [sp, #0x28]
_021D8EB4:
	ldrb r0, [r5, #8]
	mov r4, #0
	lsl r0, r0, #0x1a
	lsr r1, r0, #0x1d
	cmp r1, #0
	ble _021D8F0A
	mov r0, #1
	str r0, [sp, #0x20]
	cmp r1, #0
	ble _021D8F0A
_021D8EC8:
	add r0, sp, #0x2c
	str r0, [sp]
	add r0, sp, #0x28
	str r0, [sp, #4]
	str r4, [sp, #8]
	ldrh r0, [r7, #2]
	mov r6, #0xc0
	add r3, r5, r4
	str r0, [sp, #0xc]
	ldrb r1, [r5, #8]
	ldrb r3, [r3, #4]
	ldr r0, [sp, #0x10]
	lsl r2, r1, #0x18
	lsr r2, r2, #0x1e
	mul r6, r2
	ldr r2, _021D8F4C ; =0x021D9648
	lsl r1, r1, #0x1d
	add r2, r2, r6
	lsr r6, r1, #0x1d
	mov r1, #0x18
	mul r1, r6
	add r1, r2, r1
	ldrb r2, [r5, r4]
	sub r3, #0x11
	sub r2, #9
	bl MOD53_021D8CD8
	ldrb r0, [r5, #8]
	add r4, r4, #1
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1d
	cmp r4, r0
	blt _021D8EC8
_021D8F0A:
	ldr r0, [sp, #0x24]
	add r5, #0xa
	add r0, r0, #1
	add r7, r7, #4
	str r0, [sp, #0x24]
	cmp r0, #5
	blt _021D8E9A
	ldr r0, [sp, #0x20]
	cmp r0, #0
	beq _021D8F2A
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _021D8F2A
	ldr r0, [sp, #0x10]
	bl CopyWindowToVram
_021D8F2A:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	bl MOD53_021D8E50
	mov r3, #0
	mov r1, #0x38
_021D8F36:
	ldr r0, [sp, #0x14]
	add r3, r3, #1
	ldrb r2, [r0, #8]
	bic r2, r1
	strb r2, [r0, #8]
	add r0, #0xa
	str r0, [sp, #0x14]
	cmp r3, #5
	blt _021D8F36
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8F4C: .word MOD53_021D9648
	thumb_func_end MOD53_021D8E84

	thumb_func_start MOD53_021D8F50
MOD53_021D8F50: ; 0x021D8F50
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _021D8FB4 ; =0x00004382
	mov r7, #0x76
	mov r6, #0
	add r4, r5, r0
	lsl r7, r7, #2
_021D8F5E:
	bl FUN_02031190
	cmp r6, r0
	beq _021D8FA6
	ldrb r0, [r4, #8]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1d
	beq _021D8F9A
	add r0, r6, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _021D8F9A
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	ldrb r0, [r4, #8]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1d
	add r2, r4, r0
	sub r1, r2, #1
	ldrb r1, [r1]
	ldrb r2, [r2, #3]
	ldr r0, [r5, r7]
	bl MOD53_021D8140
	b _021D8FA6
_021D8F9A:
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
_021D8FA6:
	add r6, r6, #1
	add r4, #0xa
	add r5, r5, #4
	cmp r6, #5
	blt _021D8F5E
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8FB4: .word 0x00004382
	thumb_func_end MOD53_021D8F50

	thumb_func_start MOD53_021D8FB8
MOD53_021D8FB8: ; 0x021D8FB8
	push {r3, lr}
	ldrh r1, [r0]
	add r1, #0x14
	strh r1, [r0]
	ldrh r2, [r0]
	mov r1, #0x5a
	lsl r1, r1, #2
	cmp r2, r1
	bls _021D8FCE
	mov r1, #0
	strh r1, [r0]
_021D8FCE:
	ldrh r0, [r0]
	bl Sin_Wrap
	mov r1, #0xa
	mul r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	add r0, #0xf
	lsl r1, r0, #5
	mov r0, #0x1d
	orr r1, r0
	add r0, sp, #0
	strh r1, [r0]
	add r0, sp, #0
	mov r1, #0x18
	mov r2, #2
	bl GX_LoadOBJPltt
	pop {r3, pc}
	thumb_func_end MOD53_021D8FB8

	thumb_func_start MOD53_021D8FF8
MOD53_021D8FF8: ; 0x021D8FF8
	push {r3, r4, r5, lr}
	mov r5, #0
	add r4, r5, #0
_021D8FFE:
	add r0, r4, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _021D900A
	add r5, r5, #1
_021D900A:
	add r4, r4, #1
	cmp r4, #5
	blt _021D8FFE
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD53_021D8FF8

	thumb_func_start MOD53_021D9014
MOD53_021D9014: ; 0x021D9014
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r7, r3, #0
	add r5, r0, #0
	str r2, [sp, #0x10]
	bl FUN_02031190
	str r0, [sp, #0x14]
	add r0, r7, #0
	bl MOD53_021D9184
	cmp r0, #0
	beq _021D90EE
	mov r0, #0
	str r0, [sp, #0x18]
	add r6, r7, #0
	add r4, r7, #0
_021D9036:
	mov r0, #0xcd
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	bne _021D904E
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	b _021D905A
_021D904E:
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
_021D905A:
	ldr r0, [sp, #0x18]
	add r6, #8
	add r0, r0, #1
	add r4, r4, #4
	str r0, [sp, #0x18]
	cmp r0, #5
	blt _021D9036
	mov r6, #0
	add r4, r5, #0
_021D906C:
	mov r0, #0x50
	mov r1, #0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	add r6, r6, #1
	add r4, #0x10
	cmp r6, #5
	blt _021D906C
	mov r6, #0
	add r4, r7, #0
_021D908C:
	mov r0, #0xcd
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	cmp r0, #0
	beq _021D90DC
	ldr r1, [r4, #0x14]
	bl PlayerName_FlatToString
	ldr r0, [sp, #0x14]
	cmp r0, r6
	bne _021D90C0
	mov r0, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D90F4 ; =0x0003040F
	mov r1, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r5, #0
	mov r3, #0
	bl AddTextPrinterParameterized2
	b _021D90DC
_021D90C0:
	mov r0, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x10]
	mov r1, #1
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x14]
	add r0, r5, #0
	mov r3, #0
	bl AddTextPrinterParameterized2
_021D90DC:
	add r0, r5, #0
	bl CopyWindowToVram
	add r6, r6, #1
	add r7, #8
	add r4, r4, #4
	add r5, #0x10
	cmp r6, #5
	blt _021D908C
_021D90EE:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D90F4: .word 0x0003040F
	thumb_func_end MOD53_021D9014

	thumb_func_start MOD53_021D90F8
MOD53_021D90F8: ; 0x021D90F8
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D9138
	bl FUN_02031370
	cmp r0, #0
	beq _021D914C
	ldr r1, _021D9150 ; =0x000093F4
	ldr r0, _021D9154 ; =0x00004381
	ldr r2, [r4, r1]
	sub r1, #0x37
	strb r2, [r4, r0]
	sub r0, #9
	add r2, r4, r1
	add r3, r4, r0
	mov r1, #0xa
_021D911E:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021D911E
	ldr r1, _021D9158 ; =0x000093BD
	mov r0, #0x78
	add r1, r4, r1
	mov r2, #0x32
	bl FUN_02030BC4
	pop {r4, pc}
_021D9138:
	bl FUN_02031388
	cmp r0, #0
	beq _021D914C
	ldr r1, _021D915C ; =0x00004378
	mov r0, #0x77
	add r1, r4, r1
	mov r2, #0xa
	bl FUN_02030ADC
_021D914C:
	pop {r4, pc}
	nop
_021D9150: .word 0x000093F4
_021D9154: .word 0x00004381
_021D9158: .word 0x000093BD
_021D915C: .word 0x00004378
	thumb_func_end MOD53_021D90F8

	thumb_func_start MOD53_021D9160
MOD53_021D9160: ; 0x021D9160
	push {r3, r4, r5, lr}
	mov r5, #0
	add r4, r5, #0
_021D9166:
	add r0, r4, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _021D9172
	add r5, r5, #1
_021D9172:
	add r4, r4, #1
	cmp r4, #5
	blt _021D9166
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD53_021D9160

	thumb_func_start MOD53_021D917C
MOD53_021D917C: ; 0x021D917C
	ldr r3, _021D9180 ; =MOD53_021D9160
	bx r3
	.align 2, 0
_021D9180: .word MOD53_021D9160
	thumb_func_end MOD53_021D917C

	thumb_func_start MOD53_021D9184
MOD53_021D9184: ; 0x021D9184
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r7, #0
	add r6, r7, #0
	add r4, r5, #0
_021D918E:
	mov r0, #0xcd
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	add r0, r6, #0
	bl FUN_0202DFA4
	mov r1, #0xcd
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r6, r6, #1
	add r4, #8
	cmp r6, #5
	blt _021D918E
	mov r6, #0
	mov r2, #1
	add r0, r1, #4
_021D91B2:
	ldr r4, [r5, r0]
	ldr r3, [r5, r1]
	cmp r4, r3
	beq _021D91BC
	add r7, r2, #0
_021D91BC:
	add r6, r6, #1
	add r5, #8
	cmp r6, #5
	blt _021D91B2
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD53_021D9184

	thumb_func_start MOD53_021D91C8
MOD53_021D91C8: ; 0x021D91C8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #0x50
	mov r1, #0x27
	add r4, r2, #0
	bl String_ctor
	add r6, r0, #0
	ldr r0, [r5, #0x10]
	add r1, r7, #0
	add r2, r6, #0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x2c]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	mov r0, #0xb6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r0, #0xb6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	cmp r4, #0
	bne _021D9218
	mov r4, #0
_021D9218:
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0xb6
	lsl r0, r0, #2
	ldr r2, [r5, #0x2c]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	str r0, [r5, #0x30]
	cmp r4, #0
	bne _021D9238
	mov r0, #0xff
	str r0, [r5, #0x30]
_021D9238:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD53_021D91C8

	thumb_func_start MOD53_021D923C
MOD53_021D923C: ; 0x021D923C
	push {r3, lr}
	cmp r0, #0xff
	bne _021D9246
	mov r0, #1
	pop {r3, pc}
_021D9246:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D9256
	mov r0, #1
	pop {r3, pc}
_021D9256:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD53_021D923C

	thumb_func_start MOD53_021D925C
MOD53_021D925C: ; 0x021D925C
	mov r1, #0xb6
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r3, _021D9268 ; =FUN_0200D0E0
	mov r1, #0
	bx r3
	.align 2, 0
_021D9268: .word FUN_0200D0E0
	thumb_func_end MOD53_021D925C

	thumb_func_start MOD53_021D926C
MOD53_021D926C: ; 0x021D926C
	push {r4, lr}
	add r4, r1, #0
	bl FUN_02031190
	cmp r0, #0
	bne _021D9288
	bl FUN_02030F20
	add r0, r4, r0
	cmp r0, #5
	ble _021D9284
	mov r0, #5
_021D9284:
	bl FUN_02032B6C
_021D9288:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD53_021D926C

	thumb_func_start MOD53_021D928C
MOD53_021D928C: ; 0x021D928C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD53_021D9160
	add r5, r0, #0
	cmp r5, #5
	bhi _021D932A
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D92A6: ; jump table
	.short _021D932A - _021D92A6 - 2 ; case 0
	.short _021D92B2 - _021D92A6 - 2 ; case 1
	.short _021D92F8 - _021D92A6 - 2 ; case 2
	.short _021D92F8 - _021D92A6 - 2 ; case 3
	.short _021D92F8 - _021D92A6 - 2 ; case 4
	.short _021D9324 - _021D92A6 - 2 ; case 5
_021D92B2:
	mov r0, #0xc1
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0xe
	bgt _021D932A
	bl FUN_0202CB8C
	cmp r0, #1
	beq _021D92CC
	mov r0, #0x25
	mov r1, #1
	lsl r0, r0, #0xa
	str r1, [r4, r0]
_021D92CC:
	mov r0, #0xc2
	mov r1, #0x13
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	bl FUN_02032B6C
	ldr r0, _021D93CC ; =0x000093F8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D92F4
	add r0, r4, #0
	bl MOD53_021D9440
	mov r0, #0x9a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x15
	bl FUN_02020130
_021D92F4:
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D92F8:
	mov r0, #1
	bl FUN_02052B74
	mov r0, #0xc5
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r5, r0
	bge _021D932A
	ldr r0, _021D93D0 ; =0x000093F4
	ldr r0, [r4, r0]
	cmp r0, #2
	bne _021D931A
	add r0, r4, #0
	mov r1, #0
	bl MOD53_021D926C
	b _021D932A
_021D931A:
	add r0, r4, #0
	mov r1, #1
	bl MOD53_021D926C
	b _021D932A
_021D9324:
	mov r0, #8
	bl FUN_02052B74
_021D932A:
	mov r0, #0xc5
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r5, r0
	bge _021D9374
	bl FUN_02030F20
	mov r1, #0xc6
	lsl r1, r1, #2
	str r0, [r4, r1]
	bl FUN_0202CB8C
	mov r1, #0xc7
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, _021D93D4 ; =0x00009404
	ldr r2, [r4, r0]
	cmp r2, #0
	beq _021D9374
	add r0, r0, #4
	ldr r1, [r4, r1]
	ldr r0, [r4, r0]
	tst r0, r1
	bne _021D9374
	add r0, r4, #0
	mov r1, #1
	bl MOD53_021D926C
	ldr r1, _021D93D0 ; =0x000093F4
	mov r0, #1
	str r0, [r4, r1]
	add r0, r1, #0
	mov r2, #0
	add r0, #0x10
	str r2, [r4, r0]
	add r1, #0x14
	str r2, [r4, r1]
_021D9374:
	bl MOD53_021D9160
	mov r1, #0xc5
	lsl r1, r1, #2
	str r0, [r4, r1]
	bl FUN_02030F20
	mov r1, #0xc6
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, r0
	bge _021D93C8
	ldr r0, _021D93D0 ; =0x000093F4
	mov r1, #2
	str r1, [r4, r0]
	mov r1, #1
	add r0, #0x10
	str r1, [r4, r0]
	bl FUN_0202CB8C
	mov r1, #0xc7
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	eor r0, r1
	ldr r1, _021D93D8 ; =0x00009408
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	mov r0, #0
	sub r1, r1, #2
	cmp r1, #0xe
	bhi _021D93C0
	mov r2, #1
	add r3, r2, #0
	lsl r3, r1
	ldr r1, _021D93DC ; =0x00004045
	tst r1, r3
	beq _021D93C0
	add r0, r2, #0
_021D93C0:
	cmp r0, #0
	bne _021D93C8
	bl GF_AssertFail
_021D93C8:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D93CC: .word 0x000093F8
_021D93D0: .word 0x000093F4
_021D93D4: .word 0x00009404
_021D93D8: .word 0x00009408
_021D93DC: .word 0x00004045
	thumb_func_end MOD53_021D928C

	thumb_func_start MOD53_021D93E0
MOD53_021D93E0: ; 0x021D93E0
	mov r2, #0xc2
	lsl r2, r2, #2
	str r1, [r0, r2]
	bx lr
	thumb_func_end MOD53_021D93E0

	thumb_func_start MOD53_021D93E8
MOD53_021D93E8: ; 0x021D93E8
	push {r3, r4}
	mov r3, #0xc2
	lsl r3, r3, #2
	sub r4, r3, #4
	ldr r2, [r0, r3]
	ldr r4, [r0, r4]
	cmp r4, r2
	beq _021D9412
	cmp r1, #2
	beq _021D9404
	sub r1, r3, #4
	str r2, [r0, r1]
	pop {r3, r4}
	bx lr
_021D9404:
	ldr r1, _021D9418 ; =MOD53_021D98A0 + 4
	lsl r4, r2, #3
	ldr r1, [r1, r4]
	cmp r1, #0
	beq _021D9412
	sub r1, r3, #4
	str r2, [r0, r1]
_021D9412:
	pop {r3, r4}
	bx lr
	nop
_021D9418: .word MOD53_021D98A0 + 4
	thumb_func_end MOD53_021D93E8

	thumb_func_start MOD53_021D941C
MOD53_021D941C: ; 0x021D941C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D943C ; =0x000093F8
	ldr r2, [r4, r0]
	cmp r2, #0
	bne _021D9438
	sub r0, #8
	ldr r0, [r4, r0]
	bl FUN_020145C8
	ldr r1, _021D943C ; =0x000093F8
	mov r0, #1
	str r0, [r4, r1]
	pop {r4, pc}
_021D9438:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D943C: .word 0x000093F8
	thumb_func_end MOD53_021D941C

	thumb_func_start MOD53_021D9440
MOD53_021D9440: ; 0x021D9440
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D945C ; =0x000093F8
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D945A
	sub r0, #8
	ldr r0, [r4, r0]
	bl FUN_020146C4
	ldr r0, _021D945C ; =0x000093F8
	mov r1, #0
	str r1, [r4, r0]
_021D945A:
	pop {r4, pc}
	.align 2, 0
_021D945C: .word 0x000093F8
	thumb_func_end MOD53_021D9440

	thumb_func_start MOD53_021D9460
MOD53_021D9460: ; 0x021D9460
	push {r3, lr}
	ldr r0, _021D9478 ; =0x021D94E8
	bl FUN_02020988
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _021D9474
	mov r0, #1
	pop {r3, pc}
_021D9474:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_021D9478: .word MOD53_021D94E8
	thumb_func_end MOD53_021D9460

	thumb_func_start MOD53_021D947C
MOD53_021D947C: ; 0x021D947C
	push {r4, r5}
	ldrh r4, [r1]
	cmp r4, #0
	beq _021D949C
	ldrh r4, [r1, #2]
	strb r4, [r0]
	ldrh r4, [r1, #4]
	strb r4, [r0, #4]
	ldrh r4, [r1]
	sub r4, r4, #1
	lsl r4, r4, #3
	add r5, r1, r4
	ldrh r4, [r5, #2]
	strb r4, [r0, #1]
	ldrh r4, [r5, #4]
	strb r4, [r0, #5]
_021D949C:
	ldrh r5, [r1]
	cmp r5, #2
	blo _021D94AC
	ldrb r4, [r0, #8]
	mov r1, #0x38
	bic r4, r1
	mov r1, #0x10
	b _021D94BA
_021D94AC:
	ldrb r1, [r0, #8]
	mov r4, #0x38
	bic r1, r4
	lsl r4, r5, #0x18
	lsr r4, r4, #0x18
	lsl r4, r4, #0x1d
	lsr r4, r4, #0x1a
_021D94BA:
	orr r1, r4
	strb r1, [r0, #8]
	ldrb r1, [r0, #8]
	mov r4, #7
	lsl r2, r2, #0x18
	bic r1, r4
	lsr r4, r2, #0x18
	mov r2, #7
	and r2, r4
	orr r1, r2
	strb r1, [r0, #8]
	ldrb r2, [r0, #8]
	mov r1, #0xc0
	bic r2, r1
	lsl r1, r3, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x18
	orr r1, r2
	strb r1, [r0, #8]
	pop {r4, r5}
	bx lr
	.align 2, 0
	thumb_func_end MOD53_021D947C

	.rodata
	.global MOD53_021D94E8
MOD53_021D94E8: ; 0x021D94E8
	.byte 0x30, 0x70, 0xC8, 0xF8, 0xFF, 0x00, 0x00, 0x00

	.global MOD53_021D94F0
MOD53_021D94F0: ; 0x021D94F0
	.byte 0x10, 0x88, 0x08, 0xF8, 0xFF, 0x00, 0x00, 0x00

	.global MOD53_021D94F8
MOD53_021D94F8: ; 0x021D94F8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD53_021D9508
MOD53_021D9508: ; 0x021D9508
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00

	.global MOD53_021D9518
MOD53_021D9518: ; 0x021D9518
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD53_021D9534
MOD53_021D9534: ; 0x021D9534
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD53_021D9550
MOD53_021D9550: ; 0x021D9550
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD53_021D956C
MOD53_021D956C: ; 0x021D956C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD53_021D9588
MOD53_021D9588: ; 0x021D9588
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD53_021D95A4
MOD53_021D95A4: ; 0x021D95A4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD53_021D95CC
MOD53_021D95CC: ; 0x021D95CC
	.byte 0x96, 0xBD, 0x00, 0x17, 0x96, 0xBD, 0x18, 0x2F, 0x96, 0xBD, 0x30, 0x47, 0x96, 0xBD, 0x48, 0x5F
	.byte 0x96, 0xBD, 0x60, 0x77, 0x96, 0xBD, 0x78, 0x8F, 0x96, 0xBD, 0x90, 0xA7, 0x96, 0xBD, 0xA8, 0xBF
	.byte 0x96, 0xBD, 0xC0, 0xFF, 0x01, 0x0D, 0x0E, 0x1A, 0x01, 0x0D, 0x1E, 0x2A, 0x01, 0x0D, 0x2E, 0x3A
	.byte 0xFF, 0x00, 0x00, 0x00

	.global MOD53_021D9600
MOD53_021D9600: ; 0x021D9600
	.byte 0x0D, 0x00, 0xAB, 0x00, 0x05, 0x00, 0x25, 0x00, 0xAB, 0x00, 0x07, 0x00, 0x3D, 0x00, 0xAB, 0x00
	.byte 0x09, 0x00, 0x55, 0x00, 0xAB, 0x00, 0x0B, 0x00, 0x6D, 0x00, 0xAB, 0x00, 0x0D, 0x00, 0x85, 0x00
	.byte 0xAB, 0x00, 0x0F, 0x00, 0x9D, 0x00, 0xAB, 0x00, 0x11, 0x00, 0xB5, 0x00, 0xAB, 0x00, 0x13, 0x00
	.byte 0xE1, 0x00, 0xAB, 0x00, 0x15, 0x00, 0x14, 0x00, 0x09, 0x00, 0x1D, 0x00, 0x24, 0x00, 0x09, 0x00
	.byte 0x20, 0x00, 0x34, 0x00, 0x09, 0x00, 0x21, 0x00

	.global MOD53_021D9648
MOD53_021D9648: ; 0x021D9648
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x22, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x44, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x66, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x88, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x10, 0x11, 0x01, 0x00, 0x10, 0x11, 0x01, 0x00
	.byte 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00
	.byte 0x20, 0x22, 0x02, 0x00, 0x20, 0x22, 0x02, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x30, 0x33, 0x03, 0x00, 0x30, 0x33, 0x03, 0x00
	.byte 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00
	.byte 0x40, 0x44, 0x04, 0x00, 0x40, 0x44, 0x04, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x50, 0x55, 0x05, 0x00, 0x50, 0x55, 0x05, 0x00
	.byte 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00
	.byte 0x60, 0x66, 0x06, 0x00, 0x60, 0x66, 0x06, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x70, 0x77, 0x07, 0x00, 0x70, 0x77, 0x07, 0x00
	.byte 0x00, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00
	.byte 0x80, 0x88, 0x08, 0x00, 0x80, 0x88, 0x08, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x11, 0x01, 0x00, 0x11, 0x11, 0x11, 0x00, 0x11, 0x11, 0x11, 0x00, 0x11, 0x11, 0x11, 0x00
	.byte 0x11, 0x11, 0x11, 0x00, 0x10, 0x11, 0x01, 0x00, 0x20, 0x22, 0x02, 0x00, 0x22, 0x22, 0x22, 0x00
	.byte 0x22, 0x22, 0x22, 0x00, 0x22, 0x22, 0x22, 0x00, 0x22, 0x22, 0x22, 0x00, 0x20, 0x22, 0x02, 0x00
	.byte 0x30, 0x33, 0x03, 0x00, 0x33, 0x33, 0x33, 0x00, 0x33, 0x33, 0x33, 0x00, 0x33, 0x33, 0x33, 0x00
	.byte 0x33, 0x33, 0x33, 0x00, 0x30, 0x33, 0x03, 0x00, 0x40, 0x44, 0x04, 0x00, 0x44, 0x44, 0x44, 0x00
	.byte 0x44, 0x44, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x44, 0x44, 0x44, 0x00, 0x40, 0x44, 0x04, 0x00
	.byte 0x50, 0x55, 0x05, 0x00, 0x55, 0x55, 0x55, 0x00, 0x55, 0x55, 0x55, 0x00, 0x55, 0x55, 0x55, 0x00
	.byte 0x55, 0x55, 0x55, 0x00, 0x50, 0x55, 0x05, 0x00, 0x60, 0x66, 0x06, 0x00, 0x66, 0x66, 0x66, 0x00
	.byte 0x66, 0x66, 0x66, 0x00, 0x66, 0x66, 0x66, 0x00, 0x66, 0x66, 0x66, 0x00, 0x60, 0x66, 0x06, 0x00
	.byte 0x70, 0x77, 0x07, 0x00, 0x77, 0x77, 0x77, 0x00, 0x77, 0x77, 0x77, 0x00, 0x77, 0x77, 0x77, 0x00
	.byte 0x77, 0x77, 0x77, 0x00, 0x70, 0x77, 0x07, 0x00, 0x80, 0x88, 0x08, 0x00, 0x88, 0x88, 0x88, 0x00
	.byte 0x88, 0x88, 0x88, 0x00, 0x88, 0x88, 0x88, 0x00, 0x88, 0x88, 0x88, 0x00, 0x80, 0x88, 0x08, 0x00

	.data
	.global MOD53_021D98A0
MOD53_021D98A0: ; 0x021D98A0
	.word 0x00000000, 0x01
	.word MOD53_021D8494, 0x00
	.word MOD53_021D84EC, 0x00
	.word MOD53_021D84F8, 0x00
	.word MOD53_021D8424, 0x00
	.word MOD53_021D852C, 0x01
	.word MOD53_021D857C, 0x01
	.word MOD53_021D86E0, 0x01
	.word MOD53_021D8704, 0x01
	.word MOD53_021D879C, 0x01
	.word MOD53_021D87D8, 0x01
	.word MOD53_021D87F8, 0x01
	.word MOD53_021D8824, 0x01
	.word MOD53_021D8860, 0x01
	.word MOD53_021D88B0, 0x01
	.word MOD53_021D896C, 0x01
	.word MOD53_021D89A0, 0x01
	.word MOD53_021D89C8, 0x01
	.word MOD53_021D8A08, 0x01
	.word MOD53_021D8A0C, 0x01
	.word MOD53_021D8A2C, 0x01
	.word MOD53_021D8A50, 0x01
	.word MOD53_021D8AB0, 0x01
	.word MOD53_021D8AF8, 0x01

	.bss
