	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov06_022396A0
ov06_022396A0: ; 0x022396A0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r5, #4
	add r4, r2, #0
	add r6, r3, #0
	str r1, [r5]
	bl ov06_0223972C
	mov r0, #0
	str r0, [r5, #0x38]
	str r4, [r5, #0x30]
	str r6, [r5, #0x34]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_022396BC
ov06_022396BC: ; 0x022396BC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x38]
	cmp r1, #5
	bhi _02239712
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022396D2: ; jump table
	.short _022396DE - _022396D2 - 2 ; case 0
	.short _022396EA - _022396D2 - 2 ; case 1
	.short _02239712 - _022396D2 - 2 ; case 2
	.short _022396FC - _022396D2 - 2 ; case 3
	.short _02239708 - _022396D2 - 2 ; case 4
	.short _02239712 - _022396D2 - 2 ; case 5
_022396DE:
	bl ov06_022397F4
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	pop {r4, pc}
_022396EA:
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x34]
	bl ov06_0223987C
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	pop {r4, pc}
_022396FC:
	bl ov06_022398A8
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
	pop {r4, pc}
_02239708:
	bl ov06_02239808
	ldr r0, [r4, #0x38]
	add r0, r0, #1
	str r0, [r4, #0x38]
_02239712:
	pop {r4, pc}

	thumb_func_start ov06_02239714
ov06_02239714: ; 0x02239714
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	cmp r0, #2
	beq _02239722
	bl GF_AssertFail
_02239722:
	mov r0, #3
	str r0, [r4, #0x38]
	pop {r4, pc}

	thumb_func_start ov06_02239728
ov06_02239728: ; 0x02239728
	ldr r0, [r0, #0x38]
	bx lr

	thumb_func_start ov06_0223972C
ov06_0223972C: ; 0x0223972C
	push {r4, lr}
	add r4, r0, #0
	bl GX_GetBankForBG
	str r0, [r4]
	bl GX_GetBankForBGExtPltt
	str r0, [r4, #4]
	bl GX_GetBankForSubBG
	str r0, [r4, #8]
	bl GX_GetBankForSubBGExtPltt
	str r0, [r4, #0xc]
	bl GX_GetBankForOBJ
	str r0, [r4, #0x10]
	bl GX_GetBankForOBJExtPltt
	str r0, [r4, #0x14]
	bl GX_GetBankForSubOBJ
	str r0, [r4, #0x18]
	bl GX_GetBankForSubOBJExtPltt
	str r0, [r4, #0x1c]
	bl GX_GetBankForTex
	str r0, [r4, #0x20]
	bl GX_GetBankForTexPltt
	str r0, [r4, #0x24]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02239770
ov06_02239770: ; 0x02239770
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _0223978C ; =0x0224F1F4
	add r3, sp, #0
	mov r2, #5
_0223977A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223977A
	add r0, sp, #0
	bl GfGfx_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_0223978C: .word ov06_0224F1F4

	thumb_func_start ov06_02239790
ov06_02239790: ; 0x02239790
	push {r4, r5, lr}
	sub sp, #0x2c
	ldr r5, _022397EC ; =0x0224F180
	add r3, sp, #0x1c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl SetBothScreensModesAndDisable
	mov r0, #1
	add r1, r0, #0
	bl GfGfx_EngineATogglePlanes
	ldr r5, _022397F0 ; =0x0224F1D8
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
	mov r3, #4
	bl BG_ClearCharDataRange
	add r0, r4, #0
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	add sp, #0x2c
	pop {r4, r5, pc}
	nop
_022397EC: .word ov06_0224F180
_022397F0: .word ov06_0224F1D8

	thumb_func_start ov06_022397F4
ov06_022397F4: ; 0x022397F4
	ldr r3, _02239800 ; =sub_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _02239804 ; =ov06_0223981C
	lsl r2, r2, #0xa
	bx r3
	.align 2, 0
_02239800: .word sub_0200CA98
_02239804: .word ov06_0223981C

	thumb_func_start ov06_02239808
ov06_02239808: ; 0x02239808
	ldr r3, _02239814 ; =sub_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _02239818 ; =ov06_02239840
	lsl r2, r2, #0xa
	bx r3
	.align 2, 0
_02239814: .word sub_0200CA98
_02239818: .word ov06_02239840

	thumb_func_start ov06_0223981C
ov06_0223981C: ; 0x0223981C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl ov06_02239770
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl ov06_02239864
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl ov06_02239790
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_02239840
ov06_02239840: ; 0x02239840
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #4
	bl GfGfx_SetBanks
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl ov06_02239864
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl ov06_0223986C
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02239864
ov06_02239864: ; 0x02239864
	ldr r3, _02239868 ; =ov05_021D7A28
	bx r3
	.align 2, 0
_02239868: .word ov05_021D7A28

	thumb_func_start ov06_0223986C
ov06_0223986C: ; 0x0223986C
	push {r3, lr}
	bl ov05_021D7A20
	mov r0, #1
	add r1, r0, #0
	bl GfGfx_EngineATogglePlanes
	pop {r3, pc}

	thumb_func_start ov06_0223987C
ov06_0223987C: ; 0x0223987C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	ldr r6, _022398A4 ; =0x0224F21C
	add r3, r0, #0
	add r2, r1, #0
	add r5, sp, #0
	mov r4, #5
_0223988A:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r4, r4, #1
	bne _0223988A
	ldr r0, [r6]
	str r0, [r5]
	add r0, sp, #0
	str r3, [sp, #0x20]
	str r2, [sp, #0x24]
	bl ov05_021E8648
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022398A4: .word ov06_0224F21C

	thumb_func_start ov06_022398A8
ov06_022398A8: ; 0x022398A8
	ldr r3, _022398B4 ; =sub_0200CA98
	mov r2, #1
	add r1, r0, #0
	ldr r0, _022398B8 ; =ov06_022398BC
	lsl r2, r2, #0xa
	bx r3
	.align 2, 0
_022398B4: .word sub_0200CA98
_022398B8: .word ov06_022398BC

	thumb_func_start ov06_022398BC
ov06_022398BC: ; 0x022398BC
	push {r4, lr}
	add r1, #0x2c
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #1
	mov r2, #0
	add r3, r1, #0
	bl ov05_021E8698
	add r0, r4, #0
	bl sub_0200CAB4
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_022398D8
ov06_022398D8: ; 0x022398D8
	push {r4, lr}
	ldr r0, [r0, #0x34]
	add r4, r2, #0
	bl GetMapObjectByID
	cmp r4, #1
	bne _022398F0
	mov r1, #1
	lsl r1, r1, #0x14
	bl MapObject_SetFlagsBits
	pop {r4, pc}
_022398F0:
	mov r1, #1
	lsl r1, r1, #0x14
	bl MapObject_ClearFlagsBits
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_022398FC
ov06_022398FC: ; 0x022398FC
	push {r4, lr}
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02239918
	cmp r0, #1
	beq _02239930
	b _02239940
_02239918:
	ldr r0, [r4]
	bl ov06_0223A4E0
	ldr r0, [r4]
	bl ov06_0223A5B0
	cmp r0, #1
	bne _02239940
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02239940
_02239930:
	ldr r0, [r4]
	bl ov06_0223A44C
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
_02239940:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov06_02239944
ov06_02239944: ; 0x02239944
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r0, #0
	bl TaskManager_GetFieldSystem
	add r4, r0, #0
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	add r5, r0, #0
	add r2, r5, #0
	mov r1, #0x10
	mov r0, #0
_02239960:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _02239960
	mov r0, #4
	bl ov06_0223A428
	str r0, [r5]
	mov r1, #0x10
	str r1, [sp]
	ldr r0, [r4, #0x20]
	lsl r1, r1, #9
	str r0, [sp, #4]
	ldr r0, [r5]
	mov r2, #0
	mov r3, #1
	bl ov06_0223A460
	ldr r1, _02239994 ; =ov06_022398FC
	add r0, r6, #0
	add r2, r5, #0
	bl TaskManager_Call
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_02239994: .word ov06_022398FC

	thumb_func_start ov06_02239998
ov06_02239998: ; 0x02239998
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl ov06_0223A63C
	add r4, r0, #0
	ldr r0, [r5]
	bl ov06_0223A638
	ldr r1, [r5, #8]
	cmp r1, r0
	beq _022399C4
	mov r1, #2
	str r0, [r5, #8]
	add r0, r4, #0
	lsl r1, r1, #0xe
	bl FX_Div
	sub r1, r4, r0
	ldr r0, [r5]
	bl ov06_0223A640
_022399C4:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022399C8
ov06_022399C8: ; 0x022399C8
	push {r4, lr}
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #7
	bhi _02239AA4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022399EA: ; jump table
	.short _022399FA - _022399EA - 2 ; case 0
	.short _02239A0A - _022399EA - 2 ; case 1
	.short _02239A1E - _022399EA - 2 ; case 2
	.short _02239A36 - _022399EA - 2 ; case 3
	.short _02239A60 - _022399EA - 2 ; case 4
	.short _02239A72 - _022399EA - 2 ; case 5
	.short _02239A84 - _022399EA - 2 ; case 6
	.short _02239A94 - _022399EA - 2 ; case 7
_022399FA:
	mov r0, #0
	mov r1, #1
	bl GF_SndStartFadeOutBGM
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02239AA4
_02239A0A:
	bl GF_SndGetFadeTimer
	cmp r0, #0
	bne _02239AA4
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0x10
	str r0, [r4, #4]
	b _02239AA4
_02239A1E:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0
	bgt _02239AA4
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, _02239AA8 ; =0x0000065C
	bl PlaySE
	b _02239AA4
_02239A36:
	ldr r0, [r4]
	bl ov06_0223A4E0
	add r0, r4, #0
	bl ov06_02239998
	ldr r0, [r4]
	bl ov06_0223A5B0
	cmp r0, #1
	bne _02239AA4
	ldr r0, _02239AA8 ; =0x0000065C
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	mov r0, #0x10
	str r0, [r4, #4]
	b _02239AA4
_02239A60:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0
	bgt _02239AA4
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02239AA4
_02239A72:
	mov r0, #0x7f
	mov r1, #0x10
	mov r2, #0
	bl sub_0200538C
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02239AA4
_02239A84:
	bl GF_SndGetFadeTimer
	cmp r0, #0
	bne _02239AA4
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02239AA4
_02239A94:
	ldr r0, [r4]
	bl ov06_0223A44C
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
_02239AA4:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02239AA8: .word 0x0000065C

	thumb_func_start ov06_02239AAC
ov06_02239AAC: ; 0x02239AAC
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r0, #0
	bl TaskManager_GetFieldSystem
	add r4, r0, #0
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	add r5, r0, #0
	add r2, r5, #0
	mov r1, #0x10
	mov r0, #0
_02239AC8:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _02239AC8
	mov r0, #4
	bl ov06_0223A428
	str r0, [r5]
	mov r0, #0x18
	str r0, [sp]
	ldr r0, [r4, #0x20]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, [r5]
	lsl r1, r1, #0xe
	mov r2, #0
	mov r3, #1
	bl ov06_0223A460
	ldr r0, [r5]
	bl ov06_0223A638
	str r0, [r5, #8]
	ldr r1, _02239B04 ; =ov06_022399C8
	add r0, r6, #0
	add r2, r5, #0
	bl TaskManager_Call
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_02239B04: .word ov06_022399C8

	thumb_func_start ov06_02239B08
ov06_02239B08: ; 0x02239B08
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x74
	bl memset
	mov r0, #4
	add r1, r5, #0
	bl ov06_0223AC78
	str r0, [r4, #0x44]
	mov r0, #4
	bl ov06_0223A428
	str r0, [r4, #0x48]
	mov r0, #4
	bl ov06_0223A644
	str r0, [r4, #0x4c]
	mov r0, #0
	str r0, [r4]
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02239B38
ov06_02239B38: ; 0x02239B38
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0x44]
	bl ov06_0223ACC0
	ldr r0, [r4, #0x50]
	bl ov06_0223B8C0
	ldr r0, [r4, #0x48]
	bl ov06_0223A44C
	ldr r0, [r4, #0x4c]
	bl ov06_0223A660
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02239B58
ov06_02239B58: ; 0x02239B58
	push {r4, r5, r6, lr}
	add r4, r2, #0
	ldr r0, [r4]
	add r5, r1, #0
	cmp r0, #0xb
	bhi _02239BB0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02239B70: ; jump table
	.short _02239B88 - _02239B70 - 2 ; case 0
	.short _02239B9C - _02239B70 - 2 ; case 1
	.short _02239BBA - _02239B70 - 2 ; case 2
	.short _02239BCE - _02239B70 - 2 ; case 3
	.short _02239BEC - _02239B70 - 2 ; case 4
	.short _02239C16 - _02239B70 - 2 ; case 5
	.short _02239C46 - _02239B70 - 2 ; case 6
	.short _02239C56 - _02239B70 - 2 ; case 7
	.short _02239C72 - _02239B70 - 2 ; case 8
	.short _02239C86 - _02239B70 - 2 ; case 9
	.short _02239CA0 - _02239B70 - 2 ; case 10
	.short _02239CBA - _02239B70 - 2 ; case 11
_02239B88:
	add r0, r4, #0
	mov r2, #8
	add r0, #8
	add r3, r2, #0
	bl ov06_022396A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239B9C:
	add r0, r4, #0
	add r0, #8
	bl ov06_022396BC
	add r0, r4, #0
	add r0, #8
	bl ov06_02239728
	cmp r0, #2
	beq _02239BB2
_02239BB0:
	b _02239CBA
_02239BB2:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239BBA:
	ldr r0, [r4, #0x44]
	mov r1, #5
	bl ov06_0223ACD8
	mov r0, #0xf0
	str r0, [r4, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239BCE:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239CBA
	add r0, r4, #0
	ldr r1, [r4, #0x48]
	ldr r2, [r4, #0x4c]
	ldr r3, [r5, #0x20]
	add r0, #0x54
	bl ov06_02239D18
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239BEC:
	add r0, r4, #0
	add r0, #0x54
	bl ov06_02239D2C
	add r5, r0, #0
	ldr r0, [r4, #0x44]
	bl ov06_0223AD10
	cmp r5, #1
	bne _02239CBA
	cmp r0, #1
	bne _02239CBA
	add r0, r4, #0
	ldr r1, [r4, #0x4c]
	add r0, #0x68
	bl ov06_02239E60
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239C16:
	add r0, r4, #0
	add r0, #0x68
	bl ov06_02239E6C
	add r6, r0, #0
	ldr r0, [r4, #0x68]
	cmp r0, #3
	bne _02239C3A
	ldr r0, [r4, #0x70]
	bl ov06_0223A748
	cmp r0, #0xd
	bne _02239C3A
	mov r0, #4
	add r1, r5, #0
	bl ov06_0223B828
	str r0, [r4, #0x50]
_02239C3A:
	cmp r6, #1
	bne _02239CBA
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239C46:
	add r0, r4, #0
	add r0, #8
	bl ov06_02239714
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239C56:
	add r0, r4, #0
	add r0, #8
	bl ov06_022396BC
	add r0, r4, #0
	add r0, #8
	bl ov06_02239728
	cmp r0, #5
	bne _02239CBA
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239C72:
	ldr r0, [r4, #0x50]
	mov r1, #5
	bl ov06_0223B8EC
	mov r0, #0x48
	str r0, [r4, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239CBA
_02239C86:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0
	bgt _02239CA0
	add r0, r5, #0
	mov r1, #5
	mov r2, #1
	bl ov06_022398D8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02239CA0:
	ldr r0, [r4, #0x50]
	bl ov06_0223B924
	cmp r0, #1
	bne _02239CBA
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl ov06_022398D8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02239CBA:
	ldr r0, [r4, #0x44]
	bl ov06_0223AD24
	ldr r0, [r4, #0x48]
	bl ov06_0223A4E0
	ldr r0, [r4, #0x4c]
	bl ov06_0223A6DC
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02239CD0
ov06_02239CD0: ; 0x02239CD0
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0x44]
	bl ov06_0223AD9C
	ldr r0, [r4, #0x50]
	cmp r0, #0
	beq _02239CE4
	bl ov06_0223B93C
_02239CE4:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02239CE8
ov06_02239CE8: ; 0x02239CE8
	ldr r0, [r0, #4]
	ldr r3, _02239CF4 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _02239CF8 ; =0x0224F1C0
	bx r3
	nop
_02239CF4: .word ov05_021D8024
_02239CF8: .word ov06_0224F1C0

	thumb_func_start ov06_02239CFC
ov06_02239CFC: ; 0x02239CFC
	ldr r3, _02239D00 ; =ov05_021D80A4
	bx r3
	.align 2, 0
_02239D00: .word ov05_021D80A4

	thumb_func_start ov06_02239D04
ov06_02239D04: ; 0x02239D04
	push {r3, lr}
	bl ov05_021D80E4
	ldr r0, [r0]
	cmp r0, #0xb
	bne _02239D14
	mov r0, #1
	pop {r3, pc}
_02239D14:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov06_02239D18
ov06_02239D18: ; 0x02239D18
	push {r3, r4}
	mov r4, #0
	str r4, [r0]
	str r4, [r0, #4]
	str r1, [r0, #8]
	str r2, [r0, #0xc]
	str r3, [r0, #0x10]
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start ov06_02239D2C
ov06_02239D2C: ; 0x02239D2C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #7
	bls _02239D3A
	b _02239E58
_02239D3A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02239D46: ; jump table
	.short _02239D56 - _02239D46 - 2 ; case 0
	.short _02239D62 - _02239D46 - 2 ; case 1
	.short _02239D82 - _02239D46 - 2 ; case 2
	.short _02239DB6 - _02239D46 - 2 ; case 3
	.short _02239DD6 - _02239D46 - 2 ; case 4
	.short _02239E00 - _02239D46 - 2 ; case 5
	.short _02239E20 - _02239D46 - 2 ; case 6
	.short _02239E52 - _02239D46 - 2 ; case 7
_02239D56:
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239E58
_02239D62:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239E58
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	mov r2, #4
	mov r3, #0x10
	bl ov06_0223A67C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x50
	str r0, [r4, #4]
	b _02239E58
_02239D82:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239E58
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	mov r2, #4
	mov r3, #0x18
	bl ov06_0223A67C
	mov r1, #8
	str r1, [sp]
	ldr r0, [r4, #0x10]
	lsl r1, r1, #0xa
	str r0, [sp, #4]
	ldr r0, [r4, #8]
	mov r2, #0
	mov r3, #1
	bl ov06_0223A460
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x20
	str r0, [r4, #4]
	b _02239E58
_02239DB6:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239E58
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	mov r2, #4
	mov r3, #0x1b
	bl ov06_0223A67C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x3c
	str r0, [r4, #4]
	b _02239E58
_02239DD6:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239E58
	mov r0, #0xa
	str r0, [sp]
	ldr r0, [r4, #0x10]
	mov r1, #3
	str r0, [sp, #4]
	ldr r0, [r4, #8]
	lsl r1, r1, #0xc
	mov r2, #0
	mov r3, #1
	bl ov06_0223A460
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x3c
	str r0, [r4, #4]
	b _02239E58
_02239E00:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239E58
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	mov r2, #8
	mov r3, #0x20
	bl ov06_0223A67C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x28
	str r0, [r4, #4]
	b _02239E58
_02239E20:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239E58
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	mov r2, #4
	mov r3, #0x10
	bl ov06_0223A67C
	mov r0, #0xc
	str r0, [sp]
	ldr r0, [r4, #0x10]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, [r4, #8]
	lsl r1, r1, #0xe
	mov r2, #0
	mov r3, #1
	bl ov06_0223A460
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239E58
_02239E52:
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_02239E58:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02239E60
ov06_02239E60: ; 0x02239E60
	mov r2, #0
	str r2, [r0]
	mov r2, #0x20
	str r2, [r0, #4]
	str r1, [r0, #8]
	bx lr

	thumb_func_start ov06_02239E6C
ov06_02239E6C: ; 0x02239E6C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #4
	bhi _02239F00
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02239E82: ; jump table
	.short _02239E8C - _02239E82 - 2 ; case 0
	.short _02239E9C - _02239E82 - 2 ; case 1
	.short _02239EB4 - _02239E82 - 2 ; case 2
	.short _02239ED4 - _02239E82 - 2 ; case 3
	.short _02239EF4 - _02239E82 - 2 ; case 4
_02239E8C:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239F00
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02239F00
_02239E9C:
	ldr r0, [r4, #8]
	mov r1, #0xd
	mov r2, #4
	mov r3, #8
	bl ov06_0223A67C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x10
	str r0, [r4, #4]
	b _02239F00
_02239EB4:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239F00
	ldr r0, [r4, #8]
	mov r1, #0xd
	mov r2, #4
	mov r3, #8
	bl ov06_0223A67C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x10
	str r0, [r4, #4]
	b _02239F00
_02239ED4:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239F00
	ldr r0, [r4, #8]
	mov r1, #0xd
	mov r2, #4
	mov r3, #0x20
	bl ov06_0223A67C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0x28
	str r0, [r4, #4]
	b _02239F00
_02239EF4:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bpl _02239F00
	mov r0, #1
	pop {r4, pc}
_02239F00:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov06_02239F04
ov06_02239F04: ; 0x02239F04
	push {r4, r5, r6, lr}
	ldr r0, [r1, #0x34]
	mov r1, #5
	add r4, r2, #0
	bl GetMapObjectByID
	add r5, r0, #0
	bne _02239F18
	bl GF_AssertFail
_02239F18:
	add r0, r5, #0
	bl sub_02058B2C
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r5, #0
	bl sub_02058B4C
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	mov r0, #4
	bl ov06_0223B2F8
	add r1, r6, #0
	mov r2, #0
	add r3, r5, #0
	str r0, [r4]
	bl ov06_0223B30C
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02239F40
ov06_02239F40: ; 0x02239F40
	ldr r3, _02239F48 ; =ov06_0223B304
	ldr r0, [r2]
	bx r3
	nop
_02239F48: .word ov06_0223B304

	thumb_func_start ov06_02239F4C
ov06_02239F4C: ; 0x02239F4C
	ldr r3, _02239F54 ; =ov06_0223B338
	ldr r0, [r2]
	bx r3
	nop
_02239F54: .word ov06_0223B338

	thumb_func_start ov06_02239F58
ov06_02239F58: ; 0x02239F58
	ldr r3, _02239F60 ; =ov06_0223B340
	ldr r0, [r2]
	bx r3
	nop
_02239F60: .word ov06_0223B340

	thumb_func_start ov06_02239F64
ov06_02239F64: ; 0x02239F64
	ldr r0, [r0, #4]
	ldr r3, _02239F70 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _02239F74 ; =0x0224F190
	bx r3
	nop
_02239F70: .word ov05_021D8024
_02239F74: .word ov06_0224F190

	thumb_func_start ov06_02239F78
ov06_02239F78: ; 0x02239F78
	ldr r3, _02239F7C ; =ov05_021D80A4
	bx r3
	.align 2, 0
_02239F7C: .word ov05_021D80A4

	thumb_func_start ov06_02239F80
ov06_02239F80: ; 0x02239F80
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r1, #0
	ldr r0, _0223A008 ; =0x00001701
	ldr r1, [r5, #0x20]
	add r4, r2, #0
	bl Camera_SetPerspectiveAngle
	ldr r0, _0223A00C ; =0x000C8A55
	ldr r1, [r5, #0x20]
	bl Camera_SetDistance
	ldr r0, _0223A010 ; =0x002280EF
	str r0, [sp, #8]
	ldr r0, _0223A014 ; =0x000CA424
	str r0, [sp, #0xc]
	ldr r0, _0223A018 ; =0x00268C50
	str r0, [sp, #0x10]
	ldr r1, [r5, #0x20]
	add r0, sp, #8
	bl Camera_SetLookAtCamTarget
	ldr r1, _0223A01C ; =0x000022A2
	add r0, sp, #0
	strh r1, [r0]
	.ifdef DIAMOND
	mov r1, #0x3e
	lsl r1, r1, #0xa
	.else
	ldr r1, _0223A01C_PEARL ; =0x0000090C
	.endif
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	ldr r1, [r5, #0x20]
	add r0, sp, #0
	bl Camera_SetAnglePos
	.ifdef DIAMOND
	mov r0, #2
	mov r1, #0x7d
	.else
	mov r0, #0xe
	ldr r1, _0223A020_PEARL ; 0x007EF000
	.endif
	ldr r2, [r5, #0x20]
	lsl r0, r0, #0xc
	.ifdef DIAMOND
	lsl r1, r1, #0x10
	.endif
	bl Camera_SetPerspectiveClippingPlane
	mov r0, #4
	bl ov06_0223B574
	str r0, [r4, #4]
	mov r0, #4
	bl ov06_0223B648
	str r0, [r4, #8]
	ldr r1, [r5, #0x20]
	add r0, sp, #8
	bl Camera_GetLookAtCamTarget
	ldr r0, [r4, #4]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl ov06_0223B598
	ldr r0, [r4, #8]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl ov06_0223B66C
	add sp, #0x14
	pop {r4, r5, pc}
	nop
	.ifdef DIAMOND
_0223A008: .word 0x00001701
_0223A00C: .word 0x000C8A55
_0223A010: .word 0x002280EF
_0223A014: .word 0x000CA424
_0223A018: .word 0x00268C50
_0223A01C: .word 0x000022A2
	.else
_0223A008: .word 0x000010C1
_0223A00C: .word 0x000D5052
_0223A010: .word 0x001BFFBD
_0223A014: .word 0x000AA361
_0223A018: .word 0x0025DFDC
_0223A01C: .word 0x000019A3
_0223A01C_PEARL: .word 0x0000090C
_0223A020_PEARL: .word 0x007EF000
	.endif

	thumb_func_start ov06_0223A020
ov06_0223A020: ; 0x0223A020
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r1, #0
	ldr r0, _0223A0B8 ; =0x00000F81
	ldr r1, [r5, #0x20]
	add r4, r2, #0
	bl Camera_SetPerspectiveAngle
	ldr r0, _0223A0BC ; =0x0017E532
	ldr r1, [r5, #0x20]
	bl Camera_SetDistance
	ldr r0, _0223A0C0 ; =0x00F99D58
	str r0, [sp, #8]
	ldr r0, _0223A0C4 ; =0x000C5502
	str r0, [sp, #0xc]
	ldr r0, _0223A0C8 ; =0x028CF549
	str r0, [sp, #0x10]
	ldr r1, [r5, #0x20]
	add r0, sp, #8
	bl Camera_SetLookAtCamTarget
	ldr r1, _0223A0CC ; =0x00000642
	add r0, sp, #0
	strh r1, [r0]
	ldr r1, _0223A0D0 ; =0x0000EDA0
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	ldr r1, [r5, #0x20]
	add r0, sp, #0
	bl Camera_SetAnglePos
	mov r0, #0x16
	mov r1, #0x7d
	ldr r2, [r5, #0x20]
	lsl r0, r0, #0xe
	lsl r1, r1, #0x10
	bl Camera_SetPerspectiveClippingPlane
	add r0, r5, #0
	add r0, #0x48
	bl ov05_021DB4B0
	ldr r0, [r5, #0x40]
	mov r1, #2
	bl ov05_021DB44C
	str r0, [r5, #0x48]
	mov r0, #4
	bl ov06_0223B574
	str r0, [r4, #4]
	mov r0, #4
	bl ov06_0223B648
	str r0, [r4, #8]
	ldr r1, [r5, #0x20]
	add r0, sp, #8
	bl Camera_GetLookAtCamTarget
	ldr r0, [r4, #4]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl ov06_0223B5D0
	ldr r0, [r4, #8]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl ov06_0223B6A4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_0223A0B8: .word 0x00000F81
_0223A0BC: .word 0x0017E532
_0223A0C0: .word 0x00F99D58
_0223A0C4: .word 0x000C5502
_0223A0C8: .word 0x028CF549
_0223A0CC: .word 0x00000642
_0223A0D0: .word 0x0000EDA0

	thumb_func_start ov06_0223A0D4
ov06_0223A0D4: ; 0x0223A0D4
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r1, #0
	ldr r0, _0223A16C ; =0x000004C1
	ldr r1, [r5, #0x20]
	add r4, r2, #0
	bl Camera_SetPerspectiveAngle
	ldr r0, _0223A170 ; =0x0026BEC1
	ldr r1, [r5, #0x20]
	bl Camera_SetDistance
	ldr r0, _0223A174 ; =0x01DF5DFD
	str r0, [sp, #8]
	ldr r0, _0223A178 ; =0x00073A0C
	str r0, [sp, #0xc]
	ldr r0, _0223A17C ; =0x02B9F4A2
	str r0, [sp, #0x10]
	ldr r1, [r5, #0x20]
	add r0, sp, #8
	bl Camera_SetLookAtCamTarget
	ldr r1, _0223A180 ; =0x000004C2
	add r0, sp, #0
	strh r1, [r0]
	mov r1, #0x29
	lsl r1, r1, #6
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	ldr r1, [r5, #0x20]
	add r0, sp, #0
	bl Camera_SetAnglePos
	mov r0, #0xb
	ldr r1, _0223A184 ; =0x005C8000
	ldr r2, [r5, #0x20]
	lsl r0, r0, #0x10
	bl Camera_SetPerspectiveClippingPlane
	add r0, r5, #0
	add r0, #0x48
	bl ov05_021DB4B0
	ldr r0, [r5, #0x40]
	mov r1, #2
	bl ov05_021DB44C
	str r0, [r5, #0x48]
	mov r0, #4
	bl ov06_0223B574
	str r0, [r4, #4]
	mov r0, #4
	bl ov06_0223B648
	str r0, [r4, #8]
	ldr r1, [r5, #0x20]
	add r0, sp, #8
	bl Camera_GetLookAtCamTarget
	ldr r0, [r4, #4]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl ov06_0223B60C
	ldr r0, [r4, #8]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl ov06_0223B6E0
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_0223A16C: .word 0x000004C1
_0223A170: .word 0x0026BEC1
_0223A174: .word 0x01DF5DFD
_0223A178: .word 0x00073A0C
_0223A17C: .word 0x02B9F4A2
_0223A180: .word 0x000004C2
_0223A184: .word 0x005C8000

	thumb_func_start ov06_0223A188
ov06_0223A188: ; 0x0223A188
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #4]
	bl ov06_0223B580
	ldr r0, [r4, #8]
	bl ov06_0223B654
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A19C
ov06_0223A19C: ; 0x0223A19C
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #4]
	bl ov06_0223B588
	ldr r0, [r4, #8]
	bl ov06_0223B65C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A1B0
ov06_0223A1B0: ; 0x0223A1B0
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #4]
	bl ov06_0223B590
	ldr r0, [r4, #8]
	bl ov06_0223B664
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A1C4
ov06_0223A1C4: ; 0x0223A1C4
	lsl r2, r1, #2
	ldr r1, _0223A1D8 ; =0x0224F174
	ldr r3, _0223A1DC ; =ov05_021D8024
	ldr r2, [r1, r2]
	ldr r1, _0223A1E0 ; =ov06_02252240
	str r2, [r1, #8]
	ldr r0, [r0, #4]
	ldr r1, _0223A1E4 ; =ov06_02252240
	ldr r0, [r0, #4]
	bx r3
	.align 2, 0
_0223A1D8: .word ov06_0224F174
_0223A1DC: .word ov05_021D8024
_0223A1E0: .word ov06_02252240
_0223A1E4: .word ov06_02252240

	thumb_func_start ov06_0223A1E8
ov06_0223A1E8: ; 0x0223A1E8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r0, r5, #0
	bl ov06_0223A75C
	str r0, [r4, #8]
	mov r0, #4
	add r1, r5, #0
	bl ov06_0223B71C
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0223A208
ov06_0223A208: ; 0x0223A208
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #8]
	bl ov06_0223A790
	ldr r0, [r4, #0xc]
	bl ov06_0223B73C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A21C
ov06_0223A21C: ; 0x0223A21C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r0, [r4]
	cmp r0, #6
	bhi _0223A2CC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223A234: ; jump table
	.short _0223A242 - _0223A234 - 2 ; case 0
	.short _0223A26A - _0223A234 - 2 ; case 1
	.short _0223A2CC - _0223A234 - 2 ; case 2
	.short _0223A288 - _0223A234 - 2 ; case 3
	.short _0223A29A - _0223A234 - 2 ; case 4
	.short _0223A2B0 - _0223A234 - 2 ; case 5
	.short _0223A2CC - _0223A234 - 2 ; case 6
_0223A242:
	ldr r1, [r1, #0x20]
	add r0, sp, #0
	bl Camera_GetLookAtCamTarget
	mov r2, #2
	ldr r3, [sp, #4]
	lsl r2, r2, #0xc
	add r2, r3, r2
	ldr r0, [r4, #8]
	ldr r1, [sp]
	ldr r3, [sp, #8]
	bl ov06_0223A7AC
	ldr r0, [r4, #0xc]
	bl ov06_0223B744
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223A2CC
_0223A26A:
	ldr r0, [r4, #8]
	bl ov06_0223A820
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl ov06_0223B810
	cmp r5, #2
	bne _0223A2CC
	cmp r0, #2
	bne _0223A2CC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223A2CC
_0223A288:
	ldr r0, [r4, #8]
	bl ov06_0223A7DC
	mov r0, #0x40
	str r0, [r4, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223A2CC
_0223A29A:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bne _0223A2CC
	ldr r0, [r4, #0xc]
	bl ov06_0223B814
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0223A2CC
_0223A2B0:
	ldr r0, [r4, #8]
	bl ov06_0223A820
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl ov06_0223B810
	cmp r5, #5
	bne _0223A2CC
	cmp r0, #4
	bne _0223A2CC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_0223A2CC:
	ldr r0, [r4, #8]
	bl ov06_0223A868
	ldr r0, [r4, #0xc]
	bl ov06_0223B768
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0223A2DC
ov06_0223A2DC: ; 0x0223A2DC
	ldr r3, _0223A2E4 ; =ov06_0223A828
	ldr r0, [r2, #8]
	bx r3
	nop
_0223A2E4: .word ov06_0223A828

	thumb_func_start ov06_0223A2E8
ov06_0223A2E8: ; 0x0223A2E8
	ldr r0, [r0, #4]
	ldr r3, _0223A2F4 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _0223A2F8 ; =0x0224F1A8
	bx r3
	nop
_0223A2F4: .word ov05_021D8024
_0223A2F8: .word ov06_0224F1A8

	thumb_func_start ov06_0223A2FC
ov06_0223A2FC: ; 0x0223A2FC
	ldr r3, _0223A300 ; =ov05_021D80A4
	bx r3
	.align 2, 0
_0223A300: .word ov05_021D80A4

	thumb_func_start ov06_0223A304
ov06_0223A304: ; 0x0223A304
	push {r3, lr}
	bl ov05_021D80E4
	mov r1, #3
	str r1, [r0]
	pop {r3, pc}

	thumb_func_start ov06_0223A310
ov06_0223A310: ; 0x0223A310
	push {r3, lr}
	bl ov05_021D80E4
	ldr r0, [r0]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0223A31C
ov06_0223A31C: ; 0x0223A31C
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0xc]
	bx lr

	thumb_func_start ov06_0223A328
ov06_0223A328: ; 0x0223A328
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r3, [r5, #0xc]
	cmp r1, r3
	blt _0223A338
	add r1, r3, #0
	mov r4, #1
	b _0223A33A
_0223A338:
	mov r4, #0
_0223A33A:
	ldr r2, [r5, #8]
	add r0, r2, #0
	mul r0, r1
	add r1, r3, #0
	bl _s32_div_f
	ldr r1, [r5, #4]
	add r0, r0, r1
	str r0, [r5]
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223A350
ov06_0223A350: ; 0x0223A350
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0xc]
	bx lr

	thumb_func_start ov06_0223A35C
ov06_0223A35C: ; 0x0223A35C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r4, [r5, #0xc]
	add r2, r1, #0
	cmp r2, r4
	blt _0223A36E
	add r2, r4, #0
	mov r6, #1
	b _0223A370
_0223A36E:
	mov r6, #0
_0223A370:
	ldr r0, [r5, #8]
	lsl r2, r2, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	lsl r1, r4, #0xc
	bl FX_Div
	ldr r1, [r5, #4]
	add r0, r0, r1
	str r0, [r5]
	add r0, r6, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0223A39C
ov06_0223A39C: ; 0x0223A39C
	push {r3, lr}
	bl ov05_021F5268
	pop {r3, pc}

	thumb_func_start ov06_0223A3A4
ov06_0223A3A4: ; 0x0223A3A4
	ldr r3, _0223A3A8 ; =ov05_021F52C8
	bx r3
	.align 2, 0
_0223A3A8: .word ov05_021F52C8

	thumb_func_start ov06_0223A3AC
ov06_0223A3AC: ; 0x0223A3AC
	push {r4, lr}
	sub sp, #8
	ldr r4, [sp, #0x10]
	str r4, [sp]
	ldr r4, [sp, #0x14]
	str r4, [sp, #4]
	bl ov05_021F531C
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov06_0223A3C0
ov06_0223A3C0: ; 0x0223A3C0
	ldr r3, _0223A3C4 ; =ov05_021F5358
	bx r3
	.align 2, 0
_0223A3C4: .word ov05_021F5358

	thumb_func_start ov06_0223A3C8
ov06_0223A3C8: ; 0x0223A3C8
	ldr r3, _0223A3D0 ; =ov05_021F5384
	mov r1, #1
	lsl r1, r1, #0xc
	bx r3
	.align 2, 0
_0223A3D0: .word ov05_021F5384

	thumb_func_start ov06_0223A3D4
ov06_0223A3D4: ; 0x0223A3D4
	ldr r3, _0223A3D8 ; =ov05_021F5384
	bx r3
	.align 2, 0
_0223A3D8: .word ov05_021F5384

	thumb_func_start ov06_0223A3DC
ov06_0223A3DC: ; 0x0223A3DC
	ldr r3, _0223A3E4 ; =ov05_021F53BC
	mov r1, #1
	lsl r1, r1, #0xc
	bx r3
	.align 2, 0
_0223A3E4: .word ov05_021F53BC

	thumb_func_start ov06_0223A3E8
ov06_0223A3E8: ; 0x0223A3E8
	ldr r3, _0223A3EC ; =ov05_021F53F8
	bx r3
	.align 2, 0
_0223A3EC: .word ov05_021F53F8

	thumb_func_start ov06_0223A3F0
ov06_0223A3F0: ; 0x0223A3F0
	ldr r3, _0223A3F4 ; =ov05_021F5400
	bx r3
	.align 2, 0
_0223A3F4: .word ov05_021F5400

	thumb_func_start ov06_0223A3F8
ov06_0223A3F8: ; 0x0223A3F8
	ldr r3, _0223A3FC ; =ov05_021F5424
	bx r3
	.align 2, 0
_0223A3FC: .word ov05_021F5424

	thumb_func_start ov06_0223A400
ov06_0223A400: ; 0x0223A400
	ldr r3, _0223A404 ; =ov05_021F5430
	bx r3
	.align 2, 0
_0223A404: .word ov05_021F5430

	thumb_func_start ov06_0223A408
ov06_0223A408: ; 0x0223A408
	ldr r3, _0223A40C ; =ov05_021F54CC
	bx r3
	.align 2, 0
_0223A40C: .word ov05_021F54CC

	thumb_func_start ov06_0223A410
ov06_0223A410: ; 0x0223A410
	push {r3, lr}
	bl ov05_021F54D0
	pop {r3, pc}

	thumb_func_start ov06_0223A418
ov06_0223A418: ; 0x0223A418
	push {r3, lr}
	bl ov05_021F54D8
	pop {r3, pc}

	thumb_func_start ov06_0223A420
ov06_0223A420: ; 0x0223A420
	ldr r3, _0223A424 ; =ov05_021F54E0
	bx r3
	.align 2, 0
_0223A424: .word ov05_021F54E0

	thumb_func_start ov06_0223A428
ov06_0223A428: ; 0x0223A428
	push {r3, r4, r5, lr}
	mov r1, #0x4c
	add r5, r0, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x4c
	add r4, r0, #0
	bl memset
	add r0, r5, #0
	bl Camera_New
	str r0, [r4]
	mov r0, #5
	str r0, [r4, #0x40]
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223A44C
ov06_0223A44C: ; 0x0223A44C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl Camera_Delete
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A460
ov06_0223A460: ; 0x0223A460
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r7, r1, #0
	str r2, [sp]
	add r4, r3, #0
	bl ov06_0223A5C0
	ldr r0, [sp, #0x2c]
	ldr r1, [r5]
	bl Camera_Copy
	ldr r1, [sp, #0x2c]
	add r0, sp, #4
	bl Camera_GetLookAtCamTarget
	add r3, sp, #4
	add r2, r5, #0
	add r2, #0x28
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, r6, #0
	str r0, [r2]
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x34
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [r5]
	add r0, r6, #0
	bl Camera_SetFixedTarget
	ldr r0, [r5]
	bl Camera_SetStaticPtr
	ldr r0, [sp, #0x2c]
	mov r1, #0
	str r0, [r5, #4]
	add r0, r5, #0
	add r0, #8
	add r2, r7, #0
	add r3, r4, #0
	bl ov06_0223A350
	add r0, r5, #0
	ldr r2, [sp]
	add r0, #0x18
	mov r1, #0
	add r3, r4, #0
	bl ov06_0223A350
	ldr r0, [sp, #0x28]
	str r0, [r5, #0x48]
	ldr r0, _0223A4DC ; =0x000006D5
	bl PlaySE
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A4DC: .word 0x000006D5

	thumb_func_start ov06_0223A4E0
ov06_0223A4E0: ; 0x0223A4E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x40]
	cmp r1, #5
	bhi _0223A5AC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223A4F6: ; jump table
	.short _0223A502 - _0223A4F6 - 2 ; case 0
	.short _0223A524 - _0223A4F6 - 2 ; case 1
	.short _0223A546 - _0223A4F6 - 2 ; case 2
	.short _0223A56C - _0223A4F6 - 2 ; case 3
	.short _0223A5A0 - _0223A4F6 - 2 ; case 4
	.short _0223A5AC - _0223A4F6 - 2 ; case 5
_0223A502:
	ldr r1, [r4, #0x44]
	add r1, r1, #1
	str r1, [r4, #0x44]
	bl ov06_0223A60C
	add r5, r0, #0
	ldr r1, [r4, #8]
	ldr r2, [r4, #0x18]
	add r0, r4, #0
	bl ov06_0223A628
	cmp r5, #1
	bne _0223A5AC
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	pop {r3, r4, r5, pc}
_0223A524:
	ldr r1, [r4, #0x44]
	sub r1, r1, #1
	str r1, [r4, #0x44]
	bl ov06_0223A60C
	ldr r1, [r4, #8]
	ldr r2, [r4, #0x18]
	add r0, r4, #0
	bl ov06_0223A628
	ldr r0, [r4, #0x44]
	cmp r0, #0
	bne _0223A5AC
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	pop {r3, r4, r5, pc}
_0223A546:
	ldr r1, [r4, #0x44]
	add r1, r1, #1
	str r1, [r4, #0x44]
	bl ov06_0223A60C
	ldr r1, [r4, #8]
	ldr r2, [r4, #0x18]
	add r5, r0, #0
	add r0, r4, #0
	neg r1, r1
	neg r2, r2
	bl ov06_0223A628
	cmp r5, #1
	bne _0223A5AC
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	pop {r3, r4, r5, pc}
_0223A56C:
	ldr r1, [r4, #0x44]
	sub r1, r1, #1
	str r1, [r4, #0x44]
	bl ov06_0223A60C
	ldr r1, [r4, #8]
	ldr r2, [r4, #0x18]
	add r0, r4, #0
	neg r1, r1
	neg r2, r2
	bl ov06_0223A628
	ldr r0, [r4, #0x44]
	cmp r0, #0
	bne _0223A5AC
	ldr r0, [r4, #0x48]
	sub r0, r0, #1
	str r0, [r4, #0x48]
	beq _0223A598
	mov r0, #0
	str r0, [r4, #0x40]
	pop {r3, r4, r5, pc}
_0223A598:
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
	pop {r3, r4, r5, pc}
_0223A5A0:
	ldr r0, [r4, #4]
	bl Camera_SetStaticPtr
	ldr r0, [r4, #0x40]
	add r0, r0, #1
	str r0, [r4, #0x40]
_0223A5AC:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0223A5B0
ov06_0223A5B0: ; 0x0223A5B0
	ldr r0, [r0, #0x40]
	cmp r0, #5
	bne _0223A5BA
	mov r0, #1
	bx lr
_0223A5BA:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start ov06_0223A5C0
ov06_0223A5C0: ; 0x0223A5C0
	add r3, r0, #0
	add r3, #8
	mov r2, #0x10
	mov r1, #0
_0223A5C8:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _0223A5C8
	add r3, r0, #0
	add r3, #0x18
	mov r2, #0x10
	mov r1, #0
_0223A5D8:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _0223A5D8
	add r1, r0, #0
	add r3, r0, #0
	mov r2, #0
	add r1, #0x28
	add r3, #0x28
	strb r2, [r1]
	strb r2, [r3, #1]
	strb r2, [r3, #2]
	strb r2, [r3, #3]
	strb r2, [r3, #4]
	strb r2, [r3, #5]
	strb r2, [r3, #6]
	strb r2, [r3, #7]
	strb r2, [r3, #8]
	strb r2, [r3, #9]
	strb r2, [r3, #0xa]
	strb r2, [r3, #0xb]
	str r2, [r0, #0x40]
	str r2, [r0, #0x44]
	str r2, [r0, #0x48]
	bx lr
	.align 2, 0

	thumb_func_start ov06_0223A60C
ov06_0223A60C: ; 0x0223A60C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, [r5, #0x44]
	add r0, #8
	bl ov06_0223A35C
	add r4, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x44]
	add r0, #0x18
	bl ov06_0223A35C
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223A628
ov06_0223A628: ; 0x0223A628
	ldr r3, [r0, #0x34]
	add r1, r3, r1
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x38]
	add r1, r1, r2
	str r1, [r0, #0x2c]
	bx lr
	.align 2, 0

	thumb_func_start ov06_0223A638
ov06_0223A638: ; 0x0223A638
	ldr r0, [r0, #0x48]
	bx lr

	thumb_func_start ov06_0223A63C
ov06_0223A63C: ; 0x0223A63C
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start ov06_0223A640
ov06_0223A640: ; 0x0223A640
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start ov06_0223A644
ov06_0223A644: ; 0x0223A644
	push {r4, lr}
	mov r1, #0x24
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x24
	add r4, r0, #0
	bl memset
	mov r0, #3
	str r0, [r4, #0x1c]
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A660
ov06_0223A660: ; 0x0223A660
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _0223A672
	bl sub_0200CAB4
	mov r0, #0
	str r0, [r4, #0x20]
_0223A672:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A67C
ov06_0223A67C: ; 0x0223A67C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	add r4, r1, #0
	add r7, r2, #0
	add r6, r3, #0
	cmp r0, #3
	beq _0223A69A
	ldr r0, [r5, #0x20]
	cmp r0, #0
	beq _0223A69A
	bl sub_0200CAB4
	mov r0, #0
	str r0, [r5, #0x20]
_0223A69A:
	add r0, r5, #0
	mov r1, #0
	add r2, r4, #0
	add r3, r7, #0
	bl ov06_0223A31C
	mov r0, #0
	str r0, [r5, #0x10]
	str r0, [r5, #0x1c]
	str r6, [r5, #0x18]
	str r4, [r5, #0x14]
	ldr r0, _0223A6D0 ; =0x0400006C
	ldr r1, [r5]
	bl GXx_SetMasterBrightness_
	mov r2, #1
	ldr r0, _0223A6D4 ; =ov06_0223A74C
	add r1, r5, #0
	lsl r2, r2, #0xa
	bl sub_0200CA98
	str r0, [r5, #0x20]
	ldr r0, _0223A6D8 ; =0x000006D4
	bl PlaySE
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A6D0: .word 0x0400006C
_0223A6D4: .word ov06_0223A74C
_0223A6D8: .word 0x000006D4

	thumb_func_start ov06_0223A6DC
ov06_0223A6DC: ; 0x0223A6DC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x1c]
	cmp r1, #3
	bhi _0223A746
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223A6F2: ; jump table
	.short _0223A6FA - _0223A6F2 - 2 ; case 0
	.short _0223A720 - _0223A6F2 - 2 ; case 1
	.short _0223A736 - _0223A6F2 - 2 ; case 2
	.short _0223A746 - _0223A6F2 - 2 ; case 3
_0223A6FA:
	ldr r1, [r4, #0x10]
	add r1, r1, #1
	str r1, [r4, #0x10]
	bl ov06_0223A328
	cmp r0, #1
	bne _0223A746
	ldr r1, [r4, #0x14]
	ldr r3, [r4, #0x18]
	add r0, r4, #0
	mov r2, #0
	bl ov06_0223A31C
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	pop {r4, pc}
_0223A720:
	ldr r1, [r4, #0x10]
	add r1, r1, #1
	str r1, [r4, #0x10]
	bl ov06_0223A328
	cmp r0, #1
	bne _0223A746
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	pop {r4, pc}
_0223A736:
	ldr r0, [r4, #0x20]
	bl sub_0200CAB4
	mov r0, #0
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
_0223A746:
	pop {r4, pc}

	thumb_func_start ov06_0223A748
ov06_0223A748: ; 0x0223A748
	ldr r0, [r0]
	bx lr

	thumb_func_start ov06_0223A74C
ov06_0223A74C: ; 0x0223A74C
	ldr r3, _0223A754 ; =GXx_SetMasterBrightness_
	ldr r0, _0223A758 ; =0x0400006C
	ldr r1, [r1]
	bx r3
	.align 2, 0
_0223A754: .word GXx_SetMasterBrightness_
_0223A758: .word 0x0400006C

	thumb_func_start ov06_0223A75C
ov06_0223A75C: ; 0x0223A75C
	push {r3, r4, r5, lr}
	mov r1, #5
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #6
	bl AllocFromHeap
	mov r2, #5
	mov r1, #0
	lsl r2, r2, #6
	add r4, r0, #0
	bl memset
	mov r0, #0x4b
	str r5, [r4]
	mov r1, #5
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #0x10
	add r0, r4, r0
	mov r1, #4
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223A790
ov06_0223A790: ; 0x0223A790
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #5
	beq _0223A7A2
	bl GF_AssertFail
_0223A7A2:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223A7AC
ov06_0223A7AC: ; 0x0223A7AC
	push {r3, r4, r5, lr}
	mov r5, #0x4b
	add r4, r0, #0
	mov r0, #0
	lsl r5, r5, #2
	str r0, [r4, r5]
	add r0, r5, #0
	add r0, #8
	str r1, [r4, r0]
	add r0, r5, #0
	add r0, #0xc
	str r2, [r4, r0]
	mov r2, #1
	add r5, #0x10
	ldr r0, _0223A7D8 ; =ov06_0223A8A8
	add r1, r4, #0
	lsl r2, r2, #0xa
	str r3, [r4, r5]
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	nop
_0223A7D8: .word ov06_0223A8A8

	thumb_func_start ov06_0223A7DC
ov06_0223A7DC: ; 0x0223A7DC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #2
	beq _0223A7EE
	bl GF_AssertFail
_0223A7EE:
	mov r0, #0x4b
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r4, #0x40
	add r0, r4, #0
	bl ov06_0223AC70
	pop {r4, pc}

	thumb_func_start ov06_0223A800
ov06_0223A800: ; 0x0223A800
	add r1, r0, #0
	mov r0, #0x13
	mov r2, #0
	lsl r0, r0, #4
	str r2, [r1, r0]
	ldr r3, _0223A818 ; =sub_0200CA44
	mov r2, #4
	sub r0, r0, #4
	str r2, [r1, r0]
	ldr r0, _0223A81C ; =ov06_0223A944
	lsl r2, r2, #8
	bx r3
	.align 2, 0
_0223A818: .word sub_0200CA44
_0223A81C: .word ov06_0223A944

	thumb_func_start ov06_0223A820
ov06_0223A820: ; 0x0223A820
	mov r1, #0x4b
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start ov06_0223A828
ov06_0223A828: ; 0x0223A828
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223A860
	sub r0, r0, #4
	cmp r0, #1
	bls _0223A860
	ldr r0, _0223A864 ; =0x04000454
	mov r1, #0
	str r1, [r0]
	mov r0, #0x11
	add r2, r1, #0
	bl NNS_G3dGeBufferOP_N
	add r4, #0x40
	add r0, r4, #0
	bl ov06_0223A400
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #0
	str r2, [sp]
	bl NNS_G3dGeBufferOP_N
_0223A860:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0223A864: .word 0x04000454

	thumb_func_start ov06_0223A868
ov06_0223A868: ; 0x0223A868
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223A8A6
	sub r0, r0, #4
	cmp r0, #1
	bls _0223A8A6
	add r0, r4, #0
	add r0, #0x40
	bl ov06_0223AAB0
	mov r2, #0x4b
	lsl r2, r2, #2
	ldr r1, [r4, r2]
	cmp r1, #1
	bne _0223A89C
	add r1, r2, #0
	sub r1, #0x16
	ldrh r1, [r4, r1]
	cmp r1, #1
	bne _0223A89C
	mov r1, #2
	str r1, [r4, r2]
_0223A89C:
	cmp r0, #1
	bne _0223A8A6
	add r0, r4, #0
	bl ov06_0223A800
_0223A8A6:
	pop {r4, pc}

	thumb_func_start ov06_0223A8A8
ov06_0223A8A8: ; 0x0223A8A8
	push {r4, lr}
	sub sp, #8
	mov r3, #0x13
	add r4, r1, #0
	lsl r3, r3, #4
	ldr r1, [r4, r3]
	cmp r1, #3
	bhi _0223A940
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223A8C4: ; jump table
	.short _0223A8CC - _0223A8C4 - 2 ; case 0
	.short _0223A8E6 - _0223A8C4 - 2 ; case 1
	.short _0223A904 - _0223A8C4 - 2 ; case 2
	.short _0223A936 - _0223A8C4 - 2 ; case 3
_0223A8CC:
	mov r2, #8
	ldr r1, [r4]
	add r0, r4, #4
	add r3, r2, #0
	bl ov06_022396A0
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add sp, #8
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r4, pc}
_0223A8E6:
	add r0, r4, #4
	bl ov06_022396BC
	add r0, r4, #4
	bl ov06_02239728
	cmp r0, #2
	bne _0223A940
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add sp, #8
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r4, pc}
_0223A904:
	add r0, r3, #0
	add r0, #8
	ldr r0, [r4, r0]
	add r1, r3, #0
	str r0, [sp]
	add r0, r3, #0
	add r0, #0xc
	ldr r0, [r4, r0]
	add r3, r3, #4
	str r0, [sp, #4]
	add r0, r4, #0
	sub r1, #0x14
	ldr r3, [r4, r3]
	add r0, #0x40
	add r1, r4, r1
	mov r2, #4
	bl ov06_0223A9B8
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add sp, #8
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r4, pc}
_0223A936:
	mov r2, #1
	sub r1, r3, #4
	str r2, [r4, r1]
	bl sub_0200CAB4
_0223A940:
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov06_0223A944
ov06_0223A944: ; 0x0223A944
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x13
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	cmp r2, #3
	bhi _0223A9B6
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0223A95E: ; jump table
	.short _0223A966 - _0223A95E - 2 ; case 0
	.short _0223A97E - _0223A95E - 2 ; case 1
	.short _0223A990 - _0223A95E - 2 ; case 2
	.short _0223A9AC - _0223A95E - 2 ; case 3
_0223A966:
	add r0, r4, #0
	sub r1, #0x14
	add r0, #0x40
	add r1, r4, r1
	bl ov06_0223AA78
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r4, pc}
_0223A97E:
	add r0, r4, #4
	bl ov06_02239714
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r4, pc}
_0223A990:
	add r0, r4, #4
	bl ov06_022396BC
	add r0, r4, #4
	bl ov06_02239728
	cmp r0, #5
	bne _0223A9B6
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r4, pc}
_0223A9AC:
	mov r2, #5
	sub r1, r1, #4
	str r2, [r4, r1]
	bl sub_0200CAB4
_0223A9B6:
	pop {r4, pc}

	thumb_func_start ov06_0223A9B8
ov06_0223A9B8: ; 0x0223A9B8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	mov r0, #4
	str r1, [sp, #8]
	add r7, r2, #0
	str r3, [sp, #0xc]
	bl ov06_0223A644
	add r1, r6, #0
	add r1, #0xb0
	str r0, [r1]
	add r0, r6, #0
	add r0, #0x78
	mov r1, #0x62
	mov r2, #0xc
	add r3, r7, #0
	bl ov06_0223A39C
	add r0, r6, #0
	add r5, r6, #0
	str r0, [sp, #0x10]
	add r0, #0x78
	mov r4, #0
	add r5, #0x88
	str r0, [sp, #0x10]
_0223A9EC:
	ldr r0, [sp, #8]
	str r7, [sp]
	add r3, r4, #0
	str r0, [sp, #4]
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	mov r2, #0x62
	add r3, #0xd
	bl ov06_0223A3AC
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #2
	blt _0223A9EC
	add r1, r6, #0
	add r0, r6, #0
	add r1, #0x78
	bl ov06_0223A3F0
	add r4, r6, #0
	mov r5, #0
	add r4, #0x88
_0223AA18:
	add r0, r6, #0
	add r1, r4, #0
	bl ov06_0223A3F8
	add r5, r5, #1
	add r4, #0x14
	cmp r5, #2
	blt _0223AA18
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	add r0, r6, #0
	bl ov06_0223A410
	add r0, r6, #0
	mov r2, #1
	add r0, #0xb4
	mov r1, #0
	lsl r2, r2, #0xc
	mov r3, #0x80
	bl ov06_0223A350
	add r0, r6, #0
	mov r1, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r6, #0
	add r0, #0xb4
	ldr r1, [r0]
	add r0, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov06_0223A418
	mov r2, #2
	add r0, r6, #0
	lsl r2, r2, #0xc
	add r0, #0xd0
	str r2, [r0]
	add r0, r6, #0
	mov r1, #0
	add r0, #0xd6
	strh r1, [r0]
	lsr r0, r2, #1
	add r6, #0xd8
	str r0, [r6]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223AA78
ov06_0223AA78: ; 0x0223AA78
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0x78
	add r6, r1, #0
	bl ov06_0223A3A4
	add r5, r7, #0
	mov r4, #0
	add r5, #0x88
_0223AA8A:
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0223A3C0
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #2
	blt _0223AA8A
	add r0, r7, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl ov06_0223A660
	add r0, r7, #0
	mov r1, #0
	mov r2, #0xdc
	bl memset
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223AAB0
ov06_0223AAB0: ; 0x0223AAB0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, #0xb4
	bl ov06_0223A35C
	add r7, r0, #0
	add r0, r4, #0
	add r2, r4, #0
	add r0, #0xb4
	ldr r5, [r0]
	add r2, #0xd8
	ldr r2, [r2]
	asr r1, r5, #0x1f
	add r0, r5, #0
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r6, #2
	add r2, r0, #0
	mov r3, #0
	lsl r6, r6, #0xa
	add r0, r4, #0
	add r2, r2, r6
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	add r1, r2, #0
	lsl r2, r6, #1
	add r3, r5, #0
	bl ov06_0223A418
	add r5, r4, #0
	mov r6, #0
	add r5, #0x88
_0223AAFC:
	add r1, r4, #0
	add r1, #0xd0
	ldr r1, [r1]
	add r0, r5, #0
	bl ov06_0223A3D4
	add r6, r6, #1
	add r5, #0x14
	cmp r6, #2
	blt _0223AAFC
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	bl ov06_0223A6DC
	add r0, r4, #0
	add r0, #0xd6
	ldrh r0, [r0]
	cmp r0, #5
	bls _0223AB26
	b _0223AC5E
_0223AB26:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223AB32: ; jump table
	.short _0223AB3E - _0223AB32 - 2 ; case 0
	.short _0223AC5E - _0223AB32 - 2 ; case 1
	.short _0223AB5E - _0223AB32 - 2 ; case 2
	.short _0223AB96 - _0223AB32 - 2 ; case 3
	.short _0223ABC4 - _0223AB32 - 2 ; case 4
	.short _0223AC44 - _0223AB32 - 2 ; case 5
_0223AB3E:
	cmp r7, #1
	beq _0223AB50
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r4, #0xc4
	add r0, r0, #1
	str r0, [r4]
	b _0223AC5E
_0223AB50:
	add r0, r4, #0
	add r0, #0xd6
	ldrh r0, [r0]
	add r4, #0xd6
	add r0, r0, #1
	strh r0, [r4]
	b _0223AC5E
_0223AB5E:
	add r0, r4, #0
	add r0, #0xd0
	ldr r1, [r0]
	add r0, r4, #0
	sub r1, #0xcd
	add r0, #0xd0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xd0
	ldr r1, [r0]
	ldr r0, _0223AC64 ; =0x00000666
	cmp r1, r0
	bgt _0223AC5E
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	mov r1, #0x10
	mov r2, #0xc
	mov r3, #0x1c
	bl ov06_0223A67C
	add r0, r4, #0
	add r0, #0xd6
	ldrh r0, [r0]
	add r4, #0xd6
	add r0, r0, #1
	strh r0, [r4]
	b _0223AC5E
_0223AB96:
	add r0, r4, #0
	add r0, #0xd0
	ldr r1, [r0]
	add r0, r4, #0
	sub r1, #0xcd
	add r0, #0xd0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xd0
	ldr r0, [r0]
	cmp r0, #0
	bgt _0223AC5E
	add r0, r4, #0
	add r0, #0xd6
	ldrh r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xd6
	strh r1, [r0]
	mov r0, #8
	add r4, #0xc8
	str r0, [r4]
	b _0223AC5E
_0223ABC4:
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	cmp r0, #0
	bgt _0223AC5E
	add r0, r4, #0
	add r0, #0xd6
	ldrh r0, [r0]
	add r2, r4, #0
	add r2, #0xd8
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xd6
	strh r1, [r0]
	add r0, r4, #0
	ldr r1, _0223AC68 ; =0xFFFD8000
	add r0, #0xd0
	str r1, [r0]
	add r0, r4, #0
	ldr r1, _0223AC6C ; =0xFFFFF000
	add r0, #0xd8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xb4
	ldr r5, [r0]
	ldr r2, [r2]
	asr r1, r5, #0x1f
	add r0, r5, #0
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	add r6, r0, #0
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r4, #0
	add r6, r6, r2
	adc r1, r3
	lsl r2, r1, #0x14
	lsr r1, r6, #0xc
	orr r1, r2
	add r2, r5, #0
	add r3, r5, #0
	bl ov06_0223A418
	add r0, r4, #0
	mov r1, #1
	add r0, #0xb4
	lsl r1, r1, #0xc
	mov r2, #0
	mov r3, #0x20
	bl ov06_0223A350
	mov r0, #0
	add r4, #0xc4
	str r0, [r4]
	b _0223AC5E
_0223AC44:
	cmp r7, #1
	beq _0223AC56
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r4, #0xc4
	add r0, r0, #1
	str r0, [r4]
	b _0223AC5E
_0223AC56:
	cmp r0, #5
	bne _0223AC5E
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223AC5E:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223AC64: .word 0x00000666
_0223AC68: .word 0xFFFD8000
_0223AC6C: .word 0xFFFFF000

	thumb_func_start ov06_0223AC70
ov06_0223AC70: ; 0x0223AC70
	mov r1, #2
	add r0, #0xd6
	strh r1, [r0]
	bx lr

	thumb_func_start ov06_0223AC78
ov06_0223AC78: ; 0x0223AC78
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #5
	lsl r1, r1, #6
	add r5, r0, #0
	bl AllocFromHeap
	mov r2, #5
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #6
	bl memset
	str r6, [r4, #4]
	mov r0, #0
	str r0, [r4]
	mov r0, #0x4f
	lsl r0, r0, #2
	str r5, [r4, r0]
	sub r0, #0x10
	add r0, r4, r0
	add r1, r5, #0
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	mov r2, #0x4f
	lsl r2, r2, #2
	add r0, r4, #0
	ldr r1, [r4, r2]
	sub r2, #0x10
	add r0, #0x34
	add r2, r4, r2
	bl ov06_0223AF10
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0223ACC0
ov06_0223ACC0: ; 0x0223ACC0
	push {r4, lr}
	mov r1, #0x4b
	add r4, r0, #0
	lsl r1, r1, #2
	add r1, r4, r1
	add r0, #0x34
	bl ov06_0223AFD0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start ov06_0223ACD8
ov06_0223ACD8: ; 0x0223ACD8
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r2, r1, #0
	ldr r1, [r4, #4]
	add r0, #8
	bl ov06_0223ADB4
	ldr r0, [r4, #8]
	add r1, sp, #0
	bl sub_02058B5C
	mov r0, #1
	ldr r1, [sp, #8]
	lsl r0, r0, #0x10
	sub r3, r1, r0
	add r0, r4, #0
	ldr r1, [sp]
	ldr r2, [sp, #4]
	add r0, #0x34
	str r3, [sp, #8]
	bl ov06_0223AF7C
	mov r0, #1
	str r0, [r4]
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223AD10
ov06_0223AD10: ; 0x0223AD10
	ldr r0, [r0]
	cmp r0, #0
	beq _0223AD1A
	cmp r0, #5
	bne _0223AD1E
_0223AD1A:
	mov r0, #1
	bx lr
_0223AD1E:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start ov06_0223AD24
ov06_0223AD24: ; 0x0223AD24
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #5
	bhi _0223AD9A
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223AD3A: ; jump table
	.short _0223AD9A - _0223AD3A - 2 ; case 0
	.short _0223AD46 - _0223AD3A - 2 ; case 1
	.short _0223AD5A - _0223AD3A - 2 ; case 2
	.short _0223AD7A - _0223AD3A - 2 ; case 3
	.short _0223AD96 - _0223AD3A - 2 ; case 4
	.short _0223AD9A - _0223AD3A - 2 ; case 5
_0223AD46:
	add r0, r4, #0
	add r0, #0x34
	bl ov06_0223AFF4
	cmp r0, #1
	bne _0223AD9A
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0223AD5A:
	add r0, r4, #0
	add r0, #8
	bl ov06_0223ADD4
	add r0, r4, #0
	add r0, #0x34
	bl ov06_0223B174
	add r0, r4, #0
	add r0, #0x34
	bl ov06_0223AFF4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0223AD7A:
	add r0, r4, #0
	add r0, #0x34
	bl ov06_0223AFF4
	add r0, r4, #0
	add r0, #8
	bl ov06_0223AE28
	cmp r0, #0
	beq _0223AD9A
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0223AD96:
	add r0, r1, #1
	str r0, [r4]
_0223AD9A:
	pop {r4, pc}

	thumb_func_start ov06_0223AD9C
ov06_0223AD9C: ; 0x0223AD9C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0223AD10
	cmp r0, #1
	beq _0223ADB0
	add r4, #0x34
	add r0, r4, #0
	bl ov06_0223B194
_0223ADB0:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223ADB4
ov06_0223ADB4: ; 0x0223ADB4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0x34]
	add r1, r2, #0
	bl GetMapObjectByID
	str r0, [r4]
	cmp r0, #0
	bne _0223ADCA
	bl GF_AssertFail
_0223ADCA:
	mov r0, #0
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223ADD4
ov06_0223ADD4: ; 0x0223ADD4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl ov06_0223AEE8
	add r4, r0, #0
	mov r0, #1
	str r0, [r5, #0x28]
	ldr r0, [r5]
	mov r1, #0
	bl MapObject_SetVisible
	add r0, r4, #0
	mov r1, #0
	bl ov06_0223AEF8
	mov r2, #6
	add r0, r5, #4
	mov r1, #0
	lsl r2, r2, #0xa
	mov r3, #6
	bl ov06_0223A350
	add r0, r5, #0
	mov r1, #2
	add r0, #0x14
	lsl r1, r1, #0x10
	mov r2, #0
	mov r3, #0x2c
	bl ov06_0223A350
	mov r1, #0
	str r1, [sp]
	ldr r0, [r5, #0x14]
	str r1, [sp, #8]
	str r0, [sp, #4]
	ldr r0, [r5]
	add r1, sp, #0
	bl sub_02058BB4
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0223AE28
ov06_0223AE28: ; 0x0223AE28
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl ov06_0223AEE8
	add r6, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #4
	bhi _0223AEE0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223AE46: ; jump table
	.short _0223AEE0 - _0223AE46 - 2 ; case 0
	.short _0223AE50 - _0223AE46 - 2 ; case 1
	.short _0223AE86 - _0223AE46 - 2 ; case 2
	.short _0223AEAC - _0223AE46 - 2 ; case 3
	.short _0223AEDA - _0223AE46 - 2 ; case 4
_0223AE50:
	ldr r0, [r4, #0x24]
	add r1, r0, #1
	str r1, [r4, #0x24]
	add r0, r4, #4
	bl ov06_0223A35C
	add r5, r0, #0
	ldr r1, [r4, #4]
	add r0, r6, #0
	bl ov06_0223AEF8
	cmp r5, #1
	bne _0223AEE0
	mov r1, #6
	mov r2, #1
	add r0, r4, #4
	lsl r1, r1, #0xa
	lsl r2, r2, #0xc
	mov r3, #2
	bl ov06_0223A350
	mov r0, #0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	b _0223AEE0
_0223AE86:
	ldr r0, [r4, #0x24]
	add r1, r0, #1
	str r1, [r4, #0x24]
	add r0, r4, #4
	bl ov06_0223A35C
	add r5, r0, #0
	ldr r1, [r4, #4]
	add r0, r6, #0
	bl ov06_0223AEF8
	cmp r5, #1
	bne _0223AEE0
	mov r0, #0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	b _0223AEE0
_0223AEAC:
	ldr r0, [r4, #0x24]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x14
	str r1, [r4, #0x24]
	bl ov06_0223A35C
	mov r1, #0
	str r1, [sp]
	add r5, r0, #0
	ldr r0, [r4, #0x14]
	str r1, [sp, #8]
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0
	bl sub_02058BB4
	cmp r5, #1
	bne _0223AEE0
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	b _0223AEE0
_0223AEDA:
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_0223AEE0:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223AEE8
ov06_0223AEE8: ; 0x0223AEE8
	push {r3, lr}
	ldr r0, [r0]
	bl ov05_021F1C1C
	bl ov05_021F1C30
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0223AEF8
ov06_0223AEF8: ; 0x0223AEF8
	push {lr}
	sub sp, #0xc
	str r1, [sp]
	mov r1, #1
	lsl r1, r1, #0xc
	str r1, [sp, #4]
	str r1, [sp, #8]
	add r1, sp, #0
	bl sub_0201F7F0
	add sp, #0xc
	pop {pc}

	thumb_func_start ov06_0223AF10
ov06_0223AF10: ; 0x0223AF10
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r1, #0
	add r7, r0, #0
	str r2, [sp, #8]
	add r0, #0x78
	mov r1, #0x62
	mov r2, #7
	add r3, r6, #0
	bl ov06_0223A39C
	add r0, r7, #0
	add r5, r7, #0
	str r0, [sp, #0xc]
	add r0, #0x78
	mov r4, #0
	add r5, #0x88
	str r0, [sp, #0xc]
_0223AF34:
	ldr r0, [sp, #8]
	str r6, [sp]
	add r3, r4, #0
	str r0, [sp, #4]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	mov r2, #0x62
	add r3, #8
	bl ov06_0223A3AC
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0223AF34
	add r1, r7, #0
	add r0, r7, #0
	add r1, #0x78
	bl ov06_0223A3F0
	add r4, r7, #0
	mov r5, #0
	add r4, #0x88
_0223AF60:
	add r0, r7, #0
	add r1, r4, #0
	bl ov06_0223A3F8
	add r5, r5, #1
	add r4, #0x14
	cmp r5, #4
	blt _0223AF60
	add r0, r7, #0
	mov r1, #0
	bl ov06_0223A408
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223AF7C
ov06_0223AF7C: ; 0x0223AF7C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl ov06_0223A410
	mov r1, #1
	lsl r1, r1, #0xc
	add r0, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov06_0223A418
	mov r4, #0
	add r5, r6, #0
	add r5, #0x88
	add r7, r4, #0
_0223AF9A:
	add r0, r5, #0
	add r1, r7, #0
	bl ov06_0223A3E8
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0223AF9A
	add r0, r6, #0
	mov r2, #0
	add r0, #0xec
	str r2, [r0]
	add r0, r6, #0
	add r0, #0xd8
	str r2, [r0]
	add r0, r6, #0
	mov r1, #0x52
	add r0, #0xf0
	str r1, [r0]
	add r0, r6, #0
	add r0, #0xf4
	str r2, [r0]
	add r0, r6, #0
	mov r1, #1
	bl ov06_0223A408
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223AFD0
ov06_0223AFD0: ; 0x0223AFD0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0x78
	add r6, r1, #0
	bl ov06_0223A3A4
	mov r4, #0
	add r5, #0x88
_0223AFE0:
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0223A3C0
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0223AFE0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223AFF4
ov06_0223AFF4: ; 0x0223AFF4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r0, #0xd8
	ldr r0, [r0]
	cmp r0, #3
	bhi _0223B084
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223B00C: ; jump table
	.short _0223B014 - _0223B00C - 2 ; case 0
	.short _0223B084 - _0223B00C - 2 ; case 1
	.short _0223B03C - _0223B00C - 2 ; case 2
	.short _0223B084 - _0223B00C - 2 ; case 3
_0223B014:
	add r5, r6, #0
	mov r4, #0
	add r5, #0x88
_0223B01A:
	add r0, r5, #0
	bl ov06_0223A3DC
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0223B01A
	cmp r0, #1
	bne _0223B084
	add r0, r6, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r6, #0
	add r0, #0xd8
	str r1, [r0]
	b _0223B084
_0223B03C:
	add r0, r6, #0
	add r0, #0xec
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r6, #0
	add r0, #0xec
	str r1, [r0]
	add r1, r6, #0
	add r1, #0xec
	add r0, r6, #0
	ldr r1, [r1]
	add r0, #0xdc
	bl ov06_0223A35C
	add r4, r0, #0
	add r0, r6, #0
	add r0, #0xdc
	ldr r1, [r0]
	add r0, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov06_0223A418
	cmp r4, #1
	bne _0223B084
	add r0, r6, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r6, #0
	add r0, #0xd8
	str r1, [r0]
	add r0, r6, #0
	mov r1, #0
	bl ov06_0223A408
_0223B084:
	add r0, r6, #0
	bl ov06_0223B090
	add r6, #0xd8
	ldr r0, [r6]
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0223B090
ov06_0223B090: ; 0x0223B090
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xf4
	ldr r0, [r0]
	cmp r0, #4
	bhi _0223B162
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223B0A8: ; jump table
	.short _0223B0B2 - _0223B0A8 - 2 ; case 0
	.short _0223B0E0 - _0223B0A8 - 2 ; case 1
	.short _0223B110 - _0223B0A8 - 2 ; case 2
	.short _0223B13E - _0223B0A8 - 2 ; case 3
	.short _0223B162 - _0223B0A8 - 2 ; case 4
_0223B0B2:
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r0, #0
	bge _0223B162
	ldr r0, _0223B164 ; =0x000006D2
	bl PlaySE
	add r0, r4, #0
	mov r1, #0x48
	add r0, #0xf0
	str r1, [r0]
	mov r0, #1
	add r4, #0xf4
	str r0, [r4]
	pop {r4, pc}
_0223B0E0:
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r0, #0
	bge _0223B162
	ldr r0, _0223B168 ; =0x000006D3
	bl PlaySE
	add r0, r4, #0
	mov r1, #0x4b
	lsl r1, r1, #2
	add r0, #0xf0
	str r1, [r0]
	mov r0, #2
	add r4, #0xf4
	str r0, [r4]
	pop {r4, pc}
_0223B110:
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r0, #0
	bge _0223B162
	ldr r0, _0223B16C ; =0x000006D6
	bl PlaySE
	add r0, r4, #0
	mov r1, #0x84
	add r0, #0xf0
	str r1, [r0]
	mov r0, #3
	add r4, #0xf4
	str r0, [r4]
	pop {r4, pc}
_0223B13E:
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r0, #0
	bge _0223B162
	ldr r0, _0223B170 ; =0x000006D7
	bl PlaySE
	mov r0, #4
	add r4, #0xf4
	str r0, [r4]
_0223B162:
	pop {r4, pc}
	.align 2, 0
_0223B164: .word 0x000006D2
_0223B168: .word 0x000006D3
_0223B16C: .word 0x000006D6
_0223B170: .word 0x000006D7

	thumb_func_start ov06_0223B174
ov06_0223B174: ; 0x0223B174
	push {r3, lr}
	add r1, r0, #0
	mov r3, #2
	add r1, #0xd8
	str r3, [r1]
	add r1, r0, #0
	mov r2, #0
	add r1, #0xec
	str r2, [r1]
	lsl r1, r3, #0xb
	add r0, #0xdc
	mov r3, #0x10
	bl ov06_0223A350
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0223B194
ov06_0223B194: ; 0x0223B194
	ldr r3, _0223B198 ; =ov06_0223A400
	bx r3
	.align 2, 0
_0223B198: .word ov06_0223A400

	thumb_func_start ov06_0223B19C
ov06_0223B19C: ; 0x0223B19C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x1e
	lsl r1, r1, #4
	add r4, r0, #0
	bl AllocFromHeap
	mov r2, #0x1e
	add r6, r0, #0
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	add r0, r6, #0
	mov r1, #0x62
	add r2, r5, #0
	add r3, r4, #0
	bl ov06_0223A39C
	add r5, r6, #0
	mov r4, #0
	add r5, #0x10
_0223B1C8:
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0223B348
	add r4, r4, #1
	add r5, #0x90
	cmp r4, #3
	blt _0223B1C8
	mov r0, #7
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r6, r0]
	add r0, r6, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0223B1E4
ov06_0223B1E4: ; 0x0223B1E4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r6, #0
	mov r4, #0
	add r5, #0x10
_0223B1EE:
	add r0, r5, #0
	bl ov06_0223B36C
	add r4, r4, #1
	add r5, #0x90
	cmp r4, #3
	blt _0223B1EE
	add r0, r6, #0
	bl ov06_0223A3A4
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223B20C
ov06_0223B20C: ; 0x0223B20C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #0
	beq _0223B224
	bl GF_AssertFail
_0223B224:
	mov r0, #0x71
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r1, r0, #0
	add r1, #8
	str r4, [r5, r1]
	add r1, r0, #0
	add r1, #0xc
	str r6, [r5, r1]
	add r1, r0, #0
	add r1, #0x10
	str r7, [r5, r1]
	add r2, sp, #8
	add r1, r0, #0
	ldrh r3, [r2, #0x14]
	add r1, #0x14
	strh r3, [r5, r1]
	add r1, r0, #0
	ldrh r3, [r2, #0x18]
	add r1, #0x16
	strh r3, [r5, r1]
	add r1, r0, #0
	ldrh r2, [r2, #0x1c]
	add r1, #0x18
	strh r2, [r5, r1]
	add r1, r0, #4
	ldr r2, [sp, #0x18]
	sub r0, r0, #4
	str r2, [r5, r1]
	mov r1, #1
	str r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223B268
ov06_0223B268: ; 0x0223B268
	push {r3, r4, r5, lr}
	sub sp, #0x18
	mov r2, #0x71
	add r5, r0, #0
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	sub r1, r1, #1
	str r1, [r5, r2]
	ldr r1, [r5, r2]
	cmp r1, #0
	bge _0223B2CA
	add r1, r2, #4
	ldr r1, [r5, r1]
	str r1, [r5, r2]
	bl ov06_0223B438
	add r4, r0, #0
	bne _0223B290
	bl GF_AssertFail
_0223B290:
	mov r1, #0x73
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	mov r2, #1
	str r0, [sp]
	add r0, r1, #4
	ldr r0, [r5, r0]
	lsl r2, r2, #0x10
	str r0, [sp, #4]
	add r0, r1, #0
	add r0, #8
	ldr r0, [r5, r0]
	mov r3, #0x60
	str r0, [sp, #8]
	add r0, r1, #0
	add r0, #0xc
	ldrh r0, [r5, r0]
	str r0, [sp, #0xc]
	add r0, r1, #0
	add r0, #0xe
	ldrh r0, [r5, r0]
	add r1, #0x10
	str r0, [sp, #0x10]
	ldrh r0, [r5, r1]
	mov r1, #0
	str r0, [sp, #0x14]
	add r0, r4, #0
	bl ov06_0223B378
_0223B2CA:
	mov r4, #0
	add r5, #0x10
_0223B2CE:
	add r0, r5, #0
	bl ov06_0223B3EC
	add r4, r4, #1
	add r5, #0x90
	cmp r4, #3
	blt _0223B2CE
	add sp, #0x18
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223B2E0
ov06_0223B2E0: ; 0x0223B2E0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x10
_0223B2E8:
	add r0, r5, #0
	bl ov06_0223B42C
	add r4, r4, #1
	add r5, #0x90
	cmp r4, #3
	blt _0223B2E8
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223B2F8
ov06_0223B2F8: ; 0x0223B2F8
	ldr r3, _0223B300 ; =ov06_0223B19C
	mov r1, #6
	bx r3
	nop
_0223B300: .word ov06_0223B19C

	thumb_func_start ov06_0223B304
ov06_0223B304: ; 0x0223B304
	ldr r3, _0223B308 ; =ov06_0223B1E4
	bx r3
	.align 2, 0
_0223B308: .word ov06_0223B1E4

	thumb_func_start ov06_0223B30C
ov06_0223B30C: ; 0x0223B30C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r4, #0x40
	str r4, [sp]
	mov r5, #0
	str r5, [sp, #4]
	str r5, [sp, #8]
	str r5, [sp, #0xc]
	lsl r5, r1, #0x10
	lsl r1, r4, #9
	add r1, r5, r1
	lsl r5, r2, #0x10
	mov r2, #0xa
	lsl r2, r2, #0x10
	add r2, r5, r2
	lsl r5, r3, #0x10
	lsl r3, r4, #0xa
	add r3, r5, r3
	bl ov06_0223B20C
	add sp, #0x10
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223B338
ov06_0223B338: ; 0x0223B338
	ldr r3, _0223B33C ; =ov06_0223B268
	bx r3
	.align 2, 0
_0223B33C: .word ov06_0223B268

	thumb_func_start ov06_0223B340
ov06_0223B340: ; 0x0223B340
	ldr r3, _0223B344 ; =ov06_0223B2E0
	bx r3
	.align 2, 0
_0223B344: .word ov06_0223B2E0

	thumb_func_start ov06_0223B348
ov06_0223B348: ; 0x0223B348
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x90
	bl memset
	add r0, r4, #4
	add r1, r5, #0
	bl ov06_0223A3F0
	add r0, r4, #4
	mov r1, #0
	bl ov06_0223A408
	mov r0, #0
	str r0, [r4]
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223B36C
ov06_0223B36C: ; 0x0223B36C
	ldr r3, _0223B374 ; =memset
	mov r1, #0
	mov r2, #0x90
	bx r3
	.align 2, 0
_0223B374: .word memset

	thumb_func_start ov06_0223B378
ov06_0223B378: ; 0x0223B378
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #0
	beq _0223B38C
	bl GF_AssertFail
_0223B38C:
	add r0, r5, #0
	add r0, #0x7c
	add r1, r4, #0
	add r2, r6, #0
	add r3, r7, #0
	bl ov06_0223A350
	add r0, r5, #4
	mov r1, #1
	bl ov06_0223A408
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r0, r5, #4
	bl ov06_0223A410
	mov r2, #1
	add r0, r5, #4
	add r1, r4, #0
	lsl r2, r2, #0xc
	add r3, r4, #0
	bl ov06_0223A418
	add r1, sp, #8
	ldrh r1, [r1, #0x1c]
	add r0, r5, #4
	mov r2, #0
	bl ov06_0223A420
	add r1, sp, #8
	ldrh r1, [r1, #0x20]
	add r0, r5, #4
	mov r2, #1
	bl ov06_0223A420
	add r1, sp, #8
	ldrh r1, [r1, #0x24]
	add r0, r5, #4
	mov r2, #2
	bl ov06_0223A420
	mov r0, #1
	str r0, [r5]
	mov r0, #0
	add r5, #0x8c
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223B3EC
ov06_0223B3EC: ; 0x0223B3EC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0223B42A
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x8c
	str r1, [r0]
	add r1, r4, #0
	add r1, #0x8c
	add r0, r4, #0
	ldr r1, [r1]
	add r0, #0x7c
	bl ov06_0223A35C
	ldr r1, [r4, #0x7c]
	mov r2, #1
	add r5, r0, #0
	add r0, r4, #4
	lsl r2, r2, #0xc
	add r3, r1, #0
	bl ov06_0223A418
	cmp r5, #1
	bne _0223B42A
	mov r0, #0
	str r0, [r4]
_0223B42A:
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223B42C
ov06_0223B42C: ; 0x0223B42C
	ldr r3, _0223B434 ; =ov06_0223A400
	add r0, r0, #4
	bx r3
	nop
_0223B434: .word ov06_0223A400

	thumb_func_start ov06_0223B438
ov06_0223B438: ; 0x0223B438
	mov r2, #0
	add r3, r0, #0
_0223B43C:
	ldr r1, [r3, #0x10]
	cmp r1, #0
	bne _0223B44C
	mov r1, #0x90
	add r0, #0x10
	mul r1, r2
	add r0, r0, r1
	bx lr
_0223B44C:
	add r2, r2, #1
	add r3, #0x90
	cmp r2, #3
	blt _0223B43C
	mov r0, #0
	bx lr

	thumb_func_start ov06_0223B458
ov06_0223B458: ; 0x0223B458
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	mov r1, #0xd4
	add r7, r0, #0
	bl AllocFromHeap
	add r6, r0, #0
	mov r1, #0
	mov r2, #0xd4
	bl memset
	add r0, r6, #0
	add r0, #0xc4
	add r1, r7, #0
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	add r0, r6, #0
	add r0, #0x78
	mov r1, #0x62
	add r2, r4, #0
	add r3, r7, #0
	bl ov06_0223A39C
	add r0, r6, #0
	str r0, [sp, #8]
	add r0, #0xc4
	str r0, [sp, #8]
	add r0, r6, #0
	add r5, r6, #0
	str r0, [sp, #0xc]
	add r0, #0x78
	mov r4, #0
	add r5, #0x88
	str r0, [sp, #0xc]
_0223B4A0:
	ldr r0, [sp, #8]
	str r7, [sp]
	str r0, [sp, #4]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	mov r2, #0x62
	add r3, r4, #1
	bl ov06_0223A3AC
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #3
	blt _0223B4A0
	add r1, r6, #0
	add r0, r6, #0
	add r1, #0x78
	bl ov06_0223A3F0
	add r4, r6, #0
	mov r5, #0
	add r4, #0x88
_0223B4CA:
	add r0, r6, #0
	add r1, r4, #0
	bl ov06_0223A3F8
	add r5, r5, #1
	add r4, #0x14
	cmp r5, #3
	blt _0223B4CA
	add r0, r6, #0
	mov r1, #0
	bl ov06_0223A408
	add r0, r6, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223B4E8
ov06_0223B4E8: ; 0x0223B4E8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0x78
	bl ov06_0223A3A4
	add r5, r7, #0
	add r6, r7, #0
	mov r4, #0
	add r5, #0x88
	add r6, #0xc4
_0223B4FC:
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0223A3C0
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #3
	blt _0223B4FC
	add r0, r7, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223B514
ov06_0223B514: ; 0x0223B514
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0223A410
	ldr r1, _0223B550 ; =0xFFFFFFF8
	add r0, r4, #0
	add r1, sp
	ldrh r1, [r1, #0x10]
	mov r2, #0
	bl ov06_0223A420
	ldr r1, _0223B550 ; =0xFFFFFFF8
	add r0, r4, #0
	add r1, sp
	ldrh r1, [r1, #0x18]
	mov r2, #2
	bl ov06_0223A420
	ldr r1, _0223B550 ; =0xFFFFFFF8
	add r0, r4, #0
	add r1, sp
	ldrh r1, [r1, #0x14]
	mov r2, #1
	bl ov06_0223A420
	add r0, r4, #0
	mov r1, #1
	bl ov06_0223A408
	pop {r4, pc}
	.align 2, 0
_0223B550: .word 0xFFFFFFF8

	thumb_func_start ov06_0223B554
ov06_0223B554: ; 0x0223B554
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x88
_0223B55C:
	add r0, r5, #0
	bl ov06_0223A3C8
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #3
	blt _0223B55C
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223B56C
ov06_0223B56C: ; 0x0223B56C
	ldr r3, _0223B570 ; =ov06_0223A400
	bx r3
	.align 2, 0
_0223B570: .word ov06_0223A400

	thumb_func_start ov06_0223B574
ov06_0223B574: ; 0x0223B574
	ldr r3, _0223B57C ; =ov06_0223B458
	mov r1, #0
	bx r3
	nop
_0223B57C: .word ov06_0223B458

	thumb_func_start ov06_0223B580
ov06_0223B580: ; 0x0223B580
	ldr r3, _0223B584 ; =ov06_0223B4E8
	bx r3
	.align 2, 0
_0223B584: .word ov06_0223B4E8

	thumb_func_start ov06_0223B588
ov06_0223B588: ; 0x0223B588
	ldr r3, _0223B58C ; =ov06_0223B554
	bx r3
	.align 2, 0
_0223B58C: .word ov06_0223B554

	thumb_func_start ov06_0223B590
ov06_0223B590: ; 0x0223B590
	ldr r3, _0223B594 ; =ov06_0223B56C
	bx r3
	.align 2, 0
_0223B594: .word ov06_0223B56C

	thumb_func_start ov06_0223B598
ov06_0223B598: ; 0x0223B598
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r4, _0223B5BC ; =0x0000F49F
	str r4, [sp]
	ldr r4, _0223B5C0 ; =0x000080B5
	str r4, [sp, #4]
	.ifdef DIAMOND
	sub r4, r4, #7
	.else
	ldr r4, _0223B5C4 ; =0x000085A8
	.endif
	str r4, [sp, #8]
	.ifdef DIAMOND
	ldr r4, _0223B5C4 ; =0x00029BA8
	add r1, r1, r4
	.else
	mov r4, #0x4b
	lsl r4, r4, #0xc
	sub r1, r1, r4
	.endif
	ldr r4, _0223B5C8 ; =0x00037294
	sub r2, r2, r4
	ldr r4, _0223B5CC ; =0x000B6876
	sub r3, r3, r4
	bl ov06_0223B514
	add sp, #0xc
	pop {r3, r4, pc}
	.ifdef DIAMOND
	.align 2, 0
	.else
	nop
	.endif
.ifdef DIAMOND
_0223B5BC: .word 0x0000F49F
_0223B5C0: .word 0x000080B5
_0223B5C4: .word 0x00029BA8
_0223B5C8: .word 0x00037294
_0223B5CC: .word 0x000B6876
.else
_0223B5BC: .word 0x0000E667
_0223B5C0: .word 0x0000760B
_0223B5C4: .word 0x000085A8
_0223B5C8: .word 0x000156B1
_0223B5CC: .word 0x00099919
.endif

	thumb_func_start ov06_0223B5D0
ov06_0223B5D0: ; 0x0223B5D0
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r4, _0223B5F4 ; =0x0000E5B1
	str r4, [sp]
	ldr r4, _0223B5F8 ; =0x0000C163
	str r4, [sp, #4]
	ldr r4, _0223B5FC ; =0x00007FF8
	str r4, [sp, #8]
	ldr r4, _0223B600 ; =0x00116A4F
	add r1, r1, r4
	ldr r4, _0223B604 ; =0x0004F16B
	add r2, r2, r4
	ldr r4, _0223B608 ; =0x00092118
	sub r3, r3, r4
	bl ov06_0223B514
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0223B5F4: .word 0x0000E5B1
_0223B5F8: .word 0x0000C163
_0223B5FC: .word 0x00007FF8
_0223B600: .word 0x00116A4F
_0223B604: .word 0x0004F16B
_0223B608: .word 0x00092118

	thumb_func_start ov06_0223B60C
ov06_0223B60C: ; 0x0223B60C
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r4, _0223B634 ; =0x0000E71D
	str r4, [sp]
	ldr r4, _0223B638 ; =0x00005335
	str r4, [sp, #4]
	ldr r4, _0223B63C ; =0x00007992
	str r4, [sp, #8]
	mov r4, #0xc6
	lsl r4, r4, #0xc
	sub r1, r1, r4
	ldr r4, _0223B640 ; =0x00056FFF
	add r2, r2, r4
	ldr r4, _0223B644 ; =0x00210008
	sub r3, r3, r4
	bl ov06_0223B514
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0223B634: .word 0x0000E71D
_0223B638: .word 0x00005335
_0223B63C: .word 0x00007992
_0223B640: .word 0x00056FFF
_0223B644: .word 0x00210008

	thumb_func_start ov06_0223B648
ov06_0223B648: ; 0x0223B648
	ldr r3, _0223B650 ; =ov06_0223B19C
	mov r1, #6
	bx r3
	nop
_0223B650: .word ov06_0223B19C

	thumb_func_start ov06_0223B654
ov06_0223B654: ; 0x0223B654
	ldr r3, _0223B658 ; =ov06_0223B1E4
	bx r3
	.align 2, 0
_0223B658: .word ov06_0223B1E4

	thumb_func_start ov06_0223B65C
ov06_0223B65C: ; 0x0223B65C
	ldr r3, _0223B660 ; =ov06_0223B268
	bx r3
	.align 2, 0
_0223B660: .word ov06_0223B268

	thumb_func_start ov06_0223B664
ov06_0223B664: ; 0x0223B664
	ldr r3, _0223B668 ; =ov06_0223B2E0
	bx r3
	.align 2, 0
_0223B668: .word ov06_0223B2E0

	thumb_func_start ov06_0223B66C
ov06_0223B66C: ; 0x0223B66C
	push {r4, lr}
	sub sp, #0x10
	mov r4, #0x40
	str r4, [sp]
	ldr r4, _0223B69C ; =0x0000F49F
	str r4, [sp, #4]
	ldr r4, _0223B6A0 ; =0x000080B5
	str r4, [sp, #8]
	.ifdef DIAMOND
	sub r4, r4, #7
	.else
	ldr r4, _0223B6AC_PEARL ; =0x000085A8
	.endif
	str r4, [sp, #0xc]
	.ifdef DIAMOND
	mov r4, #0x11
	lsl r4, r4, #0xc
	add r1, r1, r4
	mov r4, #0x6f
	lsl r4, r4, #0xc
	sub r2, r2, r4
	mov r4, #0xcb
	lsl r4, r4, #0xc
	.else
	mov r4, #0x3e
	lsl r4, r4, #0xc
	sub r1, r1, r4
	mov r4, #0x4f
	lsl r4, r4, #0xc
	sub r2, r2, r4
	mov r4, #0xd
	lsl r4, r4, #0x10
	.endif
	sub r3, r3, r4
	bl ov06_0223B20C
	add sp, #0x10
	pop {r4, pc}
	nop
	.ifdef DIAMOND
_0223B69C: .word 0x0000F49F
_0223B6A0: .word 0x000080B5
	.else
_0223B69C: .word 0x0000E667
_0223B6A0: .word 0x0000760B
_0223B6AC_PEARL: .word 0x000085A8
	.endif

	thumb_func_start ov06_0223B6A4
ov06_0223B6A4: ; 0x0223B6A4
	push {r4, lr}
	sub sp, #0x10
	mov r4, #0x40
	str r4, [sp]
	ldr r4, _0223B6D0 ; =0x0000E5B1
	str r4, [sp, #4]
	ldr r4, _0223B6D4 ; =0x0000C163
	str r4, [sp, #8]
	ldr r4, _0223B6D8 ; =0x00007FF8
	str r4, [sp, #0xc]
	ldr r4, _0223B6DC ; =0x00252000
	add r1, r1, r4
	mov r4, #0x43
	lsl r4, r4, #0xc
	add r2, r2, r4
	mov r4, #0xe
	lsl r4, r4, #0xe
	sub r3, r3, r4
	bl ov06_0223B20C
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0223B6D0: .word 0x0000E5B1
_0223B6D4: .word 0x0000C163
_0223B6D8: .word 0x00007FF8
_0223B6DC: .word 0x00252000

	thumb_func_start ov06_0223B6E0
ov06_0223B6E0: ; 0x0223B6E0
	push {r4, lr}
	sub sp, #0x10
	mov r4, #0x40
	str r4, [sp]
	ldr r4, _0223B710 ; =0x0000E71D
	str r4, [sp, #4]
	ldr r4, _0223B714 ; =0x00005335
	str r4, [sp, #8]
	ldr r4, _0223B718 ; =0x00007992
	str r4, [sp, #0xc]
	mov r4, #0x53
	lsl r4, r4, #0xe
	sub r1, r1, r4
	mov r4, #0xd
	lsl r4, r4, #0xc
	sub r2, r2, r4
	mov r4, #0x71
	lsl r4, r4, #0xe
	sub r3, r3, r4
	bl ov06_0223B20C
	add sp, #0x10
	pop {r4, pc}
	nop
_0223B710: .word 0x0000E71D
_0223B714: .word 0x00005335
_0223B718: .word 0x00007992

	thumb_func_start ov06_0223B71C
ov06_0223B71C: ; 0x0223B71C
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x18
	bl AllocFromHeap
	add r3, r0, #0
	mov r2, #0x18
	mov r1, #0
_0223B72C:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _0223B72C
	str r4, [r0]
	mov r1, #0
	str r1, [r0, #0x14]
	pop {r4, pc}

	thumb_func_start ov06_0223B73C
ov06_0223B73C: ; 0x0223B73C
	ldr r3, _0223B740 ; =FreeToHeap
	bx r3
	.align 2, 0
_0223B740: .word FreeToHeap

	thumb_func_start ov06_0223B744
ov06_0223B744: ; 0x0223B744
	ldr r1, _0223B760 ; =0x0224F248
	mov r2, #1
	str r1, [r0, #4]
	mov r1, #3
	str r1, [r0, #8]
	mov r1, #0
	str r1, [r0, #0xc]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	ldr r0, [r0]
	ldr r3, _0223B764 ; =ov05_021DB52C
	ldr r0, [r0, #0x48]
	bx r3
	nop
_0223B760: .word ov06_0224F248
_0223B764: .word ov05_021DB52C

	thumb_func_start ov06_0223B768
ov06_0223B768: ; 0x0223B768
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #4
	bhi _0223B80C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223B77E: ; jump table
	.short _0223B80C - _0223B77E - 2 ; case 0
	.short _0223B788 - _0223B77E - 2 ; case 1
	.short _0223B80C - _0223B77E - 2 ; case 2
	.short _0223B7C0 - _0223B77E - 2 ; case 3
	.short _0223B80C - _0223B77E - 2 ; case 4
_0223B788:
	ldr r0, [r4, #0xc]
	add r5, r0, #1
	str r5, [r4, #0xc]
	ldr r3, [r4, #0x10]
	ldr r2, [r4, #4]
	mov r0, #0x30
	add r1, r3, #0
	mul r1, r0
	ldr r1, [r2, r1]
	cmp r1, r5
	bhi _0223B80C
	ldr r1, [r4, #8]
	add r2, r3, #1
	cmp r2, r1
	blo _0223B7AE
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	pop {r3, r4, r5, pc}
_0223B7AE:
	str r2, [r4, #0x10]
	ldr r1, [r4, #4]
	mul r0, r2
	add r0, r1, r0
	ldr r1, [r4]
	ldr r1, [r1, #0x40]
	bl ov05_021DB53C
	pop {r3, r4, r5, pc}
_0223B7C0:
	ldr r0, [r4, #0xc]
	sub r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _0223B7F6
	ldr r3, [r4, #4]
	mov r1, #0x30
	add r2, r0, #0
	mul r2, r1
	add r2, r3, r2
	sub r2, #0x30
	ldr r3, [r2]
	ldr r2, [r4, #0xc]
	cmp r3, r2
	bls _0223B80C
	sub r3, r0, #1
	str r3, [r4, #0x10]
	add r0, r3, #0
	mul r0, r1
	ldr r1, [r4]
	ldr r2, [r4, #4]
	ldr r1, [r1, #0x40]
	add r0, r2, r0
	bl ov05_021DB53C
	pop {r3, r4, r5, pc}
_0223B7F6:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _0223B80C
	ldr r0, [r4]
	mov r1, #1
	ldr r0, [r0, #0x48]
	bl ov05_021DB52C
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
_0223B80C:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0223B810
ov06_0223B810: ; 0x0223B810
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start ov06_0223B814
ov06_0223B814: ; 0x0223B814
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	cmp r0, #2
	beq _0223B822
	bl GF_AssertFail
_0223B822:
	mov r0, #3
	str r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start ov06_0223B828
ov06_0223B828: ; 0x0223B828
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	mov r1, #0xec
	add r7, r0, #0
	bl AllocFromHeap
	add r6, r0, #0
	mov r1, #0
	mov r2, #0xec
	bl memset
	add r0, r6, #0
	add r0, #0xd8
	str r4, [r0]
	add r0, r6, #0
	add r0, #0xdc
	add r1, r7, #0
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	add r0, r6, #0
	add r0, #0x78
	mov r1, #0x62
	mov r2, #0xf
	add r3, r7, #0
	bl ov06_0223A39C
	add r0, r6, #0
	str r0, [sp, #8]
	add r0, #0xdc
	str r0, [sp, #8]
	add r0, r6, #0
	add r5, r6, #0
	str r0, [sp, #0xc]
	add r0, #0x78
	mov r4, #0
	add r5, #0x88
	str r0, [sp, #0xc]
_0223B876:
	ldr r0, [sp, #8]
	str r7, [sp]
	add r3, r4, #0
	str r0, [sp, #4]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	mov r2, #0x62
	add r3, #0x10
	bl ov06_0223A3AC
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0223B876
	add r1, r6, #0
	add r0, r6, #0
	add r1, #0x78
	bl ov06_0223A3F0
	add r4, r6, #0
	mov r5, #0
	add r4, #0x88
_0223B8A2:
	add r0, r6, #0
	add r1, r4, #0
	bl ov06_0223A3F8
	add r5, r5, #1
	add r4, #0x14
	cmp r5, #4
	blt _0223B8A2
	add r0, r6, #0
	mov r1, #0
	bl ov06_0223A408
	add r0, r6, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223B8C0
ov06_0223B8C0: ; 0x0223B8C0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0x78
	bl ov06_0223A3A4
	add r5, r7, #0
	add r6, r7, #0
	mov r4, #0
	add r5, #0x88
	add r6, #0xdc
_0223B8D4:
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0223A3C0
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0223B8D4
	add r0, r7, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223B8EC
ov06_0223B8EC: ; 0x0223B8EC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, #0xd8
	ldr r0, [r0]
	ldr r0, [r0, #0x34]
	bl GetMapObjectByID
	add r1, sp, #0
	bl sub_02058B5C
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl ov06_0223A410
	add r0, r4, #0
	mov r1, #1
	bl ov06_0223A408
	ldr r0, _0223B920 ; =0x000006D8
	bl PlaySE
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0223B920: .word 0x000006D8

	thumb_func_start ov06_0223B924
ov06_0223B924: ; 0x0223B924
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x88
_0223B92C:
	add r0, r5, #0
	bl ov06_0223A3DC
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0223B92C
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223B93C
ov06_0223B93C: ; 0x0223B93C
	ldr r3, _0223B940 ; =ov06_0223A400
	bx r3
	.align 2, 0
_0223B940: .word ov06_0223A400

	thumb_func_start ov06_0223B944
ov06_0223B944: ; 0x0223B944
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl GF_RTC_GetTimeOfDay
	sub r1, r0, #1
	cmp r1, #1
	bhi _0223B960
	ldr r0, [r5, #0x6c]
	str r0, [r4]
	ldr r0, [r5, #0x70]
	str r0, [r6]
	pop {r4, r5, r6, pc}
_0223B960:
	sub r0, r0, #3
	cmp r0, #1
	bhi _0223B96E
	ldr r0, [r5, #0x74]
	str r0, [r4]
	ldr r0, [r5, #0x78]
	str r0, [r6]
_0223B96E:
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0223B970
ov06_0223B970: ; 0x0223B970
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl Save_Roamers_Get
	str r0, [sp]
	bl sub_0202AA14
	cmp r0, #0
	beq _0223B9A6
	ldr r0, [sp]
	mov r1, #2
	bl Roamers_GetRand
	bl ov06_022458FC
	ldr r1, [r5, #0x1c]
	ldr r1, [r1]
	cmp r1, r0
	bne _0223B9A6
	ldr r0, [r4, #0x64]
	str r0, [r6]
	ldr r0, [r4, #0x68]
	str r0, [r7]
_0223B9A6:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223B9A8
ov06_0223B9A8: ; 0x0223B9A8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x1c]
	add r4, r1, #0
	ldr r0, [r0]
	add r6, r2, #0
	add r7, r3, #0
	bl MapHeader_MapIsTrophyGarden
	cmp r0, #0
	beq _0223B9FC
	add r1, sp, #0
	ldr r0, [r5, #0xc]
	add r1, #2
	add r2, sp, #0
	bl sub_0202AB8C
	cmp r4, #0
	beq _0223B9FC
	mov r0, #0x6a
	mov r1, #8
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	add r1, sp, #0
	ldrh r2, [r1, #2]
	ldr r1, _0223BA00 ; =0x0000FFFF
	cmp r2, r1
	beq _0223B9E8
	lsl r1, r2, #2
	ldr r1, [r0, r1]
	str r1, [r6]
_0223B9E8:
	add r1, sp, #0
	ldrh r2, [r1]
	ldr r1, _0223BA00 ; =0x0000FFFF
	cmp r2, r1
	beq _0223B9F8
	lsl r1, r2, #2
	ldr r1, [r0, r1]
	str r1, [r7]
_0223B9F8:
	bl FreeToHeap
_0223B9FC:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223BA00: .word 0x0000FFFF

	thumb_func_start ov06_0223BA04
ov06_0223BA04: ; 0x0223BA04
	push {r4, r5, r6, r7, lr}
	sub sp, #0xb4
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	str r0, [sp, #0x14]
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r1, r6, #0
	bl sub_0204A6E0
	str r0, [sp, #0x1c]
	add r2, sp, #0x24
	ldr r1, [sp, #0x1c]
	add r0, r5, #0
	add r2, #1
	bl ov06_0223C51C
	add r1, sp, #0x24
	strb r0, [r1]
	ldrb r0, [r1]
	cmp r0, #0
	bne _0223BA42
	add sp, #0xb4
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BA42:
	ldr r0, [r5, #0xc]
	bl SaveArray_Party_Get
	add r7, r0, #0
	add r0, r5, #0
	bl sub_02034CE0
	add r4, r0, #0
	add r0, r7, #0
	mov r1, #0
	bl Party_GetMonByIndex
	str r0, [sp, #0x20]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	add r2, r4, #0
	add r3, sp, #0x30
	bl ov06_0223D2DC
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	bl sub_0202AB54
	cmp r0, #0
	bne _0223BA8C
	add r0, r7, #0
	bl GetFirstAliveMonInParty_CrashIfNone
	mov r1, #1
	str r1, [sp, #0x34]
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x24
	strb r0, [r1, #0x18]
_0223BA8C:
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetWeatherType
	add r3, r0, #0
	ldr r0, [sp, #0x20]
	add r1, sp, #0x24
	str r0, [sp]
	ldrb r1, [r1]
	mov r0, #0
	add r2, sp, #0x30
	bl ov06_0223CF14
	add r1, sp, #0x24
	strb r0, [r1]
	add r0, r5, #0
	add r1, sp, #0x24
	bl ov06_0223C764
	ldr r0, [sp, #0x20]
	add r1, sp, #0x24
	bl ov06_0223C738
	add r1, sp, #0x24
	ldrb r1, [r1]
	ldr r2, [sp, #0x1c]
	add r0, r5, #0
	bl ov06_0223C470
	cmp r0, #0
	beq _0223BAD2
	mov r0, #1
	str r0, [sp, #0x10]
	b _0223BAD6
_0223BAD2:
	mov r0, #0
	str r0, [sp, #0x10]
_0223BAD6:
	add r1, sp, #0x44
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	str r0, [r1, #0xc]
	str r1, [sp]
	add r0, sp, #0x48
	str r0, [sp, #4]
	add r0, sp, #0x4c
	add r3, r5, #0
	str r0, [sp, #8]
	add r3, #0x90
	ldr r1, [sp, #0x14]
	ldr r3, [r3]
	add r0, r6, #0
	add r2, r5, #0
	bl sub_0205DFE8
	cmp r0, #0
	bne _0223BB06
	mov r0, #0
	str r0, [sp, #0x50]
	b _0223BB0C
_0223BB06:
	mov r0, #1
	str r0, [sp, #0x10]
	str r0, [sp, #0x50]
_0223BB0C:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _0223BB18
	add sp, #0xb4
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BB18:
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl Save_VarsFlags_CheckHaveFollower
	cmp r0, #0
	beq _0223BB2C
	mov r0, #1
	str r0, [sp, #0xc]
	b _0223BB30
_0223BB2C:
	mov r0, #0
	str r0, [sp, #0xc]
_0223BB30:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0223BB98
	ldr r0, [sp, #0x50]
	cmp r0, #0
	bne _0223BB98
	add r0, r5, #0
	add r1, sp, #0x28
	bl ov06_0223D0E8
	cmp r0, #0
	beq _0223BB98
	ldr r0, [sp, #0x28]
	mov r1, #6
	bl sub_0202AAB8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, sp, #0x30
	bl ov06_0223D030
	cmp r0, #0
	bne _0223BB92
	mov r0, #0xb
	add r1, r0, #0
	add r1, #0xf5
	bl BattleSetup_New
	str r0, [sp, #0x2c]
	add r1, r5, #0
	bl BattleSetup_InitFromFieldSystem
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	bl ov06_0223D044
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	bl sub_0205DD40
	ldr r1, [sp, #0x2c]
	add r0, r5, #0
	bl sub_020469B8
	add sp, #0xb4
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223BB92:
	add sp, #0xb4
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BB98:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0223BBB6
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl Save_VarsFlags_CheckSafariSysFlag
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	add r2, sp, #0x2c
	bl ov06_0223CFD0
	b _0223BBC0
_0223BBB6:
	mov r0, #0xb
	mov r1, #0x4a
	bl BattleSetup_New
	str r0, [sp, #0x2c]
_0223BBC0:
	ldr r0, [sp, #0x2c]
	add r1, r5, #0
	bl BattleSetup_InitFromFieldSystem
	add r0, sp, #0x24
	ldrb r0, [r0, #1]
	cmp r0, #0
	bne _0223BC84
	mov r7, #4
	mov r0, #0
	add r1, r4, #0
	add r2, sp, #0x54
	add r3, r7, #0
_0223BBDA:
	ldr r6, [r1, #8]
	add r0, r0, #1
	str r6, [r2]
	ldrsb r6, [r1, r7]
	strh r6, [r2, #4]
	ldrsb r6, [r1, r3]
	add r1, #8
	strh r6, [r2, #6]
	add r2, #8
	cmp r0, #0xc
	blt _0223BBDA
	add r0, r5, #0
	bl FieldSystem_GetSaveData
	bl Save_Pokedex_Get
	bl Pokedex_GetNatDexFlag
	add r6, r0, #0
	add r0, r4, #0
	add r1, sp, #0x64
	add r2, sp, #0x6c
	bl ov06_0223B944
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0x54
	add r3, sp, #0x5c
	bl ov06_0223B970
	add r0, r5, #0
	add r1, r6, #0
	add r2, sp, #0x84
	add r3, sp, #0x8c
	bl ov06_0223B9A8
	add r0, r4, #0
	add r1, r6, #0
	add r2, sp, #0x94
	add r3, sp, #0x9c
	bl ov06_0224CDB8
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0223BC5A
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	add r2, r6, #0
	add r3, sp, #0x54
	bl ov06_0223CFFC
	add r0, sp, #0x54
	str r0, [sp]
	add r0, sp, #0x30
	str r0, [sp, #4]
	add r0, sp, #0x44
	str r0, [sp, #8]
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x2c]
	add r0, r5, #0
	add r3, r4, #0
	bl ov06_0223C31C
	b _0223BCCC
_0223BC5A:
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F368
	ldr r1, [sp, #0x2c]
	mov r2, #0xb
	str r0, [r1, #0x20]
	ldr r0, [sp, #0x2c]
	ldr r1, [r5, #0xc]
	bl EnemyTrainerSet_Init
	add r0, sp, #0x30
	str r0, [sp]
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x2c]
	add r0, r5, #0
	add r3, sp, #0x54
	bl ov06_0223C3F4
	b _0223BCCC
_0223BC84:
	cmp r0, #1
	bne _0223BCBC
	mov r0, #0
	add r1, sp, #0x54
	mov r3, #0xd0
	mov r6, #0xd1
_0223BC90:
	add r2, r4, #0
	add r2, #0xd4
	ldr r2, [r2]
	add r0, r0, #1
	str r2, [r1]
	ldrsb r2, [r4, r3]
	strh r2, [r1, #4]
	ldrsb r2, [r4, r6]
	add r4, #8
	strh r2, [r1, #6]
	add r1, #8
	cmp r0, #5
	blt _0223BC90
	add r0, sp, #0x30
	str r0, [sp]
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x2c]
	add r0, r5, #0
	add r3, sp, #0x54
	bl ov06_0223C438
	b _0223BCCC
_0223BCBC:
	bl GF_AssertFail
	ldr r0, [sp, #0x2c]
	bl BattleSetup_Delete
	add sp, #0xb4
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BCCC:
	cmp r0, #0
	beq _0223BCDA
	ldr r1, [sp, #0x2c]
	add r0, r5, #0
	bl sub_020469B8
	b _0223BCDE
_0223BCDA:
	mov r0, #0
	str r0, [sp, #0x10]
_0223BCDE:
	mov r0, #4
	bl GF_heap_c_dummy_return_true
	cmp r0, #0
	bne _0223BCEC
	bl GF_AssertFail
_0223BCEC:
	mov r0, #0xb
	bl GF_heap_c_dummy_return_true
	cmp r0, #0
	bne _0223BCFA
	bl GF_AssertFail
_0223BCFA:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _0223BD06
	ldr r0, [sp, #0x2c]
	bl BattleSetup_Delete
_0223BD06:
	mov r0, #0
	add r5, #0x74
	strh r0, [r5]
	ldr r0, [sp, #0x10]
	add sp, #0xb4
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223BD14
ov06_0223BD14: ; 0x0223BD14
	push {r4, r5, r6, r7, lr}
	sub sp, #0x94
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r2, [sp, #0x10]
	bl ov06_0223CE0C
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	bne _0223BD2E
	add sp, #0x94
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BD2E:
	ldr r0, [sp, #8]
	ldr r0, [r0, #0xc]
	bl SaveArray_Party_Get
	mov r1, #0
	bl Party_GetMonByIndex
	str r0, [sp, #0x14]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x14]
	mov r2, #0
	add r3, sp, #0x20
	bl ov06_0223D2DC
	ldr r0, [sp, #8]
	ldr r0, [r0, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetWeatherType
	add r3, r0, #0
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	str r0, [sp]
	mov r0, #1
	add r2, sp, #0x20
	bl ov06_0223CF14
	add r6, r0, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _0223BD80
	bl GF_AssertFail
_0223BD80:
	cmp r5, r6
	blt _0223BD8A
	add sp, #0x94
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BD8A:
	ldr r0, [sp, #8]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl Save_VarsFlags_CheckSafariSysFlag
	add r1, r0, #0
	ldr r0, [sp, #8]
	ldr r2, [sp, #0x10]
	bl ov06_0223CFD0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #8]
	ldr r0, [r0]
	bl BattleSetup_InitFromFieldSystem
	ldr r0, [sp, #0x10]
	ldr r0, [r0]
	bl sub_020480AC
	ldr r0, [sp, #8]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0]
	bl MapHeader_MapIsMtCoronetFeebasRoom
	cmp r0, #0
	beq _0223BDFC
	ldr r0, [sp, #8]
	bl ov06_0224CC60
	cmp r0, #0
	beq _0223BDFC
	add r0, sp, #0x18
	add r0, #1
	add r1, sp, #0x18
	bl ov06_0224CD94
	add r0, sp, #0x1c
	bl ov06_0224CDA0
	add r0, sp, #0x18
	ldrb r3, [r0, #1]
	ldrb r4, [r0]
	ldr r2, [sp, #0x1c]
	mov r1, #0
	add r0, sp, #0x34
_0223BDE6:
	lsl r5, r1, #3
	add r1, r1, #1
	lsl r1, r1, #0x18
	add r6, r0, r5
	str r2, [r0, r5]
	strh r3, [r6, #4]
	lsr r1, r1, #0x18
	strh r4, [r6, #6]
	cmp r1, #5
	blo _0223BDE6
	b _0223BE4A
_0223BDFC:
	ldr r0, [sp, #8]
	bl sub_02034CE0
	ldr r1, [sp, #0xc]
	cmp r1, #0
	beq _0223BE12
	cmp r1, #1
	beq _0223BE1A
	cmp r1, #2
	beq _0223BE22
	b _0223BE28
_0223BE12:
	mov r1, #0x4a
	lsl r1, r1, #2
	add r4, r0, r1
	b _0223BE28
_0223BE1A:
	mov r1, #0x55
	lsl r1, r1, #2
	add r4, r0, r1
	b _0223BE28
_0223BE22:
	mov r1, #6
	lsl r1, r1, #6
	add r4, r0, r1
_0223BE28:
	mov r6, #0
	add r1, sp, #0x34
	mov r7, #1
_0223BE2E:
	lsl r5, r6, #3
	add r3, r4, r5
	ldr r0, [r3, #4]
	add r2, r1, r5
	str r0, [r1, r5]
	ldrsb r0, [r4, r5]
	strh r0, [r2, #4]
	ldrsb r0, [r3, r7]
	strh r0, [r2, #6]
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #5
	blo _0223BE2E
_0223BE4A:
	add r0, sp, #0x20
	str r0, [sp]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x14]
	ldr r2, [r2]
	add r3, sp, #0x34
	bl ov06_0223C454
	cmp r0, #0
	bne _0223BE6A
	add sp, #0x94
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BE6A:
	mov r0, #1
	add sp, #0x94
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223BE70
ov06_0223BE70: ; 0x0223BE70
	push {r4, r5, r6, r7, lr}
	sub sp, #0xac
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	str r1, [sp, #0xc]
	bl GetPlayerXCoord
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl sub_0204A6E0
	add r1, r0, #0
	add r0, r5, #0
	add r2, sp, #0x1c
	bl ov06_0223C51C
	cmp r0, #0
	bne _0223BEA4
	add sp, #0xac
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223BEA4:
	ldr r0, [r5, #0xc]
	bl SaveArray_Party_Get
	add r6, r0, #0
	add r0, r5, #0
	bl sub_02034CE0
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0
	bl Party_GetMonByIndex
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	add r2, r4, #0
	add r3, sp, #0x28
	bl ov06_0223D2DC
	mov r0, #1
	mov r1, #0
	str r0, [sp, #0x30]
	add r0, sp, #0x3c
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [sp, #0x2c]
	str r1, [r0, #0xc]
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl Save_VarsFlags_CheckHaveFollower
	cmp r0, #0
	beq _0223BEF0
	mov r0, #1
	str r0, [sp, #0x10]
	b _0223BEF4
_0223BEF0:
	mov r0, #0
	str r0, [sp, #0x10]
_0223BEF4:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _0223BF3C
	add r0, r5, #0
	add r1, sp, #0x20
	bl ov06_0223D0E8
	cmp r0, #0
	beq _0223BF3C
	mov r0, #0xb
	add r1, r0, #0
	add r1, #0xf5
	bl BattleSetup_New
	str r0, [sp, #0x24]
	add r1, r5, #0
	bl BattleSetup_InitFromFieldSystem
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x24]
	bl ov06_0223D044
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	bl sub_0205DD40
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x24]
	add r0, r5, #0
	bl sub_02046A20
	add sp, #0xac
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223BF3C:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _0223BF5A
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl Save_VarsFlags_CheckSafariSysFlag
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	add r2, sp, #0x24
	bl ov06_0223CFD0
	b _0223BF64
_0223BF5A:
	mov r0, #0xb
	mov r1, #0x4a
	bl BattleSetup_New
	str r0, [sp, #0x24]
_0223BF64:
	ldr r0, [sp, #0x24]
	add r1, r5, #0
	bl BattleSetup_InitFromFieldSystem
	add r0, sp, #0x1c
	ldrb r0, [r0]
	cmp r0, #0
	bne _0223C028
	mov r7, #4
	mov r0, #0
	add r1, r4, #0
	add r2, sp, #0x4c
	add r3, r7, #0
_0223BF7E:
	ldr r6, [r1, #8]
	add r0, r0, #1
	str r6, [r2]
	ldrsb r6, [r1, r7]
	strh r6, [r2, #4]
	ldrsb r6, [r1, r3]
	add r1, #8
	strh r6, [r2, #6]
	add r2, #8
	cmp r0, #0xc
	blt _0223BF7E
	add r0, r5, #0
	bl FieldSystem_GetSaveData
	bl Save_Pokedex_Get
	bl Pokedex_GetNatDexFlag
	add r6, r0, #0
	add r0, r4, #0
	add r1, sp, #0x5c
	add r2, sp, #0x64
	bl ov06_0223B944
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0x4c
	add r3, sp, #0x54
	bl ov06_0223B970
	add r0, r5, #0
	add r1, r6, #0
	add r2, sp, #0x7c
	add r3, sp, #0x84
	bl ov06_0223B9A8
	add r0, r4, #0
	add r1, r6, #0
	add r2, sp, #0x8c
	add r3, sp, #0x94
	bl ov06_0224CDB8
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _0223BFFE
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	add r2, r6, #0
	add r3, sp, #0x4c
	bl ov06_0223CFFC
	add r0, sp, #0x4c
	str r0, [sp]
	add r0, sp, #0x28
	str r0, [sp, #4]
	add r0, sp, #0x3c
	str r0, [sp, #8]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x24]
	add r0, r5, #0
	add r3, r4, #0
	bl ov06_0223C31C
	b _0223C06A
_0223BFFE:
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F368
	ldr r1, [sp, #0x24]
	mov r2, #0xb
	str r0, [r1, #0x20]
	ldr r0, [sp, #0x24]
	ldr r1, [r5, #0xc]
	bl EnemyTrainerSet_Init
	add r0, sp, #0x28
	str r0, [sp]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x24]
	add r0, r5, #0
	add r3, sp, #0x4c
	bl ov06_0223C3F4
	b _0223C06A
_0223C028:
	cmp r0, #1
	bne _0223C060
	mov r0, #0
	add r1, sp, #0x4c
	mov r3, #0xd0
	mov r6, #0xd1
_0223C034:
	add r2, r4, #0
	add r2, #0xd4
	ldr r2, [r2]
	add r0, r0, #1
	str r2, [r1]
	ldrsb r2, [r4, r3]
	strh r2, [r1, #4]
	ldrsb r2, [r4, r6]
	add r4, #8
	strh r2, [r1, #6]
	add r1, #8
	cmp r0, #5
	blt _0223C034
	add r0, sp, #0x28
	str r0, [sp]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x24]
	add r0, r5, #0
	add r3, sp, #0x4c
	bl ov06_0223C438
	b _0223C06A
_0223C060:
	bl GF_AssertFail
	add sp, #0xac
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223C06A:
	cmp r0, #0
	beq _0223C07A
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x24]
	add r0, r5, #0
	bl sub_02046A20
	b _0223C07E
_0223C07A:
	bl GF_AssertFail
_0223C07E:
	mov r0, #0
	add r5, #0x74
	strh r0, [r5]
	mov r0, #1
	add sp, #0xac
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223C08C
ov06_0223C08C: ; 0x0223C08C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xac
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0
	str r0, [r4]
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl sub_0204A6E0
	add r7, r0, #0
	add r2, sp, #0x20
	add r0, r5, #0
	add r1, r7, #0
	add r2, #1
	bl ov06_0223C51C
	add r1, sp, #0x20
	strb r0, [r1]
	ldrb r0, [r1]
	cmp r0, #0
	bne _0223C0CE
	add sp, #0xac
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223C0CE:
	ldr r0, [r5, #0xc]
	bl SaveArray_Party_Get
	add r6, r0, #0
	add r0, r5, #0
	bl sub_02034CE0
	str r0, [sp, #0x14]
	add r0, r6, #0
	mov r1, #0
	bl Party_GetMonByIndex
	str r0, [sp, #0x1c]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x14]
	add r0, r5, #0
	add r3, sp, #0x28
	bl ov06_0223D2DC
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	bl sub_0202AB54
	cmp r0, #0
	bne _0223C118
	add r0, r6, #0
	bl GetFirstAliveMonInParty_CrashIfNone
	mov r1, #1
	str r1, [sp, #0x2c]
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	add r1, sp, #0x20
	strb r0, [r1, #0x14]
_0223C118:
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetWeatherType
	add r3, r0, #0
	ldr r0, [sp, #0x1c]
	add r1, sp, #0x20
	str r0, [sp]
	ldrb r1, [r1]
	mov r0, #0
	add r2, sp, #0x28
	bl ov06_0223CF14
	add r1, sp, #0x20
	strb r0, [r1]
	add r0, r5, #0
	add r1, sp, #0x20
	bl ov06_0223C764
	ldr r0, [sp, #0x1c]
	add r1, sp, #0x20
	bl ov06_0223C738
	add r1, sp, #0x20
	ldrb r1, [r1]
	add r0, r5, #0
	add r2, r7, #0
	bl ov06_0223C470
	cmp r0, #0
	beq _0223C15E
	mov r0, #1
	str r0, [sp, #0x10]
	b _0223C162
_0223C15E:
	mov r0, #0
	str r0, [sp, #0x10]
_0223C162:
	add r1, sp, #0x3c
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	str r0, [r1, #0xc]
	str r0, [sp, #0x48]
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl Save_VarsFlags_CheckHaveFollower
	cmp r0, #0
	beq _0223C184
	mov r0, #1
	str r0, [sp, #0xc]
	b _0223C188
_0223C184:
	mov r0, #0
	str r0, [sp, #0xc]
_0223C188:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0223C1E0
	add r0, r5, #0
	add r1, sp, #0x24
	bl ov06_0223D0E8
	cmp r0, #0
	beq _0223C1E0
	ldr r0, [sp, #0x24]
	mov r1, #6
	bl sub_0202AAB8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, sp, #0x28
	bl ov06_0223D030
	cmp r0, #0
	bne _0223C1DA
	mov r0, #0xb
	add r1, r0, #0
	add r1, #0xf5
	bl BattleSetup_New
	str r0, [r4]
	add r1, r5, #0
	bl BattleSetup_InitFromFieldSystem
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x24]
	ldr r2, [r4]
	bl ov06_0223D044
	add r5, #0x90
	ldr r0, [r5]
	bl sub_0205DD40
	add sp, #0xac
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223C1DA:
	add sp, #0xac
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223C1E0:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0223C1FE
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl Save_VarsFlags_CheckSafariSysFlag
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	add r2, r4, #0
	bl ov06_0223CFD0
	b _0223C208
_0223C1FE:
	mov r0, #0xb
	mov r1, #0x4a
	bl BattleSetup_New
	str r0, [r4]
_0223C208:
	ldr r0, [r4]
	add r1, r5, #0
	bl BattleSetup_InitFromFieldSystem
	add r0, sp, #0x20
	ldrb r0, [r0, #1]
	cmp r0, #0
	bne _0223C2CC
	mov r7, #4
	ldr r1, [sp, #0x14]
	mov r0, #0
	add r2, sp, #0x4c
	add r3, r7, #0
_0223C222:
	ldr r6, [r1, #8]
	add r0, r0, #1
	str r6, [r2]
	ldrsb r6, [r1, r7]
	strh r6, [r2, #4]
	ldrsb r6, [r1, r3]
	add r1, #8
	strh r6, [r2, #6]
	add r2, #8
	cmp r0, #0xc
	blt _0223C222
	add r0, r5, #0
	bl FieldSystem_GetSaveData
	bl Save_Pokedex_Get
	bl Pokedex_GetNatDexFlag
	add r6, r0, #0
	ldr r0, [sp, #0x14]
	add r1, sp, #0x5c
	add r2, sp, #0x64
	bl ov06_0223B944
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	add r2, sp, #0x4c
	add r3, sp, #0x54
	bl ov06_0223B970
	add r0, r5, #0
	add r1, r6, #0
	add r2, sp, #0x7c
	add r3, sp, #0x84
	bl ov06_0223B9A8
	ldr r0, [sp, #0x14]
	add r1, r6, #0
	add r2, sp, #0x8c
	add r3, sp, #0x94
	bl ov06_0224CDB8
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0223C2A2
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	add r2, r6, #0
	add r3, sp, #0x4c
	bl ov06_0223CFFC
	add r0, sp, #0x4c
	str r0, [sp]
	add r0, sp, #0x28
	str r0, [sp, #4]
	add r0, sp, #0x3c
	str r0, [sp, #8]
	ldr r1, [sp, #0x1c]
	ldr r2, [r4]
	ldr r3, [sp, #0x14]
	add r0, r5, #0
	bl ov06_0223C31C
	b _0223C2DC
_0223C2A2:
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F368
	ldr r1, [r4]
	mov r2, #0xb
	str r0, [r1, #0x20]
	ldr r0, [r4]
	ldr r1, [r5, #0xc]
	bl EnemyTrainerSet_Init
	add r0, sp, #0x28
	str r0, [sp]
	ldr r1, [sp, #0x1c]
	ldr r2, [r4]
	add r0, r5, #0
	add r3, sp, #0x4c
	bl ov06_0223C3F4
	b _0223C2DC
_0223C2CC:
	bl GF_AssertFail
	ldr r0, [r4]
	bl BattleSetup_Delete
	add sp, #0xac
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223C2DC:
	cmp r0, #0
	bne _0223C2E4
	mov r0, #0
	str r0, [sp, #0x10]
_0223C2E4:
	mov r0, #4
	bl GF_heap_c_dummy_return_true
	cmp r0, #0
	bne _0223C2F2
	bl GF_AssertFail
_0223C2F2:
	mov r0, #0xb
	bl GF_heap_c_dummy_return_true
	cmp r0, #0
	bne _0223C300
	bl GF_AssertFail
_0223C300:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	bne _0223C30E
	ldr r0, [r4]
	bl BattleSetup_Delete
	b _0223C314
_0223C30E:
	mov r0, #0
	add r5, #0x74
	strh r0, [r5]
_0223C314:
	ldr r0, [sp, #0x10]
	add sp, #0xac
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223C31C
ov06_0223C31C: ; 0x0223C31C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r6, [sp, #0x38]
	add r5, r0, #0
	ldr r0, [r6, #0xc]
	add r7, r2, #0
	str r1, [sp, #0x10]
	ldr r4, [sp, #0x30]
	cmp r0, #0
	beq _0223C3CA
	ldr r0, [r6]
	cmp r0, #1
	bne _0223C350
	ldr r0, [r3, #0x7c]
	str r0, [r4, #0x20]
	add r0, r3, #0
	add r0, #0x80
	ldr r0, [r0]
	str r0, [r4, #0x28]
	add r0, r3, #0
	add r0, #0x84
	ldr r0, [r0]
	add r3, #0x88
	str r0, [r4, #0x50]
	ldr r0, [r3]
	str r0, [r4, #0x58]
_0223C350:
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	add r1, sp, #0x18
	add r2, sp, #0x14
	bl sub_0205E098
	ldr r0, [r6, #4]
	cmp r0, #1
	bne _0223C38C
	add r0, r5, #0
	bl FieldSystem_GetSaveData
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerID
	str r0, [sp]
	ldr r0, [sp, #0x34]
	mov r2, #1
	str r0, [sp, #4]
	ldr r0, [sp, #0x10]
	str r0, [sp, #8]
	str r7, [sp, #0xc]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x14]
	ldr r3, [r6, #8]
	bl ov06_0223CBD4
	b _0223C3A6
_0223C38C:
	mov r0, #1
	str r0, [sp]
	str r7, [sp, #4]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x10]
	str r0, [sp, #8]
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x34]
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r3, r4, #0
	bl ov06_0223CC24
_0223C3A6:
	add r4, r0, #0
	cmp r4, #0
	beq _0223C3EC
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r2, r0, #0
	add r0, r5, #0
	add r5, #0x90
	ldr r3, [r5]
	add r1, r6, #0
	bl sub_0205DD80
	b _0223C3EC
_0223C3CA:
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r1, #0
	ldr r2, [sp, #0x34]
	mov r1, #0xff
	add r3, r4, #0
	str r7, [sp, #8]
	bl ov06_0223CA6C
	add r4, r0, #0
	beq _0223C3EC
	add r5, #0x90
	ldr r0, [r5]
	bl sub_0205DD40
_0223C3EC:
	add r0, r4, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223C3F4
ov06_0223C3F4: ; 0x0223C3F4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	mov r0, #0
	add r5, r1, #0
	add r4, r2, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r1, #0xff
	add r6, r3, #0
	str r4, [sp, #8]
	bl ov06_0223CA6C
	cmp r0, #0
	bne _0223C41C
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_0223C41C:
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r2, [sp, #0x20]
	add r0, r5, #0
	mov r1, #0xff
	add r3, r6, #0
	str r4, [sp, #8]
	bl ov06_0223CA6C
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223C438
ov06_0223C438: ; 0x0223C438
	push {lr}
	sub sp, #0xc
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	str r2, [sp, #8]
	add r0, r1, #0
	ldr r2, [sp, #0x10]
	mov r1, #0xff
	bl ov06_0223CA6C
	add sp, #0xc
	pop {pc}
	.align 2, 0

	thumb_func_start ov06_0223C454
ov06_0223C454: ; 0x0223C454
	push {lr}
	sub sp, #0xc
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r2, [sp, #8]
	add r0, r1, #0
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	bl ov06_0223CA6C
	add sp, #0xc
	pop {pc}

	thumb_func_start ov06_0223C470
ov06_0223C470: ; 0x0223C470
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	lsl r1, r7, #8
	add r5, r0, #0
	add r6, r2, #0
	bl ov06_0223C55C
	cmp r0, #0
	bne _0223C4B0
	add r0, r5, #0
	add r0, #0x74
	ldrh r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0x74
	strh r1, [r0]
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x64
	blo _0223C4A8
	bl GF_AssertFail
_0223C4A8:
	cmp r4, #5
	blo _0223C4B0
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223C4B0:
	add r0, r6, #0
	mov r4, #0x28
	bl sub_02054798
	cmp r0, #0
	beq _0223C4C4
	add r4, #0x1e
	lsl r0, r4, #0x18
	lsr r4, r0, #0x18
	b _0223C4D4
_0223C4C4:
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetState
	cmp r0, #1
	bne _0223C4D4
	add r4, #0x1e
	lsl r0, r4, #0x18
	lsr r4, r0, #0x18
_0223C4D4:
	add r0, r5, #0
	bl sub_0204B33C
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02249230
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x64
	bls _0223C4EC
	mov r4, #0x64
_0223C4EC:
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #0x64
	blo _0223C504
	bl GF_AssertFail
_0223C504:
	cmp r6, r4
	bge _0223C518
	add r0, r5, #0
	add r1, r7, #0
	bl ov06_0223C584
	cmp r0, #0
	beq _0223C518
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223C518:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223C51C
ov06_0223C51C: ; 0x0223C51C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	add r4, r2, #0
	bl sub_02054AFC
	cmp r0, #0
	beq _0223C558
	add r0, r6, #0
	bl sub_0205481C
	cmp r0, #0
	beq _0223C548
	mov r0, #1
	strb r0, [r4]
	add r0, r5, #0
	bl ov06_0223CE00
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, r5, r6, pc}
_0223C548:
	mov r0, #0
	strb r0, [r4]
	add r0, r5, #0
	bl ov06_0223CDF4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, r5, r6, pc}
_0223C558:
	mov r0, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0223C55C
ov06_0223C55C: ; 0x0223C55C
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #0xa
	bl _u32_div_f
	lsr r1, r0, #8
	cmp r1, #8
	bls _0223C570
	mov r1, #8
_0223C570:
	mov r0, #8
	add r4, #0x74
	sub r1, r0, r1
	ldrh r0, [r4]
	cmp r0, r1
	blo _0223C580
	mov r0, #1
	pop {r4, pc}
_0223C580:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov06_0223C584
ov06_0223C584: ; 0x0223C584
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _0223C5A0
	bl GF_AssertFail
_0223C5A0:
	cmp r5, r4
	blo _0223C5A8
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223C5A8:
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223C5AC
ov06_0223C5AC: ; 0x0223C5AC
	push {r4, lr}
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x64
	blo _0223C5C6
	bl GF_AssertFail
_0223C5C6:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x14
	bhs _0223C5D2
	mov r0, #0
	pop {r4, pc}
_0223C5D2:
	blo _0223C5DC
	cmp r0, #0x28
	bhs _0223C5DC
	mov r0, #1
	pop {r4, pc}
_0223C5DC:
	cmp r0, #0x28
	blo _0223C5E8
	cmp r0, #0x32
	bhs _0223C5E8
	mov r0, #2
	pop {r4, pc}
_0223C5E8:
	cmp r0, #0x32
	blo _0223C5F4
	cmp r0, #0x3c
	bhs _0223C5F4
	mov r0, #3
	pop {r4, pc}
_0223C5F4:
	cmp r0, #0x3c
	blo _0223C600
	cmp r0, #0x46
	bhs _0223C600
	mov r0, #4
	pop {r4, pc}
_0223C600:
	cmp r0, #0x46
	blo _0223C60C
	cmp r0, #0x50
	bhs _0223C60C
	mov r0, #5
	pop {r4, pc}
_0223C60C:
	cmp r0, #0x50
	blo _0223C618
	cmp r0, #0x55
	bhs _0223C618
	mov r0, #6
	pop {r4, pc}
_0223C618:
	cmp r0, #0x55
	blo _0223C624
	cmp r0, #0x5a
	bhs _0223C624
	mov r0, #7
	pop {r4, pc}
_0223C624:
	cmp r0, #0x5a
	blo _0223C630
	cmp r0, #0x5e
	bhs _0223C630
	mov r0, #8
	pop {r4, pc}
_0223C630:
	cmp r0, #0x5e
	blo _0223C63C
	cmp r0, #0x62
	bhs _0223C63C
	mov r0, #9
	pop {r4, pc}
_0223C63C:
	cmp r0, #0x62
	bne _0223C644
	mov r0, #0xa
	pop {r4, pc}
_0223C644:
	mov r0, #0xb
	pop {r4, pc}

	thumb_func_start ov06_0223C648
ov06_0223C648: ; 0x0223C648
	push {r4, lr}
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x64
	blo _0223C662
	bl GF_AssertFail
_0223C662:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x3c
	bhs _0223C66E
	mov r0, #0
	pop {r4, pc}
_0223C66E:
	blo _0223C678
	cmp r0, #0x5a
	bhs _0223C678
	mov r0, #1
	pop {r4, pc}
_0223C678:
	cmp r0, #0x5a
	blo _0223C684
	cmp r0, #0x5f
	bhs _0223C684
	mov r0, #2
	pop {r4, pc}
_0223C684:
	cmp r0, #0x5f
	blo _0223C690
	cmp r0, #0x63
	bhs _0223C690
	mov r0, #3
	pop {r4, pc}
_0223C690:
	mov r0, #4
	pop {r4, pc}

	thumb_func_start ov06_0223C694
ov06_0223C694: ; 0x0223C694
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r4, #0
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #0x64
	blo _0223C6B2
	bl GF_AssertFail
_0223C6B2:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	cmp r5, #0
	beq _0223C6C4
	cmp r5, #1
	beq _0223C6E8
	cmp r5, #2
	beq _0223C70C
	b _0223C730
_0223C6C4:
	cmp r0, #0x3c
	bhs _0223C6CC
	mov r4, #0
	b _0223C734
_0223C6CC:
	cmp r0, #0x5a
	bhs _0223C6D4
	mov r4, #1
	b _0223C734
_0223C6D4:
	cmp r0, #0x5f
	bhs _0223C6DC
	mov r4, #2
	b _0223C734
_0223C6DC:
	cmp r0, #0x63
	bhs _0223C6E4
	mov r4, #3
	b _0223C734
_0223C6E4:
	mov r4, #4
	b _0223C734
_0223C6E8:
	cmp r0, #0x28
	bhs _0223C6F0
	mov r4, #0
	b _0223C734
_0223C6F0:
	cmp r0, #0x50
	bhs _0223C6F8
	mov r4, #1
	b _0223C734
_0223C6F8:
	cmp r0, #0x5f
	bhs _0223C700
	mov r4, #2
	b _0223C734
_0223C700:
	cmp r0, #0x63
	bhs _0223C708
	mov r4, #3
	b _0223C734
_0223C708:
	mov r4, #4
	b _0223C734
_0223C70C:
	cmp r0, #0x28
	bhs _0223C714
	mov r4, #0
	b _0223C734
_0223C714:
	cmp r0, #0x50
	bhs _0223C71C
	mov r4, #1
	b _0223C734
_0223C71C:
	cmp r0, #0x5f
	bhs _0223C724
	mov r4, #2
	b _0223C734
_0223C724:
	cmp r0, #0x63
	bhs _0223C72C
	mov r4, #3
	b _0223C734
_0223C72C:
	mov r4, #4
	b _0223C734
_0223C730:
	bl GF_AssertFail
_0223C734:
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0223C738
ov06_0223C738: ; 0x0223C738
	push {r4, lr}
	add r4, r1, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	cmp r1, #0xe0
	beq _0223C754
	mov r0, #5
	lsl r0, r0, #6
	cmp r1, r0
	bne _0223C760
_0223C754:
	ldrb r0, [r4]
	mov r1, #3
	lsl r0, r0, #1
	bl _s32_div_f
	strb r0, [r4]
_0223C760:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223C764
ov06_0223C764: ; 0x0223C764
	push {r4, lr}
	ldr r0, [r0, #0xc]
	add r4, r1, #0
	bl Save_Roamers_Get
	bl sub_0202AB80
	cmp r0, #1
	bne _0223C77E
	ldrb r0, [r4]
	asr r0, r0, #1
	strb r0, [r4]
	pop {r4, pc}
_0223C77E:
	cmp r0, #2
	bne _0223C78A
	ldrb r1, [r4]
	lsr r0, r1, #1
	add r0, r1, r0
	strb r0, [r4]
_0223C78A:
	pop {r4, pc}

	thumb_func_start ov06_0223C78C
ov06_0223C78C: ; 0x0223C78C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r0, [r1, #0xd]
	cmp r0, #0
	bne _0223C7C6
	ldrb r0, [r1, #0xe]
	cmp r0, #0x1c
	bne _0223C7C6
	bl LCRandom
	lsl r0, r0, #1
	lsr r5, r0, #0x10
	cmp r5, #2
	blo _0223C7AC
	bl GF_AssertFail
_0223C7AC:
	cmp r5, #0
	bne _0223C7C6
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl GetMonData
	mov r1, #0x19
	bl _u32_div_f
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_0223C7C6:
	bl LCRandom
	ldr r1, _0223C7E4 ; =0x00000A3E
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x19
	blo _0223C7DC
	bl GF_AssertFail
_0223C7DC:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
	nop
_0223C7E4: .word 0x00000A3E

	thumb_func_start ov06_0223C7E8
ov06_0223C7E8: ; 0x0223C7E8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	ldrh r2, [r0, #6]
	ldrh r1, [r0, #4]
	cmp r1, r2
	blo _0223C7FC
	lsl r0, r2, #0x18
	lsr r5, r0, #0x18
	lsl r0, r1, #0x18
	b _0223C802
_0223C7FC:
	lsl r0, r1, #0x18
	lsr r5, r0, #0x18
	lsl r0, r2, #0x18
_0223C802:
	lsr r4, r0, #0x18
	bl LCRandom
	sub r1, r4, r5
	add r1, r1, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r6, r0, #0x18
	ldrb r0, [r7, #0xd]
	cmp r0, #0
	bne _0223C84C
	ldrb r0, [r7, #0xe]
	cmp r0, #0x37
	beq _0223C82C
	cmp r0, #0x48
	beq _0223C82C
	cmp r0, #0x2e
	bne _0223C84C
_0223C82C:
	bl LCRandom
	lsl r0, r0, #1
	lsr r7, r0, #0x10
	cmp r7, #2
	blo _0223C83C
	bl GF_AssertFail
_0223C83C:
	cmp r7, #0
	bne _0223C848
	add r0, r5, r6
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0223C848:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223C84C:
	add r0, r5, r6
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223C854
ov06_0223C854: ; 0x0223C854
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0x10]
	ldr r6, [sp, #0x40]
	str r1, [sp, #0x14]
	mov r0, #0xb
	str r2, [sp, #0x18]
	add r5, r3, #0
	bl AllocMonZeroed
	str r0, [sp, #0x1c]
	bl ZeroMonData
	ldrb r0, [r6, #0xd]
	mov r7, #0
	cmp r0, #0
	bne _0223C8E0
	ldrb r0, [r6, #0xe]
	cmp r0, #0x38
	bne _0223C8BE
	ldr r0, [sp, #0x10]
	mov r1, #0x12 ; BASE_GENDER_RATIO
	bl GetMonBaseStat
	cmp r0, #0
	beq _0223C8E0
	cmp r0, #0xfe
	beq _0223C8E0
	cmp r0, #0xff
	beq _0223C8E0
	bl LCRandom
	ldr r1, _0223C964 ; =0x00005556
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #3
	blo _0223C8A6
	bl GF_AssertFail
_0223C8A6:
	cmp r4, #0
	beq _0223C8E0
	ldr r0, [sp, #0x44]
	mov r1, #0x6f
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x24]
	mov r7, #1
	b _0223C8E0
_0223C8BE:
	cmp r0, #0x1c
	bne _0223C8E0
	bl LCRandom
	lsl r0, r0, #1
	lsr r4, r0, #0x10
	cmp r4, #2
	blo _0223C8D2
	bl GF_AssertFail
_0223C8D2:
	cmp r4, #0
	bne _0223C8E0
	ldr r0, [sp, #0x44]
	bl GetMonNature
	str r0, [sp, #0x20]
	mov r7, #1
_0223C8E0:
	add r0, r5, #0
	bl GenerateShinyPersonality
	add r4, r0, #0
	cmp r7, #0
	beq _0223C92E
_0223C8EC:
	ldrb r0, [r6, #0xe]
	cmp r0, #0x38
	bne _0223C914
	ldr r0, [sp, #0x10]
	add r1, r4, #0
	bl GetGenderBySpeciesAndPersonality
	add r7, r0, #0
	cmp r7, #2
	bne _0223C904
	bl GF_AssertFail
_0223C904:
	ldr r0, [sp, #0x24]
	cmp r7, r0
	bne _0223C92E
	add r0, r5, #0
	bl GenerateShinyPersonality
	add r4, r0, #0
	b _0223C8EC
_0223C914:
	cmp r0, #0x1c
	bne _0223C8EC
	add r0, r4, #0
	bl GetNatureFromPersonality
	ldr r1, [sp, #0x20]
	cmp r0, r1
	beq _0223C92E
	add r0, r5, #0
	bl GenerateShinyPersonality
	add r4, r0, #0
	b _0223C8EC
_0223C92E:
	mov r0, #1
	str r0, [sp]
	str r4, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r6]
	mov r3, #0x20
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	bl CreateMon
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x48]
	add r1, r6, #0
	bl ov06_0223D1BC
	cmp r0, #0
	bne _0223C95A
	bl GF_AssertFail
_0223C95A:
	ldr r0, [sp, #0x1c]
	bl FreeToHeap
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C964: .word 0x00005556

	thumb_func_start ov06_0223C968
ov06_0223C968: ; 0x0223C968
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	mov r0, #0xb
	str r1, [sp, #0xc]
	str r2, [sp, #0x10]
	add r5, r3, #0
	bl AllocMonZeroed
	add r4, r0, #0
	bl ZeroMonData
	add r0, r7, #0
	mov r1, #0x12 ; BASE_GENDER_RATIO
	mov r6, #1
	bl GetMonBaseStat
	cmp r0, #0
	beq _0223C996
	cmp r0, #0xfe
	beq _0223C996
	cmp r0, #0xff
	bne _0223C998
_0223C996:
	mov r6, #0
_0223C998:
	cmp r6, #0
	beq _0223CA28
	ldrb r0, [r5, #0xd]
	cmp r0, #0
	bne _0223CA28
	ldrb r0, [r5, #0xe]
	cmp r0, #0x38
	bne _0223CA28
	bl LCRandom
	ldr r1, _0223CA68 ; =0x00005556
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #3
	blo _0223C9BE
	bl GF_AssertFail
_0223C9BE:
	cmp r6, #0
	beq _0223CA28
	ldr r0, [sp, #0x28]
	mov r1, #0x6f
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #1
	bne _0223C9D8
	mov r6, #0
	b _0223C9E4
_0223C9D8:
	cmp r6, #0
	bne _0223C9E0
	mov r6, #1
	b _0223C9E4
_0223C9E0:
	bl GF_AssertFail
_0223C9E4:
	ldr r0, [sp, #0x28]
	add r1, r5, #0
	bl ov06_0223C78C
	str r6, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r2, [sp, #0xc]
	add r0, r4, #0
	add r1, r7, #0
	mov r3, #0x20
	bl CreateMonWithGenderNatureLetter
	add r0, r4, #0
	mov r1, #7
	add r2, r5, #0
	bl SetMonData
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x2c]
	add r1, r5, #0
	add r2, r4, #0
	bl ov06_0223D1BC
	cmp r0, #0
	bne _0223CA1E
	bl GF_AssertFail
_0223CA1E:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_0223CA28:
	ldr r0, [sp, #0x28]
	add r1, r5, #0
	bl ov06_0223C78C
	str r0, [sp]
	ldr r2, [sp, #0xc]
	add r0, r4, #0
	add r1, r7, #0
	mov r3, #0x20
	bl CreateMonWithNature
	add r0, r4, #0
	mov r1, #7
	add r2, r5, #0
	bl SetMonData
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x2c]
	add r1, r5, #0
	add r2, r4, #0
	bl ov06_0223D1BC
	cmp r0, #0
	bne _0223CA5C
	bl GF_AssertFail
_0223CA5C:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0223CA68: .word 0x00005556

	thumb_func_start ov06_0223CA6C
ov06_0223CA6C: ; 0x0223CA6C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #0xc]
	mov r7, #0
	add r1, sp, #0x10
	strb r7, [r1]
	add r1, sp, #0x18
	ldrb r1, [r1, #0x10]
	add r6, r0, #0
	add r5, r2, #0
	add r4, r3, #0
	cmp r1, #0
	beq _0223CA90
	cmp r1, #1
	beq _0223CAEC
	cmp r1, #2
	beq _0223CB38
	b _0223CB86
_0223CA90:
	mov r1, #8
	str r1, [sp]
	mov r1, #0x2a
	str r1, [sp, #4]
	add r1, sp, #0x10
	str r1, [sp, #8]
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #0xc
	bl ov06_0223CED4
	cmp r0, #0
	bne _0223CACE
	mov r0, #0xd
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	add r0, sp, #0x10
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #0xc
	bl ov06_0223CED4
	cmp r0, #0
	bne _0223CACE
	bl ov06_0223C5AC
	add r1, sp, #0x10
	strb r0, [r1]
_0223CACE:
	add r2, sp, #0x10
	ldrb r2, [r2]
	add r0, r4, #0
	add r1, r5, #0
	bl ov06_0223D27C
	add r1, sp, #0x10
	strb r0, [r1]
	ldrb r0, [r1]
	lsl r0, r0, #3
	add r0, r4, r0
	ldrh r0, [r0, #4]
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	b _0223CB8A
_0223CAEC:
	mov r1, #8
	str r1, [sp]
	mov r1, #0x2a
	str r1, [sp, #4]
	add r1, sp, #0x10
	str r1, [sp, #8]
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #5
	bl ov06_0223CED4
	mov r0, #0xd
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	add r0, sp, #0x10
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #5
	bl ov06_0223CED4
	cmp r0, #0
	bne _0223CB26
	bl ov06_0223C648
	add r1, sp, #0x10
	strb r0, [r1]
_0223CB26:
	add r0, sp, #0x10
	ldrb r0, [r0]
	add r1, r5, #0
	lsl r0, r0, #3
	add r0, r4, r0
	bl ov06_0223C7E8
	add r7, r0, #0
	b _0223CB8A
_0223CB38:
	mov r1, #8
	str r1, [sp]
	mov r1, #0x2a
	str r1, [sp, #4]
	add r1, sp, #0x10
	str r1, [sp, #8]
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #5
	bl ov06_0223CED4
	mov r0, #0xd
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	add r0, sp, #0x10
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	mov r3, #5
	bl ov06_0223CED4
	cmp r0, #0
	bne _0223CB74
	ldr r0, [sp, #0xc]
	bl ov06_0223C694
	add r1, sp, #0x10
	strb r0, [r1]
_0223CB74:
	add r0, sp, #0x10
	ldrb r0, [r0]
	add r1, r5, #0
	lsl r0, r0, #3
	add r0, r4, r0
	bl ov06_0223C7E8
	add r7, r0, #0
	b _0223CB8A
_0223CB86:
	bl GF_AssertFail
_0223CB8A:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov06_0223CF78
	cmp r0, #0
	beq _0223CB9E
	add sp, #0x14
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223CB9E:
	add r0, r7, #0
	add r1, r5, #0
	bl ov06_0223D030
	cmp r0, #1
	bne _0223CBB0
	add sp, #0x14
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223CBB0:
	ldr r0, [sp, #0x30]
	str r6, [sp]
	str r0, [sp, #4]
	add r0, sp, #0x10
	ldrb r0, [r0]
	ldr r2, [sp, #0x2c]
	add r1, r7, #0
	lsl r0, r0, #3
	ldr r0, [r4, r0]
	add r3, r5, #0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl ov06_0223C968
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223CBD4
ov06_0223CBD4: ; 0x0223CBD4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r5, #0
	bne _0223CBE8
	bl GF_AssertFail
_0223CBE8:
	lsl r0, r4, #0x18
	lsr r1, r0, #0x18
	cmp r7, #0
	beq _0223CC0A
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x20]
	str r0, [sp]
	ldr r0, [sp, #0x28]
	add r2, r6, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #8]
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl ov06_0223C854
	b _0223CC1E
_0223CC0A:
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x24]
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	add r2, r6, #0
	str r0, [sp, #4]
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl ov06_0223C968
_0223CC1E:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223CC24
ov06_0223CC24: ; 0x0223CC24
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	add r6, r1, #0
	mov r1, #0
	add r0, sp, #0x10
	strb r1, [r0]
	mov r0, #8
	str r0, [sp]
	mov r0, #0x2a
	add r5, r3, #0
	str r0, [sp, #4]
	add r0, sp, #0x10
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	add r1, r2, #0
	add r0, r6, #0
	add r2, r5, #0
	mov r3, #0xc
	bl ov06_0223CED4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bne _0223CC7A
	mov r0, #0xd
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	add r0, sp, #0x10
	str r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r0, r6, #0
	add r2, r5, #0
	mov r3, #0xc
	bl ov06_0223CED4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bne _0223CC7A
	bl ov06_0223C5AC
	add r1, sp, #0x10
	strb r0, [r1]
_0223CC7A:
	add r0, sp, #0x10
	ldrb r0, [r0]
	lsl r0, r0, #3
	add r1, r5, r0
	ldrh r1, [r1, #4]
	ldr r5, [r5, r0]
	ldr r0, [sp, #0x30]
	lsl r1, r1, #0x18
	lsr r7, r1, #0x18
	cmp r0, #0
	bne _0223CCA6
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	add r1, r5, #0
	add r2, r7, #0
	bl sub_0205E080
	add r0, r4, #0
	bl sub_0205E480
	b _0223CCC2
_0223CCA6:
	cmp r5, r0
	bne _0223CCBA
	add r5, r0, #0
	ldr r0, [sp, #0x34]
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r4, #0
	bl sub_0205E480
	b _0223CCC2
_0223CCBA:
	add r4, #0x90
	ldr r0, [r4]
	bl sub_0205DD40
_0223CCC2:
	ldr r0, [sp, #0x2c]
	str r6, [sp]
	str r0, [sp, #4]
	lsl r0, r5, #0x10
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0xc]
	lsr r0, r0, #0x10
	add r1, r7, #0
	bl ov06_0223C968
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223CCDC
ov06_0223CCDC: ; 0x0223CCDC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F51D0
	str r0, [sp, #8]
	ldr r0, [r5, #0xc]
	bl SaveArray_Party_Get
	mov r1, #0
	bl Party_GetMonByIndex
	str r0, [sp, #0xc]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	mov r2, #0
	add r3, sp, #0x10
	bl ov06_0223D2DC
	bl LCRandom
	ldr r1, _0223CD78 ; =0x00001746
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #0xb
	blo _0223CD1A
	bl GF_AssertFail
_0223CD1A:
	add r0, r6, #5
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, sp, #0x10
	ldrb r1, [r0, #0xd]
	cmp r1, #0
	bne _0223CD4C
	ldrb r0, [r0, #0xe]
	cmp r0, #0x37
	beq _0223CD36
	cmp r0, #0x48
	beq _0223CD36
	cmp r0, #0x2e
	bne _0223CD4C
_0223CD36:
	bl LCRandom
	lsl r0, r0, #1
	lsr r6, r0, #0x10
	cmp r6, #2
	blo _0223CD46
	bl GF_AssertFail
_0223CD46:
	cmp r6, #0
	beq _0223CD4C
	mov r7, #0xf
_0223CD4C:
	add r0, r5, #0
	bl ov05_021F522C
	mov r1, #0x63
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r0, #2
	orr r0, r2
	str r0, [r4, r1]
	ldr r0, [sp, #0xc]
	add r1, r7, #0
	str r0, [sp]
	ldr r0, [sp, #8]
	mov r2, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r3, sp, #0x10
	str r4, [sp, #4]
	bl ov06_0223C968
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223CD78: .word 0x00001746

	thumb_func_start ov06_0223CD7C
ov06_0223CD7C: ; 0x0223CD7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	str r2, [sp, #8]
	ldr r0, [r5, #0xc]
	add r7, r1, #0
	add r6, r3, #0
	bl SaveArray_Party_Get
	mov r1, #0
	bl Party_GetMonByIndex
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	add r3, sp, #0xc
	bl ov06_0223D2DC
	str r4, [sp]
	str r6, [sp, #4]
	ldr r1, [sp, #8]
	add r0, r7, #0
	mov r2, #1
	add r3, sp, #0xc
	bl ov06_0223C968
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223CDB8
ov06_0223CDB8: ; 0x0223CDB8
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r4, #0
	bl sub_02054AFC
	cmp r0, #0
	beq _0223CDE6
	add r0, r6, #0
	bl sub_0205481C
	cmp r0, #0
	beq _0223CDDE
	add r0, r5, #0
	bl ov06_0223CE00
	add r4, r0, #0
	b _0223CDE6
_0223CDDE:
	add r0, r5, #0
	bl ov06_0223CDF4
	add r4, r0, #0
_0223CDE6:
	cmp r4, #0
	beq _0223CDEE
	mov r0, #1
	pop {r4, r5, r6, pc}
_0223CDEE:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223CDF4
ov06_0223CDF4: ; 0x0223CDF4
	push {r3, lr}
	bl sub_02034CE0
	ldr r0, [r0]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0223CE00
ov06_0223CE00: ; 0x0223CE00
	push {r3, lr}
	bl sub_02034CE0
	add r0, #0xcc
	ldr r0, [r0]
	pop {r3, pc}

	thumb_func_start ov06_0223CE0C
ov06_0223CE0C: ; 0x0223CE0C
	push {r4, lr}
	add r4, r1, #0
	bl sub_02034CE0
	cmp r4, #0
	beq _0223CE22
	cmp r4, #1
	beq _0223CE2A
	cmp r4, #2
	beq _0223CE32
	b _0223CE3A
_0223CE22:
	mov r1, #0x49
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	pop {r4, pc}
_0223CE2A:
	mov r1, #0x15
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	pop {r4, pc}
_0223CE32:
	mov r1, #0x5f
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	pop {r4, pc}
_0223CE3A:
	bl GF_AssertFail
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223CE44
ov06_0223CE44: ; 0x0223CE44
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	mov r0, #0
	str r1, [sp]
	add r7, r2, #0
	str r3, [sp, #4]
	add r4, r0, #0
	add r1, sp, #0x10
_0223CE56:
	strb r4, [r1, r0]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0xc
	blo _0223CE56
	ldr r0, [sp]
	add r5, r4, #0
	cmp r0, #0
	bls _0223CEAC
_0223CE6A:
	lsl r0, r5, #3
	str r0, [sp, #0xc]
	ldr r0, [r6, r0]
	mov r1, #6 ; BASE_TYPE1
	bl GetMonBaseStat
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	mov r1, #7 ; BASE_TYPE2
	ldr r0, [r6, r0]
	bl GetMonBaseStat
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #8]
	cmp r0, r7
	beq _0223CE94
	cmp r1, r7
	bne _0223CEA0
_0223CE94:
	add r1, r4, #1
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r4, r1, #0x18
	add r1, sp, #0x10
	strb r5, [r1, r0]
_0223CEA0:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [sp]
	cmp r5, r0
	blo _0223CE6A
_0223CEAC:
	cmp r4, #0
	beq _0223CEB6
	ldr r0, [sp]
	cmp r4, r0
	bne _0223CEBC
_0223CEB6:
	add sp, #0x1c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223CEBC:
	bl LCRandom
	add r1, r4, #0
	bl _s32_div_f
	add r0, sp, #0x10
	ldrb r1, [r0, r1]
	ldr r0, [sp, #4]
	strb r1, [r0]
	mov r0, #1
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223CED4
ov06_0223CED4: ; 0x0223CED4
	push {r4, r5, r6, lr}
	ldrb r0, [r1, #0xd]
	add r5, r2, #0
	add r6, r3, #0
	cmp r0, #0
	bne _0223CF0E
	add r0, sp, #0
	ldrb r1, [r1, #0xe]
	ldrb r0, [r0, #0x14]
	cmp r1, r0
	bne _0223CF0E
	bl LCRandom
	lsl r0, r0, #1
	lsr r4, r0, #0x10
	cmp r4, #2
	blo _0223CEFA
	bl GF_AssertFail
_0223CEFA:
	cmp r4, #0
	bne _0223CF0E
	add r2, sp, #0
	ldrb r2, [r2, #0x10]
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0223CE44
	pop {r4, r5, r6, pc}
_0223CF0E:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223CF14
ov06_0223CF14: ; 0x0223CF14
	push {r3, r4}
	ldrb r4, [r2, #0xd]
	cmp r4, #0
	bne _0223CF70
	cmp r0, #0
	ldrb r0, [r2, #0xe]
	beq _0223CF26
	cmp r0, #0x3c
	b _0223CF6A
_0223CF26:
	cmp r0, #0x47
	beq _0223CF32
	cmp r0, #0x63
	beq _0223CF32
	cmp r0, #0x23
	bne _0223CF36
_0223CF32:
	lsl r1, r1, #1
	b _0223CF6A
_0223CF36:
	cmp r0, #8
	bne _0223CF46
	cmp r3, #0xa
	bne _0223CF6A
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	b _0223CF6A
_0223CF46:
	cmp r0, #0x51
	bne _0223CF58
	sub r0, r3, #5
	cmp r0, #2
	bhi _0223CF6A
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	b _0223CF6A
_0223CF58:
	cmp r0, #0x49
	beq _0223CF64
	cmp r0, #0x5f
	beq _0223CF64
	cmp r0, #1
	bne _0223CF6A
_0223CF64:
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
_0223CF6A:
	cmp r1, #0x64
	ble _0223CF70
	mov r1, #0x64
_0223CF70:
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4}
	bx lr

	thumb_func_start ov06_0223CF78
ov06_0223CF78: ; 0x0223CF78
	push {r4, lr}
	add r4, r2, #0
	ldr r2, [r0, #8]
	cmp r2, #0
	beq _0223CF86
	mov r0, #0
	pop {r4, pc}
_0223CF86:
	ldrb r2, [r0, #0xd]
	cmp r2, #0
	bne _0223CFCA
	ldrb r0, [r0, #0xe]
	cmp r0, #0x33
	beq _0223CF96
	cmp r0, #0x16
	bne _0223CFCA
_0223CF96:
	add r0, r1, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #5
	bhi _0223CFAC
	mov r0, #0
	pop {r4, pc}
_0223CFAC:
	sub r0, r0, #5
	cmp r4, r0
	bgt _0223CFCA
	bl LCRandom
	lsl r0, r0, #1
	lsr r4, r0, #0x10
	cmp r4, #2
	blo _0223CFC2
	bl GF_AssertFail
_0223CFC2:
	cmp r4, #0
	bne _0223CFCA
	mov r0, #1
	pop {r4, pc}
_0223CFCA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223CFD0
ov06_0223CFD0: ; 0x0223CFD0
	push {r4, lr}
	add r4, r2, #0
	cmp r1, #0
	bne _0223CFE4
	mov r0, #0xb
	mov r1, #0
	bl BattleSetup_New
	str r0, [r4]
	pop {r4, pc}
_0223CFE4:
	ldr r0, [r0, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetSafariBallsCounter
	add r1, r0, #0
	ldrh r1, [r1]
	mov r0, #0xb
	bl sub_020477EC
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start ov06_0223CFFC
ov06_0223CFFC: ; 0x0223CFFC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r6, r2, #0
	add r4, r3, #0
	cmp r1, #0
	beq _0223D02A
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	mov r1, #1
	bl Roamers_GetRand
	add r1, r4, #0
	add r1, #0x38
	str r1, [sp]
	ldr r2, [r5, #0x1c]
	add r4, #0x30
	ldr r2, [r2]
	add r1, r6, #0
	add r3, r4, #0
	bl ov06_02245658
_0223D02A:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223D030
ov06_0223D030: ; 0x0223D030
	ldr r2, [r1, #4]
	cmp r2, #0
	beq _0223D040
	ldrb r1, [r1, #0xc]
	cmp r1, r0
	bls _0223D040
	mov r0, #1
	bx lr
_0223D040:
	mov r0, #0
	bx lr

	thumb_func_start ov06_0223D044
ov06_0223D044: ; 0x0223D044
	push {r0, r1, r2, r3}
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	mov r0, #4
	add r6, r2, #0
	bl AllocMonZeroed
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #4
	bl sub_0202AAB8
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #6
	bl sub_0202AAB8
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r5, #0
	mov r1, #2
	bl sub_0202AAB8
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #3
	bl sub_0202AAB8
	str r0, [sp, #0xc]
	add r0, r5, #0
	mov r1, #7
	bl sub_0202AAB8
	str r0, [sp, #0x14]
	add r0, r5, #0
	mov r1, #5
	bl sub_0202AAB8
	add r1, sp, #0x10
	strh r0, [r1]
	ldr r1, [sp, #4]
	ldr r0, [sp, #0xc]
	lsl r1, r1, #0x10
	str r0, [sp]
	ldr r3, [sp, #8]
	add r0, r4, #0
	lsr r1, r1, #0x10
	add r2, r7, #0
	bl CreateMonWithFixedIVs
	add r0, r4, #0
	mov r1, #7
	add r2, sp, #0x30
	bl SetMonData
	add r0, r4, #0
	mov r1, #0x9f
	add r2, sp, #0x14
	bl SetMonData
	add r0, r4, #0
	mov r1, #0xa2
	add r2, sp, #0x10
	bl SetMonData
	ldr r0, [r6, #8]
	add r1, r4, #0
	bl Party_AddMon
	cmp r0, #0
	bne _0223D0D8
	bl GF_AssertFail
_0223D0D8:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x18
	pop {r3, r4, r5, r6, r7}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start ov06_0223D0E8
ov06_0223D0E8: ; 0x0223D0E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp]
	ldr r0, [r0, #0xc]
	str r1, [sp, #4]
	mov r5, #0
	bl Save_Roamers_Get
	add r6, r0, #0
	add r4, r5, #0
_0223D0FC:
	add r0, r6, #0
	add r1, r4, #0
	bl sub_0202AA40
	bl sub_0206043C
	add r7, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl sub_0202AA74
	cmp r0, #0
	beq _0223D134
	ldr r0, [sp]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0]
	cmp r7, r0
	bne _0223D134
	add r0, r6, #0
	add r1, r4, #0
	bl sub_0202AAA0
	lsl r2, r5, #2
	add r1, sp, #8
	str r0, [r1, r2]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0223D134:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _0223D0FC
	cmp r5, #0
	bne _0223D148
	add sp, #0x14
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223D148:
	bl LCRandom
	lsl r0, r0, #1
	lsr r4, r0, #0x10
	cmp r4, #2
	blo _0223D158
	bl GF_AssertFail
_0223D158:
	cmp r4, #0
	bne _0223D162
	add sp, #0x14
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223D162:
	cmp r5, #1
	bls _0223D1AA
	cmp r5, #0
	bne _0223D16E
	bl GF_AssertFail
_0223D16E:
	cmp r5, #1
	bhi _0223D176
	mov r4, #0
	b _0223D19E
_0223D176:
	bl LCRandom
	add r4, r0, #0
	ldr r0, _0223D1B8 ; =0x0000FFFF
	add r1, r5, #0
	bl _s32_div_f
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r5
	blo _0223D19E
	bl GF_AssertFail
_0223D19E:
	lsl r1, r4, #2
	add r0, sp, #8
	ldr r1, [r0, r1]
	ldr r0, [sp, #4]
	str r1, [r0]
	b _0223D1B0
_0223D1AA:
	ldr r1, [sp, #8]
	ldr r0, [sp, #4]
	str r1, [r0]
_0223D1B0:
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0223D1B8: .word 0x0000FFFF

	thumb_func_start ov06_0223D1BC
ov06_0223D1BC: ; 0x0223D1BC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	str r0, [sp]
	ldrb r0, [r5, #0xd]
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #0
	bne _0223D1D8
	ldrb r0, [r5, #0xe]
	cmp r0, #0xe
	bne _0223D1D8
	mov r2, #1
	b _0223D1DA
_0223D1D8:
	mov r2, #0
_0223D1DA:
	ldr r1, [r7]
	add r0, r6, #0
	bl sub_0206A094
	mov r4, #0
	add r0, r6, #0
	mov r1, #5
	add r2, r4, #0
	bl GetMonData
	ldr r1, _0223D270 ; =0x000001A6
	cmp r0, r1
	bne _0223D208
	ldrb r0, [r5, #0xf]
	mov r4, #1
	cmp r0, #0
	add r0, sp, #8
	bne _0223D204
	mov r1, #0
	strb r1, [r0]
	b _0223D24E
_0223D204:
	strb r4, [r0]
	b _0223D24E
_0223D208:
	add r1, r1, #1
	cmp r0, r1
	bne _0223D222
	ldrb r0, [r5, #0x10]
	mov r4, #1
	cmp r0, #0
	add r0, sp, #8
	bne _0223D21E
	mov r1, #0
	strb r1, [r0]
	b _0223D24E
_0223D21E:
	strb r4, [r0]
	b _0223D24E
_0223D222:
	cmp r0, #0xc9
	bne _0223D24E
	ldrb r0, [r5, #0x11]
	mov r4, #1
	lsl r1, r0, #3
	ldr r0, _0223D274 ; =0x0224F308
	ldr r0, [r0, r1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	bl LCRandom
	ldr r1, [sp, #4]
	bl _s32_div_f
	ldrb r0, [r5, #0x11]
	lsl r2, r0, #3
	ldr r0, _0223D278 ; =0x0224F30C
	ldr r0, [r0, r2]
	ldrb r1, [r0, r1]
	add r0, sp, #8
	strb r1, [r0]
_0223D24E:
	cmp r4, #0
	beq _0223D25C
	add r0, r6, #0
	mov r1, #0x70
	add r2, sp, #8
	bl SetMonData
_0223D25C:
	ldr r0, [sp]
	add r1, r6, #0
	lsl r0, r0, #2
	add r0, r7, r0
	ldr r0, [r0, #4]
	bl Party_AddMon
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0223D270: .word 0x000001A6
_0223D274: .word ov06_0224F308
_0223D278: .word ov06_0224F30C

	thumb_func_start ov06_0223D27C
ov06_0223D27C: ; 0x0223D27C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrb r0, [r1, #0xd]
	add r4, r2, #0
	cmp r0, #0
	bne _0223D2D8
	ldrb r0, [r1, #0xe]
	cmp r0, #0x48
	beq _0223D296
	cmp r0, #0x37
	beq _0223D296
	cmp r0, #0x2e
	bne _0223D2D8
_0223D296:
	bl LCRandom
	lsl r0, r0, #1
	lsr r6, r0, #0x10
	cmp r6, #2
	blo _0223D2A6
	bl GF_AssertFail
_0223D2A6:
	cmp r6, #0
	bne _0223D2AE
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223D2AE:
	mov r1, #0
_0223D2B0:
	lsl r2, r1, #3
	lsl r7, r4, #3
	add r6, r5, r2
	ldr r3, [r5, r2]
	ldr r2, [r5, r7]
	add r0, r5, r7
	cmp r3, r2
	bne _0223D2CA
	ldrh r2, [r6, #4]
	ldrh r0, [r0, #4]
	cmp r2, r0
	bls _0223D2CA
	add r4, r1, #0
_0223D2CA:
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #0xc
	blo _0223D2B0
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223D2D8:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223D2DC
ov06_0223D2DC: ; 0x0223D2DC
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r6, r0, #0
	add r5, r2, #0
	add r0, r7, #0
	mov r1, #0x4c
	mov r2, #0
	add r4, r3, #0
	bl GetMonData
	cmp r0, #0
	bne _0223D302
	mov r2, #0
	add r0, r7, #0
	mov r1, #0xa
	strb r2, [r4, #0xd]
	bl GetMonData
	b _0223D308
_0223D302:
	mov r0, #1
	strb r0, [r4, #0xd]
	mov r0, #0x7b
_0223D308:
	strb r0, [r4, #0xe]
	mov r0, #0
	strb r0, [r4, #0xc]
	str r0, [r4, #4]
	str r0, [r4, #8]
	cmp r5, #0
	beq _0223D344
	add r1, r5, #0
	add r1, #0x8c
	ldr r1, [r1]
	strb r1, [r4, #0xf]
	add r1, r5, #0
	add r1, #0x90
	ldr r1, [r1]
	strb r1, [r4, #0x10]
	add r1, r5, #0
	add r1, #0xa0
	ldr r1, [r1]
	cmp r1, #0
	beq _0223D342
	cmp r1, #8
	ble _0223D338
	bl GF_AssertFail
_0223D338:
	add r5, #0xa0
	ldr r0, [r5]
	sub r0, r0, #1
	strb r0, [r4, #0x11]
	b _0223D344
_0223D342:
	strb r0, [r4, #0x11]
_0223D344:
	ldr r0, [r6, #0xc]
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerID
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223D354
ov06_0223D354: ; 0x0223D354
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #1
	add r5, r0, #0
	ldr r2, _0223D3B0 ; =0x0000FFFF
	mov r0, #0
	lsl r1, r1, #8
_0223D362:
	lsl r3, r0, #1
	ldrh r3, [r4, r3]
	cmp r3, r2
	beq _0223D374
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, r1
	blo _0223D362
_0223D374:
	mov r1, #0x8b
	lsl r1, r1, #2
	strb r0, [r5, r1]
	ldrb r1, [r5, r1]
	mov r0, #0xb
	lsl r1, r1, #1
	bl AllocFromHeap
	mov r1, #0x8a
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r1, r1, #4
	ldrb r1, [r5, r1]
	mov r0, #0
	cmp r1, #0
	ble _0223D3AE
	mov r1, #0x8a
	lsl r1, r1, #2
	add r2, r1, #4
_0223D39A:
	lsl r7, r0, #1
	ldrh r6, [r4, r7]
	ldr r3, [r5, r1]
	add r0, r0, #1
	strh r6, [r3, r7]
	lsl r0, r0, #0x10
	ldrb r3, [r5, r2]
	lsr r0, r0, #0x10
	cmp r0, r3
	blt _0223D39A
_0223D3AE:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223D3B0: .word 0x0000FFFF

	thumb_func_start ov06_0223D3B4
ov06_0223D3B4: ; 0x0223D3B4
	push {r4, lr}
	mov r1, #0x93
	mov r0, #0xb
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x93
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start ov06_0223D3D0
ov06_0223D3D0: ; 0x0223D3D0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	str r2, [sp]
	add r6, r3, #0
	bl ov06_0223D3B4
	add r4, r0, #0
	ldr r0, [r5, #8]
	mov r1, #0xb
	str r0, [r4]
	mov r0, #0x60
	bl String_New
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0x83
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	mov r1, #0x85
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r5, #0xc]
	bl Save_GameStats_Get
	mov r1, #0x87
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #0x22
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r2, [sp, #0x18]
	add r0, r1, #4
	str r2, [r4, r0]
	add r0, r5, #0
	bl ov06_0223D490
	ldr r1, _0223D488 ; =0x0000023E
	strb r0, [r4, r1]
	add r0, r5, #0
	add r0, #0x98
	ldr r2, [r0]
	add r0, r1, #0
	sub r0, #0x26
	str r2, [r4, r0]
	add r0, r1, #3
	strb r6, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0223D456
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r4, r1]
	b _0223D472
_0223D456:
	cmp r0, #1
	ldr r0, [r5, #0xc]
	bne _0223D468
	bl sub_02026CC4
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r4, r1]
	b _0223D472
_0223D468:
	bl Save_SealCase_Get
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r4, r1]
_0223D472:
	ldr r1, [sp]
	add r0, r4, #0
	bl ov06_0223D354
	ldr r1, _0223D48C ; =ov06_0223D4AC
	add r0, r7, #0
	add r2, r4, #0
	bl TaskManager_Call
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223D488: .word 0x0000023E
_0223D48C: .word ov06_0223D4AC

	thumb_func_start ov06_0223D490
ov06_0223D490: ; 0x0223D490
	push {r3, lr}
	ldr r0, [r0, #0x38]
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #0
	beq _0223D4A4
	cmp r0, #1
	beq _0223D4A4
	cmp r0, #3
	bne _0223D4A8
_0223D4A4:
	mov r0, #0xa
	pop {r3, pc}
_0223D4A8:
	mov r0, #8
	pop {r3, pc}

	thumb_func_start ov06_0223D4AC
ov06_0223D4AC: ; 0x0223D4AC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r6, #0
	bl TaskManager_GetEnvironment
	ldr r1, _0223D604 ; =0x0000022F
	add r4, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0x14
	bls _0223D4C8
	b _0223D5D0
_0223D4C8:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223D4D4: ; jump table
	.short _0223D4FE - _0223D4D4 - 2 ; case 0
	.short _0223D50A - _0223D4D4 - 2 ; case 1
	.short _0223D514 - _0223D4D4 - 2 ; case 2
	.short _0223D524 - _0223D4D4 - 2 ; case 3
	.short _0223D52E - _0223D4D4 - 2 ; case 4
	.short _0223D538 - _0223D4D4 - 2 ; case 5
	.short _0223D542 - _0223D4D4 - 2 ; case 6
	.short _0223D54C - _0223D4D4 - 2 ; case 7
	.short _0223D556 - _0223D4D4 - 2 ; case 8
	.short _0223D560 - _0223D4D4 - 2 ; case 9
	.short _0223D56A - _0223D4D4 - 2 ; case 10
	.short _0223D574 - _0223D4D4 - 2 ; case 11
	.short _0223D57E - _0223D4D4 - 2 ; case 12
	.short _0223D58C - _0223D4D4 - 2 ; case 13
	.short _0223D596 - _0223D4D4 - 2 ; case 14
	.short _0223D5A0 - _0223D4D4 - 2 ; case 15
	.short _0223D5D0 - _0223D4D4 - 2 ; case 16
	.short _0223D5D0 - _0223D4D4 - 2 ; case 17
	.short _0223D5A8 - _0223D4D4 - 2 ; case 18
	.short _0223D5B6 - _0223D4D4 - 2 ; case 19
	.short _0223D5C6 - _0223D4D4 - 2 ; case 20
_0223D4FE:
	bl ov06_0223D608
	ldr r0, _0223D604 ; =0x0000022F
	mov r1, #1
	strb r1, [r4, r0]
	b _0223D5D0
_0223D50A:
	bl ov06_0223D788
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D514:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0223D918
	ldr r0, _0223D604 ; =0x0000022F
	mov r1, #3
	strb r1, [r4, r0]
	b _0223D5D0
_0223D524:
	bl ov06_0223DB64
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D52E:
	bl ov06_0223DFB4
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D538:
	bl ov06_0223E198
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D542:
	bl ov06_0223E29C
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D54C:
	bl ov06_0223E5E4
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D556:
	bl ov06_0223E61C
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D560:
	bl ov06_0223E79C
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D56A:
	bl ov06_0223E858
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D574:
	bl ov06_0223E950
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D57E:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0223EA38
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D58C:
	bl ov06_0223EB04
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D596:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0223ECD8
	b _0223D5D0
_0223D5A0:
	add r0, r6, #0
	bl ov06_0223ECF0
	b _0223D5D0
_0223D5A8:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0223ED54
	ldr r1, _0223D604 ; =0x0000022F
	strb r0, [r4, r1]
	b _0223D5D0
_0223D5B6:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0223EB2C
	ldr r0, _0223D604 ; =0x0000022F
	mov r1, #0x14
	strb r1, [r4, r0]
	b _0223D5D0
_0223D5C6:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0223D7EC
	pop {r4, r5, r6, pc}
_0223D5D0:
	ldr r0, _0223D604 ; =0x0000022F
	ldrb r1, [r4, r0]
	cmp r1, #4
	blo _0223D5FE
	cmp r1, #0xb
	bhi _0223D5FE
	sub r0, #0x37
	mov r1, #1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl sub_020201E4
	mov r0, #0x7f
	lsl r0, r0, #2
	mov r1, #1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl sub_020201E4
	add r4, #0x94
	ldr r0, [r4]
	bl sub_0201FDEC
_0223D5FE:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_0223D604: .word 0x0000022F

	thumb_func_start ov06_0223D608
ov06_0223D608: ; 0x0223D608
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0223D618
	add r0, r4, #0
	bl ov06_0223D63C
	pop {r4, pc}

	thumb_func_start ov06_0223D618
ov06_0223D618: ; 0x0223D618
	push {r4, lr}
	mov r2, #0x7a
	add r4, r0, #0
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #0xb
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0x88
	str r0, [r1]
	mov r0, #0xb
	bl MessageFormat_New
	add r4, #0x8c
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start ov06_0223D63C
ov06_0223D63C: ; 0x0223D63C
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, _0223D77C ; =0x00000241
	ldrb r0, [r5, r0]
	cmp r0, #0
	bne _0223D6B8
	mov r4, #3
	add r0, r4, #0
	mov r1, #0xb
	bl ListMenuItems_New
	add r1, r5, #0
	add r1, #0x84
	str r0, [r1]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x84
	add r1, #0x88
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xf
	mov r3, #2
	bl ListMenuItems_AppendFromMsgData
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x84
	add r1, #0x88
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0x10
	mov r3, #0xe
	bl ListMenuItems_AppendFromMsgData
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x84
	add r1, #0x88
	mov r2, #0x11
	add r3, r2, #0
	ldr r0, [r0]
	ldr r1, [r1]
	sub r3, #0x13
	bl ListMenuItems_AppendFromMsgData
	mov r3, #1
	str r3, [sp]
	mov r1, #0xd
	str r1, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, _0223D780 ; =0x000002DF
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, #8
	add r2, r4, #0
	bl AddWindowParameterized
	b _0223D710
_0223D6B8:
	mov r4, #2
	add r0, r4, #0
	mov r1, #0xb
	bl ListMenuItems_New
	add r1, r5, #0
	add r1, #0x84
	str r0, [r1]
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x84
	add r1, #0x88
	ldr r0, [r0]
	ldr r1, [r1]
	mov r2, #0xf
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x84
	add r1, #0x88
	mov r2, #0x11
	add r3, r2, #0
	ldr r0, [r0]
	ldr r1, [r1]
	sub r3, #0x13
	bl ListMenuItems_AppendFromMsgData
	mov r3, #1
	str r3, [sp]
	mov r1, #0xd
	str r1, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, _0223D780 ; =0x000002DF
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, #8
	mov r2, #3
	bl AddWindowParameterized
_0223D710:
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	add r2, sp, #0x14
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #8
	str r0, [sp, #0x18]
	mov r0, #0
	strb r0, [r2, #8]
	mov r1, #1
	strb r1, [r2, #9]
	strb r4, [r2, #0xa]
	ldrb r3, [r2, #0xb]
	mov r1, #0xf
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0x30
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0xc0
	bic r3, r1
	strb r3, [r2, #0xb]
	str r0, [sp]
	mov r3, #0xb
	str r3, [sp, #4]
	ldr r0, [r5]
	ldr r2, _0223D784 ; =0x000003D9
	mov r1, #3
	bl LoadUserFrameGfx1
	add r0, r5, #0
	ldr r2, _0223D784 ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl DrawFrameAndWindow1
	mov r0, #0xb
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #0x14
	mov r1, #8
	add r3, r2, #0
	bl sub_02001C14
	add r5, #0x80
	str r0, [r5]
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223D77C: .word 0x00000241
_0223D780: .word 0x000002DF
_0223D784: .word 0x000003D9

	thumb_func_start ov06_0223D788
ov06_0223D788: ; 0x0223D788
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x80
	ldr r0, [r0]
	bl sub_02001C78
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0223D7A4
	add r1, r1, #1
	cmp r0, r1
	beq _0223D7B4
	b _0223D7AE
_0223D7A4:
	add r0, r4, #0
	bl ov06_0223D7B8
	mov r0, #0x13
	pop {r4, pc}
_0223D7AE:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}
_0223D7B4:
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov06_0223D7B8
ov06_0223D7B8: ; 0x0223D7B8
	push {r4, lr}
	add r4, r0, #0
	add r0, #8
	mov r1, #1
	bl ClearFrameAndWindow1
	add r0, r4, #0
	add r0, #8
	bl ClearWindowTilemapAndCopyToVram
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0
	bl sub_02001C5C
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	bl ListMenuItems_Delete
	add r4, #8
	add r0, r4, #0
	bl RemoveWindow
	pop {r4, pc}

	thumb_func_start ov06_0223D7EC
ov06_0223D7EC: ; 0x0223D7EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x8f
	add r4, r1, #0
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223D804
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223D804:
	ldr r0, _0223D90C ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0223D908
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0
	bl ClearFrameAndWindow2
	add r0, r4, #0
	add r0, #0x18
	bl RemoveWindow
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	bl DestroyMsgData
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl MessageFormat_Delete
	mov r0, #0x23
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_Delete
	ldr r0, _0223D910 ; =0x00000241
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0223D8F4
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MapHeader_GetMapSec
	cmp r0, #0x65
	beq _0223D8F4
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	cmp r0, #0x51
	beq _0223D8F4
	ldr r1, _0223D914 ; =0x000001BE
	cmp r0, r1
	beq _0223D8F4
	add r0, r1, #0
	add r0, #0x81
	ldrb r2, [r4, r0]
	cmp r2, #0
	beq _0223D888
	add r1, #0x82
	ldrb r0, [r4, r1]
	cmp r0, #0
	beq _0223D888
	mov r0, #0xb
	bl sub_02029084
	add r1, r0, #0
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #1
	bl sub_02028AD4
	b _0223D8F4
_0223D888:
	cmp r2, #1
	bls _0223D8A2
	mov r0, #0xb
	bl sub_02029060
	add r1, r0, #0
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #1
	bl sub_02028AD4
	b _0223D8F4
_0223D8A2:
	mov r0, #9
	lsl r0, r0, #6
	ldrb r0, [r4, r0]
	cmp r0, #1
	bls _0223D8C2
	mov r0, #0xb
	bl sub_02029078
	add r1, r0, #0
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #1
	bl sub_02028AD4
	b _0223D8F4
_0223D8C2:
	cmp r2, #0
	beq _0223D8DC
	mov r0, #0xb
	bl sub_02029054
	add r1, r0, #0
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #1
	bl sub_02028AD4
	b _0223D8F4
_0223D8DC:
	cmp r0, #0
	beq _0223D8F4
	mov r0, #0xb
	bl sub_0202906C
	add r1, r0, #0
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #1
	bl sub_02028AD4
_0223D8F4:
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223D908:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223D90C: .word gSystem
_0223D910: .word 0x00000241
_0223D914: .word 0x000001BE

	thumb_func_start ov06_0223D918
ov06_0223D918: ; 0x0223D918
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #6
	mov r2, #0
	str r0, [sp, #8]
	add r4, r1, #0
	str r2, [sp, #0xc]
	ldr r0, [r4]
	mov r1, #3
	add r3, r2, #0
	bl FillBgTilemapRect
	add r0, r4, #0
	bl ov06_0223D7B8
	add r0, r4, #0
	bl ov06_0223D978
	mov r0, #0xb
	bl Camera_New
	add r1, r4, #0
	add r1, #0x90
	str r0, [r1]
	add r1, r4, #0
	add r1, #0x90
	ldr r0, [r5, #0x20]
	ldr r1, [r1]
	bl Camera_Copy
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	bl Camera_SetStaticPtr
	ldr r0, _0223D974 ; =0x0000023D
	mov r1, #0
	strb r1, [r4, r0]
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_0223D974: .word 0x0000023D

	thumb_func_start ov06_0223D978
ov06_0223D978: ; 0x0223D978
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r5, #0
	ldr r7, _0223D9B4 ; =0x0224F3AC
	mov r6, #0
	add r4, #8
_0223D984:
	ldr r0, _0223D9B8 ; =0x00000241
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _0223D99C
	cmp r6, #1
	bne _0223D99C
	ldr r0, [r5]
	ldr r2, _0223D9BC ; =0x0224F350
	add r1, r4, #0
	bl AddWindow
	b _0223D9A6
_0223D99C:
	ldr r0, [r5]
	add r1, r4, #0
	add r2, r7, #0
	bl AddWindow
_0223D9A6:
	add r6, r6, #1
	add r4, #0x10
	add r7, #8
	cmp r6, #6
	blo _0223D984
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223D9B4: .word ov06_0224F3AC
_0223D9B8: .word 0x00000241
_0223D9BC: .word ov06_0224F350

	thumb_func_start ov06_0223D9C0
ov06_0223D9C0: ; 0x0223D9C0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0x28
	mov r1, #1
	bl ClearFrameAndWindow1
	mov r4, #0
	add r5, #8
_0223D9D0:
	add r0, r5, #0
	bl ClearWindowTilemapAndCopyToVram
	add r0, r5, #0
	bl RemoveWindow
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #6
	blo _0223D9D0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0223D9E8
ov06_0223D9E8: ; 0x0223D9E8
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	add r4, r0, #0
	str r1, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x3e
	mov r3, #1
	bl GfGfxLoader_LoadCharData
	ldr r0, _0223DA88 ; =0x00000241
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0223DA26
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x3e
	mov r1, #2
	mov r3, #1
	bl GfGfxLoader_LoadScrnData
	b _0223DA3E
_0223DA26:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x3e
	mov r1, #3
	mov r3, #1
	bl GfGfxLoader_LoadScrnData
_0223DA3E:
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0xb
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x3e
	mov r1, #1
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r3, #0xb
	str r3, [sp, #4]
	ldr r0, [r4]
	mov r1, #3
	mov r2, #0x1f
	bl LoadUserFrameGfx1
	mov r0, #0x85
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #3
	mov r2, #1
	mov r3, #0xa
	bl sub_0200CD68
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0223DA88: .word 0x00000241

	thumb_func_start ov06_0223DA8C
ov06_0223DA8C: ; 0x0223DA8C
	push {r4, lr}
	add r4, r0, #0
	bl GfGfx_EngineAGetPlanes
	mov r1, #0x8e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4]
	mov r1, #0
	bl GetBgPriority
	mov r1, #0x8d
	lsl r1, r1, #2
	strb r0, [r4, r1]
	ldr r0, [r4]
	mov r1, #1
	bl GetBgPriority
	ldr r1, _0223DB10 ; =0x00000235
	strb r0, [r4, r1]
	ldr r0, [r4]
	mov r1, #2
	bl GetBgPriority
	ldr r1, _0223DB14 ; =0x00000236
	strb r0, [r4, r1]
	ldr r0, [r4]
	mov r1, #3
	bl GetBgPriority
	ldr r1, _0223DB18 ; =0x00000237
	strb r0, [r4, r1]
	mov r0, #0
	mov r1, #3
	bl SetBgPriority
	mov r0, #1
	mov r1, #2
	bl SetBgPriority
	mov r0, #2
	mov r1, #1
	bl SetBgPriority
	mov r0, #3
	mov r1, #0
	bl SetBgPriority
	mov r0, #0
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	mov r0, #1
	add r1, r0, #0
	bl GfGfx_EngineATogglePlanes
	mov r0, #2
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	mov r0, #3
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	pop {r4, pc}
	nop
_0223DB10: .word 0x00000235
_0223DB14: .word 0x00000236
_0223DB18: .word 0x00000237

	thumb_func_start ov06_0223DB1C
ov06_0223DB1C: ; 0x0223DB1C
	push {r4, lr}
	mov r1, #0x8d
	add r4, r0, #0
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	mov r0, #0
	bl SetBgPriority
	ldr r1, _0223DB58 ; =0x00000235
	mov r0, #1
	ldrb r1, [r4, r1]
	bl SetBgPriority
	ldr r1, _0223DB5C ; =0x00000236
	mov r0, #2
	ldrb r1, [r4, r1]
	bl SetBgPriority
	ldr r1, _0223DB60 ; =0x00000237
	mov r0, #3
	ldrb r1, [r4, r1]
	bl SetBgPriority
	mov r0, #0x8e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl GfGfx_EngineASetPlanes
	pop {r4, pc}
	nop
_0223DB58: .word 0x00000235
_0223DB5C: .word 0x00000236
_0223DB60: .word 0x00000237

	thumb_func_start ov06_0223DB64
ov06_0223DB64: ; 0x0223DB64
	push {r4, r5, lr}
	sub sp, #0xc
	ldr r1, _0223DBC8 ; =0x0000023D
	add r4, r0, #0
	add r2, r1, #1
	ldrb r3, [r4, r1]
	ldrb r2, [r4, r2]
	cmp r3, r2
	beq _0223DB9E
	ldr r5, _0223DBCC ; =0x0224F358
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r4, #0
	str r0, [r3]
	add r1, #0x90
	ldr r1, [r1]
	add r0, r2, #0
	bl Camera_OffsetLookAtPosAndTarget
	ldr r0, _0223DBC8 ; =0x0000023D
	add sp, #0xc
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #3
	pop {r4, r5, pc}
_0223DB9E:
	mov r2, #0
	strb r2, [r4, r1]
	bl ov06_0223EB90
	add r0, r4, #0
	bl ov06_0223D9E8
	add r0, r4, #0
	bl ov06_0223DA8C
	add r0, r4, #0
	bl ov06_0223DBF4
	add r0, r4, #0
	mov r1, #0
	bl ov06_0223DED0
	mov r0, #4
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223DBC8: .word 0x0000023D
_0223DBCC: .word ov06_0224F358

	thumb_func_start ov06_0223DBD0
ov06_0223DBD0: ; 0x0223DBD0
	push {r3, lr}
	ldr r2, _0223DBF0 ; =0x00000241
	ldrb r0, [r0, r2]
	cmp r0, #1
	bne _0223DBDE
	add r0, r1, #0
	pop {r3, pc}
_0223DBDE:
	cmp r0, #2
	bne _0223DBEC
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	bl sub_02085FD0
	add r1, r0, #0
_0223DBEC:
	add r0, r1, #0
	pop {r3, pc}
	.align 2, 0
_0223DBF0: .word 0x00000241

	thumb_func_start ov06_0223DBF4
ov06_0223DBF4: ; 0x0223DBF4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	ldr r2, _0223DCE8 ; =0x00000241
	add r5, r0, #0
	ldrb r0, [r5, r2]
	cmp r0, #0
	bne _0223DC12
	mov r0, #0
	mov r1, #0x1a
	sub r2, #0xe9
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [sp]
	b _0223DC34
_0223DC12:
	cmp r0, #1
	bne _0223DC26
	mov r0, #0
	mov r1, #0x1a
	sub r2, #0xa
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [sp]
	b _0223DC34
_0223DC26:
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xa
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [sp]
_0223DC34:
	mov r0, #0x8b
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	mov r1, #0xb
	add r0, r0, #1
	bl ListMenuItems_New
	str r0, [r5, #0x7c]
	mov r0, #0x8b
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	mov r6, #0
	cmp r0, #0
	bls _0223DC8E
	add r4, r6, #0
_0223DC52:
	mov r1, #0x8a
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	add r0, r5, #0
	ldrh r1, [r1, r4]
	bl ov06_0223DBD0
	add r1, r0, #0
	ldr r0, [sp]
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r2, #0x8a
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	ldr r0, [r5, #0x7c]
	ldrh r2, [r2, r4]
	add r1, r7, #0
	bl ListMenuItems_AddItem
	add r0, r7, #0
	bl String_Delete
	mov r0, #0x8b
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	add r6, r6, #1
	add r4, r4, #2
	cmp r6, r0
	blo _0223DC52
_0223DC8E:
	add r1, r5, #0
	add r1, #0x88
	mov r2, #8
	add r3, r2, #0
	ldr r0, [r5, #0x7c]
	ldr r1, [r1]
	sub r3, #0xa
	bl ListMenuItems_AppendFromMsgData
	ldr r0, [sp]
	bl DestroyMsgData
	ldr r4, _0223DCEC ; =0x0224F38C
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
	ldr r0, [r5, #0x7c]
	mov r3, #0xb
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #8
	str r0, [sp, #0x10]
	mov r0, #0x8b
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	add r1, r0, #1
	add r0, sp, #4
	strh r1, [r0, #0x10]
	mov r1, #0
	add r0, r2, #0
	add r2, r1, #0
	str r5, [sp, #0x20]
	bl ListMenuInit
	str r0, [r5, #0x78]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0223DCE8: .word 0x00000241
_0223DCEC: .word ov06_0224F38C

	thumb_func_start ov06_0223DCF0
ov06_0223DCF0: ; 0x0223DCF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	mov r1, #0x13
	str r0, [sp, #0x10]
	add r6, r2, #0
	bl ListMenuGetTemplateField
	add r4, r0, #0
	cmp r6, #1
	beq _0223DD0C
	ldr r0, _0223DE28 ; =0x00000638
	bl PlaySE
_0223DD0C:
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r1, #1
	mvn r1, r1
	cmp r5, r1
	beq _0223DDB2
	ldr r2, _0223DE2C ; =0x00000241
	ldrb r0, [r4, r2]
	cmp r0, #0
	bne _0223DD3C
	mov r0, #0x82
	mov r1, #0xb
	bl String_New
	lsl r1, r5, #0x10
	lsr r1, r1, #0x10
	mov r2, #0xb
	add r6, r0, #0
	bl GetItemDescIntoString
	b _0223DD86
_0223DD3C:
	cmp r0, #1
	bne _0223DD60
	mov r0, #0
	mov r1, #0x1a
	sub r2, #0xa
	mov r3, #0xb
	bl NewMsgDataFromNarc
	add r1, r5, #0
	add r7, r0, #0
	add r1, #0x8a
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r7, #0
	bl DestroyMsgData
	b _0223DD86
_0223DD60:
	mov r0, #0
	mov r1, #0x1a
	sub r2, #0x5a
	mov r3, #0xb
	bl NewMsgDataFromNarc
	add r7, r0, #0
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	bl sub_02086060
	add r1, r0, #0
	add r0, r7, #0
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r7, #0
	bl DestroyMsgData
_0223DD86:
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0223DE30 ; =0x000F0E00
	add r2, r6, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0x18
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_Delete
	lsl r1, r5, #0x10
	add r0, r4, #0
	lsr r1, r1, #0x10
	bl ov06_0223EC3C
	b _0223DDBA
_0223DDB2:
	add r0, r4, #0
	lsr r1, r1, #0x10
	bl ov06_0223EC3C
_0223DDBA:
	add r0, r4, #0
	add r0, #0x18
	bl ScheduleWindowCopyToVram
	add r1, sp, #0x14
	ldr r0, [sp, #0x10]
	add r1, #2
	add r2, sp, #0x14
	bl ListMenuGetScrollAndRow
	add r0, sp, #0x14
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _0223DDE4
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	b _0223DDF0
_0223DDE4:
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_020200A0
_0223DDF0:
	ldr r0, [sp, #0x10]
	mov r1, #2
	bl ListMenuGetTemplateField
	cmp r0, #7
	bls _0223DE16
	add r1, sp, #0x14
	ldrh r1, [r1, #2]
	add r1, r1, #7
	cmp r0, r1
	bls _0223DE16
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_020200A0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0223DE16:
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223DE28: .word 0x00000638
_0223DE2C: .word 0x00000241
_0223DE30: .word 0x000F0E00

	thumb_func_start ov06_0223DE34
ov06_0223DE34: ; 0x0223DE34
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	mov r1, #0x13
	add r7, r2, #0
	bl ListMenuGetTemplateField
	mov r1, #1
	mvn r1, r1
	add r5, r0, #0
	cmp r4, r1
	beq _0223DEC6
	lsl r1, r4, #0x10
	lsr r1, r1, #0x10
	bl ov06_0223EA08
	str r0, [sp, #0x10]
	mov r0, #0xc
	mov r1, #0xb
	bl String_New
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #9
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	ldr r2, [sp, #0x10]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r4, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl sub_02002E14
	add r3, r0, #0
	str r7, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0223DECC ; =0x00010200
	add r5, #8
	str r0, [sp, #8]
	add r0, r5, #0
	mov r5, #0x90
	mov r1, #0
	add r2, r4, #0
	sub r3, r5, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_Delete
	add r0, r4, #0
	bl String_Delete
_0223DEC6:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0223DECC: .word 0x00010200

	thumb_func_start ov06_0223DED0
ov06_0223DED0: ; 0x0223DED0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	cmp r1, #0
	bne _0223DF1C
	add r0, #0x28
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x28
	mov r1, #1
	mov r2, #0x1f
	mov r3, #0xb
	bl DrawFrameAndWindow1
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0x12
	bl NewString_ReadMsgData
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x28
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl String_Delete
	b _0223DF30
_0223DF1C:
	mov r0, #0x50
	str r0, [sp]
	add r0, r5, #0
	mov r3, #0x10
	add r0, #0x28
	mov r1, #0xf
	mov r2, #0
	str r3, [sp, #4]
	bl FillWindowPixelRect
_0223DF30:
	mov r0, #0x10
	mov r1, #0xb
	bl String_New
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0x13
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl PlayerProfile_GetMoney
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	mov r1, #0
	mov r3, #6
	bl BufferIntegerAsString
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r4, #0
	add r2, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl sub_02002E14
	add r6, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	mov r3, #0x50
	mov r1, #0
	add r0, #0x28
	add r2, r4, #0
	sub r3, r3, r6
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl String_Delete
	add r0, r4, #0
	bl String_Delete
	add r5, #0x28
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223DFB4
ov06_0223DFB4: ; 0x0223DFB4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r2, sp, #0
	ldr r0, [r5, #0x78]
	mov r1, #0
	add r2, #2
	bl ListMenuGetScrollAndRow
	ldr r0, [r5, #0x78]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	ldr r0, [r5, #0x78]
	mov r1, #0
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r0, sp, #0
	ldrh r2, [r0]
	ldrh r0, [r0, #2]
	cmp r0, r2
	beq _0223DFF4
	mov r0, #2
	lsl r2, r2, #4
	lsl r0, r0, #8
	add r2, #0x18
	lsl r2, r2, #0x10
	ldr r0, [r5, r0]
	mov r1, #0xb0
	asr r2, r2, #0x10
	bl sub_0200C6E4
_0223DFF4:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0223E006
	add r0, r0, #1
	cmp r4, r0
	bne _0223E004
	b _0223E182
_0223E004:
	b _0223E034
_0223E006:
	mov r1, #0
	ldr r0, [r5, #0x78]
	add r2, r1, #0
	bl DestroyListMenu
	ldr r0, [r5, #0x7c]
	bl ListMenuItems_Delete
	add r0, r5, #0
	bl ov06_0223D9C0
	add r0, r5, #0
	bl ov06_0223DB1C
	ldr r0, [r5]
	mov r1, #1
	bl BgClearTilemapBufferAndCommit
	ldr r0, _0223E188 ; =0x000005DC
	bl PlaySE
	mov r0, #0xc
	pop {r3, r4, r5, pc}
_0223E034:
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02020128
	mov r1, #0x82
	lsl r1, r1, #2
	strh r0, [r5, r1]
	sub r1, #0xc
	ldr r0, [r5, r1]
	bl sub_02020128
	ldr r1, _0223E18C ; =0x0000020A
	strh r0, [r5, r1]
	sub r1, #0x12
	ldr r0, [r5, r1]
	mov r1, #0
	bl sub_020200A0
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl sub_020200A0
	add r0, r5, #0
	mov r1, #1
	bl ov06_0223ECC8
	add r0, r5, #0
	add r0, #0x58
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x18
	bl ClearWindowTilemapAndCopyToVram
	add r0, r5, #0
	add r0, #0x58
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl DrawFrameAndWindow2
	ldr r1, _0223E190 ; =0x00000242
	mov r2, #1
	strh r4, [r5, r1]
	add r0, r1, #2
	strh r2, [r5, r0]
	ldrh r1, [r5, r1]
	add r0, r5, #0
	bl ov06_0223EA08
	mov r1, #0x92
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0x3c
	ldr r0, [r5, r1]
	bl PlayerProfile_GetMoney
	mov r2, #0x92
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	cmp r0, r1
	bhs _0223E0FC
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #3
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_Delete
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, #0x1c
	add r0, r5, #0
	ldr r2, [r5, r2]
	add r0, #0x58
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r5, r1]
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_0223E0FC:
	sub r2, r2, #7
	ldrb r2, [r5, r2]
	cmp r2, #1
	bne _0223E112
	ldr r0, _0223E188 ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	bl ov06_0223E384
	pop {r3, r4, r5, pc}
_0223E112:
	bl _u32_div_f
	ldr r1, _0223E194 ; =0x00000246
	strh r0, [r5, r1]
	ldrh r0, [r5, r1]
	cmp r0, #0x63
	bls _0223E124
	mov r0, #0x63
	strh r0, [r5, r1]
_0223E124:
	ldr r1, _0223E190 ; =0x00000242
	add r0, r5, #0
	ldrh r1, [r5, r1]
	mov r2, #0
	bl ov06_0223E9BC
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #4
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_Delete
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, #0x1c
	add r0, r5, #0
	ldr r2, [r5, r2]
	add r0, #0x58
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r5, r1]
	add r0, r5, #0
	mov r1, #1
	bl ov06_0223EBF8
	ldr r0, _0223E188 ; =0x000005DC
	bl PlaySE
	mov r0, #5
	pop {r3, r4, r5, pc}
_0223E182:
	mov r0, #4
	pop {r3, r4, r5, pc}
	nop
_0223E188: .word 0x000005DC
_0223E18C: .word 0x0000020A
_0223E190: .word 0x00000242
_0223E194: .word 0x00000246

	thumb_func_start ov06_0223E198
ov06_0223E198: ; 0x0223E198
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x8f
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223E1AE
	mov r0, #5
	pop {r4, pc}
_0223E1AE:
	add r0, r4, #0
	bl ov06_0223E1D8
	add r0, r4, #0
	mov r1, #0
	bl ov06_0223E4E8
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_020200A0
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_020200A0
	mov r0, #6
	pop {r4, pc}

	thumb_func_start ov06_0223E1D8
ov06_0223E1D8: ; 0x0223E1D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r1, _0223E298 ; =0x00000241
	add r5, r0, #0
	ldrb r0, [r5, r1]
	cmp r0, #0
	bne _0223E1FA
	add r0, r1, #0
	add r1, r1, #1
	sub r0, #0x31
	ldrh r1, [r5, r1]
	ldr r0, [r5, r0]
	mov r2, #0xb
	bl Bag_GetQuantity
	add r4, r0, #0
	b _0223E214
_0223E1FA:
	cmp r0, #2
	bne _0223E212
	add r0, r1, #0
	add r1, r1, #1
	sub r0, #0x31
	ldrh r1, [r5, r1]
	ldr r0, [r5, r0]
	bl SealCase_CountSealOccurrenceAnywhere
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	b _0223E214
_0223E212:
	mov r4, #0
_0223E214:
	add r0, r5, #0
	add r0, #0x48
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x48
	mov r1, #1
	mov r2, #0x1f
	mov r3, #0xb
	bl DrawFrameAndWindow1
	mov r0, #0x18
	mov r1, #0xb
	bl String_New
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0x14
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	mov r1, #0
	add r2, r4, #0
	mov r3, #3
	bl BufferIntegerAsString
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r6, #0
	add r2, r7, #0
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x48
	add r2, r6, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl String_Delete
	add r0, r6, #0
	bl String_Delete
	add r5, #0x48
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0223E298: .word 0x00000241

	thumb_func_start ov06_0223E29C
ov06_0223E29C: ; 0x0223E29C
	push {r4, lr}
	mov r1, #0x91
	add r4, r0, #0
	lsl r1, r1, #2
	add r0, r4, r1
	add r1, r1, #2
	ldrh r1, [r4, r1]
	bl sub_02079AAC
	cmp r0, #0
	beq _0223E2C4
	ldr r0, _0223E378 ; =0x00000638
	bl PlaySE
	add r0, r4, #0
	mov r1, #1
	bl ov06_0223E4E8
	mov r0, #6
	pop {r4, pc}
_0223E2C4:
	ldr r0, _0223E37C ; =gSystem
	mov r1, #1
	ldr r2, [r0, #0x48]
	add r0, r2, #0
	tst r0, r1
	beq _0223E314
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	add r0, r4, #0
	add r0, #0x48
	mov r1, #1
	bl ClearFrameAndWindow1
	add r0, r4, #0
	add r0, #0x38
	mov r1, #1
	bl ClearFrameAndWindow1
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r0, _0223E380 ; =0x000005DC
	bl PlaySE
	add r0, r4, #0
	bl ov06_0223E384
	pop {r4, pc}
_0223E314:
	mov r0, #2
	tst r0, r2
	beq _0223E374
	add r0, r4, #0
	add r0, #0x48
	bl ClearFrameAndWindow1
	add r0, r4, #0
	add r0, #0x38
	mov r1, #1
	bl ClearFrameAndWindow1
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl ClearFrameAndWindow2
	add r0, r4, #0
	mov r1, #0
	bl ov06_0223EBF8
	mov r1, #0x7e
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0x10
	ldrh r1, [r4, r1]
	bl sub_020200A0
	mov r1, #0x7f
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0xe
	ldrh r1, [r4, r1]
	bl sub_020200A0
	add r0, r4, #0
	mov r1, #0
	bl ov06_0223ECC8
	add r4, #0x18
	add r0, r4, #0
	bl ScheduleWindowCopyToVram
	ldr r0, _0223E380 ; =0x000005DC
	bl PlaySE
	mov r0, #4
	pop {r4, pc}
_0223E374:
	mov r0, #6
	pop {r4, pc}
	.align 2, 0
_0223E378: .word 0x00000638
_0223E37C: .word gSystem
_0223E380: .word 0x000005DC

	thumb_func_start ov06_0223E384
ov06_0223E384: ; 0x0223E384
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r2, _0223E4E0 ; =0x00000241
	add r4, r0, #0
	ldrb r0, [r4, r2]
	cmp r0, #0
	bne _0223E3A8
	add r0, r2, #0
	add r1, r2, #1
	add r2, r2, #3
	sub r0, #0x31
	ldrh r1, [r4, r1]
	ldrh r2, [r4, r2]
	ldr r0, [r4, r0]
	mov r3, #0xb
	bl Bag_HasSpaceForItem
	b _0223E3D2
_0223E3A8:
	cmp r0, #1
	bne _0223E3C0
	sub r2, #0x31
	ldr r0, [r4, r2]
	bl sub_02025DB0
	cmp r0, #0xc8
	bne _0223E3BC
	mov r0, #0
	b _0223E3D2
_0223E3BC:
	mov r0, #1
	b _0223E3D2
_0223E3C0:
	add r0, r2, #0
	add r1, r2, #1
	add r2, r2, #3
	sub r0, #0x31
	ldrh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, r0]
	bl sub_02029DD4
_0223E3D2:
	cmp r0, #0
	bne _0223E450
	mov r0, #0x91
	mov r1, #0
	lsl r0, r0, #2
	strh r1, [r4, r0]
	sub r0, r0, #3
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0223E3F6
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #7
	bl NewString_ReadMsgData
	add r5, r0, #0
	b _0223E418
_0223E3F6:
	cmp r0, #1
	bne _0223E40A
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0xc
	bl NewString_ReadMsgData
	add r5, r0, #0
	b _0223E418
_0223E40A:
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0xe
	bl NewString_ReadMsgData
	add r5, r0, #0
_0223E418:
	add r0, r4, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_Delete
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r4, r2]
	sub r2, #0x1c
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0x58
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r4, r1]
	add sp, #8
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_0223E450:
	ldr r1, _0223E4E4 ; =0x00000242
	add r0, r4, #0
	ldrh r1, [r4, r1]
	mov r2, #0
	bl ov06_0223E9BC
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	mov r2, #0x91
	add r0, r4, #0
	str r1, [sp, #4]
	lsl r2, r2, #2
	add r0, #0x8c
	ldrsh r2, [r4, r2]
	ldr r0, [r0]
	mov r3, #2
	bl BufferIntegerAsString
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	mov r2, #0x92
	str r0, [sp, #4]
	lsl r2, r2, #2
	ldr r3, [r4, r2]
	sub r2, r2, #4
	add r0, r4, #0
	ldrsh r2, [r4, r2]
	add r0, #0x8c
	ldr r0, [r0]
	mul r2, r3
	mov r1, #2
	mov r3, #6
	bl BufferIntegerAsString
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #5
	bl NewString_ReadMsgData
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	bl String_Delete
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r4, r2]
	sub r2, #0x1c
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0x58
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r4, r1]
	mov r0, #7
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_0223E4E0: .word 0x00000241
_0223E4E4: .word 0x00000242

	thumb_func_start ov06_0223E4E8
ov06_0223E4E8: ; 0x0223E4E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0x38
	mov r1, #0xf
	bl FillWindowPixelBuffer
	cmp r4, #0
	bne _0223E50A
	add r0, r5, #0
	add r0, #0x38
	mov r1, #1
	mov r2, #0x1f
	mov r3, #0xb
	bl DrawFrameAndWindow1
_0223E50A:
	mov r0, #0x18
	mov r1, #0xb
	bl String_New
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0x15
	bl NewString_ReadMsgData
	mov r3, #2
	add r6, r0, #0
	mov r2, #0x91
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r2, r2, #2
	add r0, #0x8c
	ldrsh r2, [r5, r2]
	ldr r0, [r0]
	mov r1, #0
	bl BufferIntegerAsString
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r4, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r5, #0
	add r0, #0x38
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_Delete
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0x16
	bl NewString_ReadMsgData
	add r7, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r2, #0x92
	str r0, [sp, #4]
	lsl r2, r2, #2
	ldr r3, [r5, r2]
	sub r2, r2, #4
	add r0, r5, #0
	ldrsh r2, [r5, r2]
	add r0, #0x8c
	ldr r0, [r0]
	mul r2, r3
	mov r1, #0
	mov r3, #6
	bl BufferIntegerAsString
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r4, #0
	add r2, r7, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl sub_02002E14
	add r6, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	mov r3, #0x60
	mov r1, #0
	add r0, #0x38
	add r2, r4, #0
	sub r3, r3, r6
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl String_Delete
	add r0, r4, #0
	bl String_Delete
	add r5, #0x38
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0223E5E4
ov06_0223E5E4: ; 0x0223E5E4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0x8f
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223E5FE
	add sp, #4
	mov r0, #7
	pop {r3, r4, pc}
_0223E5FE:
	mov r3, #0xb
	str r3, [sp]
	ldr r0, [r4]
	ldr r1, _0223E618 ; =0x0224F348
	mov r2, #0x1f
	bl Std_CreateYesNoMenu
	add r4, #0x80
	str r0, [r4]
	mov r0, #8
	add sp, #4
	pop {r3, r4, pc}
	nop
_0223E618: .word ov06_0224F348

	thumb_func_start ov06_0223E61C
ov06_0223E61C: ; 0x0223E61C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0xb
	bl sub_020021AC
	cmp r0, #0
	beq _0223E63A
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	bne _0223E638
	b _0223E74A
_0223E638:
	b _0223E78C
_0223E63A:
	ldr r1, _0223E790 ; =0x00000241
	ldrb r0, [r5, r1]
	cmp r0, #0
	bne _0223E698
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #6
	bl NewString_ReadMsgData
	mov r2, #0x91
	lsl r2, r2, #2
	add r4, r0, #0
	ldrsh r0, [r5, r2]
	cmp r0, #1
	bne _0223E66C
	add r0, r5, #0
	sub r2, r2, #2
	add r0, #0x8c
	ldrh r2, [r5, r2]
	ldr r0, [r0]
	mov r1, #0
	bl BufferItemName
	b _0223E67C
_0223E66C:
	add r0, r5, #0
	sub r2, r2, #2
	add r0, #0x8c
	ldrh r2, [r5, r2]
	ldr r0, [r0]
	mov r1, #0
	bl BufferItemNamePlural
_0223E67C:
	ldr r0, _0223E794 ; =0x00000242
	mov r1, #5
	ldrh r0, [r5, r0]
	mov r2, #0xb
	bl GetItemAttr
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	mov r1, #1
	bl BufferPocketName
	b _0223E704
_0223E698:
	cmp r0, #1
	bne _0223E6B8
	add r1, r1, #1
	ldrh r1, [r5, r1]
	add r0, r5, #0
	mov r2, #0
	bl ov06_0223E9BC
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0xb
	bl NewString_ReadMsgData
	add r4, r0, #0
	b _0223E704
_0223E6B8:
	add r0, r1, #3
	ldrsh r0, [r5, r0]
	cmp r0, #1
	bne _0223E6DC
	add r0, r1, #1
	ldrh r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02085FD0
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	mov r1, #0
	bl BufferSealName
	b _0223E6F6
_0223E6DC:
	add r0, r1, #1
	ldrh r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02085FD0
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	mov r1, #0
	bl BufferSealNamePlural
_0223E6F6:
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0xd
	bl NewString_ReadMsgData
	add r4, r0, #0
_0223E704:
	add r0, r5, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_Delete
	add r0, r5, #0
	add r0, #0x58
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, #0x1c
	add r0, r5, #0
	ldr r2, [r5, r2]
	add r0, #0x58
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r5, r1]
	ldr r0, _0223E798 ; =0x00000644
	bl PlaySE
	mov r0, #9
	pop {r3, r4, r5, pc}
_0223E74A:
	add r0, r5, #0
	add r0, #0x58
	mov r1, #0
	bl ClearFrameAndWindow2
	add r0, r5, #0
	mov r1, #0
	bl ov06_0223EBF8
	mov r1, #0x7e
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, #0x10
	ldrh r1, [r5, r1]
	bl sub_020200A0
	mov r1, #0x7f
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, #0xe
	ldrh r1, [r5, r1]
	bl sub_020200A0
	add r0, r5, #0
	mov r1, #0
	bl ov06_0223ECC8
	add r5, #0x18
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
	mov r0, #4
	pop {r3, r4, r5, pc}
_0223E78C:
	mov r0, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223E790: .word 0x00000241
_0223E794: .word 0x00000242
_0223E798: .word 0x00000644

	thumb_func_start ov06_0223E79C
ov06_0223E79C: ; 0x0223E79C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0x8f
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223E7B2
	mov r0, #9
	pop {r3, r4, r5, pc}
_0223E7B2:
	ldr r2, _0223E854 ; =0x00000241
	ldrb r0, [r4, r2]
	cmp r0, #0
	bne _0223E7D0
	add r0, r2, #0
	add r1, r2, #1
	add r2, r2, #3
	sub r0, #0x31
	ldrh r1, [r4, r1]
	ldrh r2, [r4, r2]
	ldr r0, [r4, r0]
	mov r3, #0xb
	bl Bag_AddItem
	b _0223E7F6
_0223E7D0:
	cmp r0, #1
	bne _0223E7E4
	add r0, r2, #0
	add r1, r2, #1
	sub r0, #0x31
	ldrh r1, [r4, r1]
	ldr r0, [r4, r0]
	bl sub_02025D6C
	b _0223E7F6
_0223E7E4:
	add r0, r2, #0
	add r1, r2, #1
	add r2, r2, #3
	sub r0, #0x31
	ldrh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, r0]
	bl sub_02029D44
_0223E7F6:
	mov r2, #0x83
	lsl r2, r2, #2
	add r1, r2, #0
	ldr r0, [r4, r2]
	add r1, #0x3c
	add r2, #0x38
	ldr r3, [r4, r1]
	ldrsh r1, [r4, r2]
	mul r1, r3
	bl PlayerProfile_SubMoney
	mov r3, #0x87
	lsl r3, r3, #2
	add r2, r3, #0
	ldr r0, [r4, r3]
	add r2, #0x2c
	add r3, #0x28
	ldr r5, [r4, r2]
	ldrsh r2, [r4, r3]
	mov r1, #0x23
	mul r2, r5
	bl GameStats_Add
	add r0, r4, #0
	mov r1, #1
	bl ov06_0223DED0
	mov r1, #0x91
	lsl r1, r1, #2
	ldrsh r0, [r4, r1]
	cmp r0, #1
	ble _0223E83E
	mov r2, #2
	sub r0, r1, #5
	strb r2, [r4, r0]
	b _0223E850
_0223E83E:
	sub r0, r1, #5
	ldrb r0, [r4, r0]
	cmp r0, #0xff
	beq _0223E850
	sub r0, r1, #5
	ldrb r0, [r4, r0]
	add r2, r0, #1
	sub r0, r1, #5
	strb r2, [r4, r0]
_0223E850:
	mov r0, #0xa
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223E854: .word 0x00000241

	thumb_func_start ov06_0223E858
ov06_0223E858: ; 0x0223E858
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x8f
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223E86E
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_0223E86E:
	ldr r0, _0223E948 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0223E944
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	cmp r1, #1
	bne _0223E88A
	sub r0, r0, #4
	ldr r0, [r5, r0]
	bl sub_0205F6E8
_0223E88A:
	ldr r1, _0223E94C ; =0x00000241
	ldrb r0, [r5, r1]
	cmp r0, #0
	bne _0223E902
	add r0, r1, #1
	ldrh r0, [r5, r0]
	cmp r0, #4
	bne _0223E902
	add r0, r1, #3
	ldrsh r0, [r5, r0]
	cmp r0, #0xa
	blt _0223E902
	sub r1, #0x31
	ldr r0, [r5, r1]
	mov r1, #0xc
	mov r2, #1
	mov r3, #0xb
	bl Bag_AddItem
	cmp r0, #1
	bne _0223E902
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0xa
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_Delete
	add r0, r5, #0
	add r0, #0x58
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, #0x1c
	add r0, r5, #0
	ldr r2, [r5, r2]
	add r0, #0x58
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r5, r1]
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_0223E902:
	add r0, r5, #0
	add r0, #0x58
	mov r1, #0
	bl ClearFrameAndWindow2
	add r0, r5, #0
	mov r1, #0
	bl ov06_0223EBF8
	mov r1, #0x7e
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, #0x10
	ldrh r1, [r5, r1]
	bl sub_020200A0
	mov r1, #0x7f
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	add r1, #0xe
	ldrh r1, [r5, r1]
	bl sub_020200A0
	add r0, r5, #0
	mov r1, #0
	bl ov06_0223ECC8
	add r5, #0x18
	add r0, r5, #0
	bl ScheduleWindowCopyToVram
	mov r0, #4
	pop {r3, r4, r5, pc}
_0223E944:
	mov r0, #0xa
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223E948: .word gSystem
_0223E94C: .word 0x00000241

	thumb_func_start ov06_0223E950
ov06_0223E950: ; 0x0223E950
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x8f
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223E966
	mov r0, #0xb
	pop {r4, pc}
_0223E966:
	ldr r0, _0223E9B8 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0223E9B2
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl ClearFrameAndWindow2
	add r0, r4, #0
	mov r1, #0
	bl ov06_0223EBF8
	mov r1, #0x7e
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0x10
	ldrh r1, [r4, r1]
	bl sub_020200A0
	mov r1, #0x7f
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r1, #0xe
	ldrh r1, [r4, r1]
	bl sub_020200A0
	add r0, r4, #0
	mov r1, #0
	bl ov06_0223ECC8
	add r4, #0x18
	add r0, r4, #0
	bl ScheduleWindowCopyToVram
	mov r0, #4
	pop {r4, pc}
_0223E9B2:
	mov r0, #0xb
	pop {r4, pc}
	nop
_0223E9B8: .word gSystem

	thumb_func_start ov06_0223E9BC
ov06_0223E9BC: ; 0x0223E9BC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, _0223EA04 ; =0x00000241
	add r3, r1, #0
	ldrb r0, [r4, r0]
	add r5, r2, #0
	cmp r0, #0
	bne _0223E9DA
	add r4, #0x8c
	ldr r0, [r4]
	add r1, r5, #0
	add r2, r3, #0
	bl BufferItemName
	pop {r3, r4, r5, pc}
_0223E9DA:
	cmp r0, #1
	bne _0223E9EC
	add r4, #0x8c
	ldr r0, [r4]
	add r1, r5, #0
	add r2, r3, #0
	bl BufferDecorationName
	pop {r3, r4, r5, pc}
_0223E9EC:
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	bl sub_02085FD0
	add r4, #0x8c
	add r2, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	bl BufferSealName
	pop {r3, r4, r5, pc}
	nop
_0223EA04: .word 0x00000241

	thumb_func_start ov06_0223EA08
ov06_0223EA08: ; 0x0223EA08
	push {r3, lr}
	ldr r2, _0223EA34 ; =0x00000241
	ldrb r0, [r0, r2]
	cmp r0, #0
	bne _0223EA1E
	add r0, r1, #0
	mov r1, #0
	mov r2, #0xb
	bl GetItemAttr
	pop {r3, pc}
_0223EA1E:
	cmp r0, #1
	bne _0223EA2A
	add r0, r1, #0
	bl sub_0204CAE0
	pop {r3, pc}
_0223EA2A:
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	bl sub_0208603C
	pop {r3, pc}
	.align 2, 0
_0223EA34: .word 0x00000241

	thumb_func_start ov06_0223EA38
ov06_0223EA38: ; 0x0223EA38
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _0223EAFC ; =0x0000023D
	add r5, r1, #0
	add r1, r0, #1
	ldrb r2, [r5, r0]
	ldrb r1, [r5, r1]
	cmp r2, r1
	beq _0223EA74
	ldr r4, _0223EB00 ; =0x0224F364
	add r3, sp, #0
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	add r1, r5, #0
	str r0, [r3]
	add r1, #0x90
	ldr r1, [r1]
	add r0, r2, #0
	bl Camera_OffsetLookAtPosAndTarget
	ldr r0, _0223EAFC ; =0x0000023D
	add sp, #0xc
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	mov r0, #0xc
	pop {r4, r5, pc}
_0223EA74:
	mov r1, #0
	strb r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	ldr r1, [r4, #0x20]
	bl Camera_Copy
	add r0, r5, #0
	add r0, #0x90
	ldr r0, [r0]
	bl Camera_Delete
	ldr r0, [r4, #0x20]
	bl Camera_SetStaticPtr
	add r0, r5, #0
	bl ov06_0223EBD4
	add r1, r5, #0
	ldr r0, [r4, #8]
	add r1, #0x18
	mov r2, #3
	bl sub_020545B8
	mov r1, #0x85
	lsl r1, r1, #2
	add r0, r5, #0
	ldr r1, [r5, r1]
	add r0, #0x18
	bl sub_02054608
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #2
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_Delete
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, #0x1c
	add r0, r5, #0
	ldr r2, [r5, r2]
	add r0, #0x18
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r5, r1]
	mov r0, #0xd
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0223EAFC: .word 0x0000023D
_0223EB00: .word ov06_0224F364

	thumb_func_start ov06_0223EB04
ov06_0223EB04: ; 0x0223EB04
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x8f
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223EB1A
	mov r0, #0xd
	pop {r4, pc}
_0223EB1A:
	add r0, r4, #0
	add r0, #0x18
	bl RemoveWindow
	add r0, r4, #0
	bl ov06_0223D63C
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov06_0223EB2C
ov06_0223EB2C: ; 0x0223EB2C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #1
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r4, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_Delete
	add r1, r4, #0
	ldr r0, [r5, #8]
	add r1, #0x18
	mov r2, #3
	bl sub_020545B8
	mov r1, #0x85
	lsl r1, r1, #2
	add r0, r4, #0
	ldr r1, [r4, r1]
	add r0, #0x18
	bl sub_02054608
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r4, r2]
	sub r2, #0x1c
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0x18
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r4, r1]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0223EB90
ov06_0223EB90: ; 0x0223EB90
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _0223EBCC ; =0x0224F370
	add r5, r0, #0
	add r0, #0x94
	mov r2, #4
	mov r3, #0xb
	bl ov05_021D9320
	add r7, r5, #0
	ldr r4, _0223EBD0 ; =0x0224F3DC
	mov r6, #0
	add r7, #0x94
_0223EBA8:
	add r0, r7, #0
	add r1, r4, #0
	bl ov05_021D9510
	mov r1, #0x7e
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r6, r6, #1
	add r4, #0x28
	add r5, r5, #4
	cmp r6, #4
	blo _0223EBA8
	mov r0, #0x10
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223EBCC: .word ov06_0224F370
_0223EBD0: .word ov06_0224F3DC

	thumb_func_start ov06_0223EBD4
ov06_0223EBD4: ; 0x0223EBD4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r6, #0x7e
	mov r4, #0
	add r5, r7, #0
	lsl r6, r6, #2
_0223EBE0:
	ldr r0, [r5, r6]
	bl sub_0201FFC8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blo _0223EBE0
	add r7, #0x94
	add r0, r7, #0
	bl ov05_021D94B4
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223EBF8
ov06_0223EBF8: ; 0x0223EBF8
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	bne _0223EC1E
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xb1
	mov r2, #8
	bl sub_0200C6E4
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xb1
	mov r2, #0x84
	bl sub_0200C6E4
	pop {r4, pc}
_0223EC1E:
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xa2
	mov r2, #0x6c
	bl sub_0200C6E4
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xa2
	mov r2, #0x84
	bl sub_0200C6E4
	pop {r4, pc}

	thumb_func_start ov06_0223EC3C
ov06_0223EC3C: ; 0x0223EC3C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _0223ECC4 ; =0x00000241
	add r6, r1, #0
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _0223EC5A
	sub r0, #0x3d
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	add sp, #8
	pop {r4, r5, r6, pc}
_0223EC5A:
	sub r0, #0x7d
	ldr r0, [r4, r0]
	mov r1, #2
	bl sub_020094F0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #1
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r5, #0
	mov r2, #0x10
	bl sub_020090FC
	add r0, r5, #0
	bl sub_02009BE8
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_020094F0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #2
	bl GetItemIndexMapping
	add r3, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r5, #0
	mov r2, #0x10
	bl sub_02009168
	add r0, r5, #0
	bl sub_02009DE0
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223ECC4: .word 0x00000241

	thumb_func_start ov06_0223ECC8
ov06_0223ECC8: ; 0x0223ECC8
	mov r2, #2
	lsl r2, r2, #8
	ldr r3, _0223ECD4 ; =sub_0200C664
	ldr r0, [r0, r2]
	bx r3
	nop
_0223ECD4: .word sub_0200C664

	thumb_func_start ov06_0223ECD8
ov06_0223ECD8: ; 0x0223ECD8
	push {r4, lr}
	mov r0, #0
	add r4, r1, #0
	bl ov05_021D7CA4
	ldr r0, _0223ECEC ; =0x0000022F
	mov r1, #0xf
	strb r1, [r4, r0]
	pop {r4, pc}
	nop
_0223ECEC: .word 0x0000022F

	thumb_func_start ov06_0223ECF0
ov06_0223ECF0: ; 0x0223ECF0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl IsPaletteFadeFinished
	cmp r0, #0
	beq _0223ED46
	add r0, r6, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r6, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	bl ov06_0223D7B8
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	ldr r1, _0223ED48 ; =0x0224F47C
	mov r2, #0xb
	bl Bag_CreateView
	add r3, r5, #0
	str r0, [r4, #4]
	add r3, #0x94
	ldr r1, [r5, #0xc]
	ldr r3, [r3]
	mov r2, #2
	bl sub_0206E314
	ldr r1, [r4, #4]
	add r0, r5, #0
	bl sub_0203781C
	ldr r1, _0223ED4C ; =sub_0208A258
	add r0, r6, #0
	add r2, r4, #0
	bl TaskManager_Jump
	ldr r0, _0223ED50 ; =0x0000022F
	mov r1, #0x10
	strb r1, [r4, r0]
_0223ED46:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223ED48: .word ov06_0224F47C
_0223ED4C: .word sub_0208A258
_0223ED50: .word 0x0000022F

	thumb_func_start ov06_0223ED54
ov06_0223ED54: ; 0x0223ED54
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl IsPaletteFadeFinished
	cmp r0, #0
	bne _0223ED66
	mov r0, #0x12
	pop {r3, r4, r5, pc}
_0223ED66:
	add r1, r5, #0
	ldr r0, [r4, #8]
	add r1, #0x18
	mov r2, #3
	bl sub_020545B8
	mov r1, #0x85
	lsl r1, r1, #2
	add r0, r5, #0
	ldr r1, [r5, r1]
	add r0, #0x18
	bl sub_02054608
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #2
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0x23
	add r0, #0x8c
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_Delete
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, #0x1c
	add r0, r5, #0
	ldr r2, [r5, r2]
	add r0, #0x18
	mov r3, #1
	bl sub_02054658
	mov r1, #0x8f
	lsl r1, r1, #2
	strb r0, [r5, r1]
	mov r0, #0xd
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0223EDC4
ov06_0223EDC4: ; 0x0223EDC4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _0223EE70 ; =0x02252420
	add r4, r1, #0
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223EDE6
	ldr r0, _0223EE70 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_0201BD7C
_0223EDE6:
	cmp r4, #0
	beq _0223EE08
	ldr r0, _0223EE70 ; =0x02252420
	add r1, r5, #0
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #0x10]
	bl ReadMsgDataIntoString
	ldr r0, _0223EE70 ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x58]
	ldr r1, [r2, #0x14]
	ldr r2, [r2, #0x10]
	bl StringExpandPlaceholders
	b _0223EE16
_0223EE08:
	ldr r0, _0223EE70 ; =0x02252420
	add r1, r5, #0
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #0x14]
	bl ReadMsgDataIntoString
_0223EE16:
	ldr r0, _0223EE70 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x40
	bl WindowIsInUse
	cmp r0, #0
	bne _0223EE34
	ldr r0, _0223EE70 ; =0x02252420
	mov r2, #3
	ldr r1, [r0]
	ldr r0, [r1, #0x68]
	add r1, #0x40
	ldr r0, [r0, #8]
	bl sub_020545B8
_0223EE34:
	ldr r0, _0223EE70 ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x68]
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	add r1, r0, #0
	ldr r0, _0223EE70 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x40
	bl sub_02054608
	ldr r0, _0223EE70 ; =0x02252420
	ldr r4, [r0]
	ldr r0, [r4, #0x68]
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	add r2, r0, #0
	add r0, r4, #0
	ldr r1, [r4, #0x14]
	add r0, #0x40
	mov r3, #1
	bl sub_02054658
	ldr r1, _0223EE70 ; =0x02252420
	ldr r1, [r1]
	add r1, #0x94
	strb r0, [r1]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223EE70: .word ov06_02252420

	thumb_func_start ov06_0223EE74
ov06_0223EE74: ; 0x0223EE74
	push {r0, r1, r2, r3}
	push {r3, r4, lr}
	sub sp, #0x34
	ldr r0, _0223EF10 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x20
	bl WindowIsInUse
	cmp r0, #0
	bne _0223EEB8
	ldr r0, _0223EF10 ; =0x02252420
	add r3, sp, #0x60
	ldr r1, [r0]
	add r0, sp, #0x64
	ldrb r0, [r0]
	ldrb r3, [r3]
	mov r2, #3
	str r0, [sp]
	add r0, sp, #0x68
	ldrb r0, [r0]
	str r0, [sp, #4]
	add r0, sp, #0x6c
	ldrb r0, [r0]
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	add r0, sp, #0x40
	ldrh r0, [r0, #0x30]
	str r0, [sp, #0x10]
	ldr r0, [r1, #0x68]
	add r1, #0x20
	ldr r0, [r0, #8]
	bl AddWindowParameterized
_0223EEB8:
	ldr r0, _0223EF10 ; =0x02252420
	ldr r2, _0223EF14 ; =0x000003D9
	ldr r0, [r0]
	mov r1, #1
	add r0, #0x20
	mov r3, #0xb
	bl DrawFrameAndWindow1
	add r4, sp, #0x40
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, _0223EF10 ; =0x02252420
	mov r3, #4
	ldr r1, [r0]
	ldr r0, [r1, #0x64]
	add r1, #0x20
	str r1, [sp, #0x20]
	str r0, [sp, #0x14]
	mov r1, #0
	add r0, r2, #0
	add r2, r1, #0
	bl ListMenuInit
	ldr r1, _0223EF10 ; =0x02252420
	ldr r2, [r1]
	str r0, [r2, #0x5c]
	ldr r0, [r1]
	add r0, #0x20
	bl CopyWindowToVram
	add sp, #0x34
	pop {r3, r4}
	pop {r3}
	add sp, #0x10
	bx r3
	nop
_0223EF10: .word ov06_02252420
_0223EF14: .word 0x000003D9

	thumb_func_start ov06_0223EF18
ov06_0223EF18: ; 0x0223EF18
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, _0223EFF4 ; =0x02252420
	ldr r0, [r0]
	cmp r0, #0
	beq _0223EF28
	bl GF_AssertFail
_0223EF28:
	mov r0, #4
	mov r1, #0x9c
	bl AllocFromHeap
	ldr r1, _0223EFF4 ; =0x02252420
	mov r2, #0x9c
	str r0, [r1]
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, _0223EFF4 ; =0x02252420
	mov r2, #0
	ldr r1, [r0]
	mov r3, #4
	add r1, #0x88
	str r2, [r1]
	ldr r1, [r0]
	str r4, [r1, #0x68]
	ldr r0, [r0]
	mov r1, #0x1a
	add r0, #0x97
	strb r2, [r0]
	ldr r2, _0223EFF8 ; =0x0000013A
	mov r0, #1
	bl NewMsgDataFromNarc
	ldr r1, _0223EFF4 ; =0x02252420
	ldr r2, [r1]
	str r0, [r2, #0x74]
	ldr r0, [r1]
	ldr r0, [r0, #0x68]
	bl FieldSystem_GetSaveData
	bl Save_PlayerData_GetProfileAddr
	ldr r1, _0223EFF4 ; =0x02252420
	ldr r1, [r1]
	str r0, [r1, #0x78]
	mov r0, #4
	bl PlayerProfile_New
	ldr r1, _0223EFF4 ; =0x02252420
	ldr r2, [r1]
	str r0, [r2, #0x7c]
	ldr r0, [r1]
	add r0, #0x20
	bl InitWindow
	ldr r0, _0223EFF4 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x30
	bl InitWindow
	ldr r0, _0223EFF4 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x40
	bl InitWindow
	mov r0, #4
	bl MessageFormat_New
	ldr r1, _0223EFF4 ; =0x02252420
	ldr r1, [r1]
	str r0, [r1, #0x50]
	mov r0, #4
	bl MessageFormat_New
	ldr r1, _0223EFF4 ; =0x02252420
	ldr r1, [r1]
	str r0, [r1, #0x54]
	mov r0, #4
	bl MessageFormat_New
	ldr r1, _0223EFF4 ; =0x02252420
	ldr r2, [r1]
	str r0, [r2, #0x58]
	ldr r0, [r1]
	mov r2, #0
	add r0, #0x98
	strb r2, [r0]
	add r5, r2, #0
_0223EFCA:
	ldr r0, [r1]
	add r0, r0, r2
	add r0, #0x80
	add r2, r2, #1
	strb r5, [r0]
	cmp r2, #8
	blt _0223EFCA
	ldr r6, _0223EFF4 ; =0x02252420
	add r4, r5, #0
	mov r7, #0x8c
_0223EFDE:
	add r0, r7, #0
	mov r1, #4
	bl String_New
	ldr r1, [r6]
	add r5, r5, #1
	str r0, [r1, r4]
	add r4, r4, #4
	cmp r5, #8
	blt _0223EFDE
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223EFF4: .word ov06_02252420
_0223EFF8: .word 0x0000013A

	thumb_func_start ov06_0223EFFC
ov06_0223EFFC: ; 0x0223EFFC
	push {r4, r5, r6, lr}
	mov r4, #0
	ldr r6, _0223F08C ; =0x02252420
	add r5, r4, #0
_0223F004:
	ldr r0, [r6]
	ldr r0, [r0, r5]
	bl String_Delete
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _0223F004
	ldr r0, _0223F08C ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x7c]
	bl FreeToHeap
	ldr r0, _0223F08C ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x50]
	cmp r0, #0
	beq _0223F034
	bl MessageFormat_Delete
	ldr r0, _0223F08C ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x50]
_0223F034:
	ldr r0, _0223F08C ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	cmp r0, #0
	beq _0223F04A
	bl MessageFormat_Delete
	ldr r0, _0223F08C ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x54]
_0223F04A:
	ldr r0, _0223F08C ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x58]
	cmp r0, #0
	beq _0223F060
	bl MessageFormat_Delete
	ldr r0, _0223F08C ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x58]
_0223F060:
	ldr r0, _0223F08C ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x74]
	bl DestroyMsgData
	ldr r0, _0223F08C ; =0x02252420
	ldr r0, [r0]
	ldr r1, [r0, #0x4c]
	cmp r1, #0
	beq _0223F07A
	add r0, #0x40
	bl RemoveWindow
_0223F07A:
	ldr r0, _0223F08C ; =0x02252420
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, _0223F08C ; =0x02252420
	mov r1, #0
	str r1, [r0]
	pop {r4, r5, r6, pc}
	nop
_0223F08C: .word ov06_02252420

	thumb_func_start ov06_0223F090
ov06_0223F090: ; 0x0223F090
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02240778
	add r2, r0, #0
	ldr r0, [r4, #0x68]
	add r4, #0x91
	ldrb r1, [r4]
	bl sub_0204FEF0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223F0A8
ov06_0223F0A8: ; 0x0223F0A8
	push {r3, lr}
	ldr r0, _0223F0C0 ; =0x02252420
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x98
	strb r1, [r0]
	cmp r2, #0
	bne _0223F0BE
	ldr r0, _0223F0C4 ; =0x000005DC
	bl PlaySE
_0223F0BE:
	pop {r3, pc}
	.align 2, 0
_0223F0C0: .word ov06_02252420
_0223F0C4: .word 0x000005DC

	thumb_func_start ov06_0223F0C8
ov06_0223F0C8: ; 0x0223F0C8
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #3
	add r5, r0, #0
	mov r4, #0
	bl ListMenuGetTemplateField
	cmp r0, #0
	bls _0223F0F6
	add r6, r4, #0
	mov r7, #3
_0223F0DC:
	lsl r2, r4, #0x18
	add r0, r5, #0
	add r1, r6, #0
	lsr r2, r2, #0x18
	bl ov06_0223F0F8
	add r0, r5, #0
	add r1, r7, #0
	add r4, r4, #1
	bl ListMenuGetTemplateField
	cmp r4, r0
	blo _0223F0DC
_0223F0F6:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0223F0F8
ov06_0223F0F8: ; 0x0223F0F8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r2, #0
	bl sub_0202E810
	add r4, r0, #0
	mov r2, #0
	add r0, sp, #0xc
	strh r2, [r0]
	ldr r0, _0223F26C ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x5c]
	cmp r0, #0
	beq _0223F11A
	add r1, sp, #0xc
	bl ListMenuGetScrollAndRow
_0223F11A:
	add r0, sp, #0xc
	ldrh r1, [r0]
	add r1, r1, r5
	strh r1, [r0]
	ldr r0, _0223F26C ; =0x02252420
	lsl r5, r5, #4
	ldr r0, [r0]
	add r0, #0x20
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r0, #8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	ldr r0, _0223F26C ; =0x02252420
	lsl r3, r5, #0x10
	ldr r0, [r0]
	mov r1, #0xf
	add r0, #0x20
	mov r2, #8
	lsr r3, r3, #0x10
	bl FillWindowPixelRect
	add r0, sp, #0xc
	ldrh r2, [r0]
	cmp r2, r4
	bge _0223F21C
	ldr r1, _0223F26C ; =0x02252420
	add r0, r2, #0
	ldr r1, [r1]
	ldr r1, [r1, #0x7c]
	bl sub_0202E9AC
	mov r3, #2
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0223F26C ; =0x02252420
	add r2, sp, #0xc
	ldr r0, [r0]
	ldrh r2, [r2]
	ldr r0, [r0, #0x50]
	mov r1, #0
	add r2, r2, #1
	bl BufferIntegerAsString
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #1
	ldr r2, [r0]
	ldr r0, [r2, #0x50]
	ldr r2, [r2, #0x7c]
	bl BufferPlayersName
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #0x31
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #4]
	bl ReadMsgDataIntoString
	ldr r0, _0223F26C ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x50]
	ldmia r2!, {r1, r2}
	bl StringExpandPlaceholders
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #0
	ldr r2, [r0]
	mov r0, #0xff
	str r5, [sp]
	str r0, [sp, #4]
	add r0, r2, #0
	str r1, [sp, #8]
	ldr r2, [r2]
	add r0, #0x20
	mov r3, #8
	bl AddTextPrinterParameterized
	ldr r0, _0223F26C ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x7c]
	bl PlayerProfile_GetTrainerID
	add r2, r0, #0
	mov r1, #2
	lsl r2, r2, #0x10
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0223F26C ; =0x02252420
	lsr r2, r2, #0x10
	ldr r0, [r0]
	mov r3, #5
	ldr r0, [r0, #0x50]
	bl BufferIntegerAsString
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #0x33
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #0xc]
	bl ReadMsgDataIntoString
	ldr r0, _0223F26C ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x50]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0xc]
	bl StringExpandPlaceholders
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #0
	ldr r2, [r0]
	mov r0, #0xff
	str r5, [sp]
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r2, #0
	ldr r2, [r2, #8]
	add r0, #0x20
	mov r3, #0x58
	bl AddTextPrinterParameterized
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0223F21C:
	mov r3, #2
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	add r2, r2, #1
	ldr r0, [r0, #0x50]
	bl BufferIntegerAsString
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #0x32
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #4]
	bl ReadMsgDataIntoString
	ldr r0, _0223F26C ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x50]
	ldmia r2!, {r1, r2}
	bl StringExpandPlaceholders
	ldr r0, _0223F26C ; =0x02252420
	mov r1, #0
	ldr r2, [r0]
	mov r0, #0xff
	str r5, [sp]
	str r0, [sp, #4]
	add r0, r2, #0
	str r1, [sp, #8]
	ldr r2, [r2]
	add r0, #0x20
	mov r3, #8
	bl AddTextPrinterParameterized
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_0223F26C: .word ov06_02252420

	thumb_func_start ov06_0223F270
ov06_0223F270: ; 0x0223F270
	push {r4, lr}
	sub sp, #0x58
	add r4, r0, #0
	ldr r0, _0223F330 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x30
	bl WindowIsInUse
	cmp r0, #0
	bne _0223F2AA
	ldr r0, _0223F330 ; =0x02252420
	mov r2, #3
	ldr r1, [r0]
	mov r0, #2
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xc9
	str r0, [sp, #0x10]
	ldr r0, [r1, #0x68]
	add r1, #0x30
	ldr r0, [r0, #8]
	mov r3, #0x17
	bl AddWindowParameterized
_0223F2AA:
	ldr r0, _0223F330 ; =0x02252420
	ldr r2, _0223F334 ; =0x000003D9
	ldr r0, [r0]
	mov r1, #1
	add r0, #0x30
	mov r3, #0xb
	bl DrawFrameAndWindow1
	ldr r0, _0223F330 ; =0x02252420
	mov r1, #0xf
	ldr r0, [r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r0, _0223F330 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x30
	bl CopyWindowToVram
	add r0, r4, #0
	mov r1, #1
	add r0, #0x97
	strb r1, [r0]
	ldr r0, _0223F338 ; =ov06_0223FAA4
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	ldr r0, _0223F330 ; =0x02252420
	ldr r0, [r0]
	bl ov06_0223F344
	ldr r4, _0223F33C ; =0x0224F5E0
	add r3, sp, #0x14
	mov r2, #8
_0223F2F0:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223F2F0
	ldr r0, [r4]
	str r0, [r3]
	ldr r0, _0223F330 ; =0x02252420
	ldr r1, [r0]
	add r0, r1, #0
	add r0, #0x91
	ldrb r0, [r0]
	cmp r0, #8
	bne _0223F318
	add r1, #0x92
	ldrb r0, [r1]
	mov r1, #0
	add r0, #0x59
	bl ov06_0223EDC4
	b _0223F324
_0223F318:
	lsl r1, r0, #2
	add r0, sp, #0x14
	ldr r0, [r0, r1]
	mov r1, #0
	bl ov06_0223EDC4
_0223F324:
	ldr r0, _0223F340 ; =ov06_0223F3B8
	bl ov06_0223F8BC
	add sp, #0x58
	pop {r4, pc}
	nop
_0223F330: .word ov06_02252420
_0223F334: .word 0x000003D9
_0223F338: .word ov06_0223FAA4
_0223F33C: .word ov06_0224F5E0
_0223F340: .word ov06_0223F3B8

	thumb_func_start ov06_0223F344
ov06_0223F344: ; 0x0223F344
	push {lr}
	sub sp, #0xc
	ldr r0, _0223F3B4 ; =0x02252420
	mov r1, #0
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r2, [r2, #0x78]
	bl BufferPlayersName
	ldr r0, _0223F3B4 ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x78]
	bl PlayerProfile_GetTrainerID
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r1, #1
	lsl r2, r2, #0x10
	ldr r0, _0223F3B4 ; =0x02252420
	str r1, [sp, #4]
	ldr r0, [r0]
	lsr r2, r2, #0x10
	ldr r0, [r0, #0x54]
	mov r3, #5
	bl BufferIntegerAsString
	ldr r0, _0223F3B4 ; =0x02252420
	mov r1, #0x30
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #0x18]
	bl ReadMsgDataIntoString
	ldr r0, _0223F3B4 ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r1, [r2, #0x1c]
	ldr r2, [r2, #0x18]
	bl StringExpandPlaceholders
	ldr r0, _0223F3B4 ; =0x02252420
	mov r3, #2
	ldr r2, [r0]
	mov r1, #0
	str r3, [sp]
	str r1, [sp, #4]
	add r0, r2, #0
	str r1, [sp, #8]
	ldr r2, [r2, #0x1c]
	add r0, #0x30
	bl AddTextPrinterParameterized
	add sp, #0xc
	pop {pc}
	nop
_0223F3B4: .word ov06_02252420

	thumb_func_start ov06_0223F3B8
ov06_0223F3B8: ; 0x0223F3B8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	ldr r0, _0223F454 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0223F450
	mov r0, #0x10
	mov r1, #4
	bl ListMenuItems_New
	ldr r4, _0223F454 ; =0x02252420
	mov r5, #0
	ldr r1, [r4]
	mov r6, #2
	str r0, [r1, #0x64]
	mov r7, #1
_0223F3E0:
	str r6, [sp]
	str r7, [sp, #4]
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0, #0x50]
	add r2, r5, #1
	add r3, r6, #0
	bl BufferIntegerAsString
	ldr r2, [r4]
	mov r1, #0x32
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #4]
	bl ReadMsgDataIntoString
	ldr r2, [r4]
	ldr r0, [r2, #0x50]
	ldmia r2!, {r1, r2}
	bl StringExpandPlaceholders
	ldr r1, [r4]
	mov r2, #0
	ldr r0, [r1, #0x64]
	ldr r1, [r1]
	bl ListMenuItems_AddItem
	add r5, r5, #1
	cmp r5, #0x10
	blt _0223F3E0
	mov r1, #1
	str r1, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0x14]
	mov r0, #0x14
	str r0, [sp, #0x18]
	mov r0, #0xa
	mov r4, sp
	str r0, [sp, #0x1c]
	sub r4, #0x10
	ldr r3, _0223F458 ; =0x0224F4B0
	str r1, [sp, #0x20]
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r4!, {r0, r1, r2, r3}
	bl ov06_0223EE74
	ldr r0, _0223F45C ; =ov06_0223F460
	bl ov06_0223F8BC
_0223F450:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223F454: .word ov06_02252420
_0223F458: .word ov06_0224F4B0
_0223F45C: .word ov06_0223F460

	thumb_func_start ov06_0223F460
ov06_0223F460: ; 0x0223F460
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl ov06_0223F344
	bl sub_020311F0
	cmp r0, #0
	beq _0223F48C
	ldr r0, _0223F518 ; =0x02252420
	mov r1, #3
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
	bl ov06_0223F8B4
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	pop {r3, r4, r5, pc}
_0223F48C:
	bl sub_0202E878
	cmp r0, #0
	beq _0223F49A
	mov r0, #0
	mvn r0, r0
	b _0223F4A4
_0223F49A:
	ldr r0, _0223F518 ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x5c]
	bl ListMenu_ProcessInput
_0223F4A4:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0223F4BA
	add r1, r1, #1
	cmp r0, r1
	bne _0223F4D8
	add r0, r4, #0
	bl ov06_0223F524
	pop {r3, r4, r5, pc}
_0223F4BA:
	ldr r0, _0223F51C ; =0x000005DC
	bl PlaySE
	ldr r0, _0223F518 ; =0x02252420
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
	bl ov06_0223F8B4
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	pop {r3, r4, r5, pc}
_0223F4D8:
	ldr r0, _0223F51C ; =0x000005DC
	bl PlaySE
	add r1, r4, #0
	ldr r0, [r4, #0x5c]
	add r1, #0x8e
	bl ListMenuGetCurrentItemArrayId
	add r0, r4, #0
	add r0, #0x8e
	ldrh r5, [r0]
	bl sub_0202E810
	cmp r0, r5
	ble _0223F514
	add r0, r5, #0
	bl sub_0202E844
	add r1, r4, #0
	add r1, #0x8e
	add r4, #0x8e
	strh r0, [r1]
	ldrh r0, [r4]
	bl sub_0204FF30
	bl sub_02031668
	ldr r0, _0223F520 ; =ov06_0223F584
	bl ov06_0223F8BC
_0223F514:
	pop {r3, r4, r5, pc}
	nop
_0223F518: .word ov06_02252420
_0223F51C: .word 0x000005DC
_0223F520: .word ov06_0223F584

	thumb_func_start ov06_0223F524
ov06_0223F524: ; 0x0223F524
	push {r3, lr}
	sub sp, #8
	bl sub_0202E878
	cmp r0, #0
	bne _0223F53C
	ldr r0, _0223F580 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x98
	ldrb r0, [r0]
	cmp r0, #0
	beq _0223F57A
_0223F53C:
	ldr r0, _0223F580 ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	add r0, #0x98
	strb r1, [r0]
	bl sub_0202E88C
	mov r0, #0xc
	str r0, [sp]
	mov r0, #0x50
	str r0, [sp, #4]
	ldr r0, _0223F580 ; =0x02252420
	mov r1, #0xf
	ldr r0, [r0]
	mov r2, #8
	add r0, #0x20
	mov r3, #0
	bl FillWindowPixelRect
	ldr r0, _0223F580 ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	add r2, r1, #0
	ldr r0, [r0, #0x5c]
	bl ov06_0223F0C8
	ldr r0, _0223F580 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x20
	bl CopyWindowToVram
_0223F57A:
	add sp, #8
	pop {r3, pc}
	nop
_0223F580: .word ov06_02252420

	thumb_func_start ov06_0223F584
ov06_0223F584: ; 0x0223F584
	push {r4, lr}
	add r4, r1, #0
	ldr r1, _0223F5C8 ; =0x02252420
	add r0, r4, #0
	add r0, #0x8e
	ldr r1, [r1]
	ldrh r0, [r0]
	ldr r1, [r1, #0x7c]
	bl sub_0202E9AC
	ldr r2, _0223F5C8 ; =0x02252420
	ldr r0, [r4, #0x58]
	ldr r2, [r2]
	mov r1, #1
	ldr r2, [r2, #0x7c]
	bl BufferPlayersName
	bl ov06_02240750
	cmp r0, #2
	bgt _0223F5B8
	mov r0, #1
	add r1, r0, #0
	bl ov06_0223EDC4
	b _0223F5C0
_0223F5B8:
	mov r0, #2
	mov r1, #1
	bl ov06_0223EDC4
_0223F5C0:
	ldr r0, _0223F5CC ; =ov06_0223F6D8
	bl ov06_0223F8BC
	pop {r4, pc}
	.align 2, 0
_0223F5C8: .word ov06_02252420
_0223F5CC: .word ov06_0223F6D8

	thumb_func_start ov06_0223F5D0
ov06_0223F5D0: ; 0x0223F5D0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl sub_020311F0
	cmp r0, #0
	beq _0223F5F6
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	mov r0, #0
	add r1, r0, #0
	bl ov06_0223EDC4
	add r0, r4, #0
	bl ov06_022406D4
	b _0223F6CA
_0223F5F6:
	mov r0, #0
	mov r1, #3
	bl sub_02031640
	add r6, r0, #0
	bl sub_02031190
	cmp r6, r0
	bne _0223F61C
	bl sub_02031668
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	add r0, r4, #0
	bl ov06_02240668
	b _0223F6CA
_0223F61C:
	mov r0, #0
	mov r1, #5
	bl sub_02031640
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223F640
	bl sub_02031668
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	add r0, r4, #0
	bl ov06_02240668
	b _0223F6CA
_0223F640:
	mov r0, #0
	mov r1, #4
	bl sub_02031640
	add r6, r0, #0
	bl sub_02031190
	cmp r6, r0
	bne _0223F662
	mov r0, #0x53
	mov r1, #0
	bl ov06_0223EDC4
	ldr r0, _0223F6D0 ; =ov06_0223FEF0
	bl ov06_0223F8BC
	b _0223F6CA
_0223F662:
	mov r0, #0
	mov r1, #2
	bl sub_02031640
	add r6, r0, #0
	bl sub_02031190
	cmp r6, r0
	bne _0223F6AE
	bl sub_02031668
	bl sub_0202DF28
	add r1, r4, #0
	add r1, #0x90
	strb r0, [r1]
	ldr r0, _0223F6D4 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	bne _0223F69E
	ldr r0, _0223F6D4 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_0201BD7C
_0223F69E:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	add r0, r4, #0
	bl ov06_02240418
	b _0223F6CA
_0223F6AE:
	bl ov06_02240860
	cmp r0, #0
	beq _0223F6C6
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	add r0, r4, #0
	bl ov06_02240668
	b _0223F6CA
_0223F6C6:
	mov r0, #0
	pop {r4, r5, r6, pc}
_0223F6CA:
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_0223F6D0: .word ov06_0223FEF0
_0223F6D4: .word ov06_02252420

	thumb_func_start ov06_0223F6D8
ov06_0223F6D8: ; 0x0223F6D8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _0223F714 ; =0x02252420
	add r4, r1, #0
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0223F712
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0223F5D0
	cmp r0, #0
	bne _0223F712
	ldr r0, _0223F718 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _0223F712
	mov r0, #3
	mov r1, #0
	bl ov06_0223EDC4
	ldr r0, _0223F71C ; =ov06_0223F720
	bl ov06_0223F8BC
_0223F712:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223F714: .word ov06_02252420
_0223F718: .word gSystem
_0223F71C: .word ov06_0223F720

	thumb_func_start ov06_0223F720
ov06_0223F720: ; 0x0223F720
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	bl ov06_0223F5D0
	cmp r0, #0
	bne _0223F75C
	ldr r0, _0223F760 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0223F75C
	mov r0, #4
	str r0, [sp]
	ldr r0, _0223F760 ; =0x02252420
	ldr r1, _0223F764 ; =0x0224F488
	ldr r0, [r0]
	ldr r2, _0223F768 ; =0x000003D9
	ldr r0, [r0, #0x68]
	mov r3, #0xb
	ldr r0, [r0, #8]
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x60]
	ldr r0, _0223F76C ; =ov06_0223F770
	bl ov06_0223F8BC
_0223F75C:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0223F760: .word ov06_02252420
_0223F764: .word ov06_0224F488
_0223F768: .word 0x000003D9
_0223F76C: .word ov06_0223F770

	thumb_func_start ov06_0223F770
ov06_0223F770: ; 0x0223F770
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov06_0223F5D0
	cmp r0, #0
	ldr r0, [r4, #0x60]
	beq _0223F78C
	mov r1, #4
	bl sub_020021EC
	mov r0, #0
	str r0, [r4, #0x60]
	pop {r3, r4, r5, pc}
_0223F78C:
	mov r1, #4
	bl sub_020021AC
	cmp r0, #0
	bne _0223F7AE
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	mov r0, #6
	mov r1, #0
	bl ov06_0223EDC4
	add r0, r4, #0
	bl ov06_022406D4
	pop {r3, r4, r5, pc}
_0223F7AE:
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223F7BC
	ldr r0, _0223F7C0 ; =ov06_0223F584
	bl ov06_0223F8BC
_0223F7BC:
	pop {r3, r4, r5, pc}
	nop
_0223F7C0: .word ov06_0223F584

	thumb_func_start ov06_0223F7C4
ov06_0223F7C4: ; 0x0223F7C4
	push {r4, lr}
	sub sp, #0x10
	add r4, r2, #0
	mov r2, #0
	add r0, sp, #0xc
	strh r2, [r0]
	ldr r0, _0223F898 ; =0x02252420
	ldr r0, [r0]
	ldr r0, [r0, #0x5c]
	cmp r0, #0
	beq _0223F7E0
	add r1, sp, #0xc
	bl ListMenuGetScrollAndRow
_0223F7E0:
	add r0, sp, #0xc
	ldrh r1, [r0]
	add r1, r1, r4
	strh r1, [r0]
	ldrh r0, [r0]
	bl sub_0202DFA4
	cmp r0, #0
	beq _0223F892
	add r0, sp, #0xc
	ldrh r0, [r0]
	bl sub_0202DFA4
	add r2, r0, #0
	ldr r0, _0223F898 ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	ldr r0, [r0, #0x50]
	bl BufferPlayersName
	ldr r0, _0223F898 ; =0x02252420
	mov r1, #0x34
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #4]
	bl ReadMsgDataIntoString
	ldr r0, _0223F898 ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x50]
	ldmia r2!, {r1, r2}
	bl StringExpandPlaceholders
	ldr r0, _0223F898 ; =0x02252420
	lsl r4, r4, #4
	ldr r2, [r0]
	mov r1, #0
	str r4, [sp]
	str r1, [sp, #4]
	add r0, r2, #0
	str r1, [sp, #8]
	ldr r2, [r2]
	add r0, #0x20
	mov r3, #8
	bl AddTextPrinterParameterized
	add r0, sp, #0xc
	ldrh r0, [r0]
	bl sub_0202DFA4
	bl PlayerProfile_GetTrainerID_VisibleHalf
	mov r1, #2
	add r2, r0, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0223F898 ; =0x02252420
	mov r3, #5
	ldr r0, [r0]
	ldr r0, [r0, #0x50]
	bl BufferIntegerAsString
	ldr r0, _0223F898 ; =0x02252420
	mov r1, #0x33
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #0xc]
	bl ReadMsgDataIntoString
	ldr r0, _0223F898 ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x50]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0xc]
	bl StringExpandPlaceholders
	ldr r0, _0223F898 ; =0x02252420
	mov r1, #0
	ldr r2, [r0]
	mov r3, #0x48
	str r4, [sp]
	str r1, [sp, #4]
	add r0, r2, #0
	str r1, [sp, #8]
	ldr r2, [r2, #8]
	add r0, #0x20
	bl AddTextPrinterParameterized
_0223F892:
	add sp, #0x10
	pop {r4, pc}
	nop
_0223F898: .word ov06_02252420

	thumb_func_start ov06_0223F89C
ov06_0223F89C: ; 0x0223F89C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02240778
	add r2, r0, #0
	ldr r0, [r4, #0x68]
	add r4, #0x91
	ldrb r1, [r4]
	bl sub_0204FEB0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0223F8B4
ov06_0223F8B4: ; 0x0223F8B4
	ldr r3, _0223F8B8 ; =sub_02050024
	bx r3
	.align 2, 0
_0223F8B8: .word sub_02050024

	thumb_func_start ov06_0223F8BC
ov06_0223F8BC: ; 0x0223F8BC
	ldr r1, _0223F8C4 ; =0x02252420
	ldr r1, [r1]
	str r0, [r1, #0x6c]
	bx lr
	.align 2, 0
_0223F8C4: .word ov06_02252420

	thumb_func_start ov06_0223F8C8
ov06_0223F8C8: ; 0x0223F8C8
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, _0223F94C ; =ov06_0223FAA4
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	bl ov06_0223F95C
	ldr r0, _0223F950 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x30
	bl WindowIsInUse
	cmp r0, #0
	bne _0223F910
	ldr r0, _0223F950 ; =0x02252420
	mov r2, #3
	ldr r1, [r0]
	mov r0, #2
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xcd
	str r0, [sp, #0x10]
	ldr r0, [r1, #0x68]
	add r1, #0x30
	ldr r0, [r0, #8]
	mov r3, #0x16
	bl AddWindowParameterized
_0223F910:
	ldr r0, _0223F950 ; =0x02252420
	ldr r2, _0223F954 ; =0x000003D9
	ldr r0, [r0]
	mov r1, #1
	add r0, #0x30
	mov r3, #0xb
	bl DrawFrameAndWindow1
	ldr r0, _0223F950 ; =0x02252420
	mov r1, #0xf
	ldr r0, [r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r0, _0223F950 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x30
	bl CopyWindowToVram
	mov r0, #1
	add r4, #0x97
	strb r0, [r4]
	mov r0, #0
	bl sub_0202DEE0
	ldr r0, _0223F958 ; =ov06_0223FAB8
	bl ov06_0223F8BC
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_0223F94C: .word ov06_0223FAA4
_0223F950: .word ov06_02252420
_0223F954: .word 0x000003D9
_0223F958: .word ov06_0223FAB8

	thumb_func_start ov06_0223F95C
ov06_0223F95C: ; 0x0223F95C
	push {r3, r4, lr}
	sub sp, #0x44
	ldr r4, _0223F9D0 ; =0x0224F514
	add r3, sp, #0
	mov r2, #8
_0223F966:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223F966
	ldr r0, [r4]
	str r0, [r3]
	ldr r0, _0223F9D4 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x91
	ldrb r0, [r0]
	cmp r0, #0x11
	blo _0223F982
	bl GF_AssertFail
_0223F982:
	ldr r0, _0223F9D4 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x91
	ldrb r0, [r0]
	cmp r0, #8
	bne _0223F9BE
	bl sub_0202DF28
	cmp r0, #1
	ble _0223F9AA
	ldr r0, _0223F9D4 ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	add r0, #0x92
	ldrb r0, [r0]
	add r0, #0x5e
	bl ov06_0223EDC4
	add sp, #0x44
	pop {r3, r4, pc}
_0223F9AA:
	ldr r0, _0223F9D4 ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	add r0, #0x92
	ldrb r0, [r0]
	add r0, #0x54
	bl ov06_0223EDC4
	add sp, #0x44
	pop {r3, r4, pc}
_0223F9BE:
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	mov r1, #0
	bl ov06_0223EDC4
	add sp, #0x44
	pop {r3, r4, pc}
	nop
_0223F9D0: .word ov06_0224F514
_0223F9D4: .word ov06_02252420

	thumb_func_start ov06_0223F9D8
ov06_0223F9D8: ; 0x0223F9D8
	push {r3, r4, lr}
	sub sp, #0xc
	bl sub_0202DF28
	add r4, r0, #0
	bl ov06_02240750
	cmp r4, r0
	blt _0223F9F4
	bl sub_0202DF28
	add r2, r0, #0
	mov r4, #0x36
	b _0223FA02
_0223F9F4:
	bl ov06_02240750
	add r4, r0, #0
	bl sub_0202DF28
	sub r2, r4, r0
	mov r4, #0x35
_0223FA02:
	mov r0, #5
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0223FA5C ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	mov r3, #2
	ldr r0, [r0, #0x54]
	bl BufferIntegerAsString
	ldr r0, _0223FA5C ; =0x02252420
	mov r1, #0xf
	ldr r0, [r0]
	add r0, #0x30
	bl FillWindowPixelBuffer
	ldr r0, _0223FA5C ; =0x02252420
	add r1, r4, #0
	ldr r2, [r0]
	ldr r0, [r2, #0x74]
	ldr r2, [r2, #0x1c]
	bl ReadMsgDataIntoString
	ldr r0, _0223FA5C ; =0x02252420
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r1, [r2, #0x18]
	ldr r2, [r2, #0x1c]
	bl StringExpandPlaceholders
	ldr r0, _0223FA5C ; =0x02252420
	mov r3, #2
	ldr r2, [r0]
	mov r1, #0
	str r3, [sp]
	str r1, [sp, #4]
	add r0, r2, #0
	str r1, [sp, #8]
	ldr r2, [r2, #0x18]
	add r0, #0x30
	bl AddTextPrinterParameterized
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0223FA5C: .word ov06_02252420

	thumb_func_start ov06_0223FA60
ov06_0223FA60: ; 0x0223FA60
	push {r3, r4, r5, r6, lr}
	sub sp, #0x44
	ldr r6, _0223FAA0 ; =0x0224F4D0
	add r2, r0, #0
	add r4, r1, #0
	add r5, sp, #0
	mov r3, #8
_0223FA6E:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _0223FA6E
	ldr r0, [r6]
	str r0, [r5]
	add r0, r2, #0
	bl sub_0202DFA4
	add r2, r0, #0
	beq _0223FA8C
	ldr r0, [r4, #0x58]
	mov r1, #1
	bl BufferPlayersName
_0223FA8C:
	add r4, #0x91
	ldrb r0, [r4]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	mov r1, #1
	bl ov06_0223EDC4
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0223FAA0: .word ov06_0224F4D0

	thumb_func_start ov06_0223FAA4
ov06_0223FAA4: ; 0x0223FAA4
	push {r3, lr}
	ldr r2, _0223FAB4 ; =0x02252420
	ldr r2, [r2]
	ldr r2, [r2, #0x6c]
	cmp r2, #0
	beq _0223FAB2
	blx r2
_0223FAB2:
	pop {r3, pc}
	.align 2, 0
_0223FAB4: .word ov06_02252420

	thumb_func_start ov06_0223FAB8
ov06_0223FAB8: ; 0x0223FAB8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r0, r1, #0
	bl ov06_0223F9D8
	ldr r0, _0223FB50 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0223FB4C
	mov r0, #5
	mov r1, #4
	bl ListMenuItems_New
	ldr r4, _0223FB50 ; =0x02252420
	mov r5, #0
	ldr r1, [r4]
	mov r6, #0x37
	str r0, [r1, #0x64]
	add r7, r5, #0
_0223FAE6:
	ldr r1, [r4]
	add r2, r6, #0
	ldr r0, [r1, #0x64]
	ldr r1, [r1, #0x74]
	add r3, r7, #0
	bl ListMenuItems_AppendFromMsgData
	add r5, r5, #1
	cmp r5, #5
	blt _0223FAE6
	ldr r1, _0223FB50 ; =0x02252420
	mov r2, #1
	ldr r0, [r1]
	mov r3, #0
	add r0, #0x98
	strb r2, [r0]
	add r2, r3, #0
_0223FB08:
	ldr r0, [r1]
	add r0, r0, r3
	add r0, #0x80
	add r3, r3, #1
	strb r2, [r0]
	cmp r3, #8
	blt _0223FB08
	mov r1, #1
	str r1, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0x14]
	mov r0, #0x11
	str r0, [sp, #0x18]
	mov r0, #0xc
	mov r4, sp
	str r0, [sp, #0x1c]
	sub r4, #0x10
	ldr r3, _0223FB54 ; =0x0224F490
	str r1, [sp, #0x20]
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r4!, {r0, r1, r2, r3}
	bl ov06_0223EE74
	ldr r0, _0223FB58 ; =ov06_0223FB5C
	bl ov06_0223F8BC
_0223FB4C:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223FB50: .word ov06_02252420
_0223FB54: .word ov06_0224F490
_0223FB58: .word ov06_0223FB5C

	thumb_func_start ov06_0223FB5C
ov06_0223FB5C: ; 0x0223FB5C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	str r0, [sp]
	add r0, r1, #0
	str r1, [sp, #4]
	bl ov06_0223F9D8
	mov r7, #1
	ldr r4, _0223FCF0 ; =0x02252420
	mov r5, #0
	add r6, r7, #0
_0223FB72:
	add r0, r5, #0
	bl sub_0202DEA4
	cmp r0, #0
	beq _0223FB90
	cmp r5, #0
	beq _0223FB90
	ldr r0, [r4]
	add r0, r0, r5
	add r0, #0x80
	strb r6, [r0]
	ldr r0, [r4]
	add r0, #0x98
	strb r6, [r0]
	b _0223FBDA
_0223FB90:
	add r0, r5, #0
	bl sub_0202DFA4
	cmp r0, #0
	beq _0223FBB4
	ldr r1, [r4]
	add r0, r1, r5
	add r0, #0x80
	ldrb r0, [r0]
	cmp r0, #0
	bne _0223FBB4
	add r0, r1, r5
	add r0, #0x80
	strb r7, [r0]
	ldr r0, [r4]
	add r0, #0x98
	strb r7, [r0]
	b _0223FBDA
_0223FBB4:
	add r0, r5, #0
	bl sub_0202DFA4
	cmp r0, #0
	bne _0223FBDA
	ldr r1, [r4]
	add r0, r1, r5
	add r0, #0x80
	ldrb r0, [r0]
	cmp r0, #0
	beq _0223FBDA
	add r1, r1, r5
	add r1, #0x80
	mov r0, #0
	strb r0, [r1]
	ldr r1, [r4]
	mov r0, #1
	add r1, #0x98
	strb r0, [r1]
_0223FBDA:
	add r5, r5, #1
	cmp r5, #8
	blt _0223FB72
	ldr r1, _0223FCF0 ; =0x02252420
	ldr r2, [r1]
	add r0, r2, #0
	add r0, #0x98
	ldrb r0, [r0]
	cmp r0, #0
	beq _0223FC32
	mov r0, #0
	add r2, #0x98
	strb r0, [r2]
	ldr r0, [r1]
	ldr r0, [r0, #0x5c]
	bl RedrawListMenu
	ldr r0, _0223FCF0 ; =0x02252420
	mov r1, #3
	ldr r0, [r0]
	mov r5, #0
	ldr r0, [r0, #0x5c]
	bl ListMenuGetTemplateField
	cmp r0, #0
	bls _0223FC32
	ldr r4, _0223FCF0 ; =0x02252420
	add r6, r5, #0
	mov r7, #3
_0223FC14:
	ldr r0, [r4]
	lsl r2, r5, #0x18
	ldr r0, [r0, #0x5c]
	add r1, r6, #0
	lsr r2, r2, #0x18
	bl ov06_0223F7C4
	ldr r0, [r4]
	add r1, r7, #0
	ldr r0, [r0, #0x5c]
	add r5, r5, #1
	bl ListMenuGetTemplateField
	cmp r5, r0
	blo _0223FC14
_0223FC32:
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x5c]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	bl sub_0202DF08
	cmp r0, #0xff
	beq _0223FC6A
	bl sub_0202DF08
	ldr r1, [sp, #4]
	add r1, #0x95
	strb r0, [r1]
	ldr r0, _0223FCF4 ; =0x0000060D
	bl PlaySE
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, #0x95
	ldrb r0, [r0]
	bl ov06_0223FA60
	ldr r0, _0223FCF8 ; =ov06_02240310
	bl ov06_0223F8BC
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0223FC6A:
	bl sub_020311F0
	cmp r0, #0
	beq _0223FC8C
	bl ov06_0223F8B4
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl ov06_02240364
	ldr r0, _0223FCF0 ; =0x02252420
	mov r1, #3
	ldr r0, [r0]
	add sp, #0x4c
	add r0, #0x88
	str r1, [r0]
	pop {r4, r5, r6, r7, pc}
_0223FC8C:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0223FC9C
	add r0, r0, #1
	cmp r4, r0
	beq _0223FCEA
	b _0223FCA6
_0223FC9C:
	ldr r0, _0223FCFC ; =ov06_0224019C
	bl ov06_0223F8BC
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_0223FCA6:
	bl ov06_02240750
	add r4, r0, #0
	bl sub_0202DF28
	cmp r4, r0
	bgt _0223FCEA
	ldr r4, _0223FD00 ; =0x0224F59C
	add r3, sp, #8
	mov r2, #8
_0223FCBA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223FCBA
	ldr r0, [r4]
	str r0, [r3]
	bl sub_0202DF28
	ldr r1, [sp, #4]
	add r1, #0x90
	strb r0, [r1]
	ldr r0, [sp, #4]
	add r0, #0x91
	str r0, [sp, #4]
	ldrb r0, [r0]
	lsl r1, r0, #2
	add r0, sp, #8
	ldr r0, [r0, r1]
	mov r1, #0
	bl ov06_0223EDC4
	ldr r0, _0223FD04 ; =ov06_0223FFD4
	bl ov06_0223F8BC
_0223FCEA:
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_0223FCF0: .word ov06_02252420
_0223FCF4: .word 0x0000060D
_0223FCF8: .word ov06_02240310
_0223FCFC: .word ov06_0224019C
_0223FD00: .word ov06_0224F59C
_0223FD04: .word ov06_0223FFD4

	thumb_func_start ov06_0223FD08
ov06_0223FD08: ; 0x0223FD08
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	add r0, r4, #0
	bl ov06_0223F9D8
	ldr r0, [r4, #0x5c]
	bl ListMenu_ProcessInput
	ldr r0, [r4, #0x60]
	mov r1, #4
	bl sub_020021AC
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x95
	ldrb r0, [r0]
	bl sub_02030E7C
	cmp r0, #0
	bne _0223FDA6
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _0223FD42
	ldr r0, [r4, #0x60]
	mov r1, #4
	bl sub_020021EC
_0223FD42:
	add r0, r4, #0
	add r0, #0x91
	ldrb r0, [r0]
	cmp r0, #8
	bne _0223FD8E
	mov r5, #1
	bl ov06_02240764
	cmp r0, #1
	ble _0223FD7E
	mov r4, #5
_0223FD58:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl sub_02030E7C
	cmp r0, #0
	beq _0223FD74
	add r0, r5, #0
	bl sub_0202DE78
	lsl r1, r5, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl sub_0203162C
_0223FD74:
	add r5, r5, #1
	bl ov06_02240764
	cmp r5, r0
	blt _0223FD58
_0223FD7E:
	mov r0, #0
	add r1, r0, #0
	bl ov06_0223EDC4
	ldr r0, _0223FEE0 ; =ov06_0223FF30
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_0223FD8E:
	add r4, #0x95
	ldrb r0, [r4]
	bl sub_0202DE78
	mov r0, #0
	add r1, r0, #0
	bl ov06_0223EDC4
	ldr r0, _0223FEE0 ; =ov06_0223FF30
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_0223FDA6:
	bl sub_020311F0
	cmp r0, #0
	bne _0223FDB6
	bl ov06_02240860
	cmp r0, #0
	beq _0223FDDE
_0223FDB6:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _0223FDC6
	ldr r0, [r4, #0x60]
	mov r1, #4
	bl sub_020021EC
_0223FDC6:
	add r4, #0x95
	ldrb r0, [r4]
	bl sub_0202DE78
	mov r0, #0
	add r1, r0, #0
	bl ov06_0223EDC4
	ldr r0, _0223FEE0 ; =ov06_0223FF30
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_0223FDDE:
	cmp r5, #0
	bne _0223FE6E
	add r0, r4, #0
	add r0, #0x91
	ldrb r0, [r0]
	add r0, #0xff
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _0223FE14
	bl sub_0202E08C
	cmp r0, #0
	bne _0223FE14
	mov r0, #0x53
	mov r1, #0
	bl ov06_0223EDC4
	ldr r0, _0223FEE4 ; =ov06_0223FEF0
	bl ov06_0223F8BC
	add r4, #0x95
	ldrb r1, [r4]
	mov r0, #4
	bl sub_0203162C
	pop {r4, r5, r6, pc}
_0223FE14:
	add r0, r4, #0
	add r0, #0x95
	ldrb r0, [r0]
	bl sub_0202DEE0
	add r1, r4, #0
	add r1, #0x95
	ldrb r1, [r1]
	mov r0, #2
	bl sub_0203162C
	bl ov06_02240764
	add r5, r0, #0
	bl sub_0202DF28
	cmp r5, r0
	bne _0223FE62
	bl sub_0202DF28
	add r1, r4, #0
	add r1, #0x90
	strb r0, [r1]
	bl ov06_02240764
	cmp r0, #2
	ble _0223FE52
	ldr r0, _0223FEE8 ; =ov06_0223FF94
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_0223FE52:
	add r0, r6, #0
	add r1, r4, #0
	bl ov06_02240364
	add r0, r4, #0
	bl ov06_022403E0
	pop {r4, r5, r6, pc}
_0223FE62:
	bl ov06_0223F95C
	ldr r0, _0223FEEC ; =ov06_0223FF6C
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_0223FE6E:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	beq _0223FEDC
	add r0, r4, #0
	add r0, #0x91
	ldrb r0, [r0]
	cmp r0, #8
	bne _0223FEBE
	mov r5, #1
	bl ov06_02240764
	cmp r0, #1
	ble _0223FEB2
	mov r4, #5
_0223FE8C:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl sub_02030E7C
	cmp r0, #0
	beq _0223FEA8
	add r0, r5, #0
	bl sub_0202DE78
	lsl r1, r5, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl sub_0203162C
_0223FEA8:
	add r5, r5, #1
	bl ov06_02240764
	cmp r5, r0
	blt _0223FE8C
_0223FEB2:
	bl ov06_0223F95C
	ldr r0, _0223FEEC ; =ov06_0223FF6C
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_0223FEBE:
	add r0, r4, #0
	add r0, #0x95
	ldrb r0, [r0]
	bl sub_0202DE78
	add r4, #0x95
	ldrb r1, [r4]
	mov r0, #3
	bl sub_0203162C
	bl ov06_0223F95C
	ldr r0, _0223FEEC ; =ov06_0223FF6C
	bl ov06_0223F8BC
_0223FEDC:
	pop {r4, r5, r6, pc}
	nop
_0223FEE0: .word ov06_0223FF30
_0223FEE4: .word ov06_0223FEF0
_0223FEE8: .word ov06_0223FF94
_0223FEEC: .word ov06_0223FF6C

	thumb_func_start ov06_0223FEF0
ov06_0223FEF0: ; 0x0223FEF0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _0223FF28 ; =0x02252420
	add r4, r1, #0
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0223FF26
	ldr r0, _0223FF2C ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0223FF26
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	bl ov06_0223F8B4
	ldr r0, _0223FF28 ; =0x02252420
	mov r1, #4
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
_0223FF26:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223FF28: .word ov06_02252420
_0223FF2C: .word gSystem

	thumb_func_start ov06_0223FF30
ov06_0223FF30: ; 0x0223FF30
	push {r3, lr}
	add r0, r1, #0
	bl ov06_0223F9D8
	ldr r0, _0223FF60 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0223FF5C
	ldr r0, _0223FF64 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0223FF5C
	bl ov06_0223F95C
	ldr r0, _0223FF68 ; =ov06_0223FF6C
	bl ov06_0223F8BC
_0223FF5C:
	pop {r3, pc}
	nop
_0223FF60: .word ov06_02252420
_0223FF64: .word gSystem
_0223FF68: .word ov06_0223FF6C

	thumb_func_start ov06_0223FF6C
ov06_0223FF6C: ; 0x0223FF6C
	push {r3, lr}
	add r0, r1, #0
	bl ov06_0223F9D8
	ldr r0, _0223FF8C ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0223FF8A
	ldr r0, _0223FF90 ; =ov06_0223FB5C
	bl ov06_0223F8BC
_0223FF8A:
	pop {r3, pc}
	.align 2, 0
_0223FF8C: .word ov06_02252420
_0223FF90: .word ov06_0223FB5C

	thumb_func_start ov06_0223FF94
ov06_0223FF94: ; 0x0223FF94
	push {r4, r5, lr}
	sub sp, #0x44
	ldr r5, _0223FFCC ; =0x0224F624
	add r4, r1, #0
	add r3, sp, #0
	mov r2, #8
_0223FFA0:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223FFA0
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	bl ov06_0223F9D8
	add r4, #0x91
	ldrb r0, [r4]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	mov r1, #0
	bl ov06_0223EDC4
	ldr r0, _0223FFD0 ; =ov06_0223FFD4
	bl ov06_0223F8BC
	add sp, #0x44
	pop {r4, r5, pc}
	.align 2, 0
_0223FFCC: .word ov06_0224F624
_0223FFD0: .word ov06_0223FFD4

	thumb_func_start ov06_0223FFD4
ov06_0223FFD4: ; 0x0223FFD4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	add r0, r4, #0
	bl ov06_0223F9D8
	mov r0, #0
	bl sub_02031A24
	ldr r0, [r4, #0x5c]
	bl ListMenu_ProcessInput
	ldr r0, _02240020 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0224001A
	mov r0, #4
	str r0, [sp]
	ldr r0, _02240020 ; =0x02252420
	ldr r1, _02240024 ; =0x0224F488
	ldr r0, [r0]
	ldr r2, _02240028 ; =0x000003D9
	ldr r0, [r0, #0x68]
	mov r3, #0xb
	ldr r0, [r0, #8]
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x60]
	ldr r0, _0224002C ; =ov06_02240030
	bl ov06_0223F8BC
_0224001A:
	add sp, #4
	pop {r3, r4, pc}
	nop
_02240020: .word ov06_02252420
_02240024: .word ov06_0224F488
_02240028: .word 0x000003D9
_0224002C: .word ov06_02240030

	thumb_func_start ov06_02240030
ov06_02240030: ; 0x02240030
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	bl ov06_0223F9D8
	ldr r0, [r5, #0x5c]
	bl ListMenu_ProcessInput
	ldr r0, [r5, #0x60]
	mov r1, #4
	bl sub_020021AC
	add r4, r0, #0
	bl sub_020311F0
	cmp r0, #0
	bne _02240062
	bl sub_02030F20
	add r1, r5, #0
	add r1, #0x90
	ldrb r1, [r1]
	cmp r1, r0
	beq _0224007E
_02240062:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _02240072
	ldr r0, [r5, #0x60]
	mov r1, #4
	bl sub_020021EC
_02240072:
	mov r0, #0
	str r0, [r5, #0x60]
	ldr r0, _022400E8 ; =ov06_022400F4
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_0224007E:
	cmp r4, #0
	bne _022400C0
	add r5, #0x91
	ldrb r0, [r5]
	cmp r0, #8
	bne _022400B2
	mov r4, #1
	bl sub_02030F20
	cmp r0, #1
	ble _022400B2
_02240094:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl sub_02030E7C
	cmp r0, #0
	bne _022400A8
	ldr r0, _022400E8 ; =ov06_022400F4
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_022400A8:
	add r4, r4, #1
	bl sub_02030F20
	cmp r4, r0
	blt _02240094
_022400B2:
	mov r0, #0xa
	bl sub_02031588
	ldr r0, _022400EC ; =ov06_022402B8
	bl ov06_0223F8BC
	pop {r4, r5, r6, pc}
_022400C0:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _022400E4
	mov r0, #1
	bl sub_02031A24
	bl ov06_0223F8B4
	add r0, r6, #0
	add r1, r5, #0
	bl ov06_02240364
	ldr r0, _022400F0 ; =0x02252420
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
_022400E4:
	pop {r4, r5, r6, pc}
	nop
_022400E8: .word ov06_022400F4
_022400EC: .word ov06_022402B8
_022400F0: .word ov06_02252420

	thumb_func_start ov06_022400F4
ov06_022400F4: ; 0x022400F4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x44
	ldr r6, _02240158 ; =0x0224F558
	add r2, r0, #0
	add r4, r1, #0
	add r5, sp, #0
	mov r3, #8
_02240102:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _02240102
	ldr r0, [r6]
	add r1, r4, #0
	str r0, [r5]
	add r0, r2, #0
	bl ov06_02240364
	ldr r0, _0224015C ; =0x02252420
	ldr r1, [r0]
	add r0, r1, #0
	add r0, #0x91
	ldrb r0, [r0]
	cmp r0, #8
	bne _02240132
	add r1, #0x92
	ldrb r0, [r1]
	mov r1, #0
	add r0, #0x68
	bl ov06_0223EDC4
	b _02240144
_02240132:
	add r0, r4, #0
	add r0, #0x91
	ldrb r0, [r0]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	mov r1, #0
	bl ov06_0223EDC4
_02240144:
	bl sub_02050024
	ldr r0, _02240160 ; =ov06_02240164
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
	nop
_02240158: .word ov06_0224F558
_0224015C: .word ov06_02252420
_02240160: .word ov06_02240164

	thumb_func_start ov06_02240164
ov06_02240164: ; 0x02240164
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02240194 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _02240192
	ldr r0, _02240198 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02240192
	ldr r0, _02240194 ; =0x02252420
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	bl sub_0200CAB4
_02240192:
	pop {r4, pc}
	.align 2, 0
_02240194: .word ov06_02252420
_02240198: .word gSystem

	thumb_func_start ov06_0224019C
ov06_0224019C: ; 0x0224019C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x44
	ldr r6, _022401F8 ; =0x0224F668
	add r5, r0, #0
	add r4, r1, #0
	add r3, sp, #0
	mov r2, #8
_022401AA:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022401AA
	ldr r0, [r6]
	str r0, [r3]
	add r0, r4, #0
	bl ov06_0223F9D8
	bl sub_0202DF28
	cmp r0, #1
	ble _022401DE
	add r4, #0x91
	ldrb r0, [r4]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	mov r1, #0
	bl ov06_0223EDC4
	ldr r0, _022401FC ; =ov06_02240204
	bl ov06_0223F8BC
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
_022401DE:
	bl ov06_0223F8B4
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	ldr r0, _02240200 ; =0x02252420
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022401F8: .word ov06_0224F668
_022401FC: .word ov06_02240204
_02240200: .word ov06_02252420

	thumb_func_start ov06_02240204
ov06_02240204: ; 0x02240204
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	add r0, r4, #0
	bl ov06_0223F9D8
	ldr r0, [r4, #0x5c]
	bl ListMenu_ProcessInput
	ldr r0, _02240248 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _02240244
	mov r0, #4
	str r0, [sp]
	ldr r0, _02240248 ; =0x02252420
	ldr r1, _0224024C ; =0x0224F488
	ldr r0, [r0]
	ldr r2, _02240250 ; =0x000003D9
	ldr r0, [r0, #0x68]
	mov r3, #0xb
	ldr r0, [r0, #8]
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x60]
	ldr r0, _02240254 ; =ov06_02240258
	bl ov06_0223F8BC
_02240244:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02240248: .word ov06_02252420
_0224024C: .word ov06_0224F488
_02240250: .word 0x000003D9
_02240254: .word ov06_02240258

	thumb_func_start ov06_02240258
ov06_02240258: ; 0x02240258
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	bl ov06_0223F9D8
	ldr r0, [r5, #0x5c]
	bl ListMenu_ProcessInput
	ldr r0, [r5, #0x60]
	mov r1, #4
	bl sub_020021AC
	add r4, r0, #0
	bl sub_020311F0
	cmp r0, #0
	beq _02240280
	mov r4, #1
	mvn r4, r4
_02240280:
	cmp r4, #0
	bne _0224029C
	bl ov06_0223F8B4
	add r0, r6, #0
	add r1, r5, #0
	bl ov06_02240364
	ldr r0, _022402B0 ; =0x02252420
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
	pop {r4, r5, r6, pc}
_0224029C:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _022402AE
	bl ov06_0223F95C
	ldr r0, _022402B4 ; =ov06_0223FF6C
	bl ov06_0223F8BC
_022402AE:
	pop {r4, r5, r6, pc}
	.align 2, 0
_022402B0: .word ov06_02252420
_022402B4: .word ov06_0223FF6C

	thumb_func_start ov06_022402B8
ov06_022402B8: ; 0x022402B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl sub_020311F0
	cmp r0, #0
	bne _022402D4
	bl sub_02030F20
	add r1, r4, #0
	add r1, #0x90
	ldrb r1, [r1]
	cmp r1, r0
	beq _022402DC
_022402D4:
	ldr r0, _0224030C ; =ov06_022400F4
	bl ov06_0223F8BC
	pop {r3, r4, r5, pc}
_022402DC:
	add r0, r4, #0
	bl ov06_0223F9D8
	ldr r0, [r4, #0x5c]
	bl ListMenu_ProcessInput
	mov r0, #0xa
	bl sub_020315D8
	cmp r0, #0
	beq _02240308
	bl sub_020314E8
	cmp r0, #0
	beq _02240308
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02240364
	add r0, r4, #0
	bl ov06_02240724
_02240308:
	pop {r3, r4, r5, pc}
	nop
_0224030C: .word ov06_022400F4

	thumb_func_start ov06_02240310
ov06_02240310: ; 0x02240310
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	add r0, r4, #0
	bl ov06_0223F9D8
	ldr r0, [r4, #0x5c]
	bl ListMenu_ProcessInput
	ldr r0, _02240354 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _02240350
	mov r0, #4
	str r0, [sp]
	ldr r0, _02240354 ; =0x02252420
	ldr r1, _02240358 ; =0x0224F488
	ldr r0, [r0]
	ldr r2, _0224035C ; =0x000003D9
	ldr r0, [r0, #0x68]
	mov r3, #0xb
	ldr r0, [r0, #8]
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x60]
	ldr r0, _02240360 ; =ov06_0223FD08
	bl ov06_0223F8BC
_02240350:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02240354: .word ov06_02252420
_02240358: .word ov06_0224F488
_0224035C: .word 0x000003D9
_02240360: .word ov06_0223FD08

	thumb_func_start ov06_02240364
ov06_02240364: ; 0x02240364
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _022403DC ; =0x02252420
	add r4, r1, #0
	ldr r0, [r0]
	mov r1, #0xf
	add r0, #0x40
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r0, #0x20
	mov r1, #0
	bl ClearFrameAndWindow1
	ldr r0, [r4, #0x64]
	bl ListMenuItems_Delete
	mov r1, #0
	ldr r0, [r4, #0x5c]
	add r2, r1, #0
	bl DestroyListMenu
	add r0, r4, #0
	add r0, #0x20
	bl ClearWindowTilemapAndCopyToVram
	add r0, r4, #0
	add r0, #0x20
	bl RemoveWindow
	add r0, r4, #0
	add r0, #0x97
	ldrb r0, [r0]
	cmp r0, #0
	beq _022403D0
	ldr r0, _022403DC ; =0x02252420
	mov r1, #0
	ldr r0, [r0]
	add r0, #0x30
	bl ClearFrameAndWindow1
	ldr r0, _022403DC ; =0x02252420
	ldr r0, [r0]
	add r0, #0x30
	bl ClearWindowTilemapAndCopyToVram
	ldr r0, _022403DC ; =0x02252420
	ldr r0, [r0]
	add r0, #0x30
	bl RemoveWindow
	mov r0, #0
	add r4, #0x97
	strb r0, [r4]
_022403D0:
	cmp r5, #0
	beq _022403DA
	add r0, r5, #0
	bl sub_0200CAB4
_022403DA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022403DC: .word ov06_02252420

	thumb_func_start ov06_022403E0
ov06_022403E0: ; 0x022403E0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	bl sub_0202DFA4
	add r2, r0, #0
	ldr r0, [r4, #0x58]
	mov r1, #1
	bl BufferPlayersName
	mov r0, #0x2b
	mov r1, #1
	bl ov06_0223EDC4
	ldr r0, _02240410 ; =ov06_0223FAA4
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	ldr r0, _02240414 ; =ov06_02240474
	bl ov06_0223F8BC
	pop {r4, pc}
	nop
_02240410: .word ov06_0223FAA4
_02240414: .word ov06_02240474

	thumb_func_start ov06_02240418
ov06_02240418: ; 0x02240418
	push {r4, lr}
	ldr r1, _02240468 ; =0x02252420
	add r4, r0, #0
	add r0, #0x8e
	ldr r1, [r1]
	ldrh r0, [r0]
	ldr r1, [r1, #0x7c]
	bl sub_0202E9AC
	ldr r2, _02240468 ; =0x02252420
	ldr r0, [r4, #0x58]
	ldr r2, [r2]
	mov r1, #1
	ldr r2, [r2, #0x7c]
	bl BufferPlayersName
	mov r0, #4
	mov r1, #1
	bl ov06_0223EDC4
	bl sub_02030F20
	add r1, r4, #0
	add r1, #0x90
	strb r0, [r1]
	ldr r0, _0224046C ; =ov06_0223FAA4
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	ldr r0, _02240470 ; =ov06_02240474
	bl ov06_0223F8BC
	ldr r0, _02240468 ; =0x02252420
	mov r1, #0x5a
	ldr r0, [r0]
	add r0, #0x96
	strb r1, [r0]
	pop {r4, pc}
	nop
_02240468: .word ov06_02252420
_0224046C: .word ov06_0223FAA4
_02240470: .word ov06_02240474

	thumb_func_start ov06_02240474
ov06_02240474: ; 0x02240474
	push {r4, lr}
	add r4, r1, #0
	bl sub_02031190
	cmp r0, #0
	bne _02240494
	bl sub_02030F20
	add r4, #0x90
	ldrb r1, [r4]
	cmp r1, r0
	beq _02240494
	ldr r0, _022404CC ; =ov06_02240600
	bl ov06_0223F8BC
	pop {r4, pc}
_02240494:
	bl ov06_02240860
	cmp r0, #0
	bne _022404A4
	bl sub_020311F0
	cmp r0, #0
	beq _022404AC
_022404A4:
	ldr r0, _022404CC ; =ov06_02240600
	bl ov06_0223F8BC
	pop {r4, pc}
_022404AC:
	ldr r0, _022404D0 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _022404C8
	mov r0, #0xa
	bl sub_02031588
	ldr r0, _022404D4 ; =ov06_022404D8
	bl ov06_0223F8BC
_022404C8:
	pop {r4, pc}
	nop
_022404CC: .word ov06_02240600
_022404D0: .word ov06_02252420
_022404D4: .word ov06_022404D8

	thumb_func_start ov06_022404D8
ov06_022404D8: ; 0x022404D8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x44
	add r5, r0, #0
	add r4, r1, #0
	bl sub_02031190
	cmp r0, #0
	bne _022404FE
	bl sub_02030F20
	add r1, r4, #0
	add r1, #0x90
	ldrb r1, [r1]
	cmp r1, r0
	beq _022404FE
	ldr r0, _022405F4 ; =ov06_02240600
	bl ov06_0223F8BC
	b _0224058E
_022404FE:
	bl ov06_02240860
	cmp r0, #0
	bne _0224050E
	bl sub_020311F0
	cmp r0, #0
	beq _02240518
_0224050E:
	ldr r0, _022405F4 ; =ov06_02240600
	bl ov06_0223F8BC
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
_02240518:
	mov r0, #0
	bl sub_02030E7C
	cmp r0, #0
	bne _0224052C
	ldr r0, _022405F4 ; =ov06_02240600
	bl ov06_0223F8BC
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
_0224052C:
	mov r0, #0
	mov r1, #5
	bl sub_02031640
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02240546
	ldr r0, _022405F4 ; =ov06_02240600
	bl ov06_0223F8BC
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
_02240546:
	mov r0, #0xa
	bl sub_020315D8
	cmp r0, #0
	beq _0224058E
	bl sub_020314E8
	cmp r0, #0
	beq _0224058E
	ldr r0, _022405F8 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	bne _02240574
	ldr r0, _022405F8 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_0201BD7C
_02240574:
	bl sub_02030F20
	add r1, r4, #0
	add r1, #0x90
	strb r0, [r1]
	add r0, r4, #0
	bl ov06_02240724
	add r0, r5, #0
	bl sub_0200CAB4
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
_0224058E:
	ldr r2, _022405F8 ; =0x02252420
	ldr r0, [r2]
	add r1, r0, #0
	add r1, #0x96
	ldrb r1, [r1]
	cmp r1, #0
	beq _022405F0
	add r1, r0, #0
	add r1, #0x96
	ldrb r1, [r1]
	add r0, #0x96
	sub r1, r1, #1
	strb r1, [r0]
	ldr r2, [r2]
	add r0, r2, #0
	add r0, #0x96
	ldrb r0, [r0]
	cmp r0, #0
	bne _022405F0
	ldr r6, _022405FC ; =0x0224F6AC
	add r5, sp, #0
	mov r3, #8
_022405BA:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _022405BA
	ldr r0, [r6]
	str r0, [r5]
	add r0, r2, #0
	add r0, #0x91
	ldrb r0, [r0]
	cmp r0, #8
	bne _022405E0
	add r2, #0x92
	ldrb r0, [r2]
	mov r1, #0
	add r0, #0x63
	bl ov06_0223EDC4
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
_022405E0:
	add r4, #0x91
	ldrb r0, [r4]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	mov r1, #0
	bl ov06_0223EDC4
_022405F0:
	add sp, #0x44
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022405F4: .word ov06_02240600
_022405F8: .word ov06_02252420
_022405FC: .word ov06_0224F6AC

	thumb_func_start ov06_02240600
ov06_02240600: ; 0x02240600
	push {r3, lr}
	ldr r0, _02240624 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _02240620
	mov r0, #0
	add r1, r0, #0
	bl ov06_0223EDC4
	ldr r0, _02240628 ; =ov06_0224062C
	bl ov06_0223F8BC
_02240620:
	pop {r3, pc}
	nop
_02240624: .word ov06_02252420
_02240628: .word ov06_0224062C

	thumb_func_start ov06_0224062C
ov06_0224062C: ; 0x0224062C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02240660 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _0224065E
	ldr r0, _02240664 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0224065E
	add r0, r4, #0
	bl sub_0200CAB4
	bl ov06_0223F8B4
	ldr r0, _02240660 ; =0x02252420
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
_0224065E:
	pop {r4, pc}
	.align 2, 0
_02240660: .word ov06_02252420
_02240664: .word gSystem

	thumb_func_start ov06_02240668
ov06_02240668: ; 0x02240668
	push {r4, lr}
	ldr r1, _022406A0 ; =0x02252420
	add r4, r0, #0
	add r0, #0x8e
	ldr r1, [r1]
	ldrh r0, [r0]
	ldr r1, [r1, #0x7c]
	bl sub_0202E9AC
	ldr r2, _022406A0 ; =0x02252420
	ldr r0, [r4, #0x58]
	ldr r2, [r2]
	mov r1, #1
	ldr r2, [r2, #0x7c]
	bl BufferPlayersName
	mov r0, #5
	mov r1, #1
	bl ov06_0223EDC4
	bl sub_0204FF4C
	ldr r0, _022406A4 ; =ov06_022406A8
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	pop {r4, pc}
	.align 2, 0
_022406A0: .word ov06_02252420
_022406A4: .word ov06_022406A8

	thumb_func_start ov06_022406A8
ov06_022406A8: ; 0x022406A8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _022406D0 ; =0x02252420
	add r4, r1, #0
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _022406CE
	bl sub_0204FF4C
	add r0, r4, #0
	bl ov06_0223F270
	add r0, r5, #0
	bl sub_0200CAB4
_022406CE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022406D0: .word ov06_02252420

	thumb_func_start ov06_022406D4
ov06_022406D4: ; 0x022406D4
	push {r4, lr}
	add r4, r0, #0
	bl sub_0204FF4C
	ldr r0, _022406E8 ; =ov06_022406EC
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	pop {r4, pc}
	.align 2, 0
_022406E8: .word ov06_022406EC

	thumb_func_start ov06_022406EC
ov06_022406EC: ; 0x022406EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _0224071C ; =0x02252420
	add r4, r1, #0
	ldr r0, [r0]
	add r0, #0x94
	ldrb r0, [r0]
	bl sub_020546C8
	cmp r0, #0
	beq _02240718
	ldr r0, _02240720 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02240718
	add r0, r4, #0
	bl ov06_0223F270
	add r0, r5, #0
	bl sub_0200CAB4
_02240718:
	pop {r3, r4, r5, pc}
	nop
_0224071C: .word ov06_02252420
_02240720: .word gSystem

	thumb_func_start ov06_02240724
ov06_02240724: ; 0x02240724
	push {r3, lr}
	mov r0, #0
	bl sub_02031A24
	ldr r0, _0224074C ; =0x02252420
	mov r1, #2
	ldr r0, [r0]
	add r0, #0x88
	str r1, [r0]
	mov r0, #1
	add r1, r0, #0
	bl sub_020334E8
	bl sub_0202DBE0
	mov r0, #1
	bl sub_0202EE84
	pop {r3, pc}
	nop
_0224074C: .word ov06_02252420

	thumb_func_start ov06_02240750
ov06_02240750: ; 0x02240750
	ldr r0, _0224075C ; =0x02252420
	ldr r3, _02240760 ; =sub_02031258
	ldr r0, [r0]
	add r0, #0x91
	ldrb r0, [r0]
	bx r3
	.align 2, 0
_0224075C: .word ov06_02252420
_02240760: .word sub_02031258

	thumb_func_start ov06_02240764
ov06_02240764: ; 0x02240764
	ldr r0, _02240770 ; =0x02252420
	ldr r3, _02240774 ; =sub_02031248
	ldr r0, [r0]
	add r0, #0x91
	ldrb r0, [r0]
	bx r3
	.align 2, 0
_02240770: .word ov06_02252420
_02240774: .word sub_02031248

	thumb_func_start ov06_02240778
ov06_02240778: ; 0x02240778
	ldr r0, _0224078C ; =0x02252420
	ldr r2, [r0]
	add r0, r2, #0
	add r0, #0x92
	add r2, #0x93
	ldrb r1, [r0]
	ldrb r0, [r2]
	lsl r0, r0, #4
	add r0, r1, r0
	bx lr
	.align 2, 0
_0224078C: .word ov06_02252420

	thumb_func_start ov06_02240790
ov06_02240790: ; 0x02240790
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl ov06_0223EF18
	ldr r0, _022407C8 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x91
	strb r4, [r0]
	sub r0, r4, #3
	cmp r0, #1
	bhi _022407B2
	mov r0, #0
	add r5, #0xac
	str r0, [r5]
_022407B2:
	ldr r0, _022407C8 ; =0x02252420
	ldr r1, [r0]
	add r1, #0x92
	strb r6, [r1]
	ldr r1, [r0]
	add r1, #0x93
	strb r7, [r1]
	ldr r0, [r0]
	bl ov06_0223F090
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022407C8: .word ov06_02252420

	thumb_func_start ov06_022407CC
ov06_022407CC: ; 0x022407CC
	ldr r0, _022407D4 ; =0x02252420
	ldr r3, _022407D8 ; =ov06_0223F270
	ldr r0, [r0]
	bx r3
	.align 2, 0
_022407D4: .word ov06_02252420
_022407D8: .word ov06_0223F270

	thumb_func_start ov06_022407DC
ov06_022407DC: ; 0x022407DC
	push {r4, lr}
	ldr r0, _022407F4 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x88
	ldr r4, [r0]
	cmp r4, #0
	beq _022407EE
	bl ov06_0223EFFC
_022407EE:
	add r0, r4, #0
	pop {r4, pc}
	nop
_022407F4: .word ov06_02252420

	thumb_func_start ov06_022407F8
ov06_022407F8: ; 0x022407F8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl ov06_0223EF18
	ldr r0, _02240830 ; =0x02252420
	ldr r0, [r0]
	add r0, #0x91
	strb r4, [r0]
	sub r0, r4, #3
	cmp r0, #1
	bhi _0224081A
	mov r0, #0
	add r5, #0xac
	str r0, [r5]
_0224081A:
	ldr r0, _02240830 ; =0x02252420
	ldr r1, [r0]
	add r1, #0x92
	strb r6, [r1]
	ldr r1, [r0]
	add r1, #0x93
	strb r7, [r1]
	ldr r0, [r0]
	bl ov06_0223F89C
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02240830: .word ov06_02252420

	thumb_func_start ov06_02240834
ov06_02240834: ; 0x02240834
	ldr r0, _0224083C ; =0x02252420
	ldr r3, _02240840 ; =ov06_0223F8C8
	ldr r0, [r0]
	bx r3
	.align 2, 0
_0224083C: .word ov06_02252420
_02240840: .word ov06_0223F8C8

	thumb_func_start ov06_02240844
ov06_02240844: ; 0x02240844
	push {r4, lr}
	ldr r0, _0224085C ; =0x02252420
	ldr r0, [r0]
	add r0, #0x88
	ldr r4, [r0]
	cmp r4, #0
	beq _02240856
	bl ov06_0223EFFC
_02240856:
	add r0, r4, #0
	pop {r4, pc}
	nop
_0224085C: .word ov06_02252420

	thumb_func_start ov06_02240860
ov06_02240860: ; 0x02240860
	mov r0, #0
	bx lr

	thumb_func_start ov06_02240864
ov06_02240864: ; 0x02240864
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0x54
	add r4, r1, #0
	bl WindowIsInUse
	cmp r0, #0
	bne _0224089E
	add r0, r5, #0
	add r0, #0x54
	bl InitWindow
	ldr r0, [r5, #0x10]
	add r1, r5, #0
	ldr r0, [r0, #8]
	add r1, #0x54
	mov r2, #3
	bl sub_020545B8
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	add r1, r0, #0
	add r0, r5, #0
	add r0, #0x54
	bl sub_02054608
	b _022408A6
_0224089E:
	add r0, r5, #0
	add r0, #0x54
	bl sub_0205464C
_022408A6:
	ldr r0, [r5, #0x68]
	ldr r2, [r5, #0x14]
	add r1, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x64]
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x14]
	bl StringExpandPlaceholders
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	add r2, r0, #0
	add r0, r5, #0
	ldr r1, [r5, #0x18]
	add r0, #0x54
	mov r3, #1
	bl sub_02054658
	str r0, [r5, #0x74]
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_022408D4
ov06_022408D4: ; 0x022408D4
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	beq _022408EC
	add r0, #0x54
	mov r1, #0
	bl ClearFrameAndWindow2
	add r0, r4, #0
	add r0, #0x54
	bl ClearWindowTilemapAndCopyToVram
_022408EC:
	add r4, #0x54
	add r0, r4, #0
	bl RemoveWindow
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_022408F8
ov06_022408F8: ; 0x022408F8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #0x1c]
	ldr r0, [r0, #0xc]
	mov r3, #4
	bl sub_02023C04
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r1, #0
	ldr r0, [r4, #0x64]
	ldr r2, [r4, #0x1c]
	add r3, r1, #0
	bl BufferString
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02240924
ov06_02240924: ; 0x02240924
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r4, r5, #0
	ldr r0, [r0, #0xc]
	mov r1, #0
	add r4, #0x34
	bl sub_02023BA4
	mov r6, #5
	cmp r0, #0
	beq _02240940
	add r6, r6, #1
_02240940:
	add r0, r4, #0
	bl WindowIsInUse
	cmp r0, #0
	bne _022409D2
	add r0, r6, #2
	mov r1, #4
	bl ListMenuItems_New
	str r0, [r5, #8]
	mov r3, #1
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r6, #2
	lsl r0, r0, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	ldr r0, [r0, #8]
	mov r2, #3
	bl AddWindowParameterized
	add r0, r5, #0
	ldr r2, _02240A20 ; =0x000003D9
	add r0, #0x34
	mov r1, #1
	mov r3, #0xb
	bl DrawFrameAndWindow1
	ldr r0, [r5, #8]
	ldr r1, [r5, #0x68]
	mov r2, #0x7b
	mov r3, #0xc
	bl ListMenuItems_AppendFromMsgData
	mov r4, #0
	cmp r6, #0
	ble _022409C4
	mov r7, #0x71
_02240998:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_022408F8
	ldr r0, [r5, #0x68]
	ldr r2, [r5, #0x1c]
	add r1, r7, #0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x64]
	ldr r1, [r5, #0x20]
	ldr r2, [r5, #0x1c]
	bl StringExpandPlaceholders
	ldr r0, [r5, #8]
	ldr r1, [r5, #0x20]
	add r2, r4, #0
	bl ListMenuItems_AddItem
	add r4, r4, #1
	cmp r4, r6
	blt _02240998
_022409C4:
	mov r2, #0x72
	add r3, r2, #0
	ldr r0, [r5, #8]
	ldr r1, [r5, #0x68]
	sub r3, #0x74
	bl ListMenuItems_AppendFromMsgData
_022409D2:
	ldr r4, _02240A24 ; =0x0224F704
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r6, #2
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	ldr r0, [r5, #8]
	mov r1, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0x34
	str r0, [sp, #0x20]
	add r0, r2, #0
	add r2, r5, #0
	str r5, [sp, #0x30]
	add r2, #0x78
	ldrh r2, [r2]
	mov r3, #4
	bl ListMenuInit
	str r0, [r5]
	add r5, #0x34
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_02240A20: .word 0x000003D9
_02240A24: .word ov06_0224F704

	thumb_func_start ov06_02240A28
ov06_02240A28: ; 0x02240A28
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02240A62
	mov r1, #0
	add r2, r1, #0
	bl DestroyListMenu
	add r0, r4, #0
	add r0, #0x34
	mov r1, #1
	bl ClearFrameAndWindow1
	add r1, r4, #0
	add r1, #0x38
	ldrb r1, [r1]
	ldr r0, [r4, #0x34]
	bl ScheduleBgTilemapBufferTransfer
	add r0, r4, #0
	add r0, #0x34
	bl RemoveWindow
	ldr r0, [r4, #8]
	bl ListMenuItems_Delete
	mov r0, #0
	str r0, [r4]
_02240A62:
	pop {r4, pc}

	thumb_func_start ov06_02240A64
ov06_02240A64: ; 0x02240A64
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r2, r5, #0
	ldr r0, [r5]
	mov r1, #0
	add r2, #0x78
	bl ListMenuGetScrollAndRow
	add r0, r5, #0
	add r0, #0x80
	ldrh r6, [r0]
	add r1, r5, #0
	ldr r0, [r5]
	add r1, #0x80
	bl ListMenuGetCurrentItemArrayId
	add r0, r5, #0
	add r0, #0x80
	ldrh r0, [r0]
	cmp r6, r0
	beq _02240A9C
	ldr r0, _02240B00 ; =0x000005DC
	bl PlaySE
_02240A9C:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02240ACC
	add r0, r0, #1
	cmp r4, r0
	beq _02240AB0
	cmp r4, #0xc
	beq _02240AB4
	b _02240AE6
_02240AB0:
	mov r0, #0
	pop {r4, r5, r6, pc}
_02240AB4:
	ldr r0, _02240B00 ; =0x000005DC
	bl PlaySE
	ldr r0, [r5, #0x10]
	mov r1, #0
	add r0, #0xac
	str r1, [r0]
	add r0, r5, #0
	bl ov06_02240A28
	mov r0, #2
	pop {r4, r5, r6, pc}
_02240ACC:
	ldr r0, _02240B00 ; =0x000005DC
	bl PlaySE
	ldr r0, [r5, #0x10]
	mov r1, #0
	add r0, #0xac
	str r1, [r0]
	add r0, r5, #0
	bl ov06_02240A28
	mov r0, #0
	mvn r0, r0
	pop {r4, r5, r6, pc}
_02240AE6:
	ldr r0, _02240B00 ; =0x000005DC
	bl PlaySE
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	ldr r0, [r0, #0xc]
	bl sub_02023BE8
	ldr r1, [r5, #0x10]
	add r1, #0xac
	str r0, [r1]
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_02240B00: .word 0x000005DC

	thumb_func_start ov06_02240B04
ov06_02240B04: ; 0x02240B04
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #3
	mov r1, #4
	ldr r4, _02240BA8 ; =ov06_022522E4
	bl ListMenuItems_New
	str r0, [r5, #0xc]
	mov r0, #0xa
	str r0, [sp]
	mov r0, #9
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02240BAC ; =0x000002F7
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x10]
	add r1, #0x44
	ldr r0, [r0, #8]
	mov r2, #3
	mov r3, #0x16
	bl AddWindowParameterized
	add r0, r5, #0
	ldr r2, _02240BB0 ; =0x000003D9
	add r0, #0x44
	mov r1, #1
	mov r3, #0xb
	bl DrawFrameAndWindow1
	mov r6, #0
_02240B4A:
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x68]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl ListMenuItems_AppendFromMsgData
	add r6, r6, #1
	add r4, #8
	cmp r6, #3
	blt _02240B4A
	ldr r4, _02240BB4 ; =0x0224F704
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r1, #3
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	ldr r0, [r5, #0xc]
	mov r1, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0x44
	str r0, [sp, #0x20]
	add r0, r2, #0
	add r2, r5, #0
	str r5, [sp, #0x30]
	add r2, #0x7a
	ldrh r2, [r2]
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #4]
	add r5, #0x44
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	nop
_02240BA8: .word ov06_022522E4
_02240BAC: .word 0x000002F7
_02240BB0: .word 0x000003D9
_02240BB4: .word ov06_0224F704

	thumb_func_start ov06_02240BB8
ov06_02240BB8: ; 0x02240BB8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r2, r5, #0
	ldr r0, [r5, #4]
	mov r1, #0
	add r2, #0x7a
	bl ListMenuGetScrollAndRow
	add r0, r5, #0
	add r0, #0x82
	ldrh r6, [r0]
	add r1, r5, #0
	ldr r0, [r5, #4]
	add r1, #0x82
	bl ListMenuGetCurrentItemArrayId
	add r0, r5, #0
	add r0, #0x82
	ldrh r0, [r0]
	cmp r6, r0
	beq _02240BF0
	ldr r0, _02240C54 ; =0x000005DC
	bl PlaySE
_02240BF0:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02240C02
	add r0, r0, #1
	cmp r4, r0
	bne _02240C0E
	mov r0, #0
	pop {r4, r5, r6, pc}
_02240C02:
	ldr r0, _02240C54 ; =0x000005DC
	bl PlaySE
	mov r4, #0
	mvn r4, r4
	b _02240C1A
_02240C0E:
	ldr r0, _02240C54 ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	bl ov06_02240A28
_02240C1A:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _02240C50
	mov r1, #0
	add r2, r1, #0
	bl DestroyListMenu
	add r0, r5, #0
	add r0, #0x44
	mov r1, #1
	bl ClearFrameAndWindow1
	add r1, r5, #0
	add r1, #0x48
	ldrb r1, [r1]
	ldr r0, [r5, #0x44]
	bl ScheduleBgTilemapBufferTransfer
	add r0, r5, #0
	add r0, #0x44
	bl RemoveWindow
	ldr r0, [r5, #0xc]
	bl ListMenuItems_Delete
	mov r0, #0
	str r0, [r5, #4]
_02240C50:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02240C54: .word 0x000005DC

	thumb_func_start ov06_02240C58
ov06_02240C58: ; 0x02240C58
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	ldr r2, _02240EFC ; =0x0000013A
	str r0, [sp, #0x14]
	ldr r5, [r0, #0x64]
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [sp, #0x30]
	mov r0, #0xb4
	mov r1, #4
	bl String_New
	str r0, [sp, #0x2c]
	mov r0, #0xb4
	mov r1, #4
	bl String_New
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x14]
	mov r2, #3
	str r0, [sp, #0x24]
	add r0, #0x24
	str r0, [sp, #0x24]
	mov r0, #2
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0x13
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x24]
	ldr r0, [r0, #0x10]
	mov r3, #4
	ldr r0, [r0, #8]
	bl AddWindowParameterized
	ldr r0, [sp, #0x24]
	ldr r2, _02240F00 ; =0x000003D9
	mov r1, #1
	mov r3, #0xb
	bl DrawFrameAndWindow1
	ldr r0, [sp, #0x24]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x14]
	add r1, r0, #0
	add r1, #0x78
	ldrh r1, [r1]
	sub r1, r1, #1
	bl ov06_022408F8
	ldr r0, [sp, #0x30]
	ldr r2, [sp, #0x2c]
	mov r1, #0x51
	bl ReadMsgDataIntoString
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	add r0, r5, #0
	bl StringExpandPlaceholders
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x28]
	mov r3, #0x39
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	mov r6, #0
	mov r4, #0x10
	mov r7, #0xff
_02240CFE:
	add r1, r6, #0
	ldr r0, [sp, #0x30]
	ldr r2, [sp, #0x2c]
	add r1, #0x3d
	bl ReadMsgDataIntoString
	str r4, [sp]
	str r7, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x2c]
	mov r1, #0
	mov r3, #2
	bl AddTextPrinterParameterized
	add r6, r6, #1
	add r4, #0xf
	cmp r6, #9
	blt _02240CFE
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, _02240F04 ; =ov06_022522D8
	ldr r7, _02240F08 ; =ov06_022522CC
	str r0, [sp, #0x20]
	mov r0, #0x10
	str r0, [sp, #0x1c]
_02240D34:
	ldr r0, [sp, #0x14]
	ldrb r1, [r7]
	ldr r0, [r0, #0x10]
	add r0, #0xac
	ldr r0, [r0]
	bl sub_02023B0C
	add r2, r0, #0
	ldr r0, [sp, #0x20]
	ldrb r4, [r0]
	ldrb r0, [r7]
	cmp r0, #0xb
	bls _02240D50
	b _02240E8C
_02240D50:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02240D5C: ; jump table
	.short _02240E8C - _02240D5C - 2 ; case 0
	.short _02240D74 - _02240D5C - 2 ; case 1
	.short _02240D86 - _02240D5C - 2 ; case 2
	.short _02240D9A - _02240D5C - 2 ; case 3
	.short _02240E86 - _02240D5C - 2 ; case 4
	.short _02240DB6 - _02240D5C - 2 ; case 5
	.short _02240E8C - _02240D5C - 2 ; case 6
	.short _02240E34 - _02240D5C - 2 ; case 7
	.short _02240E8C - _02240D5C - 2 ; case 8
	.short _02240E86 - _02240D5C - 2 ; case 9
	.short _02240E86 - _02240D5C - 2 ; case 10
	.short _02240E86 - _02240D5C - 2 ; case 11
_02240D74:
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	mov r3, #1
	bl BufferIntegerAsString
	b _02240E8C
_02240D86:
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	mov r3, #3
	bl BufferIntegerAsString
	b _02240E8C
_02240D9A:
	cmp r2, #0
	bne _02240DA2
	mov r4, #0x52
	b _02240E8C
_02240DA2:
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	mov r3, #3
	bl BufferIntegerAsString
	b _02240E8C
_02240DB6:
	cmp r2, #0
	ldr r0, _02240F0C ; =0x00002710
	blt _02240DD0
	mul r0, r2
	mov r1, #0xfe
	bl _s32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _s32_div_f
	add r6, r0, #0
	b _02240DE4
_02240DD0:
	neg r1, r2
	mul r0, r1
	mov r1, #0xfe
	bl _s32_div_f
	add r0, r0, #5
	mov r1, #0xa
	bl _s32_div_f
	neg r6, r0
_02240DE4:
	add r0, r6, #0
	mov r1, #0xc
	bl _s32_div_f
	bl abs
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	mov r3, #2
	bl BufferIntegerAsString
	add r0, r6, #0
	mov r1, #0xc
	bl _s32_div_f
	add r0, r1, #0
	bl abs
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	mov r3, #2
	bl BufferIntegerAsString
	cmp r6, #0
	bne _02240E2E
	mov r4, #0x52
	b _02240E8C
_02240E2E:
	ble _02240E8C
	add r4, r4, #1
	b _02240E8C
_02240E34:
	cmp r2, #0
	ldr r0, _02240F10 ; =0x00035D2E
	blt _02240E4C
	add r1, r2, #0
	mul r1, r0
	ldr r0, _02240F14 ; =0x0000C350
	add r0, r1, r0
	ldr r1, _02240F18 ; =0x000186A0
	bl _s32_div_f
	add r6, r0, #0
	b _02240E5E
_02240E4C:
	neg r1, r2
	add r2, r1, #0
	mul r2, r0
	ldr r0, _02240F14 ; =0x0000C350
	ldr r1, _02240F18 ; =0x000186A0
	add r0, r2, r0
	bl _s32_div_f
	neg r6, r0
_02240E5E:
	add r0, r6, #0
	bl abs
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	mov r3, #3
	bl BufferIntegerAsString
	cmp r6, #0
	bne _02240E80
	mov r4, #0x52
	b _02240E8C
_02240E80:
	ble _02240E8C
	add r4, r4, #1
	b _02240E8C
_02240E86:
	cmp r2, #0
	bne _02240E8C
	add r4, r4, #1
_02240E8C:
	ldr r0, [sp, #0x30]
	ldr r2, [sp, #0x2c]
	add r1, r4, #0
	bl ReadMsgDataIntoString
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	add r0, r5, #0
	bl StringExpandPlaceholders
	mov r0, #0
	ldr r1, [sp, #0x28]
	add r2, r0, #0
	bl sub_02002E14
	add r4, r0, #0
	ldr r0, [sp, #0x1c]
	mov r3, #0xbf
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x28]
	mov r1, #0
	sub r3, r3, r4
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x20]
	add r7, r7, #1
	add r0, r0, #1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r0, #0xf
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #9
	bge _02240EE0
	b _02240D34
_02240EE0:
	ldr r0, [sp, #0x2c]
	bl String_Delete
	ldr r0, [sp, #0x28]
	bl String_Delete
	ldr r0, [sp, #0x30]
	bl DestroyMsgData
	ldr r0, [sp, #0x24]
	bl CopyWindowToVram
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02240EFC: .word 0x0000013A
_02240F00: .word 0x000003D9
_02240F04: .word ov06_022522D8
_02240F08: .word ov06_022522CC
_02240F0C: .word 0x00002710
_02240F10: .word 0x00035D2E
_02240F14: .word 0x0000C350
_02240F18: .word 0x000186A0

	thumb_func_start ov06_02240F1C
ov06_02240F1C: ; 0x02240F1C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x24
	mov r1, #1
	bl ClearFrameAndWindow1
	add r1, r4, #0
	add r1, #0x28
	ldrb r1, [r1]
	ldr r0, [r4, #0x24]
	bl ScheduleBgTilemapBufferTransfer
	add r4, #0x24
	add r0, r4, #0
	bl RemoveWindow
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02240F40
ov06_02240F40: ; 0x02240F40
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0xc]
	bl SaveArray_Party_Get
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	ldr r2, [r4, #0x6c]
	add r0, #0xac
	ldr r0, [r0]
	bl sub_0206BE48
	cmp r0, #0
	beq _02240F6A
	cmp r0, #1
	beq _02240FAA
	cmp r0, #4
	beq _02240F70
	b _02240FAA
_02240F6A:
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_02240F70:
	ldr r0, _02240FE8 ; =0x000005F3
	bl PlaySE
	add r1, r4, #0
	add r1, #0x78
	ldrh r1, [r1]
	add r0, r4, #0
	sub r1, r1, #1
	bl ov06_022408F8
	ldr r0, [r4, #0x10]
	mov r1, #1
	add r0, #0xac
	ldr r0, [r0]
	bl sub_02023B0C
	mov r1, #1
	str r1, [sp]
	str r1, [sp, #4]
	add r2, r0, #0
	ldr r0, [r4, #0x64]
	add r3, r1, #0
	bl BufferIntegerAsString
	add r0, r4, #0
	mov r1, #0x6b
	bl ov06_02240864
	b _02240FE2
_02240FAA:
	ldr r0, _02240FE8 ; =0x000005F3
	bl PlaySE
	add r1, r4, #0
	add r1, #0x78
	ldrh r1, [r1]
	add r0, r4, #0
	sub r1, r1, #1
	bl ov06_022408F8
	ldr r0, [r4, #0x10]
	mov r1, #3
	add r0, #0xac
	ldr r0, [r0]
	bl sub_02023B0C
	mov r1, #1
	str r1, [sp]
	str r1, [sp, #4]
	add r2, r0, #0
	ldr r0, [r4, #0x64]
	mov r3, #3
	bl BufferIntegerAsString
	add r0, r4, #0
	mov r1, #0x79
	bl ov06_02240864
_02240FE2:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_02240FE8: .word 0x000005F3

	thumb_func_start ov06_02240FEC
ov06_02240FEC: ; 0x02240FEC
	push {r4, lr}
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r1, [r4, #0x7c]
	cmp r1, #0xb
	bls _02241004
	b _0224117A
_02241004:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02241010: ; jump table
	.short _02241028 - _02241010 - 2 ; case 0
	.short _02241036 - _02241010 - 2 ; case 1
	.short _02241054 - _02241010 - 2 ; case 2
	.short _02241086 - _02241010 - 2 ; case 3
	.short _02241092 - _02241010 - 2 ; case 4
	.short _022410B8 - _02241010 - 2 ; case 5
	.short _022410D2 - _02241010 - 2 ; case 6
	.short _022410F0 - _02241010 - 2 ; case 7
	.short _02241104 - _02241010 - 2 ; case 8
	.short _02241126 - _02241010 - 2 ; case 9
	.short _0224117E - _02241010 - 2 ; case 10
	.short _0224113A - _02241010 - 2 ; case 11
_02241028:
	mov r1, #0x6a
	bl ov06_02240864
	ldr r0, [r4, #0x7c]
	add r0, r0, #1
	str r0, [r4, #0x7c]
	b _0224117E
_02241036:
	ldr r0, [r4, #0x74]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_020546C8
	cmp r0, #0
	bne _02241046
	b _0224117E
_02241046:
	add r0, r4, #0
	bl ov06_02240924
	ldr r0, [r4, #0x7c]
	add r0, r0, #1
	str r0, [r4, #0x7c]
	b _0224117E
_02241054:
	bl ov06_02240A64
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0224106C
	ldr r0, [r4, #0x70]
	mov r1, #2
	strh r1, [r0]
	mov r0, #0xb
	str r0, [r4, #0x7c]
	b _0224117E
_0224106C:
	cmp r0, #2
	bne _0224107C
	ldr r0, [r4, #0x70]
	mov r1, #3
	strh r1, [r0]
	mov r0, #0xb
	str r0, [r4, #0x7c]
	b _0224117E
_0224107C:
	cmp r0, #1
	bne _0224117E
	mov r0, #3
	str r0, [r4, #0x7c]
	b _0224117E
_02241086:
	bl ov06_02240B04
	ldr r0, [r4, #0x7c]
	add r0, r0, #1
	str r0, [r4, #0x7c]
	b _0224117E
_02241092:
	bl ov06_02240BB8
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _022410A4
	mov r0, #2
	str r0, [r4, #0x7c]
	b _0224117E
_022410A4:
	cmp r0, #1
	bne _022410AE
	mov r0, #5
	str r0, [r4, #0x7c]
	b _0224117E
_022410AE:
	cmp r0, #2
	bne _0224117E
	mov r0, #7
	str r0, [r4, #0x7c]
	b _0224117E
_022410B8:
	bl ov06_02240F40
	cmp r0, #0
	beq _022410CC
	ldr r0, [r4, #0x70]
	mov r1, #1
	strh r1, [r0]
	mov r0, #0xb
	str r0, [r4, #0x7c]
	b _0224117E
_022410CC:
	mov r0, #6
	str r0, [r4, #0x7c]
	b _0224117E
_022410D2:
	ldr r0, [r4, #0x74]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_020546C8
	cmp r0, #0
	beq _0224117E
	ldr r0, _02241184 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0224117E
	mov r0, #0
	str r0, [r4, #0x7c]
	b _0224117E
_022410F0:
	mov r1, #1
	bl ov06_022408D4
	add r0, r4, #0
	bl ov06_02240C58
	ldr r0, [r4, #0x7c]
	add r0, r0, #1
	str r0, [r4, #0x7c]
	b _0224117E
_02241104:
	ldr r1, _02241184 ; =gSystem
	ldr r2, [r1, #0x48]
	mov r1, #3
	tst r1, r2
	beq _0224117E
	bl ov06_02240F1C
	add r0, r4, #0
	mov r1, #0x6a
	bl ov06_02240864
	add r0, r4, #0
	bl ov06_02240924
	mov r0, #9
	str r0, [r4, #0x7c]
	b _0224117E
_02241126:
	ldr r0, [r4, #0x74]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_020546C8
	cmp r0, #0
	beq _0224117E
	mov r0, #3
	str r0, [r4, #0x7c]
	b _0224117E
_0224113A:
	bl ov06_02240A28
	add r0, r4, #0
	mov r1, #0
	bl ov06_022408D4
	ldr r0, [r4, #0x64]
	bl MessageFormat_Delete
	ldr r0, [r4, #0x68]
	bl DestroyMsgData
	ldr r0, [r4, #0x14]
	bl String_Delete
	ldr r0, [r4, #0x18]
	bl String_Delete
	ldr r0, [r4, #0x1c]
	bl String_Delete
	ldr r0, [r4, #0x20]
	bl String_Delete
	ldr r0, [r4, #0x6c]
	bl sub_0206BB74
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
_0224117A:
	mov r0, #1
	pop {r4, pc}
_0224117E:
	mov r0, #0
	pop {r4, pc}
	nop
_02241184: .word gSystem

	thumb_func_start ov06_02241188
ov06_02241188: ; 0x02241188
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xb
	mov r1, #0x84
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x84
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r4, #0x7c]
	str r5, [r4, #0x10]
	add r5, #0xac
	str r0, [r5]
	mov r0, #4
	bl MessageFormat_New
	str r0, [r4, #0x64]
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xcf
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x68]
	mov r0, #0xb4
	mov r1, #4
	bl String_New
	str r0, [r4, #0x14]
	mov r0, #0xb4
	mov r1, #4
	bl String_New
	str r0, [r4, #0x18]
	mov r0, #0xb4
	mov r1, #4
	bl String_New
	str r0, [r4, #0x1c]
	mov r0, #0xb4
	mov r1, #4
	bl String_New
	str r0, [r4, #0x20]
	mov r0, #0xb
	bl sub_0206BB5C
	str r0, [r4, #0x6c]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022411F4
ov06_022411F4: ; 0x022411F4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl TaskManager_GetFieldSystem
	bl ov06_02241188
	add r2, r0, #0
	ldr r1, _02241210 ; =ov06_02240FEC
	add r0, r5, #0
	str r4, [r2, #0x70]
	bl TaskManager_Call
	pop {r3, r4, r5, pc}
	.align 2, 0
_02241210: .word ov06_02240FEC

	thumb_func_start ov06_02241214
ov06_02241214: ; 0x02241214
	asr r1, r0
	mov r0, #1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start ov06_02241220
ov06_02241220: ; 0x02241220
	mov r2, #1
	ldr r3, [r1]
	lsl r2, r0
	add r0, r3, #0
	eor r0, r2
	str r0, [r1]
	bx lr
	.align 2, 0

	thumb_func_start CheckPastoriaGymButton
CheckPastoriaGymButton: ; 0x02241230
	push {r4, r5, lr}
	sub sp, #0x2c
	ldr r3, _022412E4 ; =0x0224F7B0
	add r4, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x38]
	bl GetPlayerXCoord
	add r5, r0, #0
	ldr r0, [r4, #0x38]
	bl GetPlayerYCoord
	add r1, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, sp, #0x1c
	mov r2, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r2, #0
	bl sub_0204A840
	mov r0, #0
	str r0, [sp]
	add r0, sp, #0xc
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0x10
	mov r2, #3
	add r3, sp, #0x1c
	bl sub_0204A94C
	cmp r0, #0
	beq _022412E0
	add r0, r4, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #1
	bl sub_020254A0
	add r5, r0, #0
	mov r0, #0xb
	mov r1, #4
	bl AllocFromHeapAtEnd
	add r2, r0, #0
	mov r0, #0
	str r0, [r2]
	ldr r0, [sp, #0xc]
	cmp r0, #0xef
	bne _022412B4
	ldr r0, [r4, #0x10]
	ldr r1, _022412E8 ; =ov06_0224158C
	bl TaskManager_Call
	mov r0, #2
	add sp, #0x2c
	strb r0, [r5]
	pop {r4, r5, pc}
_022412B4:
	cmp r0, #0xf0
	bne _022412C8
	ldr r0, [r4, #0x10]
	ldr r1, _022412EC ; =ov06_02241428
	bl TaskManager_Call
	mov r0, #1
	add sp, #0x2c
	strb r0, [r5]
	pop {r4, r5, pc}
_022412C8:
	cmp r0, #0xf1
	bne _022412DC
	ldr r0, [r4, #0x10]
	ldr r1, _022412F0 ; =ov06_02241348
	bl TaskManager_Call
	mov r0, #0
	add sp, #0x2c
	strb r0, [r5]
	pop {r4, r5, pc}
_022412DC:
	bl GF_AssertFail
_022412E0:
	add sp, #0x2c
	pop {r4, r5, pc}
	.align 2, 0
_022412E4: .word ov06_0224F7B0
_022412E8: .word ov06_0224158C
_022412EC: .word ov06_02241428
_022412F0: .word ov06_02241348

	thumb_func_start ov06_022412F4
ov06_022412F4: ; 0x022412F4
	push {r4, r5, r6, lr}
	add r5, r3, #0
	ldr r4, [sp, #0x10]
	bl sub_0204A6E0
	add r6, r0, #0
	bl sub_02054890
	cmp r0, #0
	beq _02241312
	cmp r5, #0
	beq _02241342
	mov r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02241312:
	add r0, r6, #0
	bl sub_0205489C
	cmp r0, #0
	beq _0224132A
	mov r0, #2
	lsl r0, r0, #0x10
	cmp r5, r0
	beq _02241342
	mov r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_0224132A:
	add r0, r6, #0
	bl sub_020548A8
	cmp r0, #0
	beq _02241342
	mov r0, #1
	lsl r0, r0, #0x12
	cmp r5, r0
	beq _02241342
	mov r0, #1
	str r0, [r4]
	pop {r4, r5, r6, pc}
_02241342:
	mov r0, #0
	str r0, [r4]
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02241348
ov06_02241348: ; 0x02241348
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	bl TaskManager_GetFieldSystem
	add r4, r0, #0
	add r0, r5, #0
	bl TaskManager_GetEnvironment
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #3
	bhi _0224141E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224136E: ; jump table
	.short _02241376 - _0224136E - 2 ; case 0
	.short _02241386 - _0224136E - 2 ; case 1
	.short _022413F8 - _0224136E - 2 ; case 2
	.short _02241414 - _0224136E - 2 ; case 3
_02241376:
	ldr r1, [r4, #0x4c]
	mov r0, #0
	bl ov06_022417C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224141E
_02241386:
	ldr r1, [r4, #0x4c]
	mov r0, #1
	bl ov05_021DA03C
	add r6, r0, #0
	ldr r1, [r4, #0x4c]
	mov r0, #2
	bl ov05_021DA03C
	add r7, r0, #0
	ldr r1, [r4, #0x4c]
	mov r0, #3
	bl ov05_021DA03C
	str r0, [sp]
	add r0, r6, #0
	bl ov05_021DA20C
	cmp r0, #0
	beq _0224141E
	add r0, r7, #0
	bl ov05_021DA20C
	cmp r0, #0
	beq _0224141E
	ldr r0, [sp]
	bl ov05_021DA20C
	cmp r0, #0
	beq _0224141E
	add r4, #0xa0
	ldr r0, [r4]
	mov r1, #0xf2
	bl ov05_021E7ED8
	add r4, r0, #0
	add r0, sp, #4
	add r1, r4, #0
	bl ov05_021E7EA0
	mov r0, #1
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #8]
	cmp r0, #0
	bgt _022413EE
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
_022413EE:
	add r0, r4, #0
	add r1, sp, #4
	bl ov05_021E7EB0
	b _0224141E
_022413F8:
	add r4, #0x9c
	mov r0, #0
	ldr r2, [r4]
	add r1, r0, #0
	bl ov05_021F4594
	ldr r0, _02241424 ; =0x0000065A
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _0224141E
_02241414:
	bl FreeToHeap
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224141E:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02241424: .word 0x0000065A

	thumb_func_start ov06_02241428
ov06_02241428: ; 0x02241428
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	bl TaskManager_GetFieldSystem
	add r4, r0, #0
	add r0, r5, #0
	bl TaskManager_GetEnvironment
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #5
	bls _02241444
	b _02241580
_02241444:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02241450: ; jump table
	.short _0224145C - _02241450 - 2 ; case 0
	.short _0224146C - _02241450 - 2 ; case 1
	.short _022414EC - _02241450 - 2 ; case 2
	.short _02241522 - _02241450 - 2 ; case 3
	.short _02241558 - _02241450 - 2 ; case 4
	.short _02241576 - _02241450 - 2 ; case 5
_0224145C:
	ldr r1, [r4, #0x4c]
	mov r0, #1
	bl ov06_022417C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02241580
_0224146C:
	ldr r1, [r4, #0x4c]
	mov r0, #1
	bl ov05_021DA03C
	add r6, r0, #0
	ldr r1, [r4, #0x4c]
	mov r0, #2
	bl ov05_021DA03C
	add r7, r0, #0
	ldr r1, [r4, #0x4c]
	mov r0, #3
	bl ov05_021DA03C
	str r0, [sp]
	add r0, r6, #0
	bl ov05_021DA20C
	cmp r0, #0
	beq _02241580
	add r0, r7, #0
	bl ov05_021DA20C
	cmp r0, #0
	beq _02241580
	ldr r0, [sp]
	bl ov05_021DA20C
	cmp r0, #0
	beq _02241580
	add r4, #0xa0
	ldr r0, [r4]
	mov r1, #0xf2
	bl ov05_021E7ED8
	add r1, r0, #0
	add r0, sp, #0x1c
	bl ov05_021E7EA0
	ldr r1, [sp, #0x20]
	cmp r1, #0
	bne _022414C6
	mov r0, #2
	str r0, [r5]
	b _02241580
_022414C6:
	mov r0, #2
	lsl r0, r0, #0x10
	cmp r1, r0
	bne _022414DA
	add r0, r5, #0
	bl FreeToHeap
	add sp, #0x28
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022414DA:
	lsl r0, r0, #1
	cmp r1, r0
	bne _022414E6
	mov r0, #3
	str r0, [r5]
	b _02241580
_022414E6:
	bl GF_AssertFail
	b _02241580
_022414EC:
	add r4, #0xa0
	ldr r0, [r4]
	mov r1, #0xf2
	bl ov05_021E7ED8
	add r4, r0, #0
	add r0, sp, #0x10
	add r1, r4, #0
	bl ov05_021E7EA0
	mov r0, #1
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0xc
	add r2, r1, r0
	lsl r1, r0, #5
	str r2, [sp, #0x14]
	cmp r2, r1
	blt _02241518
	lsl r0, r0, #5
	str r0, [sp, #0x14]
	mov r0, #4
	str r0, [r5]
_02241518:
	add r0, r4, #0
	add r1, sp, #0x10
	bl ov05_021E7EB0
	b _02241580
_02241522:
	add r4, #0xa0
	ldr r0, [r4]
	mov r1, #0xf2
	bl ov05_021E7ED8
	add r4, r0, #0
	add r0, sp, #4
	add r1, r4, #0
	bl ov05_021E7EA0
	mov r0, #1
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	sub r2, r1, r0
	lsl r1, r0, #5
	str r2, [sp, #8]
	cmp r2, r1
	bgt _0224154E
	lsl r0, r0, #5
	str r0, [sp, #8]
	mov r0, #4
	str r0, [r5]
_0224154E:
	add r0, r4, #0
	add r1, sp, #4
	bl ov05_021E7EB0
	b _02241580
_02241558:
	add r4, #0x9c
	mov r1, #2
	ldr r2, [r4]
	mov r0, #0
	lsl r1, r1, #0x10
	bl ov05_021F4594
	ldr r0, _02241588 ; =0x0000065A
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02241580
_02241576:
	bl FreeToHeap
	add sp, #0x28
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02241580:
	mov r0, #0
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02241588: .word 0x0000065A

	thumb_func_start ov06_0224158C
ov06_0224158C: ; 0x0224158C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	bl TaskManager_GetFieldSystem
	add r4, r0, #0
	add r0, r5, #0
	bl TaskManager_GetEnvironment
	add r5, r0, #0
	ldr r1, [r5]
	cmp r1, #3
	bhi _02241666
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022415B2: ; jump table
	.short _022415BA - _022415B2 - 2 ; case 0
	.short _022415CA - _022415B2 - 2 ; case 1
	.short _0224163E - _022415B2 - 2 ; case 2
	.short _0224165C - _022415B2 - 2 ; case 3
_022415BA:
	ldr r1, [r4, #0x4c]
	mov r0, #2
	bl ov06_022417C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02241666
_022415CA:
	ldr r1, [r4, #0x4c]
	mov r0, #1
	bl ov05_021DA03C
	add r6, r0, #0
	ldr r1, [r4, #0x4c]
	mov r0, #2
	bl ov05_021DA03C
	add r7, r0, #0
	ldr r1, [r4, #0x4c]
	mov r0, #3
	bl ov05_021DA03C
	str r0, [sp]
	add r0, r6, #0
	bl ov05_021DA20C
	cmp r0, #0
	beq _02241666
	add r0, r7, #0
	bl ov05_021DA20C
	cmp r0, #0
	beq _02241666
	ldr r0, [sp]
	bl ov05_021DA20C
	cmp r0, #0
	beq _02241666
	add r4, #0xa0
	ldr r0, [r4]
	mov r1, #0xf2
	bl ov05_021E7ED8
	add r4, r0, #0
	add r0, sp, #4
	add r1, r4, #0
	bl ov05_021E7EA0
	mov r0, #1
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	add r2, r1, r0
	lsl r1, r0, #6
	str r2, [sp, #8]
	cmp r2, r1
	blt _02241634
	lsl r0, r0, #6
	str r0, [sp, #8]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
_02241634:
	add r0, r4, #0
	add r1, sp, #4
	bl ov05_021E7EB0
	b _02241666
_0224163E:
	add r4, #0x9c
	mov r1, #1
	ldr r2, [r4]
	mov r0, #0
	lsl r1, r1, #0x12
	bl ov05_021F4594
	ldr r0, _0224166C ; =0x0000065A
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _02241666
_0224165C:
	bl FreeToHeap
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02241666:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224166C: .word 0x0000065A

	thumb_func_start ov06_02241670
ov06_02241670: ; 0x02241670
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r4, r0, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #1
	bl sub_020254A0
	add r2, sp, #0x20
	ldr r6, _022417C4 ; =0x0224F780
	add r5, r0, #0
	ldmia r6!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r6]
	str r0, [r2]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #0x4c]
	mov r2, #0xf2
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r4, #0x2c]
	bl ov05_021E7FBC
	mov r0, #0x26
	str r0, [sp]
	mov r0, #0
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0x9c
	ldr r1, [r1]
	mov r2, #2
	str r1, [sp, #8]
	mov r1, #1
	mov r3, #0x19
	bl ov05_021F44D8
	ldrb r0, [r5]
	cmp r0, #0
	beq _022416D4
	cmp r0, #1
	beq _022416DE
	cmp r0, #2
	beq _022416EA
	b _022416F6
_022416D4:
	mov r5, #0
	mov r6, #1
	add r7, r6, #0
	str r5, [sp, #0xc]
	b _02241702
_022416DE:
	mov r5, #2
	mov r6, #1
	lsl r5, r5, #0x10
	mov r7, #0
	str r6, [sp, #0xc]
	b _02241702
_022416EA:
	mov r5, #1
	mov r7, #1
	lsl r5, r5, #0x12
	mov r6, #0
	str r7, [sp, #0xc]
	b _02241702
_022416F6:
	bl GF_AssertFail
	mov r5, #0
	mov r6, #1
	add r7, r6, #0
	str r5, [sp, #0xc]
_02241702:
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	mov r1, #0xf2
	bl ov05_021E7ED8
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x10]
	add r0, sp, #0x14
	bl ov05_021E7EA0
	ldr r0, [sp, #0x10]
	add r1, sp, #0x14
	str r5, [sp, #0x18]
	bl ov05_021E7EB0
	add r2, r4, #0
	add r2, #0x9c
	ldr r2, [r2]
	mov r0, #0
	add r1, r5, #0
	bl ov05_021F4594
	ldr r2, [r4, #0x4c]
	mov r0, #0xef
	mov r1, #0
	bl ov05_021DA080
	add r5, r0, #0
	mov r1, #1
	bl ov05_021DA1A8
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021DA1A0
	add r0, r5, #0
	mov r1, #1
	bl ov05_021DA1A4
	add r0, r5, #0
	mov r1, #1
	bl ov05_021DA0DC
	add r0, r5, #0
	bl ov05_021DA138
	ldr r2, [r4, #0x4c]
	mov r0, #0xf0
	mov r1, #0
	bl ov05_021DA080
	add r5, r0, #0
	mov r1, #2
	bl ov05_021DA1A8
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021DA1A0
	add r0, r5, #0
	mov r1, #1
	bl ov05_021DA1A4
	add r0, r5, #0
	mov r1, #1
	bl ov05_021DA0DC
	add r0, r5, #0
	bl ov05_021DA138
	ldr r2, [r4, #0x4c]
	mov r0, #0xf1
	mov r1, #0
	bl ov05_021DA080
	mov r1, #3
	add r4, r0, #0
	bl ov05_021DA1A8
	ldr r1, [sp, #0xc]
	add r0, r4, #0
	bl ov05_021DA1A0
	add r0, r4, #0
	mov r1, #1
	bl ov05_021DA1A4
	add r0, r4, #0
	mov r1, #1
	bl ov05_021DA0DC
	add r0, r4, #0
	bl ov05_021DA138
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022417C4: .word ov06_0224F780

	thumb_func_start ov06_022417C8
ov06_022417C8: ; 0x022417C8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	cmp r0, #2
	bne _022417D8
	mov r6, #1
	mov r4, #2
	mov r5, #3
	b _022417F4
_022417D8:
	cmp r0, #1
	bne _022417E4
	mov r6, #2
	mov r4, #1
	mov r5, #3
	b _022417F4
_022417E4:
	cmp r0, #0
	bne _022417F0
	mov r6, #3
	mov r4, #1
	mov r5, #2
	b _022417F4
_022417F0:
	bl GF_AssertFail
_022417F4:
	add r0, r6, #0
	add r1, r7, #0
	bl ov05_021DA03C
	add r6, r0, #0
	mov r1, #0
	bl ov05_021DA1A0
	add r0, r6, #0
	bl ov05_021DA118
	add r0, r6, #0
	mov r1, #0
	bl ov05_021DA0DC
	add r0, r6, #0
	bl ov05_021DA0E0
	add r0, r4, #0
	add r1, r7, #0
	bl ov05_021DA03C
	add r4, r0, #0
	mov r1, #1
	bl ov05_021DA1A0
	add r0, r4, #0
	bl ov05_021DA118
	add r0, r4, #0
	mov r1, #0
	bl ov05_021DA0DC
	add r0, r4, #0
	bl ov05_021DA0E0
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021DA03C
	add r4, r0, #0
	mov r1, #1
	bl ov05_021DA1A0
	add r0, r4, #0
	bl ov05_021DA118
	add r0, r4, #0
	mov r1, #0
	bl ov05_021DA0DC
	add r0, r4, #0
	bl ov05_021DA0E0
	ldr r0, _02241868 ; =0x0000065A
	bl PlaySE
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02241868: .word 0x0000065A

	thumb_func_start ov06_0224186C
ov06_0224186C: ; 0x0224186C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r5, r0, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #2
	bl sub_020254A0
	add r2, sp, #0x18
	ldr r6, _0224190C ; =0x0224F7A4
	add r4, r0, #0
	ldmia r6!, {r0, r1}
	add r3, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r6]
	str r0, [r2]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #0x4c]
	ldr r2, _02241910 ; =0x00000102
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	bl ov05_021E7FBC
	mov r0, #2
	str r0, [sp]
	mov r0, #0
	add r1, r5, #0
	str r0, [sp, #4]
	add r1, #0x9c
	ldr r1, [r1]
	mov r2, #0xd
	str r1, [sp, #8]
	mov r1, #8
	mov r3, #3
	bl ov05_021F44D8
	ldrb r0, [r4]
	cmp r0, #0
	beq _022418CC
	cmp r0, #1
	beq _022418D0
	b _022418D6
_022418CC:
	mov r4, #0
	b _022418DC
_022418D0:
	mov r4, #0xa
	lsl r4, r4, #0x10
	b _022418DC
_022418D6:
	bl GF_AssertFail
	mov r4, #0
_022418DC:
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, _02241910 ; =0x00000102
	bl ov05_021E7ED8
	add r6, r0, #0
	add r0, sp, #0xc
	add r1, r6, #0
	bl ov05_021E7EA0
	add r0, r6, #0
	add r1, sp, #0xc
	str r4, [sp, #0x10]
	bl ov05_021E7EB0
	add r5, #0x9c
	ldr r2, [r5]
	mov r0, #0
	add r1, r4, #0
	bl ov05_021F4594
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224190C: .word ov06_0224F7A4
_02241910: .word 0x00000102

	thumb_func_start MoveHearthomeGymElevator
MoveHearthomeGymElevator: ; 0x02241914
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0xb
	mov r1, #4
	bl AllocFromHeapAtEnd
	add r6, r0, #0
	mov r0, #0
	str r0, [r6]
	add r0, r5, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #2
	bl sub_020254A0
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	add r1, sp, #0
	bl sub_02055350
	ldr r0, [sp, #4]
	cmp r0, #0
	ldr r0, [r5, #0x10]
	bne _0224195A
	ldr r1, _0224196C ; =ov06_02241974
	add r2, r6, #0
	bl TaskManager_Call
	mov r0, #1
	add sp, #0xc
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224195A:
	ldr r1, _02241970 ; =ov06_02241A44
	add r2, r6, #0
	bl TaskManager_Call
	mov r0, #0
	strb r0, [r4]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_0224196C: .word ov06_02241974
_02241970: .word ov06_02241A44

	thumb_func_start ov06_02241974
ov06_02241974: ; 0x02241974
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #3
	bhi _02241A32
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224199A: ; jump table
	.short _022419A2 - _0224199A - 2 ; case 0
	.short _022419B8 - _0224199A - 2 ; case 1
	.short _02241A02 - _0224199A - 2 ; case 2
	.short _02241A28 - _0224199A - 2 ; case 3
_022419A2:
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl PlayerAvatar_ToggleAutomaticHeightUpdating
	ldr r0, _02241A38 ; =0x00000611
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241A32
_022419B8:
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, _02241A3C ; =0x00000102
	bl ov05_021E7ED8
	add r6, r0, #0
	add r0, sp, #0
	add r1, r6, #0
	bl ov05_021E7EA0
	mov r0, #1
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	add r1, r1, r0
	mov r0, #0xa
	lsl r0, r0, #0x10
	str r1, [sp, #4]
	cmp r1, r0
	blt _022419F0
	str r0, [sp, #4]
	ldr r0, _02241A38 ; =0x00000611
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_022419F0:
	ldr r0, [r5, #0x38]
	ldr r1, [sp, #4]
	bl sub_02055540
	add r0, r6, #0
	add r1, sp, #0
	bl ov05_021E7EB0
	b _02241A32
_02241A02:
	add r2, r5, #0
	add r2, #0x9c
	mov r1, #0xa
	ldr r2, [r2]
	mov r0, #0
	lsl r1, r1, #0x10
	bl ov05_021F4594
	ldr r0, [r5, #0x38]
	mov r1, #1
	bl sub_0205557C
	ldr r0, _02241A40 ; =0x0000061A
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241A32
_02241A28:
	bl FreeToHeap
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02241A32:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02241A38: .word 0x00000611
_02241A3C: .word 0x00000102
_02241A40: .word 0x0000061A

	thumb_func_start ov06_02241A44
ov06_02241A44: ; 0x02241A44
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #3
	bhi _02241AFC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02241A6A: ; jump table
	.short _02241A72 - _02241A6A - 2 ; case 0
	.short _02241A88 - _02241A6A - 2 ; case 1
	.short _02241ACE - _02241A6A - 2 ; case 2
	.short _02241AF2 - _02241A6A - 2 ; case 3
_02241A72:
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl PlayerAvatar_ToggleAutomaticHeightUpdating
	ldr r0, _02241B04 ; =0x00000611
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241AFC
_02241A88:
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, _02241B08 ; =0x00000102
	bl ov05_021E7ED8
	add r6, r0, #0
	add r0, sp, #0
	add r1, r6, #0
	bl ov05_021E7EA0
	mov r0, #1
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #4]
	cmp r0, #0
	bgt _02241ABC
	mov r1, #0
	ldr r0, _02241B04 ; =0x00000611
	str r1, [sp, #4]
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02241ABC:
	ldr r0, [r5, #0x38]
	ldr r1, [sp, #4]
	bl sub_02055540
	add r0, r6, #0
	add r1, sp, #0
	bl ov05_021E7EB0
	b _02241AFC
_02241ACE:
	add r2, r5, #0
	add r2, #0x9c
	mov r0, #0
	ldr r2, [r2]
	add r1, r0, #0
	bl ov05_021F4594
	ldr r0, [r5, #0x38]
	mov r1, #1
	bl sub_0205557C
	ldr r0, _02241B0C ; =0x0000061A
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241AFC
_02241AF2:
	bl FreeToHeap
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02241AFC:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02241B04: .word 0x00000611
_02241B08: .word 0x00000102
_02241B0C: .word 0x0000061A

	thumb_func_start ov06_02241B10
ov06_02241B10: ; 0x02241B10
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	add r6, r2, #0
	mov r4, #0
_02241B1A:
	add r1, r5, r4
	ldrb r0, [r1, #0x10]
	cmp r6, r0
	bne _02241B36
	ldr r0, [r5]
	add r1, #0x28
	add r0, #0xa0
	ldrb r1, [r1]
	ldr r0, [r0]
	bl ov05_021E7ED0
	add r1, r7, #0
	bl ov05_021E7EC0
_02241B36:
	add r4, r4, #1
	cmp r4, #0x18
	blt _02241B1A
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02241B40
ov06_02241B40: ; 0x02241B40
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	add r1, sp, #0
	ldr r0, [r0, #0x38]
	bl sub_02055350
	ldr r1, [sp, #4]
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	lsl r0, r0, #0x18
	ldr r1, [sp]
	lsr r2, r0, #0x18
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	lsl r0, r0, #0x18
	ldr r1, [sp, #8]
	lsr r3, r0, #0x18
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	mov r0, #0
_02241B7C:
	lsl r1, r0, #1
	add r1, r0, r1
	add r6, r4, r1
	add r6, #0x41
	ldrb r6, [r6]
	cmp r2, r6
	bne _02241B9E
	add r6, r4, r1
	add r6, #0x40
	ldrb r6, [r6]
	cmp r3, r6
	bne _02241B9E
	add r1, r4, r1
	add r1, #0x42
	ldrb r1, [r1]
	cmp r5, r1
	beq _02241BAA
_02241B9E:
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x18
	blo _02241B7C
	mov r0, #0x18
_02241BAA:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02241BB0
ov06_02241BB0: ; 0x02241BB0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #3
	bl sub_020254A0
	str r0, [sp, #4]
	mov r0, #0xb
	mov r1, #4
	bl AllocFromHeapAtEnd
	mov r1, #0
	str r1, [r0]
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xe8
	strb r4, [r0]
	lsl r0, r4, #2
	ldr r1, [sp, #4]
	add r0, r5, r0
	add r0, #0x88
	ldr r7, [r0]
	ldr r1, [r1]
	add r0, r4, #0
	bl ov06_02241214
	add r6, r0, #0
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl ov06_02241220
	ldr r0, _02241D64 ; =0x00000127
	cmp r7, r0
	bne _02241C64
	cmp r6, #0
	beq _02241C1E
	add r0, r5, #0
	mov r1, #5
	add r0, #0xf0
	str r1, [r0]
	ldr r2, _02241D68 ; =0x0224FA84
	lsl r1, r4, #4
	ldrb r0, [r2, r1]
	add r3, r2, r1
	lsl r6, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	add r6, r6, r0
	b _02241C34
_02241C1E:
	add r0, r5, #0
	ldr r2, _02241D6C ; =0x0224FA87
	lsl r1, r4, #4
	mov r6, #4
	add r0, #0xf0
	str r6, [r0]
	ldrb r0, [r2, r1]
	lsl r6, r6, #0xd
	add r3, r2, r1
	lsl r0, r0, #0x10
	add r6, r0, r6
_02241C34:
	add r0, r5, #0
	add r0, #0xec
	str r6, [r0]
	lsl r0, r4, #1
	add r0, r4, r0
	ldrb r2, [r2, r1]
	add r1, r5, r0
	add r1, #0x40
	strb r2, [r1]
	add r1, r5, r0
	add r0, r5, r0
	ldrb r2, [r3, #1]
	add r1, #0x41
	add r0, #0x42
	strb r2, [r1]
	ldrb r1, [r3, #2]
	ldr r2, [sp]
	strb r1, [r0]
	ldr r0, [r5]
	ldr r1, _02241D70 ; =ov06_02241F7C
	bl FieldSystem_CreateTask
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02241C64:
	sub r0, r0, #1
	cmp r7, r0
	bne _02241CDA
	cmp r6, #0
	beq _02241C90
	add r1, r5, #0
	mov r0, #2
	add r1, #0xf0
	str r0, [r1]
	ldr r1, _02241D74 ; =0x0224FA86
	lsl r2, r4, #4
	ldrb r1, [r1, r2]
	lsl r0, r0, #0xe
	ldr r3, _02241D68 ; =0x0224FA84
	lsl r1, r1, #0x10
	add r1, r1, r0
	add r0, r5, #0
	add r0, #0xec
	str r1, [r0]
	lsl r0, r4, #1
	add r1, r4, r0
	b _02241CB2
_02241C90:
	add r0, r5, #0
	mov r1, #3
	add r0, #0xf0
	str r1, [r0]
	ldr r0, _02241D78 ; =0x0224FA89
	lsl r2, r4, #4
	ldrb r0, [r0, r2]
	ldr r3, _02241D6C ; =0x0224FA87
	lsl r1, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	add r1, r1, r0
	add r0, r5, #0
	add r0, #0xec
	str r1, [r0]
	lsl r0, r4, #1
	add r1, r4, r0
_02241CB2:
	add r0, r3, r2
	ldrb r3, [r3, r2]
	add r2, r5, r1
	add r2, #0x40
	strb r3, [r2]
	add r2, r5, r1
	ldrb r3, [r0, #1]
	add r2, #0x41
	strb r3, [r2]
	ldrb r2, [r0, #2]
	add r0, r5, r1
	add r0, #0x42
	strb r2, [r0]
	ldr r0, [r5]
	ldr r1, _02241D7C ; =ov06_022420CC
	ldr r2, [sp]
	bl FieldSystem_CreateTask
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02241CDA:
	cmp r6, #0
	beq _02241D1E
	add r0, r5, #0
	mov r1, #1
	add r0, #0xf0
	str r1, [r0]
	ldr r0, _02241D80 ; =0x0224FA85
	lsl r2, r4, #4
	ldrb r0, [r0, r2]
	ldr r3, _02241D68 ; =0x0224FA84
	lsl r1, r0, #0x10
	add r0, r5, #0
	add r0, #0xec
	str r1, [r0]
	lsl r0, r4, #1
	add r1, r4, r0
	ldrb r6, [r3, r2]
	add r0, r3, r2
	add r3, r5, r1
	add r3, #0x40
	strb r6, [r3]
	add r3, r5, r1
	ldrb r6, [r0, #1]
	add r3, #0x41
	strb r6, [r3]
	ldrb r3, [r0, #2]
	add r0, r5, r1
	add r0, #0x42
	strb r3, [r0]
	ldr r0, _02241D84 ; =0x0224FA8A
	ldrb r1, [r0, r2]
	add r0, r5, r4
	strb r1, [r0, #0x10]
	b _02241D54
_02241D1E:
	add r0, r5, #0
	mov r1, #0
	add r0, #0xf0
	str r1, [r0]
	ldr r0, _02241D88 ; =0x0224FA88
	lsl r2, r4, #4
	ldrb r0, [r0, r2]
	ldr r3, _02241D6C ; =0x0224FA87
	lsl r1, r0, #0x10
	add r0, r5, #0
	add r0, #0xec
	str r1, [r0]
	lsl r0, r4, #1
	add r1, r4, r0
	add r0, r3, r2
	ldrb r3, [r3, r2]
	add r2, r5, r1
	add r2, #0x40
	strb r3, [r2]
	add r2, r5, r1
	ldrb r3, [r0, #1]
	add r2, #0x41
	strb r3, [r2]
	ldrb r2, [r0, #2]
	add r0, r5, r1
	add r0, #0x42
	strb r2, [r0]
_02241D54:
	ldr r0, [r5]
	ldr r1, _02241D8C ; =ov06_02241E58
	ldr r2, [sp]
	bl FieldSystem_CreateTask
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02241D64: .word 0x00000127
_02241D68: .word ov06_0224FA84
_02241D6C: .word ov06_0224FA87
_02241D70: .word ov06_02241F7C
_02241D74: .word ov06_0224FA86
_02241D78: .word ov06_0224FA89
_02241D7C: .word ov06_022420CC
_02241D80: .word ov06_0224FA85
_02241D84: .word ov06_0224FA8A
_02241D88: .word ov06_0224FA88
_02241D8C: .word ov06_02241E58

	thumb_func_start ov06_02241D90
ov06_02241D90: ; 0x02241D90
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	ldr r1, [r5, #4]
	add r0, #0xa0
	lsl r1, r1, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	bl ov05_021E7ED0
	str r0, [sp]
	ldr r0, [r5]
	ldr r1, [r5, #8]
	add r0, #0xa0
	lsl r1, r1, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	bl ov05_021E7ED0
	add r7, r0, #0
	ldr r0, [r5]
	ldr r1, [r5, #0xc]
	add r0, #0xa0
	lsl r1, r1, #0x18
	ldr r0, [r0]
	lsr r1, r1, #0x18
	bl ov05_021E7ED0
	add r6, r0, #0
	mov r0, #1
	lsl r0, r0, #0x10
	cmp r4, r0
	blt _02241DE8
	ldr r0, [sp]
	mov r1, #0
	bl ov05_021E7EC0
	add r0, r5, #0
	mov r1, #0
	mov r2, #1
	bl ov06_02241B10
	b _02241DFA
_02241DE8:
	ldr r0, [sp]
	mov r1, #1
	bl ov05_021E7EC0
	mov r1, #1
	add r0, r5, #0
	add r2, r1, #0
	bl ov06_02241B10
_02241DFA:
	mov r0, #0xb
	lsl r0, r0, #0x10
	cmp r4, r0
	blt _02241E16
	add r0, r7, #0
	mov r1, #0
	bl ov05_021E7EC0
	add r0, r5, #0
	mov r1, #0
	mov r2, #2
	bl ov06_02241B10
	b _02241E28
_02241E16:
	add r0, r7, #0
	mov r1, #1
	bl ov05_021E7EC0
	add r0, r5, #0
	mov r1, #1
	mov r2, #2
	bl ov06_02241B10
_02241E28:
	mov r0, #0x15
	lsl r0, r0, #0x10
	cmp r4, r0
	blt _02241E44
	add r0, r6, #0
	mov r1, #0
	bl ov05_021E7EC0
	add r0, r5, #0
	mov r1, #0
	mov r2, #3
	bl ov06_02241B10
	pop {r3, r4, r5, r6, r7, pc}
_02241E44:
	add r0, r6, #0
	mov r1, #1
	bl ov05_021E7EC0
	add r0, r5, #0
	mov r1, #1
	mov r2, #3
	bl ov06_02241B10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_02241E58
ov06_02241E58: ; 0x02241E58
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	ldr r1, [r6, #4]
	add r4, r0, #0
	ldr r5, [r1, #0x24]
	ldr r1, [r4]
	cmp r1, #3
	bhi _02241F68
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02241E82: ; jump table
	.short _02241E8A - _02241E82 - 2 ; case 0
	.short _02241EA0 - _02241E82 - 2 ; case 1
	.short _02241F48 - _02241E82 - 2 ; case 2
	.short _02241F5E - _02241E82 - 2 ; case 3
_02241E8A:
	ldr r0, [r6, #0x38]
	mov r1, #0
	bl PlayerAvatar_ToggleAutomaticHeightUpdating
	ldr r0, _02241F70 ; =0x00000611
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241F68
_02241EA0:
	add r1, r5, #0
	add r1, #0xe8
	ldrb r1, [r1]
	add r0, r6, #0
	add r0, #0xa0
	add r1, r5, r1
	add r1, #0x28
	ldrb r1, [r1]
	ldr r0, [r0]
	bl ov05_021E7ED0
	add r7, r0, #0
	add r0, sp, #0
	add r1, r7, #0
	bl ov05_021E7EA0
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	cmp r0, #0
	bne _02241F00
	mov r0, #2
	ldr r1, [sp, #4]
	lsl r0, r0, #0xe
	add r1, r1, r0
	add r0, r5, #0
	str r1, [sp, #4]
	add r0, #0xec
	ldr r0, [r0]
	cmp r1, r0
	blt _02241F2E
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xe8
	ldrb r0, [r0]
	ldr r1, _02241F74 ; =0x0224FA8B
	lsl r2, r0, #4
	ldrb r1, [r1, r2]
	add r0, r5, r0
	strb r1, [r0, #0x10]
	ldr r0, _02241F70 ; =0x00000611
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241F2E
_02241F00:
	cmp r0, #1
	bne _02241F2A
	mov r0, #2
	ldr r1, [sp, #4]
	lsl r0, r0, #0xe
	sub r1, r1, r0
	add r0, r5, #0
	str r1, [sp, #4]
	add r0, #0xec
	ldr r0, [r0]
	cmp r1, r0
	bgt _02241F2E
	str r0, [sp, #4]
	ldr r0, _02241F70 ; =0x00000611
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241F2E
_02241F2A:
	bl GF_AssertFail
_02241F2E:
	ldr r0, [r6, #0x38]
	ldr r1, [sp, #4]
	bl sub_02055540
	add r0, r7, #0
	add r1, sp, #0
	bl ov05_021E7EB0
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl ov06_02241D90
	b _02241F68
_02241F48:
	ldr r0, [r6, #0x38]
	mov r1, #1
	bl sub_0205557C
	ldr r0, _02241F78 ; =0x0000061A
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02241F68
_02241F5E:
	bl FreeToHeap
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02241F68:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02241F70: .word 0x00000611
_02241F74: .word ov06_0224FA8B
_02241F78: .word 0x0000061A

	thumb_func_start ov06_02241F7C
ov06_02241F7C: ; 0x02241F7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r7, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r0, [r7, #4]
	ldr r5, [r0, #0x24]
	ldr r0, [r7, #0x38]
	bl PlayerAvatar_GetMapObject
	ldr r1, [r4]
	add r6, r0, #0
	cmp r1, #4
	bls _02241FA4
	b _022420BC
_02241FA4:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02241FB0: ; jump table
	.short _02241FBA - _02241FB0 - 2 ; case 0
	.short _02241FD8 - _02241FB0 - 2 ; case 1
	.short _0224207C - _02241FB0 - 2 ; case 2
	.short _02242092 - _02241FB0 - 2 ; case 3
	.short _022420B0 - _02241FB0 - 2 ; case 4
_02241FBA:
	bl sub_0205AD98
	cmp r0, #1
	bne _022420BC
	add r0, r6, #0
	mov r1, #0x49
	bl sub_0205ADDC
	ldr r0, _022420C4 ; =0x00000611
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022420BC
_02241FD8:
	add r1, r5, #0
	add r1, #0xe8
	ldrb r1, [r1]
	add r0, r7, #0
	add r0, #0xa0
	add r1, r5, r1
	add r1, #0x28
	ldrb r1, [r1]
	ldr r0, [r0]
	bl ov05_021E7ED0
	str r0, [sp]
	ldr r1, [sp]
	add r0, sp, #0x10
	bl ov05_021E7EA0
	ldr r0, [r7, #0x38]
	add r1, sp, #4
	bl sub_02055350
	ldr r0, [sp, #4]
	add r1, r5, #0
	str r0, [sp, #0x10]
	add r1, #0xf0
	ldr r1, [r1]
	cmp r1, #4
	bne _0224203C
	add r5, #0xec
	ldr r1, [r5]
	cmp r0, r1
	blt _02242028
	ldr r0, _022420C4 ; =0x00000611
	str r1, [sp, #0x10]
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02242072
_02242028:
	add r0, r6, #0
	bl sub_0205AD98
	cmp r0, #1
	bne _02242072
	add r0, r6, #0
	mov r1, #0x17
	bl sub_0205ADDC
	b _02242072
_0224203C:
	cmp r1, #5
	bne _0224206E
	add r5, #0xec
	ldr r1, [r5]
	cmp r0, r1
	bgt _0224205A
	ldr r0, _022420C4 ; =0x00000611
	str r1, [sp, #0x10]
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02242072
_0224205A:
	add r0, r6, #0
	bl sub_0205AD98
	cmp r0, #1
	bne _02242072
	add r0, r6, #0
	mov r1, #0x16
	bl sub_0205ADDC
	b _02242072
_0224206E:
	bl GF_AssertFail
_02242072:
	ldr r0, [sp]
	add r1, sp, #0x10
	bl ov05_021E7EB0
	b _022420BC
_0224207C:
	bl sub_0205AD98
	cmp r0, #1
	bne _02242092
	add r0, r6, #0
	mov r1, #0x4a
	bl sub_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02242092:
	add r0, r6, #0
	bl sub_0205AE28
	cmp r0, #1
	bne _022420BC
	add r0, r6, #0
	bl sub_0205AE50
	ldr r0, _022420C8 ; =0x0000061A
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022420BC
_022420B0:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022420BC:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_022420C4: .word 0x00000611
_022420C8: .word 0x0000061A

	thumb_func_start ov06_022420CC
ov06_022420CC: ; 0x022420CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r0, [r6, #4]
	ldr r5, [r0, #0x24]
	ldr r0, [r6, #0x38]
	bl PlayerAvatar_GetMapObject
	ldr r1, [r4]
	add r7, r0, #0
	cmp r1, #4
	bhi _02242110
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022420FE: ; jump table
	.short _02242108 - _022420FE - 2 ; case 0
	.short _02242128 - _022420FE - 2 ; case 1
	.short _022421CC - _022420FE - 2 ; case 2
	.short _022421E4 - _022420FE - 2 ; case 3
	.short _02242208 - _022420FE - 2 ; case 4
_02242108:
	bl sub_0205AD98
	cmp r0, #1
	beq _02242112
_02242110:
	b _02242214
_02242112:
	add r0, r7, #0
	mov r1, #0x49
	bl sub_0205ADDC
	ldr r0, _0224221C ; =0x00000611
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02242214
_02242128:
	add r1, r5, #0
	add r1, #0xe8
	ldrb r1, [r1]
	add r0, r6, #0
	add r0, #0xa0
	add r1, r5, r1
	add r1, #0x28
	ldrb r1, [r1]
	ldr r0, [r0]
	bl ov05_021E7ED0
	str r0, [sp]
	ldr r1, [sp]
	add r0, sp, #0x10
	bl ov05_021E7EA0
	ldr r0, [r6, #0x38]
	add r1, sp, #4
	bl sub_02055350
	ldr r0, [sp, #0xc]
	add r1, r5, #0
	str r0, [sp, #0x18]
	add r1, #0xf0
	ldr r1, [r1]
	cmp r1, #3
	bne _0224218C
	add r5, #0xec
	ldr r1, [r5]
	cmp r0, r1
	blt _02242178
	ldr r0, _0224221C ; =0x00000611
	str r1, [sp, #0x18]
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022421C2
_02242178:
	add r0, r7, #0
	bl sub_0205AD98
	cmp r0, #1
	bne _022421C2
	add r0, r7, #0
	mov r1, #0x15
	bl sub_0205ADDC
	b _022421C2
_0224218C:
	cmp r1, #2
	bne _022421BE
	add r5, #0xec
	ldr r1, [r5]
	cmp r0, r1
	bgt _022421AA
	ldr r0, _0224221C ; =0x00000611
	str r1, [sp, #0x18]
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022421C2
_022421AA:
	add r0, r7, #0
	bl sub_0205AD98
	cmp r0, #1
	bne _022421C2
	add r0, r7, #0
	mov r1, #0x14
	bl sub_0205ADDC
	b _022421C2
_022421BE:
	bl GF_AssertFail
_022421C2:
	ldr r0, [sp]
	add r1, sp, #0x10
	bl ov05_021E7EB0
	b _02242214
_022421CC:
	bl sub_0205AD98
	cmp r0, #1
	bne _02242214
	add r0, r7, #0
	mov r1, #0x4a
	bl sub_0205ADDC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02242214
_022421E4:
	ldr r0, [r6, #0x38]
	bl PlayerAvatar_GetMapObject
	add r5, r0, #0
	bl sub_0205AE28
	cmp r0, #1
	bne _02242214
	add r0, r5, #0
	bl sub_0205AE50
	ldr r0, _02242220 ; =0x0000061A
	bl PlaySE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02242214
_02242208:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02242214:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0224221C: .word 0x00000611
_02242220: .word 0x0000061A

	thumb_func_start ov06_02242224
ov06_02242224: ; 0x02242224
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	add r6, r0, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #3
	bl sub_020254A0
	str r0, [sp, #0x10]
	mov r0, #4
	mov r1, #0xf4
	bl AllocFromHeap
	ldr r1, [r6, #4]
	add r2, sp, #0x50
	str r0, [r1, #0x24]
	ldr r0, [r6, #4]
	ldr r4, _022423EC ; =0x0224F78C
	ldr r0, [r0, #0x24]
	add r3, r2, #0
	str r0, [sp, #0x14]
	str r6, [r0]
	ldmia r4!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4]
	str r0, [r2]
	mov r0, #0xa
	lsl r0, r0, #0x10
	str r0, [sp, #0x54]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r6, #0x4c]
	mov r2, #0x4b
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r6, #0x2c]
	lsl r2, r2, #2
	bl ov05_021E7FBC
	ldr r1, [sp, #0x14]
	ldr r2, _022423F0 ; =0x0000012D
	str r0, [r1, #4]
	mov r0, #5
	lsl r0, r0, #0x12
	str r0, [sp, #0x54]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r6, #0x4c]
	add r3, sp, #0x50
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r6, #0x2c]
	bl ov05_021E7FBC
	ldr r1, [sp, #0x14]
	ldr r2, _022423F4 ; =0x0000012E
	str r0, [r1, #8]
	mov r0, #0x1e
	lsl r0, r0, #0x10
	str r0, [sp, #0x54]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r6, #0x4c]
	add r3, sp, #0x50
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r6, #0x2c]
	bl ov05_021E7FBC
	ldr r1, [sp, #0x14]
	ldr r4, _022423F8 ; =0x0224FA80
	str r0, [r1, #0xc]
	add r0, r1, #0
	mov r7, #0
	add r5, r1, #0
	str r0, [sp, #0xc]
_022422CC:
	ldr r1, [sp, #0x10]
	lsl r0, r7, #0x18
	ldr r1, [r1]
	lsr r0, r0, #0x18
	bl ov06_02241214
	cmp r0, #0
	beq _02242310
	ldrb r0, [r4, #7]
	ldrb r1, [r4, #7]
	lsl r0, r0, #0x10
	str r0, [sp, #0x44]
	ldrb r0, [r4, #8]
	lsl r0, r0, #0x10
	str r0, [sp, #0x48]
	ldrb r0, [r4, #9]
	lsl r0, r0, #0x10
	str r0, [sp, #0x4c]
	add r0, r5, #0
	add r0, #0x40
	strb r1, [r0]
	add r0, r5, #0
	ldrb r1, [r4, #8]
	add r0, #0x41
	strb r1, [r0]
	add r0, r5, #0
	ldrb r1, [r4, #9]
	add r0, #0x42
	strb r1, [r0]
	ldr r0, [sp, #0x14]
	ldrb r1, [r4, #0xb]
	add r0, r0, r7
	str r0, [sp, #8]
	b _02242342
_02242310:
	ldrb r0, [r4, #4]
	ldrb r1, [r4, #4]
	lsl r0, r0, #0x10
	str r0, [sp, #0x44]
	ldrb r0, [r4, #5]
	lsl r0, r0, #0x10
	str r0, [sp, #0x48]
	ldrb r0, [r4, #6]
	lsl r0, r0, #0x10
	str r0, [sp, #0x4c]
	add r0, r5, #0
	add r0, #0x40
	strb r1, [r0]
	add r0, r5, #0
	ldrb r1, [r4, #5]
	add r0, #0x41
	strb r1, [r0]
	add r0, r5, #0
	ldrb r1, [r4, #6]
	add r0, #0x42
	strb r1, [r0]
	ldr r0, [sp, #0x14]
	ldrb r1, [r4, #0xa]
	add r0, r0, r7
	str r0, [sp, #8]
_02242342:
	strb r1, [r0, #0x10]
	mov r0, #2
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #2
	ldr r1, [sp, #0x4c]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x4c]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r6, #0x4c]
	add r3, sp, #0x44
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r6, #0x2c]
	ldr r2, [r4]
	bl ov05_021E7FBC
	ldr r1, [sp, #8]
	add r7, r7, #1
	add r1, #0x28
	strb r0, [r1]
	ldr r0, [sp, #0xc]
	str r1, [sp, #8]
	ldr r1, [r4]
	add r0, #0x88
	str r1, [r0]
	ldr r0, [sp, #0xc]
	add r4, #0x10
	add r0, r0, #4
	add r5, r5, #3
	str r0, [sp, #0xc]
	cmp r7, #0x18
	blt _022422CC
	ldr r0, [r6, #0x38]
	add r1, sp, #0x38
	bl sub_02055350
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x3c]
	bl ov06_02241D90
	mov r0, #0x19
	ldr r1, _022423FC ; =0x006A4000
	ldr r2, [r6, #0x20]
	lsl r0, r0, #0xe
	bl Camera_SetPerspectiveClippingPlane
	mov r1, #6
	str r1, [sp]
	ldr r0, _02242400 ; =0x000076A0
	sub r1, r1, #7
	str r0, [sp, #4]
	ldr r0, [r6, #0x44]
	mov r2, #1
	mov r3, #0
	bl ov05_021DBA40
	mov r1, #0
	mov r2, #0
	ldr r0, [r6, #0x44]
	mvn r1, r1
	add r3, r2, #0
	bl ov05_021DBA78
	mov r0, #0
	add r1, r0, #0
	add r2, sp, #0x18
_022423D4:
	add r0, r0, #1
	strb r1, [r2]
	add r1, r1, #2
	add r2, r2, #1
	cmp r0, #0x20
	blt _022423D4
	ldr r0, [r6, #0x44]
	add r1, sp, #0x18
	bl ov05_021DBAA0
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022423EC: .word ov06_0224F78C
_022423F0: .word 0x0000012D
_022423F4: .word 0x0000012E
_022423F8: .word ov06_0224FA80
_022423FC: .word 0x006A4000
_02242400: .word 0x000076A0

	thumb_func_start ov06_02242404
ov06_02242404: ; 0x02242404
	push {r4, lr}
	add r4, r0, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	bl sub_020254B4
	cmp r0, #3
	beq _0224241C
	mov r0, #0
	pop {r4, pc}
_0224241C:
	ldr r0, [r4, #4]
	ldr r4, [r0, #0x24]
	cmp r4, #0
	bne _02242428
	mov r0, #0
	pop {r4, pc}
_02242428:
	add r0, r4, #0
	bl ov06_02241B40
	add r1, r0, #0
	cmp r1, #0x18
	beq _0224243E
	add r0, r4, #0
	bl ov06_02241BB0
	mov r0, #1
	pop {r4, pc}
_0224243E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02242444
ov06_02242444: ; 0x02242444
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x24]
	bl FreeToHeap
	ldr r0, [r4, #4]
	mov r1, #0
	str r1, [r0, #0x24]
	pop {r4, pc}

	thumb_func_start ov06_02242458
ov06_02242458: ; 0x02242458
	push {r4, r5, r6, lr}
	asr r0, r3, #0xf
	lsr r0, r0, #0x10
	add r0, r3, r0
	add r4, r1, #0
	asr r0, r0, #0x10
	mov r1, #0xa
	add r6, r2, #0
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #3
	bls _02242478
	bl GF_AssertFail
_02242478:
	ldr r1, _02242498 ; =0x0224FC00
	lsl r0, r5, #0xa
	add r5, r1, r0
	lsl r0, r6, #5
	add r4, r4, r0
	mov r0, #1
	lsl r0, r0, #0xa
	cmp r4, r0
	blt _0224248E
	bl GF_AssertFail
_0224248E:
	ldrb r1, [r5, r4]
	ldr r0, [sp, #0x10]
	str r1, [r0]
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_02242498: .word ov06_0224FC00

	thumb_func_start ov06_0224249C
ov06_0224249C: ; 0x0224249C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #4]
	str r0, [sp]
	ldr r0, [r0]
	add r1, sp, #8
	ldr r0, [r0, #0x38]
	bl sub_02055350
	ldr r1, [sp, #8]
	ldr r7, _02242524 ; =0x0224F8B8
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	lsl r0, r0, #0x18
	ldr r1, [sp, #0x10]
	lsr r3, r0, #0x18
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	mov r0, #0
_022424CE:
	ldr r1, _02242528 ; =0x0224F834
	lsl r2, r0, #2
	ldr r5, _02242528 ; =0x0224F834
	add r1, r1, r2
	ldrb r2, [r5, r2]
	cmp r3, r2
	bne _02242512
	ldrb r2, [r1, #1]
	cmp r4, r2
	bne _02242512
	ldrb r5, [r1, #3]
	ldrb r1, [r1, #2]
	cmp r1, #0
	beq _022424F4
	lsl r1, r5, #3
	add r1, r7, r1
	ldrb r2, [r1, #6]
	mov r1, #2
	b _022424FC
_022424F4:
	lsl r1, r5, #3
	add r1, r7, r1
	ldrb r2, [r1, #5]
	mov r1, #3
_022424FC:
	ldr r6, [sp]
	add r6, r6, r5
	ldrb r6, [r6, #0x10]
	cmp r2, r6
	bne _02242512
	ldr r2, [sp, #4]
	cmp r1, r2
	bne _02242512
	add sp, #0x14
	add r0, r5, #0
	pop {r4, r5, r6, r7, pc}
_02242512:
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0xf
	blo _022424CE
	mov r0, #0xf
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02242524: .word ov06_0224F8B8
_02242528: .word ov06_0224F834

	thumb_func_start ov06_0224252C
ov06_0224252C: ; 0x0224252C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #4
	bl sub_020254A0
	add r6, r0, #0
	mov r0, #0xb
	mov r1, #4
	bl AllocFromHeapAtEnd
	mov r1, #0
	str r1, [r0]
	strb r4, [r5, #0x1c]
	str r0, [sp]
	ldr r1, [r6]
	add r0, r4, #0
	bl ov06_02241214
	add r7, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl ov06_02241220
	cmp r7, #0
	beq _02242588
	mov r0, #5
	str r0, [r5, #0x24]
	ldr r0, _022425B8 ; =0x0224F8BD
	lsl r1, r4, #3
	ldrb r0, [r0, r1]
	mov r2, #2
	lsl r2, r2, #0x10
	lsl r3, r0, #0x10
	add r2, r3, r2
	str r2, [r5, #0x20]
	add r2, r5, r4
	strb r0, [r2, #0x10]
	ldr r0, _022425BC ; =0x0224F918
	add r1, r0, r1
	b _022425A4
_02242588:
	ldr r0, _022425C0 ; =0x0224F8BE
	lsl r1, r4, #3
	ldrb r0, [r0, r1]
	mov r2, #4
	str r2, [r5, #0x24]
	lsl r3, r0, #0x10
	lsl r2, r2, #0xf
	add r2, r3, r2
	str r2, [r5, #0x20]
	add r2, r5, r4
	strb r0, [r2, #0x10]
	ldr r0, _022425BC ; =0x0224F918
	add r0, r0, r1
	add r1, r0, #4
_022425A4:
	lsl r0, r4, #2
	add r0, r5, r0
	str r1, [r0, #0x28]
	ldr r0, [r5]
	ldr r1, _022425C4 ; =ov06_02242744
	ldr r2, [sp]
	bl FieldSystem_CreateTask
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022425B8: .word ov06_0224F8BD
_022425BC: .word ov06_0224F918
_022425C0: .word ov06_0224F8BE
_022425C4: .word ov06_02242744

	thumb_func_start ov06_022425C8
ov06_022425C8: ; 0x022425C8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #8]
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #4
	bl sub_020254A0
	str r0, [sp, #0x10]
	mov r0, #4
	mov r1, #0x58
	bl AllocFromHeap
	ldr r1, [sp, #8]
	ldr r5, _0224268C ; =0x0224F8B8
	ldr r1, [r1, #4]
	ldr r7, _02242690 ; =0x0224F918
	str r0, [r1, #0x24]
	ldr r0, [sp, #8]
	ldr r1, [sp, #8]
	ldr r0, [r0, #4]
	mov r4, #0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x14]
	str r1, [r0]
	add r6, r0, #0
_02242600:
	ldr r1, [sp, #0x10]
	lsl r0, r4, #0x18
	ldr r1, [r1]
	lsr r0, r0, #0x18
	bl ov06_02241214
	cmp r0, #0
	beq _0224262E
	ldrb r0, [r5, #6]
	lsl r1, r0, #0x10
	str r1, [sp, #0x18]
	ldr r1, _02242694 ; =0xFFFF0000
	str r1, [sp, #0x1c]
	ldrb r1, [r5, #4]
	lsl r1, r1, #0x10
	str r1, [sp, #0x20]
	ldr r1, [sp, #0x14]
	add r1, r1, r4
	strb r0, [r1, #0x10]
	add r0, r7, #4
	str r1, [sp, #0xc]
	str r0, [r6, #0x28]
	b _02242648
_0224262E:
	ldrb r0, [r5, #5]
	lsl r1, r0, #0x10
	str r1, [sp, #0x18]
	ldr r1, _02242694 ; =0xFFFF0000
	str r1, [sp, #0x1c]
	ldrb r1, [r5, #4]
	lsl r1, r1, #0x10
	str r1, [sp, #0x20]
	ldr r1, [sp, #0x14]
	add r1, r1, r4
	strb r0, [r1, #0x10]
	str r1, [sp, #0xc]
	str r7, [r6, #0x28]
_02242648:
	mov r0, #2
	ldr r1, [sp, #0x18]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x18]
	mov r0, #2
	ldr r1, [sp, #0x20]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #8]
	ldr r1, [sp, #8]
	ldr r0, [r0, #0x4c]
	add r3, sp, #0x18
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [r1, #0x2c]
	add r0, #0xa0
	ldr r0, [r0]
	ldr r2, [r5]
	bl ov05_021E7FBC
	ldr r1, [sp, #0xc]
	add r4, r4, #1
	strb r0, [r1, #4]
	add r5, #8
	add r7, #8
	add r6, r6, #4
	cmp r4, #0xc
	blt _02242600
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224268C: .word ov06_0224F8B8
_02242690: .word ov06_0224F918
_02242694: .word 0xFFFF0000

	thumb_func_start ov06_02242698
ov06_02242698: ; 0x02242698
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x24]
	bl FreeToHeap
	ldr r0, [r4, #4]
	mov r1, #0
	str r1, [r0, #0x24]
	pop {r4, pc}

	thumb_func_start ov06_022426AC
ov06_022426AC: ; 0x022426AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	bl sub_020254B4
	cmp r0, #4
	beq _022426C4
	mov r0, #0
	pop {r3, r4, r5, pc}
_022426C4:
	ldr r0, [r5, #4]
	ldr r4, [r0, #0x24]
	cmp r4, #0
	bne _022426D0
	mov r0, #0
	pop {r3, r4, r5, pc}
_022426D0:
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	add r0, r4, #0
	bl ov06_0224249C
	add r1, r0, #0
	cmp r1, #0xf
	beq _022426F0
	add r0, r4, #0
	bl ov06_0224252C
	mov r0, #1
	pop {r3, r4, r5, pc}
_022426F0:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_022426F4
ov06_022426F4: ; 0x022426F4
	push {r4, r5, r6, r7}
	ldr r0, [r0, #4]
	ldr r6, _02242740 ; =0x0224F8B8
	ldr r4, [r0, #0x24]
	mov ip, r2
	mov r7, #0
_02242700:
	ldrb r2, [r6, #4]
	mov r0, ip
	cmp r0, r2
	bne _02242730
	ldr r5, [r4, #0x28]
	mov r3, #0
_0224270C:
	ldrb r2, [r5, #1]
	cmp r2, #0
	beq _02242730
	ldrb r0, [r5]
	cmp r0, r1
	bgt _02242728
	add r0, r0, r2
	cmp r1, r0
	bge _02242728
	ldr r1, [sp, #0x10]
	mov r0, #1
	str r0, [r1]
	pop {r4, r5, r6, r7}
	bx lr
_02242728:
	add r3, r3, #1
	add r5, r5, #2
	cmp r3, #2
	blt _0224270C
_02242730:
	add r7, r7, #1
	add r6, #8
	add r4, r4, #4
	cmp r7, #0xc
	blt _02242700
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_02242740: .word ov06_0224F8B8

	thumb_func_start ov06_02242744
ov06_02242744: ; 0x02242744
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r0, [r6, #4]
	ldr r5, [r0, #0x24]
	ldr r0, [r6, #0x38]
	bl PlayerAvatar_GetMapObject
	add r7, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _0224283A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02242776: ; jump table
	.short _0224277E - _02242776 - 2 ; case 0
	.short _022427A4 - _02242776 - 2 ; case 1
	.short _02242808 - _02242776 - 2 ; case 2
	.short _0224282E - _02242776 - 2 ; case 3
_0224277E:
	ldr r0, _02242840 ; =0x00000616
	bl PlaySE
	ldr r0, [r5, #0x24]
	cmp r0, #4
	bne _02242794
	add r0, r7, #0
	mov r1, #0xf
	bl sub_0205ADDC
	b _0224279C
_02242794:
	add r0, r7, #0
	mov r1, #0xe
	bl sub_0205ADDC
_0224279C:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0224283A
_022427A4:
	ldrb r1, [r5, #0x1c]
	add r6, #0xa0
	ldr r0, [r6]
	add r1, r5, r1
	ldrb r1, [r1, #4]
	bl ov05_021E7ED0
	add r6, r0, #0
	add r0, sp, #0
	add r1, r6, #0
	bl ov05_021E7EA0
	ldr r0, [r5, #0x24]
	cmp r0, #4
	bne _022427DC
	mov r0, #2
	ldr r1, [sp]
	lsl r0, r0, #0xc
	add r1, r1, r0
	str r1, [sp]
	ldr r0, [r5, #0x20]
	cmp r1, r0
	blt _022427FE
	str r0, [sp]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022427FE
_022427DC:
	cmp r0, #5
	bne _022427FA
	mov r0, #2
	ldr r1, [sp]
	lsl r0, r0, #0xc
	sub r1, r1, r0
	str r1, [sp]
	ldr r0, [r5, #0x20]
	cmp r1, r0
	bgt _022427FE
	str r0, [sp]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _022427FE
_022427FA:
	bl GF_AssertFail
_022427FE:
	add r0, r6, #0
	add r1, sp, #0
	bl ov05_021E7EB0
	b _0224283A
_02242808:
	ldr r0, [r6, #0x38]
	bl PlayerAvatar_GetMapObject
	add r5, r0, #0
	bl sub_0205AE28
	cmp r0, #1
	bne _0224283A
	add r0, r5, #0
	bl sub_0205AE50
	ldr r0, _02242840 ; =0x00000616
	mov r1, #0
	bl sub_020054F0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0224283A
_0224282E:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224283A:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02242840: .word 0x00000616

	thumb_func_start ov06_02242844
ov06_02242844: ; 0x02242844
	push {r3, lr}
	cmp r0, #0
	beq _02242854
	cmp r0, #1
	beq _02242858
	cmp r0, #2
	beq _0224285C
	b _02242860
_02242854:
	mov r0, #3
	pop {r3, pc}
_02242858:
	mov r0, #6
	pop {r3, pc}
_0224285C:
	mov r0, #0xd
	pop {r3, pc}
_02242860:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov06_02242868
ov06_02242868: ; 0x02242868
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrb r0, [r5, #7]
	add r6, r1, #0
	mov r7, #0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _0224287E
	cmp r0, #1
	beq _02242882
	b _02242886
_0224287E:
	add r7, r2, #4
	b _0224288A
_02242882:
	add r7, r2, #0
	b _0224288A
_02242886:
	bl GF_AssertFail
_0224288A:
	ldrb r0, [r5, #7]
	mov r4, #0
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	cmp r0, #3
	bls _0224289A
	bl GF_AssertFail
_0224289A:
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	lsl r0, r0, #0xe
	add r0, r4, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r6, #3
	bls _022428B0
	bl GF_AssertFail
_022428B0:
	lsl r0, r6, #0x1e
	asr r1, r0, #0x10
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _022428C4
	add r0, r4, r1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _022428D4
_022428C4:
	cmp r0, #1
	bne _022428D0
	sub r0, r4, r1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _022428D4
_022428D0:
	bl GF_AssertFail
_022428D4:
	str r4, [r7]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_022428D8
ov06_022428D8: ; 0x022428D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #5
	bl sub_020254A0
	str r0, [sp, #0xc]
	mov r0, #4
	mov r1, #0x1c
	bl AllocFromHeap
	ldr r1, [r5, #4]
	str r0, [r1, #0x24]
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	ldr r1, [r0, #4]
	ldr r0, [sp, #0x10]
	strb r1, [r0, #0x11]
	ldr r0, [sp, #0xc]
	ldr r1, [r0]
	ldr r0, [sp, #0x10]
	strb r1, [r0, #0x13]
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl ov06_02242844
	mov r6, #0
	str r0, [sp, #8]
	cmp r0, #0
	ble _022429A6
	add r7, r6, #0
_02242926:
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #4]
	lsl r1, r0, #2
	ldr r0, _022429AC ; =0x0224F798
	ldr r0, [r0, r1]
	add r4, r0, r7
	ldrb r0, [r4, #4]
	lsl r2, r0, #0x10
	str r2, [sp, #0x20]
	ldrb r0, [r4, #5]
	lsl r1, r0, #0x10
	str r1, [sp, #0x24]
	ldrb r0, [r4, #6]
	lsl r3, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	add r0, r2, r0
	str r0, [sp, #0x20]
	mov r0, #2
	lsl r0, r0, #0xe
	str r3, [sp, #0x28]
	add r0, r3, r0
	str r0, [sp, #0x28]
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02242966
	mov r0, #2
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x24]
_02242966:
	mov r0, #0
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r1, [r1]
	add r0, r4, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, sp, #0x14
	bl ov06_02242868
	add r0, sp, #0x14
	str r0, [sp]
	ldr r0, [r5, #0x4c]
	add r3, sp, #0x20
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	ldr r2, [r4]
	bl ov05_021E7FBC
	ldr r1, [sp, #0x10]
	add r7, #8
	add r1, r1, r6
	strb r0, [r1, #4]
	ldr r0, [sp, #8]
	add r6, r6, #1
	cmp r6, r0
	blt _02242926
_022429A6:
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_022429AC: .word ov06_0224F798

	thumb_func_start ov06_022429B0
ov06_022429B0: ; 0x022429B0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x24]
	bl FreeToHeap
	ldr r0, [r4, #4]
	mov r1, #0
	str r1, [r0, #0x24]
	pop {r4, pc}

	thumb_func_start ov06_022429C4
ov06_022429C4: ; 0x022429C4
	push {r4, r5, r6, r7}
	ldr r0, [r0, #4]
	add r3, r1, #0
	add r1, r2, #0
	ldr r2, [r0, #0x24]
	mov r4, #0x14
	ldrb r0, [r2, #0x11]
	ldrb r2, [r2, #0x13]
	add r5, r0, #0
	mul r5, r4
	ldr r4, _02242A2C ; =ov06_022522FC
	lsl r2, r2, #2
	ldr r6, [r4, r5]
	ldr r4, _02242A30 ; =ov06_02252300
	add r4, r4, r5
	ldr r2, [r2, r4]
	mov r5, #0
	mov ip, r2
	lsl r2, r0, #2
	ldr r0, _02242A34 ; =0x0224F774
	cmp r6, #0
	ldr r7, [r0, r2]
	ble _02242A26
_022429F2:
	mov r0, ip
	ldrb r0, [r0, r5]
	lsl r0, r0, #2
	ldrb r2, [r7, r0]
	add r4, r7, r0
	cmp r2, r3
	bgt _02242A20
	ldrb r0, [r4, #2]
	add r0, r2, r0
	cmp r3, r0
	bge _02242A20
	ldrb r0, [r4, #1]
	cmp r0, r1
	bgt _02242A20
	ldrb r2, [r4, #3]
	add r0, r0, r2
	cmp r1, r0
	bge _02242A20
	ldr r1, [sp, #0x10]
	mov r0, #1
	str r0, [r1]
	pop {r4, r5, r6, r7}
	bx lr
_02242A20:
	add r5, r5, #1
	cmp r5, r6
	blt _022429F2
_02242A26:
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_02242A2C: .word ov06_022522FC
_02242A30: .word ov06_02252300
_02242A34: .word ov06_0224F774

	thumb_func_start RotateSunyshoreGymGear
RotateSunyshoreGymGear: ; 0x02242A38
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #5
	bl sub_020254A0
	add r6, r0, #0
	ldr r0, [r7, #4]
	mov r1, #4
	ldr r4, [r0, #0x24]
	mov r0, #0xb
	bl AllocFromHeapAtEnd
	mov r1, #0
	str r1, [r0]
	strh r5, [r4, #0x14]
	strh r1, [r4, #0x16]
	str r0, [sp]
	ldr r0, [r6, #4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl ov06_02242844
	strb r0, [r4, #0x12]
	ldr r0, [r6]
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	cmp r5, #0
	bne _02242A94
	mov r1, #1
	lsl r1, r1, #0xe
	add r0, r0, #1
	strh r1, [r4, #0x18]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	b _02242ACE
_02242A94:
	cmp r5, #1
	bne _02242AAA
	mov r1, #1
	sub r0, r0, #1
	lsl r1, r1, #0xe
	lsl r0, r0, #0x18
	strh r1, [r4, #0x18]
	asr r0, r0, #0x18
	bpl _02242ACE
	mov r0, #3
	b _02242ACE
_02242AAA:
	cmp r5, #2
	bne _02242AC8
	mov r1, #2
	lsl r1, r1, #0xe
	add r0, r0, #2
	strh r1, [r4, #0x18]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	b _02242ACE
_02242AC8:
	bl GF_AssertFail
	pop {r3, r4, r5, r6, r7, pc}
_02242ACE:
	str r0, [r6]
	strb r0, [r4, #0x13]
	ldr r0, _02242AE4 ; =0x0000063F
	bl PlaySE
	ldr r0, [r7, #0x10]
	ldr r1, _02242AE8 ; =ov06_02242AEC
	ldr r2, [sp]
	bl TaskManager_Call
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02242AE4: .word 0x0000063F
_02242AE8: .word ov06_02242AEC

	thumb_func_start ov06_02242AEC
ov06_02242AEC: ; 0x02242AEC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	str r0, [sp, #8]
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	ldr r1, [sp, #8]
	str r0, [sp, #4]
	ldr r1, [r1, #4]
	ldr r4, [r1, #0x24]
	add r1, r0, #0
	ldr r1, [r1]
	cmp r1, #0
	beq _02242B14
	cmp r1, #1
	beq _02242BCC
	b _02242BD6
_02242B14:
	ldrh r2, [r4, #0x18]
	mov r0, #1
	ldrh r1, [r4, #0x16]
	lsl r0, r0, #0xa
	str r0, [sp]
	add r0, r1, r0
	cmp r0, r2
	ble _02242B2C
	sub r0, r0, r2
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
_02242B2C:
	ldrh r1, [r4, #0x16]
	ldr r0, [sp]
	add r0, r1, r0
	strh r0, [r4, #0x16]
	ldrh r0, [r4, #0x14]
	cmp r0, #1
	bne _02242B44
	ldr r0, [sp]
	neg r0, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
_02242B44:
	ldrb r0, [r4, #0x12]
	mov r5, #0
	cmp r0, #0
	bls _02242BB8
	ldr r0, [sp]
	neg r0, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
_02242B56:
	ldr r0, [sp, #8]
	add r1, r4, r5
	add r0, #0xa0
	ldrb r1, [r1, #4]
	ldr r0, [r0]
	bl ov05_021E7ED0
	bl ov05_021E7E9C
	ldrb r1, [r4, #0x11]
	lsl r2, r1, #2
	ldr r1, _02242BDC ; =0x0224F798
	ldr r2, [r1, r2]
	lsl r1, r5, #3
	add r1, r2, r1
	ldrb r2, [r1, #7]
	lsl r2, r2, #0x1d
	lsr r2, r2, #0x1f
	cmp r2, #1
	bne _02242B82
	ldr r7, [sp, #0xc]
	b _02242B84
_02242B82:
	ldr r7, [sp]
_02242B84:
	ldrb r1, [r1, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1f
	beq _02242B92
	cmp r1, #1
	beq _02242B96
	b _02242B9A
_02242B92:
	add r6, r0, #4
	b _02242B9E
_02242B96:
	add r6, r0, #0
	b _02242B9E
_02242B9A:
	bl GF_AssertFail
_02242B9E:
	ldr r0, [r6]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r0, r0, r7
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [r6]
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldrb r0, [r4, #0x12]
	cmp r5, r0
	blo _02242B56
_02242BB8:
	ldrh r1, [r4, #0x16]
	ldrh r0, [r4, #0x18]
	cmp r1, r0
	blo _02242BD6
	ldr r0, [sp, #4]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [r0]
	b _02242BD6
_02242BCC:
	bl FreeToHeap
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02242BD6:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02242BDC: .word ov06_0224F798

	thumb_func_start ov06_02242BE0
ov06_02242BE0: ; 0x02242BE0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r2, [sp]
	add r5, r0, #0
	add r6, r1, #0
	str r3, [sp, #4]
	bl TaskManager_GetFieldSystem
	add r7, r0, #0
	ldr r0, _02242C70 ; =0x0000067C
	bl PlaySE
	mov r1, #0x11
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	add r4, r0, #0
	bne _02242C0E
	bl GF_AssertFail
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02242C0E:
	mov r2, #0x11
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	add r2, sp, #0x10
	ldrb r2, [r2, #0x10]
	ldr r3, [sp, #0x24]
	add r0, r7, #0
	add r1, r4, #0
	bl ov06_02242C78
	ldr r0, [r4]
	add r1, r4, #0
	ldr r0, [r0, #8]
	add r1, #0x14
	mov r2, #3
	bl sub_020545B8
	ldr r0, [r4]
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	add r1, r0, #0
	add r0, r4, #0
	add r0, #0x14
	bl sub_02054608
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0
	bl ov06_02243080
	add r0, r4, #0
	bl ov06_022430E0
	ldr r2, [sp]
	ldr r3, [sp, #4]
	add r0, r4, #0
	add r1, r6, #0
	bl ov06_02242CDC
	ldr r1, _02242C74 ; =ov06_02242EC0
	add r0, r5, #0
	add r2, r4, #0
	bl TaskManager_Call
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02242C70: .word 0x0000067C
_02242C74: .word ov06_02242EC0

	thumb_func_start ov06_02242C78
ov06_02242C78: ; 0x02242C78
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	add r4, r0, #0
	add r5, r1, #0
	ldr r2, _02242CD8 ; =0x00000141
	mov r0, #1
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r5, #0x54]
	mov r0, #4
	bl MessageFormat_New
	str r0, [r5, #0x58]
	add r0, r5, #0
	str r4, [r5]
	add r0, #0x5d
	strb r6, [r0]
	add r0, r5, #0
	mov r1, #0
	add r0, #0x5e
	strb r1, [r0]
	add r2, r5, #0
	add r4, r1, #0
_02242CAA:
	add r0, r2, #0
	add r0, #0x90
	str r4, [r0]
	add r0, r2, #0
	add r0, #0x94
	add r1, r1, #1
	add r2, #8
	str r4, [r0]
	cmp r1, #0x10
	blt _02242CAA
	mov r6, #0x40
	mov r7, #4
_02242CC2:
	add r0, r6, #0
	add r1, r7, #0
	bl String_New
	str r0, [r5, #0x24]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xc
	blt _02242CC2
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02242CD8: .word 0x00000141

	thumb_func_start ov06_02242CDC
ov06_02242CDC: ; 0x02242CDC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r0, #0
	str r2, [sp]
	mov r0, #0x14
	str r0, [sp, #4]
	mov r0, #0xe
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r6, r1, #0
	add r5, r3, #0
	ldr r0, [r0, #8]
	add r1, r4, #4
	mov r2, #3
	add r3, r6, #0
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r2, _02242D44 ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl LoadUserFrameGfx1
	ldr r2, _02242D44 ; =0x000003D9
	add r0, r4, #4
	mov r1, #1
	mov r3, #0xb
	bl DrawFrameAndWindow1
	add r0, r4, #0
	bl ov06_02242DA8
	add r0, r4, #0
	add r0, #0x68
	mov r1, #0
	add r2, r5, #0
	mov r3, #4
	bl ListMenuInit
	add r4, #0x88
	str r0, [r4]
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02242D44: .word 0x000003D9

	thumb_func_start ov06_02242D48
ov06_02242D48: ; 0x02242D48
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	add r2, r5, #0
	add r2, #0x5e
	ldrb r2, [r2]
	ldr r0, [r5, #0x54]
	lsl r2, r2, #2
	add r2, r5, r2
	ldr r2, [r2, #0x24]
	bl ReadMsgDataIntoString
	add r0, r5, #0
	add r0, #0x5e
	ldrb r2, [r0]
	lsl r0, r2, #2
	add r0, r5, r0
	ldr r1, [r0, #0x24]
	lsl r0, r2, #3
	add r0, r5, r0
	add r0, #0x90
	str r1, [r0]
	cmp r4, #0xfa
	bne _02242D8C
	add r0, r5, #0
	add r0, #0x5e
	ldrb r0, [r0]
	mov r1, #2
	mvn r1, r1
	lsl r0, r0, #3
	add r0, r5, r0
	add r0, #0x94
	str r1, [r0]
	b _02242D9A
_02242D8C:
	add r0, r5, #0
	add r0, #0x5e
	ldrb r0, [r0]
	lsl r0, r0, #3
	add r0, r5, r0
	add r0, #0x94
	str r4, [r0]
_02242D9A:
	add r0, r5, #0
	add r0, #0x5e
	ldrb r0, [r0]
	add r5, #0x5e
	add r0, r0, #1
	strb r0, [r5]
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02242DA8
ov06_02242DA8: ; 0x02242DA8
	push {r3, r4}
	add r1, r0, #0
	add r1, #0x90
	str r1, [r0, #0x68]
	mov r1, #0
	ldr r2, _02242E8C ; =ov06_02242E9C
	str r1, [r0, #0x6c]
	str r2, [r0, #0x70]
	add r2, r0, #4
	str r2, [r0, #0x74]
	add r2, r0, #0
	add r2, #0x5e
	ldrb r3, [r2]
	add r2, r0, #0
	add r2, #0x78
	strh r3, [r2]
	add r2, r0, #0
	mov r3, #6
	add r2, #0x7a
	strh r3, [r2]
	add r2, r0, #0
	mov r3, #1
	add r2, #0x7c
	strb r3, [r2]
	add r2, r0, #0
	mov r3, #0xc
	add r2, #0x7d
	strb r3, [r2]
	add r2, r0, #0
	add r2, #0x7e
	strb r1, [r2]
	add r1, r0, #0
	add r1, #0x7f
	ldrb r3, [r1]
	mov r1, #0xf
	mov r2, #8
	bic r3, r1
	orr r3, r2
	add r2, r0, #0
	add r2, #0x7f
	strb r3, [r2]
	add r2, r0, #0
	add r2, #0x7f
	ldrb r4, [r2]
	mov r2, #0xf0
	mov r3, #0x10
	bic r4, r2
	orr r4, r3
	add r3, r0, #0
	add r3, #0x7f
	strb r4, [r3]
	add r3, r0, #0
	add r3, #0x80
	ldrb r3, [r3]
	bic r3, r1
	mov r1, #0xf
	orr r3, r1
	add r1, r0, #0
	add r1, #0x80
	strb r3, [r1]
	add r1, r0, #0
	add r1, #0x80
	ldrb r3, [r1]
	mov r1, #0x20
	bic r3, r2
	add r2, r3, #0
	orr r2, r1
	add r1, r0, #0
	add r1, #0x80
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0x82
	ldrh r2, [r1]
	mov r1, #7
	bic r2, r1
	add r1, r0, #0
	add r1, #0x82
	strh r2, [r1]
	add r1, r0, #0
	add r1, #0x82
	ldrh r2, [r1]
	mov r1, #0x78
	bic r2, r1
	add r1, r0, #0
	add r1, #0x82
	strh r2, [r1]
	add r1, r0, #0
	add r1, #0x82
	ldrh r2, [r1]
	ldr r1, _02242E90 ; =0xFFFFFE7F
	and r2, r1
	mov r1, #0x80
	orr r2, r1
	add r1, r0, #0
	add r1, #0x82
	strh r2, [r1]
	add r1, r0, #0
	add r1, #0x82
	ldrh r2, [r1]
	ldr r1, _02242E94 ; =0xFFFF81FF
	and r2, r1
	add r1, r0, #0
	add r1, #0x82
	strh r2, [r1]
	add r1, r0, #0
	add r1, #0x82
	ldrh r2, [r1]
	ldr r1, _02242E98 ; =0xFFFF7FFF
	add r0, #0x82
	and r1, r2
	strh r1, [r0]
	pop {r3, r4}
	bx lr
	nop
_02242E8C: .word ov06_02242E9C
_02242E90: .word 0xFFFFFE7F
_02242E94: .word 0xFFFF81FF
_02242E98: .word 0xFFFF7FFF

	thumb_func_start ov06_02242E9C
ov06_02242E9C: ; 0x02242E9C
	push {r3, lr}
	mov r2, #2
	mvn r2, r2
	cmp r1, r2
	bne _02242EB2
	mov r1, #3
	mov r2, #0xf
	mov r3, #4
	bl ListMenuOverrideSetColors
	pop {r3, pc}
_02242EB2:
	mov r1, #1
	mov r2, #0xf
	mov r3, #2
	bl ListMenuOverrideSetColors
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02242EC0
ov06_02242EC0: ; 0x02242EC0
	push {r4, lr}
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0x5c
	ldrb r1, [r1]
	cmp r1, #4
	bhi _02242F0E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02242EDE: ; jump table
	.short _02242EE8 - _02242EDE - 2 ; case 0
	.short _02242EEE - _02242EDE - 2 ; case 1
	.short _02242EF4 - _02242EDE - 2 ; case 2
	.short _02242EFA - _02242EDE - 2 ; case 3
	.short _02242F00 - _02242EDE - 2 ; case 4
_02242EE8:
	bl ov06_02242F1C
	b _02242F0E
_02242EEE:
	bl ov06_02242F54
	b _02242F0E
_02242EF4:
	bl ov06_02242FEC
	b _02242F0E
_02242EFA:
	bl ov06_02243018
	b _02242F0E
_02242F00:
	bl ov06_02243024
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
_02242F0E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02242F14
ov06_02242F14: ; 0x02242F14
	add r0, #0x5c
	strb r1, [r0]
	bx lr
	.align 2, 0

	thumb_func_start ov06_02242F1C
ov06_02242F1C: ; 0x02242F1C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x88
	ldr r0, [r0]
	bl ListMenu_ProcessInput
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _02242F38
	add r1, r1, #1
	cmp r0, r1
	beq _02242F50
	b _02242F42
_02242F38:
	add r0, r4, #0
	mov r1, #4
	bl ov06_02242F14
	pop {r4, pc}
_02242F42:
	add r1, r4, #0
	add r1, #0x60
	strh r0, [r1]
	add r0, r4, #0
	mov r1, #1
	bl ov06_02242F14
_02242F50:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02242F54
ov06_02242F54: ; 0x02242F54
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _02242FE0 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #4
	tst r0, r1
	beq _02242F6E
	mov r0, #1
	add r4, #0x5f
	add sp, #4
	strb r0, [r4]
	pop {r3, r4, pc}
_02242F6E:
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	bl ListMenu_ProcessInput
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _02242F88
	add r1, r1, #1
	cmp r0, r1
	beq _02242FDC
	b _02242FA6
_02242F88:
	add r0, r4, #0
	add r0, #0x5f
	ldrb r0, [r0]
	cmp r0, #1
	bne _02242F9A
	add r0, r4, #0
	mov r1, #0
	add r0, #0x5f
	strb r1, [r0]
_02242F9A:
	add r0, r4, #0
	mov r1, #0
	bl ov06_02242F14
	add sp, #4
	pop {r3, r4, pc}
_02242FA6:
	add r1, r4, #0
	add r1, #0x5f
	ldrb r1, [r1]
	cmp r1, #1
	bne _02242FDC
	add r1, r4, #0
	add r1, #0x60
	strh r0, [r1]
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4]
	ldr r1, _02242FE4 ; =0x02250C40
	ldr r0, [r0, #8]
	ldr r2, _02242FE8 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x64]
	add r0, r4, #0
	mov r1, #0x24
	mov r2, #0
	bl ov06_02243080
	add r0, r4, #0
	mov r1, #2
	bl ov06_02242F14
_02242FDC:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02242FE0: .word gSystem
_02242FE4: .word ov06_02250C40
_02242FE8: .word 0x000003D9

	thumb_func_start ov06_02242FEC
ov06_02242FEC: ; 0x02242FEC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x64]
	mov r1, #4
	bl sub_020021AC
	cmp r0, #0
	bne _02243006
	add r0, r4, #0
	mov r1, #3
	bl ov06_02242F14
	pop {r4, pc}
_02243006:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	bne _02243016
	add r0, r4, #0
	mov r1, #1
	bl ov06_02242F14
_02243016:
	pop {r4, pc}

	thumb_func_start ov06_02243018
ov06_02243018: ; 0x02243018
	ldr r3, _02243020 ; =ov06_02242F14
	mov r1, #1
	bx r3
	nop
_02243020: .word ov06_02242F14

	thumb_func_start ov06_02243024
ov06_02243024: ; 0x02243024
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _0224307C ; =0x000005DC
	bl PlaySE
	add r0, r6, #0
	add r0, #0x14
	mov r1, #0
	bl ClearFrameAndWindow2
	add r0, r6, #0
	add r0, #0x14
	bl RemoveWindow
	add r0, r6, #0
	add r0, #0x88
	mov r1, #0
	ldr r0, [r0]
	add r2, r1, #0
	bl DestroyListMenu
	ldr r0, [r6, #0x74]
	mov r1, #0
	bl ClearFrameAndWindow1
	add r0, r6, #4
	bl RemoveWindow
	mov r4, #0
	add r5, r6, #0
_02243060:
	ldr r0, [r5, #0x24]
	bl String_Delete
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xc
	blt _02243060
	ldr r0, [r6, #0x58]
	bl MessageFormat_Delete
	ldr r0, [r6, #0x54]
	bl DestroyMsgData
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224307C: .word 0x000005DC

	thumb_func_start ov06_02243080
ov06_02243080: ; 0x02243080
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	str r1, [sp, #0xc]
	mov r0, #0x40
	mov r1, #4
	add r7, r2, #0
	bl String_New
	add r4, r0, #0
	mov r0, #0x40
	mov r1, #4
	bl String_New
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x14
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r0, [r5, #0x54]
	ldr r1, [sp, #0xc]
	add r2, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x58]
	add r1, r6, #0
	add r2, r4, #0
	bl StringExpandPlaceholders
	mov r3, #0
	str r3, [sp]
	add r5, #0x14
	str r7, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	add r2, r6, #0
	str r3, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl String_Delete
	add r0, r6, #0
	bl String_Delete
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_022430E0
ov06_022430E0: ; 0x022430E0
	push {r4, lr}
	add r4, r0, #0
	mov r1, #6
	mov r2, #0
	bl ov06_02242D48
	add r0, r4, #0
	mov r1, #7
	mov r2, #1
	bl ov06_02242D48
	add r0, r4, #0
	mov r1, #9
	mov r2, #2
	bl ov06_02242D48
	add r0, r4, #0
	mov r1, #9
	mov r2, #3
	bl ov06_02242D48
	add r0, r4, #0
	mov r1, #9
	mov r2, #4
	bl ov06_02242D48
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #5
	bl ov06_02242D48
	add r0, r4, #0
	mov r1, #0xb
	mov r2, #6
	bl ov06_02242D48
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224312C
ov06_0224312C: ; 0x0224312C
	cmp r0, #5
	bhi _02243154
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224313C: ; jump table
	.short _02243148 - _0224313C - 2 ; case 0
	.short _0224314C - _0224313C - 2 ; case 1
	.short _02243150 - _0224313C - 2 ; case 2
	.short _02243150 - _0224313C - 2 ; case 3
	.short _02243148 - _0224313C - 2 ; case 4
	.short _02243148 - _0224313C - 2 ; case 5
_02243148:
	mov r0, #3
	bx lr
_0224314C:
	mov r0, #4
	bx lr
_02243150:
	mov r0, #2
	bx lr
_02243154:
	mov r0, #0
	bx lr

	thumb_func_start ov06_02243158
ov06_02243158: ; 0x02243158
	push {r4, r5}
	mov r5, #0
	cmp r3, #0
	ble _0224317E
_02243160:
	ldrh r4, [r0]
	cmp r1, r4
	bne _02243176
	cmp r2, #0
	beq _02243176
	ldrh r4, [r0, #2]
	cmp r2, r4
	bne _02243176
	mov r0, #1
	pop {r4, r5}
	bx lr
_02243176:
	add r5, r5, #1
	add r0, r0, #4
	cmp r5, r3
	blt _02243160
_0224317E:
	mov r0, #0
	pop {r4, r5}
	bx lr

	thumb_func_start ov06_02243184
ov06_02243184: ; 0x02243184
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov lr, r0
	sub r0, r5, #1
	mov r7, #0
	mov ip, r0
	cmp r0, #0
	ble _022431D0
	mov r3, lr
_02243196:
	add r2, r7, #1
	cmp r2, r5
	bge _022431C6
	ldrh r6, [r3]
	lsl r1, r2, #2
	mov r0, lr
	add r4, r0, r1
_022431A4:
	ldrh r0, [r4]
	cmp r6, r0
	bne _022431AE
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022431AE:
	ldrh r1, [r3, #2]
	cmp r1, #0
	beq _022431BE
	ldrh r0, [r4, #2]
	cmp r1, r0
	bne _022431BE
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022431BE:
	add r2, r2, #1
	add r4, r4, #4
	cmp r2, r5
	blt _022431A4
_022431C6:
	add r7, r7, #1
	mov r0, ip
	add r3, r3, #4
	cmp r7, r0
	blt _02243196
_022431D0:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_022431D4
ov06_022431D4: ; 0x022431D4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	str r0, [sp]
	add r7, r1, #0
	add r6, r2, #0
	add r0, sp, #0x20
	mov r1, #0
	mov r2, #0x10
	str r3, [sp, #4]
	bl MI_CpuFill8
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #4]
	cmp r0, #0
	ble _022432DC
	ldr r0, [sp]
	str r0, [sp, #0x10]
_022431F8:
	ldr r0, [sp, #0x10]
	ldrh r1, [r0]
	add r0, sp, #0x20
	strh r1, [r0]
	ldr r0, [sp, #0x10]
	ldrh r1, [r0, #2]
	add r0, sp, #0x20
	strh r1, [r0, #2]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, r6
	bge _022432CA
	lsl r1, r0, #2
	ldr r0, [sp]
	add r0, r0, r1
	str r0, [sp, #0xc]
_0224321A:
	ldr r0, [sp, #0xc]
	cmp r7, #2
	ldrh r1, [r0]
	add r0, sp, #0x20
	strh r1, [r0, #4]
	ldr r0, [sp, #0xc]
	ldrh r1, [r0, #2]
	add r0, sp, #0x20
	strh r1, [r0, #6]
	bne _02243240
	add r0, sp, #0x20
	add r1, r7, #0
	bl ov06_02243184
	cmp r0, #0
	beq _022432BA
	add sp, #0x30
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02243240:
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r6
	bge _022432BA
	lsl r1, r0, #2
	ldr r0, [sp]
	add r0, r0, r1
	str r0, [sp, #8]
_02243252:
	ldr r0, [sp, #8]
	cmp r7, #3
	ldrh r1, [r0]
	add r0, sp, #0x20
	strh r1, [r0, #8]
	ldr r0, [sp, #8]
	ldrh r1, [r0, #2]
	add r0, sp, #0x20
	strh r1, [r0, #0xa]
	bne _02243278
	add r0, sp, #0x20
	add r1, r7, #0
	bl ov06_02243184
	cmp r0, #0
	beq _022432AA
	add sp, #0x30
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02243278:
	ldr r0, [sp, #0x14]
	add r4, r0, #1
	cmp r4, r6
	bge _022432AA
	ldr r0, [sp]
	lsl r1, r4, #2
	add r5, r0, r1
_02243286:
	ldrh r1, [r5]
	add r0, sp, #0x20
	strh r1, [r0, #0xc]
	ldrh r1, [r5, #2]
	strh r1, [r0, #0xe]
	add r0, sp, #0x20
	add r1, r7, #0
	bl ov06_02243184
	cmp r0, #0
	beq _022432A2
	add sp, #0x30
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022432A2:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r6
	blt _02243286
_022432AA:
	ldr r0, [sp, #8]
	add r0, r0, #4
	str r0, [sp, #8]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r6
	blt _02243252
_022432BA:
	ldr r0, [sp, #0xc]
	add r0, r0, #4
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, r6
	blt _0224321A
_022432CA:
	ldr r0, [sp, #0x10]
	add r0, r0, #4
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x1c]
	add r1, r0, #1
	ldr r0, [sp, #4]
	str r1, [sp, #0x1c]
	cmp r1, r0
	blt _022431F8
_022432DC:
	mov r0, #0
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_022432E4
ov06_022432E4: ; 0x022432E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp]
	add r0, r1, #0
	bl SaveArray_Party_Get
	str r0, [sp, #4]
	bl Party_GetCount
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	str r1, [sp, #8]
	ldr r0, [sp]
	cmp r1, r0
	bge _02243308
	add sp, #0x28
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02243308:
	ldr r0, [sp, #8]
	mov r7, #0
	add r4, r7, #0
	cmp r0, #0
	bls _0224337A
_02243312:
	ldr r0, [sp, #4]
	add r1, r7, #0
	bl Party_GetMonByIndex
	mov r1, #5
	mov r2, #0
	str r0, [sp, #0xc]
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [sp, #0xc]
	mov r1, #6
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0xc]
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0224336E
	add r0, r5, #0
	bl IsPokemonLegendaryOrMythical
	cmp r0, #1
	beq _0224336E
	add r0, sp, #0x10
	add r1, r5, #0
	add r2, r6, #0
	add r3, r4, #0
	bl ov06_02243158
	cmp r0, #1
	beq _0224336E
	lsl r1, r4, #2
	add r0, sp, #0x10
	add r2, r0, r1
	strh r5, [r0, r1]
	add r0, r4, #1
	lsl r0, r0, #0x18
	strh r6, [r2, #2]
	lsr r4, r0, #0x18
_0224336E:
	add r0, r7, #1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [sp, #8]
	cmp r7, r0
	blo _02243312
_0224337A:
	ldr r0, [sp]
	cmp r4, r0
	bge _02243386
	add sp, #0x28
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02243386:
	ldr r1, [sp]
	add r0, sp, #0x10
	add r3, r1, #0
	sub r3, r4, r3
	add r2, r4, #0
	add r3, r3, #1
	bl ov06_022431D4
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224339C
ov06_0224339C: ; 0x0224339C
	ldr r3, _022433A4 ; =OS_ResetSystem
	mov r0, #0
	bx r3
	nop
_022433A4: .word OS_ResetSystem

	thumb_func_start ov06_022433A8
ov06_022433A8: ; 0x022433A8
	ldr r3, _022433AC ; =SaveStruct23_Substruct1_Init
	bx r3
	.align 2, 0
_022433AC: .word SaveStruct23_Substruct1_Init

	thumb_func_start ov06_022433B0
ov06_022433B0: ; 0x022433B0
	ldr r3, _022433B4 ; =SaveStruct23_Substruct1_GetFlag1
	bx r3
	.align 2, 0
_022433B4: .word SaveStruct23_Substruct1_GetFlag1

	thumb_func_start ov06_022433B8
ov06_022433B8: ; 0x022433B8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	bl LocalFieldData_GetDynamicWarp
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	ldr r1, [r5, #0x1c]
	ldr r1, [r1]
	str r1, [r4]
	mov r1, #0
	mvn r1, r1
	str r1, [r4, #4]
	str r0, [r4, #8]
	str r6, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F154
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_022433F8
ov06_022433F8: ; 0x022433F8
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F164
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02243408
ov06_02243408: ; 0x02243408
	push {r4, lr}
	add r4, r1, #0
	cmp r4, #5
	bne _02243414
	mov r0, #0
	pop {r4, pc}
_02243414:
	bl Save_GameStats_Get
	lsl r1, r4, #1
	add r1, #0x36
	bl GameStats_GetCapped
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02243428
ov06_02243428: ; 0x02243428
	push {r4, lr}
	add r4, r1, #0
	bl Save_FrontierData_Get
	cmp r4, #0
	bne _0224343E
	mov r1, #5
	mov r2, #2
	bl FrontierData_SetFlag
	pop {r4, pc}
_0224343E:
	mov r1, #5
	mov r2, #1
	bl FrontierData_SetFlag
	pop {r4, pc}

	thumb_func_start ov06_02243448
ov06_02243448: ; 0x02243448
	push {r3, lr}
	bl Save_FrontierData_Get
	mov r1, #5
	mov r2, #0
	bl FrontierData_SetFlag
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, pc}

	thumb_func_start ov06_0224345C
ov06_0224345C: ; 0x0224345C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl SaveStruct23_GetSubstruct1
	add r4, r0, #0
	add r0, r5, #0
	bl Save_FrontierData_Get
	mov r1, #0
	add r6, r0, #0
	add r0, r4, #0
	add r2, r1, #0
	bl SaveStruct23_Substruct1_GetField
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	bne _02243484
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_02243484:
	add r1, r4, #0
	add r1, #8
	lsl r1, r1, #0x10
	add r0, r6, #0
	lsr r1, r1, #0x10
	mov r2, #2
	bl FrontierData_SetFlag
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #2
	bl FrontierData_SetField_0xC
	cmp r4, #4
	beq _022434A8
	add r0, r5, #0
	bl sub_020600A0
_022434A8:
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_022434AC
ov06_022434AC: ; 0x022434AC
	push {r3, lr}
	bl SaveStruct23_GetSubstruct4
	bl SaveStruct23_Substruct4_GetField_0xFE
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, pc}

	thumb_func_start ov06_022434BC
ov06_022434BC: ; 0x022434BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _022434CA
	bl GF_AssertFail
_022434CA:
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start ov06_022434D0
ov06_022434D0: ; 0x022434D0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r2, #0
	mov r2, #1
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #3
	mov r1, #0x3b
	lsl r2, r2, #0xe
	bl CreateHeapAtEnd
	ldr r1, _02243684 ; =0x000008CC
	mov r0, #0x3b
	bl AllocFromHeap
	ldr r2, _02243684 ; =0x000008CC
	mov r1, #0
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x3b
	str r0, [r4, #4]
	add r0, r6, #0
	bl SaveStruct23_GetSubstruct1
	str r0, [r4, #0x70]
	add r0, r6, #0
	bl Save_FrontierData_Get
	str r0, [r4, #0x74]
	ldr r0, _02243688 ; =0x12345678
	mov r1, #0
	str r0, [r4]
	ldr r0, [r4, #0x70]
	bl SaveStruct23_Substruct1_SetFlag1
	cmp r5, #0
	bne _0224356C
	strb r7, [r4, #0xf]
	ldrb r0, [r4, #0xf]
	bl ov06_0224312C
	strb r0, [r4, #0xe]
	mov r0, #1
	strb r0, [r4, #0xc]
	mov r2, #0
	strb r2, [r4, #0xd]
	mov r1, #0xff
_02243530:
	add r0, r4, r2
	add r0, #0x2a
	strb r1, [r0]
	add r0, r2, #1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, #4
	blo _02243530
	ldr r1, _0224368C ; =0x0000FFFF
	mov r2, #0
_02243544:
	lsl r0, r2, #1
	add r0, r4, r0
	strh r1, [r0, #0x3e]
	add r0, r2, #1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, #0xe
	blo _02243544
	ldr r0, [r4, #0x70]
	bl SaveStruct23_Substruct1_Init
	ldrb r1, [r4, #0xf]
	add r0, sp, #8
	add r2, sp, #8
	strb r1, [r0]
	ldr r0, [r4, #0x70]
	mov r1, #0
	bl SaveStruct23_Substruct1_SetField
	b _0224362A
_0224356C:
	mov r1, #0
	ldr r0, [r4, #0x70]
	add r2, r1, #0
	bl SaveStruct23_Substruct1_GetField
	strb r0, [r4, #0xf]
	ldr r0, [r4, #0x70]
	mov r1, #1
	mov r2, #0
	bl SaveStruct23_Substruct1_GetField
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0xc]
	sub r0, r0, #1
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xf]
	bl ov06_0224312C
	strb r0, [r4, #0xe]
	add r2, r4, #0
	ldr r0, [r4, #0x70]
	mov r1, #5
	add r2, #0x2a
	bl SaveStruct23_Substruct1_GetField
	add r2, r4, #0
	ldr r0, [r4, #0x70]
	mov r1, #8
	add r2, #0x3e
	bl SaveStruct23_Substruct1_GetField
	ldr r0, [r4, #0x70]
	mov r1, #0xa
	mov r2, #0
	bl SaveStruct23_Substruct1_GetField
	str r0, [r4, #8]
	ldrb r0, [r4, #0xf]
	cmp r0, #2
	bne _0224362A
	ldr r0, [r4, #0x70]
	mov r1, #9
	mov r2, #0
	bl SaveStruct23_Substruct1_GetField
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1d
	ldrb r1, [r4, #0x10]
	mov r2, #0xe0
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r4, #0x10]
	ldrb r3, [r4, #0x10]
	ldr r2, _02243690 ; =0x000007E8
	ldr r0, [r4, #0x70]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1d
	add r2, r4, r2
	lsl r3, r3, #4
	mov r1, #6
	add r2, r2, r3
	bl SaveStruct23_Substruct1_GetField
	ldrb r0, [r4, #0x10]
	mov r1, #7
	mov r2, #0
	lsl r0, r0, #0x18
	lsr r5, r0, #0x1d
	ldr r0, [r4, #0x70]
	bl SaveStruct23_Substruct1_GetField
	add r3, r0, #0
	ldr r0, _02243690 ; =0x000007E8
	mov r1, #0xa6
	lsl r1, r1, #2
	add r0, r4, r0
	lsl r2, r5, #4
	add r0, r0, r2
	add r2, r5, r2
	str r0, [sp]
	ldr r0, [r4, #4]
	add r1, r4, r1
	lsl r2, r2, #4
	add r1, r1, r2
	mov r2, #0x4b
	lsl r2, r2, #2
	add r2, r5, r2
	lsl r2, r2, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	lsr r2, r2, #0x10
	bl ov06_02244A80
_0224362A:
	add r0, r6, #0
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0xf]
	cmp r0, #5
	beq _0224367E
	add r0, r6, #0
	bl Save_GameStats_Get
	ldrb r1, [r4, #0xf]
	add r5, r0, #0
	ldr r0, [r4, #0x74]
	add r1, #8
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0
	bl FrontierData_SetFlag
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	beq _02243668
	ldrb r1, [r4, #0xf]
	add r0, r5, #0
	lsl r1, r1, #1
	add r1, #0x36
	bl GameStats_GetCapped
	strh r0, [r4, #0x1a]
_02243668:
	add r0, r5, #0
	mov r1, #0x1d
	bl GameStats_GetCapped
	str r0, [r4, #0x20]
	ldrb r1, [r4, #0xf]
	ldr r0, [r4, #0x74]
	mov r2, #0
	bl FrontierData_SetField_0xC
	strh r0, [r4, #0x1c]
_0224367E:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02243684: .word 0x000008CC
_02243688: .word 0x12345678
_0224368C: .word 0x0000FFFF
_02243690: .word 0x000007E8

	thumb_func_start ov06_02243694
ov06_02243694: ; 0x02243694
	push {r3, r4, r5, lr}
	add r4, r0, #0
	beq _022436BE
	ldr r1, [r4]
	ldr r0, _022436C0 ; =0x12345678
	cmp r1, r0
	beq _022436A6
	bl GF_AssertFail
_022436A6:
	ldr r2, _022436C4 ; =0x000008CC
	ldr r5, [r4, #4]
	add r0, r4, #0
	mov r1, #0
	bl MI_CpuFill8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl DestroyHeap
_022436BE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022436C0: .word 0x12345678
_022436C4: .word 0x000008CC

	thumb_func_start ov06_022436C8
ov06_022436C8: ; 0x022436C8
	push {r3, lr}
	sub sp, #0x10
	ldrb r0, [r0, #0xe]
	mov r3, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x64
	str r0, [sp, #8]
	add r0, r1, #0
	add r1, r2, #0
	mov r2, #0x11
	str r3, [sp, #0xc]
	bl sub_0205FC50
	add sp, #0x10
	pop {r3, pc}

	thumb_func_start ov06_022436E8
ov06_022436E8: ; 0x022436E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r1]
	str r1, [sp]
	str r0, [sp, #4]
	add r0, #0x23
	ldrb r0, [r0]
	cmp r0, #0
	bne _02243706
	ldr r0, [sp, #4]
	add r0, #0x22
	ldrb r0, [r0]
	cmp r0, #7
	bne _02243716
_02243706:
	ldr r0, [sp, #4]
	bl FreeToHeap
	ldr r1, [sp]
	mov r0, #0
	str r0, [r1]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02243716:
	add r0, r2, #0
	bl SaveArray_Party_Get
	str r0, [sp, #8]
	ldrb r0, [r5, #0xe]
	mov r4, #0
	cmp r0, #0
	ble _0224376A
_02243726:
	ldr r0, [sp, #4]
	add r0, r0, r4
	add r0, #0x2c
	ldrb r0, [r0]
	sub r1, r0, #1
	add r0, r5, r4
	add r0, #0x2a
	strb r1, [r0]
	add r1, r5, r4
	add r1, #0x2a
	ldrb r1, [r1]
	ldr r0, [sp, #8]
	bl Party_GetMonByIndex
	lsl r1, r4, #1
	add r6, r5, r1
	add r7, r0, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	strh r0, [r6, #0x2e]
	add r0, r7, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	strh r0, [r6, #0x36]
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldrb r0, [r5, #0xe]
	cmp r4, r0
	blt _02243726
_0224376A:
	ldr r0, [sp]
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, [sp]
	mov r1, #0
	str r1, [r0]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02243780
ov06_02243780: ; 0x02243780
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp]
	add r0, r1, #0
	bl SaveArray_Party_Get
	str r0, [sp, #4]
	ldr r0, [sp]
	mov r5, #0
	ldrb r0, [r0, #0xe]
	cmp r0, #0
	ble _02243808
	add r7, sp, #0xc
	add r4, sp, #0x14
_0224379C:
	ldr r1, [sp]
	ldr r0, [sp, #4]
	add r1, r1, r5
	add r1, #0x2a
	ldrb r1, [r1]
	bl Party_GetMonByIndex
	str r0, [sp, #8]
	lsl r6, r5, #1
	mov r1, #5
	mov r2, #0
	bl GetMonData
	strh r0, [r4, r6]
	ldr r0, [sp, #8]
	mov r1, #6
	mov r2, #0
	bl GetMonData
	strh r0, [r7, r6]
	cmp r5, #0
	beq _022437FA
	mov r0, #0
	cmp r5, #0
	bls _022437FA
	ldrh r1, [r4, r6]
	ldrh r2, [r7, r6]
_022437D2:
	lsl r6, r0, #1
	ldrh r3, [r4, r6]
	cmp r1, r3
	bne _022437E0
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022437E0:
	cmp r2, #0
	beq _022437F0
	ldrh r3, [r7, r6]
	cmp r2, r3
	bne _022437F0
	add sp, #0x1c
	mov r0, #2
	pop {r4, r5, r6, r7, pc}
_022437F0:
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, r5
	blo _022437D2
_022437FA:
	add r0, r5, #1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r0, [sp]
	ldrb r0, [r0, #0xe]
	cmp r5, r0
	blt _0224379C
_02243808:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02243810
ov06_02243810: ; 0x02243810
	push {r3, r4}
	mov r4, #0
	cmp r2, #0
	bls _02243830
_02243818:
	lsl r3, r4, #1
	ldrh r3, [r0, r3]
	cmp r1, r3
	bne _02243826
	mov r0, #1
	pop {r3, r4}
	bx lr
_02243826:
	add r3, r4, #1
	lsl r3, r3, #0x10
	lsr r4, r3, #0x10
	cmp r4, r2
	blo _02243818
_02243830:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start ov06_02243838
ov06_02243838: ; 0x02243838
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldrb r1, [r5, #0xf]
	add r0, r1, #0
	add r0, #0xfe
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _0224389E
	cmp r1, #3
	bne _02243858
	ldrh r1, [r5, #0x14]
	ldrh r0, [r5, #0x1c]
	cmp r1, r0
	bhi _0224385A
_02243858:
	ldrh r1, [r5, #0x1c]
_0224385A:
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	add r0, r5, #0
	str r0, [sp, #4]
	add r0, #0x3e
	mov r4, #0
	add r6, r5, #0
	str r0, [sp, #4]
_0224386C:
	lsr r2, r4, #0x1f
	add r2, r4, r2
	lsl r2, r2, #0x17
	ldrb r3, [r5, #0xf]
	ldr r1, [sp]
	add r0, r5, #0
	lsr r2, r2, #0x18
	bl ov06_0224478C
	add r7, r0, #0
	lsl r2, r4, #0x10
	ldr r0, [sp, #4]
	add r1, r7, #0
	lsr r2, r2, #0x10
	bl ov06_02243810
	cmp r0, #0
	bne _0224386C
	add r4, r4, #1
	strh r7, [r6, #0x3e]
	add r6, r6, #2
	cmp r4, #0xe
	blt _0224386C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0224389E:
	add r0, r5, #0
	str r0, [sp, #8]
	add r0, #0x3e
	mov r4, #0
	add r6, r5, #0
	str r0, [sp, #8]
_022438AA:
	ldrh r1, [r5, #0x1c]
	lsl r2, r4, #0x18
	ldrb r3, [r5, #0xf]
	lsl r1, r1, #0x18
	add r0, r5, #0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl ov06_0224478C
	add r7, r0, #0
	lsl r2, r4, #0x10
	ldr r0, [sp, #8]
	add r1, r7, #0
	lsr r2, r2, #0x10
	bl ov06_02243810
	cmp r0, #0
	bne _022438AA
	add r4, r4, #1
	strh r7, [r6, #0x3e]
	add r6, r6, #2
	cmp r4, #7
	blt _022438AA
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_022438DC
ov06_022438DC: ; 0x022438DC
	ldrb r0, [r0, #0xc]
	bx lr

	thumb_func_start ov06_022438E0
ov06_022438E0: ; 0x022438E0
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	ldr r0, [r4, #8]
	bl sub_02060064
	str r0, [r4, #8]
	ldrb r0, [r4, #0xc]
	add r0, r0, #1
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0xc]
	pop {r4, pc}

	thumb_func_start ov06_022438FC
ov06_022438FC: ; 0x022438FC
	ldrb r2, [r0, #0x10]
	lsl r1, r2, #0x1f
	lsr r1, r1, #0x1f
	beq _02243908
	mov r0, #1
	bx lr
_02243908:
	ldrb r1, [r0, #0xc]
	cmp r1, #7
	bls _0224391C
	mov r1, #1
	bic r2, r1
	mov r1, #1
	orr r2, r1
	strb r2, [r0, #0x10]
	add r0, r1, #0
	bx lr
_0224391C:
	mov r0, #0
	bx lr

	thumb_func_start ov06_02243920
ov06_02243920: ; 0x02243920
	ldrb r1, [r0, #0xd]
	ldrh r0, [r0, #0x1a]
	add r1, r0, r1
	ldr r0, _02243934 ; =0x0000FFFF
	cmp r1, r0
	bhi _02243930
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
_02243930:
	bx lr
	nop
_02243934: .word 0x0000FFFF

	thumb_func_start ov06_02243938
ov06_02243938: ; 0x02243938
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldrb r0, [r5, #0xf]
	add r4, r1, #0
	add r6, r2, #0
	cmp r0, #0
	beq _0224394A
	cmp r0, #1
	bne _02243980
_0224394A:
	ldr r0, [r4, #0xc]
	bl SaveArray_Party_Get
	ldrb r1, [r5, #0xf]
	cmp r1, #0
	bne _0224396C
	add r5, #0x2a
	ldrb r1, [r5]
	bl Party_GetMonByIndex
	add r2, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	mov r3, #1
	bl sub_02061904
	pop {r4, r5, r6, pc}
_0224396C:
	add r5, #0x2a
	ldrb r1, [r5]
	bl Party_GetMonByIndex
	add r2, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	mov r3, #0
	bl sub_02061904
_02243980:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02243984
ov06_02243984: ; 0x02243984
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r2, #0
	ldrb r2, [r5, #0xf]
	add r6, r1, #0
	add r4, r3, #0
	cmp r2, #0
	beq _0224399E
	cmp r2, #1
	beq _022439A4
	cmp r2, #4
	beq _022439B8
	pop {r3, r4, r5, r6, r7, pc}
_0224399E:
	mov r2, #0
	bl ov06_02244190
_022439A4:
	cmp r4, #7
	blo _022439F6
	add r0, r6, #0
	bl Save_SafariZone_Get
	add r1, r7, #0
	add r2, r4, #0
	bl sub_02060FBC
	pop {r3, r4, r5, r6, r7, pc}
_022439B8:
	mov r2, #1
	bl ov06_02244190
	ldrh r1, [r5, #0x28]
	ldrh r2, [r5, #0x24]
	ldrh r3, [r5, #0x26]
	lsl r1, r1, #0x18
	ldr r0, [r5, #0x70]
	lsr r1, r1, #0x18
	bl sub_0202A36C
	ldrb r1, [r5, #0xf]
	add r0, sp, #0
	add r2, sp, #0
	strb r1, [r0]
	ldr r0, [r5, #0x70]
	mov r1, #0
	bl SaveStruct23_Substruct1_SetField
	ldrb r1, [r5, #0xc]
	add r0, sp, #0
	add r2, sp, #0
	strb r1, [r0]
	ldr r0, [r5, #0x70]
	mov r1, #1
	bl SaveStruct23_Substruct1_SetField
	ldr r0, [r5, #0x74]
	ldr r1, [r5, #0x70]
	bl FrontierData_SetField_0x16
_022439F6:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_022439F8
ov06_022439F8: ; 0x022439F8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r1, #0xc]
	str r1, [sp]
	str r0, [sp, #8]
	bl Save_GameStats_Get
	ldrb r1, [r5, #0xf]
	str r0, [sp, #4]
	cmp r1, #5
	beq _02243AD0
	lsl r6, r1, #1
	add r6, #0x35
	add r1, r6, #0
	bl GameStats_GetCapped
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	ldrh r3, [r5, #0x1a]
	ldrb r2, [r5, #0xd]
	ldr r0, [sp, #4]
	add r1, r6, #0
	add r2, r3, r2
	bl GameStats_UpdateBounded
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #1
	bls _02243A52
	cmp r7, r4
	blo _02243A48
	cmp r7, r4
	bne _02243A52
	add r0, r4, #0
	mov r1, #7
	bl _s32_div_f
	cmp r1, #0
	bne _02243A52
_02243A48:
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r4, #0
	bl ov06_02243938
_02243A52:
	ldrb r1, [r5, #0xf]
	ldr r0, [r5, #0x74]
	mov r2, #0
	add r1, #8
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FrontierData_SetFlag
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	beq _02243A74
	ldrb r2, [r5, #0xd]
	ldr r0, [sp, #4]
	add r1, r6, #1
	bl GameStats_Add
	b _02243A7E
_02243A74:
	ldrb r2, [r5, #0xd]
	ldr r0, [sp, #4]
	add r1, r6, #1
	bl GameStats_SetCapped
_02243A7E:
	ldrb r1, [r5, #0xf]
	add r4, r0, #0
	ldr r0, [r5, #0x74]
	add r1, #8
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #2
	bl FrontierData_SetFlag
	ldrb r2, [r5, #0xd]
	ldr r0, [sp, #4]
	mov r1, #0x1d
	bl GameStats_Add
	ldrb r1, [r5, #0xf]
	ldr r0, [r5, #0x74]
	mov r2, #2
	bl FrontierData_SetField_0xC
	ldr r0, [sp, #8]
	bl Save_GameStats_Get
	mov r1, #0xf
	mov r2, #1
	bl GameStats_Add
	add r0, r5, #0
	bl ov06_0224403C
	ldr r0, _02243AD4 ; =0x0000270F
	add r4, r4, #1
	cmp r4, r0
	bls _02243AC2
	add r4, r0, #0
_02243AC2:
	lsl r3, r4, #0x10
	ldr r1, [sp, #8]
	add r0, r5, #0
	mov r2, #0
	lsr r3, r3, #0x10
	bl ov06_02243984
_02243AD0:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02243AD4: .word 0x0000270F

	thumb_func_start ov06_02243AD8
ov06_02243AD8: ; 0x02243AD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	add r5, r0, #0
	ldr r0, [r7, #0xc]
	str r0, [sp, #4]
	ldrb r0, [r5, #0xf]
	cmp r0, #5
	beq _02243BA2
	ldr r0, [sp, #4]
	bl Save_GameStats_Get
	ldrb r1, [r5, #0xf]
	add r6, r0, #0
	ldr r0, [r5, #0x74]
	lsl r4, r1, #1
	add r1, #8
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0
	add r4, #0x35
	bl FrontierData_SetFlag
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	beq _02243B1A
	add r0, r6, #0
	add r1, r4, #1
	mov r2, #7
	bl GameStats_Add
	str r0, [sp]
	b _02243B26
_02243B1A:
	add r0, r6, #0
	add r1, r4, #1
	mov r2, #7
	bl GameStats_SetCapped
	str r0, [sp]
_02243B26:
	ldrb r1, [r5, #0xf]
	ldr r0, [r5, #0x74]
	mov r2, #1
	add r1, #8
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FrontierData_SetFlag
	add r0, r6, #0
	add r1, r4, #0
	bl GameStats_GetCapped
	ldr r2, [sp]
	add r0, r6, #0
	add r1, r4, #0
	bl GameStats_UpdateBounded
	add r0, r6, #0
	mov r1, #0x1d
	mov r2, #7
	bl GameStats_Add
	ldrb r1, [r5, #0xf]
	ldr r0, [r5, #0x74]
	mov r2, #3
	bl FrontierData_SetField_0xC
	add r0, r6, #0
	mov r1, #0xf
	mov r2, #1
	bl GameStats_Add
	add r0, r6, #0
	mov r1, #0xe
	bl GameStats_AddSpecial
	add r0, r5, #0
	bl ov06_0224403C
	ldr r3, [sp]
	ldr r1, [sp, #4]
	lsl r3, r3, #0x10
	add r0, r5, #0
	mov r2, #1
	lsr r3, r3, #0x10
	bl ov06_02243984
	ldrb r0, [r5, #0xf]
	add r0, #0xfd
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _02243BA2
	ldr r0, [r5, #4]
	bl sub_02029578
	add r7, #0x98
	add r1, r0, #0
	ldr r0, [r7]
	mov r2, #4
	bl sub_02028AD4
_02243BA2:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02243BA8
ov06_02243BA8: ; 0x02243BA8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldrb r1, [r4, #0xf]
	add r0, sp, #0
	add r2, sp, #0
	strb r1, [r0]
	ldr r0, [r4, #0x70]
	mov r1, #0
	bl SaveStruct23_Substruct1_SetField
	ldrb r1, [r4, #0xc]
	add r0, sp, #0
	add r2, sp, #0
	strb r1, [r0]
	ldr r0, [r4, #0x70]
	mov r1, #1
	bl SaveStruct23_Substruct1_SetField
	add r2, r4, #0
	ldr r0, [r4, #0x70]
	mov r1, #5
	add r2, #0x2a
	bl SaveStruct23_Substruct1_SetField
	ldrh r1, [r4, #0x28]
	ldrh r2, [r4, #0x24]
	ldrh r3, [r4, #0x26]
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x70]
	lsr r1, r1, #0x18
	bl sub_0202A36C
	add r2, r4, #0
	ldr r0, [r4, #0x70]
	mov r1, #8
	add r2, #0x3e
	bl SaveStruct23_Substruct1_SetField
	add r2, r4, #0
	ldr r0, [r4, #0x70]
	mov r1, #0xa
	add r2, #8
	bl SaveStruct23_Substruct1_SetField
	ldr r0, [r4, #0x70]
	mov r1, #1
	bl SaveStruct23_Substruct1_SetFlag1
	ldrb r0, [r4, #0xf]
	cmp r0, #2
	bne _02243C4E
	ldrb r0, [r4, #0x10]
	add r2, sp, #0
	lsl r0, r0, #0x18
	lsr r1, r0, #0x1d
	add r0, sp, #0
	strb r1, [r0]
	ldr r0, [r4, #0x70]
	mov r1, #9
	bl SaveStruct23_Substruct1_SetField
	ldrb r3, [r4, #0x10]
	ldr r2, _02243C54 ; =0x000007E8
	ldr r0, [r4, #0x70]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1d
	add r2, r4, r2
	lsl r3, r3, #4
	mov r1, #6
	add r2, r2, r3
	bl SaveStruct23_Substruct1_SetField
	ldr r2, _02243C58 ; =0x00000838
	ldr r0, [r4, #0x70]
	add r3, r4, r2
	ldrb r2, [r4, #0x10]
	mov r1, #7
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1d
	add r2, r3, r2
	bl SaveStruct23_Substruct1_SetField
_02243C4E:
	add sp, #4
	pop {r3, r4, pc}
	nop
_02243C54: .word 0x000007E8
_02243C58: .word 0x00000838

	thumb_func_start ov06_02243C5C
ov06_02243C5C: ; 0x02243C5C
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldrb r2, [r4, #0xf]
	cmp r2, #5
	bhi _02243D16
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02243C74: ; jump table
	.short _02243D16 - _02243C74 - 2 ; case 0
	.short _02243D16 - _02243C74 - 2 ; case 1
	.short _02243C96 - _02243C74 - 2 ; case 2
	.short _02243C96 - _02243C74 - 2 ; case 3
	.short _02243C80 - _02243C74 - 2 ; case 4
	.short _02243C80 - _02243C74 - 2 ; case 5
_02243C80:
	ldrb r2, [r4, #0xc]
	add r0, r1, #0
	add r1, r4, #0
	sub r2, r2, #1
	lsl r2, r2, #0x18
	add r1, #0x78
	lsr r2, r2, #0x18
	bl ov06_0224434C
	add sp, #0x18
	pop {r4, r5, r6, pc}
_02243C96:
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldr r1, [r4, #4]
	str r1, [sp, #0xc]
	ldrb r2, [r4, #0xc]
	add r1, r4, #0
	ldrb r3, [r4, #0xe]
	sub r2, r2, #1
	lsl r2, r2, #2
	add r2, r4, r2
	ldrh r2, [r2, #0x3e]
	add r1, #0x78
	bl ov06_02244A34
	ldrb r3, [r4, #0xe]
	mov r0, #0
	cmp r3, #0
	ble _02243CE8
	add r1, r4, #0
	add r1, #0xa8
	add r2, sp, #0x14
	add r5, r4, #0
	add r6, sp, #0x10
_02243CC8:
	ldrh r3, [r1]
	add r0, r0, #1
	add r1, #0x38
	lsl r3, r3, #0x15
	lsr r3, r3, #0x15
	strh r3, [r2]
	add r3, r5, #0
	add r3, #0xaa
	ldrh r3, [r3]
	add r2, r2, #2
	add r5, #0x38
	strh r3, [r6]
	ldrb r3, [r4, #0xe]
	add r6, r6, #2
	cmp r0, r3
	blt _02243CC8
_02243CE8:
	add r0, sp, #0x14
	str r0, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	mov r1, #0x62
	str r0, [sp, #0xc]
	ldrb r2, [r4, #0xc]
	lsl r1, r1, #2
	add r0, r4, #0
	sub r2, r2, #1
	lsl r2, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	add r2, r4, r2
	ldrh r2, [r2, #0x3e]
	add r1, r4, r1
	bl ov06_02244A34
	add sp, #0x18
	pop {r4, r5, r6, pc}
_02243D16:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	add r1, r4, #0
	str r0, [sp, #0xc]
	ldrb r2, [r4, #0xc]
	ldrb r3, [r4, #0xe]
	add r0, r4, #0
	sub r2, r2, #1
	lsl r2, r2, #1
	add r2, r4, r2
	ldrh r2, [r2, #0x3e]
	add r1, #0x78
	bl ov06_02244A34
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02243D3C
ov06_02243D3C: ; 0x02243D3C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, _02243D98 ; =0x000007E8
	mov r4, #0
	add r6, r5, r0
	mov r0, #0xa6
	lsl r0, r0, #2
	add r7, r5, r0
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0x2e
	str r0, [sp, #0x10]
	add r0, r5, #0
	str r0, [sp, #0x14]
	add r0, #0x36
	str r0, [sp, #0x14]
_02243D5E:
	ldr r0, [sp, #0x10]
	mov r2, #0x4b
	str r0, [sp]
	ldr r0, [sp, #0x14]
	lsl r2, r2, #2
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r0, [r5, #4]
	add r2, r4, r2
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	ldrb r3, [r5, #0xe]
	add r0, r5, #0
	add r1, r7, #0
	lsr r2, r2, #0x10
	bl ov06_02244A34
	add r2, r5, r4
	ldr r1, _02243D9C ; =0x00000838
	add r4, r4, #1
	strb r0, [r2, r1]
	mov r0, #0x11
	lsl r0, r0, #4
	add r6, #0x10
	add r7, r7, r0
	cmp r4, #5
	blt _02243D5E
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02243D98: .word 0x000007E8
_02243D9C: .word 0x00000838

	thumb_func_start ov06_02243DA0
ov06_02243DA0: ; 0x02243DA0
	lsl r2, r1, #4
	add r1, r1, r2
	lsl r1, r1, #4
	add r0, r0, r1
	add r0, #0x7c
	ldrh r0, [r0]
	ldr r3, _02243DB4 ; =ov06_022442C4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx r3
	.align 2, 0
_02243DB4: .word ov06_022442C4

	thumb_func_start ov06_02243DB8
ov06_02243DB8: ; 0x02243DB8
	ldr r3, _02243DBC ; =sub_02046948
	bx r3
	.align 2, 0
_02243DBC: .word sub_02046948

	thumb_func_start ov06_02243DC0
ov06_02243DC0: ; 0x02243DC0
	ldrb r0, [r0, #0xf]
	bx lr

	thumb_func_start ov06_02243DC4
ov06_02243DC4: ; 0x02243DC4
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1e
	ldrb r3, [r0, #0x10]
	mov r2, #6
	lsr r1, r1, #0x1d
	bic r3, r2
	orr r1, r3
	strb r1, [r0, #0x10]
	bx lr

	thumb_func_start ov06_02243DD8
ov06_02243DD8: ; 0x02243DD8
	ldrb r0, [r0, #0x10]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1e
	bx lr

	thumb_func_start ov06_02243DE0
ov06_02243DE0: ; 0x02243DE0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r1, [r4, #0xf]
	cmp r1, #5
	bne _02243DEE
	mov r0, #0
	pop {r3, r4, r5, pc}
_02243DEE:
	cmp r1, #4
	ldr r0, [r4, #0x74]
	bne _02243E00
	mov r1, #0
	bl FrontierData_SetField_0x3
	ldr r1, _02243E2C ; =0x02250C5C
	ldrb r5, [r1, r0]
	b _02243E1E
_02243E00:
	mov r2, #0
	bl FrontierData_SetField_0xC
	ldrb r1, [r4, #0x10]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1e
	beq _02243E12
	mov r5, #0x14
	b _02243E1E
_02243E12:
	cmp r0, #7
	blo _02243E1A
	mov r5, #7
	b _02243E1E
_02243E1A:
	ldr r1, _02243E30 ; =0x02250C48
	ldrb r5, [r1, r0]
_02243E1E:
	ldr r0, [r4, #0x74]
	add r1, r5, #0
	mov r2, #5
	bl FrontierData_BattlePointAction
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02243E2C: .word ov06_02250C5C
_02243E30: .word ov06_02250C48

	thumb_func_start ov06_02243E34
ov06_02243E34: ; 0x02243E34
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	ldrb r1, [r4, #0xf]
	bl ov06_02243408
	cmp r0, #0x32
	bhs _02243E48
	mov r0, #0
	pop {r4, pc}
_02243E48:
	cmp r0, #0x64
	ldr r0, [r4, #0x74]
	blo _02243E5E
	mov r1, #1
	mov r2, #0
	bl FrontierData_SetFlag
	cmp r0, #0
	beq _02243E6E
	mov r0, #0
	pop {r4, pc}
_02243E5E:
	mov r1, #0
	add r2, r1, #0
	bl FrontierData_SetFlag
	cmp r0, #0
	beq _02243E6E
	mov r0, #0
	pop {r4, pc}
_02243E6E:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02243E74
ov06_02243E74: ; 0x02243E74
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r0, r1, #0
	add r5, r2, #0
	bl Save_FrontierData_Get
	add r4, r0, #0
	cmp r5, #0
	beq _02243E90
	cmp r5, #1
	beq _02243E98
	cmp r5, #2
	beq _02243ECC
	b _02243F10
_02243E90:
	mov r1, #0
	bl FrontierData_SetField_0x3
	pop {r4, r5, r6, pc}
_02243E98:
	mov r1, #4
	mov r2, #2
	bl FrontierData_SetFlag
	add r0, r4, #0
	mov r1, #0
	bl FrontierData_SetField_0x3
	add r5, r0, #0
	cmp r5, #0xa
	bne _02243EB2
	mov r0, #0
	pop {r4, r5, r6, pc}
_02243EB2:
	add r0, r4, #0
	mov r1, #3
	bl FrontierData_SetField_0x3
	add r0, r5, #1
	cmp r0, #5
	blt _02243EC8
	ldrb r1, [r6, #0x10]
	mov r0, #0x10
	orr r0, r1
	strb r0, [r6, #0x10]
_02243EC8:
	mov r0, #1
	pop {r4, r5, r6, pc}
_02243ECC:
	mov r1, #3
	bl FrontierData_SetField_0x2
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0
	bl FrontierData_SetField_0x3
	cmp r0, #1
	bne _02243EE4
	mov r0, #0
	pop {r4, r5, r6, pc}
_02243EE4:
	sub r1, r0, #1
	ldr r0, _02243F14 ; =0x02250C50
	ldrb r0, [r0, r1]
	cmp r5, r0
	blo _02243F0C
	add r0, r4, #0
	mov r1, #4
	bl FrontierData_SetField_0x3
	add r0, r4, #0
	mov r1, #2
	bl FrontierData_SetField_0x2
	add r0, r4, #0
	mov r1, #4
	mov r2, #2
	bl FrontierData_SetFlag
	mov r0, #1
	pop {r4, r5, r6, pc}
_02243F0C:
	mov r0, #0
	pop {r4, r5, r6, pc}
_02243F10:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02243F14: .word ov06_02250C50

	thumb_func_start ov06_02243F18
ov06_02243F18: ; 0x02243F18
	push {r3, lr}
	add r2, r0, #0
	ldrb r0, [r2, #0xf]
	cmp r0, #0
	beq _02243F26
	mov r0, #0
	pop {r3, pc}
_02243F26:
	ldrb r0, [r2, #0x10]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1e
	cmp r0, #1
	beq _02243F36
	cmp r0, #2
	beq _02243F40
	b _02243F4A
_02243F36:
	add r0, r1, #0
	mov r1, #0x1a
	bl ov06_02243FDC
	pop {r3, pc}
_02243F40:
	add r0, r1, #0
	mov r1, #0x1b
	bl ov06_02243FDC
	pop {r3, pc}
_02243F4A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02243F50
ov06_02243F50: ; 0x02243F50
	push {r4, lr}
	add r2, r0, #0
	ldrb r0, [r2, #0xf]
	cmp r0, #5
	bne _02243F5E
	mov r0, #0
	pop {r4, pc}
_02243F5E:
	ldrb r4, [r2, #0x10]
	lsl r4, r4, #0x1b
	lsr r4, r4, #0x1f
	bne _02243F6A
	mov r0, #0
	pop {r4, pc}
_02243F6A:
	cmp r0, #4
	bhi _02243F92
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02243F7A: ; jump table
	.short _02243F92 - _02243F7A - 2 ; case 0
	.short _02243F84 - _02243F7A - 2 ; case 1
	.short _02243F88 - _02243F7A - 2 ; case 2
	.short _02243F8C - _02243F7A - 2 ; case 3
	.short _02243F90 - _02243F7A - 2 ; case 4
_02243F84:
	mov r3, #0x1c
	b _02243F92
_02243F88:
	mov r3, #0x1d
	b _02243F92
_02243F8C:
	mov r3, #0x1e
	b _02243F92
_02243F90:
	mov r3, #0x1f
_02243F92:
	add r0, r1, #0
	add r1, r3, #0
	bl ov06_02243FDC
	pop {r4, pc}

	thumb_func_start ov06_02243F9C
ov06_02243F9C: ; 0x02243F9C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldrb r1, [r5, #0xf]
	ldr r0, [r5, #0x74]
	mov r2, #0
	add r1, #8
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FrontierData_SetFlag
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bne _02243FC0
	add r0, r4, #0
	bl sub_020600A0
	b _02243FC6
_02243FC0:
	add r0, r4, #0
	bl sub_020600DC
_02243FC6:
	str r0, [r5, #8]
	ldr r0, [r5, #8]
	ldr r1, _02243FD8 ; =0x0000FFFF
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, r4, r5, pc}
	nop
_02243FD8: .word 0x0000FFFF

	thumb_func_start ov06_02243FDC
ov06_02243FDC: ; 0x02243FDC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	add r5, r2, #0
	mov r2, #1
	add r1, sp, #8
	strb r2, [r1]
	bl SaveArray_Party_Get
	str r0, [sp]
	mov r7, #0
	ldrb r0, [r5, #0xe]
	add r4, r7, #0
	cmp r0, #0
	ble _0224402C
_02243FFA:
	add r1, r5, r4
	add r1, #0x2a
	ldrb r1, [r1]
	ldr r0, [sp]
	bl Party_GetMonByIndex
	add r1, r6, #0
	mov r2, #0
	str r0, [sp, #4]
	bl GetMonData
	cmp r0, #0
	bne _02244024
	ldr r0, [sp, #4]
	add r1, r6, #0
	add r2, sp, #8
	bl SetMonData
	add r0, r7, #1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
_02244024:
	ldrb r0, [r5, #0xe]
	add r4, r4, #1
	cmp r4, r0
	blt _02243FFA
_0224402C:
	cmp r7, #0
	bne _02244036
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02244036:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224403C
ov06_0224403C: ; 0x0224403C
	ldrb r1, [r0, #0xf]
	cmp r1, #5
	beq _0224404A
	cmp r1, #0
	beq _0224404A
	cmp r1, #4
	bne _0224404E
_0224404A:
	mov r0, #0
	bx lr
_0224404E:
	ldrh r2, [r0, #0x1a]
	ldrb r1, [r0, #0xd]
	add r1, r2, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #0x32
	bhs _02244060
	mov r0, #0
	bx lr
_02244060:
	ldrb r2, [r0, #0x10]
	mov r1, #0x10
	orr r1, r2
	strb r1, [r0, #0x10]
	mov r0, #1
	bx lr

	thumb_func_start ov06_0224406C
ov06_0224406C: ; 0x0224406C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	ldr r1, [sp]
	lsl r0, r0, #0x10
	ldrh r1, [r1]
	ldr r2, _02244188 ; =0xFFFFF800
	lsr r3, r0, #0x10
	lsr r0, r2, #0x15
	and r1, r2
	and r0, r3
	orr r1, r0
	ldr r0, [sp]
	mov r2, #0
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0x70
	bl GetMonData
	ldr r1, [sp]
	lsl r0, r0, #0x10
	ldrh r2, [r1]
	ldr r1, _0224418C ; =0xFFFF07FF
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1b
	and r1, r2
	lsr r0, r0, #0x10
	orr r1, r0
	ldr r0, [sp]
	mov r2, #0
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #6
	bl GetMonData
	ldr r1, [sp]
	mov r4, #0
	strh r0, [r1, #2]
	add r0, r1, #0
	str r0, [sp, #4]
	add r0, #0x1e
	add r6, r1, #0
	add r7, r4, #0
	str r0, [sp, #4]
_022440D0:
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x36
	mov r2, #0
	bl GetMonData
	add r1, r4, #0
	strh r0, [r6, #4]
	add r0, r5, #0
	add r1, #0x3e
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #4]
	lsl r0, r7
	ldrb r1, [r1]
	add r4, r4, #1
	add r6, r6, #2
	orr r1, r0
	ldr r0, [sp, #4]
	add r7, r7, #2
	strb r1, [r0]
	cmp r4, #4
	blt _022440D0
	add r0, r5, #0
	mov r1, #0xc
	mov r2, #0
	bl GetMonData
	ldr r1, [sp]
	mov r2, #0
	strb r0, [r1, #0x1f]
	add r0, r5, #0
	mov r1, #7
	bl GetMonData
	ldr r1, [sp]
	str r0, [r1, #0xc]
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl GetMonData
	ldr r1, [sp]
	mov r2, #0
	str r0, [r1, #0x10]
	add r0, r5, #0
	mov r1, #0xae
	bl GetMonData
	ldr r1, [sp]
	mov r4, #0
	str r0, [r1, #0x14]
	add r6, r4, #0
_0224413C:
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0xd
	add r2, r6, #0
	bl GetMonData
	ldr r1, [sp]
	add r1, r1, r4
	add r4, r4, #1
	strb r0, [r1, #0x18]
	cmp r4, #6
	blt _0224413C
	add r0, r5, #0
	mov r1, #0xa
	mov r2, #0
	bl GetMonData
	ldr r1, [sp]
	mov r2, #0
	add r1, #0x20
	strb r0, [r1]
	add r0, r5, #0
	mov r1, #9
	bl GetMonData
	ldr r1, [sp]
	ldr r2, [sp]
	add r1, #0x21
	strb r0, [r1]
	add r2, #0x22
	add r0, r5, #0
	mov r1, #0x74
	str r2, [sp]
	bl GetMonData
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244188: .word 0xFFFFF800
_0224418C: .word 0xFFFF07FF

	thumb_func_start ov06_02244190
ov06_02244190: ; 0x02244190
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	ldr r0, [r6, #4]
	add r4, r1, #0
	mov r1, #0xa8
	str r2, [sp]
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0xa8
	str r0, [sp, #4]
	bl MI_CpuFill8
	add r0, r4, #0
	bl SaveArray_Party_Get
	ldr r5, [sp, #4]
	add r7, r0, #0
	mov r4, #0
_022441B8:
	add r1, r6, r4
	add r1, #0x2a
	ldrb r1, [r1]
	add r0, r7, #0
	bl Party_GetMonByIndex
	add r1, r0, #0
	add r0, r5, #0
	bl ov06_0224406C
	add r4, r4, #1
	add r5, #0x38
	cmp r4, #3
	blt _022441B8
	ldr r0, [r6, #0x74]
	ldr r1, [sp]
	ldr r2, [sp, #4]
	bl FrontierData_SetArray
	ldr r0, [sp, #4]
	mov r1, #0
	mov r2, #0xa8
	bl MI_CpuFill8
	ldr r0, [sp, #4]
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_022441F4
ov06_022441F4: ; 0x022441F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl sub_02060064
	ldr r1, _0224420C ; =0x0000FFFF
	str r0, [r4, #8]
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4, pc}
	.align 2, 0
_0224420C: .word 0x0000FFFF

	thumb_func_start ov06_02244210
ov06_02244210: ; 0x02244210
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r4, r0, #0
	add r7, r1, #0
	str r2, [sp, #8]
	mov r0, #0xe
	mov r1, #4
	str r3, [sp, #0xc]
	ldr r5, [sp, #0x38]
	bl String_New
	add r6, r0, #0
	mov r0, #2
	mov r1, #4
	bl String_New
	str r0, [sp, #0x1c]
	add r0, r4, #0
	bl Save_Pokedex_Get
	str r0, [sp, #0x18]
	ldr r2, _022442C0 ; =0x0000016A
	mov r0, #1
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [sp, #0x10]
	mov r0, #0x13
	mov r1, #0xe
	mov r2, #4
	bl MessageFormat_New_Custom
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	add r2, r7, #0
	str r0, [sp, #0x14]
	str r3, [sp, #4]
	bl BufferIntegerAsString
	mov r4, #0
_02244264:
	add r0, r4, #0
	bl GetLegendaryMon
	add r7, r0, #0
	ldr r0, [sp, #0x18]
	add r1, r7, #0
	bl Pokedex_CheckMonSeenFlag
	cmp r0, #0
	beq _0224429E
	ldr r0, [sp, #0x10]
	add r1, r7, #0
	add r2, r6, #0
	bl ReadMsgDataIntoString
	ldr r0, [sp, #0xc]
	add r2, r6, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldrb r1, [r5]
	ldr r0, [sp, #0x14]
	ldr r3, [sp, #8]
	add r1, r1, #1
	bl BufferString
	ldrb r0, [r5]
	add r0, r0, #1
	strb r0, [r5]
_0224429E:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x12
	blo _02244264
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
	ldr r0, [sp, #0x1c]
	bl String_Delete
	add r0, r6, #0
	bl String_Delete
	ldr r0, [sp, #0x14]
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022442C0: .word 0x0000016A

	thumb_func_start ov06_022442C4
ov06_022442C4: ; 0x022442C4
	ldr r3, _022442E4 ; =0x02250CDA
	mov r2, #0
_022442C8:
	ldrh r1, [r3]
	cmp r0, r1
	bne _022442D6
	ldr r0, _022442E8 ; =0x02250CDC
	lsl r1, r2, #2
	ldrh r0, [r0, r1]
	bx lr
_022442D6:
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, #0x3f
	blo _022442C8
	mov r0, #3
	bx lr
	nop
_022442E4: .word ov06_02250CDA
_022442E8: .word ov06_02250CDC

	thumb_func_start ov06_022442EC
ov06_022442EC: ; 0x022442EC
	push {r3, r4, r5, r6, r7, lr}
	mov r2, #0x11
	add r4, r1, #0
	mov r1, #0
	lsl r2, r2, #4
	add r5, r0, #0
	bl MI_CpuFill8
	mov r0, #6
	mul r0, r4
	ldr r1, _02244340 ; =0x02250CB0
	str r0, [sp]
	add r6, r1, r0
	ldr r1, _02244344 ; =0x02250DD8
	mov r2, #0x30
	add r0, r4, #0
	mul r0, r2
	add r0, r1, r0
	add r1, r5, #0
	ldr r7, _02244348 ; =0x02250F28
	bl MI_CpuCopy8
	ldr r1, _02244340 ; =0x02250CB0
	ldr r0, [sp]
	mov r4, #0
	ldrh r0, [r1, r0]
	strh r0, [r5, #6]
	add r5, #0x30
_02244324:
	add r0, r6, r4
	ldrb r1, [r0, #2]
	mov r0, #0x38
	mov r2, #0x38
	mul r0, r1
	add r0, r7, r0
	add r1, r5, #0
	bl MI_CpuCopy8
	add r4, r4, #1
	add r5, #0x38
	cmp r4, #4
	blt _02244324
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02244340: .word ov06_02250CB0
_02244344: .word ov06_02250DD8
_02244348: .word ov06_02250F28

	thumb_func_start ov06_0224434C
ov06_0224434C: ; 0x0224434C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	mov r2, #0x11
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0
	lsl r2, r2, #4
	bl MI_CpuFill8
	add r0, r6, #0
	bl SaveStruct23_GetSubstruct4
	add r6, r0, #0
	bl SaveStruct23_Substruct4_GetField_0xFE
	cmp r0, #0
	bne _0224437A
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_022442EC
	pop {r4, r5, r6, pc}
_0224437A:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl sub_0202A798
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02244388
ov06_02244388: ; 0x02244388
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	bl ZeroMonData
	ldr r0, [r6, #0x10]
	ldr r3, _02244520 ; =0x3FFFFFFF
	str r0, [sp]
	ldrh r1, [r6]
	ldr r4, [r6, #0x14]
	add r0, r5, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x15
	mov r2, #0x32
	and r3, r4
	bl CreateMonWithFixedIVs
	ldrh r0, [r6]
	add r2, sp, #8
	add r2, #1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x1b
	add r0, sp, #8
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0x70
	bl SetMonData
	add r0, r5, #0
	mov r1, #6
	add r2, r6, #2
	bl SetMonData
	mov r4, #0
	str r6, [sp, #4]
	add r7, r4, #0
_022443D4:
	ldr r0, [sp, #4]
	add r2, sp, #8
	ldrh r1, [r0, #4]
	add r0, sp, #8
	add r2, #2
	strh r1, [r0, #2]
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x36
	bl SetMonData
	ldrb r0, [r6, #0x1e]
	add r2, sp, #8
	add r2, #1
	add r1, r0, #0
	asr r1, r7
	mov r0, #3
	and r1, r0
	add r0, sp, #8
	strb r1, [r0, #1]
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x3e
	bl SetMonData
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x42
	mov r2, #0
	bl GetMonData
	add r1, sp, #8
	strb r0, [r1]
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x3a
	add r2, sp, #8
	bl SetMonData
	ldr r0, [sp, #4]
	add r4, r4, #1
	add r0, r0, #2
	add r7, r7, #2
	str r0, [sp, #4]
	cmp r4, #4
	blt _022443D4
	ldr r0, [r6, #0xc]
	mov r1, #7
	str r0, [sp, #0xc]
	add r0, r5, #0
	add r2, sp, #0xc
	bl SetMonData
	add r2, sp, #8
	ldrb r1, [r6, #0x18]
	add r0, sp, #8
	add r2, #1
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0xd
	bl SetMonData
	add r2, sp, #8
	ldrb r1, [r6, #0x19]
	add r0, sp, #8
	add r2, #1
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0xe
	bl SetMonData
	add r2, sp, #8
	ldrb r1, [r6, #0x1a]
	add r0, sp, #8
	add r2, #1
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0xf
	bl SetMonData
	add r2, sp, #8
	ldrb r1, [r6, #0x1b]
	add r0, sp, #8
	add r2, #1
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0x10
	bl SetMonData
	add r2, sp, #8
	ldrb r1, [r6, #0x1c]
	add r0, sp, #8
	add r2, #1
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0x11
	bl SetMonData
	add r2, sp, #8
	ldrb r1, [r6, #0x1d]
	add r0, sp, #8
	add r2, #1
	strb r1, [r0, #1]
	add r0, r5, #0
	mov r1, #0x12
	bl SetMonData
	add r2, r6, #0
	add r0, r5, #0
	mov r1, #0xa
	add r2, #0x20
	bl SetMonData
	add r2, r6, #0
	add r0, r5, #0
	mov r1, #9
	add r2, #0x21
	bl SetMonData
	ldr r0, [r6, #0x14]
	lsl r0, r0, #1
	lsr r0, r0, #0x1f
	beq _022444FC
	ldr r2, _02244524 ; =0x0000016A
	mov r0, #1
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	ldrh r1, [r6]
	add r4, r0, #0
	lsl r1, r1, #0x15
	lsr r1, r1, #0x15
	bl NewString_ReadMsgData
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0x76
	add r2, r7, #0
	bl SetMonData
	add r0, r7, #0
	bl String_Delete
	add r0, r4, #0
	bl DestroyMsgData
	b _02244508
_022444FC:
	add r2, r6, #0
	add r0, r5, #0
	mov r1, #0x74
	add r2, #0x22
	bl SetMonData
_02244508:
	add r6, #0x1f
	add r0, r5, #0
	mov r1, #0xc
	add r2, r6, #0
	bl SetMonData
	add r0, r5, #0
	bl CalcMonLevelAndStats
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244520: .word 0x3FFFFFFF
_02244524: .word 0x0000016A

	thumb_func_start ov06_02244528
ov06_02244528: ; 0x02244528
	cmp r0, #4
	bhi _02244552
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02244538: ; jump table
	.short _02244542 - _02244538 - 2 ; case 0
	.short _02244546 - _02244538 - 2 ; case 1
	.short _0224454A - _02244538 - 2 ; case 2
	.short _0224454E - _02244538 - 2 ; case 3
	.short _02244542 - _02244538 - 2 ; case 4
_02244542:
	mov r0, #0x81
	bx lr
_02244546:
	mov r0, #0x83
	bx lr
_0224454A:
	mov r0, #0xcb
	bx lr
_0224454E:
	mov r0, #0x8f
	bx lr
_02244552:
	mov r0, #0x81
	bx lr
	.align 2, 0

	thumb_func_start ov06_02244558
ov06_02244558: ; 0x02244558
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldrb r0, [r5, #0xf]
	add r4, r1, #0
	bl ov06_02244528
	add r1, r0, #0
	ldr r0, [r5, #4]
	bl BattleSetup_New
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	bl SaveArray_Party_Get
	str r0, [sp, #4]
	add r0, r7, #0
	add r1, r4, #0
	bl sub_02047A78
	mov r0, #0x15
	mov r1, #6
	lsl r0, r0, #4
	str r1, [r7, r0]
	mov r1, #9
	add r0, r0, #4
	str r1, [r7, r0]
	ldr r0, [r5, #4]
	bl AllocMonZeroed
	add r4, r0, #0
	ldrb r1, [r5, #0xe]
	ldr r0, [r7, #4]
	bl Party_InitWithMaxSize
	ldrb r0, [r5, #0xe]
	mov r6, #0
	cmp r0, #0
	ble _022445FA
_022445A6:
	add r1, r5, r6
	add r1, #0x2a
	ldrb r1, [r1]
	ldr r0, [sp, #4]
	bl Party_GetMonByIndex
	add r1, r4, #0
	bl CopyPokemonToPokemon
	add r0, r4, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	cmp r0, #0x32
	bls _022445E8
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	mov r1, #0x32
	bl GetMonExpBySpeciesAndLevel
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #8
	add r2, sp, #8
	bl SetMonData
	add r0, r4, #0
	bl CalcMonLevelAndStats
_022445E8:
	add r0, r7, #0
	add r1, r4, #0
	mov r2, #0
	bl sub_020479FC
	ldrb r0, [r5, #0xe]
	add r6, r6, #1
	cmp r6, r0
	blt _022445A6
_022445FA:
	add r0, r4, #0
	bl FreeToHeap
	add r0, r7, #0
	bl sub_020480E4
	ldr r0, [r5, #4]
	add r1, r5, #0
	str r0, [sp]
	ldrb r2, [r5, #0xe]
	add r0, r7, #0
	add r1, #0x78
	mov r3, #1
	bl ov06_02244D04
	ldrb r0, [r5, #0xf]
	cmp r0, #2
	beq _02244624
	cmp r0, #3
	beq _02244646
	b _0224465A
_02244624:
	ldr r0, [r5, #4]
	mov r1, #0xa6
	str r0, [sp]
	ldrb r2, [r5, #0x10]
	lsl r1, r1, #2
	add r1, r5, r1
	lsl r2, r2, #0x18
	lsr r3, r2, #0x1d
	lsl r2, r3, #4
	add r2, r3, r2
	lsl r2, r2, #4
	add r1, r1, r2
	ldrb r2, [r5, #0xe]
	add r0, r7, #0
	mov r3, #2
	bl ov06_02244D04
_02244646:
	ldr r0, [r5, #4]
	mov r1, #0x62
	str r0, [sp]
	ldrb r2, [r5, #0xe]
	lsl r1, r1, #2
	add r0, r7, #0
	add r1, r5, r1
	mov r3, #3
	bl ov06_02244D04
_0224465A:
	add r0, r7, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_02244660
ov06_02244660: ; 0x02244660
	push {r3, r4}
	add r0, #0xa8
	ldr r3, [r0]
	ldrh r0, [r1]
	mov r2, #0
	strb r0, [r3, #0x12]
	ldrh r0, [r1, #2]
	strh r0, [r3, #0x16]
	ldrh r0, [r1, #4]
	strh r0, [r3, #0x18]
	ldrh r0, [r1, #6]
	mov r1, #0xe0
	strh r0, [r3, #0x14]
	ldrb r0, [r3, #0x10]
	bic r0, r1
	ldrb r1, [r3, #0x12]
	add r1, r1, #5
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r3, #0x10]
	ldrh r4, [r3, #0x16]
	ldrh r1, [r3, #0x2e]
	cmp r1, r4
	beq _0224469C
	ldrh r0, [r3, #0x18]
	cmp r1, r0
	bne _022446A2
_0224469C:
	add r0, r2, #1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_022446A2:
	ldrh r1, [r3, #0x30]
	cmp r1, r4
	beq _022446AE
	ldrh r0, [r3, #0x18]
	cmp r1, r0
	bne _022446B4
_022446AE:
	add r0, r2, #2
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_022446B4:
	add r0, r2, #0
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start ov06_022446BC
ov06_022446BC: ; 0x022446BC
	push {r3, r4, r5, lr}
	add r0, #0xa8
	add r5, r1, #0
	ldr r4, [r0]
	bl sub_02031190
	cmp r0, #0
	bne _022446D0
	mov r0, #0
	pop {r3, r4, r5, pc}
_022446D0:
	add r4, #0x3e
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1c
	bl MI_CpuCopy8
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_022446E0
ov06_022446E0: ; 0x022446E0
	add r0, #0xa8
	ldr r0, [r0]
	ldrb r0, [r0, #0x10]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	bne _022446F2
	ldrh r0, [r1]
	cmp r0, #0
	beq _022446F6
_022446F2:
	mov r0, #1
	bx lr
_022446F6:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start ov06_022446FC
ov06_022446FC: ; 0x022446FC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r6, r0, #0
	add r0, r4, #0
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	ldr r1, _02244750 ; =0x0000083E
	strh r0, [r6, r1]
	add r0, r4, #0
	bl SaveArray_Party_Get
	add r7, r0, #0
	mov r4, #0
	add r5, r6, #0
_0224471C:
	add r1, r6, r4
	add r1, #0x2a
	ldrb r1, [r1]
	add r0, r7, #0
	bl Party_GetMonByIndex
	mov r1, #5
	mov r2, #0
	bl GetMonData
	mov r1, #0x21
	lsl r1, r1, #6
	strh r0, [r5, r1]
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #2
	blt _0224471C
	ldr r0, [r6, #0x74]
	mov r1, #3
	mov r2, #0
	bl FrontierData_SetField_0xC
	ldr r1, _02244754 ; =0x00000844
	strh r0, [r6, r1]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244750: .word 0x0000083E
_02244754: .word 0x00000844

	thumb_func_start ov06_02244758
ov06_02244758: ; 0x02244758
	ldr r1, _02244768 ; =0x0000083E
	add r2, r0, #0
	add r1, r2, r1
	ldr r3, _0224476C ; =MI_CpuCopy8
	add r0, #0x3e
	mov r2, #0x1c
	bx r3
	nop
_02244768: .word 0x0000083E
_0224476C: .word MI_CpuCopy8

	thumb_func_start ov06_02244770
ov06_02244770: ; 0x02244770
	ldrb r3, [r0, #0x10]
	mov r2, #8
	bic r3, r2
	lsl r2, r1, #0x18
	lsr r2, r2, #0x18
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1c
	orr r2, r3
	strb r2, [r0, #0x10]
	ldr r2, _02244788 ; =0x0000083E
	strh r1, [r0, r2]
	bx lr
	.align 2, 0
_02244788: .word 0x0000083E

	thumb_func_start ov06_0224478C
ov06_0224478C: ; 0x0224478C
	push {r3, r4, r5, lr}
	cmp r3, #0
	bne _022447AA
	cmp r1, #2
	bne _0224479E
	cmp r2, #6
	bne _0224479E
	ldr r0, _02244808 ; =0x00000131
	pop {r3, r4, r5, pc}
_0224479E:
	cmp r1, #6
	bne _022447AA
	cmp r2, #6
	bne _022447AA
	ldr r0, _0224480C ; =0x00000132
	pop {r3, r4, r5, pc}
_022447AA:
	cmp r1, #7
	bhs _022447F6
	cmp r2, #6
	bne _022447D4
	lsl r5, r1, #2
	ldr r1, _02244810 ; =0x02250C90
	ldrh r4, [r1, r5]
	bl ov06_022441F4
	ldr r1, _02244814 ; =0x02250C92
	ldrh r1, [r1, r5]
	sub r1, r1, r4
	add r1, r1, #1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl _s32_div_f
	add r0, r4, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, r4, r5, pc}
_022447D4:
	lsl r4, r1, #2
	ldr r1, _02244818 ; =0x02250C70
	ldrh r5, [r1, r4]
	bl ov06_022441F4
	ldr r1, _0224481C ; =0x02250C72
	ldrh r1, [r1, r4]
	sub r1, r1, r5
	add r1, r1, #1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl _s32_div_f
	add r0, r5, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, r4, r5, pc}
_022447F6:
	bl ov06_022441F4
	mov r1, #0x64
	bl _s32_div_f
	add r1, #0xc8
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02244808: .word 0x00000131
_0224480C: .word 0x00000132
_02244810: .word ov06_02250C90
_02244814: .word ov06_02250C92
_02244818: .word ov06_02250C70
_0224481C: .word ov06_02250C72

	thumb_func_start ov06_02244820
ov06_02244820: ; 0x02244820
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #1
	mov r1, #0x1a
	mov r2, #0x10
	add r3, r6, #0
	bl NewMsgDataFromNarc
	add r7, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl ov06_02244CE8
	add r6, r0, #0
	ldr r0, _02244874 ; =0x0000FFFF
	str r4, [r5]
	strh r0, [r5, #0x18]
	lsl r0, r4, #1
	add r0, r4, r0
	strh r0, [r5, #0x1a]
	ldrh r0, [r6]
	add r1, r4, #0
	strh r0, [r5, #4]
	add r0, r7, #0
	bl NewString_ReadMsgData
	add r5, #8
	add r4, r0, #0
	add r1, r5, #0
	mov r2, #8
	bl CopyStringToU16Array
	add r0, r4, #0
	bl String_Delete
	add r0, r7, #0
	bl DestroyMsgData
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02244874: .word 0x0000FFFF

	thumb_func_start ov06_02244878
ov06_02244878: ; 0x02244878
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r4, r0, #0
	add r6, r2, #0
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x38
	str r3, [sp]
	bl MI_CpuFill8
	add r0, sp, #8
	add r1, r6, #0
	bl ov06_02244CF8
	ldrh r0, [r5]
	ldr r3, _02244A10 ; =0xFFFFF800
	add r2, r0, #0
	add r0, sp, #8
	and r2, r3
	ldrh r1, [r0]
	lsr r3, r3, #0x15
	and r1, r3
	orr r1, r2
	strh r1, [r5]
	ldr r1, [sp, #0x3c]
	cmp r1, #0
	beq _022448BC
	add r0, sp, #0x20
	ldrb r0, [r0, #0x18]
	lsl r1, r0, #1
	ldr r0, _02244A14 ; =0x02250C68
	ldrh r0, [r0, r1]
	b _022448BE
_022448BC:
	ldrh r0, [r0, #0xc]
_022448BE:
	strh r0, [r5, #2]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	add r1, sp, #8
	add r2, r5, #0
	add r6, r0, #0
_022448CC:
	ldrh r3, [r1, #2]
	strh r3, [r2, #4]
	ldrh r3, [r1, #2]
	cmp r3, #0xda
	bne _022448D8
	str r6, [sp, #4]
_022448D8:
	add r0, r0, #1
	add r1, r1, #2
	add r2, r2, #2
	cmp r0, #4
	blt _022448CC
	ldr r0, [sp]
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x30]
	cmp r0, #0
	bne _0224491E
_022448EC:
	add r0, r4, #0
	bl ov06_022441F4
	add r6, r0, #0
	add r0, r4, #0
	bl ov06_022441F4
	lsl r0, r0, #0x10
	add r7, r6, #0
	orr r7, r0
	add r0, r7, #0
	bl GetNatureFromPersonality
	add r1, sp, #8
	ldrb r1, [r1, #0xb]
	cmp r1, r0
	beq _0224491A
	ldr r0, [sp]
	add r1, r7, #0
	bl CalcShininessByOtIdAndPersonality
	cmp r0, #1
	beq _022448EC
_0224491A:
	str r7, [r5, #0x10]
	b _02244920
_0224491E:
	str r0, [r5, #0x10]
_02244920:
	add r0, sp, #0x20
	ldrb r1, [r0, #0x14]
	ldr r2, [r5, #0x14]
	mov r0, #0x1f
	bic r2, r0
	mov r0, #0x1f
	and r0, r1
	orr r2, r0
	ldr r0, _02244A18 ; =0xFFFFFC1F
	mov r6, #0
	and r2, r0
	lsl r0, r1, #0x1b
	lsr r1, r0, #0x16
	orr r2, r1
	ldr r1, _02244A1C ; =0xFFFF83FF
	add r4, r6, #0
	and r2, r1
	lsr r1, r0, #0x11
	orr r2, r1
	ldr r1, _02244A20 ; =0xFFF07FFF
	and r2, r1
	lsr r1, r0, #0xc
	orr r2, r1
	ldr r1, _02244A24 ; =0xFE0FFFFF
	and r2, r1
	lsr r1, r0, #7
	orr r2, r1
	ldr r1, _02244A28 ; =0xC1FFFFFF
	lsr r0, r0, #2
	and r1, r2
	orr r0, r1
	str r0, [r5, #0x14]
_02244960:
	add r0, r4, #0
	bl MaskOfFlagNo
	add r1, sp, #8
	ldrb r1, [r1, #0xa]
	tst r0, r1
	beq _02244970
	add r6, r6, #1
_02244970:
	add r4, r4, #1
	cmp r4, #6
	blt _02244960
	ldr r0, _02244A2C ; =0x000001FE
	add r1, r6, #0
	bl _s32_div_f
	cmp r0, #0xff
	ble _02244984
	mov r0, #0xff
_02244984:
	lsl r0, r0, #0x18
	mov r4, #0
	lsr r6, r0, #0x18
_0224498A:
	add r0, r4, #0
	bl MaskOfFlagNo
	add r1, sp, #8
	ldrb r1, [r1, #0xa]
	tst r0, r1
	beq _0224499C
	add r0, r5, r4
	strb r6, [r0, #0x18]
_0224499C:
	add r4, r4, #1
	cmp r4, #6
	blt _0224498A
	mov r0, #0
	strb r0, [r5, #0x1e]
	ldr r0, _02244A30 ; =gGameLanguage
	mov r1, #0x19 ; BASE_ABILITY_2
	ldrb r0, [r0]
	strb r0, [r5, #0x1f]
	ldrh r0, [r5]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x15
	bl GetMonBaseStat
	cmp r0, #0
	beq _022449E0
	ldr r2, [r5, #0x10]
	mov r1, #1
	tst r1, r2
	beq _022449CC
	add r1, r5, #0
	add r1, #0x20
	strb r0, [r1]
	b _022449F2
_022449CC:
	ldrh r0, [r5]
	mov r1, #0x18 ; BASE_ABILITY_1
	lsl r0, r0, #0x15
	lsr r0, r0, #0x15
	bl GetMonBaseStat
	add r1, r5, #0
	add r1, #0x20
	strb r0, [r1]
	b _022449F2
_022449E0:
	ldrh r0, [r5]
	mov r1, #0x18 ; BASE_ABILITY_1
	lsl r0, r0, #0x15
	lsr r0, r0, #0x15
	bl GetMonBaseStat
	add r1, r5, #0
	add r1, #0x20
	strb r0, [r1]
_022449F2:
	add r1, r5, #0
	ldr r0, [sp, #4]
	add r1, #0x21
	strb r0, [r1]
	ldrh r0, [r5]
	add r5, #0x22
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x15
	add r2, r5, #0
	bl GetSpeciesNameIntoArray
	add r0, r7, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02244A10: .word 0xFFFFF800
_02244A14: .word ov06_02250C68
_02244A18: .word 0xFFFFFC1F
_02244A1C: .word 0xFFFF83FF
_02244A20: .word 0xFFF07FFF
_02244A24: .word 0xFE0FFFFF
_02244A28: .word 0xC1FFFFFF
_02244A2C: .word 0x000001FE
_02244A30: .word gGameLanguage

	thumb_func_start ov06_02244A34
ov06_02244A34: ; 0x02244A34
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r2, #0
	add r5, r1, #0
	str r0, [sp, #0x14]
	ldr r2, [sp, #0x3c]
	add r6, r3, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02244820
	add r7, r0, #0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x30]
	add r5, #0x30
	str r0, [sp, #4]
	ldr r0, [sp, #0x34]
	add r1, r7, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x38]
	add r2, r4, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x3c]
	add r3, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	bl ov06_02244AEC
	add r4, r0, #0
	add r0, r7, #0
	bl FreeToHeap
	add r0, r4, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02244A80
ov06_02244A80: ; 0x02244A80
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x38]
	add r5, r1, #0
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	add r4, r2, #0
	str r0, [sp, #0x3c]
	ldr r2, [sp, #0x3c]
	add r0, r5, #0
	add r1, r4, #0
	str r3, [sp, #0x18]
	bl ov06_02244820
	str r0, [sp, #0x1c]
	add r0, r4, #0
	bl ov06_02244CAC
	ldr r6, [sp, #0x38]
	str r0, [sp, #0x20]
	mov r7, #0
	add r4, r6, #0
	add r5, #0x30
_02244AB0:
	ldr r0, [r6, #8]
	ldr r3, [sp, #0x38]
	str r0, [sp]
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	str r0, [sp, #4]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x3c]
	str r0, [sp, #0x10]
	ldrh r2, [r4, #4]
	ldr r0, [sp, #0x14]
	ldr r3, [r3]
	bl ov06_02244878
	add r7, r7, #1
	add r6, r6, #4
	add r4, r4, #2
	add r5, #0x38
	cmp r7, #2
	blt _02244AB0
	ldr r0, [sp, #0x1c]
	bl FreeToHeap
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02244AEC
ov06_02244AEC: ; 0x02244AEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x7c
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x94]
	str r2, [sp, #0x1c]
	str r0, [sp, #0x94]
	ldr r0, [sp, #0x98]
	str r1, [sp, #0x18]
	str r0, [sp, #0x98]
	ldr r0, [sp, #0x9c]
	str r3, [sp, #0x20]
	str r0, [sp, #0x9c]
	ldr r0, [sp, #0xa0]
	str r0, [sp, #0xa0]
	mov r0, #0
	str r0, [sp, #0x28]
	add r0, sp, #0x80
	ldrb r0, [r0, #0x10]
	cmp r0, #4
	bls _02244B18
	bl GF_AssertFail
_02244B18:
	add r0, sp, #0x80
	ldrb r6, [r0, #0x10]
	mov r4, #0
	str r4, [sp, #0x2c]
	cmp r6, #0
	beq _02244C0A
	add r0, sp, #0x6c
	str r0, [sp, #0x24]
_02244B28:
	ldr r0, [sp, #0x14]
	bl ov06_022441F4
	ldr r1, [sp, #0x18]
	ldrh r1, [r1, #2]
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r1, r0, #0x17
	ldr r0, [sp, #0x18]
	add r0, r0, r1
	ldrh r0, [r0, #4]
	str r0, [sp, #0x30]
	ldr r1, [sp, #0x30]
	add r0, sp, #0x3c
	bl ov06_02244CF8
	mov r7, #0
	cmp r4, #0
	ble _02244B6C
	add r5, sp, #0x6c
_02244B52:
	ldr r1, [r5]
	add r0, sp, #0x4c
	bl ov06_02244CF8
	add r0, sp, #0x3c
	ldrh r1, [r0, #0x10]
	ldrh r0, [r0]
	cmp r1, r0
	beq _02244B6C
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, r4
	blt _02244B52
_02244B6C:
	cmp r7, r4
	bne _02244C06
	ldr r0, [sp, #0x94]
	cmp r0, #0
	beq _02244B94
	mov r3, #0
	cmp r6, #0
	ble _02244B90
	add r1, r0, #0
	add r0, sp, #0x3c
	ldrh r2, [r0]
_02244B82:
	ldrh r0, [r1]
	cmp r2, r0
	beq _02244B90
	add r3, r3, #1
	add r1, r1, #2
	cmp r3, r6
	blt _02244B82
_02244B90:
	cmp r3, r6
	bne _02244C06
_02244B94:
	ldr r0, [sp, #0x2c]
	cmp r0, #0x32
	bge _02244BFC
	mov r7, #0
	cmp r4, #0
	ble _02244BC0
	add r5, sp, #0x6c
_02244BA2:
	ldr r1, [r5]
	add r0, sp, #0x4c
	bl ov06_02244CF8
	add r0, sp, #0x3c
	ldrh r1, [r0, #0x1c]
	cmp r1, #0
	beq _02244BB8
	ldrh r0, [r0, #0xc]
	cmp r1, r0
	beq _02244BC0
_02244BB8:
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, r4
	blt _02244BA2
_02244BC0:
	cmp r7, r4
	beq _02244BCC
	ldr r0, [sp, #0x2c]
	add r0, r0, #1
	str r0, [sp, #0x2c]
	b _02244C06
_02244BCC:
	ldr r0, [sp, #0x98]
	cmp r0, #0
	beq _02244BFC
	mov r3, #0
	cmp r6, #0
	ble _02244BF0
	add r1, r0, #0
	add r0, sp, #0x3c
	ldrh r2, [r0, #0xc]
_02244BDE:
	ldrh r0, [r1]
	cmp r2, r0
	bne _02244BE8
	cmp r0, #0
	bne _02244BF0
_02244BE8:
	add r3, r3, #1
	add r1, r1, #2
	cmp r3, r6
	blt _02244BDE
_02244BF0:
	cmp r3, r6
	beq _02244BFC
	ldr r0, [sp, #0x2c]
	add r0, r0, #1
	str r0, [sp, #0x2c]
	b _02244C06
_02244BFC:
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #0x24]
	add r4, r4, #1
	stmia r0!, {r1}
	str r0, [sp, #0x24]
_02244C06:
	cmp r4, r6
	bne _02244B28
_02244C0A:
	ldr r0, [sp, #0x1c]
	bl ov06_02244CAC
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x14]
	bl ov06_022441F4
	add r5, r0, #0
	ldr r0, [sp, #0x14]
	bl ov06_022441F4
	lsl r0, r0, #0x10
	orr r0, r5
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x2c]
	cmp r0, #0x32
	blt _02244C30
	mov r0, #1
	str r0, [sp, #0x28]
_02244C30:
	mov r5, #0
	cmp r4, #0
	ble _02244C70
	add r7, sp, #0x6c
	add r6, sp, #0x5c
_02244C3A:
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x20]
	str r0, [sp, #4]
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x34]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0xa0]
	str r0, [sp, #0x10]
	ldr r2, [r7]
	ldr r0, [sp, #0x14]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	bl ov06_02244878
	stmia r6!, {r0}
	ldr r0, [sp, #0x20]
	add r5, r5, #1
	add r0, #0x38
	add r7, r7, #4
	str r0, [sp, #0x20]
	cmp r5, r4
	blt _02244C3A
_02244C70:
	ldr r0, [sp, #0x9c]
	cmp r0, #0
	bne _02244C7C
	ldr r0, [sp, #0x28]
	add sp, #0x7c
	pop {r4, r5, r6, r7, pc}
_02244C7C:
	ldr r1, [sp, #0x34]
	ldr r2, [sp, #0x9c]
	str r1, [r0]
	mov r3, #0
	add r0, sp, #0x6c
	add r1, sp, #0x5c
_02244C88:
	ldr r5, [r0]
	ldr r4, [sp, #0x9c]
	add r3, r3, #1
	strh r5, [r4, #4]
	ldr r4, [r1]
	add r0, r0, #4
	str r4, [r2, #8]
	ldr r4, [sp, #0x9c]
	add r1, r1, #4
	add r4, r4, #2
	add r2, r2, #4
	str r4, [sp, #0x9c]
	cmp r3, #2
	blt _02244C88
	ldr r0, [sp, #0x28]
	add sp, #0x7c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02244CAC
ov06_02244CAC: ; 0x02244CAC
	cmp r0, #0x64
	bhs _02244CB4
	mov r0, #3
	bx lr
_02244CB4:
	cmp r0, #0x78
	bhs _02244CBC
	mov r0, #6
	bx lr
_02244CBC:
	cmp r0, #0x8c
	bhs _02244CC4
	mov r0, #9
	bx lr
_02244CC4:
	cmp r0, #0xa0
	bhs _02244CCC
	mov r0, #0xc
	bx lr
_02244CCC:
	cmp r0, #0xb4
	bhs _02244CD4
	mov r0, #0xf
	bx lr
_02244CD4:
	cmp r0, #0xc8
	bhs _02244CDC
	mov r0, #0x12
	bx lr
_02244CDC:
	cmp r0, #0xdc
	bhs _02244CE4
	mov r0, #0x15
	bx lr
_02244CE4:
	mov r0, #0x1f
	bx lr

	thumb_func_start ov06_02244CE8
ov06_02244CE8: ; 0x02244CE8
	add r3, r0, #0
	add r2, r1, #0
	add r1, r3, #0
	ldr r3, _02244CF4 ; =AllocAndReadWholeNarcMemberByIdPair
	mov r0, #0x86
	bx r3
	.align 2, 0
_02244CF4: .word AllocAndReadWholeNarcMemberByIdPair

	thumb_func_start ov06_02244CF8
ov06_02244CF8: ; 0x02244CF8
	ldr r3, _02244D00 ; =ReadWholeNarcMemberByIdPair
	add r2, r1, #0
	mov r1, #0x87
	bx r3
	.align 2, 0
_02244D00: .word ReadWholeNarcMemberByIdPair

	thumb_func_start ov06_02244D04
ov06_02244D04: ; 0x02244D04
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r7, r0, #0
	lsl r0, r3, #2
	str r0, [sp, #4]
	ldr r1, [r5]
	add r0, r7, r0
	str r1, [r0, #0x18]
	mov r0, #0x34
	add r4, r3, #0
	mul r4, r0
	add r0, r7, r4
	ldrh r1, [r5, #4]
	add r0, #0x29
	str r2, [sp]
	strb r1, [r0]
	add r0, r7, #0
	add r0, #0x3c
	add r1, r5, #0
	add r0, r0, r4
	add r1, #8
	bl CopyU16StringArray
	add r0, r7, r4
	ldrh r1, [r5, #0x20]
	add r0, #0x4c
	strh r1, [r0]
	add r0, r7, r4
	ldrh r1, [r5, #0x22]
	add r0, #0x4e
	strh r1, [r0]
	add r0, r7, r4
	ldrh r1, [r5, #0x24]
	add r0, #0x50
	strh r1, [r0]
	add r0, r7, r4
	ldrh r1, [r5, #0x26]
	add r0, #0x52
	strh r1, [r0]
	add r0, r7, r4
	ldrh r1, [r5, #0x28]
	add r0, #0x54
	strh r1, [r0]
	add r0, r7, r4
	ldrh r1, [r5, #0x2a]
	add r0, #0x56
	strh r1, [r0]
	add r0, r7, r4
	ldrh r1, [r5, #0x2c]
	add r0, #0x58
	strh r1, [r0]
	add r0, r7, r4
	ldrh r1, [r5, #0x2e]
	add r0, #0x5a
	strh r1, [r0]
	ldr r0, [sp, #0x20]
	bl AllocMonZeroed
	add r4, r0, #0
	ldr r0, [sp]
	mov r6, #0
	cmp r0, #0
	ble _02244DA4
	ldr r0, [sp, #4]
	add r5, #0x30
	add r7, r7, r0
_02244D8A:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02244388
	ldr r0, [r7, #4]
	add r1, r4, #0
	bl Party_AddMon
	ldr r0, [sp]
	add r6, r6, #1
	add r5, #0x38
	cmp r6, r0
	blt _02244D8A
_02244DA4:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02244DB0
ov06_02244DB0: ; 0x02244DB0
	ldr r3, _02244DB8 ; =AllocFromHeapAtEnd
	mov r1, #0x17
	lsl r1, r1, #4
	bx r3
	.align 2, 0
_02244DB8: .word AllocFromHeapAtEnd

	thumb_func_start ov06_02244DBC
ov06_02244DBC: ; 0x02244DBC
	ldr r3, _02244DC0 ; =FreeToHeap
	bx r3
	.align 2, 0
_02244DC0: .word FreeToHeap

	thumb_func_start ov06_02244DC4
ov06_02244DC4: ; 0x02244DC4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	mov r0, #0x5a
	add r4, r1, #0
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r7, r0]
	add r0, r4, #0
	mov r1, #0x12 ; BASE_GENDER_RATIO
	bl GetMonBaseStat
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _02244DEC
	cmp r0, #0xfe
	beq _02244DF0
	cmp r0, #0xff
	beq _02244DF4
	b _02244DF8
_02244DEC:
	mov r2, #0
	b _02244E10
_02244DF0:
	mov r2, #1
	b _02244E10
_02244DF4:
	mov r2, #2
	b _02244E10
_02244DF8:
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _02244E0E
	mov r2, #0
	b _02244E10
_02244E0E:
	mov r2, #1
_02244E10:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r7, #0
	lsl r1, r4, #0x10
	lsl r2, r2, #0x18
	add r0, #0x28
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	mov r3, #2
	bl sub_02068C00
	add r1, r7, #0
	mov r0, #1
	add r1, #0x3c
	mov r2, #4
	bl sub_02008C9C
	str r0, [r7, #0x38]
	mov r0, #0x61
	mov r1, #4
	bl NARC_New
	ldr r4, _02244EF4 ; =0x022512E0
	str r0, [sp, #0x10]
	mov r6, #0
	add r5, r7, #0
_02244E48:
	ldrb r0, [r4]
	add r1, r6, #0
	mov r2, #4
	bl sub_02008DEC
	add r6, r6, #1
	add r4, r4, #1
	stmia r5!, {r0}
	cmp r6, #4
	blt _02244E48
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r7]
	ldr r1, [sp, #0x10]
	mov r2, #5
	bl sub_020091E0
	str r0, [r7, #0x10]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, [r7, #4]
	ldr r1, [sp, #0x10]
	mov r2, #3
	mov r3, #0
	bl sub_02009298
	str r0, [r7, #0x14]
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r7, #8]
	ldr r1, [sp, #0x10]
	mov r2, #6
	mov r3, #0
	bl sub_02009358
	str r0, [r7, #0x18]
	mov r0, #3
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r7, #0xc]
	ldr r1, [sp, #0x10]
	mov r2, #0xc
	mov r3, #0
	bl sub_02009358
	str r0, [r7, #0x1c]
	ldrh r0, [r7, #0x28]
	ldrh r1, [r7, #0x2a]
	mov r2, #4
	bl sub_0201244C
	str r0, [r7, #0x20]
	ldrh r0, [r7, #0x28]
	ldrh r1, [r7, #0x2c]
	mov r2, #4
	bl sub_02012470
	str r0, [r7, #0x24]
	ldr r0, [r7]
	ldr r1, [r7, #4]
	ldr r2, [r7, #0x20]
	ldr r3, [r7, #0x24]
	bl ov06_02244F84
	ldr r0, [sp, #0x10]
	bl NARC_Delete
	add r0, r7, #0
	bl ov06_02244FFC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02244EF4: .word ov06_022512E0

	thumb_func_start ov06_02244EF8
ov06_02244EF8: ; 0x02244EF8
	add r1, r0, #0
	mov r0, #0x5a
	mov r2, #1
	lsl r0, r0, #2
	str r2, [r1, r0]
	ldr r3, _02244F10 ; =sub_0200CA44
	mov r2, #0
	add r0, r0, #4
	str r2, [r1, r0]
	ldr r0, _02244F14 ; =ov06_02244F64
	bx r3
	nop
_02244F10: .word sub_0200CA44
_02244F14: .word ov06_02244F64

	thumb_func_start ov06_02244F18
ov06_02244F18: ; 0x02244F18
	mov r1, #0x5a
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r0, r1]
	bx lr
	.align 2, 0

	thumb_func_start ov06_02244F24
ov06_02244F24: ; 0x02244F24
	mov r1, #0x5b
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start ov06_02244F2C
ov06_02244F2C: ; 0x02244F2C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	bl sub_02009C0C
	ldr r0, [r5, #0x14]
	bl sub_02009E04
	mov r4, #0
_02244F3E:
	lsl r0, r4, #2
	ldr r0, [r5, r0]
	bl sub_02008E2C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _02244F3E
	ldr r0, [r5, #0x38]
	bl sub_0201FD58
	ldr r0, [r5, #0x20]
	bl FreeToHeap
	ldr r0, [r5, #0x24]
	bl FreeToHeap
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02244F64
ov06_02244F64: ; 0x02244F64
	push {r3, lr}
	mov r2, #0x5a
	lsl r2, r2, #2
	ldr r3, [r1, r2]
	cmp r3, #0
	beq _02244F78
	ldr r0, [r1, #0x38]
	bl sub_0201FDEC
	pop {r3, pc}
_02244F78:
	mov r3, #1
	add r2, r2, #4
	str r3, [r1, r2]
	bl sub_0200CAB4
	pop {r3, pc}

	thumb_func_start ov06_02244F84
ov06_02244F84: ; 0x02244F84
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	mov r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl sub_020094F0
	add r5, r0, #0
	add r0, r7, #0
	mov r1, #1
	bl sub_020094F0
	add r7, r0, #0
	add r0, r5, #0
	bl sub_02009B04
	add r0, r7, #0
	bl sub_02009D68
	add r0, r5, #0
	bl sub_02009C5C
	add r5, r0, #0
	add r0, r7, #0
	add r1, r5, #0
	bl sub_02009E54
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #1
	bl NNS_G2dGetImageLocation
	str r0, [sp]
	add r0, r7, #0
	mov r1, #1
	bl NNS_G2dGetImagePaletteLocation
	mov r1, #0x32
	add r5, r0, #0
	add r0, r4, #0
	lsl r1, r1, #6
	bl DC_FlushRange
	mov r2, #0x32
	ldr r1, [sp]
	add r0, r4, #0
	lsl r2, r2, #6
	bl GX_LoadOBJ
	add r0, r6, #0
	mov r1, #0x20
	bl DC_FlushRange
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #0x20
	bl GX_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02244FFC
ov06_02244FFC: ; 0x02244FFC
	push {r4, lr}
	sub sp, #0x80
	add r4, r0, #0
	mov r0, #3
	str r0, [sp]
	sub r0, r0, #4
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r0, [r4]
	mov r2, #1
	str r0, [sp, #0x14]
	ldr r0, [r4, #4]
	mov r3, #2
	str r0, [sp, #0x18]
	ldr r0, [r4, #8]
	str r0, [sp, #0x1c]
	ldr r0, [r4, #0xc]
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	str r1, [sp, #0x28]
	add r0, sp, #0x5c
	bl sub_02008AA4
	ldr r0, [r4, #0x38]
	mov r1, #0
	str r0, [sp, #0x2c]
	add r0, sp, #0x5c
	str r0, [sp, #0x30]
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [sp, #0x34]
	str r1, [sp, #0x38]
	str r1, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r1, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x54]
	mov r0, #4
	str r0, [sp, #0x58]
	lsl r0, r0, #0x11
	str r0, [sp, #0x34]
	mov r0, #6
	lsl r0, r0, #0x10
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	str r1, [sp, #0x50]
	bl sub_0201FE94
	mov r1, #0x59
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl sub_020200BC
	mov r0, #0x59
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_02020130
	add sp, #0x80
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02245088
ov06_02245088: ; 0x02245088
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r5, r0, #0
	bl sub_02034CE0
	add r4, r0, #0
	mov r0, #0
	add r1, sp, #4
_02245098:
	lsl r2, r0, #3
	add r2, r4, r2
	ldr r3, [r2, #8]
	lsl r2, r0, #2
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r3, [r1, r2]
	cmp r0, #0xc
	blo _02245098
	add r0, r5, #0
	bl FieldSystem_GetSaveData
	bl Save_Pokedex_Get
	bl Pokedex_GetNatDexFlag
	add r6, r0, #0
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	mov r1, #1
	bl Roamers_GetRand
	add r1, sp, #0x20
	str r1, [sp]
	ldr r2, [r5, #0x1c]
	add r1, r6, #0
	ldr r2, [r2]
	add r3, sp, #0x1c
	bl ov06_02245658
	add r0, r4, #0
	add r1, sp, #0xc
	add r2, sp, #0x10
	bl ov06_0223B944
	add r0, r4, #0
	add r1, r6, #0
	add r2, sp, #0x24
	add r3, sp, #0x28
	bl ov06_0224CDB8
	bl LCRandom
	ldr r1, _02245110 ; =0x00001556
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0xc
	blo _02245104
	bl GF_AssertFail
_02245104:
	lsl r1, r4, #2
	add r0, sp, #4
	ldr r0, [r0, r1]
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	nop
_02245110: .word 0x00001556

	thumb_func_start ov06_02245114
ov06_02245114: ; 0x02245114
	push {r3, r4, r5, r6, r7, lr}
	str r1, [sp]
	mov r1, #0x34
	bl AllocFromHeapAtEnd
	add r5, r0, #0
	ldr r0, [sp]
	mov r1, #0xb
	str r0, [r5, #0x2c]
	mov r0, #0x6a
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	add r7, r0, #0
	mov r4, #0
_02245132:
	bl LCRandom
	ldr r1, _0224518C ; =0x0000071D
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r6, #0x24
	blo _02245148
	bl GF_AssertFail
_02245148:
	lsl r0, r6, #0x18
	lsr r2, r0, #0x16
	add r1, r7, r2
	ldrh r2, [r7, r2]
	lsl r3, r4, #2
	add r0, r5, r3
	strh r2, [r5, r3]
	ldrh r1, [r1, #2]
	strh r1, [r0, #2]
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #5
	blo _02245132
	ldr r0, [sp]
	ldr r0, [r0, #0x38]
	bl GetPlayerXCoord
	strh r0, [r5, #0x14]
	ldr r0, [sp]
	ldr r0, [r0, #0x38]
	bl GetPlayerYCoord
	strh r0, [r5, #0x16]
	ldr r0, [sp]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0]
	str r0, [r5, #0x30]
	add r0, r7, #0
	bl FreeToHeap
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224518C: .word 0x0000071D

	thumb_func_start ov06_02245190
ov06_02245190: ; 0x02245190
	ldr r3, _02245194 ; =FreeToHeap
	bx r3
	.align 2, 0
_02245194: .word FreeToHeap

	thumb_func_start ov06_02245198
ov06_02245198: ; 0x02245198
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0
	bne _022451BA
	lsl r2, r5, #2
	ldrh r1, [r4, r2]
	add r2, r4, r2
	ldrh r2, [r2, #2]
	lsl r1, r1, #0xb
	mov r0, #0xf0
	lsl r2, r2, #0xb
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl GetMapHeader
	b _022451D6
_022451BA:
	cmp r5, #5
	bne _022451C2
	ldr r0, [r4, #0x30]
	b _022451D6
_022451C2:
	lsl r2, r5, #2
	ldrh r1, [r4, r2]
	add r2, r4, r2
	ldr r0, [r4, #0x2c]
	ldrh r2, [r2, #2]
	ldr r0, [r0, #0x28]
	lsr r1, r1, #5
	lsr r2, r2, #5
	bl MapMatrix_GetMapHeader
_022451D6:
	lsl r3, r5, #2
	add r1, r4, r3
	ldrh r2, [r1, #2]
	ldrh r1, [r4, r3]
	str r0, [r4, #0x18]
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x1c]
	str r1, [r4, #0x20]
	str r2, [r4, #0x24]
	mov r0, #0
	str r0, [r4, #0x28]
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_022451F0
ov06_022451F0: ; 0x022451F0
	add r0, #0x18
	bx lr

	thumb_func_start ov06_022451F4
ov06_022451F4: ; 0x022451F4
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #6
	bl sub_020254A0
	mov r1, #0x42
	lsl r1, r1, #0x10
	str r1, [sp, #8]
	mov r1, #1
	lsl r1, r1, #0x10
	str r1, [sp, #0xc]
	ldrh r0, [r0]
	cmp r0, #0
	beq _02245224
	cmp r0, #1
	beq _0224522C
	cmp r0, #2
	beq _02245234
	b _0224523A
_02245224:
	mov r0, #0xa
	lsl r0, r0, #0x12
	str r0, [sp, #0x10]
	b _0224523A
_0224522C:
	mov r0, #0x52
	lsl r0, r0, #0x10
	str r0, [sp, #0x10]
	b _0224523A
_02245234:
	mov r0, #0x1b
	lsl r0, r0, #0x12
	str r0, [sp, #0x10]
_0224523A:
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #0x4c]
	ldr r2, _02245258 ; =0x000001DB
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r4, #0x2c]
	add r3, sp, #8
	bl ov05_021E7FBC
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02245258: .word 0x000001DB

	thumb_func_start ov06_0224525C
ov06_0224525C: ; 0x0224525C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	str r2, [sp]
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #6
	bl sub_020254A0
	add r4, r0, #0
	mov r0, #4
	mov r1, #0x14
	bl AllocFromHeapAtEnd
	add r5, r0, #0
	add r2, r5, #0
	mov r1, #0x14
	mov r0, #0
_02245284:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _02245284
	mov r0, #0
	strb r0, [r5, #5]
	ldrh r1, [r4]
	cmp r1, #0
	beq _022452A0
	cmp r1, #1
	beq _022452C6
	cmp r1, #2
	beq _022452EE
	b _02245312
_022452A0:
	mov r1, #1
	strb r1, [r5, #4]
	cmp r6, #1
	bne _022452B6
	mov r0, #0x52
	lsl r0, r0, #0x10
	str r0, [r5, #0xc]
	strh r1, [r4]
	mov r0, #0x4a
	str r0, [r5, #0x10]
	b _02245316
_022452B6:
	mov r0, #0x1b
	lsl r0, r0, #0x12
	str r0, [r5, #0xc]
	mov r0, #2
	strh r0, [r4]
	mov r0, #0x64
	str r0, [r5, #0x10]
	b _02245316
_022452C6:
	cmp r6, #0
	bne _022452DA
	mov r1, #0xa
	strb r0, [r5, #4]
	lsl r1, r1, #0x12
	str r1, [r5, #0xc]
	strh r0, [r4]
	mov r0, #0x2e
	str r0, [r5, #0x10]
	b _02245316
_022452DA:
	mov r0, #1
	strb r0, [r5, #4]
	mov r0, #0x1b
	lsl r0, r0, #0x12
	str r0, [r5, #0xc]
	mov r0, #2
	strh r0, [r4]
	mov r0, #0x64
	str r0, [r5, #0x10]
	b _02245316
_022452EE:
	strb r0, [r5, #4]
	cmp r6, #0
	bne _02245302
	mov r1, #0xa
	lsl r1, r1, #0x12
	str r1, [r5, #0xc]
	strh r0, [r4]
	mov r0, #0x2e
	str r0, [r5, #0x10]
	b _02245316
_02245302:
	mov r0, #0x52
	lsl r0, r0, #0x10
	str r0, [r5, #0xc]
	mov r0, #1
	strh r0, [r4]
	mov r0, #0x58
	str r0, [r5, #0x10]
	b _02245316
_02245312:
	bl GF_AssertFail
_02245316:
	ldr r0, [sp]
	str r0, [r5, #8]
	ldr r0, [sp]
	cmp r0, #3
	bne _02245324
	ldr r0, _02245334 ; =ov06_02245478
	b _02245326
_02245324:
	ldr r0, _02245338 ; =ov06_02245544
_02245326:
	str r0, [r5]
	ldr r0, [r7, #0x10]
	ldr r1, _0224533C ; =ov06_02245360
	add r2, r5, #0
	bl TaskManager_Call
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245334: .word ov06_02245478
_02245338: .word ov06_02245544
_0224533C: .word ov06_02245360

	thumb_func_start ov06_02245340
ov06_02245340: ; 0x02245340
	push {r4, lr}
	add r4, r1, #0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	mov r1, #6
	bl sub_020254A0
	ldrh r0, [r0]
	cmp r0, r4
	bne _0224535C
	mov r0, #5
	pop {r4, pc}
_0224535C:
	mov r0, #6
	pop {r4, pc}

	thumb_func_start ov06_02245360
ov06_02245360: ; 0x02245360
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldrb r1, [r4, #5]
	cmp r1, #5
	bhi _02245468
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02245386: ; jump table
	.short _02245392 - _02245386 - 2 ; case 0
	.short _022453F0 - _02245386 - 2 ; case 1
	.short _02245402 - _02245386 - 2 ; case 2
	.short _02245414 - _02245386 - 2 ; case 3
	.short _0224544C - _02245386 - 2 ; case 4
	.short _0224545E - _02245386 - 2 ; case 5
_02245392:
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, _02245470 ; =0x000001DB
	bl ov05_021E7ED8
	bl ov05_021E7EC8
	add r7, r0, #0
	ldr r0, _02245470 ; =0x000001DB
	ldr r1, [r5, #0x2c]
	bl ov05_021F4BD0
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r6, r0, r1
	ldr r0, [r5, #0x2c]
	bl ov05_021F4C88
	str r7, [sp]
	str r6, [sp, #4]
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r3, #0xff
	str r3, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #0x10
	add r3, #0xdc
	bl ov05_021DA464
	ldr r0, [r5, #0x50]
	mov r1, #0x10
	mov r2, #0
	bl ov05_021DA4EC
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	b _02245468
_022453F0:
	ldr r0, [r4, #8]
	cmp r0, #4
	bne _022453FC
	ldr r0, _02245474 ; =0x000006DB
	bl PlaySE
_022453FC:
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02245402:
	ldr r0, _02245474 ; =0x000006DB
	bl sub_02005508
	cmp r0, #0
	bne _02245468
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	b _02245468
_02245414:
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, _02245470 ; =0x000001DB
	bl ov05_021E7ED8
	add r6, r0, #0
	add r0, sp, #0x18
	add r1, r6, #0
	bl ov05_021E7EA0
	add r0, r5, #0
	add r2, r4, #0
	ldr r5, [r4]
	add r1, r4, #0
	add r2, #0xc
	add r3, sp, #0x18
	blx r5
	cmp r0, #0
	beq _02245442
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
_02245442:
	add r0, r6, #0
	add r1, sp, #0x18
	bl ov05_021E7EB0
	b _02245468
_0224544C:
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #0x10
	bl ov05_021DA54C
	ldrb r0, [r4, #5]
	add r0, r0, #1
	strb r0, [r4, #5]
	b _02245468
_0224545E:
	bl FreeToHeap
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02245468:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02245470: .word 0x000001DB
_02245474: .word 0x000006DB

	thumb_func_start ov06_02245478
ov06_02245478: ; 0x02245478
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldrb r0, [r5, #4]
	add r4, r3, #0
	add r6, r2, #0
	cmp r0, #0
	ldr r0, [r4, #8]
	bne _022454D8
	ldrb r1, [r5, #6]
	lsl r2, r1, #2
	ldr r1, _02245538 ; =0x02251324
	ldr r1, [r1, r2]
	sub r0, r0, r1
	str r0, [r4, #8]
	ldrb r0, [r5, #6]
	cmp r0, #6
	bhs _02245526
	mov r0, #2
	ldr r1, [r4, #8]
	lsl r0, r0, #0xe
	sub r1, r1, r0
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r1, r0, #0x10
	ldr r0, [r5, #0x10]
	cmp r1, r0
	bgt _02245526
	ldrb r0, [r5, #7]
	add r0, r0, #1
	strb r0, [r5, #7]
	ldrb r2, [r5, #6]
	ldr r0, _0224553C ; =0x022512E4
	ldrb r1, [r5, #7]
	ldrb r0, [r0, r2]
	cmp r1, r0
	blo _02245526
	cmp r2, #0
	bne _022454CC
	ldr r0, _02245540 ; =0x000006DA
	bl PlaySE
_022454CC:
	ldrb r0, [r5, #6]
	add r0, r0, #1
	strb r0, [r5, #6]
	mov r0, #0
	strb r0, [r5, #7]
	b _02245526
_022454D8:
	ldrb r1, [r5, #6]
	lsl r2, r1, #2
	ldr r1, _02245538 ; =0x02251324
	ldr r1, [r1, r2]
	add r0, r0, r1
	str r0, [r4, #8]
	ldrb r0, [r5, #6]
	cmp r0, #6
	bhs _02245526
	mov r0, #2
	ldr r1, [r4, #8]
	lsl r0, r0, #0xe
	sub r1, r1, r0
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r1, r0, #0x10
	ldr r0, [r5, #0x10]
	cmp r1, r0
	blt _02245526
	ldrb r0, [r5, #7]
	add r0, r0, #1
	strb r0, [r5, #7]
	ldrb r2, [r5, #6]
	ldr r0, _0224553C ; =0x022512E4
	ldrb r1, [r5, #7]
	ldrb r0, [r0, r2]
	cmp r1, r0
	blo _02245526
	cmp r2, #0
	bne _0224551C
	ldr r0, _02245540 ; =0x000006DA
	bl PlaySE
_0224551C:
	ldrb r0, [r5, #6]
	add r0, r0, #1
	strb r0, [r5, #6]
	mov r0, #0
	strb r0, [r5, #7]
_02245526:
	ldr r1, [r4, #8]
	ldr r0, [r6]
	cmp r1, r0
	bne _02245532
	mov r0, #1
	pop {r4, r5, r6, pc}
_02245532:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02245538: .word ov06_02251324
_0224553C: .word ov06_022512E4
_02245540: .word 0x000006DA

	thumb_func_start ov06_02245544
ov06_02245544: ; 0x02245544
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	add r4, r1, #0
	add r7, r2, #0
	str r3, [sp]
	bl PlayerAvatar_GetMapObject
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	add r1, sp, #4
	bl sub_02055350
	mov r0, #2
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0xe
	add r1, r1, r0
	ldr r0, [sp]
	str r1, [r0, #8]
	ldr r0, [r7]
	cmp r1, r0
	bne _02245578
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02245578:
	ldrb r0, [r4, #4]
	cmp r0, #0
	bne _022455E0
	add r0, r6, #0
	bl sub_0205AD98
	cmp r0, #1
	bne _02245640
	ldrb r1, [r4, #6]
	add r0, r6, #0
	lsl r2, r1, #2
	ldr r1, _02245648 ; =0x02251308
	ldr r1, [r1, r2]
	bl sub_0205ADDC
	ldrb r0, [r4, #6]
	cmp r0, #6
	bhs _022455BC
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	ldr r1, [r4, #0x10]
	cmp r0, r1
	ble _022455BC
	ldrb r0, [r4, #6]
	cmp r0, #0
	bne _022455B4
	ldr r0, _0224564C ; =0x000006D9
	bl PlaySE
_022455B4:
	ldrb r0, [r4, #6]
	add r0, r0, #1
	strb r0, [r4, #6]
	b _02245640
_022455BC:
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	ldr r1, [r4, #0x10]
	cmp r0, r1
	bgt _02245640
	ldrb r0, [r4, #6]
	cmp r0, #0
	beq _02245640
	cmp r0, #6
	bne _022455D8
	ldr r0, _02245650 ; =0x000006DA
	bl PlaySE
_022455D8:
	ldrb r0, [r4, #6]
	sub r0, r0, #1
	strb r0, [r4, #6]
	b _02245640
_022455E0:
	add r0, r6, #0
	bl sub_0205AD98
	cmp r0, #1
	bne _02245640
	ldrb r1, [r4, #6]
	add r0, r6, #0
	lsl r2, r1, #2
	ldr r1, _02245654 ; =0x022512EC
	ldr r1, [r1, r2]
	bl sub_0205ADDC
	ldrb r0, [r4, #6]
	cmp r0, #6
	bhs _0224561E
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	ldr r1, [r4, #0x10]
	cmp r0, r1
	bge _0224561E
	ldrb r0, [r4, #6]
	cmp r0, #0
	bne _02245616
	ldr r0, _0224564C ; =0x000006D9
	bl PlaySE
_02245616:
	ldrb r0, [r4, #6]
	add r0, r0, #1
	strb r0, [r4, #6]
	b _02245640
_0224561E:
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	ldr r1, [r4, #0x10]
	cmp r0, r1
	blt _02245640
	ldrb r0, [r4, #6]
	cmp r0, #0
	beq _02245640
	cmp r0, #6
	bne _0224563A
	ldr r0, _02245650 ; =0x000006DA
	bl PlaySE
_0224563A:
	ldrb r0, [r4, #6]
	sub r0, r0, #1
	strb r0, [r4, #6]
_02245640:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02245648: .word ov06_02251308
_0224564C: .word 0x000006D9
_02245650: .word 0x000006DA
_02245654: .word ov06_022512EC

	thumb_func_start ov06_02245658
ov06_02245658: ; 0x02245658
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, r2, #0
	add r4, r1, #0
	add r6, r3, #0
	bl ov06_022456A4
	add r7, r0, #0
	cmp r4, #0
	beq _02245670
	mov r1, #9
	b _02245672
_02245670:
	mov r1, #0xa
_02245672:
	mov r0, #0x6a
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	lsl r1, r7, #2
	add r1, r7, r1
	add r3, r5, #0
	asr r3, r1
	mov r2, #0x1f
	add r1, r3, #0
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	and r1, r2
	lsl r1, r1, #0x18
	lsr r2, r1, #0x16
	ldr r1, [r0, r2]
	str r1, [r6]
	ldr r2, [r0, r2]
	ldr r1, [sp, #0x18]
	str r2, [r1]
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_022456A4
ov06_022456A4: ; 0x022456A4
	push {r4, lr}
	mov r1, #0x7e
	lsl r1, r1, #2
	sub r0, r0, r1
	mov r4, #0
	cmp r0, #5
	bhi _022456E0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022456BE: ; jump table
	.short _022456CA - _022456BE - 2 ; case 0
	.short _022456CC - _022456BE - 2 ; case 1
	.short _022456D0 - _022456BE - 2 ; case 2
	.short _022456D4 - _022456BE - 2 ; case 3
	.short _022456D8 - _022456BE - 2 ; case 4
	.short _022456DC - _022456BE - 2 ; case 5
_022456CA:
	b _022456E4
_022456CC:
	mov r4, #1
	b _022456E4
_022456D0:
	mov r4, #2
	b _022456E4
_022456D4:
	mov r4, #3
	b _022456E4
_022456D8:
	mov r4, #4
	b _022456E4
_022456DC:
	mov r4, #5
	b _022456E4
_022456E0:
	bl GF_AssertFail
_022456E4:
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start SpearPillarSequence
SpearPillarSequence: ; 0x022456E8
	push {r3, lr}
	cmp r1, #9
	bhi _0224579C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022456FA: ; jump table
	.short _0224570E - _022456FA - 2 ; case 0
	.short _02245718 - _022456FA - 2 ; case 1
	.short _02245734 - _022456FA - 2 ; case 2
	.short _0224573E - _022456FA - 2 ; case 3
	.short _02245748 - _022456FA - 2 ; case 4
	.short _02245752 - _022456FA - 2 ; case 5
	.short _0224575C - _022456FA - 2 ; case 6
	.short _02245778 - _022456FA - 2 ; case 7
	.short _02245784 - _022456FA - 2 ; case 8
	.short _02245790 - _022456FA - 2 ; case 9
_0224570E:
	bl ov06_02239CE8
	ldr r1, _022457A4 ; =0x02252424
	str r0, [r1]
	b _022457A0
_02245718:
	ldr r0, _022457A4 ; =0x02252424
	ldr r0, [r0]
	bl ov06_02239D04
	cmp r0, #0
	beq _02245730
	ldr r0, _022457A4 ; =0x02252424
	ldr r0, [r0]
	bl ov06_02239CFC
	mov r0, #1
	pop {r3, pc}
_02245730:
	mov r0, #0
	pop {r3, pc}
_02245734:
	bl ov06_02239F64
	ldr r1, _022457A4 ; =0x02252424
	str r0, [r1]
	b _022457A0
_0224573E:
	ldr r0, _022457A4 ; =0x02252424
	ldr r0, [r0]
	bl ov06_02239F78
	b _022457A0
_02245748:
	bl ov06_0223A2E8
	ldr r1, _022457A4 ; =0x02252424
	str r0, [r1]
	b _022457A0
_02245752:
	ldr r0, _022457A4 ; =0x02252424
	ldr r0, [r0]
	bl ov06_0223A304
	b _022457A0
_0224575C:
	ldr r0, _022457A4 ; =0x02252424
	ldr r0, [r0]
	bl ov06_0223A310
	cmp r0, #6
	bne _02245774
	ldr r0, _022457A4 ; =0x02252424
	ldr r0, [r0]
	bl ov06_0223A2FC
	mov r0, #1
	pop {r3, pc}
_02245774:
	mov r0, #0
	pop {r3, pc}
_02245778:
	mov r1, #0
	bl ov06_0223A1C4
	ldr r1, _022457A4 ; =0x02252424
	str r0, [r1]
	b _022457A0
_02245784:
	mov r1, #1
	bl ov06_0223A1C4
	ldr r1, _022457A4 ; =0x02252424
	str r0, [r1]
	b _022457A0
_02245790:
	mov r1, #2
	bl ov06_0223A1C4
	ldr r1, _022457A4 ; =0x02252424
	str r0, [r1]
	b _022457A0
_0224579C:
	bl GF_AssertFail
_022457A0:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_022457A4: .word ov06_02252424

	thumb_func_start ov06_022457A8
ov06_022457A8: ; 0x022457A8
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_Roamers_Get
	bl sub_0202A9AC
	mov r2, #0
	ldrh r0, [r0, #2]
	add r1, r2, #0
_022457BA:
	cmp r0, #0
	beq _022457C0
	add r2, r2, #1
_022457C0:
	add r1, r1, #1
	cmp r1, #3
	blt _022457BA
	add r0, r2, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_022457CC
ov06_022457CC: ; 0x022457CC
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #3
	blo _022457DC
	bl GF_AssertFail
_022457DC:
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	bl sub_0202A9AC
	add r1, sp, #0
	bl ov06_02245884
	lsl r1, r4, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	ldrh r0, [r0]
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_022457F8
ov06_022457F8: ; 0x022457F8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #3
	blo _02245808
	bl GF_AssertFail
_02245808:
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	bl sub_0202A9AC
	add r1, sp, #0
	bl ov06_02245884
	lsl r1, r4, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	ldrh r0, [r0, #2]
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_02245824
ov06_02245824: ; 0x02245824
	ldr r3, _02245828 ; =sub_0205E49C
	bx r3
	.align 2, 0
_02245828: .word sub_0205E49C

	thumb_func_start ov06_0224582C
ov06_0224582C: ; 0x0224582C
	push {r3, lr}
	sub sp, #8
	add r0, #0x90
	ldr r0, [r0]
	add r1, sp, #4
	add r2, sp, #0
	bl sub_0205E098
	ldr r0, [sp, #4]
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02245844
ov06_02245844: ; 0x02245844
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r1, sp, #0
	add r4, r0, #0
	bl ov06_02245884
	mov r2, #0
	add r3, sp, #0
	add r5, sp, #0xc
_02245856:
	ldr r1, [r3]
	add r2, r2, #1
	ldrh r0, [r1]
	add r3, r3, #4
	strh r0, [r5]
	ldrh r0, [r1, #2]
	strh r0, [r5, #2]
	add r5, r5, #4
	cmp r2, #3
	blt _02245856
	mov r2, #0
	add r1, sp, #0xc
_0224586E:
	ldrh r0, [r1]
	add r2, r2, #1
	strh r0, [r4]
	ldrh r0, [r1, #2]
	add r1, r1, #4
	strh r0, [r4, #2]
	add r4, r4, #4
	cmp r2, #3
	blt _0224586E
	add sp, #0x18
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02245884
ov06_02245884: ; 0x02245884
	push {r3, r4}
	ldrh r4, [r0, #6]
	ldrh r3, [r0, #2]
	cmp r3, r4
	ldrh r2, [r0, #0xa]
	bhs _022458C6
	cmp r4, r2
	bhs _022458A4
	add r2, r0, #0
	add r2, #8
	str r2, [r1]
	add r2, r0, #4
	str r2, [r1, #4]
	str r0, [r1, #8]
	pop {r3, r4}
	bx lr
_022458A4:
	cmp r3, r2
	bhs _022458B8
	add r2, r0, #4
	str r2, [r1]
	add r2, r0, #0
	add r2, #8
	str r2, [r1, #4]
	str r0, [r1, #8]
	pop {r3, r4}
	bx lr
_022458B8:
	add r2, r0, #4
	str r2, [r1]
	str r0, [r1, #4]
	add r0, #8
	str r0, [r1, #8]
	pop {r3, r4}
	bx lr
_022458C6:
	cmp r3, r2
	bhs _022458DA
	add r2, r0, #0
	add r2, #8
	str r2, [r1]
	str r0, [r1, #4]
	add r0, r0, #4
	str r0, [r1, #8]
	pop {r3, r4}
	bx lr
_022458DA:
	cmp r4, r2
	str r0, [r1]
	bhs _022458EE
	add r2, r0, #0
	add r2, #8
	str r2, [r1, #4]
	add r0, r0, #4
	str r0, [r1, #8]
	pop {r3, r4}
	bx lr
_022458EE:
	add r2, r0, #4
	str r2, [r1, #4]
	add r0, #8
	str r0, [r1, #8]
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start ov06_022458FC
ov06_022458FC: ; 0x022458FC
	push {r3, lr}
	mov r1, #0x1c
	bl _u32_div_f
	ldr r0, _0224590C ; =0x02251340
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
_0224590C: .word ov06_02251340

	thumb_func_start GetSwarmInfoFromRand
GetSwarmInfoFromRand: ; 0x02245910
	push {r4, r5, r6, lr}
	sub sp, #0x1a8
	add r5, r1, #0
	mov r1, #0x1c
	add r4, r2, #0
	bl _u32_div_f
	ldr r0, _02245938 ; =0x02251340
	lsl r1, r1, #2
	ldr r6, [r0, r1]
	add r0, sp, #0
	add r1, r6, #0
	bl sub_02034CB4
	ldr r0, [sp, #0x64]
	strh r0, [r4]
	strh r6, [r5]
	add sp, #0x1a8
	pop {r4, r5, r6, pc}
	nop
_02245938: .word ov06_02251340

	thumb_func_start ov06_0224593C
ov06_0224593C: ; 0x0224593C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r2, #0
	ldr r0, [sp, #0x1c]
	add r7, r3, #0
	strb r6, [r5]
	ldr r4, [sp, #0x18]
	strb r7, [r5, #1]
	strb r4, [r5, #2]
	str r0, [sp, #0x1c]
	strb r0, [r5, #3]
	ldr r0, [sp, #0x20]
	mov r2, #4
	strb r0, [r5, #4]
	ldr r0, [sp, #0x24]
	strb r0, [r5, #5]
	ldr r0, [sp, #0x28]
	strb r0, [r5, #6]
	ldr r0, [sp, #0x2c]
	strb r0, [r5, #7]
	add r0, r1, #0
	add r1, r5, #0
	add r1, #0xc
	bl sub_02008C9C
	str r0, [r5, #8]
	add r0, r5, #0
	mov r2, #2
	add r0, #0xc
	mov r1, #0
	lsl r2, r2, #0x14
	bl sub_02008D24
	add r0, r6, #0
	mov r1, #0
	mov r2, #4
	bl sub_02008DEC
	mov r1, #0x4d
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r7, #0
	mov r1, #1
	mov r2, #4
	bl sub_02008DEC
	mov r1, #0x4e
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r4, #0
	mov r1, #2
	mov r2, #4
	bl sub_02008DEC
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [sp, #0x1c]
	mov r1, #3
	mov r2, #4
	bl sub_02008DEC
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r0, #4
	lsl r1, r6, #3
	bl ov06_02248634
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	lsl r1, r7, #3
	bl ov06_02248634
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #4
	lsl r1, r4, #3
	bl ov06_02248634
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r1, [sp, #0x1c]
	mov r0, #4
	lsl r1, r1, #3
	bl ov06_02248634
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r1, #0
	cmp r6, #0
	ble _02245A18
	ble _02245A18
	ldr r0, [sp, #0x20]
	add r2, r1, #0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
_02245A08:
	mov r3, #0x51
	lsl r3, r3, #2
	ldr r3, [r5, r3]
	add r1, r1, #1
	strh r0, [r3, r2]
	add r2, #8
	cmp r1, r6
	blt _02245A08
_02245A18:
	mov r3, #0
	cmp r7, #0
	ble _02245A38
	ble _02245A38
	ldr r0, [sp, #0x24]
	mov r6, #0x52
	lsl r0, r0, #0x10
	add r2, r3, #0
	asr r1, r0, #0x10
	lsl r6, r6, #2
_02245A2C:
	ldr r0, [r5, r6]
	add r3, r3, #1
	strh r1, [r0, r2]
	add r2, #8
	cmp r3, r7
	blt _02245A2C
_02245A38:
	mov r1, #0
	cmp r4, #0
	ble _02245A58
	ble _02245A58
	ldr r2, [sp, #0x28]
	add r0, r1, #0
	lsl r2, r2, #0x10
	asr r6, r2, #0x10
	mov r2, #0x53
	lsl r2, r2, #2
_02245A4C:
	ldr r3, [r5, r2]
	add r1, r1, #1
	strh r6, [r3, r0]
	add r0, #8
	cmp r1, r4
	blt _02245A4C
_02245A58:
	ldr r0, [sp, #0x1c]
	mov r1, #0
	cmp r0, #0
	ble _02245A7C
	ble _02245A7C
	ldr r2, [sp, #0x2c]
	mov r3, #0x15
	lsl r2, r2, #0x10
	add r0, r1, #0
	asr r4, r2, #0x10
	lsl r3, r3, #4
_02245A6E:
	ldr r2, [r5, r3]
	add r1, r1, #1
	strh r4, [r2, r0]
	ldr r2, [sp, #0x1c]
	add r0, #8
	cmp r1, r2
	blt _02245A6E
_02245A7C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02245A80
ov06_02245A80: ; 0x02245A80
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldrb r0, [r5]
	mov r6, #0
	cmp r0, #0
	ble _02245AB0
	add r4, r6, #0
	mov r7, #4
_02245A90:
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	ldrsb r2, [r5, r7]
	add r0, r1, r4
	ldrsh r1, [r1, r4]
	cmp r2, r1
	beq _02245AA6
	ldr r0, [r0, #4]
	bl sub_02009C0C
_02245AA6:
	ldrb r0, [r5]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blt _02245A90
_02245AB0:
	ldrb r0, [r5, #1]
	mov r6, #0
	cmp r0, #0
	ble _02245ADC
	add r4, r6, #0
	mov r7, #5
_02245ABC:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	ldrsb r2, [r5, r7]
	add r0, r1, r4
	ldrsh r1, [r1, r4]
	cmp r2, r1
	beq _02245AD2
	ldr r0, [r0, #4]
	bl sub_02009E04
_02245AD2:
	ldrb r0, [r5, #1]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blt _02245ABC
_02245ADC:
	ldrb r0, [r5, #2]
	mov r6, #0
	cmp r0, #0
	ble _02245B08
	add r4, r6, #0
	mov r7, #6
_02245AE8:
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	ldrsb r2, [r5, r7]
	add r0, r1, r4
	ldrsh r1, [r1, r4]
	cmp r2, r1
	beq _02245AFE
	ldr r0, [r0, #4]
	bl sub_02009474
_02245AFE:
	ldrb r0, [r5, #2]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blt _02245AE8
_02245B08:
	ldrb r0, [r5, #3]
	mov r6, #0
	cmp r0, #0
	ble _02245B34
	add r4, r6, #0
	mov r7, #7
_02245B14:
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	ldrsb r2, [r5, r7]
	add r0, r1, r4
	ldrsh r1, [r1, r4]
	cmp r2, r1
	beq _02245B2A
	ldr r0, [r0, #4]
	bl sub_02009474
_02245B2A:
	ldrb r0, [r5, #3]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blt _02245B14
_02245B34:
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02008E2C
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02008E2C
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02008E2C
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl sub_02008E2C
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FreeToHeap
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FreeToHeap
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FreeToHeap
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FreeToHeap
	ldr r0, [r5, #8]
	bl sub_0201FDB4
	ldr r0, [r5, #8]
	bl sub_0201FD58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02245B94
ov06_02245B94: ; 0x02245B94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldrb r5, [r6]
	str r2, [sp, #0x10]
	str r1, [sp, #0xc]
	add r7, r3, #0
	mov r2, #0
	cmp r5, #0
	ble _02245BFA
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r3, [r6, r0]
	mov r0, #4
	ldrsb r4, [r6, r0]
	mov ip, r3
	add r0, r2, #0
_02245BB6:
	ldrsh r1, [r3, r0]
	cmp r4, r1
	bne _02245BF2
	lsl r4, r2, #3
	mov r0, ip
	strh r7, [r0, r4]
	mov r0, #0x51
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	mov r3, #0
	add r1, r1, r4
	strh r3, [r1, #2]
	str r7, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	sub r0, #0x10
	ldr r0, [r6, r0]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	bl sub_020091E0
	mov r1, #0x51
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	add sp, #0x14
	add r1, r1, r4
	str r0, [r1, #4]
	pop {r4, r5, r6, r7, pc}
_02245BF2:
	add r2, r2, #1
	add r3, #8
	cmp r2, r5
	blt _02245BB6
_02245BFA:
	bl GF_AssertFail
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02245C04
ov06_02245C04: ; 0x02245C04
	push {r4, r5, r6, lr}
	ldrb r3, [r0]
	mov r2, #0
	cmp r3, #0
	ble _02245C32
	mov r4, #0x51
	lsl r4, r4, #2
	ldr r0, [r0, r4]
	add r4, r2, #0
	add r6, r0, #0
_02245C18:
	ldrsh r5, [r6, r4]
	cmp r1, r5
	bne _02245C2A
	lsl r1, r2, #3
	add r0, r0, r1
	ldr r0, [r0, #4]
	bl sub_02009B04
	pop {r4, r5, r6, pc}
_02245C2A:
	add r2, r2, #1
	add r6, #8
	cmp r2, r3
	blt _02245C18
_02245C32:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02245C38
ov06_02245C38: ; 0x02245C38
	push {r4, r5, r6, lr}
	ldrb r3, [r0]
	mov r2, #0
	cmp r3, #0
	ble _02245C66
	mov r4, #0x51
	lsl r4, r4, #2
	ldr r0, [r0, r4]
	add r4, r2, #0
	add r6, r0, #0
_02245C4C:
	ldrsh r5, [r6, r4]
	cmp r1, r5
	bne _02245C5E
	lsl r1, r2, #3
	add r0, r0, r1
	ldr r0, [r0, #4]
	bl sub_02009474
	pop {r4, r5, r6, pc}
_02245C5E:
	add r2, r2, #1
	add r6, #8
	cmp r2, r3
	blt _02245C4C
_02245C66:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02245C6C
ov06_02245C6C: ; 0x02245C6C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r0, #0
	ldrb r5, [r6]
	str r2, [sp, #0x14]
	str r1, [sp, #0x10]
	add r7, r3, #0
	mov r2, #0
	cmp r5, #0
	ble _02245CD4
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r3, [r6, r0]
	mov r0, #5
	ldrsb r4, [r6, r0]
	mov ip, r3
	add r0, r2, #0
_02245C8E:
	ldrsh r1, [r3, r0]
	cmp r4, r1
	bne _02245CCC
	lsl r4, r2, #3
	mov r0, ip
	strh r7, [r0, r4]
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	mov r3, #0
	add r1, r1, r4
	strh r3, [r1, #2]
	str r7, [sp]
	mov r1, #1
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #4
	str r1, [sp, #0xc]
	sub r0, #0x10
	ldr r0, [r6, r0]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	bl sub_02009298
	mov r1, #0x52
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	add sp, #0x18
	add r1, r1, r4
	str r0, [r1, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02245CCC:
	add r2, r2, #1
	add r3, #8
	cmp r2, r5
	blt _02245C8E
_02245CD4:
	bl GF_AssertFail
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_02245CDC
ov06_02245CDC: ; 0x02245CDC
	push {r4, r5, r6, lr}
	ldrb r3, [r0, #1]
	mov r2, #0
	cmp r3, #0
	ble _02245D0A
	mov r4, #0x52
	lsl r4, r4, #2
	ldr r0, [r0, r4]
	add r4, r2, #0
	add r6, r0, #0
_02245CF0:
	ldrsh r5, [r6, r4]
	cmp r1, r5
	bne _02245D02
	lsl r1, r2, #3
	add r0, r0, r1
	ldr r0, [r0, #4]
	bl sub_02009D68
	pop {r4, r5, r6, pc}
_02245D02:
	add r2, r2, #1
	add r6, #8
	cmp r2, r3
	blt _02245CF0
_02245D0A:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02245D10
ov06_02245D10: ; 0x02245D10
	push {r4, r5, r6, lr}
	ldrb r3, [r0, #1]
	mov r2, #0
	cmp r3, #0
	ble _02245D3E
	mov r4, #0x52
	lsl r4, r4, #2
	ldr r0, [r0, r4]
	add r4, r2, #0
	add r6, r0, #0
_02245D24:
	ldrsh r5, [r6, r4]
	cmp r1, r5
	bne _02245D36
	lsl r1, r2, #3
	add r0, r0, r1
	ldr r0, [r0, #4]
	bl sub_02009474
	pop {r4, r5, r6, pc}
_02245D36:
	add r2, r2, #1
	add r6, #8
	cmp r2, r3
	blt _02245D24
_02245D3E:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02245D44
ov06_02245D44: ; 0x02245D44
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldrb r5, [r6]
	str r2, [sp, #0x10]
	str r1, [sp, #0xc]
	add r7, r3, #0
	mov r2, #0
	cmp r5, #0
	ble _02245DAA
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r3, [r6, r0]
	mov r0, #6
	ldrsb r4, [r6, r0]
	mov ip, r3
	add r0, r2, #0
_02245D66:
	ldrsh r1, [r3, r0]
	cmp r4, r1
	bne _02245DA2
	lsl r4, r2, #3
	mov r0, ip
	strh r7, [r0, r4]
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	mov r3, #0
	add r1, r1, r4
	strh r3, [r1, #2]
	str r7, [sp]
	mov r1, #2
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	sub r0, #0x10
	ldr r0, [r6, r0]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	bl sub_02009358
	mov r1, #0x53
	lsl r1, r1, #2
	ldr r1, [r6, r1]
	add sp, #0x14
	add r1, r1, r4
	str r0, [r1, #4]
	pop {r4, r5, r6, r7, pc}
_02245DA2:
	add r2, r2, #1
	add r3, #8
	cmp r2, r5
	blt _02245D66
_02245DAA:
	bl GF_AssertFail
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02245DB4
ov06_02245DB4: ; 0x02245DB4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldrb r5, [r6]
	str r2, [sp, #0x10]
	str r1, [sp, #0xc]
	add r7, r3, #0
	mov r2, #0
	cmp r5, #0
	ble _02245E1A
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r3, [r6, r0]
	mov r0, #7
	ldrsb r4, [r6, r0]
	mov ip, r3
	add r0, r2, #0
_02245DD6:
	ldrsh r1, [r3, r0]
	cmp r4, r1
	bne _02245E12
	lsl r4, r2, #3
	mov r0, ip
	strh r7, [r0, r4]
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r1, [r6, r0]
	mov r3, #0
	add r1, r1, r4
	strh r3, [r1, #2]
	str r7, [sp]
	mov r1, #3
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	sub r0, #0x10
	ldr r0, [r6, r0]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	bl sub_02009358
	mov r1, #0x15
	lsl r1, r1, #4
	ldr r1, [r6, r1]
	add sp, #0x14
	add r1, r1, r4
	str r0, [r1, #4]
	pop {r4, r5, r6, r7, pc}
_02245E12:
	add r2, r2, #1
	add r3, #8
	cmp r2, r5
	blt _02245DD6
_02245E1A:
	bl GF_AssertFail
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02245E24
ov06_02245E24: ; 0x02245E24
	push {r4, r5, r6, lr}
	sub sp, #0x70
	add r5, r0, #0
	add r4, r1, #0
	add r1, r2, #0
	mov r0, #7
	add r2, r3, #0
	ldrsb r3, [r5, r0]
	ldr r6, [sp, #0x84]
	cmp r6, r3
	bne _02245E3E
	sub r0, #8
	str r0, [sp, #0x84]
_02245E3E:
	ldr r0, [sp, #0x84]
	mov r3, #0
	str r0, [sp]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x88]
	str r3, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r6, [r5, r0]
	str r6, [sp, #0x14]
	add r6, r0, #4
	ldr r6, [r5, r6]
	str r6, [sp, #0x18]
	add r6, r0, #0
	add r6, #8
	ldr r6, [r5, r6]
	add r0, #0xc
	str r6, [sp, #0x1c]
	ldr r0, [r5, r0]
	str r0, [sp, #0x20]
	str r3, [sp, #0x24]
	str r3, [sp, #0x28]
	ldr r3, [sp, #0x80]
	add r0, sp, #0x4c
	bl sub_02008AA4
	ldr r0, [r5, #8]
	add r2, sp, #0x34
	str r0, [sp, #0x2c]
	add r0, sp, #0x4c
	str r0, [sp, #0x30]
	ldmia r4!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4]
	str r0, [r2]
	ldr r0, [sp, #0x8c]
	str r0, [sp, #0x40]
	mov r0, #1
	str r0, [sp, #0x44]
	mov r0, #4
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	bl sub_0201FF84
	add r4, r0, #0
	bne _02245EA6
	bl GF_AssertFail
_02245EA6:
	add r0, r4, #0
	add sp, #0x70
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02245EAC
ov06_02245EAC: ; 0x02245EAC
	push {r4, lr}
	add r4, r1, #0
	bl sub_0202011C
	add r2, r0, #0
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start ov06_02245EC0
ov06_02245EC0: ; 0x02245EC0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r4, r0, #0
	mov r2, #0
	add r0, sp, #0x1c
	str r2, [r0]
	str r2, [r0, #4]
	add r3, sp, #0x28
	str r2, [r3]
	str r2, [r3, #4]
	ldr r6, _02245F28 ; =0x02251454
	str r2, [r0, #8]
	ldmia r6!, {r0, r1}
	add r5, sp, #0x10
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	str r2, [r3, #8]
	str r0, [r5]
	add r1, r3, #0
	str r2, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0x84
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r3, r2, #0
	bl ov06_02245E24
	add r4, r0, #0
	mov r1, #2
	bl sub_020200EC
	add r0, r4, #0
	add r1, sp, #0x1c
	bl sub_02020054
	add r0, r4, #0
	add r1, sp, #0x10
	bl sub_02020064
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	add r0, r4, #0
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	nop
_02245F28: .word ov06_02251454

	thumb_func_start ov06_02245F2C
ov06_02245F2C: ; 0x02245F2C
	push {r3, r4, lr}
	sub sp, #0x1c
	mov r3, #0
	add r2, sp, #0x10
	str r3, [r2]
	str r3, [r2, #4]
	str r3, [r2, #8]
	cmp r1, #1
	bne _02245F40
	mov r3, #1
_02245F40:
	mov r2, #2
	str r2, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #0x83
	str r1, [sp, #0xc]
	add r1, sp, #0x10
	bl ov06_02245E24
	add r4, r0, #0
	mov r1, #0
	bl sub_020200A0
	add r0, r4, #0
	mov r1, #6
	bl sub_02020130
	add r0, r4, #0
	add sp, #0x1c
	pop {r3, r4, pc}

	thumb_func_start ov06_02245F6C
ov06_02245F6C: ; 0x02245F6C
	push {r4, r5, lr}
	sub sp, #0x24
	add r5, sp, #0x18
	mov r4, #0
	str r4, [r5]
	str r4, [r5, #4]
	str r0, [sp, #0xc]
	str r2, [sp, #0x14]
	str r3, [sp, #0x10]
	str r4, [r5, #8]
	str r1, [sp, #8]
	add r0, sp, #8
	str r0, [sp]
	mov r0, #0x82
	str r0, [sp, #4]
	add r0, r1, #0
	ldr r1, _02245F9C ; =0x02251524
	add r2, r5, #0
	add r3, r4, #0
	bl sub_020644E4
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_02245F9C: .word ov06_02251524

	thumb_func_start ov06_02245FA0
ov06_02245FA0: ; 0x02245FA0
	push {r3, lr}
	bl sub_02064738
	ldrb r0, [r0, #2]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02245FAC
ov06_02245FAC: ; 0x02245FAC
	push {r4, lr}
	add r4, r1, #0
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x58
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x64]
	bl ov06_02245EC0
	str r0, [r4, #0x68]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02245FD0
ov06_02245FD0: ; 0x02245FD0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl sub_02064738
	add r4, r0, #0
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	beq _02245FE4
	bl sub_02064520
_02245FE4:
	ldr r0, [r4, #0x70]
	cmp r0, #0
	beq _02245FEE
	bl ov05_021F6240
_02245FEE:
	add r0, r5, #0
	bl sub_02064520
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_02245FF8
ov06_02245FF8: ; 0x02245FF8
	ldr r3, _02246000 ; =sub_0201FFC8
	ldr r0, [r1, #0x68]
	bx r3
	nop
_02246000: .word sub_0201FFC8

	thumb_func_start ov06_02246004
ov06_02246004: ; 0x02246004
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrb r0, [r5]
	lsl r1, r0, #2
	ldr r0, _02246020 ; =0x022513D8
	ldr r4, [r0, r1]
_02246010:
	ldrb r1, [r5, #1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #1
	beq _02246010
	pop {r3, r4, r5, pc}
	.align 2, 0
_02246020: .word ov06_022513D8

	thumb_func_start ov06_02246024
ov06_02246024: ; 0x02246024
	push {r3, lr}
	mov r1, #0
	strb r1, [r0, #2]
	ldr r0, [r0, #0x68]
	bl sub_020200A0
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov06_02246034
ov06_02246034: ; 0x02246034
	push {r4, r5, r6, lr}
	sub sp, #0x30
	ldr r4, _02246188 ; =0x02251418
	add r2, r0, #0
	ldmia r4!, {r0, r1}
	add r3, sp, #0x24
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	ldr r4, _0224618C ; =0x0225146C
	str r0, [r3]
	ldmia r4!, {r0, r1}
	add r3, sp, #0x18
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	add r0, r2, #0
	bl sub_02064738
	add r4, r0, #0
	mov r3, #1
	add r5, r4, #0
	strb r3, [r4]
	mov r2, #0
	strb r2, [r4, #2]
	strb r2, [r4, #1]
	str r2, [r4, #4]
	add r6, sp, #0x24
	ldmia r6!, {r0, r1}
	add r5, #8
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	str r0, [r5]
	str r2, [r4, #0x14]
	str r2, [r4, #0x18]
	str r2, [r4, #0x1c]
	ldr r0, _02246190 ; =0x0015E000
	add r2, r4, #0
	add r5, sp, #0x18
	str r0, [r4, #0x38]
	ldmia r5!, {r0, r1}
	add r2, #0x2c
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	str r0, [r2]
	lsl r0, r3, #0xa
	str r0, [r4, #0x50]
	mov r0, #0x2d
	lsl r0, r0, #0xc
	str r0, [r4, #0x40]
	mov r0, #3
	lsl r0, r0, #0x12
	str r0, [r4, #0x48]
	lsl r0, r3, #0x11
	str r0, [r4, #0x4c]
	mov r0, #0x2d
	bl Cos_Wrap
	ldr r2, [r4, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, [r4, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r4, #0x18]
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	str r0, [sp, #0x28]
	ldr r0, [r4, #0x68]
	add r1, sp, #0x24
	bl sub_02020044
	ldr r0, [r4, #0x68]
	add r1, sp, #0x18
	bl sub_02020064
	ldr r1, [r4, #0x38]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0x68]
	bl sub_02020088
	ldr r0, [r4, #0x68]
	mov r1, #0x84
	bl sub_02020310
	ldr r0, [r4, #0x68]
	mov r1, #1
	bl sub_020200A0
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	bl ov06_0224823C
	str r0, [r4, #0x6c]
	ldr r0, [r4, #0x5c]
	mov r1, #4
	bl ov05_021F61F4
	ldr r2, _02246194 ; =0xFFF88000
	mov r1, #1
	mov r3, #0xc
	str r0, [r4, #0x70]
	bl ov05_021F6254
	add r1, sp, #0xc
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r3, _02246198 ; =0x02251490
	str r0, [r1, #8]
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #2
	str r0, [r2]
	ldr r4, [r4, #0x60]
	add r0, r4, #0
	bl sub_020200EC
	add r0, r4, #0
	add r1, sp, #0xc
	bl sub_02020054
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020064
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	add r0, r4, #0
	mov r1, #2
	bl sub_02020130
	bl ov06_02246610
	add sp, #0x30
	pop {r4, r5, r6, pc}
	nop
_02246188: .word ov06_02251418
_0224618C: .word ov06_0225146C
_02246190: .word 0x0015E000
_02246194: .word 0xFFF88000
_02246198: .word ov06_02251490

	thumb_func_start ov06_0224619C
ov06_0224619C: ; 0x0224619C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x4c]
	ldr r6, [r5, #0x68]
	ldr r4, [r5, #0x60]
	sub r0, r1, r0
	str r0, [r5, #0x48]
	bpl _022461B4
	mov r0, #0
	str r0, [r5, #0x48]
_022461B4:
	mov r0, #2
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0xa
	cmp r1, r0
	ble _022461C6
	mov r0, #7
	lsl r0, r0, #0xa
	sub r0, r1, r0
	str r0, [r5, #0x4c]
_022461C6:
	mov r0, #1
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0xc
	cmp r1, r0
	bge _022461D2
	str r0, [r5, #0x4c]
_022461D2:
	mov r0, #0x2d
	bl Cos_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	cmp r0, #0x5a
	bge _0224621A
	mov r0, #1
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [r5, #0x40]
_0224621A:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x50]
	sub r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [r5, #0x2c]
	cmp r1, r0
	bge _0224622C
	str r0, [r5, #0x2c]
_0224622C:
	ldr r1, [r5, #0x30]
	ldr r0, [r5, #0x50]
	sub r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [r5, #0x30]
	cmp r1, r0
	bge _0224623E
	str r0, [r5, #0x30]
_0224623E:
	add r1, r5, #0
	add r0, r6, #0
	add r1, #0x2c
	bl sub_02020064
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x2c
	bl sub_02020064
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x14]
	add r0, r1, r0
	str r0, [sp]
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r6, #0
	add r1, sp, #0
	bl sub_02020044
	mov r0, #0x12
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020044
	ldr r0, [r5, #0x48]
	cmp r0, #0
	bne _0224628E
	mov r0, #0
	str r0, [r5, #4]
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
	b _02246294
_0224628E:
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
_02246294:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224629C
ov06_0224629C: ; 0x0224629C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x6c]
	bl ov06_022482B8
	ldr r0, [r4, #0x70]
	mov r1, #2
	mov r2, #0
	mov r3, #0xc
	bl ov05_021F6254
	mov r0, #1
	lsl r0, r0, #0xa
	str r0, [r4, #0x50]
	lsl r0, r0, #9
	str r0, [r4, #0x40]
	mov r0, #0
	str r0, [r4, #0x48]
	mov r0, #6
	lsl r0, r0, #0xa
	str r0, [r4, #0x4c]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov06_022462D0
ov06_022462D0: ; 0x022462D0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x4c]
	ldr r4, [r5, #0x68]
	add r0, r1, r0
	str r0, [r5, #0x48]
	mov r0, #1
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0xc
	add r2, r1, r0
	lsl r1, r0, #4
	str r2, [r5, #0x4c]
	cmp r2, r1
	ble _022462F4
	lsl r0, r0, #4
	str r0, [r5, #0x4c]
_022462F4:
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Cos_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x14]
	mov r0, #0x80
	bl Sin_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x18]
	mov r0, #0xa
	ldr r1, [r5, #0x40]
	lsl r0, r0, #0x10
	cmp r1, r0
	bge _02246338
	mov r0, #1
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r5, #0x40]
_02246338:
	mov r0, #2
	ldr r1, [r5, #0x38]
	lsl r0, r0, #0xc
	add r1, r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	str r1, [r5, #0x38]
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [r5, #0x2c]
	cmp r1, r0
	ble _0224636A
	str r0, [r5, #0x2c]
_0224636A:
	ldr r1, [r5, #0x30]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [r5, #0x30]
	cmp r1, r0
	ble _0224637C
	str r0, [r5, #0x30]
_0224637C:
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x2c
	bl sub_02020064
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x14]
	add r0, r1, r0
	str r0, [sp]
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x18]
	sub r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020044
	ldr r1, [sp, #4]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r1, r0, #0xc
	mov r0, #0xf
	mvn r0, r0
	cmp r1, r0
	bgt _022463B6
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
_022463B6:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_022463BC
ov06_022463BC: ; 0x022463BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x68]
	mov r1, #0
	bl sub_020200A0
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl sub_02020130
	mov r0, #0
	str r0, [r4, #4]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_022463E0
ov06_022463E0: ; 0x022463E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0x14
	bge _022463F6
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022463F6:
	ldr r3, _02246498 ; =0x0225143C
	add r2, sp, #0xc
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r3, _0224649C ; =0x02251448
	str r0, [r2]
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	add r5, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r7, #0
	str r0, [r2]
	add r2, r4, #0
	str r7, [r4, #4]
	add r3, r6, #0
	ldmia r3!, {r0, r1}
	add r2, #8
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	str r7, [r4, #0x14]
	str r7, [r4, #0x18]
	str r7, [r4, #0x1c]
	str r7, [r4, #0x38]
	add r2, r4, #0
	ldmia r5!, {r0, r1}
	add r2, #0x2c
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r2]
	lsl r1, r1, #8
	ldr r0, _022464A0 ; =0x0013B000
	str r1, [r4, #0x50]
	str r0, [r4, #0x40]
	lsl r0, r1, #0xa
	str r0, [r4, #0x48]
	lsl r0, r1, #4
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x68]
	add r1, r6, #0
	bl sub_02020044
	ldr r0, [r4, #0x68]
	add r1, sp, #0
	bl sub_02020064
	ldr r1, [r4, #0x38]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0x68]
	bl sub_02020088
	ldr r0, [r4, #0x68]
	mov r1, #1
	bl sub_020200A0
	ldr r0, [r4, #0x60]
	mov r1, #6
	bl sub_02020130
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl sub_020200BC
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	mov r0, #1
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246498: .word ov06_0225143C
_0224649C: .word ov06_02251448
_022464A0: .word 0x0013B000

	thumb_func_start ov06_022464A4
ov06_022464A4: ; 0x022464A4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x4c]
	ldr r4, [r5, #0x68]
	sub r0, r1, r0
	str r0, [r5, #0x48]
	mov r0, #1
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0x10
	cmp r1, r0
	bge _022464C4
	lsr r0, r0, #3
	add r0, r1, r0
	str r0, [r5, #0x4c]
_022464C4:
	ldr r0, [r5, #0x48]
	cmp r0, #0
	bge _022464CE
	mov r0, #0
	str r0, [r5, #0x48]
_022464CE:
	ldr r0, _022465AC ; =0x0000013B
	bl Cos_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	cmp r0, #0xb4
	bge _02246516
	mov r0, #1
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [r5, #0x40]
_02246516:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x50]
	sub r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xa
	str r1, [r5, #0x2c]
	cmp r1, r0
	bge _02246528
	str r0, [r5, #0x2c]
_02246528:
	ldr r1, [r5, #0x30]
	ldr r0, [r5, #0x50]
	sub r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xa
	str r1, [r5, #0x30]
	cmp r1, r0
	bge _0224653A
	str r0, [r5, #0x30]
_0224653A:
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x2c
	bl sub_02020064
	mov r0, #6
	ldr r1, [r5, #0x38]
	lsl r0, r0, #0xc
	add r1, r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	str r1, [r5, #0x38]
	cmp r0, #0x3c
	ble _02246560
	mov r0, #0xf
	lsl r0, r0, #0xe
	str r0, [r5, #0x38]
_02246560:
	ldr r1, [r5, #0x38]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x14]
	add r0, r1, r0
	str r0, [sp]
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020044
	ldr r0, [r5, #0x48]
	cmp r0, #0
	bgt _022465A4
	add r0, r4, #0
	mov r1, #0
	bl sub_020200A0
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
_022465A4:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_022465AC: .word 0x0000013B

	thumb_func_start ov06_022465B0
ov06_022465B0: ; 0x022465B0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #8
	bne _022465CE
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl sub_02020130
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl ov06_02246658
_022465CE:
	ldr r0, [r4, #4]
	cmp r0, #0xa
	bne _022465DC
	ldr r0, [r4, #0x60]
	mov r1, #0
	bl sub_020200A0
_022465DC:
	ldr r0, [r4, #4]
	cmp r0, #0xf
	ble _022465FA
	ldr r0, [r4, #0x70]
	bl ov05_021F6234
	cmp r0, #1
	bne _022465FA
	mov r0, #0
	str r0, [r4, #4]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	mov r0, #2
	strb r0, [r4, #2]
_022465FA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02246600
ov06_02246600: ; 0x02246600
	mov r0, #0
	bx lr

	thumb_func_start ov06_02246604
ov06_02246604: ; 0x02246604
	ldr r3, _0224660C ; =NARC_New
	mov r0, #0x61
	mov r1, #4
	bx r3
	.align 2, 0
_0224660C: .word NARC_New

	thumb_func_start ov06_02246610
ov06_02246610: ; 0x02246610
	push {lr}
	sub sp, #0xc
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r3, _02246630 ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl BeginNormalPaletteFade
	add sp, #0xc
	pop {pc}
	nop
_02246630: .word 0x00007FFF

	thumb_func_start ov06_02246634
ov06_02246634: ; 0x02246634
	push {lr}
	sub sp, #0xc
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _02246654 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl BeginNormalPaletteFade
	add sp, #0xc
	pop {pc}
	.align 2, 0
_02246654: .word 0x00007FFF

	thumb_func_start ov06_02246658
ov06_02246658: ; 0x02246658
	push {r4, lr}
	ldr r0, [r0, #0x38]
	add r4, r1, #0
	bl PlayerAvatar_GetMapObject
	add r1, r4, #0
	bl MapObject_SetVisible
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224666C
ov06_0224666C: ; 0x0224666C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl ov06_022466C0
	add r1, r0, #0
	str r4, [r1, #0x5c]
	str r6, [r1, #0xc]
	str r5, [r1, #0x20]
	cmp r5, #0
	bne _0224668E
	ldr r0, _02246698 ; =ov06_022466E8
	mov r2, #0x85
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
_0224668E:
	ldr r0, _0224669C ; =ov06_02246AA8
	mov r2, #0x85
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_02246698: .word ov06_022466E8
_0224669C: .word ov06_02246AA8

	thumb_func_start ov06_022466A0
ov06_022466A0: ; 0x022466A0
	push {r3, lr}
	bl sub_0201B6C8
	ldr r0, [r0, #4]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_022466AC
ov06_022466AC: ; 0x022466AC
	push {r4, lr}
	add r4, r0, #0
	bl sub_0201B6C8
	bl ov06_022466E0
	add r0, r4, #0
	bl sub_0200CAB4
	pop {r4, pc}

	thumb_func_start ov06_022466C0
ov06_022466C0: ; 0x022466C0
	push {r3, r4, r5, lr}
	mov r1, #0x87
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeapAtEnd
	mov r2, #0x87
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	str r5, [r4, #0x60]
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_022466E0
ov06_022466E0: ; 0x022466E0
	ldr r3, _022466E4 ; =FreeToHeap
	bx r3
	.align 2, 0
_022466E4: .word FreeToHeap

	thumb_func_start ov06_022466E8
ov06_022466E8: ; 0x022466E8
	push {r3, r4, r5, lr}
	ldr r4, _02246718 ; =0x022515A0
	add r5, r1, #0
_022466EE:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #1
	beq _022466EE
	ldr r0, [r5, #0x10]
	cmp r0, #1
	bne _02246716
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02246710
	bl sub_02064584
_02246710:
	add r0, r5, #0
	bl ov06_02247300
_02246716:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02246718: .word ov06_022515A0

	thumb_func_start ov06_0224671C
ov06_0224671C: ; 0x0224671C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02246F0C
	add r0, r4, #0
	bl ov06_02246D3C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov06_02246734
ov06_02246734: ; 0x02246734
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0224674A
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, pc}
_0224674A:
	ldr r5, _0224679C ; =0x022513E8
	add r3, sp, #0xc
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r5, _022467A0 ; =0x022514A8
	str r0, [r3]
	ldmia r5!, {r0, r1}
	add r3, sp, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	add r0, r4, #0
	bl ov06_022473EC
	mov r1, #0x79
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	add r1, sp, #0
	bl ov06_0224798C
	mov r1, #0x7a
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	bl ov06_022479AC
	add r0, r4, #0
	bl ov06_02246D8C
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r1, [r4]
	add r1, r1, #1
	str r1, [r4]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224679C: .word ov06_022513E8
_022467A0: .word ov06_022514A8

	thumb_func_start ov06_022467A4
ov06_022467A4: ; 0x022467A4
	push {r4, lr}
	add r4, r0, #0
	bl ov06_022486CC
	mov r0, #0
	ldr r1, _022467D8 ; =0xFFFC0000
	str r0, [r4, #0x2c]
	str r1, [r4, #0x54]
	mov r1, #0xfe
	lsl r1, r1, #0xc
	str r1, [r4, #0x44]
	mov r1, #0xff
	lsl r1, r1, #0xc
	str r1, [r4, #0x48]
	mov r1, #0x5f
	lsl r1, r1, #0xc
	str r1, [r4, #0x4c]
	mov r1, #0x61
	lsl r1, r1, #0xc
	str r1, [r4, #0x50]
	mov r1, #1
	str r1, [r4, #0x2c]
	ldr r1, [r4]
	add r1, r1, #1
	str r1, [r4]
	pop {r4, pc}
	.align 2, 0
_022467D8: .word 0xFFFC0000

	thumb_func_start ov06_022467DC
ov06_022467DC: ; 0x022467DC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r2, #0
	str r2, [r4, #0x2c]
	ldr r1, [r4, #0x44]
	ldr r0, [r4, #0x54]
	add r0, r1, r0
	str r0, [r4, #0x44]
	cmp r0, #0
	bgt _02246800
	mov r0, #2
	str r2, [r4, #0x44]
	lsl r0, r0, #0xc
	str r0, [r4, #0x54]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02246800:
	ldr r0, [r4, #0x50]
	str r0, [sp]
	ldr r1, [r4, #0x44]
	ldr r2, [r4, #0x4c]
	ldr r3, [r4, #0x48]
	add r0, r4, #0
	bl ov06_02247670
	mov r0, #1
	str r0, [r4, #0x2c]
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224681C
ov06_0224681C: ; 0x0224681C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r1, [r4, #0x4c]
	ldr r0, [r4, #0x54]
	sub r0, r1, r0
	str r0, [r4, #0x4c]
	ldr r1, [r4, #0x50]
	ldr r0, [r4, #0x54]
	add r0, r1, r0
	str r0, [r4, #0x50]
	mov r0, #2
	ldr r1, [r4, #0x54]
	lsl r0, r0, #0xc
	add r2, r1, r0
	lsl r1, r0, #4
	str r2, [r4, #0x54]
	cmp r2, r1
	ble _0224684A
	lsl r0, r0, #4
	str r0, [r4, #0x54]
_0224684A:
	mov r0, #0xe
	ldr r1, [r4, #0x4c]
	lsl r0, r0, #0xe
	cmp r1, r0
	bge _02246856
	str r0, [r4, #0x4c]
_02246856:
	mov r0, #0x22
	ldr r1, [r4, #0x50]
	lsl r0, r0, #0xe
	cmp r1, r0
	ble _02246862
	str r0, [r4, #0x50]
_02246862:
	ldr r0, [r4, #0x50]
	str r0, [sp]
	ldr r1, [r4, #0x44]
	ldr r2, [r4, #0x4c]
	ldr r3, [r4, #0x48]
	add r0, r4, #0
	bl ov06_02247670
	mov r0, #1
	str r0, [r4, #0x2c]
	mov r0, #0xe
	ldr r1, [r4, #0x4c]
	lsl r0, r0, #0xe
	cmp r1, r0
	bne _0224689A
	mov r0, #0x22
	ldr r1, [r4, #0x50]
	lsl r0, r0, #0xe
	cmp r1, r0
	bne _0224689A
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov06_02247424
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_0224689A:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start ov06_022468A0
ov06_022468A0: ; 0x022468A0
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	cmp r1, #0xf
	blt _022468B8
	mov r1, #0
	str r1, [r0, #8]
	ldr r1, _022468BC ; =0xFFFC0000
	str r1, [r0, #0x58]
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
_022468B8:
	mov r0, #0
	bx lr
	.align 2, 0
_022468BC: .word 0xFFFC0000

	thumb_func_start ov06_022468C0
ov06_022468C0: ; 0x022468C0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_0202011C
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [sp]
	ldr r0, [r4, #0x58]
	add r1, r1, r0
	mov r0, #0xa
	lsl r0, r0, #0x10
	str r1, [sp]
	cmp r1, r0
	bgt _022468F8
	mov r0, #3
	lsl r0, r0, #0x12
	str r0, [sp]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_022468F8:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0
	bl sub_02020044
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224690C
ov06_0224690C: ; 0x0224690C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r1, [r4, #0x58]
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	ldr r0, _02246970 ; =0xFFFFE000
	str r1, [r4, #0x58]
	cmp r1, r0
	ble _0224693C
	str r0, [r4, #0x58]
	ldr r0, [r4]
	mov r1, #5
	add r0, r0, #1
	str r0, [r4]
	ldr r0, [r4, #0x5c]
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl sub_02005578
_0224693C:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_0202011C
	add r5, r0, #0
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r1, [sp]
	ldr r0, [r4, #0x58]
	add r0, r1, r0
	str r0, [sp]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl sub_02020044
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02246970: .word 0xFFFFE000

	thumb_func_start ov06_02246974
ov06_02246974: ; 0x02246974
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	cmp r1, #8
	blt _0224698C
	mov r1, #0
	str r1, [r0, #8]
	ldr r1, _02246990 ; =0xFFFFF000
	str r1, [r0, #0x58]
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
_0224698C:
	mov r0, #0
	bx lr
	.align 2, 0
_02246990: .word 0xFFFFF000

	thumb_func_start ov06_02246994
ov06_02246994: ; 0x02246994
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x58]
	lsl r1, r0, #1
	ldr r0, _022469F0 ; =0xFFFC0000
	str r1, [r4, #0x58]
	cmp r1, r0
	bge _022469A8
	str r0, [r4, #0x58]
_022469A8:
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_0202011C
	add r5, r0, #0
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r1, [sp]
	ldr r0, [r4, #0x58]
	add r0, r1, r0
	str r0, [sp]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r2, #0
	bl sub_02020044
	ldr r1, [sp]
	ldr r0, _022469F4 ; =0xFFFD8000
	cmp r1, r0
	bgt _022469E8
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [r4, #0x54]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_022469E8:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_022469F0: .word 0xFFFC0000
_022469F4: .word 0xFFFD8000

	thumb_func_start ov06_022469F8
ov06_022469F8: ; 0x022469F8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r1, [r4, #0x4c]
	ldr r0, [r4, #0x54]
	add r0, r1, r0
	str r0, [r4, #0x4c]
	ldr r1, [r4, #0x50]
	ldr r0, [r4, #0x54]
	sub r0, r1, r0
	str r0, [r4, #0x50]
	mov r0, #1
	ldr r1, [r4, #0x54]
	lsl r0, r0, #0xe
	add r2, r1, r0
	lsl r1, r0, #3
	str r2, [r4, #0x54]
	cmp r2, r1
	ble _02246A26
	lsl r0, r0, #3
	str r0, [r4, #0x54]
_02246A26:
	mov r0, #0x16
	ldr r1, [r4, #0x4c]
	lsl r0, r0, #0xe
	cmp r1, r0
	blt _02246A32
	str r0, [r4, #0x4c]
_02246A32:
	mov r0, #0x1a
	ldr r1, [r4, #0x50]
	lsl r0, r0, #0xe
	cmp r1, r0
	bgt _02246A3E
	str r0, [r4, #0x50]
_02246A3E:
	ldr r0, [r4, #0x50]
	str r0, [sp]
	ldr r1, [r4, #0x44]
	ldr r2, [r4, #0x4c]
	ldr r3, [r4, #0x48]
	add r0, r4, #0
	bl ov06_02247670
	mov r0, #1
	str r0, [r4, #0x2c]
	mov r0, #0x16
	ldr r1, [r4, #0x4c]
	lsl r0, r0, #0xe
	cmp r1, r0
	bne _02246A72
	mov r0, #0x1a
	ldr r1, [r4, #0x50]
	lsl r0, r0, #0xe
	cmp r1, r0
	bne _02246A72
	add r0, r4, #0
	bl ov06_02248708
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02246A72:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start ov06_02246A78
ov06_02246A78: ; 0x02246A78
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02246FB8
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r1, [r4]
	add r1, r1, #1
	str r1, [r4]
	pop {r4, pc}

	thumb_func_start ov06_02246A8C
ov06_02246A8C: ; 0x02246A8C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_022476A4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02246AA0
ov06_02246AA0: ; 0x02246AA0
	mov r1, #1
	str r1, [r0, #4]
	mov r0, #0
	bx lr

	thumb_func_start ov06_02246AA8
ov06_02246AA8: ; 0x02246AA8
	push {r3, r4, r5, lr}
	ldr r4, _02246AD8 ; =0x022515D8
	add r5, r1, #0
_02246AAE:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #1
	beq _02246AAE
	ldr r0, [r5, #0x10]
	cmp r0, #1
	bne _02246AD6
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02246AD0
	bl sub_02064584
_02246AD0:
	add r0, r5, #0
	bl ov06_02247300
_02246AD6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02246AD8: .word ov06_022515D8

	thumb_func_start ov06_02246ADC
ov06_02246ADC: ; 0x02246ADC
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02246AF2
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, pc}
_02246AF2:
	ldr r5, _02246B44 ; =0x0225149C
	add r3, sp, #0xc
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r5, _02246B48 ; =0x022513F4
	str r0, [r3]
	ldmia r5!, {r0, r1}
	add r3, sp, #0
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r3]
	add r0, r4, #0
	bl ov06_022473EC
	mov r1, #0x79
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	add r1, sp, #0
	bl ov06_0224798C
	mov r1, #0x7a
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	mov r1, #1
	bl ov06_022479AC
	add r0, r4, #0
	bl ov06_02246D8C
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r1, [r4]
	add r1, r1, #1
	str r1, [r4]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_02246B44: .word ov06_0225149C
_02246B48: .word ov06_022513F4

	thumb_func_start ov06_02246B4C
ov06_02246B4C: ; 0x02246B4C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_022478A8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02246B60
ov06_02246B60: ; 0x02246B60
	push {r4, lr}
	add r4, r0, #0
	bl ov06_022474A4
	add r0, r4, #0
	bl ov06_02246D64
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov06_02246B78
ov06_02246B78: ; 0x02246B78
	push {r4, lr}
	mov r1, #0x82
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #0
	bne _02246B8A
	mov r0, #0
	pop {r4, pc}
_02246B8A:
	bl ov06_02246D8C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov06_02246B98
ov06_02246B98: ; 0x02246B98
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02247B2C
	add r0, r4, #0
	bl ov06_02247C0C
	add r0, r4, #0
	bl ov06_02247664
	add r0, r4, #0
	mov r1, #1
	bl ov06_02248654
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02246BC0
ov06_02246BC0: ; 0x02246BC0
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02247B60
	cmp r0, #2
	beq _02246BD0
	mov r0, #0
	pop {r4, pc}
_02246BD0:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_02020130
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02246BE8
ov06_02246BE8: ; 0x02246BE8
	push {r3, lr}
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	cmp r1, #0x14
	blt _02246C02
	mov r1, #0
	str r1, [r0, #8]
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	bl ov06_02247DC4
_02246C02:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02246C08
ov06_02246C08: ; 0x02246C08
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02247B60
	cmp r0, #3
	beq _02246C18
	mov r0, #0
	pop {r4, pc}
_02246C18:
	ldr r0, _02246C34 ; =0x00000649
	bl PlaySE
	mov r0, #2
	lsl r0, r0, #0xa
	str r0, [r4, #0x54]
	mov r0, #2
	str r0, [r4, #0x14]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	nop
_02246C34: .word 0x00000649

	thumb_func_start ov06_02246C38
ov06_02246C38: ; 0x02246C38
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r1, [r4, #0x4c]
	ldr r0, [r4, #0x54]
	add r0, r1, r0
	str r0, [r4, #0x4c]
	ldr r1, [r4, #0x50]
	ldr r0, [r4, #0x54]
	sub r0, r1, r0
	str r0, [r4, #0x50]
	mov r0, #2
	ldr r1, [r4, #0x54]
	lsl r0, r0, #0xa
	add r2, r1, r0
	lsl r1, r0, #5
	str r2, [r4, #0x54]
	cmp r2, r1
	ble _02246C66
	lsl r0, r0, #5
	str r0, [r4, #0x54]
_02246C66:
	mov r0, #0x5f
	ldr r1, [r4, #0x4c]
	lsl r0, r0, #0xc
	cmp r1, r0
	blt _02246C72
	str r0, [r4, #0x4c]
_02246C72:
	mov r0, #0x61
	ldr r1, [r4, #0x50]
	lsl r0, r0, #0xc
	cmp r1, r0
	bgt _02246C7E
	str r0, [r4, #0x50]
_02246C7E:
	ldr r0, [r4, #0x50]
	str r0, [sp]
	ldr r1, [r4, #0x44]
	ldr r2, [r4, #0x4c]
	ldr r3, [r4, #0x48]
	add r0, r4, #0
	bl ov06_02247670
	mov r0, #1
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02246CAA
	add r0, r4, #0
	bl ov06_02247B60
	cmp r0, #4
	bne _02246CAA
	mov r0, #1
	str r0, [r4, #0x18]
	bl ov06_02246634
_02246CAA:
	mov r0, #0x5f
	ldr r1, [r4, #0x4c]
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _02246CD6
	mov r0, #0x61
	ldr r1, [r4, #0x50]
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _02246CD6
	ldr r0, [r4, #0x60]
	ldr r0, [r0, #8]
	bl ov06_02247610
	mov r0, #1
	str r0, [r4, #0x14]
	add r0, r4, #0
	bl ov06_02247648
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02246CD6:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start ov06_02246CDC
ov06_02246CDC: ; 0x02246CDC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x18]
	cmp r1, #0
	bne _02246CF6
	bl ov06_02247B60
	cmp r0, #4
	bne _02246CF6
	mov r0, #1
	str r0, [r4, #0x18]
	bl ov06_02246634
_02246CF6:
	add r0, r4, #0
	bl ov06_02247B60
	cmp r0, #2
	beq _02246D04
	mov r0, #0
	pop {r4, pc}
_02246D04:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02246D12
	mov r0, #1
	str r0, [r4, #0x18]
	bl ov06_02246634
_02246D12:
	add r0, r4, #0
	bl ov06_02247B70
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02246D24
ov06_02246D24: ; 0x02246D24
	push {r4, lr}
	add r4, r0, #0
	bl IsPaletteFadeFinished
	cmp r0, #0
	beq _02246D36
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_02246D36:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02246D3C
ov06_02246D3C: ; 0x02246D3C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x81
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02246D60 ; =ov06_02246DA8
	add r1, r4, #0
	mov r2, #0x80
	bl sub_0200CA60
	mov r1, #0x85
	lsl r1, r1, #2
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_02246D60: .word ov06_02246DA8

	thumb_func_start ov06_02246D64
ov06_02246D64: ; 0x02246D64
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x81
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _02246D88 ; =ov06_02246EA4
	add r1, r4, #0
	mov r2, #0x80
	bl sub_0200CA60
	mov r1, #0x85
	lsl r1, r1, #2
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_02246D88: .word ov06_02246EA4

	thumb_func_start ov06_02246D8C
ov06_02246D8C: ; 0x02246D8C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x85
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02246DA6
	bl sub_0200CAB4
	mov r0, #0x85
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_02246DA6:
	pop {r4, pc}

	thumb_func_start ov06_02246DA8
ov06_02246DA8: ; 0x02246DA8
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #0x81
	add r6, r1, #0
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	bne _02246E1E
	mov r7, #0x6b
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02246DBE:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02246DC8
	bl sub_02009B04
_02246DC8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02246DBE
	mov r7, #0x6f
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_02246DD8:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _02246DE2
	bl sub_02009D68
_02246DE2:
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #3
	blt _02246DD8
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _02246DFA
	add r0, r6, #0
	bl ov06_02247808
_02246DFA:
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r1, [r6, r0]
	cmp r1, #0
	beq _02246E0A
	add r0, r6, #0
	bl ov06_02247860
_02246E0A:
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	mov r2, #0x80
	add r1, r1, #1
	str r1, [r6, r0]
	ldr r0, _02246E20 ; =ov06_02246E24
	add r1, r6, #0
	bl sub_0200CA98
_02246E1E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02246E20: .word ov06_02246E24

	thumb_func_start ov06_02246E24
ov06_02246E24: ; 0x02246E24
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	mov r0, #0x81
	add r6, r1, #0
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #1
	bne _02246EA2
	mov r7, #0x6b
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02246E3C:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02246E46
	bl sub_02009474
_02246E46:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02246E3C
	mov r7, #0x6f
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_02246E56:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _02246E60
	bl sub_02009474
_02246E60:
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #3
	blt _02246E56
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _02246E7E
	bl FreeToHeap
	mov r0, #0x83
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r6, r0]
_02246E7E:
	mov r0, #0x21
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _02246E94
	bl FreeToHeap
	mov r0, #0x21
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
_02246E94:
	mov r0, #0x82
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r6, r0]
	ldr r0, [sp]
	bl sub_0200CAB4
_02246EA2:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_02246EA4
ov06_02246EA4: ; 0x02246EA4
	push {r4, lr}
	mov r0, #0x67
	add r4, r1, #0
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020094F0
	mov r1, #0x81
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #0
	bne _02246ED6
	bl sub_02009B04
	ldr r0, _02246ED8 ; =ov06_02246EDC
	add r1, r4, #0
	mov r2, #0x80
	bl sub_0200CA98
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_02246ED6:
	pop {r4, pc}
	.align 2, 0
_02246ED8: .word ov06_02246EDC

	thumb_func_start ov06_02246EDC
ov06_02246EDC: ; 0x02246EDC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x67
	add r4, r1, #0
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020094F0
	mov r1, #0x81
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #1
	bne _02246F0A
	bl sub_02009474
	mov r0, #0x82
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r5, #0
	bl sub_0200CAB4
_02246F0A:
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02246F0C
ov06_02246F0C: ; 0x02246F0C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl ov06_0224700C
	mov r2, #3
	mov r3, #1
	add r4, r0, #0
	lsl r2, r2, #0x12
	add r0, r5, #0
	mov r1, #0
	lsl r3, r3, #0xc
	str r2, [sp]
	bl ov06_02247670
	add r0, r5, #0
	bl ov06_0224761C
	ldr r0, [r5, #0x60]
	mov r1, #0
	ldr r0, [r0, #8]
	bl GetBgPriority
	strh r0, [r5, #0x24]
	ldr r0, [r5, #0x60]
	mov r1, #3
	ldr r0, [r0, #8]
	bl GetBgPriority
	strh r0, [r5, #0x26]
	ldr r2, _02246FB4 ; =0x0400000A
	mov r1, #3
	ldrh r3, [r2]
	mov r0, #1
	bic r3, r1
	orr r0, r3
	strh r0, [r2]
	ldrh r0, [r2, #4]
	bic r0, r1
	strh r0, [r2, #4]
	mov r0, #8
	mov r1, #0
	bl GfGfx_EngineATogglePlanes
	add r2, r5, #0
	add r0, r4, #0
	mov r1, #2
	add r2, #0x6c
	bl ov06_02247544
	ldr r0, [r5, #0x60]
	add r3, r5, #0
	ldr r0, [r0, #8]
	add r1, r4, #0
	mov r2, #0
	add r3, #0x68
	bl ov06_0224756C
	ldr r0, [r5, #0x60]
	add r3, r5, #0
	ldr r0, [r0, #8]
	add r1, r4, #0
	mov r2, #1
	add r3, #0x64
	bl ov06_022475A4
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02247018
	add r0, r4, #0
	bl NARC_Delete
	mov r0, #4
	mov r1, #0x20
	bl sub_020643C0
	mov r1, #0x1e
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #8
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	pop {r3, r4, r5, pc}
	.align 2, 0
_02246FB4: .word 0x0400000A

	thumb_func_start ov06_02246FB8
ov06_02246FB8: ; 0x02246FB8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	mov r1, #0
	bl GfGfx_EngineATogglePlanes
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl sub_020643F0
	ldr r0, [r4, #0x60]
	ldr r0, [r0, #8]
	bl ov06_02247610
	add r0, r4, #0
	bl ov06_0224725C
	ldr r2, _02247008 ; =0x04000008
	ldrh r1, [r4, #0x24]
	ldrh r3, [r2]
	mov r0, #3
	bic r3, r0
	orr r1, r3
	strh r1, [r2]
	ldrh r1, [r2, #6]
	bic r1, r0
	ldrh r0, [r4, #0x26]
	orr r0, r1
	strh r0, [r2, #6]
	mov r0, #0
	mov r1, #1
	bl sub_02054590
	mov r0, #8
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	pop {r4, pc}
	nop
_02247008: .word 0x04000008

	thumb_func_start ov06_0224700C
ov06_0224700C: ; 0x0224700C
	ldr r3, _02247014 ; =NARC_New
	mov r0, #0x61
	mov r1, #4
	bx r3
	.align 2, 0
_02247014: .word NARC_New

	thumb_func_start ov06_02247018
ov06_02247018: ; 0x02247018
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r1, #0
	mov r1, #0x7d
	add r5, r0, #0
	lsl r1, r1, #2
	add r1, r5, r1
	bl ov06_0224777C
	add r1, r5, #0
	mov r0, #0x20
	add r1, #0x74
	mov r2, #4
	bl sub_02008C9C
	str r0, [r5, #0x70]
	add r0, r5, #0
	mov r2, #2
	add r0, #0x74
	mov r1, #0
	lsl r2, r2, #0x14
	bl sub_02008D24
	mov r0, #4
	mov r1, #0
	add r2, r0, #0
	bl sub_02008DEC
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	mov r1, #1
	mov r2, #4
	bl sub_02008DEC
	mov r1, #0x1a
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #4
	mov r1, #2
	add r2, r0, #0
	bl sub_02008DEC
	mov r1, #0x69
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #2
	mov r1, #3
	mov r2, #4
	bl sub_02008DEC
	mov r1, #0x6a
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0xa
	mov r3, #0
	bl sub_020091E0
	mov r1, #0x6b
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _022470C6
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x10
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0xd
	mov r3, #0
	bl sub_020091E0
	b _022470E0
_022470C6:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x10
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0x10
	mov r3, #0
	bl sub_020091E0
_022470E0:
	mov r1, #0x1b
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_022477E4
	mov r1, #0x6d
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r6, #0
	str r6, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #4
	sub r1, #0x14
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #3
	add r3, r6, #0
	bl sub_02009298
	mov r1, #0x6f
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, #0xc]
	add r6, r6, #1
	cmp r0, #0
	beq _02247142
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r2, #4
	str r2, [sp, #0xc]
	sub r1, #0x1c
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r3, #0
	bl sub_02009298
	lsl r1, r6, #2
	add r2, r5, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	str r0, [r2, r1]
	add r6, r6, #1
_02247142:
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_0224783C
	lsl r1, r6, #2
	add r2, r5, r1
	mov r1, #0x6f
	lsl r1, r1, #2
	str r0, [r2, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x18
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0xb
	mov r3, #0
	bl sub_02009358
	mov r1, #0x72
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _02247194
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x24
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0xe
	mov r3, #0
	bl sub_02009358
	b _022471AC
_02247194:
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x24
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0x11
	mov r3, #0
	bl sub_02009358
_022471AC:
	mov r1, #0x73
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #3
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	mov r2, #6
	mov r3, #0
	bl sub_02009358
	mov r1, #0x1d
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x28
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0xc
	bl sub_02009358
	mov r1, #0x76
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _02247214
	mov r0, #1
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x30
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0xf
	mov r3, #0
	bl sub_02009358
	b _0224722E
_02247214:
	mov r0, #1
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0x30
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	add r1, r4, #0
	mov r2, #0x12
	mov r3, #0
	bl sub_02009358
_0224722E:
	mov r1, #0x77
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r1, #0x7d
	lsl r1, r1, #2
	ldr r0, [r5, #0x5c]
	add r1, r5, r1
	mov r2, #4
	bl ov06_0224778C
	mov r1, #0x83
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0x18
	add r0, r5, r1
	mov r1, #4
	bl ov06_022477D4
	mov r1, #0x21
	lsl r1, r1, #4
	str r0, [r5, r1]
	add sp, #0x10
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0224725C
ov06_0224725C: ; 0x0224725C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r7, #0x6b
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02247268:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _02247272
	bl sub_02009C0C
_02247272:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02247268
	mov r7, #0x6f
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_02247282:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _0224728C
	bl sub_02009E04
_0224728C:
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #3
	blt _02247282
	mov r7, #0x72
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_0224729C:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _022472A6
	bl sub_02009474
_022472A6:
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #4
	blt _0224729C
	mov r7, #0x76
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_022472B6:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _022472C0
	bl sub_02009474
_022472C0:
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #2
	blt _022472B6
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl sub_02008E2C
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl sub_02008E2C
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl sub_02008E2C
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl sub_02008E2C
	ldr r0, [r6, #0x70]
	bl sub_0201FDB4
	ldr r0, [r6, #0x70]
	bl sub_0201FD58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02247300
ov06_02247300: ; 0x02247300
	push {r3, lr}
	ldr r0, [r0, #0x70]
	cmp r0, #0
	beq _0224730C
	bl sub_0201FDEC
_0224730C:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02247310
ov06_02247310: ; 0x02247310
	push {r4, r5, r6, lr}
	sub sp, #0x70
	add r5, r0, #0
	ldr r0, [sp, #0x84]
	add r4, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	cmp r0, #4
	bne _02247358
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	mov r6, #0x67
	ldr r3, [sp, #0x88]
	str r0, [sp, #0xc]
	lsl r6, r6, #2
	str r3, [sp, #0x10]
	ldr r3, [r5, r6]
	str r3, [sp, #0x14]
	add r3, r6, #4
	ldr r3, [r5, r3]
	add r6, #8
	str r3, [sp, #0x18]
	ldr r3, [r5, r6]
	str r3, [sp, #0x1c]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r3, [sp, #0x80]
	add r0, sp, #0x4c
	bl sub_02008AA4
	b _02247392
_02247358:
	str r0, [sp]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0
	ldr r0, [sp, #0x88]
	str r3, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r6, [r5, r0]
	str r6, [sp, #0x14]
	add r6, r0, #4
	ldr r6, [r5, r6]
	str r6, [sp, #0x18]
	add r6, r0, #0
	add r6, #8
	ldr r6, [r5, r6]
	add r0, #0xc
	str r6, [sp, #0x1c]
	ldr r0, [r5, r0]
	str r0, [sp, #0x20]
	str r3, [sp, #0x24]
	str r3, [sp, #0x28]
	ldr r3, [sp, #0x80]
	add r0, sp, #0x4c
	bl sub_02008AA4
_02247392:
	ldr r0, [r5, #0x70]
	add r2, sp, #0x34
	str r0, [sp, #0x2c]
	add r0, sp, #0x4c
	str r0, [sp, #0x30]
	ldmia r4!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4]
	str r0, [r2]
	ldr r0, [sp, #0x8c]
	str r0, [sp, #0x40]
	mov r0, #1
	str r0, [sp, #0x44]
	mov r0, #4
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	bl sub_0201FF84
	add r4, r0, #0
	bne _022473BE
	bl GF_AssertFail
_022473BE:
	add r0, r4, #0
	add sp, #0x70
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_022473C4
ov06_022473C4: ; 0x022473C4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r5, #1
	add r4, r3, #0
	str r5, [sp]
	mov r3, #0
	str r3, [sp, #4]
	str r3, [sp, #8]
	str r2, [sp, #0xc]
	add r2, r5, #0
	bl ov06_02247310
	add r1, r4, #0
	add r5, r0, #0
	bl sub_02020130
	add r0, r5, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022473EC
ov06_022473EC: ; 0x022473EC
	push {r4, lr}
	sub sp, #0x10
	ldr r2, [r0, #0xc]
	mov r3, #0
	cmp r2, #1
	bne _022473FA
	mov r3, #1
_022473FA:
	mov r2, #2
	str r2, [sp]
	mov r4, #1
	str r4, [sp, #4]
	mov r4, #0
	str r4, [sp, #8]
	mov r4, #0x83
	str r4, [sp, #0xc]
	bl ov06_02247310
	add r4, r0, #0
	mov r1, #0
	bl sub_020200A0
	add r0, r4, #0
	mov r1, #6
	bl sub_02020130
	add r0, r4, #0
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start ov06_02247424
ov06_02247424: ; 0x02247424
	push {r4, lr}
	mov r1, #1
	add r4, r0, #0
	bl sub_020200BC
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl sub_020200D8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224743C
ov06_0224743C: ; 0x0224743C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r4, r0, #0
	add r0, sp, #0x1c
	mov r7, #0
	str r7, [r0]
	str r7, [r0, #4]
	add r6, r2, #0
	ldr r5, _022474A0 ; =0x02251430
	add r3, r1, #0
	str r7, [r0, #8]
	ldmia r5!, {r0, r1}
	add r2, sp, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	add r1, r3, #0
	str r0, [r2]
	str r7, [sp]
	sub r0, r7, #1
	str r0, [sp, #4]
	str r7, [sp, #8]
	add r0, r4, #0
	add r2, r7, #0
	add r3, r7, #0
	str r6, [sp, #0xc]
	bl ov06_02247310
	add r4, r0, #0
	mov r1, #2
	bl sub_020200EC
	add r0, r4, #0
	add r1, sp, #0x1c
	bl sub_02020054
	add r0, r4, #0
	add r1, sp, #0x10
	bl sub_02020064
	add r0, r7, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	add r0, r4, #0
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022474A0: .word ov06_02251430

	thumb_func_start ov06_022474A4
ov06_022474A4: ; 0x022474A4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl ov06_0224700C
	add r6, r0, #0
	mov r0, #0x6b
	mov r5, #0
	add r2, r4, #0
	lsl r0, r0, #2
_022474B8:
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _022474E4
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r6, #0
	mov r2, #7
	bl sub_020091E0
	lsl r1, r5, #2
	add r2, r4, r1
	mov r1, #0x6b
	lsl r1, r1, #2
	str r0, [r2, r1]
	b _022474EC
_022474E4:
	add r5, r5, #1
	add r2, r2, #4
	cmp r5, #4
	blt _022474B8
_022474EC:
	cmp r5, #4
	blt _022474F4
	bl GF_AssertFail
_022474F4:
	mov r0, #0x72
	mov r5, #0
	add r2, r4, #0
	lsl r0, r0, #2
_022474FC:
	ldr r1, [r2, r0]
	cmp r1, #0
	bne _02247528
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r6, #0
	mov r2, #8
	bl sub_02009358
	lsl r1, r5, #2
	add r2, r4, r1
	mov r1, #0x72
	lsl r1, r1, #2
	str r0, [r2, r1]
	b _02247530
_02247528:
	add r5, r5, #1
	add r2, r2, #4
	cmp r5, #4
	blt _022474FC
_02247530:
	cmp r5, #4
	blt _02247538
	bl GF_AssertFail
_02247538:
	add r0, r6, #0
	bl NARC_Delete
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02247544
ov06_02247544: ; 0x02247544
	push {r3, r4, r5, lr}
	add r5, r2, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	add r1, r5, #0
	add r4, r0, #0
	bl NNS_G2dGetUnpackedPaletteData
	ldr r1, [r5]
	mov r0, #3
	ldr r1, [r1, #0xc]
	mov r2, #0x20
	lsl r3, r0, #7
	bl BG_LoadPlttData
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224756C
ov06_0224756C: ; 0x0224756C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	add r4, r3, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	add r1, r4, #0
	add r6, r0, #0
	bl NNS_G2dGetUnpackedCharacterData
	ldr r3, [r4]
	mov r0, #0
	str r0, [sp]
	ldr r2, [r3, #0x14]
	ldr r3, [r3, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl BG_LoadCharTilesData
	add r0, r6, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_022475A4
ov06_022475A4: ; 0x022475A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r2, #0
	add r6, r1, #0
	mov r2, #0
	add r4, r3, #0
	mov r1, #3
	add r3, r2, #0
	add r5, r0, #0
	bl BgSetPosTextAndCommit
	mov r1, #3
	add r0, r5, #0
	add r2, r1, #0
	mov r3, #0
	bl BgSetPosTextAndCommit
	add r0, r6, #0
	add r1, r7, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	add r1, r4, #0
	add r6, r0, #0
	bl NNS_G2dGetUnpackedScreenData
	ldr r3, [r4]
	add r0, r5, #0
	add r2, r3, #0
	ldr r3, [r3, #8]
	mov r1, #3
	add r2, #0xc
	bl BG_LoadScreenTilemapData
	mov r0, #0x20
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0xc
	mov r2, #0
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #3
	add r3, r2, #0
	bl BgTilemapRectChangePalette
	add r0, r5, #0
	mov r1, #3
	bl BgCommitTilemapBufferToVram
	add r0, r6, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_02247610
ov06_02247610: ; 0x02247610
	ldr r3, _02247618 ; =BgClearTilemapBufferAndCommit
	mov r1, #3
	bx r3
	nop
_02247618: .word BgClearTilemapBufferAndCommit

	thumb_func_start ov06_0224761C
ov06_0224761C: ; 0x0224761C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224767C
	mov r0, #0
	str r0, [r4, #0x2c]
	add r0, r4, #0
	bl ov06_02247648
	add r0, r4, #0
	bl ov06_02247650
	add r0, r4, #0
	bl ov06_02247640
	mov r0, #1
	str r0, [r4, #0x2c]
	pop {r4, pc}

	thumb_func_start ov06_02247640
ov06_02247640: ; 0x02247640
	mov r1, #1
	str r1, [r0, #0x30]
	bx lr
	.align 2, 0

	thumb_func_start ov06_02247648
ov06_02247648: ; 0x02247648
	mov r1, #0
	str r1, [r0, #0x30]
	bx lr
	.align 2, 0

	thumb_func_start ov06_02247650
ov06_02247650: ; 0x02247650
	mov r1, #0x18
	str r1, [r0, #0x34]
	mov r1, #0
	str r1, [r0, #0x38]
	mov r1, #0x17
	str r1, [r0, #0x3c]
	mov r1, #1
	str r1, [r0, #0x40]
	bx lr
	.align 2, 0

	thumb_func_start ov06_02247664
ov06_02247664: ; 0x02247664
	mov r1, #0x17
	str r1, [r0, #0x3c]
	mov r1, #1
	str r1, [r0, #0x40]
	bx lr
	.align 2, 0

	thumb_func_start ov06_02247670
ov06_02247670: ; 0x02247670
	str r1, [r0, #0x44]
	str r3, [r0, #0x48]
	ldr r1, [sp]
	str r2, [r0, #0x4c]
	str r1, [r0, #0x50]
	bx lr

	thumb_func_start ov06_0224767C
ov06_0224767C: ; 0x0224767C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0224768E
	bl GF_AssertFail
_0224768E:
	ldr r0, _022476A0 ; =ov06_022476D4
	add r1, r4, #0
	mov r2, #0x81
	bl sub_0200CA60
	mov r1, #0x86
	lsl r1, r1, #2
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_022476A0: .word ov06_022476D4

	thumb_func_start ov06_022476A4
ov06_022476A4: ; 0x022476A4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _022476B6
	bl GF_AssertFail
_022476B6:
	mov r0, #0x86
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_0200CAB4
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _022476D0 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	pop {r4, pc}
	nop
_022476D0: .word 0xFFFF1FFF

	thumb_func_start ov06_022476D4
ov06_022476D4: ; 0x022476D4
	push {r3, r4, r5, r6}
	ldr r0, [r1, #0x2c]
	cmp r0, #0
	beq _0224776A
	mov r3, #1
	lsl r3, r3, #0x1a
	ldr r2, [r3]
	ldr r0, _02247770 ; =0xFFFF1FFF
	and r2, r0
	ldr r0, [r1, #0x30]
	lsl r0, r0, #0xd
	orr r0, r2
	str r0, [r3]
	add r3, #0x48
	ldrh r2, [r3]
	mov r0, #0x3f
	bic r2, r0
	ldr r0, [r1, #0x34]
	orr r2, r0
	ldr r0, [r1, #0x38]
	cmp r0, #0
	beq _02247704
	mov r0, #0x20
	orr r2, r0
_02247704:
	ldr r0, _02247774 ; =0x04000048
	strh r2, [r0]
	ldrh r2, [r0, #2]
	mov r0, #0x3f
	bic r2, r0
	ldr r0, [r1, #0x3c]
	orr r2, r0
	ldr r0, [r1, #0x40]
	cmp r0, #0
	beq _0224771C
	mov r0, #0x20
	orr r2, r0
_0224771C:
	ldr r5, _02247778 ; =0x0400004A
	strh r2, [r5]
	ldr r2, [r1, #0x50]
	ldr r6, [r1, #0x48]
	asr r0, r2, #0xb
	lsr r0, r0, #0x14
	add r0, r2, r0
	ldr r2, [r1, #0x4c]
	asr r4, r0, #0xc
	asr r0, r2, #0xb
	lsr r0, r0, #0x14
	add r0, r2, r0
	ldr r2, [r1, #0x44]
	asr r3, r0, #0xc
	asr r0, r2, #0xb
	lsr r0, r0, #0x14
	asr r1, r6, #0xb
	add r0, r2, r0
	lsr r1, r1, #0x14
	asr r0, r0, #0xc
	add r1, r6, r1
	lsl r2, r0, #8
	mov r0, #0xff
	asr r1, r1, #0xc
	lsl r0, r0, #8
	lsl r1, r1, #0x18
	and r2, r0
	lsr r1, r1, #0x18
	orr r2, r1
	add r1, r5, #0
	sub r1, #0xa
	strh r2, [r1]
	lsl r1, r3, #8
	and r1, r0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	orr r1, r0
	sub r0, r5, #6
	strh r1, [r0]
_0224776A:
	pop {r3, r4, r5, r6}
	bx lr
	nop
_02247770: .word 0xFFFF1FFF
_02247774: .word 0x04000048
_02247778: .word 0x0400004A

	thumb_func_start ov06_0224777C
ov06_0224777C: ; 0x0224777C
	ldr r3, _02247788 ; =sub_02068B68
	add r2, r0, #0
	add r0, r1, #0
	ldr r1, [r2, #0x5c]
	mov r2, #2
	bx r3
	.align 2, 0
_02247788: .word sub_02068B68

	thumb_func_start ov06_0224778C
ov06_0224778C: ; 0x0224778C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	mov r1, #0x32
	add r6, r0, #0
	mov r0, #4
	lsl r1, r1, #6
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _022477A8
	bl GF_AssertFail
_022477A8:
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	bl GetMonData
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldrh r0, [r5, #6]
	add r2, r7, #0
	add r3, r4, #0
	str r0, [sp, #0xc]
	ldrh r0, [r5]
	ldrh r1, [r5, #2]
	bl sub_02012560
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_022477D4
ov06_022477D4: ; 0x022477D4
	add r3, r0, #0
	add r2, r1, #0
	ldrh r0, [r3]
	ldrh r1, [r3, #4]
	ldr r3, _022477E0 ; =sub_02012470
	bx r3
	.align 2, 0
_022477E0: .word sub_02012470

	thumb_func_start ov06_022477E4
ov06_022477E4: ; 0x022477E4
	push {lr}
	sub sp, #0xc
	mov r2, #3
	str r2, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r2, #4
	str r2, [sp, #8]
	mov r2, #0x67
	lsl r2, r2, #2
	ldr r0, [r0, r2]
	mov r2, #5
	mov r3, #0
	bl sub_020091E0
	add sp, #0xc
	pop {pc}
	.align 2, 0

	thumb_func_start ov06_02247808
ov06_02247808: ; 0x02247808
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x67
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #3
	bl sub_020094F0
	bl sub_02009C5C
	mov r1, #1
	bl NNS_G2dGetImageLocation
	mov r1, #0x32
	add r5, r0, #0
	add r0, r4, #0
	lsl r1, r1, #6
	bl DC_FlushRange
	mov r2, #0x32
	add r0, r4, #0
	add r1, r5, #0
	lsl r2, r2, #6
	bl GX_LoadOBJ
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224783C
ov06_0224783C: ; 0x0224783C
	push {r3, lr}
	sub sp, #0x10
	mov r2, #2
	str r2, [sp]
	mov r2, #1
	str r2, [sp, #4]
	str r2, [sp, #8]
	mov r2, #4
	str r2, [sp, #0xc]
	mov r2, #0x1a
	lsl r2, r2, #4
	ldr r0, [r0, r2]
	mov r2, #3
	mov r3, #0
	bl sub_02009298
	add sp, #0x10
	pop {r3, pc}

	thumb_func_start ov06_02247860
ov06_02247860: ; 0x02247860
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x67
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #3
	bl sub_020094F0
	bl sub_02009C5C
	add r6, r0, #0
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #2
	bl sub_020094F0
	add r1, r6, #0
	bl sub_02009E54
	mov r1, #1
	bl NNS_G2dGetImagePaletteLocation
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0x20
	bl DC_FlushRange
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x20
	bl GX_LoadOBJPltt
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_022478A8
ov06_022478A8: ; 0x022478A8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #3
	bl sub_020094F0
	add r4, r0, #0
	bl sub_02009C0C
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl sub_02009490
	mov r1, #0x6b
	mov r0, #0
	add r3, r5, #0
	lsl r1, r1, #2
_022478D2:
	ldr r2, [r3, r1]
	cmp r2, r4
	bne _022478E6
	lsl r1, r0, #2
	add r2, r5, r1
	mov r1, #0x6b
	mov r3, #0
	lsl r1, r1, #2
	str r3, [r2, r1]
	b _022478EE
_022478E6:
	add r0, r0, #1
	add r3, r3, #4
	cmp r0, #4
	blt _022478D2
_022478EE:
	cmp r0, #4
	blt _022478F6
	bl GF_AssertFail
_022478F6:
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #2
	bl sub_020094F0
	add r4, r0, #0
	bl sub_02009E04
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl sub_02009490
	mov r1, #0x6f
	mov r0, #0
	add r3, r5, #0
	lsl r1, r1, #2
_0224791C:
	ldr r2, [r3, r1]
	cmp r2, r4
	bne _02247930
	lsl r1, r0, #2
	add r2, r5, r1
	mov r1, #0x6f
	mov r3, #0
	lsl r1, r1, #2
	str r3, [r2, r1]
	b _02247938
_02247930:
	add r0, r0, #1
	add r3, r3, #4
	cmp r0, #3
	blt _0224791C
_02247938:
	cmp r0, #3
	blt _02247940
	bl GF_AssertFail
_02247940:
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #3
	bl sub_020094F0
	add r4, r0, #0
	bl sub_02009474
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl sub_02009490
	mov r1, #0x72
	mov r0, #0
	add r3, r5, #0
	lsl r1, r1, #2
_02247966:
	ldr r2, [r3, r1]
	cmp r2, r4
	bne _0224797A
	lsl r1, r0, #2
	add r2, r5, r1
	mov r1, #0x72
	mov r3, #0
	lsl r1, r1, #2
	str r3, [r2, r1]
	b _02247982
_0224797A:
	add r0, r0, #1
	add r3, r3, #4
	cmp r0, #4
	blt _02247966
_02247982:
	cmp r0, #4
	blt _0224798A
	bl GF_AssertFail
_0224798A:
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224798C
ov06_0224798C: ; 0x0224798C
	push {r3, lr}
	sub sp, #0x10
	mov r2, #3
	str r2, [sp]
	sub r3, r2, #4
	str r3, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	mov r3, #0x81
	str r3, [sp, #0xc]
	mov r3, #2
	bl ov06_02247310
	add sp, #0x10
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_022479AC
ov06_022479AC: ; 0x022479AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	mov r0, #2
	ldr r4, _02247A14 ; =0x02251634
	add r6, r1, #0
	str r0, [r5, #0x14]
	mov r7, #0
_022479BC:
	ldr r0, [r4]
	add r1, sp, #0x1c
	str r0, [sp, #0x1c]
	ldr r0, [r4, #4]
	add r2, sp, #0x10
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp, #0x24]
	ldr r0, [r4, #8]
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #0xc]
	str r0, [sp, #8]
	ldr r0, [r4, #0x10]
	ldr r3, [sp, #8]
	str r0, [sp]
	str r0, [sp, #0xc]
	str r6, [sp, #4]
	add r0, r5, #0
	bl ov06_02247A18
	mov r0, #1
	ldr r1, [sp, #0x1c]
	lsl r0, r0, #0x14
	add r0, r1, r0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	ldr r3, [sp, #8]
	str r0, [sp]
	add r0, r5, #0
	add r1, sp, #0x1c
	add r2, sp, #0x10
	str r6, [sp, #4]
	bl ov06_02247A18
	add r7, r7, #1
	add r4, #0x14
	cmp r7, #0xd
	blt _022479BC
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02247A14: .word ov06_02251634

	thumb_func_start ov06_02247A18
ov06_02247A18: ; 0x02247A18
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, [sp, #0x34]
	str r3, [sp, #8]
	str r5, [sp, #0x10]
	add r4, r1, #0
	str r0, [sp, #0xc]
	ldmia r2!, {r0, r1}
	add r3, sp, #0x14
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	ldr r1, _02247A50 ; =0x022514E8
	str r0, [r3]
	add r0, sp, #8
	str r0, [sp]
	mov r0, #0x84
	str r0, [sp, #4]
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r3, [sp, #0x30]
	add r2, r4, #0
	bl sub_020644E4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	nop
_02247A50: .word ov06_022514E8

	thumb_func_start ov06_02247A54
ov06_02247A54: ; 0x02247A54
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0xc
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r5, #0
	bl sub_02064754
	str r0, [r4, #4]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x14]
	ldr r2, [r4, #0xc]
	ldr r3, [r4, #4]
	add r1, sp, #0
	bl ov06_022473C4
	mov r1, #0
	str r0, [r4, #8]
	bl sub_020200A0
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_02247A9C
ov06_02247A9C: ; 0x02247A9C
	ldr r3, _02247AA4 ; =sub_0201FFC8
	ldr r0, [r1, #8]
	bx r3
	nop
_02247AA4: .word sub_0201FFC8

	thumb_func_start ov06_02247AA8
ov06_02247AA8: ; 0x02247AA8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	add r5, r0, #0
	bl sub_0206477C
	ldr r1, [sp]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	lsr r2, r0, #0x1f
	lsl r1, r0, #0xb
	str r0, [sp]
	sub r1, r1, r2
	mov r0, #0xb
	ror r1, r0
	add r0, r2, r1
	str r0, [sp]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #8]
	add r1, sp, #0
	bl sub_02020044
	ldr r0, [r4, #0x10]
	cmp r0, #1
	bne _02247B22
	ldr r3, [r4, #0x14]
	ldr r0, [r3, #0x14]
	cmp r0, #2
	bne _02247B16
	ldr r2, [r3, #0x4c]
	ldr r0, [r3, #0x50]
	mov r3, #2
	ldr r6, [sp, #4]
	lsl r3, r3, #0xc
	sub r5, r6, r3
	mov r1, #0
	cmp r5, r2
	blt _02247B0C
	cmp r5, r0
	bgt _02247B0C
	add r3, r6, r3
	cmp r3, r2
	blt _02247B0C
	cmp r3, r0
	bgt _02247B0C
	mov r1, #1
_02247B0C:
	ldr r0, [r4, #8]
	bl sub_020200A0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_02247B16:
	cmp r0, #1
	bne _02247B22
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_020200A0
_02247B22:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02247B28
ov06_02247B28: ; 0x02247B28
	bx lr
	.align 2, 0

	thumb_func_start ov06_02247B2C
ov06_02247B2C: ; 0x02247B2C
	push {r4, lr}
	sub sp, #0x18
	add r2, sp, #0xc
	mov r3, #0
	add r4, r0, #0
	str r3, [r2]
	str r3, [r2, #4]
	str r3, [r2, #8]
	str r4, [sp, #8]
	add r0, sp, #8
	str r0, [sp]
	mov r0, #0x82
	str r0, [sp, #4]
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r1, _02247B5C ; =0x02251510
	bl sub_020644E4
	mov r1, #0x7b
	lsl r1, r1, #2
	str r0, [r4, r1]
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_02247B5C: .word ov06_02251510

	thumb_func_start ov06_02247B60
ov06_02247B60: ; 0x02247B60
	push {r3, lr}
	mov r1, #0x7b
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl sub_02064738
	ldrb r0, [r0, #2]
	pop {r3, pc}

	thumb_func_start ov06_02247B70
ov06_02247B70: ; 0x02247B70
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_02064738
	add r5, r0, #0
	ldr r0, [r5, #0x60]
	cmp r0, #0
	beq _02247B8A
	bl sub_02064520
_02247B8A:
	ldr r0, [r5, #0x64]
	cmp r0, #0
	beq _02247B94
	bl ov05_021F6240
_02247B94:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_02064520
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02247BA0
ov06_02247BA0: ; 0x02247BA0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	ldr r0, [r0]
	add r1, sp, #0
	str r0, [r4, #0x5c]
	add r0, r5, #0
	bl sub_0206477C
	mov r2, #0
	ldr r0, [r4, #0x5c]
	add r1, sp, #0
	add r3, r2, #0
	bl ov06_0224743C
	str r0, [r4, #0x58]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_02247BCC
ov06_02247BCC: ; 0x02247BCC
	ldr r3, _02247BD4 ; =sub_0201FFC8
	ldr r0, [r1, #0x58]
	bx r3
	nop
_02247BD4: .word sub_0201FFC8

	thumb_func_start ov06_02247BD8
ov06_02247BD8: ; 0x02247BD8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldrb r0, [r5]
	lsl r1, r0, #2
	ldr r0, _02247BF4 ; =0x02251460
	ldr r4, [r0, r1]
_02247BE4:
	ldrb r1, [r5, #1]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #1
	beq _02247BE4
	pop {r3, r4, r5, pc}
	.align 2, 0
_02247BF4: .word ov06_02251460

	thumb_func_start ov06_02247BF8
ov06_02247BF8: ; 0x02247BF8
	bx lr
	.align 2, 0

	thumb_func_start ov06_02247BFC
ov06_02247BFC: ; 0x02247BFC
	push {r3, lr}
	mov r1, #0
	strb r1, [r0, #2]
	ldr r0, [r0, #0x58]
	bl sub_020200A0
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov06_02247C0C
ov06_02247C0C: ; 0x02247C0C
	push {r4, r5, r6, lr}
	sub sp, #0x18
	ldr r4, _02247CAC ; =0x02251478
	add r2, r0, #0
	ldmia r4!, {r0, r1}
	add r3, sp, #0xc
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	ldr r4, _02247CB0 ; =0x02251424
	str r0, [r3]
	ldmia r4!, {r0, r1}
	add r3, sp, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	bl sub_02064738
	add r4, r0, #0
	mov r3, #1
	add r5, r4, #0
	strb r3, [r4]
	mov r2, #0
	strb r2, [r4, #1]
	strb r2, [r4, #2]
	add r6, sp, #0xc
	ldmia r6!, {r0, r1}
	add r5, #8
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r6, sp, #0
	str r0, [r5]
	str r2, [r4, #0x14]
	str r2, [r4, #0x18]
	mov r0, #0xf
	add r5, r4, #0
	str r2, [r4, #0x1c]
	lsl r0, r0, #0xe
	str r0, [r4, #0x38]
	ldmia r6!, {r0, r1}
	add r5, #0x2c
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r1, sp, #0xc
	str r0, [r5]
	lsl r0, r3, #9
	str r0, [r4, #0x50]
	mov r0, #0x2d
	lsl r0, r0, #0xe
	str r0, [r4, #0x40]
	str r2, [r4, #0x48]
	lsl r0, r3, #0xd
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x58]
	bl sub_02020044
	ldr r0, [r4, #0x58]
	add r1, sp, #0
	bl sub_02020064
	ldr r1, [r4, #0x38]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0x58]
	bl sub_02020088
	ldr r0, [r4, #0x58]
	mov r1, #1
	bl sub_020200A0
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.align 2, 0
_02247CAC: .word ov06_02251478
_02247CB0: .word ov06_02251424

	thumb_func_start ov06_02247CB4
ov06_02247CB4: ; 0x02247CB4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x4c]
	ldr r4, [r5, #0x58]
	add r0, r1, r0
	str r0, [r5, #0x48]
	mov r0, #1
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0x10
	cmp r1, r0
	bge _02247CD4
	lsr r0, r0, #2
	add r0, r1, r0
	str r0, [r5, #0x4c]
_02247CD4:
	ldr r0, _02247DB4 ; =0x0000013B
	bl Cos_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r2, r0, #0xc
	ldr r0, _02247DB8 ; =0x0000010E
	cmp r2, r0
	bge _02247D1E
	mov r0, #1
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [r5, #0x40]
_02247D1E:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [r5, #0x2c]
	cmp r1, r0
	ble _02247D30
	str r0, [r5, #0x2c]
_02247D30:
	ldr r1, [r5, #0x30]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0xc
	str r1, [r5, #0x30]
	cmp r1, r0
	ble _02247D42
	str r0, [r5, #0x30]
_02247D42:
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x2c
	bl sub_02020064
	mov r0, #6
	ldr r1, [r5, #0x38]
	lsl r0, r0, #0xc
	sub r1, r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	str r1, [r5, #0x38]
	asr r0, r0, #0xc
	bpl _02247D64
	mov r0, #0
	str r0, [r5, #0x38]
_02247D64:
	ldr r1, [r5, #0x38]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x14]
	add r0, r1, r0
	str r0, [sp]
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020044
	ldr r1, [sp, #4]
	ldr r0, _02247DBC ; =0xFFFC0000
	cmp r1, r0
	bge _02247DAE
	add r0, r4, #0
	mov r1, #0
	bl sub_020200A0
	mov r0, #2
	strb r0, [r5, #2]
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
_02247DAE:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02247DB4: .word 0x0000013B
_02247DB8: .word 0x0000010E
_02247DBC: .word 0xFFFC0000

	thumb_func_start ov06_02247DC0
ov06_02247DC0: ; 0x02247DC0
	mov r0, #0
	bx lr

	thumb_func_start ov06_02247DC4
ov06_02247DC4: ; 0x02247DC4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r3, _02247F1C ; =0x0225140C
	add r5, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0x24
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r3, _02247F20 ; =0x02251400
	str r0, [r2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x18
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02064738
	add r4, r0, #0
	mov r0, #2
	add r2, r4, #0
	strb r0, [r4]
	mov r6, #0
	strb r6, [r4, #1]
	mov r7, #1
	strb r7, [r4, #2]
	str r6, [r4, #4]
	add r3, sp, #0x24
	ldmia r3!, {r0, r1}
	add r2, #8
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, sp, #0x18
	str r0, [r2]
	str r6, [r4, #0x14]
	str r6, [r4, #0x18]
	str r6, [r4, #0x1c]
	ldr r6, _02247F24 ; =0x0013B000
	add r2, r4, #0
	str r6, [r4, #0x38]
	ldmia r3!, {r0, r1}
	add r2, #0x2c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r7, #0
	add r0, #0xff
	str r0, [r4, #0x50]
	mov r0, #0xe1
	lsl r0, r0, #0xc
	str r0, [r4, #0x40]
	mov r0, #3
	lsl r0, r0, #0x12
	str r0, [r4, #0x48]
	lsl r0, r7, #0x11
	str r0, [r4, #0x4c]
	lsr r0, r6, #0xc
	bl Cos_Wrap
	ldr r2, [r4, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, [r4, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r4, #0x18]
	ldr r1, [r4, #8]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [sp, #0x24]
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	str r0, [sp, #0x28]
	ldr r0, [r4, #0x58]
	add r1, sp, #0x24
	bl sub_02020044
	ldr r0, [r4, #0x58]
	add r1, sp, #0x18
	bl sub_02020064
	ldr r1, [r4, #0x38]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl MathUtil_0201B9A0
	add r1, r0, #0
	ldr r0, [r4, #0x58]
	bl sub_02020088
	ldr r0, [r4, #0x58]
	add r1, r7, #0
	bl sub_020200A0
	mov r1, #0x1e
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl ov06_0224823C
	str r0, [r4, #0x60]
	add r0, r7, #0
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x60]
	mov r1, #4
	bl ov05_021F61F4
	ldr r2, _02247F28 ; =0xFFF88000
	add r1, r7, #0
	mov r3, #0xc
	str r0, [r4, #0x64]
	bl ov05_021F6254
	add r1, sp, #0xc
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	ldr r3, _02247F2C ; =0x02251484
	str r0, [r1, #8]
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	mov r0, #0x79
	ldr r1, [r4, #0x5c]
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	mov r1, #2
	add r0, r4, #0
	bl sub_020200EC
	add r0, r4, #0
	add r1, sp, #0xc
	bl sub_02020054
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020064
	mov r0, #0
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02247F1C: .word ov06_0225140C
_02247F20: .word ov06_02251400
_02247F24: .word 0x0013B000
_02247F28: .word 0xFFF88000
_02247F2C: .word ov06_02251484

	thumb_func_start ov06_02247F30
ov06_02247F30: ; 0x02247F30
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x4c]
	ldr r4, [r5, #0x58]
	sub r0, r1, r0
	str r0, [r5, #0x48]
	bpl _02247F46
	mov r0, #0
	str r0, [r5, #0x48]
_02247F46:
	mov r0, #2
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0xa
	cmp r1, r0
	ble _02247F58
	mov r0, #6
	lsl r0, r0, #0xa
	sub r0, r1, r0
	str r0, [r5, #0x4c]
_02247F58:
	mov r0, #1
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0xc
	cmp r1, r0
	bge _02247F64
	str r0, [r5, #0x4c]
_02247F64:
	ldr r0, _02248098 ; =0x0000013B
	bl Cos_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x14]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Sin_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r2, r0, #0xc
	ldr r0, _0224809C ; =0x0000010E
	cmp r2, r0
	bge _02247FAE
	mov r0, #1
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [r5, #0x40]
_02247FAE:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #6
	lsl r0, r0, #0xa
	str r1, [r5, #0x2c]
	cmp r1, r0
	ble _02247FC0
	str r0, [r5, #0x2c]
_02247FC0:
	ldr r1, [r5, #0x30]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #6
	lsl r0, r0, #0xa
	str r1, [r5, #0x30]
	cmp r1, r0
	ble _02247FD2
	str r0, [r5, #0x30]
_02247FD2:
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x2c
	bl sub_02020064
	mov r0, #2
	ldr r1, [r5, #0x38]
	lsl r0, r0, #0xe
	add r1, r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	str r1, [r5, #0x38]
	asr r1, r0, #0xc
	mov r0, #0x5a
	lsl r0, r0, #2
	cmp r1, r0
	ble _02247FFA
	lsl r0, r0, #0xc
	str r0, [r5, #0x38]
_02247FFA:
	ldr r1, [r5, #0x38]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl MathUtil_0201B9A0
	add r1, r0, #0
	add r0, r4, #0
	bl sub_02020088
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x14]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r1, r0
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r1, sp, #0xc
	bl sub_02020044
	ldr r0, [r5, #0x48]
	cmp r0, #0
	bne _0224803C
	mov r0, #0
	str r0, [r5, #4]
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
	b _02248042
_0224803C:
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
_02248042:
	ldr r0, [r5, #4]
	cmp r0, #0xc
	bne _0224804E
	ldr r0, [r5, #0x60]
	bl ov06_02248270
_0224804E:
	mov r0, #0x79
	ldr r1, [r5, #0x5c]
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	add r0, r4, #0
	bl sub_02020120
	add r3, r0, #0
	ldmia r3!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [sp]
	mov r0, #5
	add r1, #0x80
	lsl r0, r0, #0xa
	str r1, [sp]
	cmp r1, r0
	ble _02248078
	str r0, [sp]
_02248078:
	ldr r1, [sp, #4]
	mov r0, #5
	add r1, #0x80
	lsl r0, r0, #0xa
	str r1, [sp, #4]
	cmp r1, r0
	ble _02248088
	str r0, [sp, #4]
_02248088:
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020064
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_02248098: .word 0x0000013B
_0224809C: .word 0x0000010E

	thumb_func_start ov06_022480A0
ov06_022480A0: ; 0x022480A0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x79
	ldr r1, [r5, #0x5c]
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	mov r1, #3
	add r0, r4, #0
	bl sub_02020130
	add r0, r4, #0
	bl sub_0202011C
	ldr r4, [r0, #4]
	ldr r0, [r5, #0x58]
	bl sub_0202011C
	ldr r0, [r0, #4]
	sub r0, r4, r0
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	bl ov06_02248264
	ldr r0, [r5, #0x64]
	mov r1, #2
	mov r2, #0
	mov r3, #0xc
	bl ov05_021F6254
	mov r1, #1
	lsl r1, r1, #8
	str r1, [r5, #0x50]
	lsl r0, r1, #0xb
	str r0, [r5, #0x40]
	mov r0, #0
	str r0, [r5, #0x48]
	lsl r0, r1, #3
	str r0, [r5, #0x4c]
	mov r0, #3
	strb r0, [r5, #2]
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022480FC
ov06_022480FC: ; 0x022480FC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x4c]
	ldr r4, [r5, #0x58]
	add r0, r1, r0
	str r0, [r5, #0x48]
	mov r0, #1
	ldr r1, [r5, #0x4c]
	lsl r0, r0, #0xc
	add r2, r1, r0
	lsl r1, r0, #4
	str r2, [r5, #0x4c]
	cmp r2, r1
	ble _02248120
	lsl r0, r0, #4
	str r0, [r5, #0x4c]
_02248120:
	ldr r1, [r5, #0x40]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	lsl r0, r0, #4
	lsr r0, r0, #0x10
	bl Cos_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x14]
	mov r0, #0x80
	bl Sin_Wrap
	ldr r2, [r5, #0x48]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	mul r0, r1
	str r0, [r5, #0x18]
	mov r0, #0x87
	ldr r1, [r5, #0x40]
	lsl r0, r0, #0xc
	cmp r1, r0
	bge _02248164
	mov r0, #1
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r5, #0x40]
_02248164:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #2
	lsl r0, r0, #0xc
	str r1, [r5, #0x2c]
	cmp r1, r0
	ble _02248176
	str r0, [r5, #0x2c]
_02248176:
	ldr r1, [r5, #0x30]
	ldr r0, [r5, #0x50]
	add r1, r1, r0
	mov r0, #2
	lsl r0, r0, #0xc
	str r1, [r5, #0x30]
	cmp r1, r0
	ble _02248188
	str r0, [r5, #0x30]
_02248188:
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x2c
	bl sub_02020064
	ldr r1, [r5, #8]
	ldr r0, [r5, #0x14]
	add r0, r1, r0
	str r0, [sp, #0x18]
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x18]
	add r0, r1, r0
	str r0, [sp, #0x1c]
	add r0, r4, #0
	add r1, sp, #0x18
	bl sub_02020044
	mov r0, #0x79
	ldr r1, [r5, #0x5c]
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	add r0, r4, #0
	bl sub_02020120
	add r2, sp, #0xc
	add r3, sp, #0x18
	add r6, r0, #0
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldmia r6!, {r0, r1}
	add r2, sp, #0
	stmia r2!, {r0, r1}
	ldr r0, [r6]
	str r0, [r2]
	mov r0, #1
	ldr r1, [r5, #0x54]
	lsl r0, r0, #0xc
	sub r1, r1, r0
	str r1, [r5, #0x54]
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r1, r7, #0
	bl sub_02020044
	mov r0, #1
	ldr r1, [sp]
	lsl r0, r0, #8
	add r2, r1, r0
	lsl r1, r0, #5
	str r2, [sp]
	cmp r2, r1
	ble _022481FE
	lsl r0, r0, #5
	str r0, [sp]
_022481FE:
	mov r0, #1
	ldr r1, [sp, #4]
	lsl r0, r0, #8
	add r2, r1, r0
	lsl r1, r0, #5
	str r2, [sp, #4]
	cmp r2, r1
	ble _02248212
	lsl r0, r0, #5
	str r0, [sp, #4]
_02248212:
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02020064
	ldr r1, [sp, #0x1c]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	cmp r0, #0xf0
	blt _02248232
	mov r0, #2
	strb r0, [r5, #2]
	ldrb r0, [r5, #1]
	add r0, r0, #1
	strb r0, [r5, #1]
_02248232:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_02248238
ov06_02248238: ; 0x02248238
	mov r0, #0
	bx lr

	thumb_func_start ov06_0224823C
ov06_0224823C: ; 0x0224823C
	push {lr}
	sub sp, #0x1c
	add r2, sp, #0x10
	mov r3, #0
	str r3, [r2]
	str r3, [r2, #4]
	str r1, [sp, #0xc]
	str r3, [r2, #8]
	add r1, sp, #8
	str r1, [sp]
	mov r1, #0x81
	str r1, [sp, #4]
	ldr r1, _02248260 ; =0x022514D4
	bl sub_020644E4
	add sp, #0x1c
	pop {pc}
	nop
_02248260: .word ov06_022514D4

	thumb_func_start ov06_02248264
ov06_02248264: ; 0x02248264
	push {r3, lr}
	bl sub_02064738
	mov r1, #0
	str r1, [r0]
	pop {r3, pc}

	thumb_func_start ov06_02248270
ov06_02248270: ; 0x02248270
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl sub_02064738
	add r4, r0, #0
	mov r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #4]
	str r0, [r4, #0xc]
	str r0, [r4, #8]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x20]
	bl sub_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	add r0, r5, #0
	bl sub_0206476C
	ldr r0, [r4, #0x20]
	mov r1, #5
	bl sub_02020130
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_022482B8
ov06_022482B8: ; 0x022482B8
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl sub_02064738
	add r4, r0, #0
	mov r0, #2
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #4]
	str r0, [r4, #0xc]
	str r0, [r4, #8]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x20]
	add r1, sp, #0
	bl ov06_02245EAC
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #0x20]
	mov r1, #4
	bl sub_02020130
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022482F4
ov06_022482F4: ; 0x022482F4
	push {r4, lr}
	add r4, r1, #0
	bl sub_0206475C
	ldr r1, [r0]
	str r1, [r4, #0x1c]
	ldr r0, [r0, #4]
	str r0, [r4, #0x20]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov06_02248308
ov06_02248308: ; 0x02248308
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _0224834C
	ldr r1, [r4, #0xc]
	lsl r2, r1, #2
	ldr r1, _02248350 ; =0x02251570
	ldr r1, [r1, r2]
	str r1, [r4, #0x14]
	add r1, sp, #0
	bl sub_0206477C
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4, #0x20]
	add r1, sp, #0
	bl sub_02020044
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0xc
	blt _0224834C
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_0224834C:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02248350: .word ov06_02251570

	thumb_func_start ov06_02248354
ov06_02248354: ; 0x02248354
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _02248398
	ldr r1, [r4, #0xc]
	lsl r2, r1, #2
	ldr r1, _0224839C ; =0x022514C4
	ldr r1, [r1, r2]
	str r1, [r4, #0x14]
	add r1, sp, #0
	bl sub_0206477C
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r0, [r4, #0x20]
	add r1, sp, #0
	bl sub_02020044
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #4
	blt _02248398
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #1
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_02248398:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0224839C: .word ov06_022514C4

	thumb_func_start ov06_022483A0
ov06_022483A0: ; 0x022483A0
	push {r3, lr}
	ldr r2, [r1]
	cmp r2, #1
	beq _022483AE
	cmp r2, #2
	beq _022483B4
	pop {r3, pc}
_022483AE:
	bl ov06_02248308
	pop {r3, pc}
_022483B4:
	bl ov06_02248354
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_022483BC
ov06_022483BC: ; 0x022483BC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x5f
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #2
	bl ov06_02248634
	add r1, r0, #0
	str r4, [r1, #0xc]
	ldr r0, _022483DC ; =ov06_02248400
	mov r2, #0x85
	str r5, [r1, #0x14]
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	.align 2, 0
_022483DC: .word ov06_02248400

	thumb_func_start ov06_022483E0
ov06_022483E0: ; 0x022483E0
	push {r3, lr}
	bl sub_0201B6C8
	ldr r0, [r0, #4]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_022483EC
ov06_022483EC: ; 0x022483EC
	push {r4, lr}
	add r4, r0, #0
	bl sub_0201B6C8
	bl FreeToHeap
	add r0, r4, #0
	bl sub_0200CAB4
	pop {r4, pc}

	thumb_func_start ov06_02248400
ov06_02248400: ; 0x02248400
	push {r3, r4, r5, lr}
	ldr r4, _02248434 ; =0x02251538
	add r5, r1, #0
_02248406:
	ldr r1, [r5]
	add r0, r5, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	blx r1
	cmp r0, #1
	beq _02248406
	ldr r0, [r5, #0x10]
	cmp r0, #0
	beq _02248432
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02248428
	bl sub_02064584
_02248428:
	ldr r0, [r5, #0x20]
	cmp r0, #0
	beq _02248432
	bl sub_0201FDEC
_02248432:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02248434: .word ov06_02251538

	thumb_func_start ov06_02248438
ov06_02248438: ; 0x02248438
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl ov06_02246658
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02248450
ov06_02248450: ; 0x02248450
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x20
	bl sub_020643C0
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r2, #2
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	add r0, r5, #0
	add r0, #0x18
	mov r1, #0x20
	add r3, r2, #0
	str r2, [sp, #0x14]
	bl ov06_0224593C
	bl ov06_02246604
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #7
	mov r3, #0
	bl ov06_02245B94
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #3
	mov r3, #0
	bl ov06_02245C6C
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov06_02245D44
	add r0, r5, #0
	add r0, #0x18
	mov r1, #0
	bl ov06_02245C04
	add r0, r5, #0
	add r0, #0x18
	mov r1, #0
	bl ov06_02245CDC
	add r0, r5, #0
	add r0, #0x18
	mov r1, #0
	bl ov06_02245C38
	add r0, r5, #0
	add r0, #0x18
	mov r1, #0
	bl ov06_02245D10
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _02248522
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #0xd
	mov r3, #2
	bl ov06_02245B94
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #0xe
	mov r3, #2
	bl ov06_02245D44
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #0xf
	mov r3, #1
	bl ov06_02245DB4
	add r0, r5, #0
	add r0, #0x18
	mov r1, #2
	bl ov06_02245C04
	add r0, r5, #0
	add r0, #0x18
	mov r1, #2
	bl ov06_02245C38
	b _02248582
_02248522:
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #0x10
	mov r3, #2
	bl ov06_02245B94
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #4
	mov r3, #1
	bl ov06_02245C6C
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #0x11
	mov r3, #2
	bl ov06_02245D44
	add r0, r5, #0
	add r0, #0x18
	add r1, r4, #0
	mov r2, #0x12
	mov r3, #1
	bl ov06_02245DB4
	add r0, r5, #0
	add r0, #0x18
	mov r1, #2
	bl ov06_02245C04
	add r0, r5, #0
	add r0, #0x18
	mov r1, #1
	bl ov06_02245CDC
	add r0, r5, #0
	add r0, #0x18
	mov r1, #2
	bl ov06_02245C38
	add r0, r5, #0
	add r0, #0x18
	mov r1, #1
	bl ov06_02245D10
_02248582:
	add r0, r4, #0
	bl NARC_Delete
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02248594
ov06_02248594: ; 0x02248594
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0xc]
	add r0, #0x18
	bl ov06_02245F2C
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl sub_020200A0
	mov r3, #0x17
	lsl r3, r3, #4
	ldr r1, [r4, r3]
	sub r3, r3, #4
	add r2, r4, #0
	ldr r0, [r4, #0x14]
	ldr r3, [r4, r3]
	add r2, #0x18
	bl ov06_02245F6C
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl ov06_02246034
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	str r0, [r4, #0x10]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov06_022485DC
ov06_022485DC: ; 0x022485DC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov06_02245FA0
	cmp r0, #2
	beq _022485F2
	mov r0, #0
	pop {r4, pc}
_022485F2:
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov06_02245FD0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02248608
ov06_02248608: ; 0x02248608
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl sub_020643F0
	add r0, r4, #0
	add r0, #0x18
	bl ov06_02245A80
	mov r0, #0
	str r0, [r4, #0x10]
	mov r1, #1
	str r1, [r4, #4]
	ldr r1, [r4]
	add r1, r1, #1
	str r1, [r4]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02248630
ov06_02248630: ; 0x02248630
	mov r0, #0
	bx lr

	thumb_func_start ov06_02248634
ov06_02248634: ; 0x02248634
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bne _02248644
	bl GF_AssertFail
_02248644:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_02248654
ov06_02248654: ; 0x02248654
	push {r3, r4, r5, lr}
	ldr r0, [r0, #0x60]
	add r4, r1, #0
	ldr r0, [r0, #0x38]
	bl PlayerAvatar_GetMapObject
	add r5, r0, #0
	bl sub_02058914
	add r0, r5, #0
	add r1, r4, #0
	bl MapObject_SetVisible
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02248670
ov06_02248670: ; 0x02248670
	push {r4, lr}
	add r4, r1, #0
	bl sub_0206475C
	ldr r1, [r0]
	ldr r0, [r0, #4]
	str r1, [r4]
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov06_02248684
ov06_02248684: ; 0x02248684
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r0, [r4]
	bl sub_0202011C
	ldr r1, [r4, #4]
	ldr r0, [r0, #4]
	ldr r5, [r1, #0x4c]
	ldr r3, [r1, #0x50]
	ldr r1, [r1, #0x1c]
	cmp r1, #0
	bne _022486C0
	mov r1, #2
	lsl r1, r1, #0xe
	sub r2, r0, r1
	cmp r2, r5
	blt _022486B6
	add r0, r0, r1
	cmp r0, r3
	bgt _022486B6
	ldr r0, [r4]
	mov r1, #1
	bl sub_020200A0
	pop {r3, r4, r5, pc}
_022486B6:
	ldr r0, [r4]
	mov r1, #0
	bl sub_020200A0
	pop {r3, r4, r5, pc}
_022486C0:
	ldr r0, [r4]
	mov r1, #1
	bl sub_020200A0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022486CC
ov06_022486CC: ; 0x022486CC
	push {r3, r4, lr}
	sub sp, #0x1c
	add r2, sp, #0x10
	mov r3, #0
	str r3, [r2]
	add r4, r0, #0
	str r3, [r2, #4]
	mov r0, #0x79
	str r3, [r2, #8]
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r0, r0, #4
	str r1, [sp, #8]
	str r4, [sp, #0xc]
	add r1, sp, #8
	str r1, [sp]
	mov r1, #0x86
	str r1, [sp, #4]
	ldr r0, [r4, r0]
	ldr r1, _02248704 ; =0x022514FC
	bl sub_020644E4
	mov r1, #0x1f
	lsl r1, r1, #4
	str r0, [r4, r1]
	add sp, #0x1c
	pop {r3, r4, pc}
	nop
_02248704: .word ov06_022514FC

	thumb_func_start ov06_02248708
ov06_02248708: ; 0x02248708
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02248722
	bl sub_02064520
	mov r0, #0x1f
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
_02248722:
	pop {r4, pc}

	thumb_func_start ov06_02248724
ov06_02248724: ; 0x02248724
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r1, #8]
	str r1, [sp]
	mov r1, #0
	bl Party_GetMonByIndex
	add r6, r0, #0
	ldr r0, [r5, #0xc]
	bl Save_Roamers_Get
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	add r1, r0, #0
	add r0, r7, #0
	bl ov06_02248810
	str r0, [sp, #4]
	cmp r0, #0
	beq _022487AC
	add r0, r6, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldr r0, [sp]
	ldr r0, [r0, #0x14]
	cmp r0, #1
	bne _0224877E
	cmp r4, #0
	beq _02248782
_0224877E:
	cmp r0, #4
	bne _0224878A
_02248782:
	add r0, sp, #4
	bl sub_0202AA90
	b _0224879E
_0224878A:
	ldr r0, [sp, #4]
	mov r1, #5
	add r2, r4, #0
	bl sub_0202AAFC
	ldr r0, [sp, #4]
	mov r1, #7
	add r2, r6, #0
	bl sub_0202AAFC
_0224879E:
	ldr r1, [r5, #0x1c]
	add r0, r7, #0
	ldr r1, [r1]
	bl ov06_022487D8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_022487AC:
	bl LCRandom
	mov r1, #0x29
	lsl r1, r1, #4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x64
	blo _022487C4
	bl GF_AssertFail
_022487C4:
	cmp r4, #0x1e
	bhs _022487D2
	ldr r1, [r5, #0x1c]
	add r0, r7, #0
	ldr r1, [r1]
	bl ov06_022487D8
_022487D2:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_022487D8
ov06_022487D8: ; 0x022487D8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
_022487E0:
	add r0, r5, #0
	add r1, r4, #0
	bl sub_0202AA74
	cmp r0, #0
	beq _02248804
	add r0, r5, #0
	add r1, r4, #0
	bl sub_0202AA40
	bl sub_0206043C
	cmp r6, r0
	bne _02248804
	add r0, r5, #0
	add r1, r4, #0
	bl sub_020603B0
_02248804:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _022487E0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02248810
ov06_02248810: ; 0x02248810
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
_02248818:
	add r0, r5, #0
	add r1, r4, #0
	bl sub_0202AA74
	cmp r0, #0
	beq _0224883C
	add r0, r5, #0
	add r1, r4, #0
	bl sub_0202AAA0
	mov r1, #4
	add r7, r0, #0
	bl sub_0202AAB8
	cmp r6, r0
	bne _0224883C
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224883C:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #3
	blo _02248818
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start NPCTradeApp_Init
NPCTradeApp_Init: ; 0x0224884C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x104
	add r6, r1, #0
	add r5, r0, #0
	cmp r6, #4
	blo _0224885C
	bl GF_AssertFail
_0224885C:
	add r0, r5, #0
	mov r1, #0x14
	bl AllocFromHeap
	add r4, r0, #0
	add r2, r4, #0
	mov r1, #0x14
	mov r0, #0
_0224886C:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _0224886C
	mov r2, #0
	str r2, [sp]
	mov r0, #0x73
	add r1, r6, #0
	add r3, r5, #0
	bl GfGfxLoader_LoadFromNarc
	str r0, [r4]
	str r5, [r4, #0x10]
	str r6, [r4, #0xc]
	add r0, r5, #0
	bl AllocMonZeroed
	str r0, [r4, #4]
	add r0, r5, #0
	bl PlayerProfile_New
	str r0, [r4, #8]
	bl PlayerProfile_Init
	add r0, r5, #0
	add r1, r6, #4
	bl GetInGameTradeMonOrPartnerName
	add r5, r0, #0
	add r1, sp, #4
	mov r2, #0x80
	bl CopyStringToU16Array
	add r0, r5, #0
	bl String_Delete
	ldr r0, [r4, #8]
	add r1, sp, #4
	bl CopyPlayerName
	ldr r1, [r4]
	ldr r0, [r4, #8]
	ldr r1, [r1, #0x40]
	bl PlayerProfile_SetTrainerGender
	add r0, r4, #0
	add sp, #0x104
	pop {r3, r4, r5, r6, pc}

	thumb_func_start NPCTradeApp_Delete
NPCTradeApp_Delete: ; 0x022488CC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FreeToHeap
	ldr r0, [r4, #8]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start NPCTradeApp_GetOfferedSpecies
NPCTradeApp_GetOfferedSpecies: ; 0x022488EC
	ldr r0, [r0]
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start NPCTradeApp_GetRequestedSpecies
NPCTradeApp_GetRequestedSpecies: ; 0x022488F4
	ldr r0, [r0]
	ldr r0, [r0, #0x4c]
	bx lr
	.align 2, 0

	thumb_func_start ov06_022488FC
ov06_022488FC: ; 0x022488FC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	add r6, r2, #0
	bl SaveArray_Party_Get
	ldr r2, [r4, #4]
	add r1, r6, #0
	bl ReplacePartySlotWithMon
	ldr r0, [r5, #0xc]
	ldr r1, [r4, #4]
	bl sub_0202C144
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0224891C
ov06_0224891C: ; 0x0224891C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	ldr r0, [r6, #0xc]
	add r7, r2, #0
	add r5, r1, #0
	add r4, r3, #0
	bl SaveArray_Party_Get
	add r1, r7, #0
	bl Party_GetMonByIndex
	mov r1, #0xa0
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	add r2, r0, #0
	ldr r0, [r5, #0x10]
	str r0, [sp]
	ldr r0, [r6, #0x1c]
	ldr r0, [r0]
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	ldr r1, [r5]
	ldr r3, [r5, #0xc]
	bl CreateInGameTradeMon
	ldr r1, [sp, #0x20]
	add r0, r7, #0
	bl CopyPokemonToPokemon
	ldr r0, [r5, #4]
	ldr r1, [sp, #0x24]
	bl CopyPokemonToPokemon
	ldr r0, [sp, #0x20]
	bl sub_020690E4
	str r0, [r4]
	ldr r0, [sp, #0x24]
	bl sub_020690E4
	str r0, [r4, #4]
	ldr r0, [r5, #8]
	str r0, [r4, #8]
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r0, [r6, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x14]
	add r0, r6, #0
	bl Script_GetTimeOfDay
	cmp r0, #1
	bhi _02248996
	mov r0, #0
	add sp, #8
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02248996:
	cmp r0, #2
	bne _022489A2
	mov r0, #1
	add sp, #8
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_022489A2:
	mov r0, #2
	str r0, [r4, #0xc]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start GetInGameTradeMonOrPartnerName
GetInGameTradeMonOrPartnerName: ; 0x022489AC
	push {r3, r4, r5, lr}
	ldr r2, _022489D0 ; =0x00000146
	add r3, r0, #0
	add r4, r1, #0
	mov r0, #0
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r5, r0, #0
	add r1, r4, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r5, #0
	bl DestroyMsgData
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022489D0: .word 0x00000146

	thumb_func_start CreateInGameTradeMon
CreateInGameTradeMon: ; 0x022489D4
	; void CreateInGameTradeMon(struct Pokemon * mon, struct InGameTrade * trade, u32 level, u32 name_idx, HeapID heapId)
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r3, #0
	mov r3, #1
	add r4, r1, #0
	str r3, [sp]
	ldr r1, [r4, #0x38]
	add r5, r0, #0
	str r1, [sp, #4]
	str r3, [sp, #8]
	ldr r1, [r4, #0x20]
	mov r3, #0x20
	str r1, [sp, #0xc]
	ldr r1, [r4]
	bl CreateMon
	ldr r0, [sp, #0x28]
	add r1, r6, #0
	bl GetInGameTradeMonOrPartnerName
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0x76
	add r2, r7, #0
	bl SetMonData
	add r0, r7, #0
	bl String_Delete
	mov r1, #1
	add r0, sp, #0x10
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0x4d
	add r2, sp, #0x10
	bl SetMonData
	add r0, r5, #0
	mov r1, #0x46
	add r2, r4, #4
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x47
	add r2, #8
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x48
	add r2, #0xc
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x49
	add r2, #0x10
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x4a
	add r2, #0x14
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x4b
	add r2, #0x18
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x13
	add r2, #0x24
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x14
	add r2, #0x28
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x15
	add r2, #0x2c
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x16
	add r2, #0x30
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x17
	add r2, #0x34
	bl SetMonData
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #6
	add r2, #0x3c
	bl SetMonData
	ldr r0, [sp, #0x28]
	add r1, r6, #4
	bl GetInGameTradeMonOrPartnerName
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0x90
	add r2, r6, #0
	bl SetMonData
	add r0, r6, #0
	bl String_Delete
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #0x9c
	add r2, #0x40
	bl SetMonData
	add r4, #0x48
	add r0, r5, #0
	mov r1, #0xc
	add r2, r4, #0
	bl SetMonData
	ldr r0, [sp, #0x2c]
	bl MapHeader_GetMapSec
	add r3, r0, #0
	ldr r0, [sp, #0x28]
	mov r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r2, #1
	bl sub_0208089C
	add r0, r5, #0
	bl CalcMonLevelAndStats
	add r0, r5, #0
	bl MonIsShiny
	cmp r0, #0
	beq _02248B08
	bl GF_AssertFail
_02248B08:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_02248B0C
ov06_02248B0C: ; 0x02248B0C
	ldr r3, _02248B14 ; =MI_CpuFill8
	mov r1, #0
	mov r2, #0x18
	bx r3
	.align 2, 0
_02248B14: .word MI_CpuFill8

	thumb_func_start ov06_02248B18
ov06_02248B18: ; 0x02248B18
	strb r1, [r0, #3]
	bx lr

	thumb_func_start ov06_02248B1C
ov06_02248B1C: ; 0x02248B1C
	strb r1, [r0, #2]
	bx lr

	thumb_func_start ov06_02248B20
ov06_02248B20: ; 0x02248B20
	strb r1, [r0, #1]
	bx lr

	thumb_func_start ov06_02248B24
ov06_02248B24: ; 0x02248B24
	ldr r3, _02248B2C ; =CopyU16StringArrayN
	add r0, r0, #4
	mov r2, #8
	bx r3
	.align 2, 0
_02248B2C: .word CopyU16StringArrayN

	thumb_func_start ov06_02248B30
ov06_02248B30: ; 0x02248B30
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl sub_0202B5C8
	strb r0, [r5]
	str r4, [r5, #0x14]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_02248B44
ov06_02248B44: ; 0x02248B44
	push {r3, lr}
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _02248B50
	bl sub_0202B5CC
_02248B50:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02248B54
ov06_02248B54: ; 0x02248B54
	ldrb r0, [r0, #3]
	bx lr

	thumb_func_start ov06_02248B58
ov06_02248B58: ; 0x02248B58
	ldrb r0, [r0, #2]
	bx lr

	thumb_func_start ov06_02248B5C
ov06_02248B5C: ; 0x02248B5C
	add r0, r0, #4
	bx lr

	thumb_func_start ov06_02248B60
ov06_02248B60: ; 0x02248B60
	ldr r3, _02248B68 ; =sub_0202B5D8
	ldr r0, [r0, #0x14]
	bx r3
	nop
_02248B68: .word sub_0202B5D8

	thumb_func_start ov06_02248B6C
ov06_02248B6C: ; 0x02248B6C
	ldrb r0, [r0]
	bx lr

	thumb_func_start ov06_02248B70
ov06_02248B70: ; 0x02248B70
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r0, #4
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	bl ov06_02248B0C
	add r0, r5, #0
	bl sub_0202B534
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B24
	add r0, r5, #0
	bl sub_0202B538
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B1C
	add r0, r5, #0
	bl sub_0202B53C
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B20
	add r0, r5, #0
	bl sub_0202B540
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B30
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_02248BC0
ov06_02248BC0: ; 0x02248BC0
	push {r4, r5, r6, lr}
	ldr r0, [r0, #0xc]
	add r6, r1, #0
	bl Save_PlayerData_GetProfileAddr
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	bl ov06_02248B0C
	add r0, r5, #0
	bl PlayerProfile_GetNamePtr
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B24
	add r0, r5, #0
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B18
	add r0, r4, #0
	mov r1, #2
	bl ov06_02248B1C
	add r0, r4, #0
	mov r1, #GAME_VERSION
	bl ov06_02248B20
	add r0, r6, #0
	bl sub_0202B544
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B30
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02248C18
ov06_02248C18: ; 0x02248C18
	push {r4, r5, r6, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0
	bl Save_PlayerData_GetProfileAddr
	add r6, r0, #0
	mov r0, #4
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	bl ov06_02248B0C
	add r0, r6, #0
	strb r5, [r4]
	bl PlayerProfile_GetNamePtr
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B24
	add r0, r6, #0
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0
	add r0, r4, #0
	bl ov06_02248B18
	add r0, r4, #0
	mov r1, #2
	bl ov06_02248B1C
	add r0, r4, #0
	mov r1, #GAME_VERSION
	bl ov06_02248B20
	mov r0, #0
	str r0, [r4, #0x14]
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_02248C68
ov06_02248C68: ; 0x02248C68
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	add r6, r2, #0
	bl Save_SafariZone_Get
	add r7, r0, #0
	cmp r4, #4
	bne _02248C86
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_02248C18
	pop {r3, r4, r5, r6, r7, pc}
_02248C86:
	add r0, r6, #0
	bl sub_0202B820
	cmp r0, #0
	bne _02248CA4
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	bl sub_0202B7F4
	add r1, r0, #0
	add r0, r5, #0
	bl ov06_02248B70
	pop {r3, r4, r5, r6, r7, pc}
_02248CA4:
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	bl sub_0202B7C8
	add r1, r0, #0
	add r0, r5, #0
	bl ov06_02248BC0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_02248CB8
ov06_02248CB8: ; 0x02248CB8
	ldr r3, _02248CBC ; =FreeToHeap
	bx r3
	.align 2, 0
_02248CBC: .word FreeToHeap

	thumb_func_start ov06_02248CC0
ov06_02248CC0: ; 0x02248CC0
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_SafariZone_Get
	mov r1, #1
	bl sub_0202B40C
	pop {r3, pc}

	thumb_func_start ov06_02248CD0
ov06_02248CD0: ; 0x02248CD0
	push {r4, lr}
	ldr r0, [r0, #0xc]
	bl Save_SafariZone_Get
	add r4, r0, #0
	bl sub_0202B410
	cmp r0, #1
	bne _02248CE6
	mov r0, #0
	pop {r4, pc}
_02248CE6:
	add r0, r4, #0
	bl sub_0202B458
	cmp r0, #0
	bne _02248CF4
	mov r0, #2
	pop {r4, pc}
_02248CF4:
	cmp r0, #4
	bne _02248CFC
	mov r0, #1
	pop {r4, pc}
_02248CFC:
	mov r0, #3
	pop {r4, pc}

	thumb_func_start ov06_02248D00
ov06_02248D00: ; 0x02248D00
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl Script_GetWeekday
	add r0, r0, #6
	mov r1, #7
	bl _s32_div_f
	add r0, r4, #0
	add r5, r1, #0
	bl Script_GetHour
	add r6, r0, #0
	add r0, r4, #0
	bl Script_GetMinute
	mov r1, #0xf
	bl _s32_div_f
	add r6, #0x13
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0x18
	bl _s32_div_f
	add r6, r1, #0
	lsl r6, r6, #2
	mov r3, #7
	add r4, r4, r6
	str r3, [sp]
	add r0, sp, #4
	mov r1, #0x7e
	mov r2, #0
	mul r3, r4
	bl ReadFromNarcMemberByIdPair
	add r0, sp, #4
	ldrb r4, [r0, r5]
	cmp r4, #0
	beq _02248D56
	cmp r4, #9
	blo _02248D5A
_02248D56:
	bl GF_AssertFail
_02248D5A:
	add r0, r4, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}

	thumb_func_start ov06_02248D60
ov06_02248D60: ; 0x02248D60
	push {r4, lr}
	sub sp, #8
	add r3, r0, #0
	sub r4, r3, #1
	lsl r3, r4, #3
	mov r2, #1
	add r0, sp, #4
	mov r1, #0x7e
	add r3, r4, r3
	str r2, [sp]
	bl ReadFromNarcMemberByIdPair
	add r0, sp, #4
	ldrb r0, [r0]
	cmp r0, #5
	blo _02248D84
	bl GF_AssertFail
_02248D84:
	add r0, sp, #4
	ldrb r0, [r0]
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov06_02248D8C
ov06_02248D8C: ; 0x02248D8C
	push {r3, r4, lr}
	sub sp, #4
	add r3, r0, #0
	sub r4, r3, #1
	lsl r3, r4, #3
	mov r0, #8
	add r3, r4, r3
	str r0, [sp]
	add r0, r1, #0
	mov r1, #0x7e
	mov r2, #1
	add r3, r3, #1
	bl ReadFromNarcMemberByIdPair
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start ov06_02248DAC
ov06_02248DAC: ; 0x02248DAC
	mov r0, #1
	bx lr

	thumb_func_start ov06_02248DB0
ov06_02248DB0: ; 0x02248DB0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r1, #0
	str r0, [sp]
	ldr r0, [r7, #0xc]
	str r2, [sp, #4]
	bl Save_SafariZone_Get
	ldr r0, [sp]
	add r1, sp, #8
	bl ov06_02248D8C
	ldr r0, [sp, #4]
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	mov r6, #0
	add r4, r6, #0
	add r5, sp, #8
_02248DD8:
	ldrb r2, [r5]
	cmp r2, #0
	beq _02248DFA
	ldr r1, [sp]
	add r0, r7, #0
	bl ov06_02248DAC
	cmp r0, #1
	bne _02248DF2
	ldrb r1, [r5]
	ldr r0, [sp, #4]
	strb r1, [r0, r4]
	add r4, r4, #1
_02248DF2:
	add r6, r6, #1
	add r5, r5, #1
	cmp r6, #8
	blt _02248DD8
_02248DFA:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02248E00
ov06_02248E00: ; 0x02248E00
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r1, #0
	add r0, sp, #0
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	mov r1, #0
	add r4, r1, #0
	add r2, sp, #0
_02248E16:
	ldrb r0, [r5, r1]
	cmp r0, #0
	beq _02248E22
	strb r0, [r2]
	add r2, r2, #1
	add r4, r4, #1
_02248E22:
	add r1, r1, #1
	cmp r1, #8
	blt _02248E16
	cmp r4, #0
	bne _02248E32
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, pc}
_02248E32:
	cmp r4, #1
	bne _02248E3E
	add r0, sp, #0
	add sp, #8
	ldrb r0, [r0]
	pop {r3, r4, r5, pc}
_02248E3E:
	bl MTRandom
	add r1, r4, #0
	bl _u32_div_f
	add r0, sp, #0
	ldrb r0, [r0, r1]
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02248E50
ov06_02248E50: ; 0x02248E50
	push {r4, lr}
	sub sp, #8
	add r4, r2, #0
	cmp r1, #4
	beq _02248E6A
	ldr r4, [sp, #0x10]
	str r4, [sp]
	ldr r4, [sp, #0x14]
	str r4, [sp, #4]
	bl sub_0202B678
	add sp, #8
	pop {r4, pc}
_02248E6A:
	ldr r1, [sp, #0x10]
	cmp r1, #0
	beq _02248E76
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02248E76:
	cmp r3, #0
	bne _02248E80
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02248E80:
	add r1, r4, #0
	bl sub_0202B440
	cmp r0, #0
	bne _02248E94
	ldr r0, [sp, #0x14]
	add sp, #8
	strb r4, [r0]
	mov r0, #1
	pop {r4, pc}
_02248E94:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_02248E9C
ov06_02248E9C: ; 0x02248E9C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #8]
	ldr r6, [sp, #0x40]
	ldr r0, [r1, #0xc]
	str r2, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r5, [sp, #0x44]
	bl Save_SafariZone_Get
	str r0, [sp, #0x14]
	ldrb r0, [r6]
	mov r4, #0
	cmp r0, #0
	beq _02248EFC
	add r7, sp, #0x18
_02248EBC:
	add r0, r7, #0
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #8]
	str r0, [sp]
	str r7, [sp, #4]
	ldrb r2, [r6]
	ldr r0, [sp, #0x14]
	ldr r3, [sp, #0xc]
	bl ov06_02248E50
	cmp r0, #0
	beq _02248EF4
	mov r0, #0
	add r1, r7, #0
	b _02248EEA
_02248EE2:
	strb r2, [r5, r4]
	add r4, r4, #1
	add r1, r1, #1
	add r0, r0, #1
_02248EEA:
	ldrb r2, [r1]
	cmp r2, #0
	beq _02248EF4
	cmp r0, #0x10
	blt _02248EE2
_02248EF4:
	add r6, r6, #1
	ldrb r0, [r6]
	cmp r0, #0
	bne _02248EBC
_02248EFC:
	add r0, r4, #0
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02248F04
ov06_02248F04: ; 0x02248F04
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	mov r4, #0
	b _02248F36
_02248F10:
	add r0, r6, #0
	add r1, r7, #0
	bl ov06_02248C68
	str r0, [sp]
	ldr r2, [sp]
	add r0, r7, #0
	add r1, r6, #0
	bl sub_02060D48
	cmp r0, #0
	bne _02248F2C
	mov r0, #0
	strb r0, [r5]
_02248F2C:
	ldr r0, [sp]
	bl ov06_02248CB8
	add r5, r5, #1
	add r4, r4, #1
_02248F36:
	ldrb r2, [r5]
	cmp r2, #0
	beq _02248F40
	cmp r4, #0x10
	blt _02248F10
_02248F40:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02248F44
ov06_02248F44: ; 0x02248F44
	push {r4, r5, r6, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0
	bl Save_SafariZone_Get
	ldrb r1, [r5]
	add r4, r0, #0
	cmp r1, #0
	beq _02248F6C
	mov r6, #0
_02248F58:
	add r0, r4, #0
	bl sub_0202B440
	cmp r0, #0
	beq _02248F64
	strb r6, [r5]
_02248F64:
	add r5, r5, #1
	ldrb r1, [r5]
	cmp r1, #0
	bne _02248F58
_02248F6C:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02248F70
ov06_02248F70: ; 0x02248F70
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	bl ov06_02248D00
	str r0, [sp, #8]
	bl ov06_02248D60
	add r4, r0, #0
	add r0, sp, #0xc
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	add r0, sp, #0x14
	mov r1, #0
	mov r2, #0x10
	bl MI_CpuFill8
	ldr r0, [sp, #8]
	add r1, r5, #0
	add r2, sp, #0xc
	bl ov06_02248DB0
	add r0, sp, #0xc
	str r0, [sp]
	add r0, sp, #0x14
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	add r3, r7, #0
	bl ov06_02248E9C
	cmp r0, #0
	bne _02248FC2
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02248FC2:
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0x14
	bl ov06_02248F04
	add r0, r5, #0
	add r1, sp, #0x14
	bl ov06_02248F44
	add r0, r5, #0
	add r1, sp, #0x14
	bl ov06_02248E00
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_02248FE0
ov06_02248FE0: ; 0x02248FE0
	push {r4, lr}
	mov r1, #0
	add r2, r1, #0
	add r4, r0, #0
	bl ov06_02248F70
	cmp r0, #0
	bne _02249016
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov06_02248F70
	cmp r0, #0
	bne _02249016
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl ov06_02248F70
	cmp r0, #0
	bne _02249016
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl ov06_02248F70
_02249016:
	pop {r4, pc}

	thumb_func_start ov06_02249018
ov06_02249018: ; 0x02249018
	push {r4, lr}
	bl ov06_02248D00
	add r4, r0, #0
	cmp r4, #8
	bls _02249028
	bl GF_AssertFail
_02249028:
	ldr r2, _02249034 ; =0x02251738
	sub r1, r4, #1
	mov r0, #7
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
	.align 2, 0
_02249034: .word ov06_02251738

	thumb_func_start ov06_02249038
ov06_02249038: ; 0x02249038
	push {r4, r5, r6, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	add r5, r1, #0
	bl Save_SafariZone_Get
	add r6, r0, #0
	add r0, r4, #0
	bl ov06_02249018
	add r4, r0, #0
	cmp r5, #3
	bhi _02249066
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224905E: ; jump table
	.short _0224906A - _0224905E - 2 ; case 0
	.short _02249084 - _0224905E - 2 ; case 1
	.short _02249096 - _0224905E - 2 ; case 2
	.short _0224909A - _0224905E - 2 ; case 3
_02249066:
	bl GF_AssertFail
_0224906A:
	bl GF_RTC_GetTimeOfDay
	cmp r0, #0
	beq _02249078
	cmp r0, #1
	beq _0224907C
	b _02249080
_02249078:
	ldrb r0, [r4]
	pop {r4, r5, r6, pc}
_0224907C:
	ldrb r0, [r4, #1]
	pop {r4, r5, r6, pc}
_02249080:
	ldrb r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02249084:
	add r0, r6, #0
	bl sub_0202B458
	cmp r0, #0
	bne _02249092
	ldrb r0, [r4, #3]
	pop {r4, r5, r6, pc}
_02249092:
	ldrb r0, [r4, #4]
	pop {r4, r5, r6, pc}
_02249096:
	ldrb r0, [r4, #5]
	pop {r4, r5, r6, pc}
_0224909A:
	ldrb r0, [r4, #6]
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_022490A0
ov06_022490A0: ; 0x022490A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	str r1, [sp, #4]
	add r5, r2, #0
	add r6, r3, #0
	bl ov06_02248D00
	bl ov06_02248D60
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_SafariZone_Get
	add r1, r5, #0
	bl sub_0202B414
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl ov06_02248C68
	add r5, r0, #0
	bl ov06_02248B44
	ldr r2, [sp, #4]
	add r0, r7, #0
	add r1, r4, #0
	add r3, r5, #0
	str r6, [sp]
	bl sub_02060D1C
	ldr r1, [sp, #0x20]
	strh r0, [r1]
	add r0, r5, #0
	bl ov06_02248CB8
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_022490F0
ov06_022490F0: ; 0x022490F0
	mov r0, #1
	bx lr

	thumb_func_start ov06_022490F4
ov06_022490F4: ; 0x022490F4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #2
	mov r2, #7
	bl sub_0205F2E4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02249108
ov06_02249108: ; 0x02249108
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #2
	add r2, r1, #0
	bl sub_0205F2E4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224911C
ov06_0224911C: ; 0x0224911C
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #2
	mov r2, #9
	bl sub_0205F2E4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02249130
ov06_02249130: ; 0x02249130
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #2
	mov r2, #0xa
	bl sub_0205F2E4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02249144
ov06_02249144: ; 0x02249144
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #2
	mov r2, #0xb
	bl sub_0205F2E4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02249158
ov06_02249158: ; 0x02249158
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	mov r1, #2
	mov r2, #0x11
	bl sub_0205F2E4
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224916C
ov06_0224916C: ; 0x0224916C
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_CountBadges
	cmp r0, #5
	blt _02249180
	mov r0, #1
	pop {r3, pc}
_02249180:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov06_02249184
ov06_02249184: ; 0x02249184
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_Pokedex_Get
	bl Pokedex_SinnohDexIsComplete
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02249194
ov06_02249194: ; 0x02249194
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_Pokedex_Get
	bl Pokedex_GetSinnohDexFlag
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_022491A4
ov06_022491A4: ; 0x022491A4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205ED0C
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_022491B4
ov06_022491B4: ; 0x022491B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r4, _022491F4 ; =0x02251770
	str r0, [sp]
	add r7, r1, #0
	mov r6, #0
	add r5, sp, #4
_022491C2:
	ldr r0, [sp]
	ldr r1, [r4]
	blx r1
	add r6, r6, #1
	add r4, r4, #4
	stmia r5!, {r0}
	cmp r6, #0xb
	blo _022491C2
	mov r4, #0
	ldr r3, _022491F8 ; =ov06_02252338
	add r0, r4, #0
	add r2, sp, #4
_022491DA:
	ldrb r1, [r3]
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _022491E8
	strb r4, [r7, r0]
	add r0, r0, #1
_022491E8:
	add r4, r4, #1
	add r3, r3, #1
	cmp r4, #0x1d
	blo _022491DA
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022491F4: .word ov06_02251770
_022491F8: .word ov06_02252338

	thumb_func_start ov06_022491FC
ov06_022491FC: ; 0x022491FC
	push {r4, lr}
	sub sp, #0x20
	add r4, r0, #0
	add r0, sp, #0
	mov r1, #0
	mov r2, #0x20
	bl MI_CpuFill8
	add r0, r4, #0
	add r1, sp, #0
	bl ov06_022491B4
	add r4, r0, #0
	bne _0224921E
	add sp, #0x20
	mov r0, #0
	pop {r4, pc}
_0224921E:
	bl MTRandom
	add r1, r4, #0
	bl _u32_div_f
	add r0, sp, #0
	ldrb r0, [r0, r1]
	add sp, #0x20
	pop {r4, pc}

	thumb_func_start ov06_02249230
ov06_02249230: ; 0x02249230
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	cmp r1, #0
	bne _022492A4
	cmp r4, #0
	bne _02249244
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02249244:
	add r0, sp, #0
	bl GF_RTC_CopyDate
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _02249254
	bl GF_AssertFail
_02249254:
	ldr r0, [sp, #4]
	cmp r0, #0xc
	bls _0224925E
	bl GF_AssertFail
_0224925E:
	ldr r0, [sp, #4]
	ldr r3, _022492A8 ; =0x0225181C
	sub r0, r0, #1
	lsl r0, r0, #3
	ldr r6, [r3, r0]
	add r2, r3, r0
	mov r1, #0
	cmp r6, #0
	ble _022492A2
	ldr r3, [r2, #4]
	ldr r5, [sp, #8]
_02249274:
	lsl r0, r1, #1
	ldrh r7, [r3, r0]
	asr r7, r7, #8
	lsl r7, r7, #0x18
	lsr r7, r7, #0x18
	cmp r5, r7
	bne _02249298
	ldr r1, [r2, #4]
	ldrh r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x16
	ldr r0, _022492AC ; =0x02251808
	ldr r0, [r0, r1]
	add r0, r4, r0
	bpl _022492A4
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02249298:
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, r6
	blt _02249274
_022492A2:
	add r0, r4, #0
_022492A4:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022492A8: .word ov06_0225181C
_022492AC: .word ov06_02251808

	thumb_func_start ov06_022492B0
ov06_022492B0: ; 0x022492B0
	push {r3, r4, r5, lr}
	mov r1, #0x4f
	mov r2, #0
	lsl r1, r1, #2
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4, #0x20]
	bl ov06_02249460
	add r0, r4, #0
	bl ov06_022492EC
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022492D4
ov06_022492D4: ; 0x022492D4
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02249310
	add r0, r4, #0
	bl ov06_022494C0
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_022492EC
ov06_022492EC: ; 0x022492EC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	bl ov05_021E4C20
	ldr r0, [r0, #0x34]
	bl sub_0205839C
	sub r2, r0, #1
	ldr r0, _0224930C ; =ov06_02249388
	add r1, r4, #0
	bl sub_0200CA44
	str r0, [r4, #0x24]
	pop {r4, pc}
	nop
_0224930C: .word ov06_02249388

	thumb_func_start ov06_02249310
ov06_02249310: ; 0x02249310
	ldr r3, _02249318 ; =sub_0200CAB4
	ldr r0, [r0, #0x24]
	bx r3
	nop
_02249318: .word sub_0200CAB4

	thumb_func_start ov06_0224931C
ov06_0224931C: ; 0x0224931C
	add r2, r0, #0
	add r2, #0x14
	add r3, r1, #0
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	bx lr

	thumb_func_start ov06_0224932C
ov06_0224932C: ; 0x0224932C
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	bx lr
	.align 2, 0

	thumb_func_start ov06_02249338
ov06_02249338: ; 0x02249338
	ldr r1, [r0, #4]
	lsl r2, r1, #2
	ldr r1, _0224935C ; =0x0225189C
	ldr r1, [r1, r2]
	str r1, [r0, #0x10]
	ldr r2, [r0, #4]
	mov r1, #0xc
	add r3, r2, #0
	mul r3, r1
	ldr r1, _02249360 ; =0x0225190C
	add r2, r0, #0
	add r3, r1, r3
	ldmia r3!, {r0, r1}
	add r2, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	bx lr
	.align 2, 0
_0224935C: .word ov06_0225189C
_02249360: .word ov06_0225190C

	thumb_func_start ov06_02249364
ov06_02249364: ; 0x02249364
	ldr r3, [r0]
	cmp r3, r1
	bge _02249376
	add r2, r3, r2
	str r2, [r0]
	cmp r2, r1
	ble _02249384
	str r1, [r0]
	bx lr
_02249376:
	cmp r3, r1
	ble _02249384
	sub r2, r3, r2
	str r2, [r0]
	cmp r2, r1
	bge _02249384
	str r1, [r0]
_02249384:
	bx lr
	.align 2, 0

	thumb_func_start ov06_02249388
ov06_02249388: ; 0x02249388
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	bl GF_RTC_GetTimeOfDay
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0
	beq _022493A6
	cmp r1, #1
	beq _022493C8
	cmp r1, #2
	beq _022493D2
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_022493A6:
	str r4, [r5, #4]
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02249338
	ldr r0, [r5, #0x10]
	bl ov06_0224932C
	add r1, r0, #0
	add r0, r5, #0
	bl ov06_022494E4
	ldr r0, [r5]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_022493C8:
	ldr r0, [r5, #4]
	cmp r0, r4
	beq _02249454
	add r0, r1, #1
	str r0, [r5]
_022493D2:
	ldr r0, _02249458 ; =0x0225189C
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	add r1, r4, #0
	str r0, [sp]
	mov r0, #0xc
	mul r1, r0
	ldr r0, _0224945C ; =0x0225190C
	add r2, sp, #4
	add r3, r0, r1
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	ldr r1, [sp, #4]
	add r0, #0x14
	mov r2, #0x10
	bl ov06_02249364
	ldr r7, [sp, #8]
	add r0, r5, #0
	add r0, #0x18
	add r1, r7, #0
	mov r2, #0x10
	bl ov06_02249364
	ldr r6, [sp, #0xc]
	add r0, r5, #0
	add r0, #0x1c
	add r1, r6, #0
	mov r2, #0x10
	bl ov06_02249364
	add r0, r5, #0
	mov r2, #2
	ldr r1, [sp]
	add r0, #0x10
	lsl r2, r2, #8
	bl ov06_02249364
	ldr r0, [r5, #0x10]
	bl ov06_0224932C
	add r1, r0, #0
	add r0, r5, #0
	bl ov06_022494E4
	ldr r1, [sp, #4]
	ldr r0, [r5, #0x14]
	cmp r1, r0
	bne _02249454
	ldr r0, [r5, #0x18]
	cmp r7, r0
	bne _02249454
	ldr r0, [r5, #0x1c]
	cmp r6, r0
	bne _02249454
	ldr r1, [r5, #0x10]
	ldr r0, [sp]
	cmp r0, r1
	bne _02249454
	str r4, [r5, #4]
	mov r0, #1
	str r0, [r5]
_02249454:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02249458: .word ov06_0225189C
_0224945C: .word ov06_0225190C

	thumb_func_start ov06_02249460
ov06_02249460: ; 0x02249460
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0x49
	lsl r0, r0, #2
	add r1, r4, r0
	add r0, #0xc
	str r1, [sp]
	add r0, r4, r0
	str r0, [sp, #4]
	add r3, r4, #0
	ldr r0, [r4, #0x20]
	mov r1, #0x11
	mov r2, #0
	add r3, #0x28
	bl ov05_021E51EC
	mov r0, #0x4a
	lsl r0, r0, #2
	add r1, r4, r0
	add r0, #0xc
	str r1, [sp]
	add r0, r4, r0
	str r0, [sp, #4]
	add r3, r4, #0
	ldr r0, [r4, #0x20]
	mov r1, #0x12
	mov r2, #0
	add r3, #0x7c
	bl ov05_021E51EC
	mov r0, #0x4b
	lsl r0, r0, #2
	add r1, r4, r0
	add r0, #0xc
	str r1, [sp]
	add r0, r4, r0
	str r0, [sp, #4]
	ldr r0, [r4, #0x20]
	add r4, #0xd0
	mov r1, #0x13
	mov r2, #0
	add r3, r4, #0
	bl ov05_021E51EC
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_022494C0
ov06_022494C0: ; 0x022494C0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl ov05_021E4C00
	mov r0, #0x4d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov05_021E4C00
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_022494E4
ov06_022494E4: ; 0x022494E4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x49
	lsl r0, r0, #2
	mov r2, #0x1f
	add r4, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	lsl r2, r2, #0x10
	bl NNSi_G3dModifyPolygonAttrMask
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl NNS_G3dMdlSetMdlAlphaAll
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02249508
ov06_02249508: ; 0x02249508
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	add r4, r0, #0
	mov r1, #0
	str r4, [sp, #0x14]
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x1c]
	bl sub_02058B5C
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _02249548 ; =0x02251888
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	nop
_02249548: .word ov06_02251888

	thumb_func_start ov06_0224954C
ov06_0224954C: ; 0x0224954C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	bl sub_02064754
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x1c]
	bl sub_02058458
	str r0, [r4]
	ldr r0, [r4, #0x1c]
	bl MapObject_GetID
	str r0, [r4, #4]
	ldr r0, [r4, #0x1c]
	bl sub_020589CC
	cmp r0, #1
	ldr r0, [r4, #0x1c]
	bne _0224958E
	bl sub_02058750
	b _02249592
_0224958E:
	bl sub_02058450
_02249592:
	str r0, [r4, #8]
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_02249598
ov06_02249598: ; 0x02249598
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224959C
ov06_0224959C: ; 0x0224959C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r6, [r4, #0x1c]
	ldr r1, [r4]
	add r5, r0, #0
	ldr r2, [r4, #4]
	ldr r3, [r4, #8]
	add r0, r6, #0
	bl sub_020582F8
	cmp r0, #0
	bne _022495C0
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_022495C0:
	add r0, r6, #0
	mov r1, #8
	bl sub_020587F4
	cmp r0, #0
	beq _022495D6
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_022495D6:
	mov r0, #0
	str r0, [r4, #0xc]
	ldr r1, _02249604 ; =0x00100200
	add r0, r6, #0
	bl MapObject_TestFlagsBits
	cmp r0, #1
	bne _022495EE
	mov r0, #1
	add sp, #0xc
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, pc}
_022495EE:
	add r0, r6, #0
	add r1, sp, #0
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02249604: .word 0x00100200

	thumb_func_start ov06_02249608
ov06_02249608: ; 0x02249608
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #1
	beq _02249660
	ldr r6, _02249664 ; =0x022518C4
	add r3, sp, #0
	mov r2, #4
_0224961C:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224961C
	ldr r0, [r6]
	add r1, sp, #0x24
	str r0, [r3]
	ldr r0, [r4, #0x18]
	bl ov06_0224931C
	add r0, r5, #0
	add r1, sp, #0x30
	bl sub_0206477C
	mov r0, #2
	ldr r1, [sp, #0x30]
	lsl r0, r0, #0xa
	sub r1, r1, r0
	str r1, [sp, #0x30]
	lsl r1, r0, #3
	ldr r2, [sp, #0x34]
	lsl r0, r0, #1
	sub r1, r2, r1
	str r1, [sp, #0x34]
	ldr r1, [sp, #0x38]
	add r2, sp, #0
	add r0, r1, r0
	str r0, [sp, #0x38]
	ldr r0, [r4, #0x18]
	add r1, sp, #0x30
	add r0, #0x28
	add r3, sp, #0x24
	bl sub_0201B26C
_02249660:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02249664: .word ov06_022518C4

	thumb_func_start ov06_02249668
ov06_02249668: ; 0x02249668
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021E4C24
	add r6, r0, #0
	mov r1, #0
	str r6, [sp, #0x14]
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x1c]
	bl sub_02058B5C
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _022496A8 ; =0x022518B0
	add r0, r6, #0
	add r2, sp, #8
	add r3, r4, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r4, r5, r6, pc}
	.align 2, 0
_022496A8: .word ov06_022518B0

	thumb_func_start ov06_022496AC
ov06_022496AC: ; 0x022496AC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r6, [r4, #0x1c]
	ldr r1, [r4]
	add r5, r0, #0
	ldr r2, [r4, #4]
	ldr r3, [r4, #8]
	add r0, r6, #0
	bl sub_020582F8
	cmp r0, #0
	bne _022496D0
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_022496D0:
	mov r0, #0
	str r0, [r4, #0xc]
	ldr r1, _022496FC ; =0x00100200
	add r0, r6, #0
	bl MapObject_TestFlagsBits
	cmp r0, #1
	bne _022496E8
	mov r0, #1
	add sp, #0xc
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, pc}
_022496E8:
	add r0, r6, #0
	add r1, sp, #0
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022496FC: .word 0x00100200

	thumb_func_start ov06_02249700
ov06_02249700: ; 0x02249700
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #1
	beq _02249792
	ldr r5, _02249798 ; =0x0225187C
	add r3, sp, #0x24
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _0224979C ; =0x022518E8
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_02249720:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _02249720
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	mov r0, #2
	ldr r1, [sp, #0x30]
	lsl r0, r0, #0xa
	sub r1, r1, r0
	str r1, [sp, #0x30]
	lsl r1, r0, #3
	ldr r2, [sp, #0x34]
	lsl r0, r0, #1
	sub r1, r2, r1
	str r1, [sp, #0x34]
	ldr r1, [sp, #0x38]
	add r0, r1, r0
	str r0, [sp, #0x38]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _02249760
	cmp r0, #1
	beq _02249772
	cmp r0, #2
	beq _02249784
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
_02249760:
	ldr r0, [r4, #0x18]
	add r1, sp, #0x30
	add r0, #0x28
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
_02249772:
	ldr r0, [r4, #0x18]
	add r1, sp, #0x30
	add r0, #0x7c
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
_02249784:
	ldr r0, [r4, #0x18]
	add r1, sp, #0x30
	add r0, #0xd0
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
_02249792:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	nop
_02249798: .word ov06_0225187C
_0224979C: .word ov06_022518E8

	thumb_func_start ov06_022497A0
ov06_022497A0: ; 0x022497A0
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_022497CC
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_022497BC
ov06_022497BC: ; 0x022497BC
	push {r4, lr}
	add r4, r0, #0
	bl ov06_022497DC
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_022497CC
ov06_022497CC: ; 0x022497CC
	ldr r3, _022497D8 ; =ov05_021E5078
	ldr r0, [r0]
	mov r1, #2
	mov r2, #0x14
	bx r3
	nop
_022497D8: .word ov05_021E5078

	thumb_func_start ov06_022497DC
ov06_022497DC: ; 0x022497DC
	ldr r3, _022497E4 ; =ov05_021E50A0
	ldr r0, [r0]
	mov r1, #2
	bx r3
	.align 2, 0
_022497E4: .word ov05_021E50A0

	thumb_func_start ov06_022497E8
ov06_022497E8: ; 0x022497E8
	push {r4, r5, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r4, r1, #0
	bl MapObject_GetFieldSystemPtr
	str r0, [sp, #8]
	add r0, r5, #0
	bl ov05_021E4C24
	mov r1, #1
	str r0, [sp, #0xc]
	bl ov05_021E4C08
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r1, sp, #0x18
	str r5, [sp, #0x14]
	bl sub_02058B5C
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #8
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	ldr r1, _02249830 ; =0x02251958
	add r2, sp, #0x18
	add r3, r4, #0
	bl ov05_021E4DC4
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_02249830: .word ov06_02251958

	thumb_func_start ov06_02249834
ov06_02249834: ; 0x02249834
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x14
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r5, #0
	bl sub_02064754
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x20]
	bl MapObject_GetID
	str r0, [r4]
	ldr r0, [r4, #0x20]
	bl sub_02058450
	str r0, [r4, #4]
	ldr r0, [r4, #0x20]
	bl sub_02058458
	str r0, [r4, #8]
	bl sub_0205C334
	cmp r0, #1
	bne _0224987E
	ldr r0, [r4, #0x20]
	bl sub_0205C340
	str r0, [r4, #8]
_0224987E:
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	str r0, [r4, #0x30]
	mov r0, #0x40
	str r0, [r4, #0x34]
	ldr r1, [r4, #0x20]
	add r0, r4, #0
	add r2, sp, #0
	bl ov06_02249A00
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02249A68
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_022498AC
ov06_022498AC: ; 0x022498AC
	push {r3, lr}
	ldr r0, [r1, #0xc]
	cmp r0, #1
	bne _022498BA
	ldr r0, [r1, #0x24]
	bl sub_0201F744
_022498BA:
	pop {r3, pc}

	thumb_func_start ov06_022498BC
ov06_022498BC: ; 0x022498BC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r6, [r4, #0x20]
	add r5, r0, #0
	add r0, r6, #0
	bl sub_02058458
	add r7, r0, #0
	bl sub_0205C334
	cmp r0, #1
	bne _022498DE
	ldr r0, [r4, #0x20]
	bl sub_0205C340
	add r7, r0, #0
_022498DE:
	ldr r0, [r4, #8]
	cmp r0, r7
	bne _022498FC
	ldr r1, [r4]
	ldr r2, [r4, #4]
	add r0, r6, #0
	bl sub_020582A8
	cmp r0, #0
	beq _022498FC
	add r0, r6, #0
	bl sub_02058A9C
	cmp r0, #0
	bne _02249906
_022498FC:
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02249906:
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x34]
	add r1, r1, r0
	mov r0, #0x12
	lsl r0, r0, #8
	str r1, [r4, #0x28]
	cmp r1, r0
	blt _02249920
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x34]
	neg r0, r0
	str r0, [r4, #0x34]
	b _02249930
_02249920:
	mov r0, #0xe
	lsl r0, r0, #8
	cmp r1, r0
	bgt _02249930
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x34]
	neg r0, r0
	str r0, [r4, #0x34]
_02249930:
	add r0, r4, #0
	add r1, r6, #0
	add r2, sp, #0
	bl ov06_02249A00
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _02249950
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02249A68
_02249950:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_02249954
ov06_02249954: ; 0x02249954
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r4, [r5, #0x20]
	add r6, r0, #0
	add r0, r4, #0
	bl sub_02058458
	add r7, r0, #0
	bl sub_0205C334
	cmp r0, #1
	bne _02249976
	ldr r0, [r5, #0x20]
	bl sub_0205C340
	add r7, r0, #0
_02249976:
	ldr r0, [r5, #8]
	cmp r0, r7
	bne _02249994
	ldr r1, [r5]
	ldr r2, [r5, #4]
	add r0, r4, #0
	bl sub_020582A8
	cmp r0, #0
	beq _02249994
	add r0, r4, #0
	bl sub_02058A9C
	cmp r0, #0
	bne _0224999E
_02249994:
	add r0, r6, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0224999E:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _022499FA
	add r0, r4, #0
	bl sub_02058890
	cmp r0, #1
	ldr r0, [r5, #0x24]
	bne _022499B8
	mov r1, #0
	bl sub_0201F80C
	b _022499BE
_022499B8:
	mov r1, #1
	bl sub_0201F80C
_022499BE:
	add r0, r6, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r5, #0x24]
	add r1, sp, #0
	bl sub_0201F7C8
	add r1, r5, #0
	ldr r0, [r5, #0x24]
	add r1, #0x28
	bl sub_0201F7F0
	ldr r0, [r5, #0x20]
	bl ov05_021F0514
	add r4, r0, #0
	bl sub_0201F844
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl sub_0201F830
	add r0, r4, #0
	bl sub_0201F880
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl sub_0201F86C
_022499FA:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_02249A00
ov06_02249A00: ; 0x02249A00
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _02249A64 ; =0x02251948
	str r1, [sp]
	ldr r1, [r0, #8]
	ldr r0, [r0, #0xc]
	add r4, r2, #0
	str r0, [sp, #8]
	str r1, [sp, #4]
	ldr r0, [sp]
	add r1, r4, #0
	bl sub_02058B84
	ldr r0, [r4, #8]
	add r1, r4, #0
	neg r6, r0
	ldr r0, [sp]
	ldr r7, [r4]
	bl sub_02058B5C
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	bl sub_02059E9C
	ldr r1, [r4]
	add r1, r1, r7
	str r1, [r4]
	mov r1, #7
	lsl r1, r1, #0xc
	ldr r2, [r4, #8]
	sub r1, r6, r1
	add r1, r2, r1
	str r1, [r4, #8]
	cmp r0, #0
	bne _02249A50
	mov r0, #0
	add sp, #0xc
	str r0, [r4, #4]
	pop {r4, r5, r6, r7, pc}
_02249A50:
	ldr r0, [r5, #0x10]
	ldr r2, [r4, #4]
	lsl r1, r0, #2
	add r0, sp, #4
	ldr r0, [r0, r1]
	sub r0, r2, r0
	str r0, [r4, #4]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02249A64: .word ov06_02251948

	thumb_func_start ov06_02249A68
ov06_02249A68: ; 0x02249A68
	push {r4, r5, lr}
	sub sp, #0x34
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x20]
	bl MapObject_GetManager
	ldr r1, [r4, #8]
	add r2, sp, #0
	bl ov05_021F220C
	cmp r0, #0
	beq _02249AAE
	ldr r0, [r4, #0x20]
	bl ov05_021F2E28
	cmp r0, #1
	beq _02249AAE
	ldr r0, [r4, #0x18]
	mov r1, #2
	bl ov05_021E5094
	str r0, [sp]
	add r0, r5, #0
	add r1, sp, #0x28
	bl sub_0206477C
	ldr r0, [r4, #0x18]
	add r1, sp, #0
	add r2, sp, #0x28
	bl ov05_021E4E90
	str r0, [r4, #0x24]
	mov r0, #1
	str r0, [r4, #0xc]
_02249AAE:
	add sp, #0x34
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_02249AB4
ov06_02249AB4: ; 0x02249AB4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r4, r1, #0
	add r6, r4, #0
	add r5, r0, #0
	add r6, #0x10
	add r3, sp, #0
	mov r2, #5
_02249AC4:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02249AC4
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov05_021E5094
	str r0, [sp]
	add r0, r5, #0
	add r1, sp, #0x28
	bl sub_0206477C
	ldr r0, [r4, #8]
	add r1, sp, #0
	add r2, sp, #0x28
	bl ov05_021E4E90
	str r0, [r4, #0x3c]
	ldr r5, [r4, #0x38]
	add r0, r5, #0
	bl sub_0201F844
	add r1, r0, #0
	ldr r0, [r4, #0x3c]
	bl sub_0201F830
	add r0, r5, #0
	bl sub_0201F8C0
	add r1, r0, #0
	ldr r0, [r4, #0x3c]
	bl sub_0201F890
	add r0, r5, #0
	bl sub_0201F880
	add r1, r0, #0
	ldr r0, [r4, #0x3c]
	bl sub_0201F86C
	ldr r0, [r4, #0x3c]
	mov r1, #0
	bl sub_0201F854
	ldr r0, [r4, #0x3c]
	bl sub_0201F8F0
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}

	thumb_func_start ov06_02249B28
ov06_02249B28: ; 0x02249B28
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _02249B78 ; =0x02251948
	add r4, r1, #0
	ldr r1, [r0]
	ldr r0, [r0, #4]
	add r3, r5, #0
	add r3, #0x50
	str r1, [sp]
	str r0, [sp, #4]
	ldmia r3!, {r0, r1}
	add r2, r4, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r4, #0
	str r0, [r2]
	ldr r0, [r5, #4]
	bl sub_02059E9C
	mov r1, #7
	ldr r2, [r4, #8]
	lsl r1, r1, #0xc
	sub r1, r2, r1
	str r1, [r4, #8]
	cmp r0, #0
	bne _02249B66
	mov r0, #0
	add sp, #8
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
_02249B66:
	ldr r0, [r5]
	ldr r2, [r4, #4]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	sub r0, r2, r0
	str r0, [r4, #4]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02249B78: .word ov06_02251948

	thumb_func_start ov06_02249B7C
ov06_02249B7C: ; 0x02249B7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl ov05_021E4C20
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	str r5, [sp, #0xc]
	bl ov05_021E4C08
	str r0, [sp, #0x10]
	add r3, sp, #0x14
	mov r2, #5
_02249B9E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02249B9E
	str r6, [sp, #0x3c]
	add r0, sp, #8
	str r0, [sp]
	ldr r0, [sp, #0x5c]
	ldr r1, _02249BC0 ; =0x0225196C
	str r0, [sp, #4]
	ldr r3, [sp, #0x58]
	add r0, r5, #0
	add r2, r7, #0
	bl ov05_021E4DC4
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02249BC0: .word ov06_0225196C

	thumb_func_start ov06_02249BC4
ov06_02249BC4: ; 0x02249BC4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r6, r0, #0
	add r3, r4, #4
	mov r2, #7
_02249BD6:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02249BD6
	add r0, r5, #0
	bl sub_02064754
	str r0, [r4]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [r4, #0x40]
	str r0, [r4, #0x44]
	str r0, [r4, #0x48]
	mov r0, #0x40
	add r1, r4, #0
	str r0, [r4, #0x4c]
	add r0, r5, #0
	add r1, #0x50
	bl sub_0206477C
	add r0, r4, #0
	add r1, sp, #0
	bl ov06_02249B28
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02249AB4
	add r0, r5, #0
	bl sub_020646DC
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_02249C24
ov06_02249C24: ; 0x02249C24
	ldr r3, _02249C2C ; =sub_0201F744
	ldr r0, [r1, #0x3c]
	bx r3
	nop
_02249C2C: .word sub_0201F744

	thumb_func_start ov06_02249C30
ov06_02249C30: ; 0x02249C30
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r2, [r1, #0x40]
	ldr r0, [r1, #0x4c]
	add r2, r2, r0
	mov r0, #0x12
	lsl r0, r0, #8
	str r2, [r1, #0x40]
	cmp r2, r0
	blt _02249C50
	str r0, [r1, #0x40]
	ldr r0, [r1, #0x4c]
	neg r0, r0
	str r0, [r1, #0x4c]
	b _02249C60
_02249C50:
	mov r0, #0xe
	lsl r0, r0, #8
	cmp r2, r0
	bgt _02249C60
	str r0, [r1, #0x40]
	ldr r0, [r1, #0x4c]
	neg r0, r0
	str r0, [r1, #0x4c]
_02249C60:
	add r0, r1, #0
	add r1, sp, #0
	bl ov06_02249B28
	add r0, r4, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start ov06_02249C74
ov06_02249C74: ; 0x02249C74
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x3c]
	add r1, sp, #0
	bl sub_0201F7C8
	ldr r0, [r4, #0x3c]
	add r4, #0x40
	add r1, r4, #0
	bl sub_0201F7F0
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov06_02249C98
ov06_02249C98: ; 0x02249C98
	push {r3, r4, r5, lr}
	mov r2, #0
	ldr r1, _02249CB4 ; =0x00000734
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_02249CC8
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_02249CB4: .word 0x00000734

	thumb_func_start ov06_02249CB8
ov06_02249CB8: ; 0x02249CB8
	push {r4, lr}
	add r4, r0, #0
	bl ov06_02249D60
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_02249CC8
ov06_02249CC8: ; 0x02249CC8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, _02249D54 ; =0x022519EC
	ldr r4, _02249D58 ; =0x022519C4
	str r0, [sp, #0x18]
	ldr r0, _02249D5C ; =0x000006E4
	add r1, r5, r0
	str r1, [sp, #0x14]
	add r1, r0, #0
	sub r1, #0x50
	add r1, r5, r1
	str r1, [sp, #0x10]
	add r1, r5, #4
	str r1, [sp, #0xc]
	add r1, r0, #0
	sub r0, #0x28
	add r6, r5, r0
	mov r0, #0xd3
	lsl r0, r0, #2
	add r1, #0x28
	add r0, r5, r0
	add r7, r5, r1
	str r0, [sp, #8]
_02249CFC:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	str r0, [sp]
	ldr r0, [sp, #0x14]
	ldr r3, [sp, #0xc]
	str r0, [sp, #4]
	ldr r0, [r5]
	ldr r1, [r1]
	mov r2, #0
	bl ov05_021E51EC
	str r6, [sp]
	str r7, [sp, #4]
	ldr r0, [r5]
	ldr r1, [r4]
	ldr r3, [sp, #8]
	mov r2, #0
	bl ov05_021E51EC
	ldr r0, [sp, #0x18]
	add r7, r7, #4
	add r0, r0, #4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r6, r6, #4
	add r0, r0, #4
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r4, r4, #4
	add r0, r0, #4
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	add r0, #0x54
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	add r0, #0x54
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, #0xa
	blt _02249CFC
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02249D54: .word ov06_022519EC
_02249D58: .word ov06_022519C4
_02249D5C: .word 0x000006E4

	thumb_func_start ov06_02249D60
ov06_02249D60: ; 0x02249D60
	push {r3, r4, r5, r6, r7, lr}
	ldr r7, _02249D84 ; =0x000006E4
	add r5, r0, #0
	add r6, r7, #0
	mov r4, #0
	add r6, #0x28
_02249D6C:
	ldr r0, [r5, r7]
	bl ov05_021E4C00
	ldr r0, [r5, r6]
	bl ov05_021E4C00
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa
	blt _02249D6C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02249D84: .word 0x000006E4

	thumb_func_start ov06_02249D88
ov06_02249D88: ; 0x02249D88
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r1, r3, #0
	mov r4, #0
	cmp r0, #3
	bhi _02249DEC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02249DA2: ; jump table
	.short _02249DAA - _02249DA2 - 2 ; case 0
	.short _02249DB4 - _02249DA2 - 2 ; case 1
	.short _02249DC8 - _02249DA2 - 2 ; case 2
	.short _02249DD6 - _02249DA2 - 2 ; case 3
_02249DAA:
	mov r0, #0x54
	add r1, r5, #4
	mul r0, r2
	add r4, r1, r0
	b _02249DEC
_02249DB4:
	lsl r3, r1, #4
	ldr r1, _02249DF8 ; =0x02251A14
	lsl r2, r2, #2
	add r1, r1, r3
	ldr r2, [r2, r1]
	mov r1, #0x54
	add r0, r5, #4
	mul r1, r2
	add r4, r0, r1
	b _02249DEC
_02249DC8:
	mov r0, #0xd3
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x54
	mul r0, r2
	add r4, r1, r0
	b _02249DEC
_02249DD6:
	lsl r3, r1, #4
	ldr r1, _02249DF8 ; =0x02251A14
	lsl r2, r2, #2
	add r1, r1, r3
	mov r0, #0xd3
	ldr r2, [r2, r1]
	lsl r0, r0, #2
	mov r1, #0x54
	add r0, r5, r0
	mul r1, r2
	add r4, r0, r1
_02249DEC:
	cmp r4, #0
	bne _02249DF4
	bl GF_AssertFail
_02249DF4:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02249DF8: .word ov06_02251A14

	thumb_func_start ov06_02249DFC
ov06_02249DFC: ; 0x02249DFC
	push {r4, lr}
	mov r4, #0
	cmp r1, #3
	bhi _02249E52
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02249E10: ; jump table
	.short _02249E18 - _02249E10 - 2 ; case 0
	.short _02249E22 - _02249E10 - 2 ; case 1
	.short _02249E36 - _02249E10 - 2 ; case 2
	.short _02249E40 - _02249E10 - 2 ; case 3
_02249E18:
	lsl r1, r2, #2
	add r1, r0, r1
	ldr r0, _02249E60 ; =0x00000694
	ldr r4, [r1, r0]
	b _02249E52
_02249E22:
	ldr r1, _02249E64 ; =0x02251A14
	lsl r3, r3, #4
	lsl r2, r2, #2
	add r1, r1, r3
	ldr r1, [r2, r1]
	lsl r1, r1, #2
	add r1, r0, r1
	ldr r0, _02249E60 ; =0x00000694
	ldr r4, [r1, r0]
	b _02249E52
_02249E36:
	lsl r1, r2, #2
	add r1, r0, r1
	ldr r0, _02249E68 ; =0x000006BC
	ldr r4, [r1, r0]
	b _02249E52
_02249E40:
	ldr r1, _02249E64 ; =0x02251A14
	lsl r3, r3, #4
	lsl r2, r2, #2
	add r1, r1, r3
	ldr r1, [r2, r1]
	lsl r1, r1, #2
	add r1, r0, r1
	ldr r0, _02249E68 ; =0x000006BC
	ldr r4, [r1, r0]
_02249E52:
	cmp r4, #0
	bne _02249E5A
	bl GF_AssertFail
_02249E5A:
	add r0, r4, #0
	pop {r4, pc}
	nop
_02249E60: .word 0x00000694
_02249E64: .word ov06_02251A14
_02249E68: .word 0x000006BC

	thumb_func_start ov06_02249E6C
ov06_02249E6C: ; 0x02249E6C
	ldr r3, _02249E74 ; =ov06_02249E9C
	mov r1, #0
	bx r3
	nop
_02249E74: .word ov06_02249E9C

	thumb_func_start ov06_02249E78
ov06_02249E78: ; 0x02249E78
	ldr r3, _02249E80 ; =ov06_02249E9C
	mov r1, #1
	bx r3
	nop
_02249E80: .word ov06_02249E9C

	thumb_func_start ov06_02249E84
ov06_02249E84: ; 0x02249E84
	ldr r3, _02249E8C ; =ov06_02249E9C
	mov r1, #2
	bx r3
	nop
_02249E8C: .word ov06_02249E9C

	thumb_func_start ov06_02249E90
ov06_02249E90: ; 0x02249E90
	ldr r3, _02249E98 ; =ov06_02249E9C
	mov r1, #3
	bx r3
	nop
_02249E98: .word ov06_02249E9C

	thumb_func_start ov06_02249E9C
ov06_02249E9C: ; 0x02249E9C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	add r4, r1, #0
	bl sub_02058B14
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl sub_02058B24
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl sub_02058B80
	add r6, r0, #0
	add r0, r5, #0
	bl sub_020584C4
	str r0, [sp, #0x14]
	add r0, r5, #0
	bl sub_020584C8
	str r0, [sp, #0x18]
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r7, r0, #0
	add r0, r5, #0
	bl ov05_021E4C24
	mov r1, #0xb
	str r0, [sp, #8]
	bl ov05_021E4C08
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	add r1, r4, #0
	add r5, r0, #0
	bl ov06_02249D88
	str r0, [sp, #0x20]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	add r1, r4, #0
	bl ov06_02249DFC
	str r0, [sp, #0x24]
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	add r2, sp, #0x28
	str r4, [sp, #0x1c]
	bl sub_02059E60
	str r6, [sp, #0x2c]
	cmp r4, #3
	bhi _02249F6A
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02249F1C: ; jump table
	.short _02249F24 - _02249F1C - 2 ; case 0
	.short _02249F24 - _02249F1C - 2 ; case 1
	.short _02249F46 - _02249F1C - 2 ; case 2
	.short _02249F46 - _02249F1C - 2 ; case 3
_02249F24:
	mov r0, #2
	lsl r0, r0, #0xe
	sub r1, r6, r0
	str r1, [sp, #0x2c]
	sub r1, r4, #2
	cmp r1, #1
	bhi _02249F3C
	ldr r1, [sp, #0x30]
	lsr r0, r0, #2
	sub r0, r1, r0
	str r0, [sp, #0x30]
	b _02249F6A
_02249F3C:
	ldr r1, [sp, #0x30]
	lsr r0, r0, #3
	add r0, r1, r0
	str r0, [sp, #0x30]
	b _02249F6A
_02249F46:
	mov r0, #0xa
	lsl r0, r0, #0xc
	sub r0, r6, r0
	str r0, [sp, #0x2c]
	sub r0, r4, #2
	cmp r0, #1
	bhi _02249F60
	mov r0, #2
	ldr r1, [sp, #0x30]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [sp, #0x30]
	b _02249F6A
_02249F60:
	mov r0, #2
	ldr r1, [sp, #0x30]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x30]
_02249F6A:
	add r0, sp, #0x1c
	str r0, [sp]
	ldr r0, [sp, #8]
	ldr r1, _02249F80 ; =0x0225198C
	add r2, sp, #0x28
	mov r3, #0
	str r7, [sp, #4]
	bl ov05_021E4DC4
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02249F80: .word ov06_0225198C

	thumb_func_start ov06_02249F84
ov06_02249F84: ; 0x02249F84
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl sub_02064754
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl sub_0206475C
	ldr r1, [r0, #4]
	str r1, [r4, #0x14]
	ldr r1, [r0, #8]
	str r1, [r4, #0x18]
	mov r1, #0x1f
	str r1, [r4, #0xc]
	ldr r0, [r0]
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_02249FAC
ov06_02249FAC: ; 0x02249FAC
	bx lr
	.align 2, 0

	thumb_func_start ov06_02249FB0
ov06_02249FB0: ; 0x02249FB0
	push {r3, lr}
	ldr r2, [r1]
	cmp r2, #0
	beq _02249FBE
	cmp r2, #1
	beq _02249FD0
	pop {r3, pc}
_02249FBE:
	ldr r0, [r1, #4]
	add r0, r0, #1
	str r0, [r1, #4]
	cmp r0, #0x10
	blt _02249FDC
	ldr r0, [r1]
	add r0, r0, #1
	str r0, [r1]
	pop {r3, pc}
_02249FD0:
	ldr r2, [r1, #0xc]
	sub r2, r2, #2
	str r2, [r1, #0xc]
	bpl _02249FDC
	bl ov05_021E4DE4
_02249FDC:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_02249FE0
ov06_02249FE0: ; 0x02249FE0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #1
	beq _0224A034
	ldr r5, _0224A038 ; =0x02251980
	add r3, sp, #0x24
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _0224A03C ; =0x022519A0
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_0224A000:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _0224A000
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	mov r2, #0x1f
	ldr r0, [r4, #0x18]
	mov r1, #1
	lsl r2, r2, #0x10
	bl NNSi_G3dModifyPolygonAttrMask
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #0xc]
	bl NNS_G3dMdlSetMdlAlphaAll
	ldr r0, [r4, #0x14]
	add r1, sp, #0x30
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
_0224A034:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224A038: .word ov06_02251980
_0224A03C: .word ov06_022519A0

	thumb_func_start ov06_0224A040
ov06_0224A040: ; 0x0224A040
	push {r3, r4, r5, lr}
	mov r1, #0x8b
	mov r2, #0
	lsl r1, r1, #2
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224A06C
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224A05C
ov06_0224A05C: ; 0x0224A05C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224A0B4
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224A06C
ov06_0224A06C: ; 0x0224A06C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r1, #0x85
	ldr r0, [sp, #8]
	lsl r1, r1, #2
	add r6, r0, r1
	sub r1, #0x18
	ldr r5, _0224A0B0 ; =0x02251A74
	add r4, r0, r1
	add r7, r0, #4
_0224A086:
	str r4, [sp]
	str r6, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [r5]
	ldr r0, [r0]
	mov r2, #0
	add r3, r7, #0
	bl ov05_021E51EC
	ldr r0, [sp, #0xc]
	add r6, r6, #4
	add r0, r0, #1
	add r4, r4, #4
	add r7, #0x54
	add r5, r5, #4
	str r0, [sp, #0xc]
	cmp r0, #6
	blt _0224A086
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224A0B0: .word ov06_02251A74

	thumb_func_start ov06_0224A0B4
ov06_0224A0B4: ; 0x0224A0B4
	push {r4, r5, r6, lr}
	mov r6, #0x85
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #2
_0224A0BE:
	ldr r0, [r5, r6]
	bl ov05_021E4C00
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _0224A0BE
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224A0D0
ov06_0224A0D0: ; 0x0224A0D0
	push {r3, r4}
	add r3, r0, #0
	mov r0, #0x54
	mul r0, r2
	add r0, r1, r0
	add r4, r0, #4
	mov r2, #0xa
_0224A0DE:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224A0DE
	ldr r0, [r4]
	str r0, [r3]
	pop {r3, r4}
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224A0F0
ov06_0224A0F0: ; 0x0224A0F0
	push {r3, lr}
	sub r0, #0x5b
	cmp r0, #5
	bhi _0224A128
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224A104: ; jump table
	.short _0224A110 - _0224A104 - 2 ; case 0
	.short _0224A114 - _0224A104 - 2 ; case 1
	.short _0224A118 - _0224A104 - 2 ; case 2
	.short _0224A11C - _0224A104 - 2 ; case 3
	.short _0224A120 - _0224A104 - 2 ; case 4
	.short _0224A124 - _0224A104 - 2 ; case 5
_0224A110:
	mov r0, #0
	pop {r3, pc}
_0224A114:
	mov r0, #1
	pop {r3, pc}
_0224A118:
	mov r0, #2
	pop {r3, pc}
_0224A11C:
	mov r0, #3
	pop {r3, pc}
_0224A120:
	mov r0, #4
	pop {r3, pc}
_0224A124:
	mov r0, #5
	pop {r3, pc}
_0224A128:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov06_0224A130
ov06_0224A130: ; 0x0224A130
	push {r4, r5, r6, lr}
	sub sp, #0xc8
	add r5, r0, #0
	bl ov05_021E4C24
	mov r1, #0xc
	add r4, r0, #0
	bl ov05_021E4C08
	add r6, r0, #0
	add r0, r5, #0
	bl sub_02058458
	bl ov06_0224A0F0
	add r2, r0, #0
	add r0, sp, #0x14
	add r1, r6, #0
	str r2, [sp, #0x68]
	bl ov06_0224A0D0
	add r6, sp, #0x14
	add r3, sp, #0x70
	mov r2, #0xa
_0224A160:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224A160
	ldr r0, [r6]
	add r1, sp, #8
	str r0, [r3]
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r5, #0
	mov r1, #2
	str r4, [sp, #0x6c]
	str r5, [sp, #0xc4]
	bl sub_0205829C
	add r1, sp, #0x68
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224A198 ; =0x02251A60
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0xc8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224A198: .word ov06_02251A60

	thumb_func_start ov06_0224A19C
ov06_0224A19C: ; 0x0224A19C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	bl sub_0206475C
	add r3, r4, #0
	add r5, r0, #0
	add r3, #0xc
	mov r2, #0xc
_0224A1AC:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224A1AC
	ldr r0, [r4, #0x68]
	bl MapObject_GetID
	str r0, [r4, #4]
	ldr r0, [r4, #0x68]
	bl sub_020589CC
	cmp r0, #1
	ldr r0, [r4, #0x68]
	bne _0224A1CE
	bl sub_02058750
	b _0224A1D2
_0224A1CE:
	bl sub_02058450
_0224A1D2:
	str r0, [r4, #8]
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224A1D8
ov06_0224A1D8: ; 0x0224A1D8
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224A1DC
ov06_0224A1DC: ; 0x0224A1DC
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r2, r1, #0
	ldr r5, [r2, #0x68]
	ldr r1, [r2, #4]
	add r4, r0, #0
	ldr r2, [r2, #8]
	add r0, r5, #0
	bl sub_020582A8
	cmp r0, #0
	bne _0224A1FE
	add r0, r4, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, pc}
_0224A1FE:
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02058B84
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	ldr r2, [sp, #0x14]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #0x10]
	mov r0, #2
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	add r0, r2, r0
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r1, sp, #0xc
	bl sub_0206476C
	add sp, #0x18
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224A238
ov06_0224A238: ; 0x0224A238
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	ldr r5, _0224A278 ; =0x02251A54
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x24
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _0224A27C ; =0x02251A8C
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_0224A252:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _0224A252
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	add r4, #0x14
	add r0, r4, #0
	add r1, sp, #0x30
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224A278: .word ov06_02251A54
_0224A27C: .word ov06_02251A8C

	thumb_func_start ov06_0224A280
ov06_0224A280: ; 0x0224A280
	push {r3, r4, r5, lr}
	mov r1, #0x46
	mov r2, #0
	lsl r1, r1, #2
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224A2AC
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224A29C
ov06_0224A29C: ; 0x0224A29C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224A2F4
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224A2AC
ov06_0224A2AC: ; 0x0224A2AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r1, #0x43
	ldr r0, [sp, #8]
	lsl r1, r1, #2
	add r6, r0, r1
	sub r1, #0xc
	ldr r5, _0224A2F0 ; =0x02251ABC
	add r4, r0, r1
	add r7, r0, #4
_0224A2C6:
	str r4, [sp]
	str r6, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [r5]
	ldr r0, [r0]
	mov r2, #0
	add r3, r7, #0
	bl ov05_021E51EC
	ldr r0, [sp, #0xc]
	add r6, r6, #4
	add r0, r0, #1
	add r4, r4, #4
	add r7, #0x54
	add r5, r5, #4
	str r0, [sp, #0xc]
	cmp r0, #3
	blt _0224A2C6
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224A2F0: .word ov06_02251ABC

	thumb_func_start ov06_0224A2F4
ov06_0224A2F4: ; 0x0224A2F4
	push {r4, r5, r6, lr}
	mov r6, #0x43
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #2
_0224A2FE:
	ldr r0, [r5, r6]
	bl ov05_021E4C00
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _0224A2FE
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224A310
ov06_0224A310: ; 0x0224A310
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	add r4, r0, #0
	mov r1, #0xd
	str r4, [sp, #0x14]
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x1c]
	bl sub_02058B5C
	add r0, r5, #0
	bl sub_02058744
	add r1, r0, #1
	add r0, sp, #0x14
	str r0, [sp]
	str r1, [sp, #4]
	ldr r1, _0224A350 ; =0x02251ADC
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	nop
_0224A350: .word ov06_02251ADC

	thumb_func_start ov06_0224A354
ov06_0224A354: ; 0x0224A354
	push {r4, lr}
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x18]
	bl MapObject_GetID
	str r0, [r4]
	ldr r0, [r4, #0x18]
	bl sub_02058450
	str r0, [r4, #4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224A380
ov06_0224A380: ; 0x0224A380
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224A384
ov06_0224A384: ; 0x0224A384
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r4, [r5, #0x18]
	ldr r1, [r5]
	add r6, r0, #0
	ldr r2, [r5, #4]
	add r0, r4, #0
	bl sub_020582A8
	cmp r0, #0
	bne _0224A3A6
	add r0, r6, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0224A3A6:
	mov r0, #0
	mov r1, #2
	str r0, [r5, #8]
	add r0, r4, #0
	lsl r1, r1, #8
	bl MapObject_TestFlagsBits
	cmp r0, #1
	beq _0224A3C8
	add r0, r4, #0
	bl MapObject_GetFieldSystemPtr
	add r1, r4, #0
	bl sub_0204B5FC
	cmp r0, #0
	bne _0224A3D0
_0224A3C8:
	mov r0, #1
	add sp, #0xc
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, pc}
_0224A3D0:
	add r0, r4, #0
	bl MapObject_GetFieldSystemPtr
	add r1, r4, #0
	bl sub_0204B684
	str r0, [r5, #0xc]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02058B5C
	add r0, r6, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224A3F4
ov06_0224A3F4: ; 0x0224A3F4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #1
	beq _0224A43E
	ldr r5, _0224A444 ; =0x02251AB0
	add r3, sp, #0x24
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _0224A448 ; =0x02251B1C
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_0224A414:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _0224A414
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0xc]
	add r2, r0, #4
	mov r0, #0x54
	mul r0, r1
	add r0, r2, r0
	add r1, sp, #0x30
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
_0224A43E:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	nop
_0224A444: .word ov06_02251AB0
_0224A448: .word ov06_02251B1C

	thumb_func_start ov06_0224A44C
ov06_0224A44C: ; 0x0224A44C
	push {r4, lr}
	mov r2, #0
	mov r1, #0xc
	add r3, r2, #0
	add r4, r0, #0
	bl ov05_021E4BE8
	str r4, [r0, #8]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224A460
ov06_0224A460: ; 0x0224A460
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224A4D8
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224A470
ov06_0224A470: ; 0x0224A470
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	bx lr

	thumb_func_start ov06_0224A478
ov06_0224A478: ; 0x0224A478
	push {r3, lr}
	ldr r1, [r0]
	sub r1, r1, #1
	str r1, [r0]
	bpl _0224A486
	bl GF_AssertFail
_0224A486:
	pop {r3, pc}

	thumb_func_start ov06_0224A488
ov06_0224A488: ; 0x0224A488
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _0224A4D0
	mov r0, #1
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	mov r1, #0xb
	mov r2, #0x6d
	bl ov05_021E5078
	ldr r0, [r4, #8]
	mov r1, #0xb
	mov r2, #0x80
	bl ov05_021E50AC
	ldr r0, [r4, #8]
	mov r1, #0xc
	mov r2, #0xe
	mov r3, #1
	bl ov05_021E50D4
	mov r0, #0xc
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224A4D4 ; =0x02251B04
	mov r2, #0xb
	str r0, [sp, #8]
	ldr r0, [r4, #8]
	mov r1, #0xd
	add r3, r2, #0
	bl ov05_021E4EFC
_0224A4D0:
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0224A4D4: .word ov06_02251B04

	thumb_func_start ov06_0224A4D8
ov06_0224A4D8: ; 0x0224A4D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _0224A506
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	mov r1, #0xb
	bl ov05_021E50A0
	ldr r0, [r4, #8]
	mov r1, #0xb
	bl ov05_021E50C8
	ldr r0, [r4, #8]
	mov r1, #0xc
	bl ov05_021E5114
	ldr r0, [r4, #8]
	mov r1, #0xd
	bl ov05_021E506C
_0224A506:
	pop {r4, pc}

	thumb_func_start ov06_0224A508
ov06_0224A508: ; 0x0224A508
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #0
	bne _0224A514
	bl ov06_0224A488
_0224A514:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224A518
ov06_0224A518: ; 0x0224A518
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #0
	bne _0224A524
	bl ov06_0224A4D8
_0224A524:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224A528
ov06_0224A528: ; 0x0224A528
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	add r1, sp, #0x14
	bl ov05_021F1E64
	mov r0, #2
	ldr r1, [sp, #0x1c]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x1c]
	add r0, r4, #0
	mov r1, #0x1e
	str r4, [sp, #8]
	bl ov05_021E4C08
	str r0, [sp, #0xc]
	add r0, sp, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r1, _0224A56C ; =0x02251AC8
	add r0, r4, #0
	add r2, sp, #0x14
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	nop
_0224A56C: .word ov06_02251AC8

	thumb_func_start ov06_0224A570
ov06_0224A570: ; 0x0224A570
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x10]
	bl ov06_0224A508
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0xc]
	mov r1, #0xd
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x10]
	bl ov06_0224A470
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224A5B0
ov06_0224A5B0: ; 0x0224A5B0
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x18]
	bl sub_0201F744
	ldr r0, [r4, #0x10]
	bl ov06_0224A478
	ldr r0, [r4, #0x10]
	bl ov06_0224A518
	pop {r4, pc}

	thumb_func_start ov06_0224A5C8
ov06_0224A5C8: ; 0x0224A5C8
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r5, _0224A620 ; =0x02251AF0
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4, #8]
	cmp r0, #1
	bne _0224A604
	mov r1, #0
	str r1, [r4, #8]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #5
	blt _0224A5FE
	add r0, r2, #0
	bl ov05_021E4DE4
	add sp, #0x14
	pop {r4, r5, pc}
_0224A5FE:
	ldr r0, [r4, #0x18]
	bl sub_0201F86C
_0224A604:
	ldr r1, [r4, #4]
	ldr r0, [r4, #0x18]
	lsl r2, r1, #2
	add r1, sp, #0
	ldr r1, [r1, r2]
	bl sub_0201F854
	cmp r0, #1
	bne _0224A61A
	mov r0, #1
	str r0, [r4, #8]
_0224A61A:
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_0224A620: .word ov06_02251AF0

	thumb_func_start ov06_0224A624
ov06_0224A624: ; 0x0224A624
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x18]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start ov06_0224A63C
ov06_0224A63C: ; 0x0224A63C
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x38
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224A668
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224A658
ov06_0224A658: ; 0x0224A658
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224A6A0
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224A668
ov06_0224A668: ; 0x0224A668
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x28
	bl ov05_021E5294
	ldr r0, [r4]
	add r1, r4, #4
	mov r2, #0x4e
	mov r3, #0
	bl ov05_021E5224
	mov r0, #0x74
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r1, r4, #0
	ldr r0, [r4]
	add r2, r4, #4
	add r4, #0x28
	add r1, #0x14
	add r3, r4, #0
	bl ov05_021E5260
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov06_0224A6A0
ov06_0224A6A0: ; 0x0224A6A0
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	bl ov05_021F52C8
	add r0, r4, #0
	add r4, #0x28
	add r0, #0x14
	add r1, r4, #0
	bl ov05_021F5358
	pop {r4, pc}

	thumb_func_start ov06_0224A6B8
ov06_0224A6B8: ; 0x0224A6B8
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	mov r1, #0xe
	add r4, r0, #0
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r1, sp, #8
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r5, #0
	mov r1, #2
	str r4, [sp, #0x14]
	str r5, [sp, #0x1c]
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224A6F8 ; =0x02251B58
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224A6F8: .word ov06_02251B58

	thumb_func_start ov06_0224A6FC
ov06_0224A6FC: ; 0x0224A6FC
	push {r3, lr}
	bl sub_02064738
	mov r1, #1
	str r1, [r0, #0xc]
	ldr r0, [r0, #0x1c]
	mov r1, #0
	str r1, [r0, #0x14]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224A710
ov06_0224A710: ; 0x0224A710
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r6, r0, #0
	add r5, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #0x90
	str r0, [r2]
	ldr r0, [r5, #0x10]
	mov r2, #1
	mov r3, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r4, [r5, #0x1c]
	ldr r0, [r5, #0x10]
	add r1, r4, #4
	bl ov05_021E5294
	ldr r2, [r5, #0x14]
	add r0, r4, #4
	ldr r1, [r2, #0x18]
	ldr r2, [r2, #0xc]
	bl NNS_G3dAllocAnmObj
	str r0, [r4]
	ldr r3, [r5, #0x14]
	ldr r1, [r3, #0x18]
	ldr r2, [r3, #0xc]
	ldr r3, [r3, #0x10]
	bl NNS_G3dAnmObjInit
	ldr r1, [r5, #0x14]
	add r0, r4, #0
	add r0, #0x18
	add r1, r1, #4
	bl ov05_021F5400
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0x18
	bl NNS_G3dRenderObjAddAnmObj
	ldr r0, [r5, #0x18]
	bl MapObject_GetID
	str r0, [r5, #4]
	ldr r0, [r5, #0x18]
	bl sub_02058450
	str r0, [r5, #8]
	ldr r5, [r5, #0x18]
	add r1, sp, #0xc
	add r0, r5, #0
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02058B84
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r6, #0
	add r1, sp, #0xc
	bl sub_0206476C
	add r4, #0x18
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021F54D0
	mov r0, #1
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0224A7C8
ov06_0224A7C8: ; 0x0224A7C8
	push {r4, lr}
	ldr r4, [r1, #0x1c]
	ldr r1, [r4]
	add r0, r4, #4
	bl NNS_G3dFreeAnmObj
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224A7DC
ov06_0224A7DC: ; 0x0224A7DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r1, [r5, #0xc]
	add r7, r0, #0
	ldr r4, [r5, #0x1c]
	ldr r6, [r5, #0x18]
	cmp r1, #0
	bne _0224A806
	ldr r1, [r5, #4]
	ldr r2, [r5, #8]
	add r0, r6, #0
	bl sub_020582A8
	cmp r0, #0
	bne _0224A828
	add r0, r7, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224A806:
	ldr r1, [r4]
	ldr r2, [r4, #0x14]
	ldr r1, [r1, #8]
	ldrh r1, [r1, #4]
	lsl r3, r1, #0xc
	mov r1, #1
	lsl r1, r1, #0xc
	add r1, r2, r1
	str r1, [r4, #0x14]
	cmp r1, r3
	ble _0224A824
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224A824:
	ldr r0, [r4]
	str r1, [r0]
_0224A828:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _0224A86C
	add r0, r6, #0
	add r1, sp, #0xc
	bl sub_02058B5C
	add r0, r6, #0
	add r1, sp, #0
	bl sub_02058B84
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r7, #0
	add r1, sp, #0xc
	bl sub_0206476C
	add r4, #0x18
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r4, #0
	bl ov05_021F54D0
_0224A86C:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224A870
ov06_0224A870: ; 0x0224A870
	ldr r0, [r1, #0x1c]
	ldr r3, _0224A878 ; =ov05_021F5430
	add r0, #0x18
	bx r3
	.align 2, 0
_0224A878: .word ov05_021F5430

	thumb_func_start ov06_0224A87C
ov06_0224A87C: ; 0x0224A87C
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x60
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224A8A8
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224A898
ov06_0224A898: ; 0x0224A898
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224A8C8
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224A8A8
ov06_0224A8A8: ; 0x0224A8A8
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x58
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x5c
	str r0, [sp, #4]
	ldr r0, [r3]
	mov r1, #0x4f
	mov r2, #0
	add r3, r3, #4
	bl ov05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov06_0224A8C8
ov06_0224A8C8: ; 0x0224A8C8
	ldr r3, _0224A8D0 ; =ov05_021E4C00
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_0224A8D0: .word ov05_021E4C00

	thumb_func_start ov06_0224A8D4
ov06_0224A8D4: ; 0x0224A8D4
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	mov r1, #0xf
	add r4, r0, #0
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r1, sp, #8
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r5, #0
	mov r1, #2
	str r4, [sp, #0x14]
	str r5, [sp, #0x1c]
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224A914 ; =0x02251B6C
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224A914: .word ov06_02251B6C

	thumb_func_start ov06_0224A918
ov06_0224A918: ; 0x0224A918
	push {r4, lr}
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x14]
	bl MapObject_GetID
	str r0, [r4, #4]
	ldr r0, [r4, #0x14]
	bl sub_02058450
	str r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224A944
ov06_0224A944: ; 0x0224A944
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224A948
ov06_0224A948: ; 0x0224A948
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r2, r1, #0
	ldr r5, [r2, #0x14]
	ldr r1, [r2, #4]
	add r4, r0, #0
	ldr r2, [r2, #8]
	add r0, r5, #0
	bl sub_020582A8
	cmp r0, #0
	bne _0224A96A
	add r0, r4, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, pc}
_0224A96A:
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02058B84
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r1, sp, #0xc
	bl sub_0206476C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224A9A0
ov06_0224A9A0: ; 0x0224A9A0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	ldr r5, _0224A9E0 ; =0x02251B40
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x24
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _0224A9E4 ; =0x02251BB8
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_0224A9BA:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _0224A9BA
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	ldr r0, [r4, #0x10]
	add r1, sp, #0x30
	add r0, r0, #4
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224A9E0: .word ov06_02251B40
_0224A9E4: .word ov06_02251BB8

	thumb_func_start ov06_0224A9E8
ov06_0224A9E8: ; 0x0224A9E8
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x60
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224AA14
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224AA04
ov06_0224AA04: ; 0x0224AA04
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224AA34
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224AA14
ov06_0224AA14: ; 0x0224AA14
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x58
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x5c
	str r0, [sp, #4]
	ldr r0, [r3]
	mov r1, #0x6e
	mov r2, #0
	add r3, r3, #4
	bl ov05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov06_0224AA34
ov06_0224AA34: ; 0x0224AA34
	ldr r3, _0224AA3C ; =ov05_021E4C00
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_0224AA3C: .word ov05_021E4C00

	thumb_func_start ov06_0224AA40
ov06_0224AA40: ; 0x0224AA40
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	bl ov05_021E4C24
	mov r1, #0x1f
	add r4, r0, #0
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r1, sp, #8
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r5, #0
	mov r1, #2
	str r4, [sp, #0x14]
	str r5, [sp, #0x1c]
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224AA80 ; =0x02251B80
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224AA80: .word ov06_02251B80

	thumb_func_start ov06_0224AA84
ov06_0224AA84: ; 0x0224AA84
	push {r4, lr}
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0xc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x14]
	bl MapObject_GetID
	str r0, [r4, #4]
	ldr r0, [r4, #0x14]
	bl sub_02058450
	str r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224AAB0
ov06_0224AAB0: ; 0x0224AAB0
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224AAB4
ov06_0224AAB4: ; 0x0224AAB4
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r2, r1, #0
	ldr r5, [r2, #0x14]
	ldr r1, [r2, #4]
	add r4, r0, #0
	ldr r2, [r2, #8]
	add r0, r5, #0
	bl sub_020582A8
	cmp r0, #0
	bne _0224AAD6
	add r0, r4, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, pc}
_0224AAD6:
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02058B84
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r1, sp, #0xc
	bl sub_0206476C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224AB0C
ov06_0224AB0C: ; 0x0224AB0C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	ldr r5, _0224AB4C ; =0x02251B4C
	add r2, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x24
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _0224AB50 ; =0x02251B94
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_0224AB26:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _0224AB26
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	ldr r0, [r4, #0x10]
	add r1, sp, #0x30
	add r0, r0, #4
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224AB4C: .word ov06_02251B4C
_0224AB50: .word ov06_02251B94

	thumb_func_start ov06_0224AB54
ov06_0224AB54: ; 0x0224AB54
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x60
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224AB80
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224AB70
ov06_0224AB70: ; 0x0224AB70
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224ABA0
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224AB80
ov06_0224AB80: ; 0x0224AB80
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x58
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x5c
	str r0, [sp, #4]
	ldr r0, [r3]
	mov r1, #0x51
	mov r2, #0
	add r3, r3, #4
	bl ov05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov06_0224ABA0
ov06_0224ABA0: ; 0x0224ABA0
	ldr r3, _0224ABA8 ; =ov05_021E4C00
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_0224ABA8: .word ov05_021E4C00

	thumb_func_start ov06_0224ABAC
ov06_0224ABAC: ; 0x0224ABAC
	push {r4, r5, r6, lr}
	sub sp, #0x30
	add r4, r1, #0
	add r6, r2, #0
	add r2, sp, #0x14
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r5, r0, #0
	str r1, [r2, #8]
	str r3, [sp, #0x20]
	bl ov05_021E4C24
	mov r1, #0x11
	str r0, [sp, #0x24]
	bl ov05_021E4C08
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x40]
	str r5, [sp, #0x2c]
	cmp r0, #0
	bne _0224ABF6
	add r0, r5, #0
	bl MapObject_GetFieldSystemPtr
	mov r1, #2
	lsl r2, r4, #0x10
	lsl r1, r1, #0xe
	add r2, r2, r1
	str r2, [sp, #0x14]
	lsl r2, r6, #0x10
	add r1, r2, r1
	str r1, [sp, #0x1c]
	add r1, sp, #0x14
	bl sub_02059E9C
	b _0224AC12
_0224ABF6:
	ldr r3, _0224AC30 ; =0x02251BDC
	add r2, sp, #8
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x14
	str r0, [r2]
	add r0, r5, #0
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #8
	bl sub_02058BB4
_0224AC12:
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #0x20
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x24]
	ldr r1, _0224AC34 ; =0x02251BF4
	ldr r3, [sp, #0x40]
	add r2, sp, #0x14
	bl ov05_021E4DC4
	add sp, #0x30
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224AC30: .word ov06_02251BDC
_0224AC34: .word ov06_02251BF4

	thumb_func_start ov06_0224AC38
ov06_0224AC38: ; 0x0224AC38
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl sub_0206475C
	add r7, r0, #0
	add r2, r5, #0
	add r3, r7, #0
	ldr r4, [r7, #0xc]
	add r2, #0x24
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r4, #0
	bl MapObject_GetID
	str r0, [r5, #0xc]
	add r0, r4, #0
	bl sub_02058450
	str r0, [r5, #0x10]
	ldr r0, [r7]
	str r0, [r5, #8]
	add r0, r6, #0
	bl sub_02064754
	str r0, [r5, #0x18]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [r5, #0x1c]
	lsr r0, r0, #2
	str r0, [r5, #0x20]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224AC80
ov06_0224AC80: ; 0x0224AC80
	push {lr}
	sub sp, #0xc
	ldr r0, [r1, #0x30]
	add r1, sp, #0
	mov r2, #0
	str r2, [r1]
	str r2, [r1, #4]
	str r2, [r1, #8]
	bl sub_02058BB4
	add sp, #0xc
	pop {pc}

	thumb_func_start ov06_0224AC98
ov06_0224AC98: ; 0x0224AC98
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r4, [r5, #0x30]
	ldr r1, [r5, #0xc]
	add r6, r0, #0
	ldr r2, [r5, #0x10]
	add r0, r4, #0
	bl sub_020582A8
	cmp r0, #0
	bne _0224ACBA
	add r0, r6, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r4, r5, r6, pc}
_0224ACBA:
	mov r0, #0
	str r0, [r5]
	add r0, r4, #0
	bl sub_020584C4
	mov r1, #0
	mvn r1, r1
	str r0, [r5, #4]
	cmp r0, r1
	bne _0224ACD6
	mov r0, #1
	add sp, #0x18
	str r0, [r5]
	pop {r4, r5, r6, pc}
_0224ACD6:
	ldr r1, [r5, #0x18]
	cmp r1, #0
	beq _0224AD40
	str r0, [r5, #8]
	ldr r1, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	add r2, r1, r0
	mov r1, #1
	lsl r1, r1, #0xe
	str r2, [r5, #0x1c]
	cmp r2, r1
	blt _0224ACF8
	str r1, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	neg r0, r0
	str r0, [r5, #0x20]
	b _0224AD06
_0224ACF8:
	lsr r0, r1, #2
	cmp r2, r0
	bgt _0224AD06
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	neg r0, r0
	str r0, [r5, #0x20]
_0224AD06:
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #7
	ldr r1, [r5, #0x1c]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x10]
	mov r0, #1
	lsl r0, r0, #0xe
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r1, sp, #0xc
	bl sub_02058BB4
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02058B5C
	mov r0, #1
	ldr r1, [r5, #0x1c]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	ldr r2, [sp, #4]
	add r1, sp, #0
	add r0, r2, r0
	str r0, [sp, #4]
	add r0, r6, #0
	bl sub_0206476C
_0224AD40:
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0224AD44
ov06_0224AD44: ; 0x0224AD44
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	beq _0224ADE6
	mov r0, #0
	ldr r1, [r4, #8]
	mvn r0, r0
	cmp r1, r0
	beq _0224ADE6
	ldr r0, [r4, #0x14]
	ldr r3, _0224ADEC ; =0x02251BE8
	add r0, r0, #1
	str r0, [r4, #0x14]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x24
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _0224ADF0 ; =0x02251C08
	str r0, [r2]
	add r3, sp, #0
	mov r2, #4
_0224AD74:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224AD74
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _0224ADD0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224AD92: ; jump table
	.short _0224AD9A - _0224AD92 - 2 ; case 0
	.short _0224ADA8 - _0224AD92 - 2 ; case 1
	.short _0224ADB6 - _0224AD92 - 2 ; case 2
	.short _0224ADC4 - _0224AD92 - 2 ; case 3
_0224AD9A:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0xb4
	add r3, r1, #0
	bl sub_0201CB20
	b _0224ADD0
_0224ADA8:
	mov r1, #0
	add r0, sp, #0
	add r2, r1, #0
	add r3, r1, #0
	bl sub_0201CB20
	b _0224ADD0
_0224ADB6:
	mov r1, #0
	ldr r2, _0224ADF4 ; =0x0000010E
	add r0, sp, #0
	add r3, r1, #0
	bl sub_0201CB20
	b _0224ADD0
_0224ADC4:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0x5a
	add r3, r1, #0
	bl sub_0201CB20
_0224ADD0:
	add r0, r6, #0
	add r1, sp, #0x30
	bl sub_0206477C
	ldr r0, [r4, #0x2c]
	add r1, sp, #0x30
	add r0, r0, #4
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
_0224ADE6:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	nop
_0224ADEC: .word ov06_02251BE8
_0224ADF0: .word ov06_02251C08
_0224ADF4: .word 0x0000010E

	thumb_func_start ov06_0224ADF8
ov06_0224ADF8: ; 0x0224ADF8
	push {r4, lr}
	add r4, r1, #0
	bl sub_02064738
	mov r1, #1
	str r4, [r0, #0x18]
	lsl r1, r1, #0xc
	str r1, [r0, #0x1c]
	lsr r1, r1, #2
	str r1, [r0, #0x20]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224AE10
ov06_0224AE10: ; 0x0224AE10
	push {r4, lr}
	mov r2, #0
	mov r1, #0x70
	add r3, r2, #0
	add r4, r0, #0
	bl ov05_021E4BE8
	str r4, [r0, #0x10]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224AE24
ov06_0224AE24: ; 0x0224AE24
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224AE78
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224AE34
ov06_0224AE34: ; 0x0224AE34
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	bx lr

	thumb_func_start ov06_0224AE3C
ov06_0224AE3C: ; 0x0224AE3C
	push {r3, lr}
	ldr r1, [r0]
	sub r1, r1, #1
	str r1, [r0]
	bpl _0224AE4A
	bl GF_AssertFail
_0224AE4A:
	pop {r3, pc}

	thumb_func_start ov06_0224AE4C
ov06_0224AE4C: ; 0x0224AE4C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _0224AE72
	ldr r0, [r4, #0x10]
	mov r1, #0x52
	mov r2, #1
	bl ov05_021E4C6C
	str r0, [r4, #0x6c]
	ldr r0, _0224AE74 ; =ov06_0224AEC0
	add r1, r4, #0
	mov r2, #0x80
	bl sub_0200CA60
	str r0, [r4, #0xc]
	mov r0, #1
	str r0, [r4, #4]
_0224AE72:
	pop {r4, pc}
	.align 2, 0
_0224AE74: .word ov06_0224AEC0

	thumb_func_start ov06_0224AE78
ov06_0224AE78: ; 0x0224AE78
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0224AE8C
	bl sub_0200CAB4
	mov r0, #0
	str r0, [r4, #0xc]
	str r0, [r4, #8]
_0224AE8C:
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _0224AE9C
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4, #0x6c]
	bl ov05_021E4C00
_0224AE9C:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224AEA0
ov06_0224AEA0: ; 0x0224AEA0
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #0
	bne _0224AEAC
	bl ov06_0224AE4C
_0224AEAC:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224AEB0
ov06_0224AEB0: ; 0x0224AEB0
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #0
	bne _0224AEBC
	bl ov06_0224AE78
_0224AEBC:
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224AEC0
ov06_0224AEC0: ; 0x0224AEC0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r2, r4, #0
	add r3, r4, #0
	ldr r0, [r4, #0x10]
	add r1, #0x14
	add r2, #0x68
	add r3, #0x6c
	bl ov05_021E5198
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #1
	str r0, [r4, #8]
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224AEE8
ov06_0224AEE8: ; 0x0224AEE8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r6, r1, #0
	add r7, r2, #0
	add r2, sp, #0xc
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	str r3, [sp, #8]
	add r5, r0, #0
	str r1, [r2, #8]
	bl ov05_021E4C24
	add r4, r0, #0
	ldr r0, [sp, #8]
	str r4, [sp, #0x1c]
	str r0, [sp, #0x18]
	add r0, r5, #0
	bl MapObject_GetFieldSystemPtr
	str r0, [sp, #0x20]
	add r0, r4, #0
	mov r1, #0x12
	bl ov05_021E4C08
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x40]
	str r5, [sp, #0x28]
	cmp r0, #0
	bne _0224AF3E
	mov r0, #2
	lsl r1, r6, #0x10
	lsl r0, r0, #0xe
	add r1, r1, r0
	str r1, [sp, #0xc]
	lsl r1, r7, #0x10
	add r0, r1, r0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	add r1, sp, #0xc
	bl sub_02059E9C
	b _0224AF46
_0224AF3E:
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_02058B5C
_0224AF46:
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #0x18
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224AF64 ; =0x02251C38
	ldr r3, [sp, #0x40]
	add r0, r4, #0
	add r2, sp, #0xc
	bl ov05_021E4DC4
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224AF64: .word ov06_02251C38

	thumb_func_start ov06_0224AF68
ov06_0224AF68: ; 0x0224AF68
	push {r4, lr}
	add r4, r1, #0
	bl sub_02064738
	str r4, [r0, #0xc]
	pop {r4, pc}

	thumb_func_start ov06_0224AF74
ov06_0224AF74: ; 0x0224AF74
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r2, r0, #0
	add r6, r2, #0
	add r3, r4, #0
	ldmia r6!, {r0, r1}
	add r3, #0x10
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	str r0, [r3]
	ldr r0, [r2]
	str r0, [r4, #4]
	add r0, r5, #0
	bl sub_02064754
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x1c]
	bl ov06_0224AEA0
	ldr r0, [r4, #0x1c]
	bl ov06_0224AE34
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224AFB0
ov06_0224AFB0: ; 0x0224AFB0
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x1c]
	bl ov06_0224AE3C
	ldr r0, [r4, #0x1c]
	bl ov06_0224AEB0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224AFC4
ov06_0224AFC4: ; 0x0224AFC4
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, [r1, #0xc]
	ldr r4, [r1, #0x20]
	cmp r0, #0
	beq _0224AFF2
	add r1, sp, #0xc
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r4, #0
	bl sub_02058BB4
	add r0, r4, #0
	add r1, sp, #0
	bl sub_02058B5C
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
_0224AFF2:
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224AFF8
ov06_0224AFF8: ; 0x0224AFF8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	beq _0224B098
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _0224B098
	ldr r0, [r4, #8]
	ldr r3, _0224B09C ; =0x02251C2C
	add r0, r0, #1
	str r0, [r4, #8]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x24
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _0224B0A0 ; =0x02251C4C
	str r0, [r2]
	add r3, sp, #0
	mov r2, #4
_0224B026:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224B026
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4, #4]
	cmp r0, #3
	bhi _0224B082
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224B044: ; jump table
	.short _0224B04C - _0224B044 - 2 ; case 0
	.short _0224B05A - _0224B044 - 2 ; case 1
	.short _0224B068 - _0224B044 - 2 ; case 2
	.short _0224B076 - _0224B044 - 2 ; case 3
_0224B04C:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0xb4
	add r3, r1, #0
	bl sub_0201CB20
	b _0224B082
_0224B05A:
	mov r1, #0
	add r0, sp, #0
	add r2, r1, #0
	add r3, r1, #0
	bl sub_0201CB20
	b _0224B082
_0224B068:
	mov r1, #0
	ldr r2, _0224B0A4 ; =0x0000010E
	add r0, sp, #0
	add r3, r1, #0
	bl sub_0201CB20
	b _0224B082
_0224B076:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0x5a
	add r3, r1, #0
	bl sub_0201CB20
_0224B082:
	add r0, r6, #0
	add r1, sp, #0x30
	bl sub_0206477C
	ldr r0, [r4, #0x1c]
	add r1, sp, #0x30
	add r0, #0x14
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
_0224B098:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224B09C: .word ov06_02251C2C
_0224B0A0: .word ov06_02251C4C
_0224B0A4: .word 0x0000010E

	thumb_func_start ov06_0224B0A8
ov06_0224B0A8: ; 0x0224B0A8
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x38
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224B0D4
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224B0C4
ov06_0224B0C4: ; 0x0224B0C4
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224B10C
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224B0D4
ov06_0224B0D4: ; 0x0224B0D4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x28
	bl ov05_021E5294
	ldr r0, [r4]
	add r1, r4, #4
	mov r2, #0xf
	mov r3, #0
	bl ov05_021E5224
	mov r0, #0x6f
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r1, r4, #0
	ldr r0, [r4]
	add r2, r4, #4
	add r4, #0x28
	add r1, #0x14
	add r3, r4, #0
	bl ov05_021E5260
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov06_0224B10C
ov06_0224B10C: ; 0x0224B10C
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	bl ov05_021F52C8
	add r0, r4, #0
	add r4, #0x28
	add r0, #0x14
	add r1, r4, #0
	bl ov05_021F5358
	pop {r4, pc}

	thumb_func_start ov06_0224B124
ov06_0224B124: ; 0x0224B124
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	bl ov05_021E4C24
	mov r1, #0x13
	str r0, [sp, #8]
	bl ov05_021E4C08
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r1, r7, #0
	add r2, sp, #0x10
	bl sub_02059E60
	mov r0, #1
	ldr r2, [sp, #0x18]
	lsl r1, r4, #3
	lsl r0, r0, #0xc
	add r0, r1, r0
	add r0, r2, r0
	str r0, [sp, #0x18]
	add r0, r5, #0
	bl sub_02058B1C
	lsl r1, r0, #0xf
	mov r0, #2
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #8
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, _0224B184 ; =0x02251C70
	add r2, sp, #0x10
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224B184: .word ov06_02251C70

	thumb_func_start ov06_0224B188
ov06_0224B188: ; 0x0224B188
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	bl sub_0206475C
	ldr r1, [r0]
	ldr r0, [r0, #4]
	mov r2, #1
	str r1, [r5, #4]
	str r0, [r5, #8]
	ldr r0, [r0]
	mov r1, #0x90
	mov r3, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r4, [r5]
	ldr r0, [r5, #4]
	add r1, r4, #4
	bl ov05_021E5294
	ldr r2, [r5, #8]
	add r0, r4, #4
	ldr r1, [r2, #0x18]
	ldr r2, [r2, #0xc]
	bl NNS_G3dAllocAnmObj
	str r0, [r4]
	ldr r3, [r5, #8]
	ldr r1, [r3, #0x18]
	ldr r2, [r3, #0xc]
	ldr r3, [r3, #0x10]
	bl NNS_G3dAnmObjInit
	ldr r1, [r5, #8]
	add r0, r4, #0
	add r0, #0x18
	add r1, r1, #4
	bl ov05_021F5400
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0x18
	bl NNS_G3dRenderObjAddAnmObj
	add r0, r6, #0
	add r1, sp, #0
	bl sub_0206477C
	add r4, #0x18
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl ov05_021F54D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}

	thumb_func_start ov06_0224B200
ov06_0224B200: ; 0x0224B200
	push {r4, lr}
	ldr r4, [r1]
	ldr r1, [r4]
	add r0, r4, #4
	bl NNS_G3dFreeAnmObj
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224B214
ov06_0224B214: ; 0x0224B214
	push {r4, lr}
	ldr r1, [r1]
	ldr r2, [r1]
	ldr r3, [r1, #0x14]
	ldr r2, [r2, #8]
	ldrh r2, [r2, #4]
	lsl r4, r2, #0xc
	mov r2, #1
	lsl r2, r2, #0xc
	add r2, r3, r2
	str r2, [r1, #0x14]
	cmp r2, r4
	ble _0224B234
	bl ov05_021E4DE4
	pop {r4, pc}
_0224B234:
	ldr r0, [r1]
	str r2, [r0]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224B23C
ov06_0224B23C: ; 0x0224B23C
	ldr r0, [r1]
	ldr r3, _0224B244 ; =ov05_021F5430
	add r0, #0x18
	bx r3
	.align 2, 0
_0224B244: .word ov05_021F5430

	thumb_func_start ov06_0224B248
ov06_0224B248: ; 0x0224B248
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x38
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224B274
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224B264
ov06_0224B264: ; 0x0224B264
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224B2AC
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224B274
ov06_0224B274: ; 0x0224B274
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x28
	bl ov05_021E5294
	ldr r0, [r4]
	add r1, r4, #4
	mov r2, #0x10
	mov r3, #0
	bl ov05_021E5224
	mov r0, #0x70
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r1, r4, #0
	ldr r0, [r4]
	add r2, r4, #4
	add r4, #0x28
	add r1, #0x14
	add r3, r4, #0
	bl ov05_021E5260
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov06_0224B2AC
ov06_0224B2AC: ; 0x0224B2AC
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	bl ov05_021F52C8
	add r0, r4, #0
	add r4, #0x28
	add r0, #0x14
	add r1, r4, #0
	bl ov05_021F5358
	pop {r4, pc}

	thumb_func_start ov06_0224B2C4
ov06_0224B2C4: ; 0x0224B2C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	bl ov05_021E4C24
	mov r1, #0x14
	str r0, [sp, #8]
	bl ov05_021E4C08
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r1, r7, #0
	add r2, sp, #0x10
	bl sub_02059E60
	ldr r1, [sp, #0x18]
	lsl r0, r4, #3
	add r0, r1, r0
	str r0, [sp, #0x18]
	add r0, r5, #0
	bl sub_02058B1C
	lsl r1, r0, #0xf
	mov r0, #2
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #8
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, _0224B320 ; =0x02251C84
	add r2, sp, #0x10
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0224B320: .word ov06_02251C84

	thumb_func_start ov06_0224B324
ov06_0224B324: ; 0x0224B324
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	bl sub_0206475C
	ldr r1, [r0]
	ldr r0, [r0, #4]
	mov r2, #1
	str r1, [r5, #4]
	str r0, [r5, #8]
	ldr r0, [r0]
	mov r1, #0x90
	mov r3, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r4, [r5]
	ldr r0, [r5, #4]
	add r1, r4, #4
	bl ov05_021E5294
	ldr r2, [r5, #8]
	add r0, r4, #4
	ldr r1, [r2, #0x18]
	ldr r2, [r2, #0xc]
	bl NNS_G3dAllocAnmObj
	str r0, [r4]
	ldr r3, [r5, #8]
	ldr r1, [r3, #0x18]
	ldr r2, [r3, #0xc]
	ldr r3, [r3, #0x10]
	bl NNS_G3dAnmObjInit
	ldr r1, [r5, #8]
	add r0, r4, #0
	add r0, #0x18
	add r1, r1, #4
	bl ov05_021F5400
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0x18
	bl NNS_G3dRenderObjAddAnmObj
	add r0, r6, #0
	add r1, sp, #0
	bl sub_0206477C
	add r4, #0x18
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl ov05_021F54D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}

	thumb_func_start ov06_0224B39C
ov06_0224B39C: ; 0x0224B39C
	push {r4, lr}
	ldr r4, [r1]
	ldr r1, [r4]
	add r0, r4, #4
	bl NNS_G3dFreeAnmObj
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224B3B0
ov06_0224B3B0: ; 0x0224B3B0
	push {r4, lr}
	ldr r1, [r1]
	ldr r2, [r1]
	ldr r3, [r1, #0x14]
	ldr r2, [r2, #8]
	ldrh r2, [r2, #4]
	lsl r4, r2, #0xc
	mov r2, #1
	lsl r2, r2, #0xc
	add r2, r3, r2
	str r2, [r1, #0x14]
	cmp r2, r4
	ble _0224B3D0
	bl ov05_021E4DE4
	pop {r4, pc}
_0224B3D0:
	ldr r0, [r1]
	str r2, [r0]
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224B3D8
ov06_0224B3D8: ; 0x0224B3D8
	ldr r0, [r1]
	ldr r3, _0224B3E0 ; =ov05_021F5430
	add r0, #0x18
	bx r3
	.align 2, 0
_0224B3E0: .word ov05_021F5430

	thumb_func_start ov06_0224B3E4
ov06_0224B3E4: ; 0x0224B3E4
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224B410
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224B400
ov06_0224B400: ; 0x0224B400
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224B4F0
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224B410
ov06_0224B410: ; 0x0224B410
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x53
	bl ov05_021E5078
	ldr r0, [r4]
	mov r1, #5
	mov r2, #0x54
	bl ov05_021E5078
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x75
	bl ov05_021E50AC
	ldr r0, [r4]
	mov r1, #3
	mov r2, #0x76
	bl ov05_021E50AC
	ldr r0, [r4]
	mov r1, #4
	mov r2, #0x77
	bl ov05_021E50AC
	ldr r0, [r4]
	mov r1, #5
	mov r2, #0x78
	bl ov05_021E50AC
	mov r1, #0
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #1
	bl ov05_021E50D4
	mov r2, #1
	ldr r0, [r4]
	mov r1, #4
	add r3, r2, #0
	bl ov05_021E50D4
	ldr r0, [r4]
	mov r1, #5
	mov r2, #2
	mov r3, #1
	bl ov05_021E50D4
	ldr r0, [r4]
	mov r1, #6
	mov r2, #3
	mov r3, #1
	bl ov05_021E50D4
	mov r1, #0
	str r1, [sp]
	ldr r0, _0224B4E0 ; =0x02251CEC
	str r1, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	add r2, r1, #0
	add r3, r1, #0
	bl ov05_021E4EFC
	mov r0, #4
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224B4E4 ; =0x02251D04
	mov r1, #5
	str r0, [sp, #8]
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #3
	bl ov05_021E4EFC
	mov r2, #5
	str r2, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224B4E8 ; =0x02251CD4
	mov r1, #6
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r3, #4
	bl ov05_021E4EFC
	mov r0, #6
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224B4EC ; =0x02251D1C
	mov r2, #5
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #7
	add r3, r2, #0
	bl ov05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0224B4E0: .word ov06_02251CEC
_0224B4E4: .word ov06_02251D04
_0224B4E8: .word ov06_02251CD4
_0224B4EC: .word ov06_02251D1C

	thumb_func_start ov06_0224B4F0
ov06_0224B4F0: ; 0x0224B4F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #0
	bl ov05_021E50A0
	ldr r0, [r4]
	mov r1, #5
	bl ov05_021E50A0
	ldr r0, [r4]
	mov r1, #0
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #3
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #4
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #5
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #0
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #4
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #5
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #6
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #0
	bl ov05_021E506C
	ldr r0, [r4]
	mov r1, #5
	bl ov05_021E506C
	ldr r0, [r4]
	mov r1, #6
	bl ov05_021E506C
	ldr r0, [r4]
	mov r1, #7
	bl ov05_021E506C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224B568
ov06_0224B568: ; 0x0224B568
	push {r4, r5, r6, lr}
	sub sp, #0x30
	add r5, r0, #0
	add r6, r1, #0
	bl ov05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl sub_02058B2C
	str r0, [sp, #8]
	add r0, r5, #0
	bl sub_02058B3C
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl sub_02058B4C
	str r0, [sp, #0x10]
	add r0, r4, #0
	str r4, [sp, #0x18]
	bl ov05_021E4C20
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x15
	bl ov05_021E4C08
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, sp, #0x24
	str r5, [sp, #0x20]
	bl sub_02058B5C
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #8
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224B5CC ; =0x02251C98
	add r0, r4, #0
	add r2, sp, #0x24
	add r3, r6, #0
	bl ov05_021E4DC4
	add sp, #0x30
	pop {r4, r5, r6, pc}
	nop
_0224B5CC: .word ov06_02251C98

	thumb_func_start ov06_0224B5D0
ov06_0224B5D0: ; 0x0224B5D0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x18
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x30]
	bl sub_0205845C
	str r0, [r4, #4]
	ldr r0, [r4, #0x30]
	bl MapObject_GetID
	str r0, [r4, #8]
	ldr r0, [r4, #0x30]
	bl sub_02058450
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x18]
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [r4, #0x30]
	bl sub_02058B80
	str r0, [sp, #4]
	ldr r0, [r4, #0x24]
	add r1, sp, #0
	bl sub_02059E9C
	str r0, [r4, #0x14]
	mov r0, #2
	ldr r1, [sp]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp]
	mov r0, #0x12
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #0x28]
	mov r1, #0
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x34]
	add r0, r5, #0
	bl sub_02064754
	cmp r0, #0
	bne _0224B65E
	mov r0, #1
	str r0, [r4]
_0224B65E:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224B664
ov06_0224B664: ; 0x0224B664
	ldr r3, _0224B66C ; =sub_0201F744
	ldr r0, [r1, #0x34]
	bx r3
	nop
_0224B66C: .word sub_0201F744

	thumb_func_start ov06_0224B670
ov06_0224B670: ; 0x0224B670
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	ldr r6, [r4, #0x30]
	ldr r1, [r4, #4]
	add r5, r0, #0
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	add r0, r6, #0
	bl sub_020582F8
	cmp r0, #0
	bne _0224B694
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224B694:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _0224B6CC
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_0206477C
	ldr r0, [r4, #0x18]
	add r1, sp, #0
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	str r0, [sp, #4]
	ldr r0, [r4, #0x24]
	bl sub_02059E9C
	str r0, [r4, #0x14]
	cmp r0, #1
	bne _0224B6CC
	ldr r0, [sp, #4]
	add r1, sp, #0xc
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl sub_0206476C
_0224B6CC:
	ldr r0, [r4]
	cmp r0, #0
	beq _0224B6DE
	cmp r0, #1
	beq _0224B702
	cmp r0, #2
	beq _0224B710
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224B6DE:
	mov r1, #1
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xc
	bl sub_0201F854
	ldr r0, [r4, #0x34]
	bl sub_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r0, #0xc
	blt _0224B74A
	mov r0, #1
	add sp, #0x18
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0224B702:
	mov r1, #3
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xe
	bl sub_0201F86C
	mov r0, #2
	str r0, [r4]
_0224B710:
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	add r0, r6, #0
	bl sub_020582F8
	cmp r0, #0
	bne _0224B72A
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224B72A:
	add r0, r6, #0
	bl sub_02058B2C
	add r7, r0, #0
	add r0, r6, #0
	bl sub_02058B4C
	ldr r1, [r4, #0x18]
	cmp r1, r7
	bne _0224B744
	ldr r1, [r4, #0x20]
	cmp r1, r0
	beq _0224B74A
_0224B744:
	add r0, r5, #0
	bl ov05_021E4DE4
_0224B74A:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224B750
ov06_0224B750: ; 0x0224B750
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	bl sub_020582F8
	cmp r0, #0
	bne _0224B772
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r4, r5, pc}
_0224B772:
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x34]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224B788
ov06_0224B788: ; 0x0224B788
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #8
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0
	str r0, [r2]
	add r0, r5, #0
	bl sub_0206477C
	ldr r0, [r4, #0x14]
	mov r1, #0
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x1c]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224B7C0
ov06_0224B7C0: ; 0x0224B7C0
	ldr r3, _0224B7C8 ; =sub_0201F744
	ldr r0, [r1, #0x1c]
	bx r3
	nop
_0224B7C8: .word sub_0201F744

	thumb_func_start ov06_0224B7CC
ov06_0224B7CC: ; 0x0224B7CC
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0224B7DA
	cmp r0, #1
	pop {r4, pc}
_0224B7DA:
	mov r1, #1
	ldr r0, [r4, #0x1c]
	lsl r1, r1, #0xc
	bl sub_0201F854
	ldr r0, [r4, #0x1c]
	bl sub_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r0, #0xc
	blt _0224B7FC
	mov r0, #1
	str r0, [r4, #4]
	str r0, [r4]
_0224B7FC:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224B800
ov06_0224B800: ; 0x0224B800
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x1c]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start ov06_0224B818
ov06_0224B818: ; 0x0224B818
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	ldr r6, [r0, #0x3c]
	add r5, r1, #0
	add r4, r2, #0
	str r0, [sp, #0x10]
	add r0, r6, #0
	mov r1, #0x15
	add r7, r3, #0
	str r5, [sp, #8]
	str r4, [sp, #0xc]
	str r6, [sp, #0x14]
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	mov r0, #2
	lsl r1, r5, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	mov r0, #9
	lsl r1, r4, #0x10
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x24]
	add r0, sp, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r1, _0224B868 ; =0x02251CC0
	add r0, r6, #0
	add r2, sp, #0x1c
	add r3, r7, #0
	bl ov05_021E4DC4
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224B868: .word ov06_02251CC0

	thumb_func_start ov06_0224B86C
ov06_0224B86C: ; 0x0224B86C
	push {r3, lr}
	bl sub_02064738
	ldr r0, [r0, #4]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224B878
ov06_0224B878: ; 0x0224B878
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x10
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	bl sub_02064754
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x10]
	lsl r1, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp]
	ldr r0, [r4, #0x14]
	lsl r1, r0, #0x10
	mov r0, #9
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	add r1, sp, #0
	bl sub_02059E9C
	mov r0, #1
	ldr r1, [sp, #4]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _0224B8E2
	cmp r0, #1
	beq _0224B8E6
	cmp r0, #2
	b _0224B8EA
_0224B8E2:
	mov r1, #5
	b _0224B8EC
_0224B8E6:
	mov r1, #6
	b _0224B8EC
_0224B8EA:
	mov r1, #7
_0224B8EC:
	ldr r0, [r4, #0x1c]
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x24]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224B8FC
ov06_0224B8FC: ; 0x0224B8FC
	ldr r3, _0224B904 ; =sub_0201F744
	ldr r0, [r1, #0x24]
	bx r3
	nop
_0224B904: .word sub_0201F744

	thumb_func_start ov06_0224B908
ov06_0224B908: ; 0x0224B908
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0224B916
	cmp r0, #1
	pop {r4, pc}
_0224B916:
	mov r1, #1
	ldr r0, [r4, #0x24]
	lsl r1, r1, #0xc
	bl sub_0201F854
	cmp r0, #1
	bne _0224B92E
	mov r0, #1
	str r0, [r4, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_0224B92E:
	pop {r4, pc}

	thumb_func_start ov06_0224B930
ov06_0224B930: ; 0x0224B930
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x24]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start ov06_0224B948
ov06_0224B948: ; 0x0224B948
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224B974
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224B964
ov06_0224B964: ; 0x0224B964
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224B9B8
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224B974
ov06_0224B974: ; 0x0224B974
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #3
	mov r2, #0x56
	bl ov05_021E5078
	ldr r0, [r4]
	mov r1, #2
	mov r2, #0x79
	bl ov05_021E50AC
	ldr r0, [r4]
	mov r1, #2
	mov r2, #5
	mov r3, #1
	bl ov05_021E50D4
	mov r3, #2
	mov r1, #3
	str r3, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224B9B4 ; =0x02251D48
	add r2, r1, #0
	str r0, [sp, #8]
	ldr r0, [r4]
	bl ov05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_0224B9B4: .word ov06_02251D48

	thumb_func_start ov06_0224B9B8
ov06_0224B9B8: ; 0x0224B9B8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #3
	bl ov05_021E50A0
	ldr r0, [r4]
	mov r1, #2
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #2
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #3
	bl ov05_021E506C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224B9E0
ov06_0224B9E0: ; 0x0224B9E0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r6, r1, #0
	bl ov05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl MapObject_GetFieldSystemPtr
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x17
	str r4, [sp, #0x18]
	bl ov05_021E4C08
	str r0, [sp, #0x1c]
	add r1, sp, #8
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r5, #0
	mov r1, #2
	str r5, [sp, #0x20]
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224BA2C ; =0x02251D34
	add r0, r4, #0
	add r2, sp, #8
	add r3, r6, #0
	bl ov05_021E4DC4
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224BA2C: .word ov06_02251D34

	thumb_func_start ov06_0224BA30
ov06_0224BA30: ; 0x0224BA30
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, sp, #0
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r5, r0, #0
	str r1, [r2, #8]
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x14
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x20]
	bl sub_0205845C
	str r0, [r4, #4]
	ldr r0, [r4, #0x20]
	bl MapObject_GetID
	str r0, [r4, #8]
	ldr r0, [r4, #0x20]
	bl sub_02058450
	str r0, [r4, #0xc]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #0x18]
	mov r1, #3
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x24]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224BA88
ov06_0224BA88: ; 0x0224BA88
	ldr r3, _0224BA90 ; =sub_0201F744
	ldr r0, [r1, #0x24]
	bx r3
	nop
_0224BA90: .word sub_0201F744

	thumb_func_start ov06_0224BA94
ov06_0224BA94: ; 0x0224BA94
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r7, [r4, #0x20]
	ldr r1, [r4, #4]
	add r5, r0, #0
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	add r0, r7, #0
	bl sub_020582F8
	cmp r0, #0
	bne _0224BAB4
	add r0, r5, #0
	bl ov05_021E4DE4
	pop {r3, r4, r5, r6, r7, pc}
_0224BAB4:
	add r0, r5, #0
	bl sub_02064754
	add r6, r0, #0
	cmp r6, #1
	bne _0224BAD2
	add r0, r7, #0
	bl sub_02058A00
	cmp r0, #0
	bne _0224BAD2
	add r0, r5, #0
	bl ov05_021E4DE4
	pop {r3, r4, r5, r6, r7, pc}
_0224BAD2:
	ldr r0, [r4]
	cmp r0, #0
	bne _0224BB08
	mov r1, #1
	ldr r0, [r4, #0x24]
	lsl r1, r1, #0xc
	bl sub_0201F854
	ldr r0, [r4, #0x24]
	bl sub_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r0, #0xc
	blt _0224BB08
	cmp r6, #0
	bne _0224BB00
	add r0, r5, #0
	bl ov05_021E4DE4
	pop {r3, r4, r5, r6, r7, pc}
_0224BB00:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl sub_0201F86C
_0224BB08:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224BB0C
ov06_0224BB0C: ; 0x0224BB0C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r6, [r4, #0x20]
	ldr r1, [r4, #4]
	add r5, r0, #0
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	add r0, r6, #0
	bl sub_020582F8
	cmp r0, #0
	bne _0224BB30
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0224BB30:
	add r0, r6, #0
	add r1, sp, #0
	bl sub_02058B5C
	mov r0, #2
	ldr r1, [sp, #8]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #8]
	ldr r0, [r4, #0x24]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224BB50
ov06_0224BB50: ; 0x0224BB50
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224BB7C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224BB6C
ov06_0224BB6C: ; 0x0224BB6C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224BBC4
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224BB7C
ov06_0224BB7C: ; 0x0224BB7C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #6
	mov r2, #0x58
	bl ov05_021E5078
	ldr r0, [r4]
	mov r1, #6
	mov r2, #0x7a
	bl ov05_021E50AC
	mov r1, #7
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #1
	bl ov05_021E50D4
	mov r0, #7
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224BBC0 ; =0x02251D74
	mov r2, #6
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #8
	add r3, r2, #0
	bl ov05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0224BBC0: .word ov06_02251D74

	thumb_func_start ov06_0224BBC4
ov06_0224BBC4: ; 0x0224BBC4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #6
	bl ov05_021E50A0
	ldr r0, [r4]
	mov r1, #6
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #7
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #8
	bl ov05_021E506C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224BBEC
ov06_0224BBEC: ; 0x0224BBEC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r5, r0, #0
	bl ov05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl MapObject_GetFieldSystemPtr
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x19
	str r4, [sp, #0x18]
	bl ov05_021E4C08
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x20]
	bl sub_02058B5C
	add r0, r5, #0
	bl sub_02058B2C
	add r6, r0, #0
	add r0, r5, #0
	bl sub_02058B4C
	add r1, r0, #0
	add r0, r6, #0
	add r2, sp, #8
	bl sub_02059E60
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224BC4C ; =0x02251D60
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224BC4C: .word ov06_02251D60

	thumb_func_start ov06_0224BC50
ov06_0224BC50: ; 0x0224BC50
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x10
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x1c]
	bl MapObject_GetID
	str r0, [r4, #4]
	ldr r0, [r4, #0x1c]
	bl sub_02058450
	str r0, [r4, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x14]
	mov r1, #8
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x20]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224BC94
ov06_0224BC94: ; 0x0224BC94
	ldr r3, _0224BC9C ; =sub_0201F744
	ldr r0, [r1, #0x20]
	bx r3
	nop
_0224BC9C: .word sub_0201F744

	thumb_func_start ov06_0224BCA0
ov06_0224BCA0: ; 0x0224BCA0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _0224BCCE
	mov r1, #1
	ldr r0, [r4, #0x20]
	lsl r1, r1, #0xc
	bl sub_0201F854
	ldr r0, [r4, #0x20]
	bl sub_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r0, #9
	blt _0224BCCE
	add r0, r5, #0
	bl ov05_021E4DE4
_0224BCCE:
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224BCD0
ov06_0224BCD0: ; 0x0224BCD0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl sub_0206477C
	mov r0, #2
	ldr r1, [sp, #8]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #8]
	ldr r0, [r4, #0x20]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224BCF4
ov06_0224BCF4: ; 0x0224BCF4
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224BD20
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224BD10
ov06_0224BD10: ; 0x0224BD10
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224BD68
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224BD20
ov06_0224BD20: ; 0x0224BD20
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #7
	mov r2, #0x59
	bl ov05_021E5078
	ldr r0, [r4]
	mov r1, #7
	mov r2, #0x7b
	bl ov05_021E50AC
	mov r1, #8
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #1
	bl ov05_021E50D4
	mov r0, #8
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224BD64 ; =0x02251DA0
	mov r2, #7
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #9
	add r3, r2, #0
	bl ov05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0224BD64: .word ov06_02251DA0

	thumb_func_start ov06_0224BD68
ov06_0224BD68: ; 0x0224BD68
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #7
	bl ov05_021E50A0
	ldr r0, [r4]
	mov r1, #7
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #8
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #9
	bl ov05_021E506C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224BD90
ov06_0224BD90: ; 0x0224BD90
	push {r4, r5, r6, lr}
	sub sp, #0x30
	add r5, r0, #0
	add r6, r1, #0
	bl ov05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl sub_02058B2C
	str r0, [sp, #8]
	add r0, r5, #0
	bl sub_02058B3C
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl sub_02058B4C
	str r0, [sp, #0x10]
	add r0, r4, #0
	str r4, [sp, #0x18]
	bl ov05_021E4C20
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x1a
	bl ov05_021E4C08
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, sp, #0x24
	str r5, [sp, #0x20]
	bl sub_02058B5C
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #8
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224BDF4 ; =0x02251D8C
	add r0, r4, #0
	add r2, sp, #0x24
	add r3, r6, #0
	bl ov05_021E4DC4
	add sp, #0x30
	pop {r4, r5, r6, pc}
	nop
_0224BDF4: .word ov06_02251D8C

	thumb_func_start ov06_0224BDF8
ov06_0224BDF8: ; 0x0224BDF8
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x18
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x30]
	bl sub_0205845C
	str r0, [r4, #4]
	ldr r0, [r4, #0x30]
	bl MapObject_GetID
	str r0, [r4, #8]
	ldr r0, [r4, #0x30]
	bl sub_02058450
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x18]
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [r4, #0x30]
	bl sub_02058B80
	str r0, [sp, #4]
	ldr r0, [r4, #0x24]
	add r1, sp, #0
	bl sub_02059E9C
	str r0, [r4, #0x14]
	mov r0, #2
	ldr r1, [sp]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp]
	mov r0, #0x12
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #0x28]
	mov r1, #9
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x34]
	add r0, r5, #0
	bl sub_02064754
	cmp r0, #0
	bne _0224BE86
	mov r0, #1
	str r0, [r4]
_0224BE86:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224BE8C
ov06_0224BE8C: ; 0x0224BE8C
	ldr r3, _0224BE94 ; =sub_0201F744
	ldr r0, [r1, #0x34]
	bx r3
	nop
_0224BE94: .word sub_0201F744

	thumb_func_start ov06_0224BE98
ov06_0224BE98: ; 0x0224BE98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	ldr r6, [r4, #0x30]
	ldr r1, [r4, #4]
	add r5, r0, #0
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	add r0, r6, #0
	bl sub_020582F8
	cmp r0, #0
	bne _0224BEBC
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224BEBC:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _0224BEF4
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_0206477C
	ldr r0, [r4, #0x18]
	add r1, sp, #0
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	str r0, [sp, #4]
	ldr r0, [r4, #0x24]
	bl sub_02059E9C
	str r0, [r4, #0x14]
	cmp r0, #1
	bne _0224BEF4
	ldr r0, [sp, #4]
	add r1, sp, #0xc
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl sub_0206476C
_0224BEF4:
	ldr r0, [r4]
	cmp r0, #0
	beq _0224BF06
	cmp r0, #1
	beq _0224BF2A
	cmp r0, #2
	beq _0224BF40
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224BF06:
	mov r1, #1
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xc
	bl sub_0201F854
	ldr r0, [r4, #0x34]
	bl sub_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r0, #0xc
	blt _0224BF60
	mov r0, #1
	add sp, #0x18
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0224BF2A:
	mov r1, #3
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xe
	bl sub_0201F86C
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl sub_0201F854
	mov r0, #2
	str r0, [r4]
_0224BF40:
	add r0, r6, #0
	bl sub_02058B2C
	add r7, r0, #0
	add r0, r6, #0
	bl sub_02058B4C
	ldr r1, [r4, #0x18]
	cmp r1, r7
	bne _0224BF5A
	ldr r1, [r4, #0x20]
	cmp r1, r0
	beq _0224BF60
_0224BF5A:
	add r0, r5, #0
	bl ov05_021E4DE4
_0224BF60:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224BF64
ov06_0224BF64: ; 0x0224BF64
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	bl sub_020582F8
	cmp r0, #0
	bne _0224BF86
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r4, r5, pc}
_0224BF86:
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x34]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224BF9C
ov06_0224BF9C: ; 0x0224BF9C
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224BFC8
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224BFB8
ov06_0224BFB8: ; 0x0224BFB8
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224C010
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224BFC8
ov06_0224BFC8: ; 0x0224BFC8
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #8
	mov r2, #0x5a
	bl ov05_021E5078
	ldr r0, [r4]
	mov r1, #8
	mov r2, #0x7c
	bl ov05_021E50AC
	mov r1, #9
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #1
	bl ov05_021E50D4
	mov r0, #9
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224C00C ; =0x02251DCC
	mov r2, #8
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0xa
	add r3, r2, #0
	bl ov05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0224C00C: .word ov06_02251DCC

	thumb_func_start ov06_0224C010
ov06_0224C010: ; 0x0224C010
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #8
	bl ov05_021E50A0
	ldr r0, [r4]
	mov r1, #8
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #9
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #0xa
	bl ov05_021E506C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224C038
ov06_0224C038: ; 0x0224C038
	push {r4, r5, r6, lr}
	sub sp, #0x30
	add r5, r0, #0
	add r6, r1, #0
	bl ov05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl sub_02058B2C
	str r0, [sp, #8]
	add r0, r5, #0
	bl sub_02058B3C
	str r0, [sp, #0xc]
	add r0, r5, #0
	bl sub_02058B4C
	str r0, [sp, #0x10]
	add r0, r4, #0
	str r4, [sp, #0x18]
	bl ov05_021E4C20
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x1b
	bl ov05_021E4C08
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, sp, #0x24
	str r5, [sp, #0x20]
	bl sub_02058B5C
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #8
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224C09C ; =0x02251DB8
	add r0, r4, #0
	add r2, sp, #0x24
	add r3, r6, #0
	bl ov05_021E4DC4
	add sp, #0x30
	pop {r4, r5, r6, pc}
	nop
_0224C09C: .word ov06_02251DB8

	thumb_func_start ov06_0224C0A0
ov06_0224C0A0: ; 0x0224C0A0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	add r2, #0x18
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #0x30]
	bl sub_0205845C
	str r0, [r4, #4]
	ldr r0, [r4, #0x30]
	bl MapObject_GetID
	str r0, [r4, #8]
	ldr r0, [r4, #0x30]
	bl sub_02058450
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x18]
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [r4, #0x30]
	bl sub_02058B80
	str r0, [sp, #4]
	ldr r0, [r4, #0x24]
	add r1, sp, #0
	bl sub_02059E9C
	str r0, [r4, #0x14]
	mov r0, #0x1e
	ldr r1, [sp]
	lsl r0, r0, #0xa
	add r0, r1, r0
	str r0, [sp]
	mov r0, #2
	ldr r1, [sp, #4]
	lsl r0, r0, #0xe
	sub r0, r1, r0
	str r0, [sp, #4]
	mov r0, #0xd
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	ldr r0, [r4, #0x28]
	mov r1, #0xa
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x34]
	add r0, r5, #0
	bl sub_02064754
	cmp r0, #0
	bne _0224C138
	mov r0, #1
	str r0, [r4]
_0224C138:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224C140
ov06_0224C140: ; 0x0224C140
	ldr r3, _0224C148 ; =sub_0201F744
	ldr r0, [r1, #0x34]
	bx r3
	nop
_0224C148: .word sub_0201F744

	thumb_func_start ov06_0224C14C
ov06_0224C14C: ; 0x0224C14C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	ldr r6, [r4, #0x30]
	ldr r1, [r4, #4]
	add r5, r0, #0
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	add r0, r6, #0
	bl sub_020582F8
	cmp r0, #0
	bne _0224C170
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224C170:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _0224C1A8
	add r0, r5, #0
	add r1, sp, #0xc
	bl sub_0206477C
	ldr r0, [r4, #0x18]
	add r1, sp, #0
	lsl r0, r0, #0x10
	str r0, [sp]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #0x10
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	str r0, [sp, #4]
	ldr r0, [r4, #0x24]
	bl sub_02059E9C
	str r0, [r4, #0x14]
	cmp r0, #1
	bne _0224C1A8
	ldr r0, [sp, #4]
	add r1, sp, #0xc
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl sub_0206476C
_0224C1A8:
	ldr r0, [r4]
	cmp r0, #0
	beq _0224C1BA
	cmp r0, #1
	beq _0224C1DE
	cmp r0, #2
	beq _0224C1F4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0224C1BA:
	mov r1, #1
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xc
	bl sub_0201F854
	ldr r0, [r4, #0x34]
	bl sub_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r0, #2
	blt _0224C214
	mov r0, #1
	add sp, #0x18
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0224C1DE:
	mov r1, #2
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xc
	bl sub_0201F86C
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl sub_0201F854
	mov r0, #2
	str r0, [r4]
_0224C1F4:
	add r0, r6, #0
	bl sub_02058B2C
	add r7, r0, #0
	add r0, r6, #0
	bl sub_02058B4C
	ldr r1, [r4, #0x18]
	cmp r1, r7
	bne _0224C20E
	ldr r1, [r4, #0x20]
	cmp r1, r0
	beq _0224C214
_0224C20E:
	add r0, r5, #0
	bl ov05_021E4DE4
_0224C214:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224C218
ov06_0224C218: ; 0x0224C218
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #8]
	ldr r2, [r4, #0xc]
	bl sub_020582A8
	cmp r0, #0
	bne _0224C238
	add r0, r5, #0
	bl ov05_021E4DE4
	add sp, #0xc
	pop {r4, r5, pc}
_0224C238:
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x34]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224C24C
ov06_0224C24C: ; 0x0224C24C
	push {r4, lr}
	add r4, r1, #0
	bl Save_Roamers_Get
	bl sub_0202AB4C
	ldrb r1, [r0]
	cmp r1, #0
	beq _0224C278
	sub r1, r1, #1
	strb r1, [r0]
	ldrb r0, [r0]
	cmp r0, #0
	bne _0224C278
	mov r1, #0x7f
	add r0, r4, #0
	lsl r1, r1, #4
	mov r2, #0
	bl sub_02038C78
	mov r0, #1
	pop {r4, pc}
_0224C278:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start CallTask_PokecenterAnimation
CallTask_PokecenterAnimation: ; 0x0224C27C
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r6, r1, #0
	mov r1, #0x7b
	add r2, sp, #4
	add r3, sp, #0
	add r5, r0, #0
	bl sub_0204A9F0
	cmp r0, #0
	beq _0224C2E8
	mov r0, #4
	mov r1, #0x18
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	strb r6, [r4, #0xc]
	mov r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
	ldr r0, [r5, #0x28]
	bl MapMatrix_GetWidth
	add r1, r0, #0
	ldr r0, [sp]
	add r2, sp, #0x14
	bl sub_0204AAD4
	ldr r1, [sp, #4]
	add r0, sp, #8
	bl ov05_021E7EA0
	add r3, sp, #8
	ldmia r3!, {r0, r1}
	add r2, r4, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [r4]
	ldr r0, [sp, #0x14]
	add r2, r4, #0
	add r0, r1, r0
	str r0, [r4]
	ldr r1, [r4, #8]
	ldr r0, [sp, #0x1c]
	add r0, r1, r0
	str r0, [r4, #8]
	ldr r0, [r5, #0x10]
	ldr r1, _0224C2F0 ; =ov06_0224C2F4
	bl TaskManager_Call
	add sp, #0x20
	pop {r4, r5, r6, pc}
_0224C2E8:
	bl GF_AssertFail
	add sp, #0x20
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224C2F0: .word ov06_0224C2F4

	thumb_func_start ov06_0224C2F4
ov06_0224C2F4: ; 0x0224C2F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldrb r1, [r4, #0xf]
	cmp r1, #5
	bls _0224C310
	b _0224C500
_0224C310:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224C31C: ; jump table
	.short _0224C328 - _0224C31C - 2 ; case 0
	.short _0224C3C2 - _0224C31C - 2 ; case 1
	.short _0224C44A - _0224C31C - 2 ; case 2
	.short _0224C476 - _0224C31C - 2 ; case 3
	.short _0224C498 - _0224C31C - 2 ; case 4
	.short _0224C4F6 - _0224C31C - 2 ; case 5
_0224C328:
	ldr r0, _0224C508 ; =0x00000205
	ldr r1, [r5, #0x2c]
	bl ov05_021F4BD0
	add r6, r0, #0
	ldr r1, [r5, #0x2c]
	mov r0, #0x7c
	bl ov05_021F4BD0
	str r0, [sp, #0x18]
	ldr r0, [r6]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r7, r0, r1
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r6, r0, r1
	ldr r0, [r5, #0x2c]
	bl ov05_021F4C88
	mov r1, #0
	str r1, [sp]
	str r7, [sp, #4]
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	ldr r3, _0224C508 ; =0x00000205
	mov r2, #0x10
	bl ov05_021DA464
	add r0, r5, #0
	mov r1, #0x7c
	add r2, sp, #0x1c
	mov r3, #0
	bl sub_0204A9F0
	cmp r0, #0
	bne _0224C390
	bl GF_AssertFail
_0224C390:
	ldr r0, [sp, #0x1c]
	bl ov05_021E7EC8
	add r7, r0, #0
	ldr r0, [r5, #0x2c]
	bl ov05_021F4C88
	str r7, [sp]
	str r6, [sp, #4]
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #0x20
	mov r3, #0x7c
	bl ov05_021DA464
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224C500
_0224C3C2:
	add r1, sp, #0x20
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	ldrb r2, [r4, #0xd]
	mov r1, #0xc
	ldr r0, [r4]
	add r3, r2, #0
	ldr r2, _0224C50C ; =ov06_02252358
	mul r3, r1
	ldr r2, [r2, r3]
	add r0, r0, r2
	str r0, [sp, #0x2c]
	ldrb r2, [r4, #0xd]
	ldr r0, [r4, #4]
	add r3, r2, #0
	ldr r2, _0224C510 ; =ov06_0225235C
	mul r3, r1
	ldr r2, [r2, r3]
	add r0, r0, r2
	str r0, [sp, #0x30]
	ldrb r2, [r4, #0xd]
	ldr r0, [r4, #8]
	add r3, r2, #0
	mul r3, r1
	ldr r1, _0224C514 ; =ov06_02252360
	ldr r1, [r1, r3]
	add r0, r0, r1
	str r0, [sp, #0x34]
	ldr r0, _0224C518 ; =0x000005FE
	bl PlaySE
	add r0, sp, #0x20
	str r0, [sp]
	ldr r0, [r5, #0x4c]
	ldr r2, _0224C508 ; =0x00000205
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	add r3, sp, #0x2c
	bl ov05_021E7FBC
	ldrb r1, [r4, #0xd]
	add r1, r4, r1
	strb r0, [r1, #0x10]
	ldrb r1, [r4, #0xd]
	add r0, r5, #0
	add r0, #0xa0
	add r1, r4, r1
	ldrb r1, [r1, #0x10]
	ldr r0, [r0]
	bl ov05_021E7EEC
	bl ov05_021E7EC8
	add r3, r0, #0
	ldrb r2, [r4, #0xd]
	ldr r0, [r5, #0x50]
	mov r1, #0x10
	bl ov05_021DA4BC
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224C500
_0224C44A:
	ldrb r0, [r4, #0xe]
	cmp r0, #0xf
	bhs _0224C456
	add r0, r0, #1
	strb r0, [r4, #0xe]
	b _0224C500
_0224C456:
	mov r0, #0
	strb r0, [r4, #0xe]
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	ldrb r1, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	cmp r1, r0
	bhs _0224C46E
	mov r0, #1
	strb r0, [r4, #0xf]
	b _0224C500
_0224C46E:
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224C500
_0224C476:
	ldr r0, [r5, #0x50]
	mov r1, #0x10
	mov r2, #0
	bl ov05_021DA4EC
	ldr r0, [r5, #0x50]
	mov r1, #0x20
	mov r2, #0
	bl ov05_021DA4EC
	ldr r0, _0224C51C ; =0x0000048E
	bl PlaySound
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224C500
_0224C498:
	ldr r0, [r5, #0x50]
	mov r1, #0x10
	bl ov05_021DA58C
	cmp r0, #0
	beq _0224C500
	ldr r0, [r5, #0x50]
	mov r1, #0x20
	bl ov05_021DA58C
	cmp r0, #0
	beq _0224C500
	bl sub_02005CBC
	cmp r0, #0
	bne _0224C500
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #0x20
	bl ov05_021DA54C
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #0x10
	bl ov05_021DA54C
	ldrb r0, [r4, #0xc]
	mov r6, #0
	cmp r0, #0
	bls _0224C4EE
_0224C4D4:
	add r0, r4, r6
	add r1, r5, #0
	add r1, #0xa0
	ldrb r0, [r0, #0x10]
	ldr r1, [r1]
	bl ov05_021E7C80
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldrb r0, [r4, #0xc]
	cmp r6, r0
	blo _0224C4D4
_0224C4EE:
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224C500
_0224C4F6:
	bl FreeToHeap
	add sp, #0x38
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224C500:
	mov r0, #0
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224C508: .word 0x00000205
_0224C50C: .word ov06_02252358
_0224C510: .word ov06_0225235C
_0224C514: .word ov06_02252360
_0224C518: .word 0x000005FE
_0224C51C: .word 0x0000048E

	thumb_func_start ov06_0224C520
ov06_0224C520: ; 0x0224C520
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r2, #0
	mov r2, #0
	ldr r1, _0224C558 ; =0x000001F2
	add r3, r2, #0
	add r5, r0, #0
	bl sub_0204A9F0
	cmp r0, #0
	beq _0224C552
	mov r0, #4
	add r1, r0, #0
	bl AllocFromHeapAtEnd
	add r2, r0, #0
	strb r6, [r2]
	strb r4, [r2, #1]
	mov r0, #0
	strb r0, [r2, #2]
	ldr r0, [r5, #0x10]
	ldr r1, _0224C55C ; =ov06_0224C560
	bl TaskManager_Call
	pop {r4, r5, r6, pc}
_0224C552:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224C558: .word 0x000001F2
_0224C55C: .word ov06_0224C560

	thumb_func_start ov06_0224C560
ov06_0224C560: ; 0x0224C560
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #4
	bhi _0224C664
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224C586: ; jump table
	.short _0224C590 - _0224C586 - 2 ; case 0
	.short _0224C5EE - _0224C586 - 2 ; case 1
	.short _0224C61C - _0224C586 - 2 ; case 2
	.short _0224C648 - _0224C586 - 2 ; case 3
	.short _0224C65A - _0224C586 - 2 ; case 4
_0224C590:
	ldr r0, _0224C66C ; =0x000001F2
	ldr r1, [r5, #0x2c]
	bl ov05_021F4BD0
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r2, sp, #0x18
	mov r3, #0
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r6, r0, r1
	ldr r1, _0224C66C ; =0x000001F2
	add r0, r5, #0
	bl sub_0204A9F0
	cmp r0, #0
	bne _0224C5BA
	bl GF_AssertFail
_0224C5BA:
	ldr r0, [sp, #0x18]
	bl ov05_021E7EC8
	add r7, r0, #0
	ldr r0, [r5, #0x2c]
	bl ov05_021F4C88
	str r7, [sp]
	str r6, [sp, #4]
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	ldrb r0, [r4]
	ldr r3, _0224C66C ; =0x000001F2
	mov r2, #1
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	bl ov05_021DA464
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	b _0224C664
_0224C5EE:
	ldrb r0, [r4, #1]
	mov r1, #1
	cmp r0, #0
	beq _0224C5FC
	cmp r0, #1
	beq _0224C5FC
	mov r1, #0
_0224C5FC:
	cmp r1, #0
	bne _0224C604
	bl GF_AssertFail
_0224C604:
	ldrb r2, [r4, #1]
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl ov05_021DA4EC
	ldr r0, _0224C670 ; =0x00000612
	bl PlaySE
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	b _0224C664
_0224C61C:
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl ov05_021DA58C
	cmp r0, #0
	beq _0224C664
	ldr r0, _0224C670 ; =0x00000612
	mov r1, #0
	bl sub_020054F0
	ldr r0, _0224C674 ; =0x000005F1
	bl PlaySE
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #1
	bl ov05_021DA54C
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	b _0224C664
_0224C648:
	ldr r0, _0224C674 ; =0x000005F1
	bl sub_02005508
	cmp r0, #0
	bne _0224C664
	ldrb r0, [r4, #2]
	add r0, r0, #1
	strb r0, [r4, #2]
	b _0224C664
_0224C65A:
	bl FreeToHeap
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224C664:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0224C66C: .word 0x000001F2
_0224C670: .word 0x00000612
_0224C674: .word 0x000005F1

	thumb_func_start ov06_0224C678
ov06_0224C678: ; 0x0224C678
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r4, _0224C6E4 ; =0x02251DE4
	add r3, sp, #0x20
	add r5, r0, #0
	add r7, r1, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, sp, #0x18
	str r0, [sp]
	add r1, r2, #0
	add r0, r5, #0
	mov r2, #4
	add r3, sp, #0x1c
	bl sub_0204AA5C
	cmp r0, #0
	beq _0224C6DA
	ldr r0, [r5, #0x2c]
	bl ov05_021F4C88
	add r4, r0, #0
	ldr r0, [sp, #0x1c]
	bl ov05_021E7EC8
	add r6, r0, #0
	ldr r0, [sp, #0x1c]
	bl ov05_021E7ECC
	str r6, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	ldr r3, [sp, #0x18]
	add r2, r7, #0
	bl ov05_021DA464
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
_0224C6DA:
	bl GF_AssertFail
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224C6E4: .word ov06_02251DE4

	thumb_func_start ov06_0224C6E8
ov06_0224C6E8: ; 0x0224C6E8
	ldr r3, _0224C6F0 ; =ov05_021DA4EC
	ldr r0, [r0, #0x50]
	mov r2, #0
	bx r3
	.align 2, 0
_0224C6F0: .word ov05_021DA4EC

	thumb_func_start ov06_0224C6F4
ov06_0224C6F4: ; 0x0224C6F4
	ldr r3, _0224C6FC ; =ov05_021DA4EC
	ldr r0, [r0, #0x50]
	mov r2, #1
	bx r3
	.align 2, 0
_0224C6FC: .word ov05_021DA4EC

	thumb_func_start ov06_0224C700
ov06_0224C700: ; 0x0224C700
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	mov r1, #0x24
	bl ov06_0224CB90
	add r4, r0, #0
	mov r0, #0
	str r0, [r4, #8]
	str r5, [r4, #0x1c]
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetMapObject
	str r0, [r4, #0x18]
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224C720
ov06_0224C720: ; 0x0224C720
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl TaskManager_GetFieldSystem
	add r7, r0, #0
	add r0, r6, #0
	bl TaskManager_GetEnvironment
	add r5, r0, #0
_0224C732:
	ldr r3, [r5]
	add r0, r6, #0
	lsl r4, r3, #2
	ldr r3, _0224C758 ; =0x02251E04
	add r1, r7, #0
	ldr r3, [r3, r4]
	add r2, r5, #0
	blx r3
	add r4, r0, #0
	cmp r4, #2
	bne _0224C74E
	add r0, r5, #0
	bl FreeToHeap
_0224C74E:
	cmp r4, #1
	beq _0224C732
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224C758: .word ov06_02251E04

	thumb_func_start ov06_0224C75C
ov06_0224C75C: ; 0x0224C75C
	push {r4, lr}
	add r0, r1, #0
	mov r1, #4
	add r4, r2, #0
	bl ov05_021F61F4
	ldr r2, _0224C7B0 ; =0xFFF6A000
	str r0, [r4, #0x14]
	mov r1, #1
	mov r3, #0xf
	bl ov05_021F6254
	ldr r0, [r4, #0x18]
	ldr r1, _0224C7B4 ; =0x02251E40
	bl sub_0205AEA4
	str r0, [r4, #0xc]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0224C794
	cmp r0, #1
	beq _0224C79C
	cmp r0, #2
	beq _0224C7A4
	b _0224C7AA
_0224C794:
	ldr r0, _0224C7B8 ; =0x00000603
	bl PlaySE
	b _0224C7AA
_0224C79C:
	ldr r0, _0224C7B8 ; =0x00000603
	bl PlaySE
	b _0224C7AA
_0224C7A4:
	ldr r0, _0224C7BC ; =0x0000064E
	bl PlaySE
_0224C7AA:
	mov r0, #0
	pop {r4, pc}
	nop
_0224C7B0: .word 0xFFF6A000
_0224C7B4: .word ov06_02251E40
_0224C7B8: .word 0x00000603
_0224C7BC: .word 0x0000064E

	thumb_func_start ov06_0224C7C0
ov06_0224C7C0: ; 0x0224C7C0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r0, [r4, #0xc]
	bl sub_0205AEF0
	cmp r0, #0
	bne _0224C7D6
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_0224C7D6:
	ldr r0, [r4, #0xc]
	bl sub_0205AEFC
	ldr r0, [r4, #0x18]
	ldr r1, _0224C83C ; =0x02251E14
	bl sub_0205AEA4
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #8
	bge _0224C7F6
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, pc}
_0224C7F6:
	ldr r0, [r4, #8]
	cmp r0, #2
	bne _0224C816
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
	b _0224C82E
_0224C816:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0
	ldr r3, _0224C840 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	bl BeginNormalPaletteFade
_0224C82E:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0224C83C: .word ov06_02251E14
_0224C840: .word 0x00007FFF

	thumb_func_start ov06_0224C844
ov06_0224C844: ; 0x0224C844
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0xc]
	bl sub_0205AEF0
	cmp r0, #1
	bne _0224C862
	ldr r0, [r4, #0xc]
	bl sub_0205AEFC
	ldr r0, [r4, #0x18]
	ldr r1, _0224C884 ; =0x02251E14
	bl sub_0205AEA4
	str r0, [r4, #0xc]
_0224C862:
	bl IsPaletteFadeFinished
	cmp r0, #0
	bne _0224C86E
	mov r0, #0
	pop {r4, pc}
_0224C86E:
	ldr r0, [r4, #0xc]
	bl sub_0205AEFC
	ldr r0, [r4, #0x14]
	bl ov05_021F6240
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_0224C884: .word ov06_02251E14

	thumb_func_start ov06_0224C888
ov06_0224C888: ; 0x0224C888
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r1, #0xc]
	add r4, r2, #0
	bl Save_LocalFieldData_Get
	ldr r1, [r4, #8]
	cmp r1, #2
	bne _0224C8B2
	bl LocalFieldData_GetBlackoutSpawn
	add r1, sp, #0
	bl GetSpecialSpawnWarpData
	ldr r2, [r4, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_02049494
	b _0224C8C0
_0224C8B2:
	bl LocalFieldData_GetSpecialSpawnWarpPtr
	add r1, r0, #0
	ldr r2, [r4, #8]
	add r0, r5, #0
	bl sub_02049494
_0224C8C0:
	mov r0, #2
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224C8C8
ov06_0224C8C8: ; 0x0224C8C8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, r1, #0
	mov r1, #0x24
	add r6, r2, #0
	bl ov06_0224CB90
	add r4, r0, #0
	str r6, [r4, #8]
	str r5, [r4, #0x1c]
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetMapObject
	str r0, [r4, #0x18]
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0224C8E8
ov06_0224C8E8: ; 0x0224C8E8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0
	add r0, r5, #0
	bl TaskManager_GetEnvironment
	ldr r7, _0224C928 ; =0x02251DF4
	add r4, r0, #0
_0224C8FC:
	ldr r3, [r4]
	add r0, r5, #0
	lsl r3, r3, #2
	ldr r3, [r7, r3]
	add r1, r6, #0
	add r2, r4, #0
	blx r3
	cmp r0, #2
	bne _0224C920
	add r0, r6, #0
	add r1, r4, #0
	bl ov06_0224C92C
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224C920:
	cmp r0, #1
	beq _0224C8FC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224C928: .word ov06_02251DF4

	thumb_func_start ov06_0224C92C
ov06_0224C92C: ; 0x0224C92C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #8]
	cmp r0, #2
	bne _0224C952
	ldr r1, [r4, #0x1c]
	mov r0, #9
	ldr r1, [r1]
	mov r2, #4
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl sub_0202914C
	add r4, #0x98
	add r1, r0, #0
	ldr r0, [r4]
	mov r2, #1
	bl sub_02028AD4
_0224C952:
	pop {r4, pc}

	thumb_func_start ov06_0224C954
ov06_0224C954: ; 0x0224C954
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r0, [r4, #8]
	add r5, r1, #0
	cmp r0, #2
	bne _0224C97A
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
	b _0224C990
_0224C97A:
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r3, _0224C9BC ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl BeginNormalPaletteFade
_0224C990:
	add r0, r5, #0
	mov r1, #4
	bl ov05_021F61F4
	mov r1, #1
	ldr r2, _0224C9C0 ; =0xFFF6A000
	str r0, [r4, #0x14]
	add r3, r1, #0
	bl ov05_021F6254
	ldr r0, [r4, #0x18]
	ldr r1, _0224C9C4 ; =0x02251E14
	bl sub_0205AEA4
	str r0, [r4, #0xc]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0224C9BC: .word 0x00007FFF
_0224C9C0: .word 0xFFF6A000
_0224C9C4: .word ov06_02251E14

	thumb_func_start ov06_0224C9C8
ov06_0224C9C8: ; 0x0224C9C8
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0xc]
	bl sub_0205AEF0
	cmp r0, #1
	bne _0224C9E6
	ldr r0, [r4, #0xc]
	bl sub_0205AEFC
	ldr r0, [r4, #0x18]
	ldr r1, _0224CA08 ; =0x02251E14
	bl sub_0205AEA4
	str r0, [r4, #0xc]
_0224C9E6:
	bl IsPaletteFadeFinished
	cmp r0, #0
	bne _0224C9F2
	mov r0, #0
	pop {r4, pc}
_0224C9F2:
	ldr r0, [r4, #0x14]
	mov r1, #2
	mov r2, #0
	mov r3, #0x3c
	bl ov05_021F6254
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_0224CA08: .word ov06_02251E14

	thumb_func_start ov06_0224CA0C
ov06_0224CA0C: ; 0x0224CA0C
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0xc]
	bl sub_0205AEF0
	cmp r0, #0
	bne _0224CA1E
	mov r0, #0
	pop {r4, pc}
_0224CA1E:
	ldr r0, [r4, #0xc]
	bl sub_0205AEFC
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #4
	ldr r0, [r4, #0x18]
	bge _0224CA3C
	ldr r1, _0224CA50 ; =0x02251E14
	bl sub_0205AEA4
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_0224CA3C:
	ldr r1, _0224CA54 ; =0x02251EA4
	bl sub_0205AEA4
	str r0, [r4, #0xc]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r4, pc}
	nop
_0224CA50: .word ov06_02251E14
_0224CA54: .word ov06_02251EA4

	thumb_func_start ov06_0224CA58
ov06_0224CA58: ; 0x0224CA58
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0xc]
	bl sub_0205AEF0
	cmp r0, #0
	bne _0224CA6A
	mov r0, #0
	pop {r4, pc}
_0224CA6A:
	ldr r0, [r4, #0x14]
	bl ov05_021F6234
	cmp r0, #0
	bne _0224CA78
	mov r0, #0
	pop {r4, pc}
_0224CA78:
	ldr r0, [r4, #0x14]
	bl ov05_021F6240
	ldr r0, [r4, #0xc]
	bl sub_0205AEFC
	mov r0, #2
	pop {r4, pc}

	thumb_func_start ov06_0224CA88
ov06_0224CA88: ; 0x0224CA88
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r0, r2, #0
	mov r1, #0x24
	bl ov06_0224CB90
	add r4, r0, #0
	mov r0, #1
	str r0, [r4, #8]
	str r5, [r4, #0x1c]
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetMapObject
	str r0, [r4, #0x18]
	str r6, [r4, #0x20]
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0224CAAC
ov06_0224CAAC: ; 0x0224CAAC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl TaskManager_GetFieldSystem
	add r7, r0, #0
	add r0, r6, #0
	bl TaskManager_GetEnvironment
	add r5, r0, #0
_0224CABE:
	ldr r3, [r5]
	add r0, r6, #0
	lsl r4, r3, #2
	ldr r3, _0224CAE4 ; =0x02251E28
	add r1, r7, #0
	ldr r3, [r3, r4]
	add r2, r5, #0
	blx r3
	add r4, r0, #0
	cmp r4, #2
	bne _0224CADA
	add r0, r5, #0
	bl FreeToHeap
_0224CADA:
	cmp r4, #1
	beq _0224CABE
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224CAE4: .word ov06_02251E28

	thumb_func_start ov06_0224CAE8
ov06_0224CAE8: ; 0x0224CAE8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x38]
	add r4, r2, #0
	bl PlayerAvatar_GetGender
	add r3, r0, #0
	ldr r2, [r4, #0x20]
	add r0, r5, #0
	mov r1, #0
	bl ov06_0224666C
	str r0, [r4, #0x10]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224CB0C
ov06_0224CB0C: ; 0x0224CB0C
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0x10]
	bl ov06_022466A0
	cmp r0, #0
	bne _0224CB1E
	mov r0, #0
	pop {r4, pc}
_0224CB1E:
	ldr r0, [r4, #0x10]
	bl ov06_022466AC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224CB30
ov06_0224CB30: ; 0x0224CB30
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r0, r2, #0
	mov r1, #0x24
	bl ov06_0224CB90
	add r4, r0, #0
	mov r0, #2
	str r0, [r4, #8]
	str r5, [r4, #0x1c]
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetMapObject
	str r0, [r4, #0x18]
	str r6, [r4, #0x20]
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov06_0224CB54
ov06_0224CB54: ; 0x0224CB54
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl TaskManager_GetFieldSystem
	add r7, r0, #0
	add r0, r6, #0
	bl TaskManager_GetEnvironment
	add r5, r0, #0
_0224CB66:
	ldr r3, [r5]
	add r0, r6, #0
	lsl r4, r3, #2
	ldr r3, _0224CB8C ; =0x02251E28
	add r1, r7, #0
	ldr r3, [r3, r4]
	add r2, r5, #0
	blx r3
	add r4, r0, #0
	cmp r4, #2
	bne _0224CB82
	add r0, r5, #0
	bl FreeToHeap
_0224CB82:
	cmp r4, #1
	beq _0224CB66
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224CB8C: .word ov06_02251E28

	thumb_func_start ov06_0224CB90
ov06_0224CB90: ; 0x0224CB90
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bne _0224CBA0
	bl GF_AssertFail
_0224CBA0:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224CBB0
ov06_0224CBB0: ; 0x0224CBB0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	mov r0, #0x6a
	mov r1, #8
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	add r4, r0, #0
	add r1, sp, #4
	ldr r0, [sp]
	add r1, #2
	add r2, sp, #4
	bl sub_0202AB8C
	add r0, sp, #4
	ldrh r1, [r0, #2]
	ldr r0, _0224CC20 ; =0x0000FFFF
	cmp r1, r0
	beq _0224CBDE
	lsl r0, r1, #2
	ldr r6, [r4, r0]
	b _0224CBE0
_0224CBDE:
	mov r6, #0
_0224CBE0:
	add r0, sp, #4
	ldrh r1, [r0]
	ldr r0, _0224CC20 ; =0x0000FFFF
	cmp r1, r0
	beq _0224CBF0
	lsl r0, r1, #2
	ldr r7, [r4, r0]
	b _0224CBF2
_0224CBF0:
	mov r7, #0
_0224CBF2:
	bl LCRandom
	lsl r0, r0, #4
	lsr r5, r0, #0x10
	cmp r5, #0x10
	blo _0224CC02
	bl GF_AssertFail
_0224CC02:
	lsl r0, r5, #2
	ldr r0, [r4, r0]
	cmp r6, r0
	beq _0224CBF2
	cmp r7, r0
	beq _0224CBF2
	ldr r0, [sp]
	add r1, r5, #0
	bl sub_0202ABA0
	add r0, r4, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224CC20: .word 0x0000FFFF

	thumb_func_start ov06_0224CC24
ov06_0224CC24: ; 0x0224CC24
	push {r3, r4, lr}
	sub sp, #4
	add r1, sp, #0
	add r1, #2
	add r2, sp, #0
	bl sub_0202AB8C
	add r0, sp, #0
	ldrh r1, [r0, #2]
	ldr r0, _0224CC5C ; =0x0000FFFF
	cmp r1, r0
	bne _0224CC40
	bl GF_AssertFail
_0224CC40:
	mov r0, #0x6a
	mov r1, #8
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	add r1, sp, #0
	ldrh r1, [r1, #2]
	lsl r1, r1, #2
	ldr r4, [r0, r1]
	bl FreeToHeap
	add r0, r4, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0224CC5C: .word 0x0000FFFF

	thumb_func_start ov06_0224CC60
ov06_0224CC60: ; 0x0224CC60
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r5, r0, #0
	bl LCRandom
	lsl r0, r0, #1
	lsr r4, r0, #0x10
	cmp r4, #2
	blo _0224CC76
	bl GF_AssertFail
_0224CC76:
	cmp r4, #0
	bne _0224CC80
	add sp, #0x4c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0224CC80:
	ldr r0, [r5, #0xc]
	bl sub_0202881C
	bl sub_020287A4
	add r4, r0, #0
	ldr r0, [r5, #0x38]
	add r1, sp, #0x18
	add r2, sp, #0x14
	bl sub_020572B8
	ldr r0, [r5, #0x28]
	bl MapMatrix_GetWidth
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	lsr r0, r4, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x3c]
	lsr r0, r4, #0x10
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x40]
	lsr r0, r4, #8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x44]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x48]
	mov r0, #0x6a
	mov r1, #1
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	str r0, [sp, #0xc]
	mov r4, #0
	ldr r0, [r0]
	add r3, r4, #0
	cmp r0, #0
	ble _0224CCEA
_0224CCD6:
	ldr r1, [sp, #0xc]
	lsl r2, r3, #2
	add r1, r1, r2
	ldr r1, [r1, #4]
	add r4, r4, r1
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, r0
	blt _0224CCD6
_0224CCEA:
	lsl r0, r0, #1
	add r0, r0, #2
	lsl r1, r0, #1
	ldr r0, [sp, #0xc]
	add r0, r0, r1
	str r0, [sp, #8]
	asr r0, r4, #1
	lsr r0, r0, #0x1e
	add r0, r4, r0
	mov r1, #1
	asr r0, r0, #2
	lsl r1, r1, #8
	str r0, [sp, #0x10]
	cmp r0, r1
	blt _0224CD0C
	bl GF_AssertFail
_0224CD0C:
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	mov r7, #0
	lsr r6, r0, #0x18
	add r5, r7, #0
_0224CD20:
	lsl r4, r5, #2
	add r0, sp, #0x3c
	ldr r0, [r0, r4]
	ldr r1, [sp, #0x10]
	bl _s32_div_f
	ldr r0, [sp, #0x10]
	add r2, r0, #0
	mul r2, r5
	add r0, r1, r2
	add r1, r7, r0
	add r0, sp, #0x2c
	str r1, [r0, r4]
	ldr r0, [r0, r4]
	lsl r1, r0, #1
	ldr r0, [sp, #8]
	cmp r6, #0
	ldrh r1, [r0, r1]
	add r0, sp, #0x1c
	str r1, [r0, r4]
	beq _0224CD56
	add r0, r7, #1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	sub r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_0224CD56:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #4
	blo _0224CD20
	ldr r0, [sp]
	ldr r1, [sp, #0x14]
	lsl r0, r0, #5
	mul r0, r1
	ldr r2, [sp, #0x18]
	mov r3, #0
	add r2, r2, r0
	add r1, sp, #0x1c
_0224CD70:
	lsl r0, r3, #2
	ldr r0, [r1, r0]
	cmp r2, r0
	bne _0224CD7E
	mov r0, #1
	str r0, [sp, #4]
	b _0224CD88
_0224CD7E:
	add r0, r3, #1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #4
	blo _0224CD70
_0224CD88:
	ldr r0, [sp, #0xc]
	bl FreeToHeap
	ldr r0, [sp, #4]
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224CD94
ov06_0224CD94: ; 0x0224CD94
	mov r2, #0x14
	strb r2, [r0]
	mov r0, #0xa
	strb r0, [r1]
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224CDA0
ov06_0224CDA0: ; 0x0224CDA0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6a
	mov r1, #0
	mov r2, #4
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	ldr r1, [r0]
	str r1, [r4]
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start ov06_0224CDB8
ov06_0224CDB8: ; 0x0224CDB8
	cmp r1, #0
	beq _0224CE2A
	ldr r1, _0224CE2C ; =gSystem + 0x60
	ldrb r1, [r1, #6]
	cmp r1, #5
	bhi _0224CE2A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224CDD0: ; jump table
	.short _0224CE2A - _0224CDD0 - 2 ; case 0
	.short _0224CDDC - _0224CDD0 - 2 ; case 1
	.short _0224CDEC - _0224CDD0 - 2 ; case 2
	.short _0224CDFC - _0224CDD0 - 2 ; case 3
	.short _0224CE0C - _0224CDD0 - 2 ; case 4
	.short _0224CE1C - _0224CDD0 - 2 ; case 5
_0224CDDC:
	add r1, r0, #0
	add r1, #0xac
	ldr r1, [r1]
	add r0, #0xb0
	str r1, [r2]
	ldr r0, [r0]
	str r0, [r3]
	bx lr
_0224CDEC:
	add r1, r0, #0
	add r1, #0xa4
	ldr r1, [r1]
	add r0, #0xa8
	str r1, [r2]
	ldr r0, [r0]
	str r0, [r3]
	bx lr
_0224CDFC:
	add r1, r0, #0
	add r1, #0xb4
	ldr r1, [r1]
	add r0, #0xb8
	str r1, [r2]
	ldr r0, [r0]
	str r0, [r3]
	bx lr
_0224CE0C:
	add r1, r0, #0
	add r1, #0xbc
	ldr r1, [r1]
	add r0, #0xc0
	str r1, [r2]
	ldr r0, [r0]
	str r0, [r3]
	bx lr
_0224CE1C:
	add r1, r0, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r0, #0xc8
	str r1, [r2]
	ldr r0, [r0]
	str r0, [r3]
_0224CE2A:
	bx lr
	.align 2, 0
_0224CE2C: .word gSystem + 0x60

	thumb_func_start ov06_0224CE30
ov06_0224CE30: ; 0x0224CE30
	push {r3, r4, r5, lr}
	mov r1, #0x5d
	mov r2, #0
	lsl r1, r1, #2
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224CE5C
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224CE4C
ov06_0224CE4C: ; 0x0224CE4C
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224CEA4
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224CE5C
ov06_0224CE5C: ; 0x0224CE5C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r1, #0x59
	ldr r0, [sp, #8]
	lsl r1, r1, #2
	add r6, r0, r1
	sub r1, #0x10
	ldr r5, _0224CEA0 ; =0x02251F18
	add r4, r0, r1
	add r7, r0, #4
_0224CE76:
	str r4, [sp]
	str r6, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [r5]
	ldr r0, [r0]
	mov r2, #0
	add r3, r7, #0
	bl ov05_021E51EC
	ldr r0, [sp, #0xc]
	add r6, r6, #4
	add r0, r0, #1
	add r4, r4, #4
	add r7, #0x54
	add r5, r5, #4
	str r0, [sp, #0xc]
	cmp r0, #4
	blt _0224CE76
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224CEA0: .word ov06_02251F18

	thumb_func_start ov06_0224CEA4
ov06_0224CEA4: ; 0x0224CEA4
	push {r4, r5, r6, lr}
	mov r6, #0x59
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #2
_0224CEAE:
	ldr r0, [r5, r6]
	bl ov05_021E4C00
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0224CEAE
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224CEC0
ov06_0224CEC0: ; 0x0224CEC0
	add r2, r0, #4
	mov r0, #0x54
	mul r0, r1
	add r0, r2, r0
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224CECC
ov06_0224CECC: ; 0x0224CECC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021E4C24
	add r6, r0, #0
	bl ov05_021E4C20
	add r7, r0, #0
	add r0, r5, #0
	bl sub_02058B2C
	str r0, [sp, #8]
	add r0, r5, #0
	bl sub_02058B4C
	add r1, r0, #0
	ldr r0, [sp, #8]
	add r2, sp, #0x20
	bl sub_02059E60
	add r0, r7, #0
	add r1, sp, #0x20
	bl sub_02059E9C
	add r0, r6, #0
	mov r1, #0x1c
	str r4, [sp, #0xc]
	str r6, [sp, #0x10]
	bl ov05_021E4C08
	add r1, r4, #0
	str r0, [sp, #0x14]
	str r5, [sp, #0x18]
	bl ov06_0224CEC0
	str r0, [sp, #0x1c]
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #0xc
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224CF38 ; =0x02251F28
	add r0, r6, #0
	add r2, sp, #0x20
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_0224CF38: .word ov06_02251F28

	thumb_func_start ov06_0224CF3C
ov06_0224CF3C: ; 0x0224CF3C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl sub_0206475C
	add r3, r0, #0
	ldr r4, [r3, #0xc]
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x10
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r4, #0
	bl MapObject_GetID
	str r0, [r5, #8]
	add r0, r4, #0
	bl sub_02058450
	str r0, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224CF6C
ov06_0224CF6C: ; 0x0224CF6C
	push {r4, lr}
	add r2, r1, #0
	ldr r4, [r2, #0x1c]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0xc]
	add r0, r4, #0
	bl sub_020582A8
	cmp r0, #1
	bne _0224CF88
	add r0, r4, #0
	mov r1, #0
	bl sub_0205EB14
_0224CF88:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224CF8C
ov06_0224CF8C: ; 0x0224CF8C
	bx lr
	.align 2, 0

	thumb_func_start ov06_0224CF90
ov06_0224CF90: ; 0x0224CF90
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r2, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #1
	beq _0224CFD0
	ldr r5, _0224CFD4 ; =0x02251F0C
	add r3, sp, #0x24
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	ldr r6, _0224CFD8 ; =0x02251F3C
	str r0, [r3]
	add r5, sp, #0
	mov r3, #4
_0224CFB0:
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	sub r3, r3, #1
	bne _0224CFB0
	ldr r0, [r6]
	add r1, sp, #0x30
	str r0, [r5]
	add r0, r2, #0
	bl sub_0206477C
	ldr r0, [r4, #0x20]
	add r1, sp, #0x30
	add r2, sp, #0
	add r3, sp, #0x24
	bl sub_0201B26C
_0224CFD0:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224CFD4: .word ov06_02251F0C
_0224CFD8: .word ov06_02251F3C

	thumb_func_start ov06_0224CFDC
ov06_0224CFDC: ; 0x0224CFDC
	push {r4, r5, r6, r7}
	add r6, r2, #0
	sub r2, r6, #1
	add r3, r6, #0
	lsl r2, r2, #0x18
	lsr r6, r2, #0x18
	cmp r3, #0
	beq _0224D038
	sub r5, r1, #1
_0224CFEE:
	ldrb r1, [r0]
	mov r4, #0
	asr r2, r1, #7
	mov r1, #1
	and r1, r2
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r5, #0
	ble _0224D020
	mov r7, #1
_0224D002:
	ldrb r1, [r0, r4]
	add r2, r0, r4
	lsl r1, r1, #1
	strb r1, [r0, r4]
	ldrb r2, [r2, #1]
	ldrb r1, [r0, r4]
	asr r2, r2, #7
	and r2, r7
	orr r1, r2
	strb r1, [r0, r4]
	add r1, r4, #1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	cmp r4, r5
	blt _0224D002
_0224D020:
	ldrb r1, [r0, r4]
	add r2, r6, #0
	lsl r1, r1, #1
	strb r1, [r0, r4]
	ldrb r1, [r0, r4]
	orr r1, r3
	strb r1, [r0, r4]
	sub r1, r6, #1
	lsl r1, r1, #0x18
	lsr r6, r1, #0x18
	cmp r2, #0
	bne _0224CFEE
_0224D038:
	pop {r4, r5, r6, r7}
	bx lr

	thumb_func_start ov06_0224D03C
ov06_0224D03C: ; 0x0224D03C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	str r0, [sp]
	add r6, r2, #0
	add r7, r3, #0
	bl sub_02089368
	add r4, r0, #0
	add r0, r5, #0
	bl sub_02089394
	add r1, sp, #4
	strh r0, [r1, #4]
	add r0, r6, #0
	bl sub_02089394
	add r1, sp, #4
	strh r0, [r1, #6]
	add r0, r7, #0
	bl sub_02089394
	add r1, sp, #4
	strh r0, [r1, #8]
	add r0, sp, #0x18
	ldrh r0, [r0, #0x10]
	bl sub_02089394
	add r1, sp, #4
	mov r2, #0
	strh r0, [r1, #0xa]
	add r3, sp, #8
	add r5, sp, #4
	add r7, r2, #0
_0224D080:
	ldrsh r0, [r3, r7]
	cmp r0, #0
	bge _0224D08E
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0224D08E:
	cmp r2, #0
	ble _0224D0C2
	mov r6, #1
	mvn r6, r6
	ldrsh r6, [r3, r6]
	cmp r0, r6
	blt _0224D0AE
	sub r0, r0, r6
	cmp r0, #0xff
	ble _0224D0AA
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0224D0AA:
	strb r0, [r5]
	b _0224D0D4
_0224D0AE:
	sub r0, r6, r0
	sub r0, r4, r0
	cmp r0, #0xff
	ble _0224D0BE
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0224D0BE:
	strb r0, [r5]
	b _0224D0D4
_0224D0C2:
	mov r0, #4
	ldrsh r0, [r1, r0]
	cmp r0, #0xff
	ble _0224D0D2
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0224D0D2:
	strb r0, [r1]
_0224D0D4:
	add r2, r2, #1
	add r3, r3, #2
	add r5, r5, #1
	cmp r2, #4
	blt _0224D080
	add r0, sp, #4
	mov r1, #4
	mov r2, #7
	bl ov06_0224CFDC
	mov r2, #0
	add r1, sp, #4
	add r4, sp, #4
	mov r3, #0xf0
_0224D0F0:
	ldrb r5, [r4, #3]
	ldrb r0, [r1]
	add r2, r2, #1
	asr r6, r5, #4
	and r5, r3
	orr r5, r6
	eor r0, r5
	strb r0, [r1]
	add r1, r1, #1
	cmp r2, #3
	blt _0224D0F0
	add r2, sp, #4
	ldrb r3, [r2, #3]
	mov r2, #0xf
	add r0, sp, #4
	and r2, r3
	lsl r2, r2, #0x18
	mov r1, #3
	lsr r2, r2, #0x18
	bl ov06_0224CFDC
	add r1, sp, #4
	ldrb r0, [r1]
	cmp r0, #8
	blo _0224D12A
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0224D12A:
	ldrb r2, [r1, #1]
	eor r2, r0
	strb r2, [r1, #1]
	ldrb r2, [r1, #2]
	eor r2, r0
	strb r2, [r1, #2]
	ldrb r2, [r1, #1]
	ldrb r1, [r1, #2]
	lsl r2, r2, #8
	orr r2, r1
	ldr r1, [sp]
	cmp r1, r2
	beq _0224D148
	mov r0, #0
	mvn r0, r0
_0224D148:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224D14C
ov06_0224D14C: ; 0x0224D14C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	str r1, [sp, #4]
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	add r4, r0, #0
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x48]
	ldr r0, [sp, #4]
	bl GetDuplicateWordNum
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2c]
	ldr r0, [sp, #8]
	bl GetDuplicateWordNum
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x28]
	ldr r0, [sp, #0xc]
	bl GetDuplicateWordNum
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x48]
	bl GetDuplicateWordNum
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x20]
	add r0, r4, #0
	bl PlayerProfile_GetTrainerID_VisibleHalf
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x2c]
	cmp r0, #0
	bls _0224D23A
_0224D1A6:
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x28]
	cmp r0, #0
	bls _0224D22A
_0224D1B0:
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x24]
	cmp r0, #0
	bls _0224D21A
_0224D1BA:
	ldr r0, [sp, #0x20]
	mov r5, #0
	cmp r0, #0
	bls _0224D20A
_0224D1C2:
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x18]
	bl RemapDuplicateWord
	add r4, r0, #0
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x14]
	bl RemapDuplicateWord
	add r6, r0, #0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	bl RemapDuplicateWord
	add r7, r0, #0
	ldr r0, [sp, #0x48]
	add r1, r5, #0
	bl RemapDuplicateWord
	str r0, [sp]
	ldr r0, [sp, #0x1c]
	add r1, r4, #0
	add r2, r6, #0
	add r3, r7, #0
	bl ov06_0224D03C
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0224D23E
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldr r0, [sp, #0x20]
	cmp r5, r0
	blo _0224D1C2
_0224D20A:
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x24]
	str r1, [sp, #0x10]
	cmp r1, r0
	blo _0224D1BA
_0224D21A:
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x14]
	cmp r1, r0
	blo _0224D1B0
_0224D22A:
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x2c]
	str r1, [sp, #0x18]
	cmp r1, r0
	blo _0224D1A6
_0224D23A:
	mov r0, #0
	mvn r0, r0
_0224D23E:
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224D244
ov06_0224D244: ; 0x0224D244
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov06_0224D270
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224D260
ov06_0224D260: ; 0x0224D260
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224D2B8
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov06_0224D270
ov06_0224D270: ; 0x0224D270
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #9
	mov r2, #0x6b
	bl ov05_021E5078
	ldr r0, [r4]
	mov r1, #9
	mov r2, #0x7f
	bl ov05_021E50AC
	ldr r0, [r4]
	mov r1, #0xa
	mov r2, #0xc
	mov r3, #1
	bl ov05_021E50D4
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _0224D2B4 ; =0x02251F74
	mov r2, #9
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #0xb
	add r3, r2, #0
	bl ov05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0224D2B4: .word ov06_02251F74

	thumb_func_start ov06_0224D2B8
ov06_0224D2B8: ; 0x0224D2B8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #9
	bl ov05_021E50A0
	ldr r0, [r4]
	mov r1, #9
	bl ov05_021E50C8
	ldr r0, [r4]
	mov r1, #0xa
	bl ov05_021E5114
	ldr r0, [r4]
	mov r1, #0xb
	bl ov05_021E506C
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224D2E0
ov06_0224D2E0: ; 0x0224D2E0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r5, r0, #0
	bl ov05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl MapObject_GetFieldSystemPtr
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x1d
	str r4, [sp, #0x18]
	bl ov05_021E4C08
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x20]
	bl sub_02058B5C
	add r0, r5, #0
	bl sub_02058B2C
	add r6, r0, #0
	add r0, r5, #0
	bl sub_02058B4C
	add r1, r0, #0
	add r0, r6, #0
	add r2, sp, #8
	bl sub_02059E60
	add r0, r5, #0
	mov r1, #2
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _0224D340 ; =0x02251F60
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224D340: .word ov06_02251F60

	thumb_func_start ov06_0224D344
ov06_0224D344: ; 0x0224D344
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x10
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x1c]
	bl MapObject_GetID
	str r0, [r4, #4]
	ldr r0, [r4, #0x1c]
	bl sub_02058450
	str r0, [r4, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x14]
	mov r1, #0xb
	add r2, sp, #0
	bl ov05_021E4EE4
	str r0, [r4, #0x20]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov06_0224D388
ov06_0224D388: ; 0x0224D388
	ldr r3, _0224D390 ; =sub_0201F744
	ldr r0, [r1, #0x20]
	bx r3
	nop
_0224D390: .word sub_0201F744

	thumb_func_start ov06_0224D394
ov06_0224D394: ; 0x0224D394
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _0224D3C2
	mov r1, #1
	ldr r0, [r4, #0x20]
	lsl r1, r1, #0xc
	bl sub_0201F854
	ldr r0, [r4, #0x20]
	bl sub_0201F8C0
	asr r1, r0, #0xb
	lsr r1, r1, #0x14
	add r1, r0, r1
	asr r0, r1, #0xc
	cmp r0, #7
	blt _0224D3C2
	add r0, r5, #0
	bl ov05_021E4DE4
_0224D3C2:
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224D3C4
ov06_0224D3C4: ; 0x0224D3C4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl sub_0206477C
	mov r0, #2
	ldr r1, [sp, #8]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #8]
	ldr r0, [r4, #0x20]
	add r1, sp, #0
	bl sub_0201F7C8
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224D3E8
ov06_0224D3E8: ; 0x0224D3E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xb
	mov r1, #8
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #8
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r1, _0224D40C ; =ov06_0224D410
	add r0, r5, #0
	add r2, r4, #0
	bl TaskManager_Call
	pop {r3, r4, r5, pc}
	nop
_0224D40C: .word ov06_0224D410

	thumb_func_start ov06_0224D410
ov06_0224D410: ; 0x0224D410
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _0224D432
	cmp r1, #1
	beq _0224D442
	cmp r1, #2
	beq _0224D45A
	b _0224D462
_0224D432:
	add r0, r5, #0
	bl ov06_0224D46C
	str r0, [r4]
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _0224D462
_0224D442:
	ldr r0, _0224D468 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0224D462
	ldr r0, [r4]
	bl ov06_0224D6A4
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _0224D462
_0224D45A:
	bl FreeToHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224D462:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0224D468: .word gSystem

	thumb_func_start ov06_0224D46C
ov06_0224D46C: ; 0x0224D46C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r4, r0, #0
	bl sub_020377A8
	add r5, r0, #0
	add r0, r4, #0
	bl FieldSystem_GetSaveData
	str r0, [sp, #0x1c]
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x18
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	mov r1, #0x1a
	mov r2, #0xc3
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [r4, #0x10]
	mov r0, #0xb
	bl MessageFormat_New
	str r0, [r4, #0x14]
	mov r2, #3
	str r2, [sp]
	mov r0, #0x1e
	str r0, [sp, #4]
	mov r0, #0x11
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #0xb
	str r0, [sp, #0x10]
	add r0, r5, #0
	add r1, r4, #0
	mov r3, #1
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	mov r3, #0xb
	add r0, r5, #0
	mov r1, #3
	mov r2, #1
	str r3, [sp, #4]
	bl LoadUserFrameGfx1
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	mov r3, #0xb
	bl DrawFrameAndWindow1
	add r0, r4, #0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r0, #0x64
	mov r1, #0xb
	bl String_New
	add r6, r0, #0
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl NewString_ReadMsgData
	add r5, r0, #0
	ldr r0, [sp, #0x1c]
	bl Save_PlayerData_GetProfileAddr
	add r2, r0, #0
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl BufferPlayersName
	ldr r0, [r4, #0x14]
	add r1, r6, #0
	add r2, r5, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0x78
	bl ov06_0224D6D0
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r6, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r5, #0
	bl String_Delete
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl NewString_ReadMsgData
	mov r1, #0
	mov r2, #1
	mov r3, #0x78
	add r5, r0, #0
	bl ov06_0224D6D0
	add r3, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r4, #0
	add r2, r5, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r5, #0
	bl String_Delete
	mov r0, #0
	ldr r5, _0224D698 ; =0x02251FAC
	str r0, [sp, #0x24]
_0224D576:
	ldr r0, [r4, #0x10]
	ldr r1, [r5]
	bl NewString_ReadMsgData
	mov r3, #4
	mov r1, #0
	ldrsh r3, [r5, r3]
	add r2, r1, #0
	add r7, r0, #0
	bl ov06_0224D6D0
	add r3, r0, #0
	mov r0, #6
	ldrsh r0, [r5, r0]
	mov r1, #0
	add r2, r7, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl String_Delete
	ldr r0, [sp, #0x24]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #5
	blt _0224D576
	mov r0, #0
	ldr r5, _0224D69C ; =0x02251F8C
	str r0, [sp, #0x14]
_0224D5BE:
	ldr r0, [r4, #0x10]
	ldr r1, [r5]
	bl NewString_ReadMsgData
	mov r3, #4
	ldrsh r3, [r5, r3]
	mov r1, #0
	mov r2, #2
	add r7, r0, #0
	bl ov06_0224D6D0
	add r3, r0, #0
	mov r0, #6
	ldrsh r0, [r5, r0]
	mov r1, #0
	add r2, r7, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	bl AddTextPrinterParameterized
	add r0, r7, #0
	bl String_Delete
	ldr r0, [sp, #0x14]
	add r5, #8
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, #4
	blt _0224D5BE
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, _0224D6A0 ; =0x02251FD4
	str r0, [sp, #0x18]
_0224D608:
	ldr r5, [sp, #0x18]
	mov r7, #0
_0224D60C:
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x20]
	add r2, r7, #0
	bl sub_0202C12C
	str r0, [sp, #0x28]
	ldr r0, [r4, #0x10]
	ldr r1, [r5]
	bl NewString_ReadMsgData
	str r0, [sp, #0x2c]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	ldr r2, [sp, #0x28]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	ldr r0, [r4, #0x14]
	ldr r2, [sp, #0x2c]
	add r1, r6, #0
	bl StringExpandPlaceholders
	mov r3, #4
	ldrsh r3, [r5, r3]
	add r0, r6, #0
	mov r1, #0
	mov r2, #2
	bl ov06_0224D6D0
	add r3, r0, #0
	mov r0, #6
	ldrsh r0, [r5, r0]
	mov r1, #0
	add r2, r6, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x2c]
	bl String_Delete
	add r7, r7, #1
	add r5, #8
	cmp r7, #4
	blt _0224D60C
	ldr r0, [sp, #0x18]
	add r0, #0x20
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, #5
	blt _0224D608
	add r0, r6, #0
	bl String_Delete
	add r0, r4, #0
	bl CopyWindowToVram
	add r0, r4, #0
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224D698: .word ov06_02251FAC
_0224D69C: .word ov06_02251F8C
_0224D6A0: .word ov06_02251FD4

	thumb_func_start ov06_0224D6A4
ov06_0224D6A4: ; 0x0224D6A4
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	bl ClearFrameAndWindow1
	add r0, r4, #0
	bl ClearWindowTilemapAndCopyToVram
	add r0, r4, #0
	bl RemoveWindow
	ldr r0, [r4, #0x10]
	bl DestroyMsgData
	ldr r0, [r4, #0x14]
	bl MessageFormat_Delete
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224D6D0
ov06_0224D6D0: ; 0x0224D6D0
	push {r4, r5, r6, lr}
	add r5, r2, #0
	add r6, r0, #0
	add r4, r3, #0
	cmp r5, #0
	bne _0224D6E0
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_0224D6E0:
	add r0, r1, #0
	add r1, r6, #0
	mov r2, #0
	bl sub_02002E14
	cmp r5, #1
	beq _0224D6F4
	cmp r5, #2
	beq _0224D6FE
	b _0224D702
_0224D6F4:
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #1
	sub r0, r4, r0
	pop {r4, r5, r6, pc}
_0224D6FE:
	sub r0, r4, r0
	pop {r4, r5, r6, pc}
_0224D702:
	bl GF_AssertFail
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224D70C
ov06_0224D70C: ; 0x0224D70C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0xc1
	lsl r1, r1, #2
	add r5, r0, #0
	add r7, r2, #0
	bl AllocFromHeap
	mov r2, #0xc1
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	str r5, [r4, #0x18]
	str r7, [r4, #0x14]
	str r6, [r4, #8]
	add r0, r6, #0
	bl Save_FashionData_Get
	bl Save_FashionData_GetFashionCase
	str r0, [r4, #0xc]
	add r0, r6, #0
	bl Save_Bag_Get
	str r0, [r4, #0x10]
	mov r2, #0x81
	ldr r3, [r4, #0x18]
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	bl NewMsgDataFromNarc
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	bl ov06_0224DBA8
	add r0, r4, #0
	bl ov06_0224DBCC
	add r0, r4, #0
	bl ov06_0224DC3C
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224D76C
ov06_0224D76C: ; 0x0224D76C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl DestroyMsgData
	add r0, r4, #0
	bl ov06_0224DC28
	add r0, r4, #0
	bl ov06_0224DC50
	mov r2, #0xc1
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224D79C
ov06_0224D79C: ; 0x0224D79C
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0xc
	bls _0224D7AA
	b _0224DB9A
_0224D7AA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224D7B6: ; jump table
	.short _0224D7D0 - _0224D7B6 - 2 ; case 0
	.short _0224D80E - _0224D7B6 - 2 ; case 1
	.short _0224D84E - _0224D7B6 - 2 ; case 2
	.short _0224D8A6 - _0224D7B6 - 2 ; case 3
	.short _0224D8DC - _0224D7B6 - 2 ; case 4
	.short _0224D97E - _0224D7B6 - 2 ; case 5
	.short _0224D992 - _0224D7B6 - 2 ; case 6
	.short _0224DA82 - _0224D7B6 - 2 ; case 7
	.short _0224DAD2 - _0224D7B6 - 2 ; case 8
	.short _0224DAFE - _0224D7B6 - 2 ; case 9
	.short _0224DB2A - _0224D7B6 - 2 ; case 10
	.short _0224DB3E - _0224D7B6 - 2 ; case 11
	.short _0224DB6C - _0224D7B6 - 2 ; case 12
_0224D7D0:
	mov r3, #0x55
	lsl r3, r3, #2
	add r0, r4, r3
	sub r3, r3, #4
	ldr r1, [r4, #0x14]
	ldr r2, [r4, #0x18]
	ldr r3, [r4, r3]
	bl ov06_0224DC5C
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #4
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb
	str r0, [r4]
	mov r0, #1
	str r0, [r4, #4]
	b _0224DB9A
_0224D80E:
	ldr r0, [r4, #0xc]
	ldr r1, _0224DB5C ; =0x02252080
	mov r2, #0x16
	bl ov06_0224E4B4
	cmp r0, #0
	beq _0224D848
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb
	str r0, [r4]
	mov r0, #0xc
	str r0, [r4, #4]
	b _0224DB9A
_0224D848:
	mov r0, #2
	str r0, [r4]
	b _0224DB9A
_0224D84E:
	mov r2, #0x5a
	lsl r2, r2, #2
	add r0, r4, r2
	sub r2, #0x20
	ldr r1, [r4, #0x14]
	ldr r2, [r4, r2]
	ldr r3, [r4, #0x18]
	bl ov06_0224DE60
	ldr r0, [r4, #0x18]
	mov r1, #0x5a
	str r0, [sp]
	ldr r0, [r4, #0x14]
	lsl r1, r1, #2
	str r0, [sp, #4]
	mov r0, #0x2f
	lsl r0, r0, #4
	ldr r2, _0224DB5C ; =0x02252080
	ldr r3, [r4, #0x10]
	add r0, r4, r0
	add r1, r4, r1
	bl ov06_0224E3FC
	mov r1, #0x52
	mov r0, #0x16
	lsl r1, r1, #2
	str r0, [sp]
	ldr r0, [r4, r1]
	add r1, #0x3c
	str r0, [sp, #4]
	mov r0, #0x2f
	lsl r0, r0, #4
	add r0, r4, r0
	str r0, [sp, #8]
	ldr r0, _0224DB60 ; =ov06_0224E410
	ldr r3, _0224DB5C ; =0x02252080
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x1c]
	str r0, [sp, #0x10]
	add r0, r4, r1
	ldr r1, [r4, #0x14]
	ldr r2, [r4, #0x18]
	bl ov06_0224DFA8
_0224D8A6:
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E24C
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #6
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xa
	str r0, [r4]
	mov r0, #4
	str r0, [r4, #4]
	b _0224DB9A
_0224D8DC:
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E1E4
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0224D942
	sub r1, r1, #1
	cmp r0, r1
	beq _0224D942
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x12
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x14]
	mov r1, #3
	add r3, r2, #0
	bl FillBgTilemapRect
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E274
	mov r0, #0x2b
	lsl r0, r0, #4
	ldrh r0, [r4, r0]
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [sp]
	add r0, r4, r1
	sub r1, #0xc
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x18]
	ldr r3, _0224DB5C ; =0x02252080
	bl ov06_0224DD50
	mov r0, #0xa
	str r0, [r4]
	mov r0, #5
	str r0, [r4, #4]
	ldr r0, _0224DB64 ; =0x000005DC
	bl PlaySE
	b _0224DB9A
_0224D942:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0224D94C
	b _0224DB9A
_0224D94C:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xb
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb
	str r0, [r4]
	mov r0, #0xc
	str r0, [r4, #4]
	ldr r0, _0224DB64 ; =0x000005DC
	bl PlaySE
	b _0224DB9A
_0224D97E:
	mov r0, #0xb9
	lsl r0, r0, #2
	ldr r1, [r4, #0x14]
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	bl ov06_0224E470
	mov r0, #6
	str r0, [r4]
	b _0224DB9A
_0224D992:
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E4A4
	cmp r0, #0
	bne _0224DA68
	mov r2, #0x2b
	lsl r2, r2, #4
	ldrh r2, [r4, r2]
	ldr r0, [r4, #0x10]
	ldr r1, _0224DB5C ; =0x02252080
	ldr r3, [r4, #0x18]
	bl ov06_0224E4E4
	cmp r0, #0
	bne _0224D9EA
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #9
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb
	str r0, [r4]
	mov r0, #3
	str r0, [r4, #4]
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E498
	b _0224DB9A
_0224D9EA:
	mov r2, #0x2b
	lsl r2, r2, #4
	ldrh r2, [r4, r2]
	ldr r0, [r4, #0xc]
	ldr r1, _0224DB5C ; =0x02252080
	bl ov06_0224E510
	cmp r0, #0
	bne _0224DA32
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xa
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E498
	mov r0, #0xb
	str r0, [r4]
	mov r0, #3
	str r0, [r4, #4]
	b _0224DB9A
_0224DA32:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #8
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E498
	mov r0, #0xb
	str r0, [r4]
	mov r0, #7
	str r0, [r4, #4]
	b _0224DB9A
_0224DA68:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0224DA72
	b _0224DB9A
_0224DA72:
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E498
	mov r0, #3
	str r0, [r4]
	b _0224DB9A
_0224DA82:
	ldr r0, [r4, #0x18]
	mov r3, #0x2b
	str r0, [sp]
	lsl r3, r3, #4
	ldrh r3, [r4, r3]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, _0224DB5C ; =0x02252080
	bl ov06_0224E520
	mov r0, #0x2b
	lsl r0, r0, #4
	ldrh r0, [r4, r0]
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [sp]
	add r0, r4, r1
	sub r1, #0xc
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x18]
	ldr r3, _0224DB5C ; =0x02252080
	bl ov06_0224DDD8
	ldr r0, [r4, #0xc]
	ldr r1, _0224DB5C ; =0x02252080
	mov r2, #0x16
	bl ov06_0224E4B4
	cmp r0, #0
	beq _0224DAC8
	mov r0, #0xb
	str r0, [r4]
	mov r0, #8
	str r0, [r4, #4]
	b _0224DB9A
_0224DAC8:
	mov r0, #0xb
	str r0, [r4]
	mov r0, #3
	str r0, [r4, #4]
	b _0224DB9A
_0224DAD2:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0xd
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb
	str r0, [r4]
	mov r0, #9
	str r0, [r4, #4]
	b _0224DB9A
_0224DAFE:
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #5
	bl NewString_ReadMsgData
	add r5, r0, #0
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r2, [r4, #0x18]
	add r0, r4, r0
	add r1, r5, #0
	bl ov06_0224DCD8
	add r0, r5, #0
	bl String_Delete
	mov r0, #0xb
	str r0, [r4]
	mov r0, #0xc
	str r0, [r4, #4]
	b _0224DB9A
_0224DB2A:
	mov r0, #0x55
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224DD28
	cmp r0, #0
	beq _0224DB9A
	ldr r0, [r4, #4]
	str r0, [r4]
	b _0224DB9A
_0224DB3E:
	mov r0, #0x55
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224DD28
	cmp r0, #0
	beq _0224DB9A
	ldr r0, _0224DB68 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0224DB9A
	ldr r0, [r4, #4]
	str r0, [r4]
	b _0224DB9A
	.align 2, 0
_0224DB5C: .word ov06_02252080
_0224DB60: .word ov06_0224E410
_0224DB64: .word 0x000005DC
_0224DB68: .word gSystem
_0224DB6C:
	mov r0, #0x55
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224DCB4
	mov r0, #0x5a
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224DED8
	mov r0, #0x61
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E174
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	bl ov06_0224E498
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, pc}
_0224DB9A:
	ldr r0, [r4, #0x1c]
	bl sub_0201FDEC
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224DBA8
ov06_0224DBA8: ; 0x0224DBA8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl Save_PlayerData_GetOptionsAddr
	add r4, r0, #0
	bl Options_GetFrame
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r4, #0
	bl Options_GetTextFrameDelay
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224DBCC
ov06_0224DBCC: ; 0x0224DBCC
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4, #0x18]
	mov r2, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	mov r3, #0xa
	bl sub_0200CD68
	mov r1, #6
	ldr r2, [r4, #0x18]
	mov r0, #0
	lsl r1, r1, #6
	bl LoadFontPal1
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #0x18]
	mov r1, #3
	str r0, [sp, #4]
	ldr r0, [r4, #0x14]
	mov r2, #0x1f
	mov r3, #0xb
	bl LoadUserFrameGfx1
	mov r1, #0x1a
	ldr r2, [r4, #0x18]
	mov r0, #0
	lsl r1, r1, #4
	bl LoadFontPal0
	ldr r0, [r4, #0x14]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224DC28
ov06_0224DC28: ; 0x0224DC28
	push {r3, lr}
	ldr r0, [r0, #0x14]
	mov r1, #3
	bl BgClearTilemapBufferAndCommit
	mov r0, #0
	mov r1, #1
	bl sub_02054590
	pop {r3, pc}

	thumb_func_start ov06_0224DC3C
ov06_0224DC3C: ; 0x0224DC3C
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r2, [r4, #0x18]
	mov r0, #2
	add r1, #0x20
	bl sub_02008C9C
	str r0, [r4, #0x1c]
	pop {r4, pc}

	thumb_func_start ov06_0224DC50
ov06_0224DC50: ; 0x0224DC50
	ldr r3, _0224DC58 ; =sub_0201FD58
	ldr r0, [r0, #0x1c]
	bx r3
	nop
_0224DC58: .word sub_0201FD58

	thumb_func_start ov06_0224DC5C
ov06_0224DC5C: ; 0x0224DC5C
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	cmp r0, #1
	beq _0224DCAE
	str r3, [r5, #8]
	add r0, r2, #0
	mov r1, #1
	bl AllocWindows
	str r0, [r5, #4]
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #0x28
	str r0, [sp, #0x10]
	ldr r1, [r5, #4]
	add r0, r4, #0
	mov r2, #3
	mov r3, #2
	bl AddWindowParameterized
	ldr r0, [r5, #4]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r0, [r5, #4]
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl DrawFrameAndWindow2
	mov r0, #1
	str r0, [r5]
_0224DCAE:
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224DCB4
ov06_0224DCB4: ; 0x0224DCB4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0224DCD6
	ldr r0, [r4, #4]
	bl ClearWindowTilemapAndCopyToVram
	ldr r0, [r4, #4]
	bl RemoveWindow
	ldr r0, [r4, #4]
	mov r1, #1
	bl WindowArray_Delete
	mov r0, #0
	str r0, [r4]
_0224DCD6:
	pop {r4, pc}

	thumb_func_start ov06_0224DCD8
ov06_0224DCD8: ; 0x0224DCD8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r4, r1, #0
	add r6, r2, #0
	cmp r0, #0
	beq _0224DCEC
	bl GF_AssertFail
_0224DCEC:
	ldr r0, [r5, #4]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r4, #0
	add r1, r6, #0
	bl StringDup
	str r0, [r5, #0x10]
	mov r3, #0
	str r3, [sp]
	ldr r0, [r5, #8]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, _0224DD24 ; =0x0001020F
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r5, #0x10]
	bl AddTextPrinterParameterized2
	str r0, [r5, #0xc]
	ldr r0, [r5, #4]
	bl CopyWindowToVram
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_0224DD24: .word 0x0001020F

	thumb_func_start ov06_0224DD28
ov06_0224DD28: ; 0x0224DD28
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	bne _0224DD4C
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _0224DD48
	bl String_Delete
	mov r0, #0
	str r0, [r4, #0x10]
_0224DD48:
	mov r0, #1
	pop {r4, pc}
_0224DD4C:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov06_0224DD50
ov06_0224DD50: ; 0x0224DD50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r2, #0
	str r0, [sp, #8]
	add r0, r7, #0
	add r4, r1, #0
	add r5, r3, #0
	bl MessageFormat_New
	add r6, r0, #0
	mov r0, #0xc8
	add r1, r7, #0
	bl String_New
	str r0, [sp, #0xc]
	add r0, r4, #0
	mov r1, #7
	bl NewString_ReadMsgData
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x10]
	add r4, r1, #0
	mov r0, #0xc
	mul r4, r0
	add r2, r5, r4
	ldr r2, [r2, #4]
	add r0, r6, #0
	mov r1, #0
	add r2, #0x95
	bl BufferItemNamePlural
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r2, r5, r4
	ldr r2, [r2, #8]
	add r0, r6, #0
	mov r3, #3
	bl BufferIntegerAsString
	ldr r2, [r5, r4]
	add r0, r6, #0
	mov r1, #2
	bl BufferFashionName
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r0, r6, #0
	bl StringExpandPlaceholders
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r2, r7, #0
	bl ov06_0224DCD8
	add r0, r6, #0
	bl MessageFormat_Delete
	ldr r0, [sp, #0xc]
	bl String_Delete
	ldr r0, [sp, #0x10]
	bl String_Delete
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224DDD8
ov06_0224DDD8: ; 0x0224DDD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r2, #0
	str r0, [sp, #8]
	add r0, r7, #0
	add r4, r1, #0
	add r5, r3, #0
	bl MessageFormat_New
	add r6, r0, #0
	mov r0, #0xc8
	add r1, r7, #0
	bl String_New
	str r0, [sp, #0xc]
	add r0, r4, #0
	mov r1, #0xc
	bl NewString_ReadMsgData
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x10]
	add r4, r1, #0
	mov r0, #0xc
	mul r4, r0
	add r2, r5, r4
	ldr r2, [r2, #4]
	add r0, r6, #0
	mov r1, #0
	add r2, #0x95
	bl BufferItemNamePlural
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r2, r5, r4
	ldr r2, [r2, #8]
	add r0, r6, #0
	mov r3, #3
	bl BufferIntegerAsString
	ldr r2, [r5, r4]
	add r0, r6, #0
	mov r1, #2
	bl BufferFashionName
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r0, r6, #0
	bl StringExpandPlaceholders
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r2, r7, #0
	bl ov06_0224DCD8
	add r0, r6, #0
	bl MessageFormat_Delete
	ldr r0, [sp, #0xc]
	bl String_Delete
	ldr r0, [sp, #0x10]
	bl String_Delete
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224DE60
ov06_0224DE60: ; 0x0224DE60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r0, #0
	ldr r0, [r6]
	add r4, r1, #0
	add r7, r2, #0
	str r3, [sp, #0x14]
	cmp r0, #1
	beq _0224DED2
	add r0, r3, #0
	mov r1, #1
	bl AllocWindows
	str r0, [r6, #4]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x94
	str r0, [sp, #0x10]
	ldr r1, [r6, #4]
	add r0, r4, #0
	mov r2, #3
	mov r3, #1
	bl AddWindowParameterized
	ldr r0, [sp, #0x14]
	bl MessageFormat_New
	str r0, [r6, #8]
	mov r4, #0
	add r5, r6, #0
_0224DEA8:
	add r1, r4, #0
	add r0, r7, #0
	add r1, #0x10
	bl NewString_ReadMsgData
	str r0, [r5, #0x10]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _0224DEA8
	ldr r1, [sp, #0x14]
	mov r0, #0x20
	bl String_New
	str r0, [r6, #0xc]
	ldr r0, [r6, #4]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r0, #1
	str r0, [r6]
_0224DED2:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224DED8
ov06_0224DED8: ; 0x0224DED8
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6]
	cmp r0, #0
	beq _0224DF18
	mov r4, #0
	add r5, r6, #0
_0224DEE6:
	ldr r0, [r5, #0x10]
	bl String_Delete
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #3
	blt _0224DEE6
	ldr r0, [r6, #0xc]
	bl String_Delete
	ldr r0, [r6, #8]
	bl MessageFormat_Delete
	ldr r0, [r6, #4]
	bl ClearWindowTilemapAndCopyToVram
	ldr r0, [r6, #4]
	bl RemoveWindow
	ldr r0, [r6, #4]
	mov r1, #1
	bl WindowArray_Delete
	mov r0, #0
	str r0, [r6]
_0224DF18:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224DF1C
ov06_0224DF1C: ; 0x0224DF1C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r1, #0
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r6, #0x95
	add r4, r2, #0
	mov r1, #0
	add r2, r6, #0
	add r7, r3, #0
	bl BufferItemName
	mov r1, #1
	str r1, [sp]
	str r1, [sp, #4]
	ldr r0, [r5, #8]
	add r2, r4, #0
	mov r3, #3
	bl BufferIntegerAsString
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r5, #8]
	mov r1, #2
	add r2, r7, #0
	mov r3, #3
	bl BufferIntegerAsString
	ldr r0, [r5, #4]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r7, #0
	add r6, r5, #0
	add r4, r7, #0
_0224DF64:
	ldr r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r6, #0x10]
	bl StringExpandPlaceholders
	mov r1, #0
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0224DFA4 ; =0x0001020F
	add r3, r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r5, #4]
	ldr r2, [r5, #0xc]
	bl AddTextPrinterParameterized2
	add r7, r7, #1
	add r6, r6, #4
	add r4, #0x10
	cmp r7, #3
	blt _0224DF64
	ldr r0, [r5, #4]
	mov r1, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl DrawFrameAndWindow1
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224DFA4: .word 0x0001020F

	thumb_func_start ov06_0224DFA8
ov06_0224DFA8: ; 0x0224DFA8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	add r5, r0, #0
	ldr r0, [sp, #0x78]
	add r4, r1, #0
	str r0, [sp, #0x78]
	ldr r0, [r5]
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	cmp r0, #1
	bne _0224DFC0
	b _0224E164
_0224DFC0:
	ldr r0, [sp, #0x78]
	mov r1, #1
	mov r2, #0x12
	str r1, [r5]
	add r0, r0, #1
	lsl r2, r2, #4
	str r0, [r5, r2]
	add r0, r2, #0
	ldr r3, [sp, #0x80]
	add r0, #0x10
	str r3, [r5, r0]
	ldr r0, [sp, #0x84]
	add r2, #0x14
	str r0, [r5, r2]
	ldr r0, [sp, #0x14]
	bl AllocWindows
	str r0, [r5, #4]
	mov r0, #1
	str r0, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	mov r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xe8
	str r0, [sp, #0x10]
	ldr r1, [r5, #4]
	add r0, r4, #0
	mov r2, #3
	mov r3, #0x11
	bl AddWindowParameterized
	ldr r0, [sp, #0x14]
	bl MessageFormat_New
	mov r1, #0x49
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r1, [sp, #0x14]
	mov r0, #0x20
	bl String_New
	mov r1, #0x4a
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [sp, #0x7c]
	mov r1, #0x10
	bl NewString_ReadMsgData
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x78]
	mov r7, #0
	cmp r0, #0
	bls _0224E084
	add r6, r5, #0
	add r4, r5, #0
_0224E034:
	mov r0, #0x49
	ldr r2, [sp, #0x18]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r2, [r2]
	mov r1, #0
	bl BufferFashionName
	mov r0, #0x49
	mov r1, #0x4a
	lsl r0, r0, #2
	lsl r1, r1, #2
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, [sp, #0x1c]
	bl StringExpandPlaceholders
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x14]
	bl StringDup
	add r1, r6, #0
	add r1, #0xc4
	str r0, [r1]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r6, r6, #4
	str r0, [r4, #0xc]
	str r7, [r4, #0x10]
	ldr r0, [sp, #0x18]
	add r7, r7, #1
	add r0, #0xc
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x78]
	add r4, #8
	cmp r7, r0
	blo _0224E034
_0224E084:
	ldr r0, [sp, #0x78]
	add r4, r5, #0
	lsl r6, r0, #2
	ldr r0, [sp, #0x7c]
	add r4, #0xc4
	mov r1, #0x13
	bl NewString_ReadMsgData
	str r0, [r4, r6]
	ldr r0, [sp, #0x78]
	lsl r1, r0, #3
	ldr r0, [r4, r6]
	add r1, r5, r1
	str r0, [r1, #0xc]
	ldr r0, [sp, #0x78]
	str r0, [r1, #0x10]
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MessageFormat_Delete
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl String_Delete
	ldr r0, [sp, #0x1c]
	bl String_Delete
	ldr r3, [sp, #0x14]
	ldr r0, [r5, #4]
	ldr r1, _0224E168 ; =ov06_022523A0
	lsl r3, r3, #0x18
	str r0, [r1, #0xc]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	lsr r3, r3, #0x18
	strh r0, [r1, #0x10]
	add r0, r5, #0
	add r0, #0xc
	str r0, [r1]
	mov r1, #0
	ldr r0, _0224E16C ; =ov06_022523A0
	add r2, r1, #0
	bl ListMenuInit
	str r0, [r5, #8]
	ldr r0, [r5, #4]
	mov r1, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl DrawFrameAndWindow1
	mov r7, #0x4e
	mov r4, #0
	add r6, r5, #0
	lsl r7, r7, #2
_0224E0F8:
	ldr r2, [sp, #0x14]
	mov r0, #1
	add r1, r4, #0
	bl sub_02008DEC
	str r0, [r6, r7]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, #4
	blt _0224E0F8
	ldr r2, [sp, #0x14]
	add r0, sp, #0x40
	add r1, r5, #0
	bl ov06_0224E294
	ldr r0, [sp, #0x88]
	mov r6, #0
	str r0, [sp, #0x20]
	add r0, sp, #0x40
	str r0, [sp, #0x24]
	mov r0, #1
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x14]
	mov r7, #0x56
	str r0, [sp, #0x3c]
	mov r0, #3
	lsl r0, r0, #0x12
	ldr r4, _0224E170 ; =0x02252074
	str r6, [sp, #0x34]
	str r0, [sp, #0x28]
	lsl r7, r7, #2
_0224E136:
	ldrb r0, [r4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x2c]
	add r0, sp, #0x20
	bl sub_0201FF84
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl sub_02020130
	ldr r0, [r5, r7]
	mov r1, #1
	bl sub_020200BC
	add r6, r6, #1
	add r4, r4, #1
	add r5, r5, #4
	cmp r6, #2
	blt _0224E136
_0224E164:
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224E168: .word ov06_022523A0
_0224E16C: .word ov06_022523A0
_0224E170: .word ov06_02252074

	thumb_func_start ov06_0224E174
ov06_0224E174: ; 0x0224E174
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6]
	cmp r0, #0
	beq _0224E1E2
	mov r7, #0x56
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_0224E186:
	ldr r0, [r5, r7]
	bl sub_0201FFC8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _0224E186
	add r0, r6, #0
	bl ov06_0224E36C
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	mov r5, #0
	cmp r0, #0
	ble _0224E1C0
	mov r7, #0x12
	add r4, r6, #0
	lsl r7, r7, #4
_0224E1AC:
	add r0, r4, #0
	add r0, #0xc4
	ldr r0, [r0]
	bl String_Delete
	ldr r0, [r6, r7]
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, r0
	blt _0224E1AC
_0224E1C0:
	mov r1, #0
	ldr r0, [r6, #8]
	add r2, r1, #0
	bl DestroyListMenu
	ldr r0, [r6, #4]
	bl ClearWindowTilemapAndCopyToVram
	ldr r0, [r6, #4]
	bl RemoveWindow
	ldr r0, [r6, #4]
	mov r1, #1
	bl WindowArray_Delete
	mov r0, #1
	str r0, [r6]
_0224E1E2:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224E1E4
ov06_0224E1E4: ; 0x0224E1E4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	bl ListMenu_ProcessInput
	mov r1, #0
	add r4, r0, #0
	mvn r1, r1
	cmp r4, r1
	bne _0224E22A
	ldr r0, [r5, #8]
	add r1, sp, #0
	bl ListMenuGetCurrentItemArrayId
	mov r2, #0x4b
	add r0, sp, #0
	lsl r2, r2, #2
	ldrh r1, [r0]
	ldrh r0, [r5, r2]
	cmp r0, r1
	beq _0224E242
	strh r1, [r5, r2]
	add r0, r2, #4
	ldrh r1, [r5, r2]
	add r2, #8
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	blx r2
	ldr r0, _0224E248 ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	bl ov06_0224E39C
	b _0224E242
_0224E22A:
	sub r0, r1, #1
	cmp r4, r0
	beq _0224E242
	mov r0, #0x4b
	lsl r0, r0, #2
	ldrh r2, [r5, r0]
	sub r0, #0xc
	ldr r0, [r5, r0]
	sub r0, r0, #1
	cmp r2, r0
	bne _0224E242
	sub r4, r1, #1
_0224E242:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_0224E248: .word 0x000005DC

	thumb_func_start ov06_0224E24C
ov06_0224E24C: ; 0x0224E24C
	push {r4, lr}
	mov r2, #0x13
	lsl r2, r2, #4
	add r4, r0, #0
	sub r1, r2, #4
	ldr r0, [r4, r2]
	add r2, r2, #4
	ldrh r1, [r4, r1]
	ldr r2, [r4, r2]
	blx r2
	ldr r0, [r4, #4]
	mov r1, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl DrawFrameAndWindow1
	add r0, r4, #0
	bl ov06_0224E39C
	pop {r4, pc}

	thumb_func_start ov06_0224E274
ov06_0224E274: ; 0x0224E274
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224E294
ov06_0224E294: ; 0x0224E294
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	add r5, r1, #0
	ldr r1, _0224E368 ; =0x00001388
	add r6, r0, #0
	add r4, r2, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	lsr r0, r1, #4
	str r4, [sp, #8]
	ldr r0, [r5, r0]
	mov r1, #0x3e
	mov r2, #4
	mov r3, #0
	bl sub_02008F34
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, _0224E368 ; =0x00001388
	sub r1, #0xc
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r4, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x3e
	mov r2, #0xa
	mov r3, #0
	bl sub_02008FEC
	mov r1, #0x53
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, _0224E368 ; =0x00001388
	sub r1, #0xc
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r4, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x3e
	mov r2, #5
	mov r3, #0
	bl sub_020090AC
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, _0224E368 ; =0x00001388
	sub r1, #0xc
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	str r4, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x3e
	mov r2, #6
	mov r3, #0
	bl sub_020090AC
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0xc
	ldr r0, [r5, r1]
	bl sub_02009B04
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02009D68
	ldr r1, _0224E368 ; =0x00001388
	mov r0, #0
	mov r3, #0x4f
	str r1, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsr r2, r1, #4
	ldr r2, [r5, r2]
	lsl r3, r3, #2
	str r2, [sp, #0x14]
	ldr r2, [r5, r3]
	str r2, [sp, #0x18]
	add r2, r3, #4
	ldr r2, [r5, r2]
	add r3, #8
	str r2, [sp, #0x1c]
	ldr r2, [r5, r3]
	add r3, r1, #0
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r6, #0
	add r2, r1, #0
	bl sub_02008AA4
	add sp, #0x2c
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0224E368: .word 0x00001388

	thumb_func_start ov06_0224E36C
ov06_0224E36C: ; 0x0224E36C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02009C0C
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_02009E04
	mov r6, #0x4e
	mov r4, #0
	lsl r6, r6, #2
_0224E38A:
	ldr r0, [r5, r6]
	bl sub_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0224E38A
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224E39C
ov06_0224E39C: ; 0x0224E39C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #8]
	add r1, sp, #0
	mov r2, #0
	bl ListMenuGetScrollAndRow
	add r0, sp, #0
	ldrh r0, [r0]
	cmp r0, #0
	bne _0224E3C2
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	b _0224E3CE
_0224E3C2:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_020200A0
_0224E3CE:
	add r0, sp, #0
	ldrh r2, [r0]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	sub r1, r1, #7
	cmp r2, r1
	blt _0224E3EC
	add r0, #0x3c
	ldr r0, [r4, r0]
	mov r1, #0
	bl sub_020200A0
	add sp, #4
	pop {r3, r4, pc}
_0224E3EC:
	add r0, #0x3c
	ldr r0, [r4, r0]
	mov r1, #1
	bl sub_020200A0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224E3FC
ov06_0224E3FC: ; 0x0224E3FC
	push {r3, r4}
	ldr r4, [sp, #0xc]
	str r4, [r0, #4]
	str r1, [r0, #8]
	str r2, [r0, #0xc]
	ldr r1, [sp, #8]
	str r3, [r0, #0x10]
	str r1, [r0]
	pop {r3, r4}
	bx lr

	thumb_func_start ov06_0224E410
ov06_0224E410: ; 0x0224E410
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	cmp r1, #0x16
	bhs _0224E448
	add r4, r1, #0
	mov r0, #0xc
	mul r4, r0
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x10]
	add r1, r1, r4
	ldr r1, [r1, #4]
	ldr r2, [r5]
	add r1, #0x95
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl Bag_GetQuantity
	ldr r1, [r5, #0xc]
	add r3, r0, #0
	add r2, r1, r4
	ldr r1, [r2, #4]
	ldr r0, [r5, #8]
	ldr r2, [r2, #8]
	bl ov06_0224DF1C
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0224E448:
	mov r0, #0xa
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	mov r2, #0
	ldr r0, [r5, #4]
	mov r1, #3
	add r3, r2, #0
	bl FillBgTilemapRect
	ldr r0, [r5, #4]
	mov r1, #3
	bl BgCommitTilemapBufferToVram
	add sp, #0x10
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224E470
ov06_0224E470: ; 0x0224E470
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r2, #0
	cmp r0, #1
	beq _0224E492
	add r0, r1, #0
	ldr r1, _0224E494 ; =0x02252078
	mov r2, #0x1f
	mov r3, #0xb
	str r4, [sp]
	bl Std_CreateYesNoMenu
	str r0, [r5, #4]
	str r4, [r5, #8]
	mov r0, #1
	str r0, [r5]
_0224E492:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224E494: .word ov06_02252078

	thumb_func_start ov06_0224E498
ov06_0224E498: ; 0x0224E498
	ldr r1, [r0]
	cmp r1, #0
	beq _0224E4A2
	mov r1, #0
	str r1, [r0]
_0224E4A2:
	bx lr

	thumb_func_start ov06_0224E4A4
ov06_0224E4A4: ; 0x0224E4A4
	ldr r3, _0224E4B0 ; =sub_020021AC
	add r1, r0, #0
	ldr r0, [r1, #4]
	ldr r1, [r1, #8]
	bx r3
	nop
_0224E4B0: .word sub_020021AC

	thumb_func_start ov06_0224E4B4
ov06_0224E4B4: ; 0x0224E4B4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	ldr r4, _0224E4E0 ; =0x00000000
	beq _0224E4DA
_0224E4C0:
	ldr r1, [r5]
	add r0, r7, #0
	mov r2, #1
	bl sub_020270D8
	cmp r0, #1
	bne _0224E4D2
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224E4D2:
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r6
	blo _0224E4C0
_0224E4DA:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224E4E0: .word 0x00000000

	thumb_func_start ov06_0224E4E4
ov06_0224E4E4: ; 0x0224E4E4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r2, #0
	mov r1, #0xc
	mul r4, r1
	add r1, r5, r4
	ldr r1, [r1, #4]
	add r2, r3, #0
	add r1, #0x95
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl Bag_GetQuantity
	add r1, r5, r4
	ldr r1, [r1, #8]
	cmp r0, r1
	blo _0224E50A
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224E50A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224E510
ov06_0224E510: ; 0x0224E510
	mov r3, #0xc
	mul r3, r2
	ldr r1, [r1, r3]
	ldr r3, _0224E51C ; =sub_020270D8
	mov r2, #1
	bx r3
	.align 2, 0
_0224E51C: .word sub_020270D8

	thumb_func_start ov06_0224E520
ov06_0224E520: ; 0x0224E520
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0xc
	mul r1, r3
	add r3, r2, r1
	ldr r4, [r3, #4]
	ldr r1, [r2, r1]
	ldr r5, [r3, #8]
	add r4, #0x95
	mov r2, #1
	bl sub_020271A4
	lsl r1, r4, #0x10
	lsl r2, r5, #0x10
	ldr r3, [sp, #0x10]
	add r0, r6, #0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl Bag_TakeItem
	cmp r0, #1
	beq _0224E550
	bl GF_AssertFail
_0224E550:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224E554
ov06_0224E554: ; 0x0224E554
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r6, r1, #0
	ldr r1, _0224E5C8 ; =0x000001FB
	add r2, sp, #4
	add r3, sp, #0
	add r5, r0, #0
	bl sub_0204A9F0
	cmp r0, #0
	beq _0224E5C0
	mov r0, #4
	mov r1, #0x18
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	strb r6, [r4, #0xc]
	mov r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
	ldr r0, [r5, #0x28]
	bl MapMatrix_GetWidth
	add r1, r0, #0
	ldr r0, [sp]
	add r2, sp, #0x14
	bl sub_0204AAD4
	ldr r1, [sp, #4]
	add r0, sp, #8
	bl ov05_021E7EA0
	add r3, sp, #8
	ldmia r3!, {r0, r1}
	add r2, r4, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r1, [r4]
	ldr r0, [sp, #0x14]
	add r2, r4, #0
	add r0, r1, r0
	str r0, [r4]
	ldr r1, [r4, #8]
	ldr r0, [sp, #0x1c]
	add r0, r1, r0
	str r0, [r4, #8]
	ldr r0, [r5, #0x10]
	ldr r1, _0224E5CC ; =ov06_0224E5D0
	bl TaskManager_Call
	add sp, #0x20
	pop {r4, r5, r6, pc}
_0224E5C0:
	bl GF_AssertFail
	add sp, #0x20
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224E5C8: .word 0x000001FB
_0224E5CC: .word ov06_0224E5D0

	thumb_func_start ov06_0224E5D0
ov06_0224E5D0: ; 0x0224E5D0
	push {r4, r5, r6, lr}
	sub sp, #0x30
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldrb r1, [r4, #0xf]
	cmp r1, #5
	bls _0224E5EC
	b _0224E74C
_0224E5EC:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224E5F8: ; jump table
	.short _0224E604 - _0224E5F8 - 2 ; case 0
	.short _0224E644 - _0224E5F8 - 2 ; case 1
	.short _0224E6C4 - _0224E5F8 - 2 ; case 2
	.short _0224E6F0 - _0224E5F8 - 2 ; case 3
	.short _0224E702 - _0224E5F8 - 2 ; case 4
	.short _0224E742 - _0224E5F8 - 2 ; case 5
_0224E604:
	ldr r0, _0224E754 ; =0x00000205
	ldr r1, [r6, #0x2c]
	bl ov05_021F4BD0
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r5, r0, r1
	ldr r0, [r6, #0x2c]
	bl ov05_021F4C88
	mov r1, #0
	str r1, [sp]
	str r5, [sp, #4]
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r0, [r6, #0x4c]
	ldr r1, [r6, #0x50]
	ldr r3, _0224E754 ; =0x00000205
	mov r2, #0x10
	bl ov05_021DA464
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224E74C
_0224E644:
	add r0, sp, #0x18
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	ldrb r5, [r4, #0xd]
	mov r1, #0xc
	ldr r3, [r4]
	add r2, r5, #0
	ldr r5, _0224E758 ; =ov06_022523C0
	mul r2, r1
	ldr r2, [r5, r2]
	add r2, r3, r2
	str r2, [sp, #0x24]
	ldrb r5, [r4, #0xd]
	ldr r3, [r4, #4]
	add r2, r5, #0
	ldr r5, _0224E75C ; =ov06_022523C4
	mul r2, r1
	ldr r2, [r5, r2]
	add r2, r3, r2
	str r2, [sp, #0x28]
	ldrb r3, [r4, #0xd]
	ldr r2, [r4, #8]
	add r5, r3, #0
	mul r5, r1
	ldr r1, _0224E760 ; =ov06_022523C8
	add r3, sp, #0x24
	ldr r1, [r1, r5]
	add r1, r2, r1
	str r1, [sp, #0x2c]
	str r0, [sp]
	ldr r0, [r6, #0x4c]
	ldr r2, _0224E754 ; =0x00000205
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r6, #0x2c]
	bl ov05_021E7FBC
	ldrb r1, [r4, #0xd]
	add r1, r4, r1
	strb r0, [r1, #0x10]
	ldrb r1, [r4, #0xd]
	add r0, r6, #0
	add r0, #0xa0
	add r1, r4, r1
	ldrb r1, [r1, #0x10]
	ldr r0, [r0]
	bl ov05_021E7EEC
	bl ov05_021E7EC8
	add r3, r0, #0
	ldrb r2, [r4, #0xd]
	ldr r0, [r6, #0x50]
	mov r1, #0x10
	bl ov05_021DA4BC
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224E74C
_0224E6C4:
	ldrb r0, [r4, #0xe]
	cmp r0, #0xf
	bhs _0224E6D0
	add r0, r0, #1
	strb r0, [r4, #0xe]
	b _0224E74C
_0224E6D0:
	mov r0, #0
	strb r0, [r4, #0xe]
	ldrb r0, [r4, #0xd]
	add r0, r0, #1
	strb r0, [r4, #0xd]
	ldrb r1, [r4, #0xd]
	ldrb r0, [r4, #0xc]
	cmp r1, r0
	bhs _0224E6E8
	mov r0, #1
	strb r0, [r4, #0xf]
	b _0224E74C
_0224E6E8:
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224E74C
_0224E6F0:
	ldr r0, [r6, #0x50]
	mov r1, #0x10
	mov r2, #0
	bl ov05_021DA4EC
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224E74C
_0224E702:
	ldr r0, [r6, #0x50]
	mov r1, #0x10
	bl ov05_021DA58C
	cmp r0, #0
	beq _0224E74C
	ldr r0, [r6, #0x4c]
	ldr r1, [r6, #0x50]
	mov r2, #0x10
	bl ov05_021DA54C
	ldrb r0, [r4, #0xc]
	mov r5, #0
	cmp r0, #0
	bls _0224E73A
_0224E720:
	add r0, r4, r5
	add r1, r6, #0
	add r1, #0xa0
	ldrb r0, [r0, #0x10]
	ldr r1, [r1]
	bl ov05_021E7C80
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	ldrb r0, [r4, #0xc]
	cmp r5, r0
	blo _0224E720
_0224E73A:
	ldrb r0, [r4, #0xf]
	add r0, r0, #1
	strb r0, [r4, #0xf]
	b _0224E74C
_0224E742:
	bl FreeToHeap
	add sp, #0x30
	mov r0, #1
	pop {r4, r5, r6, pc}
_0224E74C:
	mov r0, #0
	add sp, #0x30
	pop {r4, r5, r6, pc}
	nop
_0224E754: .word 0x00000205
_0224E758: .word ov06_022523C0
_0224E75C: .word ov06_022523C4
_0224E760: .word ov06_022523C8

	thumb_func_start ov06_0224E764
ov06_0224E764: ; 0x0224E764
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F1A4
	cmp r0, #0
	bne _0224E794
	mov r0, #0x1f
	ldr r2, [r4, #0x4c]
	lsl r0, r0, #4
	mov r1, #1
	bl ov05_021DA080
	add r4, r0, #0
	mov r1, #1
	bl ov05_021DA1A4
	add r0, r4, #0
	mov r1, #1
	bl ov05_021DA0DC
	pop {r4, pc}
_0224E794:
	mov r0, #0x1f
	ldr r2, [r4, #0x4c]
	lsl r0, r0, #4
	mov r1, #0
	bl ov05_021DA080
	mov r1, #1
	bl ov05_021DA0DC
	mov r0, #0x1f
	ldr r2, [r4, #0x4c]
	lsl r0, r0, #4
	mov r1, #1
	bl ov05_021DA080
	add r4, r0, #0
	bl ov05_021DA138
	add r0, r4, #0
	mov r1, #1
	bl ov05_021DA0DC
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224E7C4
ov06_0224E7C4: ; 0x0224E7C4
	ldr r3, _0224E7D0 ; =TaskManager_Call
	ldr r0, [r0, #0x10]
	ldr r1, _0224E7D4 ; =ov06_0224E7D8
	mov r2, #0
	bx r3
	nop
_0224E7D0: .word TaskManager_Call
_0224E7D4: .word ov06_0224E7D8

	thumb_func_start ov06_0224E7D8
ov06_0224E7D8: ; 0x0224E7D8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetStatePtr
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0224E7FA
	cmp r0, #1
	beq _0224E820
	cmp r0, #2
	beq _0224E83A
	b _0224E852
_0224E7FA:
	mov r0, #0x1f
	ldr r2, [r5, #0x4c]
	lsl r0, r0, #4
	mov r1, #0
	bl ov05_021DA080
	add r5, r0, #0
	bl ov05_021DA0E8
	cmp r0, #0
	beq _0224E852
	add r0, r5, #0
	mov r1, #1
	bl ov05_021DA0DC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0224E852
_0224E820:
	mov r0, #0x1f
	ldr r2, [r5, #0x4c]
	lsl r0, r0, #4
	mov r1, #1
	bl ov05_021DA080
	mov r1, #0
	bl ov05_021DA0DC
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _0224E852
_0224E83A:
	mov r0, #0x1f
	ldr r2, [r5, #0x4c]
	lsl r0, r0, #4
	mov r1, #1
	bl ov05_021DA080
	bl ov05_021DA20C
	cmp r0, #0
	beq _0224E852
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224E852:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224E858
ov06_0224E858: ; 0x0224E858
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r2, #0
	bl GetMapObjectByID
	add r6, r0, #0
	add r1, sp, #0
	bl sub_02058B5C
	add r0, r6, #0
	bl sub_02058B2C
	add r5, r0, #0
	add r0, r6, #0
	bl sub_02058B4C
	add r4, r0, #0
	add r0, r6, #0
	bl sub_020584C4
	cmp r0, #3
	bhi _0224E8A8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224E890: ; jump table
	.short _0224E898 - _0224E890 - 2 ; case 0
	.short _0224E89C - _0224E890 - 2 ; case 1
	.short _0224E8A0 - _0224E890 - 2 ; case 2
	.short _0224E8A4 - _0224E890 - 2 ; case 3
_0224E898:
	sub r4, r4, #1
	b _0224E8AC
_0224E89C:
	add r4, r4, #1
	b _0224E8AC
_0224E8A0:
	sub r5, r5, #1
	b _0224E8AC
_0224E8A4:
	add r5, r5, #1
	b _0224E8AC
_0224E8A8:
	bl GF_AssertFail
_0224E8AC:
	mov r3, #2
	lsl r1, r5, #0x10
	lsl r3, r3, #0xe
	ldr r2, [sp, #4]
	lsl r4, r4, #0x10
	add r1, r1, r3
	add r0, r7, #0
	add r3, r4, r3
	bl ov05_021F54D0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224E8C4
ov06_0224E8C4: ; 0x0224E8C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r1, #0
	add r6, r0, #0
	add r1, sp, #0
	bl sub_02055350
	add r0, r6, #0
	bl GetPlayerXCoord
	add r5, r0, #0
	add r0, r6, #0
	bl GetPlayerYCoord
	add r4, r0, #0
	add r0, r6, #0
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #3
	bhi _0224E910
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224E8F8: ; jump table
	.short _0224E900 - _0224E8F8 - 2 ; case 0
	.short _0224E904 - _0224E8F8 - 2 ; case 1
	.short _0224E908 - _0224E8F8 - 2 ; case 2
	.short _0224E90C - _0224E8F8 - 2 ; case 3
_0224E900:
	sub r4, r4, #1
	b _0224E914
_0224E904:
	add r4, r4, #1
	b _0224E914
_0224E908:
	sub r5, r5, #1
	b _0224E914
_0224E90C:
	add r5, r5, #1
	b _0224E914
_0224E910:
	bl GF_AssertFail
_0224E914:
	mov r3, #2
	lsl r1, r5, #0x10
	lsl r3, r3, #0xe
	ldr r2, [sp, #4]
	lsl r4, r4, #0x10
	add r1, r1, r3
	add r0, r7, #0
	add r3, r4, r3
	bl ov05_021F54D0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224E92C
ov06_0224E92C: ; 0x0224E92C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl sub_02055350
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl ov05_021F54D0
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start ov06_0224E948
ov06_0224E948: ; 0x0224E948
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	str r2, [sp, #8]
	add r6, r0, #0
	mov r1, #0
	mov r2, #0xdc
	add r4, r3, #0
	ldr r7, [sp, #0x28]
	bl memset
	add r0, r6, #0
	add r0, #0x78
	mov r1, #0x8d
	add r2, r5, #0
	mov r3, #4
	bl ov05_021F5268
	add r1, r6, #0
	add r0, r6, #0
	add r1, #0x78
	bl ov05_021F5400
	add r0, r6, #0
	add r0, #0xd8
	str r4, [r0]
	add r0, r6, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r4, #0
	cmp r0, #0
	bls _0224E9BE
	add r0, r6, #0
	add r5, r6, #0
	str r0, [sp, #0xc]
	add r0, #0x78
	add r5, #0x88
	str r0, [sp, #0xc]
_0224E994:
	ldr r3, [sp, #8]
	mov r0, #4
	str r0, [sp]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	mov r2, #0x8d
	add r3, r3, r4
	str r7, [sp, #4]
	bl ov05_021F531C
	add r0, r6, #0
	add r1, r5, #0
	bl ov05_021F5424
	add r0, r6, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r4, r4, #1
	add r5, #0x14
	cmp r4, r0
	blo _0224E994
_0224E9BE:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224E9C4
ov06_0224E9C4: ; 0x0224E9C4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r0, #0x78
	add r7, r1, #0
	bl ov05_021F52C8
	add r0, r6, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r4, #0
	cmp r0, #0
	bls _0224E9F6
	add r5, r6, #0
	add r5, #0x88
_0224E9E0:
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021F5358
	add r0, r6, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r4, r4, #1
	add r5, #0x14
	cmp r4, r0
	blo _0224E9E0
_0224E9F6:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224E9F8
ov06_0224E9F8: ; 0x0224E9F8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r6, #1
	mov r4, #0
	cmp r0, #0
	bls _0224EA26
	add r5, r7, #0
	add r5, #0x88
_0224EA0C:
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl ov05_021F53BC
	and r6, r0
	add r0, r7, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r4, r4, #1
	add r5, #0x14
	cmp r4, r0
	blo _0224EA0C
_0224EA26:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224EA2C
ov06_0224EA2C: ; 0x0224EA2C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r0, #0xd8
	ldr r0, [r0]
	mov r4, #0
	cmp r0, #0
	bls _0224EA58
	add r5, r6, #0
	mov r7, #1
	add r5, #0x88
	lsl r7, r7, #0xc
_0224EA42:
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021F5384
	add r0, r6, #0
	add r0, #0xd8
	ldr r0, [r0]
	add r4, r4, #1
	add r5, #0x14
	cmp r4, r0
	blo _0224EA42
_0224EA58:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov06_0224EA5C
ov06_0224EA5C: ; 0x0224EA5C
	ldr r3, _0224EA60 ; =ov05_021F5430
	bx r3
	.align 2, 0
_0224EA60: .word ov05_021F5430

	thumb_func_start ov06_0224EA64
ov06_0224EA64: ; 0x0224EA64
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf0
	bl memset
	add r0, r4, #0
	add r0, #0xdc
	mov r1, #4
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	add r0, r4, #0
	add r0, #0xdc
	mov r1, #3
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0
	add r3, r1, #0
	bl ov06_0224E948
	ldr r0, [r5, #0x38]
	add r1, r4, #0
	bl ov06_0224E8C4
	ldr r0, _0224EAA8 ; =0x0000064B
	bl PlaySE
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224EAA8: .word 0x0000064B

	thumb_func_start ov06_0224EAAC
ov06_0224EAAC: ; 0x0224EAAC
	ldr r3, _0224EAB8 ; =ov06_0224E9C4
	add r0, r2, #0
	add r2, #0xdc
	add r1, r2, #0
	bx r3
	nop
_0224EAB8: .word ov06_0224E9C4

	thumb_func_start ov06_0224EABC
ov06_0224EABC: ; 0x0224EABC
	push {r4, lr}
	add r4, r2, #0
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0
	beq _0224EACE
	cmp r0, #1
	pop {r4, pc}
_0224EACE:
	add r0, r4, #0
	bl ov06_0224E9F8
	cmp r0, #1
	bne _0224EAEC
	add r0, r4, #0
	mov r1, #0
	bl ov05_021F54CC
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	add r4, #0xec
	add r0, r0, #1
	str r0, [r4]
_0224EAEC:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224EAF0
ov06_0224EAF0: ; 0x0224EAF0
	ldr r3, _0224EAF8 ; =ov06_0224EA5C
	add r0, r2, #0
	bx r3
	nop
_0224EAF8: .word ov06_0224EA5C

	thumb_func_start ov06_0224EAFC
ov06_0224EAFC: ; 0x0224EAFC
	ldr r0, [r0, #4]
	ldr r3, _0224EB08 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _0224EB0C ; =0x022521D4
	bx r3
	nop
_0224EB08: .word ov05_021D8024
_0224EB0C: .word ov06_022521D4

	thumb_func_start ov06_0224EB10
ov06_0224EB10: ; 0x0224EB10
	ldr r3, _0224EB14 ; =ov05_021D80A4
	bx r3
	.align 2, 0
_0224EB14: .word ov05_021D80A4

	thumb_func_start ov06_0224EB18
ov06_0224EB18: ; 0x0224EB18
	push {r3, lr}
	bl ov05_021D80E4
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #1
	bne _0224EB2A
	mov r0, #1
	pop {r3, pc}
_0224EB2A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224EB30
ov06_0224EB30: ; 0x0224EB30
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf0
	bl memset
	add r0, r4, #0
	add r0, #0xdc
	mov r1, #4
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	add r0, r4, #0
	add r0, #0xdc
	mov r2, #4
	str r0, [sp]
	add r0, r4, #0
	mov r1, #8
	add r3, r2, #0
	bl ov06_0224E948
	ldr r0, [r5, #0x38]
	add r1, r4, #0
	bl ov06_0224E8C4
	ldr r0, _0224EB74 ; =0x0000064A
	bl PlaySE
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224EB74: .word 0x0000064A

	thumb_func_start ov06_0224EB78
ov06_0224EB78: ; 0x0224EB78
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xf0
	bl memset
	add r0, r4, #0
	add r0, #0xdc
	mov r1, #4
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	add r0, r4, #0
	add r0, #0xdc
	mov r2, #4
	str r0, [sp]
	add r0, r4, #0
	mov r1, #8
	add r3, r2, #0
	bl ov06_0224E948
	ldr r0, [r5, #0x34]
	mov r1, #0
	add r2, r4, #0
	bl ov06_0224E858
	ldr r0, _0224EBC0 ; =0x0000064A
	bl PlaySE
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	pop {r3, r4, r5, pc}
	nop
_0224EBC0: .word 0x0000064A

	thumb_func_start ov06_0224EBC4
ov06_0224EBC4: ; 0x0224EBC4
	ldr r3, _0224EBD0 ; =ov06_0224E9C4
	add r0, r2, #0
	add r2, #0xdc
	add r1, r2, #0
	bx r3
	nop
_0224EBD0: .word ov06_0224E9C4

	thumb_func_start ov06_0224EBD4
ov06_0224EBD4: ; 0x0224EBD4
	push {r4, lr}
	add r4, r2, #0
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0
	beq _0224EBE6
	cmp r0, #1
	pop {r4, pc}
_0224EBE6:
	add r0, r4, #0
	bl ov06_0224E9F8
	cmp r0, #1
	bne _0224EC04
	add r0, r4, #0
	mov r1, #0
	bl ov05_021F54CC
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	add r4, #0xec
	add r0, r0, #1
	str r0, [r4]
_0224EC04:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224EC08
ov06_0224EC08: ; 0x0224EC08
	ldr r3, _0224EC10 ; =ov06_0224EA5C
	add r0, r2, #0
	bx r3
	nop
_0224EC10: .word ov06_0224EA5C

	thumb_func_start ov06_0224EC14
ov06_0224EC14: ; 0x0224EC14
	ldr r0, [r0, #4]
	ldr r3, _0224EC20 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _0224EC24 ; =0x0225218C
	bx r3
	nop
_0224EC20: .word ov05_021D8024
_0224EC24: .word ov06_0225218C

	thumb_func_start ov06_0224EC28
ov06_0224EC28: ; 0x0224EC28
	ldr r0, [r0, #4]
	ldr r3, _0224EC34 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _0224EC38 ; =0x022521A4
	bx r3
	nop
_0224EC34: .word ov05_021D8024
_0224EC38: .word ov06_022521A4

	thumb_func_start ov06_0224EC3C
ov06_0224EC3C: ; 0x0224EC3C
	ldr r3, _0224EC40 ; =ov05_021D80A4
	bx r3
	.align 2, 0
_0224EC40: .word ov05_021D80A4

	thumb_func_start ov06_0224EC44
ov06_0224EC44: ; 0x0224EC44
	push {r3, lr}
	bl ov05_021D80E4
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #1
	bne _0224EC56
	mov r0, #1
	pop {r3, pc}
_0224EC56:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov06_0224EC5C
ov06_0224EC5C: ; 0x0224EC5C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #4]
	ldr r1, _0224ECEC ; =0x02252188
	str r2, [sp, #8]
	ldrb r2, [r1, #2]
	add r0, sp, #0x10
	strb r2, [r0, #2]
	ldrb r2, [r1, #3]
	strb r2, [r0, #3]
	ldrb r2, [r1]
	strb r2, [r0]
	ldrb r1, [r1, #1]
	mov r2, #0x73
	lsl r2, r2, #2
	strb r1, [r0, #1]
	ldr r0, [sp, #8]
	mov r1, #0
	bl memset
	mov r1, #0x6e
	ldr r0, [sp, #8]
	lsl r1, r1, #2
	add r0, r0, r1
	mov r1, #4
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	ldr r5, [sp, #8]
	mov r1, #0x6e
	add r4, sp, #0x10
	lsl r1, r1, #2
	add r0, r5, #0
	add r0, r0, r1
	mov r7, #0
	add r6, sp, #0x10
	add r4, #2
	str r0, [sp, #0xc]
_0224ECA8:
	ldr r0, [sp, #0xc]
	mov r3, #2
	str r0, [sp]
	ldrb r1, [r4]
	ldrb r2, [r6]
	add r0, r5, #0
	bl ov06_0224E948
	ldr r0, [sp, #4]
	add r1, r5, #0
	ldr r0, [r0, #0x38]
	bl ov06_0224E92C
	add r7, r7, #1
	add r6, r6, #1
	add r4, r4, #1
	add r5, #0xdc
	cmp r7, #2
	blt _0224ECA8
	ldr r0, [sp, #8]
	mov r1, #0
	add r0, #0xdc
	bl ov05_021F54CC
	ldr r0, _0224ECF0 ; =0x0000064D
	bl PlaySE
	mov r1, #0x72
	ldr r0, [sp, #8]
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r0, r1]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224ECEC: .word ov06_02252188
_0224ECF0: .word 0x0000064D

	thumb_func_start ov06_0224ECF4
ov06_0224ECF4: ; 0x0224ECF4
	push {r4, r5, r6, lr}
	mov r0, #0x6e
	add r5, r2, #0
	lsl r0, r0, #2
	mov r4, #0
	add r6, r5, r0
_0224ED00:
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0224E9C4
	add r4, r4, #1
	add r5, #0xdc
	cmp r4, #2
	blt _0224ED00
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224ED14
ov06_0224ED14: ; 0x0224ED14
	push {r4, r5, r6, lr}
	mov r0, #0x72
	add r4, r2, #0
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r5, r1, #0
	cmp r0, #0
	beq _0224ED2A
	cmp r0, #1
	beq _0224ED66
	pop {r4, r5, r6, pc}
_0224ED2A:
	add r0, r4, #0
	bl ov06_0224E9F8
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	add r1, r4, #0
	bl ov06_0224E92C
	cmp r6, #1
	bne _0224ED78
	add r0, r4, #0
	add r0, #0xdc
	mov r1, #1
	bl ov05_021F54CC
	add r0, r4, #0
	mov r1, #0
	bl ov05_021F54CC
	add r1, r4, #0
	ldr r0, [r5, #0x38]
	add r1, #0xdc
	bl ov06_0224E92C
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224ED66:
	add r0, r4, #0
	add r0, #0xdc
	bl ov06_0224EA2C
	add r4, #0xdc
	ldr r0, [r5, #0x38]
	add r1, r4, #0
	bl ov06_0224E92C
_0224ED78:
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov06_0224ED7C
ov06_0224ED7C: ; 0x0224ED7C
	push {r3, r4, r5, lr}
	add r5, r2, #0
	mov r4, #0
_0224ED82:
	add r0, r5, #0

	thumb_func_start ov06_0224ED84
ov06_0224ED84: ; 0x0224ED84
	bl ov06_0224EA5C
	add r4, r4, #1
	add r5, #0xdc
	cmp r4, #2
	blt _0224ED82
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov06_0224ED94
ov06_0224ED94: ; 0x0224ED94
	ldr r0, [r0, #4]
	ldr r3, _0224EDA0 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _0224EDA4 ; =0x022521BC
	bx r3
	nop
_0224EDA0: .word ov05_021D8024
_0224EDA4: .word ov06_022521BC

	thumb_func_start ov06_0224EDA8
ov06_0224EDA8: ; 0x0224EDA8
	ldr r3, _0224EDAC ; =ov05_021D80A4
	bx r3
	.align 2, 0
_0224EDAC: .word ov05_021D80A4

	thumb_func_start ov06_0224EDB0
ov06_0224EDB0: ; 0x0224EDB0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	add r0, #0xc8
	ldr r0, [r0]
	add r6, r1, #0
	add r4, r2, #0
	add r5, r3, #0
	cmp r0, #0
	beq _0224EDC8
	bl GF_AssertFail
_0224EDC8:
	add r0, r6, #0
	add r1, sp, #0
	bl sub_02055350
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	ldr r1, [sp]
	add r0, r7, #0
	add r2, r2, r4
	add r3, r3, r5
	bl ov05_021F54D0
	add r0, r7, #0
	mov r4, #0
	add r5, r7, #0
	mov r1, #1
	add r0, #0xc8
	str r1, [r0]
	add r5, #0x78
	add r6, r4, #0
_0224EDF0:
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021F53F8
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0224EDF0
	add r0, r7, #0
	mov r1, #1
	bl ov05_021F54CC
	ldr r0, _0224EE14 ; =0x00000627
	bl PlaySE
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0224EE14: .word 0x00000627

	thumb_func_start ov06_0224EE18
ov06_0224EE18: ; 0x0224EE18
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r0, #0xc8
	ldr r0, [r0]
	cmp r0, #0
	beq _0224EE52
	ldr r5, [sp]
	mov r4, #1
	mov r6, #0
	add r5, #0x78
	lsl r7, r4, #0xc
_0224EE2E:
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021F53BC
	add r6, r6, #1
	and r4, r0
	add r5, #0x14
	cmp r6, #4
	blt _0224EE2E
	cmp r4, #1
	bne _0224EE52
	ldr r0, [sp]
	mov r1, #0
	add r0, #0xc8
	str r1, [r0]
	ldr r0, [sp]
	bl ov05_021F54CC
_0224EE52:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224EE54
ov06_0224EE54: ; 0x0224EE54
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r1, [sp]
	str r2, [sp, #4]
	mov r1, #0
	mov r2, #0xcc
	add r7, r0, #0
	add r5, r3, #0
	bl memset
	ldr r1, [sp]
	add r0, r7, #0
	bl ov05_021F5400
	add r4, r7, #0
	mov r6, #0
	add r4, #0x78
_0224EE76:
	ldr r1, [sp]
	ldr r2, [r5]
	ldr r3, [sp, #4]
	add r0, r4, #0
	bl ov05_021F5348
	add r0, r7, #0
	add r1, r4, #0
	bl ov05_021F5424
	add r6, r6, #1
	add r5, r5, #4
	add r4, #0x14
	cmp r6, #4
	blt _0224EE76
	add r0, r7, #0
	mov r1, #0
	bl ov05_021F54CC
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224EEA0
ov06_0224EEA0: ; 0x0224EEA0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r7, #0
	add r6, r1, #0
	mov r4, #0
	add r5, #0x78
_0224EEAC:
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021F5358
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #4
	blt _0224EEAC
	add r0, r7, #0
	mov r1, #0
	mov r2, #0xcc
	bl memset
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov06_0224EEC8
ov06_0224EEC8: ; 0x0224EEC8
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0xce
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0
	ldr r0, [r0, #0x38]
	bl sub_02055350
	mov r1, #0xcf
	lsl r1, r1, #4
	ldr r2, [sp]
	ldr r0, [r4, r1]
	sub r0, r2, r0
	bne _0224EF10
	add r0, r1, #4
	ldr r2, [sp, #4]
	ldr r0, [r4, r0]
	cmp r2, r0
	bge _0224EF10
	add r0, r1, #0
	add r0, #8
	ldr r2, [sp, #8]
	ldr r0, [r4, r0]
	cmp r2, r0
	ble _0224EF10
	add r0, r1, #0
	mov r2, #0
	sub r0, #8
	str r2, [r4, r0]
	mov r2, #2
	lsl r2, r2, #0x10
	sub r0, r1, #4
	str r2, [r4, r0]
	b _0224EF1E
_0224EF10:
	mov r1, #2
	ldr r0, _0224EF34 ; =0x00000CE8
	lsl r1, r1, #0x10
	str r1, [r4, r0]
	lsr r1, r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
_0224EF1E:
	mov r0, #0xcf
	lsl r0, r0, #4
	add r3, sp, #0
	add r2, r4, r0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0224EF34: .word 0x00000CE8

	thumb_func_start ov06_0224EF38
ov06_0224EF38: ; 0x0224EF38
	push {r4, lr}
	add r4, r0, #0
	bl ov06_0224EEC8
	mov r2, #0
	add r1, r4, #0
_0224EF44:
	add r0, r1, #0
	add r0, #0xd8
	ldr r0, [r0]
	cmp r0, #0
	bne _0224EF70
	add r1, r4, #0
	mov r0, #0xcc
	mov r3, #0xce
	add r1, #0x10
	mul r0, r2
	lsl r3, r3, #4
	add r0, r1, r0
	ldr r1, [r4, r3]
	add r2, r3, #0
	add r2, #8
	add r3, #0xc
	ldr r1, [r1, #0x38]
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	bl ov06_0224EDB0
	pop {r4, pc}
_0224EF70:
	add r2, r2, #1
	add r1, #0xcc
	cmp r2, #0x10
	blt _0224EF44
	bl GF_AssertFail
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov06_0224EF80
ov06_0224EF80: ; 0x0224EF80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x10
_0224EF88:
	add r0, r5, #0
	bl ov06_0224EE18
	add r4, r4, #1
	add r5, #0xcc
	cmp r4, #0x10
	blt _0224EF88
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224EF98
ov06_0224EF98: ; 0x0224EF98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r2, #0
	mov r2, #0xd1
	str r1, [sp, #4]
	add r0, r5, #0
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r0, _0224F024 ; =0x00000CFC
	mov r1, #4
	add r0, r5, r0
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	add r0, r5, #0
	mov r1, #0x8d
	mov r2, #8
	mov r3, #4
	bl ov05_021F5268
	mov r7, #0xcd
	mov r4, #0
	add r6, r5, #0
	lsl r7, r7, #4
_0224EFCC:
	mov r0, #0
	str r0, [sp]
	mov r0, #0x8d
	add r1, r4, #4
	mov r2, #0
	mov r3, #4
	bl GfGfxLoader_LoadFromNarc
	str r0, [r6, r7]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, #4
	blt _0224EFCC
	add r4, r5, #0
	mov r7, #0xcd
	mov r6, #0
	add r4, #0x10
	lsl r7, r7, #4
_0224EFF0:
	ldr r2, _0224F024 ; =0x00000CFC
	add r0, r4, #0
	add r1, r5, #0
	add r2, r5, r2
	add r3, r5, r7
	bl ov06_0224EE54
	add r6, r6, #1
	add r4, #0xcc
	cmp r6, #0x10
	blt _0224EFF0
	mov r1, #0xce
	ldr r0, [sp, #4]
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	add r1, #0x10
	ldr r0, [r0, #0x38]
	add r1, r5, r1
	bl sub_02055350
	ldr r0, _0224F028 ; =0x00000D0C
	mov r1, #0
	str r1, [r5, r0]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224F024: .word 0x00000CFC
_0224F028: .word 0x00000D0C

	thumb_func_start ov06_0224F02C
ov06_0224F02C: ; 0x0224F02C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r2, #0
	add r4, r5, #0
	ldr r7, _0224F064 ; =0x00000CFC
	mov r6, #0
	add r4, #0x10
_0224F038:
	add r0, r4, #0
	add r1, r5, r7
	bl ov06_0224EEA0
	add r6, r6, #1
	add r4, #0xcc
	cmp r6, #0x10
	blt _0224F038
	add r0, r5, #0
	bl ov05_021F52C8
	mov r6, #0xcd
	mov r4, #0
	lsl r6, r6, #4
_0224F054:
	ldr r0, [r5, r6]
	bl FreeToHeap
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0224F054
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224F064: .word 0x00000CFC

	thumb_func_start ov06_0224F068
ov06_0224F068: ; 0x0224F068
	push {r4, lr}
	ldr r1, _0224F0A0 ; =0x00000D0C
	add r4, r2, #0
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _0224F09E
	add r0, r1, #0
	sub r0, #0x28
	ldr r0, [r4, r0]
	sub r2, r0, #1
	add r0, r1, #0
	sub r0, #0x28
	str r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0x28
	ldr r0, [r4, r0]
	cmp r0, #0
	bge _0224F098
	mov r0, #4
	sub r1, #0x28
	str r0, [r4, r1]
	add r0, r4, #0
	bl ov06_0224EF38
_0224F098:
	add r0, r4, #0
	bl ov06_0224EF80
_0224F09E:
	pop {r4, pc}
	.align 2, 0
_0224F0A0: .word 0x00000D0C

	thumb_func_start ov06_0224F0A4
ov06_0224F0A4: ; 0x0224F0A4
	push {r3, r4, r5, lr}
	add r5, r2, #0
	mov r4, #0
	add r5, #0x10
_0224F0AC:
	add r0, r5, #0
	bl ov05_021F5430
	add r4, r4, #1
	add r5, #0xcc
	cmp r4, #0x10
	blt _0224F0AC
	pop {r3, r4, r5, pc}

	thumb_func_start ov06_0224F0BC
ov06_0224F0BC: ; 0x0224F0BC
	ldr r0, [r0, #4]
	ldr r3, _0224F0C8 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _0224F0CC ; =0x022521EC
	bx r3
	nop
_0224F0C8: .word ov05_021D8024
_0224F0CC: .word ov06_022521EC

	thumb_func_start ov06_0224F0D0
ov06_0224F0D0: ; 0x0224F0D0
	ldr r3, _0224F0D4 ; =ov05_021D80A4
	bx r3
	.align 2, 0
_0224F0D4: .word ov05_021D80A4

	thumb_func_start ov06_0224F0D8
ov06_0224F0D8: ; 0x0224F0D8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0224F0EA
	cmp r0, #1
	beq _0224F102
	pop {r3, r4, r5, pc}
_0224F0EA:
	ldr r1, [r4, #0xc]
	ldr r0, [r4]
	lsl r2, r1, #2
	ldr r1, _0224F124 ; =0x0225221C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #1
	bne _0224F120
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0224F102:
	ldr r1, [r4, #0xc]
	ldr r0, [r4]
	lsl r2, r1, #2
	ldr r1, _0224F128 ; =0x02252204
	ldr r1, [r1, r2]
	blx r1
	ldr r0, [r4, #4]
	mov r1, #1
	strh r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_0224F120:
	pop {r3, r4, r5, pc}
	nop
_0224F124: .word ov06_0225221C
_0224F128: .word ov06_02252204

	thumb_func_start ov06_0224F12C
ov06_0224F12C: ; 0x0224F12C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r0, r3, #0
	mov r1, #0x10
	add r4, r2, #0
	bl AllocFromHeap
	add r6, r0, #0
	add r2, r6, #0
	mov r1, #0x10
	mov r0, #0
_0224F144:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _0224F144
	ldr r1, _0224F16C ; =0x02252210
	lsl r2, r4, #2
	ldr r1, [r1, r2]
	add r0, r7, #0
	blx r1
	str r0, [r6]
	str r5, [r6, #4]
	ldr r0, _0224F170 ; =ov06_0224F0D8
	str r4, [r6, #0xc]
	mov r2, #0
	add r1, r6, #0
	strh r2, [r5]
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224F16C: .word ov06_02252210
_0224F170: .word ov06_0224F0D8

	.rodata
	.global ov06_0224F174
ov06_0224F174: ; 0x0224F174
	.word ov06_02239F80, ov06_0223A020, ov06_0223A0D4

	.global ov06_0224F180
ov06_0224F180: ; 0x0224F180
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global ov06_0224F190
ov06_0224F190: ; 0x0224F190
	.word 0x00000400, 0x00000004, ov06_02239F04, ov06_02239F40
	.word ov06_02239F4C, ov06_02239F58

	.global ov06_0224F1A8
ov06_0224F1A8: ; 0x0224F1A8
	.word 0x00000400, 0x00000010, ov06_0223A1E8, ov06_0223A208
	.word ov06_0223A21C, ov06_0223A2DC

	.global ov06_0224F1C0
ov06_0224F1C0: ; 0x0224F1C0
	.word 0x00000400, 0x00000074, ov06_02239B08, ov06_02239B38
	.word ov06_02239B58, ov06_02239CD0

	.global ov06_0224F1D8
ov06_0224F1D8: ; 0x0224F1D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F1F4
ov06_0224F1F4: ; 0x0224F1F4
	.byte 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00

	.global ov06_0224F21C
ov06_0224F21C: ; 0x0224F21C
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00

	.global ov06_0224F248
ov06_0224F248: ; 0x0224F248
	.byte 0x08, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x6D, 0x2D, 0x00, 0x00, 0x6A, 0x00, 0xFF, 0x7F, 0x1A, 0xF8
	.byte 0x17, 0xF2, 0x5D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xAD, 0x39, 0x8D, 0x31, 0x6D, 0x39, 0x2B, 0x29, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x2B, 0x25, 0x00, 0x00, 0x6A, 0x00, 0xFF, 0x7F, 0x1A, 0xF8
	.byte 0x17, 0xF2, 0x5D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x6B, 0x31, 0x8D, 0x31, 0x6D, 0x39, 0x2B, 0x29, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x09, 0x21, 0x00, 0x00, 0x6A, 0x00, 0xFF, 0x7F, 0x1A, 0xF8
	.byte 0x17, 0xF2, 0x5D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x2A, 0x25, 0x4B, 0x29, 0x6D, 0x39, 0x2B, 0x29, 0x00, 0x00

	.global ov06_0224F2D8
ov06_0224F2D8: ; 0x0224F2D8
	.byte 0x05, 0x00, 0x00, 0x00

	.global ov06_0224F2DC
ov06_0224F2DC: ; 0x0224F2DC
	.byte 0x03, 0x00, 0x00, 0x00

	.global ov06_0224F2E0
ov06_0224F2E0: ; 0x0224F2E0
	.byte 0x04, 0x00, 0x00, 0x00

	.global ov06_0224F2E4
ov06_0224F2E4: ; 0x0224F2E4
	.byte 0x0D, 0x00, 0x00, 0x00

	.global ov06_0224F2E8
ov06_0224F2E8: ; 0x0224F2E8
	.byte 0x08, 0x00, 0x00, 0x00

	.global ov06_0224F2EC
ov06_0224F2EC: ; 0x0224F2EC
	.byte 0x11, 0x00, 0x00, 0x00

	.global ov06_0224F2F0
ov06_0224F2F0: ; 0x0224F2F0
	.byte 0x1A, 0x1B, 0x00, 0x00

	.global ov06_0224F2F4
ov06_0224F2F4: ; 0x0224F2F4
	.byte 0x00, 0x01, 0x02, 0x06
	.byte 0x07, 0x09, 0x0A, 0x0B, 0x0C, 0x0E, 0x0F, 0x10, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19

	.global ov06_0224F308
ov06_0224F308: ; 0x0224F308
	.byte 0x14, 0x00, 0x00, 0x00

	.global ov06_0224F30C
ov06_0224F30C: ; 0x0224F30C
	.word ov06_0224F2F4, 0x00000001, ov06_0224F2D8, 0x00000001
	.word ov06_0224F2EC, 0x00000001, ov06_0224F2E8, 0x00000001
	.word ov06_0224F2E4, 0x00000001, ov06_0224F2E0, 0x00000001
	.word ov06_0224F2DC, 0x00000002, ov06_0224F2F0

	.global ov06_0224F348
ov06_0224F348: ; 0x0224F348
	.byte 0x03, 0x17, 0x0D, 0x07, 0x04, 0x0D, 0x08, 0x01

	.global ov06_0224F350
ov06_0224F350: ; 0x0224F350
	.byte 0x02, 0x01, 0x12, 0x1B, 0x06, 0x0D, 0xFD, 0x00

	.global ov06_0224F358
ov06_0224F358: ; 0x0224F358
	.byte 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F364
ov06_0224F364: ; 0x0224F364
	.byte 0x00, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F370
ov06_0224F370: ; 0x0224F370
	.word ov06_0225226C, ov06_02252284, ov06_0225229C, ov06_022522B4
	.word 0x00000000, 0x00000000, ov06_02252258

	.global ov06_0224F38C
ov06_0224F38C: ; 0x0224F38C
	.word 0x00000000, ov06_0223DCF0, ov06_0223DE34, 0x00000000
	.word 0x00070000, 0x10000000, 0x80000020, 0x00000000

	.global ov06_0224F3AC
ov06_0224F3AC: ; 0x0224F3AC
	.byte 0x02, 0x0D, 0x02, 0x12, 0x0E, 0x0D, 0x01, 0x00, 0x02, 0x05, 0x12, 0x1B, 0x06, 0x0D, 0xFD, 0x00
	.byte 0x03, 0x01, 0x01, 0x0A, 0x04, 0x0D, 0x28, 0x00, 0x03, 0x13, 0x0D, 0x0C, 0x04, 0x0D, 0x50, 0x00
	.byte 0x03, 0x01, 0x0F, 0x0E, 0x02, 0x0D, 0x80, 0x00, 0x03, 0x02, 0x13, 0x1B, 0x04, 0x0C, 0x9C, 0x00

	.global ov06_0224F3DC
ov06_0224F3DC: ; 0x0224F3DC
	.byte 0x00, 0x00, 0x00, 0x00, 0xB1, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB1, 0x00, 0x84, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16, 0x00, 0xAC, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F47C
ov06_0224F47C: ; 0x0224F47C
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0x00, 0x00, 0x00

	.global ov06_0224F488
ov06_0224F488: ; 0x0224F488
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global ov06_0224F490
ov06_0224F490: ; 0x0224F490
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x05, 0x00, 0x00, 0x01, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F4B0
ov06_0224F4B0: ; 0x0224F4B0
	.word 0x00000000, ov06_0223F0A8, ov06_0223F0C8, 0x00000000
	.byte 0x10, 0x00, 0x05, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F4D0
ov06_0224F4D0: ; 0x0224F4D0
	.byte 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x15, 0x00, 0x00, 0x00

	.global ov06_0224F514
ov06_0224F514: ; 0x0224F514
	.byte 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00

	.global ov06_0224F558
ov06_0224F558: ; 0x0224F558
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00
	.byte 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F59C
ov06_0224F59C: ; 0x0224F59C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x17, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00
	.byte 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F5E0
ov06_0224F5E0: ; 0x0224F5E0
	.byte 0x1F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00
	.byte 0x22, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00
	.byte 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x27, 0x00, 0x00, 0x00

	.global ov06_0224F624
ov06_0224F624: ; 0x0224F624
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00
	.byte 0x17, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00
	.byte 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F668
ov06_0224F668: ; 0x0224F668
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00
	.byte 0x1B, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00
	.byte 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F6AC
ov06_0224F6AC: ; 0x0224F6AC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00
	.byte 0x2C, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00
	.byte 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00

	.global ov06_0224F704
ov06_0224F704: ; 0x0224F704
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F724
ov06_0224F724: ; 0x0224F724
	.byte 0x00, 0x03, 0x06, 0x07, 0x08, 0x09, 0x00, 0x00

	.global ov06_0224F72C
ov06_0224F72C: ; 0x0224F72C
	.byte 0x02, 0x03, 0x04, 0x07, 0x08, 0x0B, 0x00, 0x00

	.global ov06_0224F734
ov06_0224F734: ; 0x0224F734
	.byte 0x00, 0x01, 0x05, 0x06, 0x09, 0x0A, 0x00, 0x00

	.global ov06_0224F73C
ov06_0224F73C: ; 0x0224F73C
	.byte 0x01, 0x02, 0x04, 0x05, 0x0A, 0x0B, 0x00, 0x00

	.global ov06_0224F744
ov06_0224F744: ; 0x0224F744
	.byte 0x00, 0x03, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x11, 0x00

	.global ov06_0224F750
ov06_0224F750: ; 0x0224F750
	.byte 0x02, 0x03, 0x04, 0x06
	.byte 0x07, 0x0A, 0x0B, 0x0D, 0x10, 0x02, 0x02, 0x00

	.global ov06_0224F75C
ov06_0224F75C: ; 0x0224F75C
	.byte 0x01, 0x02, 0x04, 0x05, 0x07, 0x08, 0x09, 0x0A
	.byte 0x0B, 0x0C, 0x0F, 0x00

	.global ov06_0224F768
ov06_0224F768: ; 0x0224F768
	.byte 0x00, 0x01, 0x04, 0x05, 0x06, 0x0B, 0x0C, 0x0D, 0x0E, 0x00, 0x00, 0x00

	.global ov06_0224F774
ov06_0224F774: ; 0x0224F774
	.word ov06_0224F804, ov06_0224F870, ov06_0224F9E0

	.global ov06_0224F780
ov06_0224F780: ; 0x0224F780
	.byte 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00

	.global ov06_0224F78C
ov06_0224F78C: ; 0x0224F78C
	.byte 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00

	.global ov06_0224F798
ov06_0224F798: ; 0x0224F798
	.word ov06_0224F7BC, ov06_0224F7D4, ov06_0224F978

	.global ov06_0224F7A4
ov06_0224F7A4: ; 0x0224F7A4
	.byte 0x00, 0x80, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0D, 0x00

	.global ov06_0224F7B0
ov06_0224F7B0: ; 0x0224F7B0
	.byte 0xEF, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00

	.global ov06_0224F7BC
ov06_0224F7BC: ; 0x0224F7BC
	.byte 0xCB, 0x01, 0x00, 0x00
	.byte 0x03, 0x00, 0x08, 0x01, 0xCC, 0x01, 0x00, 0x00, 0x08, 0x00, 0x08, 0x06, 0xCB, 0x01, 0x00, 0x00
	.byte 0x0D, 0x00, 0x08, 0x00

	.global ov06_0224F7D4
ov06_0224F7D4: ; 0x0224F7D4
	.byte 0xCB, 0x01, 0x00, 0x00, 0x06, 0x00, 0x08, 0x01, 0xCA, 0x01, 0x00, 0x00
	.byte 0x0B, 0x00, 0x08, 0x07, 0xCF, 0x01, 0x00, 0x00, 0x0F, 0x03, 0x08, 0x0D, 0xCF, 0x01, 0x00, 0x00
	.byte 0x02, 0x03, 0x0D, 0x09, 0xCA, 0x01, 0x00, 0x00, 0x06, 0x00, 0x0D, 0x06, 0xCD, 0x01, 0x00, 0x00
	.byte 0x0B, 0x00, 0x0D, 0x02

	.global ov06_0224F804
ov06_0224F804: ; 0x0224F804
	.byte 0x01, 0x08, 0x02, 0x01, 0x03, 0x06, 0x01, 0x02, 0x04, 0x08, 0x02, 0x01
	.byte 0x03, 0x09, 0x01, 0x02, 0x06, 0x08, 0x02, 0x01, 0x08, 0x06, 0x01, 0x02, 0x09, 0x08, 0x02, 0x01
	.byte 0x08, 0x09, 0x01, 0x02, 0x0B, 0x08, 0x02, 0x01, 0x0D, 0x06, 0x01, 0x02, 0x0E, 0x08, 0x02, 0x01
	.byte 0x0D, 0x09, 0x01, 0x02

	.global ov06_0224F834
ov06_0224F834: ; 0x0224F834
	.byte 0x0C, 0x14, 0x01, 0x0B, 0x02, 0x14, 0x00, 0x0B, 0x12, 0x13, 0x00, 0x0A, 0x09, 0x12, 0x01, 0x09
	.byte 0x15, 0x10, 0x01, 0x08, 0x0F, 0x10, 0x00, 0x08, 0x0B, 0x10, 0x01, 0x07, 0x12, 0x0E, 0x00, 0x06
	.byte 0x0F, 0x0D, 0x00, 0x05, 0x09, 0x0C, 0x01, 0x04, 0x16, 0x0A, 0x01, 0x03, 0x10, 0x0A, 0x01, 0x02
	.byte 0x02, 0x0A, 0x00, 0x01, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0224F870
ov06_0224F870: ; 0x0224F870
	.byte 0x04, 0x08, 0x02, 0x01
	.byte 0x06, 0x06, 0x01, 0x02, 0x07, 0x08, 0x02, 0x01, 0x06, 0x09, 0x01, 0x02, 0x09, 0x08, 0x02, 0x01
	.byte 0x0B, 0x06, 0x01, 0x02, 0x0C, 0x08, 0x02, 0x01, 0x0B, 0x09, 0x01, 0x02, 0x0F, 0x06, 0x01, 0x05
	.byte 0x02, 0x0B, 0x01, 0x05, 0x04, 0x0D, 0x02, 0x01, 0x06, 0x0B, 0x01, 0x02, 0x07, 0x0D, 0x02, 0x01
	.byte 0x06, 0x0E, 0x01, 0x02, 0x09, 0x0D, 0x02, 0x01, 0x0B, 0x0B, 0x01, 0x02, 0x0C, 0x0D, 0x02, 0x01
	.byte 0x0B, 0x0E, 0x01, 0x02

	.global ov06_0224F8B8
ov06_0224F8B8: ; 0x0224F8B8
	.byte 0x24, 0x01, 0x00, 0x00, 0x09

	.global ov06_0224F8BD
ov06_0224F8BD: ; 0x0224F8BD
	.byte 0x09

	.global ov06_0224F8BE
ov06_0224F8BE: ; 0x0224F8BE
	.byte 0x0A, 0x00, 0x20, 0x01, 0x00, 0x00, 0x0A, 0x03, 0x04, 0x00, 0x20, 0x01, 0x00, 0x00, 0x0A, 0x0B
	.byte 0x0C, 0x01, 0x22, 0x01, 0x00, 0x00, 0x0A, 0x11, 0x12, 0x01, 0x23, 0x01, 0x00, 0x00, 0x0C, 0x01
	.byte 0x05, 0x01, 0x1F, 0x01, 0x00, 0x00, 0x0D, 0x10, 0x14, 0x00, 0x25, 0x01, 0x00, 0x00, 0x0E, 0x13
	.byte 0x14, 0x00, 0x24, 0x01, 0x00, 0x00, 0x10, 0x04, 0x07, 0x01, 0x24, 0x01, 0x00, 0x00, 0x10, 0x10
	.byte 0x11, 0x00, 0x23, 0x01, 0x00, 0x00, 0x12, 0x01, 0x05, 0x01, 0x25, 0x01, 0x00, 0x00, 0x13, 0x13
	.byte 0x14, 0x00, 0x21, 0x01, 0x00, 0x00, 0x14, 0x03, 0x08, 0x01

	.global ov06_0224F918
ov06_0224F918: ; 0x0224F918
	.byte 0x09, 0x02, 0x0C, 0x01, 0x0A, 0x02, 0x0D, 0x01, 0x03, 0x01, 0x05, 0x02, 0x04, 0x01, 0x06, 0x02
	.byte 0x0B, 0x01, 0x0D, 0x02, 0x0C, 0x01, 0x0E, 0x02, 0x12, 0x01, 0x14, 0x01, 0x13, 0x01, 0x15, 0x01
	.byte 0x04, 0x01, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x14, 0x01, 0x00, 0x00
	.byte 0x13, 0x04, 0x00, 0x00, 0x16, 0x01, 0x00, 0x00, 0x04, 0x02, 0x07, 0x01, 0x07, 0x02, 0x0A, 0x01
	.byte 0x10, 0x02, 0x13, 0x01, 0x11, 0x02, 0x14, 0x01, 0x04, 0x01, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00
	.byte 0x13, 0x04, 0x00, 0x00, 0x16, 0x01, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x08, 0x04, 0x00, 0x00

	.global ov06_0224F978
ov06_0224F978: ; 0x0224F978
	.byte 0xCD, 0x01, 0x00, 0x00, 0x06, 0x06, 0x08, 0x01, 0xCC, 0x01, 0x00, 0x00, 0x0B, 0x06, 0x08, 0x04
	.byte 0xCE, 0x01, 0x00, 0x00, 0x10, 0x06, 0x08, 0x00, 0xCF, 0x01, 0x00, 0x00, 0x02, 0x03, 0x0D, 0x0C
	.byte 0xCC, 0x01, 0x00, 0x00, 0x06, 0x06, 0x0D, 0x05, 0xCD, 0x01, 0x00, 0x00, 0x0B, 0x06, 0x0D, 0x03
	.byte 0xCE, 0x01, 0x00, 0x00, 0x10, 0x06, 0x0D, 0x07, 0xCF, 0x01, 0x00, 0x00, 0x14, 0x03, 0x0D, 0x09
	.byte 0xD0, 0x01, 0x00, 0x00, 0x02, 0x03, 0x12, 0x08, 0xCB, 0x01, 0x00, 0x00, 0x06, 0x00, 0x12, 0x05
	.byte 0xCE, 0x01, 0x00, 0x00, 0x0B, 0x00, 0x12, 0x03, 0xCD, 0x01, 0x00, 0x00, 0x10, 0x00, 0x12, 0x04
	.byte 0xD0, 0x01, 0x00, 0x00, 0x14, 0x03, 0x12, 0x0D

	.global ov06_0224F9E0
ov06_0224F9E0: ; 0x0224F9E0
	.byte 0x04, 0x08, 0x02, 0x01, 0x06, 0x06, 0x01, 0x02
	.byte 0x07, 0x08, 0x02, 0x01, 0x06, 0x09, 0x01, 0x02, 0x09, 0x08, 0x02, 0x01, 0x0B, 0x06, 0x01, 0x02
	.byte 0x0C, 0x08, 0x02, 0x01, 0x0B, 0x09, 0x01, 0x02, 0x0E, 0x08, 0x02, 0x01, 0x10, 0x06, 0x01, 0x02
	.byte 0x11, 0x08, 0x02, 0x01, 0x10, 0x09, 0x01, 0x02, 0x02, 0x0B, 0x01, 0x05, 0x04, 0x0D, 0x02, 0x01
	.byte 0x06, 0x0B, 0x01, 0x02, 0x07, 0x0D, 0x02, 0x01, 0x06, 0x0E, 0x01, 0x02, 0x09, 0x0D, 0x02, 0x01
	.byte 0x0B, 0x0B, 0x01, 0x02, 0x0C, 0x0D, 0x02, 0x01, 0x0B, 0x0E, 0x01, 0x02, 0x0E, 0x0D, 0x02, 0x01
	.byte 0x10, 0x0B, 0x01, 0x02, 0x11, 0x0D, 0x02, 0x01, 0x10, 0x0E, 0x01, 0x02, 0x14, 0x0B, 0x01, 0x05
	.byte 0x02, 0x10, 0x01, 0x05, 0x04, 0x12, 0x02, 0x01, 0x06, 0x10, 0x01, 0x02, 0x07, 0x12, 0x02, 0x01
	.byte 0x06, 0x13, 0x01, 0x02, 0x09, 0x12, 0x02, 0x01, 0x0B, 0x10, 0x01, 0x02, 0x0C, 0x12, 0x02, 0x01
	.byte 0x0B, 0x13, 0x01, 0x02, 0x0E, 0x12, 0x02, 0x01, 0x10, 0x10, 0x01, 0x02, 0x11, 0x12, 0x02, 0x01
	.byte 0x10, 0x13, 0x01, 0x02, 0x14, 0x10, 0x01, 0x05

	.global ov06_0224FA80
ov06_0224FA80: ; 0x0224FA80
	.byte 0x29, 0x01, 0x00, 0x00

	.global ov06_0224FA84
ov06_0224FA84: ; 0x0224FA84
	.byte 0x10

	.global ov06_0224FA85
ov06_0224FA85: ; 0x0224FA85
	.byte 0x00

	.global ov06_0224FA86
ov06_0224FA86: ; 0x0224FA86
	.byte 0x09

	.global ov06_0224FA87
ov06_0224FA87: ; 0x0224FA87
	.byte 0x10

	.global ov06_0224FA88
ov06_0224FA88: ; 0x0224FA88
	.byte 0x1E

	.global ov06_0224FA89
ov06_0224FA89: ; 0x0224FA89
	.byte 0x09

	.global ov06_0224FA8A
ov06_0224FA8A: ; 0x0224FA8A
	.byte 0x00

	.global ov06_0224FA8B
ov06_0224FA8B: ; 0x0224FA8B
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x0B, 0x00, 0x0D, 0x0B, 0x0A, 0x0D, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x0F, 0x00, 0x0D, 0x0F, 0x0A, 0x0D, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x13, 0x00, 0x0D, 0x13, 0x0A, 0x0D, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x18, 0x00, 0x0D, 0x18, 0x0A, 0x0D, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x15, 0x00, 0x16, 0x15, 0x0A, 0x16, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x19, 0x00, 0x09, 0x19, 0x0A, 0x09, 0x00
	.byte 0x01, 0x01, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x19, 0x00, 0x16, 0x19, 0x0A, 0x16, 0x00
	.byte 0x01, 0x01, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x1D, 0x00, 0x16, 0x1D, 0x0A, 0x16, 0x00
	.byte 0x01, 0x01, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x05, 0x0A, 0x1A, 0x05, 0x14, 0x1A, 0x01
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x0B, 0x0A, 0x16, 0x12, 0x0A, 0x16, 0x01
	.byte 0x01, 0x01, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x1D, 0x0A, 0x09, 0x1D, 0x14, 0x09, 0x01
	.byte 0x02, 0x01, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x0A, 0x14, 0x04, 0x0E, 0x14, 0x04, 0x02
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x13, 0x14, 0x04, 0x16, 0x14, 0x04, 0x02
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x07, 0x14, 0x0C, 0x16, 0x14, 0x0C, 0x02
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x09, 0x14, 0x1A, 0x15, 0x14, 0x1A, 0x02
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x26, 0x01, 0x00, 0x00, 0x02, 0x14, 0x13, 0x02, 0x14, 0x16, 0x02
	.byte 0x02, 0x01, 0x00, 0x00, 0x00, 0x26, 0x01, 0x00, 0x00, 0x1A, 0x14, 0x10, 0x1A, 0x14, 0x16, 0x02
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x26, 0x01, 0x00, 0x00, 0x1D, 0x14, 0x10, 0x1D, 0x14, 0x16, 0x02
	.byte 0x02, 0x01, 0x00, 0x00, 0x00, 0x29, 0x01, 0x00, 0x00, 0x07, 0x00, 0x09, 0x07, 0x1E, 0x09, 0x00
	.byte 0x03, 0x01, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x13, 0x1E, 0x04, 0x1A, 0x1E, 0x04, 0x03
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x05, 0x1E, 0x1A, 0x1A, 0x1E, 0x1A, 0x03
	.byte 0x03, 0x01, 0x00, 0x00, 0x00, 0x26, 0x01, 0x00, 0x00, 0x1D, 0x1E, 0x07, 0x1D, 0x1E, 0x17, 0x03
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x26, 0x01, 0x00, 0x00, 0x02, 0x1E, 0x0C, 0x02, 0x1E, 0x17, 0x03
	.byte 0x03, 0x01, 0x00, 0x00, 0x00

	.global ov06_0224FC00
ov06_0224FC00: ; 0x0224FC00
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01
	.byte 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01
	.byte 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01
	.byte 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
	.byte 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01

	.global ov06_02250C00
ov06_02250C00: ; 0x02250C00
	.byte 0x00, 0x04, 0x05, 0x09, 0x0D, 0x10, 0x13, 0x17, 0x19, 0x1B, 0x1E, 0x21, 0x24, 0x27, 0x00, 0x00

	.global ov06_02250C10
ov06_02250C10: ; 0x02250C10
	.byte 0x02, 0x06, 0x07, 0x0B, 0x0E, 0x0F, 0x11, 0x15, 0x19, 0x1C, 0x1D, 0x1F, 0x26, 0x27, 0x00, 0x00

	.global ov06_02250C20
ov06_02250C20: ; 0x02250C20
	.byte 0x01, 0x04, 0x07, 0x0A, 0x0C, 0x0F, 0x10, 0x14, 0x16, 0x1A, 0x1D, 0x1E, 0x22, 0x23, 0x00, 0x00

	.global ov06_02250C30
ov06_02250C30: ; 0x02250C30
	.byte 0x03, 0x05, 0x06, 0x08, 0x0C, 0x0D, 0x0E, 0x12, 0x18, 0x1A, 0x1B, 0x1C, 0x20, 0x25, 0x00, 0x00

	.global ov06_02250C40
ov06_02250C40: ; 0x02250C40
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0xC1, 0x03

	.global ov06_02250C48
ov06_02250C48: ; 0x02250C48
	.byte 0x00, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06

	.global ov06_02250C50
ov06_02250C50: ; 0x02250C50
	.byte 0x00, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00

	.global ov06_02250C5C
ov06_02250C5C: ; 0x02250C5C
	.byte 0x00, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0A, 0x0A, 0x00

	.global ov06_02250C68
ov06_02250C68: ; 0x02250C68
	.byte 0xD5, 0x00, 0x9D, 0x00, 0xEA, 0x00, 0xD9, 0x00

	.global ov06_02250C70
ov06_02250C70: ; 0x02250C70
	.byte 0x00, 0x00

	.global ov06_02250C72
ov06_02250C72: ; 0x02250C72
	.byte 0x63, 0x00, 0x50, 0x00, 0x77, 0x00, 0x64, 0x00, 0x8B, 0x00, 0x78, 0x00, 0x9F, 0x00, 0x8C, 0x00
	.byte 0xB3, 0x00, 0xA0, 0x00, 0xC7, 0x00, 0xB4, 0x00, 0xDB, 0x00, 0xC8, 0x00, 0x2B, 0x01

	.global ov06_02250C90
ov06_02250C90: ; 0x02250C90
	.byte 0x64, 0x00

	.global ov06_02250C92
ov06_02250C92: ; 0x02250C92
	.byte 0x77, 0x00, 0x78, 0x00, 0x8B, 0x00, 0x8C, 0x00, 0x9F, 0x00, 0xA0, 0x00, 0xB3, 0x00, 0xB4, 0x00
	.byte 0xC7, 0x00, 0xC8, 0x00, 0xDB, 0x00, 0xDC, 0x00, 0xEF, 0x00, 0xC8, 0x00, 0x2B, 0x01

	.global ov06_02250CB0
ov06_02250CB0: ; 0x02250CB0
	.byte 0x04, 0x00, 0x00, 0x01, 0x02, 0x03, 0x14, 0x00, 0x02, 0x03, 0x04, 0x05, 0x09, 0x00, 0x04, 0x06
	.byte 0x06, 0x07, 0x0A, 0x00, 0x06, 0x07, 0x08, 0x09, 0x23, 0x00, 0x08, 0x09, 0x0A, 0x0B, 0x0D, 0x00
	.byte 0x0B, 0x0C, 0x0D, 0x0E, 0x11, 0x00, 0x0D, 0x0E, 0x0F, 0x10

	.global ov06_02250CDA
ov06_02250CDA: ; 0x02250CDA
	.byte 0x5A, 0x00

	.global ov06_02250CDC
ov06_02250CDC: ; 0x02250CDC
	.byte 0x8D, 0x00, 0x5B, 0x00, 0x8E, 0x00, 0x5C, 0x00, 0x8F, 0x00, 0x5D, 0x00, 0x90, 0x00, 0x5E, 0x00
	.byte 0x91, 0x00, 0x02, 0x00, 0x04, 0x00, 0x03, 0x00, 0x06, 0x00, 0x3C, 0x00, 0x03, 0x00, 0x3D, 0x00
	.byte 0x08, 0x00, 0x20, 0x00, 0x3E, 0x00, 0x21, 0x00, 0x3F, 0x00, 0x04, 0x00, 0x34, 0x00, 0x05, 0x00
	.byte 0x35, 0x00, 0x2C, 0x00, 0x01, 0x00, 0x2D, 0x00, 0x02, 0x00, 0x14, 0x00, 0x0F, 0x00, 0x15, 0x00
	.byte 0x10, 0x00, 0x51, 0x00, 0x3B, 0x00, 0x1A, 0x00, 0x3C, 0x00, 0x10, 0x00, 0x09, 0x00, 0x11, 0x00
	.byte 0x0C, 0x00, 0x53, 0x00, 0x17, 0x00, 0x54, 0x00, 0x16, 0x00, 0x47, 0x00, 0x29, 0x00, 0x12, 0x00
	.byte 0x2A, 0x00, 0x0C, 0x00, 0x26, 0x00, 0x0D, 0x00, 0x27, 0x00, 0x0E, 0x00, 0x33, 0x00, 0x0A, 0x00
	.byte 0x07, 0x00, 0x1B, 0x00, 0x11, 0x00, 0x23, 0x00, 0x25, 0x00, 0x31, 0x00, 0x46, 0x00, 0x32, 0x00
	.byte 0x46, 0x00, 0x27, 0x00, 0x0B, 0x00, 0x28, 0x00, 0x0E, 0x00, 0x18, 0x00, 0x0B, 0x00, 0x19, 0x00
	.byte 0x0E, 0x00, 0x35, 0x00, 0x44, 0x00, 0x36, 0x00, 0x45, 0x00, 0x1D, 0x00, 0x0B, 0x00, 0x06, 0x00
	.byte 0x05, 0x00, 0x1C, 0x00, 0x01, 0x00, 0x13, 0x00, 0x2D, 0x00, 0x0B, 0x00, 0x36, 0x00, 0x2E, 0x00
	.byte 0x38, 0x00, 0x09, 0x00, 0x14, 0x00, 0x30, 0x00, 0x32, 0x00, 0x34, 0x00, 0x0A, 0x00, 0x25, 0x00
	.byte 0x13, 0x00, 0x39, 0x00, 0x1F, 0x00, 0x29, 0x00, 0x1D, 0x00, 0x22, 0x00, 0x24, 0x00, 0x3B, 0x00
	.byte 0x28, 0x00, 0x3A, 0x00, 0x2B, 0x00, 0x26, 0x00, 0x22, 0x00, 0x33, 0x00, 0x3E, 0x00, 0x1E, 0x00
	.byte 0x0E, 0x00, 0x50, 0x00, 0x37, 0x00, 0x24, 0x00, 0x0D, 0x00, 0x07, 0x00, 0x0C, 0x00, 0x55, 0x00
	.byte 0x23, 0x00, 0x0F, 0x00, 0x2C, 0x00, 0x16, 0x00, 0x47, 0x00, 0x00, 0x00

	.global ov06_02250DD8
ov06_02250DD8: ; 0x02250DD8
	.byte 0x78, 0x56, 0x34, 0x12, 0x02, 0x00, 0x00, 0x00, 0x71, 0x00, 0x90, 0x00, 0xF1, 0x00, 0xA2, 0x00
	.byte 0xA3, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x78, 0x56, 0x34, 0x12, 0x09, 0x00, 0x00, 0x00, 0x71, 0x00, 0x90, 0x00, 0xF1, 0x00, 0xA2, 0x00
	.byte 0xA4, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x78, 0x56, 0x34, 0x12, 0x0B, 0x00, 0x00, 0x00, 0x71, 0x00, 0x90, 0x00, 0xF1, 0x00, 0xA2, 0x00
	.byte 0xA5, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x78, 0x56, 0x34, 0x12, 0x1E, 0x00, 0x00, 0x00, 0x71, 0x00, 0x90, 0x00, 0xF1, 0x00, 0xA2, 0x00
	.byte 0xA6, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x78, 0x56, 0x34, 0x12, 0x55, 0x00, 0x00, 0x00, 0x71, 0x00, 0x90, 0x00, 0xF1, 0x00, 0xA2, 0x00
	.byte 0xA7, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x78, 0x56, 0x34, 0x12, 0x50, 0x00, 0x00, 0x00, 0x71, 0x00, 0x90, 0x00, 0xF1, 0x00, 0xA2, 0x00
	.byte 0xA8, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x78, 0x56, 0x34, 0x12, 0x1D, 0x00, 0x00, 0x00, 0x71, 0x00, 0x90, 0x00, 0xF1, 0x00, 0xA2, 0x00
	.byte 0xA9, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02250F28
ov06_02250F28: ; 0x02250F28
	.byte 0x01, 0x00, 0xEA, 0x00, 0x16, 0x00, 0x4B, 0x00, 0xEB, 0x00, 0x4C, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x86, 0x00, 0x68, 0x00, 0x5F, 0x00, 0x71, 0x00, 0x7E, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0xFD, 0x00, 0x34, 0x00, 0x53, 0x00
	.byte 0x35, 0x00, 0x7E, 0x00, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x83, 0x00, 0x79, 0x00, 0x5C, 0x00
	.byte 0x63, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x07, 0x00, 0xF3, 0x00, 0x37, 0x00, 0x39, 0x00, 0x60, 0x01, 0x38, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x6D, 0x00, 0x7C, 0x00, 0x5D, 0x00, 0x92, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7B, 0x00, 0xDD, 0x00, 0x3E, 0x01, 0xD3, 0x00
	.byte 0x68, 0x00, 0x3A, 0x01, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x6A, 0x00, 0x79, 0x00, 0x9A, 0x00
	.byte 0x55, 0x00, 0x60, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x6B, 0x01, 0xF6, 0x00, 0x2D, 0x01, 0x60, 0x01, 0x02, 0x01, 0xBD, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x70, 0x00, 0x8F, 0x00, 0x67, 0x00, 0x9A, 0x00, 0x68, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x51, 0x00, 0x99, 0x00, 0x5F, 0x01, 0x30, 0x00
	.byte 0x3F, 0x01, 0x73, 0x00, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x64, 0x00, 0x55, 0x00, 0x9C, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x2C, 0x01, 0xD9, 0x00, 0x2F, 0x00, 0x39, 0x01, 0xCC, 0x00, 0x03, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x59, 0x00, 0x7E, 0x00, 0x64, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0x01, 0xE8, 0x00, 0xFC, 0x00, 0x45, 0x00
	.byte 0xC5, 0x00, 0x12, 0x00, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x8F, 0x00, 0x60, 0x00, 0x7F, 0x00
	.byte 0x68, 0x00, 0x70, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xA7, 0x00, 0xC9, 0x00, 0x44, 0x01, 0x65, 0x00, 0xA9, 0x00, 0xB8, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x55, 0x00, 0x79, 0x00, 0x8F, 0x00, 0x9C, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1B, 0x00, 0xED, 0x00, 0x5B, 0x00, 0x3D, 0x01
	.byte 0xC9, 0x00, 0x1C, 0x00, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x66, 0x00, 0xA1, 0x00, 0x7A, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x14, 0x01, 0xCB, 0x00, 0x13, 0x00, 0x62, 0x00, 0x1B, 0x01, 0x74, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x6A, 0x00, 0x81, 0x00, 0x92, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x66, 0x00, 0x97, 0x00, 0x5D, 0x00, 0xF6, 0x00
	.byte 0x49, 0x00, 0x71, 0x00, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x70, 0x00, 0x8F, 0x00, 0x70, 0x00
	.byte 0x8F, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x4A, 0x00, 0xE6, 0x00, 0xDE, 0x00, 0x5E, 0x01, 0x46, 0x00, 0xB6, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x55, 0x00, 0x68, 0x00, 0x75, 0x00, 0x87, 0x00, 0x77, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC8, 0x00, 0xD5, 0x00, 0xDC, 0x00, 0xF7, 0x00
	.byte 0x6D, 0x00, 0x56, 0x00, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x91, 0x00, 0x57, 0x00, 0x8F, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x73, 0x01, 0x9D, 0x00, 0xE1, 0x00, 0x1D, 0x00, 0x18, 0x01, 0xB8, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x70, 0x00, 0x75, 0x00, 0x8A, 0x00, 0x55, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE4, 0x00, 0xF9, 0x00, 0xF2, 0x00, 0x34, 0x00
	.byte 0x2E, 0x00, 0xB6, 0x00, 0x78, 0x56, 0x34, 0x12, 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F
	.byte 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF, 0x78, 0x00, 0x9C, 0x00, 0x84, 0x00
	.byte 0x9C, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x31, 0x01, 0x9E, 0x00, 0xE8, 0x00, 0x3D, 0x01, 0x4E, 0x01, 0x6A, 0x00, 0x78, 0x56, 0x34, 0x12
	.byte 0x32, 0x54, 0x76, 0x98, 0xFF, 0xFF, 0xFF, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00
	.byte 0x00, 0xFF, 0x64, 0x00, 0x7A, 0x00, 0x9A, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF

	.global ov06_022512E0
ov06_022512E0: ; 0x022512E0
	.byte 0x01, 0x01, 0x01, 0x01

	.global ov06_022512E4
ov06_022512E4: ; 0x022512E4
	.byte 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x00

	.global ov06_022512EC
ov06_022512EC: ; 0x022512EC
	.byte 0x05, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00
	.byte 0x11, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00

	.global ov06_02251308
ov06_02251308: ; 0x02251308
	.byte 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00

	.global ov06_02251324
ov06_02251324: ; 0x02251324
	.byte 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00

	.global ov06_02251340
ov06_02251340: ; 0x02251340
	.byte 0x56, 0x01, 0x00, 0x00, 0x57, 0x01, 0x00, 0x00, 0x58, 0x01, 0x00, 0x00, 0x5E, 0x01, 0x00, 0x00
	.byte 0x61, 0x01, 0x00, 0x00, 0x62, 0x01, 0x00, 0x00, 0x64, 0x01, 0x00, 0x00, 0x75, 0x01, 0x00, 0x00
	.byte 0x7C, 0x01, 0x00, 0x00, 0x7E, 0x01, 0x00, 0x00, 0x7F, 0x01, 0x00, 0x00, 0x81, 0x01, 0x00, 0x00
	.byte 0x84, 0x01, 0x00, 0x00, 0x88, 0x01, 0x00, 0x00, 0x8B, 0x01, 0x00, 0x00, 0x8F, 0x01, 0x00, 0x00
	.byte 0x90, 0x01, 0x00, 0x00, 0xD5, 0x01, 0x00, 0x00, 0x93, 0x01, 0x00, 0x00, 0x96, 0x01, 0x00, 0x00
	.byte 0x97, 0x01, 0x00, 0x00, 0xD7, 0x01, 0x00, 0x00, 0x38, 0x01, 0x00, 0x00, 0x3B, 0x01, 0x00, 0x00
	.byte 0x3E, 0x01, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xCB, 0x00, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x00

	.global ov06_022513B0
ov06_022513B0: ; 0x022513B0
	.word ov06_02247BFC

	.global ov06_022513B4
ov06_022513B4: ; 0x022513B4
	.word ov06_02246024

	.global ov06_022513B8
ov06_022513B8: ; 0x022513B8
	.word ov06_02247CB4, ov06_02247DC0
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global ov06_022513D8
ov06_022513D8: ; 0x022513D8
	.word ov06_022513B4, ov06_02251550, 0x00000001, 0x0000000B

	.global ov06_022513E8
ov06_022513E8: ; 0x022513E8
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_022513F4
ov06_022513F4: ; 0x022513F4
	.byte 0x00, 0x80, 0x12, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251400
ov06_02251400: ; 0x02251400
	.byte 0x00, 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0225140C
ov06_0225140C: ; 0x0225140C
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251418
ov06_02251418: ; 0x02251418
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0xF0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251424
ov06_02251424: ; 0x02251424
	.byte 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251430
ov06_02251430: ; 0x02251430
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0225143C
ov06_0225143C: ; 0x0225143C
	.byte 0x00, 0x80, 0x08, 0x00, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251448
ov06_02251448: ; 0x02251448
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251454
ov06_02251454: ; 0x02251454
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251460
ov06_02251460: ; 0x02251460
	.word ov06_022513B0, ov06_022513B8, ov06_022514B4

	.global ov06_0225146C
ov06_0225146C: ; 0x0225146C
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251478
ov06_02251478: ; 0x02251478
	.byte 0x00, 0x80, 0x08, 0x00, 0x00, 0x80, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251484
ov06_02251484: ; 0x02251484
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_02251490
ov06_02251490: ; 0x02251490
	.byte 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_0225149C
ov06_0225149C: ; 0x0225149C
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_022514A8
ov06_022514A8: ; 0x022514A8
	.byte 0x00, 0x80, 0x12, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_022514B4
ov06_022514B4: ; 0x022514B4
	.word ov06_02247F30, ov06_022480A0, ov06_022480FC, ov06_02248238

	.global ov06_022514C4
ov06_022514C4: ; 0x022514C4
	.byte 0x00, 0xC0, 0xFF, 0xFF, 0x00, 0xA0, 0xFF, 0xFF, 0x00, 0x90, 0xFF, 0xFF, 0x00, 0x80, 0xFF, 0xFF

	.global ov06_022514D4
ov06_022514D4: ; 0x022514D4
	.word 0x00000024, ov06_022482F4, sub_02064798, ov06_022483A0
	.word sub_02064794

	.global ov06_022514E8
ov06_022514E8: ; 0x022514E8
	.word 0x00000024, ov06_02247A54, ov06_02247A9C, ov06_02247AA8
	.word ov06_02247B28

	.global ov06_022514FC
ov06_022514FC: ; 0x022514FC
	.word 0x00000008, ov06_02248670, sub_02064798, ov06_02248684
	.word sub_02064794

	.global ov06_02251510
ov06_02251510: ; 0x02251510
	.word 0x00000068, ov06_02247BA0, ov06_02247BCC, ov06_02247BD8
	.word ov06_02247BF8

	.global ov06_02251524
ov06_02251524: ; 0x02251524
	.word 0x00000074, ov06_02245FAC, ov06_02245FF8, ov06_02246004
	.word sub_02064794

	.global ov06_02251538
ov06_02251538: ; 0x02251538
	.word ov06_02248438, ov06_02248450, ov06_02248594, ov06_022485DC
	.word ov06_02248608, ov06_02248630

	.global ov06_02251550
ov06_02251550: ; 0x02251550
	.word ov06_0224619C, ov06_0224629C, ov06_022462D0, ov06_022463BC
	.word ov06_022463E0, ov06_022464A4, ov06_022465B0, ov06_02246600

	.global ov06_02251570
ov06_02251570: ; 0x02251570
	.byte 0x00, 0x40, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xC0, 0xFE, 0xFF, 0x00, 0x80, 0xFE, 0xFF
	.byte 0x00, 0x60, 0xFE, 0xFF, 0x00, 0x40, 0xFE, 0xFF, 0x00, 0x40, 0xFE, 0xFF, 0x00, 0x40, 0xFE, 0xFF
	.byte 0x00, 0x60, 0xFE, 0xFF, 0x00, 0x80, 0xFE, 0xFF, 0x00, 0xA0, 0xFE, 0xFF, 0x00, 0xC0, 0xFE, 0xFF

	.global ov06_022515A0
ov06_022515A0: ; 0x022515A0
	.word ov06_0224671C, ov06_02246734, ov06_022467A4, ov06_022467DC
	.word ov06_0224681C, ov06_022468A0, ov06_022468C0, ov06_0224690C
	.word ov06_02246974, ov06_02246994, ov06_022469F8, ov06_02246A78
	.word ov06_02246A8C, ov06_02246AA0

	.global ov06_022515D8
ov06_022515D8: ; 0x022515D8
	.word ov06_0224671C, ov06_02246ADC, ov06_022467A4, ov06_022467DC
	.word ov06_0224681C, ov06_022468A0, ov06_022468C0, ov06_0224690C
	.word ov06_02246974, ov06_02246994, ov06_02246B4C, ov06_02246B60
	.word ov06_02246B78, ov06_02246B98, ov06_02246BC0, ov06_02246BE8
	.word ov06_02246C08, ov06_02246C38, ov06_02246CDC, ov06_02246D24
	.word ov06_02246A78, ov06_02246A8C, ov06_02246AA0

	.global ov06_02251634
ov06_02251634: ; 0x02251634
	.byte 0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x85, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x04, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xD0, 0x03, 0x00
	.byte 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00
	.byte 0x00, 0x50, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x80, 0x02, 0x00, 0x00, 0xE0, 0x04, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0xB0, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x60, 0x05, 0x00
	.byte 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00
	.byte 0x00, 0x40, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xF0, 0x05, 0x00, 0x00, 0xD0, 0x06, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x09, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xE0, 0x07, 0x00
	.byte 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x08, 0x00
	.byte 0x00, 0xD0, 0x07, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0xD0, 0x0D, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global ov06_02251738
ov06_02251738: ; 0x02251738
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
	.byte 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
	.byte 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F
	.byte 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37

	.global ov06_02251770
ov06_02251770: ; 0x02251770
	.word ov06_022490F0, ov06_02249108, ov06_022490F4, ov06_0224911C
	.word ov06_02249130, ov06_02249144, ov06_02249158, ov06_0224916C
	.word ov06_02249184, ov06_02249194, ov06_022491A4

	.global ov06_0225179C
ov06_0225179C: ; 0x0225179C
	.byte 0x02, 0x02, 0x02, 0x15

	.global ov06_022517A0
ov06_022517A0: ; 0x022517A0
	.byte 0x02, 0x0F, 0x02, 0x14, 0x03, 0x17

	.global ov06_022517A6
ov06_022517A6: ; 0x022517A6
	.byte 0x02, 0x01, 0x02, 0x19, 0x02, 0x1D

	.global ov06_022517AC
ov06_022517AC: ; 0x022517AC
	.byte 0x02, 0x03, 0x02, 0x11
	.byte 0x03, 0x15, 0x02, 0x19

	.global ov06_022517B4
ov06_022517B4: ; 0x022517B4
	.byte 0x03, 0x01, 0x02, 0x06, 0x02, 0x0B, 0x04, 0x0C

	.global ov06_022517BC
ov06_022517BC: ; 0x022517BC
	.byte 0x02, 0x03, 0x02, 0x0B
	.byte 0x02, 0x0C, 0x00, 0x0E

	.global ov06_022517C4
ov06_022517C4: ; 0x022517C4
	.byte 0x02, 0x04, 0x04, 0x07, 0x02, 0x0E, 0x02, 0x18

	.global ov06_022517CC
ov06_022517CC: ; 0x022517CC
	.byte 0x02, 0x03, 0x02, 0x0C
	.byte 0x02, 0x1E, 0x00, 0x1F

	.global ov06_022517D4
ov06_022517D4: ; 0x022517D4
	.byte 0x02, 0x01, 0x01, 0x03, 0x02, 0x0B, 0x02, 0x10, 0x00, 0x17

	.global ov06_022517DE
ov06_022517DE: ; 0x022517DE
	.byte 0x00, 0x01
	.byte 0x02, 0x03, 0x00, 0x04, 0x02, 0x05, 0x02, 0x08, 0x02, 0x1D

	.global ov06_022517EA
ov06_022517EA: ; 0x022517EA
	.byte 0x03, 0x06, 0x03, 0x09, 0x01, 0x0D
	.byte 0x01, 0x0E, 0x02, 0x0F, 0x01, 0x10, 0x02, 0x1C

	.global ov06_022517F8
ov06_022517F8: ; 0x022517F8
	.byte 0x02, 0x06, 0x02, 0x08, 0x02, 0x17, 0x02, 0x18
	.byte 0x01, 0x19, 0x00, 0x1A, 0x01, 0x1F, 0x00, 0x00

	.global ov06_02251808
ov06_02251808: ; 0x02251808
	.byte 0x00, 0x00, 0x00, 0x00, 0xFB, 0xFF, 0xFF, 0xFF, 0x05, 0x00, 0x00, 0x00, 0xF6, 0xFF, 0xFF, 0xFF
	.byte 0x0A, 0x00, 0x00, 0x00

	.global ov06_0225181C
ov06_0225181C: ; 0x0225181C
	.word 0x00000004, ov06_022517B4, 0x00000004, ov06_022517BC
	.word 0x00000004, ov06_022517AC, 0x00000003, ov06_022517A6
	.word 0x00000006, ov06_022517DE, 0x00000002, ov06_0225179C
	.word 0x00000004, ov06_022517C4, 0x00000007, ov06_022517EA
	.word 0x00000003, ov06_022517A0, 0x00000004, ov06_022517CC
	.word 0x00000005, ov06_022517D4, 0x00000007, ov06_022517F8

	.global ov06_0225187C
ov06_0225187C: ; 0x0225187C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251888
ov06_02251888: ; 0x02251888
	.word 0x00000020, ov06_0224954C, ov06_02249598, ov06_0224959C
	.word ov06_02249608

	.global ov06_0225189C
ov06_0225189C: ; 0x0225189C
	.byte 0x00, 0xE0, 0x00, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00
	.byte 0x00, 0x40, 0x00, 0x00

	.global ov06_022518B0
ov06_022518B0: ; 0x022518B0
	.word 0x00000020, ov06_0224954C, ov06_02249598, ov06_022496AC
	.word ov06_02249700

	.global ov06_022518C4
ov06_022518C4: ; 0x022518C4
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_022518E8
ov06_022518E8: ; 0x022518E8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_0225190C
ov06_0225190C: ; 0x0225190C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x0E, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00

	.global ov06_02251948
ov06_02251948: ; 0x02251948
	.byte 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00

	.global ov06_02251958
ov06_02251958: ; 0x02251958
	.word 0x00000038, ov06_02249834, ov06_022498AC, ov06_022498BC
	.word ov06_02249954

	.global ov06_0225196C
ov06_0225196C: ; 0x0225196C
	.word 0x00000038, ov06_02249BC4, ov06_02249C24, ov06_02249C30
	.word ov06_02249C74

	.global ov06_02251980
ov06_02251980: ; 0x02251980
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_0225198C
ov06_0225198C: ; 0x0225198C
	.word 0x0000001C, ov06_02249F84, ov06_02249FAC, ov06_02249FB0
	.word ov06_02249FE0

	.global ov06_022519A0
ov06_022519A0: ; 0x022519A0
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_022519C4
ov06_022519C4: ; 0x022519C4
	.byte 0x5D, 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x61, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00
	.byte 0x65, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00

	.global ov06_022519EC
ov06_022519EC: ; 0x022519EC
	.byte 0x3B, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00
	.byte 0x3F, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00
	.byte 0x43, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00

	.global ov06_02251A14
ov06_02251A14: ; 0x02251A14
	.byte 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global ov06_02251A54
ov06_02251A54: ; 0x02251A54
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251A60
ov06_02251A60: ; 0x02251A60
	.word 0x0000006C, ov06_0224A19C, ov06_0224A1D8, ov06_0224A1DC
	.word ov06_0224A238

	.global ov06_02251A74
ov06_02251A74: ; 0x02251A74
	.byte 0x45, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00
	.byte 0x49, 0x00, 0x00, 0x00, 0x4A, 0x00, 0x00, 0x00

	.global ov06_02251A8C
ov06_02251A8C: ; 0x02251A8C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251AB0
ov06_02251AB0: ; 0x02251AB0
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251ABC
ov06_02251ABC: ; 0x02251ABC
	.byte 0x4D, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x00

	.global ov06_02251AC8
ov06_02251AC8: ; 0x02251AC8
	.word 0x0000001C, ov06_0224A570, ov06_0224A5B0, ov06_0224A5C8
	.word ov06_0224A624

	.global ov06_02251ADC
ov06_02251ADC: ; 0x02251ADC
	.word 0x0000001C, ov06_0224A354, ov06_0224A380, ov06_0224A384
	.word ov06_0224A3F4

	.global ov06_02251AF0
ov06_02251AF0: ; 0x02251AF0
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251B04
ov06_02251B04: ; 0x02251B04
	.byte 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251B1C
ov06_02251B1C: ; 0x02251B1C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251B40
ov06_02251B40: ; 0x02251B40
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251B4C
ov06_02251B4C: ; 0x02251B4C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251B58
ov06_02251B58: ; 0x02251B58
	.word 0x00000020, ov06_0224A710, ov06_0224A7C8, ov06_0224A7DC
	.word ov06_0224A870

	.global ov06_02251B6C
ov06_02251B6C: ; 0x02251B6C
	.word 0x00000018, ov06_0224A918, ov06_0224A944, ov06_0224A948
	.word ov06_0224A9A0

	.global ov06_02251B80
ov06_02251B80: ; 0x02251B80
	.word 0x00000018, ov06_0224AA84, ov06_0224AAB0, ov06_0224AAB4
	.word ov06_0224AB0C

	.global ov06_02251B94
ov06_02251B94: ; 0x02251B94
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251BB8
ov06_02251BB8: ; 0x02251BB8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251BDC
ov06_02251BDC: ; 0x02251BDC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00

	.global ov06_02251BE8
ov06_02251BE8: ; 0x02251BE8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251BF4
ov06_02251BF4: ; 0x02251BF4
	.word 0x00000034, ov06_0224AC38, ov06_0224AC80, ov06_0224AC98
	.word ov06_0224AD44

	.global ov06_02251C08
ov06_02251C08: ; 0x02251C08
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251C2C
ov06_02251C2C: ; 0x02251C2C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251C38
ov06_02251C38: ; 0x02251C38
	.word 0x00000024, ov06_0224AF74, ov06_0224AFB0, ov06_0224AFC4
	.word ov06_0224AFF8

	.global ov06_02251C4C
ov06_02251C4C: ; 0x02251C4C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251C70
ov06_02251C70: ; 0x02251C70
	.word 0x0000000C, ov06_0224B188, ov06_0224B200, ov06_0224B214
	.word ov06_0224B23C

	.global ov06_02251C84
ov06_02251C84: ; 0x02251C84
	.word 0x0000000C, ov06_0224B324, ov06_0224B39C, ov06_0224B3B0
	.word ov06_0224B3D8

	.global ov06_02251C98
ov06_02251C98: ; 0x02251C98
	.word 0x00000038, ov06_0224B5D0, ov06_0224B664, ov06_0224B670
	.word ov06_0224B750, 0x00000020, ov06_0224B788, ov06_0224B7C0
	.word ov06_0224B7CC, ov06_0224B800

	.global ov06_02251CC0
ov06_02251CC0: ; 0x02251CC0
	.word 0x00000028, ov06_0224B878, ov06_0224B8FC, ov06_0224B908
	.word ov06_0224B930

	.global ov06_02251CD4
ov06_02251CD4: ; 0x02251CD4
	.byte 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251CEC
ov06_02251CEC: ; 0x02251CEC
	.byte 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251D04
ov06_02251D04: ; 0x02251D04
	.byte 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251D1C
ov06_02251D1C: ; 0x02251D1C
	.byte 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251D34
ov06_02251D34: ; 0x02251D34
	.word 0x00000028, ov06_0224BA30, ov06_0224BA88, ov06_0224BA94
	.word ov06_0224BB0C

	.global ov06_02251D48
ov06_02251D48: ; 0x02251D48
	.byte 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251D60
ov06_02251D60: ; 0x02251D60
	.word 0x00000024, ov06_0224BC50, ov06_0224BC94, ov06_0224BCA0
	.word ov06_0224BCD0

	.global ov06_02251D74
ov06_02251D74: ; 0x02251D74
	.byte 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251D8C
ov06_02251D8C: ; 0x02251D8C
	.word 0x00000038, ov06_0224BDF8, ov06_0224BE8C, ov06_0224BE98
	.word ov06_0224BF64

	.global ov06_02251DA0
ov06_02251DA0: ; 0x02251DA0
	.byte 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251DB8
ov06_02251DB8: ; 0x02251DB8
	.word 0x00000038, ov06_0224C0A0, ov06_0224C140, ov06_0224C14C
	.word ov06_0224C218

	.global ov06_02251DCC
ov06_02251DCC: ; 0x02251DCC
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251DE4
ov06_02251DE4: ; 0x02251DE4
	.byte 0x77, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00

	.global ov06_02251DF4
ov06_02251DF4: ; 0x02251DF4
	.word ov06_0224C954, ov06_0224C9C8, ov06_0224CA0C, ov06_0224CA58

	.global ov06_02251E04
ov06_02251E04: ; 0x02251E04
	.word ov06_0224C75C, ov06_0224C7C0, ov06_0224C844, ov06_0224C888

	.global ov06_02251E14
ov06_02251E14: ; 0x02251E14
	.byte 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00
	.byte 0xFE, 0x00, 0x00, 0x00

	.global ov06_02251E28
ov06_02251E28: ; 0x02251E28
	.word ov06_0224CAE8, ov06_0224CB0C, ov06_0224C75C, ov06_0224C7C0
	.word ov06_0224C844, ov06_0224C888

	.global ov06_02251E40
ov06_02251E40: ; 0x02251E40
	.byte 0x01, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00
	.byte 0xFE, 0x00, 0x00, 0x00

	.global ov06_02251EA4
ov06_02251EA4: ; 0x02251EA4
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x01, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x03, 0x00
	.byte 0x00, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x04, 0x00, 0x03, 0x00, 0x01, 0x00, 0x3C, 0x00, 0x05, 0x00
	.byte 0x01, 0x00, 0x01, 0x00, 0xFE, 0x00, 0x00, 0x00

	.global ov06_02251F0C
ov06_02251F0C: ; 0x02251F0C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov06_02251F18
ov06_02251F18: ; 0x02251F18
	.byte 0x67, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x69, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x00, 0x00

	.global ov06_02251F28
ov06_02251F28: ; 0x02251F28
	.word 0x00000024, ov06_0224CF3C, ov06_0224CF6C, ov06_0224CF8C
	.word ov06_0224CF90

	.global ov06_02251F3C
ov06_02251F3C: ; 0x02251F3C
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov06_02251F60
ov06_02251F60: ; 0x02251F60
	.word 0x00000024, ov06_0224D344, ov06_0224D388, ov06_0224D394
	.word ov06_0224D3C4

	.global ov06_02251F74
ov06_02251F74: ; 0x02251F74
	.byte 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global ov06_02251F8C
ov06_02251F8C: ; 0x02251F8C
	.byte 0x07, 0x00, 0x00, 0x00, 0x70, 0x00, 0x28, 0x00, 0x08, 0x00, 0x00, 0x00, 0x98, 0x00, 0x28, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x28, 0x00, 0x0A, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x28, 0x00

	.global ov06_02251FAC
ov06_02251FAC: ; 0x02251FAC
	.byte 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x38, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x48, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x58, 0x00, 0x05, 0x00, 0x00, 0x00, 0x08, 0x00, 0x68, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x78, 0x00

	.global ov06_02251FD4
ov06_02251FD4: ; 0x02251FD4
	.byte 0x0B, 0x00, 0x00, 0x00, 0x70, 0x00, 0x38, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x98, 0x00, 0x38, 0x00
	.byte 0x0D, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x38, 0x00, 0x0E, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x38, 0x00
	.byte 0x0F, 0x00, 0x00, 0x00, 0x70, 0x00, 0x48, 0x00, 0x10, 0x00, 0x00, 0x00, 0x98, 0x00, 0x48, 0x00
	.byte 0x11, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x48, 0x00, 0x12, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x48, 0x00
	.byte 0x13, 0x00, 0x00, 0x00, 0x70, 0x00, 0x58, 0x00, 0x14, 0x00, 0x00, 0x00, 0x98, 0x00, 0x58, 0x00
	.byte 0x15, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x58, 0x00, 0x16, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x58, 0x00
	.byte 0x17, 0x00, 0x00, 0x00, 0x70, 0x00, 0x68, 0x00, 0x18, 0x00, 0x00, 0x00, 0x98, 0x00, 0x68, 0x00
	.byte 0x19, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x68, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x68, 0x00
	.byte 0x1B, 0x00, 0x00, 0x00, 0x70, 0x00, 0x78, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x98, 0x00, 0x78, 0x00
	.byte 0x1D, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x78, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x78, 0x00

	.global ov06_02252074
ov06_02252074: ; 0x02252074
	.byte 0x08, 0x88, 0x00, 0x00

	.global ov06_02252078
ov06_02252078: ; 0x02252078
	.byte 0x03, 0x18, 0x0D, 0x07, 0x04, 0x0D, 0xC8, 0x01

	.global ov06_02252080
ov06_02252080: ; 0x02252080
	.byte 0x32, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
	.byte 0x36, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00
	.byte 0x1C, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x3A, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00
	.byte 0x11, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x1E, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00
	.byte 0x3E, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00
	.byte 0x1D, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00
	.byte 0xFA, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x42, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0xB4, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00
	.byte 0x1E, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00
	.byte 0x78, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00
	.byte 0x46, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0xFA, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00
	.byte 0x22, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00

	.global ov06_02252188
ov06_02252188: ; 0x02252188
	.byte 0x0C, 0x09, 0x0E, 0x0B

	.global ov06_0225218C
ov06_0225218C: ; 0x0225218C
	.word 0x00000400, 0x000000F0, ov06_0224EB30, ov06_0224EBC4
	.word ov06_0224EBD4, ov06_0224EC08

	.global ov06_022521A4
ov06_022521A4: ; 0x022521A4
	.word 0x00000400, 0x000000F0, ov06_0224EB78, ov06_0224EBC4
	.word ov06_0224EBD4, ov06_0224EC08

	.global ov06_022521BC
ov06_022521BC: ; 0x022521BC
	.word 0x00000400, 0x000001CC, ov06_0224EC5C, ov06_0224ECF4
	.word ov06_0224ED14, ov06_0224ED7C

	.global ov06_022521D4
ov06_022521D4: ; 0x022521D4
	.word 0x00000400, 0x000000F0, ov06_0224EA64, ov06_0224EAAC
	.word ov06_0224EABC, ov06_0224EAF0

	.global ov06_022521EC
ov06_022521EC: ; 0x022521EC
	.word 0x00000400, 0x00000D10, ov06_0224EF98, ov06_0224F02C
	.word ov06_0224F068, ov06_0224F0A4

	.global ov06_02252204
ov06_02252204: ; 0x02252204
	.word ov06_0224EB10, ov06_0224EC3C, ov06_0224EC3C

	.global ov06_02252210
ov06_02252210: ; 0x02252210
	.word ov06_0224EAFC, ov06_0224EC14, ov06_0224EC28

	.global ov06_0225221C
ov06_0225221C: ; 0x0225221C
	.word ov06_0224EB18, ov06_0224EC44, ov06_0224EC44

	.data
	.global ov06_02252240
ov06_02252240: ; 0x02252240
	.word 0x00000400, 0x0000000C, 0x00000000, ov06_0223A188
	.word ov06_0223A19C, ov06_0223A1B0

	.global ov06_02252258
ov06_02252258: ; 0x02252258
	.byte 0x64, 0x61, 0x74, 0x61, 0x2F, 0x73, 0x68, 0x6F
	.byte 0x70, 0x5F, 0x68, 0x2E, 0x63, 0x6C, 0x64, 0x61, 0x74, 0x00, 0x00, 0x00

	.global ov06_0225226C
ov06_0225226C: ; 0x0225226C
	.byte 0x64, 0x61, 0x74, 0x61
	.byte 0x2F, 0x73, 0x68, 0x6F, 0x70, 0x5F, 0x63, 0x68, 0x72, 0x2E, 0x72, 0x65, 0x73, 0x64, 0x61, 0x74
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov06_02252284
ov06_02252284: ; 0x02252284
	.byte 0x64, 0x61, 0x74, 0x61, 0x2F, 0x73, 0x68, 0x6F, 0x70, 0x5F, 0x70, 0x61
	.byte 0x6C, 0x2E, 0x72, 0x65, 0x73, 0x64, 0x61, 0x74, 0x00, 0x00, 0x00, 0x00

	.global ov06_0225229C
ov06_0225229C: ; 0x0225229C
	.byte 0x64, 0x61, 0x74, 0x61
	.byte 0x2F, 0x73, 0x68, 0x6F, 0x70, 0x5F, 0x63, 0x65, 0x6C, 0x6C, 0x2E, 0x72, 0x65, 0x73, 0x64, 0x61
	.byte 0x74, 0x00, 0x00, 0x00

	.global ov06_022522B4
ov06_022522B4: ; 0x022522B4
	.byte 0x64, 0x61, 0x74, 0x61, 0x2F, 0x73, 0x68, 0x6F, 0x70, 0x5F, 0x63, 0x61
	.byte 0x6E, 0x6D, 0x2E, 0x72, 0x65, 0x73, 0x64, 0x61, 0x74, 0x00, 0x00, 0x00

	.global ov06_022522CC
ov06_022522CC: ; 0x022522CC
	.byte 0x01, 0x02, 0x03, 0x05
	.byte 0x07, 0x04, 0x0B, 0x0A, 0x09, 0x00, 0x00, 0x00

	.global ov06_022522D8
ov06_022522D8: ; 0x022522D8
	.byte 0x46, 0x47, 0x48, 0x49, 0x4B, 0x4D, 0x4D, 0x4D
	.byte 0x4F, 0x00, 0x00, 0x00

	.global ov06_022522E4
ov06_022522E4: ; 0x022522E4
	.byte 0x73, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global ov06_022522FC
ov06_022522FC: ; 0x022522FC
	.byte 0x06, 0x00, 0x00, 0x00

	.global ov06_02252300
ov06_02252300: ; 0x02252300
	.word ov06_0224F73C, ov06_0224F734, ov06_0224F724, ov06_0224F72C
	.word 0x0000000B, ov06_0224F75C, ov06_0224F768, ov06_0224F744
	.word ov06_0224F750, 0x0000000E, ov06_02250C10, ov06_02250C20
	.word ov06_02250C00, ov06_02250C30

	.global ov06_02252338
ov06_02252338: ; 0x02252338
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x04
	.byte 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 0x07, 0x03, 0x08, 0x0A, 0x0A, 0x08, 0x05, 0x05
	.byte 0x09, 0x09, 0x06, 0x06, 0x0A, 0x00, 0x00, 0x00

	.global ov06_02252358
ov06_02252358: ; 0x02252358
	.byte 0x00, 0xB8, 0xFF, 0xFF

	.global ov06_0225235C
ov06_0225235C: ; 0x0225235C
	.byte 0x00, 0xC0, 0x00, 0x00

	.global ov06_02252360
ov06_02252360: ; 0x02252360
	.byte 0x00, 0xB8, 0xFF, 0xFF, 0x00, 0x48, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xB8, 0xFF, 0xFF
	.byte 0x00, 0xB8, 0xFF, 0xFF, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00
	.byte 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB8, 0xFF, 0xFF, 0x00, 0xC0, 0x00, 0x00
	.byte 0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00

	.global ov06_022523A0
ov06_022523A0: ; 0x022523A0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x10, 0x00, 0x18, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov06_022523C0
ov06_022523C0: ; 0x022523C0
	.byte 0x00, 0xB8, 0xFF, 0xFF

	.global ov06_022523C4
ov06_022523C4: ; 0x022523C4
	.byte 0x00, 0xC0, 0x00, 0x00

	.global ov06_022523C8
ov06_022523C8: ; 0x022523C8
	.byte 0x00, 0xB8, 0xFF, 0xFF, 0x00, 0x48, 0x00, 0x00
	.byte 0x00, 0xC0, 0x00, 0x00, 0x00, 0xB8, 0xFF, 0xFF, 0x00, 0xB8, 0xFF, 0xFF, 0x00, 0xC0, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xB8, 0xFF, 0xFF, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00
	.byte 0x00, 0xC0, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
	.global ov06_02252420
ov06_02252420: ; 0x02252420
	.space 0x4

	.global ov06_02252424
ov06_02252424: ; 0x02252424
	.space 0x1C
