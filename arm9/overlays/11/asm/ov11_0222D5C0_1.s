	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_0222D5C0
ov11_0222D5C0: ; 0x0222D5C0
	push {r4, r5, r6, lr}
	sub sp, #0x28
	add r4, r1, #0
	add r6, r0, #0
	bl OverlayManager_GetField18
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0xf
	bhi _0222D6D2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222D5E0: ; jump table
	.short _0222D600 - _0222D5E0 - 2 ; case 0
	.short _0222D620 - _0222D5E0 - 2 ; case 1
	.short _0222D65A - _0222D5E0 - 2 ; case 2
	.short _0222D670 - _0222D5E0 - 2 ; case 3
	.short _0222D686 - _0222D5E0 - 2 ; case 4
	.short _0222D696 - _0222D5E0 - 2 ; case 5
	.short _0222D6AC - _0222D5E0 - 2 ; case 6
	.short _0222D6C8 - _0222D5E0 - 2 ; case 7
	.short _0222D6DA - _0222D5E0 - 2 ; case 8
	.short _0222D6EE - _0222D5E0 - 2 ; case 9
	.short _0222D704 - _0222D5E0 - 2 ; case 10
	.short _0222D720 - _0222D5E0 - 2 ; case 11
	.short _0222D742 - _0222D5E0 - 2 ; case 12
	.short _0222D752 - _0222D5E0 - 2 ; case 13
	.short _0222D7C2 - _0222D5E0 - 2 ; case 14
	.short _0222D7E4 - _0222D5E0 - 2 ; case 15
_0222D600:
	mov r2, #0xb
	mov r0, #3
	mov r1, #5
	lsl r2, r2, #0x10
	bl CreateHeap
	ldr r1, [r5]
	mov r0, #4
	tst r0, r1
	beq _0222D61A
	mov r0, #1
	str r0, [r4]
	b _0222D7EA
_0222D61A:
	mov r0, #3
	str r0, [r4]
	b _0222D7EA
_0222D620:
	add r0, r6, #0
	add r1, r5, #0
	bl ov11_0222F29C
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02033778
	bl sub_02033590
	cmp r0, #0
	bne _0222D648
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x14
	bl GameStats_Inc
	b _0222D654
_0222D648:
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x19
	bl GameStats_Inc
_0222D654:
	mov r0, #2
	str r0, [r4]
	b _0222D7EA
_0222D65A:
	add r0, r6, #0
	bl ov11_0222F4E4
	cmp r0, #1
	bne _0222D6D2
	add r0, r6, #0
	bl ov11_0222F93C
	mov r0, #3
	str r0, [r4]
	b _0222D7EA
_0222D670:
	add r0, r6, #0
	bl ov11_0222F988
	cmp r0, #1
	bne _0222D680
	mov r0, #4
	str r0, [r4]
	b _0222D7EA
_0222D680:
	mov r0, #5
	str r0, [r4]
	b _0222D7EA
_0222D686:
	add r0, r6, #0
	bl ov11_0222FABC
	cmp r0, #1
	bne _0222D6D2
	mov r0, #5
	str r0, [r4]
	b _0222D7EA
_0222D696:
	add r0, r6, #0
	bl ov11_0222FB04
	cmp r0, #1
	bne _0222D6A6
	mov r0, #6
	str r0, [r4]
	b _0222D7EA
_0222D6A6:
	mov r0, #8
	str r0, [r4]
	b _0222D7EA
_0222D6AC:
	add r0, r6, #0
	bl ov11_0222FC38
	cmp r0, #1
	bne _0222D6D2
	ldr r0, _0222D7F0 ; =SDK_OVERLAY_OVERLAY_07_ID
	bl UnloadOverlayByID
	mov r0, #7
	str r0, [r4]
	mov r0, #0x3d
	bl sub_02031588
	b _0222D7EA
_0222D6C8:
	mov r0, #0x3d
	bl sub_020315D8
	cmp r0, #0
	bne _0222D6D4
_0222D6D2:
	b _0222D7EA
_0222D6D4:
	mov r0, #8
	str r0, [r4]
	b _0222D7EA
_0222D6DA:
	ldr r0, _0222D7F4 ; =SDK_OVERLAY_OVERLAY_08_ID
	mov r1, #2
	bl HandleLoadOverlay
	add r0, r6, #0
	bl ov11_0222DB50
	mov r0, #9
	str r0, [r4]
	b _0222D7EA
_0222D6EE:
	add r0, r6, #0
	bl ov11_0222DF4C
	cmp r0, #1
	bne _0222D7EA
	add r0, r6, #0
	bl ov11_0222DFA4
	mov r0, #0xa
	str r0, [r4]
	b _0222D7EA
_0222D704:
	add r0, r6, #0
	bl ov11_0222FC80
	cmp r0, #1
	bne _0222D714
	mov r0, #0xb
	str r0, [r4]
	b _0222D7EA
_0222D714:
	mov r0, #5
	bl DestroyHeap
	mov r0, #0xd
	str r0, [r4]
	b _0222D7EA
_0222D720:
	add r0, r6, #0
	bl ov11_0222FE58
	cmp r0, #1
	bne _0222D7EA
	ldr r0, _0222D7F0 ; =SDK_OVERLAY_OVERLAY_07_ID
	bl UnloadOverlayByID
	mov r0, #5
	bl DestroyHeap
	mov r0, #0x3e
	bl sub_02031588
	mov r0, #0xc
	str r0, [r4]
	b _0222D7EA
_0222D742:
	mov r0, #0x3e
	bl sub_020315D8
	cmp r0, #0
	beq _0222D7EA
	mov r0, #0xf
	str r0, [r4]
	b _0222D7EA
