	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD63_021D74E0
MOD63_021D74E0: ; 0x021D74E0
	push {r4, lr}
	ldr r1, _021D7584 ; =0x00007FFF
	add r4, r0, #0
	mov r0, #0
	bl FUN_0200E3A0
	ldr r1, _021D7584 ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
	ldr r1, _021D7588 ; =0x04001050
	mov r0, #0
	strh r0, [r1]
	ldr r1, _021D758C ; =0x04000050
	strh r0, [r1]
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7590 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7594 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	mov r2, #1
	mov r0, #3
	mov r1, #0x1e
	lsl r2, r2, #0x12
	bl FUN_0201681C
	mov r1, #0x79
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #0x1e
	bl OverlayManager_CreateAndGetData
	mov r2, #0x79
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r0, #0x1e
	str r0, [r4]
	mov r0, #0x1d
	mov r1, #0
	lsl r0, r0, #4
	strh r1, [r4, r0]
	add r0, #0x10
	str r1, [r4, r0]
	bl MOD63_021D7838
	add r0, r4, #0
	bl MOD63_021D7A48
	add r0, r4, #0
	bl MOD63_021D7880
	ldr r0, _021D7598 ; =MOD63_021D782C
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	bl GX_BothDispOn
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D7584: .word 0x00007FFF
_021D7588: .word 0x04001050
_021D758C: .word 0x04000050
_021D7590: .word 0xFFFFE0FF
_021D7594: .word 0x04001000
_021D7598: .word MOD63_021D782C
	thumb_func_end MOD63_021D74E0

	thumb_func_start MOD63_021D759C
MOD63_021D759C: ; 0x021D759C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #6
	bhi _021D7614
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D75BA: ; jump table
	.short _021D75C8 - _021D75BA - 2 ; case 0
	.short _021D7604 - _021D75BA - 2 ; case 1
	.short _021D7622 - _021D75BA - 2 ; case 2
	.short _021D7638 - _021D75BA - 2 ; case 3
	.short _021D76FA - _021D75BA - 2 ; case 4
	.short _021D773C - _021D75BA - 2 ; case 5
	.short _021D777E - _021D75BA - 2 ; case 6
