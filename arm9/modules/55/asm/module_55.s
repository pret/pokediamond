	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD55_021D74E0
MOD55_021D74E0: ; 0x021D74E0
	push {r4, lr}
	add r4, r0, #0
	bl MOD55_021D7BF0
	add r0, r4, #0
	bl MOD55_021D7C20
	add r0, r4, #0
	bl MOD55_021D7DA0
	mov r0, #0x34
	bl FUN_02053708
	mov r1, #0xeb
	lsl r1, r1, #2
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD55_021D74E0

	thumb_func_start MOD55_021D7504
MOD55_021D7504: ; 0x021D7504
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
	ldr r0, _021D7560 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7564 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #4
	mov r1, #8
	bl SetKeyRepeatTimers
	mov r0, #0x34
	bl BgConfig_Alloc
	str r0, [r4, #4]
	bl MOD55_021D780C
	ldr r0, [r4, #4]
	bl MOD55_021D781C
	add r0, r4, #0
	bl MOD55_021D7AE0
	ldr r0, _021D7568 ; =MOD55_021D77D0
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	add r0, r4, #0
	bl MOD55_021D74E0
	pop {r4, pc}
	.align 2, 0
_021D7560: .word 0xFFFFE0FF
_021D7564: .word 0x04001000
_021D7568: .word MOD55_021D77D0
	thumb_func_end MOD55_021D7504

	thumb_func_start MOD55_021D756C
MOD55_021D756C: ; 0x021D756C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5]
	add r6, r0, #0
	cmp r1, #0
	beq _021D7580
	cmp r1, #1
	beq _021D75FC
	b _021D760A
_021D7580:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl MOD55_021DA27C
	mov r2, #1
	mov r0, #3
	mov r1, #0x34
	lsl r2, r2, #0x12
	bl CreateHeap
	ldr r1, _021D7610 ; =0x0000041C
	add r0, r6, #0
	mov r2, #0x34
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D7610 ; =0x0000041C
	mov r1, #0
	add r4, r0, #0
	bl MI_CpuFill8
	add r0, r6, #0
	bl OverlayManager_GetField18
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD55_021D7994
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x11
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r4, #0
	bl MOD55_021D7504
	add r0, r4, #0
	bl MOD55_021D7EE4
	add r0, r4, #0
	bl MOD55_021D8044
	mov r0, #1
	bl MOD55_021DA27C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D760A
_021D75FC:
	bl OverlayManager_GetData
	mov r0, #0
	str r0, [r5]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D760A:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D7610: .word 0x0000041C
	thumb_func_end MOD55_021D756C

	thumb_func_start MOD55_021D7614
MOD55_021D7614: ; 0x021D7614
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5]
	add r6, r0, #0
	cmp r1, #0
	beq _021D7628
	cmp r1, #1
	beq _021D76A4
	b _021D76B2
_021D7628:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r2, #1
	mov r0, #3
	mov r1, #0x34
	lsl r2, r2, #0x12
	bl CreateHeap
	ldr r1, _021D76B8 ; =0x0000041C
	add r0, r6, #0
	mov r2, #0x34
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D76B8 ; =0x0000041C
	mov r1, #0
	add r4, r0, #0
	bl MI_CpuFill8
	add r0, r6, #0
	bl OverlayManager_GetField18
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD55_021D7994
	mov r0, #0
	bl MOD55_021DA27C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x11
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r4, #0
	bl MOD55_021D7504
	add r0, r4, #0
	bl MOD55_021D7EE4
	add r0, r4, #0
	bl MOD55_021D8044
	mov r0, #1
	bl MOD55_021DA27C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D76B2
_021D76A4:
	bl OverlayManager_GetData
	mov r0, #0
	str r0, [r5]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D76B2:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D76B8: .word 0x0000041C
	thumb_func_end MOD55_021D7614

	thumb_func_start MOD55_021D76BC
MOD55_021D76BC: ; 0x021D76BC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0
	beq _021D76D6
	cmp r1, #1
	beq _021D76E4
	cmp r1, #2
	beq _021D76FA
	b _021D770C
_021D76D6:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D770C
	mov r0, #1
	str r0, [r5]
	b _021D770C
_021D76E4:
	mov r2, #0x3b
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	lsl r3, r2, #2
	ldr r2, _021D771C ; =0x021DA4A0
	ldr r2, [r2, r3]
	cmp r2, #0
	beq _021D770C
	blx r2
	str r0, [r5]
	b _021D770C
_021D76FA:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D770C
	mov r0, #0
	bl MOD55_021DA27C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D770C:
	add r4, #0xec
	ldr r0, [r4]
	cmp r0, #0
	beq _021D7718
	bl FUN_0201FDEC
_021D7718:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D771C: .word MOD55_021DA4A0
	thumb_func_end MOD55_021D76BC

	thumb_func_start MOD55_021D7720
MOD55_021D7720: ; 0x021D7720
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x8e
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0x86
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_021D7754:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D7754
	add r0, r6, #0
	add r0, #0xec
	ldr r0, [r0]
	bl FUN_0201FD58
	add r0, r6, #0
	mov r1, #0
	add r0, #0xec
	str r1, [r0]
	bl DeinitOamData
	bl FUN_0201D12C
	bl FUN_0201E08C
	mov r0, #0xeb
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD55_021D7720

	thumb_func_start MOD55_021D778C