_0222D752:
	add r1, sp, #0x24
	add r2, sp, #0x20
	bl ov11_02230D38
	add r6, r0, #0
	beq _0222D7BC
	mov r0, #3
	mov r1, #0x49
	lsl r2, r0, #0x10
	bl CreateHeap
	ldr r0, [r5, #4]
	ldr r1, [sp, #0x24]
	bl GetPartyMonByIndex
	add r1, r0, #0
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r2, [r5, r0]
	mov r3, #0x49
	str r2, [sp]
	add r2, r0, #0
	sub r2, #0x58
	ldr r2, [r5, r2]
	str r2, [sp, #4]
	add r2, r0, #0
	sub r2, #0x60
	ldr r2, [r5, r2]
	str r2, [sp, #8]
	add r2, r0, #0
	sub r2, #0x24
	ldr r2, [r5, r2]
	sub r0, #0x40
	str r2, [sp, #0xc]
	ldr r0, [r5, r0]
	add r2, r6, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x20]
	str r0, [sp, #0x14]
	mov r0, #3
	str r0, [sp, #0x18]
	str r3, [sp, #0x1c]
	add r3, #0xe7
	ldr r0, [r5, #4]
	ldr r3, [r5, r3]
	bl sub_0206C700
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0xe
	str r0, [r4]
	b _0222D7EA
_0222D7BC:
	mov r0, #0xf
	str r0, [r4]
	b _0222D7EA
_0222D7C2:
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r5, [r5, r0]
	add r0, r5, #0
	bl sub_0206C91C
	cmp r0, #1
	bne _0222D7EA
	add r0, r5, #0
	bl sub_0206C92C
	mov r0, #0x49
	bl DestroyHeap
	mov r0, #0xd
	str r0, [r4]
	b _0222D7EA
_0222D7E4:
	add sp, #0x28
	mov r0, #1
	pop {r4, r5, r6, pc}
_0222D7EA:
	mov r0, #0
	add sp, #0x28
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222D7F0: .word SDK_OVERLAY_OVERLAY_07_ID
_0222D7F4: .word SDK_OVERLAY_OVERLAY_08_ID

	thumb_func_start ov11_0222D7F8
ov11_0222D7F8: ; 0x0222D7F8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov11_02258658
	ldr r0, [r4, #4]
	bl ov11_022584AC
	ldr r1, _0222D834 ; =0x000023FB
	mov r0, #4
	ldrb r2, [r4, r1]
	orr r0, r2
	strb r0, [r4, r1]
	mov r0, #2
	bl sub_02002CF8
	add r0, r4, #0
	mov r1, #3
	bl ov11_02231338
	ldr r0, _0222D838 ; =SDK_OVERLAY_OVERLAY_08_ID
	bl UnloadOverlayByID
	ldr r0, _0222D83C ; =SDK_OVERLAY_OVERLAY_09_ID
	mov r1, #2
	bl HandleLoadOverlay
	pop {r4, pc}
	.align 2, 0
_0222D834: .word 0x000023FB
_0222D838: .word SDK_OVERLAY_OVERLAY_08_ID
_0222D83C: .word SDK_OVERLAY_OVERLAY_09_ID

	thumb_func_start ov11_0222D840
ov11_0222D840: ; 0x0222D840
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov11_02258658
	ldr r0, [r4, #8]
	bl RemoveWindow
	ldr r0, [r4, #4]
	bl ov11_0222E4E8
	add r0, r4, #0
	bl ov11_0222E51C
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x90
	add r1, #0x94
	ldr r0, [r0]
	ldr r1, [r1]
	bl sub_0200C398
	add r4, #0x90
	ldr r0, [r4]
	bl sub_0200BD04
	bl sub_0201C29C
	mov r0, #2
	bl sub_02002CF8
	pop {r4, pc}

	thumb_func_start ov11_0222D88C
ov11_0222D88C: ; 0x0222D88C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, _0222D938 ; =SDK_OVERLAY_OVERLAY_09_ID
	bl UnloadOverlayByID
	ldr r0, _0222D93C ; =SDK_OVERLAY_OVERLAY_08_ID
	mov r1, #2
	bl HandleLoadOverlay
	add r0, r4, #0
	mov r1, #0
	bl ov11_02231338
	bl sub_02022300
	add r5, r0, #0
	bl sub_020222F8
	add r1, r0, #0
	mov r0, #0
	add r2, r5, #0
	bl MIi_CpuClear16
	bl sub_02031190
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_0223021C
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_022584D4
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #2
	mov r1, #5
	bl sub_02002C50
	ldr r1, _0222D940 ; =0x000023FB
	mov r0, #2
	ldrb r2, [r4, r1]
	orr r0, r2
	strb r0, [r4, r1]
	ldr r0, [r4, #4]
	bl ov11_02258450
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov11_022586BC
	mov r0, #0x67
	lsl r0, r0, #2
	mov r1, #0
	ldr r0, [r4, r0]
	mov r2, #1
	add r3, r1, #0
	bl ov11_02258820
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov11_02258958
	mov r0, #1
	bl sub_02002840
	add r0, r4, #0
	bl ov11_0222FE94
	add r4, #0x90
	ldr r0, [r4]
	bl sub_0200BB68
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #0x10
	bl sub_02008D24
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222D938: .word SDK_OVERLAY_OVERLAY_09_ID
_0222D93C: .word SDK_OVERLAY_OVERLAY_08_ID
_0222D940: .word 0x000023FB

	thumb_func_start ov11_0222D944
ov11_0222D944: ; 0x0222D944
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl RemoveWindow
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #4]
	mov r1, #1
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #4]
	mov r1, #2
	bl FreeBgTilemapBuffer
	ldr r0, [r4, #4]
	mov r1, #3
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl ov11_02231410
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_0222D980
ov11_0222D980: ; 0x0222D980
	push {r4, r5, r6, lr}
	sub sp, #0x68
	ldr r1, _0222DB38 ; =0x000023FB
	add r5, r0, #0
	ldrb r2, [r5, r1]
	mov r0, #1
	ldr r4, _0222DB3C ; =ov11_0225DAE0
	bic r2, r0
	mov r0, #1
	orr r0, r2
	strb r0, [r5, r1]
	add r3, sp, #0x14
	mov r2, #0xa
_0222D99A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222D99A
	ldr r0, [r4]
	mov r1, #1
	str r0, [r3]
	ldr r0, [r5, #4]
	add r2, sp, #0x14
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r5, #4]
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	ldr r0, [r5, #4]
	mov r1, #2
	add r2, sp, #0x30
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r5, #4]
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	ldr r0, [r5, #4]
	mov r1, #3
	add r2, sp, #0x4c
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r5, #4]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	ldr r1, _0222DB40 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r2, r0
	strh r2, [r1]
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	add r0, r5, #0
	bl ov11_02230E44
	add r4, r0, #0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r1, #1
	ldr r0, [r5, #4]
	add r2, r1, #0
	mov r3, #0xa
	bl sub_0200D274
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	mov r1, #9
	lsl r1, r1, #0xa
	ldr r1, [r5, r1]
	ldr r2, [r5, #4]
	mov r0, #7
	add r1, r1, #3
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	add r0, r5, #0
	bl ov11_02230C68
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r3, #9
	str r0, [sp, #8]
	lsl r3, r3, #0xa
	ldr r6, [r5, r3]
	ldr r0, [r5, #0x28]
	lsl r3, r6, #1
	add r3, r6, r3
	add r3, #0x9e
	add r2, r3, r2
	mov r1, #7
	mov r3, #5
	bl PaletteData_LoadNarc
	add r0, r4, #0
	bl sub_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xa0
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	mov r1, #0x26
	mov r3, #5
	bl PaletteData_LoadNarc
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xb0
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	mov r1, #0xe
	mov r2, #7
	mov r3, #5
	bl PaletteData_LoadNarc
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #7
	mov r1, #2
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _0222DB44 ; =0xFFFF1FFF
	ldr r3, _0222DB48 ; =0x04001000
	and r2, r1
	str r2, [r0]
	ldr r2, [r3]
	and r1, r2
	add r2, r0, #0
	str r1, [r3]
	add r2, #0x48
	ldrh r3, [r2]
	mov r1, #0x3f
	add r0, #0x4a
	bic r3, r1
	strh r3, [r2]
	ldrh r2, [r0]
	bic r2, r1
	strh r2, [r0]
	bl GX_BothDispOn
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	ldr r0, _0222DB4C ; =ov11_0222F01C
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	ldr r0, _0222DB38 ; =0x000023FB
	mov r3, #2
	ldrb r1, [r5, r0]
	mov r2, #1
	orr r1, r3
	strb r1, [r5, r0]
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	ldr r1, [r5, #8]
	bl AddWindowParameterized
	ldr r0, [r5, #8]
	mov r1, #0xff
	bl FillWindowPixelBuffer
	ldr r0, [r5, #8]
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl DrawFrameAndWindow2
	add r0, r5, #0
	bl ov11_0222FE94
	add sp, #0x68
	pop {r4, r5, r6, pc}
	nop
_0222DB38: .word 0x000023FB
_0222DB3C: .word ov11_0225DAE0
_0222DB40: .word 0x04000008
_0222DB44: .word 0xFFFF1FFF
_0222DB48: .word 0x04001000
_0222DB4C: .word ov11_0222F01C

	thumb_func_start ov11_0222DB50
ov11_0222DB50: ; 0x0222DB50
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	bl OverlayManager_GetData
	add r4, r0, #0
	bl sub_020222F0
	add r5, r0, #0
	bl sub_020222E8
	add r1, r0, #0
	mov r0, #0
	add r2, r5, #0
	bl MIi_CpuClear16
	bl sub_02022300
	add r5, r0, #0
	bl sub_020222F8
	add r1, r0, #0
	mov r0, #0
	add r2, r5, #0
	bl MIi_CpuClear16
	bl GetLCRNGSeed
	ldr r1, _0222DF0C ; =0x00002430
	str r0, [r4, r1]
	add r0, sp, #0x20
	add r1, sp, #0x14
	bl GF_RTC_CopyDateTime
	ldr r0, _0222DF10 ; =gSystem
	ldr r6, [sp, #0x24]
	ldr r5, [r0, #0x2c]
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	lsl r6, r6, #8
	add r0, r1, r0
	lsl r3, r0, #0x18
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x20]
	lsl r2, r0, #0x10
	ldr r0, [sp, #0x28]
	mul r6, r0
	lsl r0, r6, #0x10
	add r0, r1, r0
	add r0, r2, r0
	add r0, r3, r0
	add r0, r5, r0
	bl SetLCRNGSeed
	bl ov11_0222EF30
	str r0, [r4]
	bl sub_02015F1C
	mov r0, #2
	mov r1, #5
	bl sub_02002C50
	mov r0, #0xe
	mov r1, #1
	mov r2, #0xf
	mov r3, #5
	bl MessagePrinter_New
	mov r1, #0x6a
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r2, [r4, r1]
	add r0, r1, #4
	str r2, [r4, r0]
	mov r0, #5
	bl sub_02002FD0
	str r0, [r4, #0x28]
	mov r1, #1
	bl sub_020038F0
	mov r2, #2
	ldr r0, [r4, #0x28]
	mov r1, #0
	lsl r2, r2, #8
	mov r3, #5
	bl PaletteData_AllocBuffers
	mov r1, #1
	ldr r0, [r4, #0x28]
	lsl r2, r1, #9
	mov r3, #5
	bl PaletteData_AllocBuffers
	mov r2, #7
	ldr r0, [r4, #0x28]
	mov r1, #2
	lsl r2, r2, #6
	mov r3, #5
	bl PaletteData_AllocBuffers
	mov r2, #2
	ldr r0, [r4, #0x28]
	mov r1, #3
	lsl r2, r2, #8
	mov r3, #5
	bl PaletteData_AllocBuffers
	mov r0, #5
	bl BgConfig_Alloc
	str r0, [r4, #4]
	mov r0, #5
	mov r1, #3
	bl AllocWindows
	mov r7, #0x73
	str r0, [r4, #8]
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_0222DC42:
	mov r1, #0x32
	mov r0, #5
	lsl r1, r1, #6
	bl AllocFromHeap
	str r0, [r5, r7]
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #4
	blt _0222DC42
	mov r0, #0x40
	mov r1, #5
	bl sub_0201C24C
	bl sub_02031190
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_0223021C
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_022584D4
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, [r4, #4]
	add r0, r4, #0
	bl ov11_0222E264
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	ldr r1, [r4, #8]
	mov r2, #1
	mov r3, #2
	bl AddWindowParameterized
	ldr r0, [r4, #8]
	mov r1, #0xff
	bl FillWindowPixelBuffer
	ldr r0, [r4, #8]
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl DrawFrameAndWindow2
	mov r0, #5
	bl sub_0200BB14
	add r1, r4, #0
	add r1, #0x90
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	ldr r1, _0222DF14 ; =ov11_0225DA20
	ldr r2, _0222DF18 ; =ov11_0225D9D8
	mov r3, #0x20
	bl sub_0200BB6C
	ldr r1, _0222DF1C ; =0x00100010
	mov r0, #1
	bl sub_02008D44
	mov r0, #1
	bl sub_02008DDC
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl sub_0200BB34
	add r1, r4, #0
	add r1, #0x94
	str r0, [r1]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x90
	add r1, #0x94
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x80
	bl sub_0200BBF0
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x90
	add r1, #0x94
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, _0222DF20 ; =ov11_0225D9EC
	bl sub_0200BF60
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl sub_0200BB68
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #0x10
	bl sub_02008D24
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov11_022586BC
	mov r0, #0x67
	lsl r0, r0, #2
	mov r1, #0
	ldr r0, [r4, r0]
	mov r2, #1
	add r3, r1, #0
	bl ov11_02258820
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov11_02258958
	mov r0, #5
	bl sub_02006D98
	add r1, r4, #0
	add r1, #0x88
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0
	mov r2, #0xc0
	bl sub_020081B4
	add r0, r4, #0
	bl ov11_02231390
	bl ov11_0222EFDC
	mov r0, #5
	bl ov08_02211F5C
	add r1, r4, #0
	add r1, #0x8c
	str r0, [r1]
	add r0, r4, #0
	bl ov11_0222E470
	bl sub_0201CC08
	mov r0, #4
	bl sub_0201CC24
	mov r2, #0x51
	mov r0, #1
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #5
	bl NewMsgDataFromNarc
	str r0, [r4, #0xc]
	mov r0, #1
	mov r1, #0x1a
	mov r2, #0
	mov r3, #5
	bl NewMsgDataFromNarc
	str r0, [r4, #0x10]
	mov r0, #5
	bl MessageFormat_New
	str r0, [r4, #0x14]
	mov r0, #5
	lsl r0, r0, #6
	mov r1, #5
	bl String_New
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl PaletteData_GetUnfadedBuf
	ldr r1, _0222DF24 ; =0x00002224
	mov r2, #0xe0
	add r1, r4, r1
	bl MIi_CpuCopy16
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl PaletteData_GetUnfadedBuf
	ldr r1, _0222DF28 ; =0x00002304
	mov r2, #0xe0
	add r1, r4, r1
	bl MIi_CpuCopy16
	add r0, r4, #0
	bl ov11_02230C68
	mov r1, #0
	lsl r5, r0, #2
	mov r3, #9
	str r1, [sp]
	mov r0, #0x70
	str r0, [sp, #4]
	lsl r3, r3, #0xa
	ldr r3, [r4, r3]
	mov r6, #0xc
	mul r6, r3
	ldr r3, _0222DF2C ; =ov11_0225DB88
	ldr r0, [r4, #0x28]
	add r3, r3, r6
	ldr r3, [r5, r3]
	mov r2, #2
	lsl r3, r3, #0x10
	lsr r3, r3, #0x10
	bl PaletteData_FillPalette
	mov r0, #0xc0
	str r0, [sp]
	add r0, #0x40
	mov r3, #9
	str r0, [sp, #4]
	lsl r3, r3, #0xa
	ldr r3, [r4, r3]
	mov r6, #0xc
	mul r6, r3
	ldr r3, _0222DF2C ; =ov11_0225DB88
	ldr r0, [r4, #0x28]
	add r3, r3, r6
	ldr r3, [r5, r3]
	mov r1, #0
	lsl r3, r3, #0x10
	mov r2, #2
	lsr r3, r3, #0x10
	bl PaletteData_FillPalette
	mov r0, #0
	str r0, [sp]
	mov r0, #0xdf
	mov r3, #9
	str r0, [sp, #4]
	lsl r3, r3, #0xa
	mov r1, #2
	ldr r3, [r4, r3]
	mov r6, #0xc
	mul r6, r3
	ldr r3, _0222DF2C ; =ov11_0225DB88
	ldr r0, [r4, #0x28]
	add r3, r3, r6
	ldr r3, [r5, r3]
	add r2, r1, #0
	lsl r3, r3, #0x10
	lsr r3, r3, #0x10
	bl PaletteData_FillPalette
	mov r1, #0
	mov r0, #0xa0
	str r0, [sp]
	mov r0, #0xc0
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	add r3, r1, #0
	bl PaletteData_FillPalette
	mov r2, #0
	str r2, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	ldr r3, _0222DF30 ; =0x0000FFFF
	mov r1, #1
	bl PaletteData_FillPalette
	mov r2, #0
	str r2, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	ldr r3, _0222DF30 ; =0x0000FFFF
	mov r1, #3
	bl PaletteData_FillPalette
	ldr r0, [r4, #0x28]
	mov r1, #0
	mov r2, #0xb
	mov r3, #5
	bl sub_020142EC
	mov r1, #0x1b
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl sub_020143A8
	ldr r0, _0222DF34 ; =ov11_0222F100
	ldr r2, _0222DF38 ; =0x0000EA60
	add r1, r4, #0
	bl sub_0200CA44
	str r0, [r4, #0x1c]
	ldr r0, _0222DF3C ; =ov11_0222F144
	ldr r2, _0222DF40 ; =0x0000C350
	add r1, r4, #0
	bl sub_0200CA44
	str r0, [r4, #0x20]
	mov r2, #0x4b
	ldr r0, _0222DF44 ; =ov11_0222F254
	add r1, r4, #0
	lsl r2, r2, #4
	bl sub_0200CA60
	str r0, [r4, #0x24]
	mov r1, #0x32
	ldr r0, _0222DF48 ; =0x00002434
	mvn r1, r1
	str r1, [r4, r0]
	add r0, r4, #0
	bl ov11_0222FE94
	add r0, r4, #0
	bl ov11_02230218
	bl BagCursor_Battle_Init
	mov r0, #5
	mov r1, #4
	mov r2, #0
	bl sub_02014BF4
	mov r1, #0x71
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #2
	mov r1, #5
	bl sub_0201C328
	mov r1, #0x72
	lsl r1, r1, #2
	str r0, [r4, r1]
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222DF0C: .word 0x00002430
_0222DF10: .word gSystem
_0222DF14: .word ov11_0225DA20
_0222DF18: .word ov11_0225D9D8
_0222DF1C: .word 0x00100010
_0222DF20: .word ov11_0225D9EC
_0222DF24: .word 0x00002224
_0222DF28: .word 0x00002304
_0222DF2C: .word ov11_0225DB88
_0222DF30: .word 0x0000FFFF
_0222DF34: .word ov11_0222F100
_0222DF38: .word 0x0000EA60
_0222DF3C: .word ov11_0222F144
_0222DF40: .word 0x0000C350
_0222DF44: .word ov11_0222F254
_0222DF48: .word 0x00002434

	thumb_func_start ov11_0222DF4C
ov11_0222DF4C: ; 0x0222DF4C
	push {r4, r5, r6, lr}
	bl OverlayManager_GetData
	ldr r1, _0222DF9C ; =0x000023F8
	add r4, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0
	beq _0222DF7A
	ldr r2, [r4, #0x2c]
	mov r1, #4
	tst r1, r2
	ldr r1, [r4, #0x30]
	beq _0222DF6C
	bl ov11_0223D238
	b _0222DF7A
_0222DF6C:
	bl ov11_0223D238
	ldr r1, _0222DFA0 ; =0x000023FA
	strb r0, [r4, r1]
	add r0, r4, #0
	bl ov11_02254820
_0222DF7A:
	ldr r0, [r4, #0x44]
	mov r6, #0
	cmp r0, #0
	ble _0222DF96
	add r5, r4, #0
_0222DF84:
	ldr r1, [r5, #0x34]
	add r0, r4, #0
	bl ov11_0224CB38
	ldr r0, [r4, #0x44]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r0
	blt _0222DF84
_0222DF96:
	ldr r0, _0222DFA0 ; =0x000023FA
	ldrb r0, [r4, r0]
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222DF9C: .word 0x000023F8
_0222DFA0: .word 0x000023FA

	thumb_func_start ov11_0222DFA4
ov11_0222DFA4: ; 0x0222DFA4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r7, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl sub_0200E3A0
	mov r0, #1
	mov r1, #0
	bl sub_0200E3A0
	add r0, r4, #0
	bl ov11_02230EC8
	ldr r0, _0222E248 ; =0x0000241C
	ldrb r0, [r4, r0]
	cmp r0, #4
	beq _0222DFE4
	ldr r0, [r4, #0x6c]
	mov r1, #0
	bl GetPartyMonByIndex
	add r1, r0, #0
	add r0, r4, #0
	bl ov11_02230FA8
_0222DFE4:
	mov r0, #0
	str r0, [sp]
	add r6, r7, #0
	add r5, r4, #0
_0222DFEC:
	ldr r0, [r5, #0x68]
	ldr r1, [r6, #4]
	bl CopyPlayerParty
	ldr r0, [r5, #0x68]
	bl FreeToHeap
	add r1, r6, #0
	add r1, #0xf8
	ldr r0, [r5, #0x48]
	ldr r1, [r1]
	bl PlayerProfile_Copy
	ldr r0, [r5, #0x48]
	bl FreeToHeap
	ldr r0, [sp]
	add r6, r6, #4
	add r0, r0, #1
	add r5, r5, #4
	str r0, [sp]
	cmp r0, #4
	blt _0222DFEC
	mov r0, #0x1b
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl sub_020143D0
	mov r1, #0x42
	lsl r1, r1, #2
	ldr r0, [r4, #0x58]
	ldr r1, [r7, r1]
	bl Save_Bag_Copy
	ldr r0, [r4, #0x58]
	bl FreeToHeap
	mov r1, #0x11
	lsl r1, r1, #4
	ldr r0, [r4, #0x60]
	ldr r1, [r7, r1]
	bl Save_Pokedex_Copy
	ldr r0, [r4, #0x60]
	bl FreeToHeap
	mov r0, #0x45
	ldr r1, [r4, #0x64]
	lsl r0, r0, #2
	str r1, [r7, r0]
	add r1, r0, #0
	ldr r2, [r4, #0x5c]
	sub r1, #8
	str r2, [r7, r1]
	add r1, r4, #0
	add r1, #0x98
	ldr r2, [r1]
	add r1, r0, #0
	add r1, #0x14
	str r2, [r7, r1]
	add r1, r4, #0
	add r1, #0x9c
	ldr r2, [r1]
	add r1, r0, #0
	add r1, #0x20
	str r2, [r7, r1]
	add r1, r0, #0
	ldr r2, _0222E24C ; =0x00002410
	add r1, #0x7c
	ldr r3, [r4, r2]
	add r0, #0x5c
	str r3, [r7, r1]
	add r1, r2, #0
	add r1, #0xc
	ldrb r3, [r4, r1]
	mov r1, #0x3f
	add r2, #0x28
	and r1, r3
	str r1, [r7, #0x14]
	ldr r1, [r4, r2]
	mov r2, #4
	str r1, [r7, r0]
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r3, #0
	bl ov11_0224C474
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r7, r1]
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r2, #3
	mov r3, #0
	bl ov11_0224C474
	mov r1, #0x4e
	lsl r1, r1, #2
	ldr r2, [r7, r1]
	mov r3, #0
	add r0, r2, r0
	str r0, [r7, r1]
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r2, #6
	bl ov11_0224C474
	add r5, r0, #0
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r2, #6
	mov r3, #2
	bl ov11_0224C474
	mov r1, #0x4f
	lsl r1, r1, #2
	ldr r2, [r7, r1]
	add r0, r5, r0
	add r0, r2, r0
	str r0, [r7, r1]
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r2, #7
	mov r3, #0
	bl ov11_0224C474
	add r5, r0, #0
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r2, #7
	mov r3, #2
	bl ov11_0224C474
	mov r1, #5
	lsl r1, r1, #6
	ldr r2, [r7, r1]
	add r0, r5, r0
	add r0, r2, r0
	str r0, [r7, r1]
	add r7, r1, #0
	mov r6, #0
	add r5, r4, #0
	add r7, #0x8c
_0222E10A:
	ldr r0, [r5, r7]
	bl FreeToHeap
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #4
	blt _0222E10A
	ldr r0, [r4, #0x18]
	bl FreeToHeap
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl PaletteData_FreeBuffers
	ldr r0, [r4, #0x28]
	mov r1, #1
	bl PaletteData_FreeBuffers
	ldr r0, [r4, #0x28]
	mov r1, #2
	bl PaletteData_FreeBuffers
	ldr r0, [r4, #0x28]
	mov r1, #3
	bl PaletteData_FreeBuffers
	ldr r0, [r4, #0x28]
	bl sub_02002FEC
	ldr r0, [r4, #0xc]
	bl DestroyMsgData
	ldr r0, [r4, #0x10]
	bl DestroyMsgData
	ldr r0, [r4, #0x14]
	bl MessageFormat_Delete
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_02014C28
	bl sub_02012EAC
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl ov08_02212024
	ldr r0, [r4, #0x30]
	bl ov11_0223D284
	ldr r0, [r4, #0x44]
	mov r6, #0
	cmp r0, #0
	ble _0222E194
	ldr r7, _0222E250 ; =0x000023F9
	add r5, r4, #0
_0222E180:
	ldrb r2, [r4, r7]
	ldr r1, [r5, #0x34]
	add r0, r4, #0
	bl ov11_0224CB54
	ldr r0, [r4, #0x44]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r0
	blt _0222E180
_0222E194:
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	bl sub_020072E8
	ldr r0, _0222E250 ; =0x000023F9
	ldrb r0, [r4, r0]
	cmp r0, #2
	beq _0222E1AC
	add r0, r4, #0
	bl ov11_0222D840
_0222E1AC:
	mov r0, #0
	bl TextFlags_SetCanABSpeedUpPrint
	mov r0, #0
	bl sub_02002B7C
	mov r0, #0
	bl sub_02002BB8
	ldr r0, [r4, #8]
	mov r1, #3
	bl WindowArray_Delete
	ldr r0, [r4, #4]
	bl FreeToHeap
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MessagePrinter_Delete
	mov r0, #2
	bl sub_02002CF8
	ldr r0, [r4, #0x1c]
	bl sub_0200CAB4
	ldr r0, [r4, #0x20]
	bl sub_0200CAB4
	bl sub_0201CD04
	ldr r0, [r4]
	bl ov11_0222EFD4
	ldr r0, _0222E254 ; =0x00002430
	ldr r0, [r4, r0]
	bl SetLCRNGSeed
	add r0, r4, #0
	bl ov11_02231474
	cmp r0, #0
	beq _0222E220
	ldr r0, _0222E258 ; =0x00000704
	mov r1, #0
	bl sub_020054F0
_0222E220:
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_0201C350
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, _0222E25C ; =SDK_OVERLAY_OVERLAY_08_ID
	bl UnloadOverlayByID
	bl sub_02033590
	cmp r0, #0
	bne _0222E244
	ldr r0, _0222E260 ; =SDK_OVERLAY_OVERLAY_16_ID
	bl UnloadOverlayByID
_0222E244:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E248: .word 0x0000241C
_0222E24C: .word 0x00002410
_0222E250: .word 0x000023F9
_0222E254: .word 0x00002430
_0222E258: .word 0x00000704
_0222E25C: .word SDK_OVERLAY_OVERLAY_08_ID
_0222E260: .word SDK_OVERLAY_OVERLAY_16_ID

	thumb_func_start ov11_0222E264
ov11_0222E264: ; 0x0222E264
	push {r4, r5, r6, r7, lr}
	sub sp, #0x9c
	add r5, r0, #0
	add r4, r1, #0
	bl GX_DisableEngineALayers
	mov r0, #0
	bl SetMasterBrightnessNeutral
	mov r0, #1
	bl SetMasterBrightnessNeutral
	ldr r6, _0222E450 ; =ov11_0225DA68
	add r3, sp, #0x20
	mov r2, #5
_0222E282:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E282
	add r0, sp, #0x20
	bl GX_SetBanks
	mov r1, #6
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #1
	mov r0, #0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #2
	mov r0, #0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	ldr r6, _0222E454 ; =ov11_0225D9A8
	add r3, sp, #0x10
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r1, _0222E458 ; =0x000023FB
	mov r0, #1
	ldrb r2, [r5, r1]
	ldr r6, _0222E45C ; =ov11_0225DB34
	add r3, sp, #0x48
	bic r2, r0
	mov r0, #1
	orr r0, r2
	strb r0, [r5, r1]
	mov r2, #0xa
_0222E2F0:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E2F0
	ldr r0, [r6]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	add r2, sp, #0x48
	mov r3, #0
	bl InitBgFromTemplate
	add r0, r4, #0
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	add r0, r4, #0
	mov r1, #2
	add r2, sp, #0x64
	mov r3, #0
	bl InitBgFromTemplate
	add r0, r4, #0
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	add r0, r4, #0
	mov r1, #3
	add r2, sp, #0x80
	mov r3, #0
	bl InitBgFromTemplate
	add r0, r4, #0
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	ldr r1, _0222E460 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r2, r0
	strh r2, [r1]
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	bl ov11_02258450
	add r0, r5, #0
	bl ov11_02230E44
	add r7, r0, #0
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #5
	mov r1, #1
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0xa
	bl sub_0200D274
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #5
	mov r1, #9
	str r0, [sp, #0xc]
	lsl r1, r1, #0xa
	ldr r1, [r5, r1]
	mov r0, #7
	add r1, r1, #3
	add r2, r4, #0
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	add r0, r5, #0
	bl ov11_02230C68
	add r6, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r2, #9
	str r0, [sp, #8]
	lsl r2, r2, #0xa
	ldr r3, [r5, r2]
	ldr r0, [r5, #0x28]
	lsl r2, r3, #1
	add r2, r3, r2
	add r2, #0x9e
	mov r1, #7
	add r2, r2, r6
	mov r3, #5
	bl PaletteData_LoadNarc
	add r0, r7, #0
	bl sub_0200CD64
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xa0
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	mov r1, #0x26
	mov r3, #5
	bl PaletteData_LoadNarc
	mov r0, #0
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0xb0
	str r0, [sp, #8]
	ldr r0, [r5, #0x28]
	mov r1, #0xe
	mov r2, #7
	mov r3, #5
	bl PaletteData_LoadNarc
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #5
	str r0, [sp, #0xc]
	mov r0, #7
	mov r1, #2
	add r2, r4, #0
	mov r3, #3
	bl GfGfxLoader_LoadScrnData
	mov r0, #1
	lsl r0, r0, #0x1a
	ldr r2, [r0]
	ldr r1, _0222E464 ; =0xFFFF1FFF
	ldr r3, _0222E468 ; =0x04001000
	and r2, r1
	str r2, [r0]
	ldr r2, [r3]
	and r1, r2
	add r2, r0, #0
	str r1, [r3]
	add r2, #0x48
	ldrh r3, [r2]
	mov r1, #0x3f
	add r0, #0x4a
	bic r3, r1
	strh r3, [r2]
	ldrh r2, [r0]
	bic r2, r1
	strh r2, [r0]
	bl GX_BothDispOn
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	ldr r0, _0222E46C ; =ov11_0222F01C
	add r1, r5, #0
	bl Main_SetVBlankIntrCB
	add sp, #0x9c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222E450: .word ov11_0225DA68
_0222E454: .word ov11_0225D9A8
_0222E458: .word 0x000023FB
_0222E45C: .word ov11_0225DB34
_0222E460: .word 0x04000008
_0222E464: .word 0xFFFF1FFF
_0222E468: .word 0x04001000
_0222E46C: .word ov11_0222F01C

	thumb_func_start ov11_0222E470
ov11_0222E470: ; 0x0222E470
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl ov11_02230294
	add r4, r0, #0
	mov r0, #0x5f
	lsl r0, r0, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #0
	add r3, r4, #0
	bl ov11_022583D8
	mov r0, #0x63
	lsl r0, r0, #2
	add r0, r5, r0
	add r1, r5, #0
	mov r2, #1
	add r3, r4, #0
	bl ov11_022583D8
	add r0, r5, #0
	bl ov11_0222FF78
	str r0, [sp]
	ldr r0, [r5, #0x44]
	mov r4, #0
	cmp r0, #0
	ble _0222E4E2
	add r6, r5, #0
_0222E4AC:
	ldr r1, [sp]
	add r0, r5, #0
	mov r2, #2
	add r3, r4, #0
	bl ov11_0224C474
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_02230014
	mov r1, #0x9a
	mov r2, #0
	bl GetMonData
	add r2, r0, #0
	ldr r1, [r6, #0x34]
	add r0, r5, #0
	add r3, r7, #0
	bl ov11_0224CA94
	ldr r0, [r5, #0x44]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, r0
	blt _0222E4AC
_0222E4E2:
	bl sub_02033E74
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_0222E4E8
ov11_0222E4E8: ; 0x0222E4E8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	mov r1, #1
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #2
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #3
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl ov11_022584AC
	pop {r4, pc}

	thumb_func_start ov11_0222E51C
ov11_0222E51C: ; 0x0222E51C
	bx lr
	.align 2, 0

	thumb_func_start ov11_0222E520
ov11_0222E520: ; 0x0222E520
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r0, #0
	ldr r0, [r1]
	str r1, [sp, #4]
	str r0, [r4, #0x2c]
	mov r7, #0
	add r6, r4, #0
	add r5, r1, #0
_0222E532:
	mov r0, #5
	bl PlayerProfile_New
	add r1, r0, #0
	add r0, r5, #0
	str r1, [r6, #0x48]
	add r0, #0xf8
	ldr r0, [r0]
	bl PlayerProfile_Copy
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r7, r7, #1
	str r0, [r6, #0x78]
	add r6, r6, #4
	add r5, r5, #4
	cmp r7, #4
	blt _0222E532
	mov r0, #5
	bl Save_Bag_New
	str r0, [r4, #0x58]
	mov r1, #0x42
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	ldr r1, [r4, #0x58]
	bl Save_Bag_Copy
	mov r0, #5
	bl Save_Pokedex_New
	str r0, [r4, #0x60]
	mov r1, #0x11
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	ldr r1, [r4, #0x60]
	bl Save_Pokedex_Copy
	mov r1, #0x45
	lsl r1, r1, #2
	ldr r0, [sp, #4]
	add r2, r1, #0
	ldr r0, [r0, r1]
	add r3, r1, #0
	str r0, [r4, #0x64]
	ldr r0, [sp, #4]
	add r2, #0x1c
	ldr r2, [r0, r2]
	add r0, r1, #0
	add r0, #0xa0
	str r2, [r4, r0]
	add r2, r1, #0
	ldr r0, [sp, #4]
	add r2, #0x38
	ldr r2, [r0, r2]
	add r0, r1, #0
	add r0, #0xa4
	str r2, [r4, r0]
	add r2, r1, #0
	ldr r0, [sp, #4]
	sub r2, #8
	ldr r0, [r0, r2]
	add r2, r1, #0
	str r0, [r4, #0x5c]
	ldr r0, [sp, #4]
	add r2, #0x14
	ldr r2, [r0, r2]
	add r0, r4, #0
	add r0, #0x98
	str r2, [r0]
	add r2, r1, #0
	ldr r0, [sp, #4]
	add r2, #0x50
	ldr r2, [r0, r2]
	ldr r0, _0222E8BC ; =0x00002420
	add r3, #0x20
	str r2, [r4, r0]
	ldr r2, [sp, #4]
	ldr r3, [r2, r3]
	add r2, r4, #0
	add r2, #0x9c
	str r3, [r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x7c
	ldr r3, [r2, r3]
	add r2, r0, #0
	sub r2, #0x10
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x40
	ldr r3, [r2, r3]
	add r2, r0, #0
	sub r2, #0x24
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x3c
	ldr r3, [r2, r3]
	add r2, r0, #0
	sub r2, #0x20
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x44
	ldr r3, [r2, r3]
	add r2, r0, #0
	sub r2, #0x1c
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x4c
	ldr r3, [r2, r3]
	add r2, r0, #0
	sub r2, #0x14
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x78
	ldr r3, [r2, r3]
	add r2, r0, #0
	sub r2, #0x18
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x80
	ldr r3, [r2, r3]
	add r2, r0, #0
	sub r2, #8
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x54
	ldr r3, [r2, r3]
	add r2, r0, #4
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x58
	ldr r3, [r2, r3]
	add r2, r0, #0
	add r2, #0xc
	str r3, [r4, r2]
	add r3, r1, #0
	ldr r2, [sp, #4]
	add r3, #0x60
	ldr r2, [r2, r3]
	add r0, #8
	str r2, [r4, r0]
	ldr r0, [sp, #4]
	add r1, #0x30
	ldr r0, [r0, r1]
	mov r1, #0x86
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #4]
	sub r1, #0xd4
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _0222E67E
	bl GF_AssertFail
_0222E67E:
	ldr r5, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r4, [sp, #0x30]
	add r6, r5, #0
	add r7, r4, #0
_0222E68A:
	ldr r0, [sp, #0x30]
	ldr r1, [r5, #0x18]
	add r0, #0xa0
	strh r1, [r0]
	add r3, r6, #0
	add r2, r7, #0
	mov r0, #6
	add r3, #0x28
	add r2, #0xac
	mov ip, r0
_0222E69E:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, ip
	sub r0, r0, #1
	mov ip, r0
	bne _0222E69E
	ldr r0, [r3]
	add r5, r5, #4
	str r0, [r2]
	ldr r0, [sp, #0x30]
	add r6, #0x34
	add r0, r0, #2
	str r0, [sp, #0x30]
	ldr r0, [sp, #8]
	add r7, #0x34
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #4
	blt _0222E68A
	add r0, r4, #0
	bl ov11_0223D1DC
	str r0, [r4, #0x30]
	mov r6, #0
	add r5, r4, #0
	mov r7, #5
_0222E6D2:
	add r0, r7, #0
	bl SaveArray_Party_Alloc
	str r0, [r5, #0x68]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _0222E6D2
	ldr r0, [r4, #0x2c]
	mov r1, #4
	tst r1, r0
	bne _0222E6EC
	b _0222EA8A
_0222E6EC:
	add r0, r4, #0
	bl sub_0206BF90
	bl sub_02031190
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x34]
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl ov11_0222FEC0
	ldr r1, [r4, #0x2c]
	mov r0, #0x80
	tst r0, r1
	beq _0222E7D0
	ldr r6, _0222E8C0 ; =ov11_0225DC18
	mov r5, #0
	add r7, r4, #0
_0222E712:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldrb r1, [r6]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	str r0, [r7, #0x34]
	add r5, r5, #1
	add r6, r6, #1
	add r7, r7, #4
	cmp r5, #4
	blt _0222E712
	str r5, [r4, #0x44]
	mov r6, #0
	add r5, r4, #0
_0222E734:
	ldr r1, [r5, #0x34]
	add r0, r4, #0
	bl ov11_0225377C
	ldr r0, [sp, #4]
	ldr r1, [r5, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [sp, #4]
	add r6, r6, #1
	add r0, r0, #4
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r6, #4
	blt _0222E734
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x44]
	cmp r0, #0
	ble _0222E7C6
	add r7, r4, #0
_0222E760:
	ldr r0, [r7, #0x68]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222E7AA
_0222E76C:
	ldr r0, [r7, #0x68]
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0222E79E
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E79E
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E7AA
_0222E79E:
	ldr r0, [r7, #0x68]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222E76C
_0222E7AA:
	str r5, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0xc]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C54C
	ldr r0, [sp, #0xc]
	ldr r1, [r4, #0x44]
	add r0, r0, #1
	add r7, r7, #4
	str r0, [sp, #0xc]
	cmp r0, r1
	blt _0222E760
_0222E7C6:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_0224B240
	b _0222EA80
_0222E7D0:
	mov r0, #8
	tst r0, r1
	beq _0222E8AC
	mov r5, #0
	add r6, r4, #0
_0222E7DA:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldr r0, [sp, #0x34]
	bl sub_020313CC
	add r7, r0, #0
	add r0, r5, #0
	bl sub_020313CC
	ldr r1, _0222E8C4 ; =ov11_0225D9C8
	lsl r2, r7, #2
	add r1, r1, r2
	ldrb r1, [r0, r1]
	add r0, sp, #0x3c
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	str r0, [r6, #0x34]
	add r5, r5, #1
	add r6, r6, #4
	cmp r5, #4
	blt _0222E7DA
	str r5, [r4, #0x44]
	mov r6, #0
	add r5, r4, #0
_0222E810:
	ldr r1, [r5, #0x34]
	add r0, r4, #0
	bl ov11_0225377C
	ldr r0, [sp, #4]
	ldr r1, [r5, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [sp, #4]
	add r6, r6, #1
	add r0, r0, #4
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r6, #4
	blt _0222E810
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x44]
	cmp r0, #0
	ble _0222E8A2
	add r7, r4, #0
_0222E83C:
	ldr r0, [r7, #0x68]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222E886
_0222E848:
	ldr r0, [r7, #0x68]
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0222E87A
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E87A
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E886
_0222E87A:
	ldr r0, [r7, #0x68]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222E848
_0222E886:
	str r5, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x10]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C54C
	ldr r0, [sp, #0x10]
	ldr r1, [r4, #0x44]
	add r0, r0, #1
	add r7, r7, #4
	str r0, [sp, #0x10]
	cmp r0, r1
	blt _0222E83C
_0222E8A2:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_0224B240
	b _0222EA80
_0222E8AC:
	mov r0, #2
	tst r0, r1
	bne _0222E8B4
	b _0222E9D4
_0222E8B4:
	ldr r0, [sp, #0x34]
	ldr r1, _0222E8C8 ; =ov11_0225D9A0
	b _0222E8CC
	nop
_0222E8BC: .word 0x00002420
_0222E8C0: .word ov11_0225DC18
_0222E8C4: .word ov11_0225D9C8
_0222E8C8: .word ov11_0225D9A0
_0222E8CC:
	lsl r0, r0, #2
	mov r5, #0
	add r6, r1, r0
	add r7, r4, #0
_0222E8D4:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldrb r1, [r6]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	add r1, r0, #0
	add r0, r4, #0
	str r1, [r7, #0x34]
	bl ov11_0225377C
	add r5, r5, #1
	add r6, r6, #1
	add r7, r7, #4
	cmp r5, #4
	blt _0222E8D4
	str r5, [r4, #0x44]
	mov r6, #0
	add r5, r4, #0
_0222E8FE:
	ldr r0, [sp, #4]
	ldr r1, [r5, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [sp, #4]
	add r6, r6, #1
	add r0, r0, #4
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r6, #4
	blt _0222E8FE
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x44]
	cmp r0, #0
	ble _0222E9D2
_0222E920:
	ldr r0, [sp, #0x14]
	mov r1, #1
	and r0, r1
	str r0, [sp, #0x2c]
	lsl r0, r0, #2
	add r7, r4, r0
	ldr r0, [r7, #0x68]
	mov r6, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222E9B8
_0222E938:
	ldr r0, [r7, #0x68]
	add r1, r6, #0
	bl GetPartyMonByIndex
	ldr r1, [sp, #0x14]
	add r5, r0, #0
	cmp r1, #1
	ble _0222E984
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x2c]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C474
	cmp r6, r0
	beq _0222E9AC
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222E9AC
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E9AC
	add r0, r5, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E9B8
	b _0222E9AC
_0222E984:
	mov r1, #5
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222E9AC
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E9AC
	add r0, r5, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222E9B8
_0222E9AC:
	ldr r0, [r7, #0x68]
	add r6, r6, #1
	bl GetPartyCount
	cmp r6, r0
	blt _0222E938
_0222E9B8:
	str r6, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x14]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C54C
	ldr r0, [sp, #0x14]
	ldr r1, [r4, #0x44]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r1
	blt _0222E920
_0222E9D2:
	b _0222EA80
_0222E9D4:
	ldr r0, [sp, #0x34]
	ldr r1, _0222EC6C ; =ov11_0225D99C
	lsl r0, r0, #1
	mov r5, #0
	add r6, r1, r0
	add r7, r4, #0
_0222E9E0:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldrb r1, [r6]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	add r1, r0, #0
	add r0, r4, #0
	str r1, [r7, #0x34]
	bl ov11_0225377C
	add r5, r5, #1
	add r6, r6, #1
	add r7, r7, #4
	cmp r5, #2
	blt _0222E9E0
	mov r0, #0
	str r5, [r4, #0x44]
	str r0, [sp, #0x18]
	add r7, r4, #0
_0222EA0C:
	ldr r0, [sp, #4]
	ldr r1, [r7, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [r7, #0x68]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222EA60
_0222EA22:
	ldr r0, [r7, #0x68]
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0222EA54
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EA54
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EA60
_0222EA54:
	ldr r0, [r7, #0x68]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222EA22
_0222EA60:
	str r5, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x18]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C54C
	ldr r0, [sp, #4]
	add r7, r7, #4
	add r0, r0, #4
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #4
	blt _0222EA0C
_0222EA80:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_0224B240
	b _0222EE3E
_0222EA8A:
	mov r1, #0x10
	tst r1, r0
	beq _0222EB90
	ldr r6, _0222EC70 ; =ov11_0225DC18
	mov r5, #0
	add r7, r4, #0
_0222EA96:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldrb r1, [r6]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	add r1, r0, #0
	add r0, r4, #0
	str r1, [r7, #0x34]
	bl ov11_0225377C
	add r5, r5, #1
	add r6, r6, #1
	add r7, r7, #4
	cmp r5, #4
	blt _0222EA96
	str r5, [r4, #0x44]
	mov r6, #0
	add r5, r4, #0
_0222EAC0:
	ldr r0, [sp, #4]
	ldr r1, [r5, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [sp, #4]
	add r6, r6, #1
	add r0, r0, #4
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r6, #4
	blt _0222EAC0
	ldr r0, [r4, #0x44]
	mov r7, #0
	cmp r0, #0
	ble _0222EB80
_0222EAE0:
	add r0, r4, #0
	add r1, r7, #0
	mov r5, #0
	bl ov11_0222FFC8
	cmp r0, #0
	ble _0222EB64
_0222EAEE:
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl ov11_02230014
	add r6, r0, #0
	cmp r7, #2
	bne _0222EB2E
	mov r1, #5
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222EB56
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EB56
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222EB56
	ldr r0, [sp, #0x38]
	cmp r0, r5
	bne _0222EB64
	b _0222EB56
_0222EB2E:
	mov r1, #5
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222EB56
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EB56
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EB64
_0222EB56:
	add r0, r4, #0
	add r1, r7, #0
	add r5, r5, #1
	bl ov11_0222FFC8
	cmp r5, r0
	blt _0222EAEE
_0222EB64:
	str r5, [sp]
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r2, #2
	add r3, r7, #0
	bl ov11_0224C54C
	cmp r7, #0
	bne _0222EB78
	str r5, [sp, #0x38]
_0222EB78:
	ldr r0, [r4, #0x44]
	add r7, r7, #1
	cmp r7, r0
	blt _0222EAE0
_0222EB80:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_0224B240
	ldr r0, _0222EC74 ; =0x000023F8
	mov r1, #1
	strb r1, [r4, r0]
	b _0222EE3E
_0222EB90:
	mov r1, #8
	tst r1, r0
	beq _0222EC60
	ldr r6, _0222EC70 ; =ov11_0225DC18
	mov r5, #0
	add r7, r4, #0
_0222EB9C:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldrb r1, [r6]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	add r1, r0, #0
	add r0, r4, #0
	str r1, [r7, #0x34]
	bl ov11_0225377C
	add r5, r5, #1
	add r6, r6, #1
	add r7, r7, #4
	cmp r5, #4
	blt _0222EB9C
	str r5, [r4, #0x44]
	mov r6, #0
	add r5, r4, #0
_0222EBC6:
	ldr r0, [sp, #4]
	ldr r1, [r5, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [sp, #4]
	add r6, r6, #1
	add r0, r0, #4
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r6, #4
	blt _0222EBC6
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [r4, #0x44]
	cmp r0, #0
	ble _0222EC50
	add r7, r4, #0
_0222EBEA:
	ldr r0, [r7, #0x68]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222EC34
_0222EBF6:
	ldr r0, [r7, #0x68]
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0222EC28
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EC28
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EC34
_0222EC28:
	ldr r0, [r7, #0x68]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222EBF6
_0222EC34:
	str r5, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x1c]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C54C
	ldr r0, [sp, #0x1c]
	ldr r1, [r4, #0x44]
	add r0, r0, #1
	add r7, r7, #4
	str r0, [sp, #0x1c]
	cmp r0, r1
	blt _0222EBEA
_0222EC50:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_0224B240
	ldr r0, _0222EC74 ; =0x000023F8
	mov r1, #1
	strb r1, [r4, r0]
	b _0222EE3E
_0222EC60:
	mov r1, #2
	tst r0, r1
	bne _0222EC68
	b _0222ED8A
_0222EC68:
	ldr r6, _0222EC70 ; =ov11_0225DC18
	b _0222EC78
	.align 2, 0
_0222EC6C: .word ov11_0225D99C
_0222EC70: .word ov11_0225DC18
_0222EC74: .word 0x000023F8
_0222EC78:
	mov r5, #0
	add r7, r4, #0
_0222EC7C:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldrb r1, [r6]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	add r1, r0, #0
	add r0, r4, #0
	str r1, [r7, #0x34]
	bl ov11_0225377C
	add r5, r5, #1
	add r6, r6, #1
	add r7, r7, #4
	cmp r5, #4
	blt _0222EC7C
	str r5, [r4, #0x44]
	mov r6, #0
	add r5, r4, #0
_0222ECA6:
	ldr r0, [sp, #4]
	ldr r1, [r5, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [sp, #4]
	add r6, r6, #1
	add r0, r0, #4
	add r5, r5, #4
	str r0, [sp, #4]
	cmp r6, #4
	blt _0222ECA6
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [r4, #0x44]
	cmp r0, #0
	ble _0222ED7A
_0222ECC8:
	ldr r0, [sp, #0x20]
	mov r1, #1
	and r0, r1
	str r0, [sp, #0x28]
	lsl r0, r0, #2
	add r7, r4, r0
	ldr r0, [r7, #0x68]
	mov r6, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222ED60
_0222ECE0:
	ldr r0, [r7, #0x68]
	add r1, r6, #0
	bl GetPartyMonByIndex
	ldr r1, [sp, #0x20]
	add r5, r0, #0
	cmp r1, #1
	ble _0222ED2C
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x28]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C474
	cmp r6, r0
	beq _0222ED54
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222ED54
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222ED54
	add r0, r5, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222ED60
	b _0222ED54
_0222ED2C:
	mov r1, #5
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0222ED54
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222ED54
	add r0, r5, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222ED60
_0222ED54:
	ldr r0, [r7, #0x68]
	add r6, r6, #1
	bl GetPartyCount
	cmp r6, r0
	blt _0222ECE0
_0222ED60:
	str r6, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x20]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C54C
	ldr r0, [sp, #0x20]
	ldr r1, [r4, #0x44]
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, r1
	blt _0222ECC8
_0222ED7A:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_0224B240
	ldr r0, _0222EEE0 ; =0x000023F8
	mov r1, #1
	strb r1, [r4, r0]
	b _0222EE3E
_0222ED8A:
	ldr r6, _0222EEE4 ; =ov11_0225D998
	mov r5, #0
	add r7, r4, #0
_0222ED90:
	add r0, sp, #0x3c
	strb r5, [r0]
	ldrb r1, [r6]
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, sp, #0x3c
	bl ov11_0224CA64
	add r1, r0, #0
	add r0, r4, #0
	str r1, [r7, #0x34]
	bl ov11_0225377C
	add r5, r5, #1
	add r6, r6, #1
	add r7, r7, #4
	cmp r5, #2
	blt _0222ED90
	mov r0, #0
	str r5, [r4, #0x44]
	str r0, [sp, #0x24]
	add r7, r4, #0
_0222EDBC:
	ldr r0, [sp, #4]
	ldr r1, [r7, #0x68]
	ldr r0, [r0, #4]
	bl CopyPlayerParty
	ldr r0, [r7, #0x68]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222EE10
_0222EDD2:
	ldr r0, [r7, #0x68]
	add r1, r5, #0
	bl GetPartyMonByIndex
	mov r1, #5
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0222EE04
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EE04
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0222EE10
_0222EE04:
	ldr r0, [r7, #0x68]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222EDD2
_0222EE10:
	str r5, [sp]
	ldr r1, [r4, #0x30]
	ldr r3, [sp, #0x24]
	add r0, r4, #0
	mov r2, #2
	bl ov11_0224C54C
	ldr r0, [sp, #4]
	add r7, r7, #4
	add r0, r0, #4
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #4
	blt _0222EDBC
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_0224B240
	ldr r0, _0222EEE0 ; =0x000023F8
	mov r1, #1
	strb r1, [r4, r0]
_0222EE3E:
	mov r0, #2
	ldr r1, [r4, #0x2c]
	lsl r0, r0, #8
	tst r0, r1
	beq _0222EE5A
	ldr r0, [r4, #0x6c]
	mov r1, #0
	bl GetPartyMonByIndex
	add r2, r4, #0
	mov r1, #0x8f
	add r2, #0xf4
	bl GetMonData
_0222EE5A:
	ldr r1, [r4, #0x2c]
	mov r0, #1
	tst r0, r1
	beq _0222EEDC
	add r0, r4, #0
	add r0, #0xe1
	ldrb r0, [r0]
	bl ov11_0222EEF0
	cmp r0, #1
	beq _0222EE7C
	ldr r0, _0222EEE8 ; =0x00000149
	ldrb r0, [r4, r0]
	bl ov11_0222EEF0
	cmp r0, #1
	bne _0222EEDC
_0222EE7C:
	ldr r0, [r4, #0x68]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222EEAC
	ldr r6, _0222EEEC ; =0x00002404
	mov r7, #3
_0222EE8C:
	ldr r0, [r4, #0x68]
	add r1, r5, #0
	bl GetPartyMonByIndex
	ldr r2, [r4, r6]
	add r1, r7, #0
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl MonApplyFriendshipMod
	ldr r0, [r4, #0x68]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222EE8C
_0222EEAC:
	ldr r0, [r4, #0x70]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0222EEDC
	ldr r6, _0222EEEC ; =0x00002404
	mov r7, #3
_0222EEBC:
	ldr r0, [r4, #0x70]
	add r1, r5, #0
	bl GetPartyMonByIndex
	ldr r2, [r4, r6]
	add r1, r7, #0
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl MonApplyFriendshipMod
	ldr r0, [r4, #0x70]
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _0222EEBC
_0222EEDC:
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222EEE0: .word 0x000023F8
_0222EEE4: .word ov11_0225D998
_0222EEE8: .word 0x00000149
_0222EEEC: .word 0x00002404

	thumb_func_start ov11_0222EEF0
ov11_0222EEF0: ; 0x0222EEF0
	sub r0, #0x3e
	cmp r0, #0x11
	bhi _0222EF2A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222EF02: ; jump table
	.short _0222EF26 - _0222EF02 - 2 ; case 0
	.short _0222EF2A - _0222EF02 - 2 ; case 1
	.short _0222EF26 - _0222EF02 - 2 ; case 2
	.short _0222EF26 - _0222EF02 - 2 ; case 3
	.short _0222EF26 - _0222EF02 - 2 ; case 4
	.short _0222EF26 - _0222EF02 - 2 ; case 5
	.short _0222EF26 - _0222EF02 - 2 ; case 6
	.short _0222EF26 - _0222EF02 - 2 ; case 7
	.short _0222EF2A - _0222EF02 - 2 ; case 8
	.short _0222EF2A - _0222EF02 - 2 ; case 9
	.short _0222EF2A - _0222EF02 - 2 ; case 10
	.short _0222EF2A - _0222EF02 - 2 ; case 11
	.short _0222EF26 - _0222EF02 - 2 ; case 12
	.short _0222EF26 - _0222EF02 - 2 ; case 13
	.short _0222EF26 - _0222EF02 - 2 ; case 14
	.short _0222EF26 - _0222EF02 - 2 ; case 15
	.short _0222EF26 - _0222EF02 - 2 ; case 16
	.short _0222EF26 - _0222EF02 - 2 ; case 17
_0222EF26:
	mov r0, #1
	bx lr
_0222EF2A:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start ov11_0222EF30
ov11_0222EF30: ; 0x0222EF30
	push {r3, lr}
	sub sp, #8
	mov r2, #2
	mov r1, #0
	ldr r0, _0222EF4C ; =ov11_0222EF50
	str r2, [sp]
	str r0, [sp, #4]
	mov r0, #5
	add r3, r1, #0
	bl sub_02022318
	add sp, #8
	pop {r3, pc}
	nop
_0222EF4C: .word ov11_0222EF50

	thumb_func_start ov11_0222EF50
ov11_0222EF50: ; 0x0222EF50
	push {r3, lr}
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r0, _0222EFBC ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	add r0, #0x58
	ldrh r2, [r0]
	ldr r1, _0222EFC0 ; =0xFFFFCFFD
	and r2, r1
	strh r2, [r0]
	add r2, r1, #2
	ldrh r3, [r0]
	add r1, r1, #2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0]
	ldrh r3, [r0]
	ldr r2, _0222EFC4 ; =0x0000CFFB
	and r3, r2
	strh r3, [r0]
	ldrh r3, [r0]
	sub r2, #0x1c
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl G3X_SetFog
	mov r0, #0
	ldr r2, _0222EFC8 ; =0x00007FFF
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _0222EFCC ; =0xBFFF0000
	ldr r0, _0222EFD0 ; =0x04000580
	str r1, [r0]
	pop {r3, pc}
	.align 2, 0
_0222EFBC: .word 0x04000008
_0222EFC0: .word 0xFFFFCFFD
_0222EFC4: .word 0x0000CFFB
_0222EFC8: .word 0x00007FFF
_0222EFCC: .word 0xBFFF0000
_0222EFD0: .word 0x04000580

	thumb_func_start ov11_0222EFD4
ov11_0222EFD4: ; 0x0222EFD4
	ldr r3, _0222EFD8 ; =sub_020223BC
	bx r3
	.align 2, 0
_0222EFD8: .word sub_020223BC

	thumb_func_start ov11_0222EFDC
ov11_0222EFDC: ; 0x0222EFDC
	push {r3, r4, r5, lr}
	ldr r3, _0222F014 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r0, #2
	mov r1, #0
	ldr r3, [r3]
	lsl r0, r0, #0xe
	add r2, r1, #0
	blx r3
	ldr r3, _0222F018 ; =NNS_GfdDefaultFuncAllocPlttVram
	mov r1, #0
	add r4, r0, #0
	ldr r3, [r3]
	mov r0, #0xc0
	add r2, r1, #0
	blx r3
	add r5, r0, #0
	cmp r4, #0
	bne _0222F004
	bl GF_AssertFail
_0222F004:
	cmp r5, #0
	bne _0222F00C
	bl GF_AssertFail
_0222F00C:
	bl sub_02012CC8
	pop {r3, r4, r5, pc}
	nop
_0222F014: .word NNS_GfdDefaultFuncAllocTexVram
_0222F018: .word NNS_GfdDefaultFuncAllocPlttVram

	thumb_func_start ov11_0222F01C
ov11_0222F01C: ; 0x0222F01C
	push {r3, r4, r5, lr}
	sub sp, #0x50
	add r4, r0, #0
	bl LCRandom
	ldr r1, _0222F0B8 ; =0x000023FB
	ldrb r2, [r4, r1]
	lsl r0, r2, #0x1f
	lsr r0, r0, #0x1f
	beq _0222F040
	mov r0, #1
	bic r2, r0
	strb r2, [r4, r1]
	ldr r0, _0222F0BC ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r0, _0222F0C0 ; =0x04001050
	strh r1, [r0]
_0222F040:
	ldr r1, _0222F0B8 ; =0x000023FB
	ldrb r2, [r4, r1]
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1f
	beq _0222F064
	mov r0, #2
	bic r2, r0
	strb r2, [r4, r1]
	ldr r5, _0222F0C4 ; =ov11_0225DA90
	add r3, sp, #0x28
	mov r2, #5
_0222F056:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222F056
	add r0, sp, #0x28
	bl GX_SetBanks
_0222F064:
	ldr r1, _0222F0B8 ; =0x000023FB
	ldrb r2, [r4, r1]
	lsl r0, r2, #0x1d
	lsr r0, r0, #0x1f
	beq _0222F088
	mov r0, #4
	bic r2, r0
	strb r2, [r4, r1]
	ldr r5, _0222F0C8 ; =ov11_0225DAB8
	add r3, sp, #0
	mov r2, #5
_0222F07A:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222F07A
	add r0, sp, #0
	bl GX_SetBanks
_0222F088:
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	bl sub_020081C4
	bl sub_0201C30C
	bl sub_0200BC30
	ldr r0, [r4, #0x28]
	bl sub_0200372C
	ldr r0, [r4, #4]
	bl DoScheduledBgGpuUpdates
	ldr r3, _0222F0CC ; =0x027E0000
	ldr r1, _0222F0D0 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	add sp, #0x50
	pop {r3, r4, r5, pc}
	nop
_0222F0B8: .word 0x000023FB
_0222F0BC: .word 0x04000050
_0222F0C0: .word 0x04001050
_0222F0C4: .word ov11_0225DA90
_0222F0C8: .word ov11_0225DAB8
_0222F0CC: .word 0x027E0000
_0222F0D0: .word 0x00003FF8

	thumb_func_start ov11_0222F0D4
ov11_0222F0D4: ; 0x0222F0D4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl sub_0200372C
	bl sub_0201C30C
	ldr r0, [r4, #4]
	bl DoScheduledBgGpuUpdates
	ldr r3, _0222F0F8 ; =0x027E0000
	ldr r1, _0222F0FC ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_0222F0F8: .word 0x027E0000
_0222F0FC: .word 0x00003FF8

	thumb_func_start ov11_0222F100
ov11_0222F100: ; 0x0222F100
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #4]
	mov r0, #5
	bl sub_020335F0
	ldr r0, _0222F140 ; =0x000023F9
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _0222F118
	cmp r0, #3
	bne _0222F13E
_0222F118:
	cmp r0, #0
	bne _0222F120
	bl ov08_02215A44
_0222F120:
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	bl sub_02006ED4
	add r4, #0x94
	ldr r0, [r4]
	bl sub_0200BC1C
	bl sub_0200BC38
	mov r0, #1
	mov r1, #0
	bl sub_020222B4
_0222F13E:
	pop {r4, pc}
	.align 2, 0
_0222F140: .word 0x000023F9

	thumb_func_start ov11_0222F144
ov11_0222F144: ; 0x0222F144
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl ov11_0222FF84
	str r0, [sp]
	add r0, r6, #0
	mov r5, #0
	bl ov11_02231474
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	bne _0222F24E
	mov r0, #2
	tst r0, r4
	beq _0222F186
	mov r0, #1
	tst r0, r4
	beq _0222F24E
	ldr r0, _0222F250 ; =0x00000704
	add r1, r5, #0
	bl sub_020054F0
	add r0, r6, #0
	mov r1, #2
	bl ov11_02231484
	pop {r3, r4, r5, r6, r7, pc}
_0222F186:
	ldr r0, [sp]
	add r4, r5, #0
	cmp r0, #0
	ble _0222F1D0
_0222F18E:
	add r0, r6, #0
	add r1, r4, #0
	bl ov11_0222FF7C
	add r7, r0, #0
	bl ov11_02253A58
	cmp r0, #0
	bne _0222F1C8
	add r0, r7, #0
	bl ov11_02253A70
	add r1, r0, #0
	beq _0222F1C8
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x2c]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x30
	bl sub_02079A54
	cmp r0, #1
	bne _0222F1C8
	add r0, r4, #0
	bl MaskOfFlagNo
	orr r5, r0
_0222F1C8:
	ldr r0, [sp]
	add r4, r4, #1
	cmp r4, r0
	blt _0222F18E
_0222F1D0:
	cmp r5, #0
	beq _0222F1F6
	add r0, r6, #0
	bl ov11_02231474
	cmp r0, #0
	bne _0222F1F6
	ldr r0, _0222F250 ; =0x00000704
	bl PlaySE
	add r0, r6, #0
	mov r1, #1
	bl ov11_02231484
	add r0, r6, #0
	mov r1, #4
	bl ov11_022314B0
	b _0222F214
_0222F1F6:
	cmp r5, #0
	bne _0222F214
	add r0, r6, #0
	bl ov11_02231474
	cmp r0, #0
	beq _0222F214
	ldr r0, _0222F250 ; =0x00000704
	mov r1, #0
	bl sub_020054F0
	add r0, r6, #0
	mov r1, #0
	bl ov11_02231484
_0222F214:
	add r0, r6, #0
	bl ov11_02231474
	cmp r0, #0
	beq _0222F24E
	add r0, r6, #0
	bl ov11_022314A0
	add r4, r0, #0
	ldr r0, _0222F250 ; =0x00000704
	bl sub_02005508
	cmp r0, #0
	bne _0222F24E
	sub r1, r4, #1
	bne _0222F244
	ldr r0, _0222F250 ; =0x00000704
	bl PlaySE
	add r0, r6, #0
	mov r1, #4
	bl ov11_022314B0
	pop {r3, r4, r5, r6, r7, pc}
_0222F244:
	lsl r1, r1, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl ov11_022314B0
_0222F24E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222F250: .word 0x00000704

	thumb_func_start ov11_0222F254
ov11_0222F254: ; 0x0222F254
	push {r3, r4, r5, lr}
	ldr r3, _0222F280 ; =0x00002434
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, r3]
	mov r1, #1
	add r0, r0, #3
	str r0, [r4, r3]
	ldr r0, [r4, #4]
	ldr r3, [r4, r3]
	mov r2, #3
	bl BgSetPosTextAndCommit
	ldr r0, _0222F280 ; =0x00002434
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222F27C
	add r0, r5, #0
	bl sub_0200CAB4
_0222F27C:
	pop {r3, r4, r5, pc}
	nop
_0222F280: .word 0x00002434

	.section .rodata

	.global ov11_0225D998
ov11_0225D998: ; 0x0225D998
	.byte 0x00, 0x01, 0x00, 0x00

	.global ov11_0225D99C
ov11_0225D99C: ; 0x0225D99C
	.byte 0x00, 0x01, 0x01, 0x00

	.global ov11_0225D9A0
ov11_0225D9A0: ; 0x0225D9A0
	.byte 0x02, 0x03, 0x04, 0x05, 0x03, 0x02, 0x05, 0x04

	.global ov11_0225D9A8
ov11_0225D9A8: ; 0x0225D9A8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global ov11_0225D9B8
ov11_0225D9B8: ; 0x0225D9B8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global ov11_0225D9C8
ov11_0225D9C8: ; 0x0225D9C8
	.byte 0x02, 0x05, 0x04, 0x03, 0x03, 0x04, 0x05, 0x02, 0x02, 0x05, 0x04, 0x03, 0x03, 0x04, 0x05, 0x02

	.global ov11_0225D9D8
ov11_0225D9D8: ; 0x0225D9D8
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00
	.byte 0x10, 0x00, 0x00, 0x00

	.global ov11_0225D9EC
ov11_0225D9EC: ; 0x0225D9EC
	.byte 0x60, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
	.byte 0x40, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00

	.global ov11_0225DA04
ov11_0225DA04: ; 0x0225DA04
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov11_0225DA20
ov11_0225DA20: ; 0x0225DA20
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00

	.global ov11_0225DA40
ov11_0225DA40: ; 0x0225DA40
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global ov11_0225DA68
ov11_0225DA68: ; 0x0225DA68
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global ov11_0225DA90
ov11_0225DA90: ; 0x0225DA90
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global ov11_0225DAB8
ov11_0225DAB8: ; 0x0225DAB8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global ov11_0225DAE0
ov11_0225DAE0: ; 0x0225DAE0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x01, 0x06, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov11_0225DB34
ov11_0225DB34: ; 0x0225DB34
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x03, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x06, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov11_0225DB88
ov11_0225DB88: ; 0x0225DB88
	.byte 0x51, 0x7B, 0x00, 0x00, 0x3E, 0x02, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x51, 0x7B, 0x00, 0x00
	.byte 0x3E, 0x02, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x51, 0x7B, 0x00, 0x00, 0x3E, 0x02, 0x00, 0x00
	.byte 0x00, 0x5E, 0x00, 0x00, 0xAB, 0x16, 0x00, 0x00, 0xAB, 0x16, 0x00, 0x00, 0xAB, 0x16, 0x00, 0x00
	.byte 0x51, 0x7B, 0x00, 0x00, 0x3E, 0x02, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x5F, 0x7F, 0x00, 0x00
	.byte 0x5F, 0x5B, 0x00, 0x00, 0xD8, 0x5A, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00
	.byte 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00
	.byte 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xA5, 0x1C, 0x00, 0x00
	.byte 0xA5, 0x1C, 0x00, 0x00, 0xA5, 0x1C, 0x00, 0x00, 0xA5, 0x1C, 0x00, 0x00, 0xA5, 0x1C, 0x00, 0x00
	.byte 0xA5, 0x1C, 0x00, 0x00, 0xA5, 0x1C, 0x00, 0x00, 0xA5, 0x1C, 0x00, 0x00, 0xA5, 0x1C, 0x00, 0x00

	.global ov11_0225DC18
ov11_0225DC18: ; 0x0225DC18
	.byte 0x02, 0x03, 0x04, 0x05
