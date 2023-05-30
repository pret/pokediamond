	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD60_021D74E0
MOD60_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl OverlayManager_GetField18
	mov r2, #1
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x26
	lsl r2, r2, #0x10
	bl CreateHeap
	mov r1, #0xad
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x26
	bl OverlayManager_CreateAndGetData
	mov r2, #0xad
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	add r0, r5, #0
	bl Options_GetTextSpeed
	ldrh r1, [r4, #0x18]
	mov r2, #0xf
	lsl r0, r0, #0x10
	bic r1, r2
	lsr r2, r0, #0x10
	mov r0, #0xf
	and r0, r2
	orr r0, r1
	strh r0, [r4, #0x18]
	add r0, r5, #0
	bl Options_GetBattleScene
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1f
	ldrh r1, [r4, #0x18]
	mov r2, #0x40
	lsr r0, r0, #0x19
	bic r1, r2
	orr r0, r1
	strh r0, [r4, #0x18]
	add r0, r5, #0
	bl Options_GetBattleStyle
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1f
	ldrh r1, [r4, #0x18]
	mov r2, #0x80
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strh r0, [r4, #0x18]
	add r0, r5, #0
	bl Options_GetSoundMethod
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1e
	ldrh r1, [r4, #0x18]
	mov r2, #0x30
	lsr r0, r0, #0x1a
	bic r1, r2
	orr r0, r1
	strh r0, [r4, #0x18]
	add r0, r5, #0
	bl Options_GetButtonMode
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1e
	ldrh r2, [r4, #0x18]
	ldr r1, _021D75A8 ; =0xFFFFFCFF
	lsr r0, r0, #0x16
	and r1, r2
	orr r0, r1
	strh r0, [r4, #0x18]
	add r0, r5, #0
	bl Options_GetFrame
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1b
	ldrh r2, [r4, #0x18]
	ldr r1, _021D75AC ; =0xFFFF83FF
	lsr r0, r0, #0x11
	and r1, r2
	orr r0, r1
	strh r0, [r4, #0x18]
	mov r0, #0x26
	str r0, [r4]
	str r5, [r4, #0x1c]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D75A8: .word 0xFFFFFCFF
_021D75AC: .word 0xFFFF83FF
	thumb_func_end MOD60_021D74E0

	thumb_func_start MOD60_021D75B0
MOD60_021D75B0: ; 0x021D75B0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	cmp r0, #1
	bne _021D7680
	ldrh r1, [r4, #0x18]
	mov r0, #0xf
	bic r1, r0
	add r0, r4, #0
	add r0, #0x5e
	ldrh r2, [r0]
	mov r0, #0xf
	and r2, r0
	orr r1, r2
	strh r1, [r4, #0x18]
	ldrh r1, [r4, #0x18]
	mov r2, #0x40
	add r0, #0xf7
	bic r1, r2
	add r2, r4, #0
	add r2, #0xb2
	ldrh r2, [r2]
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x19
	orr r1, r2
	strh r1, [r4, #0x18]
	ldrh r0, [r4, r0]
	ldrh r1, [r4, #0x18]
	mov r2, #0x80
	lsl r0, r0, #0x1f
	bic r1, r2
	lsr r0, r0, #0x18
	orr r0, r1
	strh r0, [r4, #0x18]
	ldrh r1, [r4, #0x18]
	mov r0, #0x30
	bic r1, r0
	ldr r0, _021D76AC ; =0x0000015A
	ldrh r2, [r4, r0]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1a
	orr r1, r2
	strh r1, [r4, #0x18]
	ldrh r2, [r4, #0x18]
	ldr r1, _021D76B0 ; =0xFFFFFCFF
	and r1, r2
	add r2, r0, #0
	add r2, #0x54
	ldrh r2, [r4, r2]
	add r0, #0xa8
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x16
	orr r1, r2
	strh r1, [r4, #0x18]
	ldrh r0, [r4, r0]
	ldrh r2, [r4, #0x18]
	ldr r1, _021D76B4 ; =0xFFFF83FF
	lsl r0, r0, #0x1b
	and r1, r2
	lsr r0, r0, #0x11
	orr r0, r1
	strh r0, [r4, #0x18]
	ldrh r1, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl Options_SetTextSpeed
	ldrh r1, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1f
	bl Options_SetBattleScene
	ldrh r1, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	bl Options_SetBattleStyle
	ldrh r1, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1e
	bl Options_SetSoundMethod
	ldrh r1, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	lsl r1, r1, #0x16
	lsr r1, r1, #0x1e
	bl Options_SetButtonMode
	ldrh r1, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1b
	bl Options_SetFrame
	b _021D769A
_021D7680:
	cmp r0, #2
	bne _021D769A
	ldrh r0, [r4, #0x18]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	bl GF_SndSetMonoFlag
	ldrh r1, [r4, #0x18]
	mov r0, #0
	lsl r1, r1, #0x16
	lsr r1, r1, #0x1e
	bl Options_SetButtonModeOnMain
_021D769A:
	add r0, r5, #0
	bl OverlayManager_FreeData
	ldr r0, [r4]
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021D76AC: .word 0x0000015A
_021D76B0: .word 0xFFFFFCFF
_021D76B4: .word 0xFFFF83FF
	thumb_func_end MOD60_021D75B0

	thumb_func_start MOD60_021D76B8
MOD60_021D76B8: ; 0x021D76B8
	push {r3, r4, lr}
	sub sp, #0xc
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #4
	bhi _021D77A0
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D76D4: ; jump table
	.short _021D76DE - _021D76D4 - 2 ; case 0
	.short _021D7706 - _021D76D4 - 2 ; case 1
	.short _021D7714 - _021D76D4 - 2 ; case 2
	.short _021D777E - _021D76D4 - 2 ; case 3
	.short _021D778C - _021D76D4 - 2 ; case 4
_021D76DE:
	bl MOD60_021D7834
	cmp r0, #0
	bne _021D76EC
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D76EC:
	mov r3, #0
	str r3, [r4, #0xc]
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	mov r0, #3
	bl FUN_0200E1D0
	b _021D77A0
_021D7706:
	bl FUN_0200E308
	cmp r0, #0
	bne _021D77A0
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D7714:
	ldr r0, _021D77AC ; =gMain
	mov r1, #1
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _021D773C
	ldr r1, [r4, #0x10]
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1d
	cmp r1, #6
	bne _021D773C
	ldr r0, _021D77B0 ; =0x0000061B
	bl PlaySE
	ldr r1, [r4, #0x10]
	mov r0, #3
	bic r1, r0
	mov r0, #1
	orr r0, r1
	str r0, [r4, #0x10]
	b _021D774E
_021D773C:
	mov r1, #2
	tst r0, r1
	beq _021D774E
	ldr r2, [r4, #0x10]
	mov r0, #3
	bic r2, r0
	add r0, r2, #0
	orr r0, r1
	str r0, [r4, #0x10]
_021D774E:
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	beq _021D7772
	mov r1, #0
	str r1, [r4, #0xc]
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	mov r0, #3
	add r3, r1, #0
	bl FUN_0200E1D0
	b _021D77A0
_021D7772:
	add r0, r4, #0
	bl MOD60_021D801C
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D777E:
	bl FUN_0200E308
	cmp r0, #0
	bne _021D77A0
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D778C:
	bl MOD60_021D78E8
	cmp r0, #0
	beq _021D779A
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, pc}
_021D779A:
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_021D77A0:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_021D77AC: .word gMain
_021D77B0: .word 0x0000061B
	thumb_func_end MOD60_021D76B8

	thumb_func_start MOD60_021D77B4
MOD60_021D77B4: ; 0x021D77B4
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D77D0 ; =0x021D8140
	add r3, sp, #0
	mov r2, #5
_021D77BE:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D77BE
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D77D0: .word MOD60_021D8140
	thumb_func_end MOD60_021D77B4

	thumb_func_start MOD60_021D77D4
MOD60_021D77D4: ; 0x021D77D4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0xa
	lsr r0, r0, #0x1f
	beq _021D7804
	ldr r2, _021D7824 ; =0x00000202
	mov r1, #1
	ldrh r0, [r4, r2]
	add r2, #0x39
	mov r3, #0xf
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4]
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	bl FUN_0200CD68
	ldr r1, [r4, #0x10]
	ldr r0, _021D7828 ; =0xFFDFFFFF
	and r0, r1
	str r0, [r4, #0x10]
_021D7804:
	bl FUN_0200BC30
	bl NNS_GfdDoVramTransfer
	ldr r0, [r4, #0x14]
	bl DoScheduledBgGpuUpdates
	ldr r3, _021D782C ; =0x027E0000
	ldr r1, _021D7830 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	add sp, #8
	pop {r4, pc}
	nop
_021D7824: .word 0x00000202
_021D7828: .word 0xFFDFFFFF
_021D782C: .word 0x027E0000
_021D7830: .word 0x00003FF8
	thumb_func_end MOD60_021D77D4

	thumb_func_start MOD60_021D7834
MOD60_021D7834: ; 0x021D7834
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	cmp r1, #0
	beq _021D7848
	cmp r1, #1
	beq _021D7888
	cmp r1, #2
	beq _021D78A2
	b _021D78D0
_021D7848:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D78DC ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D78E0 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	bl MOD60_021D77B4
	mov r0, #0
	bl FUN_0200E388
	mov r0, #1
	bl FUN_0200E388
	add r0, r4, #0
	bl MOD60_021D7990
	b _021D78D0
_021D7888:
	bl MOD60_021D7A40
	ldr r3, [r4]
	mov r0, #1
	mov r1, #0x1a
	mov r2, #0xce
	bl NewMsgDataFromNarc
	str r0, [r4, #0x20]
	add r0, r4, #0
	bl MOD60_021D7DF8
	b _021D78D0
_021D78A2:
	bl MOD60_021D7BA4
	add r0, r4, #0
	bl MOD60_021D7D18
	ldr r1, [r4]
	mov r0, #0x20
	bl FUN_0201C24C
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	bl FUN_02033F20
	ldr r0, _021D78E4 ; =MOD60_021D77D4
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0
	str r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
_021D78D0:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	mov r0, #0
	pop {r4, pc}
	nop
_021D78DC: .word 0xFFFFE0FF
_021D78E0: .word 0x04001000
_021D78E4: .word MOD60_021D77D4
	thumb_func_end MOD60_021D7834

	thumb_func_start MOD60_021D78E8
MOD60_021D78E8: ; 0x021D78E8
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _021D78F8
	cmp r0, #1
	beq _021D7946
	b _021D7978
_021D78F8:
	bl FUN_0201C29C
	ldr r0, [sp]
	bl MOD60_021D7CD4
	ldr r6, [sp]
	mov r7, #0
_021D7906:
	add r0, r6, #0
	add r0, #0x5c
	ldrh r0, [r0]
	mov r4, #0
	cmp r0, #0
	ble _021D7928
	add r5, r6, #0
_021D7914:
	ldr r0, [r5, #0x60]
	bl String_dtor
	add r0, r6, #0
	add r0, #0x5c
	ldrh r0, [r0]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _021D7914
_021D7928:
	add r7, r7, #1
	add r6, #0x54
	cmp r7, #7
	blt _021D7906
	ldr r0, [sp]
	ldr r0, [r0, #0x20]
	bl DestroyMsgData
	ldr r0, [sp]
	bl MOD60_021D7B98
	ldr r0, [sp]
	bl MOD60_021D7A14
	b _021D7978
_021D7946:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7988 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D798C ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	ldr r0, [sp]
	mov r1, #0
	str r1, [r0, #8]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D7978:
	ldr r0, [sp]
	ldr r0, [r0, #8]
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [r0, #8]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7988: .word 0xFFFFE0FF
_021D798C: .word 0x04001000
	thumb_func_end MOD60_021D78E8

	thumb_func_start MOD60_021D7990
MOD60_021D7990: ; 0x021D7990
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x80
	add r6, r0, #0
	ldr r0, [r6]
	bl BgConfig_Alloc
	add r3, sp, #0
	ldr r4, _021D7A08 ; =0x021D8114
	str r0, [r6, #0x14]
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r4, _021D7A0C ; =0x021D8168
	add r3, sp, #0x10
	mov r2, #0xe
_021D79B8:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D79B8
	ldr r5, _021D7A10 ; =0x021D8104
	mov r7, #0
	add r4, sp, #0x10
_021D79C6:
	ldr r1, [r5]
	ldr r0, [r6, #0x14]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r4, #0
	mov r3, #0
	bl InitBgFromTemplate
	ldr r1, [r5]
	ldr r0, [r6, #0x14]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl BgClearTilemapBufferAndCommit
	add r7, r7, #1
	add r4, #0x1c
	add r5, r5, #4
	cmp r7, #4
	blt _021D79C6
	mov r0, #0
	ldr r3, [r6]
	mov r1, #0x20
	add r2, r0, #0
	bl BG_ClearCharDataRange
	ldr r3, [r6]
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	add sp, #0x80
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7A08: .word MOD60_021D8114
_021D7A0C: .word MOD60_021D8168
_021D7A10: .word MOD60_021D8104
	thumb_func_end MOD60_021D7990

	thumb_func_start MOD60_021D7A14
MOD60_021D7A14: ; 0x021D7A14
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #4
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #0x14]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD60_021D7A14

	thumb_func_start MOD60_021D7A40
MOD60_021D7A40: ; 0x021D7A40
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r1, [r5]
	mov r0, #0x49
	bl NARC_ctor
	add r4, r0, #0
	mov r0, #0x49
	mov r1, #1
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r5]
	bl AllocFromHeapAtEnd
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #1
	add r2, r6, #0
	bl NARC_ReadWholeMember
	add r0, r6, #0
	add r1, sp, #0x20
	bl NNS_G2dGetUnpackedCharacterData
	ldr r3, [sp, #0x20]
	mov r1, #0
	str r1, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r5, #0x14]
	ldr r3, [r3, #0x10]
	bl BG_LoadCharTilesData
	ldr r3, [sp, #0x20]
	mov r0, #0
	str r0, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r5, #0x14]
	ldr r3, [r3, #0x10]
	mov r1, #4
	bl BG_LoadCharTilesData
	add r0, r6, #0
	bl FreeToHeap
	mov r0, #0x49
	mov r1, #0
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r5]
	bl AllocFromHeapAtEnd
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #0
	add r2, r6, #0
	bl NARC_ReadWholeMember
	add r0, r6, #0
	add r1, sp, #0x1c
	bl NNS_G2dGetUnpackedPaletteData
	ldr r1, [sp, #0x1c]
	mov r0, #0
	ldr r1, [r1, #0xc]
	mov r2, #0x20
	add r3, r0, #0
	bl BG_LoadPlttData
	ldr r1, [sp, #0x1c]
	mov r0, #4
	ldr r1, [r1, #0xc]
	mov r2, #0x20
	mov r3, #0
	bl BG_LoadPlttData
	add r0, r6, #0
	bl FreeToHeap
	mov r0, #0x49
	mov r1, #2
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0
	ldr r0, [r5]
	bl AllocFromHeap
	str r0, [r5, #0x24]
	ldr r2, [r5, #0x24]
	add r0, r4, #0
	mov r1, #2
	bl NARC_ReadWholeMember
	add r1, r5, #0
	ldr r0, [r5, #0x24]
	add r1, #0x28
	bl NNS_G2dGetUnpackedScreenData
	add r0, r4, #0
	bl NARC_dtor
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	mov r1, #2
	mov r2, #1
	bl FillBgTilemapRect
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x14]
	mov r1, #4
	mov r2, #1
	bl FillBgTilemapRect
	ldr r0, [r5, #0x28]
	mov r1, #0x20
	str r1, [sp]
	mov r1, #2
	str r1, [sp, #4]
	add r1, r0, #0
	add r1, #0xc
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	ldrh r2, [r0]
	add r3, r1, #0
	lsl r2, r2, #0x15
	lsr r2, r2, #0x18
	str r2, [sp, #0x14]
	ldrh r0, [r0, #2]
	add r2, r1, #0
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [r5, #0x14]
	bl CopyRectToBgTilemapRect
	mov r2, #3
	add r3, r2, #0
	ldr r0, [r5, #0x14]
	mov r1, #0
	sub r3, #0x1b
	bl BgSetPosTextAndCommit
	ldr r0, [r5, #0x14]
	mov r1, #2
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, [r5, #0x14]
	mov r1, #0
	bl ScheduleBgTilemapBufferTransfer
	ldr r0, [r5, #0x14]
	mov r1, #4
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD60_021D7A40

	thumb_func_start MOD60_021D7B98
MOD60_021D7B98: ; 0x021D7B98
	ldr r3, _021D7BA0 ; =FreeToHeap
	ldr r0, [r0, #0x24]
	bx r3
	nop
_021D7BA0: .word FreeToHeap
	thumb_func_end MOD60_021D7B98

	thumb_func_start MOD60_021D7BA4
MOD60_021D7BA4: ; 0x021D7BA4
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xa
	str r0, [sp, #0x10]
	add r1, r4, #0
	mov r2, #1
	ldr r0, [r4, #0x14]
	add r1, #0x2c
	add r3, r2, #0
	bl AddWindowParameterized
	mov r0, #3
	str r0, [sp]
	mov r0, #0x1e
	str r0, [sp, #4]
	mov r0, #0xe
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x22
	str r0, [sp, #0x10]
	add r1, r4, #0
	mov r2, #1
	ldr r0, [r4, #0x14]
	add r1, #0x3c
	add r3, r2, #0
	bl AddWindowParameterized
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _021D7CC8 ; =0x000001C6
	add r1, r4, #0
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x14]
	add r1, #0x4c
	mov r2, #1
	mov r3, #2
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4]
	ldr r2, _021D7CCC ; =0x00000232
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	mov r1, #1
	mov r3, #0xe
	bl LoadUserFrameGfx1
	ldrh r0, [r4, #0x18]
	ldr r2, _021D7CD0 ; =0x0000023B
	mov r1, #1
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1b
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4]
	mov r3, #0xf
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	bl FUN_0200CD68
	mov r1, #0x1a
	ldr r2, [r4]
	mov r0, #0
	lsl r1, r1, #4
	bl LoadFontPal0
	mov r1, #0x1a
	ldr r2, [r4]
	mov r0, #4
	lsl r1, r1, #4
	bl LoadFontPal0
	mov r1, #6
	ldr r2, [r4]
	mov r0, #0
	lsl r1, r1, #6
	bl FUN_02002EEC
	mov r1, #6
	ldr r2, [r4]
	mov r0, #4
	lsl r1, r1, #6
	bl FUN_02002EEC
	add r0, r4, #0
	add r0, #0x2c
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r0, #0x3c
	mov r1, #0xff
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r0, #0x4c
	mov r1, #0xff
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r0, #0x4c
	bl ClearWindowTilemap
	add r0, r4, #0
	add r0, #0x3c
	bl ClearWindowTilemap
	add r0, r4, #0
	add r0, #0x2c
	bl ClearWindowTilemap
	add r0, r4, #0
	ldr r2, _021D7CCC ; =0x00000232
	add r0, #0x3c
	mov r1, #1
	mov r3, #0xe
	bl DrawFrameAndWindow1
	add r4, #0x4c
	ldr r2, _021D7CD0 ; =0x0000023B
	add r0, r4, #0
	mov r1, #1
	mov r3, #0xf
	bl DrawFrameAndWindow2
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_021D7CC8: .word 0x000001C6
_021D7CCC: .word 0x00000232
_021D7CD0: .word 0x0000023B
	thumb_func_end MOD60_021D7BA4

	thumb_func_start MOD60_021D7CD4
MOD60_021D7CD4: ; 0x021D7CD4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0x3c
	mov r1, #0
	bl ClearFrameAndWindow1
	add r0, r5, #0
	add r0, #0x4c
	mov r1, #0
	bl ClearFrameAndWindow2
	mov r6, #0
	add r5, #0x2c
	add r7, r6, #0
_021D7CF0:
	lsl r4, r6, #4
	add r0, r5, r4
	bl ClearWindowTilemapAndCopyToVram
	add r0, r5, r4
	add r1, r7, #0
	bl FillWindowPixelBuffer
	add r0, r5, r4
	bl ClearWindowTilemap
	add r0, r5, r4
	bl RemoveWindow
	add r0, r6, #1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #3
	blo _021D7CF0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD60_021D7CD4

	thumb_func_start MOD60_021D7D18
MOD60_021D7D18: ; 0x021D7D18
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	ldr r1, [r6]
	mov r0, #0x28
	bl String_ctor
	add r5, r0, #0
	ldr r0, [r6, #0x20]
	mov r1, #0
	add r2, r5, #0
	bl ReadMsgDataIntoString
	mov r3, #2
	str r3, [sp]
	mov r1, #0
	ldr r0, _021D7DEC ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0x2c
	add r2, r5, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl StringSetEmpty
	ldr r1, _021D7DF0 ; =gGameVersion
	ldr r0, [r6, #0x20]
	ldrb r1, [r1]
	add r2, r5, #0
	sub r1, #9
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D7DF4 ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	str r1, [sp, #0xc]
	add r0, #0x4c
	mov r1, #1
	add r2, r5, #0
	mov r3, #4
	bl AddTextPrinterParameterized2
	add r7, r6, #0
	mov r4, #0
	add r7, #0x3c
_021D7D7E:
	add r0, r5, #0
	bl StringSetEmpty
	ldr r0, [r6, #0x20]
	add r1, r4, #3
	add r2, r5, #0
	bl ReadMsgDataIntoString
	lsl r0, r4, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D7DF4 ; =0x0001020F
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r7, #0
	add r2, r5, #0
	mov r3, #4
	bl AddTextPrinterParameterized2
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #7
	blo _021D7D7E
	mov r4, #0
_021D7DB6:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD60_021D7EA4
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #7
	blo _021D7DB6
	add r0, r6, #0
	add r0, #0x2c
	bl CopyWindowToVram
	add r0, r6, #0
	add r0, #0x3c
	bl CopyWindowToVram
	add r6, #0x4c
	add r0, r6, #0
	bl CopyWindowToVram
	add r0, r5, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7DEC: .word 0x00010200
_021D7DF0: .word gGameVersion
_021D7DF4: .word 0x0001020F
	thumb_func_end MOD60_021D7D18

	thumb_func_start MOD60_021D7DF8
MOD60_021D7DF8: ; 0x021D7DF8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r5, #0
	add r6, r0, #0
	str r5, [sp, #4]
_021D7E02:
	ldr r0, [sp, #4]
	ldr r2, [sp, #4]
	lsl r7, r0, #2
	ldr r0, _021D7E9C ; =0x021D8124
	mov r1, #0x54
	mul r1, r2
	add r1, r6, r1
	str r1, [sp]
	ldr r0, [r0, r7]
	add r1, #0x5c
	mov r4, #0
	strh r0, [r1]
	cmp r0, #0
	ble _021D7E44
_021D7E1E:
	add r0, r5, #1
	lsl r0, r0, #0x10
	add r1, r5, #0
	lsr r5, r0, #0x10
	ldr r0, [r6, #0x20]
	add r1, #0xa
	bl NewString_ReadMsgData
	ldr r1, [sp]
	lsl r2, r4, #2
	add r1, r1, r2
	str r0, [r1, #0x60]
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, _021D7E9C ; =0x021D8124
	ldr r0, [r0, r7]
	cmp r4, r0
	blt _021D7E1E
_021D7E44:
	ldr r0, [sp, #4]
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	cmp r0, #7
	blo _021D7E02
	ldrh r0, [r6, #0x18]
	lsl r0, r0, #0x1c
	lsr r1, r0, #0x1c
	add r0, r6, #0
	add r0, #0x5e
	strh r1, [r0]
	ldrh r0, [r6, #0x18]
	lsl r0, r0, #0x19
	lsr r1, r0, #0x1f
	add r0, r6, #0
	add r0, #0xb2
	strh r1, [r0]
	ldrh r0, [r6, #0x18]
	ldr r1, _021D7EA0 ; =0x00000106
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	strh r0, [r6, r1]
	ldrh r0, [r6, #0x18]
	lsl r0, r0, #0x1a
	lsr r2, r0, #0x1e
	add r0, r1, #0
	add r0, #0x54
	strh r2, [r6, r0]
	ldrh r0, [r6, #0x18]
	lsl r0, r0, #0x16
	lsr r2, r0, #0x1e
	add r0, r1, #0
	add r0, #0xa8
	strh r2, [r6, r0]
	ldrh r0, [r6, #0x18]
	add r1, #0xfc
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1b
	strh r0, [r6, r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7E9C: .word MOD60_021D8124
_021D7EA0: .word 0x00000106
	thumb_func_end MOD60_021D7DF8

	thumb_func_start MOD60_021D7EA4
MOD60_021D7EA4: ; 0x021D7EA4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x10]
	lsl r0, r1, #4
	str r0, [sp, #0x18]
	mov r0, #6
	str r1, [sp, #0x14]
	lsl r0, r0, #6
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r3, _021D8010 ; =0x021D80FC
	ldr r2, [sp, #0x14]
	ldr r0, [sp, #0x10]
	ldrsb r2, [r3, r2]
	ldr r3, [sp, #0x18]
	add r0, #0x3c
	add r2, #0x64
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	mov r1, #0xff
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
	ldr r0, [sp, #0x14]
	cmp r0, #5
	bne _021D7F26
	add r2, r0, #0
	ldr r0, [sp, #0x18]
	mov r1, #0x54
	str r0, [sp]
	mov r0, #0xff
	mul r2, r1
	ldr r3, [sp, #0x10]
	str r0, [sp, #4]
	ldr r0, _021D8014 ; =0x0003040F
	add r3, r3, r2
	str r0, [sp, #8]
	mov r1, #0
	add r2, r3, #0
	ldr r0, [sp, #0x10]
	str r1, [sp, #0xc]
	add r2, #0x5e
	ldrh r2, [r2]
	add r0, #0x3c
	lsl r2, r2, #2
	add r2, r3, r2
	ldr r2, [r2, #0x60]
	mov r3, #0x94
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	add r0, #0x3c
	bl CopyWindowToVram
	ldr r0, [sp, #0x10]
	ldr r1, [r0, #0x10]
	mov r0, #2
	lsl r0, r0, #0x14
	orr r1, r0
	ldr r0, [sp, #0x10]
	add sp, #0x24
	str r1, [r0, #0x10]
	pop {r4, r5, r6, r7, pc}
_021D7F26:
	cmp r0, #3
	bne _021D7F3C
	mov r1, #0x54
	mul r1, r0
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	add r0, #0x5e
	ldrh r0, [r0]
	bl GF_SndSetMonoFlag
	b _021D7F54
_021D7F3C:
	cmp r0, #4
	bne _021D7F54
	ldr r1, [sp, #0x14]
	mov r2, #0x54
	mul r2, r1
	ldr r1, [sp, #0x10]
	mov r0, #0
	add r1, r1, r2
	add r1, #0x5e
	ldrh r1, [r1]
	bl Options_SetButtonModeOnMain
_021D7F54:
	ldr r0, [sp, #0x14]
	mov r1, #0x54
	mul r1, r0
	ldr r0, [sp, #0x10]
	mov r7, #0
	add r5, r0, r1
	add r0, r5, #0
	add r0, #0x5c
	ldrh r0, [r0]
	add r4, r7, #0
	cmp r0, #0
	bls _021D8002
	bls _021D8002
	ldr r1, _021D8010 ; =0x021D80FC
	ldr r0, [sp, #0x14]
	add r0, r1, r0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	str r0, [sp, #0x20]
	add r0, #0x3c
	str r0, [sp, #0x20]
_021D7F7E:
	add r0, r5, #0
	add r0, #0x5e
	ldrh r0, [r0]
	cmp r4, r0
	bne _021D7F8C
	ldr r0, _021D8014 ; =0x0003040F
	b _021D7F8E
_021D7F8C:
	ldr r0, _021D8018 ; =0x0001020F
_021D7F8E:
	ldr r1, [sp, #0x14]
	cmp r1, #4
	bne _021D7FC8
	lsl r1, r4, #2
	add r6, r5, r1
	ldr r1, [sp, #0x18]
	add r3, r7, #0
	str r1, [sp]
	mov r1, #0xff
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x20]
	ldr r2, [r6, #0x60]
	mov r1, #0
	add r3, #0x64
	bl AddTextPrinterParameterized2
	mov r0, #0
	ldr r1, [r6, #0x60]
	add r2, r0, #0
	bl FUN_02002E14
	add r0, #0xc
	add r0, r7, r0
	lsl r0, r0, #0x18
	asr r7, r0, #0x18
	b _021D7FF2
_021D7FC8:
	ldr r1, [sp, #0x18]
	lsl r2, r4, #2
	str r1, [sp]
	mov r1, #0xff
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0
	str r0, [sp, #0xc]
	add r2, r5, r2
	ldr r6, [sp, #0x1c]
	add r3, r1, #0
	ldrsb r6, [r6, r3]
	mov r3, #0x30
	mul r3, r4
	add r3, #0x64
	ldr r0, [sp, #0x20]
	ldr r2, [r2, #0x60]
	add r3, r6, r3
	bl AddTextPrinterParameterized2
_021D7FF2:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r5, #0
	add r0, #0x5c
	ldrh r0, [r0]
	cmp r4, r0
	blo _021D7F7E
_021D8002:
	ldr r0, [sp, #0x10]
	add r0, #0x3c
	str r0, [sp, #0x10]
	bl CopyWindowToVram
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8010: .word MOD60_021D80FC
_021D8014: .word 0x0003040F
_021D8018: .word 0x0001020F
	thumb_func_end MOD60_021D7EA4

	thumb_func_start MOD60_021D801C
MOD60_021D801C: ; 0x021D801C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r1, r5, #0
	lsl r0, r0, #0x1b
	lsr r2, r0, #0x1d
	mov r0, #0x54
	add r1, #0x5c
	mul r0, r2
	add r4, r1, r0
	cmp r2, #6
	beq _021D8080
	ldr r0, _021D80F8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x10
	tst r0, r1
	beq _021D805C
	ldrh r0, [r4, #2]
	ldrh r1, [r4]
	add r0, r0, #1
	bl _s32_div_f
	strh r1, [r4, #2]
	ldr r1, [r5, #0x10]
	add r0, r5, #0
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1d
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl MOD60_021D7EA4
	b _021D8080
_021D805C:
	mov r0, #0x20
	tst r0, r1
	beq _021D8080
	ldrh r1, [r4]
	ldrh r0, [r4, #2]
	add r0, r0, r1
	sub r0, r0, #1
	bl _s32_div_f
	strh r1, [r4, #2]
	ldr r1, [r5, #0x10]
	add r0, r5, #0
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1d
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl MOD60_021D7EA4
_021D8080:
	ldr r0, _021D80F8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x40
	tst r0, r1
	beq _021D80BE
	ldr r0, [r5, #0x10]
	mov r1, #7
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1d
	add r0, r0, #6
	bl _u32_div_f
	ldr r2, [r5, #0x10]
	mov r0, #0x1c
	bic r2, r0
	lsl r0, r1, #0x1d
	add r3, r2, #0
	lsr r0, r0, #0x1b
	orr r3, r0
	str r3, [r5, #0x10]
	lsl r3, r3, #0x1b
	lsr r3, r3, #0x1d
	lsl r3, r3, #4
	add r3, #0x18
	ldr r0, [r5, #0x14]
	mov r1, #0
	mov r2, #3
	neg r3, r3
	bl ScheduleSetBgPosText
	pop {r3, r4, r5, pc}
_021D80BE:
	mov r0, #0x80
	tst r0, r1
	beq _021D80F6
	ldr r0, [r5, #0x10]
	mov r1, #7
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1d
	add r0, r0, #1
	bl _u32_div_f
	ldr r2, [r5, #0x10]
	mov r0, #0x1c
	bic r2, r0
	lsl r0, r1, #0x1d
	add r3, r2, #0
	lsr r0, r0, #0x1b
	orr r3, r0
	str r3, [r5, #0x10]
	lsl r3, r3, #0x1b
	lsr r3, r3, #0x1d
	lsl r3, r3, #4
	add r3, #0x18
	ldr r0, [r5, #0x14]
	mov r1, #0
	mov r2, #3
	neg r3, r3
	bl ScheduleSetBgPosText
_021D80F6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D80F8: .word gMain
	thumb_func_end MOD60_021D801C

	.rodata
	.global MOD60_021D80FC
MOD60_021D80FC: ; 0x021D80FC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD60_021D8104
MOD60_021D8104: ; 0x021D8104
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00

	.global MOD60_021D8114
MOD60_021D8114: ; 0x021D8114
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD60_021D8124
MOD60_021D8124: ; 0x021D8124
	.byte 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD60_021D8140
MOD60_021D8140: ; 0x021D8140
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD60_021D8168
MOD60_021D8168: ; 0x021D8168
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1E, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.bss