MOD55_021D778C: ; 0x021D778C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	add r0, r4, #0
	bl MOD55_021D7720
	add r0, r4, #0
	bl MOD55_021D8140
	ldr r0, [r4, #4]
	bl MOD55_021D7AA4
	pop {r4, pc}
	thumb_func_end MOD55_021D778C

	thumb_func_start MOD55_021D77AC
MOD55_021D77AC: ; 0x021D77AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD55_021D778C
	add r0, r4, #0
	bl MOD55_021D7A38
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0x34
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD55_021D77AC

	thumb_func_start MOD55_021D77D0
MOD55_021D77D0: ; 0x021D77D0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xe0
	ldr r0, [r0]
	cmp r0, #0
	beq _021D77E6
	add r0, r4, #0
	add r0, #0xdc
	ldr r0, [r0]
	bl FUN_020081C4
_021D77E6:
	ldr r0, [r4, #4]
	bl DoScheduledBgGpuUpdates
	bl FUN_0201C30C
	bl ApplyAndResetOamManagerBuffer
	ldr r3, _021D7804 ; =0x027E0000
	ldr r1, _021D7808 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_021D7804: .word 0x027E0000
_021D7808: .word 0x00003FF8
	thumb_func_end MOD55_021D77D0

	thumb_func_start MOD55_021D780C
MOD55_021D780C: ; 0x021D780C
	ldr r3, _021D7814 ; =GX_SetBanks
	ldr r0, _021D7818 ; =0x021DA458
	bx r3
	nop
_021D7814: .word GX_SetBanks
_021D7818: .word MOD55_021DA458
	thumb_func_end MOD55_021D780C

	thumb_func_start MOD55_021D781C
MOD55_021D781C: ; 0x021D781C
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _021D7974 ; =0x021DA2C8
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r5, _021D7978 ; =0x021DA34C
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
	bl InitBgFromTemplate
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #0
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D797C ; =0x021DA368
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
	bl InitBgFromTemplate
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D7980 ; =0x021DA384
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
	bl InitBgFromTemplate
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D7984 ; =0x021DA3A0
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D7988 ; =0x021DA3BC
	add r3, sp, #0
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
	bl InitBgFromTemplate
	add r0, r4, #0
	mov r1, #4
	bl BgClearTilemapBufferAndCommit
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	mov r0, #0
	mov r1, #3
	bl SetBgPriority
	mov r0, #1
	mov r1, #2
	bl SetBgPriority
	mov r0, #3
	mov r1, #1
	bl SetBgPriority
	mov r0, #2
	mov r1, #0
	bl SetBgPriority
	ldr r0, _021D798C ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r0, _021D7990 ; =0x04001050
	strh r1, [r0]
	add sp, #0x9c
	pop {r4, r5, pc}
	.align 2, 0
_021D7974: .word MOD55_021DA2C8
_021D7978: .word MOD55_021DA34C
_021D797C: .word MOD55_021DA368
_021D7980: .word MOD55_021DA384
_021D7984: .word MOD55_021DA3A0
_021D7988: .word MOD55_021DA3BC
_021D798C: .word 0x04000050
_021D7990: .word 0x04001050
	thumb_func_end MOD55_021D781C

	thumb_func_start MOD55_021D7994
MOD55_021D7994: ; 0x021D7994
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x34
	bl MessageFormat_New
	str r0, [r6, #0xc]
	ldr r2, _021D7A34 ; =0x00000251
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x34
	bl NewMsgDataFromNarc
	str r0, [r6, #0x10]
	mov r4, #0
	add r5, r6, #0
	mov r7, #0x10
_021D79B4:
	add r0, r7, #0
	mov r1, #0x34
	bl String_New
	str r0, [r5, #0x38]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x20
	blt _021D79B4
	mov r0, #0x10
	mov r1, #0x34
	bl String_New
	add r1, r6, #0
	add r1, #0xd4
	str r0, [r1]
	mov r0, #0x1a
	mov r1, #0x34
	bl String_New
	add r1, r6, #0
	add r1, #0xd8
	str r0, [r1]
	mov r0, #0xb4
	mov r1, #0x34
	bl String_New
	add r1, r6, #0
	add r1, #0xbc
	str r0, [r1]
	mov r5, #0
	add r4, r6, #0
	mov r7, #0xb4
_021D79F6:
	add r0, r7, #0
	mov r1, #0x34
	bl String_New
	add r1, r4, #0
	add r1, #0xc4
	add r5, r5, #1
	add r4, r4, #4
	str r0, [r1]
	cmp r5, #4
	blt _021D79F6
	mov r0, #0xb4
	mov r1, #0x34
	bl String_New
	add r1, r6, #0
	add r1, #0xb8
	str r0, [r1]
	mov r0, #0x28
	mov r1, #0x34
	bl String_New
	add r1, r6, #0
	add r1, #0xc0
	str r0, [r1]
	mov r0, #0x3b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7A34: .word 0x00000251
	thumb_func_end MOD55_021D7994

	thumb_func_start MOD55_021D7A38
MOD55_021D7A38: ; 0x021D7A38
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x10]
	bl DestroyMsgData
	ldr r0, [r6, #0xc]
	bl MessageFormat_Delete
	mov r4, #0
	add r5, r6, #0
_021D7A4C:
	ldr r0, [r5, #0x38]
	bl String_Delete
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x20
	blt _021D7A4C
	add r0, r6, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl String_Delete
	add r0, r6, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl String_Delete
	add r0, r6, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl String_Delete
	mov r5, #0
	add r4, r6, #0
_021D7A7C:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl String_Delete
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #4
	blt _021D7A7C
	add r0, r6, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl String_Delete
	add r6, #0xd8
	ldr r0, [r6]
	bl String_Delete
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD55_021D7A38

	thumb_func_start MOD55_021D7AA4
MOD55_021D7AA4: ; 0x021D7AA4
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #4
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #3
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #2
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #1
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	mov r1, #0
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD55_021D7AA4

	thumb_func_start MOD55_021D7AE0
MOD55_021D7AE0: ; 0x021D7AE0
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r2, #0
	str r2, [sp]
	mov r0, #0x34
	str r0, [sp, #4]
	mov r0, #0x59
	mov r1, #3
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r3, #0
	str r3, [sp]
	mov r0, #0x34
	str r0, [sp, #4]
	mov r0, #0x59
	mov r1, #3
	mov r2, #4
	bl GfGfxLoader_GXLoadPal
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x34
	bl FUN_02002EEC
	mov r1, #6
	mov r0, #0
	lsl r1, r1, #6
	mov r2, #0x34
	bl FUN_02002EEC
	ldr r1, _021D7BE4 ; =0x000052D8
	add r0, sp, #0x10
	strh r1, [r0]
	mov r1, #0x6f
	add r0, sp, #0x10
	lsl r1, r1, #2
	mov r2, #2
	bl GX_LoadBGPltt
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	mov r0, #0x59
	mov r1, #2
	add r2, r4, #0
	bl GfGfxLoader_LoadCharData
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	mov r0, #0x59
	mov r1, #8
	add r2, r4, #0
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x59
	mov r1, #4
	mov r3, #1
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	mov r0, #0x59
	mov r1, #0xa
	add r2, r4, #0
	mov r3, #4
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	mov r0, #0x59
	mov r1, #0xb
	add r2, r4, #0
	mov r3, #4
	bl GfGfxLoader_LoadScrnData
	ldr r0, [r5, #8]
	bl Save_PlayerData_GetOptionsAddr
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x34
	str r0, [sp, #4]
	ldr r2, _021D7BE8 ; =0x000001E2
	add r0, r4, #0
	mov r1, #2
	mov r3, #0xa
	bl FUN_0200CD68
	mov r0, #0
	str r0, [sp]
	mov r0, #0x34
	str r0, [sp, #4]
	ldr r2, _021D7BEC ; =0x000001D9
	add r0, r4, #0
	mov r1, #2
	mov r3, #0xb
	bl LoadUserFrameGfx1
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021D7BE4: .word 0x000052D8
_021D7BE8: .word 0x000001E2
_021D7BEC: .word 0x000001D9
	thumb_func_end MOD55_021D7AE0

	thumb_func_start MOD55_021D7BF0
MOD55_021D7BF0: ; 0x021D7BF0
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D7C1C ; =0x021DA2E8
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x34
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D7C1C: .word MOD55_021DA2E8
	thumb_func_end MOD55_021D7BF0

	thumb_func_start MOD55_021D7C20
MOD55_021D7C20: ; 0x021D7C20
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
	mov r2, #0x34
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r5, #0
	mov r0, #0x1e
	add r1, #0xf0
	mov r2, #0x34
	bl FUN_02008C9C
	add r1, r5, #0
	add r1, #0xec
	str r0, [r1]
	add r0, r5, #0
	mov r2, #1
	add r0, #0xf0
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r7, #0x86
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #2
_021D7C6A:
	mov r0, #2
	add r1, r6, #0
	mov r2, #0x34
	bl FUN_02008DEC
	str r0, [r4, r7]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _021D7C6A
	mov r3, #1
	str r3, [sp]
	str r3, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x56
	mov r2, #9
	bl FUN_02008F34
	mov r1, #0x8e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	sub r1, #0x20
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x59
	mov r2, #9
	bl FUN_02008F34
	mov r1, #0x8a
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	mov r0, #0x34
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x56
	mov r2, #7
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x8f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	mov r0, #0x34
	sub r1, #0x20
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x59
	mov r2, #3
	bl FUN_02008FEC
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x34
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x56
	mov r2, #0xa
	bl FUN_020090AC
	mov r1, #9
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x34
	sub r1, #0x20
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x59
	mov r2, #1
	bl FUN_020090AC
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x34
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x56
	mov r2, #0xb
	bl FUN_020090AC
	mov r1, #0x91
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r2, #0
	str r2, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x34
	sub r1, #0x20
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x59
	add r3, r2, #0
	bl FUN_020090AC
	mov r1, #0x8d
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #4
	ldr r0, [r5, r0]
	bl FUN_02009A50
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009A50
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD55_021D7C20

	thumb_func_start MOD55_021D7DA0
MOD55_021D7DA0: ; 0x021D7DA0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	mov r1, #0
	add r5, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r2, #0x86
	str r1, [sp, #0x10]
	lsl r2, r2, #2
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
	mov r3, #0x86
	str r1, [sp]
	sub r0, r1, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r3, r3, #2
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
	add r0, r5, #0
	add r0, #0xec
	ldr r0, [r0]
	mov r4, #0
	str r0, [sp, #0x2c]
	mov r0, #0x9b
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x30]
	mov r0, #1
	lsl r0, r0, #0xc
	mov r7, #0x62
	str r4, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r4, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x50]
	str r0, [sp, #0x54]
	mov r0, #0x34
	str r0, [sp, #0x58]
	mov r0, #0x92
	lsl r0, r0, #2
	lsl r7, r7, #0xc
	add r6, r5, r0
_021D7E56:
	asr r0, r4, #1
	lsr r0, r0, #0x1e
	add r0, r4, r0
	asr r1, r0, #2
	mov r0, #0x78
	mul r0, r1
	add r0, #0x16
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #5
	add r0, #0x2b
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	cmp r4, #8
	bne _021D7E8C
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	str r7, [sp, #0x38]
	str r6, [sp, #0x30]
	b _021D7E9A
_021D7E8C:
	cmp r4, #9
	bne _021D7E9A
	mov r0, #0xf9
	lsl r0, r0, #0xc
	str r0, [sp, #0x34]
	str r7, [sp, #0x38]
	str r6, [sp, #0x30]
_021D7E9A:
	add r0, sp, #0x2c
	bl FUN_0201FE94
	mov r1, #0x29
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r4, #0
	sub r0, #8
	cmp r0, #1
	bhi _021D7EB8
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
_021D7EB8:
	mov r0, #0x29
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_02020238
	mov r0, #0x29
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa
	blt _021D7E56
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD55_021D7DA0

	thumb_func_start MOD55_021D7EE4
MOD55_021D7EE4: ; 0x021D7EE4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D7F02
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021D7F02:
	mov r0, #0
	str r0, [sp]
	mov r0, #0xd
	str r0, [sp, #4]
	mov r2, #3
	str r2, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _021D8038 ; =0x00000171
	mov r1, #0xe6
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	mov r3, #1
	bl AddWindowParameterized
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r2, r5, #0
	add r2, #0xc0
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	mov r1, #0
	bl ReadMsgDataIntoString
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D803C ; =0x000F0E00
	add r2, r5, #0
	str r0, [sp, #8]
	mov r3, #0
	mov r0, #0xe6
	lsl r0, r0, #2
	str r3, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized2
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl ScheduleWindowCopyToVram
	mov r6, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	add r4, r5, r0
	str r6, [sp, #0x18]
	str r6, [sp, #0x14]
	add r7, r5, #0
_021D7F76:
	add r0, r4, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D7F86
	add r0, r4, #0
	bl RemoveWindow
_021D7F86:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	add r0, r0, #5
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x15
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021D8038 ; =0x00000171
	add r1, #0x3c
	sub r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	add r1, r4, #0
	mov r2, #3
	mov r3, #7
	bl AddWindowParameterized
	add r0, r4, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	cmp r6, #2
	bne _021D7FF4
	ldr r0, [r5, #8]
	bl Save_PlayerData_GetProfileAddr
	add r2, r0, #0
	ldr r0, [r5, #0xc]
	mov r1, #0
	bl BufferPlayersName
	add r2, r5, #0
	add r2, #0xb8
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	add r1, r6, #1
	bl ReadMsgDataIntoString
	add r1, r7, #0
	add r2, r5, #0
	add r1, #0xc4
	add r2, #0xb8
	ldr r0, [r5, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	b _021D8002
_021D7FF4:
	add r2, r7, #0
	add r2, #0xc4
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	add r1, r6, #1
	bl ReadMsgDataIntoString
_021D8002:
	ldr r0, _021D8040 ; =0x00010200
	add r1, r7, #0
	str r0, [sp]
	add r1, #0xc4
	ldr r1, [r1]
	add r0, r4, #0
	mov r2, #0xff
	mov r3, #0x90
	bl MOD55_021D80F0
	add r0, r4, #0
	bl ScheduleWindowCopyToVram
	ldr r0, [sp, #0x18]
	add r6, r6, #1
	add r0, #0x3c
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r4, #0x10
	add r0, r0, #5
	add r7, r7, #4
	str r0, [sp, #0x14]
	cmp r6, #4
	blt _021D7F76
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D8038: .word 0x00000171
_021D803C: .word 0x000F0E00
_021D8040: .word 0x00010200
	thumb_func_end MOD55_021D7EE4

	thumb_func_start MOD55_021D8044
MOD55_021D8044: ; 0x021D8044
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r1, _021D80E8 ; =0x021DA298
	str r0, [sp]
	ldrb r2, [r1, #8]
	add r0, sp, #0x10
	strb r2, [r0]
	ldrb r2, [r1, #9]
	strb r2, [r0, #1]
	ldrb r2, [r1, #0xa]
	ldrb r1, [r1, #0xb]
	strb r2, [r0, #2]
	strb r1, [r0, #3]
	ldr r0, [sp]
	mov r1, #1
	ldr r0, [r0, #4]
	bl GetBgTilemapBuffer
	mov ip, r0
	mov r1, #0xf2
	ldr r0, [sp]
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #8]
_021D8078:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #8]
	cmp r1, r0
	bne _021D8086
	mov r3, #1
	lsl r3, r3, #0xc
	b _021D8088
_021D8086:
	mov r3, #0
_021D8088:
	add r1, sp, #0x10
	ldrb r7, [r1, #1]
	ldrb r0, [r1, #3]
	add r0, r7, r0
	str r0, [sp, #4]
	cmp r7, r0
	bge _021D80C6
	ldrb r2, [r1]
	ldrb r1, [r1, #2]
	lsl r0, r7, #5
	ldr r4, _021D80EC ; =0x00000FFF
	add r6, r2, r0
_021D80A0:
	mov r0, #0
	cmp r1, #0
	ble _021D80BC
	lsl r5, r6, #1
	mov r2, ip
	add r2, r2, r5
_021D80AC:
	ldrh r5, [r2]
	add r0, r0, #1
	and r5, r4
	add r5, r3, r5
	strh r5, [r2]
	add r2, r2, #2
	cmp r0, r1
	blt _021D80AC
_021D80BC:
	ldr r0, [sp, #4]
	add r7, r7, #1
	add r6, #0x20
	cmp r7, r0
	blt _021D80A0
_021D80C6:
	add r0, sp, #0x10
	ldrb r1, [r0, #1]
	add r1, r1, #5
	strb r1, [r0, #1]
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #4
	blt _021D8078
	ldr r0, [sp]
	mov r1, #1
	ldr r0, [r0, #4]
	bl BgCommitTilemapBufferToVram
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D80E8: .word MOD55_021DA298
_021D80EC: .word 0x00000FFF
	thumb_func_end MOD55_021D8044

	thumb_func_start MOD55_021D80F0
MOD55_021D80F0: ; 0x021D80F0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0
	add r4, r2, #0
	add r7, r3, #0
	add r2, r0, #0
	add r6, r1, #0
	bl FUN_02002E14
	sub r1, r7, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	ldr r1, [sp, #0x28]
	asr r3, r0, #1
	cmp r1, #0
	bne _021D8128
	mov r0, #1
	str r0, [sp]
	str r4, [sp, #4]
	mov r1, #0
	add r0, r5, #0
	add r2, r6, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_021D8128:
	mov r0, #1
	str r0, [sp]
	str r4, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	add r0, r5, #0
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD55_021D80F0

	thumb_func_start MOD55_021D8140
MOD55_021D8140: ; 0x021D8140
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r0, #0xae
	lsl r0, r0, #2
	mov r4, #0
	add r5, r6, r0
_021D814C:
	add r0, r5, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D815C
	add r0, r5, #0
	bl RemoveWindow
_021D815C:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #8
	blt _021D814C
	mov r0, #0xd2
	lsl r0, r0, #2
	mov r5, #0
	add r4, r6, r0
_021D816C:
	add r0, r4, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D817C
	add r0, r4, #0
	bl RemoveWindow
_021D817C:
	add r5, r5, #1
	add r4, #0x10
	cmp r5, #4
	blt _021D816C
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r6, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D819C
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r6, r0
	bl RemoveWindow
_021D819C:
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r6, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D81B4
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r6, r0
	bl RemoveWindow
_021D81B4:
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r6, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D81CC
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r6, r0
	bl RemoveWindow
_021D81CC:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD55_021D8140

	thumb_func_start MOD55_021D81D0
MOD55_021D81D0: ; 0x021D81D0
	mov r2, #0x3b
	mov r3, #1
	lsl r2, r2, #4
	str r3, [r0, r2]
	add r0, r1, #0
	bx lr
	thumb_func_end MOD55_021D81D0

	thumb_func_start MOD55_021D81DC
MOD55_021D81DC: ; 0x021D81DC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl FUN_0200E308
	cmp r0, #0
	bne _021D81EE
	add r0, r5, #0
	pop {r3, r4, r5, pc}
_021D81EE:
	ldr r2, _021D82B8 ; =gSystem
	mov r1, #1
	ldr r0, [r2, #0x48]
	tst r1, r0
	beq _021D824C
	ldr r0, _021D82BC ; =0x000005DC
	bl PlaySE
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	cmp r1, #3
	bhi _021D82B2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8214: ; jump table
	.short _021D821C - _021D8214 - 2 ; case 0
	.short _021D8234 - _021D8214 - 2 ; case 1
	.short _021D823C - _021D8214 - 2 ; case 2
	.short _021D8244 - _021D8214 - 2 ; case 3
_021D821C:
	mov r2, #0
	strb r2, [r4, r0]
	add r1, r0, #3
	strb r2, [r4, r1]
	add r1, r0, #1
	strb r2, [r4, r1]
	add r1, r0, #2
	strb r2, [r4, r1]
	mov r1, #2
	sub r0, #0x18
	str r1, [r4, r0]
	b _021D82B2
_021D8234:
	mov r1, #7
	sub r0, #0x18
	str r1, [r4, r0]
	b _021D82B2
_021D823C:
	mov r1, #0x12
	sub r0, #0x18
	str r1, [r4, r0]
	b _021D82B2
_021D8244:
	mov r1, #0x11
	sub r0, #0x18
	str r1, [r4, r0]
	b _021D82B2
_021D824C:
	mov r1, #2
	tst r0, r1
	beq _021D8262
	ldr r0, _021D82BC ; =0x000005DC
	bl PlaySE
	mov r0, #0x3b
	mov r1, #0x11
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _021D82B2
_021D8262:
	ldr r1, [r2, #0x4c]
	mov r0, #0x40
	tst r0, r1
	beq _021D828C
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _021D82B2
	ldr r0, _021D82BC ; =0x000005DC
	bl PlaySE
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD55_021D8044
	b _021D82B2
_021D828C:
	mov r0, #0x80
	tst r0, r1
	beq _021D82B2
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r0, #3
	bhs _021D82B2
	ldr r0, _021D82BC ; =0x000005DC
	bl PlaySE
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD55_021D8044
_021D82B2:
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	nop
_021D82B8: .word gSystem
_021D82BC: .word 0x000005DC
	thumb_func_end MOD55_021D81DC

	thumb_func_start MOD55_021D82C0
MOD55_021D82C0: ; 0x021D82C0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	ldr r0, [r7, #8]
	str r1, [sp, #0xc]
	bl FUN_020286EC
	mov r6, #0
	add r4, r0, #0
	add r5, r6, #0
_021D82D4:
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _021D82E2
	mov r6, #1
_021D82E2:
	add r5, r5, #1
	cmp r5, #0x20
	blt _021D82D4
	cmp r6, #0
	beq _021D8308
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x10
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r1, #8
	b _021D8312
_021D8308:
	add r0, r7, #0
	mov r1, #0x1d
	bl MOD55_021DA0A4
	mov r1, #0xf
_021D8312:
	mov r0, #0x3b
	lsl r0, r0, #4
	str r1, [r7, r0]
	ldr r0, [sp, #0xc]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD55_021D82C0

	thumb_func_start MOD55_021D8320
MOD55_021D8320: ; 0x021D8320
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _021D8366
	mov r0, #0
	bl MOD55_021DA27C
	add r0, r5, #0
	bl MOD55_021D778C
	ldr r0, [r5, #8]
	bl Save_PlayerData_GetOptionsAddr
	mov r1, #7
	str r0, [sp]
	mov r0, #0x34
	mov r2, #0
	add r3, r1, #0
	bl FUN_02077A84
	str r0, [r5]
	ldr r0, _021D836C ; =UNK_020FA5FC
	ldr r1, [r5]
	mov r2, #0x34
	bl OverlayManager_New
	mov r1, #0x3d
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #9
	sub r1, #0x20
	str r0, [r5, r1]
_021D8366:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D836C: .word UNK_020FA5FC
	thumb_func_end MOD55_021D8320

	thumb_func_start MOD55_021D8370
MOD55_021D8370: ; 0x021D8370
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl OverlayManager_Run
	cmp r0, #0
	beq _021D83FC
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl OverlayManager_Delete
	ldr r1, [r5]
	ldr r0, [r1, #0x14]
	cmp r0, #0
	bne _021D83A8
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	ldr r1, [r1, #0x18]
	bl StringCopy
	mov r1, #0xa
	b _021D83F0
_021D83A8:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl MOD55_021DA27C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x11
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r5, #0
	bl MOD55_021D7504
	add r0, r5, #0
	bl MOD55_021D7EE4
	add r0, r5, #0
	bl MOD55_021D8044
	mov r0, #1
	bl MOD55_021DA27C
	mov r1, #6
_021D83F0:
	mov r0, #0x3b
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [r5]
	bl FUN_02077AC4
_021D83FC:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD55_021D8370

	thumb_func_start MOD55_021D8404
MOD55_021D8404: ; 0x021D8404
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r4, r1, #0
	bl Save_PlayerData_GetOptionsAddr
	str r0, [sp]
	mov r0, #0x34
	mov r1, #4
	mov r2, #0
	mov r3, #0xc
	bl FUN_02077A84
	str r0, [r5]
	ldr r0, _021D843C ; =UNK_020FA5FC
	ldr r1, [r5]
	mov r2, #0x34
	bl OverlayManager_New
	mov r1, #0x3d
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #0xb
	sub r1, #0x20
	str r0, [r5, r1]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D843C: .word UNK_020FA5FC
	thumb_func_end MOD55_021D8404

	thumb_func_start MOD55_021D8440
MOD55_021D8440: ; 0x021D8440
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl OverlayManager_Run
	cmp r0, #0
	beq _021D84C2
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl OverlayManager_Delete
	add r0, r5, #0
	ldr r1, [r5]
	add r0, #0xd8
	ldr r0, [r0]
	ldr r1, [r1, #0x18]
	bl StringCopy
	ldr r0, [r5]
	bl FUN_02077AC4
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl MOD55_021DA27C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x11
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r5, #0
	bl MOD55_021D7504
	add r0, r5, #0
	bl MOD55_021D7EE4
	add r0, r5, #0
	bl MOD55_021D8044
	mov r0, #1
	bl MOD55_021DA27C
	mov r0, #0x3b
	mov r1, #0xc
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D84C2:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD55_021D8440

	thumb_func_start MOD55_021D84C8
MOD55_021D84C8: ; 0x021D84C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _021D853C
	add r0, r5, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r1, sp, #4
	bl String_atoi
	str r0, [sp]
	ldr r0, [sp, #4]
	add r7, r1, #0
	cmp r0, #0
	beq _021D8534
	mov r0, #0x34
	bl PlayerProfile_New
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	bl String_c_str
	add r1, r0, #0
	add r0, r4, #0
	bl CopyPlayerName
	ldr r0, [r5, #0xc]
	mov r1, #0
	add r2, r4, #0
	bl BufferPlayersName
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r7, #0
	bl MOD55_021D93F8
	add r0, r5, #0
	mov r1, #0x19
	bl MOD55_021DA0A4
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #0x3b
	mov r1, #0xd
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _021D853C
_021D8534:
	mov r0, #0x3b
	mov r1, #0xf
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D853C:
	add r0, r6, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD55_021D84C8

	thumb_func_start MOD55_021D8544
MOD55_021D8544: ; 0x021D8544
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8578
	mov r0, #0x34
	str r0, [sp]
	ldr r0, [r5, #4]
	ldr r1, _021D857C ; =0x021DA2AC
	ldr r2, _021D8580 ; =0x000001D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	add r1, r5, #0
	add r1, #0xe8
	str r0, [r1]
	mov r0, #0x3b
	mov r1, #0xe
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D8578:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D857C: .word MOD55_021DA2AC
_021D8580: .word 0x000001D9
	thumb_func_end MOD55_021D8544

	thumb_func_start MOD55_021D8584
MOD55_021D8584: ; 0x021D8584
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, #0xe8
	str r1, [sp]
	ldr r0, [r0]
	mov r1, #0x34
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021D85A4
	ldr r0, [sp]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021D85A4:
	cmp r0, #0
	bne _021D866C
	ldr r0, [r5, #8]
	bl FUN_020286EC
	str r0, [sp, #4]
	mov r4, #0
_021D85B2:
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _021D8666
	add r0, r5, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r1, sp, #8
	bl String_atoi
	add r7, r0, #0
	ldr r0, [sp, #4]
	add r6, r1, #0
	bl FUN_02028228
	bl DWC_CreateFriendKey
	eor r1, r6
	eor r0, r7
	orr r0, r1
	bne _021D85E4
	mov r0, #0
	str r0, [sp, #8]
_021D85E4:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _021D8650
	ldr r0, [r5, #8]
	add r1, r4, #0
	add r2, r7, #0
	add r3, r6, #0
	bl MOD55_021DA224
	cmp r0, #0
	bne _021D8616
	add r2, r5, #0
	add r2, #0xd4
	ldr r0, [sp, #4]
	ldr r2, [r2]
	add r1, r4, #0
	bl FUN_020283C0
	ldr r0, [sp, #4]
	add r1, r4, #0
	mov r2, #8
	mov r3, #2
	bl FUN_020282E8
	b _021D866C
_021D8616:
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021D8634
	add r0, r5, #0
	mov r1, #0x1a
	bl MOD55_021DA0A4
	mov r0, #0x3b
	mov r1, #0xf
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021D8634:
	sub r1, r1, #1
	cmp r0, r1
	bne _021D8666
	add r0, r5, #0
	mov r1, #0x1e
	bl MOD55_021DA0A4
	mov r0, #0x3b
	mov r1, #0xf
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021D8650:
	add r0, r5, #0
	mov r1, #0x1a
	bl MOD55_021DA0A4
	mov r0, #0x3b
	mov r1, #0xf
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_021D8666:
	add r4, r4, #1
	cmp r4, #0x20
	blt _021D85B2
_021D866C:
	add r0, r5, #0
	bl MOD55_021DA214
	mov r0, #0x3b
	mov r1, #6
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD55_021D8584

	thumb_func_start MOD55_021D8680
MOD55_021D8680: ; 0x021D8680
	mov r2, #0x3b
	mov r3, #0x10
	lsl r2, r2, #4
	str r3, [r0, r2]
	add r0, r1, #0
	bx lr
	thumb_func_end MOD55_021D8680

	thumb_func_start MOD55_021D868C
MOD55_021D868C: ; 0x021D868C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D86CA
	ldr r0, _021D86D0 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021D86CA
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl ClearFrameAndWindow2
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl ClearWindowTilemapAndCopyToVram
	mov r0, #0x3b
	mov r1, #6
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D86CA:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D86D0: .word gSystem
	thumb_func_end MOD55_021D868C

	thumb_func_start MOD55_021D86D4
MOD55_021D86D4: ; 0x021D86D4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	ldr r1, _021D88C4 ; =0x021DA298
	str r0, [sp]
	ldrb r2, [r1]
	add r0, sp, #0x28
	strb r2, [r0, #0x14]
	ldrb r2, [r1, #1]
	strb r2, [r0, #0x15]
	ldrb r2, [r1, #2]
	strb r2, [r0, #0x16]
	ldrb r2, [r1, #3]
	strb r2, [r0, #0x17]
	ldrb r2, [r1, #4]
	strb r2, [r0, #0x10]
	ldrb r2, [r1, #5]
	strb r2, [r0, #0x11]
	ldrb r2, [r1, #6]
	strb r2, [r0, #0x12]
	ldrb r1, [r1, #7]
	strb r1, [r0, #0x13]
	ldr r0, [sp]
	mov r1, #1
	ldr r0, [r0, #4]
	bl GetBgTilemapBuffer
	str r0, [sp, #0x24]
	mov r1, #0xf2
	ldr r0, [sp]
	lsl r1, r1, #2
	ldrb r3, [r0, r1]
	mov r0, #0x1d
	lsr r2, r3, #0x1f
	lsl r1, r3, #0x1d
	sub r1, r1, r2
	ror r1, r0
	add r0, r2, r1
	str r0, [sp, #0x20]
	lsr r0, r3, #3
	str r0, [sp, #0xc]
	ldr r0, [sp]
	ldr r0, [r0, #8]
	bl FUN_020286EC
	ldr r1, _021D88C4 ; =0x021DA298
	str r0, [sp, #0x18]
	ldrh r2, [r1, #0x1c]
	add r0, sp, #0x28
	strh r2, [r0, #8]
	ldrh r2, [r1, #0x1e]
	strh r2, [r0, #0xa]
	ldrh r2, [r1, #0x20]
	strh r2, [r0, #0xc]
	ldrh r2, [r1, #0x22]
	strh r2, [r0, #0xe]
	ldrh r2, [r1, #0xc]
	strh r2, [r0]
	ldrh r2, [r1, #0xe]
	strh r2, [r0, #2]
	ldrh r2, [r1, #0x10]
	strh r2, [r0, #4]
	ldrh r1, [r1, #0x12]
	strh r1, [r0, #6]
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	lsl r1, r0, #3
	ldr r0, [sp]
	add r0, r0, r1
	str r0, [sp, #0x14]
_021D8760:
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0x18]
	ldrb r1, [r1, #0x18]
	mov r2, #8
	sub r1, r1, #1
	bl FUN_0202822C
	ldr r1, [sp, #0x14]
	ldrb r1, [r1, #0x18]
	cmp r1, #0
	beq _021D877E
	cmp r0, #2
	beq _021D877E
	add r3, sp, #0x28
	b _021D8780
_021D877E:
	add r3, sp, #0x30
_021D8780:
	add r1, sp, #0x28
	ldrb r7, [r1, #0x11]
	ldrb r0, [r1, #0x13]
	add r0, r7, r0
	str r0, [sp, #0x10]
	cmp r7, r0
	bge _021D87BE
	ldrb r2, [r1, #0x10]
	ldrb r4, [r1, #0x12]
	lsl r0, r7, #5
	add r2, r2, r0
_021D8796:
	add r0, r2, #0
	mov r1, #0
	cmp r4, #0
	ble _021D87B4
	ldr r5, [sp, #0x24]
	lsl r6, r2, #1
	add r6, r5, r6
_021D87A4:
	ldrh r5, [r3]
	add r1, r1, #1
	add r3, r3, #2
	strh r5, [r6]
	add r6, r6, #2
	add r0, r0, #1
	cmp r1, r4
	blt _021D87A4
_021D87B4:
	ldr r0, [sp, #0x10]
	add r7, r7, #1
	add r2, #0x20
	cmp r7, r0
	blt _021D8796
_021D87BE:
	add r1, sp, #0x28
	ldrb r0, [r1, #0x11]
	add r0, r0, #4
	strb r0, [r1, #0x11]
	ldr r0, [sp, #0x1c]
	cmp r0, #3
	bne _021D87D4
	mov r0, #5
	strb r0, [r1, #0x11]
	mov r0, #0x11
	strb r0, [r1, #0x10]
_021D87D4:
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, #8
	blt _021D8760
	mov r0, #0x3f
	mov r4, #0x17
	mov r3, #0
	mov r7, #0x16
	mov r2, #2
	lsl r0, r0, #0xa
_021D87F0:
	ldr r5, [sp, #0xc]
	add r1, r4, #0
	add r1, #0x20
	cmp r3, r5
	bne _021D87FE
	add r5, r2, #0
	b _021D8800
_021D87FE:
	add r5, r7, #0
_021D8800:
	ldr r6, [sp, #0x24]
	lsl r1, r1, #1
	ldrh r6, [r6, r1]
	add r3, r3, #1
	add r4, r4, #2
	and r6, r0
	add r6, r5, r6
	ldr r5, [sp, #0x24]
	cmp r3, #4
	strh r6, [r5, r1]
	blt _021D87F0
	ldr r1, _021D88C8 ; =0x000003CB
	ldr r0, [sp]
	ldrb r0, [r0, r1]
	cmp r0, #0
	beq _021D8824
	mov r0, #8
	str r0, [sp, #0x20]
_021D8824:
	mov r0, #0
	str r0, [sp, #8]
_021D8828:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #8]
	cmp r1, r0
	bne _021D8836
	mov r4, #1
	lsl r4, r4, #0xc
	b _021D8838
_021D8836:
	mov r4, #0
_021D8838:
	add r0, sp, #0x28
	ldrb r1, [r0, #0x15]
	ldrb r2, [r0, #0x17]
	str r1, [sp, #4]
	add r1, r1, r2
	ldr r2, [sp, #4]
	mov ip, r1
	cmp r2, r1
	bge _021D8884
	ldrb r2, [r0, #0x14]
	ldr r1, [sp, #4]
	ldrb r0, [r0, #0x16]
	lsl r1, r1, #5
	ldr r6, _021D88CC ; =0x00000FFF
	add r7, r2, r1
_021D8856:
	add r2, r7, #0
	mov r3, #0
	cmp r0, #0
	ble _021D8876
	ldr r1, [sp, #0x24]
	lsl r5, r7, #1
	add r1, r1, r5
_021D8864:
	ldrh r5, [r1]
	add r3, r3, #1
	add r2, r2, #1
	and r5, r6
	add r5, r4, r5
	strh r5, [r1]
	add r1, r1, #2
	cmp r3, r0
	blt _021D8864
_021D8876:
	ldr r1, [sp, #4]
	add r7, #0x20
	add r2, r1, #1
	mov r1, ip
	str r2, [sp, #4]
	cmp r2, r1
	blt _021D8856
_021D8884:
	add r1, sp, #0x28
	ldrb r0, [r1, #0x15]
	add r0, r0, #4
	strb r0, [r1, #0x15]
	ldr r0, [sp, #8]
	cmp r0, #3
	bne _021D889A
	mov r0, #4
	strb r0, [r1, #0x15]
	mov r0, #0x10
	strb r0, [r1, #0x14]
_021D889A:
	ldr r0, [sp, #8]
	cmp r0, #7
	bne _021D88AA
	mov r1, #0x14
	add r0, sp, #0x28
	strb r1, [r0, #0x15]
	mov r1, #9
	strb r1, [r0, #0x14]
_021D88AA:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #9
	blt _021D8828
	ldr r0, [sp]
	mov r1, #1
	ldr r0, [r0, #4]
	bl BgCommitTilemapBufferToVram
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D88C4: .word MOD55_021DA298
_021D88C8: .word 0x000003CB
_021D88CC: .word 0x00000FFF
	thumb_func_end MOD55_021D86D4

	thumb_func_start MOD55_021D88D0
MOD55_021D88D0: ; 0x021D88D0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	ldr r0, [r0, #8]
	bl FUN_020286EC
	mov r1, #0xf2
	ldr r5, [sp]
	add r7, r0, #0
	lsl r1, r1, #2
	add r0, r5, #0
	ldrb r0, [r0, r1]
	mov r4, #0
	lsr r0, r0, #3
	lsl r1, r0, #3
	add r0, r5, #0
	add r6, r0, r1
_021D88F2:
	mov r0, #0x29
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	ldrb r0, [r6, #0x18]
	cmp r0, #0
	beq _021D8968
	sub r0, r0, #1
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r7, #0
	mov r2, #7
	bl FUN_0202822C
	str r0, [sp, #8]
	ldr r1, [sp, #4]
	add r0, r7, #0
	mov r2, #8
	bl FUN_0202822C
	cmp r0, #2
	beq _021D8968
	ldr r1, [sp, #8]
	mov r2, #0
	bl FUN_020536D0
	str r0, [sp, #0xc]
	mov r0, #0xeb
	ldr r1, [sp]
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	ldr r0, [sp, #0xc]
	mov r2, #0x20
	lsl r0, r0, #5
	add r0, r1, r0
	add r1, r4, #7
	lsl r1, r1, #5
	bl GX_LoadOBJPltt
	mov r0, #0x29
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #7
	bl FUN_02020248
	mov r0, #0x29
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r1, [sp, #0xc]
	bl FUN_02020130
	mov r0, #0x29
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
_021D8968:
	add r4, r4, #1
	add r5, r5, #4
	add r6, r6, #1
	cmp r4, #8
	blt _021D88F2
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD55_021D88D0

	thumb_func_start MOD55_021D8978
MOD55_021D8978: ; 0x021D8978
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	str r0, [sp, #0x10]
	ldr r0, [r0, #8]
	bl FUN_020286EC
	add r2, sp, #0x20
	ldr r3, _021D8A24 ; =0x021DA2BC
	str r0, [sp, #0x18]
	ldmia r3!, {r0, r1}
	str r2, [sp, #0x1c]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #0xf2
	str r0, [r2]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	lsl r1, r1, #2
	ldrb r0, [r0, r1]
	lsr r0, r0, #3
	lsl r1, r0, #3
	ldr r0, [sp, #0x10]
	add r4, r0, r1
	mov r1, #0xae
	lsl r1, r1, #2
	add r5, r0, r1
_021D89AE:
	ldrb r0, [r4, #0x18]
	mov r7, #0
	cmp r0, #0
	beq _021D8A00
	sub r6, r0, #1
	ldr r0, [sp, #0x18]
	add r1, r6, #0
	bl FUN_0202842C
	cmp r0, #0
	beq _021D8A00
	ldr r0, [sp, #0x18]
	add r1, r6, #0
	mov r2, #8
	bl FUN_0202822C
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	lsl r1, r7, #2
	ldr r0, [r0, r1]
	ldr r2, [sp, #0x10]
	str r0, [sp, #8]
	mov r0, #0
	lsl r3, r6, #2
	str r0, [sp, #0xc]
	add r2, r2, r3
	ldr r2, [r2, #0x38]
	add r0, r5, #0
	mov r1, #0
	mov r3, #1
	bl AddTextPrinterParameterized2
	mov r7, #1
_021D8A00:
	cmp r7, #0
	bne _021D8A0C
	add r0, r5, #0
	bl ClearWindowTilemapAndScheduleTransfer
	b _021D8A12
_021D8A0C:
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
_021D8A12:
	ldr r0, [sp, #0x14]
	add r4, r4, #1
	add r0, r0, #1
	add r5, #0x10
	str r0, [sp, #0x14]
	cmp r0, #8
	blt _021D89AE
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8A24: .word MOD55_021DA2BC
	thumb_func_end MOD55_021D8978

	thumb_func_start MOD55_021D8A28
MOD55_021D8A28: ; 0x021D8A28
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	ldr r0, [r0, #8]
	bl FUN_020286EC
	add r7, r0, #0
	ldr r0, [sp]
	mov r6, #0
	add r0, #0x18
	add r1, r6, #0
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r5, [sp]
	add r4, r6, #0
_021D8A46:
	ldr r0, [r5, #0x38]
	bl StringSetEmpty
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	beq _021D8A72
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_020283A4
	add r1, r0, #0
	ldr r0, [r5, #0x38]
	bl CopyU16ArrayToString
	ldr r0, [sp]
	add r1, r4, #1
	add r0, r0, r6
	strb r1, [r0, #0x18]
	add r6, r6, #1
_021D8A72:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x20
	blt _021D8A46
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD55_021D8A28

	thumb_func_start MOD55_021D8A7C
MOD55_021D8A7C: ; 0x021D8A7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r0, [r5, #8]
	str r1, [sp, #0x14]
	bl FUN_020286EC
	ldr r0, [r5, #4]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x59
	mov r1, #2
	bl GfGfxLoader_LoadCharData
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x59
	mov r1, #8
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x59
	mov r1, #5
	mov r3, #1
	bl GfGfxLoader_LoadScrnData
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D8AEE
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021D8AEE:
	mov r0, #0
	str r0, [sp]
	mov r0, #0xd
	str r0, [sp, #4]
	mov r2, #3
	str r2, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _021D8CAC ; =0x00000171
	mov r1, #0xe6
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	mov r3, #1
	bl AddWindowParameterized
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r2, r5, #0
	add r2, #0xc0
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	mov r1, #5
	bl ReadMsgDataIntoString
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8CB0 ; =0x000F0E00
	add r2, r5, #0
	str r0, [sp, #8]
	mov r3, #0
	mov r0, #0xe6
	lsl r0, r0, #2
	str r3, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized2
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl ScheduleWindowCopyToVram
	mov r0, #0xde
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D8B6C
	mov r0, #0xde
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021D8B6C:
	mov r0, #0x15
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021D8CB4 ; =0x00000135
	mov r1, #0xde
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	mov r2, #3
	mov r3, #0xf
	bl AddWindowParameterized
	mov r0, #0xde
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r2, r5, #0
	add r2, #0xd0
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	mov r1, #7
	bl ReadMsgDataIntoString
	mov r1, #0
	add r2, r5, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8CB8 ; =0x00010200
	add r2, #0xd0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0xde
	lsl r0, r0, #2
	ldr r2, [r2]
	add r0, r5, r0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	mov r0, #0xde
	lsl r0, r0, #2
	add r0, r5, r0
	bl ScheduleWindowCopyToVram
	add r0, r5, #0
	bl MOD55_021D8A28
	mov r0, #0xae
	mov r6, #0
	lsl r0, r0, #2
	add r4, r5, r0
	add r7, r6, #0
_021D8BE4:
	cmp r6, #4
	bge _021D8BEE
	mov r0, #5
	str r0, [sp, #0x18]
	b _021D8BF2
_021D8BEE:
	mov r0, #0x14
	str r0, [sp, #0x18]
_021D8BF2:
	add r0, r4, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D8C02
	add r0, r4, #0
	bl RemoveWindow
_021D8C02:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #2
	add r0, r0, #5
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	add r1, r7, #0
	ldr r3, [sp, #0x18]
	ldr r0, _021D8CB4 ; =0x00000135
	add r1, #0x18
	sub r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	lsl r3, r3, #0x18
	ldr r0, [r5, #4]
	add r1, r4, #0
	mov r2, #3
	lsr r3, r3, #0x18
	bl AddWindowParameterized
	add r0, r4, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r0, r4, #0
	bl ScheduleWindowCopyToVram
	add r6, r6, #1
	add r4, #0x10
	add r7, #0x18
	cmp r6, #8
	blt _021D8BE4
	add r0, r5, #0
	bl MOD55_021D86D4
	add r0, r5, #0
	bl MOD55_021D8978
	add r0, r5, #0
	bl MOD55_021D88D0
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020130
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x3b
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r5, r0]
	ldr r0, [sp, #0x14]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D8CAC: .word 0x00000171
_021D8CB0: .word 0x000F0E00
_021D8CB4: .word 0x00000135
_021D8CB8: .word 0x00010200
	thumb_func_end MOD55_021D8A7C

	thumb_func_start MOD55_021D8CBC
MOD55_021D8CBC: ; 0x021D8CBC
	push {r3, r4, r5, lr}
	mov r3, #0xf2
	lsl r3, r3, #2
	add r5, r0, #0
	add r2, r3, #1
	ldrb r0, [r5, r3]
	ldrb r2, [r5, r2]
	lsr r4, r0, #3
	cmp r2, #4
	bne _021D8CD8
	mov r1, #1
	add r0, r3, #3
	strb r1, [r5, r0]
	b _021D8CF4
_021D8CD8:
	add r2, r3, #3
	ldrb r2, [r5, r2]
	cmp r2, #1
	bne _021D8CE8
	mov r1, #0
	add r0, r3, #3
	strb r1, [r5, r0]
	b _021D8CF4
_021D8CE8:
	add r0, r0, r1
	strb r0, [r5, r3]
	ldrb r1, [r5, r3]
	mov r0, #0x1f
	and r0, r1
	strb r0, [r5, r3]
_021D8CF4:
	add r0, r5, #0
	bl MOD55_021D86D4
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	lsr r0, r0, #3
	cmp r4, r0
	beq _021D8D12
	add r0, r5, #0
	bl MOD55_021D8978
	add r0, r5, #0
	bl MOD55_021D88D0
_021D8D12:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD55_021D8CBC

	thumb_func_start MOD55_021D8D14
MOD55_021D8D14: ; 0x021D8D14
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0xf3
	add r5, r0, #0
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	cmp r1, #0
	beq _021D8D52
	ldr r1, _021D8E5C ; =gSystem
	ldr r1, [r1, #0x48]
	cmp r1, #0
	beq _021D8D52
	bl MOD55_021DA214
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xf3
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r5, r0]
	b _021D8E36
_021D8D52:
	ldr r2, _021D8E5C ; =gSystem
	mov r0, #1
	ldr r3, [r2, #0x48]
	add r1, r3, #0
	tst r1, r0
	beq _021D8D88
	ldr r0, _021D8E60 ; =0x000005DC
	bl PlaySE
	ldr r1, _021D8E64 ; =0x000003CB
	ldrb r0, [r5, r1]
	cmp r0, #0
	beq _021D8D74
	mov r0, #6
	sub r1, #0x1b
	str r0, [r5, r1]
	b _021D8E36
_021D8D74:
	sub r0, r1, #3
	ldrb r0, [r5, r0]
	add r0, r5, r0
	ldrb r0, [r0, #0x18]
	cmp r0, #0
	beq _021D8E36
	mov r0, #4
	sub r1, #0x1b
	str r0, [r5, r1]
	b _021D8E36
_021D8D88:
	mov r1, #2
	tst r1, r3
	beq _021D8D9E
	ldr r0, _021D8E60 ; =0x000005DC
	bl PlaySE
	mov r0, #0x3b
	mov r1, #6
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _021D8E36
_021D8D9E:
	ldr r1, [r2, #0x4c]
	mov r2, #0x40
	tst r2, r1
	beq _021D8DC4
	ldr r0, _021D8E68 ; =0x000003C9
	ldrb r1, [r5, r0]
	cmp r1, #0
	beq _021D8E36
	sub r1, r1, #1
	strb r1, [r5, r0]
	ldr r0, _021D8E60 ; =0x000005DC
	bl PlaySE
	mov r1, #0
	add r0, r5, #0
	mvn r1, r1
	bl MOD55_021D8CBC
	b _021D8E36
_021D8DC4:
	mov r2, #0x80
	tst r2, r1
	beq _021D8DE6
	ldr r0, _021D8E68 ; =0x000003C9
	ldrb r1, [r5, r0]
	cmp r1, #4
	bhs _021D8E36
	add r1, r1, #1
	strb r1, [r5, r0]
	ldr r0, _021D8E60 ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	mov r1, #1
	bl MOD55_021D8CBC
	b _021D8E36
_021D8DE6:
	mov r2, #0x20
	tst r2, r1
	beq _021D8E10
	ldr r2, _021D8E64 ; =0x000003CB
	ldrb r1, [r5, r2]
	cmp r1, #0
	bne _021D8E36
	sub r1, r2, #1
	ldrb r1, [r5, r1]
	sub r1, r0, r1
	sub r0, r2, #1
	strb r1, [r5, r0]
	ldr r0, _021D8E60 ; =0x000005DC
	bl PlaySE
	mov r1, #3
	add r0, r5, #0
	mvn r1, r1
	bl MOD55_021D8CBC
	b _021D8E36
_021D8E10:
	mov r2, #0x10
	tst r1, r2
	beq _021D8E36
	ldr r2, _021D8E64 ; =0x000003CB
	ldrb r1, [r5, r2]
	cmp r1, #0
	bne _021D8E36
	sub r1, r2, #1
	ldrb r1, [r5, r1]
	sub r1, r0, r1
	sub r0, r2, #1
	strb r1, [r5, r0]
	ldr r0, _021D8E60 ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	mov r1, #4
	bl MOD55_021D8CBC
_021D8E36:
	mov r0, #0x3b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #3
	beq _021D8E58
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
_021D8E58:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8E5C: .word gSystem
_021D8E60: .word 0x000005DC
_021D8E64: .word 0x000003CB
_021D8E68: .word 0x000003C9
	thumb_func_end MOD55_021D8D14

	thumb_func_start MOD55_021D8E6C
MOD55_021D8E6C: ; 0x021D8E6C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r5, r0, #0
	ldr r0, [r5, #8]
	str r1, [sp, #0x14]
	bl FUN_020286EC
	mov r1, #0xf2
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	mov r2, #8
	str r0, [sp, #0x18]
	add r1, r5, r1
	ldrb r1, [r1, #0x18]
	sub r1, r1, #1
	bl FUN_0202822C
	cmp r0, #2
	add r2, sp, #0x1c
	bne _021D8ECC
	ldr r3, _021D8FCC ; =0x021DA418
	mov r7, #4
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r7, #0
	mov r1, #0x34
	bl ListMenuItems_New
	ldr r4, _021D8FD0 ; =0x021DA3D8
	str r0, [r5, #0x14]
	mov r6, #0
_021D8EB6:
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x10]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl ListMenuItems_AppendFromMsgData
	add r6, r6, #1
	add r4, #8
	cmp r6, #4
	blt _021D8EB6
	b _021D8F02
_021D8ECC:
	ldr r3, _021D8FD4 ; =0x021DA3F8
	mov r7, #4
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r7, #0
	mov r1, #0x34
	bl ListMenuItems_New
	ldr r4, _021D8FD8 ; =0x021DA438
	str r0, [r5, #0x14]
	mov r6, #0
_021D8EEE:
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x10]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl ListMenuItems_AppendFromMsgData
	add r6, r6, #1
	add r4, #8
	cmp r6, #4
	blt _021D8EEE
_021D8F02:
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D8F1A
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021D8F1A:
	mov r1, #9
	str r1, [sp]
	mov r1, #0xf
	lsl r0, r7, #1
	str r1, [sp, #4]
	lsl r1, r0, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xd
	str r1, [sp, #0xc]
	mov r1, #0x3b
	sub r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0xe2
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	mov r2, #2
	mov r3, #0x10
	bl AddWindowParameterized
	mov r0, #0xe2
	lsl r0, r0, #2
	ldr r2, _021D8FDC ; =0x000001D9
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xb
	bl DrawFrameAndWindow1
	ldr r0, [r5, #0x14]
	mov r1, #0
	str r0, [sp, #0x1c]
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x28]
	add r0, sp, #0x1c
	add r2, r1, #0
	mov r3, #0x34
	bl ListMenuInit
	mov r1, #0xea
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0x20
	add r0, r5, r1
	bl ScheduleWindowCopyToVram
	mov r0, #0x34
	bl PlayerProfile_New
	mov r1, #0xf2
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r4, r0, #0
	ldr r0, [sp, #0x18]
	add r1, r5, r1
	ldrb r1, [r1, #0x18]
	sub r1, r1, #1
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r4, #0
	bl CopyPlayerName
	ldr r0, [r5, #0xc]
	mov r1, #0
	add r2, r4, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #0xc
	bl MOD55_021DA0A4
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, _021D8FE0 ; =0x00000418
	mov r1, #0
	strh r1, [r5, r0]
	mov r1, #5
	sub r0, #0x68
	str r1, [r5, r0]
	ldr r0, [sp, #0x14]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_021D8FCC: .word MOD55_021DA418
_021D8FD0: .word MOD55_021DA3D8
_021D8FD4: .word MOD55_021DA3F8
_021D8FD8: .word MOD55_021DA438
_021D8FDC: .word 0x000001D9
_021D8FE0: .word 0x00000418
	thumb_func_end MOD55_021D8E6C

	thumb_func_start MOD55_021D8FE4
MOD55_021D8FE4: ; 0x021D8FE4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r6, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _021D9002
	add sp, #0xc
	add r0, r6, #0
	pop {r4, r5, r6, r7, pc}
_021D9002:
	mov r0, #0xea
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl ListMenu_ProcessInput
	ldr r1, _021D90D0 ; =0x00000418
	add r4, r0, #0
	add r0, r1, #0
	sub r0, #0x70
	ldrh r7, [r5, r1]
	ldr r0, [r5, r0]
	add r1, r5, r1
	bl ListMenuGetCurrentItemArrayId
	ldr r0, _021D90D0 ; =0x00000418
	ldrh r0, [r5, r0]
	cmp r7, r0
	beq _021D902C
	ldr r0, _021D90D4 ; =0x000005DC
	bl PlaySE
_021D902C:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _021D9040
	add r0, r0, #1
	cmp r4, r0
	bne _021D9068
	add sp, #0xc
	add r0, r6, #0
	pop {r4, r5, r6, r7, pc}
_021D9040:
	ldr r0, _021D90D4 ; =0x000005DC
	bl PlaySE
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x3b
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r5, r0]
	b _021D9098
_021D9068:
	ldr r0, _021D90D4 ; =0x000005DC
	bl PlaySE
	cmp r4, #0x14
	bne _021D9092
	ldr r0, [r5, #4]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
_021D9092:
	mov r0, #0x3b
	lsl r0, r0, #4
	str r4, [r5, r0]
_021D9098:
	add r0, r5, #0
	bl MOD55_021DA214
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl ClearFrameAndWindow1
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
	mov r0, #0xea
	lsl r0, r0, #2
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl DestroyListMenu
	ldr r0, [r5, #0x14]
	bl ListMenuItems_Delete
	add r0, r6, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021D90D0: .word 0x00000418
_021D90D4: .word 0x000005DC
	thumb_func_end MOD55_021D8FE4

	thumb_func_start MOD55_021D90D8
MOD55_021D90D8: ; 0x021D90D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	add r7, r1, #0
	add r0, r5, r0
	ldrb r0, [r0, #0x18]
	cmp r0, #0
	beq _021D9170
	ldr r0, [r5, #8]
	bl FUN_020286EC
	mov r1, #0xf2
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	str r0, [sp, #8]
	add r1, r5, r1
	ldrb r1, [r1, #0x18]
	sub r1, r1, #1
	bl FUN_0202838C
	bl DWC_GetFriendKey
	str r1, [sp, #4]
	add r4, r0, #0
	ldr r0, [sp, #4]
	mov r1, #0
	eor r1, r0
	mov r2, #0
	add r0, r4, #0
	eor r0, r2
	orr r0, r1
	beq _021D9170
	mov r0, #0x34
	bl PlayerProfile_New
	mov r1, #0xf2
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r6, r0, #0
	ldr r0, [sp, #8]
	add r1, r5, r1
	ldrb r1, [r1, #0x18]
	sub r1, r1, #1
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r6, #0
	bl CopyPlayerName
	ldr r0, _021D9180 ; =0x000005DC
	bl PlaySE
	ldr r2, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD55_021D93F8
	ldr r0, [r5, #0xc]
	mov r1, #0
	add r2, r6, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #0x1f
	bl MOD55_021DA15C
	mov r0, #0xf3
	mov r1, #1
	lsl r0, r0, #2
	strb r1, [r5, r0]
	add r0, r6, #0
	bl FreeToHeap
_021D9170:
	mov r0, #0x3b
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r7, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021D9180: .word 0x000005DC
	thumb_func_end MOD55_021D90D8

	thumb_func_start MOD55_021D9184
MOD55_021D9184: ; 0x021D9184
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r7, r1, #0
	bl FUN_020286EC
	bl FUN_02028228
	bl DWC_CreateFriendKey
	add r6, r0, #0
	add r4, r1, #0
	ldr r0, [r5, #4]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x59
	mov r1, #7
	mov r3, #1
	bl GfGfxLoader_LoadScrnData
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D91D6
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021D91D6:
	mov r0, #0
	str r0, [sp]
	mov r0, #0x14
	str r0, [sp, #4]
	mov r2, #3
	mov r1, #0xe6
	lsl r1, r1, #2
	str r2, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021D93D0 ; =0x00000139
	add r1, r5, r1
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	mov r3, #1
	bl AddWindowParameterized
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r5, #8]
	bl Save_PlayerData_GetProfileAddr
	add r2, r0, #0
	ldr r0, [r5, #0xc]
	mov r1, #0
	bl BufferPlayersName
	add r2, r5, #0
	add r2, #0xb8
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	mov r1, #0x16
	bl ReadMsgDataIntoString
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0xc0
	add r2, #0xb8
	ldr r0, [r5, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D93D4 ; =0x000F0E00
	add r2, r5, #0
	str r0, [sp, #8]
	mov r3, #0
	mov r0, #0xe6
	lsl r0, r0, #2
	str r3, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized2
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r5, r0
	bl ScheduleWindowCopyToVram
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D9278
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021D9278:
	mov r1, #0xd
	str r1, [sp]
	mov r0, #0x15
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0x64
	mov r1, #0xce
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	mov r2, #3
	mov r3, #6
	bl AddWindowParameterized
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r1, #0
	mov r0, #0
	eor r1, r4
	eor r0, r6
	orr r0, r1
	ldr r0, [r5, #0x10]
	bne _021D92C2
	add r2, r5, #0
	add r2, #0xbc
	ldr r2, [r2]
	mov r1, #0x18
	bl ReadMsgDataIntoString
	b _021D92CE
_021D92C2:
	add r2, r5, #0
	add r2, #0xbc
	ldr r2, [r2]
	mov r1, #0x17
	bl ReadMsgDataIntoString
_021D92CE:
	add r1, r5, #0
	add r1, #0xbc
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002F08
	mov r1, #0xa8
	sub r0, r1, r0
	mov r1, #0
	lsr r3, r0, #1
	add r2, r5, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D93D8 ; =0x00010200
	add r2, #0xbc
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r2, [r2]
	add r0, r5, r0
	bl AddTextPrinterParameterized2
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl ScheduleWindowCopyToVram
	mov r1, #0
	mov r0, #0
	eor r1, r4
	eor r0, r6
	orr r0, r1
	beq _021D93C2
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	bl MOD55_021D93F8
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D9338
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021D9338:
	mov r0, #8
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x32
	mov r1, #0xe2
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	mov r2, #3
	mov r3, #9
	bl AddWindowParameterized
	add r2, r5, #0
	add r2, #0xb8
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	mov r1, #0x1b
	bl ReadMsgDataIntoString
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0xbc
	add r2, #0xb8
	ldr r0, [r5, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r1, r5, #0
	add r1, #0xbc
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	mov r3, #0x70
	bl FUN_02002F40
	mov r1, #0
	add r3, r0, #0
	add r2, r5, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D93D8 ; =0x00010200
	add r2, #0xbc
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0xe2
	lsl r0, r0, #2
	ldr r2, [r2]
	add r0, r5, r0
	bl AddTextPrinterParameterized2
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl ScheduleWindowCopyToVram
_021D93C2:
	mov r0, #0x3b
	mov r1, #0x13
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r7, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D93D0: .word 0x00000139
_021D93D4: .word 0x000F0E00
_021D93D8: .word 0x00010200
	thumb_func_end MOD55_021D9184

	thumb_func_start MOD55_021D93DC
MOD55_021D93DC: ; 0x021D93DC
	ldr r2, _021D93F4 ; =gSystem
	ldr r3, [r2, #0x48]
	mov r2, #3
	tst r2, r3
	beq _021D93EE
	mov r2, #0x3b
	mov r3, #6
	lsl r2, r2, #4
	str r3, [r0, r2]
_021D93EE:
	add r0, r1, #0
	bx lr
	nop
_021D93F4: .word gSystem
	thumb_func_end MOD55_021D93DC

	thumb_func_start MOD55_021D93F8
MOD55_021D93F8: ; 0x021D93F8
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r2, #0
	add r4, r1, #0
	add r5, r0, #0
	ldr r2, _021D946C ; =0x05F5E100
	add r0, r4, #0
	add r1, r6, #0
	mov r3, #0
	bl _ll_udiv
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, [r5, #0xc]
	mov r3, #4
	bl BufferIntegerAsString
	ldr r2, _021D9470 ; =0x00002710
	add r0, r4, #0
	add r1, r6, #0
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021D9470 ; =0x00002710
	mov r3, #0
	bl _ull_mod
	mov r1, #2
	add r2, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0xc]
	mov r3, #4
	bl BufferIntegerAsString
	ldr r2, _021D9470 ; =0x00002710
	add r0, r4, #0
	add r1, r6, #0
	mov r3, #0
	bl _ull_mod
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0xc]
	mov r1, #3
	mov r3, #4
	bl BufferIntegerAsString
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_021D946C: .word 0x05F5E100
_021D9470: .word 0x00002710
	thumb_func_end MOD55_021D93F8

	thumb_func_start MOD55_021D9474
MOD55_021D9474: ; 0x021D9474
	push {r4, r5, lr}
	sub sp, #0x64
	add r4, r0, #0
	mov r0, #1
	mov r1, #0
	add r2, r0, #0
	bl GX_SetGraphicsMode
	ldr r5, _021D9564 ; =0x021DA2D8
	add r3, sp, #0x54
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r5, _021D9568 ; =0x021DA2F8
	add r3, sp, #0x38
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
	bl InitBgFromTemplate
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D956C ; =0x021DA330
	add r3, sp, #0x1c
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
	bl InitBgFromTemplate
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D9570 ; =0x021DA314
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x34
	bl BG_ClearCharDataRange
	mov r0, #1
	mov r1, #3
	bl SetBgPriority
	mov r0, #2
	add r1, r0, #0
	bl SetBgPriority
	mov r0, #0
	mov r1, #1
	bl SetBgPriority
	mov r0, #3
	mov r1, #0
	bl SetBgPriority
	add sp, #0x64
	pop {r4, r5, pc}
	.align 2, 0
_021D9564: .word MOD55_021DA2D8
_021D9568: .word MOD55_021DA2F8
_021D956C: .word MOD55_021DA330
_021D9570: .word MOD55_021DA314
	thumb_func_end MOD55_021D9474

	thumb_func_start MOD55_021D9574
MOD55_021D9574: ; 0x021D9574
	push {r3, lr}
	bl NNS_G3dInit
	bl G3X_InitMtxStack
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r0, _021D95D8 ; =0x04000008
	mov r1, #3
	ldrh r2, [r0]
	bic r2, r1
	mov r1, #1
	orr r1, r2
	strh r1, [r0]
	add r0, #0x58
	ldrh r1, [r0]
	ldr r2, _021D95DC ; =0xFFFFCFFD
	and r1, r2
	strh r1, [r0]
	ldrh r3, [r0]
	add r1, r2, #2
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0]
	ldr r1, _021D95E0 ; =0x0000CFFB
	and r1, r3
	strh r1, [r0]
	add r1, r2, #2
	ldrh r3, [r0]
	lsr r2, r2, #0x11
	and r3, r1
	mov r1, #8
	orr r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _021D95E4 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _021D95E8 ; =0xBFFF0000
	str r0, [r1, #0x40]
	pop {r3, pc}
	.align 2, 0
_021D95D8: .word 0x04000008
_021D95DC: .word 0xFFFFCFFD
_021D95E0: .word 0x0000CFFB
_021D95E4: .word 0x04000540
_021D95E8: .word 0xBFFF0000
	thumb_func_end MOD55_021D9574

	thumb_func_start MOD55_021D95EC
MOD55_021D95EC: ; 0x021D95EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r4, r0, #0
	ldr r0, [r4, #8]
	str r1, [sp, #0x14]
	bl FUN_020286EC
	str r0, [sp, #0x1c]
	mov r0, #0xf2
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	add r0, r4, r0
	ldrb r0, [r0, #0x18]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	bl FUN_0200E308
	cmp r0, #0
	bne _021D9618
	ldr r0, [sp, #0x14]
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
_021D9618:
	add r0, r4, #0
	bl MOD55_021D7720
	add r0, r4, #0
	bl MOD55_021D8140
	ldr r0, [r4, #4]
	bl MOD55_021D7AA4
	mov r0, #0x34
	bl BgConfig_Alloc
	str r0, [r4, #4]
	bl MOD55_021D9474
	bl MOD55_021D9574
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x59
	mov r1, #2
	mov r3, #1
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x59
	mov r1, #8
	mov r3, #1
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x59
	mov r1, #6
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r4, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D969A
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r4, r0
	bl RemoveWindow
_021D969A:
	mov r0, #0
	str r0, [sp]
	mov r0, #0x14
	str r0, [sp, #4]
	mov r2, #3
	mov r1, #0xe6
	lsl r1, r1, #2
	str r2, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021D9A50 ; =0x0000019D
	add r1, r4, r1
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	mov r3, #1
	bl AddWindowParameterized
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #0x34
	bl PlayerProfile_New
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	bl FUN_020283A4
	add r1, r0, #0
	ldr r0, [sp, #0x20]
	bl CopyPlayerName
	ldr r0, [r4, #0xc]
	ldr r2, [sp, #0x20]
	mov r1, #0
	bl BufferPlayersName
	add r2, r4, #0
	add r2, #0xb8
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0xd
	bl ReadMsgDataIntoString
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0xc0
	add r2, #0xb8
	ldr r0, [r4, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	mov r0, #4
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9A54 ; =0x000F0E00
	add r2, r4, #0
	str r0, [sp, #8]
	mov r3, #0
	mov r0, #0xe6
	lsl r0, r0, #2
	str r3, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r4, r0
	mov r1, #1
	bl AddTextPrinterParameterized2
	mov r0, #0xe6
	lsl r0, r0, #2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r4, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D974E
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r4, r0
	bl RemoveWindow
_021D974E:
	mov r0, #0x12
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r3, #2
	mov r1, #0xe2
	lsl r1, r1, #2
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021D9A58 ; =0x00000141
	add r1, r4, r1
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	mov r2, #3
	bl AddWindowParameterized
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0xc]
	ldr r2, [sp, #0x20]
	mov r1, #0
	bl BufferPlayersName
	add r2, r4, #0
	add r2, #0xb8
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #6
	bl ReadMsgDataIntoString
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0xc0
	add r2, #0xb8
	ldr r0, [r4, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	ldr r0, _021D9A54 ; =0x000F0E00
	add r1, r4, #0
	str r0, [sp]
	mov r0, #0xe2
	add r1, #0xc0
	lsl r0, r0, #2
	ldr r1, [r1]
	add r0, r4, r0
	mov r2, #0xff
	mov r3, #0x40
	bl MOD55_021D80F0
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	mov r0, #0x34
	bl FUN_02006D98
	add r1, r4, #0
	add r1, #0xdc
	str r0, [r1]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #7
	bl FUN_0202822C
	add r6, r0, #0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #8
	bl FUN_0202822C
	add r1, r6, #0
	mov r2, #1
	add r5, r0, #0
	bl FUN_020536D0
	add r1, r0, #0
	lsl r1, r1, #0x10
	lsl r3, r5, #0x18
	add r0, sp, #0x24
	lsr r1, r1, #0x10
	mov r2, #2
	lsr r3, r3, #0x18
	bl FUN_02068FE0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0xdc
	ldr r0, [r0]
	add r1, sp, #0x24
	mov r2, #0x36
	mov r3, #0x54
	bl FUN_020073A0
	add r1, r4, #0
	add r1, #0xe0
	str r0, [r1]
	cmp r5, #1
	bne _021D9864
	ldr r0, [r4, #4]
	mov r1, #2
	bl GetBgTilemapBuffer
	ldr r2, _021D9A5C ; =0x00000FFF
	mov r7, #0x10
	mov ip, r0
	lsl r6, r7, #5
	add r3, r2, #1
_021D983C:
	lsl r5, r6, #1
	mov r1, ip
	mov r0, #0
	add r1, r1, r5
_021D9844:
	ldrh r5, [r1]
	add r0, r0, #1
	and r5, r2
	add r5, r5, r3
	strh r5, [r1]
	add r1, r1, #2
	cmp r0, #0xc
	blt _021D9844
	add r7, r7, #1
	add r6, #0x20
	cmp r7, #0x15
	blt _021D983C
	ldr r0, [r4, #4]
	mov r1, #2
	bl BgCommitTilemapBufferToVram
_021D9864:
	mov r0, #0xd2
	lsl r0, r0, #2
	add r0, r4, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021D987C
	mov r0, #0xd2
	lsl r0, r0, #2
	add r0, r4, r0
	bl RemoveWindow
_021D987C:
	mov r0, #4
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0x13
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #2
	mov r1, #0xd2
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #3
	mov r3, #0xf
	bl AddWindowParameterized
	mov r0, #0xd2
	lsl r0, r0, #2
	add r0, r4, r0
	mov r1, #0
	bl FillWindowPixelBuffer
	add r2, r4, #0
	add r2, #0xc4
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0xe
	bl ReadMsgDataIntoString
	mov r0, #2
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9A60 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r2, r4, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc4
	ldr r2, [r2]
	add r0, r4, r0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	mov r0, #0x34
	bl PlayerProfile_New
	add r5, r0, #0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	bl FUN_020283E8
	add r1, r0, #0
	add r0, r5, #0
	bl CopyPlayerName
	ldr r0, [r4, #0xc]
	mov r1, #0
	add r2, r5, #0
	bl BufferPlayersName
	add r0, r5, #0
	bl FreeToHeap
	add r2, r4, #0
	add r2, #0xb8
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0x2a
	bl ReadMsgDataIntoString
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0xc4
	add r2, #0xb8
	ldr r0, [r4, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	add r1, r4, #0
	add r1, #0xc4
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x78
	sub r3, r1, r0
	mov r0, #2
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9A60 ; =0x00010200
	add r2, r4, #0
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc4
	ldr r2, [r2]
	add r0, r4, r0
	bl AddTextPrinterParameterized2
	add r2, r4, #0
	add r2, #0xc8
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0xf
	bl ReadMsgDataIntoString
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9A60 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r2, r4, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc8
	ldr r2, [r2]
	add r0, r4, r0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #1
	bl FUN_0202822C
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0xc]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	add r2, r4, #0
	add r2, #0xb8
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0x10
	bl ReadMsgDataIntoString
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0xc0
	add r2, #0xb8
	ldr r0, [r4, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	add r1, r4, #0
	add r1, #0xc0
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x78
	sub r3, r1, r0
	mov r0, #0x27
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9A60 ; =0x00010200
	add r2, r4, #0
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r4, r0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #2
	bl FUN_0202822C
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0xc]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	add r2, r4, #0
	add r2, #0xb8
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0x11
	bl ReadMsgDataIntoString
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0xc0
	add r2, #0xb8
	ldr r0, [r4, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	add r1, r4, #0
	add r1, #0xc0
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x78
	sub r3, r1, r0
	mov r0, #0x35
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9A60 ; =0x00010200
	b _021D9A64
	nop
_021D9A50: .word 0x0000019D
_021D9A54: .word 0x000F0E00
_021D9A58: .word 0x00000141
_021D9A5C: .word 0x00000FFF
_021D9A60: .word 0x00010200
_021D9A64:
	add r2, r4, #0
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r4, r0
	bl AddTextPrinterParameterized2
	add r2, r4, #0
	add r2, #0xc0
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0x12
	bl ReadMsgDataIntoString
	mov r0, #0x4a
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9C4C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r2, r4, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r4, r0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #3
	bl FUN_0202822C
	add r5, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0xc]
	mov r1, #0
	add r2, r5, #0
	mov r3, #4
	bl BufferIntegerAsString
	cmp r5, #1
	ldr r0, [r4, #0x10]
	bne _021D9ADC
	add r2, r4, #0
	add r2, #0xb8
	ldr r2, [r2]
	mov r1, #0x13
	bl ReadMsgDataIntoString
	b _021D9AE8
_021D9ADC:
	add r2, r4, #0
	add r2, #0xb8
	ldr r2, [r2]
	mov r1, #0x2b
	bl ReadMsgDataIntoString
_021D9AE8:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0xc0
	add r2, #0xb8
	ldr r0, [r4, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	add r1, r4, #0
	add r1, #0xc0
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x78
	sub r3, r1, r0
	mov r0, #0x5c
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9C4C ; =0x00010200
	add r2, r4, #0
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r4, r0
	bl AddTextPrinterParameterized2
	add r2, r4, #0
	add r2, #0xc0
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0x14
	bl ReadMsgDataIntoString
	mov r0, #0x71
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D9C4C ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	add r2, r4, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r4, r0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #6
	bl FUN_0202822C
	add r2, r0, #0
	beq _021D9C18
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #2
	ldr r0, [r4, #0xc]
	add r3, r1, #0
	bl BufferIntegerAsString
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #4
	bl FUN_0202822C
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0xc]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #5
	bl FUN_0202822C
	add r2, r0, #0
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl BufferMonthNameAbbr
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	mov r2, #6
	bl FUN_0202822C
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #2
	ldr r0, [r4, #0xc]
	add r3, r1, #0
	bl BufferIntegerAsString
	add r2, r4, #0
	add r2, #0xb8
	ldr r0, [r4, #0x10]
	ldr r2, [r2]
	mov r1, #0x15
	bl ReadMsgDataIntoString
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0xc0
	add r2, #0xb8
	ldr r0, [r4, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	add r1, r4, #0
	add r1, #0xc0
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x78
	sub r3, r1, r0
	mov r1, #0x81
	add r2, r4, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	lsl r0, r1, #9
	str r0, [sp, #8]
	mov r1, #0
	mov r0, #0xd2
	lsl r0, r0, #2
	str r1, [sp, #0xc]
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r4, r0
	bl AddTextPrinterParameterized2
_021D9C18:
	mov r0, #0xd2
	lsl r0, r0, #2
	add r0, r4, r0
	bl ScheduleWindowCopyToVram
	ldr r0, [sp, #0x20]
	bl FreeToHeap
	mov r0, #0x3b
	mov r1, #0x15
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [sp, #0x14]
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9C4C: .word 0x00010200
	thumb_func_end MOD55_021D95EC

	thumb_func_start MOD55_021D9C50
MOD55_021D9C50: ; 0x021D9C50
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl G3X_ResetMtxStack
	bl G3X_ResetMtxStack_2
	bl NNS_G2dSetupSoftwareSpriteCamera
	add r0, r5, #0
	add r0, #0xdc
	ldr r0, [r0]
	bl FUN_02006ED4
	ldr r0, _021D9CB8 ; =0x04000540
	mov r1, #0
	str r1, [r0]
	bl FUN_0200E308
	cmp r0, #0
	bne _021D9C82
	add sp, #0xc
	add r0, r4, #0
	pop {r4, r5, pc}
_021D9C82:
	ldr r0, _021D9CBC ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D9CB2
	ldr r0, _021D9CC0 ; =0x000005DC
	bl PlaySE
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x3b
	mov r1, #0x16
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D9CB2:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021D9CB8: .word 0x04000540
_021D9CBC: .word gSystem
_021D9CC0: .word 0x000005DC
	thumb_func_end MOD55_021D9C50

	thumb_func_start MOD55_021D9CC4
MOD55_021D9CC4: ; 0x021D9CC4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r1, #0
	bl G3X_ResetMtxStack
	bl G3X_ResetMtxStack_2
	bl NNS_G2dSetupSoftwareSpriteCamera
	add r0, r5, #0
	add r0, #0xdc
	ldr r0, [r0]
	bl FUN_02006ED4
	ldr r0, _021D9D84 ; =0x04000540
	mov r1, #0
	str r1, [r0]
	bl FUN_0200E308
	cmp r0, #0
	bne _021D9CF6
	add sp, #0x10
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021D9CF6:
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	cmp r0, #0
	beq _021D9D16
	bl FUN_02007534
	add r0, r5, #0
	add r0, #0xdc
	ldr r0, [r0]
	bl FUN_020072E8
	add r0, r5, #0
	mov r1, #0
	add r0, #0xe0
	str r1, [r0]
_021D9D16:
	ldr r0, [r5, #4]
	bl MOD55_021D7AA4
	mov r0, #0x34
	bl BgConfig_Alloc
	str r0, [r5, #4]
	bl MOD55_021D781C
	add r0, r5, #0
	bl MOD55_021D74E0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x59
	mov r1, #0xa
	mov r3, #4
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x59
	mov r1, #0xb
	mov r3, #4
	bl GfGfxLoader_LoadScrnData
	mov r0, #3
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x3b
	mov r1, #2
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D9D84: .word 0x04000540
	thumb_func_end MOD55_021D9CC4

	thumb_func_start MOD55_021D9D88
MOD55_021D9D88: ; 0x021D9D88
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r0, [r6, #4]
	str r1, [sp, #0x10]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r6, #4]
	mov r0, #0x59
	mov r1, #8
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x34
	str r0, [sp, #0xc]
	ldr r2, [r6, #4]
	mov r0, #0x59
	mov r1, #4
	mov r3, #1
	bl GfGfxLoader_LoadScrnData
	mov r7, #0x29
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_021D9DCE:
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa
	blt _021D9DCE
	mov r0, #0xf2
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r6, r0]
	add r0, r0, #3
	strb r1, [r6, r0]
	add r0, r6, #0
	bl MOD55_021D7EE4
	add r0, r6, #0
	bl MOD55_021D8044
	mov r0, #0x3b
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r6, r0]
	ldr r0, [sp, #0x10]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD55_021D9D88

	thumb_func_start MOD55_021D9E04
MOD55_021D9E04: ; 0x021D9E04
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	add r4, r1, #0
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x10
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0x3b
	mov r1, #0x18
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD55_021D9E04

	thumb_func_start MOD55_021D9E34
MOD55_021D9E34: ; 0x021D9E34
	ldr r3, _021D9E3C ; =FUN_0201C78C
	ldrh r0, [r0]
	bx r3
	nop
_021D9E3C: .word FUN_0201C78C
	thumb_func_end MOD55_021D9E34

	thumb_func_start MOD55_021D9E40
MOD55_021D9E40: ; 0x021D9E40
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #8]
	add r6, r1, #0
	bl FUN_020286EC
	add r5, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9EBE
	mov r0, #0
	bl MOD55_021DA27C
	add r0, r4, #0
	bl MOD55_021D778C
	ldr r0, [r4, #8]
	bl Save_PlayerData_GetOptionsAddr
	mov r1, #7
	str r0, [sp]
	mov r0, #0x34
	mov r2, #0
	add r3, r1, #0
	bl FUN_02077A84
	str r0, [r4]
	ldr r0, _021D9EC4 ; =UNK_020FA5FC
	ldr r1, [r4]
	mov r2, #0x34
	bl OverlayManager_New
	mov r1, #0x3d
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	mov r2, #0x19
	sub r0, #0x20
	str r2, [r4, r0]
	sub r1, #8
	ldrb r1, [r4, r1]
	add r0, r5, #0
	add r1, r4, r1
	ldrb r1, [r1, #0x18]
	sub r1, r1, #1
	bl FUN_020283A4
	add r5, r0, #0
	bl MOD55_021D9E34
	cmp r0, #0
	ldr r0, [r4]
	bne _021D9EB8
	ldr r0, [r0, #0x18]
	add r1, r5, #0
	bl CopyU16ArrayToString
	b _021D9EBE
_021D9EB8:
	ldr r0, [r0, #0x18]
	bl StringSetEmpty
_021D9EBE:
	add r0, r6, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D9EC4: .word UNK_020FA5FC
	thumb_func_end MOD55_021D9E40

	thumb_func_start MOD55_021D9EC8
MOD55_021D9EC8: ; 0x021D9EC8
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl OverlayManager_Run
	cmp r0, #0
	beq _021D9F68
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl OverlayManager_Delete
	ldr r1, [r5]
	ldr r0, [r1, #0x14]
	cmp r0, #0
	bne _021D9F18
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	ldr r1, [r1, #0x18]
	bl StringCopy
	ldr r0, [r5, #8]
	bl FUN_020286EC
	mov r1, #0xf2
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r2, r5, #0
	add r2, #0xd4
	add r1, r5, r1
	ldrb r1, [r1, #0x18]
	ldr r2, [r2]
	sub r1, r1, #1
	bl FUN_020283C0
_021D9F18:
	ldr r0, [r5]
	bl FUN_02077AC4
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	bl MOD55_021DA27C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x11
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r5, #0
	bl MOD55_021D7504
	add r0, r5, #0
	add r1, r4, #0
	bl MOD55_021D8A7C
	mov r0, #1
	bl MOD55_021DA27C
	mov r0, #0x3b
	mov r1, #0x1a
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D9F68:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD55_021D9EC8

	thumb_func_start MOD55_021D9F70
MOD55_021D9F70: ; 0x021D9F70
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9F86
	mov r0, #0x3b
	mov r1, #3
	lsl r0, r0, #4
	str r1, [r5, r0]
_021D9F86:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD55_021D9F70

	thumb_func_start MOD55_021D9F8C
MOD55_021D9F8C: ; 0x021D9F8C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x34
	add r6, r1, #0
	bl PlayerProfile_New
	add r4, r0, #0
	ldr r0, [r5, #8]
	bl FUN_020286EC
	mov r1, #0xf2
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r1, r5, r1
	ldrb r1, [r1, #0x18]
	sub r1, r1, #1
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r4, #0
	bl CopyPlayerName
	ldr r0, [r5, #0xc]
	mov r1, #0
	add r2, r4, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #0x1c
	bl MOD55_021DA0A4
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #0x3b
	mov r1, #0x1c
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD55_021D9F8C

	thumb_func_start MOD55_021D9FDC
MOD55_021D9FDC: ; 0x021D9FDC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xe4
	ldr r0, [r0]
	add r4, r1, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021DA010
	mov r0, #0x34
	str r0, [sp]
	ldr r0, [r5, #4]
	ldr r1, _021DA014 ; =0x021DA2AC
	ldr r2, _021DA018 ; =0x000001D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	add r1, r5, #0
	add r1, #0xe8
	str r0, [r1]
	mov r0, #0x3b
	mov r1, #0x1d
	lsl r0, r0, #4
	str r1, [r5, r0]
_021DA010:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA014: .word MOD55_021DA2AC
_021DA018: .word 0x000001D9
	thumb_func_end MOD55_021D9FDC

	thumb_func_start MOD55_021DA01C
MOD55_021DA01C: ; 0x021DA01C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xe8
	add r4, r1, #0
	ldr r0, [r0]
	mov r1, #0x34
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021DA038
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021DA038:
	cmp r0, #0
	bne _021DA056
	ldr r0, [r5, #8]
	bl FUN_020286EC
	mov r1, #0xf2
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r1, r5, r1
	ldrb r1, [r1, #0x18]
	sub r1, r1, #1
	bl FUN_02028468
	mov r1, #2
	b _021DA070
_021DA056:
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #3
_021DA070:
	mov r0, #0x3b
	lsl r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD55_021DA214
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD55_021DA01C

	thumb_func_start MOD55_021DA080
MOD55_021DA080: ; 0x021DA080
	push {lr}
	sub sp, #0xc
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x34
	str r0, [sp, #8]
	mov r0, #0
	mov r1, #0x10
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #2
	add sp, #0xc
	pop {pc}
	.align 2, 0
	thumb_func_end MOD55_021DA080

	thumb_func_start MOD55_021DA0A4
MOD55_021DA0A4: ; 0x021DA0A4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r6, r1, #0
	bl Save_PlayerData_GetOptionsAddr
	bl Options_GetTextFrameDelay
	add r4, r0, #0
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	beq _021DA0D0
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021DA0D0:
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _021DA154 ; =0x0000012D
	mov r1, #0xce
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	mov r2, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	add r3, r2, #0
	bl AddWindowParameterized
	add r2, r5, #0
	add r2, #0xb8
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	add r1, r6, #0
	bl ReadMsgDataIntoString
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0xbc
	add r2, #0xb8
	ldr r0, [r5, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r2, _021DA158 ; =0x000001E2
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xa
	bl DrawFrameAndWindow2
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	add r2, r5, #0
	mov r0, #0xce
	lsl r0, r0, #2
	str r3, [sp, #8]
	add r2, #0xbc
	ldr r2, [r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	add r5, #0xe4
	str r0, [r5]
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021DA154: .word 0x0000012D
_021DA158: .word 0x000001E2
	thumb_func_end MOD55_021DA0A4

	thumb_func_start MOD55_021DA15C
MOD55_021DA15C: ; 0x021DA15C
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	add r4, r1, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _021DA17C
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl RemoveWindow
_021DA17C:
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _021DA20C ; =0x0000012D
	mov r1, #0xce
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	mov r2, #2
	ldr r0, [r5, #4]
	add r1, r5, r1
	add r3, r2, #0
	bl AddWindowParameterized
	add r2, r5, #0
	add r2, #0xb8
	ldr r0, [r5, #0x10]
	ldr r2, [r2]
	add r1, r4, #0
	bl ReadMsgDataIntoString
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0xbc
	add r2, #0xb8
	ldr r0, [r5, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl StringExpandPlaceholders
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r0, #0xce
	lsl r0, r0, #2
	ldr r2, _021DA210 ; =0x000001E2
	add r0, r5, r0
	mov r1, #1
	mov r3, #0xa
	bl DrawFrameAndWindow2
	mov r3, #0
	add r2, r5, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0xce
	lsl r0, r0, #2
	str r3, [sp, #8]
	add r2, #0xbc
	ldr r2, [r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	add r1, r5, #0
	add r1, #0xe4
	str r0, [r1]
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r5, r0
	bl ScheduleWindowCopyToVram
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_021DA20C: .word 0x0000012D
_021DA210: .word 0x000001E2
	thumb_func_end MOD55_021DA15C

	thumb_func_start MOD55_021DA214
MOD55_021DA214: ; 0x021DA214
	mov r1, #0xce
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r3, _021DA220 ; =ClearFrameAndWindow2
	mov r1, #0
	bx r3
	.align 2, 0
_021DA220: .word ClearFrameAndWindow2
	thumb_func_end MOD55_021DA214

	thumb_func_start MOD55_021DA224
MOD55_021DA224: ; 0x021DA224
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	cmp r5, #0
	beq _021DA276
	bl FUN_020286EC
	bl FUN_02028228
	add r1, r4, #0
	add r2, r6, #0
	bl DWC_CheckFriendKey
	cmp r0, #0
	bne _021DA24C
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_021DA24C:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	add r3, sp, #0
	bl FUN_02033918
	cmp r0, #0
	bne _021DA262
	mov r0, #1
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_021DA262:
	add r0, r5, #0
	bl FUN_020286EC
	add r1, r7, #0
	bl FUN_0202838C
	add r1, r4, #0
	add r2, r6, #0
	bl DWC_CreateFriendKeyToken
_021DA276:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD55_021DA224

	thumb_func_start MOD55_021DA27C
MOD55_021DA27C: ; 0x021DA27C
	push {r4, lr}
	add r4, r0, #0
	lsl r1, r4, #0x18
	mov r0, #0xf
	lsr r1, r1, #0x18
	bl GX_EngineAToggleLayers
	lsl r1, r4, #0x18
	mov r0, #1
	lsr r1, r1, #0x18
	bl GX_EngineBToggleLayers
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD55_021DA27C

	.rodata
	.global MOD55_021DA298
MOD55_021DA298: ; 0x021DA298
	.byte 0x01, 0x04, 0x0F, 0x04, 0x02, 0x05, 0x02, 0x02, 0x02, 0x04, 0x1C, 0x04, 0x08, 0x00, 0x42, 0x00
	.byte 0x08, 0x08, 0x42, 0x08

	.global MOD55_021DA2AC
MOD55_021DA2AC: ; 0x021DA2AC
	.byte 0x02, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x01, 0x2E, 0x00, 0x2F, 0x00, 0x33, 0x00, 0x34, 0x00

	.global MOD55_021DA2BC
MOD55_021DA2BC: ; 0x021DA2BC
	.byte 0x00, 0x06, 0x05, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x02, 0x01, 0x00

	.global MOD55_021DA2C8
MOD55_021DA2C8: ; 0x021DA2C8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA2D8
MOD55_021DA2D8: ; 0x021DA2D8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD55_021DA2E8
MOD55_021DA2E8: ; 0x021DA2E8
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00

	.global MOD55_021DA2F8
MOD55_021DA2F8: ; 0x021DA2F8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x18, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA314
MOD55_021DA314: ; 0x021DA314
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA330
MOD55_021DA330: ; 0x021DA330
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1A, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA34C
MOD55_021DA34C: ; 0x021DA34C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x18, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA368
MOD55_021DA368: ; 0x021DA368
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1A, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA384
MOD55_021DA384: ; 0x021DA384
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA3A0
MOD55_021DA3A0: ; 0x021DA3A0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA3BC
MOD55_021DA3BC: ; 0x021DA3BC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA3D8
MOD55_021DA3D8: ; 0x021DA3D8
	.byte 0x20, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD55_021DA3F8
MOD55_021DA3F8: ; 0x021DA3F8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA418
MOD55_021DA418: ; 0x021DA418
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD55_021DA438
MOD55_021DA438: ; 0x021DA438
	.byte 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD55_021DA458
MOD55_021DA458: ; 0x021DA458
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.data
	.global MOD55_021DA4A0
MOD55_021DA4A0: ; 0x021DA4A0
	.word MOD55_021D81D0, MOD55_021D81DC, MOD55_021D8A7C, MOD55_021D8D14
	.word MOD55_021D8E6C, MOD55_021D8FE4, MOD55_021D9D88, MOD55_021D82C0
	.word MOD55_021D8320, MOD55_021D8370, MOD55_021D8404, MOD55_021D8440
	.word MOD55_021D84C8, MOD55_021D8544, MOD55_021D8584, MOD55_021D8680
	.word MOD55_021D868C, MOD55_021DA080, MOD55_021D9184, MOD55_021D93DC
	.word MOD55_021D95EC, MOD55_021D9C50, MOD55_021D9CC4, MOD55_021D9E04
	.word MOD55_021D9E40, MOD55_021D9EC8, MOD55_021D9F70, MOD55_021D9F8C
	.word MOD55_021D9FDC, MOD55_021DA01C, MOD55_021D90D8, 0x00000000

	.bss
