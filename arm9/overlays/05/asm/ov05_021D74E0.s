	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021D74E0
ov05_021D74E0: ; 0x021D74E0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl DoScheduledBgGpuUpdates
	bl sub_0201C30C
	bl ApplyAndResetOamManagerBuffer
	ldr r0, [r4, #0x34]
	bl sub_020583A0
	bl ov05_021F2D48
	bl sub_0201F2D8
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021D7504
ov05_021D7504: ; 0x021D7504
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r6, #0
	bl OverlayManager_GetField18
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #3
	bls _021D7518
	b _021D7666
_021D7518:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7524: ; jump table
	.short _021D752C - _021D7524 - 2 ; case 0
	.short _021D75DE - _021D7524 - 2 ; case 1
	.short _021D7654 - _021D7524 - 2 ; case 2
	.short _021D765A - _021D7524 - 2 ; case 3
_021D752C:
	add r0, r6, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl sub_02015F1C
	ldr r1, _021D7670 ; =0x04000050
	add r0, r6, #0
	strh r0, [r1]
	ldr r1, _021D7674 ; =0x04001050
	strh r0, [r1]
	bl sub_0200E388
	mov r0, #1
	bl sub_0200E388
	add r0, r4, #0
	bl sub_020489DC
	ldr r0, [r4, #0x70]
	ldr r0, [r0]
	lsl r0, r0, #8
	lsr r0, r0, #0x1c
	beq _021D7564
	ldr r0, _021D7678 ; =SDK_OVERLAY_OVERLAY_06_ID
	mov r1, #2
	bl HandleLoadOverlay
_021D7564:
	ldr r2, [r4, #0x70]
	mov r0, #3
	ldr r2, [r2, #4]
	mov r1, #4
	bl CreateHeap
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D757A
	bl GF_AssertFail
_021D757A:
	mov r0, #4
	mov r1, #0x28
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x28
	str r0, [r4, #4]
	bl MI_CpuFill8
	add r0, r4, #0
	mov r1, #4
	mov r2, #8
	bl ov05_021D7F4C
	ldr r1, [r4, #4]
	str r0, [r1, #4]
	bl ov05_021D7A00
	mov r0, #0x80
	mov r1, #4
	bl sub_0201C24C
	mov r0, #4
	add r1, r0, #0
	bl sub_0201F100
	mov r0, #4
	bl sub_0201B2EC
	bl ov05_021D7BA0
	bl ov05_021D7B38
	bl GX_SwapDisplay
	mov r0, #4
	bl BgConfig_Alloc
	str r0, [r4, #8]
	bl ov05_021D7A30
	mov r0, #0
	mov r1, #1
	bl sub_02054590
	add r0, r4, #0
	mov r1, #4
	bl sub_0203989C
	b _021D7666
_021D75DE:
	bl ov05_021D7CF0
	ldr r0, [r4, #0x2c]
	bl ov05_021F49AC
	mov r0, #4
	bl ov05_021E7C00
	add r1, r4, #0
	add r1, #0xa0
	str r0, [r1]
	add r0, r4, #0
	bl ov05_021F5B9C
	add r0, r4, #0
	bl ov05_021D7D4C
	add r0, r4, #0
	bl ov05_021D7D98
	add r0, r4, #0
	bl ov05_021D7E4C
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetWeatherType
	add r1, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0xc]
	bl ov05_021DC124
	ldr r1, [r4, #0x1c]
	add r0, r4, #0
	ldr r1, [r1]
	bl sub_0204ADBC
	add r0, r4, #0
	mov r1, #3
	bl sub_0203989C
	mov r0, #4
	bl ov05_021F45B4
	ldr r1, [r4, #4]
	str r0, [r1, #0x1c]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x1c]
	bl ov05_021F45E8
	ldr r1, [r4, #4]
	mov r0, #4
	ldr r1, [r1, #0x1c]
	bl ov05_021F46C8
	ldr r1, [r4, #4]
	str r0, [r1, #0x20]
	b _021D7666
_021D7654:
	bl ov05_021DBE1C
	b _021D7666
_021D765A:
	bl ov05_021DBE38
	cmp r0, #0
	beq _021D7666
	mov r6, #1
	str r6, [r4, #0x64]
_021D7666:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021D7670: .word 0x04000050
_021D7674: .word 0x04001050
_021D7678: .word SDK_OVERLAY_OVERLAY_06_ID

	thumb_func_start ov05_021D767C
ov05_021D767C: ; 0x021D767C
	push {r4, lr}
	bl OverlayManager_GetField18
	add r4, r0, #0
	bl ov05_021D7864
	cmp r0, #0
	beq _021D76A8
	add r0, r4, #0
	bl sub_0204B490
	add r0, r4, #0
	bl ov05_021D79B4
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl ov05_021EFA9C
	add r0, r4, #0
	bl ov05_021D7894
_021D76A8:
	add r0, r4, #0
	mov r1, #0xf
	bl ov05_021D795C
	ldr r0, [r4, #0x64]
	cmp r0, #0
	beq _021D76BA
	mov r0, #0
	pop {r4, pc}
_021D76BA:
	mov r0, #1
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021D76C0
ov05_021D76C0: ; 0x021D76C0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl OverlayManager_GetField18
	add r4, r0, #0
	ldr r1, [r4, #0x24]
	bl ov05_021EE52C
	ldr r0, [r5]
	cmp r0, #0
	beq _021D76E2
	cmp r0, #1
	beq _021D7782
	cmp r0, #2
	bne _021D76E0
	b _021D7806
_021D76E0:
	b _021D785A
_021D76E2:
	add r0, r4, #0
	bl sub_0205CDD8
	ldr r0, [r4, #0x24]
	bl ov05_021EF5FC
	ldr r0, [r4, #0x38]
	bl GetPlayerXCoord
	ldr r1, [r4, #0x1c]
	str r0, [r1, #8]
	ldr r0, [r4, #0x38]
	bl GetPlayerYCoord
	ldr r1, [r4, #0x1c]
	str r0, [r1, #0xc]
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	ldr r1, [r4, #0x1c]
	str r0, [r1, #0x10]
	add r0, r4, #0
	add r0, #0x9c
	ldr r0, [r0]
	bl ov05_021F450C
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	bne _021D7720
	bl GF_AssertFail
_021D7720:
	ldr r0, [r4, #0x24]
	bl ov05_021EF514
	ldr r0, [r4, #0x4c]
	bl ov05_021D9F48
	ldr r0, [r4, #0x4c]
	bl ov05_021DA018
	add r0, r4, #0
	add r0, #0x50
	bl ov05_021DA450
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x10]
	bl ov05_021DC094
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x10]
	bl ov05_021DC0AC
	ldr r0, [r4, #4]
	mov r1, #0
	str r1, [r0, #0x10]
	ldr r0, [r4, #0x34]
	bl sub_02057750
	ldr r0, [r4, #0x34]
	bl ov05_021F1D2C
	ldr r0, [r4, #0x34]
	bl sub_02058768
	ldr r0, [r4, #0x3c]
	bl ov05_021E4BA8
	ldr r0, [r4, #0x30]
	bl ov05_021D7F44
	mov r0, #0
	str r0, [r4, #0x30]
	add r4, #0xa0
	ldr r0, [r4]
	bl ov05_021E7C14
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D785A
_021D7782:
	ldr r0, [r4, #0x24]
	bl ov05_021EF5C4
	cmp r0, #1
	bne _021D785A
	add r0, r4, #0
	add r0, #0x2c
	bl ov05_021F4BF8
	ldr r0, [r4, #0x24]
	bl ov05_021EF5A8
	add r0, r4, #0
	add r0, #0xa4
	bl ov05_021F4D1C
	add r0, r4, #0
	bl ov05_021DBDEC
	add r0, r4, #0
	add r0, #0x48
	bl ov05_021DB4B0
	ldr r0, [r4, #0x60]
	bl ov05_021E8110
	ldr r0, [r4, #4]
	ldr r0, [r0, #8]
	bl ov05_021E3248
	ldr r0, [r4, #4]
	ldr r0, [r0, #0xc]
	bl ov05_021DC0F8
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl ov05_021F4704
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x1c]
	bl ov05_021F45C8
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x18]
	bl sub_0204B3B8
	add r0, r4, #0
	add r0, #0x44
	bl ov05_021DBA1C
	add r0, r4, #0
	add r0, #0x40
	bl ov05_021DBAD8
	bl ov05_021D7B5C
	ldr r0, [r4, #8]
	bl ov05_021D7B10
	add r0, r4, #0
	bl ov05_021DBE58
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D785A
_021D7806:
	add r0, r4, #0
	bl ov05_021DBE74
	cmp r0, #0
	beq _021D785A
	bl ov05_021D7BD4
	bl sub_0201F140
	bl sub_0201C29C
	bl sub_0201B398
	ldr r0, [r4, #4]
	ldr r0, [r0, #4]
	bl ov05_021D7F9C
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	ldr r0, [r4, #8]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #4
	bl DestroyHeap
	ldr r0, [r4, #0x70]
	ldr r0, [r0]
	lsl r0, r0, #8
	lsr r0, r0, #0x1c
	beq _021D7856
	ldr r0, _021D7860 ; =SDK_OVERLAY_OVERLAY_06_ID
	bl UnloadOverlayByID
_021D7856:
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D785A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D7860: .word SDK_OVERLAY_OVERLAY_06_ID

	thumb_func_start ov05_021D7864
ov05_021D7864: ; 0x021D7864
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	ldr r2, [r5, #0x1c]
	ldr r1, [r2, #8]
	cmp r4, r1
	bne _021D7884
	ldr r1, [r2, #0xc]
	cmp r0, r1
	beq _021D788E
_021D7884:
	str r4, [r2, #8]
	ldr r1, [r5, #0x1c]
	str r0, [r1, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D788E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021D7894
ov05_021D7894: ; 0x021D7894
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	asr r1, r0, #4
	lsr r1, r1, #0x1b
	add r1, r0, r1
	ldr r0, [r5, #0x38]
	asr r4, r1, #5
	bl GetPlayerYCoord
	asr r1, r0, #4
	lsr r1, r1, #0x1b
	add r1, r0, r1
	asr r2, r1, #5
	ldr r0, [r5, #0x28]
	add r1, r4, #0
	bl MapMatrix_GetMapHeader
	add r4, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r6, [r0]
	cmp r4, r6
	bne _021D78CE
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D78CE:
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	add r7, r0, #0
	ldr r0, [r5, #0x1c]
	add r1, r4, #0
	str r4, [r0]
	add r0, r5, #0
	bl sub_02034A60
	add r0, r5, #0
	mov r1, #1
	bl sub_020489FC
	add r0, r5, #0
	bl sub_02034B64
	str r0, [sp, #4]
	add r0, r5, #0
	bl sub_02034B6C
	str r0, [sp]
	ldr r0, [r5, #0x34]
	ldr r3, [sp, #4]
	add r1, r6, #0
	add r2, r4, #0
	bl sub_020573C8
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	bl sub_0205DD40
	ldr r1, [r5, #0x1c]
	add r0, r5, #0
	ldr r1, [r1]
	bl FieldSystem_GetOverriddenMusicId
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #1
	bl FieldSystem_PlayOrFadeToNewMusicId
	add r0, r5, #0
	bl sub_02034AC8
	add r0, r7, #0
	bl LocalFieldData_GetWeatherType
	add r1, r0, #0
	ldr r0, [r5, #4]
	ldr r0, [r0, #0xc]
	bl ov05_021DC174
	add r0, r6, #0
	bl MapHeader_GetMapSec
	add r6, r0, #0
	add r0, r4, #0
	bl MapHeader_GetMapSec
	add r1, r0, #0
	cmp r6, r1
	beq _021D7956
	ldr r0, [r5, #4]
	ldr r0, [r0, #8]
	bl ov05_021E3270
_021D7956:
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021D795C
ov05_021D795C: ; 0x021D795C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0204646C
	cmp r0, #0
	bne _021D7970
	add r0, r5, #0
	bl sub_0204B0F8
_021D7970:
	ldr r0, [r5, #0x48]
	bl ov05_021DB4D0
	add r0, r5, #0
	bl ov05_021E8158
	mov r0, #1
	tst r0, r4
	beq _021D798A
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x10]
	bl ov05_021DBFF8
_021D798A:
	mov r0, #8
	tst r0, r4
	beq _021D7996
	ldr r0, [r5, #0x4c]
	bl ov05_021DA1AC
_021D7996:
	mov r0, #2
	tst r0, r4
	beq _021D79A4
	ldr r1, [r5, #0x24]
	add r0, r5, #0
	bl ov05_021EE52C
_021D79A4:
	mov r0, #4
	tst r0, r4
	beq _021D79B0
	add r0, r5, #0
	bl ov05_021D7BE0
_021D79B0:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021D79B4
ov05_021D79B4: ; 0x021D79B4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #0
	beq _021D79FE
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034E0C
	add r7, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	asr r1, r0, #4
	lsr r1, r1, #0x1b
	add r1, r0, r1
	ldr r0, [r5, #0x38]
	asr r6, r1, #5
	bl GetPlayerYCoord
	asr r1, r0, #4
	lsr r1, r1, #0x1b
	add r1, r0, r1
	ldr r0, [r5, #0x38]
	asr r4, r1, #5
	bl PlayerAvatar_GetFacingDirection
	add r3, r0, #0
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl sub_0204AE5C
_021D79FE:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021D7A00
ov05_021D7A00: ; 0x021D7A00
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7A1C ; =ov05_021F64A0
	add r3, sp, #0
	mov r2, #5
_021D7A0A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7A0A
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.balign 4, 0
_021D7A1C: .word ov05_021F64A0

	thumb_func_start ov05_021D7A20
ov05_021D7A20: ; 0x021D7A20
	ldr r3, _021D7A24 ; =ov05_021D7A30
	bx r3
	.balign 4, 0
_021D7A24: .word ov05_021D7A30

	thumb_func_start ov05_021D7A28
ov05_021D7A28: ; 0x021D7A28
	ldr r3, _021D7A2C ; =ov05_021D7B10
	bx r3
	.balign 4, 0
_021D7A2C: .word ov05_021D7B10

	thumb_func_start ov05_021D7A30
ov05_021D7A30: ; 0x021D7A30
	push {r3, r4, r5, lr}
	sub sp, #0x68
	ldr r5, _021D7B00 ; =ov05_021F643C
	add r3, sp, #0x58
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	ldr r5, _021D7B04 ; =ov05_021F6468
	add r3, sp, #0x3c
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
	mov r3, #4
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D7B08 ; =ov05_021F644C
	add r3, sp, #0x20
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
	mov r3, #4
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #2
	bl BgClearTilemapBufferAndCommit
	ldr r5, _021D7B0C ; =ov05_021F6484
	add r3, sp, #4
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
	mov r3, #4
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r0, #0
	add r1, sp, #0
	strh r0, [r1]
	mov r1, #2
	bl DC_FlushRange
	add r0, sp, #0
	mov r1, #0
	mov r2, #2
	bl GX_LoadBGPltt
	add sp, #0x68
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021D7B00: .word ov05_021F643C
_021D7B04: .word ov05_021F6468
_021D7B08: .word ov05_021F644C
_021D7B0C: .word ov05_021F6484

	thumb_func_start ov05_021D7B10
ov05_021D7B10: ; 0x021D7B10
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xf
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
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021D7B38
ov05_021D7B38: ; 0x021D7B38
	push {lr}
	sub sp, #0x14
	bl NNS_G2dInitOamManagerModule
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7c
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x1f
	str r3, [sp, #0xc]
	mov r2, #4
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl sub_02009EAC
	add sp, #0x14
	pop {pc}

	thumb_func_start ov05_021D7B5C
ov05_021D7B5C: ; 0x021D7B5C
	ldr r3, _021D7B60 ; =DeinitOamData
	bx r3
	.balign 4, 0
_021D7B60: .word DeinitOamData

	thumb_func_start ov05_021D7B64
ov05_021D7B64: ; 0x021D7B64
	push {r4, lr}
	mov r1, #0
	add r4, r0, #0
	add r2, r1, #0
	bl ov05_021DBD20
	add r0, r4, #0
	mov r1, #2
	mov r2, #0
	bl ov05_021DBD34
	add r0, r4, #0
	mov r1, #0x1f
	mov r2, #0
	bl ov05_021DBD48
	mov r1, #2
	add r0, r4, #0
	lsl r1, r1, #0xe
	mov r2, #1
	mov r3, #0
	bl ov05_021DBD5C
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0x16
	bl ov05_021DBAEC
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021D7BA0
ov05_021D7BA0: ; 0x021D7BA0
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D7BD0 ; =ov05_021F642C
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r1, #0x10
	add r0, r2, #0
	add r2, r1, #0
	bl sub_0201D060
	mov r0, #0x14
	mov r1, #4
	bl sub_0201E00C
	bl sub_0201D168
	bl sub_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.balign 4, 0
_021D7BD0: .word ov05_021F642C

	thumb_func_start ov05_021D7BD4
ov05_021D7BD4: ; 0x021D7BD4
	push {r3, lr}
	bl sub_0201D12C
	bl sub_0201E08C
	pop {r3, pc}

	thumb_func_start ov05_021D7BE0
ov05_021D7BE0: ; 0x021D7BE0
	push {r3, r4, r5, lr}
	sub sp, #0x80
	add r4, r0, #0
	bl sub_020222AC
	bl Camera_PushLookAtToNNSGlb
	add r0, r4, #0
	bl sub_0205E0A8
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x40]
	bl ov05_021EF4C4
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r4, #0x2c]
	bl ov05_021E805C
	ldr r5, _021D7C98 ; =NNS_G3dGlb + 0x8
	add r3, sp, #0x40
	mov r2, #8
_021D7C0E:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7C0E
	add r5, sp, #0x40
	add r3, sp, #0
	mov r2, #8
_021D7C1C:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7C1C
	ldr r3, [sp, #0x28]
	ldr r1, [sp, #0x38]
	asr r0, r3, #0x1f
	lsr r2, r3, #0x12
	lsl r0, r0, #0xe
	orr r0, r2
	mov r2, #2
	lsl r5, r3, #0xe
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r5, r2
	adc r0, r3
	lsl r0, r0, #0x14
	lsr r2, r2, #0xc
	orr r2, r0
	add r0, r1, r2
	str r0, [sp, #0x38]
	ldr r1, _021D7C98 ; =NNS_G3dGlb + 0x8
	add r0, sp, #0
	mov r2, #0x40
	bl MIi_CpuCopyFast
	ldr r1, _021D7C9C ; =NNS_G3dGlb + 0x80
	mov r0, #0x50
	ldr r2, [r1, #0x7c]
	bic r2, r0
	str r2, [r1, #0x7c]
	bl NNS_G3dGlbFlushP
	ldr r0, [r4, #0x3c]
	bl ov05_021E4BA0
	bl sub_0201F178
	ldr r1, _021D7C98 ; =NNS_G3dGlb + 0x8
	add r0, sp, #0x40
	mov r2, #0x40
	bl MIi_CpuCopyFast
	ldr r1, _021D7C9C ; =NNS_G3dGlb + 0x80
	mov r0, #0x50
	ldr r2, [r1, #0x7c]
	bic r2, r0
	str r2, [r1, #0x7c]
	bl NNS_G3dGlbFlushP
	ldr r0, [r4, #4]
	ldr r0, [r0, #4]
	bl ov05_021D7FD0
	ldr r1, _021D7CA0 ; =g3dDepthBufferingMode
	mov r0, #0
	ldr r1, [r1]
	bl sub_020222B4
	add sp, #0x80
	pop {r3, r4, r5, pc}
	nop
_021D7C98: .word NNS_G3dGlb + 0x8
_021D7C9C: .word NNS_G3dGlb + 0x80
_021D7CA0: .word g3dDepthBufferingMode

	thumb_func_start ov05_021D7CA4
ov05_021D7CA4: ; 0x021D7CA4
	push {lr}
	sub sp, #0xc
	cmp r0, #1
	bne _021D7CC6
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl BeginNormalPaletteFade
	add sp, #0xc
	pop {pc}
_021D7CC6:
	cmp r0, #0
	bne _021D7CE6
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl BeginNormalPaletteFade
	add sp, #0xc
	pop {pc}
_021D7CE6:
	bl GF_AssertFail
	add sp, #0xc
	pop {pc}
	.balign 4, 0

	thumb_func_start ov05_021D7CF0
ov05_021D7CF0: ; 0x021D7CF0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, _021D7D44 ; =g3dDepthBufferingMode
	ldr r0, [r0]
	lsl r1, r0, #1
	ldr r0, _021D7D48 ; =0x04000540
	str r1, [r0]
	bl ov05_021D9B54
	str r0, [r5, #0x4c]
	bl ov05_021DA430
	str r0, [r5, #0x50]
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MapHeader_GetAreaDataBank
	ldr r1, [r5, #0x4c]
	bl ov05_021F4978
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MapHeader_GetMoveModelBank
	add r4, r0, #0
	ldr r0, [r5, #0x30]
	cmp r0, #0
	beq _021D7D36
	bl GF_AssertFail
_021D7D36:
	mov r0, #4
	add r1, r4, #0
	bl ov05_021D7EE8
	str r0, [r5, #0x30]
	pop {r3, r4, r5, pc}
	nop
_021D7D44: .word g3dDepthBufferingMode
_021D7D48: .word 0x04000540

	thumb_func_start ov05_021D7D4C
ov05_021D7D4C: ; 0x021D7D4C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	ldr r2, [r4, #0x4c]
	ldr r3, [r4, #0x5c]
	bl ov05_021EF368
	str r0, [r4, #0x24]
	mov r0, #8
	mov r1, #4
	bl ov05_021F4498
	add r1, r4, #0
	add r1, #0x9c
	str r0, [r1]
	bl ov05_021F4CF8
	add r1, r4, #0
	add r1, #0xa4
	str r0, [r1]
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	bne _021D7D86
	ldr r0, [r4, #0x24]
	ldr r1, _021D7D94 ; =ov05_021F521C
	add r2, r4, #0
	bl ov05_021EF8E8
_021D7D86:
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x24]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0xc]
	bl ov05_021EF434
	pop {r4, pc}
	.balign 4, 0
_021D7D94: .word ov05_021F521C

	thumb_func_start ov05_021D7D98
ov05_021D7D98: ; 0x021D7D98
	push {r4, r5, lr}
	sub sp, #0x14
	mov r3, #6
	mov r1, #0x20
	mov r2, #4
	lsl r3, r3, #0xe
	add r4, r0, #0
	bl ov05_021E4AE4
	mov r1, #0x50
	str r0, [r4, #0x3c]
	bl ov05_021E4B38
	mov r2, #0x20
	str r2, [sp]
	mov r0, #5
	str r2, [sp, #4]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	lsl r0, r2, #6
	str r0, [sp, #0xc]
	lsl r0, r2, #0xb
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x3c]
	mov r1, #4
	add r3, r2, #0
	bl ov05_021E4B44
	ldr r0, [r4, #0x6c]
	sub r0, r0, #1
	cmp r0, #1
	bhi _021D7DE0
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl sub_02058804
_021D7DE0:
	ldr r0, [r4, #0x6c]
	cmp r0, #1
	ldr r0, [r4, #0x3c]
	bne _021D7DF0
	ldr r1, _021D7E44 ; =ov05_021FC79C
	bl ov05_021E4B84
	b _021D7DF6
_021D7DF0:
	ldr r1, _021D7E48 ; =ov05_021FC718
	bl ov05_021E4B84
_021D7DF6:
	ldr r0, [r4, #0x30]
	bl ov05_021D7F40
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	bl ov05_021D7F3C
	add r3, r0, #0
	ldr r0, [r4, #0x34]
	mov r1, #0x20
	add r2, r5, #3
	bl ov05_021F1CB8
	ldr r0, [r4, #0x38]
	bl sub_02055108
	ldr r0, [r4, #0x34]
	bl sub_020577A8
	bl sub_0204F88C
	ldr r0, [r4, #0x34]
	bl sub_02058774
	ldr r0, [r4, #0x38]
	bl sub_02055360
	ldr r1, [r4, #0x24]
	bl ov05_021EF5E0
	add r0, r4, #0
	mov r1, #4
	bl sub_0204B388
	ldr r1, [r4, #4]
	str r0, [r1, #0x18]
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_021D7E44: .word ov05_021FC79C
_021D7E48: .word ov05_021FC718

	thumb_func_start ov05_021D7E4C
ov05_021D7E4C: ; 0x021D7E4C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	bl GX_BothDispOn
	bl ov05_021DBABC
	str r0, [r4, #0x40]
	bl ov05_021D7B64
	bl ov05_021DBA00
	str r0, [r4, #0x44]
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034E10
	add r5, r0, #0
	ldr r0, [r4, #0x38]
	bl sub_02055360
	add r1, r4, #0
	add r2, r5, #0
	mov r3, #1
	bl ov05_021DBD84
	ldr r0, [r4, #0x2c]
	bl ov05_021F4CBC
	add r1, r0, #0
	ldr r0, [r4, #0x40]
	bl ov05_021DB44C
	str r0, [r4, #0x48]
	add r0, r4, #0
	bl ov05_021DC0B8
	ldr r1, [r4, #4]
	str r0, [r1, #0xc]
	ldr r0, [r4, #8]
	bl ov05_021E320C
	ldr r1, [r4, #4]
	str r0, [r1, #8]
	mov r0, #4
	bl ov05_021E80F8
	str r0, [r4, #0x60]
	bl ov05_021DBEF4
	ldr r1, [r4, #4]
	str r0, [r1, #0x10]
	ldr r0, [r4, #0x2c]
	bl ov05_021F4C74
	add r1, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x10]
	bl ov05_021DBF20
	add r0, r4, #0
	bl sub_0205CDB4
	add r0, r4, #0
	bl ov05_021F38B8
	ldr r0, _021D7EE4 ; =ov05_021D74E0
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	pop {r3, r4, r5, pc}
	nop
_021D7EE4: .word ov05_021D74E0

	thumb_func_start ov05_021D7EE8
ov05_021D7EE8: ; 0x021D7EE8
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	mov r1, #0x64
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0x60
	add r1, r6, #0
	add r2, r5, #0
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	ldr r1, _021D7F38 ; =0x0000FFFF
	mov r2, #0
	add r3, r4, #0
_021D7F06:
	add r2, r2, #1
	str r1, [r3, #4]
	add r3, r3, #4
	cmp r2, #0x18
	blt _021D7F06
	ldr r5, _021D7F38 ; =0x0000FFFF
	mov r3, #0
	add r1, r0, #0
	add r2, r4, #0
_021D7F18:
	ldrh r6, [r1]
	str r6, [r2, #4]
	ldrh r6, [r1]
	cmp r6, r5
	beq _021D7F2C
	add r3, r3, #1
	add r1, r1, #2
	add r2, r2, #4
	cmp r3, #0x18
	blt _021D7F18
_021D7F2C:
	strh r3, [r4]
	bl FreeToHeap
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_021D7F38: .word 0x0000FFFF

	thumb_func_start ov05_021D7F3C
ov05_021D7F3C: ; 0x021D7F3C
	add r0, r0, #4
	bx lr

	thumb_func_start ov05_021D7F40
ov05_021D7F40: ; 0x021D7F40
	ldrh r0, [r0]
	bx lr

	thumb_func_start ov05_021D7F44
ov05_021D7F44: ; 0x021D7F44
	ldr r3, _021D7F48 ; =FreeToHeap
	bx r3
	.balign 4, 0
_021D7F48: .word FreeToHeap

	.section .rodata

	.global ov05_021F642C
ov05_021F642C: ; 0x021F642C
	.word 0x00000014, 0x00004000, 0x00004000, 0x00000004

	.global ov05_021F643C
ov05_021F643C: ; 0x021F643C
	.word 0x00000001, 0x00000000, 0x00000000, 0x00000001

	.global ov05_021F644C
ov05_021F644C: ; 0x021F644C
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.word 0x05010001, 0x00000301, 0x00000000

	.global ov05_021F6468
ov05_021F6468: ; 0x021F6468
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.word 0x04000001, 0x00000300, 0x00000000

	.global ov05_021F6484
ov05_021F6484: ; 0x021F6484
	.word 0x00000000, 0x00000000, 0x00000800, 0x00000000
	.word 0x02020001, 0x00000001, 0x00000000

	.global ov05_021F64A0
ov05_021F64A0: ; 0x021F64A0
	.word 0x00000004, 0x00000000, 0x00000080, 0x00000000
	.word 0x00000020, 0x00000000, 0x00000100, 0x00000000
	.word 0x00000003, 0x00000010

	.global ov05_021F64C8
ov05_021F64C8: ; 0x021F64C8
	.word ov05_021D7504, ov05_021D767C, ov05_021D76C0, 0xFFFFFFFF
