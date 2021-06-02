	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD74_021D74E0
MOD74_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl OverlayManager_GetField18
	mov r2, #1
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x4a
	lsl r2, r2, #0x10
	bl FUN_0201681C
	mov r1, #0xad
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x4a
	bl OverlayManager_CreateAndGetData
	mov r2, #0xad
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	ldrh r0, [r5, #4]
	strh r0, [r4, #8]
	ldrh r0, [r5, #6]
	strb r0, [r4, #0xa]
	ldr r0, [r5]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0x18]
	ldr r0, [r5]
	bl FUN_02029FC8
	str r0, [r4, #0x1c]
	ldr r0, [r5]
	bl FUN_0202A8D8
	str r0, [r4, #0x20]
	ldr r0, [r5]
	bl FUN_0202A8E4
	str r0, [r4, #0x24]
	mov r0, #0x4a
	str r0, [r4]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD74_021D74E0

	thumb_func_start MOD74_021D7540
MOD74_021D7540: ; 0x021D7540
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r5, #0
	bl OverlayManager_FreeData
	ldr r0, [r4]
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD74_021D7540

	thumb_func_start MOD74_021D755C
MOD74_021D755C: ; 0x021D755C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #4
	bhi _021D760C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D757A: ; jump table
	.short _021D7584 - _021D757A - 2 ; case 0
	.short _021D75AA - _021D757A - 2 ; case 1
	.short _021D75BA - _021D757A - 2 ; case 2
	.short _021D75EE - _021D757A - 2 ; case 3
	.short _021D75FE - _021D757A - 2 ; case 4
_021D7584:
	bl MOD74_021D7624
	cmp r0, #0
	beq _021D760C
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r5]
	add r2, r1, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D760C
_021D75AA:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D760C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D760C
_021D75BA:
	ldrh r1, [r5, #8]
	cmp r1, #0
	bne _021D75C6
	bl MOD74_021D77AC
	b _021D75CA
_021D75C6:
	bl MOD74_021D790C
_021D75CA:
	cmp r0, #0
	beq _021D760C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	mov r1, #0
	str r0, [sp, #4]
	ldr r0, [r5]
	add r2, r1, #0
	str r0, [sp, #8]
	mov r0, #3
	add r3, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D760C
_021D75EE:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D760C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D760C
_021D75FE:
	bl MOD74_021D76E8
	cmp r0, #0
	beq _021D760C
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D760C:
	ldr r0, [r4]
	cmp r0, #1
	blt _021D761C
	cmp r0, #3
	bgt _021D761C
	add r0, r5, #0
	bl MOD74_021D82D4
_021D761C:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD74_021D755C

	thumb_func_start MOD74_021D7624
MOD74_021D7624: ; 0x021D7624
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #4
	bhi _021D76D2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D763A: ; jump table
	.short _021D7644 - _021D763A - 2 ; case 0
	.short _021D7684 - _021D763A - 2 ; case 1
	.short _021D7690 - _021D763A - 2 ; case 2
	.short _021D76B6 - _021D763A - 2 ; case 3
	.short _021D76C2 - _021D763A - 2 ; case 4
_021D7644:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D76DC ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D76E0 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	bl MOD74_021D7764
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	add r0, r4, #0
	bl MOD74_021D7934
	b _021D76D2
_021D7684:
	bl MOD74_021D79F8
	add r0, r4, #0
	bl MOD74_021D7B20
	b _021D76D2
_021D7690:
	bl MOD74_021D7A88
	ldrh r0, [r4, #8]
	cmp r0, #0
	bne _021D76A8
	add r0, r4, #0
	bl MOD74_021D7D1C
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _021D76D2
_021D76A8:
	add r0, r4, #0
	bl MOD74_021D7E9C
	add r0, r4, #0
	bl MOD74_021D8008
	b _021D76D2
_021D76B6:
	bl MOD74_021D8200
	add r0, r4, #0
	bl MOD74_021D82F0
	b _021D76D2
_021D76C2:
	ldr r0, _021D76E4 ; =MOD74_021D7784
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_021D76D2:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D76DC: .word 0xFFFFE0FF
_021D76E0: .word 0x04001000
_021D76E4: .word MOD74_021D7784
	thumb_func_end MOD74_021D7624

	thumb_func_start MOD74_021D76E8
MOD74_021D76E8: ; 0x021D76E8
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021D76F8
	cmp r1, #1
	beq _021D7722
	b _021D7752
_021D76F8:
	ldrh r1, [r4, #8]
	cmp r1, #0
	beq _021D770E
	bl MOD74_021D836C
	add r0, r4, #0
	bl MOD74_021D82B0
	add r0, r4, #0
	bl MOD74_021D7F28
_021D770E:
	add r0, r4, #0
	bl MOD74_021D7AF0
	add r0, r4, #0
	bl MOD74_021D7BB4
	add r0, r4, #0
	bl MOD74_021D79C8
	b _021D7752
_021D7722:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D775C ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7760 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
_021D7752:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D775C: .word 0xFFFFE0FF
_021D7760: .word 0x04001000
	thumb_func_end MOD74_021D76E8

	thumb_func_start MOD74_021D7764
MOD74_021D7764: ; 0x021D7764
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7780 ; =0x021D8518
	add r3, sp, #0
	mov r2, #5
_021D776E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D776E
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7780: .word MOD74_021D8518
	thumb_func_end MOD74_021D7764

	thumb_func_start MOD74_021D7784
MOD74_021D7784: ; 0x021D7784
	push {r4, lr}
	add r4, r0, #0
	bl MOD74_021D82E8
	bl NNS_GfdDoVramTransfer
	ldr r0, [r4, #0x10]
	bl FUN_0201AB60
	ldr r3, _021D77A4 ; =0x027E0000
	ldr r1, _021D77A8 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_021D77A4: .word 0x027E0000
_021D77A8: .word 0x00003FF8
	thumb_func_end MOD74_021D7784

	thumb_func_start MOD74_021D77AC
MOD74_021D77AC: ; 0x021D77AC
	ldr r0, _021D77C0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D77BA
	mov r0, #1
	bx lr
_021D77BA:
	mov r0, #0
	bx lr
	nop
_021D77C0: .word gMain
	thumb_func_end MOD74_021D77AC

	thumb_func_start MOD74_021D77C4
MOD74_021D77C4: ; 0x021D77C4
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r1, _021D78B8 ; =gMain
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #2
	mov r3, #0
	tst r1, r2
	beq _021D77DC
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D77DC:
	mov r1, #1
	add r5, r2, #0
	tst r5, r1
	beq _021D7800
	ldrb r2, [r4, #0xb]
	cmp r2, #0xa
	blo _021D77F0
	add sp, #8
	add r0, r1, #0
	pop {r3, r4, r5, pc}
_021D77F0:
	ldrb r1, [r4, #0xd]
	add r1, r1, #1
	strb r1, [r4, #0xd]
	bl MOD74_021D80D0
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D7800:
	mov r0, #0x40
	tst r0, r2
	beq _021D7828
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	beq _021D787A
	sub r0, r0, #1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _021D7820
	ldrb r0, [r4, #0xe]
	add r3, r1, #0
	sub r0, r0, #1
	strb r0, [r4, #0xe]
	b _021D787A
_021D7820:
	sub r0, r0, #1
	strb r0, [r4, #0xf]
	add r3, r1, #0
	b _021D787A
_021D7828:
	mov r0, #0x80
	tst r0, r2
	beq _021D7850
	ldrb r0, [r4, #0xb]
	cmp r0, #0xa
	bhs _021D787A
	add r0, r0, #1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	bls _021D7848
	ldrb r0, [r4, #0xe]
	add r3, r1, #0
	add r0, r0, #1
	strb r0, [r4, #0xe]
	b _021D787A
_021D7848:
	add r0, r0, #1
	strb r0, [r4, #0xf]
	add r3, r1, #0
	b _021D787A
_021D7850:
	mov r0, #0x20
	tst r0, r2
	beq _021D7866
	ldrb r0, [r4, #0xc]
	mov r1, #3
	add r0, r0, #2
	bl _s32_div_f
	strb r1, [r4, #0xc]
	mov r3, #1
	b _021D787A
_021D7866:
	mov r0, #0x10
	tst r0, r2
	beq _021D787A
	ldrb r0, [r4, #0xc]
	mov r1, #3
	add r0, r0, #1
	bl _s32_div_f
	strb r1, [r4, #0xc]
	mov r3, #1
_021D787A:
	ldrb r0, [r4, #0xb]
	cmp r0, #0xa
	bne _021D7884
	mov r0, #2
	strb r0, [r4, #0xc]
_021D7884:
	cmp r3, #0
	bne _021D788E
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D788E:
	ldrb r1, [r4, #0xb]
	ldrb r2, [r4, #0xc]
	ldrb r3, [r4, #0xf]
	add r0, r4, #0
	bl MOD74_021D83D4
	ldrb r0, [r4, #0xb]
	add r1, r4, #0
	add r1, #0x7c
	str r0, [sp]
	ldrb r0, [r4, #0xc]
	str r0, [sp, #4]
	add r0, r4, #0
	ldrb r3, [r4, #0xe]
	ldr r2, [r4, #0x34]
	add r0, #0xbc
	bl MOD74_021D7F44
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D78B8: .word gMain
	thumb_func_end MOD74_021D77C4

	thumb_func_start MOD74_021D78BC
MOD74_021D78BC: ; 0x021D78BC
	push {r4, lr}
	ldr r1, _021D78E8 ; =gMain
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #1
	tst r1, r2
	beq _021D78D6
	bl MOD74_021D818C
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	b _021D78E4
_021D78D6:
	mov r1, #2
	tst r1, r2
	beq _021D78E4
	bl MOD74_021D81E0
	mov r0, #0
	strb r0, [r4, #0xd]
_021D78E4:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D78E8: .word gMain
	thumb_func_end MOD74_021D78BC

	thumb_func_start MOD74_021D78EC
MOD74_021D78EC: ; 0x021D78EC
	push {r4, lr}
	ldr r1, _021D7908 ; =gMain
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #3
	tst r1, r2
	beq _021D7902
	bl MOD74_021D81E0
	mov r0, #0
	strb r0, [r4, #0xd]
_021D7902:
	mov r0, #0
	pop {r4, pc}
	nop
_021D7908: .word gMain
	thumb_func_end MOD74_021D78EC

	thumb_func_start MOD74_021D790C
MOD74_021D790C: ; 0x021D790C
	push {r3, lr}
	ldrb r1, [r0, #0xd]
	cmp r1, #0
	beq _021D791E
	cmp r1, #1
	beq _021D7924
	cmp r1, #2
	beq _021D792A
	b _021D7930
_021D791E:
	bl MOD74_021D77C4
	pop {r3, pc}
_021D7924:
	bl MOD74_021D78BC
	pop {r3, pc}
_021D792A:
	bl MOD74_021D78EC
	pop {r3, pc}
_021D7930:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD74_021D790C

	thumb_func_start MOD74_021D7934
MOD74_021D7934: ; 0x021D7934
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	add r5, r0, #0
	ldr r0, [r5]
	bl FUN_02016B94
	add r3, sp, #0
	ldr r4, _021D79C0 ; =0x021D84A0
	str r0, [r5, #0x10]
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r4, _021D79C4 ; =0x021D8570
	add r3, sp, #0x10
	mov r2, #0xa
_021D795C:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D795C
	ldr r0, [r4]
	mov r4, #0
	str r0, [r3]
	ldrh r0, [r5, #8]
	add r7, r4, #0
	add r0, r0, #2
	cmp r0, #0
	ble _021D799C
	add r6, sp, #0x10
_021D7976:
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x10]
	lsr r1, r1, #0x18
	add r2, r6, #0
	mov r3, #0
	bl FUN_02016C18
	lsl r1, r4, #0x18
	ldr r0, [r5, #0x10]
	lsr r1, r1, #0x18
	bl FUN_02018744
	ldrh r0, [r5, #8]
	add r7, r7, #1
	add r4, r4, #1
	add r0, r0, #2
	add r6, #0x1c
	cmp r7, r0
	blt _021D7976
_021D799C:
	mov r0, #0
	ldr r3, [r5]
	mov r1, #0x20
	add r2, r0, #0
	bl FUN_02017F18
	ldrh r0, [r5, #8]
	cmp r0, #0
	beq _021D79BA
	ldr r3, [r5]
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
_021D79BA:
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}
	nop
_021D79C0: .word MOD74_021D84A0
_021D79C4: .word MOD74_021D8570
	thumb_func_end MOD74_021D7934

	thumb_func_start MOD74_021D79C8
MOD74_021D79C8: ; 0x021D79C8
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldrh r0, [r6, #8]
	mov r5, #0
	add r4, r5, #0
	add r0, r0, #2
	cmp r0, #0
	ble _021D79EE
_021D79D8:
	lsl r1, r5, #0x18
	ldr r0, [r6, #0x10]
	lsr r1, r1, #0x18
	add r5, r5, #1
	bl FUN_020178A0
	ldrh r0, [r6, #8]
	add r4, r4, #1
	add r0, r0, #2
	cmp r4, r0
	blt _021D79D8
_021D79EE:
	ldr r0, [r6, #0x10]
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD74_021D79C8

	thumb_func_start MOD74_021D79F8
MOD74_021D79F8: ; 0x021D79F8
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r1, [r5]
	mov r0, #0x7b
	bl NARC_ctor
	add r4, r0, #0
	mov r0, #5
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x10]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x7b
	bl FUN_02079B60
	mov r0, #4
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0x40
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x10]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x7b
	bl FUN_02079B60
	ldrh r0, [r5, #8]
	cmp r0, #1
	bne _021D7A4E
	mov r0, #7
	b _021D7A5A
_021D7A4E:
	ldrb r0, [r5, #0xa]
	cmp r0, #2
	bne _021D7A58
	mov r0, #8
	b _021D7A5A
_021D7A58:
	mov r0, #6
_021D7A5A:
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x10]
	ldr r1, [r5]
	add r2, r4, #0
	mov r3, #0x7b
	bl FUN_02079B60
	add r0, r4, #0
	bl NARC_dtor
	ldr r0, [r5, #0x10]
	mov r1, #1
	bl FUN_0201AC68
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD74_021D79F8

	thumb_func_start MOD74_021D7A88
MOD74_021D7A88: ; 0x021D7A88
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldrh r0, [r6, #8]
	cmp r0, #0
	bne _021D7AB8
	add r5, r6, #0
	ldr r4, _021D7AE8 ; =0x021D8540
	mov r7, #0
	add r5, #0x6c
_021D7A9A:
	ldr r0, [r6, #0x10]
	add r1, r5, #0
	add r2, r4, #0
	bl FUN_02019150
	add r0, r5, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r7, r7, #1
	add r4, #8
	add r5, #0x10
	cmp r7, #5
	blt _021D7A9A
	b _021D7ADC
_021D7AB8:
	add r5, r6, #0
	ldr r4, _021D7AEC ; =0x021D84C4
	mov r7, #0
	add r5, #0x6c
_021D7AC0:
	ldr r0, [r6, #0x10]
	add r1, r5, #0
	add r2, r4, #0
	bl FUN_02019150
	add r0, r5, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r7, r7, #1
	add r4, #8
	add r5, #0x10
	cmp r7, #3
	blt _021D7AC0
_021D7ADC:
	ldr r2, [r6]
	mov r0, #0
	mov r1, #0x40
	bl FUN_02002ED0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7AE8: .word MOD74_021D8540
_021D7AEC: .word MOD74_021D84C4
	thumb_func_end MOD74_021D7A88

	thumb_func_start MOD74_021D7AF0
MOD74_021D7AF0: ; 0x021D7AF0
	push {r4, r5, r6, lr}
	ldrh r1, [r0, #8]
	cmp r1, #0
	bne _021D7AFC
	mov r6, #5
	b _021D7AFE
_021D7AFC:
	mov r6, #3
_021D7AFE:
	mov r4, #0
	cmp r6, #0
	ble _021D7B1C
	add r5, r0, #0
	add r5, #0x6c
_021D7B08:
	add r0, r5, #0
	bl FUN_02019570
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, r6
	blt _021D7B08
_021D7B1C:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD74_021D7AF0

	thumb_func_start MOD74_021D7B20
MOD74_021D7B20: ; 0x021D7B20
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r3, [r5]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0x11
	bl NewMsgDataFromNarc
	str r0, [r5, #0x28]
	ldr r2, [r5]
	mov r0, #2
	mov r1, #0x4c
	bl ScrStrBufs_new_custom
	str r0, [r5, #0x2c]
	ldr r1, [r5]
	mov r0, #0x4c
	bl String_ctor
	str r0, [r5, #0x30]
	mov r6, #0
	add r4, r5, #0
_021D7B4C:
	add r1, r6, #0
	ldr r0, [r5, #0x28]
	add r1, #9
	bl NewString_ReadMsgData
	str r0, [r4, #0x4c]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #6
	blt _021D7B4C
	ldr r0, [r5, #0x28]
	mov r1, #0xf
	bl NewString_ReadMsgData
	str r0, [r5, #0x38]
	ldr r0, [r5, #0x28]
	mov r1, #0x11
	bl NewString_ReadMsgData
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x28]
	mov r1, #0x12
	bl NewString_ReadMsgData
	str r0, [r5, #0x34]
	ldr r0, [r5, #0x28]
	mov r1, #0x13
	bl NewString_ReadMsgData
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x28]
	mov r1, #0x14
	bl NewString_ReadMsgData
	str r0, [r5, #0x44]
	ldr r0, [r5, #0x28]
	mov r1, #0x15
	bl NewString_ReadMsgData
	str r0, [r5, #0x48]
	ldr r0, [r5, #0x28]
	mov r1, #0x16
	bl NewString_ReadMsgData
	str r0, [r5, #0x64]
	ldr r0, [r5, #0x28]
	mov r1, #0x17
	bl NewString_ReadMsgData
	str r0, [r5, #0x68]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD74_021D7B20

	thumb_func_start MOD74_021D7BB4
MOD74_021D7BB4: ; 0x021D7BB4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x68]
	bl String_dtor
	ldr r0, [r6, #0x64]
	bl String_dtor
	ldr r0, [r6, #0x48]
	bl String_dtor
	ldr r0, [r6, #0x44]
	bl String_dtor
	ldr r0, [r6, #0x40]
	bl String_dtor
	ldr r0, [r6, #0x34]
	bl String_dtor
	ldr r0, [r6, #0x3c]
	bl String_dtor
	ldr r0, [r6, #0x38]
	bl String_dtor
	mov r4, #0
	add r5, r6, #0
_021D7BEC:
	ldr r0, [r5, #0x4c]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _021D7BEC
	ldr r0, [r6, #0x30]
	bl String_dtor
	ldr r0, [r6, #0x2c]
	bl ScrStrBufs_delete
	ldr r0, [r6, #0x28]
	bl DestroyMsgData
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD74_021D7BB4

	thumb_func_start MOD74_021D7C10
MOD74_021D7C10: ; 0x021D7C10
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r7, r3, #0
	add r4, r1, #0
	ldr r0, [r5, #0x1c]
	add r1, r7, #0
	add r6, r2, #0
	bl FUN_0202A150
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x1c]
	add r1, r7, #1
	bl FUN_0202A150
	lsl r0, r0, #0x10
	add r6, #8
	lsr r7, r0, #0x10
	lsl r1, r6, #0x10
	ldr r0, [r5, #0x20]
	lsr r1, r1, #0x10
	mov r2, #0
	bl FUN_0202A578
	lsl r2, r0, #0x10
	add r0, sp, #0x18
	ldrb r6, [r0, #0x10]
	lsr r2, r2, #0xe
	mov r0, #0xff
	str r6, [sp]
	str r0, [sp, #4]
	mov r0, #0xc1
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	add r2, r5, r2
	ldr r2, [r2, #0x4c]
	add r0, r4, #0
	mov r3, #4
	bl AddTextPrinterParameterized2
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r5, #0x2c]
	mov r1, #0
	add r2, r7, #0
	mov r3, #4
	bl BufferIntegerAsString
	ldr r0, [r5, #0x2c]
	ldr r1, [r5, #0x30]
	ldr r2, [r5, #0x5c]
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [r5, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xa4
	sub r3, r1, r0
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7D18 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x30]
	add r0, r4, #0
	bl AddTextPrinterParameterized2
	add r0, sp, #0x18
	ldrb r0, [r0, #0x10]
	add r0, #0x18
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0xc1
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x54]
	add r0, r4, #0
	mov r3, #4
	bl AddTextPrinterParameterized2
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r5, #0x2c]
	ldr r2, [sp, #0x10]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	ldr r0, [r5, #0x2c]
	ldr r1, [r5, #0x30]
	ldr r2, [r5, #0x5c]
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [r5, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xa4
	sub r3, r1, r0
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7D18 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5, #0x30]
	add r0, r4, #0
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl CopyWindowToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D7D18: .word 0x00010200
	thumb_func_end MOD74_021D7C10

	thumb_func_start MOD74_021D7D1C
MOD74_021D7D1C: ; 0x021D7D1C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldrb r1, [r4, #0xa]
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x30]
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r3, r1, r0
	mov r0, #8
	str r0, [sp]
	mov r1, #0
	lsr r5, r3, #0x1f
	add r5, r3, r5
	ldr r0, _021D7E94 ; =0x000F0200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x6c
	asr r3, r5, #1
	bl AddTextPrinterParameterized2
	ldrb r1, [r4, #0xa]
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x30]
	add r1, r1, #3
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #0xc1
	str r1, [sp, #4]
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x7c
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	ldrb r1, [r4, #0xa]
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x30]
	add r1, r1, #6
	bl ReadMsgDataIntoString
	mov r0, #3
	str r0, [sp]
	mov r1, #0
	mov r0, #0xc1
	str r1, [sp, #4]
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x8c
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	ldrb r0, [r4, #0xa]
	cmp r0, #0
	beq _021D7DB8
	cmp r0, #1
	beq _021D7DDE
	cmp r0, #2
	beq _021D7E04
	add sp, #0x10
	pop {r3, r4, r5, pc}
_021D7DB8:
	add r1, r4, #0
	mov r2, #0
	add r0, r4, #0
	add r1, #0x9c
	mov r3, #0x35
	str r2, [sp]
	bl MOD74_021D7C10
	mov r0, #3
	str r0, [sp]
	add r0, r4, #0
	add r4, #0xac
	add r1, r4, #0
	mov r2, #1
	mov r3, #0x37
	bl MOD74_021D7C10
	add sp, #0x10
	pop {r3, r4, r5, pc}
_021D7DDE:
	mov r0, #0
	add r1, r4, #0
	str r0, [sp]
	add r0, r4, #0
	add r1, #0x9c
	mov r2, #2
	mov r3, #0x39
	bl MOD74_021D7C10
	add r0, r4, #0
	add r4, #0xac
	mov r2, #3
	add r1, r4, #0
	mov r3, #0x3b
	str r2, [sp]
	bl MOD74_021D7C10
	add sp, #0x10
	pop {r3, r4, r5, pc}
_021D7E04:
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x30]
	mov r1, #0xc
	bl ReadMsgDataIntoString
	mov r0, #0xa
	str r0, [sp]
	mov r1, #0
	mov r0, #0xc1
	str r1, [sp, #4]
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x9c
	mov r3, #4
	bl AddTextPrinterParameterized2
	ldr r0, [r4, #0x20]
	mov r1, #0
	bl FUN_0202A444
	mov r1, #0
	add r2, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x2c]
	mov r3, #2
	bl BufferIntegerAsString
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x30]
	ldr r2, [r4, #0x60]
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [r4, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x40
	sub r1, r1, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r3, r0, #1
	mov r0, #0xa
	str r0, [sp]
	mov r1, #0
	ldr r0, _021D7E98 ; =0x00050600
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r3, #0x40
	add r0, #0x9c
	bl AddTextPrinterParameterized2
	mov r0, #3
	str r0, [sp]
	add r0, r4, #0
	add r4, #0xac
	add r1, r4, #0
	mov r2, #4
	mov r3, #0x3d
	bl MOD74_021D7C10
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D7E94: .word 0x000F0200
_021D7E98: .word 0x00050600
	thumb_func_end MOD74_021D7D1C

	thumb_func_start MOD74_021D7E9C
MOD74_021D7E9C: ; 0x021D7E9C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	ldr r0, [r7, #0x24]
	ldr r1, [r7]
	bl FUN_0202A878
	str r0, [sp]
	ldr r5, [sp]
	mov r0, #0
	add r4, r7, #0
	str r0, [sp, #4]
	add r4, #0xbc
	add r6, r5, #0
_021D7EB8:
	add r0, r5, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r4, #0
	add r1, #8
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	strb r0, [r4, #4]
	ldrb r0, [r5, #0x12]
	mov r2, #8
	strb r0, [r4, #5]
	ldrb r0, [r5, #0x13]
	strb r0, [r4, #6]
	add r0, r5, #0
	add r0, #0x20
	ldrb r0, [r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	strb r0, [r4, #7]
	add r0, r5, #0
	add r0, #0x18
	bl MI_CpuCopy8
	ldr r1, [r7]
	mov r0, #8
	bl String_ctor
	str r0, [r4]
	ldrb r0, [r4, #7]
	cmp r0, #0
	ldr r0, [r4]
	beq _021D7F06
	ldrb r1, [r4, #4]
	lsl r1, r1, #2
	add r1, r7, r1
	ldr r1, [r1, #0x64]
	bl StringCopy
	b _021D7F0C
_021D7F06:
	add r1, r6, #0
	bl CopyU16ArrayToString
_021D7F0C:
	ldr r0, [sp, #4]
	add r4, #0x10
	add r0, r0, #1
	add r5, #0x22
	add r6, #0x22
	str r0, [sp, #4]
	cmp r0, #0x1e
	blt _021D7EB8
	ldr r0, [sp]
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD74_021D7E9C

	thumb_func_start MOD74_021D7F28
MOD74_021D7F28: ; 0x021D7F28
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D7F2E:
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl String_dtor
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0x1e
	blt _021D7F2E
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD74_021D7F28

	thumb_func_start MOD74_021D7F44
MOD74_021D7F44: ; 0x021D7F44
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	add r0, r1, #0
	mov r1, #0
	add r5, r2, #0
	add r4, r3, #0
	bl FillWindowPixelBuffer
	cmp r4, #8
	blo _021D7F8C
	mov r0, #2
	str r0, [sp, #0x18]
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x28
	sub r0, r1, r0
	lsr r3, r0, #1
	mov r0, #0x34
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7FFC ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x14]
	add r2, r5, #0
	add r3, #0xa0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	b _021D7F90
_021D7F8C:
	mov r0, #3
	str r0, [sp, #0x18]
_021D7F90:
	lsl r0, r4, #1
	add r0, r4, r0
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	cmp r0, #0
	ble _021D7FF0
	ldr r7, [sp, #0x20]
	mov r6, #4
_021D7FA4:
	mov r4, #0
	add r5, r4, #0
_021D7FA8:
	ldr r0, [sp, #0x1c]
	add r1, r4, r7
	add r0, r0, r1
	lsl r1, r0, #4
	ldr r0, [sp, #0x10]
	add r2, r0, r1
	ldrb r0, [r2, #4]
	cmp r0, #0
	beq _021D7FBE
	ldr r1, _021D8000 ; =0x000B0C00
	b _021D7FC0
_021D7FBE:
	ldr r1, _021D8004 ; =0x00090A00
_021D7FC0:
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	ldr r2, [r2]
	mov r1, #0
	add r3, r5, #0
	bl AddTextPrinterParameterized2
	add r4, r4, #1
	add r5, #0x48
	cmp r4, #3
	blt _021D7FA8
	ldr r0, [sp, #0x20]
	add r7, r7, #3
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	add r6, #0x18
	str r1, [sp, #0x20]
	cmp r1, r0
	blt _021D7FA4
_021D7FF0:
	ldr r0, [sp, #0x14]
	bl CopyWindowToVram
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021D7FFC: .word 0x00010200
_021D8000: .word 0x000B0C00
_021D8004: .word 0x00090A00
	thumb_func_end MOD74_021D7F44

	thumb_func_start MOD74_021D8008
MOD74_021D8008: ; 0x021D8008
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	add r1, sp, #0x10
	bl FUN_0202A864
	ldr r0, [r4, #0x30]
	bl StringSetEmpty
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r2, sp, #0x10
	ldrb r2, [r2]
	ldr r0, [r4, #0x2c]
	mov r3, #2
	bl BufferIntegerAsString
	mov r0, #2
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r2, sp, #0x10
	ldrb r2, [r2, #1]
	ldr r0, [r4, #0x2c]
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x30]
	ldr r2, [r4, #0x38]
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [r4, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r3, r1, r0
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D80CC ; =0x000F0200
	lsr r5, r3, #0x1f
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	add r0, r4, #0
	add r5, r3, r5
	ldr r2, [r4, #0x30]
	add r0, #0x6c
	asr r3, r5, #1
	bl AddTextPrinterParameterized2
	ldrb r1, [r4, #0xa]
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x30]
	add r1, #0x10
	bl ReadMsgDataIntoString
	mov r0, #0
	ldr r1, [r4, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xc0
	sub r3, r1, r0
	mov r0, #0x14
	str r0, [sp]
	mov r1, #0
	lsr r5, r3, #0x1f
	add r5, r3, r5
	ldr r0, _021D80CC ; =0x000F0200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x6c
	asr r3, r5, #1
	bl AddTextPrinterParameterized2
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r0, r4, #0
	add r1, r4, #0
	ldr r2, [r4, #0x34]
	add r0, #0xbc
	add r1, #0x7c
	bl MOD74_021D7F44
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_021D80CC: .word 0x000F0200
	thumb_func_end MOD74_021D8008

	thumb_func_start MOD74_021D80D0
MOD74_021D80D0: ; 0x021D80D0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldrb r2, [r4, #0xb]
	ldrb r3, [r4, #0xc]
	add r0, #0xbc
	lsl r1, r2, #1
	add r1, r2, r1
	add r1, r3, r1
	lsl r1, r1, #4
	add r5, r0, r1
	ldrb r2, [r5, #5]
	cmp r2, #0
	bne _021D8108
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	ldr r0, _021D8188 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x48]
	add r0, #0x8c
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	b _021D8172
_021D8108:
	ldrb r0, [r5, #6]
	cmp r0, #0
	ldr r0, [r4, #0x2c]
	bne _021D813C
	mov r1, #0
	bl BufferCountryName
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x30]
	ldr r2, [r4, #0x44]
	bl StringExpandPlaceholders
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	ldr r0, _021D8188 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x8c
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	b _021D8172
_021D813C:
	mov r1, #0
	bl BufferCountryName
	ldrb r2, [r5, #5]
	ldrb r3, [r5, #6]
	ldr r0, [r4, #0x2c]
	mov r1, #1
	bl BufferCityName
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x30]
	ldr r2, [r4, #0x40]
	bl StringExpandPlaceholders
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	ldr r0, _021D8188 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r4, #0
	ldr r2, [r4, #0x30]
	add r0, #0x8c
	add r3, r1, #0
	bl AddTextPrinterParameterized2
_021D8172:
	add r0, r4, #0
	add r0, #0x8c
	bl CopyWindowToVram
	add r0, r4, #0
	mov r1, #0
	bl MOD74_021D8388
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D8188: .word 0x00010200
	thumb_func_end MOD74_021D80D0

	thumb_func_start MOD74_021D818C
MOD74_021D818C: ; 0x021D818C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldrb r2, [r4, #0xb]
	ldrb r3, [r4, #0xc]
	add r0, #0xbc
	lsl r1, r2, #1
	add r1, r2, r1
	add r1, r3, r1
	lsl r1, r1, #4
	add r0, r0, r1
	ldr r1, [r4]
	add r0, #8
	bl MailMsg_GetExpandedString
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x8c
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #4
	str r0, [sp]
	mov r1, #0
	ldr r0, _021D81DC ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r4, #0x8c
	add r0, r4, #0
	add r2, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D81DC: .word 0x00010200
	thumb_func_end MOD74_021D818C

	thumb_func_start MOD74_021D81E0
MOD74_021D81E0: ; 0x021D81E0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x8c
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r0, #0x8c
	bl FUN_02019570
	add r0, r4, #0
	mov r1, #1
	bl MOD74_021D8388
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD74_021D81E0

	thumb_func_start MOD74_021D8200
MOD74_021D8200: ; 0x021D8200
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x50
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #0x20
	bl FUN_0201C24C
	ldr r0, [r4]
	bl FUN_0200BB14
	mov r1, #0xa7
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl FUN_0200BB34
	mov r7, #0x2a
	lsl r7, r7, #4
	add r2, sp, #0x30
	ldr r3, _021D82A4 ; =0x021D84F8
	str r0, [r4, r7]
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	ldr r5, _021D82A8 ; =0x021D84B0
	stmia r2!, {r0, r1}
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r6, #0
	str r0, [r3]
	sub r0, r7, #4
	ldr r0, [r4, r0]
	mov r3, #0x20
	bl FUN_0200BB6C
	sub r1, r7, #4
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #4
	bl FUN_0200BBF0
	ldr r0, [r4]
	bl FUN_0200A064
	ldr r0, [r4]
	bl FUN_0200A06C
	ldr r5, _021D82AC ; =0x021D84DC
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	sub r1, r7, #4
	str r0, [r3]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0200BD20
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D82A4: .word MOD74_021D84F8
_021D82A8: .word MOD74_021D84B0
_021D82AC: .word MOD74_021D84DC
	thumb_func_end MOD74_021D8200

	thumb_func_start MOD74_021D82B0
MOD74_021D82B0: ; 0x021D82B0
	push {r4, lr}
	mov r1, #0xa7
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl FUN_0200BCE0
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200BD04
	bl FUN_0201C29C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD74_021D82B0

	thumb_func_start MOD74_021D82D4
MOD74_021D82D4: ; 0x021D82D4
	push {r3, lr}
	mov r1, #0x2a
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _021D82E4
	bl FUN_0200BC1C
_021D82E4:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD74_021D82D4

	thumb_func_start MOD74_021D82E8
MOD74_021D82E8: ; 0x021D82E8
	ldr r3, _021D82EC ; =FUN_0200BC30
	bx r3
	.align 2, 0
_021D82EC: .word FUN_0200BC30
	thumb_func_end MOD74_021D82E8

	thumb_func_start MOD74_021D82F0
MOD74_021D82F0: ; 0x021D82F0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r6, _021D8368 ; =0x021D85C4
	mov r7, #0
	add r4, r5, #0
_021D82FA:
	mov r0, #0xa7
	mov r1, #0x2a
	lsl r0, r0, #2
	lsl r1, r1, #4
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl FUN_0200BE38
	mov r1, #0xa9
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r7, r7, #1
	add r6, #0x28
	add r4, r4, #4
	cmp r7, #4
	blt _021D82FA
	add r0, r1, #0
	add r0, #8
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xaa
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xa9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0xab
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0xaa
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #3
	bl FUN_02020238
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8368: .word MOD74_021D85C4
	thumb_func_end MOD74_021D82F0

	thumb_func_start MOD74_021D836C
MOD74_021D836C: ; 0x021D836C
	push {r4, r5, r6, lr}
	mov r6, #0xa9
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #2
_021D8376:
	ldr r0, [r5, r6]
	bl FUN_0200BC14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D8376
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD74_021D836C

	thumb_func_start MOD74_021D8388
MOD74_021D8388: ; 0x021D8388
	push {r3, r4, r5, lr}
	add r5, r0, #0
	cmp r1, #0
	bne _021D83A0
	mov r0, #0xa9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020248
	mov r4, #0
	b _021D83AE
_021D83A0:
	mov r0, #0xa9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020248
	mov r4, #1
_021D83AE:
	mov r0, #0xa9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_020200BC
	mov r0, #0xab
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_020200BC
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_020200BC
	pop {r3, r4, r5, pc}
	thumb_func_end MOD74_021D8388

	thumb_func_start MOD74_021D83D4
MOD74_021D83D4: ; 0x021D83D4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrb r0, [r5, #0xe]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #8
	bne _021D8428
	mov r0, #0xaa
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	cmp r4, #0xa
	bne _021D840E
	mov r0, #0xaa
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020208
	mov r0, #0xa9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	b _021D8440
_021D840E:
	mov r0, #0xaa
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020208
	mov r0, #0xa9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	b _021D8440
_021D8428:
	mov r0, #0xa9
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xaa
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
_021D8440:
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _021D844C
	cmp r0, #8
	beq _021D845A
	b _021D8468
_021D844C:
	mov r0, #0xab
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	b _021D8480
_021D845A:
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	b _021D8480
_021D8468:
	mov r0, #0xab
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
_021D8480:
	mov r1, #0x48
	mov r2, #0x18
	mov r0, #0xa9
	mul r1, r6
	mul r2, r7
	lsl r0, r0, #2
	add r1, #0x36
	add r2, #0x44
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD74_021D83D4

	.rodata
	.global MOD74_021D84A0
MOD74_021D84A0: ; 0x021D84A0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD74_021D84B0
MOD74_021D84B0: ; 0x021D84B0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD74_021D84C4
MOD74_021D84C4: ; 0x021D84C4
	.byte 0x00, 0x04, 0x01, 0x18, 0x05, 0x02, 0xC0, 0x00, 0x02, 0x03, 0x07, 0x1A, 0x09, 0x01, 0x01, 0x00
	.byte 0x00, 0x03, 0x12, 0x1A, 0x05, 0x02, 0x38, 0x01

	.global MOD74_021D84DC
MOD74_021D84DC: ; 0x021D84DC
	.word MOD74_021D8698, MOD74_021D8680, MOD74_021D86B0, MOD74_021D86C8
	.word 0x00000000, 0x00000000, MOD74_021D86E0

	.global MOD74_021D84F8
MOD74_021D84F8: ; 0x021D84F8
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD74_021D8518
MOD74_021D8518: ; 0x021D8518
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD74_021D8540
MOD74_021D8540: ; 0x021D8540
	.byte 0x00, 0x04, 0x01, 0x18, 0x05, 0x02, 0xC0, 0x00, 0x00, 0x01, 0x09, 0x08, 0x05, 0x01, 0x38, 0x01
	.byte 0x00, 0x01, 0x11, 0x08, 0x05, 0x01, 0x60, 0x01, 0x00, 0x0A, 0x09, 0x15, 0x05, 0x01, 0x88, 0x01
	.byte 0x00, 0x0A, 0x11, 0x15, 0x05, 0x01, 0xF1, 0x01, 0x00, 0x03, 0x12, 0x1A, 0x05, 0x02, 0x38, 0x01

	.global MOD74_021D8570
MOD74_021D8570: ; 0x021D8570
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x04, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD74_021D85C4
MOD74_021D85C4: ; 0x021D85C4
	.byte 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x00, 0x72, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x34, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x84, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.global MOD74_021D8680
MOD74_021D8680: ; 0x021D8680
	.asciz "data/btower_pal.resdat"

	.balign 4, 0
	.global MOD74_021D8698
MOD74_021D8698: ; 0x021D8698
	.asciz "data/btower_chr.resdat"

	.balign 4, 0
	.global MOD74_021D86B0
MOD74_021D86B0: ; 0x021D86B0
	.asciz "data/btower_cell.resdat"

	.balign 4, 0
	.global MOD74_021D86C8
MOD74_021D86C8: ; 0x021D86C8
	.asciz "data/btower_canm.resdat"

	.balign 4, 0
	.global MOD74_021D86E0
MOD74_021D86E0: ; 0x021D86E0
	.asciz "data/btower_celact.cldat"

	.bss
