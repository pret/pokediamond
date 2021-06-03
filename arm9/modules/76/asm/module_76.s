	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD76_021D74E0
MOD76_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	mov r2, #2
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x43
	lsl r2, r2, #0x10
	bl CreateHeap
	mov r1, #0x62
	add r0, r5, #0
	lsl r1, r1, #2
	mov r2, #0x43
	bl OverlayManager_CreateAndGetData
	mov r2, #0x62
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	add r0, r5, #0
	bl OverlayManager_GetField18
	str r0, [r4]
	add r0, r4, #0
	bl MOD76_021D7638
	ldr r1, [r4]
	add r0, r4, #0
	ldrh r1, [r1, #0x10]
	mov r2, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD76_021D8C88
	add r0, r4, #0
	mov r1, #0
	bl MOD76_021D8354
	mov r0, #0
	str r0, [sp]
	ldr r3, _021D7560 ; =0x0001020F
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #1
	bl MOD76_021D7CC8
	mov r0, #6
	mov r1, #1
	lsl r0, r0, #6
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xc8
	bl FUN_02019220
	add r0, r4, #0
	bl MOD76_021D8CD4
	ldr r0, _021D7564 ; =MOD76_021D76E8
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7560: .word 0x0001020F
_021D7564: .word MOD76_021D76E8
	thumb_func_end MOD76_021D74E0

	thumb_func_start MOD76_021D7568
MOD76_021D7568: ; 0x021D7568
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0xc
	bhi _021D7606
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7584: ; jump table
	.short _021D759E - _021D7584 - 2 ; case 0
	.short _021D75A6 - _021D7584 - 2 ; case 1
	.short _021D75AE - _021D7584 - 2 ; case 2
	.short _021D75B6 - _021D7584 - 2 ; case 3
	.short _021D75BE - _021D7584 - 2 ; case 4
	.short _021D75C6 - _021D7584 - 2 ; case 5
	.short _021D75CE - _021D7584 - 2 ; case 6
	.short _021D75D6 - _021D7584 - 2 ; case 7
	.short _021D75DE - _021D7584 - 2 ; case 8
	.short _021D75E6 - _021D7584 - 2 ; case 9
	.short _021D75EA - _021D7584 - 2 ; case 10
	.short _021D75F2 - _021D7584 - 2 ; case 11
	.short _021D75FC - _021D7584 - 2 ; case 12
_021D759E:
	bl MOD76_021D795C
	str r0, [r4]
	b _021D7606
_021D75A6:
	bl MOD76_021D7974
	str r0, [r4]
	b _021D7606
_021D75AE:
	bl MOD76_021D7A94
	str r0, [r4]
	b _021D7606
_021D75B6:
	bl MOD76_021D7AB4
	str r0, [r4]
	b _021D7606
_021D75BE:
	bl MOD76_021D7ADC
	str r0, [r4]
	b _021D7606
_021D75C6:
	bl MOD76_021D7B2C
	str r0, [r4]
	b _021D7606
_021D75CE:
	bl MOD76_021D7B80
	str r0, [r4]
	b _021D7606
_021D75D6:
	bl MOD76_021D7B98
	str r0, [r4]
	b _021D7606
_021D75DE:
	bl MOD76_021D7BC8
	str r0, [r4]
	b _021D7606
_021D75E6:
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D75EA:
	bl MOD76_021D8D44
	str r0, [r4]
	b _021D7606
_021D75F2:
	bl MOD76_021D8D5C
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D75FC:
	bl MOD76_021D8DEC
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D7606:
	add r0, r5, #0
	bl MOD76_021D882C
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0200BC1C
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD76_021D7568

	thumb_func_start MOD76_021D761C
MOD76_021D761C: ; 0x021D761C
	push {r4, lr}
	add r4, r0, #0
	bl OverlayManager_GetData
	bl MOD76_021D76B8
	add r0, r4, #0
	bl OverlayManager_FreeData
	mov r0, #0x43
	bl DestroyHeap
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD76_021D761C

	thumb_func_start MOD76_021D7638
MOD76_021D7638: ; 0x021D7638
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D76AC ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D76B0 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #0x43
	bl FUN_02016B94
	str r0, [r4, #4]
	mov r0, #0
	mov r1, #0x43
	bl FUN_02079A70
	bl MOD76_021D7710
	ldr r0, [r4, #4]
	bl MOD76_021D7730
	add r0, r4, #0
	bl MOD76_021D7814
	add r0, r4, #0
	bl MOD76_021D8C4C
	add r0, r4, #0
	bl MOD76_021D7900
	add r0, r4, #0
	bl MOD76_021D789C
	add r0, r4, #0
	bl MOD76_021D7ECC
	add r0, r4, #0
	bl MOD76_021D7BE0
	ldr r0, _021D76B4 ; =MOD76_021D76E8
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	pop {r4, pc}
	.align 2, 0
_021D76AC: .word 0xFFFFE0FF
_021D76B0: .word 0x04001000
_021D76B4: .word MOD76_021D76E8
	thumb_func_end MOD76_021D7638

	thumb_func_start MOD76_021D76B8
MOD76_021D76B8: ; 0x021D76B8
	push {r4, lr}
	add r4, r0, #0
	bl MOD76_021D7FAC
	add r0, r4, #0
	bl MOD76_021D78E8
	ldr r0, [r4, #4]
	bl MOD76_021D77E4
	add r0, r4, #0
	bl MOD76_021D7938
	add r0, r4, #0
	bl MOD76_021D87F8
	bl FUN_0201C29C
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD76_021D76B8

	thumb_func_start MOD76_021D76E8
MOD76_021D76E8: ; 0x021D76E8
	push {r3, lr}
	ldr r0, [r0, #4]
	bl FUN_0201AB60
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r3, _021D7708 ; =0x027E0000
	ldr r1, _021D770C ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	nop
_021D7708: .word 0x027E0000
_021D770C: .word 0x00003FF8
	thumb_func_end MOD76_021D76E8

	thumb_func_start MOD76_021D7710
MOD76_021D7710: ; 0x021D7710
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D772C ; =0x021D8F44
	add r3, sp, #0
	mov r2, #5
_021D771A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D771A
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D772C: .word MOD76_021D8F44
	thumb_func_end MOD76_021D7710

	thumb_func_start MOD76_021D7730
MOD76_021D7730: ; 0x021D7730
	push {r4, r5, lr}
	sub sp, #0x64
	ldr r5, _021D77D4 ; =0x021D8E4C
	add r3, sp, #0x54
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D77D8 ; =0x021D8E88
	add r3, sp, #0x38
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
	ldr r5, _021D77DC ; =0x021D8EC0
	add r3, sp, #0x1c
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
	ldr r5, _021D77E0 ; =0x021D8EA4
	add r3, sp, #0
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
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x43
	bl FUN_02017F18
	add sp, #0x64
	pop {r4, r5, pc}
	nop
_021D77D4: .word MOD76_021D8E4C
_021D77D8: .word MOD76_021D8E88
_021D77DC: .word MOD76_021D8EC0
_021D77E0: .word MOD76_021D8EA4
	thumb_func_end MOD76_021D7730

	thumb_func_start MOD76_021D77E4
MOD76_021D77E4: ; 0x021D77E4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x17
	mov r1, #0
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	mov r0, #0x43
	add r1, r4, #0
	bl FreeToHeapExplicit
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD76_021D77E4

	thumb_func_start MOD76_021D7814
MOD76_021D7814: ; 0x021D7814
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x43
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x71
	mov r1, #0xa
	mov r3, #2
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x43
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x71
	mov r1, #0xb
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r2, #0
	str r2, [sp]
	mov r0, #0x43
	str r0, [sp, #4]
	mov r0, #0x71
	mov r1, #0xc
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r1, #7
	mov r0, #0
	lsl r1, r1, #6
	mov r2, #0x43
	bl FUN_02002EEC
	mov r1, #0
	str r1, [sp]
	mov r0, #0x43
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	mov r2, #1
	mov r3, #0xc
	bl FUN_0200CB00
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x43
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	mov r1, #0
	mov r2, #0xa
	mov r3, #0xd
	bl FUN_0200CD68
	add sp, #0x10
	pop {r4, pc}
	thumb_func_end MOD76_021D7814

	thumb_func_start MOD76_021D789C
MOD76_021D789C: ; 0x021D789C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r7, #0
	ldr r4, _021D78E4 ; =0x021D8FC4
	mov r6, #0
	add r5, #8
_021D78A8:
	ldr r0, [r7, #4]
	add r1, r5, #0
	add r2, r4, #0
	bl AddWindow
	add r0, r5, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r6, r6, #1
	add r4, #8
	add r5, #0x10
	cmp r6, #0xf
	blo _021D78A8
	add r0, r7, #0
	bl MOD76_021D7DAC
	add r0, r7, #0
	add r0, #0xc8
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r7, #0xc8
	add r0, r7, #0
	mov r1, #0
	mov r2, #0xa
	mov r3, #0xd
	bl FUN_0200D0BC
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D78E4: .word MOD76_021D8FC4
	thumb_func_end MOD76_021D789C

	thumb_func_start MOD76_021D78E8
MOD76_021D78E8: ; 0x021D78E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #8
_021D78F0:
	add r0, r5, #0
	bl RemoveWindow
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0xf
	blo _021D78F0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD76_021D78E8

	thumb_func_start MOD76_021D7900
MOD76_021D7900: ; 0x021D7900
	push {r4, lr}
	ldr r2, _021D7934 ; =0x0000024A
	add r4, r0, #0
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x43
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0xf8
	str r0, [r1]
	mov r0, #0x43
	bl ScrStrBufs_new
	add r1, r4, #0
	add r1, #0xfc
	str r0, [r1]
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #0x43
	bl String_ctor
	mov r1, #1
	lsl r1, r1, #8
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_021D7934: .word 0x0000024A
	thumb_func_end MOD76_021D7900

	thumb_func_start MOD76_021D7938
MOD76_021D7938: ; 0x021D7938
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl DestroyMsgData
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	bl ScrStrBufs_delete
	mov r0, #1
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD76_021D7938

	thumb_func_start MOD76_021D795C
MOD76_021D795C: ; 0x021D795C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7970
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	pop {r4, pc}
_021D7970:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD76_021D795C

	thumb_func_start MOD76_021D7974
MOD76_021D7974: ; 0x021D7974
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D7A88 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x30
	tst r1, r0
	beq _021D799C
	ldr r0, _021D7A8C ; =0x000005DD
	bl FUN_020054C8
	ldr r2, [r5]
	mov r0, #1
	ldrb r1, [r2, #0x14]
	eor r0, r1
	strb r0, [r2, #0x14]
	add r0, r5, #0
	bl MOD76_021D7BE0
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D799C:
	add r0, #0xd4
	add r1, sp, #0
	ldr r0, [r5, r0]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	ldr r2, [r5]
	mov r0, #0x41
	add r1, r2, #0
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, #0x12
	add r2, #0x10
	bl ListMenuGetScrollAndRow
	ldr r2, [r5]
	add r1, sp, #0
	ldrh r1, [r1, #2]
	ldrh r2, [r2, #0x12]
	add r0, r5, #0
	bl MOD76_021D8AC0
	ldr r0, [r5]
	ldrh r1, [r0, #0x10]
	add r0, sp, #0
	ldrh r0, [r0]
	cmp r1, r0
	beq _021D79EE
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #0
	bl MOD76_021D8C88
_021D79EE:
	add r0, r5, #0
	bl MOD76_021D8CD4
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _021D7A04
	add r0, r0, #1
	cmp r4, r0
	beq _021D7A82
	b _021D7A38
_021D7A04:
	ldr r0, _021D7A8C ; =0x000005DD
	bl FUN_020054C8
	ldr r1, [r5]
	add r0, r5, #0
	ldrh r1, [r1, #0x10]
	mov r2, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD76_021D8C88
	add r0, r5, #0
	bl MOD76_021D8D24
	add r0, r5, #0
	mov r1, #2
	bl MOD76_021D853C
	ldr r0, _021D7A90 ; =0x00000186
	mov r1, #1
	strb r1, [r5, r0]
	mov r1, #3
	lsl r0, r1, #7
	str r1, [r5, r0]
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D7A38:
	ldr r0, _021D7A8C ; =0x000005DD
	bl FUN_020054C8
	ldr r1, [r5]
	add r0, r5, #0
	ldrh r1, [r1, #0x10]
	mov r2, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD76_021D8C88
	add r0, r5, #0
	bl MOD76_021D8D24
	add r0, r5, #0
	bl MOD76_021D85E4
	cmp r0, #4
	bhs _021D7A6A
	add r0, r5, #0
	mov r1, #1
	bl MOD76_021D853C
	mov r1, #0
	b _021D7A74
_021D7A6A:
	add r0, r5, #0
	mov r1, #4
	bl MOD76_021D853C
	mov r1, #2
_021D7A74:
	ldr r0, _021D7A90 ; =0x00000186
	strb r1, [r5, r0]
	mov r1, #3
	lsl r0, r1, #7
	str r1, [r5, r0]
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D7A82:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021D7A88: .word gMain
_021D7A8C: .word 0x000005DD
_021D7A90: .word 0x00000186
	thumb_func_end MOD76_021D7974

	thumb_func_start MOD76_021D7A94
MOD76_021D7A94: ; 0x021D7A94
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D7AB0 ; =0x00000185
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D7AAC
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	pop {r4, pc}
_021D7AAC:
	mov r0, #2
	pop {r4, pc}
	.align 2, 0
_021D7AB0: .word 0x00000185
	thumb_func_end MOD76_021D7A94

	thumb_func_start MOD76_021D7AB4
MOD76_021D7AB4: ; 0x021D7AB4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0x43
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r1, _021D7AD8 ; =0x021D9034
	mov r2, #1
	mov r3, #0xc
	bl Std_CreateYesNoMenu
	mov r1, #0x43
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #4
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D7AD8: .word MOD76_021D9034
	thumb_func_end MOD76_021D7AB4

	thumb_func_start MOD76_021D7ADC
MOD76_021D7ADC: ; 0x021D7ADC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x43
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0x43
	bl FUN_020021AC
	cmp r0, #0
	beq _021D7AFA
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _021D7B0A
	b _021D7B1A
_021D7AFA:
	ldr r1, _021D7B20 ; =0x00000186
	add r0, r4, #0
	ldrb r1, [r4, r1]
	lsl r2, r1, #3
	ldr r1, _021D7B24 ; =0x021D8F1C
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
_021D7B0A:
	ldr r1, _021D7B20 ; =0x00000186
	add r0, r4, #0
	ldrb r1, [r4, r1]
	lsl r2, r1, #3
	ldr r1, _021D7B28 ; =0x021D8F20
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
_021D7B1A:
	mov r0, #4
	pop {r4, pc}
	nop
_021D7B20: .word 0x00000186
_021D7B24: .word MOD76_021D8F1C
_021D7B28: .word MOD76_021D8F20
	thumb_func_end MOD76_021D7ADC

	thumb_func_start MOD76_021D7B2C
MOD76_021D7B2C: ; 0x021D7B2C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl MOD76_021D8514
	str r0, [sp]
	ldr r1, [r4]
	add r2, sp, #0
	ldr r0, [r1]
	ldrb r1, [r1, #0x17]
	add r1, #0x36
	bl SetMonData
	mov r0, #0
	str r0, [sp]
	ldr r1, [r4]
	add r2, sp, #0
	ldr r0, [r1]
	ldrb r1, [r1, #0x17]
	add r1, #0x3e
	bl SetMonData
	add r0, r4, #0
	bl MOD76_021D8514
	mov r1, #0
	bl WazaGetMaxPp
	str r0, [sp]
	ldr r1, [r4]
	add r2, sp, #0
	ldr r0, [r1]
	ldrb r1, [r1, #0x17]
	add r1, #0x3a
	bl SetMonData
	ldr r0, [r4]
	mov r1, #0
	strb r1, [r0, #0x16]
	mov r0, #8
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD76_021D7B2C

	thumb_func_start MOD76_021D7B80
MOD76_021D7B80: ; 0x021D7B80
	push {r4, lr}
	mov r1, #6
	add r4, r0, #0
	bl MOD76_021D853C
	mov r0, #6
	mov r1, #5
	lsl r0, r0, #6
	str r1, [r4, r0]
	mov r0, #2
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD76_021D7B80

	thumb_func_start MOD76_021D7B98
MOD76_021D7B98: ; 0x021D7B98
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	ldrb r1, [r1, #0x17]
	cmp r1, #4
	bhs _021D7BAE
	mov r1, #0xa
	bl MOD76_021D853C
	mov r1, #4
	b _021D7BB6
_021D7BAE:
	mov r1, #7
	bl MOD76_021D853C
	mov r1, #3
_021D7BB6:
	ldr r0, _021D7BC4 ; =0x00000186
	strb r1, [r4, r0]
	mov r1, #3
	lsl r0, r1, #7
	str r1, [r4, r0]
	mov r0, #2
	pop {r4, pc}
	.align 2, 0
_021D7BC4: .word 0x00000186
	thumb_func_end MOD76_021D7B98

	thumb_func_start MOD76_021D7BC8
MOD76_021D7BC8: ; 0x021D7BC8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0x43
	bl FUN_02079A70
	mov r0, #6
	mov r1, #9
	lsl r0, r0, #6
	str r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD76_021D7BC8

	thumb_func_start MOD76_021D7BE0
MOD76_021D7BE0: ; 0x021D7BE0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD76_021D8514
	add r4, r0, #0
	ldr r0, [r5]
	ldrb r0, [r0, #0x14]
	cmp r0, #0
	ldr r0, [r5, #4]
	bne _021D7C3A
	mov r2, #0
	mov r1, #2
	add r3, r2, #0
	bl FUN_0201AEE4
	add r0, r5, #0
	add r0, #0x18
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x68
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0xb8
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #8
	bl FUN_02019220
	ldr r0, _021D7CC4 ; =0x0000FFFF
	cmp r4, r0
	beq _021D7C2E
	add r0, r5, #0
	add r1, r4, #0
	bl MOD76_021D800C
	b _021D7CBC
_021D7C2E:
	mov r1, #1
	add r0, r5, #0
	mvn r1, r1
	bl MOD76_021D800C
	b _021D7CBC
_021D7C3A:
	mov r1, #2
	add r3, r1, #0
	mov r2, #0
	add r3, #0xfe
	bl FUN_0201AEE4
	add r0, r5, #0
	add r0, #8
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x28
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x38
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x48
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x58
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0xa8
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x78
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x88
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x98
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x18
	bl FUN_02019220
	ldr r0, _021D7CC4 ; =0x0000FFFF
	cmp r4, r0
	beq _021D7CA6
	add r0, r5, #0
	add r1, r4, #0
	bl MOD76_021D81AC
	b _021D7CB0
_021D7CA6:
	mov r1, #1
	add r0, r5, #0
	mvn r1, r1
	bl MOD76_021D81AC
_021D7CB0:
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C644
_021D7CBC:
	add r0, r5, #0
	bl MOD76_021D8A58
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7CC4: .word 0x0000FFFF
	thumb_func_end MOD76_021D7BE0

	thumb_func_start MOD76_021D7CC8
MOD76_021D7CC8: ; 0x021D7CC8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [sp, #0x28]
	add r4, r1, #0
	add r7, r3, #0
	str r2, [sp, #0x10]
	cmp r0, #0
	beq _021D7CE4
	cmp r0, #1
	beq _021D7CE8
	cmp r0, #2
	beq _021D7D12
	b _021D7D3E
_021D7CE4:
	mov r3, #0
	b _021D7D3E
_021D7CE8:
	mov r1, #1
	lsl r1, r1, #8
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	add r1, r5, #0
	lsr r6, r0, #0x18
	add r1, #8
	lsl r0, r4, #4
	add r0, r1, r0
	bl GetWindowWidth
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x18
	sub r0, r0, r6
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	b _021D7D3E
_021D7D12:
	mov r1, #1
	lsl r1, r1, #8
	mov r0, #0
	ldr r1, [r5, r1]
	add r2, r0, #0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	add r1, r5, #0
	lsr r6, r0, #0x18
	add r1, #8
	lsl r0, r4, #4
	add r0, r1, r0
	bl GetWindowWidth
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x18
	sub r1, r0, r6
	lsr r0, r1, #0x1f
	add r0, r1, r0
	lsl r0, r0, #0x17
	lsr r3, r0, #0x18
_021D7D3E:
	mov r0, #0
	str r0, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	str r7, [sp, #8]
	add r1, r5, #0
	str r0, [sp, #0xc]
	add r2, r2, #1
	add r1, #8
	lsl r0, r4, #4
	add r0, r1, r0
	ldr r1, [sp, #0x10]
	ldr r2, [r5, r2]
	bl AddTextPrinterParameterized2
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD76_021D7CC8

	thumb_func_start MOD76_021D7D60
MOD76_021D7D60: ; 0x021D7D60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r6, r2, #0
	add r7, r3, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	mov r1, #0
	add r2, r6, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xfc
	ldr r0, [r0]
	add r3, r7, #0
	bl BufferIntegerAsString
	add r0, r5, #0
	mov r1, #1
	add r0, #0xfc
	lsl r1, r1, #8
	ldr r0, [r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD76_021D7D60

	thumb_func_start MOD76_021D7DAC
MOD76_021D7DAC: ; 0x021D7DAC
	push {r3, r4, lr}
	sub sp, #4
	mov r1, #0x1a
	add r2, r1, #0
	add r4, r0, #0
	add r0, #0xf8
	add r2, #0xe6
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r0, #2
	mov r1, #0
	str r0, [sp]
	ldr r3, _021D7E9C ; =0x000F0E00
	add r0, r4, #0
	add r2, r1, #0
	bl MOD76_021D7CC8
	mov r1, #0x1c
	add r0, r4, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xe4
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r0, #2
	str r0, [sp]
	ldr r3, _021D7E9C ; =0x000F0E00
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD76_021D7CC8
	mov r1, #0x16
	add r0, r4, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xea
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r2, #0
	ldr r3, _021D7E9C ; =0x000F0E00
	add r0, r4, #0
	mov r1, #2
	str r2, [sp]
	bl MOD76_021D7CC8
	mov r1, #0x17
	add r0, r4, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xe9
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r2, #0
	ldr r3, _021D7E9C ; =0x000F0E00
	add r0, r4, #0
	mov r1, #3
	str r2, [sp]
	bl MOD76_021D7CC8
	mov r1, #0x18
	add r0, r4, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xe8
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r2, #0
	ldr r3, _021D7E9C ; =0x000F0E00
	add r0, r4, #0
	mov r1, #4
	str r2, [sp]
	bl MOD76_021D7CC8
	mov r1, #0x19
	add r0, r4, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xe7
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r2, #0
	ldr r3, _021D7EA0 ; =0x00010200
	add r0, r4, #0
	mov r1, #5
	str r2, [sp]
	bl MOD76_021D7CC8
	mov r1, #0x1b
	add r0, r4, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xe5
	ldr r0, [r0]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	mov r0, #2
	str r0, [sp]
	ldr r3, _021D7E9C ; =0x000F0E00
	add r0, r4, #0
	mov r1, #6
	mov r2, #0
	bl MOD76_021D7CC8
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D7E9C: .word 0x000F0E00
_021D7EA0: .word 0x00010200
	thumb_func_end MOD76_021D7DAC

	thumb_func_start MOD76_021D7EA4
MOD76_021D7EA4: ; 0x021D7EA4
	push {r3, r4}
	ldr r0, [r0]
	ldr r1, _021D7EC8 ; =0x0000FFFF
	ldr r4, [r0, #0xc]
	mov r0, #1
	mov r3, #0
	lsl r0, r0, #8
_021D7EB2:
	ldrh r2, [r4]
	cmp r2, r1
	beq _021D7EC0
	add r3, r3, #1
	add r4, r4, #2
	cmp r3, r0
	blo _021D7EB2
_021D7EC0:
	add r0, r3, #0
	pop {r3, r4}
	bx lr
	nop
_021D7EC8: .word 0x0000FFFF
	thumb_func_end MOD76_021D7EA4

	thumb_func_start MOD76_021D7ECC
MOD76_021D7ECC: ; 0x021D7ECC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl MOD76_021D7EA4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r0, #1
	mov r0, #0x61
	lsl r0, r0, #2
	strb r1, [r5, r0]
	ldrb r0, [r5, r0]
	mov r1, #0x43
	bl ListMenuItems_ctor
	mov r1, #0x42
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r2, #0x93
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #0x43
	bl NewMsgDataFromNarc
	add r7, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	mov r4, #0
	cmp r0, #0
	bls _021D7F50
	add r6, r4, #0
_021D7F0E:
	ldr r0, [r5]
	ldr r0, [r0, #0xc]
	ldrh r2, [r0, r6]
	ldr r0, _021D7FA4 ; =0x0000FFFF
	cmp r2, r0
	beq _021D7F2A
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r7, #0
	add r3, r2, #0
	bl ListMenuItems_AppendFromMsgData
	b _021D7F42
_021D7F2A:
	mov r0, #0x42
	add r1, r5, #0
	lsl r0, r0, #2
	add r1, #0xf8
	mov r2, #0x20
	add r3, r2, #0
	ldr r0, [r5, r0]
	ldr r1, [r1]
	sub r3, #0x22
	bl ListMenuItems_AppendFromMsgData
	b _021D7F50
_021D7F42:
	mov r0, #0x61
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	add r4, r4, #1
	add r6, r6, #2
	cmp r4, r0
	blo _021D7F0E
_021D7F50:
	add r0, r7, #0
	bl DestroyMsgData
	ldr r4, _021D7FA8 ; =0x021D8EFC
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	add r0, #0x7c
	str r1, [sp]
	add r1, r5, #0
	add r1, #0xd8
	str r1, [sp, #0xc]
	ldrb r1, [r5, r0]
	add r0, sp, #0
	strh r1, [r0, #0x10]
	str r5, [sp, #0x1c]
	ldr r3, [r5]
	add r0, r2, #0
	ldrh r1, [r3, #0x12]
	ldrh r2, [r3, #0x10]
	mov r3, #0x43
	bl ListMenuInit
	mov r1, #0x41
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r5, #0xd8
	add r0, r5, #0
	bl FUN_02019220
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7FA4: .word 0x0000FFFF
_021D7FA8: .word MOD76_021D8EFC
	thumb_func_end MOD76_021D7ECC

	thumb_func_start MOD76_021D7FAC
MOD76_021D7FAC: ; 0x021D7FAC
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4]
	mov r0, #0x41
	add r1, r2, #0
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, #0x12
	add r2, #0x10
	bl DestroyListMenu
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ListMenuItems_dtor
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD76_021D7FAC

	thumb_func_start MOD76_021D7FD0
MOD76_021D7FD0: ; 0x021D7FD0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x13
	add r6, r2, #0
	bl ListMenuGetTemplateField
	add r4, r0, #0
	cmp r6, #1
	beq _021D7FE8
	ldr r0, _021D8004 ; =0x000005DD
	bl FUN_020054C8
_021D7FE8:
	ldr r0, [r4]
	ldrb r0, [r0, #0x14]
	cmp r0, #0
	bne _021D7FFA
	add r0, r4, #0
	add r1, r5, #0
	bl MOD76_021D800C
	pop {r4, r5, r6, pc}
_021D7FFA:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD76_021D81AC
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8004: .word 0x000005DD
	thumb_func_end MOD76_021D7FD0

	thumb_func_start MOD76_021D8008
MOD76_021D8008: ; 0x021D8008
	bx lr
	.align 2, 0
	thumb_func_end MOD76_021D8008

	thumb_func_start MOD76_021D800C
MOD76_021D800C: ; 0x021D800C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0xa8
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x78
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x88
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x98
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _021D8050
	b _021D815E
_021D8050:
	add r0, r4, #0
	mov r1, #2
	bl GetWazaAttr
	add r2, r0, #0
	cmp r2, #1
	bhi _021D8072
	mov r1, #0x21
	add r0, r5, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xdf
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	b _021D8080
_021D8072:
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x1d
	mov r3, #3
	bl MOD76_021D7D60
_021D8080:
	mov r0, #2
	str r0, [sp]
	ldr r3, _021D81A4 ; =0x00010200
	add r0, r5, #0
	mov r1, #7
	mov r2, #0
	bl MOD76_021D7CC8
	add r0, r4, #0
	mov r1, #4
	bl GetWazaAttr
	add r2, r0, #0
	bne _021D80B0
	mov r1, #0x21
	add r0, r5, #0
	add r2, r1, #0
	add r0, #0xf8
	add r2, #0xdf
	ldr r0, [r0]
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	b _021D80BE
_021D80B0:
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x1e
	mov r3, #3
	bl MOD76_021D7D60
_021D80BE:
	mov r0, #2
	str r0, [sp]
	ldr r3, _021D81A4 ; =0x00010200
	add r0, r5, #0
	mov r1, #8
	mov r2, #0
	bl MOD76_021D7CC8
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	mov r1, #0
	bl WazaGetMaxPp
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x1f
	mov r3, #2
	bl MOD76_021D7D60
	mov r0, #2
	str r0, [sp]
	ldr r3, _021D81A4 ; =0x00010200
	add r0, r5, #0
	mov r1, #9
	mov r2, #0
	bl MOD76_021D7CC8
	ldr r2, _021D81A8 ; =0x0000024B
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x43
	bl NewMsgDataFromNarc
	mov r2, #1
	lsl r2, r2, #8
	ldr r2, [r5, r2]
	add r1, r4, #0
	add r6, r0, #0
	bl ReadMsgDataIntoString
	mov r2, #0
	ldr r3, _021D81A4 ; =0x00010200
	add r0, r5, #0
	mov r1, #0xa
	str r2, [sp]
	bl MOD76_021D7CC8
	add r0, r6, #0
	bl DestroyMsgData
	lsl r1, r4, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl MOD76_021D8BF8
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_0200C644
	add r0, r5, #0
	add r0, #0x28
	bl FUN_02019220
	add r0, r5, #0
	add r0, #0x38
	bl FUN_02019220
	add r0, r5, #0
	add r0, #0x48
	bl FUN_02019220
	add r0, r5, #0
	add r0, #0x58
	bl FUN_02019220
	b _021D817E
_021D815E:
	add r0, r5, #0
	add r0, #0x28
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x38
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x48
	bl FUN_0201958C
	add r0, r5, #0
	add r0, #0x58
	bl FUN_0201958C
_021D817E:
	add r0, r5, #0
	add r0, #0xa8
	bl FUN_02019220
	add r0, r5, #0
	add r0, #0x78
	bl FUN_02019220
	add r0, r5, #0
	add r0, #0x88
	bl FUN_02019220
	add r5, #0x98
	add r0, r5, #0
	bl FUN_02019220
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021D81A4: .word 0x00010200
_021D81A8: .word 0x0000024B
	thumb_func_end MOD76_021D800C

	thumb_func_start MOD76_021D81AC
MOD76_021D81AC: ; 0x021D81AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0xb8
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r1, #1
	mvn r1, r1
	cmp r4, r1
	beq _021D8222
	add r0, r4, #0
	mov r1, #0xa
	bl GetWazaAttr
	bl FUN_0208315C
	add r6, r0, #0
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc5
	mov r3, #0x43
	bl NewMsgDataFromNarc
	mov r2, #1
	lsl r2, r2, #8
	ldr r2, [r5, r2]
	add r1, r6, #0
	add r7, r0, #0
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r2, #0xff
	str r2, [sp, #4]
	ldr r0, _021D8240 ; =0x00010200
	add r2, r2, #1
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	ldr r2, [r5, r2]
	add r0, #0xb8
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl DestroyMsgData
	lsl r1, r4, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl MOD76_021D8300
	add r0, r5, #0
	add r0, #0x68
	bl FUN_02019220
	b _021D8232
_021D8222:
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl MOD76_021D8300
	add r0, r5, #0
	add r0, #0x68
	bl FUN_0201958C
_021D8232:
	add r5, #0xb8
	add r0, r5, #0
	bl FUN_02019220
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8240: .word 0x00010200
	thumb_func_end MOD76_021D81AC

	thumb_func_start MOD76_021D8244
MOD76_021D8244: ; 0x021D8244
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #5
	lsl r6, r2, #1
	str r0, [sp]
	add r4, r1, #0
	mov r0, #1
	add r7, r6, #0
	str r0, [sp, #4]
	add r7, #0x22
	str r0, [sp, #8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	lsl r3, r7, #0x18
	ldr r0, [r5, #4]
	mov r1, #2
	add r2, r4, #0
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r0, #5
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r6, #0x23
	str r0, [sp, #8]
	mov r0, #0x10
	add r2, r4, #1
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, #4]
	mov r1, #2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r2, r4, #0
	str r0, [sp, #8]
	mov r0, #0x10
	add r2, #0x20
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r7, #0x18
	ldr r0, [r5, #4]
	mov r1, #2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x10
	add r4, #0x21
	str r0, [sp, #0xc]
	lsl r2, r4, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, #4]
	mov r1, #2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD76_021D8244

	thumb_func_start MOD76_021D82D8
MOD76_021D82D8: ; 0x021D82D8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r4, #0
	mov r6, #0x12
_021D82E0:
	lsl r2, r4, #0x18
	add r0, r5, #0
	add r1, r6, #0
	lsr r2, r2, #0x18
	bl MOD76_021D8244
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #6
	blo _021D82E0
	ldr r0, [r5, #4]
	mov r1, #2
	bl FUN_0201AC68
	pop {r4, r5, r6, pc}
	thumb_func_end MOD76_021D82D8

	thumb_func_start MOD76_021D8300
MOD76_021D8300: ; 0x021D8300
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD76_021D82D8
	ldr r0, _021D8350 ; =0x0000FFFF
	cmp r4, r0
	beq _021D8344
	add r0, r4, #0
	mov r1, #0xa
	bl GetWazaAttr
	bl FUN_02083114
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	asr r6, r0, #0x18
	mov r4, #0
	cmp r6, #0
	ble _021D8344
	mov r7, #0xe
_021D832E:
	lsl r2, r4, #0x18
	add r0, r5, #0
	add r1, r7, #0
	lsr r2, r2, #0x18
	bl MOD76_021D8244
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blt _021D832E
_021D8344:
	ldr r0, [r5, #4]
	mov r1, #2
	bl FUN_0201AC68
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8350: .word 0x0000FFFF
	thumb_func_end MOD76_021D8300

	thumb_func_start MOD76_021D8354
MOD76_021D8354: ; 0x021D8354
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #0xa
	bls _021D8360
	b _021D84D8
_021D8360:
	add r1, r5, r5
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D836C: ; jump table
	.short _021D8382 - _021D836C - 2 ; case 0
	.short _021D839A - _021D836C - 2 ; case 1
	.short _021D83AE - _021D836C - 2 ; case 2
	.short _021D83C6 - _021D836C - 2 ; case 3
	.short _021D83F2 - _021D836C - 2 ; case 4
	.short _021D841E - _021D836C - 2 ; case 5
	.short _021D844A - _021D836C - 2 ; case 6
	.short _021D8476 - _021D836C - 2 ; case 7
	.short _021D848A - _021D836C - 2 ; case 8
	.short _021D84B6 - _021D836C - 2 ; case 9
	.short _021D84C6 - _021D836C - 2 ; case 10
_021D8382:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	b _021D84D8
_021D839A:
	bl MOD76_021D8514
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl BufferMoveName
	b _021D84D8
_021D83AE:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	b _021D84D8
_021D83C6:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	add r0, r4, #0
	bl MOD76_021D8514
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl BufferMoveName
	b _021D84D8
_021D83F2:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	add r0, r4, #0
	bl MOD76_021D8514
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl BufferMoveName
	b _021D84D8
_021D841E:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	add r0, r4, #0
	bl MOD76_021D8524
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl BufferMoveName
	b _021D84D8
_021D844A:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	add r0, r4, #0
	bl MOD76_021D8514
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl BufferMoveName
	b _021D84D8
_021D8476:
	bl MOD76_021D8514
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl BufferMoveName
	b _021D84D8
_021D848A:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_020690E4
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferBoxMonNickname
	add r0, r4, #0
	bl MOD76_021D8514
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #1
	bl BufferMoveName
	b _021D84D8
_021D84B6:
	ldr r2, [r4]
	add r0, #0xfc
	ldr r0, [r0]
	ldr r2, [r2, #4]
	mov r1, #2
	bl BufferPlayersName
	b _021D84D8
_021D84C6:
	bl MOD76_021D8524
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	mov r1, #0
	bl BufferMoveName
_021D84D8:
	ldr r1, [r4]
	add r0, r4, #0
	ldrb r2, [r1, #0x15]
	add r0, #0xf8
	mov r1, #0x2c
	add r3, r2, #0
	mul r3, r1
	ldr r1, _021D8510 ; =0x021D8F6C
	lsl r2, r5, #2
	add r1, r1, r3
	ldr r0, [r0]
	ldr r1, [r2, r1]
	bl NewString_ReadMsgData
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	add r0, #0xfc
	lsl r1, r1, #8
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_dtor
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8510: .word MOD76_021D8F6C
	thumb_func_end MOD76_021D8354

	thumb_func_start MOD76_021D8514
MOD76_021D8514: ; 0x021D8514
	ldr r0, [r0]
	ldr r2, [r0, #0xc]
	ldrh r1, [r0, #0x12]
	ldrh r0, [r0, #0x10]
	add r0, r1, r0
	lsl r0, r0, #1
	ldrh r0, [r2, r0]
	bx lr
	thumb_func_end MOD76_021D8514

	thumb_func_start MOD76_021D8524
MOD76_021D8524: ; 0x021D8524
	push {r3, lr}
	ldr r1, [r0]
	mov r2, #0
	ldr r0, [r1]
	ldrb r1, [r1, #0x17]
	add r1, #0x36
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD76_021D8524

	thumb_func_start MOD76_021D853C
MOD76_021D853C: ; 0x021D853C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r5, r1, #0
	add r0, #0xc8
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r1, r5, #0
	bl MOD76_021D8354
	mov r0, #1
	bl FUN_02002B60
	mov r0, #0
	bl FUN_02002B7C
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl Options_GetTextFrameDelay
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, _021D858C ; =MOD76_021D8594
	mov r1, #1
	add r2, r1, #0
	str r0, [sp, #8]
	add r2, #0xff
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0xc8
	bl AddTextPrinterParameterized
	ldr r1, _021D8590 ; =0x00000185
	strb r0, [r4, r1]
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021D858C: .word MOD76_021D8594
_021D8590: .word 0x00000185
	thumb_func_end MOD76_021D853C

	thumb_func_start MOD76_021D8594
MOD76_021D8594: ; 0x021D8594
	push {r3, lr}
	cmp r1, #5
	bhi _021D85D6
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D85A6: ; jump table
	.short _021D85D6 - _021D85A6 - 2 ; case 0
	.short _021D85B2 - _021D85A6 - 2 ; case 1
	.short _021D85B8 - _021D85A6 - 2 ; case 2
	.short _021D85BE - _021D85A6 - 2 ; case 3
	.short _021D85C6 - _021D85A6 - 2 ; case 4
	.short _021D85CE - _021D85A6 - 2 ; case 5
_021D85B2:
	bl FUN_02005514
	pop {r3, pc}
_021D85B8:
	bl FUN_02005CBC
	pop {r3, pc}
_021D85BE:
	ldr r0, _021D85DC ; =0x000005E6
	bl FUN_020054C8
	b _021D85D6
_021D85C6:
	ldr r0, _021D85E0 ; =0x00000483
	bl PlaySound
	b _021D85D6
_021D85CE:
	ldr r0, _021D85DC ; =0x000005E6
	bl FUN_02005508
	pop {r3, pc}
_021D85D6:
	mov r0, #0
	pop {r3, pc}
	nop
_021D85DC: .word 0x000005E6
_021D85E0: .word 0x00000483
	thumb_func_end MOD76_021D8594

	thumb_func_start MOD76_021D85E4
MOD76_021D85E4: ; 0x021D85E4
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_021D85EC:
	ldr r0, [r5]
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #0x36
	add r2, r6, #0
	bl GetMonData
	cmp r0, #0
	beq _021D8608
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D85EC
_021D8608:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD76_021D85E4

	thumb_func_start MOD76_021D860C
MOD76_021D860C: ; 0x021D860C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #3
	bl MOD76_021D853C
	add r0, r4, #0
	bl MOD76_021D85E4
	ldr r1, [r4]
	strb r0, [r1, #0x17]
	mov r0, #6
	mov r1, #5
	lsl r0, r0, #6
	str r1, [r4, r0]
	mov r0, #2
	pop {r4, pc}
	thumb_func_end MOD76_021D860C

	thumb_func_start MOD76_021D862C
MOD76_021D862C: ; 0x021D862C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r0, #0xc8
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r4, #0
	mov r1, #0
	bl MOD76_021D8354
	mov r0, #0
	str r0, [sp]
	ldr r3, _021D8678 ; =0x0001020F
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #1
	bl MOD76_021D7CC8
	add r0, r4, #0
	add r0, #0xc8
	bl FUN_02019220
	ldr r1, [r4]
	add r0, r4, #0
	ldrh r1, [r1, #0x10]
	mov r2, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD76_021D8C88
	add r0, r4, #0
	mov r1, #1
	bl MOD76_021D8CB4
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D8678: .word 0x0001020F
	thumb_func_end MOD76_021D862C

	thumb_func_start MOD76_021D867C
MOD76_021D867C: ; 0x021D867C
	ldr r0, [r0]
	mov r1, #1
	strb r1, [r0, #0x16]
	mov r0, #8
	bx lr
	.align 2, 0
	thumb_func_end MOD76_021D867C

	thumb_func_start MOD76_021D8688
MOD76_021D8688: ; 0x021D8688
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r0, #0xc8
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r4, #0
	mov r1, #0
	bl MOD76_021D8354
	mov r0, #0
	str r0, [sp]
	ldr r3, _021D86D4 ; =0x0001020F
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #1
	bl MOD76_021D7CC8
	add r0, r4, #0
	add r0, #0xc8
	bl FUN_02019220
	ldr r1, [r4]
	add r0, r4, #0
	ldrh r1, [r1, #0x10]
	mov r2, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD76_021D8C88
	add r0, r4, #0
	mov r1, #1
	bl MOD76_021D8CB4
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D86D4: .word 0x0001020F
	thumb_func_end MOD76_021D8688

	thumb_func_start MOD76_021D86D8
MOD76_021D86D8: ; 0x021D86D8
	mov r1, #6
	mov r2, #0xa
	lsl r1, r1, #6
	str r2, [r0, r1]
	mov r0, #0
	bx lr
	thumb_func_end MOD76_021D86D8

	thumb_func_start MOD76_021D86E4
MOD76_021D86E4: ; 0x021D86E4
	push {r4, lr}
	mov r1, #7
	add r4, r0, #0
	bl MOD76_021D853C
	ldr r0, _021D86FC ; =0x00000186
	mov r1, #3
	strb r1, [r4, r0]
	sub r0, r0, #6
	str r1, [r4, r0]
	mov r0, #2
	pop {r4, pc}
	.align 2, 0
_021D86FC: .word 0x00000186
	thumb_func_end MOD76_021D86E4

	thumb_func_start MOD76_021D8700
MOD76_021D8700: ; 0x021D8700
	push {r4, lr}
	mov r1, #8
	add r4, r0, #0
	bl MOD76_021D853C
	mov r0, #6
	mov r1, #8
	lsl r0, r0, #6
	str r1, [r4, r0]
	ldr r0, [r4]
	mov r1, #1
	strb r1, [r0, #0x16]
	mov r0, #2
	pop {r4, pc}
	thumb_func_end MOD76_021D8700

	thumb_func_start MOD76_021D871C
MOD76_021D871C: ; 0x021D871C
	push {r4, lr}
	mov r1, #4
	add r4, r0, #0
	bl MOD76_021D853C
	ldr r1, _021D8734 ; =0x00000186
	mov r0, #2
	mov r2, #3
	strb r0, [r4, r1]
	lsl r1, r2, #7
	str r2, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_021D8734: .word 0x00000186
	thumb_func_end MOD76_021D871C

	thumb_func_start MOD76_021D8738
MOD76_021D8738: ; 0x021D8738
	push {r4, lr}
	mov r1, #5
	add r4, r0, #0
	bl MOD76_021D853C
	mov r1, #6
	lsl r0, r1, #6
	str r1, [r4, r0]
	mov r0, #2
	pop {r4, pc}
	thumb_func_end MOD76_021D8738

	thumb_func_start MOD76_021D874C
MOD76_021D874C: ; 0x021D874C
	mov r1, #6
	mov r2, #0xa
	lsl r1, r1, #6
	str r2, [r0, r1]
	mov r0, #0
	bx lr
	thumb_func_end MOD76_021D874C

	thumb_func_start MOD76_021D8758
MOD76_021D8758: ; 0x021D8758
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	ldr r3, _021D87EC ; =0x021D8E70
	add r2, sp, #0x34
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, #0x40
	mov r1, #0x43
	bl FUN_0201C24C
	mov r0, #0x43
	bl FUN_0200BB14
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl FUN_0200BB34
	mov r7, #0x45
	lsl r7, r7, #2
	add r2, sp, #0x14
	ldr r3, _021D87F0 ; =0x021D8EDC
	str r0, [r4, r7]
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	ldr r5, _021D87F4 ; =0x021D8E5C
	stmia r2!, {r0, r1}
	add r3, sp, #0
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
	mov r2, #0xd
	bl FUN_0200BBF0
	sub r1, r7, #4
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	add r2, sp, #0x34
	bl FUN_0200BF60
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_021D87EC: .word MOD76_021D8E70
_021D87F0: .word MOD76_021D8EDC
_021D87F4: .word MOD76_021D8E5C
	thumb_func_end MOD76_021D8758

	thumb_func_start MOD76_021D87F8
MOD76_021D87F8: ; 0x021D87F8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0x46
	mov r4, #0
	add r5, r7, #0
	lsl r6, r6, #2
_021D8804:
	ldr r0, [r5, r6]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xd
	blo _021D8804
	mov r1, #0x11
	lsl r1, r1, #4
	ldr r0, [r7, r1]
	add r1, r1, #4
	ldr r1, [r7, r1]
	bl FUN_0200C398
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r0, [r7, r0]
	bl FUN_0200BD04
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD76_021D87F8

	thumb_func_start MOD76_021D882C
MOD76_021D882C: ; 0x021D882C
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #1
	mov r6, #0x46
	add r5, r0, #0
	mov r4, #0
	lsl r7, r7, #0xc
	lsl r6, r6, #2
_021D883A:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	add r1, r7, #0
	ldr r0, [r0]
	bl FUN_020201E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0xd
	blo _021D883A
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD76_021D882C

	thumb_func_start MOD76_021D8854
MOD76_021D8854: ; 0x021D8854
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021D89D0 ; =0x0000B8A8
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #5
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021D89D4 ; =0x0000B8A9
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #8
	bl FUN_0200C00C
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _021D89D8 ; =0x0000B8AA
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #2
	bl FUN_0200C00C
	ldr r4, _021D89DC ; =0x0000B8AC
	mov r7, #0x45
	lsl r7, r7, #2
	add r6, r4, #6
_021D88BC:
	mov r0, #0x11
	str r4, [sp]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r1, [r5, r7]
	mov r2, #1
	mov r3, #0
	bl FUN_0206E130
	add r4, r4, #1
	cmp r4, r6
	bls _021D88BC
	ldr r0, _021D89E0 ; =0x0000B8AB
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #1
	mov r3, #0
	bl FUN_0206E2AC
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _021D89D0 ; =0x0000B8A8
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #9
	bl FUN_0200C06C
	mov r1, #0x11
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	ldr r3, _021D89D4 ; =0x0000B8A9
	mov r2, #1
	bl FUN_0206E164
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D89D0 ; =0x0000B8A8
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #4
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D89D4 ; =0x0000B8A9
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #7
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D89D8 ; =0x0000B8AA
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #1
	bl FUN_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D89D0 ; =0x0000B8A8
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #3
	bl FUN_0200C13C
	mov r0, #0
	str r0, [sp]
	ldr r0, _021D89D4 ; =0x0000B8A9
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	mov r3, #6
	bl FUN_0200C13C
	mov r3, #0
	mov r1, #0x11
	ldr r0, _021D89D8 ; =0x0000B8AA
	str r3, [sp]
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x71
	bl FUN_0200C13C
	mov r1, #0x11
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r2, _021D89E0 ; =0x0000B8AB
	ldr r1, [r5, r1]
	add r3, r2, #0
	bl FUN_0206E1D4
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D89D0: .word 0x0000B8A8
_021D89D4: .word 0x0000B8A9
_021D89D8: .word 0x0000B8AA
_021D89DC: .word 0x0000B8AC
_021D89E0: .word 0x0000B8AB
	thumb_func_end MOD76_021D8854

	thumb_func_start MOD76_021D89E4
MOD76_021D89E4: ; 0x021D89E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r2, #0
	ldrb r0, [r0, #0x14]
	cmp r0, #0
	bne _021D8A00
	add r0, r1, #0
	mov r1, #3
	bl GetWazaAttr
	add r6, r0, #0
	b _021D8A0C
_021D8A00:
	add r0, r1, #0
	mov r1, #0xb
	bl GetWazaAttr
	add r6, r0, #0
	add r6, #0x12
_021D8A0C:
	bl FUN_0206E12C
	add r7, r0, #0
	add r0, r6, #0
	bl FUN_0206E0F0
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r0, _021D8A54 ; =0x0000B8AC
	mov r1, #0x11
	add r0, r4, r0
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	add r2, r7, #0
	bl FUN_0200C9D8
	add r0, r6, #0
	bl FUN_0206E114
	add r1, r0, #0
	add r0, r4, #6
	lsl r0, r0, #2
	add r2, r5, r0
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	add r1, r1, #2
	bl FUN_0200C66C
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8A54: .word 0x0000B8AC
	thumb_func_end MOD76_021D89E4

	thumb_func_start MOD76_021D8A58
MOD76_021D8A58: ; 0x021D8A58
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	mov r7, #0x20
	add r5, r6, #0
_021D8A62:
	mov r0, #0x13
	lsl r0, r0, #4
	lsl r2, r7, #0x10
	ldr r0, [r5, r0]
	mov r1, #0x98
	asr r2, r2, #0x10
	bl FUN_0200C714
	ldr r0, [r6]
	mov r1, #0x61
	lsl r1, r1, #2
	ldrh r0, [r0, #0x12]
	ldrb r1, [r6, r1]
	add r0, r0, r4
	sub r1, r1, #1
	cmp r0, r1
	blo _021D8A92
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_0200C644
	b _021D8AB4
_021D8A92:
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_0200C644
	ldr r2, [r6]
	add r0, r6, #0
	ldr r1, [r2, #0xc]
	ldrh r2, [r2, #0x12]
	add r2, r2, r4
	lsl r2, r2, #1
	ldrh r1, [r1, r2]
	lsl r2, r4, #0x10
	lsr r2, r2, #0x10
	bl MOD76_021D89E4
_021D8AB4:
	add r4, r4, #1
	add r7, #0x10
	add r5, r5, #4
	cmp r4, #7
	blo _021D8A62
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD76_021D8A58

	thumb_func_start MOD76_021D8AC0
MOD76_021D8AC0: ; 0x021D8AC0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	str r2, [sp]
	cmp r1, r2
	bhs _021D8B30
	ldr r0, [sp]
	mov r6, #0
	add r0, r0, #6
	lsl r0, r0, #1
	add r4, r5, #0
	str r0, [sp, #4]
	add r7, sp, #0xc
_021D8ADA:
	mov r0, #0x13
	lsl r0, r0, #4
	add r1, sp, #0xc
	ldr r0, [r4, r0]
	add r1, #2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	mov r0, #0
	ldrsh r0, [r7, r0]
	cmp r0, #0x20
	bne _021D8B10
	mov r0, #0x80
	strh r0, [r7]
	ldr r0, [r5]
	ldr r1, [r0, #0xc]
	ldr r0, [sp, #4]
	ldrh r1, [r0, r1]
	ldr r0, _021D8BF4 ; =0x0000FFFF
	cmp r1, r0
	beq _021D8B14
	lsl r2, r6, #0x10
	add r0, r5, #0
	lsr r2, r2, #0x10
	bl MOD76_021D89E4
	b _021D8B14
_021D8B10:
	sub r0, #0x10
	strh r0, [r7]
_021D8B14:
	mov r0, #0x13
	mov r1, #2
	mov r2, #0
	lsl r0, r0, #4
	ldrsh r1, [r7, r1]
	ldrsh r2, [r7, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C714
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #7
	blo _021D8ADA
	b _021D8B94
_021D8B30:
	ldr r0, [sp]
	cmp r1, r0
	bls _021D8BF0
	lsl r0, r0, #1
	mov r6, #0
	add r4, r5, #0
	str r0, [sp, #8]
	add r7, sp, #0xc
_021D8B40:
	mov r0, #0x13
	lsl r0, r0, #4
	add r1, sp, #0xc
	ldr r0, [r4, r0]
	add r1, #2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	mov r0, #0
	ldrsh r0, [r7, r0]
	cmp r0, #0x80
	bne _021D8B76
	mov r0, #0x20
	strh r0, [r7]
	ldr r0, [r5]
	ldr r1, [r0, #0xc]
	ldr r0, [sp, #8]
	ldrh r1, [r0, r1]
	ldr r0, _021D8BF4 ; =0x0000FFFF
	cmp r1, r0
	beq _021D8B7A
	lsl r2, r6, #0x10
	add r0, r5, #0
	lsr r2, r2, #0x10
	bl MOD76_021D89E4
	b _021D8B7A
_021D8B76:
	add r0, #0x10
	strh r0, [r7]
_021D8B7A:
	mov r0, #0x13
	mov r1, #2
	mov r2, #0
	lsl r0, r0, #4
	ldrsh r1, [r7, r1]
	ldrsh r2, [r7, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C714
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #7
	blo _021D8B40
_021D8B94:
	mov r6, #0
	add r4, r5, #0
	add r7, sp, #0xc
_021D8B9A:
	mov r0, #0x13
	lsl r0, r0, #4
	add r1, sp, #0xc
	ldr r0, [r4, r0]
	add r1, #2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	mov r0, #0
	ldrsh r1, [r7, r0]
	sub r1, #0x20
	asr r0, r1, #3
	lsr r0, r0, #0x1c
	add r0, r1, r0
	asr r0, r0, #4
	strh r0, [r7]
	mov r0, #0
	ldrsh r1, [r7, r0]
	ldr r0, [sp]
	add r0, r0, r1
	mov r1, #0x61
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	sub r1, r1, #1
	cmp r0, r1
	blt _021D8BDC
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	b _021D8BE8
_021D8BDC:
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
_021D8BE8:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #7
	blo _021D8B9A
_021D8BF0:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8BF4: .word 0x0000FFFF
	thumb_func_end MOD76_021D8AC0

	thumb_func_start MOD76_021D8BF8
MOD76_021D8BF8: ; 0x021D8BF8
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, r1, #0
	mov r1, #1
	bl GetWazaAttr
	add r4, r0, #0
	bl FUN_0206E2A8
	add r6, r0, #0
	add r0, r4, #0
	bl FUN_0206E278
	add r3, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r0, _021D8C48 ; =0x0000B8AB
	mov r1, #0x11
	lsl r1, r1, #4
	str r0, [sp, #4]
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl FUN_0200C9D8
	add r0, r4, #0
	bl FUN_0206E290
	add r1, r0, #0
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r1, #2
	bl FUN_0200C66C
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_021D8C48: .word 0x0000B8AB
	thumb_func_end MOD76_021D8BF8

	thumb_func_start MOD76_021D8C4C
MOD76_021D8C4C: ; 0x021D8C4C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl MOD76_021D8758
	add r0, r6, #0
	bl MOD76_021D8854
	ldr r4, _021D8C84 ; =0x021D903C
	mov r7, #0
	add r5, r6, #0
_021D8C60:
	mov r0, #0x11
	mov r1, #0x45
	lsl r0, r0, #4
	lsl r1, r1, #2
	ldr r0, [r6, r0]
	ldr r1, [r6, r1]
	add r2, r4, #0
	bl FUN_0200C154
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r7, r7, #1
	add r4, #0x34
	add r5, r5, #4
	cmp r7, #0xd
	blo _021D8C60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8C84: .word MOD76_021D903C
	thumb_func_end MOD76_021D8C4C

	thumb_func_start MOD76_021D8C88
MOD76_021D8C88: ; 0x021D8C88
	push {r3, r4, r5, lr}
	add r3, r1, #0
	add r5, r0, #0
	add r4, r2, #0
	mov r0, #0x4a
	lsl r2, r3, #4
	lsl r0, r0, #2
	add r2, #0x20
	lsl r2, r2, #0x10
	ldr r0, [r5, r0]
	mov r1, #0xc4
	asr r2, r2, #0x10
	bl FUN_0200C714
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0200C66C
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD76_021D8C88

	thumb_func_start MOD76_021D8CB4
MOD76_021D8CB4: ; 0x021D8CB4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl FUN_0200C644
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0200C644
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD76_021D8CB4

	thumb_func_start MOD76_021D8CD4
MOD76_021D8CD4: ; 0x021D8CD4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldrh r0, [r0, #0x12]
	cmp r0, #0
	beq _021D8CEE
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
	b _021D8CFA
_021D8CEE:
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
_021D8CFA:
	ldr r0, [r4]
	ldrh r0, [r0, #0x12]
	add r2, r0, #7
	mov r0, #0x61
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	cmp r2, r1
	bge _021D8D16
	sub r0, #0x60
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_0200C644
	pop {r4, pc}
_021D8D16:
	sub r0, #0x60
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD76_021D8CD4

	thumb_func_start MOD76_021D8D24
MOD76_021D8D24: ; 0x021D8D24
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_0200C644
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD76_021D8D24

	thumb_func_start MOD76_021D8D44
MOD76_021D8D44: ; 0x021D8D44
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0x43
	bl FUN_02079A70
	mov r0, #6
	mov r1, #0xb
	lsl r0, r0, #6
	str r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD76_021D8D44

	thumb_func_start MOD76_021D8D5C
MOD76_021D8D5C: ; 0x021D8D5C
	push {r3, r4, lr}
	sub sp, #4
	ldr r2, _021D8DE4 ; =0x021D8E48
	add r1, sp, #0
	ldrb r3, [r2]
	add r4, r0, #0
	strb r3, [r1]
	ldrb r3, [r2, #1]
	ldrb r2, [r2, #2]
	strb r3, [r1, #1]
	strb r2, [r1, #2]
	bl MOD76_021D76B8
	ldr r0, [r4]
	mov r1, #0x53
	ldr r0, [r0]
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4]
	ldr r2, [r0, #8]
	add r0, r1, #4
	str r2, [r4, r0]
	add r0, r1, #0
	mov r2, #0
	add r0, #0x11
	strb r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x14
	strb r2, [r4, r0]
	mov r0, #1
	add r1, #0x13
	strb r0, [r4, r1]
	add r0, r4, #0
	bl MOD76_021D8514
	mov r1, #0x59
	lsl r1, r1, #2
	strh r0, [r4, r1]
	mov r2, #2
	sub r0, r1, #6
	strb r2, [r4, r0]
	add r0, r1, #0
	mov r2, #1
	add r0, #0x14
	str r2, [r4, r0]
	add r0, r1, #0
	mov r2, #0
	add r0, #0x10
	sub r1, #0x18
	str r2, [r4, r0]
	add r0, r4, r1
	add r1, sp, #0
	bl FUN_0207B000
	mov r1, #0x53
	lsl r1, r1, #2
	ldr r0, _021D8DE8 ; =UNK_020FA6E8
	add r1, r4, r1
	mov r2, #0x43
	bl OverlayManager_new
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xc
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D8DE4: .word MOD76_021D8E48
_021D8DE8: .word UNK_020FA6E8
	thumb_func_end MOD76_021D8D5C

	thumb_func_start MOD76_021D8DEC
MOD76_021D8DEC: ; 0x021D8DEC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl OverlayManager_Run
	cmp r0, #0
	beq _021D8E3E
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl OverlayManager_delete
	add r0, r4, #0
	bl MOD76_021D7638
	ldr r1, [r4]
	add r0, r4, #0
	ldrh r1, [r1, #0x10]
	mov r2, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD76_021D8C88
	add r0, r4, #0
	mov r1, #0
	bl MOD76_021D8CB4
	add r0, r4, #0
	bl MOD76_021D8D24
	ldr r0, _021D8E44 ; =0x00000162
	ldr r1, [r4]
	ldrb r2, [r4, r0]
	add r0, #0x1e
	strb r2, [r1, #0x17]
	mov r1, #7
	str r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
_021D8E3E:
	mov r0, #0xc
	pop {r4, pc}
	nop
_021D8E44: .word 0x00000162
	thumb_func_end MOD76_021D8DEC

	.rodata
	.global MOD76_021D8E48
MOD76_021D8E48: ; 0x021D8E48
	.byte 0x03, 0x05, 0x08, 0x00

	.global MOD76_021D8E4C
MOD76_021D8E4C: ; 0x021D8E4C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD76_021D8E5C
MOD76_021D8E5C: ; 0x021D8E5C
	.byte 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global MOD76_021D8E70
MOD76_021D8E70: ; 0x021D8E70
	.byte 0x0B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD76_021D8E88
MOD76_021D8E88: ; 0x021D8E88
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD76_021D8EA4
MOD76_021D8EA4: ; 0x021D8EA4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x1C, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD76_021D8EC0
MOD76_021D8EC0: ; 0x021D8EC0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD76_021D8EDC
MOD76_021D8EDC: ; 0x021D8EDC
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global MOD76_021D8EFC
MOD76_021D8EFC: ; 0x021D8EFC
	.word 0x00000000, MOD76_021D7FD0, MOD76_021D8008, 0x00000000
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x02, 0x00, 0x10, 0x20, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00

	.global MOD76_021D8F1C
MOD76_021D8F1C: ; 0x021D8F1C
	.word MOD76_021D860C

	.global MOD76_021D8F20
MOD76_021D8F20: ; 0x021D8F20
	.word MOD76_021D862C, MOD76_021D867C, MOD76_021D8688, MOD76_021D86D8
	.word MOD76_021D86E4, MOD76_021D8700, MOD76_021D871C, MOD76_021D8738
	.word MOD76_021D874C

	.global MOD76_021D8F44
MOD76_021D8F44: ; 0x021D8F44
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD76_021D8F6C
MOD76_021D8F6C: ; 0x021D8F6C
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00

	.global MOD76_021D8FC4
MOD76_021D8FC4: ; 0x021D8FC4
	.byte 0x01, 0x13, 0x00, 0x0B, 0x02, 0x0F, 0x28, 0x00, 0x01, 0x13, 0x00, 0x0B, 0x02, 0x0F, 0x3E, 0x00
	.byte 0x01, 0x01, 0x00, 0x06, 0x02, 0x0F, 0x54, 0x00, 0x01, 0x01, 0x02, 0x06, 0x02, 0x0F, 0x60, 0x00
	.byte 0x01, 0x01, 0x04, 0x08, 0x02, 0x0F, 0x6C, 0x00, 0x01, 0x01, 0x06, 0x03, 0x02, 0x0F, 0x7C, 0x00
	.byte 0x01, 0x02, 0x02, 0x0C, 0x02, 0x0F, 0x82, 0x00, 0x01, 0x0D, 0x02, 0x03, 0x02, 0x0F, 0x9A, 0x00
	.byte 0x01, 0x0D, 0x04, 0x03, 0x02, 0x0F, 0xA0, 0x00, 0x01, 0x0B, 0x06, 0x05, 0x02, 0x0F, 0xA6, 0x00
	.byte 0x01, 0x01, 0x08, 0x0F, 0x0A, 0x0F, 0xB0, 0x00, 0x01, 0x01, 0x09, 0x0F, 0x06, 0x0F, 0x46, 0x01
	.byte 0x00, 0x02, 0x13, 0x1B, 0x04, 0x0E, 0xA0, 0x01, 0x01, 0x15, 0x03, 0x0B, 0x0E, 0x0F, 0x0C, 0x02

	.global MOD76_021D9034
MOD76_021D9034: ; 0x021D9034
	.byte 0x00, 0x17, 0x0D, 0x07, 0x04, 0x0E, 0xA6, 0x02

	.global MOD76_021D903C
MOD76_021D903C: ; 0x021D903C
	.byte 0x92, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00
	.byte 0xA8, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xF6, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00
	.byte 0xA8, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xA9, 0xB8, 0x00, 0x00
	.byte 0xA8, 0xB8, 0x00, 0x00, 0xA9, 0xB8, 0x00, 0x00, 0xA9, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x00, 0x8C, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xA9, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xA9, 0xB8, 0x00, 0x00, 0xA9, 0xB8, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xC4, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xAA, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xAA, 0xB8, 0x00, 0x00
	.byte 0xAA, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x74, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00
	.byte 0xAB, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xAC, 0xB8, 0x00, 0x00
	.byte 0xA8, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x30, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xAD, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x98, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xAE, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00
	.byte 0xAB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xAF, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00
	.byte 0xAB, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xB0, 0xB8, 0x00, 0x00
	.byte 0xA8, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x70, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0xB1, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x98, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xB2, 0xB8, 0x00, 0x00, 0xA8, 0xB8, 0x00, 0x00, 0xAB, 0xB8, 0x00, 0x00
	.byte 0xAB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.data
	.bss
