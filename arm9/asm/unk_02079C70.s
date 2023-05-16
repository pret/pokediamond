	.include "asm/macros.inc"
	.include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020FA624
UNK_020FA624: ; 0x020FA624
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global UNK_020FA634
UNK_020FA634: ; 0x020FA634
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FA650
UNK_020FA650: ; 0x020FA650
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FA66C
UNK_020FA66C: ; 0x020FA66C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FA688
UNK_020FA688: ; 0x020FA688
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1A, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FA6A4
UNK_020FA6A4: ; 0x020FA6A4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FA6C0
UNK_020FA6C0: ; 0x020FA6C0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global UNK_020FA6E8
UNK_020FA6E8: ; 0x020FA6E8
	.word FUN_02079C7C, FUN_02079DB4, FUN_02079ECC, 0xFFFFFFFF

	.text

	thumb_func_start FUN_02079C70
FUN_02079C70: ; 0x02079C70
	push {r3, lr}
	bl SavArray_Flags_get
	bl FUN_0205F184
	pop {r3, pc}

	thumb_func_start FUN_02079C7C
FUN_02079C7C: ; 0x02079C7C
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r1, #0x1
	lsl r1, r1, #0x1a
	ldr r0, [r1, #0x0]
	ldr r2, _02079DA0 ; =0xFFFFE0FF
	and r0, r2
	str r0, [r1, #0x0]
	ldr r0, _02079DA4 ; =0x04001000
	ldr r3, [r0, #0x0]
	and r2, r3
	str r2, [r0, #0x0]
	ldr r3, [r1, #0x0]
	ldr r2, _02079DA8 ; =0xFFFF1FFF
	and r3, r2
	str r3, [r1, #0x0]
	ldr r3, [r0, #0x0]
	add r1, #0x50
	and r2, r3
	str r2, [r0, #0x0]
	mov r2, #0x0
	strh r2, [r1, #0x0]
	add r0, #0x50
	strh r2, [r0, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl SetKeyRepeatTimers
	mov r2, #0x1
	mov r0, #0x3
	mov r1, #0x13
	lsl r2, r2, #0x12
	bl CreateHeap
	ldr r1, _02079DAC ; =0x0000069C
	add r0, r4, #0x0
	mov r2, #0x13
	bl OverlayManager_CreateAndGetData
	ldr r2, _02079DAC ; =0x0000069C
	mov r1, #0x0
	add r5, r0, #0x0
	bl memset
	add r0, r4, #0x0
	bl OverlayManager_GetField18
	mov r1, #0x93
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	mov r0, #0x13
	bl BgConfig_Alloc
	mov r1, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x13
	add r2, r1, #0x0
	bl FUN_02014BF4
	mov r1, #0x2d
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	mov r0, #0x0
	mov r1, #0x13
	bl FUN_02002C84
	bl FUN_0201CC08
	mov r0, #0x4
	bl FUN_0201CC24
	add r0, r5, #0x0
	bl FUN_0207B028
	bl FUN_02079F58
	ldr r0, [r5, #0x0]
	bl FUN_02079F78
	add r0, r5, #0x0
	bl FUN_0207A0CC
	bl FUN_0207A188
	add r0, r5, #0x0
	bl FUN_0207EF6C
	add r0, r5, #0x0
	bl FUN_0207A1A0
	add r0, r5, #0x0
	bl FUN_0207AAB0
	add r0, r5, #0x0
	bl FUN_0207C328
	add r0, r5, #0x0
	bl FUN_0207C448
	add r0, r5, #0x0
	bl FUN_0207F840
	add r0, r5, #0x0
	bl FUN_0207C71C
	add r0, r5, #0x0
	bl FUN_0207C77C
	add r0, r5, #0x0
	bl FUN_0207D5BC
	add r0, r5, #0x0
	bl FUN_0207AF58
	add r0, r5, #0x0
	bl FUN_0207F95C
	add r0, r5, #0x0
	bl FUN_0207F098
	ldr r0, _02079DB0 ; =FUN_02079F24
	add r1, r5, #0x0
	bl Main_SetVBlankIntrCB
	bl GX_BothDispOn
	mov r1, #0x0
	mov r0, #0x3d
	add r2, r1, #0x0
	bl FUN_0200433C
	bl FUN_02033F20
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02079DA0: .word 0xFFFFE0FF
_02079DA4: .word 0x04001000
_02079DA8: .word 0xFFFF1FFF
_02079DAC: .word 0x0000069C
_02079DB0: .word FUN_02079F24

	thumb_func_start FUN_02079DB4
FUN_02079DB4: ; 0x02079DB4
	push {r3-r5, lr}
	add r4, r1, #0x0
	bl OverlayManager_GetData
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	cmp r1, #0x13
	bhi _02079EA2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02079DD0: ; jump table (using 16-bit offset)
	.short _02079DF8 - _02079DD0 - 2; case 0
	.short _02079E06 - _02079DD0 - 2; case 1
	.short _02079E0E - _02079DD0 - 2; case 2
	.short _02079E16 - _02079DD0 - 2; case 3
	.short _02079E1E - _02079DD0 - 2; case 4
	.short _02079E26 - _02079DD0 - 2; case 5
	.short _02079E2E - _02079DD0 - 2; case 6
	.short _02079E36 - _02079DD0 - 2; case 7
	.short _02079E3E - _02079DD0 - 2; case 8
	.short _02079E46 - _02079DD0 - 2; case 9
	.short _02079E4E - _02079DD0 - 2; case 10
	.short _02079E56 - _02079DD0 - 2; case 11
	.short _02079E5E - _02079DD0 - 2; case 12
	.short _02079E66 - _02079DD0 - 2; case 13
	.short _02079E6E - _02079DD0 - 2; case 14
	.short _02079E76 - _02079DD0 - 2; case 15
	.short _02079E7E - _02079DD0 - 2; case 16
	.short _02079E86 - _02079DD0 - 2; case 17
	.short _02079E8E - _02079DD0 - 2; case 18
	.short _02079E96 - _02079DD0 - 2; case 19
_02079DF8:
	mov r0, #0x0
	mov r1, #0x13
	bl FUN_02079A70
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02079EA2
_02079E06:
	bl FUN_0207A2D8
	str r0, [r4, #0x0]
	b _02079EA2
_02079E0E:
	bl FUN_0207A310
	str r0, [r4, #0x0]
	b _02079EA2
_02079E16:
	bl FUN_0207A448
	str r0, [r4, #0x0]
	b _02079EA2
_02079E1E:
	bl FUN_0207A45C
	str r0, [r4, #0x0]
	b _02079EA2
_02079E26:
	bl FUN_0207A470
	str r0, [r4, #0x0]
	b _02079EA2
_02079E2E:
	bl FUN_0207A484
	str r0, [r4, #0x0]
	b _02079EA2
_02079E36:
	bl FUN_0207A498
	str r0, [r4, #0x0]
	b _02079EA2
_02079E3E:
	bl FUN_0207A57C
	str r0, [r4, #0x0]
	b _02079EA2
_02079E46:
	bl FUN_0207A654
	str r0, [r4, #0x0]
	b _02079EA2
_02079E4E:
	bl FUN_0207A760
	str r0, [r4, #0x0]
	b _02079EA2
_02079E56:
	bl FUN_0207A77C
	str r0, [r4, #0x0]
	b _02079EA2
_02079E5E:
	bl FUN_0207A790
	str r0, [r4, #0x0]
	b _02079EA2
_02079E66:
	bl FUN_0207A7A4
	str r0, [r4, #0x0]
	b _02079EA2
_02079E6E:
	bl FUN_0207A818
	str r0, [r4, #0x0]
	b _02079EA2
_02079E76:
	bl FUN_0207A884
	str r0, [r4, #0x0]
	b _02079EA2
_02079E7E:
	bl FUN_0207AA20
	str r0, [r4, #0x0]
	b _02079EA2
_02079E86:
	bl FUN_0207AA70
	str r0, [r4, #0x0]
	b _02079EA2
_02079E8E:
	bl FUN_0207AA88
	str r0, [r4, #0x0]
	b _02079EA2
_02079E96:
	bl FUN_0207AA98
	cmp r0, #0x1
	bne _02079EA2
	mov r0, #0x1
	pop {r3-r5, pc}
_02079EA2:
	add r0, r5, #0x0
	bl FUN_0207C3F4
	add r0, r5, #0x0
	bl FUN_0207CC88
	add r0, r5, #0x0
	bl FUN_0207D3F4
	ldr r0, _02079EC8 ; =0x00000404
	ldr r0, [r5, r0]
	bl FUN_0200BC1C
	add r0, r5, #0x0
	bl FUN_0207F008
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02079EC8: .word 0x00000404

	thumb_func_start FUN_02079ECC
FUN_02079ECC: ; 0x02079ECC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl OverlayManager_GetData
	add r5, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl Main_SetVBlankIntrCB
	add r0, r5, #0x0
	bl FUN_0207F068
	add r0, r5, #0x0
	bl FUN_0207C3D4
	add r0, r5, #0x0
	bl FUN_0207D74C
	ldr r0, [r5, #0x0]
	bl FUN_0207A08C
	bl FUN_0201CD04
	bl FUN_0201C29C
	add r0, r5, #0x0
	bl FUN_0207A264
	mov r0, #0x0
	bl FUN_02002CC0
	ldr r0, _02079F20 ; =0x04000050
	mov r1, #0x0
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	bl OverlayManager_FreeData
	mov r0, #0x13
	bl DestroyHeap
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02079F20: .word 0x04000050

	thumb_func_start FUN_02079F24
FUN_02079F24: ; 0x02079F24
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl DoScheduledBgGpuUpdates
	mov r0, #0xae
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020081C4
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r3, _02079F50 ; =0x027E0000
	ldr r1, _02079F54 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_02079F50: .word 0x027E0000
_02079F54: .word 0x00003FF8

	thumb_func_start FUN_02079F58
FUN_02079F58: ; 0x02079F58
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _02079F74 ; =UNK_020FA6C0
	add r3, sp, #0x0
	mov r2, #0x5
_02079F62:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02079F62
	add r0, sp, #0x0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.balign 4
_02079F74: .word UNK_020FA6C0

	thumb_func_start FUN_02079F78
FUN_02079F78: ; 0x02079F78
	push {r4-r5, lr}
	sub sp, #0x9c
	ldr r5, _0207A074 ; =UNK_020FA624
	add r3, sp, #0x8c
	add r4, r0, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl SetBothScreensModesAndDisable
	ldr r5, _0207A078 ; =UNK_020FA650
	add r3, sp, #0x70
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl InitBgFromTemplate
	add r0, r4, #0x0
	mov r1, #0x1
	bl BgClearTilemapBufferAndCommit
	ldr r5, _0207A07C ; =UNK_020FA66C
	add r3, sp, #0x54
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl InitBgFromTemplate
	add r0, r4, #0x0
	mov r1, #0x2
	bl BgClearTilemapBufferAndCommit
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl ScheduleSetBgPosText
	ldr r5, _0207A080 ; =UNK_020FA688
	add r3, sp, #0x38
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl InitBgFromTemplate
	ldr r5, _0207A084 ; =UNK_020FA6A4
	add r3, sp, #0x1c
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl InitBgFromTemplate
	add r0, r4, #0x0
	mov r1, #0x4
	bl BgClearTilemapBufferAndCommit
	ldr r5, _0207A088 ; =UNK_020FA634
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x5
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl InitBgFromTemplate
	mov r0, #0x1
	mov r1, #0x20
	mov r2, #0x0
	mov r3, #0x13
	bl BG_ClearCharDataRange
	mov r0, #0x4
	mov r1, #0x20
	mov r2, #0x0
	mov r3, #0x13
	bl BG_ClearCharDataRange
	add sp, #0x9c
	pop {r4-r5, pc}
	nop
_0207A074: .word UNK_020FA624
_0207A078: .word UNK_020FA650
_0207A07C: .word UNK_020FA66C
_0207A080: .word UNK_020FA688
_0207A084: .word UNK_020FA6A4
_0207A088: .word UNK_020FA634

	thumb_func_start FUN_0207A08C
FUN_0207A08C: ; 0x0207A08C
	push {r4, lr}
	add r4, r0, #0x0
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	add r0, r4, #0x0
	mov r1, #0x5
	bl FreeBgTilemapBuffer
	add r0, r4, #0x0
	mov r1, #0x4
	bl FreeBgTilemapBuffer
	add r0, r4, #0x0
	mov r1, #0x3
	bl FreeBgTilemapBuffer
	add r0, r4, #0x0
	mov r1, #0x2
	bl FreeBgTilemapBuffer
	add r0, r4, #0x0
	mov r1, #0x1
	bl FreeBgTilemapBuffer
	mov r0, #0x13
	add r1, r4, #0x0
	bl FreeToHeapExplicit
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207A0CC
FUN_0207A0CC: ; 0x0207A0CC
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r4, r0, #0x0
	str r1, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r3, #0x3
	bl GfGfxLoader_LoadCharData
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	mov r1, #0x3
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	add r3, r1, #0x0
	bl GfGfxLoader_LoadScrnData
	mov r2, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	mov r0, #0x27
	mov r1, #0x1
	add r3, r2, #0x0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0xb
	mov r3, #0x2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0x2
	mov r3, #0x4
	bl GfGfxLoader_LoadCharData
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0x10
	mov r3, #0x5
	bl GfGfxLoader_LoadCharData
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0xf
	mov r3, #0x5
	bl GfGfxLoader_LoadScrnData
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	mov r0, #0x27
	mov r1, #0xe
	mov r2, #0x4
	bl GfGfxLoader_GXLoadPal
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_0207A188
FUN_0207A188: ; 0x0207A188
	push {r3, lr}
	mov r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, _0207A19C ; =0x04000050
	mov r1, #0x1
	mov r2, #0x1e
	mov r3, #0x17
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.balign 4
_0207A19C: .word 0x04000050

	thumb_func_start FUN_0207A1A0
FUN_0207A1A0: ; 0x0207A1A0
	push {r4, lr}
	mov r2, #0x65
	add r4, r0, #0x0
	mov r0, #0x0
	mov r1, #0x1a
	lsl r2, r2, #0x2
	mov r3, #0x13
	bl NewMsgDataFromNarc
	ldr r1, _0207A250 ; =0x00000674
	mov r2, #0x79
	str r0, [r4, r1]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	mov r3, #0x13
	bl NewMsgDataFromNarc
	ldr r1, _0207A254 ; =0x00000678
	mov r2, #0x0
	str r0, [r4, r1]
	mov r0, #0x1
	mov r1, #0x2
	mov r3, #0x13
	bl MessagePrinter_new
	mov r1, #0x67
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	mov r0, #0x13
	bl MessageFormat_new
	ldr r1, _0207A258 ; =0x0000067C
	str r0, [r4, r1]
	mov r0, #0xc
	mov r1, #0x13
	bl String_ctor
	mov r1, #0x25
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	mov r0, #0xc
	mov r1, #0x13
	bl String_ctor
	mov r1, #0x95
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0x8
	mov r1, #0x13
	bl String_ctor
	mov r1, #0x96
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0x80
	mov r1, #0x13
	bl String_ctor
	mov r1, #0x1a
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	mov r2, #0x93
	mov r0, #0x0
	mov r1, #0x1a
	lsl r2, r2, #0x2
	mov r3, #0x13
	bl NewMsgDataFromNarc
	ldr r1, _0207A25C ; =0x00000688
	str r0, [r4, r1]
	mov r0, #0x8
	mov r1, #0x13
	bl String_ctor
	ldr r2, _0207A260 ; =0x00000684
	str r0, [r4, r2]
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _0207A24C
	ldr r0, [r4, r2]
	bl CopyU16ArrayToString
_0207A24C:
	pop {r4, pc}
	nop
_0207A250: .word 0x00000674
_0207A254: .word 0x00000678
_0207A258: .word 0x0000067C
_0207A25C: .word 0x00000688
_0207A260: .word 0x00000684

	thumb_func_start FUN_0207A264
FUN_0207A264: ; 0x0207A264
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207A2C4 ; =0x00000688
	ldr r0, [r4, r0]
	bl DestroyMsgData
	ldr r0, _0207A2C8 ; =0x00000678
	ldr r0, [r4, r0]
	bl DestroyMsgData
	ldr r0, _0207A2CC ; =0x00000674
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #0x67
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl MessagePrinter_delete
	ldr r0, _0207A2D0 ; =0x0000067C
	ldr r0, [r4, r0]
	bl MessageFormat_delete
	mov r0, #0x25
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x95
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x96
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0x1a
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _0207A2D4 ; =0x00000684
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	.balign 4
_0207A2C4: .word 0x00000688
_0207A2C8: .word 0x00000678
_0207A2CC: .word 0x00000674
_0207A2D0: .word 0x0000067C
_0207A2D4: .word 0x00000684

	thumb_func_start FUN_0207A2D8
FUN_0207A2D8: ; 0x0207A2D8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0207A30C
	add r0, r4, #0x0
	bl FUN_0207F8D0
	add r0, r4, #0x0
	bl FUN_0207AF20
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207A300
	mov r0, #0x9
	pop {r4, pc}
_0207A300:
	cmp r0, #0x4
	bne _0207A308
	mov r0, #0xf
	pop {r4, pc}
_0207A308:
	mov r0, #0x2
	pop {r4, pc}
_0207A30C:
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0207A310
FUN_0207A310: ; 0x0207A310
	push {r4-r6, lr}
	ldr r3, _0207A438 ; =0x0000068F
	add r4, r0, #0x0
	ldrb r1, [r4, r3]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	cmp r1, #0x1
	bne _0207A32E
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4-r6, pc}
_0207A32E:
	ldr r2, _0207A43C ; =gMain
	mov r1, #0x20
	ldr r5, [r2, #0x4c]
	add r6, r5, #0x0
	tst r6, r1
	beq _0207A344
	sub r1, #0x21
	bl FUN_0207B178
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A344:
	mov r1, #0x10
	tst r1, r5
	beq _0207A354
	mov r1, #0x1
	bl FUN_0207B178
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A354:
	mov r1, #0x40
	add r6, r5, #0x0
	tst r6, r1
	beq _0207A366
	sub r1, #0x41
	bl FUN_0207B3F0
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A366:
	mov r1, #0x80
	tst r1, r5
	beq _0207A376
	mov r1, #0x1
	bl FUN_0207B3F0
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A376:
	ldr r1, [r2, #0x48]
	mov r0, #0x2
	tst r0, r1
	beq _0207A394
	sub r3, #0xb2
	add r0, r3, #0x0
	bl PlaySE
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4-r6, pc}
_0207A394:
	mov r0, #0x1
	tst r0, r1
	beq _0207A420
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x3
	bne _0207A3BE
	sub r0, r3, #0x3
	ldrsb r0, [r4, r0]
	cmp r0, #0x4
	bne _0207A3BE
	sub r3, #0xb2
	add r0, r3, #0x0
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207C23C
	pop {r4-r6, pc}
_0207A3BE:
	ldr r0, _0207A440 ; =0x0000068C
	ldrsb r1, [r4, r0]
	cmp r1, #0x3
	bne _0207A3D6
	add r0, #0x10
	bl PlaySE
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0x3
	pop {r4-r6, pc}
_0207A3D6:
	cmp r1, #0x5
	bne _0207A3EA
	add r0, #0x10
	bl PlaySE
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0x5
	pop {r4-r6, pc}
_0207A3EA:
	cmp r1, #0x6
	bne _0207A408
	add r1, r0, #0x0
	add r1, #0xd
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207A420
	sub r0, #0xaf
	bl PlaySE
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0xb
	pop {r4-r6, pc}
_0207A408:
	cmp r1, #0x7
	bne _0207A420
	sub r0, #0xaf
	bl PlaySE
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4-r6, pc}
_0207A420:
	add r0, r4, #0x0
	bl FUN_0207B200
	cmp r0, #0x1
	bne _0207A434
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	mov r0, #0xe
	pop {r4-r6, pc}
_0207A434:
	mov r0, #0x2
	pop {r4-r6, pc}
	.balign 4
_0207A438: .word 0x0000068F
_0207A43C: .word gMain
_0207A440: .word 0x0000068C
_0207A444: .word 0x0000068E

	thumb_func_start FUN_0207A448
FUN_0207A448: ; 0x0207A448
	push {r3, lr}
	bl FUN_0207B66C
	cmp r0, #0x1
	bne _0207A456
	mov r0, #0x7
	pop {r3, pc}
_0207A456:
	mov r0, #0x3
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A45C
FUN_0207A45C: ; 0x0207A45C
	push {r3, lr}
	bl FUN_0207B788
	cmp r0, #0x1
	bne _0207A46A
	mov r0, #0x2
	pop {r3, pc}
_0207A46A:
	mov r0, #0x4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A470
FUN_0207A470: ; 0x0207A470
	push {r3, lr}
	bl FUN_0207BAEC
	cmp r0, #0x1
	bne _0207A47E
	mov r0, #0x7
	pop {r3, pc}
_0207A47E:
	mov r0, #0x5
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A484
FUN_0207A484: ; 0x0207A484
	push {r3, lr}
	bl FUN_0207BBF0
	cmp r0, #0x1
	bne _0207A492
	mov r0, #0x2
	pop {r3, pc}
_0207A492:
	mov r0, #0x6
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A498
FUN_0207A498: ; 0x0207A498
	push {r4, lr}
	ldr r1, _0207A568 ; =gMain
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x40
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A4C2
	sub r1, #0x41
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A4BE
	ldr r0, _0207A56C ; =0x000005DC
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A4BE:
	mov r0, #0x7
	pop {r4, pc}
_0207A4C2:
	mov r1, #0x80
	tst r1, r2
	beq _0207A4E2
	mov r1, #0x1
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A4DE
	ldr r0, _0207A56C ; =0x000005DC
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A4DE:
	mov r0, #0x7
	pop {r4, pc}
_0207A4E2:
	mov r0, #0x1
	tst r0, r2
	beq _0207A542
	ldr r0, _0207A570 ; =0x0000068D
	ldrb r1, [r4, r0]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, #0x4
	bne _0207A510
	add r0, #0xf
	bl PlaySE
	ldr r0, _0207A574 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, r0, #0x2
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207A50C
	mov r0, #0x4
	pop {r4, pc}
_0207A50C:
	mov r0, #0x6
	pop {r4, pc}
_0207A510:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldrb r1, [r1, #0x12]
	cmp r1, #0x1
	beq _0207A542
	sub r0, #0xb0
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207CBE8
	ldr r2, _0207A570 ; =0x0000068D
	mov r1, #0xf0
	ldrb r3, [r4, r2]
	add r0, r3, #0x0
	bic r0, r1
	lsl r1, r3, #0x1c
	lsr r1, r1, #0x1c
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r4, r2]
	mov r0, #0x8
	pop {r4, pc}
_0207A542:
	mov r0, #0x2
	tst r0, r2
	beq _0207A564
	ldr r0, _0207A578 ; =0x0000069C
	bl PlaySE
	ldr r0, _0207A574 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, r0, #0x2
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207A560
	mov r0, #0x4
	pop {r4, pc}
_0207A560:
	mov r0, #0x6
	pop {r4, pc}
_0207A564:
	mov r0, #0x7
	pop {r4, pc}
	.balign 4
_0207A568: .word gMain
_0207A56C: .word 0x000005DC
_0207A570: .word 0x0000068D
_0207A574: .word 0x0000068E
_0207A578: .word 0x0000069C

	thumb_func_start FUN_0207A57C
FUN_0207A57C: ; 0x0207A57C
	push {r4, lr}
	ldr r1, _0207A644 ; =gMain
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x40
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A5A6
	sub r1, #0x41
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A5A2
	ldr r0, _0207A648 ; =0x000005DC
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A5A2:
	mov r0, #0x8
	pop {r4, pc}
_0207A5A6:
	mov r1, #0x80
	tst r1, r2
	beq _0207A5C6
	mov r1, #0x1
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A5C2
	ldr r0, _0207A648 ; =0x000005DC
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A5C2:
	mov r0, #0x8
	pop {r4, pc}
_0207A5C6:
	mov r0, #0x1
	tst r0, r2
	beq _0207A622
	mov r0, #0x43
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207A64C ; =0x0000068D
	ldrb r1, [r4, r0]
	lsl r2, r1, #0x1c
	lsr r2, r2, #0x1c
	cmp r2, #0x4
	beq _0207A618
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	cmp r2, r1
	beq _0207A618
	sub r0, #0xb0
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207B9C0
	ldr r1, _0207A64C ; =0x0000068D
	add r0, r4, #0x0
	ldrb r2, [r4, r1]
	lsl r1, r2, #0x1c
	lsl r2, r2, #0x18
	lsr r1, r1, #0x1c
	lsr r2, r2, #0x1c
	bl FUN_0207CB08
	add r0, r4, #0x0
	bl FUN_0207ED30
	add r0, r4, #0x0
	bl FUN_0207B8D8
	b _0207A61E
_0207A618:
	ldr r0, _0207A650 ; =0x000005DD
	bl PlaySE
_0207A61E:
	mov r0, #0x7
	pop {r4, pc}
_0207A622:
	mov r0, #0x2
	tst r0, r2
	beq _0207A63E
	ldr r0, _0207A650 ; =0x000005DD
	bl PlaySE
	mov r0, #0x43
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	mov r0, #0x7
	pop {r4, pc}
_0207A63E:
	mov r0, #0x8
	pop {r4, pc}
	nop
_0207A644: .word gMain
_0207A648: .word 0x000005DC
_0207A64C: .word 0x0000068D
_0207A650: .word 0x000005DD

	thumb_func_start FUN_0207A654
FUN_0207A654: ; 0x0207A654
	push {r4, lr}
	ldr r1, _0207A750 ; =gMain
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x20
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A66E
	sub r1, #0x21
	bl FUN_0207B178
	mov r0, #0x9
	pop {r4, pc}
_0207A66E:
	mov r1, #0x10
	tst r1, r2
	beq _0207A67E
	mov r1, #0x1
	bl FUN_0207B178
	mov r0, #0x9
	pop {r4, pc}
_0207A67E:
	mov r1, #0x40
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A6A0
	sub r1, #0x41
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A69C
	ldr r0, _0207A754 ; =0x000005DC
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A69C:
	mov r0, #0x9
	pop {r4, pc}
_0207A6A0:
	mov r1, #0x80
	tst r1, r2
	beq _0207A6C0
	mov r1, #0x1
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A6BC
	ldr r0, _0207A754 ; =0x000005DC
	bl PlaySE
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A6BC:
	mov r0, #0x9
	pop {r4, pc}
_0207A6C0:
	mov r0, #0x1
	tst r0, r2
	beq _0207A72C
	ldr r0, _0207A758 ; =0x000005DD
	bl PlaySE
	ldr r0, _0207A75C ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0x4
	beq _0207A712
	lsl r0, r0, #0x1
	add r1, r4, r0
	mov r0, #0xa1
	lsl r0, r0, #0x2
	ldrh r0, [r1, r0]
	bl MoveIsHM
	cmp r0, #0x1
	bne _0207A712
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0207A712
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C63C
	add r0, r4, #0x0
	bl FUN_0207BD58
	add r0, r4, #0x0
	bl FUN_0207EDB4
	mov r0, #0xa
	pop {r4, pc}
_0207A712:
	ldr r0, _0207A75C ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1c
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	strb r2, [r1, #0x16]
	ldr r0, [r4, r0]
	mov r1, #0x0
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4, pc}
_0207A72C:
	mov r0, #0x2
	tst r0, r2
	beq _0207A74C
	ldr r0, _0207A758 ; =0x000005DD
	bl PlaySE
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	mov r2, #0x4
	strb r2, [r1, #0x16]
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4, pc}
_0207A74C:
	mov r0, #0x9
	pop {r4, pc}
	.balign 4
_0207A750: .word gMain
_0207A754: .word 0x000005DC
_0207A758: .word 0x000005DD
_0207A75C: .word 0x0000068D

	thumb_func_start FUN_0207A760
FUN_0207A760: ; 0x0207A760
	push {r3, lr}
	ldr r1, _0207A778 ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	beq _0207A774
	bl FUN_0207B8D8
	mov r0, #0x9
	pop {r3, pc}
_0207A774:
	mov r0, #0xa
	pop {r3, pc}
	.balign 4
_0207A778: .word gMain

	thumb_func_start FUN_0207A77C
FUN_0207A77C: ; 0x0207A77C
	push {r3, lr}
	bl FUN_0207BE68
	cmp r0, #0x1
	bne _0207A78A
	mov r0, #0xd
	pop {r3, pc}
_0207A78A:
	mov r0, #0xb
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A790
FUN_0207A790: ; 0x0207A790
	push {r3, lr}
	bl FUN_0207BF90
	cmp r0, #0x1
	bne _0207A79E
	mov r0, #0x2
	pop {r3, pc}
_0207A79E:
	mov r0, #0xc
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A7A4
FUN_0207A7A4: ; 0x0207A7A4
	push {r3-r5, lr}
	ldr r3, _0207A80C ; =gMain
	mov r1, #0x20
	ldr r2, [r3, #0x4c]
	add r4, r0, #0x0
	add r5, r2, #0x0
	tst r5, r1
	beq _0207A7BE
	sub r1, #0x21
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7BE:
	mov r1, #0x10
	tst r1, r2
	beq _0207A7CE
	mov r1, #0x1
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7CE:
	mov r1, #0x40
	add r5, r2, #0x0
	tst r5, r1
	beq _0207A7E0
	sub r1, #0x44
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7E0:
	mov r1, #0x80
	tst r1, r2
	beq _0207A7F0
	mov r1, #0x4
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7F0:
	ldr r1, [r3, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207A808
	ldr r0, _0207A810 ; =0x000005DD
	bl PlaySE
	ldr r0, _0207A814 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0xc
	pop {r3-r5, pc}
_0207A808:
	mov r0, #0xd
	pop {r3-r5, pc}
	.balign 4
_0207A80C: .word gMain
_0207A810: .word 0x000005DD
_0207A814: .word 0x0000068E

	thumb_func_start FUN_0207A818
FUN_0207A818: ; 0x0207A818
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207FB28
	cmp r0, #0x1
	bne _0207A82A
	ldr r0, _0207A878 ; =0x0000068E
	ldrb r0, [r4, r0]
	pop {r4, pc}
_0207A82A:
	ldr r1, _0207A87C ; =0x00000695
	ldrb r0, [r4, r1]
	cmp r0, #0x1
	bne _0207A874
	add r1, r1, #0x1
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	bl FUN_0207FC40
	add r1, r0, #0x0
	cmp r1, #0x7
	bne _0207A850
	ldr r2, _0207A880 ; =0x0000068F
	mov r0, #0xf0
	ldrb r3, [r4, r2]
	bic r3, r0
	mov r0, #0x10
	orr r0, r3
	strb r0, [r4, r2]
_0207A850:
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _0207A86E
	cmp r1, #0x1
	beq _0207A866
	cmp r1, #0x7
	bne _0207A874
_0207A866:
	add r0, r4, #0x0
	bl FUN_0207B0CC
	b _0207A874
_0207A86E:
	add r0, r4, #0x0
	bl FUN_0207B0CC
_0207A874:
	mov r0, #0xe
	pop {r4, pc}
	.balign 4
_0207A878: .word 0x0000068E
_0207A87C: .word 0x00000695
_0207A880: .word 0x0000068F

	thumb_func_start FUN_0207A884
FUN_0207A884: ; 0x0207A884
	push {r4-r6, lr}
	sub sp, #0x8
	ldr r1, _0207AA00 ; =gMain
	add r5, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	bne _0207A896
	b _0207A9FA
_0207A896:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	ldrb r1, [r1, #0x11]
	cmp r1, #0x2
	bne _0207A8BA
	bl FUN_0207B628
	add r6, r0, #0x0
	mov r0, #0x13
	bl AllocMonZeroed
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl CopyBoxPokemonToPokemon
	b _0207A8C0
_0207A8BA:
	bl FUN_0207B628
	add r4, r0, #0x0
_0207A8C0:
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x24]
	bl FUN_0208821C
	ldr r0, _0207AA04 ; =0x0000068E
	mov r2, #0x0
	strb r2, [r5, r0]
	ldr r0, _0207AA08 ; =0x00000295
	mov r1, #0x13
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	bl GetMonData
	ldr r1, _0207AA08 ; =0x00000295
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A8F4
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x1
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A8F4:
	ldr r0, _0207AA0C ; =0x00000296
	mov r1, #0x14
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	ldr r1, _0207AA0C ; =0x00000296
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A916
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x2
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A916:
	ldr r0, _0207AA10 ; =0x00000297
	mov r1, #0x15
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	ldr r1, _0207AA10 ; =0x00000297
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A938
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x4
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A938:
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r1, #0x16
	mov r2, #0x0
	bl GetMonData
	mov r1, #0xa6
	lsl r1, r1, #0x2
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A95E
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x8
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A95E:
	ldr r0, _0207AA14 ; =0x00000299
	mov r1, #0x17
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	ldr r1, _0207AA14 ; =0x00000299
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A980
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x10
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A980:
	add r0, r4, #0x0
	mov r1, #0x18
	mov r2, #0x0
	bl GetMonData
	ldr r1, _0207AA18 ; =0x0000029A
	strb r0, [r5, r1]
	sub r1, #0x4e
	ldr r0, [r5, r1]
	ldrb r0, [r0, #0x11]
	cmp r0, #0x2
	bne _0207A99E
	add r0, r4, #0x0
	bl FreeToHeap
_0207A99E:
	mov r1, #0x7
	mov r0, #0x0
	lsl r1, r1, #0x6
	mov r2, #0x13
	bl FUN_02002EEC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x4]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	ldr r2, _0207AA1C ; =0x000003E2
	mov r1, #0x1
	mov r3, #0xd
	bl FUN_0200CD68
	ldr r0, _0207AA04 ; =0x0000068E
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	bne _0207A9E2
	add r0, r5, #0x0
	mov r1, #0xfe
	bl FUN_0207EECC
	add sp, #0x8
	mov r0, #0x11
	pop {r4-r6, pc}
_0207A9E2:
	add r0, r5, #0x0
	bl FUN_0207F608
	add r0, r5, #0x0
	bl FUN_0207CC24
	add r0, r5, #0x0
	bl FUN_0207CF78
	add sp, #0x8
	mov r0, #0x10
	pop {r4-r6, pc}
_0207A9FA:
	mov r0, #0xf
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0207AA00: .word gMain
_0207AA04: .word 0x0000068E
_0207AA08: .word 0x00000295
_0207AA0C: .word 0x00000296
_0207AA10: .word 0x00000297
_0207AA14: .word 0x00000299
_0207AA18: .word 0x0000029A
_0207AA1C: .word 0x000003E2

	thumb_func_start FUN_0207AA20
FUN_0207AA20: ; 0x0207AA20
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0207AA68 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207AA62
	ldr r0, _0207AA6C ; =0x0000068E
	mov r1, #0x0
	ldrb r2, [r5, r0]
	mov r0, #0x1
_0207AA36:
	add r4, r0, #0x0
	lsl r4, r1
	add r3, r2, #0x0
	tst r3, r4
	beq _0207AA58
	add r0, r5, #0x0
	bl FUN_0207EECC
	ldr r0, _0207AA6C ; =0x0000068E
	ldrb r1, [r5, r0]
	eor r1, r4
	strb r1, [r5, r0]
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	bne _0207AA62
	mov r0, #0x11
	pop {r3-r5, pc}
_0207AA58:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x5
	blo _0207AA36
_0207AA62:
	mov r0, #0x10
	pop {r3-r5, pc}
	nop
_0207AA68: .word gMain
_0207AA6C: .word 0x0000068E

	thumb_func_start FUN_0207AA70
FUN_0207AA70: ; 0x0207AA70
	ldr r0, _0207AA84 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207AA7E
	mov r0, #0x12
	bx lr
_0207AA7E:
	mov r0, #0x11
	bx lr
	nop
_0207AA84: .word gMain

	thumb_func_start FUN_0207AA88
FUN_0207AA88: ; 0x0207AA88
	push {r3, lr}
	mov r0, #0x1
	mov r1, #0x13
	bl FUN_02079A70
	mov r0, #0x13
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207AA98
FUN_0207AA98: ; 0x0207AA98
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0207AAA6
	mov r0, #0x1
	b _0207AAA8
_0207AAA6:
	mov r0, #0x0
_0207AAA8:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207AAB0
FUN_0207AAB0: ; 0x0207AAB0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207B628
	mov r2, #0x93
	lsl r2, r2, #0x2
	add r1, r0, #0x0
	ldr r0, [r4, r2]
	ldrb r0, [r0, #0x11]
	cmp r0, #0x2
	bne _0207AAD2
	add r2, r2, #0x4
	add r0, r4, #0x0
	add r2, r4, r2
	bl FUN_0207AAE0
	pop {r4, pc}
_0207AAD2:
	add r2, r2, #0x4
	add r0, r4, #0x0
	add r2, r4, r2
	bl FUN_0207AB0C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207AAE0
FUN_0207AAE0: ; 0x0207AAE0
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x13
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl AllocMonZeroed
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl CopyBoxPokemonToPokemon
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_0207AB0C
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207AB0C
FUN_0207AB0C: ; 0x0207AB0C
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r5, r2, #0x0
	bl AcquireMonLock
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0xc]
	add r0, r6, #0x0
	bl FUN_020690E4
	ldr r2, _0207AEAC ; =0x00000674
	add r4, r0, #0x0
	ldr r0, [r7, r2]
	add r2, #0xc
	ldr r2, [r7, r2]
	mov r1, #0xb
	bl ReadMsgDataIntoString
	ldr r0, _0207AEB0 ; =0x0000067C
	mov r1, #0x0
	ldr r0, [r7, r0]
	add r2, r4, #0x0
	bl BufferBoxMonSpeciesName
	ldr r2, _0207AEB0 ; =0x0000067C
	mov r1, #0x25
	ldr r0, [r7, r2]
	lsl r1, r1, #0x4
	add r2, r2, #0x4
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	bl StringExpandPlaceholders
	ldr r2, _0207AEAC ; =0x00000674
	mov r1, #0x0
	ldr r0, [r7, r2]
	add r2, #0xc
	ldr r2, [r7, r2]
	bl ReadMsgDataIntoString
	ldr r0, _0207AEB0 ; =0x0000067C
	mov r1, #0x0
	ldr r0, [r7, r0]
	add r2, r4, #0x0
	bl BufferBoxMonNickname
	ldr r2, _0207AEB0 ; =0x0000067C
	mov r1, #0x95
	ldr r0, [r7, r2]
	lsl r1, r1, #0x2
	add r2, r2, #0x4
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	bl StringExpandPlaceholders
	ldr r2, _0207AEAC ; =0x00000674
	mov r1, #0xe
	ldr r0, [r7, r2]
	add r2, #0xc
	ldr r2, [r7, r2]
	bl ReadMsgDataIntoString
	ldr r0, _0207AEB0 ; =0x0000067C
	mov r1, #0x0
	ldr r0, [r7, r0]
	add r2, r4, #0x0
	bl BufferBoxMonOTName
	ldr r2, _0207AEB0 ; =0x0000067C
	mov r1, #0x96
	ldr r0, [r7, r2]
	lsl r1, r1, #0x2
	add r2, r2, #0x4
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	bl StringExpandPlaceholders
	add r0, r6, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0xe]
	add r0, r6, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	ldrb r1, [r5, #0x12]
	mov r2, #0x7f
	lsl r0, r0, #0x18
	bic r1, r2
	lsr r2, r0, #0x18
	mov r0, #0x7f
	and r0, r2
	orr r0, r1
	strb r0, [r5, #0x12]
	add r0, r6, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x1f
	ldr r2, [r5, #0x50]
	ldr r1, _0207AEB4 ; =0xEFFFFFFF
	lsr r0, r0, #0x3
	and r1, r2
	orr r0, r1
	str r0, [r5, #0x50]
	add r0, r6, #0x0
	mov r1, #0xaf
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x1
	bne _0207AC16
	ldr r0, [r5, #0x50]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	bne _0207AC16
	ldrb r1, [r5, #0x12]
	mov r0, #0x80
	bic r1, r0
	strb r1, [r5, #0x12]
	b _0207AC1E
_0207AC16:
	ldrb r1, [r5, #0x12]
	mov r0, #0x80
	orr r0, r1
	strb r0, [r5, #0x12]
_0207AC1E:
	add r0, r6, #0x0
	bl GetMonGender
	ldrb r1, [r5, #0x13]
	mov r2, #0x3
	bic r1, r2
	mov r2, #0x3
	and r0, r2
	orr r0, r1
	strb r0, [r5, #0x13]
	add r0, r6, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1a
	ldrb r1, [r5, #0x13]
	mov r2, #0xfc
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r5, #0x13]
	add r0, r6, #0x0
	mov r1, #0xb0
	mov r2, #0x0
	bl GetMonData
	strb r0, [r5, #0x10]
	add r0, r6, #0x0
	mov r1, #0xb1
	mov r2, #0x0
	bl GetMonData
	strb r0, [r5, #0x11]
	add r0, r6, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl GetMonData
	str r0, [r5, #0x14]
	add r0, r6, #0x0
	mov r1, #0x8
	mov r2, #0x0
	bl GetMonData
	str r0, [r5, #0x18]
	add r0, r6, #0x0
	mov r1, #0x9c
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x44
	strb r0, [r1, #0x0]
	ldrb r1, [r5, #0x12]
	ldrh r0, [r5, #0xc]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x19
	bl GetMonExpBySpeciesAndLevel
	str r0, [r5, #0x1c]
	ldrb r0, [r5, #0x12]
	lsl r0, r0, #0x19
	lsr r1, r0, #0x19
	cmp r1, #0x64
	bne _0207ACAA
	ldr r0, [r5, #0x1c]
	b _0207ACB2
_0207ACAA:
	ldrh r0, [r5, #0xc]
	add r1, r1, #0x1
	bl GetMonExpBySpeciesAndLevel
_0207ACB2:
	str r0, [r5, #0x20]
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x24]
	add r0, r6, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x26]
	add r0, r6, #0x0
	mov r1, #0xa4
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x28]
	add r0, r6, #0x0
	mov r1, #0xa5
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x2a]
	add r0, r6, #0x0
	mov r1, #0xa7
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x2c]
	add r0, r6, #0x0
	mov r1, #0xa8
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x2e]
	add r0, r6, #0x0
	mov r1, #0xa6
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x30]
	add r0, r6, #0x0
	mov r1, #0xa
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x32
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	bl GetMonNature
	add r1, r5, #0x0
	add r1, #0x33
	strb r0, [r1, #0x0]
	mov r4, #0x0
_0207AD26:
	lsl r0, r4, #0x1
	add r0, r5, r0
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x0]
	mov r2, #0x0
	strh r0, [r1, #0x34]
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x3a
	bl GetMonData
	add r1, r5, r4
	add r1, #0x3c
	strb r0, [r1, #0x0]
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x34]
	bl WazaGetMaxPp
	add r1, r5, r4
	add r1, #0x40
	strb r0, [r1, #0x0]
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x4
	blo _0207AD26
	add r0, r6, #0x0
	mov r1, #0x13
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x45
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x14
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x46
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x15
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x47
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x16
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x48
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x17
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x49
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x18
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x4a
	strb r0, [r1, #0x0]
	add r0, r5, #0x0
	mov r1, #0x5
	add r0, #0x4b
	strb r1, [r0, #0x0]
	mov r4, #0x0
_0207ADE0:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl MonGetFlavorPreference
	cmp r0, #0x1
	bne _0207ADF4
	add r0, r5, #0x0
	add r0, #0x4b
	strb r4, [r0, #0x0]
	b _0207ADFE
_0207ADF4:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x5
	blo _0207ADE0
_0207ADFE:
	add r0, r6, #0x0
	mov r1, #0xb
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x4c
	strh r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonData
	add r1, r5, #0x0
	add r1, #0x4e
	strh r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_0207C2D4
	mov r1, #0xf
	ldr r2, [r5, #0x50]
	lsl r1, r1, #0x1c
	and r2, r1
	ldr r1, _0207AEB8 ; =0x0FFFFFFF
	and r0, r1
	orr r0, r2
	str r0, [r5, #0x50]
	add r0, r6, #0x0
	bl Pokemon_IsImmuneToPokerus
	cmp r0, #0x1
	bne _0207AE4E
	ldr r1, [r5, #0x50]
	ldr r0, _0207AEBC ; =0x3FFFFFFF
	and r1, r0
	mov r0, #0x2
	lsl r0, r0, #0x1e
	orr r0, r1
	str r0, [r5, #0x50]
	b _0207AE84
_0207AE4E:
	add r0, r6, #0x0
	bl Pokemon_HasPokerus
	cmp r0, #0x1
	bne _0207AE7C
	ldr r2, [r5, #0x50]
	ldr r1, _0207AEBC ; =0x3FFFFFFF
	add r0, r5, #0x0
	and r2, r1
	add r1, r1, #0x1
	orr r1, r2
	str r1, [r5, #0x50]
	lsl r1, r1, #0x4
	lsr r1, r1, #0x4
	add r0, #0x50
	cmp r1, #0x7
	bne _0207AE84
	mov r1, #0xf
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x1c
	and r1, r2
	str r1, [r0, #0x0]
	b _0207AE84
_0207AE7C:
	ldr r1, [r5, #0x50]
	ldr r0, _0207AEBC ; =0x3FFFFFFF
	and r0, r1
	str r0, [r5, #0x50]
_0207AE84:
	add r0, r6, #0x0
	bl MonIsShiny
	cmp r0, #0x1
	ldr r1, [r5, #0x50]
	bne _0207AE98
	mov r0, #0x2
	lsl r0, r0, #0x1c
	orr r0, r1
	b _0207AE9C
_0207AE98:
	ldr r0, _0207AEC0 ; =0xDFFFFFFF
	and r0, r1
_0207AE9C:
	str r0, [r5, #0x50]
	mov r4, #0x0
	str r4, [r5, #0x54]
	str r4, [r5, #0x58]
	str r4, [r5, #0x5c]
	ldr r0, _0207AEC4 ; =0x00000699
	b _0207AEC8
	nop
_0207AEAC: .word 0x00000674
_0207AEB0: .word 0x0000067C
_0207AEB4: .word 0xEFFFFFFF
_0207AEB8: .word 0x0FFFFFFF
_0207AEBC: .word 0x3FFFFFFF
_0207AEC0: .word 0xDFFFFFFF
_0207AEC4: .word 0x00000699
_0207AEC8:
	str r4, [r5, #0x60]
	strb r4, [r7, r0]
_0207AECC:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r6, #0x0
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0207AF04
	lsr r0, r4, #0x5
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1f
	add r2, r4, #0x0
	and r2, r1
	mov r1, #0x1
	ldr r3, [r0, #0x54]
	lsl r1, r2
	orr r1, r3
	str r1, [r0, #0x54]
	ldr r0, _0207AF1C ; =0x00000699
	ldrb r0, [r7, r0]
	add r1, r0, #0x1
	ldr r0, _0207AF1C ; =0x00000699
	strb r1, [r7, r0]
_0207AF04:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x50
	blo _0207AECC
	ldr r1, [sp, #0x4]
	add r0, r6, #0x0
	bl ReleaseMonLock
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0207AF1C: .word 0x00000699

	thumb_func_start FUN_0207AF20
FUN_0207AF20: ; 0x0207AF20
	push {r3, lr}
	mov r2, #0x2a
	lsl r2, r2, #0x4
	ldr r1, [r0, r2]
	lsl r1, r1, #0x3
	lsr r1, r1, #0x1f
	bne _0207AF54
	add r1, r2, #0x0
	sub r1, #0x44
	ldrh r3, [r0, r1]
	add r1, r2, #0x0
	sub r1, #0xe7
	cmp r3, r1
	bne _0207AF4E
	sub r2, #0x54
	ldr r0, [r0, r2]
	mov r1, #0x0
	ldr r0, [r0, #0x28]
	mov r2, #0x64
	add r3, r1, #0x0
	bl FUN_02005E90
	pop {r3, pc}
_0207AF4E:
	add r0, r3, #0x0
	bl FUN_02005578
_0207AF54:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207AF58
FUN_0207AF58: ; 0x0207AF58
	push {r4, lr}
	mov r1, #0x93
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	ldr r0, [r4, r1]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x4
	bhi _0207AFA4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207AF74: ; jump table (using 16-bit offset)
	.short _0207AF7E - _0207AF74 - 2; case 0
	.short _0207AF7E - _0207AF74 - 2; case 1
	.short _0207AF96 - _0207AF74 - 2; case 2
	.short _0207AF9E - _0207AF74 - 2; case 3
	.short _0207AF9E - _0207AF74 - 2; case 4
_0207AF7E:
	add r1, #0x54
	ldr r0, [r4, r1]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	ldr r0, _0207AFFC ; =0x0000068C
	bne _0207AF90
	mov r1, #0x0
	strb r1, [r4, r0]
	b _0207AFA4
_0207AF90:
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207AFA4
_0207AF96:
	ldr r0, _0207AFFC ; =0x0000068C
	mov r1, #0x3
	strb r1, [r4, r0]
	b _0207AFA4
_0207AF9E:
	ldr r0, _0207AFFC ; =0x0000068C
	mov r1, #0x4
	strb r1, [r4, r0]
_0207AFA4:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207C5D4
	add r0, r4, #0x0
	bl FUN_0207C838
	add r0, r4, #0x0
	bl FUN_0207D2C8
	add r0, r4, #0x0
	bl FUN_0207C6A4
	add r0, r4, #0x0
	bl FUN_0207CE4C
	add r0, r4, #0x0
	bl FUN_0207CC24
	add r0, r4, #0x0
	bl FUN_0207D604
	add r0, r4, #0x0
	bl FUN_0207DD88
	add r0, r4, #0x0
	bl FUN_0207B228
	add r0, r4, #0x0
	bl FUN_0207F2A0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207AFFA
	add r0, r4, #0x0
	bl FUN_0207BA74
_0207AFFA:
	pop {r4, pc}
	.balign 4
_0207AFFC: .word 0x0000068C

	thumb_func_start FUN_0207B000
FUN_0207B000: ; 0x0207B000
	push {r3-r6}
	mov r6, #0x0
	strb r6, [r0, #0x15]
	add r0, #0x15
	mov r3, #0x1
_0207B00A:
	ldrb r5, [r1, r6]
	cmp r5, #0x8
	beq _0207B024
	add r2, r3, #0x0
	ldrb r4, [r0, #0x0]
	lsl r2, r5
	orr r2, r4
	strb r2, [r0, #0x0]
	add r2, r6, #0x1
	lsl r2, r2, #0x18
	lsr r6, r2, #0x18
	cmp r6, #0x8
	blo _0207B00A
_0207B024:
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_0207B028
FUN_0207B028: ; 0x0207B028
	push {r3-r4}
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	ldr r1, [r4, #0x2c]
	cmp r1, #0x1
	beq _0207B06C
	ldrb r2, [r4, #0x15]
	mov r1, #0x10
	add r3, r2, #0x0
	tst r3, r1
	beq _0207B044
	eor r1, r2
	strb r1, [r4, #0x15]
_0207B044:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	mov r1, #0x20
	ldrb r2, [r4, #0x15]
	add r3, r2, #0x0
	tst r3, r1
	beq _0207B058
	eor r1, r2
	strb r1, [r4, #0x15]
_0207B058:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r3, [r0, r1]
	mov r0, #0x40
	ldrb r1, [r3, #0x15]
	add r2, r1, #0x0
	tst r2, r0
	beq _0207B06C
	eor r0, r1
	strb r0, [r3, #0x15]
_0207B06C:
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0207B070
FUN_0207B070: ; 0x0207B070
	mov r2, #0x2a
	lsl r2, r2, #0x4
	ldr r2, [r0, r2]
	lsl r2, r2, #0x3
	lsr r2, r2, #0x1f
	beq _0207B088
	cmp r1, #0x1
	beq _0207B088
	cmp r1, #0x7
	beq _0207B088
	mov r0, #0x0
	bx lr
_0207B088:
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r0, [r0, r2]
	ldrb r2, [r0, #0x15]
	mov r0, #0x1
	lsl r0, r1
	and r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_0207B09C
FUN_0207B09C: ; 0x0207B09C
	push {r3-r4}
	mov r3, #0x93
	lsl r3, r3, #0x2
	ldr r0, [r0, r3]
	mov r2, #0x0
	ldrb r0, [r0, #0x15]
	add r1, r2, #0x0
	mov r3, #0x1
_0207B0AC:
	add r4, r3, #0x0
	lsl r4, r1
	tst r4, r0
	beq _0207B0BA
	add r2, r2, #0x1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
_0207B0BA:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x8
	blo _0207B0AC
	add r0, r2, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0207B0CC
FUN_0207B0CC: ; 0x0207B0CC
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	ldr r1, _0207B174 ; =0x0000068C
	add r5, r0, #0x0
	ldrsb r1, [r5, r1]
	cmp r1, r4
	beq _0207B170
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	ldrb r1, [r1, #0x12]
	cmp r1, #0x2
	bne _0207B0EC
	bl FUN_0207BDD8
_0207B0EC:
	add r0, r5, #0x0
	bl FUN_0207D6F8
	ldr r0, _0207B174 ; =0x0000068C
	mov r1, #0x0
	strb r4, [r5, r0]
	add r0, r5, #0x0
	bl FUN_0207CFAC
	add r0, r5, #0x0
	bl FUN_0207C5D4
	add r0, r5, #0x0
	bl FUN_0207C6A4
	add r0, r5, #0x0
	bl FUN_0207C838
	add r0, r5, #0x0
	bl FUN_0207D2C8
	add r0, r5, #0x0
	bl FUN_0207CC24
	add r0, r5, #0x0
	bl FUN_0207D604
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0207D418
	mov r0, #0x4
	str r0, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	mov r0, #0x14
	str r0, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	mov r3, #0xe
	bl FillBgTilemapRect
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	bl BgCommitTilemapBufferToVram
	add r0, r5, #0x0
	bl FUN_0207DD88
	add r0, r5, #0x0
	bl FUN_0207B228
	add r0, r5, #0x0
	bl FUN_0207F2A0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207B170
	add r0, r5, #0x0
	bl FUN_0207BDF4
_0207B170:
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_0207B174: .word 0x0000068C

	thumb_func_start FUN_0207B178
FUN_0207B178: ; 0x0207B178
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0207B1F8 ; =0x0000068C
	mov r6, #0x1
	ldrsb r4, [r5, r0]
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r12, r4
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	add r7, r6, #0x0
_0207B190:
	add r2, r4, r1
	lsl r2, r2, #0x18
	asr r4, r2, #0x18
	bpl _0207B19C
	mov r4, #0x7
	b _0207B1A2
_0207B19C:
	cmp r4, #0x7
	ble _0207B1A2
	mov r4, #0x0
_0207B1A2:
	cmp r0, #0x0
	bne _0207B1B8
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r2, [r5, r2]
	ldrb r3, [r2, #0x15]
	add r2, r6, #0x0
	lsl r2, r4
	tst r2, r3
	bne _0207B1D0
	b _0207B190
_0207B1B8:
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r2, [r5, r2]
	ldrb r3, [r2, #0x15]
	add r2, r7, #0x0
	lsl r2, r4
	tst r2, r3
	beq _0207B190
	cmp r4, #0x1
	beq _0207B1D0
	cmp r4, #0x7
	bne _0207B190
_0207B1D0:
	mov r0, r12
	cmp r4, r0
	beq _0207B1F4
	ldr r0, _0207B1FC ; =0x000005E1
	bl PlaySE
	add r0, r5, #0x0
	bl FUN_0207FA38
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0207D418
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_0207B0CC
_0207B1F4:
	pop {r3-r7, pc}
	nop
_0207B1F8: .word 0x0000068C
_0207B1FC: .word 0x000005E1

	thumb_func_start FUN_0207B200
FUN_0207B200: ; 0x0207B200
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207FA80
	cmp r0, #0xff
	bne _0207B210
	mov r0, #0x0
	pop {r4, pc}
_0207B210:
	ldr r1, _0207B224 ; =0x00000694
	mov r3, #0x0
	strb r3, [r4, r1]
	add r2, r1, #0x2
	strb r0, [r4, r2]
	add r0, r1, #0x1
	strb r3, [r4, r0]
	mov r0, #0x1
	pop {r4, pc}
	nop
_0207B224: .word 0x00000694

	thumb_func_start FUN_0207B228
FUN_0207B228: ; 0x0207B228
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	ldrb r0, [r1, #0x12]
	cmp r0, #0x2
	bne _0207B250
	ldrh r0, [r1, #0x18]
	cmp r0, #0x0
	beq _0207B250
	ldr r0, _0207B2AC ; =0x0000068C
	ldrsb r0, [r5, r0]
	cmp r0, #0x3
	bne _0207B24C
	mov r1, #0xc
	b _0207B256
_0207B24C:
	mov r1, #0xd
	b _0207B256
_0207B250:
	ldr r0, _0207B2AC ; =0x0000068C
	ldrsb r0, [r5, r0]
	add r1, r0, #0x3
_0207B256:
	mov r0, #0x27
	mov r2, #0x13
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0xc
	add r4, r0, #0x0
	bl NNS_G2dGetUnpackedScreenData
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	add r2, #0xc
	bl LoadRectToBgTilemapRect
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	bl ScheduleBgTilemapBufferTransfer
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, _0207B2AC ; =0x0000068C
	ldrsb r0, [r5, r0]
	cmp r0, #0x0
	bne _0207B29C
	add r0, r5, #0x0
	bl FUN_0207B364
	add sp, #0x10
	pop {r3-r5, pc}
_0207B29C:
	cmp r0, #0x2
	bne _0207B2A6
	add r0, r5, #0x0
	bl FUN_0207B2B0
_0207B2A6:
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_0207B2AC: .word 0x0000068C

	thumb_func_start FUN_0207B2B0
FUN_0207B2B0: ; 0x0207B2B0
	push {r4-r7, lr}
	sub sp, #0x14
	mov r1, #0x9d
	add r6, r0, #0x0
	lsl r1, r1, #0x2
	ldrh r0, [r6, r1]
	add r1, r1, #0x2
	ldrh r1, [r6, r1]
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #0x4
	bhi _0207B2EC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207B2D6: ; jump table (using 16-bit offset)
	.short _0207B2E0 - _0207B2D6 - 2; case 0
	.short _0207B2E8 - _0207B2D6 - 2; case 1
	.short _0207B2E4 - _0207B2D6 - 2; case 2
	.short _0207B2E0 - _0207B2D6 - 2; case 3
	.short _0207B2E0 - _0207B2D6 - 2; case 4
_0207B2E0:
	ldr r7, _0207B35C ; =0x0000A0C0
	b _0207B2EC
_0207B2E4:
	ldr r7, _0207B360 ; =0x0000A0E0
	b _0207B2EC
_0207B2E8:
	mov r7, #0xa1
	lsl r7, r7, #0x8
_0207B2EC:
	mov r1, #0x9d
	lsl r1, r1, #0x2
	ldrh r0, [r6, r1]
	add r1, r1, #0x2
	ldrh r1, [r6, r1]
	mov r2, #0x30
	bl FUN_02079A0C
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r5, #0x0
	str r0, [sp, #0x10]
_0207B30A:
	cmp r4, #0x8
	blo _0207B312
	ldr r2, [sp, #0x10]
	b _0207B318
_0207B312:
	add r0, r7, r4
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0207B318:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r3, r5, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x11
	add r3, #0x18
	str r0, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	cmp r4, #0x8
	bhs _0207B33E
	mov r4, #0x0
	b _0207B344
_0207B33E:
	sub r4, #0x8
	lsl r0, r4, #0x18
	lsr r4, r0, #0x18
_0207B344:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x6
	blo _0207B30A
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_0207B35C: .word 0x0000A0C0
_0207B360: .word 0x0000A0E0

	thumb_func_start FUN_0207B364
FUN_0207B364: ; 0x0207B364
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r2, _0207B3EC ; =0x00000262
	add r6, r0, #0x0
	ldrb r0, [r6, r2]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	cmp r0, #0x64
	bhs _0207B38C
	add r0, r2, #0x0
	add r1, r2, #0x0
	add r0, #0xa
	add r1, #0xe
	add r2, r2, #0x6
	ldr r0, [r6, r0]
	ldr r1, [r6, r1]
	ldr r2, [r6, r2]
	sub r1, r1, r0
	sub r0, r2, r0
	b _0207B390
_0207B38C:
	mov r1, #0x0
	add r0, r1, #0x0
_0207B390:
	mov r2, #0x38
	bl FUN_02079A0C
	add r4, r0, #0x0
	mov r5, #0x0
	mov r7, #0x17
_0207B39C:
	cmp r4, #0x8
	blo _0207B3A4
	mov r2, #0xb4
	b _0207B3AC
_0207B3A4:
	add r0, r4, #0x0
	add r0, #0xac
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0207B3AC:
	str r7, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r3, r5, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x11
	add r3, #0x17
	str r0, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	cmp r4, #0x8
	bhs _0207B3D0
	mov r4, #0x0
	b _0207B3D6
_0207B3D0:
	sub r4, #0x8
	lsl r0, r4, #0x18
	lsr r4, r0, #0x18
_0207B3D6:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x7
	blo _0207B39C
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	bl ScheduleBgTilemapBufferTransfer
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0207B3EC: .word 0x00000262

	thumb_func_start FUN_0207B3F0
FUN_0207B3F0: ; 0x0207B3F0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207B4A4
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0207B49C
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	strb r0, [r1, #0x14]
	add r0, r4, #0x0
	bl FUN_0207AAB0
	add r0, r4, #0x0
	bl FUN_0207AF20
	add r0, r4, #0x0
	bl FUN_0207D768
	add r0, r4, #0x0
	bl FUN_0207D800
	add r0, r4, #0x0
	bl FUN_0207D8A0
	ldr r0, _0207B4A0 ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x0
	bne _0207B436
	add r0, r4, #0x0
	bl FUN_0207B364
	b _0207B44C
_0207B436:
	cmp r0, #0x2
	bne _0207B442
	add r0, r4, #0x0
	bl FUN_0207B2B0
	b _0207B44C
_0207B442:
	cmp r0, #0x4
	bne _0207B44C
	add r0, r4, #0x0
	bl FUN_0207F608
_0207B44C:
	add r0, r4, #0x0
	bl FUN_0207F934
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207C5D4
	add r0, r4, #0x0
	bl FUN_0207C6A4
	add r0, r4, #0x0
	bl FUN_0207CA44
	add r0, r4, #0x0
	bl FUN_0207C838
	add r0, r4, #0x0
	bl FUN_0207D2C8
	add r0, r4, #0x0
	bl FUN_0207CFEC
	add r0, r4, #0x0
	bl FUN_0207C71C
	add r0, r4, #0x0
	bl FUN_0207C77C
	add r0, r4, #0x0
	bl FUN_0207CC24
	add r0, r4, #0x0
	bl FUN_0207CE4C
	add r0, r4, #0x0
	bl FUN_0207DD88
_0207B49C:
	pop {r4, pc}
	nop
_0207B4A0: .word 0x0000068C

	thumb_func_start FUN_0207B4A4
FUN_0207B4A4: ; 0x0207B4A4
	push {r3, lr}
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r2, [r0, r2]
	ldrb r2, [r2, #0x11]
	cmp r2, #0x0
	beq _0207B4BC
	cmp r2, #0x1
	beq _0207B4C2
	cmp r2, #0x2
	beq _0207B4C8
	b _0207B4CE
_0207B4BC:
	bl FUN_0207B4FC
	pop {r3, pc}
_0207B4C2:
	bl FUN_0207B564
	pop {r3, pc}
_0207B4C8:
	bl FUN_0207B5C0
	pop {r3, pc}
_0207B4CE:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}

	thumb_func_start FUN_0207B4D4
FUN_0207B4D4: ; 0x0207B4D4
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r0, r1]
	ldrb r1, [r1, #0x12]
	cmp r1, #0x3
	bne _0207B4E4
	mov r0, #0x0
	bx lr
_0207B4E4:
	ldr r1, _0207B4F8 ; =0x0000068C
	ldrsb r0, [r0, r1]
	cmp r0, #0x1
	beq _0207B4F4
	cmp r0, #0x7
	beq _0207B4F4
	mov r0, #0x0
	bx lr
_0207B4F4:
	mov r0, #0x1
	bx lr
	.balign 4
_0207B4F8: .word 0x0000068C

	thumb_func_start FUN_0207B4FC
FUN_0207B4FC: ; 0x0207B4FC
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	str r1, [sp, #0x0]
	ldr r1, [r5, r0]
	mov r0, #0x14
	ldrsb r4, [r1, r0]
_0207B50C:
	ldr r0, [sp, #0x0]
	add r0, r4, r0
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	bmi _0207B522
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x13]
	cmp r4, r0
	blt _0207B528
_0207B522:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0207B528:
	bl FUN_020690C4
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	add r7, r4, #0x0
	ldr r6, [r1, #0x0]
	mul r7, r0
	add r0, r6, r7
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0207B50C
	add r0, r6, r7
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0207B55E
	add r0, r5, #0x0
	bl FUN_0207B4D4
	cmp r0, #0x1
	bne _0207B50C
_0207B55E:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207B564
FUN_0207B564: ; 0x0207B564
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	add r7, r1, #0x0
	ldr r1, [r5, r0]
	mov r0, #0x14
	ldrsb r4, [r1, r0]
_0207B574:
	add r0, r4, r7
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	bmi _0207B588
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	ldrb r0, [r1, #0x13]
	cmp r4, r0
	blt _0207B58E
_0207B588:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0207B58E:
	ldr r0, [r1, #0x0]
	add r1, r4, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0207B574
	add r0, r6, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0207B5BC
	add r0, r5, #0x0
	bl FUN_0207B4D4
	cmp r0, #0x1
	bne _0207B574
_0207B5BC:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0207B5C0
FUN_0207B5C0: ; 0x0207B5C0
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	str r1, [sp, #0x0]
	ldr r1, [r5, r0]
	mov r0, #0x14
	ldrsb r4, [r1, r0]
_0207B5D0:
	ldr r0, [sp, #0x0]
	add r0, r4, r0
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	bmi _0207B5E6
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x13]
	cmp r4, r0
	blt _0207B5EC
_0207B5E6:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0207B5EC:
	bl FUN_020690C8
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	add r7, r4, #0x0
	ldr r6, [r1, #0x0]
	mul r7, r0
	add r0, r6, r7
	mov r1, #0x5
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	beq _0207B5D0
	add r0, r6, r7
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	beq _0207B622
	add r0, r5, #0x0
	bl FUN_0207B4D4
	cmp r0, #0x1
	bne _0207B5D0
_0207B622:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207B628
FUN_0207B628: ; 0x0207B628
	push {r4, lr}
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	ldrb r0, [r4, #0x11]
	cmp r0, #0x0
	beq _0207B640
	cmp r0, #0x1
	beq _0207B64E
	cmp r0, #0x2
	beq _0207B658
	b _0207B666
_0207B640:
	bl FUN_020690C4
	ldrb r1, [r4, #0x14]
	ldr r2, [r4, #0x0]
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0207B64E:
	ldrb r1, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl GetPartyMonByIndex
	pop {r4, pc}
_0207B658:
	bl FUN_020690C8
	ldrb r1, [r4, #0x14]
	ldr r2, [r4, #0x0]
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0207B666:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207B66C
FUN_0207B66C: ; 0x0207B66C
	push {r4, lr}
	ldr r1, _0207B774 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207B682
	cmp r1, #0x1
	beq _0207B6E2
	cmp r1, #0x2
	beq _0207B70E
	b _0207B76E
_0207B682:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl ScheduleSetBgPosText
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl ScheduleSetBgPosText
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C6F0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	add r0, #0x64
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	ldr r1, _0207B778 ; =0x0000068D
	mov r0, #0xf
	ldrb r2, [r4, r1]
	bic r2, r0
	strb r2, [r4, r1]
	mov r2, #0x1
	add r0, r1, #0x1
	strb r2, [r4, r0]
	b _0207B76E
_0207B6E2:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl Bg_GetXpos
	cmp r0, #0x40
	ldr r0, [r4, #0x0]
	bgt _0207B702
	mov r2, #0x0
	mov r1, #0x2
	add r3, r2, #0x0
	bl ScheduleSetBgPosText
	ldr r0, _0207B774 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207B76E
_0207B702:
	mov r1, #0x2
	add r2, r1, #0x0
	mov r3, #0x40
	bl ScheduleSetBgPosText
	b _0207B76E
_0207B70E:
	bl FUN_0207ECDC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x1
	beq _0207B732
	add r0, r4, #0x0
	mov r1, #0x98
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
_0207B732:
	add r0, r4, #0x0
	bl FUN_0207B8D8
	ldr r0, _0207B77C ; =0x00000434
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	add r0, r4, #0x0
	bl FUN_0207D06C
	mov r0, #0x26
	lsl r0, r0, #0x4
	ldrb r1, [r4, r0]
	add r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r1, r0
	beq _0207B760
	ldr r0, _0207B780 ; =0x00000438
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
_0207B760:
	ldr r0, _0207B784 ; =0x0000042C
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x1
	pop {r4, pc}
_0207B76E:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207B774: .word 0x0000068E
_0207B778: .word 0x0000068D
_0207B77C: .word 0x00000434
_0207B780: .word 0x00000438
_0207B784: .word 0x0000042C

	thumb_func_start FUN_0207B788
FUN_0207B788: ; 0x0207B788
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207B864 ; =0x0000068E
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	beq _0207B79E
	cmp r0, #0x1
	beq _0207B7F8
	cmp r0, #0x2
	beq _0207B824
	b _0207B860
_0207B79E:
	ldr r0, _0207B868 ; =0x00000434
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	ldr r0, _0207B86C ; =0x00000438
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C63C
	ldr r0, _0207B870 ; =0x00000454
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	ldr r0, _0207B874 ; =0x0000042C
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207ED18
	add r0, r4, #0x0
	bl FUN_0207EC94
	ldr r0, _0207B864 ; =0x0000068E
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207B860
_0207B7F8:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl Bg_GetXpos
	cmp r0, #0x80
	ldr r0, [r4, #0x0]
	blt _0207B818
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl ScheduleSetBgPosText
	ldr r0, _0207B864 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207B860
_0207B818:
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x40
	bl ScheduleSetBgPosText
	b _0207B860
_0207B824:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	add r0, r4, #0x0
	add r0, #0x64
	bl ScheduleWindowCopyToVram
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	add r0, r4, #0x0
	mov r1, #0x81
	bl FUN_0207D924
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207C6F0
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x1
	pop {r4, pc}
_0207B860:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0207B864: .word 0x0000068E
_0207B868: .word 0x00000434
_0207B86C: .word 0x00000438
_0207B870: .word 0x00000454
_0207B874: .word 0x0000042C

	thumb_func_start FUN_0207B878
FUN_0207B878: ; 0x0207B878
	push {r4-r7}
	add r5, r0, #0x0
	ldr r0, _0207B8D4 ; =0x0000068D
	mov r6, #0xa1
	ldrb r0, [r5, r0]
	mov r2, #0x4
	lsl r6, r6, #0x2
	lsl r0, r0, #0x1c
	lsr r4, r0, #0x1c
	add r3, r4, #0x0
	mov r0, #0x0
_0207B88E:
	add r3, r3, r1
	lsl r3, r3, #0x18
	asr r3, r3, #0x18
	bpl _0207B89A
	add r3, r2, #0x0
	b _0207B8A0
_0207B89A:
	cmp r3, #0x5
	bne _0207B8A0
	add r3, r0, #0x0
_0207B8A0:
	lsl r7, r3, #0x1
	add r7, r5, r7
	ldrh r7, [r7, r6]
	cmp r7, #0x0
	bne _0207B8AE
	cmp r3, #0x4
	bne _0207B88E
_0207B8AE:
	cmp r3, r4
	beq _0207B8CC
	ldr r2, _0207B8D4 ; =0x0000068D
	mov r1, #0xf
	ldrb r0, [r5, r2]
	bic r0, r1
	lsl r1, r3, #0x18
	lsr r3, r1, #0x18
	mov r1, #0xf
	and r1, r3
	orr r0, r1
	strb r0, [r5, r2]
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_0207B8CC:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_0207B8D4: .word 0x0000068D

	thumb_func_start FUN_0207B8D8
FUN_0207B8D8: ; 0x0207B8D8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207CBC0
	ldr r2, _0207B95C ; =0x0000068D
	ldrb r0, [r4, r2]
	lsl r0, r0, #0x1c
	lsr r1, r0, #0x1c
	cmp r1, #0x4
	bne _0207B930
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrh r1, [r0, #0x18]
	cmp r1, #0x0
	beq _0207B910
	sub r0, r2, #0x1
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207B908
	add r0, r4, #0x0
	bl FUN_0207B960
	pop {r4, pc}
_0207B908:
	add r0, r4, #0x0
	bl FUN_0207B99C
	pop {r4, pc}
_0207B910:
	sub r0, r2, #0x1
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207B924
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207B960
	pop {r4, pc}
_0207B924:
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207B99C
	pop {r4, pc}
_0207B930:
	sub r0, r2, #0x1
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207B94A
	lsl r1, r1, #0x1
	add r2, r4, r1
	mov r1, #0xa1
	lsl r1, r1, #0x2
	ldrh r1, [r2, r1]
	add r0, r4, #0x0
	bl FUN_0207B960
	pop {r4, pc}
_0207B94A:
	lsl r1, r1, #0x1
	add r2, r4, r1
	mov r1, #0xa1
	lsl r1, r1, #0x2
	ldrh r1, [r2, r1]
	add r0, r4, #0x0
	bl FUN_0207B99C
	pop {r4, pc}
	.balign 4
_0207B95C: .word 0x0000068D

	thumb_func_start FUN_0207B960
FUN_0207B960: ; 0x0207B960
	push {r3-r5, lr}
	mov r2, #0x0
	add r4, r1, #0x0
	mvn r2, r2
	add r5, r0, #0x0
	cmp r4, r2
	bne _0207B980
	bl FUN_0207EC94
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200C63C
	pop {r3-r5, pc}
_0207B980:
	bl FUN_0207EB64
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207CB70
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x1
	bl FUN_0200C63C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0207B99C
FUN_0207B99C: ; 0x0207B99C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0207BD84
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _0207B9B6
	add r0, r5, #0x0
	bl FUN_0207EEB0
	pop {r3-r5, pc}
_0207B9B6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207EE2C
	pop {r3-r5, pc}

	thumb_func_start FUN_0207B9C0
FUN_0207B9C0: ; 0x0207B9C0
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl FUN_0207B628
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldrb r1, [r1, #0x11]
	cmp r1, #0x2
	ldr r1, _0207BA70 ; =0x0000068D
	bne _0207B9E6
	ldrb r2, [r4, r1]
	lsl r1, r2, #0x1c
	lsl r2, r2, #0x18
	lsr r1, r1, #0x1c
	lsr r2, r2, #0x1c
	bl FUN_020698E8
	b _0207B9F4
_0207B9E6:
	ldrb r2, [r4, r1]
	lsl r1, r2, #0x1c
	lsl r2, r2, #0x18
	lsr r1, r1, #0x1c
	lsr r2, r2, #0x1c
	bl FUN_020698E0
_0207B9F4:
	ldr r0, _0207BA70 ; =0x0000068D
	mov r1, #0xa1
	ldrb r6, [r4, r0]
	lsl r1, r1, #0x2
	add r5, r4, r1
	lsl r2, r6, #0x1c
	lsl r6, r6, #0x18
	lsr r6, r6, #0x1c
	lsl r6, r6, #0x1
	lsr r3, r2, #0x1b
	add r6, r4, r6
	ldrh r2, [r5, r3]
	ldrh r6, [r6, r1]
	strh r6, [r5, r3]
	ldrb r3, [r4, r0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	lsl r3, r3, #0x1
	add r3, r4, r3
	strh r2, [r3, r1]
	add r2, r1, #0x0
	add r2, #0x8
	ldrb r6, [r4, r0]
	add r5, r4, r2
	lsl r2, r6, #0x1c
	lsl r6, r6, #0x18
	lsr r6, r6, #0x1c
	add r7, r4, r6
	add r6, r1, #0x0
	lsr r3, r2, #0x1c
	add r6, #0x8
	ldrb r2, [r5, r3]
	ldrb r6, [r7, r6]
	strb r6, [r5, r3]
	ldrb r3, [r4, r0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	add r5, r4, r3
	add r3, r1, #0x0
	add r3, #0x8
	strb r2, [r5, r3]
	add r2, r1, #0x0
	add r2, #0xc
	ldrb r6, [r4, r0]
	add r5, r4, r2
	lsl r2, r6, #0x1c
	lsl r6, r6, #0x18
	lsr r6, r6, #0x1c
	add r7, r4, r6
	add r6, r1, #0x0
	lsr r3, r2, #0x1c
	add r6, #0xc
	ldrb r2, [r5, r3]
	ldrb r6, [r7, r6]
	add r1, #0xc
	strb r6, [r5, r3]
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	add r0, r4, r0
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	.balign 4
_0207BA70: .word 0x0000068D

	thumb_func_start FUN_0207BA74
FUN_0207BA74: ; 0x0207BA74
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	add r0, #0x64
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	mov r2, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	add r3, r2, #0x0
	bl ScheduleSetBgPosText
	add r0, r4, #0x0
	bl FUN_0207ECDC
	add r0, r4, #0x0
	bl FUN_0207B8D8
	ldr r0, _0207BAE0 ; =0x00000434
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	add r0, r4, #0x0
	bl FUN_0207D06C
	mov r0, #0x26
	lsl r0, r0, #0x4
	ldrb r1, [r4, r0]
	add r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r1, r0
	beq _0207BAD4
	ldr r0, _0207BAE4 ; =0x00000438
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
_0207BAD4:
	ldr r0, _0207BAE8 ; =0x0000042C
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
	.balign 4
_0207BAE0: .word 0x00000434
_0207BAE4: .word 0x00000438
_0207BAE8: .word 0x0000042C

	thumb_func_start FUN_0207BAEC
FUN_0207BAEC: ; 0x0207BAEC
	push {r4, lr}
	ldr r1, _0207BBE4 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207BB02
	cmp r1, #0x1
	beq _0207BB6E
	cmp r1, #0x2
	beq _0207BB9A
	b _0207BBDE
_0207BB02:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl ScheduleSetBgPosText
	mov r2, #0x3
	add r3, r2, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	add r3, #0xfd
	bl ScheduleSetBgPosText
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207BD84
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C6F0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	add r0, #0x64
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	ldr r1, _0207BBE8 ; =0x0000068D
	mov r0, #0xf
	ldrb r2, [r4, r1]
	bic r2, r0
	strb r2, [r4, r1]
	mov r2, #0x1
	add r0, r1, #0x1
	strb r2, [r4, r0]
	b _0207BBDE
_0207BB6E:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl Bg_GetXpos
	cmp r0, #0x40
	ldr r0, [r4, #0x0]
	bgt _0207BB8E
	mov r2, #0x0
	mov r1, #0x2
	add r3, r2, #0x0
	bl ScheduleSetBgPosText
	ldr r0, _0207BBE4 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207BBDE
_0207BB8E:
	mov r1, #0x2
	add r2, r1, #0x0
	mov r3, #0x40
	bl ScheduleSetBgPosText
	b _0207BBDE
_0207BB9A:
	bl FUN_0207ECDC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x1
	beq _0207BBBE
	add r0, r4, #0x0
	mov r1, #0x98
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
_0207BBBE:
	add r0, r4, #0x0
	bl FUN_0207B8D8
	add r0, r4, #0x0
	bl FUN_0207D06C
	add r0, r4, #0x0
	bl FUN_0207D10C
	ldr r0, _0207BBEC ; =0x0000042C
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x1
	pop {r4, pc}
_0207BBDE:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207BBE4: .word 0x0000068E
_0207BBE8: .word 0x0000068D
_0207BBEC: .word 0x0000042C

	thumb_func_start FUN_0207BBF0
FUN_0207BBF0: ; 0x0207BBF0
	push {r4, lr}
	ldr r1, _0207BCBC ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207BC06
	cmp r1, #0x1
	beq _0207BC4E
	cmp r1, #0x2
	beq _0207BC7A
	b _0207BCB6
_0207BC06:
	bl FUN_0207D22C
	ldr r0, _0207BCC0 ; =0x00000454
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207BD84
	ldr r0, _0207BCC4 ; =0x0000042C
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207ED18
	add r0, r4, #0x0
	bl FUN_0207EEB0
	ldr r0, _0207BCBC ; =0x0000068E
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207BCB6
_0207BC4E:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl Bg_GetXpos
	cmp r0, #0x80
	ldr r0, [r4, #0x0]
	blt _0207BC6E
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl ScheduleSetBgPosText
	ldr r0, _0207BCBC ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207BCB6
_0207BC6E:
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x40
	bl ScheduleSetBgPosText
	b _0207BCB6
_0207BC7A:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	add r0, r4, #0x0
	add r0, #0x64
	bl ScheduleWindowCopyToVram
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	add r0, r4, #0x0
	mov r1, #0x9e
	bl FUN_0207D924
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207C6F0
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x1
	pop {r4, pc}
_0207BCB6:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207BCBC: .word 0x0000068E
_0207BCC0: .word 0x00000454
_0207BCC4: .word 0x0000042C

	thumb_func_start FUN_0207BCC8
FUN_0207BCC8: ; 0x0207BCC8
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x2f
	str r0, [sp, #0x0]
	mov r0, #0x1
	lsl r6, r2, #0x1
	add r4, r1, #0x0
	str r0, [sp, #0x4]
	add r7, r6, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	lsl r3, r7, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	add r2, r4, #0x0
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	mov r0, #0x2f
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r6, r6, #0x3
	str r0, [sp, #0x8]
	mov r0, #0x10
	add r2, r4, #0x1
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	mov r0, #0x30
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r2, r4, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x10
	add r2, #0x20
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r7, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	mov r0, #0x30
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	add r4, #0x21
	str r0, [sp, #0xc]
	lsl r2, r4, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FillBgTilemapRect
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_0207BD58
FUN_0207BD58: ; 0x0207BD58
	push {r4-r6, lr}
	ldr r6, _0207BD80 ; =0x0000012E
	add r5, r0, #0x0
	mov r4, #0x0
_0207BD60:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_0207BCC8
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x6
	blo _0207BD60
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	bl ScheduleBgTilemapBufferTransfer
	pop {r4-r6, pc}
	.balign 4
_0207BD80: .word 0x0000012E

	thumb_func_start FUN_0207BD84
FUN_0207BD84: ; 0x0207BD84
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0207BD58
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _0207BDCC
	add r0, r4, #0x0
	mov r1, #0xa
	bl GetWazaAttr
	bl FUN_02083114
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	asr r6, r0, #0x18
	mov r4, #0x0
	cmp r6, #0x0
	ble _0207BDCC
	mov r7, #0x4b
	lsl r7, r7, #0x2
_0207BDB6:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	add r1, r7, #0x0
	lsr r2, r2, #0x18
	bl FUN_0207BCC8
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blt _0207BDB6
_0207BDCC:
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	bl ScheduleBgTilemapBufferTransfer
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207BDD8
FUN_0207BDD8: ; 0x0207BDD8
	push {r3, lr}
	ldr r1, _0207BDF0 ; =0x0000068C
	ldrsb r1, [r0, r1]
	cmp r1, #0x3
	bne _0207BDE8
	bl FUN_0207EC94
	pop {r3, pc}
_0207BDE8:
	bl FUN_0207EEB0
	pop {r3, pc}
	nop
_0207BDF0: .word 0x0000068C

	thumb_func_start FUN_0207BDF4
FUN_0207BDF4: ; 0x0207BDF4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207ECDC
	add r0, r4, #0x0
	bl FUN_0207B8D8
	add r0, r4, #0x0
	bl FUN_0207D06C
	ldr r0, _0207BE5C ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207BE46
	add r0, r4, #0x0
	bl FUN_0207D22C
	ldr r0, _0207BE60 ; =0x00000434
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	mov r0, #0x26
	lsl r0, r0, #0x4
	ldrb r1, [r4, r0]
	add r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r1, r0
	beq _0207BE38
	ldr r0, _0207BE64 ; =0x00000438
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
_0207BE38:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl ScheduleSetBgPosText
	pop {r4, pc}
_0207BE46:
	add r0, r4, #0x0
	bl FUN_0207D10C
	mov r2, #0x3
	add r3, r2, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	add r3, #0xfd
	bl ScheduleSetBgPosText
	pop {r4, pc}
	.balign 4
_0207BE5C: .word 0x0000068C
_0207BE60: .word 0x00000434
_0207BE64: .word 0x00000438

	thumb_func_start FUN_0207BE68
FUN_0207BE68: ; 0x0207BE68
	push {r4, lr}
	ldr r1, _0207BF78 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207BE7E
	cmp r1, #0x1
	beq _0207BEEA
	cmp r1, #0x2
	beq _0207BF16
	b _0207BF74
_0207BE7E:
	mov r1, #0x2
	add r3, r1, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x0
	add r3, #0xfe
	bl ScheduleSetBgPosText
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl ScheduleSetBgPosText
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C6F0
	add r0, r4, #0x0
	add r0, #0x64
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x79
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	ldr r1, _0207BF7C ; =0x00000697
	mov r2, #0x0
	strb r2, [r4, r1]
	add r0, r1, #0x1
	strb r2, [r4, r0]
	mov r0, #0x1
	sub r1, #0x9
	strb r0, [r4, r1]
	b _0207BF74
_0207BEEA:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl Bg_GetYpos
	cmp r0, #0x30
	ldr r0, [r4, #0x0]
	blt _0207BF0A
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x38
	bl ScheduleSetBgPosText
	ldr r0, _0207BF78 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207BF74
_0207BF0A:
	mov r1, #0x2
	mov r2, #0x4
	mov r3, #0x10
	bl ScheduleSetBgPosText
	b _0207BF74
_0207BF16:
	mov r1, #0xb5
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	ldr r0, _0207BF80 ; =0x00000514
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x52
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_020200A0
	ldr r0, _0207BF84 ; =0x00000504
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207BF88 ; =0x00000508
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207BF8C ; =0x0000050C
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x51
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C07C
	mov r0, #0x1
	pop {r4, pc}
_0207BF74:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0207BF78: .word 0x0000068E
_0207BF7C: .word 0x00000697
_0207BF80: .word 0x00000514
_0207BF84: .word 0x00000504
_0207BF88: .word 0x00000508
_0207BF8C: .word 0x0000050C

	thumb_func_start FUN_0207BF90
FUN_0207BF90: ; 0x0207BF90
	push {r4, lr}
	ldr r1, _0207C078 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	beq _0207BFA6
	cmp r0, #0x1
	beq _0207BFF6
	cmp r0, #0x2
	beq _0207C022
	b _0207C072
_0207BFA6:
	add r0, r1, #0x0
	mov r2, #0x0
	add r0, #0x9
	strb r2, [r4, r0]
	add r1, #0xa
	mov r0, #0x91
	strb r2, [r4, r1]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x20
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x30
	bl ClearWindowTilemapAndScheduleTransfer
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ClearWindowTilemapAndScheduleTransfer
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207D2C8
	ldr r0, _0207C078 ; =0x0000068E
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207C072
_0207BFF6:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl Bg_GetYpos
	cmp r0, #0x8
	ldr r0, [r4, #0x0]
	bgt _0207C016
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl ScheduleSetBgPosText
	ldr r0, _0207C078 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207C072
_0207C016:
	mov r1, #0x2
	mov r2, #0x5
	mov r3, #0x10
	bl ScheduleSetBgPosText
	b _0207C072
_0207C022:
	add r0, r4, #0x0
	add r0, #0x64
	bl ScheduleWindowCopyToVram
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	mov r0, #0x79
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl ScheduleWindowCopyToVram
	add r0, r4, #0x0
	mov r1, #0xb4
	bl FUN_0207D924
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207C6F0
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x1
	pop {r4, pc}
_0207C072:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207C078: .word 0x0000068E

	thumb_func_start FUN_0207C07C
FUN_0207C07C: ; 0x0207C07C
	push {r4-r6, lr}
	ldr r2, _0207C1D0 ; =0x00000697
	add r5, r0, #0x0
	add r3, r2, #0x1
	ldrb r0, [r5, r2]
	ldrb r4, [r5, r3]
	cmp r1, #0x1
	bne _0207C0A8
	mov r1, #0x3
	and r1, r0
	cmp r1, #0x3
	beq _0207C0B6
	lsl r1, r4, #0x2
	add r1, r0, r1
	add r3, r1, #0x1
	add r1, r2, #0x2
	ldrb r1, [r5, r1]
	cmp r3, r1
	bge _0207C14A
	add r1, r0, #0x1
	strb r1, [r5, r2]
	b _0207C14A
_0207C0A8:
	mov r3, #0x0
	mvn r3, r3
	cmp r1, r3
	bne _0207C0BE
	mov r1, #0x3
	tst r1, r0
	bne _0207C0B8
_0207C0B6:
	b _0207C1CE
_0207C0B8:
	sub r1, r0, #0x1
	strb r1, [r5, r2]
	b _0207C14A
_0207C0BE:
	cmp r1, #0x4
	bne _0207C12C
	cmp r0, #0x4
	bhs _0207C0F2
	add r1, r2, #0x2
	ldrb r3, [r5, r1]
	lsl r1, r4, #0x2
	add r1, r0, r1
	add r1, r1, #0x4
	cmp r1, r3
	blt _0207C0EC
	cmp r3, #0x4
	bls _0207C14A
	lsr r1, r3, #0x1f
	lsl r6, r3, #0x1e
	sub r6, r6, r1
	mov r3, #0x1e
	ror r6, r3
	add r1, r1, r6
	beq _0207C14A
	add r1, r1, #0x3
	strb r1, [r5, r2]
	b _0207C14A
_0207C0EC:
	add r1, r0, #0x4
	strb r1, [r5, r2]
	b _0207C14A
_0207C0F2:
	add r1, r2, #0x2
	ldrb r1, [r5, r1]
	lsl r3, r4, #0x2
	add r3, #0x8
	cmp r3, r1
	bge _0207C14A
	add r1, r2, #0x1
	ldrb r1, [r5, r1]
	add r6, r2, #0x1
	add r3, r1, #0x1
	add r1, r2, #0x1
	strb r3, [r5, r1]
	add r1, r2, #0x2
	ldrb r6, [r5, r6]
	ldrb r3, [r5, r1]
	ldrb r1, [r5, r2]
	lsl r6, r6, #0x2
	add r1, r1, r6
	cmp r1, r3
	blt _0207C14A
	lsr r1, r3, #0x1f
	lsl r6, r3, #0x1e
	sub r6, r6, r1
	mov r3, #0x1e
	ror r6, r3
	add r1, r1, r6
	add r1, r1, #0x3
	strb r1, [r5, r2]
	b _0207C14A
_0207C12C:
	sub r3, r3, #0x3
	cmp r1, r3
	bne _0207C14A
	cmp r0, #0x4
	blo _0207C13C
	sub r1, r0, #0x4
	strb r1, [r5, r2]
	b _0207C14A
_0207C13C:
	cmp r4, #0x0
	beq _0207C14A
	add r1, r2, #0x1
	ldrb r1, [r5, r1]
	sub r3, r1, #0x1
	add r1, r2, #0x1
	strb r3, [r5, r1]
_0207C14A:
	ldr r1, _0207C1D0 ; =0x00000697
	ldrb r2, [r5, r1]
	cmp r0, r2
	bne _0207C15A
	add r0, r1, #0x1
	ldrb r0, [r5, r0]
	cmp r4, r0
	beq _0207C160
_0207C15A:
	ldr r0, _0207C1D4 ; =0x000005DC
	bl PlaySE
_0207C160:
	ldr r1, _0207C1D0 ; =0x00000697
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_0207C1E8
	ldr r1, _0207C1D8 ; =0x0000069A
	strb r0, [r5, r1]
	add r0, r5, #0x0
	bl FUN_0207D3C4
	ldr r0, _0207C1DC ; =0x00000698
	ldrb r0, [r5, r0]
	cmp r4, r0
	beq _0207C182
	add r0, r5, #0x0
	bl FUN_0207D364
_0207C182:
	add r0, r5, #0x0
	bl FUN_0207E9A0
	add r0, r5, #0x0
	bl FUN_0207E840
	ldr r0, _0207C1DC ; =0x00000698
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	ldr r0, _0207C1E0 ; =0x00000518
	beq _0207C1A2
	ldr r0, [r5, r0]
	mov r1, #0x1
	bl FUN_020200A0
	b _0207C1AA
_0207C1A2:
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
_0207C1AA:
	ldr r0, _0207C1DC ; =0x00000698
	ldrb r1, [r5, r0]
	add r0, r0, #0x1
	ldrb r0, [r5, r0]
	lsl r1, r1, #0x2
	add r1, #0x8
	cmp r1, r0
	ldr r0, _0207C1E4 ; =0x0000051C
	bge _0207C1C6
	ldr r0, [r5, r0]
	mov r1, #0x1
	bl FUN_020200A0
	pop {r4-r6, pc}
_0207C1C6:
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
_0207C1CE:
	pop {r4-r6, pc}
	.balign 4
_0207C1D0: .word 0x00000697
_0207C1D4: .word 0x000005DC
_0207C1D8: .word 0x0000069A
_0207C1DC: .word 0x00000698
_0207C1E0: .word 0x00000518
_0207C1E4: .word 0x0000051C

	thumb_func_start FUN_0207C1E8
FUN_0207C1E8: ; 0x0207C1E8
	push {r4-r7}
	ldr r2, _0207C238 ; =0x00000698
	mov r6, #0x0
	ldrb r2, [r0, r2]
	add r4, r6, #0x0
	lsl r2, r2, #0x2
	add r1, r1, r2
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	mov r1, #0xa9
	mov r2, #0x1
	lsl r1, r1, #0x2
_0207C200:
	mov r3, #0x1f
	add r7, r4, #0x0
	and r7, r3
	add r3, r2, #0x0
	lsl r3, r7
	lsr r7, r4, #0x5
	lsl r7, r7, #0x2
	add r7, r0, r7
	ldr r7, [r7, r1]
	tst r3, r7
	beq _0207C228
	cmp r5, r6
	bne _0207C222
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r4-r7}
	bx lr
_0207C222:
	add r3, r6, #0x1
	lsl r3, r3, #0x18
	lsr r6, r3, #0x18
_0207C228:
	add r3, r4, #0x1
	lsl r3, r3, #0x10
	lsr r4, r3, #0x10
	cmp r4, #0x50
	blo _0207C200
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	.balign 4
_0207C238: .word 0x00000698

	thumb_func_start FUN_0207C23C
FUN_0207C23C: ; 0x0207C23C
	push {r4, lr}
	sub sp, #0x8
	ldr r1, _0207C29C ; =0x0000029A
	add r4, r0, #0x0
	ldrb r0, [r4, r1]
	cmp r0, #0xff
	bne _0207C28E
	mov r0, #0x0
	sub r1, #0xda
	mov r2, #0x13
	bl FUN_02002EEC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x4]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	ldr r2, _0207C2A0 ; =0x000003E2
	mov r1, #0x1
	mov r3, #0xd
	bl FUN_0200CD68
	add r0, r4, #0x0
	mov r1, #0xff
	bl FUN_0207EECC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	add sp, #0x8
	mov r0, #0x11
	pop {r4, pc}
_0207C28E:
	sub r1, #0x4e
	ldr r0, [r4, r1]
	mov r2, #0x0
	strb r2, [r0, #0x17]
	mov r0, #0x12
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0207C29C: .word 0x0000029A
_0207C2A0: .word 0x000003E2

	thumb_func_start FUN_0207C2A4
FUN_0207C2A4: ; 0x0207C2A4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl PlayerProfile_GetNamePtr
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	bl PlayerProfile_GetTrainerID
	str r0, [r5, #0xc]
	add r0, r4, #0x0
	bl PlayerProfile_GetTrainerGender
	strb r0, [r5, #0x10]
	pop {r3-r5, pc}

	thumb_func_start FUN_0207C2C4
FUN_0207C2C4: ; 0x0207C2C4
	mov r0, #0x40
	bx lr

	thumb_func_start FUN_0207C2C8
FUN_0207C2C8: ; 0x0207C2C8
	mov r0, #0x41
	bx lr

	thumb_func_start FUN_0207C2CC
FUN_0207C2CC: ; 0x0207C2CC
	mov r0, #0x3f
	bx lr

	thumb_func_start FUN_0207C2D0
FUN_0207C2D0: ; 0x0207C2D0
	mov r0, #0x3e
	bx lr

	thumb_func_start FUN_0207C2D4
FUN_0207C2D4: ; 0x0207C2D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x9f
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0207C2F4
	mov r0, #0x6
	pop {r3-r5, pc}
_0207C2F4:
	mov r0, #0x88
	tst r0, r4
	beq _0207C2FE
	mov r0, #0x4
	pop {r3-r5, pc}
_0207C2FE:
	mov r0, #0x7
	add r1, r4, #0x0
	tst r1, r0
	beq _0207C30A
	mov r0, #0x3
	pop {r3-r5, pc}
_0207C30A:
	mov r1, #0x10
	tst r1, r4
	beq _0207C314
	mov r0, #0x5
	pop {r3-r5, pc}
_0207C314:
	mov r1, #0x20
	tst r1, r4
	beq _0207C31E
	mov r0, #0x2
	pop {r3-r5, pc}
_0207C31E:
	mov r1, #0x40
	tst r1, r4
	beq _0207C326
	mov r0, #0x1
_0207C326:
	pop {r3-r5, pc}