_021D75C8:
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D7C18
	cmp r0, #1
	bne _021D7614
	add r0, r4, #0
	ldr r1, _021D77A4 ; =gMain
	mov r2, #0
	add r0, #0xb4
	str r2, [r0]
	ldr r0, [r1, #0x6c]
	cmp r0, #0
	bne _021D75F6
	mov r0, #0x75
	mov r1, #0x1e
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #2
	str r0, [r5]
	b _021D779C
_021D75F6:
	mov r0, #0x75
	lsl r0, r0, #2
	str r2, [r4, r0]
	str r2, [r1, #0x6c]
	mov r0, #1
	str r0, [r5]
	b _021D779C
_021D7604:
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D7D74
	cmp r0, #1
	beq _021D7616
_021D7614:
	b _021D779C
_021D7616:
	mov r0, #0
	add r4, #0xb4
	str r0, [r4]
	mov r0, #2
	str r0, [r5]
	b _021D779C
_021D7622:
	mov r0, #0
	bl FUN_0200415C
	mov r0, #1
	ldr r1, _021D77A8 ; =0x00000495
	add r2, r0, #0
	bl FUN_0200433C
	mov r0, #3
	str r0, [r5]
	b _021D779C
_021D7638:
	mov r0, #0x75
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D765A
	sub r1, r1, #1
	str r1, [r4, r0]
	mov r1, #0
	sub r0, #0x4c
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	b _021D779C
_021D765A:
	mov r1, #1
	sub r0, #0x4c
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	mov r1, #0x1e
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	ldr r2, _021D77A4 ; =gMain
	add r0, r0, #1
	str r0, [r4, r1]
	ldr r3, [r2, #0x48]
	mov r0, #1
	add r6, r3, #0
	and r6, r0
	cmp r6, #1
	beq _021D768C
	mov r6, #8
	and r3, r6
	cmp r3, #8
	bne _021D76A8
_021D768C:
	mov r0, #0x1d
	mov r1, #1
	lsl r0, r0, #4
	strh r1, [r4, r0]
	mov r0, #0
	mov r1, #0x3c
	bl FUN_020053CC
	ldr r0, _021D77AC ; =0x000005F4
	bl FUN_020054C8
	mov r0, #4
	str r0, [r5]
	b _021D779C
_021D76A8:
	ldr r6, [r2, #0x44]
	mov r3, #0x46
	and r3, r6
	cmp r3, #0x46
	bne _021D76D4
	mov r2, #2
	sub r1, #0x10
	strh r2, [r4, r1]
	mov r1, #6
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #6
	str r0, [r5]
	b _021D779C
_021D76D4:
	mov r3, #0xe1
	ldr r6, [r4, r1]
	lsl r3, r3, #2
	cmp r6, r3
	ble _021D779C
	mov r3, #3
	sub r1, #0x10
	strh r3, [r4, r1]
	mov r1, #0
	str r0, [r2, #0x6c]
	bl GX_EngineBToggleLayers
	mov r0, #0
	mov r1, #0x3c
	bl FUN_020053CC
	mov r0, #5
	str r0, [r5]
	b _021D779C
_021D76FA:
	mov r0, #0x62
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	bl FUN_02005404
	cmp r0, #0
	bne _021D779C
	ldr r0, _021D77A8 ; =0x00000495
	mov r1, #0
	bl FUN_02005350
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #6
	str r0, [r5]
	b _021D779C
_021D773C:
	mov r0, #0x62
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8260
	bl FUN_02005404
	cmp r0, #0
	bne _021D779C
	ldr r0, _021D77A8 ; =0x00000495
	mov r1, #0
	bl FUN_02005350
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r3, _021D77B0 ; =0x00007FFF
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl FUN_0200E1D0
	mov r0, #6
	str r0, [r5]
	b _021D779C
_021D777E:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D779C
	add r0, r4, #0
	ldr r1, [r4, #4]
	ldr r2, [r4]
	add r0, #0xb4
	bl MOD63_021D8360
	cmp r0, #1
	bne _021D779C
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D779C:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D77A4: .word gMain
_021D77A8: .word 0x00000495
_021D77AC: .word 0x000005F4
_021D77B0: .word 0x00007FFF
	thumb_func_end MOD63_021D759C

	thumb_func_start MOD63_021D77B4
MOD63_021D77B4: ; 0x021D77B4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl OverlayManager_GetData
	add r6, r0, #0
	mov r0, #0x1d
	lsl r0, r0, #4
	ldrh r5, [r6, r0]
	mov r0, #0
	add r1, r0, #0
	ldr r4, [r6]
	bl Main_SetVBlankIntrCB
	add r0, r6, #0
	bl MOD63_021D78B0
	add r0, r6, #0
	bl MOD63_021D7B9C
	add r0, r7, #0
	bl OverlayManager_FreeData
	add r0, r4, #0
	bl FUN_020168D0
	cmp r5, #1
	beq _021D77F2
	cmp r5, #2
	beq _021D77FE
	cmp r5, #3
	beq _021D780A
_021D77F2:
	mov r0, #0
	ldr r1, _021D781C ; =UNK_020FF3D4
	mvn r0, r0
	bl RegisterMainOverlay
	b _021D7818
_021D77FE:
	mov r0, #0
	ldr r1, _021D7820 ; =UNK_020FF368
	mvn r0, r0
	bl RegisterMainOverlay
	b _021D7818
_021D780A:
	mov r0, #0
	bl FUN_0200415C
	ldr r0, _021D7824 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _021D7828 ; =MOD63_021DBE18
	bl RegisterMainOverlay
_021D7818:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D781C: .word UNK_020FF3D4
_021D7820: .word UNK_020FF368
_021D7824: .word SDK_OVERLAY_MODULE_63_ID
_021D7828: .word MOD63_021DBE18
	thumb_func_end MOD63_021D77B4

	thumb_func_start MOD63_021D782C
MOD63_021D782C: ; 0x021D782C
	ldr r3, _021D7834 ; =FUN_0201AB60
	ldr r0, [r0, #4]
	bx r3
	nop
_021D7834: .word FUN_0201AB60
	thumb_func_end MOD63_021D782C

	thumb_func_start MOD63_021D7838
MOD63_021D7838: ; 0x021D7838
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7854 ; =MOD63_021DBA90
	add r3, sp, #0
	mov r2, #5
_021D7842:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7842
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7854: .word MOD63_021DBA90
	thumb_func_end MOD63_021D7838

	thumb_func_start MOD63_021D7858
MOD63_021D7858: ; 0x021D7858
	ldr r0, _021D787C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	and r0, r1
	cmp r0, #1
	beq _021D7874
	mov r0, #8
	and r0, r1
	cmp r0, #8
	beq _021D7874
	mov r0, #4
	and r0, r1
	cmp r0, #4
	bne _021D7878
_021D7874:
	mov r0, #1
	bx lr
_021D7878:
	mov r0, #0
	bx lr
	.align 2, 0
_021D787C: .word gMain
	thumb_func_end MOD63_021D7858

	thumb_func_start MOD63_021D7880
MOD63_021D7880: ; 0x021D7880
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #4
	mov r1, #0
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r4]
	mov r2, #1
	add r3, r1, #0
	bl FUN_02022318
	str r0, [r4, #8]
	ldr r1, _021D78AC ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r0, r2
	strh r0, [r1]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021D78AC: .word 0x04000008
	thumb_func_end MOD63_021D7880

	thumb_func_start MOD63_021D78B0
MOD63_021D78B0: ; 0x021D78B0
	ldr r3, _021D78B8 ; =FUN_020223BC
	ldr r0, [r0, #8]
	bx r3
	nop
_021D78B8: .word FUN_020223BC
	thumb_func_end MOD63_021D78B0

	thumb_func_start MOD63_021D78BC
MOD63_021D78BC: ; 0x021D78BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r3, #0
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	add r0, #0x68
	add r1, r4, #0
	mov r2, #4
	bl FUN_02016B20
	mov r0, #0x30
	add r1, r6, #0
	add r2, r4, #0
	bl AllocAndReadWholeNarcMemberByIdPair
	str r0, [r5, #0x5c]
	mov r0, #0x30
	add r1, r7, #0
	add r2, r4, #0
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, r5, #0
	add r2, r5, #0
	str r0, [r5, #0x60]
	add r0, r5, #4
	add r1, #0x58
	add r2, #0x5c
	bl FUN_0201B234
	ldr r0, [r5, #0x60]
	mov r1, #0
	bl NNS_G3dGetAnmByIdx
	add r4, r0, #0
	add r0, r5, #0
	ldr r2, [r5, #0x58]
	add r0, #0x68
	add r1, r4, #0
	bl NNS_G3dAllocAnmObj
	str r0, [r5, #0x64]
	ldr r0, [r5, #0x5c]
	bl NNS_G3dGetTex
	add r3, r0, #0
	ldr r0, [r5, #0x64]
	ldr r2, [r5, #0x58]
	add r1, r4, #0
	bl NNS_G3dAnmObjInit
	ldr r1, [r5, #0x64]
	add r0, r5, #4
	bl NNS_G3dRenderObjAddAnmObj
	add r4, r5, #0
	add r6, sp, #0xc
	mov r3, #0
	str r3, [r6]
	add r2, sp, #0
	str r3, [r6, #4]
	str r3, [r2]
	str r3, [r6, #8]
	str r3, [r2, #4]
	ldmia r6!, {r0, r1}
	str r3, [r2, #8]
	add r4, #0x78
	stmia r4!, {r0, r1}
	ldr r0, [r6]
	ldr r6, _021D796C ; =MOD63_021DB9A8
	str r0, [r4]
	add r4, r5, #0
	ldmia r6!, {r0, r1}
	add r4, #0x84
	stmia r4!, {r0, r1}
	ldr r0, [r6]
	str r0, [r4]
	add r4, r5, #0
	ldmia r2!, {r0, r1}
	add r4, #0x90
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	add r5, #0xa0
	str r0, [r4]
	str r3, [r5]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D796C: .word MOD63_021DB9A8
	thumb_func_end MOD63_021D78BC

	thumb_func_start MOD63_021D7970
MOD63_021D7970: ; 0x021D7970
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x64]
	add r0, #0x68
	bl NNS_G3dFreeAnmObj
	ldr r0, [r4, #0x60]
	bl FreeToHeap
	ldr r0, [r4, #0x5c]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD63_021D7970

	thumb_func_start MOD63_021D798C
MOD63_021D798C: ; 0x021D798C
	push {r4, r5, lr}
	sub sp, #0x24
	ldr r5, _021D7A44 ; =MOD63_021DBA6C
	add r4, r0, #0
	add r3, sp, #0
	mov r2, #4
_021D7998:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7998
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4]
	cmp r0, #0
	beq _021D7A3E
	cmp r0, #1
	beq _021D79B6
	cmp r0, #2
	beq _021D79CA
	add sp, #0x24
	pop {r4, r5, pc}
_021D79B6:
	bl FUN_020222AC
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
	mov r0, #0
	add sp, #0x24
	str r0, [r4]
	pop {r4, r5, pc}
_021D79CA:
	bl FUN_020222AC
	bl FUN_0201EBA4
	add r1, r4, #0
	add r0, sp, #0
	add r1, #0x90
	bl FUN_0201CAA8
	add r1, r4, #0
	add r3, r4, #0
	add r0, r4, #4
	add r1, #0x78
	add r2, sp, #0
	add r3, #0x84
	bl FUN_0201B26C
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	cmp r0, #0
	beq _021D7A00
	cmp r0, #1
	beq _021D7A08
	cmp r0, #2
	beq _021D7A18
	b _021D7A36
_021D7A00:
	ldr r0, [r4, #0x64]
	mov r1, #0
	str r1, [r0]
	b _021D7A36
_021D7A08:
	ldr r0, [r4, #0x64]
	ldr r0, [r0]
	cmp r0, #0
	bne _021D7A18
	mov r0, #0
	add r4, #0xa0
	str r0, [r4]
	b _021D7A36
_021D7A18:
	ldr r2, [r4, #0x64]
	mov r0, #1
	ldr r1, [r2]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [r2]
	ldr r2, [r4, #0x64]
	ldr r0, [r2, #8]
	ldr r1, [r2]
	ldrh r0, [r0, #4]
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _021D7A36
	mov r0, #0
	str r0, [r2]
_021D7A36:
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
_021D7A3E:
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D7A44: .word MOD63_021DBA6C
	thumb_func_end MOD63_021D798C

	thumb_func_start MOD63_021D7A48
MOD63_021D7A48: ; 0x021D7A48
	push {r3, r4, r5, lr}
	sub sp, #0xb8
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02016B94
	add r3, sp, #0xa8
	ldr r5, _021D7B80 ; =MOD63_021DB9B4
	str r0, [r4, #4]
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D7B84 ; =MOD63_021DB9E0
	add r3, sp, #0x8c
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
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B88 ; =MOD63_021DB9C4
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B8C ; =MOD63_021DBA50
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #6
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B90 ; =MOD63_021DBA34
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
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B94 ; =MOD63_021DB9FC
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D7B98 ; =MOD63_021DBA18
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #7
	str r0, [r3]
	ldr r0, [r4, #4]
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #1
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0xb8
	pop {r3, r4, r5, pc}
	nop
_021D7B80: .word MOD63_021DB9B4
_021D7B84: .word MOD63_021DB9E0
_021D7B88: .word MOD63_021DB9C4
_021D7B8C: .word MOD63_021DBA50
_021D7B90: .word MOD63_021DBA34
_021D7B94: .word MOD63_021DB9FC
_021D7B98: .word MOD63_021DBA18
	thumb_func_end MOD63_021D7A48

	thumb_func_start MOD63_021D7B9C
MOD63_021D7B9C: ; 0x021D7B9C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #1
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineBToggleLayers
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_020178A0
	ldr r0, [r4, #4]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD63_021D7B9C

	thumb_func_start MOD63_021D7C18
MOD63_021D7C18: ; 0x021D7C18
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	bl MOD63_021D86E0
	add r0, r6, #0
	add r1, r4, #0
	add r2, r5, #0
	bl MOD63_021D83A8
	ldr r0, _021D7D5C ; =gGameVersion
	ldrb r0, [r0]
	cmp r0, #0xa ; VERSION_DIAMOND
	bne _021D7C46
	add r0, r5, #4
	mov r1, #6
	mov r2, #0x13
	add r3, r4, #0
	bl MOD63_021D78BC
	b _021D7C52
_021D7C46:
	add r0, r5, #4
	mov r1, #5
	mov r2, #0x12
	add r3, r4, #0
	bl MOD63_021D78BC
_021D7C52:
	ldr r0, _021D7D60 ; =0x04000060
	ldr r2, _021D7D64 ; =0xFFFFCFFF
	ldrh r1, [r0]
	add r3, r1, #0
	and r3, r2
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0]
	and r2, r1
	mov r1, #8
	orr r1, r2
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0xf0
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xbc
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xf4
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc0
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xf8
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc4
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xd8
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc8
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xdc
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xcc
	str r1, [r0]
	add r0, r5, #0
	add r0, #0xe0
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xd0
	str r1, [r0]
	add r0, r4, #0
	bl FUN_0201EB64
	add r1, r5, #0
	add r1, #0xa0
	str r0, [r1]
	mov r3, #0
	add r0, r5, #0
	add r1, r5, #0
	mov r2, #0xb6
	str r3, [sp]
	add r0, #0xa0
	ldr r0, [r0]
	add r1, #0xc8
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xbc
	lsl r2, r2, #4
	bl FUN_0201ED5C
	add r2, r5, #0
	add r2, #0xa0
	mov r1, #0x19
	ldr r2, [r2]
	mov r0, #0
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	add r1, r5, #0
	add r1, #0xa0
	ldr r1, [r1]
	mov r0, #0
	bl FUN_0201EE2C
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	bl FUN_0201EB8C
	mov r3, #0x42
	lsl r3, r3, #2
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	mov r0, #0
	bl NNS_G3dGlbLightVector
	ldr r1, _021D7D68 ; =0x00007FFF
	mov r0, #0
	bl NNS_G3dGlbLightColor
	ldr r3, _021D7D6C ; =0x0000010E
	mov r0, #1
	add r2, r3, #2
	ldrsh r1, [r5, r3]
	add r3, r3, #4
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	bl NNS_G3dGlbLightVector
	ldr r1, _021D7D68 ; =0x00007FFF
	mov r0, #1
	bl NNS_G3dGlbLightColor
	ldr r2, _021D7D60 ; =0x04000060
	ldr r0, _021D7D64 ; =0xFFFFCFFF
	ldrh r1, [r2]
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	strh r0, [r2]
	ldr r0, _021D7D70 ; =gMain + 0x60
	mov r1, #1
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	mov r0, #2
	str r0, [r5, #4]
	mov r0, #1
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_021D7D5C: .word gGameVersion
_021D7D60: .word 0x04000060
_021D7D64: .word 0xFFFFCFFF
_021D7D68: .word 0x00007FFF
_021D7D6C: .word 0x0000010E
_021D7D70: .word gMain + 0x60
	thumb_func_end MOD63_021D7C18

	thumb_func_start MOD63_021D7D74
MOD63_021D7D74: ; 0x021D7D74
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	mov r6, #0
	bl MOD63_021D7858
	cmp r0, #1
	bne _021D7D92
	bl FUN_0200E31C
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D7D92:
	ldr r0, [r4]
	cmp r0, #9
	bhi _021D7E38
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7DA4: ; jump table
	.short _021D7DB8 - _021D7DA4 - 2 ; case 0
	.short _021D7DF6 - _021D7DA4 - 2 ; case 1
	.short _021D7E24 - _021D7DA4 - 2 ; case 2
	.short _021D7E8C - _021D7DA4 - 2 ; case 3
	.short _021D7ECC - _021D7DA4 - 2 ; case 4
	.short _021D7EF4 - _021D7DA4 - 2 ; case 5
	.short _021D7F44 - _021D7DA4 - 2 ; case 6
	.short _021D7F72 - _021D7DA4 - 2 ; case 7
	.short _021D7FA6 - _021D7DA4 - 2 ; case 8
	.short _021D8232 - _021D7DA4 - 2 ; case 9
_021D7DB8:
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineBToggleLayers
	ldr r1, _021D80F0 ; =0x00000116
	add r0, r6, #0
	strh r0, [r4, r1]
	add r1, r4, #0
	mov r2, #0xf
	add r1, #0xa8
	strh r2, [r1]
	str r2, [sp]
	mov r1, #3
	str r1, [sp, #4]
	mov r1, #1
	ldr r3, _021D80F4 ; =0x00007FFF
	add r2, r1, #0
	str r5, [sp, #8]
	bl FUN_0200E1D0
	mov r0, #1
	str r0, [r4]
	b _021D824E
_021D7DF6:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7E38
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7E18
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	b _021D824E
_021D7E18:
	add r0, r4, #0
	mov r1, #2
	add r0, #0xa8
	strh r1, [r0]
	str r1, [r4]
	b _021D824E
_021D7E24:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _021D7E38
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	beq _021D7E3A
_021D7E38:
	b _021D824E
_021D7E3A:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7E7E
	mov r0, #1
	str r0, [sp]
	mov r0, #0xa
	mov r1, #0x10
	add r2, r6, #0
	mov r3, #6
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #0xa
	mov r1, #0x10
	add r2, r6, #0
	mov r3, #7
	bl FUN_0200A208
	ldr r0, _021D80F0 ; =0x00000116
	mov r1, #2
	strh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #3
	str r0, [r4]
	b _021D824E
_021D7E7E:
	add r0, r4, #0
	add r1, r6, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #4
	str r0, [r4]
	b _021D824E
_021D7E8C:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #1
	bne _021D7F94
	mov r0, #2
	bl FUN_0200A344
	cmp r0, #1
	bne _021D7F94
	mov r0, #1
	str r0, [sp]
	mov r0, #0xa
	add r1, r6, #0
	mov r2, #0x10
	mov r3, #6
	bl FUN_0200A208
	mov r0, #2
	str r0, [sp]
	mov r0, #0xa
	add r1, r6, #0
	mov r2, #0x10
	mov r3, #7
	bl FUN_0200A208
	ldr r0, _021D80F0 ; =0x00000116
	mov r1, #3
	strh r1, [r4, r0]
	mov r0, #2
	str r0, [r4]
	b _021D824E
_021D7ECC:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7EE6
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	b _021D824E
_021D7EE6:
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #5
	str r0, [r4]
	b _021D824E
_021D7EF4:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7F94
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7F36
	mov r0, #5
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r6, #0
	ldr r3, _021D80F4 ; =0x00007FFF
	add r1, r0, #0
	add r2, r0, #0
	str r5, [sp, #8]
	bl FUN_0200E1D0
	ldr r0, _021D80F0 ; =0x00000116
	mov r1, #2
	strh r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #6
	str r0, [r4]
	b _021D824E
_021D7F36:
	add r0, r4, #0
	mov r1, #0x28
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #7
	str r0, [r4]
	b _021D824E
_021D7F44:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7F94
	add r0, r7, #0
	add r1, r5, #0
	add r2, r4, #0
	bl MOD63_021D85D8
	mov r0, #0x10
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r1, #1
	ldr r3, _021D80F4 ; =0x00007FFF
	add r0, r6, #0
	add r2, r1, #0
	str r5, [sp, #8]
	bl FUN_0200E1D0
	mov r0, #5
	str r0, [r4]
	b _021D824E
_021D7F72:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D7FA0
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0xf
	beq _021D7F96
_021D7F94:
	b _021D824E
_021D7F96:
	add r0, r4, #0
	mov r1, #2
	add r0, #0xa4
	str r1, [r0]
	b _021D824E
_021D7FA0:
	mov r0, #8
	str r0, [r4]
	b _021D824E
_021D7FA6:
	add r0, r4, #0
	add r0, #0xfc
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xbc
	ldr r1, [r0]
	mov r5, #1
	cmp r1, r2
	ble _021D7FDE
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D7FD4
	add r1, r4, #0
	add r1, #0xbc
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	b _021D7FDA
_021D7FD4:
	add r0, r4, #0
	add r0, #0xbc
	str r2, [r0]
_021D7FDA:
	mov r5, #0
	b _021D8006
_021D7FDE:
	cmp r1, r2
	bge _021D8006
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D7FFE
	add r1, r4, #0
	add r1, #0xbc
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	b _021D8004
_021D7FFE:
	add r0, r4, #0
	add r0, #0xbc
	str r2, [r0]
_021D8004:
	mov r5, #0
_021D8006:
	mov r0, #1
	add r1, r4, #0
	lsl r0, r0, #8
	add r1, #0xc0
	ldr r2, [r4, r0]
	ldr r1, [r1]
	cmp r1, r2
	ble _021D803A
	add r0, #0x18
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D8030
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	b _021D8036
_021D8030:
	add r0, r4, #0
	add r0, #0xc0
	str r2, [r0]
_021D8036:
	mov r5, #0
	b _021D8060
_021D803A:
	cmp r1, r2
	bge _021D8060
	add r0, #0x18
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D8058
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xc0
	str r1, [r0]
	b _021D805E
_021D8058:
	add r0, r4, #0
	add r0, #0xc0
	str r2, [r0]
_021D805E:
	mov r5, #0
_021D8060:
	mov r0, #0x41
	add r1, r4, #0
	lsl r0, r0, #2
	add r1, #0xc4
	ldr r2, [r4, r0]
	ldr r1, [r1]
	cmp r1, r2
	ble _021D8094
	add r0, #0x14
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D808A
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	b _021D8090
_021D808A:
	add r0, r4, #0
	add r0, #0xc4
	str r2, [r0]
_021D8090:
	mov r5, #0
	b _021D80BA
_021D8094:
	cmp r1, r2
	bge _021D80BA
	add r0, #0x14
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D80B2
	add r1, r4, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xc4
	str r1, [r0]
	b _021D80B8
_021D80B2:
	add r0, r4, #0
	add r0, #0xc4
	str r2, [r0]
_021D80B8:
	mov r5, #0
_021D80BA:
	add r0, r4, #0
	add r0, #0xe4
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xc8
	ldr r1, [r0]
	cmp r1, r2
	ble _021D80F8
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D80E6
	add r1, r4, #0
	add r1, #0xc8
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	b _021D80EC
_021D80E6:
	add r0, r4, #0
	add r0, #0xc8
	str r2, [r0]
_021D80EC:
	mov r5, #0
	b _021D8120
	.align 2, 0
_021D80F0: .word 0x00000116
_021D80F4: .word 0x00007FFF
_021D80F8:
	cmp r1, r2
	bge _021D8120
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D8118
	add r1, r4, #0
	add r1, #0xc8
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	b _021D811E
_021D8118:
	add r0, r4, #0
	add r0, #0xc8
	str r2, [r0]
_021D811E:
	mov r5, #0
_021D8120:
	add r0, r4, #0
	add r0, #0xe8
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xcc
	ldr r1, [r0]
	cmp r1, r2
	ble _021D8156
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D814C
	add r1, r4, #0
	add r1, #0xcc
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xcc
	str r1, [r0]
	b _021D8152
_021D814C:
	add r0, r4, #0
	add r0, #0xcc
	str r2, [r0]
_021D8152:
	mov r5, #0
	b _021D817E
_021D8156:
	cmp r1, r2
	bge _021D817E
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D8176
	add r1, r4, #0
	add r1, #0xcc
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xcc
	str r1, [r0]
	b _021D817C
_021D8176:
	add r0, r4, #0
	add r0, #0xcc
	str r2, [r0]
_021D817C:
	mov r5, #0
_021D817E:
	add r0, r4, #0
	add r0, #0xec
	ldr r2, [r0]
	add r0, r4, #0
	add r0, #0xd0
	ldr r1, [r0]
	cmp r1, r2
	ble _021D81B4
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r1, r2
	cmp r1, r0
	ble _021D81AA
	add r1, r4, #0
	add r1, #0xd0
	ldr r1, [r1]
	sub r1, r1, r0
	add r0, r4, #0
	add r0, #0xd0
	str r1, [r0]
	b _021D81B0
_021D81AA:
	add r0, r4, #0
	add r0, #0xd0
	str r2, [r0]
_021D81B0:
	mov r5, #0
	b _021D81DC
_021D81B4:
	cmp r1, r2
	bge _021D81DC
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	sub r1, r2, r1
	cmp r1, r0
	ble _021D81D4
	add r1, r4, #0
	add r1, #0xd0
	ldr r1, [r1]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xd0
	str r1, [r0]
	b _021D81DA
_021D81D4:
	add r0, r4, #0
	add r0, #0xd0
	str r2, [r0]
_021D81DA:
	mov r5, #0
_021D81DC:
	add r1, r4, #0
	add r1, #0xa0
	add r0, r4, #0
	ldr r1, [r1]
	add r0, #0xbc
	bl FUN_0201F04C
	add r1, r4, #0
	add r1, #0xa0
	add r0, r4, #0
	ldr r1, [r1]
	add r0, #0xc8
	bl FUN_0201F05C
	cmp r5, #1
	bne _021D824E
	mov r0, #4
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineBToggleLayers
	add r0, r4, #0
	mov r1, #0x5a
	add r0, #0xa8
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa4
	str r1, [r0]
	mov r0, #9
	str r0, [r4]
	b _021D824E
_021D8232:
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	beq _021D824C
	add r0, r4, #0
	add r0, #0xa8
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	b _021D824E
_021D824C:
	mov r6, #1
_021D824E:
	add r0, r4, #0
	bl MOD63_021D8650
	add r0, r4, #4
	bl MOD63_021D798C
	add r0, r6, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD63_021D7D74

	thumb_func_start MOD63_021D8260
MOD63_021D8260: ; 0x021D8260
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	mov r4, #0
	cmp r0, #0
	beq _021D8272
	cmp r0, #1
	beq _021D82FC
	b _021D8350
_021D8272:
	add r1, r5, #0
	add r1, #0xa0
	add r0, r5, #0
	ldr r1, [r1]
	add r0, #0xfc
	bl FUN_0201F04C
	add r1, r5, #0
	add r1, #0xa0
	add r0, r5, #0
	ldr r1, [r1]
	add r0, #0xe4
	bl FUN_0201F05C
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #4
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #2
	add r1, r4, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	bl FUN_0200E394
	mov r0, #1
	bl FUN_0200E394
	add r0, r4, #0
	mov r1, #6
	mov r2, #1
	bl FUN_0200A274
	add r0, r4, #0
	mov r1, #7
	mov r2, #2
	bl FUN_0200A274
	add r0, r5, #0
	mov r1, #2
	add r0, #0xa4
	str r1, [r0]
	ldr r1, _021D835C ; =0x00007FFF
	mov r0, #1
	bl NNS_G3dGlbLightColor
	add r0, r5, #0
	add r1, r4, #0
	add r0, #0xa8
	strh r1, [r0]
	mov r0, #1
	str r0, [r5]
	b _021D8350
_021D82FC:
	add r0, r5, #0
	add r0, #0xd4
	ldr r0, [r0]
	cmp r0, #1
	bne _021D8328
	add r0, r5, #0
	add r0, #0xa8
	ldrh r0, [r0]
	cmp r0, #0
	bne _021D831A
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineBToggleLayers
	b _021D8330
_021D831A:
	cmp r0, #0x10
	bne _021D8330
	mov r0, #1
	add r1, r4, #0
	bl GX_EngineBToggleLayers
	b _021D8330
_021D8328:
	mov r0, #1
	add r1, r4, #0
	bl GX_EngineBToggleLayers
_021D8330:
	add r0, r5, #0
	add r0, #0xa8
	ldrh r0, [r0]
	mov r4, #1
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xa8
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0xa8
	ldrh r1, [r0]
	mov r0, #0x1f
	and r1, r0
	add r0, r5, #0
	add r0, #0xa8
	strh r1, [r0]
_021D8350:
	add r0, r5, #4
	bl MOD63_021D798C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021D835C: .word 0x00007FFF
	thumb_func_end MOD63_021D8260

	thumb_func_start MOD63_021D8360
MOD63_021D8360: ; 0x021D8360
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xa0
	ldr r0, [r0]
	add r4, r1, #0
	add r6, r2, #0
	bl FUN_0201EB70
	add r0, r5, #4
	bl MOD63_021D7970
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD63_021D8644
	ldr r2, _021D839C ; =0x04000050
	mov r3, #0
	strh r3, [r2]
	add r2, #0x10
	ldrh r1, [r2]
	ldr r0, _021D83A0 ; =0x0000CFDF
	and r0, r1
	strh r0, [r2]
	ldr r0, _021D83A4 ; =gMain + 0x60
	strb r3, [r0, #5]
	bl GX_SwapDisplay
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D839C: .word 0x04000050
_021D83A0: .word 0x0000CFDF
_021D83A4: .word gMain + 0x60
	thumb_func_end MOD63_021D8360

	thumb_func_start MOD63_021D83A8
MOD63_021D83A8: ; 0x021D83A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	add r4, r1, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #7
	add r6, r2, #0
	mov r0, #0x30
	add r2, r5, #0
	add r3, r1, #0
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0xb
	add r2, r5, #0
	mov r3, #3
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #8
	add r2, r5, #0
	mov r3, #7
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0xc
	add r2, r5, #0
	mov r3, #3
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadScrnData
	ldr r0, _021D85C8 ; =gGameVersion
	ldrb r7, [r0]
	cmp r7, #0xa ; VERSION_DIAMOND
	bne _021D841A
	mov r0, #0xd
	mov r1, #9
	str r0, [sp, #0x18]
	b _021D8420
_021D841A:
	mov r0, #0xe
	mov r1, #0xa
	str r0, [sp, #0x18]
_021D8420:
	mov r3, #0
	str r3, [sp]
	mov r0, #0x30
	mov r2, #4
	str r4, [sp, #4]
	bl GfGfxLoader_GXLoadPal
	mov r2, #0
	str r2, [sp]
	ldr r1, [sp, #0x18]
	mov r0, #0x30
	add r3, r2, #0
	str r4, [sp, #4]
	bl GfGfxLoader_GXLoadPal
	cmp r7, #0xa
	bne _021D8448
	mov r1, #1
	mov r7, #2
	b _021D844C
_021D8448:
	mov r1, #3
	mov r7, #4
_021D844C:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	add r2, r5, #0
	mov r3, #6
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	mov r0, #0x30
	add r1, r7, #0
	mov r2, #6
	lsl r3, r3, #0xe
	str r4, [sp, #4]
	bl GfGfxLoader_GXLoadPal
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x30
	add r2, r5, #0
	mov r3, #6
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	mov r1, #0x11
	add r2, r5, #0
	mov r3, #5
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r1, #0x10
	mov r0, #0x80
	mov r2, #6
	lsl r3, r1, #9
	str r4, [sp, #4]
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	mov r1, #0xf
	add r2, r5, #0
	mov r3, #5
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0xf
	add r2, r5, #0
	mov r3, #1
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x30
	mov r1, #0x11
	add r2, r5, #0
	mov r3, #1
	str r4, [sp, #0xc]
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x30
	mov r1, #0x10
	mov r2, #0
	mov r3, #0x20
	str r4, [sp, #4]
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	add r3, r4, #0
	bl FUN_02017F18
	ldr r2, _021D85CC ; =0x00000227
	mov r0, #1
	mov r1, #0x1a
	add r3, r4, #0
	bl NewMsgDataFromNarc
	add r7, r0, #0
	mov r0, #0x40
	add r1, r4, #0
	bl String_ctor
	add r1, r6, #0
	add r4, r0, #0
	ldr r2, _021D85D0 ; =MOD63_021DB9A0
	add r0, r5, #0
	add r1, #0xac
	bl FUN_02019150
	mov r1, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xac
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	add r0, r7, #0
	mov r1, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r3, r6, #0
	add r3, #0xb3
	ldrb r3, [r3]
	mov r0, #0
	add r1, r4, #0
	mov r2, #1
	lsl r3, r3, #3
	bl FUN_02002F40
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	ldr r0, _021D85D4 ; =0x00010100
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r6, #0xac
	str r1, [sp, #0x10]
	add r0, r6, #0
	add r2, r4, #0
	str r1, [sp, #0x14]
	bl AddTextPrinterParameterized3
	add r0, r4, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	mov r1, #0x15
	add r0, sp, #0x1c
	strh r1, [r0, #2]
	strh r1, [r0]
	add r1, sp, #0x1c
	mov r0, #4
	add r1, #2
	mov r2, #2
	mov r3, #0x42
	bl FUN_02017FB4
	mov r0, #4
	add r1, sp, #0x1c
	mov r2, #2
	mov r3, #0x44
	bl FUN_02017FB4
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D85C8: .word gGameVersion
_021D85CC: .word 0x00000227
_021D85D0: .word MOD63_021DB9A0
_021D85D4: .word 0x00010100
	thumb_func_end MOD63_021D83A8

	thumb_func_start MOD63_021D85D8
MOD63_021D85D8: ; 0x021D85D8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r2, #0xa8
	add r7, r0, #0
	ldrh r0, [r2]
	add r5, r1, #0
	cmp r0, #0
	bne _021D863A
	ldr r0, _021D8640 ; =gGameVersion
	ldrb r0, [r0]
	cmp r0, #0xa ; VERSION_DIAMOND
	bne _021D85F8
	mov r1, #0xb
	mov r6, #0xa
	mov r4, #0xc
	b _021D85FE
_021D85F8:
	mov r1, #8
	mov r6, #7
	mov r4, #9
_021D85FE:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	add r2, r7, #0
	mov r3, #5
	str r5, [sp, #0xc]
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #0x80
	add r1, r6, #0
	mov r2, #6
	lsl r3, r0, #6
	str r5, [sp, #4]
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x80
	add r1, r4, #0
	add r2, r7, #0
	mov r3, #5
	str r5, [sp, #0xc]
	bl GfGfxLoader_LoadScrnData
_021D863A:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8640: .word gGameVersion
	thumb_func_end MOD63_021D85D8

	thumb_func_start MOD63_021D8644
MOD63_021D8644: ; 0x021D8644
	ldr r3, _021D864C ; =FUN_02019178
	add r2, #0xac
	add r0, r2, #0
	bx r3
	.align 2, 0
_021D864C: .word FUN_02019178
	thumb_func_end MOD63_021D8644

	thumb_func_start MOD63_021D8650
MOD63_021D8650: ; 0x021D8650
	push {r4, lr}
	ldr r1, _021D86DC ; =0x00000116
	ldrh r2, [r0, r1]
	cmp r2, #3
	bhi _021D86B2
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021D8666: ; jump table
	.short _021D866E - _021D8666 - 2 ; case 0
	.short _021D86B2 - _021D8666 - 2 ; case 1
	.short _021D867A - _021D8666 - 2 ; case 2
	.short _021D8698 - _021D8666 - 2 ; case 3
_021D866E:
	mov r3, #5
	sub r2, r1, #2
	strh r3, [r0, r2]
	mov r2, #1
	strh r2, [r0, r1]
	b _021D86B2
_021D867A:
	sub r2, r1, #2
	ldrh r2, [r0, r2]
	add r3, r2, #2
	sub r2, r1, #2
	strh r3, [r0, r2]
	ldrh r2, [r0, r2]
	cmp r2, #0x1f
	blo _021D86B2
	mov r3, #0x1f
	add r2, r3, #0
	add r2, #0xf5
	strh r3, [r0, r2]
	mov r2, #1
	strh r2, [r0, r1]
	b _021D86B2
_021D8698:
	sub r2, r1, #2
	ldrh r2, [r0, r2]
	sub r3, r2, #2
	sub r2, r1, #2
	strh r3, [r0, r2]
	ldrh r2, [r0, r2]
	cmp r2, #5
	bhi _021D86B2
	mov r3, #5
	sub r2, r1, #2
	strh r3, [r0, r2]
	mov r2, #1
	strh r2, [r0, r1]
_021D86B2:
	mov r1, #0x45
	lsl r1, r1, #2
	ldrh r3, [r0, r1]
	mov r1, #0x1f
	lsl r1, r1, #0xa
	lsl r2, r3, #0xa
	and r1, r2
	add r4, r3, #0
	mov r2, #0x1f
	and r4, r2
	lsl r3, r3, #5
	lsl r2, r2, #5
	and r2, r3
	orr r2, r4
	orr r1, r2
	lsl r1, r1, #0x10
	mov r0, #1
	lsr r1, r1, #0x10
	bl NNS_G3dGlbLightColor
	pop {r4, pc}
	.align 2, 0
_021D86DC: .word 0x00000116
	thumb_func_end MOD63_021D8650

	thumb_func_start MOD63_021D86E0
MOD63_021D86E0: ; 0x021D86E0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, _021D8858 ; =gGameVersion
	ldrb r0, [r0]
	cmp r0, #0xa ; VERSION_DIAMOND
	bne _021D8788
	add r0, r4, #0
	mov r2, #0
	add r0, #0xd8
	str r2, [r0]
	mov r1, #0x41
	add r0, r4, #0
	mov r3, #0x12
	lsl r1, r1, #0xc
	add r0, #0xdc
	str r1, [r0]
	add r0, r4, #0
	mov r5, #0xf6
	lsl r3, r3, #0xe
	add r0, #0xe0
	str r3, [r0]
	mov r3, #0xc3
	add r0, r4, #0
	lsl r3, r3, #0xc
	add r0, #0xe4
	str r3, [r0]
	mov r0, #2
	add r3, r4, #0
	lsl r0, r0, #0x10
	add r3, #0xe8
	str r0, [r3]
	add r3, r4, #0
	lsl r5, r5, #0xc
	add r3, #0xec
	str r5, [r3]
	add r3, r4, #0
	add r3, #0xf0
	str r2, [r3]
	mov r5, #0x5a
	add r3, r4, #0
	lsl r5, r5, #0xc
	add r3, #0xf4
	str r5, [r3]
	add r3, r4, #0
	add r3, #0xf8
	str r2, [r3]
	add r2, r4, #0
	ldr r3, _021D885C ; =0xFFFFE000
	add r2, #0xfc
	str r3, [r2]
	mov r2, #0x1f
	lsl r2, r2, #0xe
	lsr r0, r0, #9
	str r2, [r4, r0]
	lsr r0, r1, #0xa
	ldr r2, _021D8860 ; =0xFFFDA000
	ldr r1, _021D8864 ; =0xFFFFF6E3
	str r2, [r4, r0]
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r3, _021D8868 ; =0x00000A2B
	strh r1, [r4, r0]
	add r2, r0, #2
	strh r3, [r4, r2]
	add r3, r1, #0
	add r3, #0xc6
	add r2, r0, #4
	strh r3, [r4, r2]
	add r1, #0x42
	add r2, r0, #6
	strh r1, [r4, r2]
	add r1, r0, #0
	ldr r2, _021D886C ; =0x000007A1
	add r1, #8
	strh r2, [r4, r1]
	add r1, r0, #0
	ldr r2, _021D8870 ; =0xFFFFF513
	add r1, #0xa
	strh r2, [r4, r1]
	mov r1, #3
	lsl r1, r1, #0xc
	add r0, #0x10
	b _021D8828
_021D8788:
	add r0, r4, #0
	ldr r1, _021D8874 ; =0xFFFBF000
	add r0, #0xd8
	str r1, [r0]
	mov r1, #0x29
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xdc
	str r1, [r0]
	mov r1, #0x13
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xe0
	str r1, [r0]
	add r0, r4, #0
	ldr r1, _021D8878 ; =0xFFF6C000
	add r0, #0xe4
	str r1, [r0]
	mov r1, #0x3a
	add r0, r4, #0
	mov r2, #2
	lsl r1, r1, #0xc
	add r0, #0xe8
	str r1, [r0]
	mov r1, #0xbe
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xf0
	str r1, [r0]
	mov r1, #0xb
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xf4
	str r1, [r0]
	mov r1, #0x12
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0xf8
	str r1, [r0]
	add r0, r4, #0
	lsl r2, r2, #0xe
	add r0, #0xfc
	str r2, [r0]
	ldr r1, _021D887C ; =0xFFFFB000
	lsr r0, r2, #7
	str r1, [r4, r0]
	mov r0, #0x41
	lsr r1, r2, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r2, _021D8880 ; =0x00000653
	add r1, r0, #4
	strh r2, [r4, r1]
	ldr r2, _021D8884 ; =0xFFFFF71C
	add r1, r0, #6
	strh r2, [r4, r1]
	add r1, r0, #0
	sub r2, #0x14
	add r1, #8
	strh r2, [r4, r1]
	add r1, r0, #0
	ldr r2, _021D8888 ; =0x0000091B
	add r1, #0xa
	strh r2, [r4, r1]
	add r1, r0, #0
	ldr r2, _021D888C ; =0xFFFFFB61
	add r1, #0xc
	strh r2, [r4, r1]
	add r1, r0, #0
	mov r2, #0xc5
	lsl r2, r2, #4
	add r1, #0xe
	strh r2, [r4, r1]
	mov r1, #3
	lsl r1, r1, #0xc
	add r0, #0x14
_021D8828:
	str r1, [r4, r0]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xfc
	add r1, #0xe4
	add r2, sp, #0xc
	bl VEC_Subtract
	add r0, sp, #0xc
	add r1, sp, #0
	bl VEC_Normalize
	mov r0, #0x42
	ldr r1, [sp]
	lsl r0, r0, #2
	strh r1, [r4, r0]
	add r1, r0, #2
	ldr r2, [sp, #4]
	add r0, r0, #4
	strh r2, [r4, r1]
	ldr r1, [sp, #8]
	strh r1, [r4, r0]
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8858: .word gGameVersion
_021D885C: .word 0xFFFFE000
_021D8860: .word 0xFFFDA000
_021D8864: .word 0xFFFFF6E3
_021D8868: .word 0x00000A2B
_021D886C: .word 0x000007A1
_021D8870: .word 0xFFFFF513
_021D8874: .word 0xFFFBF000
_021D8878: .word 0xFFF6C000
_021D887C: .word 0xFFFFB000
_021D8880: .word 0x00000653
_021D8884: .word 0xFFFFF71C
_021D8888: .word 0x0000091B
_021D888C: .word 0xFFFFFB61
	thumb_func_end MOD63_021D86E0

	.section .rodata

	.global MOD63_021DB9A0
MOD63_021DB9A0: ; 0x021DB9A0
	.byte 0x04, 0x02, 0x13, 0x1C, 0x02, 0x02, 0x01, 0x00

	.global MOD63_021DB9A8
MOD63_021DB9A8: ; 0x021DB9A8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global MOD63_021DB9B4
MOD63_021DB9B4: ; 0x021DB9B4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD63_021DB9C4
MOD63_021DB9C4: ; 0x021DB9C4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DB9E0
MOD63_021DB9E0: ; 0x021DB9E0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DB9FC
MOD63_021DB9FC: ; 0x021DB9FC
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00
	.byte 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBA18
MOD63_021DBA18: ; 0x021DBA18
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBA34
MOD63_021DBA34: ; 0x021DBA34
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBA50
MOD63_021DBA50: ; 0x021DBA50
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x07, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD63_021DBA6C
MOD63_021DBA6C: ; 0x021DBA6C
	.byte 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD63_021DBA90
MOD63_021DBA90: ; 0x021DBA90
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
